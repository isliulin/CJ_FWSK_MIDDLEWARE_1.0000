

#include "ProtocolXML.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"




ProtocolXML::ProtocolXML(AppProtocol *p):AppProtocol(p)
{
	m_pOrganize = NULL;
	reset();
}

ProtocolXML::ProtocolXML(ProtocolOrganize *p):AppProtocol(NULL)
{
	m_pOrganize = p;
	reset();
}


ProtocolXML::~ProtocolXML()
{
	DBG_PRINT(("in ~ProtocolXML()"))
}

void ProtocolXML::reset()
{
	m_ver = XML_DEF_VERSION;
	m_character = XML_DEF_ENCODING ;
	m_charType = GBK_CHAR_TYPE;
	m_rootName = XML_DEF_ROOTNAME;
	m_xmlReqFile = XML_DEF_REQFILE;
	m_xmlRspFile = XML_DEF_RSPFILE;
	m_xmlUpdateFile = XML_RESPONSE_FILE;
	m_declarationFlag = 0;
}

void ProtocolXML::setDeclaration(string ver, string character, int charType, int declarationFlag)
{
	m_ver = ver;
	m_character = character;
	m_charType = charType;
	m_declarationFlag = declarationFlag;
}

void ProtocolXML::setRootName(string name)
{
	m_rootName = name;
}


void ProtocolXML::setXmlSaveFile(string ReqFileName, string RspFileName)
{
	m_xmlReqFile = ReqFileName;
	m_xmlRspFile = RspFileName;
}

void ProtocolXML::setUpdateFile(string updateFile,  int charType, int declarationFlag)
{
	m_xmlUpdateFile = updateFile;
	m_charType = charType;
	m_declarationFlag = declarationFlag;
}

INT32 ProtocolXML::BuildXml(void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	DBG_ASSERT_EXIT((m_pOrganize != NULL), (" m_pOrganize == NULL!"));
	DBG_ASSERT_EXIT((pData->pBuff!=NULL || pData->getmax()!=0), ("pBuff==NULL or maxLen=0"));

	INT32 ret=0;
	ret = m_pOrganize->Build(this, pBusiness, pData, pNote, strErr);
	m_XmlBuild.XMLConstructDelete();

	return ret;
}

INT32 ProtocolXML::ParseXml(void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	DBG_ASSERT_EXIT((m_pOrganize != NULL), (" m_pOrganize == NULL!"));
	DBG_ASSERT_EXIT((pData->pBuff!=NULL || pData->getmax()!=0), ("pBuff==NULL or maxLen=0"));

	INT32 ret=0;
	ret = m_pOrganize->Parse(this, pBusiness, pData, pNote, strErr);
	
	return ret;
}

void *ProtocolXML::getBusinessData_p(AppProtocol *protocol, DataOutType *pData)
{
	if (pData->type == DataOutType::POINT)
	{
		pData->type = DataOutType::STREAM;	//恢复为stream类型，多数情况下为该类型
		return (void *)pData->getPoint();
	}
	else
	{
		return pData->getBuff();
	}
}

INT32 ProtocolXML::signNode(TiXmlElement *pNode, DataOutType *pData)
{
	if (m_XmlParse.SignNode(pNode) != SUCCESS)
		return FAILURE;
	pData->setPoint((INT32 *)&m_XmlParse);
	return SUCCESS;
}

