/*! \file  CJSKMakeInvoice.cpp
\brief    awe4000r处理数据库信息
\author   zcy
\version  1.0
\date     2014-05-03
*/

#include "IncludeMe.h"
#include "JSKInfoFunc.h"
#include "JSKMakeInvoice.h"
#include "JSKInvManageProc.h"
#include "CGlobalArgLib.h"
#include "JSKDeclareProc.h"
#include "base64.h"
#include "xmlbase.h"
#include "USBMount.h"
#include "DataTransformFunc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

static UINT8 g_invInfo[MAX_INV_INFO_LEN];

CJSKMakeInvoice::CJSKMakeInvoice()
{
}

CJSKMakeInvoice::~CJSKMakeInvoice()
{
}



INT32 CJSKMakeInvoice::GPXXCX_Proc(CDataInvVol *pInvVol, string &strErr)
{
	DBG_PRINT(("===== GPXXCX_Proc Begin() ======"));
	INT32 retcode = JSK_SUCCESS;
	INT8 tmpbuf[64];
	
	retcode = CJSKInfoFunc::GetCurInvInfo(pInvVol, strErr);
	CJSKInvManageProc::fplx2fplxdm(pInvVol->m_invtype, pInvVol->m_fplxdm);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		return retcode;
	}

	DBG_PRINT(("===== GPXXCX_Proc End() ======"));
	return JSK_SUCCESS;
}


