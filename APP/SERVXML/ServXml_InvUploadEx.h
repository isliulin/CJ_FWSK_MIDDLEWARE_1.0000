/*! \file   ServXml_InvUpload.h
   \brief    网络接口 业务: 发票上传接口
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_INV_UPLOAD_EX_XML_H
#define LIB_INV_UPLOAD_EX_XML_H


#include "IncludeMe.h"
#include "ProtocolXML.h"


class CInvUploadEx : public ProtocolXML  
{
	
private:
	INT32 XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr);	
	INT32 XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);	
	
public:

	CInvUploadEx(AppProtocol *p);
	~CInvUploadEx();
	
};


#endif