INT32 ProtocolXML::MakeData(void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("----------Begin of ProtocolXML::MakeData------------"))
	INT32 ret=0;
	INT32 oLenMax = pData->getmax();
	INT32 *oLen = pData->getLen_p();

	//先调用前一级的MakeData
	if (m_pProtocol != NULL)
	{
		ret = m_pProtocol->MakeData(pBusiness, pData, pNote, strErr);
	}
	else
	{
		DBG_PRINT(("--------the begin of app protocol organize--------"));
		ret = SUCCESS;
	}
	if (ret != SUCCESS)
	{
		return ret;
	}

	//开始构造XML
	DBG_PRINT(("m_declarationFlag = %ld", m_declarationFlag));
	DBG_PRINT(("m_xmlUpdateFile = %s", m_xmlUpdateFile.c_str()));
	if (m_declarationFlag == 1)	//表示需要建立一个完整XML文件
	{
		m_XmlBuild.XMLConstructBegin(m_ver, m_character, m_rootName, m_charType);
	}
	else if(m_declarationFlag == 2)	//表示读取一个已存在的XML文件
	{
		ret = m_XmlBuild.XMLConstructBeginUpdate(m_xmlUpdateFile.c_str(), m_charType);
		DBG_PRINT(("ret = %d", ret));
		if (ret != SUCCESS)
		{
			strErr = "XML文件构造失败";
			return FAILURE;
		}
	}
	else
	{
		m_XmlBuild.XMLConstructBeginSimple("root", m_charType);
	}

	//确定XML构造过程的输入参数
	void *pTmp = getBusinessData_p(m_pProtocol, pData);
	DBG_PRINT(("pTmp : %x", pTmp));

	//调用XML业务内容的构造
	ret = XmlBusinessBuild(&m_XmlBuild, pBusiness, pTmp, pNote, strErr);
	if (ret != SUCCESS)
	{
		return FAILURE;
	}

	//结束构造
	DBG_PRINT(("m_declarationFlag = %ld", m_declarationFlag));
	DBG_PRINT(("m_xmlReqFile = %s", m_xmlReqFile.c_str()));
	if( (m_declarationFlag == 1) || (m_declarationFlag == 2) )
	{
		ret = m_XmlBuild.XMLConstructEnd(m_xmlReqFile.c_str());
		if (ret != SUCCESS)
		{
			strErr = "XML文件构造失败";
			return FAILURE;
		}
		
		//将XML文件读入缓存
		pData->type = DataOutType::STREAM;
		*oLen = oLenMax;
		ret = readfile(m_xmlReqFile.c_str(), pData->pBuff, oLen, strErr);
		if (ret != SUCCESS)
		{
			return FAILURE;
		}
		DBG_PRINT(("pData->outLen = %u", pData->outLen));
	}
	else 
	{
		//将指针内的地址传递给输出参数
		pData->setPoint((INT32 *)m_XmlBuild.m_RootElement);
		DBG_PRINT(("pData->point: %x, m_RootElement: %x", pData->getPoint(), m_XmlBuild.m_RootElement));
	}

	DBG_PRINT(("----------End of ProtocolXML::MakeData------------"))
	return SUCCESS;
}

INT32 ProtocolXML::ObtainData(void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("---------Begin of ProtocolXML::ObtainData---------"))
	INT32 ret=0;
	XMLParse *pXmlParse=NULL;

	//开始解析XML
	DBG_PRINT(("m_declarationFlag = %ld", m_declarationFlag));
	DBG_PRINT(("m_xmlRspFile = %s", m_xmlRspFile.c_str()));
	if( (m_declarationFlag == 1) || (m_declarationFlag == 2) )	//表示是一个完整XML文件
	{
		DBG_ASSERT_EXIT((pData->type==DataOutType::STREAM), ("pData->type != STREAM"));
		DBG_PRINT(("!ProtocolXML::ObtainData"));
		ret = writefile(m_xmlRspFile.c_str(), pData->pBuff, pData->outLen, strErr);
		if (ret != SUCCESS)
		{
			return FAILURE;
		}
		if (m_XmlParse.XMLParseBegin(m_xmlRspFile.c_str(), m_charType) == FAILURE)
		{
			strErr = "未解析到XML根节点";
			return FAILURE;
		}
		pXmlParse = &m_XmlParse;
		pXmlParse->m_signNode = pXmlParse->m_RootElement;
		pXmlParse->m_signNodeLayer = 0;
	}
	else
	{
		DBG_ASSERT_EXIT((pData->type==DataOutType::POINT), ("pData->type != POINT"));
		pXmlParse = (XMLParse *)pData->getPoint();
		pData->type = DataOutType::STREAM;
	}

	//调用XML业务内容的解析
	ret = XmlBusinessParse(pXmlParse, pBusiness, pData, pNote, strErr);
	DBG_PRINT(("ret = %d", ret));
	if (ret != SUCCESS)
	{
		if( (m_declarationFlag == 1) || (m_declarationFlag == 2) )
		{
			m_XmlParse.XMLParseEnd();
		}
		return FAILURE;
	}
	DBG_PRINT(("---------End of ProtocolXML::ObtainData---------"));

	//调用后一级的ObtainData
	if (m_pProtocol != NULL)
	{
		ret = m_pProtocol->ObtainData(pBusiness, pData, pNote, strErr);
		if (ret != SUCCESS)
		{
			if( (m_declarationFlag == 1) || (m_declarationFlag == 2) )
			{
				m_XmlParse.XMLParseEnd();
			}
			return ret;
		}
	}	

	//结束解析
	if( (m_declarationFlag == 1) || (m_declarationFlag == 2) )
	{
		m_XmlParse.XMLParseEnd();
	}

	return SUCCESS;
}

void ProtocolXML::SetServRetInfo(string retCode, string retMsg)
{
	m_servRetInfo.m_retCode=retCode;
	m_servRetInfo.m_retMsg=retMsg;
}
void ProtocolXML::GetServRetInfo(string &retCode, string &retMsg)
{
	retCode=m_servRetInfo.m_retCode;
	retMsg=m_servRetInfo.m_retMsg;
	m_servRetInfo.InitServRetInfo();
}
UINT8 ProtocolXML::CheckServRetInfo()
{
	if(m_servRetInfo.m_retCode != SERV_RET_INFO_SUCCESS)
		return FAILURE;
	
	return SUCCESS;
}