INT32 CJSKMakeInvoice::FPKJ_Proc(CDataInvHead *pInvhead, string &strErr, UINT8 wasteflag)
{
	DBG_PRINT(("===== FPKJ_Proc Begin() ======"));
	DBG_ASSERT_EXIT((pInvhead != NULL), (" pInvhead == NULL!"));
	INT32 retcode = JSK_SUCCESS;
	UINT8 tmpBuf[16];
	INT8 sqlbuf[128];

	//获取可滚动表的记录数
    UINT8 nIfRolled=0;
	retcode = g_globalArgLib->RollData(nIfRolled);
	if(retcode!= SUCCESS)
	{
		strErr = "中间件数据库滚动失败!";
		DBG_PRINT((" Roll() error !"));
		return JSK_FAILURE;	
	}

	if(wasteflag == 0)
	{
		DBG_PRINT(("kplx = %u", pInvhead->m_kplx));
		if(pInvhead->m_kplx == 0)
		{
			DBG_PRINT(("m_maxSign = %lld", g_globalArgLib->m_invKind->m_maxSign));
			DBG_PRINT(("pInvhead->m_kphjje = %lld", pInvhead->m_kphjje));
			if(pInvhead->m_kphjje > g_globalArgLib->m_invKind->m_maxSign)
			{
				strErr = "开票单张金额超限!";
				return JSK_FAILURE;
			}
			
			if(pInvhead->m_kphjje <= 0)
			{
				strErr = "正数发票金额不能为零";
				return JSK_FAILURE;
			}
			
			pInvhead->m_kplx = JSK_NORMAL_INV;
		}
		else if(pInvhead->m_kplx == 1)
		{
			pInvhead->m_kplx = JSK_RETURN_INV;
		}
		else
		{
			strErr = "发票类型错误!";
			return JSK_FAILURE;
		}
	}
	else
	{
		if(pInvhead->m_kplx != JSK_WASTE_INV)
		{
			strErr = "发票类型错误!";
			return JSK_FAILURE;
		}
	}
	
	//当前开票时间
	UINT8 curTime[MAX_DATETIME_LEN+1];
	retcode = CJSKInfoFunc::GetJSPCurDate(curTime, strErr);
	if( retcode != JSK_SUCCESS )
	{
		return retcode;
	}
	TDateTime tmpDateTime((INT8 *)curTime, DATETIME_POS);
	pInvhead->m_kprq = tmpDateTime.FormatInt(YYYYMMDD);
	pInvhead->m_kpsj = tmpDateTime.FormatInt(HHMMSS);
	pInvhead->m_CurTime = tmpDateTime.FormatString(YYYYMMDDHHMMSS, "%u%02u%02u%02u%02u%02u");
	if(pInvhead->m_kplx == JSK_WASTE_INV)
	{
		pInvhead->m_zfsj = (INT8 *)curTime;
	}

	//权限控制
	retcode = MakeInvAuthority(pInvhead, strErr);
	if( retcode != JSK_SUCCESS )
	{
		//retcode = JSK_COMMON_ERR_NO;
		return retcode;
	}

	CJSKInvManageProc::fplxdm2fplx(pInvhead->m_fplxdm, pInvhead->m_fplb);

	pInvhead->m_xfyhzh = g_globalArgLib->m_corpInfo->m_Khzh;		//销方银行账号
	DBG_PRINT(("pInvhead->fplb = %u", pInvhead->m_fplb));

	//取发票代码、号码
	CDataInvVol invVol;
	retcode = CJSKInfoFunc::GetCurInvInfo(&invVol, strErr);
	if( retcode != JSK_SUCCESS )
	{
		return retcode;
	}
	pInvhead->m_fpdm = invVol.m_code;
	pInvhead->m_fphm = invVol.m_curInvNo;


	//调用金税盘函数获取税控码、CA签名、索引号
	retcode = CJSKInfoFunc::MakeInvHandInfo(pInvhead, strErr);
	DBG_PRINT(("retcode = %d", retcode));
	if( retcode != JSK_SUCCESS )
	{
		return retcode;
	}

	//////////////////////////////////////////////////////////////////////////
	//数据库事务开始
	CInvHead invHead;
	CDataTransformFunc::Data2InvHead(pInvhead, &invHead);
	invHead.BeginTransaction();

	//存数据库
	UINT32  errorcode;
	errorcode = invHead.Save();
	if (errorcode != SUCCESS)
	{
// 		retcode = JSK_COMMON_ERR_NO;
// 		DBG_PRINT(("pInvhead->Save() wrong"));
// 		return retcode;
	}
	DBG_PRINT(("invHead.Save() SUCCESS"));

	
	//将该发票记录存储到DB的INV_SERV
	CInvServ invServ;
	DBG_PRINT(("m_InvServNum = %lu, m_InvServSum = %lld", g_globalArgLib->m_InvServNum, g_globalArgLib->m_InvServSum));
	errorcode = invServ.Save(&invHead, g_globalArgLib->m_InvServNum, g_globalArgLib->m_InvServSum, strErr);	
	DBG_PRINT(("存储到DB的INV_SERV, errorcode = %u", errorcode));

	//更新RT_INV表
	if(pInvhead->m_kplx == JSK_RETURN_INV )
	{
		DBG_PRINT(("更新RT_INV表"));
		CRtInv curRtInv;
		CRtInv *pRtInv = &curRtInv;

		pRtInv-> m_fpdm = pInvhead->m_yfpdm;					
		pRtInv-> m_fphm = pInvhead->m_yfphm;
		errorcode = pRtInv->AddNew();				//写已退发票信息表
		if( errorcode != SQLITE_OK )
		{
			DBG_PRINT((" pRtInv->AddNew() error!"));
			//retcode = JSK_COMMON_ERR_NO;
			//return retcode;
		}
	}
	//数据库事务结束
	invHead.EndTransaction();
	//////////////////////////////////////////////////////////////////////////

	return JSK_SUCCESS;
}
INT32 CJSKMakeInvoice::FPZF_Proc(CDataInvHead *pInvhead, UINT8 zflx, string &strErr)
{
	DBG_PRINT(("===== FPZF_Proc Begin() ======"));
	DBG_ASSERT_EXIT((pInvhead != NULL), (" pInvhead == NULL!"));
	INT32 retcode = JSK_SUCCESS;

	if(zflx == 0)	//空白票作废
	{
		pInvhead->m_kplx = JSK_WASTE_INV;
		pInvhead->m_xfmc = g_globalArgLib->m_corpInfo->m_Nsrmc;
		retcode = FPKJ_Proc(pInvhead, strErr, 1);

		return retcode;
	}

	//////////////////////////////////////////////////////////////////////////
	if(zflx != 1)
	{
		strErr = "发票作废类型错误!";
		return JSK_FAILURE;
	}
	CJSKInvManageProc::fplxdm2fplx(pInvhead->m_fplxdm, pInvhead->m_fplb);
	//已开票作废
	//查询数据库中已开发票信息
	INT8 sqlbuf[256];
	UINT32  errorcode;
	CInvHead tmpInvHead;
	memset(sqlbuf, 0, sizeof(sqlbuf));
	sprintf(sqlbuf, "where FPDM='%s' and FPHM=%u", pInvhead->m_fpdm.c_str(), pInvhead->m_fphm);
	DBG_PRINT(("sqlbuf = %s", sqlbuf));
	tmpInvHead.m_filter.append(sqlbuf);
	if(tmpInvHead.Load() != SQLITE_OK)
	{
		DBG_PRINT(("here find by jsp"));
		//数据库查询不到，从盘中查询
		retcode = CJSKInfoFunc::GetInvDetailInfoNO(pInvhead, strErr);
		if(retcode != JSK_SUCCESS)
		{
			return retcode;
		}

		CDataTransformFunc::Data2InvHead(pInvhead, &tmpInvHead);
		tmpInvHead.Save();
	}
	else
	{
		CJSKInvManageProc::fplx2fplxdm(tmpInvHead.m_fplb, tmpInvHead.m_fplxdm);
		CDataTransformFunc::InvHead2Data(&tmpInvHead, pInvhead);
	}

	//已开发票作废控制
	if(tmpInvHead.m_kplx == JSK_NORMAL_INV)
	{
		pInvhead->m_kplx = JSK_WASTE_NOR;
	}
	else if(tmpInvHead.m_kplx == JSK_RETURN_INV)
	{
		pInvhead->m_kplx = JSK_WASTE_RET;
	}
	else
	{
		retcode = JSK_COMMON_ERR_NO;
		strErr = "废票不能再次作废!";
		return retcode;
	}

	//权限控制
	retcode = MakeInvAuthority(pInvhead, strErr);
	if( retcode != JSK_SUCCESS )
	{
		return retcode;
	}

	retcode = CJSKInfoFunc::WasteInvHandInfo(pInvhead, strErr);
	if( retcode != JSK_SUCCESS )
	{
		return retcode;
	}

	//////////////////////////////////////////////////////////////////////////
	//数据库事务开始
	tmpInvHead.BeginTransaction();

	//修改数据库对应信息
	tmpInvHead.m_kplx = pInvhead->m_kplx;
	tmpInvHead.m_fpsyh = pInvhead->m_fpsyh;
	tmpInvHead.m_casign = pInvhead->m_casign;
	tmpInvHead.m_zfsj = pInvhead->m_zfsj;
	retcode = tmpInvHead.Update(sqlbuf, &tmpInvHead.m_kplx, &tmpInvHead.m_fpsyh, &tmpInvHead.m_zfsj, &tmpInvHead.m_casign, NULL);
	DBG_PRINT(("更新DB的INV_HEAD：retcode = %d", retcode));
	CInvDet invDet;
	invDet.m_kplx = pInvhead->m_kplx;
	retcode = invDet.Update(sqlbuf, &invDet.m_kplx, NULL);
	DBG_PRINT(("更新DB的INV_DET：retcode = %d", retcode));

	if(pInvhead->m_kplx == JSK_WASTE_RET )
	{
		DBG_PRINT(("更新RT_INV表"));
		CRtInv curRtInv;
		CRtInv *pRtInv = &curRtInv;
		memset(sqlbuf, 0, sizeof(sqlbuf));
		sprintf(sqlbuf, "where FPDM='%s' and FPHM=%u ", pInvhead->m_yfpdm.c_str(), pInvhead->m_yfphm);
		DBG_PRINT(("sqlbuf = %s", sqlbuf));
		pRtInv->m_filter.append(sqlbuf);
		pRtInv->Delete();
	}

	//处理INV_SERV表，如果已上传发票，需要重新记录INV_SERV???
	CInvServ invServ;
	errorcode = invServ.Save(&tmpInvHead, g_globalArgLib->m_InvServNum, g_globalArgLib->m_InvServSum, strErr);	
	DBG_PRINT(("存储到DB的INV_SERV, errorcode = %u", errorcode));
	
	//数据库事务结束
	tmpInvHead.EndTransaction();
	//////////////////////////////////////////////////////////////////////////

	return JSK_SUCCESS;
}

