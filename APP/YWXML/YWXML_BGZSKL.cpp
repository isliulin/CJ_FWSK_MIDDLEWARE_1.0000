/*! \file    YWXML_BGZSKL.cpp
   \brief    款机调用的中间件接口 业务: 变更证书口令
   \author   zcy
   \version  1.0
   \date     2015 
*/

#include "YWXML_BGZSKL.h"
#include "JSKManageProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CBgzskl::CBgzskl(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CBgzskl::~CBgzskl()
{

}


INT32 CBgzskl::XmlParse(XMLParse *parse, string &yzskl, string &xzskl)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;
	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "yzskl");
	yzskl = parse->GetText();	
	DBG_PRINT(("yzskl == %s", yzskl.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "xzskl");
	xzskl = parse->GetText();	
	DBG_PRINT(("xzskl == %s", xzskl.c_str()));

	return SUCCESS;
}

INT32 CBgzskl::XmlBuild(XMLConstruct *construct, Return_Info *retInfo)
{
	
	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;
	
	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);
	DBG_PRINT(("retInfo->m_retCode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);
	DBG_PRINT(("retInfo->m_retMsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;

}


INT32 CBgzskl::Execute()
{
	string oldPwd("");
	string newPwd("");
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	
	XmlParse(m_pXmlParse, oldPwd, newPwd);
	CheckYWXmlPara(retInfo.m_retMsg);
	
	retcode = CJSKManageProc::BGZSKL_Proc(oldPwd, newPwd, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}
	
	XmlBuild(m_pXmlConstruct, &retInfo);

	return SUCCESS;
}





