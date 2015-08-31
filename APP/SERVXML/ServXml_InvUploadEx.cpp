/*! \file   ServXml_InvUpload.pp
   \brief    网络接口 业务: 发票上传接口
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "ServXml_InvUploadEx.h"
#include "TDateTime.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "CInvHead.h"
#include "GlobalNetArg.h"
#include "SysMacDef.h"
#include "JSKInfoDef.h"


CInvUploadEx::CInvUploadEx(AppProtocol *p):ProtocolXML(p)
{
	setXmlSaveFile(XML_DEF_BUSSINESS_REQFILE, XML_DEF_BUSSINESS_RSPFILE); 
	setUpdateFile(XML_RESPONSE_FILE,  GBK_CHAR_TYPE);
}

CInvUploadEx::~CInvUploadEx()
{
	DBG_PRINT(("in ~CInvUploadEx()"))
}

INT32 CInvUploadEx::XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("IN CInvUploadEx::XmlBusinessBuild"));
//	DBG_ASSERT_EXIT((pBusiness != NULL), (" pData == NULL!"));
	
	UINT8 i = 0;
	
	pXmlBuild->LocateNodeByName(pXmlBuild->m_RootElement, "body");
	pXmlBuild->m_parentElement[1] = pXmlBuild->m_Child;
	UINT32 FpmxCount = (UINT8)atoi(pXmlBuild->GetAttr("count").c_str());	//解析XML后得到明细个数
	DBG_PRINT(("FpmxCount == %u", FpmxCount));
	
	pXmlBuild->LocateNodeByName(pXmlBuild->m_parentElement[1], "input");
	pXmlBuild->m_parentElement[2] = pXmlBuild->m_Child;
	
	for (i=0; i<FpmxCount; i++)
	{
		//得到group节点
		pXmlBuild->LocateNodeByName(pXmlBuild->m_parentElement[2], "group", i);
		pXmlBuild->m_parentElement[3] = pXmlBuild->m_Child;
		
		DBG_ASSERT_EXIT((pData != NULL), (" pData == NULL!"));
		pXmlBuild->LocateNodeByName(pXmlBuild->m_parentElement[3], "fpmx");
		pXmlBuild->UpdateText((INT8 *)pData);
	}

	return SUCCESS;
}

INT32 CInvUploadEx::XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("CInvUploadEx::XmlBusinessParse Begin"));
	int res = 0;
	
	string tmpStr("");
	
	INT32 layer = pXmlParse->m_signNodeLayer;
	
	pXmlParse->LocateNodeByName(pXmlParse->m_signNode, "body");
	pXmlParse->m_parentElement[layer+1] = pXmlParse->m_Child;
	UINT32 FpmxCount = (UINT8)atoi(pXmlParse->GetAttr("count").c_str());	//解析XML后得到明细个数
	DBG_PRINT(("FpmxCount == %u", FpmxCount));

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+1], "output");
	pXmlParse->m_parentElement[layer+2] = pXmlParse->m_Child;

	for (int i=0; i<FpmxCount; i++)
	{
		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "group");
		pXmlParse->m_parentElement[layer+3] = pXmlParse->m_Child;

		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+3], "returncode");
		string m_retCode = pXmlParse->GetText();
		DBG_PRINT(("returncode : %s", m_retCode.c_str()));

		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+3], "slxlh");
		tmpStr = pXmlParse->GetText();
		g_gNetArg->SetSlxlh(tmpStr);
	}

	memset(g_Xml_ExchangeBuf_Inv, 0, PROTOCOL_OUT_BUFF_LEN);
	memcpy(g_Xml_ExchangeBuf_Inv, pData->pBuff, pData->outLen);
	pData->fill(g_Xml_ExchangeBuf_Inv, pData->outLen);
	memset(g_Xml_ExchangeBuf_Inv, 0, PROTOCOL_OUT_BUFF_LEN);

	return SUCCESS;
}