INT32 CJSKMakeInvoice::FPCX_Proc(UINT8 cxfs, string cxtj, UINT32 &invNum, CDataInvHead *pInvhead, string &strErr)
{
	DBG_ASSERT_EXIT((pInvhead != NULL), (" pInvhead == NULL!"));
	INT32 retcode = JSK_SUCCESS;

	INT8 sqlbuf[128];
	string fpdm("");
	UINT32 fphm = 0;
	string tmpStr;
	INT32 errcode = 0;
	CInvHead invHead;

	invNum = 1;
	//cxfs为0时：12发票代码+8位起始号码+8位终止号码; cxfs
	if(cxfs == 0)
	{
		fpdm = cxtj.substr(0, 12);
		tmpStr = cxtj.substr(12, 8);
		fphm = atoi(tmpStr.c_str());

		memset(sqlbuf, 0, sizeof(sqlbuf));
		sprintf(sqlbuf, "where FPDM='%s' and FPHM=%u", fpdm.c_str(), fphm);
		DBG_PRINT(("sqlbuf = %s", sqlbuf));
		invHead.m_filter.append(sqlbuf);
		errcode = invHead.Load();
		if(errcode != SQLITE_OK)
		{
			DBG_PRINT(("here search JSK========="));
			pInvhead->m_fpdm = fpdm;
			pInvhead->m_fphm = fphm;
			retcode = CJSKInfoFunc::GetInvDetailInfoNO(pInvhead, strErr);
			if(retcode != JSK_SUCCESS)
			{
				return retcode;
			}
			CDataTransformFunc::Data2InvHead(pInvhead, &invHead);
			if(invHead.Save() != SUCCESS)
			{
				DBG_PRINT(("InvHead Save Error!"));
				//retcode = JSK_COMMON_ERR_NO;
				//strErr = "发票信息保存数据库错误";
				//return retcode;
			}

			if(pInvhead->m_kplx == JSK_RETURN_INV)
			{
				DBG_PRINT(("更新RT_INV表"));
				CRtInv curRtInv;
				CRtInv *pRtInv = &curRtInv;
				
				pRtInv-> m_fpdm = pInvhead->m_yfpdm;					
				pRtInv-> m_fphm = pInvhead->m_yfphm;
				if( pRtInv->AddNew() != SQLITE_OK )
				{
					DBG_PRINT((" pRtInv->AddNew() error!"));
				}
			}
		}

		CJSKInvManageProc::fplx2fplxdm(invHead.m_fplb, invHead.m_fplxdm);
		CDataTransformFunc::InvHead2Data(&invHead, pInvhead);

		CInvServ invServ;
		DBG_PRINT(("sqlbuf = %s", sqlbuf));
		invServ.m_filter.append(sqlbuf);
		invServ.Requery();
		if(invServ.LoadOneRecord() != SQLITE_OK)
			pInvhead->m_scbz = 1;
		else
		{
			if(invServ.m_upFlag == INV_UPLOAD_FLAG2)
			{
				invServ.m_upFlag = INV_UPLOAD_FLAG0;
				DBG_PRINT(("sqlbuf = %s", sqlbuf));
				invServ.Update(sqlbuf, &invServ.m_upFlag, NULL);
				g_globalArgLib->m_pthreadFlag = 1;
			}
		}
	}
	//为1是：起始日期（YYYYMMDD）+终止日期（YYYYMMDD）
	else if(cxfs == 1)
	{
		retcode = JSK_COMMON_ERR_NO;
		strErr = "不支持时间段查询方式!";
		return retcode;
	}
	else
	{
		retcode = JSK_COMMON_ERR_NO;
		strErr = "非法查询方式!";
		return retcode;
	}
	
	return JSK_SUCCESS;
}

INT32 CJSKMakeInvoice::FPSC_Proc(UINT8 czlx, UINT32 &fpzx, string &strInvInfo, string &strErr)
{
	INT8 sqlbuf[128];
	CInvServ invServ;
	CInvHead invHead;
	INT32 retcode = JSK_SUCCESS;
	INT32 errcode = 0;
	string tmpErr("");
	CDataInvHead dataInvHead;

//	CJSKDeclareProc::DelUploadInv();

	memset(sqlbuf, 0, sizeof(sqlbuf));
	sprintf(sqlbuf, "where UP_FLAG=0 or UP_FLAG=1 ");
	invServ.m_filter.append(sqlbuf);
	invServ.Requery();
	errcode = invServ.LoadOneRecord();
	DBG_PRINT(("errcode = %d", errcode));
	if(errcode == SQLITE_OK)
	{
		if((invServ.m_code=="") || (invServ.m_InvNo==0))
			errcode = SQLITE_DONE;
	}
	if(errcode != SQLITE_OK)
	{
		retcode = CJSKInfoFunc::GetFirstOffInvInfo(&dataInvHead, tmpErr);
		if((dataInvHead.m_fpdm=="") || (dataInvHead.m_fphm==0))
			retcode = JSK_FAILURE;
		if(retcode != JSK_SUCCESS)
		{
			g_globalArgLib->m_pthreadFlag = 0;
			g_globalArgLib->m_InvServNum = 0;
			retcode = JSK_COMMON_ERR_NO;
			strErr = "所有发票都已上传!";
			return retcode;
		}
		memset(sqlbuf, 0, sizeof(sqlbuf));
		sprintf(sqlbuf, "where FPDM='%s' and FPHM=%u ", dataInvHead.m_fpdm.c_str(), dataInvHead.m_fphm);
		DBG_PRINT(("sqlbuf = %s", sqlbuf));
		invServ.m_filter.append(sqlbuf);
		invServ.Requery();
		if(invServ.LoadOneRecord() == SQLITE_OK)
		{
			if(invServ.m_upFlag == INV_UPLOAD_FLAG2)
			{
				g_globalArgLib->m_pthreadFlag = 0;
				retcode = JSK_COMMON_ERR_NO;
				strErr = "发票上传错误,请核对!";
				return retcode;
			}
		}

		invServ.m_code = dataInvHead.m_fpdm;
		invServ.m_InvNo = dataInvHead.m_fphm;
		invServ.m_fpsyh = dataInvHead.m_fpsyh;
	}

	UINT32 invLen = 0;
	fpzx = 1;		//发票张数
	memset(sqlbuf, 0, sizeof(sqlbuf));
	sprintf(sqlbuf, "where FPDM='%s' and FPHM=%u ", invServ.m_code.c_str(), invServ.m_InvNo);
	DBG_PRINT(("sqlbuf = %s", sqlbuf));
	invHead.m_filter.append(sqlbuf);
	retcode = invHead.Load();
	if(retcode != SQLITE_OK)
	{
		DBG_PRINT(("here query from JSK"));
		dataInvHead.m_fpdm = invServ.m_code;
		dataInvHead.m_fphm = invServ.m_InvNo;
		dataInvHead.m_fpsyh = invServ.m_fpsyh;
		retcode = CJSKInfoFunc::GetInvDetailInfoNO(&dataInvHead, g_invInfo, invLen, strErr);
		if(retcode != JSK_SUCCESS)
		{
			return retcode;
		}
		
// 		if(invHead.Save() != SQLITE_OK)
// 		{
// 			retcode = JSK_COMMON_ERR_NO;
// 			strErr = "发票信息保存数据库错误";
// 			return retcode;
// 		}
	}
	else
	{
		CJSKInvManageProc::fplx2fplxdm(invHead.m_fplb, invHead.m_fplxdm);
		CDataTransformFunc::InvHead2Data(&invHead, &dataInvHead);
		DBG_PRINT(("here query from DB success"));
		//将invHead类转换成string类型输出
		CJSKInfoFunc::MutexLock();
		CJSKInfoFunc::InvDetail2Data(&dataInvHead, g_invInfo, invLen);
		CJSKInfoFunc::MutexUnlock();
		DBG_PRINT(("invLen = %u", invLen));
	}

	DBG_PRINT(("invLen = %u", invLen));
	AddInvDetail2Data(&dataInvHead, g_invInfo, invLen);
	strInvInfo.append((INT8 *)g_invInfo);
	DBG_PRINT(("invLen = %u", invLen));


	//更新上传标志
	invServ.m_upFlag = INV_UPLOAD_FLAG1;
	DBG_PRINT(("sqlbuf = %s", sqlbuf));
	invServ.Update(sqlbuf, &invServ.m_upFlag, NULL);
	
	return JSK_SUCCESS;
}

