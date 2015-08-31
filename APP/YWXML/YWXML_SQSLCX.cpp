/*! \file    YWXML_SQSLCX.cpp
   \brief    款机调用的中间件接口 业务: 授权税率查询
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "YWXML_SQSLCX.h"
#include "JSKManageProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CSqslcx::CSqslcx(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CSqslcx::~CSqslcx()
{

}


INT32 CSqslcx::XmlParse(XMLParse *parse)
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

INT32 CSqslcx::XmlBuild(XMLConstruct *construct, CTax *pTax, UINT8 slNum, Return_Info *retInfo)
{
	INT8 buf[64];
	UINT8 Num = 0;
	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;
	
	construct->AddNode(construct->m_parentElement[2], "fplxdm");
	construct->AddText(m_ywxml_gy.m_fplxdm);
	DBG_PRINT(("m_ywxml_gy.m_fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));

	construct->AddNode(construct->m_parentElement[2], "sqslxx");
	construct->m_parentElement[3] = construct->m_NewElement;
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%d", slNum);
	DBG_PRINT(("sqslxx = %s", buf));
	construct->AddAttr("count", buf);	
	
	for (Num=1; Num<=slNum; Num++, pTax++)
	{
		construct->AddNode(construct->m_parentElement[3], "group");
		construct->m_parentElement[4] = construct->m_NewElement;
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "%d", Num);
		DBG_PRINT(("group_xh = %s", buf));
		construct->AddAttr("xh", buf);

		construct->AddNode(construct->m_parentElement[4], "sl");
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "%.2f", ((double)pTax->m_sl)/100.0);
		construct->AddText(buf);
		DBG_PRINT(("pTax->m_sl = %s", buf));

	}
	
	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);
	DBG_PRINT(("sksbbh : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);
	DBG_PRINT(("retInfo->m_retMsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;

}


INT32 CSqslcx::Execute()
{
	CTax tax[MAX_TAX_NUM];
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	UINT8 taxNum = 0;
	
	XmlParse(m_pXmlParse);
	CheckYWXmlPara(retInfo.m_retMsg);
	
	retcode = CJSKManageProc::SQSLCX_Proc(tax, taxNum, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
		taxNum = 0;
	}
	
	XmlBuild(m_pXmlConstruct, tax, taxNum, &retInfo);
	
	return SUCCESS;
}





