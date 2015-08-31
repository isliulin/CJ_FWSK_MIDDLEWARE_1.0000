/*! \file     NETXML_QLJS.cpp
   \brief    ������õ��м���ӿ� ҵ��: ��ػش�
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "SKJNETXML_QLJS.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CSKJQljs::CSKJQljs(CYWXML_GY &ywxml_gy, string Qtxx, string &Fpjkmw):m_Qtxx(Qtxx), m_Fpjkmw(Fpjkmw), CSKJYWXmlBase(ywxml_gy)
{
	m_FpCount = 1;
	m_Count = 1;
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CSKJQljs::~CSKJQljs()
{

}


INT32 CSKJQljs::XmlBuild()
{
	UINT8 i = 0;
	INT8 Buf[64];
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_RootElement, "body");
	m_pXmlConstruct.m_parentElement[1] = m_pXmlConstruct.m_NewElement;
	memset(Buf, 0, sizeof(Buf));
	sprintf(Buf, "%u", m_FpCount);
	m_pXmlConstruct.AddAttr("count", Buf);
	DBG_PRINT(("count : %s", Buf));

	m_pXmlConstruct.AddAttr("skph", m_ywxml_gy.m_sksbbh);	
	m_pXmlConstruct.AddAttr("nsrsbh", m_ywxml_gy.m_nsrsbh);
	m_pXmlConstruct.AddAttr("kpjh", m_ywxml_gy.m_kpjh);
	DBG_PRINT(("skph : %s", m_ywxml_gy.m_sksbbh.c_str()));
	DBG_PRINT(("nsrsbh : %s", m_ywxml_gy.m_nsrsbh.c_str()));
	DBG_PRINT(("kpjh : %s", m_ywxml_gy.m_kpjh.c_str()));
	
	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[1], "input");
	m_pXmlConstruct.m_parentElement[2] = m_pXmlConstruct.m_NewElement;
	
	for (i=1; i<=m_FpCount; i++)
	{
		//�õ�group�ڵ�
		m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "group");
		m_pXmlConstruct.m_parentElement[3] = m_pXmlConstruct.m_NewElement;
		memset(Buf, 0, sizeof(Buf));
		sprintf(Buf, "%u", i);
		m_pXmlConstruct.AddAttr("xh", Buf);
		
		m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[3], "fplxdm");
		m_pXmlConstruct.AddText(m_ywxml_gy.m_fplxdm);	
		DBG_PRINT(("fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));
		
	}

	m_pXmlConstruct.AddNode(m_pXmlConstruct.m_parentElement[2], "qtxx");
	m_pXmlConstruct.AddText(m_Qtxx);
	DBG_PRINT(("Qtxx == %s", m_Qtxx.c_str()));

	return XML_SUCCESS;
}

INT32 CSKJQljs::XmlParse()
{

	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_RootElement, "body");
	m_pXmlParse.m_parentElement[1] = m_pXmlParse.m_Child;
	
	m_Count = (UINT8)atoi(m_pXmlParse.GetAttr("count").c_str());
	DBG_PRINT(("count : %u", m_Count));
	
// 	m_ywxml_gy.m_sksbbh = m_pXmlParse.GetAttr("skph");
// 	m_ywxml_gy.m_nsrsbh = m_pXmlParse.GetAttr("nsrsbh");
// 	DBG_PRINT(("skph : %s", m_ywxml_gy.m_sksbbh.c_str()));
// 	DBG_PRINT(("nsrsbh : %s", m_ywxml_gy.m_nsrsbh.c_str()));
	
	m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[1], "output");
	m_pXmlParse.m_parentElement[2] = m_pXmlParse.m_Child;
	
	for (UINT8 i=0; i<m_Count; i++)
	{
		m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[2], "group", i);
		m_pXmlParse.m_parentElement[3] = m_pXmlParse.m_Child;
		
		m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[3], "fplxdm");
		m_ywxml_gy.m_fplxdm = m_pXmlParse.GetText();
		DBG_PRINT(("fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));		
		
		m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[3], "fpjkmw");
		m_Fpjkmw = m_pXmlParse.GetText();
		DBG_PRINT(("m_Fpjkmw : %s", m_Fpjkmw.c_str()));

// 		m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[3], "szjkmw");
// 		m_Szjkmw = m_pXmlParse.GetText();
// 		DBG_PRINT(("m_Szjkmw : %s", m_Szjkmw.c_str()));
		
		m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[3], "returncode");
		m_retInfo.m_retCode = m_pXmlParse.GetText();
		DBG_PRINT(("returncode : %s", m_retInfo.m_retCode.c_str()));
		
		m_pXmlParse.LocateNodeByName(m_pXmlParse.m_parentElement[3], "returnmsg");
		m_retInfo.m_retMsg = m_pXmlParse.GetText();
		DBG_PRINT(("returnmsg : %s", m_retInfo.m_retMsg.c_str()));
	}
	
	return XML_SUCCESS;
	
}