INT32 CJSKMakeInvoice::FPGX_Proc(string scqrbw, string &strErr)
{
	INT32 retcode = JSK_SUCCESS;
	string mxjgmw("");

	if( ParseFpscjg(scqrbw, mxjgmw, strErr) != JSK_SUCCESS )
	{
		//return JSK_FAILURE;
		return JSK_SUCCESS;
	}

	UINT8 upInfo[JSK_LXXXMW_LEN+1];
	memset(upInfo, 0, sizeof(upInfo));
	sprintf((INT8 *)upInfo, "%s", mxjgmw.c_str());
	DBG_PRINT(("upInfo = %s", upInfo));

	int nLen = mxjgmw.length();
	DBG_PRINT(("nLen = %d", nLen));
	Base64_Decode_2((INT8 *)upInfo, &nLen);
	DBG_PRINT(("nLen = %d", nLen));

	retcode = CJSKInfoFunc::SetUpLoadFlag(upInfo, nLen, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}

	//删除INV_SERV中已上传的发票信息
	INT8 sqlbuf[128];
	CInvServ invServ;
	memset(sqlbuf, 0, sizeof(sqlbuf));
	sprintf(sqlbuf, "where UP_FLAG=1 ");
	DBG_PRINT(("sqlbuf = %s", sqlbuf));
	invServ.m_filter.append(sqlbuf);
	invServ.Requery();
	invServ.LoadOneRecord();

	invServ.m_filter.append(sqlbuf);
	retcode = invServ.Delete();
	if(retcode != SQLITE_OK)
	{
		retcode = JSK_COMMON_ERR_NO;
		strErr = "删除已上传发票信息错误";
		//return retcode;
	}
	else
	{
		g_globalArgLib->m_InvServNum--;
		if(invServ.m_issuetype == NORMAL_INV)
			g_globalArgLib->m_InvServSum -= invServ.m_moneySum;
	}

	return JSK_SUCCESS;
}



INT32 CJSKMakeInvoice::MakeInvAuthority(CDataInvHead *pInvHead, string& strErr)
{
	INT32 retcode = JSK_SUCCESS;
	INT8 tmpBuff[32];
	UINT8 sDecBuff[MAX_DATETIME_LEN+1];
	INT8 sqlbuf[128];
	INT32 errcode = 0;
	memset(sqlbuf, 0, sizeof(sqlbuf));

	UINT32 uCurDate = 0;
	UINT32 uCurTime = 0;
	uCurDate = pInvHead->m_kprq;
	uCurTime = pInvHead->m_kpsj;
	DBG_PRINT(("uCurDate = %u", uCurDate));
	DBG_PRINT(("uCurTime = %u", uCurTime));

	switch(pInvHead->m_kplx)
	{
	case JSK_NORMAL_INV:
// 		{
// 			//离线锁死日（判断当前时间是否超过离线锁死日）
// 			
// 			//离线开票限定时长（当前时间与第一张未上传的发票时间比对）
// 			CInvServ invServ;
// 			invServ.Requery();
// 			if(invServ.LoadOneRecord() == SQLITE_OK)
// 			{
// 				DBG_PRINT(("invServ.m_issueDate = %u", invServ.m_issueDate));
// 				DBG_PRINT(("invServ.m_issueTime = %u", invServ.m_issueTime));
// 				DBG_PRINT(("g_globalArgLib->m_invKind->m_Lxkjsj = %u", g_globalArgLib->m_invKind->m_Lxkjsj));
// 				TDateTime upDateTime(invServ.m_issueDate, invServ.m_issueTime);
// 				upDateTime = upDateTime.HourAdd(upDateTime, g_globalArgLib->m_invKind->m_Lxkjsj);
// 				DBG_PRINT(("upDateTime = %s", upDateTime.FormatString(YYYYMMDDHHMMSS).c_str()));
// 				DBG_PRINT(("curDateTime = %s", curDateTime.FormatString(YYYYMMDDHHMMSS).c_str()));
// 				if(curDateTime >= upDateTime)
// 				{
// 					strErr = "离线开具限定时长超限!";
// 					return JSK_FAILURE;
// 				}
// 			}
// 			
// 			//离线开票限定正数累计金额
// 			if(nSum + g_globalArgLib->m_InvServSum > g_globalArgLib->m_invKind->m_maxSum)
// 			{
// 				strErr = "离线累计金额超限!";
// 				return JSK_FAILURE;
// 			}
// 		}
		break;
	case JSK_RETURN_INV:
		{
			sprintf(sqlbuf, "where FPDM='%s' and FPHM=%u", pInvHead->m_yfpdm.c_str(), pInvHead->m_yfphm);
			DBG_PRINT(("sqlbuf = %s", sqlbuf));
			CRtInv tmpRtInv;
			tmpRtInv.m_filter.append(sqlbuf);
			tmpRtInv.Requery();
			errcode = tmpRtInv.LoadOneRecord();
			if(errcode == SQLITE_OK)
			{
				retcode = JSK_COMMON_ERR_NO;
				strErr = "已开过负票,不能再次开具!";
				return retcode;
			}
			
			memset(sDecBuff, 0, sizeof(sDecBuff));
			retcode = CJSKInfoFunc::GetJSPSendTime(sDecBuff, strErr);
			if( retcode != JSK_SUCCESS )
			{
				return retcode;
			}
			TDateTime sDecDate((INT8 *)sDecBuff, DATETIME_POS);
			CInvHead tmpInvHead;
			CDataInvHead dataInvHead;
			tmpInvHead.m_filter.append(sqlbuf);
			tmpInvHead.Requery();
			errcode = tmpInvHead.LoadOneRecord();
			if(errcode != SQLITE_OK)
			{
				dataInvHead.m_fpdm = pInvHead->m_yfpdm;
				dataInvHead.m_fphm = pInvHead->m_yfphm;
				retcode = CJSKInfoFunc::GetInvDetailInfoNO(&dataInvHead, strErr);
				if(retcode != JSK_SUCCESS)
				{
					return retcode;
				}

				CDataTransformFunc::Data2InvHead(&dataInvHead, &tmpInvHead);
				if(tmpInvHead.Save() != SUCCESS)
				{
					DBG_PRINT(("InvHead Save Error!"));
				}
			}

			if(tmpInvHead.m_kplx != JSK_NORMAL_INV)
			{
				retcode = JSK_COMMON_ERR_NO;
				strErr = "原发票非正数发票,不能开具负票!";
				return retcode;
			}

			if(tmpInvHead.m_kphjje != pInvHead->m_kphjje)
			{
				retcode = JSK_COMMON_ERR_NO;
				strErr = "负票金额与原发票不一致!";
				return retcode;
			}

// 			TDateTime invDate(tmpInvHead.m_kprq, tmpInvHead.m_kpsj);
// 			DBG_PRINT(("invDate = %s", invDate.FormatString(YYYYMMDDHHMMSS).c_str()));
// 			DBG_PRINT(("sDecDate = %s", sDecDate.FormatString(YYYYMMDDHHMMSS).c_str()));
// 			if(invDate >= sDecDate)
// 			{
// 				retcode = JSK_COMMON_ERR_NO;
// 				strErr = "原发票未抄报,不能开具负票!";
// 				return retcode;
// 			}
		}
		break;
	case JSK_WASTE_INV:
		break;
	case JSK_WASTE_NOR:
	case JSK_WASTE_RET:
		{
			memset(sDecBuff, 0, sizeof(sDecBuff));
			retcode = CJSKInfoFunc::GetJSPSendTime(sDecBuff, strErr);
			if( retcode != JSK_SUCCESS )
			{
				return retcode;
			}
			TDateTime sDecDate((INT8 *)sDecBuff, DATETIME_POS);

			memset(sDecBuff, 0, sizeof(sDecBuff));
			sprintf((INT8 *)sDecBuff, "%08u%06u", pInvHead->m_kprq, pInvHead->m_kpsj);
			TDateTime invDate((INT8 *)sDecBuff, DATETIME_POS);
			if(invDate < sDecDate)
			{
				retcode = JSK_COMMON_ERR_NO;
				strErr = "原发票已抄报,不能作废";
				return retcode;
			}
		}
		break;
	default:
		break;
	}

	
	return JSK_SUCCESS;
}

