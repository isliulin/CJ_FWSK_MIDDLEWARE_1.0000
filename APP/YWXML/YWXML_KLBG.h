/*! \file    YWXML_KLBG.h
   \brief    ������õ��м���ӿ� ҵ��: ������
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_KLBG_H
#define LIB_YWXML_KLBG_H

#include "IncludeMe.h"
#include "YWXmlBase.h"

namespace middleware
{

/**
 *@class CKlbg
 *@brief ������
 */
class CKlbg: public CYWXmlBase
{

public:

	CKlbg(XMLConstruct *construct, XMLParse *parse);
	~CKlbg();
	
	INT32 Execute(); 

private:

	/*!
	@brief �������������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@param[out] ykl ԭ���� 
	@param[out] xkl �¿���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &ykl, string &xkl);
	
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



