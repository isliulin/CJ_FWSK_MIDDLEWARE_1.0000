/*! \file    YWXML_BSPXXCX.cpp
   \brief    款机调用的中间件接口 业务: 报税盘信息查询
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "YWXML_BSPXXCX.h"
#include "JSKManageProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CBspxxcx::CBspxxcx(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CBspxxcx::~CBspxxcx()
{

}


INT32 CBspxxcx::XmlParse(XMLParse *parse)
{

	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh = parse->GetText();		//税控收款机编号
	DBG_PRINT(("m_ywxml_gy.m_jqbh == %s", m_ywxml_gy.m_jqbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "bspkl");
	m_ywxml_gy.m_bspkl = parse->GetText();		//报税盘口令
	DBG_PRINT(("PROTOCOLINFO--bspkl == %s", m_ywxml_gy.m_bspkl.c_str()));	

	return SUCCESS;
}

INT32 CBspxxcx::XmlBuild(XMLConstruct *construct, CUserInfo *pUserinfo, string dqsz, Return_Info *retInfo)
{
	INT8 tmpbuff[64];
	
	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;
	
	construct->AddNode(construct->m_parentElement[2], "bspbh");
	construct->AddText(pUserinfo->m_bspbh);
	DBG_PRINT(("pUserinfo->m_bspbh : %s", pUserinfo->m_bspbh.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "nsrsbh");
	construct->AddText(pUserinfo->m_Nsrsbh);
	DBG_PRINT(("pUserinfo->m_Nsrsbh : %s", pUserinfo->m_Nsrsbh.c_str()));

	construct->AddNode(construct->m_parentElement[2], "nsrmc");
	construct->AddText(pUserinfo->m_Nsrmc);
	DBG_PRINT(("pUserinfo->m_Nsrmc : %s", pUserinfo->m_Nsrmc.c_str()));

	construct->AddNode(construct->m_parentElement[2], "swjgdm");
	construct->AddText(pUserinfo->m_Swjgdm);
	DBG_PRINT(("pUserinfo->m_Swjgdm : %s", pUserinfo->m_Swjgdm.c_str()));

	construct->AddNode(construct->m_parentElement[2], "swjgmc");
	construct->AddText(pUserinfo->m_Swjgmc);
	DBG_PRINT(("pUserinfo->m_Swjgmc : %s", pUserinfo->m_Swjgmc.c_str()));

	construct->AddNode(construct->m_parentElement[2], "dqsz");
	construct->AddText(dqsz);
	DBG_PRINT(("dqsz : %s", dqsz.c_str()));

	construct->AddNode(construct->m_parentElement[2], "qysj");
	construct->AddText(pUserinfo->m_qysj);
	DBG_PRINT(("pUserinfo->m_qysj : %s", pUserinfo->m_qysj.c_str()));

	construct->AddNode(construct->m_parentElement[2], "ffbz");
	construct->AddText(pUserinfo->m_ffbz);
	DBG_PRINT(("pUserinfo->m_ffbz : %s", pUserinfo->m_ffbz.c_str()));

	construct->AddNode(construct->m_parentElement[2], "bbh");
	construct->AddText(pUserinfo->m_bbh);
	DBG_PRINT(("pUserinfo->m_bbh : %s", pUserinfo->m_bbh.c_str()));

	construct->AddNode(construct->m_parentElement[2], "kpjh");
	memset(tmpbuff, 0, sizeof(tmpbuff));
	sprintf(tmpbuff, "%u", pUserinfo->m_Kpjhm);
	construct->AddText(tmpbuff);
	DBG_PRINT(("pUserinfo->m_Kpjhm : %s", tmpbuff));

	construct->AddNode(construct->m_parentElement[2], "qylx");
	memset(tmpbuff, 0, sizeof(tmpbuff));
	sprintf(tmpbuff, "%u", pUserinfo->m_Nsrxz);
	construct->AddText(tmpbuff);
	DBG_PRINT(("pUserinfo->m_Nsrxz : %s", tmpbuff));

	construct->AddNode(construct->m_parentElement[2], "blxx");
	construct->AddText(pUserinfo->m_blxx);
	DBG_PRINT(("pUserinfo->m_blxx : %s", pUserinfo->m_blxx.c_str()));

	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);
	DBG_PRINT(("retcode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);
	DBG_PRINT(("retmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;

}


INT32 CBspxxcx::Execute()
{
	CUserInfo userInfo;
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	string curTime("");
	
	XmlParse(m_pXmlParse);
	CheckYWXmlPara(retInfo.m_retMsg);
	
	retcode = CJSKManageProc::BSPXXCX_Proc(&userInfo, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}
	
	XmlBuild(m_pXmlConstruct, &userInfo, curTime, &retInfo);
	
	return SUCCESS;
}





