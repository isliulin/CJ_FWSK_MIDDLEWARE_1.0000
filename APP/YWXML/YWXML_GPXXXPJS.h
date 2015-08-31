/*! \file    YWXML_GPXXXPJS.h
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ��Ϣд�̽���
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_GPXXXPJS_H
#define LIB_YWXML_GPXXXPJS_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CGpxxxpjs
 *@brief ��Ʊ��Ϣд�̽���
 */
class CGpxxxpjs: public CYWXmlBase
{

public:

	CGpxxxpjs(XMLConstruct *construct, XMLParse *parse);
	~CGpxxxpjs();
	
	INT32 Execute(); 

private:

	/*!
	@brief ��Ʊ��Ϣд�̽����������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@param[out] wslpjsxx		������Ʊ������Ϣ
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &wslpjsxx);
	
	/*! 
	@brief ��Ʊ��Ϣд�̽��������������װ����װ��XML�ļ��� 
	@param[in] sksbbh ˰���豸��� 
	@param[in] bspbh ��˰�̱�� 
	@param[in] retInfo ������Ϣָ��
	@param[out] construct  XML������
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);		
};

}
#endif



