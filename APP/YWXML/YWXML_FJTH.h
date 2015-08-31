/*! \file    YWXML_FJTH.h
   \brief    ������õ��м���ӿ� ҵ��2.24 �ֻ��˻�
   \author   zfj
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_FJTH_H
#define LIB_YWXML_FJTH_H


#include "IncludeMe.h"
#include "YWXmlBase.h"

namespace middleware
{

/**
 *@class CFjth
 *@brief �ֻ��˻�
 */
class CYWXMLFjth : public CYWXmlBase
{


public:

	CYWXMLFjth(XMLConstruct *construct, XMLParse *parse);
	~CYWXMLFjth();
	
	INT32 Execute(); 


private:
	/*!
	@brief �ֻ��˻أ������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT8 &jzlx);
	
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);

		
};

}
#endif



