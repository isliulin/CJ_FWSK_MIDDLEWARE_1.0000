/*! \file     YWXML_FPZF.cpp
   \brief    款机调用的中间件接口 业务: 发票作废
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "YWXML_FPZF.h"
#include "JSKMakeInvoice.h"
#include "JSKInvManageProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CFpzf::CFpzf(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CFpzf::~CFpzf()
{

}


INT32 CFpzf::XmlParse(XMLParse *parse, CInvHead *pInvInfo, UINT8 &zflx)
{
	UINT8 i = 0;

	//添加到发票明细

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
	pInvInfo->m_xfsh = m_ywxml_gy.m_nsrsbh;
	DBG_PRINT(("m_ywxml_gy.sksbbh == %s", m_ywxml_gy.m_sksbbh.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "sksbkl");
	m_ywxml_gy.m_sksbkl = parse->GetText();	
	DBG_PRINT(("m_ywxml_gy.sksbkl == %s", m_ywxml_gy.m_sksbkl.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();	
	pInvInfo->m_fplxdm = m_ywxml_gy.m_fplxdm;
	DBG_PRINT(("m_ywxml_gy.fplxdm == %s", m_ywxml_gy.m_fplxdm.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "zskl");
	pInvInfo->m_zskl = parse->GetText();		//证书口令
	DBG_PRINT(("pInvInfo->m_zskl == %s", pInvInfo->m_zskl.c_str()));
	

	parse->LocateNodeByName(parse->m_parentElement[2], "zflx");
//	pInvInfo->m_kplx = (UINT8)atoi(parse->GetText().c_str());	
	zflx = (UINT8)atoi(parse->GetText().c_str());
	DBG_PRINT(("pInvInfo->zflx == %u", zflx));

	parse->LocateNodeByName(parse->m_parentElement[2], "fpdm");
	pInvInfo->m_fpdm = parse->GetText();	
	DBG_PRINT(("pInvInfo->m_fpdm == %s", pInvInfo->m_fpdm.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fphm");
	pInvInfo->m_fphm = atoi(parse->GetText().c_str());	
	DBG_PRINT(("pInvInfo->m_fphm == %u", pInvInfo->m_fphm));

	parse->LocateNodeByName(parse->m_parentElement[2], "zfr");	//作废人
	pInvInfo->m_sky = parse->GetText();	
	DBG_PRINT(("pInvInfo->m_sky == %s", pInvInfo->m_sky.c_str()));

	return SUCCESS;
}

INT32 CFpzf::XmlBuild(XMLConstruct *construct, CInvHead *pInvInfo, Return_Info *retInfo)
{
	INT8 Buf[64];
	
	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;
	
	construct->AddNode(construct->m_parentElement[2], "fplxdm");
	construct->AddText(m_ywxml_gy.m_fplxdm);
	
	construct->AddNode(construct->m_parentElement[2], "fpdm");
	construct->AddText(pInvInfo->m_fpdm);
	DBG_PRINT(("pInvInfo->m_fpdm : %s", pInvInfo->m_fpdm.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "fphm");
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%08u", pInvInfo->m_fphm);
	construct->AddText(Buf);
	DBG_PRINT(("pInvInfo->m_fphm : %s", Buf));
	
	construct->AddNode(construct->m_parentElement[2], "zfrq");
// 	memset(Buf, 0, sizeof(Buf));
// 	sprintf(Buf, "%08u%06u", pInvInfo->m_kprq, pInvInfo->m_kpsj);
// 	construct->AddText(Buf);
// 	DBG_PRINT(("pInvInfo->m_kprq + pInvInfo->m_kpsj : %s", Buf));
	construct->AddText(pInvInfo->m_zfsj);
 	DBG_PRINT(("pInvInfo->m_zfsj : %s", pInvInfo->m_zfsj.c_str()));

	construct->AddNode(construct->m_parentElement[2], "qmz");	
	construct->AddText(pInvInfo->m_casign);
	DBG_PRINT(("pInvInfo->m_casign : %s", pInvInfo->m_casign.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);
	DBG_PRINT(("retInfo->m_retCode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);
	DBG_PRINT(("retInfo->m_retMsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;

}


INT32 CFpzf::Execute()
{
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	CInvHead invHead;
	UINT8 zflx = 0;
	
	XmlParse(m_pXmlParse, &invHead, zflx);
	CheckYWXmlPara(retInfo.m_retMsg);

	invHead.m_jqbh = m_ywxml_gy.m_jqbh;
	invHead.m_xfsh = m_ywxml_gy.m_nsrsbh;
	invHead.m_sksbbh = m_ywxml_gy.m_sksbbh;

	retcode = CJSKMakeInvoice::FPZF_Proc(&invHead, zflx, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}
	
	XmlBuild(m_pXmlConstruct, &invHead, &retInfo);
	
	return SUCCESS;
}





