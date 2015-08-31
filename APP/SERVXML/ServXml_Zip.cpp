

#include "ServXml_Zip.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CServXml_Zip::CServXml_Zip(AppProtocol *p):ProtocolXML(p)
{
	setDeclaration(XML_DEF_VERSION, XML_DEF_ENCODING, GBK_CHAR_TYPE);
	setRootName("root");
}

CServXml_Zip::~CServXml_Zip()
{
	DBG_PRINT(("in ~CServXml_Zip()"))
}

INT32 CServXml_Zip::XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("IN CServXml_Zip::XmlBusinessBuild"));
	char tmpBuf[32];
	NoteData_Para *note = (NoteData_Para *)pNote; 

	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "digitalEnvelope");
	pXmlBuild->AddText("0");

	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "zip");
	pXmlBuild->AddText("0");

	DBG_ASSERT_EXIT((pData != NULL), (" pData == NULL!"));
	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "context");
	pXmlBuild->AddText((INT8 *)pData);

	return SUCCESS;
}

INT32 CServXml_Zip::XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("CServXml_Zip::XmlBusinessParse Begin"));
	int res = 0;
	string tmpStr;
	NoteData_Para *note = (NoteData_Para *)pNote; 

	res = pXmlParse->LocateNodeByName(pXmlParse->m_signNode, "digitalEnvelope");
	DBG_PRINT(("res = %d, note->m_appType = %s", res, note->m_appType.c_str()));
	if(res != SUCCESS)
	{
		if( (note->m_appType == NET_FPSC) || (note->m_appType == NET_FPSCJGXZ) )
		{
			memset(g_Xml_ExchangeBuf_Inv, 0, PROTOCOL_OUT_BUFF_LEN);
			memcpy(g_Xml_ExchangeBuf_Inv, pData->pBuff, pData->outLen);
			pData->fill(g_Xml_ExchangeBuf_Inv, pData->outLen);
			memset(g_Xml_ExchangeBuf_Inv, 0, PROTOCOL_OUT_BUFF_LEN);
		}
		else
		{
			memset(g_Xml_ExchangeBuf, 0, PROTOCOL_OUT_BUFF_LEN);
			memcpy(g_Xml_ExchangeBuf, pData->pBuff, pData->outLen);
			pData->fill(g_Xml_ExchangeBuf, pData->outLen);
			memset(g_Xml_ExchangeBuf, 0, PROTOCOL_OUT_BUFF_LEN);
		}
		return SUCCESS;
	}
	tmpStr = pXmlParse->GetText();
	DBG_PRINT(("tmpStr = %s", tmpStr.c_str()));

	pXmlParse->LocateNodeByName(pXmlParse->m_signNode, "zip");
	tmpStr = pXmlParse->GetText();
	DBG_PRINT(("tmpStr = %s", tmpStr.c_str()));

	pXmlParse->LocateNodeByName(pXmlParse->m_signNode, "context");
	tmpStr = pXmlParse->GetText();
	DBG_PRINT(("tmpStr = %s", tmpStr.c_str()));
	pData->fill((INT8 *)tmpStr.c_str(), tmpStr.length());

	return SUCCESS;
}

