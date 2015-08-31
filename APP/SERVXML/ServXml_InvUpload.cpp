/*! \file   ServXml_InvUpload.pp
   \brief    网络接口 业务: 发票上传接口
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "ServXml_InvUpload.h"
#if SSL_USE_TYPE == 1
#include "uniAcceptFrameworkApi.h"
#endif
#include "TDateTime.h"
#include "base64.h"
#include "CInvHead.h"
#include "GlobalNetArg.h"
#include "SysMacDef.h"
#include "JSKInfoDef.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CInvUpload::CInvUpload(ProtocolOrganize *p):ProtocolXML(p)
{
	setDeclaration(XML_DEF_VERSION, XML_DEF_ENCODING, GBK_CHAR_TYPE);
	setXmlSaveFile(XML_DEF_INVUPLOAD_REQFILE, XML_DEF_BUSSINESS_RSPFILE); 
}

CInvUpload::~CInvUpload()
{
	DBG_PRINT(("in ~CNsrPara()"))
}

INT32 CInvUpload::XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("IN CInvUpload::XmlBusinessBuild"));
	DBG_ASSERT_EXIT((pBusiness != NULL), (" pData == NULL!"));
	
	INT8 Buf[64];
	CDataInvHead *pInvHead = (CDataInvHead *)pBusiness;

	UINT8 j=0;

	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "INPUT");
	pXmlBuild->m_parentElement[1] = pXmlBuild->m_NewElement;
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "NSRSBH");
	pXmlBuild->AddText(g_gNetArg->m_nsrsbh);
	DBG_PRINT(("g_gNetArg->m_nsrsbh : %s", g_gNetArg->m_nsrsbh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "KPJH");
	pXmlBuild->AddText(g_gNetArg->m_kpjh);
	DBG_PRINT(("g_gNetArg->m_kpjh : %s", g_gNetArg->m_kpjh.c_str()));
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "SBBH");
	pXmlBuild->AddText(g_gNetArg->m_sbbh);
	DBG_PRINT(("g_gNetArg->m_sbbh : %s", g_gNetArg->m_sbbh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "FP");
	pXmlBuild->m_parentElement[2] = pXmlBuild->m_NewElement;

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "FPZL");
	pXmlBuild->AddText(pInvHead->m_fplxdm);
// 	memset(Buf, 0, sizeof(Buf));
// 	sprintf(Buf, "%u", pInvHead->m_fplb);
// 	pXmlBuild->AddText(Buf);
// 	DBG_PRINT(("pInvHead->m_fplb : %s", Buf));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "FPDM");
	pXmlBuild->AddText(pInvHead->m_fpdm);
	DBG_PRINT(("InvHead->m_fpdm : %s", pInvHead->m_fpdm.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "FPHM");
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%08u", pInvHead->m_fphm);
	pXmlBuild->AddText(Buf);
	DBG_PRINT(("pInvHead->m_fphm : %s", Buf));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "TSPZ");	//UINT32 m_xxpzlb;		/**< 票种类别 */
// 	memset(Buf, 0, sizeof(Buf));
// 	sprintf(Buf, "%u", pInvHead->m_xxpzlb);
	pXmlBuild->AddText("");	//特殊票钟赋空
