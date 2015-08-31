/*! \file    YWXML_HQLXSJ.h
   \brief    ������õ��м���ӿ� ҵ��2.28.��ȡ�����������
   \author   MYF
   \version  1.0
   \date     2015 
*/

#include "YWXML_HQLXSJ.h"
#include "JSKManageProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CHqlxsj::CHqlxsj(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CHqlxsj::~CHqlxsj()
{

}

INT32 CHqlxsj::XmlParse(XMLParse *parse)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh= parse->GetText();		//˰���տ�����
	DBG_PRINT(("YWXML_HQLXSJ: jqbh = %s", m_ywxml_gy.m_jqbh.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "nsrsbh");
	m_ywxml_gy.m_nsrsbh= parse->GetText();		//��˰��ʶ���
	DBG_PRINT(("YWXML_HQLXSJ: nsrsbh = %s", m_ywxml_gy.m_nsrsbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "bspbh");
	m_ywxml_gy.m_sksbbh = parse->GetText();		//˰���豸���
	DBG_PRINT(("YWXML_HQLXSJ: sksbbh = %s", m_ywxml_gy.m_sksbbh.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "bspkl");
	m_ywxml_gy.m_sksbkl = parse->GetText();		//˰���豸����
	DBG_PRINT(("YWXML_HQLXSJ: sksbkl = %s", m_ywxml_gy.m_sksbkl.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();		//��Ʊ���ʹ���
	DBG_PRINT(("YWXML_HQLXSJ: fplxdm = %s", m_ywxml_gy.m_fplxdm.c_str()));

	return SUCCESS;
}

INT32 CHqlxsj::XmlBuild(XMLConstruct *construct, UINT32 &wscfpzs, string &wscfpsj, INT64 &wscfpljje, Return_Info *retInfo)
{
	INT8 buf[256];
	memset(buf, 0, sizeof(buf));

	//���body�ڵ�
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;


	construct->AddNode(construct->m_parentElement[2], "wscfpzs");
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%u", wscfpzs);
	construct->AddText(buf);	//δ�ϴ���Ʊ����
	DBG_PRINT(("YWXML_HQLXSJ: wscfpzs = %u",wscfpzs));

	construct->AddNode(construct->m_parentElement[2], "wscfpsj");
	construct->AddText(wscfpsj);	//δ�ϴ���Ʊʱ��
	DBG_PRINT(("YWXML_HQLXSJ: wscfpsj : %s", wscfpsj.c_str()));

	construct->AddNode(construct->m_parentElement[2], "wscfpljje");
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%0.2f", (double)(wscfpljje/100.0));
	construct->AddText(buf);	//��Ʊ��ֹ����
	DBG_PRINT(("YWXML_HQLXSJ: wscfpljje  = %lld",wscfpljje));

	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);	//���ش���
	DBG_PRINT(("YWXML_HQLXSJ: returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);		//������Ϣ
	DBG_PRINT(("YWXML_HQLXSJ: returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
}


INT32 CHqlxsj::Execute()
{
	UINT32 wscfpzs=0;
	string wscfpsj="";
	INT64  wscfpljje=0;

	Return_Info retInfo;//������Ϣ
	INT32 retcode = 0;
	INT8 tmpbuf[64];


	XmlParse(m_pXmlParse);	//����XML��������
	CheckYWXmlPara(retInfo.m_retMsg);

	retcode = CJSKManageProc::OffInvInfo_Proc(wscfpzs, wscfpsj, wscfpljje, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}
	
	XmlBuild(m_pXmlConstruct, wscfpzs, wscfpsj, wscfpljje, &retInfo);	//����XML��װ����

	return SUCCESS;
}


