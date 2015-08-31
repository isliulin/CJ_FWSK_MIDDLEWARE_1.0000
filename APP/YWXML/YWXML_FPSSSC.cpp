 /*! \file    YWXML_FPSSSC.cpp
   \brief    ������õ��м���ӿ� ҵ��2.21.��Ʊʱʱ�ϴ�
   \author   YY
   \version  1.0
   \date     2015
 */

#include "YWXML_FPSSSC.h"
#include "JSKMakeInvoice.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CFpsssc::CFpsssc(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CFpsssc::~CFpsssc()
{

}



INT32 CFpsssc::XmlParse(XMLParse *parse, UINT32 &nFpzs, UINT8 &czlx)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh= parse->GetText();		//˰���տ�����
	DBG_PRINT(("YWXML_FPSSSC: jqbh = %s", m_ywxml_gy.m_jqbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "nsrsbh");
	m_ywxml_gy.m_nsrsbh= parse->GetText();		//��˰��ʶ���
	DBG_PRINT(("YWXML_FPSSSC: nsrsbh == %s", m_ywxml_gy.m_nsrsbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "sksbbh");
	m_ywxml_gy.m_sksbbh= parse->GetText();		//˰���豸���
	DBG_PRINT(("YWXML_FPSSSC: sksbbh == %s", m_ywxml_gy.m_sksbbh.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "sksbkl");
	m_ywxml_gy.m_sksbkl= parse->GetText();		//˰���豸����
	DBG_PRINT(("YWXML_FPSSSC: sksbkl == %s", m_ywxml_gy.m_sksbkl.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();		//��Ʊ���ʹ���
	DBG_PRINT(("YWXML_FPSSSC: fplxdm == %s", m_ywxml_gy.m_fplxdm.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "fpzs");
	nFpzs = atoi(parse->GetText().c_str());		//��Ʊ����
	DBG_PRINT(("YWXML_FPSSSC: fpzs == %u", nFpzs));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "czlx");
	czlx = atoi(parse->GetText().c_str());		//��������
	DBG_PRINT(("YWXML_FPSSSC: czlx == %u", czlx));
}

INT32 CFpsssc::XmlBuild(XMLConstruct *construct, UINT32 nFpzs, UINT8 czlx, string strFpmx, Return_Info *retInfo)
{
	INT8 chBuf[64];
	memset((void*)chBuf, 0, sizeof(chBuf));
	
	//���body�ڵ�
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[2], "fplxdm");
	construct->AddText(m_ywxml_gy.m_fplxdm);
	DBG_PRINT(("YWXML_FPSSSC: fplxdm : %s", retInfo->m_retCode.c_str()));

	construct->AddNode(construct->m_parentElement[2], "czlx");
	sprintf(chBuf, "%u", czlx);
	construct->AddText(chBuf);
	DBG_PRINT(("czlx : %s", retInfo->m_retCode.c_str()));

	construct->AddNode(construct->m_parentElement[2], "fpzs");//��Ʊ����
	sprintf(chBuf, "%u", nFpzs);
	construct->AddText(chBuf);
	DBG_PRINT(("YWXML_FPSSSC: fpzs : %s", chBuf));

	construct->AddNode(construct->m_parentElement[2], "fpmx");//��Ʊ��ϸ
	construct->AddText(strFpmx, XML_SET_TEXT_CDATA);
	//DBG_PRINT(("YWXML_FPSSSC: fpmx : %s", strFpmx.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);
	DBG_PRINT(("YWXML_FPSSSC: returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);
	DBG_PRINT(("YWXML_FPSSSC: returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
}


INT32 CFpsssc::Execute()
{
	UINT32 nFpzs = 0;
	UINT8 czlx=0;
	string strFpmx("");
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];

	XmlParse(m_pXmlParse, nFpzs, czlx);
	CheckYWXmlPara(retInfo.m_retMsg);

	retcode = CJSKMakeInvoice::FPSC_Proc(czlx, nFpzs, strFpmx, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}

	XmlBuild(m_pXmlConstruct, nFpzs, czlx, strFpmx, &retInfo);

	return SUCCESS;
}