// 	DBG_PRINT(("pInvHead->m_xxpzlb : %s", Buf));

	DBG_PRINT(("pInvHead->m_kplx = %u", pInvHead->m_kplx));
	string fpztbz("");
	string zfbz("N");
	switch(pInvHead->m_kplx)
	{
	case JSK_NORMAL_INV:
		fpztbz = "0";
		break;
	case JSK_RETURN_INV:
		fpztbz = "1";
		break;
	case JSK_WASTE_INV:
		zfbz = "Y";
		fpztbz = "2";
		break;
	case JSK_WASTE_NOR:
		zfbz = "Y";
		fpztbz = "3";
		break;
	case JSK_WASTE_RET:
		zfbz = "Y";
		fpztbz = "4";
		break;
	}
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "FPZTBZ");
	pXmlBuild->AddText(fpztbz);
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "ZFBZ");
	pXmlBuild->AddText(zfbz);
	DBG_PRINT(("pInvHead->m_zfbz : %s", zfbz.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "MW"); 
	pXmlBuild->AddText("");
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "XFSH");
//	pXmlBuild->AddText(pInvHead->m_xfsh);
	pXmlBuild->AddText(g_gNetArg->m_nsrsbh);
	DBG_PRINT(("pInvHead->m_xfsh : %s", pInvHead->m_xfsh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "XFMC");
	pXmlBuild->AddText(pInvHead->m_xfmc);
	DBG_PRINT(("pInvHead->m_xfmc : %s", pInvHead->m_xfmc.c_str()));
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "XFDZDH");
	pXmlBuild->AddText(pInvHead->m_xfdzdh);
	DBG_PRINT(("pInvHead->m_xfdzdh : %s", pInvHead->m_xfdzdh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "XFYHZH");
	pXmlBuild->AddText(pInvHead->m_xfyhzh);
	DBG_PRINT(("pInvHead->m_xfyhzh : %s", pInvHead->m_xfyhzh.c_str()));
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "GFSH");
	pXmlBuild->AddText(pInvHead->m_payerCode);
	DBG_PRINT(("pInvHead->m_payerCode : %s", pInvHead->m_payerCode.c_str()));

	DBG_PRINT(("pInvHead->m_fkdw : %s", pInvHead->m_fkdw.c_str()));
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "GFMC");
	pXmlBuild->AddText(pInvHead->m_fkdw);
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "GFDZDH");
	pXmlBuild->AddText(pInvHead->m_gfdzdh);
	DBG_PRINT(("pInvHead->m_gfdzdh : %s", pInvHead->m_gfdzdh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "GFYHZH");
	pXmlBuild->AddText(pInvHead->m_gfyhzh);
	DBG_PRINT(("pInvHead->m_gfyhzh : %s", pInvHead->m_gfyhzh.c_str()));
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "KPRQ");
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%u", pInvHead->m_kprq);
	pXmlBuild->AddText(Buf);
	DBG_PRINT(("KPRQ : %s", Buf));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "KPSJ");
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%06u", pInvHead->m_kpsj);
	pXmlBuild->AddText(Buf);
	DBG_PRINT(("KPSJ : %s", Buf));

	if(zfbz == "Y")
	{
		DBG_PRINT(("pInvHead->m_zfsj= %s",pInvHead->m_zfsj.c_str()));
		TDateTime zfDate(pInvHead->m_zfsj.c_str(), DATETIME_POS);
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "ZFRQ");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%u", zfDate.FormatInt(YYYYMMDD));
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("ZFRQ : %s", Buf));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "ZFSJ");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%06u", zfDate.FormatInt(HHMMSS));
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("ZFSJ : %s", Buf));
	}
	else
	{
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "ZFRQ");
		pXmlBuild->AddText("");
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "ZFSJ");
		pXmlBuild->AddText("");
	}
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "JE");
	memset(Buf, 0, sizeof(Buf));
	DBG_PRINT(("pInvHead->m_kpje: %lld", pInvHead->m_kpje));
	sprintf(Buf, "%.2lf", ((double)(pInvHead->m_kpje)*1.0)/SUM_EXTENSION);
	pXmlBuild->AddText(Buf);
	DBG_PRINT(("pInvHead->m_kpje : %s", Buf));
	
	DBG_PRINT(("pInvHead->m_kpse: %lld", pInvHead->m_kpse));
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "SE");
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%.2lf", ((double)pInvHead->m_kpse *1.0)/SUM_EXTENSION);
	pXmlBuild->AddText(Buf);
	DBG_PRINT(("pInvHead->m_kpse : %s", Buf));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "JSHJ");
	memset(Buf, 0, sizeof(Buf));
	pInvHead->m_kphjje = pInvHead->m_kpje + pInvHead->m_kpse;
	DBG_PRINT(("pInvHead->m_kphjje: %lld", pInvHead->m_kphjje));
	sprintf(Buf, "%.2lf", ((double)pInvHead->m_kphjje *1.0)/SUM_EXTENSION);
	pXmlBuild->AddText(Buf);
	DBG_PRINT(("pInvHead->m_kphjje : %s", Buf));
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "BZ");
	UINT8 baseBuf[256];
	memset(baseBuf, 0, sizeof(baseBuf));
	sprintf((INT8 *)baseBuf, "%s", pInvHead->m_backup1.c_str());
	Base64_Encode_2(baseBuf, pInvHead->m_backup1.length());
	string tmpStr = (INT8 *)baseBuf;
	pXmlBuild->AddText(tmpStr);
	DBG_PRINT(("pInvHead->m_backup1 : %s", pInvHead->m_backup1.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "KPR");
	pXmlBuild->AddText(pInvHead->m_sky);
	DBG_PRINT(("pInvHead->m_sky : %s", pInvHead->m_sky.c_str()));
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "SKR");
	pXmlBuild->AddText(pInvHead->m_sky);
	DBG_PRINT(("pInvHead->m_sky : %s", pInvHead->m_sky.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "FHR");
	pXmlBuild->AddText(pInvHead->m_sky);

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "HZFPXXBBH");
	pXmlBuild->AddText("");

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "JYM");
	pXmlBuild->AddText(pInvHead->m_fwm);
	DBG_PRINT(("pInvHead->m_fwm : %s", pInvHead->m_fwm.c_str()));

	if( (fpztbz == "1") || (fpztbz == "4") )
	{
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "LZFPDM");
		pXmlBuild->AddText(pInvHead->m_yfpdm);
		DBG_PRINT(("pInvHead->m_yfpdm : %s", pInvHead->m_yfpdm.c_str()));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "LZFPHM");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%u",  pInvHead->m_yfphm);
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("pInvHead->m_yfphm : %u", pInvHead->m_yfphm));
	}
	else
	{
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "LZFPDM");
		pXmlBuild->AddText("");
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "LZFPHM");
		pXmlBuild->AddText("");
	}
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "DKNSRSBH");
	pXmlBuild->AddText("");

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "DKQYMC");
	pXmlBuild->AddText("");
	

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "MX");
	pXmlBuild->m_parentElement[3] = pXmlBuild->m_NewElement;

	vector<CDataInvDet>::iterator pInvDet;
	for (pInvDet=pInvHead->m_gvector.begin(); pInvDet!=pInvHead->m_gvector.end(); ++pInvDet)
	{
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[3], "MXXX");
		pXmlBuild->m_parentElement[4] = pXmlBuild->m_NewElement;
		
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "MXXH");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%u", pInvDet->m_sphxh);
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("pInvDet->m_sphxh : %s", Buf));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "MC");
		pXmlBuild->AddText(pInvDet->m_spmc);
		DBG_PRINT(("pInvDet->m_spmc : %s", pInvDet->m_spmc.c_str()));
		
		DBG_PRINT(("pInvDet->m_spje : %lld", pInvDet->m_spje));
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "JE");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.2lf", ((double)pInvDet->m_je*1.0)/SUM_EXTENSION);
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("pInvDet->m_je : %s", Buf));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "SL");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.2lf", (double)pInvDet->m_sl);
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("pInvDet->m_sl : %s", Buf));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "SE");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.2lf", ((double)pInvDet->m_spse*1.0)/SUM_EXTENSION);
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("pInvDet->m_spse : %s", Buf));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "HSJE");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.2lf", ((double)pInvDet->m_spje*1.0)/SUM_EXTENSION);
		//sprintf(Buf, "%.2lf", fabs(((double)pInvDet->m_spje*1.0)/SUM_EXTENSION));
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("pInvDet->m_spje : %s", Buf));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "HSDJ");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.3lf00000", pInvDet->m_spdj);
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("pInvDet->m_spdj : %s", Buf));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "SHUL");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%0.3lf00000",  pInvDet->m_spsl);
		//sprintf(Buf, "%0.8lf",  fabs(pInvDet->m_spsl));
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("pInvDet->m_spsl : %s", Buf));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "DJ");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.3lf00000", pInvDet->m_dj);
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("pInvDet->m_dj : %s", Buf));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "GGXH");
		pXmlBuild->AddText("");
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "JLDW");
		pXmlBuild->AddText(pInvDet->m_spdw);
		DBG_PRINT(("pInvDet->m_spdw : %s", pInvDet->m_spdw.c_str()));
	}
