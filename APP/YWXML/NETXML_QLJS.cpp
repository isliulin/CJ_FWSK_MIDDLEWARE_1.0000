/*! \file     NETXML_QLJS.cpp
   \brief    款机调用的中间件接口 业务: 3.4.清零解锁
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "NETXML_QLJS.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"
#include "GetResultOrganize.h"
#include "ServXml_Qkxxxz.h"
#include "JSKInfoDef.h"
#include "GlobalNetArg.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CQljs::CQljs(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CQljs::~CQljs()
{

}


INT32 CQljs::XmlParse(XMLParse *parse, string &Kpjh, UINT8 &FpmxCount, string &Qtxx)
{

	UINT8 i = 0;

	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	FpmxCount = (UINT8)atoi(parse->GetAttr("count").c_str());	//解析XML后得到明细个数
	DBG_PRINT(("FpmxCount == %u", FpmxCount));

	m_ywxml_gy.m_sksbbh = parse->GetAttr("skph");//税控设备编号属性	
	DBG_PRINT(("m_ywxml_gy.m_sksbbh == %s", m_ywxml_gy.m_sksbbh.c_str()));	

	m_ywxml_gy.m_nsrsbh = parse->GetAttr("nsrsbh");//纳税人识别号属性	
	DBG_PRINT(("m_ywxml_gy.m_nsrsbh == %s", m_ywxml_gy.m_nsrsbh.c_str()))

	m_ywxml_gy.m_kpjh = parse->GetAttr("kpjh");
	DBG_PRINT(("m_ywxml_gy.m_kpjh == %s", m_ywxml_gy.m_kpjh.c_str()));

	Kpjh = parse->GetAttr("kpjh");//开票机号属性
	DBG_PRINT(("Kpjh == %s", Kpjh.c_str()))

	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;
/*
	for (i=0; i<FpmxCount; i++)
	{
		//得到group节点
		parse->LocateNodeByName(parse->m_parentElement[2], "group", i);
		parse->m_parentElement[3] = parse->m_Child;

		parse->LocateNodeByName(parse->m_parentElement[3], "fplxdm");
		m_ywxml_gy.m_fplxdm = parse->GetText();	//发票类型代码
		DBG_PRINT(("m_ywxml_gy.m_fplxdm == %s", m_ywxml_gy.m_fplxdm.c_str()));
	}
*/
	parse->LocateNodeByName(parse->m_parentElement[2], "qtxx");
	Qtxx = parse->GetText();	
	DBG_PRINT(("qtxx == %s", Qtxx.c_str()));

	return SUCCESS;
}

INT32 CQljs::XmlBuild(XMLConstruct *construct, CServWlcb *ServWlcb, UINT8 Count, Return_Info *retInfo)
{
/*	INT8 Buf[64];
	string Szjkmw = "szjkwm222"; //为测试添加，20150430_linzihao

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
		DBG_PRINT(("xh = %s", Buf));
		construct->AddAttr("xh", Buf);

		construct->AddNode(construct->m_parentElement[3], "fplxdm");
		construct->AddText(m_ywxml_gy.m_fplxdm);
		DBG_PRINT(("m_ywxml_gy.m_fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));

		construct->AddNode(construct->m_parentElement[3], "fpjkmw");
		construct->AddText(ServWlcb->m_qkxx);//新的发票监控密文,对应业务七:清卡信息下载中的清卡信息
		DBG_PRINT(("Fpjkmw : %s", ServWlcb->m_qkxx.c_str()));

		construct->AddNode(construct->m_parentElement[3], "szjkmw");
		construct->AddText(Szjkmw);//新的时钟监控密文，待赋值
		DBG_PRINT(("Szjkmw : %s", Szjkmw.c_str()));
		
		construct->AddNode(construct->m_parentElement[3], "returncode");
		construct->AddText(retInfo->m_retCode);
		DBG_PRINT(("returncode : %s", retInfo->m_retCode.c_str()));
		
		construct->AddNode(construct->m_parentElement[3], "returnmsg");
		construct->AddText(retInfo->m_retMsg);
		DBG_PRINT(("returnmsg : %s", retInfo->m_retMsg.c_str()));
	}
*/
	return SUCCESS;

}


INT32 CQljs::Execute()
{
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	string strErr = "";
	
	string Kpjh = "";
	string Qtxx = "";

	CServWlcb ServWlcb;

	CGetResultOrganize GetResultOrganize;
	CServQkxxxz ServQkxxxz(&GetResultOrganize);
	UINT8 FpmxCount = 0; 

	XmlParse(m_pXmlParse, Kpjh, FpmxCount, Qtxx);

	ServWlcb.m_cssj = Qtxx;//将3.4解析出的"其他信息"赋值给业务七:清卡信息下载的"抄税时间"_linzihao

	retcode = ServQkxxxz.CommunicationProc((void *)&ServWlcb, (void *)&ServWlcb, strErr);
	if(retcode != SUCCESS)
	{
// 		retInfo.m_retCode = JSK_COMMON_ERR_CODE;
// 		retInfo.m_retMsg = strErr;
		m_sslStrErr = strErr;
		return retcode;
	}
	else
	{
		ServQkxxxz.GetServRetInfo(retInfo.m_retCode, retInfo.m_retMsg);
	}
	
	XmlBuild(m_pXmlConstruct, &ServWlcb, FpmxCount, &retInfo);
	
	return SUCCESS;
}





