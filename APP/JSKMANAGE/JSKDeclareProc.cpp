/*! \file  JSKDeclareProc.h
\brief    awe4000r 数据抄报、监控回传
\author   zfj
\version  1.0
\date     2015-04-16
*/
#include <string.h>
#include "JSKDeclareProc.h"
#include "JSKInfoFunc.h"
#include "JSKInvManageProc.h"
#include "base64.h"
#include "CInvHead.h"
#include "CInvServ.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CJSKDeclareProc::CJSKDeclareProc()
{
}

CJSKDeclareProc::~CJSKDeclareProc()
{
}

// INT32 CJSKDeclareProc::SJCB_Proc(string fplxdm, UINT8 *sqBuff, UINT8 *fphzBuff, string &strErr)
// {
// 	INT32 retcode = 0;
// 	INT8 tmpbuf[64];
// 	UINT8 fplx;
// 	
// 	//发票类型代码转换为发票类型
// 	CJSKInvManageProc::fplxdm2fplx(fplxdm, fplx);
// 
// 	retcode = CJSKInfoFunc::NetCopyTax(fplx, sqBuff, sqBuff+MAX_DATETIME_LEN, fphzBuff, strErr);
// 	if(retcode != JSK_SUCCESS)
// 	{
// 		return retcode;
// 	}
// 
// 	return JSK_SUCCESS;
// }
INT32 CJSKDeclareProc::SJCB_Proc(string fplxdm, UINT8 jzlx, string &strSQ, string &strFphz, string &strErr)
{
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	UINT8 fplx;
	UINT8 sqBuff[MAX_DATETIME_LEN*2+1];		//属期
	UINT8 fphzBuff[JSK_SUM_INFO_LEN*2+1];		//发票汇总数据
	UINT32 nTaxLen = 0;
	
	//发票类型代码转换为发票类型
	CJSKInvManageProc::fplxdm2fplx(fplxdm, fplx);

	//1：网络（税控盘与金税盘）	2：税控设备（金税盘专用）
	if(jzlx == 1)
	{
		memset(sqBuff, 0, sizeof(sqBuff));
		memset(fphzBuff, 0, sizeof(fphzBuff));
		retcode = CJSKInfoFunc::NetCopyTax(fplx, sqBuff, sqBuff+MAX_DATETIME_LEN, fphzBuff,nTaxLen, strErr);
		if(retcode != JSK_SUCCESS)
		{
			return retcode;
		}
		DBG_PRINT(("nTaxLen = %u", nTaxLen));
		strSQ = (INT8 *)sqBuff;
		strFphz = (INT8 *)fphzBuff;
	}
	else if(jzlx == 2)
	{
		if(DeclareAuthority(strErr) != JSK_SUCCESS)
		{
			return JSK_COMMON_ERR_NO;
		}

		strSQ = "";
		strFphz = "";
		retcode = CJSKInfoFunc::JSPCopyTax(fplx, strErr);
		if(retcode != JSK_SUCCESS)
		{
			return retcode;
		}

		DelUploadInv();
	}
	else
	{
		strErr = "介质类型错误!";
		return JSK_COMMON_ERR_NO;
	}

	return JSK_SUCCESS;
}