/*
	CDataInvDet *pInvDet = pInvHead->pHead;

	for(j=1; j<=pInvHead->m_sphsl; j++, pInvDet=pInvDet->pNext)
	{
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[3], "MXXX");
		pXmlBuild->m_parentElement[4] = pXmlBuild->m_NewElement;

		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "MXXH");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%u", pInvDet->m_sphxh);
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("pInvDet->m_sphxh : %s", Buf));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "MC");
		pXmlBuild->AddText(pInvDet->m_spmc);
		DBG_PRINT(("pInvDet->m_spmc : %s", pInvDet->m_spmc.c_str()));
		
		DBG_PRINT(("pInvDet->m_spje : %lld", pInvDet->m_spje));
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "JE");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.2lf", ((double)pInvDet->m_je*1.0)/SUM_EXTENSION);
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("pInvDet->m_je : %s", Buf));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "SL");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.2lf", (double)pInvDet->m_sl);
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("pInvDet->m_sl : %s", Buf));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "SE");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.2lf", ((double)pInvDet->m_spse*1.0)/SUM_EXTENSION);
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("pInvDet->m_spse : %s", Buf));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "HSJE");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.2lf", ((double)pInvDet->m_spje*1.0)/SUM_EXTENSION);
		//sprintf(Buf, "%.2lf", fabs(((double)pInvDet->m_spje*1.0)/SUM_EXTENSION));
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("pInvDet->m_spje : %s", Buf));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "HSDJ");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.3lf00000", pInvDet->m_spdj);
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("pInvDet->m_spdj : %s", Buf));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "SHUL");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%0.3lf00000",  pInvDet->m_spsl);
		//sprintf(Buf, "%0.8lf",  fabs(pInvDet->m_spsl));
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("pInvDet->m_spsl : %s", Buf));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "DJ");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.3lf00000", pInvDet->m_dj);
		pXmlBuild->AddText(Buf);
		DBG_PRINT(("pInvDet->m_dj : %s", Buf));
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "GGXH");
		pXmlBuild->AddText("");
		
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[4], "JLDW");
		pXmlBuild->AddText(pInvDet->m_spdw);
		DBG_PRINT(("pInvDet->m_spdw : %s", pInvDet->m_spdw.c_str()));
		
	}
*/
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "SIGN");
	pXmlBuild->AddText(pInvHead->m_casign);
	DBG_PRINT(("pInvHead->m_casign : %s", pInvHead->m_casign.c_str()));

	return SUCCESS;
}

