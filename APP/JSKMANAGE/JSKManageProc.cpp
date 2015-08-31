/*! \file  JSKManageProc.h
\brief    awe4000r 税控设备信息查询管理流程   2.1 ~ 2.5
\author   zfj
\version  1.0
\date     2015-04-16
*/

#include "JSKManageProc.h"
#include "JSKInvManageProc.h"
#include "JSKInfoFunc.h"
#include "CGlobalArgLib.h"
#include "base64.h"
#include "SysArgMac.h"
#include "CSysArg.h"
#include "CInvServ.h"
#include "GlobalNetArg.h"
#include "DataTransformFunc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CJSKManageProc::CJSKManageProc()
{
}

CJSKManageProc::~CJSKManageProc()
{
}

void CJSKManageProc::set_JSKPara(string jqbh, string sksbkl, string bspkl)
{
	if(jqbh.length() > JSK_MAX_JQBH_LEN)
	{
		UINT8 tmpLen = jqbh.length() - JSK_MAX_JQBH_LEN;
		DBG_PRINT(("tmpLen = %u", tmpLen));
		jqbh.erase(0, tmpLen);
		DBG_PRINT(("jqbh = %s", jqbh.c_str()));
	}

	CJSKInfoFunc::set_Para(jqbh, sksbkl, bspkl);
}

INT32 CJSKManageProc::SKSBBH_Proc(string &sksbbh, string &strErr)
{
	DBG_PRINT(("===== SKSBBH_Proc Begin() ======"));
	UINT8 sksbbhBuf[MAX_SKSBBH_LEN+1];
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	string tmpMsg;

	//获取税控设备编号
	memset(sksbbhBuf, 0, sizeof(sksbbhBuf));
	retcode = CJSKInfoFunc::GetJSPNo(sksbbhBuf, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}

	sksbbh = (INT8 *)sksbbhBuf;
	DBG_PRINT(("sksbbh = %s", sksbbh.c_str()));

	g_globalArgLib->m_corpInfo->m_Jspsbh = sksbbh;
	
	DBG_PRINT(("===== SKSBBH_Proc End() ======"));
	return JSK_SUCCESS;
}

