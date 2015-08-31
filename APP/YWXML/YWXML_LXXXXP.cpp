 /*! \file    YWXML_LXXXXP.cpp
   \brief    款机调用的中间件接口 业务2.20.离线信息写盘
   \author   YY&LZH
   \version  1.0
   \date     2015
 */

#include "YWXML_LXXXXP.h"
#include "JSKManageProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CLxxxxp::CLxxxxp(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CLxxxxp::~CLxxxxp()
{

}



INT32 CLxxxxp::XmlParse(XMLParse *parse, string &strLxxxmw)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh= parse->GetText();		//税控收款机别号
	DBG_PRINT(("YWXML_LXXXXP: jqbh = %s", m_ywxml_gy.m_jqbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "nsrsbh");
	m_ywxml_gy.m_nsrsbh= parse->GetText();		//纳税人识别号
	DBG_PRINT(("YWXML_LXXXXP: nsrsbh == %s", m_ywxml_gy.m_nsrsbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "sksbbh");
	m_ywxml_gy.m_sksbbh= parse->GetText();		//税控设备编号
	DBG_PRINT(("YWXML_LXXXXP: sksbbh == %s", m_ywxml_gy.m_sksbbh.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "sksbkl");
	m_ywxml_gy.m_sksbkl= parse->GetText();		//税控设备口令
	DBG_PRINT(("YWXML_LXXXXP: sksbkl == %s", m_ywxml_gy.m_sksbkl.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();		//发票类型代码
	DBG_PRINT(("YWXML_LXXXXP: fplxdm == %s", m_ywxml_gy.m_fplxdm.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "lxxxmw");
	strLxxxmw = parse->GetText();		//离线信息密文
	DBG_PRINT(("YWXML_LXXXXP: lxxxmw == %s", strLxxxmw.c_str()));
}

INT32 CLxxxxp::XmlBuild(XMLConstruct *construct, Return_Info *retInfo)
{
	
	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);
	DBG_PRINT(("YWXML_LXXXXP: returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);
	DBG_PRINT(("YWXML_LXXXXP: returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
}


INT32 CLxxxxp::Execute()
{
	string lxxxmw("");
	Return_Info retInfo;	//	返回信息类对象
	INT32 retcode = 0;
	INT8 tmpbuf[64];

	XmlParse(m_pXmlParse, lxxxmw);
	CheckYWXmlPara(retInfo.m_retMsg);

	retcode = CJSKManageProc::LXXXXP_Proc(lxxxmw, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}

	XmlBuild(m_pXmlConstruct, &retInfo);

	return SUCCESS;
}


