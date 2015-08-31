/*! \file     YWXML_FPCX.cpp
   \brief    款机调用的中间件接口 业务: 发票查询
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "YWXML_FPCX.h"
#include "CGlobalArgLib.h"
#include "JSKMakeInvoice.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"
#include "SysMacDef.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CFpcx::CFpcx(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CFpcx::~CFpcx()
{

}


INT32 CFpcx::XmlParse(XMLParse *parse, UINT8 &cxfs, string &cxtj)
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
	
	parse->LocateNodeByName(parse->m_parentElement[2], "cxfs");	//查询方式
	cxfs = (UINT8)atoi(parse->GetText().c_str());	
	DBG_PRINT(("cxfs == %u", cxfs));

	parse->LocateNodeByName(parse->m_parentElement[2], "cxtj");	//查询条件
	cxtj = parse->GetText();	
	DBG_PRINT(("cxtj == %s", cxtj.c_str()));

	return SUCCESS;
}

INT32 CFpcx::XmlBuild(XMLConstruct *construct, CInvHead *pInvInfo, CUserInfo *pUserinfo, UINT8 InvCOunt, Return_Info *retInfo)
{
	UINT8 i = 0;
	UINT8 j = 0;
	INT8 Buf[64];
	UINT8 fpzt = 0;

	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);
	DBG_PRINT(("retInfo->m_retCode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);
	DBG_PRINT(("retInfo->m_retCode : %s", retInfo->m_retMsg.c_str()));

	construct->AddNode(construct->m_parentElement[2], "fpxx");
	construct->m_parentElement[3] = construct->m_NewElement;
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%u", InvCOunt);
	DBG_PRINT(("Buf = %s", Buf));
	construct->AddAttr("count", Buf);

	for (i=1; i<=InvCOunt; i++)
	{
		construct->AddNode(construct->m_parentElement[3], "group");
		construct->m_parentElement[4] = construct->m_NewElement;
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%u", i);
		DBG_PRINT(("Buf = %s", Buf));
		construct->AddAttr("xh", Buf);

		construct->AddNode(construct->m_parentElement[4], "fpdm");
		construct->AddText(pInvInfo->m_fpdm);
		DBG_PRINT(("pInvInfo->m_fpdm : %s", pInvInfo->m_fpdm.c_str()));

		construct->AddNode(construct->m_parentElement[4], "fphm");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%08u", pInvInfo->m_fphm);
		construct->AddText(Buf);
		DBG_PRINT(("pInvInfo->m_fphm : %s", Buf));

		//发票状态
		switch(pInvInfo->m_kplx)
		{
		case JSK_NORMAL_INV:
			fpzt = 0;
			break;
		case JSK_RETURN_INV:
			fpzt = 1;
			break;
		case JSK_WASTE_INV:
			fpzt = 2;
			break;
		case JSK_WASTE_NOR:
			fpzt = 3;
			break;
		case JSK_WASTE_RET:
			fpzt = 4;
			break;
		}
		construct->AddNode(construct->m_parentElement[4], "fpzt");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%u", fpzt);
		construct->AddText(Buf);
		DBG_PRINT(("buf : %s", Buf));

		construct->AddNode(construct->m_parentElement[4], "scbz");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%u", pInvInfo->m_scbz);
		construct->AddText(Buf);
		DBG_PRINT(("pInvInfo->m_scbz : %s", Buf));

		construct->AddNode(construct->m_parentElement[4], "kprq");	
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%u", pInvInfo->m_kprq);
		construct->AddText(Buf);
		DBG_PRINT(("pInvInfo->m_kprq : %s", Buf));
	
		construct->AddNode(construct->m_parentElement[4], "kpsj");	
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%u", pInvInfo->m_kpsj);
		construct->AddText(Buf);
		DBG_PRINT(("pInvInfo->m_kpsj : %s", Buf));

		construct->AddNode(construct->m_parentElement[4], "skm");	
		construct->AddText(pInvInfo->m_fwm);
		DBG_PRINT(("pInvInfo->m_fwm : %s", pInvInfo->m_fwm.c_str()));

		construct->AddNode(construct->m_parentElement[4], "sksbbh");	//税控设备编号
		construct->AddText(pUserinfo->m_Jspsbh);
		DBG_PRINT(("pUserinfo->m_Jspsbh : %s", pUserinfo->m_Jspsbh.c_str()));


		//收款单位名称
		construct->AddNode(construct->m_parentElement[4], "skdwmc");	
		construct->AddText(pUserinfo->m_Nsrmc);
		DBG_PRINT(("pUserinfo->m_Nsrmc : %s",pUserinfo->m_Nsrmc.c_str()));

		//销货单位识别号
		construct->AddNode(construct->m_parentElement[4], "xhdwdm");	
		construct->AddText(pUserinfo->m_Nsrsbh);
		DBG_PRINT(("pUserinfo->m_Nsrsbh : %s",pUserinfo->m_Nsrsbh.c_str()));
		//销货单位名称
		construct->AddNode(construct->m_parentElement[4], "xhdwmc");	
		construct->AddText(pUserinfo->m_Nsrmc);
		DBG_PRINT(("pUserinfo->m_Nsrmc : %s",pUserinfo->m_Nsrmc.c_str()));

		//购货单位识别号
		construct->AddNode(construct->m_parentElement[4], "ghdwdm");	
		construct->AddText(pInvInfo->m_payerCode);
		DBG_PRINT(("pInvInfo->m_fkdw : %s", pInvInfo->m_fkdw.c_str()));
		//购货单位名称
		construct->AddNode(construct->m_parentElement[4], "ghdwmc");	
		construct->AddText(pInvInfo->m_fkdw);
		DBG_PRINT(("pInvInfo->m_fkdw : %s", pInvInfo->m_fkdw.c_str()));

		construct->AddNode(construct->m_parentElement[4], "sfxm");
		construct->m_parentElement[5] = construct->m_NewElement;
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%u", pInvInfo->m_sphsl);
		DBG_PRINT(("m_sphsl = %s", Buf));
		construct->AddAttr("count", Buf);
	
		CInvDet *pInvDet = pInvInfo->pHead;
		for (j=1; j<=pInvInfo->m_sphsl; j++, pInvDet = pInvDet->pNext)
		{
			construct->AddNode(construct->m_parentElement[5], "group");
			construct->m_parentElement[6] = construct->m_NewElement;
			memset(Buf, 0, sizeof(Buf));
			sprintf(Buf, "%u", j);
			DBG_PRINT(("Buf = %s", Buf));
			construct->AddAttr("xh", Buf);

			construct->AddNode(construct->m_parentElement[6], "xm");
			construct->AddText(pInvDet->m_spmc);
			DBG_PRINT(("pInvDetp->m_spmc : %s", pInvDet->m_spmc.c_str()));
			
			construct->AddNode(construct->m_parentElement[6], "dj");
			memset(Buf, 0, sizeof(Buf));
			sprintf(Buf, "%.3lf", pInvDet->m_dj);
			construct->AddText(Buf);
			DBG_PRINT(("pInvDet->m_dj : %s", Buf));

			construct->AddNode(construct->m_parentElement[6], "sl");
			memset(Buf, 0, sizeof(Buf));
			sprintf(Buf, "%.3lf", pInvDet->m_spsl);
			construct->AddText(Buf);
			DBG_PRINT(("pInvDet->m_spsl : %s", Buf));

			construct->AddNode(construct->m_parentElement[6], "je");
			memset(Buf, 0, sizeof(Buf));
			sprintf(Buf, "%.2lf", ((double)pInvDet->m_je*1.0)/SUM_EXTENSION);
			construct->AddText(Buf);
			DBG_PRINT(("pInvDet->m_je : %s", Buf));

			construct->AddNode(construct->m_parentElement[6], "zsl");
			memset(Buf, 0, sizeof(Buf));
			// sprintf(Buf, "%lf", p->m_sl);
			sprintf(Buf, "%.2lf", (double)pInvDet->m_sl);
			construct->AddText(Buf);
			DBG_PRINT(("pInvDet->m_sl : %s", Buf));

			construct->AddNode(construct->m_parentElement[6], "se");
			memset(Buf, 0, sizeof(Buf));
			sprintf(Buf, "%.2lf", ((double)pInvDet->m_spse*1.0)/SUM_EXTENSION);
			construct->AddText(Buf);
			DBG_PRINT(("pInvDet->m_spse : %s", Buf));

			construct->AddNode(construct->m_parentElement[6], "hsdj");
			memset(Buf, 0, sizeof(Buf));
			sprintf(Buf, "%.3lf", pInvDet->m_spdj);
			construct->AddText(Buf);
			DBG_PRINT(("pInvDet->m_spdj : %s", Buf));
			
			construct->AddNode(construct->m_parentElement[6], "hsje");
			memset(Buf, 0, sizeof(Buf));
			sprintf(Buf, "%.2lf", ((double)pInvDet->m_spje*1.0)/SUM_EXTENSION);
			construct->AddText(Buf);
			DBG_PRINT(("pInvDet->m_spje : %s", Buf));
		}

		construct->AddNode(construct->m_parentElement[4], "hjje");	
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.2lf", ((double)pInvInfo->m_kpje*1.0)/SUM_EXTENSION);//合计金额不含税
		construct->AddText(Buf);
		DBG_PRINT(("pInvInfo->m_kpje : %s", Buf));

		construct->AddNode(construct->m_parentElement[4], "hjse");	
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.2lf", ((double)pInvInfo->m_kpse*1.0)/SUM_EXTENSION);//合计税额
		construct->AddText(Buf);
		DBG_PRINT(("pInvInfo->m_kpse : %s", Buf));

		construct->AddNode(construct->m_parentElement[4], "jshj");	
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.2lf", ((double)pInvInfo->m_kphjje*1.0)/SUM_EXTENSION);//价税合计
		construct->AddText(Buf);
		DBG_PRINT(("pInvInfo->m_kphjje : %s", Buf));

		construct->AddNode(construct->m_parentElement[4], "bz");
		construct->AddText(pInvInfo->m_backup1);
		DBG_PRINT(("pInvInfo->m_backup1 : %s", pInvInfo->m_backup1.c_str()));

		construct->AddNode(construct->m_parentElement[4], "skr");
		construct->AddText(pInvInfo->m_sky);
		DBG_PRINT(("pInvInfo->m_sky : %s", pInvInfo->m_sky.c_str()));

// 		construct->AddNode(construct->m_parentElement[4], "kpr");
// 		construct->AddText(pInvInfo->m_sky);
// 		DBG_PRINT(("pInvInfo->m_sky : %s", pInvInfo->m_sky.c_str()));

		construct->AddNode(construct->m_parentElement[4], "yfpdm");
		construct->AddText(pInvInfo->m_yfpdm);
		DBG_PRINT(("pInvInfo->m_yfpdm : %s", pInvInfo->m_yfpdm.c_str()));

		construct->AddNode(construct->m_parentElement[4], "yfphm");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%08u",pInvInfo->m_yfphm);
		construct->AddText(Buf);
		DBG_PRINT(("pInvInfo->m_yfphm : %s", Buf));

		//作废日期
		construct->AddNode(construct->m_parentElement[4], "zfrq");
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%u%06u",pInvInfo->m_kprq, pInvInfo->m_kpsj);
		construct->AddText(Buf);
		DBG_PRINT(("buf : %s", Buf));
		
		//作废人
		construct->AddNode(construct->m_parentElement[4], "zfr");
		construct->AddText(pInvInfo->m_sky);

		//已开负数金额
		construct->AddNode(construct->m_parentElement[4], "ykfsje");	
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%.2f", ((double)pInvInfo->m_kphjje)/SUM_EXTENSION);
		construct->AddText(Buf);
		DBG_PRINT(("buf : %s", Buf));

		construct->AddNode(construct->m_parentElement[2], "qmz");	
		construct->AddText(pInvInfo->m_casign);
		DBG_PRINT(("pInvInfo->m_casign : %s", pInvInfo->m_casign.c_str()));
	}

	return SUCCESS;
	
}


INT32 CFpcx::Execute()
{
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	CInvHead invHead;
	UINT8 cxfs = 0;
	string cxtj("");
	UINT32 invNum = 0;
	string tmpStr("");
	
	XmlParse(m_pXmlParse, cxfs, cxtj);
	CheckYWXmlPara(retInfo.m_retMsg);

	retcode = CJSKMakeInvoice::FPCX_Proc(cxfs, cxtj, invNum, &invHead, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
		invNum = 0;
	}
	
	XmlBuild(m_pXmlConstruct, &invHead, g_globalArgLib->m_corpInfo, invNum, &retInfo);
	
	return SUCCESS;
}





