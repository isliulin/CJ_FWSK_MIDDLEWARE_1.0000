/*! \file   ServXml_InvUploadResult.h
   \brief    网络接口 业务: 发票上传结果下载接口
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
	string m_fpdm;	//发票代码
	string m_fphm;	//发票号码
	string m_scbzFlag;	//BASE64后的上传标志加密包，接受后解码写入设备底层
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
	UINT8	m_IfSuccFlag;	//发票下载是否成功 0：失败 1：成功
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



