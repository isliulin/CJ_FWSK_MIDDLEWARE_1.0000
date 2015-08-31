/*! \file    YWXML_JKHC.cpp
   \brief    款机调用的中间件接口 业务2.18监控回传
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "YWXML_JKHC.h"
#include "JSKDeclareProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CJkhc::CJkhc(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CJkhc::~CJkhc()
{

}

INT32 CJkhc::XmlParse(XMLParse *parse, string &strFpjkmw, string &strSzjkmw)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh= parse->GetText();		//税控收款机别号
	DBG_PRINT(("YWXML_JKHC: jqbh = %s", m_ywxml_gy.m_jqbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "nsrsbh");
	m_ywxml_gy.m_nsrsbh= parse->GetText();		//纳税人识别号
	DBG_PRINT(("YWXML_JKHC: nsrsbh = %s", m_ywxml_gy.m_nsrsbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "sksbbh");
	m_ywxml_gy.m_sksbbh= parse->GetText();		//税控设备编号
	DBG_PRINT(("YWXML_JKHC: sksbbh = %s", m_ywxml_gy.m_sksbbh.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "sksbkl");
	m_ywxml_gy.m_sksbkl= parse->GetText();		//税控设备口令
	DBG_PRINT(("YWXML_JKHC: sksbkl = %s", m_ywxml_gy.m_sksbkl.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();		//发票类型代码
	DBG_PRINT(("YWXML_JKHC: fplxdm = %s", m_ywxml_gy.m_fplxdm.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fpjkmw");
	strFpjkmw = parse->GetText();		//发票监控密文
	DBG_PRINT(("YWXML_JKHC: fpjkmw = %s",strFpjkmw.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "szjkmw");
	strSzjkmw = parse->GetText();		//时钟监控密文
	DBG_PRINT(("YWXML_JKHC: szjkmw = %s", strSzjkmw.c_str()));
	
	return SUCCESS;
}

INT32 CJkhc::XmlBuild(XMLConstruct *construct, Return_Info *retInfo)
{
	
	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;
	
	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);	//返回代码
	DBG_PRINT(("YWXML_JKHC: returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);		//返回信息
	DBG_PRINT(("YWXML_JKHC: returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
}


INT32 CJkhc::Execute()
{
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	string fpjkmw("");	//发票监控密文
	string szjkmw("");	//时钟监控密文
	Return_Info retInfo;	//	返回信息类对象

	XmlParse(m_pXmlParse, fpjkmw, szjkmw);	//调用XML解析函数
	CheckYWXmlPara(retInfo.m_retMsg);

	retcode = CJSKDeclareProc::JKHC_Proc(m_ywxml_gy.m_fplxdm, fpjkmw, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}
	
	XmlBuild(m_pXmlConstruct, &retInfo);	//调用XML组装函数

	return SUCCESS;
}


































