/*! \file     NETXML_WLCB.cpp
   \brief    款机调用的中间件接口 业务:3.3.  网络抄报
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "NETXML_WLCB.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"
#include "YccbOrganize.h"
#include "ServXml_Yccb.h"
#include "ServWlcb.h"
#include "JSKInfoDef.h"

//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CWlcb::CWlcb(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CWlcb::~CWlcb()
{

}


INT32 CWlcb::XmlParse(XMLParse *parse, string &Sq, string &Fpmx, string &Fpdxx, string &Fphzsj, string &Szfphz, UINT8 &FpmxCount, string &Qtxx)
{
	string tmpStr("");
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
	DBG_PRINT(("m_ywxml_gy.m_kpjh == %s", m_ywxml_gy.m_kpjh.c_str()))

	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;

	for (i=0; i<FpmxCount; i++)
	{
		//得到group节点
		parse->LocateNodeByName(parse->m_parentElement[2], "group", i);
		parse->m_parentElement[3] = parse->m_Child;

		parse->LocateNodeByName(parse->m_parentElement[3], "fplxdm");
		m_ywxml_gy.m_fplxdm = parse->GetText();	
		DBG_PRINT(("m_ywxml_gy.m_fplxdm == %s",m_ywxml_gy.m_fplxdm.c_str()));

		parse->LocateNodeByName(parse->m_parentElement[3], "sq");
		Sq = parse->GetText();	
		DBG_PRINT(("Sq == %s", Sq.c_str()));

// 		parse->LocateNodeByName(parse->m_parentElement[3], "fpmx");
// 		Fpmx = parse->GetText();	
// 		DBG_PRINT(("Fpmx == %s", Fpmx.c_str()));
// 
// 		parse->LocateNodeByName(parse->m_parentElement[3], "fpdxx");
// 		Fpdxx = parse->GetText();	
// 		DBG_PRINT(("Fpdxx == %s", Fpdxx.c_str()));

		parse->LocateNodeByName(parse->m_parentElement[3], "fphz");
		Fphzsj = parse->GetText();	
//		DBG_PRINT(("Fphzsj == %s", Fphzsj.c_str()));

// 		parse->LocateNodeByName(parse->m_parentElement[3], "szfphz");
// 		Szfphz = parse->GetText();	
// 		DBG_PRINT(("Szfphz == %s", Szfphz.c_str()));
// 
// 		parse->LocateNodeByName(parse->m_parentElement[3], "sfjchz");
// 		tmpStr = parse->GetText();	
// 		DBG_PRINT(("sfjchz == %s", tmpStr.c_str()));
		
		parse->LocateNodeByName(parse->m_parentElement[3], "qtxx");
		Qtxx = parse->GetText();	
		DBG_PRINT(("Qtxx == %s", Qtxx.c_str()));
	}

	return SUCCESS;
}

INT32 CWlcb::XmlBuild(XMLConstruct *construct, UINT8 Count, Return_Info *retInfo)
{
/*
	INT8 Buf[64];

	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%u", Count);
	construct->AddAttr("count", Buf);
	DBG_PRINT(("count : %s", Buf));

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
	}
*/	
	return SUCCESS;

}


INT32 CWlcb::Execute()
{
	//XML解析输出的数据	
	string Sq = "";
	string Fpmx = "";
	string Fpdxx  = "";
	string Fphzsj = "";
	string Szfphz = "";
	UINT8  FpmxCount = 0;
	string Qtxx = "";
	string tmpTime("");
	XmlParse(m_pXmlParse, Sq, Fpmx, Fpdxx, Fphzsj, Szfphz, FpmxCount, Qtxx);

	CServWlcb servwlcb;
	servwlcb.m_fplxdm = m_ywxml_gy.m_fplxdm;
	servwlcb.m_hzxx = Fphzsj;//将3.3网络抄报中的"发票汇总数据"赋值给远程抄报中的"汇总信息"
	tmpTime = Sq.substr(14, 14);
	TDateTime tmpCssj(tmpTime.c_str(), DATETIME_POS);
	servwlcb.m_cssj = tmpCssj.FormatString(YYYYMMDDHHMM);
	servwlcb.m_ssqrs = Qtxx;
	
	CYccbOrganize YccbOrganize;
	CServYccb ServYccb(&YccbOrganize);

	string strErr = "";	
	INT32 retcode = 0;
	retcode = ServYccb.CommunicationProc((void *)(&servwlcb), (void *)(&servwlcb), strErr);
	
	Return_Info retInfo;
	if(retcode != SUCCESS)
	{
// 		retInfo.m_retCode = JSK_COMMON_ERR_CODE;
// 		retInfo.m_retMsg = strErr;
		m_sslStrErr = strErr;
		return retcode;
	}
	else
	{
		ServYccb.GetServRetInfo(retInfo.m_retCode, retInfo.m_retMsg);
	}

	XmlBuild(m_pXmlConstruct, FpmxCount, &retInfo);

	return SUCCESS;
}





