/*! \file    YWXML_GPXXXP.h
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ��Ϣд��
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_GPXXXP_H
#define LIB_YWXML_GPXXXP_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CGpxxxp
 *@brief ��Ʊ��Ϣд��
 */
class CGpxxxp: public CYWXmlBase
{

public:

	CGpxxxp(XMLConstruct *construct, XMLParse *parse);
	~CGpxxxp();
	
	INT32 Execute(); 

private:

	/*!
	@brief ��Ʊ��Ϣд�̣������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@param[out] gpxxmw		��Ʊ��Ϣ����
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &gpxxmw);
	
	/*! 
	@brief ��Ʊ��Ϣд�̣����������װ����װ��XML�ļ��� 
	@param[in] retInfo ������Ϣָ��
	@param[out] construct  XML������
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);	
};

}
#endif



