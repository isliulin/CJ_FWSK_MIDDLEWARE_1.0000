/*! \file    YWXML_FPGX.h
   \brief    ������õ��м���ӿ� ҵ��2.22.��Ʊ����
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_FPGX_H
#define LIB_YWXML_FPGX_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CFpgx
 *@brief 2.22.��Ʊ����
 */
class CFpgx : public CYWXmlBase
{


public:

	CFpgx(XMLConstruct *construct, XMLParse *parse);
	~CFpgx();
	
	INT32 Execute(); 


private:
	/*!
	@brief ��Ʊ���룺�����������������XML�ļ���
	@param[in]  pXmlParse XML������
	@param[out]  strScqrbw  �ϴ��ɹ�ȷ�ϱ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &strScqrbw);
	
	/*!
	@brief ��Ʊ���룺���������װ����װ��XML�ļ���
	@param[in]  retInfo ���ؽ��
	@param[out]  construct  ����XML��
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);

		
};

}
#endif



