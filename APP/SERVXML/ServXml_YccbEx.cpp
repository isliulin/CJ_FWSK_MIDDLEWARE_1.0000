/*! \file    SerXml_Yccb.cpp
   \brief    ������õ��м���ӿ� (����ӿ�)ҵ����: Զ�̳����ӿ�(0013ר��Ʊ)
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "ServXml_YccbEx.h"
#include "ServWlcb.h"
#include "GlobalNetArg.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

CServYccbEx::CServYccbEx(AppProtocol *p):ProtocolXML(p)
{
	setXmlSaveFile(XML_DEF_BUSSINESS_REQFILE, XML_DEF_BUSSINESS_RSPFILE); 
	setUpdateFile(XML_RESPONSE_FILE,  GBK_CHAR_TYPE);
}

CServYccbEx::~CServYccbEx()
{
	DBG_PRINT(("in ~CServYccbEx()"))
}

INT32 CServYccbEx::XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("IN CServYccbEx::XmlBusinessBuild"));
//	DBG_ASSERT_EXIT((pBusiness != NULL), (" pBusiness == NULL!"));

	pXmlBuild->LocateNodeByName(pXmlBuild->m_RootElement, "body");
	pXmlBuild->m_parentElement[1] = pXmlBuild->m_Child;
	UINT32 FpmxCount = (UINT8)atoi(pXmlBuild->GetAttr("count").c_str());	//����XML��õ���ϸ����
	DBG_PRINT(("FpmxCount == %u", FpmxCount));
	
	pXmlBuild->LocateNodeByName(pXmlBuild->m_parentElement[1], "input");
	pXmlBuild->m_parentElement[2] = pXmlBuild->m_Child;
	
	for (int i=0; i<FpmxCount; i++)
	{
		//�õ�group�ڵ�
		pXmlBuild->LocateNodeByName(pXmlBuild->m_parentElement[2], "group", i);
		pXmlBuild->m_parentElement[3] = pXmlBuild->m_Child;
		
		DBG_ASSERT_EXIT((pData != NULL), (" pData == NULL!"));
		pXmlBuild->LocateNodeByName(pXmlBuild->m_parentElement[3], "fphz");
		pXmlBuild->UpdateText((INT8 *)pData);
	}
	
	return SUCCESS;
}

INT32 CServYccbEx::XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("CServYccbEx::XmlBusinessParse Begin"));
	
	memset(g_Xml_ExchangeBuf, 0, PROTOCOL_OUT_BUFF_LEN);
	memcpy(g_Xml_ExchangeBuf, pData->pBuff, pData->outLen);
	pData->fill(g_Xml_ExchangeBuf, pData->outLen);
	memset(g_Xml_ExchangeBuf, 0, PROTOCOL_OUT_BUFF_LEN);
	

	return SUCCESS;
}

