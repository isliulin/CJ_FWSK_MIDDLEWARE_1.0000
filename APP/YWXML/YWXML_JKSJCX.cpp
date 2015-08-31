/*! \file    YWXML_JKSJCX.cpp
   \brief    款机调用的中间件接口 业务: 监控数据查询
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "YWXML_JKSJCX.h"
#include "CGlobalArgLib.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CJksjcx::CJksjcx(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CJksjcx::~CJksjcx()
{

}

INT32 CJksjcx::XmlParse(XMLParse *parse)
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

INT32 CJksjcx::XmlBuild(XMLConstruct *construct, CInvKind *pInvKind, Return_Info *retInfo)
{
	INT8 Buf[64];

	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[2], "fplxdm");
	construct->AddText(pInvKind->m_fplxdm);
	DBG_PRINT(("pInvKind->m_fplxdm : %s", pInvKind->m_fplxdm.c_str()));
	
	//开票截至时间
	construct->AddNode(construct->m_parentElement[2], "kpjzsj");
	construct->AddText("");
// 	DBG_PRINT(("retInfo->m_retCode : %s", retInfo->m_retCode.c_str()));

	//数据报送起始日期
	construct->AddNode(construct->m_parentElement[2], "bsqsrq");
	construct->AddText(pInvKind->m_bsqsrq);
	DBG_PRINT(("pInvKind->m_bsqsrq : %s", pInvKind->m_bsqsrq.c_str()));

	//数据报送终止日期
	construct->AddNode(construct->m_parentElement[2], "bszzrq");
	construct->AddText(pInvKind->m_bszzrq);
	DBG_PRINT(("pInvKind->m_bszzrq : %s", pInvKind->m_bszzrq.c_str()));

	construct->AddNode(construct->m_parentElement[2], "dzkpxe");
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%.2lf", (double)(pInvKind->m_maxSign/100.0));
	construct->AddText(Buf);
	DBG_PRINT(("pInvKind->m_maxSign: %s", Buf));

	//最新报税日期
	construct->AddNode(construct->m_parentElement[2], "zxbsrq");
	construct->AddText(""); //待赋值
	// DBG_PRINT(("retInfo->m_retCode : %s", retInfo->m_retCode.c_str()));

	//剩余容量
	construct->AddNode(construct->m_parentElement[2], "syrl");
	construct->AddText("");

	//上传截止日期
	construct->AddNode(construct->m_parentElement[2], "scjzrq");
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%u", pInvKind->m_Lxssr);
	construct->AddText(Buf);
	DBG_PRINT(("pInvKind->m_Lxssr: %s", Buf));
	
	construct->AddNode(construct->m_parentElement[2], "lxkpsc");
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%u", pInvKind->m_Lxkjsj);
	construct->AddText(Buf);
	DBG_PRINT(("pInvKind->m_Lxkjsj: %s", Buf));

	construct->AddNode(construct->m_parentElement[2], "lxzsljje");
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%.2lf", (double)(pInvKind->m_maxSum/100.0));
	construct->AddText(Buf);
	DBG_PRINT(("pInvKind->m_maxSum: %s", Buf));

	//离线扩展信息
	construct->AddNode(construct->m_parentElement[2], "lxkzxx");
	construct->AddText("");
	
	//自定义信息
	construct->AddNode(construct->m_parentElement[2], "zdyxx");
	construct->AddText("");

	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);
	DBG_PRINT(("retInfo->m_retCode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);
	DBG_PRINT(("retInfo->m_retMsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
	
}


INT32 CJksjcx::Execute()
{
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];

	XmlParse(m_pXmlParse);
	CheckYWXmlPara(retInfo.m_retMsg);

	g_globalArgLib->m_invKind->m_fplxdm = m_ywxml_gy.m_fplxdm;
	retcode = CJSKManageProc::JKSJCX_Proc(g_globalArgLib->m_invKind, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}

	DBG_PRINT(("m_maxSign = %lld", g_globalArgLib->m_invKind->m_maxSign));
	DBG_PRINT(("m_Lxkjsj = %u", g_globalArgLib->m_invKind->m_Lxkjsj));
	DBG_PRINT(("m_Lxssr = %u", g_globalArgLib->m_invKind->m_Lxssr));
	DBG_PRINT(("m_maxSum = %lld", g_globalArgLib->m_invKind->m_maxSum));
	DBG_PRINT(("m_bsqsrq = %s", g_globalArgLib->m_invKind->m_bsqsrq.c_str()));
	DBG_PRINT(("m_bszzrq = %s", g_globalArgLib->m_invKind->m_bszzrq.c_str()));

	XmlBuild(m_pXmlConstruct, g_globalArgLib->m_invKind, &retInfo);

	return SUCCESS;
}





