

#ifndef LIB_SERV_XML_ZIP_XML_H
#define LIB_SERV_XML_ZIP_XML_H


#include "IncludeMe.h"
#include "ProtocolXML.h"



class CServXml_Zip : public ProtocolXML 
{
public:
	CServXml_Zip(AppProtocol *p);
	~CServXml_Zip(); 

private:
	INT32 XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr);		
	INT32 XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);	

};


#endif



