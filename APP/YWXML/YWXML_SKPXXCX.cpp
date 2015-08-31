 /*! \file    YWXML_SKPXXCX.cpp
   \brief    款机调用的中间件接口 业务2.2.税控设备信息查询
   \author   YY
   \version  1.0
   \date     2015
 */

#include "YWXML_SKPXXCX.h"
#include "JSKManageProc.h"
#include "TDateTime.h"
#include "CUserInfo.h"
#include "CInvKind.h"
#include "GlobalNetArg.h"
#include "CGlobalArgLib.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CSkpxxcx::CSkpxxcx(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CSkpxxcx::~CSkpxxcx()
{

}


INT32 CSkpxxcx::XmlParse(XMLParse *parse)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh = parse->GetText();		//税控收款机编号
	DBG_PRINT(("m_ywxml_gy.m_jqbh == %s", m_ywxml_gy.m_jqbh.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "sksbkl");
	m_ywxml_gy.m_sksbkl = parse->GetText();		//税控设备口令
	DBG_PRINT(("m_sksbkl == %s", m_ywxml_gy.m_sksbkl.c_str()));			
		
	return SUCCESS;
}

INT32 CSkpxxcx::XmlBuild(XMLConstruct *construct, CUserInfo *pUserinfo, string strCurTime, Return_Info *retInfo)
{
	INT8 tmpBuff[128];
	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;
	
	construct->AddNode(construct->m_parentElement[2], "sksbbh");
	construct->AddText(pUserinfo->m_Jspsbh);
	DBG_PRINT(("pUserinfo->sksbbh : %s", pUserinfo->m_Jspsbh.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "nsrsbh");
	construct->AddText(pUserinfo->m_Nsrsbh);
	DBG_PRINT(("pUserinfo->nsrsbh : %s", pUserinfo->m_Nsrsbh.c_str()));

	construct->AddNode(construct->m_parentElement[2], "nsrmc");
	construct->AddText(pUserinfo->m_Nsrmc);
	DBG_PRINT(("pUserinfo->nsrmc : %s", pUserinfo->m_Nsrmc.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "swjgdm");
	construct->AddText(pUserinfo->m_Swjgdm);
	DBG_PRINT(("pUserinfo->swjgdm : %s", pUserinfo->m_Swjgdm.c_str()));

	construct->AddNode(construct->m_parentElement[2], "swjgmc");
	construct->AddText(pUserinfo->m_Swjgmc);
	DBG_PRINT(("pUserinfo->swjgmc : %s", pUserinfo->m_Swjgmc.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "fplxdm");
	construct->AddText(pUserinfo->m_fplxdm);	
	DBG_PRINT(("pUserinfo->fplxdm : %s", pUserinfo->m_fplxdm.c_str()));

	construct->AddNode(construct->m_parentElement[2], "dqsz");//当前时钟
	construct->AddText(strCurTime);
	DBG_PRINT(("strCurTime : %s", strCurTime.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "qysj");
	construct->AddText(pUserinfo->m_qysj);
	DBG_PRINT(("pUserinfo->qysj : %s", pUserinfo->m_qysj.c_str()));

	construct->AddNode(construct->m_parentElement[2], "bbh");
	construct->AddText(pUserinfo->m_bbh);
	DBG_PRINT(("pUserinfo->bbh : %s", pUserinfo->m_bbh.c_str()));

	construct->AddNode(construct->m_parentElement[2], "kpjh");
	memset(tmpBuff, 0, sizeof(tmpBuff));
	sprintf(tmpBuff, "%u", pUserinfo->m_Kpjhm);
	construct->AddText(tmpBuff);
	DBG_PRINT(("pUserinfo->kpjh : %s", tmpBuff));

	construct->AddNode(construct->m_parentElement[2], "qylx");
	memset(tmpBuff, 0, sizeof(tmpBuff));
	sprintf(tmpBuff, "%u", pUserinfo->m_Hylx);
	construct->AddText(tmpBuff);
	DBG_PRINT(("pUserinfo->m_Hylx : %s", tmpBuff));

	construct->AddNode(construct->m_parentElement[2], "blxx");
	construct->AddText(pUserinfo->m_blxx);
	DBG_PRINT(("pUserinfo->blxx : %s", pUserinfo->m_blxx.c_str()));

	construct->AddNode(construct->m_parentElement[2], "qtkzxx");//其它扩展信息
	construct->AddText(pUserinfo->m_qtkzxx);
	DBG_PRINT(("pUserinfo->qtkzxx : %s", pUserinfo->m_qtkzxx.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);
	DBG_PRINT(("returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);
	DBG_PRINT(("returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;

}


INT32 CSkpxxcx::Execute()
{
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	string strCurTime;
	memset(tmpbuf, 0, sizeof(tmpbuf));

	XmlParse(m_pXmlParse);
	CheckYWXmlPara(retInfo.m_retMsg);
	
	retcode = CJSKManageProc::SKPXXCX_Proc(g_globalArgLib->m_corpInfo, strCurTime, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}

#if MODE_TYPE_JSP == 1
	memset(tmpbuf, 0, sizeof(tmpbuf));
	sprintf(tmpbuf, "%u", g_globalArgLib->m_corpInfo->m_Kpjhm);
	g_gNetArg->SetBaseInfo(g_globalArgLib->m_corpInfo->m_Nsrsbh, tmpbuf, g_globalArgLib->m_corpInfo->m_Jspsbh);
#endif

	XmlBuild(m_pXmlConstruct, g_globalArgLib->m_corpInfo, strCurTime, &retInfo);

	return SUCCESS;
}





