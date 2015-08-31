 /*! \file    YWXML_FPGX.cpp
   \brief    款机调用的中间件接口 业务2.22.发票更新
   \author   YY
   \version  1.0
   \date     2015
 */

#include "YWXML_FPGX.h"
#include "JSKMakeInvoice.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CFpgx::CFpgx(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CFpgx::~CFpgx()
{

}

INT32 CFpgx::XmlParse(XMLParse *parse, string &strScqrbw)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh= parse->GetText();		//税控收款机别号
	DBG_PRINT(("YWXML_FPGX: jqbh = %s", m_ywxml_gy.m_jqbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "nsrsbh");
	m_ywxml_gy.m_nsrsbh= parse->GetText();		//纳税人识别号
	DBG_PRINT(("YWXML_FPGX: nsrsbh == %s", m_ywxml_gy.m_nsrsbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "sksbbh");
	m_ywxml_gy.m_sksbbh= parse->GetText();		//税控设备编号
	DBG_PRINT(("YWXML_FPGX: sksbbh == %s", m_ywxml_gy.m_sksbbh.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "sksbkl");
	m_ywxml_gy.m_sksbkl= parse->GetText();		//税控设备口令
	DBG_PRINT(("YWXML_FPGX: sksbkl == %s", m_ywxml_gy.m_sksbkl.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();		//发票类型代码
	DBG_PRINT(("YWXML_FPGX: fplxdm == %s", m_ywxml_gy.m_fplxdm.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "scqrbw");
	strScqrbw = parse->GetText();		//上传成功确认报文
	DBG_PRINT(("YWXML_FPGX: scqrbw == %s", strScqrbw.c_str()));
}

INT32 CFpgx::XmlBuild(XMLConstruct *construct, Return_Info *retInfo)
{
	
	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);
	DBG_PRINT(("YWXML_FPGX: returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);
	DBG_PRINT(("YWXML_FPGX: returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
}


INT32 CFpgx::Execute()
{
	string scqrbw("");
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];

	XmlParse(m_pXmlParse, scqrbw);
	CheckYWXmlPara(retInfo.m_retMsg);

	retcode = CJSKMakeInvoice::FPGX_Proc(scqrbw, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}

	XmlBuild(m_pXmlConstruct, &retInfo);

	return SUCCESS;
}


