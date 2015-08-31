 /*! \file    YWXML_FPBL.cpp
   \brief    ������õ��м���ӿ� ҵ��2.28.��Ʊ��¼
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "YWXML_FPBL.h"
#include "JSKMakeInvoice.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CFpbl::CFpbl(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CFpbl::~CFpbl()
{

}

INT32 CFpbl::XmlParse(XMLParse *parse, UINT32 &StartDate, UINT32 &EndDate)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh= parse->GetText();		//˰���տ�����
	DBG_PRINT(("YWXML_FPBL: jqbh = %s", m_ywxml_gy.m_jqbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "nsrsbh");
	m_ywxml_gy.m_nsrsbh= parse->GetText();		//��˰��ʶ���
	DBG_PRINT(("YWXML_FPBL: nsrsbh == %s", m_ywxml_gy.m_nsrsbh.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "sksbbh");
	m_ywxml_gy.m_sksbbh= parse->GetText();		//˰���豸���
	DBG_PRINT(("YWXML_FPBL: sksbbh == %s", m_ywxml_gy.m_sksbbh.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "sksbkl");
	m_ywxml_gy.m_sksbkl= parse->GetText();		//˰���豸����
	DBG_PRINT(("YWXML_FPBL: sksbkl == %s", m_ywxml_gy.m_sksbkl.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();		//��Ʊ���ʹ���
	DBG_PRINT(("YWXML_FPBL: fplxdm == %s", m_ywxml_gy.m_fplxdm.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "bsqsrq");
	StartDate = atoi(parse->GetText().c_str());					//��˰��ʼ����
	DBG_PRINT(("YWXML_FPBL: bsqsrq == %u", StartDate));

	parse->LocateNodeByName(parse->m_parentElement[2], "bsjzrq");
	EndDate = atoi(parse->GetText().c_str());					//��˰��ֹ����
	DBG_PRINT(("YWXML_FPBL: bsjzrq == %u", EndDate));

	return SUCCESS;
}

INT32 CFpbl::XmlBuild(XMLConstruct *construct, Return_Info *retInfo)
{
	//���body�ڵ�
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);
	DBG_PRINT(("YWXML_FPBL: returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);
	DBG_PRINT(("YWXML_FPBL: returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
}


INT32 CFpbl::Execute()
{
	UINT32 StartDate = 0;		//��˰��ʼ����
	UINT32 EndDate = 0;			//��˰��ֹ����
	Return_Info retInfo;//������Ϣ
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	
	XmlParse(m_pXmlParse, StartDate, EndDate);	//����XML��������
	CheckYWXmlPara(retInfo.m_retMsg);
	
	retcode = CJSKMakeInvoice::FPBL_Proc(m_ywxml_gy.m_nsrsbh, m_ywxml_gy.m_sksbbh, StartDate, EndDate,  retInfo.m_retMsg);	
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}
	
	XmlBuild(m_pXmlConstruct, &retInfo);	//����XML��װ����
	
	return SUCCESS;
}