void CJSKMakeInvoice::AddInvDetail2Data(CDataInvHead *pInvHead,UINT8 *pDataPtr,UINT32 &nDataLen)
{
	INT8 tmpBuf[128];
	UINT32 tmpLen = nDataLen;

	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;

	//开票日期
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
    sprintf(tmpBuf, "%u", pInvHead->m_kprq);
    memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf, strlen(tmpBuf));
	tmpLen += strlen(tmpBuf);
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;

	//开票时间
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
    sprintf(tmpBuf, "%u", pInvHead->m_kpsj);
    memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf, strlen(tmpBuf));
	tmpLen += strlen(tmpBuf);
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;

	//发票类别
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
    sprintf(tmpBuf, "%u", pInvHead->m_fplb);
    memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf, strlen(tmpBuf));
	tmpLen += strlen(tmpBuf);
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;

	//开票类型
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
    sprintf(tmpBuf, "%u", pInvHead->m_kplx);
    memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf, strlen(tmpBuf));
	tmpLen += strlen(tmpBuf);
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;

	//原发票代码
	DBG_PRINT(("pInvHead->m_yfpdm = %s", pInvHead->m_yfpdm.c_str()));
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_yfpdm.c_str(), pInvHead->m_yfpdm.length());
	tmpLen += pInvHead->m_yfpdm.length();
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//原发票号码
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
    sprintf(tmpBuf, "%u", pInvHead->m_yfphm);
    memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf, strlen(tmpBuf));
	tmpLen += strlen(tmpBuf);
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//防伪码
	DBG_PRINT(("pInvHead->m_fwm = %s", pInvHead->m_fwm.c_str()));
    memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_fwm.c_str(), pInvHead->m_fwm.length());
	tmpLen += pInvHead->m_fwm.length();
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;

	//签名
	//DBG_PRINT(("pInvHead->m_casign = %s", pInvHead->m_casign.c_str()));
    memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_casign.c_str(), pInvHead->m_casign.length());
	tmpLen += pInvHead->m_casign.length();
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;

	//作废日期
	DBG_PRINT(("pInvHead->m_zfsj= %s",pInvHead->m_zfsj.c_str()));
    memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_zfsj.c_str(), pInvHead->m_zfsj.length());
	tmpLen += pInvHead->m_zfsj.length();
	
	nDataLen = tmpLen;

	return;
}

void CJSKMakeInvoice::Str2InvHead(INT8 *pDataPtr,CDataInvHead *pInvHead)
{
	CJSKInfoFunc::MutexLock();
	CJSKInfoFunc::Data2InvDetail(pDataPtr, pInvHead, 1);
	CJSKInfoFunc::MutexUnlock();
	CJSKInvManageProc::fplx2fplxdm(pInvHead->m_fplb, pInvHead->m_fplxdm);
	pInvHead->m_xfmc = g_globalArgLib->m_corpInfo->m_Nsrmc;
	pInvHead->m_xfsh = g_globalArgLib->m_corpInfo->m_Nsrsbh;
	pInvHead->m_xfdzdh = g_globalArgLib->m_corpInfo->m_Djzcdz;
	pInvHead->m_xfyhzh = g_globalArgLib->m_corpInfo->m_Khzh;
}

