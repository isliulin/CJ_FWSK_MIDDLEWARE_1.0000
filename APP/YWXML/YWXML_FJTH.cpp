/*! \file    YWXML_FJTH.h
   \brief    款机调用的中间件接口 业务2.24 分机退回
   \author   zfj
   \version  1.0
   \date     2015 
*/

#include "YWXML_FJTH.h"
#include "JSKInvManageProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CYWXMLFjth::CYWXMLFjth(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CYWXMLFjth::~CYWXMLFjth()
{

}

INT32 CYWXMLFjth::XmlParse(XMLParse *parse, UINT8 &jzlx)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh= parse->GetText();		//税控收款机别号
	DBG_PRINT(("YWXML_FJTH: jqbh = %s", m_ywxml_gy.m_jqbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "nsrsbh");
	m_ywxml_gy.m_nsrsbh= parse->GetText();		//纳税人识别号
	DBG_PRINT(("YWXML_FJTH: nsrsbh == %s", m_ywxml_gy.m_nsrsbh.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "jzlx");
	jzlx = atoi(parse->GetText().c_str());		//介质类型
	DBG_PRINT(("YWXML_FJTH: jzlx == %u", jzlx));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "bspbh");
	m_ywxml_gy.m_bspbh = parse->GetText();		//报税盘编号
	DBG_PRINT(("YWXML_FJTH: bspbh == %s", m_ywxml_gy.m_bspbh.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "bspkl");
	m_ywxml_gy.m_bspkl = parse->GetText();		//报税盘口令
	DBG_PRINT(("YWXML_FJTH: bspkl == %s", m_ywxml_gy.m_bspkl.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "sksbbh");
	m_ywxml_gy.m_sksbbh= parse->GetText();		//税控设备编号
	DBG_PRINT(("YWXML_FJTH: sksbbh == %s", m_ywxml_gy.m_sksbbh.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "sksbkl");
	m_ywxml_gy.m_sksbkl= parse->GetText();		//税控设备口令
	DBG_PRINT(("YWXML_FJTH: sksbkl == %s", m_ywxml_gy.m_sksbkl.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();		//发票类型代码
	DBG_PRINT(("YWXML_FJTH: fplxdm == %s", m_ywxml_gy.m_fplxdm.c_str()));

	return SUCCESS;
}

INT32 CYWXMLFjth::XmlBuild(XMLConstruct *construct, Return_Info *retInfo)
{
	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	//添加returncode节点
	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);
	DBG_PRINT(("YWXML_FJTH: returncode : %s", retInfo->m_retCode.c_str()));

	//添加returnmsg节点
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);
	DBG_PRINT(("YWXML_FJTH: returnmsg : %s", retInfo->m_retMsg.c_str()));

	return SUCCESS;
}


INT32 CYWXMLFjth::Execute()
{
	UINT8 jzlx=2;		//介质类型
	Return_Info retInfo;//返回信息
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	
	XmlParse(m_pXmlParse, jzlx);	//调用XML解析函数
	CheckYWXmlPara(retInfo.m_retMsg);
	
	retcode = CJSKInvManageProc::FJTH_Proc(jzlx, m_ywxml_gy.m_fplxdm, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}
	
	XmlBuild(m_pXmlConstruct, &retInfo);	//调用XML组装函数

	return SUCCESS;
}