INT32 CJSKManageProc::BSPBH_Proc(string &bspbh, string &strErr)
{
	DBG_PRINT(("===== BSPBH_Proc Begin() ======"));
	UINT8 bspbhBuf[MAX_SKSBBH_LEN+1];
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	string tmpMsg;
	
	//获取报税盘编号
	memset(bspbhBuf, 0, sizeof(bspbhBuf));
	CJSKInfoFunc::GetBSPNo(bspbhBuf, tmpMsg);	//报税盘获取不返回错误
	retcode = CJSKInfoFunc::GetBSPNo(bspbhBuf, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	
	bspbh = (INT8 *)bspbhBuf;
	DBG_PRINT(("bspbh = %s", bspbh.c_str()));
	
	g_globalArgLib->m_corpInfo->m_bspbh = bspbh;
	
	DBG_PRINT(("===== BSPBH_Proc End() ======"));
	return JSK_SUCCESS;
}

INT32 CJSKManageProc::SKPXXCX_Proc(CDataUserInfo *pUserInfo, string &strCurTime, string &strErr)
{
	DBG_PRINT(("===== SKPXXCX_Proc Begin() ======"));
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	TDateTime curDate;
	CDataTax dataTax[MAX_TAX_NUM];
	UINT8 verBuf[MAX_VER_LEN+1];
	UINT8 timeBuf[MAX_DATETIME_LEN+1];
	UINT8 sksbbhBuf[MAX_SKSBBH_LEN+1];

	//Case 0x01：获取纳税户信息
	retcode = CJSKInfoFunc::GetCorpInfo(pUserInfo, dataTax, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	memset(tmpbuf, 0, sizeof(tmpbuf));
	sprintf(tmpbuf, "0000%02u", pUserInfo->m_Nsrxz);
	pUserInfo->m_blxx = tmpbuf;

	Transformfplx(pUserInfo->m_Fplxgs, pUserInfo->m_Fplxsz);
	pUserInfo->m_fplxdm = pUserInfo->m_Fplxsz;

	memset(tmpbuf, 0, sizeof(tmpbuf));
	sprintf(tmpbuf, "%u", g_globalArgLib->m_corpInfo->m_Kpjhm);
	g_gNetArg->SetBaseInfo(g_globalArgLib->m_corpInfo->m_Nsrsbh, tmpbuf, g_globalArgLib->m_corpInfo->m_Jspsbh);
	
	//获取税控设备编号
	memset(sksbbhBuf, 0, sizeof(sksbbhBuf));
	retcode = CJSKInfoFunc::GetJSPNo(sksbbhBuf, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	pUserInfo->m_Jspsbh = (INT8 *)sksbbhBuf;

	//获取金税盘版本号
	memset(verBuf, 0, sizeof(verBuf));
	retcode = CJSKInfoFunc::GetJSPVer(verBuf, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	pUserInfo->m_bbh = (INT8 *)verBuf;
	
	//获取金税盘启用时间
	memset(timeBuf, 0, sizeof(timeBuf));
    retcode = CJSKInfoFunc::GetJSPOpenTime(timeBuf, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	pUserInfo->m_qysj = (INT8 *)timeBuf;

#if MIDDLEWARE_SAVE_DB == 1
	CUserInfo userInfo;
	CDataTransformFunc::Data2UserInfo(pUserInfo, &userInfo);
	userInfo.Delete();
	userInfo.AddNew();
	g_globalArgLib->m_corpInfo->Requery();
	g_globalArgLib->m_corpInfo->LoadOneRecord();
#endif
	
	//获取当期时钟YYYYMMDDHHMMSS
	memset(timeBuf, 0, sizeof(timeBuf));
	retcode = CJSKInfoFunc::GetJSPCurDate(timeBuf, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	strCurTime = (INT8 *)timeBuf;
	DBG_PRINT(("strCurTime = %s", strCurTime.c_str()));

	DBG_PRINT(("===== SKPXXCX_Proc End() ======"));
	return JSK_SUCCESS;
}

void CJSKManageProc::Transformfplx(UINT32 nCount, string &strMsg)
{
	UINT8 tmpInt = 0;
	INT8 tmpbuf[8];
	int j = 0;
	UINT32 num = 0;
	string tmpStr("");
	INT8 buff[MAX_FPLXDM_LEN*INVKIND_MAX_NUM+1];

	DBG_PRINT(("strMsg = %s", strMsg.c_str()));
	memset(buff, 0, sizeof(buff));
	sprintf(buff, "%s", strMsg.c_str());
	strMsg = "";

	for(int i=0; i<strlen(buff); i++)
	{
		if(buff[i] == ' ')
		{
			tmpInt = atoi(tmpbuf);
			CJSKInvManageProc::fplx2fplxdm(tmpInt, tmpStr);
			strMsg.append(tmpStr);
			num++;
			if(num >= nCount)
				break;
			j = 0;
			memset(tmpbuf, 0, sizeof(tmpbuf));
		}
		else
		{
			tmpbuf[j++] = buff[i];
		}
	}
	DBG_PRINT(("strMsg = %s", strMsg.c_str()));
}

INT32 CJSKManageProc::BSPXXCX_Proc(CDataUserInfo *pUserInfo, string &strErr)
{
	INT32 retcode = 0;
	UINT8 bspNo[MAX_SKSBBH_LEN+1];
	UINT8 nsrsbh[MAX_NSRSBH_LEN+1];
	UINT8 bspVer[MAX_VER_LEN+1];
	UINT8 bspKpjh[MAX_KPJH_LEN+1];

	//报税盘编号
	retcode = CJSKInfoFunc::GetBSPNo(bspNo, strErr);
	DBG_PRINT(("retcode = %d", retcode));
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	pUserInfo->m_bspbh = (INT8 *)bspNo;

	//纳税人识别号
	retcode = CJSKInfoFunc::GetBSPNsrsbh(nsrsbh, strErr);
	DBG_PRINT(("retcode = %d", retcode));
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	pUserInfo->m_Nsrsbh = (INT8 *)nsrsbh;

	//报税盘版本号
	retcode = CJSKInfoFunc::GetBSPVer(bspVer, strErr);
	DBG_PRINT(("retcode = %d", retcode));
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	pUserInfo->m_bbh = (INT8 *)bspVer;

	//报税盘开票机号
	retcode = CJSKInfoFunc::GetBSPKpjh(bspKpjh, strErr);
	DBG_PRINT(("retcode = %d", retcode));
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
 	}
	pUserInfo->m_Kpjhm = atoi((INT8 *)bspKpjh);

	strErr = "其他信息报税盘不支持";
	return JSK_SUCCESS;
}

INT32 CJSKManageProc::JKSJCX_Proc(CDataInvKind *pInvKind, string &strErr)
{
	DBG_PRINT(("===== JKSJCX_Proc Begin() ======"));
	INT32 retcode = 0;
	UINT8 timeBuf[MAX_DATETIME_LEN+1];
	UINT8 fplx;
	int i=0;
	
	CJSKInvManageProc::fplxdm2fplx(pInvKind->m_fplxdm, fplx);
	retcode = CJSKInfoFunc::GetOffLimitInfo(fplx, pInvKind, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	CJSKInvManageProc::fplx2fplxdm(pInvKind->m_fplx, pInvKind->m_fplxdm);
	
#if MIDDLEWARE_SAVE_DB == 1
	CInvKind invKind;
	CDataTransformFunc::Data2InvKind(pInvKind, &invKind);
	invKind.Delete();
	invKind.AddNew();
	g_globalArgLib->m_invKind->Requery();
	g_globalArgLib->m_invKind->LoadOneRecord();
#endif
	

	//报送起始日期
	memset(timeBuf, 0, sizeof(timeBuf));
    retcode = CJSKInfoFunc::GetJSPSendTime(timeBuf, strErr);
	pInvKind->m_bsqsrq = (INT8 *)timeBuf;
	TDateTime decDate((INT8 *)timeBuf, DATE_POS);
	//金税盘当前日期
	memset(timeBuf, 0, sizeof(timeBuf));
    retcode = CJSKInfoFunc::GetJSPCurDate(timeBuf, strErr);
	TDateTime curDate((INT8 *)timeBuf, DATE_POS);
	
	TDateTime dateEnd = decDate.MonthEnd(decDate);			//抄报起始月底
	TDateTime dateBegin = curDate.MonthBegin(curDate);		//当前月初
	if( dateEnd < dateBegin)	//跨月
	{
		dateEnd = dateEnd + 1;
		pInvKind->m_bszzrq = dateEnd.FormatString(YYYYMMDD, "%u%02u%02u") + "000000";
		pInvKind->m_kpjzrq = pInvKind->m_bszzrq;
	}
	else
	{
		pInvKind->m_bszzrq = (INT8 *)timeBuf;
		dateEnd = dateEnd + 1;
		pInvKind->m_kpjzrq = dateEnd.FormatString(YYYYMMDD, "%u%02u%02u") + "000000";
	}
	
	DBG_PRINT(("m_fplx = %u", pInvKind->m_fplx));
	DBG_PRINT(("m_fplxdm = %s", pInvKind->m_fplxdm.c_str()));
	DBG_PRINT(("m_Lxkjsj = %u", pInvKind->m_Lxkjsj));
	DBG_PRINT(("m_Lxssr = %u", pInvKind->m_Lxssr));
	DBG_PRINT(("m_maxSign = %lld", pInvKind->m_maxSign));
	DBG_PRINT(("m_maxSum = %lld", pInvKind->m_maxSum));
	DBG_PRINT(("m_bsqsrq = %s", pInvKind->m_bsqsrq.c_str()));
	DBG_PRINT(("m_bszzrq = %s", pInvKind->m_bszzrq.c_str()));
	DBG_PRINT(("m_kpjzrq = %s", pInvKind->m_kpjzrq.c_str()));
	
	DBG_PRINT(("===== JKSJCX_Proc End() ======"));
	return JSK_SUCCESS;
}

INT32 CJSKManageProc::SQSLCX_Proc(CDataTax *pTax, UINT8 &taxNum, string &strErr)
{
	DBG_PRINT(("===== SQSLCX_Proc Begin() ======"));
	INT32 retcode = 0;
	CDataUserInfo dataUserInfo;

	//Case 0x01：获取纳税户信息
	retcode = CJSKInfoFunc::GetCorpInfo(&dataUserInfo, pTax, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}

	taxNum = dataUserInfo.m_Slgs;
	DBG_PRINT(("taxNum = %u", taxNum));

#if MIDDLEWARE_SAVE_DB == 1
	CTax tax;
	tax.Delete();
	for(int i=0; i<taxNum; i++)
	{
		CDataTransformFunc::Data2Tax(&pTax[i], &tax);
		tax.AddNew();
	}
#endif

	DBG_PRINT(("===== SQSLCX_Proc End() ======"));
	return JSK_SUCCESS;
}

INT32 CJSKManageProc::KLBG_Proc(string oldPwd, string newPwd, string &strErr)
{
	DBG_PRINT(("===== KLBG_Proc Begin() ======"));
	INT32 retcode = 0;
	UINT8 pwdBuf[MAX_PWD_LEN+1];

	memset(pwdBuf, 0x00, sizeof(pwdBuf));
	//sprintf((INT8 *)pwdBuf, "%-09s%-09s", oldPwd.c_str(), newPwd.c_str());
	sprintf((INT8 *)pwdBuf, "%s", oldPwd.c_str());
	sprintf((INT8 *)pwdBuf+9, "%s", newPwd.c_str());

	retcode = CJSKInfoFunc::JSPModPassW(pwdBuf, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}

	CSysArg sysArg;
	INT8 sqlbuf[128];
	memset(sqlbuf, 0, sizeof(sqlbuf));
	sprintf(sqlbuf, "where SA_ID=%d", SYS_SKSB_PWD);
	sysArg.m_vText = newPwd;
	if( sysArg.Update(sqlbuf, &sysArg.m_vText, NULL) != SQLITE_OK )
	{
		DBG_PRINT(("Update SYS_SKSB_PWD Error!"));
	}

	DBG_PRINT(("===== KLBG_Proc End() ======"));
	return JSK_SUCCESS;
}

INT32 CJSKManageProc::BGZSKL_Proc(string oldPwd, string newPwd, string &strErr)
{
	INT32 retcode = 0;
	UINT8 pwdBuf[MAX_PWD_LEN+1];
	
	memset(pwdBuf, 0x00, sizeof(pwdBuf));
	sprintf((INT8 *)pwdBuf, "%s", oldPwd.c_str());
	sprintf((INT8 *)pwdBuf+9, "%s", newPwd.c_str());
	
	retcode = CJSKInfoFunc::ZSPassW(pwdBuf, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	
	CSysArg sysArg;
	INT8 sqlbuf[128];
	memset(sqlbuf, 0, sizeof(sqlbuf));
	sprintf(sqlbuf, "where SA_ID=%d", SYS_ZS_PWD);
	sysArg.m_vText = newPwd;
	if( sysArg.Update(sqlbuf, &sysArg.m_vText, NULL) != SQLITE_OK )
	{
		DBG_PRINT(("Update SYS_ZS_PWD Error!"));
	}
	
	g_globalArgLib->m_strZskl = newPwd;
	g_gNetArg->SetZskl(g_globalArgLib->m_strZskl);

	return JSK_SUCCESS;
}

INT32 CJSKManageProc::LXXXXP_Proc(string lxxxmw, string &strErr)
{
	INT32 retcode = 0;
	UINT8 uCorpInfo[JSK_LXXXMW_LEN+1];

	memset(uCorpInfo, 0, sizeof(uCorpInfo));
	sprintf((INT8 *)uCorpInfo, "%s", lxxxmw.c_str());

	int nLen = lxxxmw.length();
	Base64_Decode_2((INT8 *)uCorpInfo, &nLen);
	DBG_PRINT(("nLen = %d", nLen));
	retcode = CJSKInfoFunc::UpdateCorpInfo(uCorpInfo, nLen, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	
	return JSK_SUCCESS;
}

INT32 CJSKManageProc::SKSBQTYXXCX_Proc(string fplxdm, UINT8 xxlx, string &sksbxx, string &strErr)
{
	INT32 retcode = JSK_SUCCESS;
	UINT8 uSksbxx[JSK_LXXXMW_LEN+1];
	UINT8 uAddrNo[JSK_ADDR_NO_LEN+1];
	UINT8 verBuf[MAX_VER_LEN+1];		//底层版本
	UINT8 fplx;
	UINT16 outLen = 0;
	UINT8 hashFlag = HASH_NO_FLAG_16;
	UINT32 nTaxLen = 0;
	CDataInvVol dataInvVol;

	memset(uSksbxx, 0, sizeof(uSksbxx));
	memset(uAddrNo, 0, sizeof(uAddrNo));
	memset(verBuf, 0, sizeof(verBuf));

	CJSKInvManageProc::fplxdm2fplx(fplxdm, fplx);
	if(fplx == 0)
	{
		fplx = DEFAULT_FPLB_NO;
	}
	DBG_PRINT(("fplx = %u", fplx));
	
	DBG_PRINT(("xxlx = %u", xxlx));
	switch(xxlx)
	{
	case SKSBQTYXXCX_XXLX_WLCB:		//网络抄报：锁死期
// 		retcode = CJSKInfoFunc::GetHashNo(uSksbxx, uAddrNo, strErr);
// 		g_gNetArg->SetHashNo((INT8 *)uSksbxx, (INT8 *)uAddrNo);
		GetHashTaxNo(hashFlag, strErr);
		retcode = CJSKInfoFunc::GetLockDate(fplx, uSksbxx, strErr);
		break;
	case SKSBQTYXXCX_XXLX_QLJS:		//清卡：抄税时间
		{
			UINT8 sqBuff[MAX_DATETIME_LEN*2+1];		//属期
			memset(sqBuff, 0, sizeof(sqBuff));
			retcode = CJSKInfoFunc::NetCopyTaxDate(fplx, sqBuff, uSksbxx,strErr);
		}
		break;
	case SKSBQTYXXCX_XXLX_LXXXSC:
		retcode = CJSKInfoFunc::ReadCorpInfo(outLen, uSksbxx, strErr);
		break;
	case SKSBQTYXXCX_XXLX_WLLQFP:
		hashFlag = HASH_NO_FLAG_24;
		retcode = CJSKInfoFunc::AppNetInvVol(fplx, outLen, uSksbxx, strErr);
		break;
	case SKSBQTYXXCX_XXLX_WLLQFPJGQR:
		hashFlag = HASH_NO_FLAG_24;
		retcode = CJSKInfoFunc::App2NetInvVol(fplx, outLen, uSksbxx,&dataInvVol, strErr);
		break;
	case SKSBQTYXXCX_XXLX_FPSCJGHQ:
		retcode = CJSKInfoFunc::GetIssueNo(uSksbxx, strErr);
		g_gNetArg->SetIssueNo((INT8 *)uSksbxx);
	default:
		sksbxx = "";
		break;
	}

	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}

	DBG_PRINT(("outLen = %u", outLen));
	if(outLen > 0)
	{
		if( (xxlx==SKSBQTYXXCX_XXLX_LXXXSC) || (xxlx==SKSBQTYXXCX_XXLX_WLLQFP) || (xxlx==SKSBQTYXXCX_XXLX_WLLQFPJGQR) )
		{
			DBG_PRINT(("here Base64_Encode_2"));
			GetHashTaxNo(hashFlag, strErr);
			GetIssueTaxNo(strErr);
			if( (xxlx==SKSBQTYXXCX_XXLX_WLLQFP) || (xxlx==SKSBQTYXXCX_XXLX_WLLQFPJGQR) )
			{
				CJSKInfoFunc::GetJSPVer(verBuf, strErr);
				g_gNetArg->SetDcbb((INT8 *)verBuf);
			}
			
			Base64_Encode_2((UINT8 *)uSksbxx, outLen);
		}
	}

	if(xxlx == SKSBQTYXXCX_XXLX_QLJS)
	{
		TDateTime tmpCssj((INT8 *)uSksbxx, DATETIME_POS);
		sksbxx = tmpCssj.FormatString(YYYYMMDDHHMM);
	}
	else
	{
		sksbxx = (INT8 *)uSksbxx;
	}

	DBG_PRINT(("sksbxx = %s", sksbxx.c_str()));

	return JSK_SUCCESS;
}

INT32 CJSKManageProc::GetHashTaxNo(UINT8 HashFlag, string &strErr)
{
	INT32 retcode = 0;
	UINT8 uHashNo[JSK_HASH_NO_LEN+1];
	UINT8 uAddrNo[JSK_ADDR_NO_LEN+1];

	memset(uHashNo, 0, sizeof(uHashNo));
	memset(uAddrNo, 0, sizeof(uAddrNo));
	
	retcode = CJSKInfoFunc::GetHashNo(uHashNo, uAddrNo, strErr, HashFlag);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	g_gNetArg->SetHashNo((INT8 *)uHashNo, (INT8 *)uAddrNo);

	return JSK_SUCCESS;
}

INT32 CJSKManageProc::GetIssueTaxNo(string &strErr)
{
	INT32 retcode = 0;
	UINT8 uIssueNo[JSK_ISSUE_NO_LEN+1];
	
	memset(uIssueNo, 0, sizeof(uIssueNo));
	retcode = CJSKInfoFunc::GetIssueNo(uIssueNo, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	g_gNetArg->SetIssueNo((INT8 *)uIssueNo);
	
	return JSK_SUCCESS;
}

INT32 CJSKManageProc::NetPara_Proc(CDataNetPara *pNetPara, string &strErr)
{
	INT32 retcode = 0;

	CNetPara netPara;
	CDataTransformFunc::Data2NetPara(pNetPara, &netPara);
	netPara.Delete();
	if(netPara.AddNew() != SQLITE_OK)
	{
		retcode = JSK_COMMON_ERR_NO;
		strErr = "保存网络参数错误!";
		return retcode;
	}

	return JSK_SUCCESS;
}

INT32 CJSKManageProc::OffInvInfo_Proc(UINT32 &wscfpzs, string &wscfpsj, INT64 &wscfpljje, string &strErr)
{
	CInvServ invServ;
	INT8 sqlbuf[128];
	INT8 tmpbuf[32];
	string strTmp("");

	invServ.Requery();
	if(invServ.LoadOneRecord() != SQLITE_OK)
	{
		wscfpzs = 0;
		wscfpsj = "";
		wscfpljje = 0;
	}
	else
	{
		wscfpzs = invServ.GetRecordNum();
		DBG_PRINT(("缓存张数 wscfpzs= %u", wscfpzs));

		memset((void*)sqlbuf, 0, sizeof(sqlbuf));
		sprintf(sqlbuf, "where I_TYPE = %u", JSK_NORMAL_INV);
		strTmp = "select sum(M_SUM) from INV_SERV ";
		strTmp.append(sqlbuf);
		invServ.SetSQL(strTmp);
		invServ.GetOneResult(DB_INT64, (void*)&wscfpljje); 
		DBG_PRINT(("缓存金额 wscfpljje= %lld",  wscfpljje));
		
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%u%06u", invServ.m_issueDate, invServ.m_issueTime);
		wscfpsj = tmpbuf;
		DBG_PRINT(("缓存时间 wscfpsj= %s",  wscfpsj.c_str()));
	}

	return JSK_SUCCESS;
}


