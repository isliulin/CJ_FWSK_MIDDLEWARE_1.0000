
 /*! \file    ServXML_Yccb.h
   \brief    款机调用的中间件接口(网络接口)业务六: 远程抄报接口(0013专普票)
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_SERV_YCCB_EX_XML_H
#define LIB_SERV_YCCB_EX_XML_H


#include "IncludeMe.h"
#include "ProtocolXML.h"



/**
 *@class CServYccb
 *@brief 远程抄报接口
 */

class CServYccbEx : public ProtocolXML  
{
	
private:
	INT32 XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr);	
	INT32 XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);	
	
public:

	CServYccbEx(AppProtocol *p);
	~CServYccbEx();

};


#endif

