/*! \file  JSKManageProc.h
\brief    awe4000r 发票管理流程
\author   zfj
\version  1.0
\date     2015-04-16
*/

#include "JSKInvManageProc.h"
#include "JSKInfoFunc.h"
#include "base64.h"
#include "CInvHead.h"
#include "DataTransformFunc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CJSKInvManageProc::CJSKInvManageProc()
{
}

CJSKInvManageProc::~CJSKInvManageProc()
{
}

INT32 CJSKInvManageProc::GPXXXP_Proc(string fplxdm, string gpxxmw, string &strErr)
{
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	UINT8 NetCrypData[JSK_GPXXMW_LEN+1];
	UINT8 fplx;

	fplxdm2fplx(fplxdm, fplx);
	memset(NetCrypData, 0, sizeof(NetCrypData));
	sprintf((INT8 *)NetCrypData, "%s", gpxxmw.c_str());

	DBG_PRINT(("gpxxmw = %s", NetCrypData));
	int nLen = gpxxmw.length();
	Base64_Decode_2((INT8 *)NetCrypData, &nLen);
	DBG_PRINT(("nLen = %d", nLen));

	retcode = CJSKInfoFunc::ReadNetInvVol(fplx, NetCrypData, strErr);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		return retcode;
	}
	
	return JSK_SUCCESS;
}
	
INT32 CJSKInvManageProc::GPXXXPJS_Proc(string fplxdm, string wslpjsxx, string &strErr)
{
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	UINT8 NetCrypData[JSK_NET_INV_CON_LEN+1];
	UINT8 fplx;

	fplxdm2fplx(fplxdm, fplx);
	memset(NetCrypData, 0, sizeof(NetCrypData));
	sprintf((INT8 *)NetCrypData, "%s", wslpjsxx.c_str());

	int nLen = wslpjsxx.length();
	Base64_Decode_2((INT8 *)NetCrypData, &nLen);
	DBG_PRINT(("nLen = %d", nLen));

	retcode = CJSKInfoFunc::ConNetInvVol(fplx, NetCrypData, strErr);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		return retcode;
	}
	
	return JSK_SUCCESS;
}

INT32 CJSKInvManageProc::BSPFPCX_Proc(string fplxdm, UINT32 &invNum, CDataInvVol *pInvVol, string &strErr)
{
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	UINT8 fplx;
	
	retcode = CJSKInfoFunc::GetJSKInvVolInfo(pInvVol, invNum, strErr);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		return retcode;
	}
	
	return JSK_SUCCESS;
}

INT32 CJSKInvManageProc::BSPFPFF_Proc(UINT8 jzlx, CDataInvVol *pInvVol, string &strErr)
{
	INT32 retcode = 0;
	INT8 tmpbuf[64];

	CJSKInvManageProc::fplxdm2fplx(pInvVol->m_fplxdm, pInvVol->m_invtype);
	if(jzlx == JSK_FP_JZLX_BSP)
	{
		retcode = CJSKInfoFunc::HostToInvBSP(pInvVol, strErr);
	}
	else
	{
		retcode = CJSKInfoFunc::HostToInvJSP(pInvVol, strErr);
	}
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		return retcode;
	}
	
	return JSK_SUCCESS;
}

INT32 CJSKInvManageProc::BSPFPSH_Proc(UINT8 jzlx, CDataInvVol *pInvVol, string &strErr)
{
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	
	CJSKInvManageProc::fplxdm2fplx(pInvVol->m_fplxdm, pInvVol->m_invtype);
	if(jzlx == JSK_FP_JZLX_BSP)
	{
		retcode = CJSKInfoFunc::InvVolRetBSP(pInvVol, strErr);
	}
	else
	{
		retcode = CJSKInfoFunc::InvVolRetJSP(pInvVol, strErr);
	}
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		return retcode;
	}
	
	return JSK_SUCCESS;
}

INT32 CJSKInvManageProc::FPDR_Proc(UINT8 jzlx, string fplxdm, string &strErr)
{
	DBG_PRINT(("===== FPDR_Proc Begin() ======"));
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	UINT8 fplx= 0;
	
	fplxdm2fplx(fplxdm, fplx);
	if(jzlx == JSK_FP_JZLX_BSP)
	{
			retcode = CJSKInfoFunc::BSPGetInvVolInfo(fplx, strErr);
	}
	else
	{
		retcode = CJSKInfoFunc::JSPGetInvVolInfo(fplx, strErr);
	}
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		return retcode;
	}
	
	DBG_PRINT(("===== FPDR_Proc End() ======"));
	return JSK_SUCCESS;
}