INT32 CJSKMakeInvoice::ParseFpscjg(string scqrbw, string &mxjgmw, string &strErr)
{
	UINT8 upInfo[JSK_MAKE_INV_SIGN_LEN];
	
	memset(upInfo, 0, sizeof(upInfo));
	sprintf((INT8 *)upInfo, "%s", scqrbw.c_str());
	
	int nLen = scqrbw.length();
	DBG_PRINT(("nLen = %d", nLen));
	Base64_Decode_2((INT8 *)upInfo, &nLen);
	DBG_PRINT(("nLen = %d", nLen));
	DBG_PRINT(("upInfo = %s", upInfo));
	
	//接收数据写文件
	FILE *fp;	
	if( (fp = fopen(XML_FPSCJGHQ_FILE, "wb")) == NULL )
	{
		strErr = "解析发票上传结果错误!";
		return JSK_FAILURE;
	}
	fwrite( (void *)upInfo, nLen, 1, fp);
	fclose(fp);
	

	XMLParse xmlParse;
	int res = 0;
	string tmpCode("");
	string strFphm("");

	res = xmlParse.XMLParseBegin(XML_FPSCJGHQ_FILE);
	xmlParse.LocateNodeByName(xmlParse.m_RootElement, "OUTPUT");
	xmlParse.m_parentElement[1] = xmlParse.m_Child;

	xmlParse.LocateNodeByName(xmlParse.m_parentElement[1], "CODE");
	tmpCode = xmlParse.GetText();
	if(tmpCode != "0000")
	{
		xmlParse.LocateNodeByName(xmlParse.m_parentElement[1], "MESS");
		strErr = xmlParse.GetText();

		xmlParse.XMLParseEnd();
		return JSK_FAILURE;
	}
	
	xmlParse.LocateNodeByName(xmlParse.m_parentElement[1], "DATA");
	xmlParse.m_parentElement[2] = xmlParse.m_Child;
	
	res = xmlParse.LocateNodeByName(xmlParse.m_parentElement[2], "FP_SUCC");
	xmlParse.m_parentElement[3] = xmlParse.m_Child;
		
	string tempStr;
	xmlParse.LocateNodeByName(xmlParse.m_parentElement[3], "FPXX");
	tempStr = xmlParse.GetText();
	DBG_PRINT(("FPXX = %s", tempStr.c_str()));

	xmlParse.LocateNodeByName(xmlParse.m_parentElement[3], "FLAG");
	mxjgmw = xmlParse.GetText();
	DBG_PRINT(("mxjgmw = %s", mxjgmw.c_str()));
	if(mxjgmw != "")
	{
		return JSK_SUCCESS;
	}

	xmlParse.LocateNodeByName(xmlParse.m_parentElement[2], "FP_ERR");
	xmlParse.m_parentElement[3] = xmlParse.m_Child;
	
	xmlParse.LocateNodeByName(xmlParse.m_parentElement[3], "FP");
	xmlParse.m_parentElement[4] = xmlParse.m_Child;
	
	xmlParse.LocateNodeByName(xmlParse.m_parentElement[4], "FPDM");
	string tmpfpdm = xmlParse.GetText();
	DBG_PRINT(("tmpfpdm = %s", tmpfpdm.c_str()));

	xmlParse.LocateNodeByName(xmlParse.m_parentElement[4], "FPHM");
	strFphm = xmlParse.GetText();
	UINT32 tmpfphm = atoi(xmlParse.GetText().c_str());
	DBG_PRINT(("tmpfphm = %u", tmpfphm));

	xmlParse.LocateNodeByName(xmlParse.m_parentElement[4], "CODE");
	tmpCode = xmlParse.GetText();
	
	xmlParse.LocateNodeByName(xmlParse.m_parentElement[4], "MESS");
	strErr = xmlParse.GetText();
//	strErr = strFphm + ":" + strErr;
	DBG_PRINT(("strErr = %s", strErr.c_str()));

	xmlParse.XMLParseEnd();

	INT8 sqlbuf[128];
	memset(sqlbuf, 0, sizeof(sqlbuf));
	sprintf(sqlbuf, "where FPDM='%s' and FPHM=%u ", tmpfpdm.c_str(), tmpfphm);
	CInvServ invServ;
	invServ.m_upFlag = INV_UPLOAD_FLAG2;		//上传错误
	if(strErr.length() > MAX_ERR_MSG_LEN)
		strErr.erase(MAX_ERR_MSG_LEN, strErr.length()-MAX_ERR_MSG_LEN);
	invServ.m_errMsg = tmpCode + ":" + strErr;
	DBG_PRINT(("m_errMsg = %s", invServ.m_errMsg.c_str()));
	invServ.Update(sqlbuf, &invServ.m_upFlag, &invServ.m_errMsg, NULL);

	return JSK_FAILURE;
}

INT32 CJSKMakeInvoice::FPBL_Proc(string nsrsbh, string sksbbh, UINT32 SDate, UINT32 EDate, string &strErr)
{
	DBG_PRINT(("FPBL_Proc Begin()"));
	CInvHead invHead;
	INT8 sqlbuf[128];
	INT8 tmpBuf[128];
	INT32 errcode = 0;
	XMLConstruct pXmlBuild;
	UINT32 nCount = 1;
	string filename("");

	memset(tmpBuf, 0, sizeof(tmpBuf));
	UINT8 ret = UsbDiskMount(tmpBuf);
	if (SUCCESS != ret)
	{
		DBG_PRINT(("挂载U盘失败"));
		strErr = "挂载U盘失败";
		UsbDiskUnMount();
		return JSK_FAILURE;
	}

	UINT32 uDate = SDate/100;
	DBG_PRINT(("uDate= %u",uDate));
	sprintf(tmpBuf, "/mnt/%s%s%s_%s_%u_%s%s.DAT", XML_FILE_NAME_CGLPLBL,XML_FILE_NAME_KFSBM,nsrsbh.c_str(),sksbbh.c_str(),uDate,XML_FILE_NAME_ENCODE,"0001");
	filename = tmpBuf;
	DBG_PRINT(("filename = %s", filename.c_str()));

	memset(sqlbuf, 0, sizeof(sqlbuf));
	sprintf(sqlbuf, "where KPRQ>=%u and KPRQ<=%u", SDate, EDate);
	DBG_PRINT(("sqlbuf = %s", sqlbuf));
	invHead.m_filter.append(sqlbuf);
	INT32 m_InvNum = invHead.GetRecordNum();
	DBG_PRINT(("m_InvNum = %ld", m_InvNum));
	if(m_InvNum  > 0 )
	{
		pXmlBuild.XMLConstructBegin("1.0", "gbk", "business");
		pXmlBuild.m_RootElement->SetAttribute("id", "JSZZP");
		pXmlBuild.m_RootElement->SetAttribute("comment", "卷式增普票");
		pXmlBuild.m_RootElement->SetAttribute("version", "1.0");
	}
	else
	{
		strErr = "该时间段没有开票信息!";
		return JSK_FAILURE;
	}

	UINT32 date_StartNo = 0;	//当天的发票起始号码
	TDateTime tmpDateTime(SDate, 0);
	UINT32 TempDate = tmpDateTime.FormatInt(YYYYMMDD);	
	DBG_PRINT(("TempDate = %u", TempDate));
	while(TempDate <= EDate)
	{
		DBG_PRINT(("补录日期: %u", TempDate));
		date_StartNo = 0;

		memset(sqlbuf, 0, sizeof(sqlbuf));
		sprintf(sqlbuf, "WHERE KPRQ=%u order by NO limit 1", TempDate);
		DBG_PRINT(("sqlbuf = %s", sqlbuf));
		invHead.m_filter.append(sqlbuf);
		errcode = invHead.Load();
		DBG_PRINT(("errcode = %u", errcode));	

		while (errcode == SQLITE_OK)	//查到记录
		{
			DBG_PRINT(("查询invhead表有内容！"));
			pXmlBuild.AddNode(pXmlBuild.m_RootElement, "body");
			memset(tmpBuf, 0, sizeof(tmpBuf));
			sprintf(tmpBuf, "%u", nCount);
			pXmlBuild.AddAttr("no", tmpBuf);
			pXmlBuild.m_parentElement[1] = pXmlBuild.m_NewElement;
			
			pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "fpdm");
			pXmlBuild.AddText(invHead.m_fpdm);
			
			pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "fphm");
			memset(tmpBuf, 0, sizeof(tmpBuf));
			sprintf(tmpBuf, "%08u", invHead.m_fphm);
			pXmlBuild.AddText(tmpBuf);


			TDateTime tmpdate(invHead.m_kprq, invHead.m_kpsj);
			string tmpKprq = tmpdate.FormatString(YYYYMMDD);
			DBG_PRINT(("tmpKprq= %s",tmpKprq.c_str()));
			string tmpKpsj = tmpdate.FormatString(HHMMSS);
			DBG_PRINT(("tmpKpsj= %s",tmpKpsj.c_str()));

			pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "kprq");
			//memset(tmpBuf, 0, sizeof(tmpBuf));
			//sprintf(tmpBuf, "%08u", invHead.m_kprq);
			pXmlBuild.AddText(tmpKprq);			
			
			pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "kpsj");