INT32 CInvUpload::XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("CInvUpload::XmlBusinessParse Begin"));
/*	int res = 0;
	string tmpStr("");
	string tmpCode;
	string tmpMess;
	
//	CInvUploadOutInfo *p = (CInvUploadOutInfo *)pBusiness;
	INT32 layer = pXmlParse->m_signNodeLayer;
	
	pXmlParse->LocateNodeByName(pXmlParse->m_signNode, "OUTPUT");
	pXmlParse->m_parentElement[layer+1] = pXmlParse->m_Child;

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+1], "CODE");
	tmpCode = pXmlParse->GetText();

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+1], "MESS");
	tmpMess = pXmlParse->GetText();
	SetServRetInfo(tmpCode, tmpMess);

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+1], "DATA");
	pXmlParse->m_parentElement[layer+2] = pXmlParse->m_Child;

// 	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "NSRSBH");
// 	tmpStr = pXmlParse->GetText();
// 
// 	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "KPJH");
// 	tmpStr = pXmlParse->GetText();
// 	
// 	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "SBBH");
// 	tmpStr = pXmlParse->GetText();
	
	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "SLXLH");
	tmpStr = pXmlParse->GetText();
	g_gNetArg->SetSlxlh(tmpStr);
*/	

	memset(g_Xml_ExchangeBuf_Inv, 0, PROTOCOL_OUT_BUFF_LEN);
	memcpy(g_Xml_ExchangeBuf_Inv, pData->pBuff, pData->outLen);
	pData->fill(g_Xml_ExchangeBuf_Inv, pData->outLen);
	memset(g_Xml_ExchangeBuf_Inv, 0, PROTOCOL_OUT_BUFF_LEN);

	return SUCCESS;
}

