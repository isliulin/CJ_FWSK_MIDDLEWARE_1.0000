/*! \file    SerXml_Yccb.cpp
   \brief    ������õ��м���ӿ� (����ӿ�)ҵ����: Զ�̳����ӿ�(0013ר��Ʊ)
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "ServXml_YccbHx.h"
#include "ServWlcb.h"
#include "GlobalNetArg.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

CServYccbHx::CServYccbHx(AppProtocol *p):ProtocolXML(p)
{
	setDeclaration(XML_DEF_VERSION, XML_DEF_ENCODING, GBK_CHAR_TYPE);
	setXmlSaveFile(XML_DEF_YCCBHX_REQFILE, XML_DEF_BUSSINESS_RSPFILE); 
	setRootName("hydataFromHxClient");
}

CServYccbHx::~CServYccbHx()
{
	DBG_PRINT(("in ~CServYccbHx()"))
}

INT32 CServYccbHx::XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("IN CServYccbHx::XmlBusinessBuild"));
	DBG_ASSERT_EXIT((pBusiness != NULL), (" pBusiness == NULL!"));
	
	CServWlcb *p = (CServWlcb *)pBusiness;

	//��������:01,��ȡ��˰��������;02,��ȡ����������� �ɲ���
	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "czlx");
	pXmlBuild->AddText("");

	//��Ʊ����,������
	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "kpjh");
	pXmlBuild->AddText(g_gNetArg->m_kpjh);
	DBG_PRINT(("kpjh : %s", g_gNetArg->m_kpjh.c_str()));
	
	//��˰ʱ��,YYYY-MM-DD HH24:MI,������
	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "bssj");
	pXmlBuild->AddText(p->m_cssj);
	DBG_PRINT(("bssj : %s", p->m_cssj.c_str()));
	
	//���ܱ�˰����,������
	DBG_ASSERT_EXIT((pData != NULL), (" pData == NULL!"));
	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "encryptedTaxData");
	pXmlBuild->AddText((INT8 *)pData);
	
	//Ʊ����Ȩ���� ��Ʊ:025 ,������
	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "pzsqdm");
	pXmlBuild->AddText(p->m_fplxdm);
	DBG_PRINT(("pzsqdm : %s", p->m_fplxdm.c_str()));
	
	return SUCCESS;
}

INT32 CServYccbHx::XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("CServYccbHx::XmlBusinessParse Begin"));

	memset(g_Xml_ExchangeBuf, 0, PROTOCOL_OUT_BUFF_LEN);
	memcpy(g_Xml_ExchangeBuf, pData->pBuff, pData->outLen);
	pData->fill(g_Xml_ExchangeBuf, pData->outLen);
	memset(g_Xml_ExchangeBuf, 0, PROTOCOL_OUT_BUFF_LEN);
	

	return SUCCESS;
}