INT32 CJSKDeclareProc::JKHC_Proc(string fplxdm, string strFpjkmw, string &strErr)
{
	INT32 retcode = 0;
	UINT8 CCardInfo[JSK_CLEAR_CARD_INFO_LEN*2];
	UINT8 fplx;

	//发票类型代码转换为发票类型
	CJSKInvManageProc::fplxdm2fplx(fplxdm, fplx);

	memset(CCardInfo, 0, sizeof(CCardInfo));
	sprintf((INT8 *)CCardInfo, "%s", strFpjkmw.c_str());

	int nLen = strFpjkmw.length();
	Base64_Decode_2((INT8 *)CCardInfo, &nLen);
	DBG_PRINT(("nLen = %d", nLen));

	retcode = CJSKInfoFunc::NetClearCard(fplx, CCardInfo, nLen, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	
	return JSK_SUCCESS;
}

INT32 CJSKDeclareProc::SKPBSP_Proc(string fplxdm, UINT8 czlx, string &strErr)
{
	INT32 retcode = 0;
	UINT8 fplx;

	CJSKInvManageProc::fplxdm2fplx(fplxdm, fplx);
	switch(czlx)
	{
	case SKPBSP_CZLX_SJCB:		//数据抄报
		{
			if(DeclareAuthority(strErr) != JSK_SUCCESS)
			{
				return JSK_COMMON_ERR_NO;
			}
			
			retcode = CJSKInfoFunc::BSPCopyTax(fplx, strErr);
		}
		break;
	case SKPBSP_CZLX_QLJS:		//清零解锁
		retcode = CJSKInfoFunc::BSPClearCard(fplx, strErr);
		break;
	case SKPBSP_CZLX_FXGPXX:	//反写购票信息
		break;
	case SKPBSP_CZLX_JZSZ:		//校准税控设备时钟
		break;
	default:
		break;
	}

	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}

	if( (czlx == SKPBSP_CZLX_SJCB) || (czlx == SKPBSP_CZLX_QLJS) )
	{
		DelUploadInv();
	}
	
	return JSK_SUCCESS;
}

INT32 CJSKDeclareProc::DeclareAuthority(string &strErr)
{
	INT32 retcode = 0;
	UINT8 timeBuf[MAX_DATETIME_LEN+1];

	//获取当期时钟YYYYMMDDHHMMSS
	memset(timeBuf, 0, sizeof(timeBuf));
	retcode = CJSKInfoFunc::GetJSPCurDate(timeBuf, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	DBG_PRINT(("timeBuf = %s", timeBuf));
	TDateTime CurDate((INT8 *)timeBuf, DATE_POS);

	//报送起始日期
	memset(timeBuf, 0, sizeof(timeBuf));
    retcode = CJSKInfoFunc::GetJSPSendTime(timeBuf, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	DBG_PRINT(("timeBuf = %s", timeBuf));
	TDateTime DecDate((INT8 *)timeBuf, DATE_POS);

	//检查当天是否有报税资料
	UINT8  uFlag=0; //0-无，1-有
	retcode = CJSKInfoFunc::GetJSPCopyFlag(uFlag, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}

	DBG_PRINT(("DecDate = %s", DecDate.FormatString(YYYYMMDD).c_str()));
    DBG_PRINT(("CurDate = %s", CurDate.FormatString(YYYYMMDD).c_str()));
    DBG_PRINT(("uFlag= %u",uFlag));

	if((DecDate >= CurDate)&&(uFlag ==0))
	{
		strErr = "当天不能再次抄报!";
		return JSK_FAILURE;
	}

	return JSK_SUCCESS;
}

INT32 CJSKDeclareProc::DelUploadInv()
{
	CDataInvHead dataInvHead;
	CInvServ invServ;
	INT8 sqlbuf[128];
	string strErr("");
	INT32 retcode = 0;
	
	retcode = CJSKInfoFunc::GetFirstOffInvInfo(&dataInvHead, strErr);
	if(retcode == JSK_SUCCESS)
	{
		if(dataInvHead.m_fphm != 0)
		{
			memset(sqlbuf, 0, sizeof(sqlbuf));
			sprintf(sqlbuf, "where FPDM='%s' and FPHM=%u ", dataInvHead.m_fpdm.c_str(), dataInvHead.m_fphm);
			DBG_PRINT(("sqlbuf = %s", sqlbuf));
			invServ.m_filter.append(sqlbuf);
			invServ.Requery();
			if(invServ.LoadOneRecord() == SQLITE_OK)
			{
				memset(sqlbuf, 0, sizeof(sqlbuf));
				sprintf(sqlbuf, "where NO < %u ", invServ.m_no);
				DBG_PRINT(("sqlbuf = %s", sqlbuf));
				invServ.m_filter.append(sqlbuf);
				invServ.Delete();
			}
		}
		else
		{
			invServ.Delete();
		}
	}
	
	return JSK_SUCCESS;
}

