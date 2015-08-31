/*! \file    YWXML_KLBG.cpp
   \brief    款机调用的中间件接口 业务: 报税盘信息查询
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "YWXML_KLBG.h"
#include "JSKManageProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CKlbg::CKlbg(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CKlbg::~CKlbg()
{

}


INT32 CKlbg::XmlParse(XMLParse *parse, string &ykl, string &xkl)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh = parse->GetText();		//税控收款机编号
	DBG_PRINT(("m_ywxml_gy.m_jqbh == %s", m_ywxml_gy.m_jqbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "nsrsbh");
	m_ywxml_gy.m_nsrsbh = parse->GetText();	
	DBG_PRINT(("m_ywxml_gy.nsrsbh == %s", m_ywxml_gy.m_nsrsbh.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "sksbbh");
	m_ywxml_gy.m_sksbbh = parse->GetText();	
	DBG_PRINT(("m_ywxml_gy.sksbbh == %s", m_ywxml_gy.m_sksbbh.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "ykl");
	ykl = parse->GetText();	
	m_ywxml_gy.m_sksbkl = ykl;
	DBG_PRINT(("ykl == %s", ykl.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "xkl");
	xkl = parse->GetText();	
	DBG_PRINT(("xkl == %s", xkl.c_str()));

	return SUCCESS;
}

INT32 CKlbg::XmlBuild(XMLConstruct *construct, Return_Info *retInfo)
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


INT32 CKlbg::Execute()
{
	string oldPwd("");
	string newPwd("");
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	
	XmlParse(m_pXmlParse, oldPwd, newPwd);
	CheckYWXmlPara(retInfo.m_retMsg);
	
	retcode = CJSKManageProc::KLBG_Proc(oldPwd, newPwd, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}
	
	XmlBuild(m_pXmlConstruct, &retInfo);

	return SUCCESS;
}





