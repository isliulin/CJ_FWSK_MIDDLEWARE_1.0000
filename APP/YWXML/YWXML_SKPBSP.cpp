/*! \file    YWXML_SKPBSP.cpp
   \brief    款机调用的中间件接口 业务: 税控设备报税盘组合操作
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "YWXML_SKPBSP.h"
#include "JSKDeclareProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CSkpBsp::CSkpBsp(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CSkpBsp::~CSkpBsp()
{

}


INT32 CSkpBsp::XmlParse(XMLParse *parse, UINT8 &Czlx, string &Hzxx, string &Qtxx)
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
	
	parse->LocateNodeByName(parse->m_parentElement[2], "sksbkl");
	m_ywxml_gy.m_sksbkl = parse->GetText();	
	DBG_PRINT(("m_ywxml_gy.sksbkl == %s", m_ywxml_gy.m_sksbkl.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "bspbh");
	m_ywxml_gy.m_bspbh = parse->GetText();	
	DBG_PRINT(("m_ywxml_gy.m_bspbh == %s", parse->GetText().c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "bspkl");
	m_ywxml_gy.m_bspkl = parse->GetText();	
	DBG_PRINT(("m_ywxml_gy.m_bspkl == %s", m_ywxml_gy.m_bspkl.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();	
	DBG_PRINT(("m_ywxml_gy.fplxdm == %s", m_ywxml_gy.m_fplxdm.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "czlx");
	Czlx = (UINT8)atoi(parse->GetText().c_str());	
	DBG_PRINT(("m_ywxml_gy.fplxdm == %s", Czlx));	

	parse->LocateNodeByName(parse->m_parentElement[2], "hzxx");
	Hzxx = parse->GetText();	
	DBG_PRINT(("Hzxx == %s", Hzxx.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "qtxx");
//	Qtxx = parse->GetText().c_str();	
	Qtxx = "";	//仅数据抄报有效，用于抄报发票领用存信息（此字段目前不用，给空值。）
	DBG_PRINT(("Qtxx == %s", parse->GetText().c_str()));	

	return SUCCESS;
}

INT32 CSkpBsp::XmlBuild(XMLConstruct *construct, Return_Info *retInfo)
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
	DBG_PRINT(("retInfo->m_retCode : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;

}


INT32 CSkpBsp::Execute()
{
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	UINT8 czlx = 0;
	string strHzxx("");
	string strQtxx("");

	XmlParse(m_pXmlParse, czlx, strHzxx, strQtxx);
	CheckYWXmlPara(retInfo.m_retMsg);

	retcode = CJSKDeclareProc::SKPBSP_Proc(m_ywxml_gy.m_fplxdm, czlx, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}
	
	XmlBuild(m_pXmlConstruct, &retInfo);

	return SUCCESS;
}





