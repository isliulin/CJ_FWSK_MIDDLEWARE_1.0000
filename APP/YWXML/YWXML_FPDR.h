/*! \file    YWXML_FPDR.h
   \brief    ������õ��м���ӿ� ҵ��2.23.��Ʊ����
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_FPDR_H
#define LIB_YWXML_FPDR_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CFpdr
 *@brief 2.23.��Ʊ����
 */
class CFpdr : public CYWXmlBase
{


public:

	CFpdr(XMLConstruct *construct, XMLParse *parse);
	~CFpdr();
	
	INT32 Execute(); 


private:
	/*!
	@brief ��Ʊ���룺�����������������XML�ļ���
	@param[in]  pXmlParse XML������
	@param[out]  jzlx		��������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT8 &jzlx);
	
	/*!
	@brief ��Ʊ���룺���������װ����װ��XML�ļ���
	@param[in]   retInfo	���ؽ��
	@param[out]  construct  ����XML��
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);

		
};

}
#endif



