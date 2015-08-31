
 /*! \file    ServXML_Yccb.h
   \brief    ������õ��м���ӿ�(����ӿ�)ҵ����: Զ�̳����ӿ�(0013ר��Ʊ)
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
 *@brief Զ�̳����ӿ�
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

