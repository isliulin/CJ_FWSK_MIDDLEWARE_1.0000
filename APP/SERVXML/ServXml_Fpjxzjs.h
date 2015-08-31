
 /*! \file    ServXml_Fpjxzjs.h
   \brief    款机调用的中间件接口(网络接口)业务九: 发票卷下载/解锁接口(0020)
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_SERV_FPJXZJS_XML_H
#define LIB_SERV_FPJXZJS_XML_H


#include "IncludeMe.h"
#include "ProtocolXML.h"



/*struct FpjxzjsInfoData 
{
	INT8 nsrsbh[20+1];
	INT8 nsrmc[70+1];
	INT8 nsrdzdah[20+1];
	INT8 password[10];
};*/

/**
 *@class CServFpjxzjs
 *@brief 发票卷下载/解锁接口
 */

class CServFpjxzjs : public ProtocolXML  
{
	
private:
	INT32 XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr);	
	INT32 XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);	
	
public:
	INT32 CommunicationProc(void* pDataIn, void* pDataOut, string &strErr);

	CServFpjxzjs(ProtocolOrganize *p);
	~CServFpjxzjs();
};


#endif

