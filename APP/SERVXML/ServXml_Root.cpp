

#include "ServXml_Root.h"
#include "md5c.h"
#include "GlobalNetArg.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CServXml_Root::CServXml_Root(AppProtocol *p):ProtocolXML(p)
{
	setDeclaration(XML_DEF_VERSION, XML_DEF_ENCODING, GBK_CHAR_TYPE);
	setRootName("ZZSFPXT");
}

CServXml_Root::~CServXml_Root()
{
	DBG_PRINT(("in ~CServXml_Root()"))
}

INT32 CServXml_Root::XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("IN CServXml_Root::XmlBusinessBuild"));
	char tmpBuf[32];
	NoteData_Para *note = (NoteData_Para *)pNote; 

	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "SK_TYPE");
	pXmlBuild->AddText(SK_TYPE_JSP);

	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "OP_TYPE");
	pXmlBuild->AddText(note->m_appType);

	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "INPUT");
	pXmlBuild->m_parentElement[1] = pXmlBuild->m_NewElement;

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "NSRSBH");
	pXmlBuild->AddText(g_gNetArg->m_nsrsbh);

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "KPJH");
	pXmlBuild->AddText(g_gNetArg->m_kpjh);

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "SBBH");
	pXmlBuild->AddText(g_gNetArg->m_sbbh);

	DBG_ASSERT_EXIT((pData != NULL), (" pData == NULL!"));
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "DATA");
	pXmlBuild->AddText((INT8 *)pData);

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "CRC");
	pXmlBuild->AddText((INT8 *)note->m_md5Buf);

	return SUCCESS;
}

INT32 CServXml_Root::XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("CServXml_Root::XmlBusinessParse Begin"));
	int res = 0;
	string tmpStr;
	string tmpCode;
	string tmpMess;

	pXmlParse->LocateNodeByName(pXmlParse->m_signNode, "SK_TYPE");
	tmpStr = pXmlParse->GetText();
	DBG_PRINT(("SK_TYPE = %s", tmpStr.c_str()));

	pXmlParse->LocateNodeByName(pXmlParse->m_signNode, "OP_TYPE");
	tmpStr = pXmlParse->GetText();
	DBG_PRINT(("OP_TYPE = %s", tmpStr.c_str()));

	pXmlParse->LocateNodeByName(pXmlParse->m_signNode, "responseCode");
	tmpCode = pXmlParse->GetText();
	res = atoi(tmpCode.c_str());
	DBG_PRINT(("responseCode = %s", tmpCode.c_str()));

	if(res != 0)
	{
		pXmlParse->LocateNodeByName(pXmlParse->m_signNode, "responseMessage");
		tmpMess = pXmlParse->GetText();
		//DBG_PRINT(("responseMessage = %s", tmpMess.c_str()));

		if(tmpMess.length() > MAX_ERR_MSG_LEN)
			tmpMess.erase(MAX_ERR_MSG_LEN, tmpMess.length()-MAX_ERR_MSG_LEN);

		INT8 tmpBuf[512];
		memset(tmpBuf, 0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%s:%s", tmpCode.c_str(), tmpMess.c_str());
		strErr = tmpBuf;
		//SetServRetInfo(resCode, resMess);
		return FAILURE;
	}

	pXmlParse->LocateNodeByName(pXmlParse->m_signNode, "INPUT");
	pXmlParse->m_parentElement[1] = pXmlParse->m_Child;

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[1], "DATA");	
	tmpStr = pXmlParse->GetText();
	pData->fill((INT8 *)tmpStr.c_str(), tmpStr.length());
	DBG_PRINT(("DATA = %s", tmpStr.c_str()));

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[1], "CRC");	
	tmpStr = pXmlParse->GetText();

	return SUCCESS;
}

