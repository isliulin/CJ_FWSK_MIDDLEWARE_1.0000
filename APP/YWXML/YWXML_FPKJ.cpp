/*! \file     YWXML_GPXXCX.cpp
   \brief    款机调用的中间件接口 业务: 发票开具
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "YWXML_FPKJ.h"
#include "JSKMakeInvoice.h"
#include "JSKInvManageProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CFpkj::CFpkj(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CFpkj::~CFpkj()
{

}


INT32 CFpkj::XmlParse(XMLParse *parse, CInvHead *pInvInfo)
{

	UINT8 i = 0;

	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh = parse->GetText();		//税控收款机编号
	DBG_PRINT(("m_ywxml_gy.m_jqbh == %s", m_ywxml_gy.m_jqbh.c_str()));	

	pInvInfo->m_jqbh = m_ywxml_gy.m_jqbh;
	DBG_PRINT(("pInvInfo->m_jqbh == %s", pInvInfo->m_jqbh.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "zskl");
	pInvInfo->m_zskl = parse->GetText();		//证书口令
	DBG_PRINT(("pInvInfo->m_zskl == %s", pInvInfo->m_zskl.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "xhdwdm");
	m_ywxml_gy.m_nsrsbh = parse->GetText();	
	DBG_PRINT(("m_ywxml_gy.nsrsbh == %s", m_ywxml_gy.m_nsrsbh.c_str()));
	pInvInfo->m_xfsh = parse->GetText();
	DBG_PRINT(("pInvInfo->m_xfsh == %s", pInvInfo->m_xfsh.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "xhdwmc");
	pInvInfo->m_xfmc = parse->GetText();
	DBG_PRINT(("pInvInfo->m_xfmc == %s", pInvInfo->m_xfmc.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "sksbbh");
	m_ywxml_gy.m_sksbbh = parse->GetText();	
	DBG_PRINT(("m_ywxml_gy.sksbbh == %s", m_ywxml_gy.m_sksbbh.c_str()));	
	pInvInfo->m_sksbbh = m_ywxml_gy.m_sksbbh;
	DBG_PRINT(("pInvInfo->m_sksbbh == %s", pInvInfo->m_sksbbh.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "sksbkl");
	m_ywxml_gy.m_sksbkl = parse->GetText();	
	DBG_PRINT(("m_ywxml_gy.sksbkl == %s", m_ywxml_gy.m_sksbkl.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();	
	pInvInfo->m_fplxdm = m_ywxml_gy.m_fplxdm;
	DBG_PRINT(("m_ywxml_gy.fplxdm == %s", m_ywxml_gy.m_fplxdm.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "kplx");
	pInvInfo->m_kplx = (UINT8)atoi(parse->GetText().c_str());	
	DBG_PRINT(("pInvInfo->m_kplx == %u", pInvInfo->m_kplx));

// 	parse->LocateNodeByName(parse->m_parentElement[2], "hyfl");
// 	pInvInfo->m_hyfl = parse->GetText();	
// 	DBG_PRINT(("hyfl== %s", pInvInfo->m_hyfl.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "ghdwdm");
	pInvInfo->m_payerCode = parse->GetText();
	CJSKMakeInvoice::FilterSpace(pInvInfo->m_payerCode);
	if(pInvInfo->m_payerCode == "")
		pInvInfo->m_payerCode = "000000000000000";
	DBG_PRINT(("pInvInfo->m_payerCode == %s", pInvInfo->m_payerCode.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "ghdwmc");
	pInvInfo->m_fkdw = parse->GetText();
	CJSKMakeInvoice::FilterSpace(pInvInfo->m_fkdw);
	DBG_PRINT(("pInvInfo->m_fkdw == %s", pInvInfo->m_fkdw.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "sfxm");
	parse->m_parentElement[3] = parse->m_Child;
	pInvInfo->m_sphsl = atoi(parse->GetAttr("count").c_str());	//解析XML后得到商品明细行数
	DBG_PRINT(("pInvInfo->m_sphsl == %u", pInvInfo->m_sphsl));
	
	CInvDet* pInvDet = NULL;

	for (i=0; i<pInvInfo->m_sphsl; i++)
	{
		pInvDet = pInvDet->GetNewInvDet();	//从静态数组获取一个可用的CInvDet对象
		DBG_ASSERT_EXIT((pInvDet != NULL), (" pInvDet == NULL!"));

		pInvDet->m_sphxh = i+1;

		//得到group节点
		parse->LocateNodeByName(parse->m_parentElement[3], "group", i);
		parse->m_parentElement[4] = parse->m_Child;

		parse->LocateNodeByName(parse->m_parentElement[4], "xm");
		pInvDet->m_spmc = parse->GetText();	
		CJSKMakeInvoice::FilterSpace(pInvDet->m_spmc);
		DBG_PRINT(("pInvDet->m_spmc == %s", pInvDet->m_spmc.c_str()));

		parse->LocateNodeByName(parse->m_parentElement[4], "dj");
		pInvDet->m_dj = atof(parse->GetText().c_str());
		DBG_PRINT(("pInvDet->m_dj == %lf", pInvDet->m_dj));

		parse->LocateNodeByName(parse->m_parentElement[4], "sl");
		pInvDet->m_spsl = atof(parse->GetText().c_str());	
		DBG_PRINT(("pInvDet->m_spsl == %lf", pInvDet->m_spsl));

		parse->LocateNodeByName(parse->m_parentElement[4], "je");
		pInvDet->m_je =double2int(atof(parse->GetText().c_str())*SUM_EXTENSION);	
		DBG_PRINT(("pInvDet->m_je == %lld", pInvDet->m_je));

		parse->LocateNodeByName(parse->m_parentElement[4], "zsl");
		pInvDet->m_sl = (float)atof(parse->GetText().c_str());	
		DBG_PRINT(("pInvDet->m_sl == %f", pInvDet->m_sl));

		parse->LocateNodeByName(parse->m_parentElement[4], "se");
		DBG_PRINT(("pInvDet->m_spse == %s", parse->GetText().c_str()));
		pInvDet->m_spse = double2int(atof(parse->GetText().c_str())*SUM_EXTENSION);	
		DBG_PRINT(("pInvDet->m_spse == %lld", pInvDet->m_spse));

		parse->LocateNodeByName(parse->m_parentElement[4], "hsdj");
		pInvDet->m_spdj = atof(parse->GetText().c_str());
		DBG_PRINT(("pInvDet->m_spdj == %lf", pInvDet->m_spdj));
		
		parse->LocateNodeByName(parse->m_parentElement[4], "hsje");
		pInvDet->m_spje = double2int(atof(parse->GetText().c_str())*SUM_EXTENSION);	
		DBG_PRINT(("pInvDet->m_spje == %lld", pInvDet->m_spje));

		pInvInfo->InsertNode(pInvDet);

		pInvDet = NULL;
	}

	parse->LocateNodeByName(parse->m_parentElement[2], "hjje");
	pInvInfo->m_kpje = double2int(atof(parse->GetText().c_str())*SUM_EXTENSION);	
	DBG_PRINT(("pInvInfo->m_kpje == %lld", pInvInfo->m_kpje));

	parse->LocateNodeByName(parse->m_parentElement[2], "hjse");
	DBG_PRINT(("pInvDet->m_spse == %s", parse->GetText().c_str()));
	pInvInfo->m_kpse = double2int(atof(parse->GetText().c_str())*SUM_EXTENSION);	
	DBG_PRINT(("pInvInfo->m_kpse == %lld", pInvInfo->m_kpse));

	parse->LocateNodeByName(parse->m_parentElement[2], "jshj");
	pInvInfo->m_kphjje = double2int(atof(parse->GetText().c_str())*SUM_EXTENSION);	
	DBG_PRINT(("pInvInfo->m_kphjje == %lld", pInvInfo->m_kphjje));

	parse->LocateNodeByName(parse->m_parentElement[2], "bz");
	pInvInfo->m_backup1 = parse->GetText();	
	CJSKMakeInvoice::FilterSpace(pInvInfo->m_backup1);
	DBG_PRINT(("pInvInfo->m_backup1 == %s", pInvInfo->m_backup1.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "skr");
	pInvInfo->m_sky = parse->GetText();	
	CJSKMakeInvoice::FilterSpace(pInvInfo->m_sky);
	DBG_PRINT(("pInvInfo->m_sky == %s", pInvInfo->m_sky.c_str()));

//	parse->LocateNodeByName(parse->m_parentElement[2], "kpr");
//	pInvInfo->m_sky = parse->GetText();	
//	DBG_PRINT(("pInvInfo->m_sky == %s", pInvInfo->m_sky.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "yfpdm");
	pInvInfo->m_yfpdm = parse->GetText();	
	DBG_PRINT(("pInvInfo->m_yfpdm == %s", pInvInfo->m_yfpdm.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "yfphm");
	pInvInfo->m_yfphm = atoi(parse->GetText().c_str());	
	DBG_PRINT(("pInvInfo->m_yfphm == %u", pInvInfo->m_yfphm));

	return SUCCESS;
}

INT32 CFpkj::XmlBuild(XMLConstruct *construct, CInvHead *pInvInfo, Return_Info *retInfo)
{

	INT8 Buf[64];

	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;
	
	construct->AddNode(construct->m_parentElement[2], "fplxdm");
// 	memset(Buf, 0, sizeof(Buf));
// 	sprintf(Buf, "%u", pInvInfo->m_kplx);
// 	construct->AddText(Buf);
	construct->AddText(m_ywxml_gy.m_fplxdm);
	DBG_PRINT(("m_ywxml_gy.m_fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "fpdm");
	construct->AddText(pInvInfo->m_fpdm);
	DBG_PRINT(("pInvInfo->m_fpdm : %s", pInvInfo->m_fpdm.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "fphm");
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%08u", pInvInfo->m_fphm);
	construct->AddText(Buf);
	DBG_PRINT(("pInvInfo->m_fphm : %s", Buf));
	
	construct->AddNode(construct->m_parentElement[2], "kprq");	
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%08u%06u", pInvInfo->m_kprq, pInvInfo->m_kpsj);
	construct->AddText(Buf);
	DBG_PRINT(("pInvInfo->m_kprq + pInvInfo->m_kpsj : %s", Buf));

	construct->AddNode(construct->m_parentElement[2], "skm");	
	construct->AddText(pInvInfo->m_fwm);
	DBG_PRINT(("pInvInfo->m_fwm : %s", pInvInfo->m_fwm.c_str()));

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


INT32 CFpkj::Execute()
{
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	CInvHead invHead;

	XmlParse(m_pXmlParse, &invHead);
	CheckYWXmlPara(retInfo.m_retMsg);

	retcode = CJSKMakeInvoice::FPKJ_Proc(&invHead, retInfo.m_retMsg);
	DBG_PRINT(("retcode = %d", retcode));
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}
	
	XmlBuild(m_pXmlConstruct, &invHead, &retInfo);
	
	return SUCCESS;
}





