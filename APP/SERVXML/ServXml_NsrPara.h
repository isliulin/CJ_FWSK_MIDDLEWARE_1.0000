/*! \file    ServXml_NsrPara.h
   \brief    款机调用的中间件接口 (网络接口)业务二: 企业参数下载
   \author   zfj & myf & lzh
   \version  1.0
   \date     2015
 */

#ifndef LIB_NSR_PARA_XML_H
#define LIB_NSR_PARA_XML_H


#include "IncludeMe.h"
#include "ProtocolXML.h"
#include "GlobalNetArg.h"

struct NsrInfoData 
{
	INT8 nsrsbh[20+1];
	INT8 nsrmc[70+1];
	INT8 nsrdzdah[20+1];
	INT8 password[10];
};

class CNsrParaOutInfo
{
public:
	string m_sqxx;	//授权信息
	string m_sccs;	//上传参数设置
public:
	CNsrParaOutInfo()
	{
		m_sqxx = "";
		m_sccs = "";
	}
};

class CNsrPara : public ProtocolXML  
{
	
private:
	INT32 XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr);	
	INT32 XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);	
	
public:
	INT32 CommunicationProc(void* pDataIn, void* pDataOut, string &strErr);

	INT32 SSLConnectTest(string nsrsbh, string strZskl, string &strErr);

	CNsrPara(ProtocolOrganize *p);
	~CNsrPara();

};


#endif



