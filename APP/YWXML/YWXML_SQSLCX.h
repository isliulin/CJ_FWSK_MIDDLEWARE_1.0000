/*! \file    YWXML_SQSLCX.h
   \brief    ������õ��м���ӿ� ҵ��:��Ȩ˰�ʲ�ѯ
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_SQSLCX_H
#define LIB_YWXML_SQSLCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"

#include "CTax.h"

namespace middleware
{

/**
 *@class CSqslcx
 *@brief ��Ȩ˰�ʲ�ѯ
 */
class CSqslcx : public CYWXmlBase
{

public:

	CSqslcx(XMLConstruct *construct, XMLParse *parse);
	~CSqslcx();
	
	INT32 Execute(); 

private:

	/*!
	@brief ��Ȩ˰�ʲ�ѯ�������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);
	
	/*! 
	@brief ��Ȩ˰�ʲ�ѯ�����������װ����װ��XML�ļ��� 
	@param[in] pTax     ˰�ʱ��ָ��
	@param[in] slNum	˰�ʵĸ���
	@param[in] retInfo ������Ϣָ��
	@param[out] construct  XML������
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, CTax *pTax, UINT8 slNum, Return_Info *retInfo);	
};

}
#endif