// 			memset(tmpBuf, 0, sizeof(tmpBuf));
// 			sprintf(tmpBuf, "%u", invHead.m_kpsj);
			pXmlBuild.AddText(tmpKpsj);			

			pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "sbbh");
			pXmlBuild.AddText(sksbbh);

			if(invHead.m_kplx == JSK_RETURN_INV)
			{
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "hjje");
				memset(tmpBuf, 0, sizeof(tmpBuf));
				sprintf(tmpBuf, "-%.2lf", ((double)(invHead.m_kpje)*1.0)/SUM_EXTENSION);
				pXmlBuild.AddText(tmpBuf);
			
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "se");
				memset(tmpBuf, 0, sizeof(tmpBuf));
				if(invHead.m_kpse == 0)
				{
					sprintf(tmpBuf, "%.2lf", ((double)invHead.m_kpse *1.0)/SUM_EXTENSION);
				}
				else
				{
					sprintf(tmpBuf, "-%.2lf", ((double)invHead.m_kpse *1.0)/SUM_EXTENSION);
				}
				pXmlBuild.AddText(tmpBuf);

				pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "jshj");
				memset(tmpBuf, 0, sizeof(tmpBuf));
				invHead.m_kphjje = invHead.m_kpje + invHead.m_kpse;
				sprintf(tmpBuf, "-%.2lf", ((double)invHead.m_kphjje *1.0)/SUM_EXTENSION);
				pXmlBuild.AddText(tmpBuf);		
			}
			else
			{
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "hjje");
				memset(tmpBuf, 0, sizeof(tmpBuf));
				sprintf(tmpBuf, "%.2lf", ((double)(invHead.m_kpje)*1.0)/SUM_EXTENSION);
				pXmlBuild.AddText(tmpBuf);
				
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "se");
				memset(tmpBuf, 0, sizeof(tmpBuf));
				sprintf(tmpBuf, "%.2lf", ((double)invHead.m_kpse *1.0)/SUM_EXTENSION);
				pXmlBuild.AddText(tmpBuf);
				
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "jshj");
				memset(tmpBuf, 0, sizeof(tmpBuf));
				invHead.m_kphjje = invHead.m_kpje + invHead.m_kpse;
				sprintf(tmpBuf, "%.2lf", ((double)invHead.m_kphjje *1.0)/SUM_EXTENSION);
				pXmlBuild.AddText(tmpBuf);
			}
			
			pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "jym");
			pXmlBuild.AddText(invHead.m_fwm);
			
			pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "xfmc");
			pXmlBuild.AddText(g_globalArgLib->m_corpInfo->m_Nsrmc);
			
			pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "xfsh");
			pXmlBuild.AddText(nsrsbh);
			
			pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "gfmc");
			pXmlBuild.AddText(invHead.m_fkdw);
			
			pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "gfsh");
			pXmlBuild.AddText(invHead.m_payerCode);
			
				
			string fpztbz("");
			switch(invHead.m_kplx)
			{
			case JSK_NORMAL_INV:
					fpztbz = "0";	//正票
				break;
			case JSK_RETURN_INV:
					fpztbz = "1";	//退票
				break;
			case JSK_WASTE_INV:
					fpztbz = "2";	//空白废
				break;
			case JSK_WASTE_NOR:
					fpztbz = "3";	//正废
				break;
			case JSK_WASTE_RET:
					fpztbz = "4";	//负废
				break;
			}
			//发票状态标志（0 正常票1 退票2新发票的作废发票3正常发票的作废发票4已开退票的作废发票）
			pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "fpbz");
			pXmlBuild.AddText(fpztbz);

			pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "skr");
			pXmlBuild.AddText(invHead.m_sky);
			
			pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "bz");
			UINT8 baseBuf[256];
			memset(baseBuf, 0, sizeof(baseBuf));
			sprintf((INT8 *)baseBuf, "%s", invHead.m_backup1.c_str());
			Base64_Encode_2(baseBuf, invHead.m_backup1.length());
			string tmpStr = (INT8 *)baseBuf;
			pXmlBuild.AddText(tmpStr);
			
			if(invHead.m_kplx == JSK_RETURN_INV)
			{
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "yfpdm");
				pXmlBuild.AddText(invHead.m_yfpdm);
				
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "yfphm");
				memset(tmpBuf, 0, sizeof(tmpBuf));
				sprintf(tmpBuf, "%u",  invHead.m_yfphm);
				pXmlBuild.AddText(tmpBuf);
			}
			else
			{
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "yfpdm");
				pXmlBuild.AddText("");
				
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "yfphm");
				pXmlBuild.AddText("");
			}

			if( (invHead.m_kplx == JSK_WASTE_NOR) || (invHead.m_kplx == JSK_WASTE_RET) || (invHead.m_kplx == JSK_WASTE_INV) )
			{
				TDateTime zfDate(invHead.m_zfsj.c_str(), DATETIME_POS);
				string strZfrq =  zfDate.FormatString(YYYYMMDD);
				DBG_PRINT(("strZfrq= %s",strZfrq.c_str()));
				string strZfsj=zfDate.FormatString(HHMMSS);
				DBG_PRINT(("strZfsj= %s",strZfsj.c_str()));

				pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "zfrq");
				memset(tmpBuf, 0, sizeof(tmpBuf));
				//sprintf(tmpBuf, "%u", zfDate.FormatInt(YYYYMMDD));
				pXmlBuild.AddText(strZfrq);
				
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "zfsj");
				memset(tmpBuf, 0, sizeof(tmpBuf));
				//sprintf(tmpBuf, "%u", zfDate.FormatInt(HHMMSS));
				pXmlBuild.AddText(strZfsj);				
			}
			else
			{
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "zfrq");
				pXmlBuild.AddText("");
				
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "zfsj");
				pXmlBuild.AddText("");
			}

			pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "qmz");
			pXmlBuild.AddText(invHead.m_casign);


			CInvDet *pInvDet = invHead.pHead;
			
			for(int j=1; j<=invHead.m_sphsl; j++, pInvDet=pInvDet->pNext)
			{
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[1], "zb");
				pXmlBuild.m_parentElement[2] = pXmlBuild.m_NewElement;
				
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[2], "xh");
				memset(tmpBuf, 0, sizeof(tmpBuf));
				sprintf(tmpBuf, "%u", pInvDet->m_sphxh);
				pXmlBuild.AddText(tmpBuf);
				
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[2], "xm");
				pXmlBuild.AddText(pInvDet->m_spmc);
				
				if(invHead.m_kplx == JSK_RETURN_INV)
				{
					pXmlBuild.AddNode(pXmlBuild.m_parentElement[2], "sl");
					memset(tmpBuf, 0, sizeof(tmpBuf));
					if(pInvDet->m_spsl < 0.001)
					{
						sprintf(tmpBuf, "0.00000000");
					}
					else
					{
						sprintf(tmpBuf, "-%.3lf00000",  pInvDet->m_spsl);
					}
					pXmlBuild.AddText(tmpBuf);
				}
				else
				{
					pXmlBuild.AddNode(pXmlBuild.m_parentElement[2], "sl");
					memset(tmpBuf, 0, sizeof(tmpBuf));
					sprintf(tmpBuf, "%.3lf00000",  pInvDet->m_spsl);
					pXmlBuild.AddText(tmpBuf);
				}
				
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[2], "hsdj");
				memset(tmpBuf, 0, sizeof(tmpBuf));
				sprintf(tmpBuf, "%.3lf00000", pInvDet->m_spdj);
				pXmlBuild.AddText(tmpBuf);
				
				if(invHead.m_kplx == JSK_RETURN_INV)
				{
					pXmlBuild.AddNode(pXmlBuild.m_parentElement[2], "hsje");
					memset(tmpBuf, 0, sizeof(tmpBuf));
					sprintf(tmpBuf, "-%.2lf", ((double)pInvDet->m_spje*1.0)/SUM_EXTENSION);
					pXmlBuild.AddText(tmpBuf);
				}
				else
				{
					pXmlBuild.AddNode(pXmlBuild.m_parentElement[2], "hsje");
					memset(tmpBuf, 0, sizeof(tmpBuf));
					sprintf(tmpBuf, "%.2lf", ((double)pInvDet->m_spje*1.0)/SUM_EXTENSION);
					pXmlBuild.AddText(tmpBuf);
				}
				
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[2], "dj");
				memset(tmpBuf, 0, sizeof(tmpBuf));
				sprintf(tmpBuf, "%.3lf00000", pInvDet->m_dj);
				pXmlBuild.AddText(tmpBuf);
				
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[2], "je");
				memset(tmpBuf, 0, sizeof(tmpBuf));
				sprintf(tmpBuf, "%.2lf", ((double)pInvDet->m_je*1.0)/SUM_EXTENSION);
				pXmlBuild.AddText(tmpBuf);
				
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[2], "zsl");
				memset(tmpBuf, 0, sizeof(tmpBuf));
				sprintf(tmpBuf, "%.2lf", (double)pInvDet->m_sl);
				pXmlBuild.AddText(tmpBuf);
				
				pXmlBuild.AddNode(pXmlBuild.m_parentElement[2], "se");
				memset(tmpBuf, 0, sizeof(tmpBuf));
				sprintf(tmpBuf, "%.2lf", ((double)pInvDet->m_spse*1.0)/SUM_EXTENSION);
				pXmlBuild.AddText(tmpBuf);
			}

			nCount++;
			DBG_PRINT(("nCount = %u", nCount));
			date_StartNo = invHead.m_no;
			sprintf(sqlbuf, "WHERE KPRQ=%u and NO>%u limit 1", TempDate, date_StartNo);
			invHead.m_filter.append(sqlbuf);
			errcode = invHead.Load();			
		}

		//--------------------------------------------------
		//未找到票，查下一天
		//--------------------------------------------------
		if (errcode == SQLITE_DONE)
		{
			tmpDateTime ++;
			TempDate = tmpDateTime.FormatInt(YYYYMMDD);
			continue;
		}
		else
		{
			DBG_PRINT(("读数据库错误"));
			break;
		}
	}


	if( 1 != pXmlBuild.XMLConstructEnd(filename.c_str()) )
	{
		strErr = "报存XML文件错误!";
		return JSK_FAILURE;
	}

	UsbDiskUnMount();
	
	return JSK_SUCCESS;
}

