
 /*! \file    ServXML_Qkxxxz.h
   \brief    款机调用的中间件接口(网络接口)业务七: 清卡信息下载接口(0014专普票)
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
 *@brief 清卡信息下载接口
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




























