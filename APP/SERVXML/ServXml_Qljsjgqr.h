
 /*! \file    ServXML_Qljsjgqr.h
   \brief    款机调用的中间件接口(网络接口)业务七: 清零解锁结果确认接口(0014专普票)
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_SERV_QLJSJGQR_XML_H
#define LIB_SERV_QLJSJGQR_XML_H


#include "IncludeMe.h"
#include "ProtocolXML.h"


/**
 *@class CServQljsjgqr
 *@brief 清零解锁结果确认
 */

class CServQljsjgqr : public ProtocolXML  
{
	
private:
	INT32 XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr);	
	INT32 XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);	
	
public:
	INT32 CommunicationProc(void* pDataIn, void* pDataOut, string &strErr);

	CServQljsjgqr(ProtocolOrganize *p);
	~CServQljsjgqr();

};


#endif




