INT32 CInvUpload::CommunicationProc(void* pDataIn, void* pDataOut, string &strErr)
{
	INT32 res = 0;

	NoteData_Para noteData;
	noteData.m_appType = NET_FPSC;	//此处设置业务类型
	DataOutType dataOut(g_Xml_OutBuf_Inv, PROTOCOL_OUT_BUFF_LEN);
	res = BuildXml(pDataIn, &dataOut, &noteData, strErr);
	DBG_PRINT(("res = %u", res));
	if (res != SUCCESS)
	{
		return res;
	}
	
	DBG_PRINT(("outLen = %d", dataOut.outLen));

	//////////////////////////////////////////////////////////////////////////
	//此处为处理流程，将上面组织的数据发送给库SSL接口，接收到的数据放入g_Xml_OutBuf_Inv中。
	//////////////////////////////////////////////////////////////////////////
#if SSL_USE_TYPE == 1
	int rec_len = PROTOCOL_OUT_BUFF_LEN;
	CTechnologyMsg pTechMsg;
	string strTechMsg("");

	pTechMsg.m_nsrsbh = g_gNetArg->m_nsrsbh;
	pTechMsg.m_servIP = g_gNetArg->m_servIP;
	pTechMsg.m_servPort = g_gNetArg->m_servPort;
	pTechMsg.m_passWord = g_gNetArg->m_strzskl;
	pTechMsg.m_certPwd = g_gNetArg->m_strzskl;
	pTechMsg.m_servId = TECH_MSG_SERV_ID_INV;
	if(g_gNetArg->m_servId != "")
	{
		pTechMsg.m_servId = g_gNetArg->m_servId;
	}
	GetTechMsgStr(&pTechMsg, strTechMsg);
	UINT8 errBuf[1024];
	memset(errBuf, 0, sizeof(errBuf));

// 	printf("------------------------send-------------------------------------\n");
// 	DBG_PRINT(("dataOut.outLen = %d", dataOut.outLen));
// 	printf("%s\n", g_Xml_OutBuf_Inv);
// 	printf("\n----------------------send---------------------------------------\n");

	int retval = 0;
#if NET_LOCK_FLAG == 1
	CJSKInfoFunc::MutexLock();
#endif
	retval=aisino_ssl_transfer_call(SSL_AUTH_CODE,(char*)strTechMsg.c_str(),strTechMsg.size(),
		(unsigned char*)g_Xml_OutBuf_Inv,dataOut.outLen,(unsigned char*)g_Xml_ExchangeBuf_Inv,&rec_len,errBuf);
#if NET_LOCK_FLAG == 1
	CJSKInfoFunc::MutexUnlock();
#endif
	DBG_PRINT(("retval = %d", retval));
	if( retval != 0)
	{
		DBG_PRINT(("errBuf = %s", errBuf));
		//strErr = (INT8 *)errBuf;
		strErr = "网络通信错误!";
		return retval;
	}

	DBG_PRINT(("rec_len = %d", rec_len));
	dataOut.fill(g_Xml_ExchangeBuf_Inv, rec_len);
	memset(g_Xml_ExchangeBuf_Inv, 0, PROTOCOL_OUT_BUFF_LEN);

#ifdef XML_DEBUG_OUT
	printf("--------------------------CInvUpload rec begin-----------------------------------\n");
	DBG_PRINT(("rec_len = %d", rec_len));
	printf("%s\n", g_Xml_OutBuf_Inv);
	printf("\n------------------------CInvUpload rec end-------------------------------------\n");
#endif
#endif

	res = ParseXml(pDataOut, &dataOut, &noteData, strErr);
	DBG_PRINT(("res = %d", res));
	if (res != SUCCESS)
	{
		return res;
	}
	
	return SUCCESS;
}

