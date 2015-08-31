/*! \file   ServXml_InvUpload.h
   \brief    ����ӿ� ҵ��: ��Ʊ�ϴ��ӿ�
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
// 	string m_nsrsbh;	//��ҵ˰��
// 	string m_kpjh;		//��Ʊ����
// 	string m_sbbh;		//�豸���	
// 	string m_slxlh;		//�������к�
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