INT32 CJSKInvManageProc::FJTH_Proc(UINT8 jzlx, string fplxdm, string &strErr)
{
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	UINT8 fplx = 0;
	
	fplxdm2fplx(fplxdm, fplx);
	if(jzlx == JSK_FP_JZLX_BSP)
	{
		retcode = CJSKInfoFunc::HostGetInvBSP(fplx, strErr);
	}
	else
	{
		retcode = CJSKInfoFunc::HostGetInvJSP(fplx, strErr);
	}
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		return retcode;
	}
	
	return JSK_SUCCESS;
}

INT32 CJSKInvManageProc::TJXXCX_Proc(string strFplxdm, INT32 &MonthCount, CDataTjxxhz *pTjxxhz, string &strErr)
{
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	UINT8 fplx = 0;

	//将发票类型代码转换为发票类型
	fplxdm2fplx(strFplxdm, fplx);

	TDateTime sDateTime(pTjxxhz[0].m_Qsrq,DATE_POS);//必须是8位,如20150615
	TDateTime eDateTime(pTjxxhz[0].m_Jzrq,DATE_POS);	
	eDateTime = eDateTime.MonthEnd(eDateTime);//计算截止日期的月末

	UINT32 nDate = 0;
	UINT32 sDate = 0;
	INT32 itemp = 0;
	INT64 nZpHjje=0;
	INT64 nFpHjje=0;
	TDateTime tempeDateTime;
	UINT32 tempedate = 0;
	string strTmp("");
	char chValue[256], chTmpValue[64];
	CInvHead *pInvHead, invHead;
	pInvHead = &invHead;
	//UINT32 nCurDate = TDateTime::CurrentDateTime().FormatInt(YYYYMMDD);

	//获取当期时钟YYYYMMDDHHMMSS
	memset(chValue, 0, sizeof(chValue));
	retcode = CJSKInfoFunc::GetJSPCurDate((UINT8 *)chValue, strErr);
	if(retcode != JSK_SUCCESS)
	{
		return retcode;
	}
	DBG_PRINT(("chValue = %s", chValue));
	TDateTime CurDate(chValue, DATE_POS);

	UINT32 nCurDate =CurDate.FormatInt(YYYYMMDD);
     DBG_PRINT(("nCurDate= %u",nCurDate));

	DBG_PRINT(("MonthCount= %d",MonthCount));
	while((sDateTime <= eDateTime)&&(itemp<MonthCount))
	{
		sDate= sDateTime.FormatInt(YYYYMMDD);
		nDate =sDate/100;
		DBG_PRINT(("nDate= %u",nDate));
		//查询月统计数据，输入nDdate；

		retcode = CJSKInfoFunc::GetMonthCountDate(nDate, fplx, &pTjxxhz[itemp], strErr);
		DBG_PRINT(("retcode:%u ",retcode));
	
		if(retcode != JSK_SUCCESS)
		{
			memset(tmpbuf, 0, sizeof(tmpbuf));
			sprintf(tmpbuf, "%d", retcode);
			return retcode;
		}
		if (itemp == 0)
		{		
			pTjxxhz[itemp].m_Qsrq = sDate;
		}
		else
		{
			pTjxxhz[itemp].m_Qsrq = nDate*100+1;
		}

		tempeDateTime = sDateTime.MonthEnd(sDateTime);//该月月末
		tempedate = tempeDateTime.FormatInt(YYYYMMDD);
		if (tempedate > nCurDate)
		{
			if (1970 == nCurDate/10000)
			{
				strErr = "当前日期为1970,请修改";
				return JSK_FAILURE;
			}
			
			tempedate = nCurDate;
			DBG_PRINT(("tempedate > nCurDate :%u  ",tempedate));
		}
		pTjxxhz[itemp].m_Jzrq = tempedate;

		memset((void*)chValue, 0, sizeof(chValue));
		sprintf(chValue, "where KPRQ>=%u and KPRQ<=%u", pTjxxhz[itemp].m_Qsrq, pTjxxhz[itemp].m_Jzrq);
		DBG_PRINT(("chValue = %s", chValue));
		
		//正废份数
		memset((void*)chTmpValue, 0, sizeof(chTmpValue));
		sprintf(chTmpValue, " and KPLX = %u", WASTE_NOR);
		strTmp = "select count(NO) from INV_HEAD "; 
		strTmp.append(chValue);
		strTmp.append(chTmpValue);
		DBG_PRINT(("strTmp = %s", strTmp.c_str()));
		pInvHead->SetSQL(strTmp);
		pInvHead->GetOneResult(DB_UINT32, (void*)&(pTjxxhz[itemp].m_Zffpfs)); 
		strTmp="";

		//空白作废份数
		memset((void*)chTmpValue, 0, sizeof(chTmpValue));
		sprintf(chTmpValue, " and KPLX = %u", WASTE_INV);
		strTmp = "select count(NO) from INV_HEAD "; 
		strTmp.append(chValue);
		strTmp.append(chTmpValue);
		DBG_PRINT(("strTmp = %s", strTmp.c_str()));
		pInvHead->SetSQL(strTmp);
		pInvHead->GetOneResult(DB_UINT32, (void*)&(pTjxxhz[itemp].m_Kffpfs)); 
		strTmp="";

		
		//正废发票累计税额
		memset((void*)chTmpValue, 0, sizeof(chTmpValue));
		sprintf(chTmpValue, " and KPLX = %u", WASTE_NOR);
		strTmp = "select sum(KPSE) from INV_HEAD "; 
		strTmp.append(chValue);
		strTmp.append(chTmpValue);
		DBG_PRINT(("strTmp = %s", strTmp.c_str()));
		pInvHead->SetSQL(strTmp);
		pInvHead->GetOneResult(DB_INT64, (void*)&(pTjxxhz[itemp].m_Zffpljse)); 
		strTmp="";
        DBG_PRINT(("pTjxxhz[%d].m_Zffpljse= %lld",itemp,pTjxxhz[itemp].m_Zffpljse));


		//正废发票累计金额
		memset((void*)chTmpValue, 0, sizeof(chTmpValue));
		sprintf(chTmpValue, " and KPLX = %u", WASTE_NOR);
		strTmp = "select sum(KPHJJE) from INV_HEAD "; 
		strTmp.append(chValue);
		strTmp.append(chTmpValue);
		DBG_PRINT(("strTmp = %s", strTmp.c_str()));
		pInvHead->SetSQL(strTmp);
		pInvHead->GetOneResult(DB_INT64, (void*)&(nZpHjje)); 
		DBG_PRINT(("nZpHjje= %lld",itemp,nZpHjje));
		pTjxxhz[itemp].m_Zffpljje  =nZpHjje- pTjxxhz[itemp].m_Zffpljse;
		DBG_PRINT(("pTjxxhz[%d].m_Zffpljje= %lld",itemp,pTjxxhz[itemp].m_Zffpljje));
		strTmp="";

		//负废发票累计税额
		memset((void*)chTmpValue, 0, sizeof(chTmpValue));
		sprintf(chTmpValue, " and KPLX = %u", WASTE_RET);
		strTmp = "select sum(KPSE) from INV_HEAD "; 
		strTmp.append(chValue);
		strTmp.append(chTmpValue);
		DBG_PRINT(("strTmp = %s", strTmp.c_str()));
		pInvHead->SetSQL(strTmp);
		pInvHead->GetOneResult(DB_INT64, (void*)&(pTjxxhz[itemp].m_Fffpljse)); 
		strTmp="";
		

		//负废发票累计金额
		memset((void*)chTmpValue, 0, sizeof(chTmpValue));
		sprintf(chTmpValue, " and KPLX = %u", WASTE_RET);
		strTmp = "select sum(KPHJJE) from INV_HEAD "; 
		strTmp.append(chValue);
		strTmp.append(chTmpValue);
		DBG_PRINT(("strTmp = %s", strTmp.c_str()));
		pInvHead->SetSQL(strTmp);
		pInvHead->GetOneResult(DB_INT64, (void*)&(nFpHjje)); 
		DBG_PRINT(("nFpHjje= %lld",itemp,nFpHjje));
		pTjxxhz[itemp].m_Fffpljje  =nFpHjje- pTjxxhz[itemp].m_Fffpljse;
		DBG_PRINT(("pTjxxhz[%d].m_Fffpljje= %lld",itemp,pTjxxhz[itemp].m_Fffpljje));
		strTmp="";
		
		sDateTime = sDateTime.MonthAdd(sDateTime, 1);
		itemp ++;
	}
		
	MonthCount = itemp;//统计查询的月数
	DBG_PRINT(("MonthCount= %d",MonthCount));
	
	return JSK_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////
//需要发票类型和发票类型代码之间的对应关系???
INT32 CJSKInvManageProc::fplx2fplxdm(UINT8 fplx, string &fplxdm)
{
	DBG_PRINT(("fplx = %u", fplx));
	switch(fplx)
	{
	case FPLX_NO_1:		//普票
		fplxdm = FPLX_DM_1;
		break;
	default:
		INT8 buff[8];
		memset(buff, 0, sizeof(buff));
		sprintf(buff, "%03u", fplx);
		fplxdm = buff;
		break;
	}
	
	DBG_PRINT(("fplxdm = %s", fplxdm.c_str()));
	return JSK_SUCCESS;
}

INT32 CJSKInvManageProc::fplxdm2fplx(string fplxdm, UINT8 &fplx)
{
	DBG_PRINT(("fplxdm = %s", fplxdm.c_str()));
	if(fplxdm == FPLX_DM_1)
		fplx = FPLX_NO_1;
	else
		fplx = atoi(fplxdm.c_str());

	DBG_PRINT(("fplx = %u", fplx));
	return JSK_SUCCESS;
}