void CJSKMakeInvoice::FilterSpace(string &str)
{
/*	INT8 tmpBuf[512];
	int nCount = 0;
	int nLen = str.length();
	
	memset(tmpBuf, 0, sizeof(tmpBuf));
	sprintf(tmpBuf, "%s", str.c_str());
	
	for(int i=nLen-1; i>=0; i--)
	{
		if(tmpBuf[i] == ' ')
		{
			nCount++;
			continue;
		}
		break;
	}
	if(nCount >= nLen)
	{
		str = "";
		return;
	}
	
	if(nCount > 0)
		str.erase(nLen-nCount, nCount);
	
	nCount = 0;
	for(int i=0; i<nLen; i++)
	{
		if(tmpBuf[i] == ' ')
		{
			nCount++;
			continue;
		}
		break;
	}
	if(nCount > 0)
		str.erase(0, nCount);
*/
	
	str.erase(str.find_last_not_of(" ") + 1);
	str.erase(0, str.find_first_not_of(" "));
	
	return;
}

INT32 CJSKMakeInvoice::GetErrUpInv(CDataInvServ *pDataInvServ, UINT32 &nCount, string &strErr)
{
	CInvServ invServ;
	INT8 sqlbuf[128];
	UINT32 i = 0;

	memset(sqlbuf, 0, sizeof(sqlbuf));
	sprintf(sqlbuf, "where UP_FLAG = %d", INV_UPLOAD_FLAG2);
	invServ.m_filter.append(sqlbuf);
	nCount = invServ.GetRecordNum();
	DBG_PRINT(("nCount = %u", nCount));

	if(nCount > MAX_ERR_INV_COUNT)
		nCount = MAX_ERR_INV_COUNT;

	invServ.m_filter.append(sqlbuf);
	invServ.Requery();
	UINT32 retCode = invServ.MoveFirst();
	while(retCode == SQLITE_ROW)
	{
		pDataInvServ[i].m_fpdm = invServ.m_code;
		pDataInvServ[i].m_fphm = invServ.m_InvNo;
		pDataInvServ[i].m_errMsg = invServ.m_errMsg;

		i++;
		if(i >= nCount)
			break;
		retCode = invServ.MoveNext();
	}
	invServ.MoveEnd();

	return JSK_SUCCESS;
}




