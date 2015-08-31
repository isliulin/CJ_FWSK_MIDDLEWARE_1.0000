/*! \file    YWXML_JKHC.h
   \brief    ������õ��м���ӿ� ҵ��2.18��ػش�
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_JKHC_H
#define LIB_YWXML_JKHC_H


#include "IncludeMe.h"
#include "YWXmlBase.h"

namespace middleware
{
/**
 *@class CJkhc
 *@brief ��ػش�
 */
class CJkhc : public CYWXmlBase
{


public:

	CJkhc(XMLConstruct *construct, XMLParse *parse);
	~CJkhc();
	
	INT32 Execute(); 


private:
	/*!
	@������: XmlParse
	@brief ��ػش��������������������XML�ļ���
	@param[in]  parse		XML������
	@param[out]  strFpjkmw	��Ʊ�������
	@param[out]  strSzjkmw	ʱ�Ӽ������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &strFpjkmw, string &strSzjkmw);

	/*!
	@������: XmlBuild
	@brief��ػش������������װ����װXML�ļ���
	@param[in]  construct		XML��װ��
	@param[in]  retInfo		������Ϣ��
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);

		
};

}
#endif































