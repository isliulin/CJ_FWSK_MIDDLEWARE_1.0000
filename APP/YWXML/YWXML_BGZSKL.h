/*! \file    YWXML_BGZSKL.h
   \brief    ������õ��м���ӿ� ҵ��: ������
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_BGZSKL_H
#define LIB_YWXML_BGZSKL_H

#include "IncludeMe.h"
#include "YWXmlBase.h"

namespace middleware
{

/**
 *@class CBgzskl
 *@brief ���֤�����
 */
class CBgzskl: public CYWXmlBase
{

public:

	CBgzskl(XMLConstruct *construct, XMLParse *parse);
	~CBgzskl();
	
	INT32 Execute(); 

private:

	/*!
	@brief �������������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@param[out] ykl ԭ֤����� 
	@param[out] xkl ��֤�����
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &yzskl, string &xzskl);
	
	/*! 
	@brief �����������������װ����װ��XML�ļ��� 
	@param[in] retInfo ������Ϣָ��
	@param[out] construct  XML������
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);	
};

}
#endif



