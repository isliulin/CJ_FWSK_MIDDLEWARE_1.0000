/*! \file    YWXML_JKSJCX.h
\brief    ������õ��м���ӿ� ҵ��: ������ݲ�ѯ
\author   myf
\version  1.0
\date     2015 
*/

#ifndef LIB_YWXML_JKSJCX_H
#define LIB_YWXML_JKSJCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CUserInfo.h"
#include "CInvKind.h"
#include "JSKManageProc.h"

namespace middleware
{
/**
 *@class CJksjcx
 *@brief ������ݲ�ѯ
 */
class CJksjcx: public CYWXmlBase
{

public:

	CJksjcx(XMLConstruct *construct, XMLParse *parse);
	~CJksjcx();
	
	INT32 Execute(); 

private:

	/*!
	@brief ������ݲ�ѯ�������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);
	
	/*! 
	@brief ������ݲ�ѯ�����������װ����װ��XML�ļ��� 
	@param[in] pUserinfo ָ����˰����Ϣ��ָ�� 
	@param[in] pInvkind  ָ��Ʊ������Ϣ��ָ�� 
	@param[in] retInfo ������Ϣָ��
	@param[out] construct  XML������
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, CInvKind *pInvKind, Return_Info *retInfo);	
};

}
#endif



