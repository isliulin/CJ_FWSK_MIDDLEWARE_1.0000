/*! \file     YWXML_GPXXCX.cpp
   \brief    款机调用的中间件接口 业务: 购票信息查询
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "YWXML_GPXXCX.h"
#include "JSKMakeInvoice.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CGpxxcx::CGpxxcx(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CGpxxcx::~CGpxxcx()
{

}


INT32 CGpxxcx::XmlParse(XMLParse *parse)
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
	
	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();	
	DBG_PRINT(("m_ywxml_gy.fplxdm == %s", m_ywxml_gy.m_fplxdm.c_str()));

	return SUCCESS;
}

INT32 CGpxxcx::XmlBuild(XMLConstruct *construct, CInvVol *pInvVol, Return_Info *retInfo)
{
	INT8 Buf[64];
	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;
	
	construct->AddNode(construct->m_parentElement[2], "fplxdm");
	construct->AddText(pInvVol->m_fplxdm);
// 	memset(Buf, 0, sizeof(Buf));
// 	sprintf(Buf, "%u", pInvVol->m_invtype);
// 	construct->AddText(Buf);
// 	DBG_PRINT(("pInvVol->m_invtype : %s", Buf));
	
	construct->AddNode(construct->m_parentElement[2], "dqfpdm");
	construct->AddText(pInvVol->m_code);
	DBG_PRINT(("pInvVol->m_code : %s", pInvVol->m_code.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "dqfphm");
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%08u", pInvVol->m_curInvNo);
	construct->AddText(Buf);
	DBG_PRINT(("pInvVol->m_curInvNo : %s", Buf));
	
	construct->AddNode(construct->m_parentElement[2], "zsyfs");	//总剩余份数
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%u", pInvVol->m_remain);
	construct->AddText(Buf);
	DBG_PRINT(("pInvVol->m_remain : %s", Buf));

	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);
	DBG_PRINT(("retInfo->m_retCode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);
	DBG_PRINT(("retInfo->m_retMsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;

}


INT32 CGpxxcx::Execute()
{
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	CInvVol invVol;
	
	XmlParse(m_pXmlParse);
	CheckYWXmlPara(retInfo.m_retMsg);
	
	retcode = CJSKMakeInvoice::GPXXCX_Proc(&invVol, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}
	
	XmlBuild(m_pXmlConstruct, &invVol, &retInfo);
	
	return SUCCESS;
}





