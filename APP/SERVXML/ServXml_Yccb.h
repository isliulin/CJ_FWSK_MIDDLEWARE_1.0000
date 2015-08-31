
 /*! \file    ServXML_Yccb.h
   \brief    ������õ��м���ӿ�(����ӿ�)ҵ����: Զ�̳����ӿ�(0013ר��Ʊ)
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_SERV_YCCB_XML_H
#define LIB_SERV_YCCB_XML_H


#include "IncludeMe.h"
#include "ProtocolXML.h"



/*struct YccbInfoData 
{
	INT8 nsrsbh[20+1];
	INT8 nsrmc[70+1];
	INT8 nsrdzdah[20+1];
	INT8 password[10];
};*/

/**
 *@class CServYccb
 *@brief Զ�̳����ӿ�
 */

class CServYccb : public ProtocolXML  
{
	
private:
	INT32 XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr);	
	INT32 XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);	
	
public:
	INT32 CommunicationProc(void* pDataIn, void* pDataOut, string &strErr);

	CServYccb(ProtocolOrganize *p);
	~CServYccb();

};


#endif

