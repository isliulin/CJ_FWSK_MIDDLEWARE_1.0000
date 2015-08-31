

#ifndef LIB_SERV_XML_ROOT_XML_H
#define LIB_SERV_XML_ROOT_XML_H


#include "IncludeMe.h"
#include "ProtocolXML.h"



class CServXml_Root : public ProtocolXML 
{
public:
	CServXml_Root(AppProtocol *p);
	~CServXml_Root(); 

private:
	INT32 XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr);		
	INT32 XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);	

};


#endif