void ProtocolXML::GetTechMsgStr(CTechnologyMsg *pTechMsg, string &strTechMsg)
{
	INT8 tmpbuf[128];
	strTechMsg = "";
	strTechMsg.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	strTechMsg.append("<tripTechnologyPackage version=\"1.0\">");
	strTechMsg.append("<identity>");
	memset(tmpbuf, 0, sizeof(tmpbuf));
	sprintf(tmpbuf, "<applicationId>%s</applicationId>", pTechMsg->m_appId.c_str());
	strTechMsg.append(tmpbuf);
	memset(tmpbuf, 0, sizeof(tmpbuf));
	sprintf(tmpbuf, "<serviceId>%s</serviceId>", pTechMsg->m_servId.c_str());
	strTechMsg.append(tmpbuf);
	memset(tmpbuf, 0, sizeof(tmpbuf));
	sprintf(tmpbuf, "<serviceURI>https://%s:%s</serviceURI>", pTechMsg->m_servIP.c_str(), pTechMsg->m_servPort.c_str());
	strTechMsg.append(tmpbuf);
	strTechMsg.append("<SSL>TA</SSL>");
//	strTechMsg.append("<SSL>OA</SSL>");

	memset(tmpbuf, 0, sizeof(tmpbuf));
	sprintf(tmpbuf, "<digigalCertPassword>%s</digigalCertPassword>", pTechMsg->m_certPwd.c_str());
	strTechMsg.append(tmpbuf);
	strTechMsg.append("<showDigigalCertSelectDialog>FALSE</showDigigalCertSelectDialog>");
#ifdef NO_POS_DEBUG
	strTechMsg.append("<logEnabled>FALSE</logEnabled>");
#else
	strTechMsg.append("<logEnabled>TRUE</logEnabled>");
#endif
	memset(tmpbuf, 0, sizeof(tmpbuf));
	sprintf(tmpbuf, "<password>%s</password>", pTechMsg->m_passWord.c_str());
	strTechMsg.append(tmpbuf);
	memset(tmpbuf, 0, sizeof(tmpbuf));
	sprintf(tmpbuf, "<nsrsbh>%s</nsrsbh>", pTechMsg->m_nsrsbh.c_str());
	strTechMsg.append(tmpbuf);
	memset(tmpbuf, 0, sizeof(tmpbuf));
	sprintf(tmpbuf, "<senderName>%s</senderName>", pTechMsg->m_sendName.c_str());
	strTechMsg.append(tmpbuf);
	strTechMsg.append("</identity>");
	strTechMsg.append("</tripTechnologyPackage>");

	DBG_PRINT(("strTechMsg = %s", strTechMsg.c_str()));

	return;
}

void ProtocolXML::GetTechMsgStrTest(CTechnologyMsg *pTechMsg, string &strTechMsg)
{
	INT8 tmpbuf[128];
	strTechMsg = "";

	strTechMsg.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	strTechMsg.append("<tripTechnologyPackage version=\"1.0\">");
	strTechMsg.append("<identity>");
	memset(tmpbuf, 0, sizeof(tmpbuf));
	sprintf(tmpbuf, "<serviceURI>https://%s:%s</serviceURI>", pTechMsg->m_servIP.c_str(), pTechMsg->m_servPort.c_str());
	strTechMsg.append(tmpbuf);
	strTechMsg.append("<SSL>TA</SSL>");
	memset(tmpbuf, 0, sizeof(tmpbuf));
	sprintf(tmpbuf, "<digigalCertPassword>%s</digigalCertPassword>", pTechMsg->m_certPwd.c_str());
	strTechMsg.append(tmpbuf);
	strTechMsg.append("<showDigigalCertSelectDialog>FALSE</showDigigalCertSelectDialog>");
	memset(tmpbuf, 0, sizeof(tmpbuf));
	sprintf(tmpbuf, "<password>%s</password>", pTechMsg->m_passWord.c_str());
	strTechMsg.append(tmpbuf);
	memset(tmpbuf, 0, sizeof(tmpbuf));
	sprintf(tmpbuf, "<nsrsbh>%s</nsrsbh>", pTechMsg->m_nsrsbh.c_str());
	strTechMsg.append(tmpbuf);
	strTechMsg.append("<senderName>zyc</senderName>");
	strTechMsg.append("<command>COMPATIBILITY_CUSTOM</command>");
	strTechMsg.append("</identity>");
	strTechMsg.append("<attachment>");
	strTechMsg.append("<Properties>");
	strTechMsg.append("<Key Name=\"FRAMEWORK_CURRENT_VERSION\">4.3.47</Key>");
	strTechMsg.append("<Key Name=\"FRAMEWORK_BIZ_SUBTYPE\">NETWORK_CONNECT_CHECK</Key>");
	strTechMsg.append("</Properties>");
	strTechMsg.append("</attachment>");
	strTechMsg.append("</tripTechnologyPackage>");

	DBG_PRINT(("strTechMsg = %s", strTechMsg.c_str()));
	
	return;
}


