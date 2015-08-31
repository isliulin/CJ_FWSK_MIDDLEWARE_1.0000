/*! \file     NETXML_FPSCJGHQ.cpp
   \brief    款机调用的中间件接口 业务: 发票明细上传结果获取
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "NETXML_FPSCJGHQ.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"
#include "ServXml_InvUploadResult.h"
#include "GetResultOrganize.h"
#include "JSKInfoDef.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CFpscjghq::CFpscjghq(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CFpscjghq::~CFpscjghq()
{

}


INT32 CFpscjghq::XmlParse(XMLParse *parse, UINT8 &FpmxCount, string &qtxx)
{

	UINT8 i = 0;

	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	FpmxCount = (UINT8)atoi(parse->GetAttr("count").c_str());	//解析XML后得到明细个数
	DBG_PRINT(("FpmxCount == %u", FpmxCount));

	m_ywxml_gy.m_sksbbh = parse->GetAttr("skph");	
	DBG_PRINT(("m_ywxml_gy.m_sksbbh == %s", m_ywxml_gy.m_sksbbh.c_str()));	


	m_ywxml_gy.m_nsrsbh = parse->GetAttr("nsrsbh");
	DBG_PRINT(("m_ywxml_gy.m_nsrsbh == %s", m_ywxml_gy.m_nsrsbh.c_str()))

	m_ywxml_gy.m_kpjh = parse->GetAttr("kpjh");
	DBG_PRINT(("m_ywxml_gy.m_kpjh == %s", m_ywxml_gy.m_kpjh.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;
/*
	for (i=0; i<FpmxCount; i++)
	{
		//得到group节点
		parse->LocateNodeByName(parse->m_parentElement[2], "group", i);
		parse->m_parentElement[3] = parse->m_Child;

		parse->LocateNodeByName(parse->m_parentElement[3], "fplxdm");
		m_ywxml_gy.m_fplxdm = parse->GetText();	
		DBG_PRINT(("m_ywxml_gy.m_fplxdm == %s", m_ywxml_gy.m_fplxdm.c_str()));
	}
*/
	parse->LocateNodeByName(parse->m_parentElement[2], "qtxx");
	qtxx = parse->GetText();	
	DBG_PRINT(("qtxx== %s", qtxx.c_str()));

	return SUCCESS;
}

INT32 CFpscjghq::XmlBuild(XMLConstruct *construct, string Mxjgmw, UINT8 Count, Return_Info *retInfo)
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

// 	construct->AddAttr("fplx_dm", "001");

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

		construct->AddNode(construct->m_parentElement[2], "mxjgmw");
		construct->AddText(Mxjgmw);
		DBG_PRINT(("Mxjgmw : %s", Mxjgmw.c_str()));
	}
*/	
	return SUCCESS;

}


INT32 CFpscjghq::Execute()
{
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	string strErr = "";

	void *pBussness = NULL; 
	CInvUpResultOutinfo InvUpResultOutinfo;
	
	CGetResultOrganize GetResultOrganize;
	CInvUpResult InvUpResult(&GetResultOrganize);
	
	string Mxjgmw = "";  
	UINT8 Count = 0;
	string qtxx = "";

	UINT8 FpmxCount = 0; 
	
	XmlParse(m_pXmlParse, FpmxCount, qtxx);
	retcode = InvUpResult.CommunicationProc(pBussness, (void *)&InvUpResultOutinfo, strErr);
	if(retcode != SUCCESS)
	{
// 		retInfo.m_retCode = JSK_COMMON_ERR_CODE;
// 		retInfo.m_retMsg = strErr;
		m_sslStrErr = strErr;
		return retcode;
	}
	else
	{
		InvUpResult.GetServRetInfo(retInfo.m_retCode, retInfo.m_retMsg);
	}

	Mxjgmw = InvUpResultOutinfo.m_FpSucc.m_scbzFlag;

	XmlBuild(m_pXmlConstruct, Mxjgmw, FpmxCount, &retInfo);

	return SUCCESS;
}





