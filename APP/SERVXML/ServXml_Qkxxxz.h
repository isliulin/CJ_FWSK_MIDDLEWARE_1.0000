
 /*! \file    ServXML_Qkxxxz.h
   \brief    ������õ��м���ӿ�(����ӿ�)ҵ����: �忨��Ϣ���ؽӿ�(0014ר��Ʊ)
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_SERV_QKXXXZ_XML_H
#define LIB_SERV_QKXXXZ_XML_H


#include "IncludeMe.h"
#include "ProtocolXML.h"



/*struct QkxxxzInfoData 
{
	INT8 nsrsbh[20+1];
	INT8 nsrmc[70+1];
	INT8 nsrdzdah[20+1];
	INT8 password[10];
};*/

/**
 *@class CServQkxxxz
 *@brief �忨��Ϣ���ؽӿ�
 */

class CServQkxxxz : public ProtocolXML  
{
	
private:
	INT32 XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr);	
	INT32 XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);	
	
public:
	INT32 CommunicationProc(void* pDataIn, void* pDataOut, string &strErr);

	CServQkxxxz(ProtocolOrganize *p);
	~CServQkxxxz();

};


#endif




























