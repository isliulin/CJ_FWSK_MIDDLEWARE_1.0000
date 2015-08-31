/*! \file   ServXml_InvUploadResult.h
   \brief    ����ӿ� ҵ��: ��Ʊ�ϴ�������ؽӿ�
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_INV_UP_RESULT_XML_H
#define LIB_INV_UP_RESULT_XML_H

#include "IncludeMe.h"
#include "ProtocolXML.h"

class CFpSucc
{
public:
	string m_fpdm;	//��Ʊ����
	string m_fphm;	//��Ʊ����
	string m_scbzFlag;	//BASE64����ϴ���־���ܰ������ܺ����д���豸�ײ�
};

class CFpErr
{
public:
	string m_fpdm;
	string m_fphm;
	string m_errCode;
	string m_errInfo;	
};


class CInvUpResultOutinfo
{
public:
	CFpSucc m_FpSucc;
	CFpErr  m_FpErr;
	UINT8	m_IfSuccFlag;	//��Ʊ�����Ƿ�ɹ� 0��ʧ�� 1���ɹ�
	CInvUpResultOutinfo();
	~CInvUpResultOutinfo();
};


class CInvUpResult : public ProtocolXML  
{
	
private:
	INT32 XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr);	
	INT32 XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);	
	
public:
	INT32 CommunicationProc(void* pDataIn, void* pDataOut, string &strErr);


	
	CInvUpResult(ProtocolOrganize *p);
	~CInvUpResult();
	
};


#endif



