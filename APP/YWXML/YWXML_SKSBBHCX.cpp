 /*! \file    YWXML_SKSBBHCX.cpp
   \brief    款机调用的中间件接口 业务2.1 税控设备编号查询
   \author   YY
   \version  1.0
   \date     2015
 */

#include "YWXML_SKSBBHCX.h"
#include "JSKManageProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CSksbbhcx::CSksbbhcx(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CSksbbhcx::~CSksbbhcx()
{

}


INT32 CSksbbhcx::XmlParse(XMLParse *parse)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh = parse->GetText();		//税控收款机编号
	DBG_PRINT(("m_ywxml_gy.m_jqbh == %s", m_ywxml_gy.m_jqbh.c_str()));	

	return SUCCESS;
}

INT32 CSksbbhcx::XmlBuild(XMLConstruct *construct, string sksbbh, string bspbh, string qtxx, Return_Info *retInfo)
{
	
	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;


	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	
	construct->AddNode(construct->m_parentElement[2], "sksbbh");
	construct->AddText(sksbbh);
	DBG_PRINT(("sksbbh : %s", sksbbh.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "bspbh");
	construct->AddText(bspbh);
	DBG_PRINT(("bspbh : %s", bspbh.c_str()));

	construct->AddNode(construct->m_parentElement[2], "qtxx");
	construct->AddText(qtxx);
	DBG_PRINT(("qtxx : %s", qtxx.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);
	DBG_PRINT(("returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);
	DBG_PRINT(("returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
}


INT32 CSksbbhcx::Execute()
{
	string sksbbh("");
	string bspbh("");
	string qtxx("");

	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	string strErr("");
	string tmpStr("");

	XmlParse(m_pXmlParse);
	CheckYWXmlPara(retInfo.m_retMsg);

	retcode = CJSKManageProc::SKSBBH_Proc(sksbbh, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}
	CJSKManageProc::BSPBH_Proc(bspbh, tmpStr);

	XmlBuild(m_pXmlConstruct, sksbbh, bspbh, qtxx, &retInfo);

	return SUCCESS;
}


