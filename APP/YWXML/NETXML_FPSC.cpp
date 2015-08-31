/*! \file     NETXML_FPSC.cpp
   \brief    款机调用的中间件接口 业务: 发票上传
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "NETXML_FPSC.h"
#include "JSKMakeInvoice.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"

#include "ServXml_InvUpload.h"
#include "CInvHead.h"
#include "InvUploadOrganize.h"
#include "GlobalNetArg.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CFpsc::CFpsc(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CFpsc::~CFpsc()
{

}


INT32 CFpsc::XmlParse(XMLParse *parse, string &Fpmx, UINT8 &FpmxCount, UINT32 &Fpzs)
{

	UINT8 i = 0;

	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	FpmxCount = (UINT8)atoi(parse->GetAttr("count").c_str());	//解析XML后得到明细个数
	DBG_PRINT(("FpmxCount == %u", FpmxCount));

	m_ywxml_gy.m_sksbbh = parse->GetAttr("skph");	
	DBG_PRINT(("m_ywxml_gy.skph == %s", m_ywxml_gy.m_sksbbh.c_str()));	

	m_ywxml_gy.m_nsrsbh = parse->GetAttr("nsrsbh");
	DBG_PRINT(("m_ywxml_gy.m_nsrsbh == %s", m_ywxml_gy.m_nsrsbh.c_str()));

	m_ywxml_gy.m_kpjh = parse->GetAttr("kpjh");
	DBG_PRINT(("m_ywxml_gy.m_kpjh == %s", m_ywxml_gy.m_kpjh.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;

	for (i=0; i<FpmxCount; i++)
	{
		//得到group节点
		parse->LocateNodeByName(parse->m_parentElement[2], "group", i);
		parse->m_parentElement[3] = parse->m_Child;

		parse->LocateNodeByName(parse->m_parentElement[3], "fplxdm");
		m_ywxml_gy.m_fplxdm = parse->GetText();	
		DBG_PRINT(("m_ywxml_gy.m_fplxdm == %s", m_ywxml_gy.m_fplxdm.c_str()));

		parse->LocateNodeByName(parse->m_parentElement[3], "fpzs");
		Fpzs = atoi(parse->GetText().c_str());	
		DBG_PRINT(("Fpzs== %u", Fpzs));

		parse->LocateNodeByName(parse->m_parentElement[3], "fpmx");
		Fpmx = parse->GetText();	
		//DBG_PRINT(("Fpmx == %s", Fpmx.c_str()));
	
	}

	return SUCCESS;
}

INT32 CFpsc::XmlBuild(XMLConstruct *construct, UINT8 Count, Return_Info *retInfo)
{
/*
	INT8 Buf[64];

	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%u", Count);
	construct->AddAttr("count", Buf);
	DBG_PRINT(("buf : %s", Buf));

	construct->AddAttr("skph", m_ywxml_gy.m_sksbbh);
	DBG_PRINT(("m_ywxml_gy.m_sksbbh : %s", m_ywxml_gy.m_sksbbh.c_str()));

	construct->AddAttr("nsrsbh", m_ywxml_gy.m_nsrsbh);
	DBG_PRINT(("m_ywxml_gy.m_nsrsbh : %s", m_ywxml_gy.m_nsrsbh.c_str()));

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;
	
	for (UINT8 i=1; i<=Count; i++)
	{
		construct->AddNode(construct->m_parentElement[2], "group");
		construct->m_parentElement[3] = construct->m_NewElement;
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%u", i);
		DBG_PRINT(("Buf = %s", Buf));
		construct->AddAttr("xh", Buf);

		construct->AddNode(construct->m_parentElement[2], "fplxdm");
		construct->AddText(m_ywxml_gy.m_fplxdm);
		DBG_PRINT(("m_ywxml_gy.m_fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));
		
		construct->AddNode(construct->m_parentElement[2], "returncode");
		construct->AddText(retInfo->m_retCode);
		DBG_PRINT(("retInfo->m_retCode : %s", retInfo->m_retCode.c_str()));
		
		construct->AddNode(construct->m_parentElement[2], "returnmsg");
		construct->AddText(retInfo->m_retMsg);
		DBG_PRINT(("retInfo->m_retMsg : %s", retInfo->m_retMsg.c_str()));

		construct->AddNode(construct->m_parentElement[2], "slxlh");
		construct->AddText(strSlxlh);
		DBG_PRINT(("slxlh : %s", strSlxlh.c_str()));

	}
*/	
	return SUCCESS;
}


INT32 CFpsc::Execute()
{
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	string strErr = "";

	CDataInvHead dataInvHead;	
 	void *pDateOut = NULL;

	CInvUploadOrganize InvUploadOrganize;
	CInvUpload InvUpload(&InvUploadOrganize);
	
	string Fpmx = ""; 
	UINT8 FpmxCount = 0; 
	UINT32 Fpzs = 0;
	
	XmlParse(m_pXmlParse, Fpmx, FpmxCount, Fpzs);
	
	CJSKMakeInvoice::Str2InvHead((INT8 *)Fpmx.c_str(), &dataInvHead);  //将上面解析出来的Fpmx转换为InvHead

	g_gNetArg->SetBaseInfo(m_ywxml_gy.m_nsrsbh,m_ywxml_gy.m_kpjh,m_ywxml_gy.m_sksbbh);

	retcode = InvUpload.CommunicationProc((void *)&dataInvHead, pDateOut, strErr);
	if(retcode != SUCCESS)
	{
// 		retInfo.m_retCode = JSK_COMMON_ERR_CODE;
// 		retInfo.m_retMsg = strErr;
		m_sslStrErr = strErr;
		return retcode;
	}
	else
	{
		InvUpload.GetServRetInfo(retInfo.m_retCode, retInfo.m_retMsg);
	}
	
	XmlBuild(m_pXmlConstruct, FpmxCount, &retInfo);
	
	return SUCCESS;
}





