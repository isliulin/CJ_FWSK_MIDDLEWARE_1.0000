/*! \file   ServXml_InvUpload.h
   \brief    网络接口 业务: 发票上传接口
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_INV_UPLOAD_XML_H
#define LIB_INV_UPLOAD_XML_H


#include "IncludeMe.h"
#include "ProtocolXML.h"

// class CInvUploadOutInfo
// {
// public:
// 	string m_nsrsbh;	//企业税号
// 	string m_kpjh;		//开票机号
// 	string m_sbbh;		//设备编号	
// 	string m_slxlh;		//受理序列号
// };

class CInvUpload : public ProtocolXML  
{
	
private:
	INT32 XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr);	
	INT32 XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);	


public:
	INT32 CommunicationProc(void* pDataIn, void* pDataOut, string &strErr);
	
	CInvUpload(ProtocolOrganize *p);
	~CInvUpload();

};


#endif



