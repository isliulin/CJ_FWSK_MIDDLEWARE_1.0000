/*! \file    YWXML_JKHC.cpp
   \brief    ������õ��м���ӿ� ҵ��2.18��ػش�
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
//���캯��
//-------------------------------------------------------------------------------------------
CJkhc::CJkhc(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
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
	m_ywxml_gy.m_jqbh= parse->GetText();		//˰���տ�����
	DBG_PRINT(("YWXML_JKHC: jqbh = %s", m_ywxml_gy.m_jqbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "nsrsbh");
	m_ywxml_gy.m_nsrsbh= parse->GetText();		//��˰��ʶ���
	DBG_PRINT(("YWXML_JKHC: nsrsbh = %s", m_ywxml_gy.m_nsrsbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "sksbbh");
	m_ywxml_gy.m_sksbbh= parse->GetText();		//˰���豸���
	DBG_PRINT(("YWXML_JKHC: sksbbh = %s", m_ywxml_gy.m_sksbbh.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "sksbkl");
	m_ywxml_gy.m_sksbkl= parse->GetText();		//˰���豸����
	DBG_PRINT(("YWXML_JKHC: sksbkl = %s", m_ywxml_gy.m_sksbkl.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();		//��Ʊ���ʹ���
	DBG_PRINT(("YWXML_JKHC: fplxdm = %s", m_ywxml_gy.m_fplxdm.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fpjkmw");
	strFpjkmw = parse->GetText();		//��Ʊ�������
	DBG_PRINT(("YWXML_JKHC: fpjkmw = %s",strFpjkmw.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "szjkmw");
	strSzjkmw = parse->GetText();		//ʱ�Ӽ������
	DBG_PRINT(("YWXML_JKHC: szjkmw = %s", strSzjkmw.c_str()));
	
	return SUCCESS;
}

INT32 CJkhc::XmlBuild(XMLConstruct *construct, Return_Info *retInfo)
{
	
	//���body�ڵ�
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;
	
	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);	//���ش���
	DBG_PRINT(("YWXML_JKHC: returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);		//������Ϣ
	DBG_PRINT(("YWXML_JKHC: returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
}


INT32 CJkhc::Execute()
{
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	string fpjkmw("");	//��Ʊ�������
	string szjkmw("");	//ʱ�Ӽ������
	Return_Info retInfo;	//	������Ϣ�����

	XmlParse(m_pXmlParse, fpjkmw, szjkmw);	//����XML��������
	CheckYWXmlPara(retInfo.m_retMsg);

	retcode = CJSKDeclareProc::JKHC_Proc(m_ywxml_gy.m_fplxdm, fpjkmw, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}
	
	XmlBuild(m_pXmlConstruct, &retInfo);	//����XML��װ����

	return SUCCESS;
}


































