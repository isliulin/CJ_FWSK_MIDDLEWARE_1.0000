/*! \file    YWXML_FPBL.h
   \brief    ������õ��м���ӿ� ҵ��2.28.��Ʊ��¼
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_FPBL_H
#define LIB_YWXML_FPBL_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CFpbl
 *@brief 2.28.��Ʊ��¼
 */
class CFpbl : public CYWXmlBase
{


public:

	CFpbl(XMLConstruct *construct, XMLParse *parse);
	~CFpbl();
	
	INT32 Execute(); 


private:
	/*!
	@brief ��Ʊ��¼�������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@param[out]  StartDate		��˰��ʼ����
	@param[out]  EndDate		��˰��ֹ����
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT32 &StartDate, UINT32 &EndDate);
	
	/*!
	@brief ��Ʊ��¼�����������װ����װ��XML�ļ���
	@param[in]   retInfo	���ؽ��
	@param[out]  construct  ����XML��
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);

		
};

}
#endif



