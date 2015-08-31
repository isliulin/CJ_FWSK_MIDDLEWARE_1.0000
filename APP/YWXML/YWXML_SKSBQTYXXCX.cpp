/*! \file     YWXML_SKSBQTYXXCX.cpp
   \brief    款机调用的中间件接口 业务: 税控设备其他信息查询
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "YWXML_SKSBQTYXXCX.h"
#include "JSKManageProc.h"
#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CSksbqtxxcx::CSksbqtxxcx(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CSksbqtxxcx::~CSksbqtxxcx()
{

}


INT32 CSksbqtxxcx::XmlParse(XMLParse *parse, UINT8 &xxlx)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh = parse->GetText();		//税控收款机编号
	DBG_PRINT(("m_ywxml_gy.m_jqbh == %s", m_ywxml_gy.m_jqbh.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "sksbkl");
	m_ywxml_gy.m_sksbkl = parse->GetText();	
	DBG_PRINT(("m_ywxml_gy.sksbkl == %s", m_ywxml_gy.m_sksbkl.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "xxlx");
	xxlx = atoi(parse->GetText().c_str());	
	DBG_PRINT(("xxlx == %u", xxlx));

	return SUCCESS;
}

INT32 CSksbqtxxcx::XmlBuild(XMLConstruct *construct, string sksbxx, Return_Info *retInfo)
{
	INT8 Buf[64];
	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;
	
	
	construct->AddNode(construct->m_parentElement[2], "sksbxx");
	construct->AddText(sksbxx);
	DBG_PRINT(("sksbxx : %s", sksbxx.c_str()));
	

	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);
	DBG_PRINT(("retInfo->m_retCode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);
	DBG_PRINT(("retInfo->m_retMsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;

}


INT32 CSksbqtxxcx::Execute()
{
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	UINT8 xxlx = 0;
	string sksbxx = "";
	
	XmlParse(m_pXmlParse, xxlx);
	CheckYWXmlPara(retInfo.m_retMsg);
	
	retcode = CJSKManageProc::SKSBQTYXXCX_Proc(m_ywxml_gy.m_fplxdm, xxlx, sksbxx, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}
	
	XmlBuild(m_pXmlConstruct, sksbxx, &retInfo);
	
	return SUCCESS;
}



