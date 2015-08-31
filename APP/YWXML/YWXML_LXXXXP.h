/*! \file    YWXML_LXXXXP.h
   \brief    ������õ��м���ӿ� ҵ��2.20.������Ϣд��
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_LXXXXP_H
#define LIB_YWXML_LXXXXP_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"

namespace middleware
{

/**
 *@class CLxxxxp
 *@brief 2.20.������Ϣд��
 */
class CLxxxxp : public CYWXmlBase
{


public:

	CLxxxxp(XMLConstruct *construct, XMLParse *parse);
	~CLxxxxp();
	
	INT32 Execute(); 


private:
	/*!
	@brief ������Ϣд�̣������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@param[out]  strLxxxmw ������Ϣ����
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &strLxxxmw);
	
	/*!
	@brief ������Ϣд�̣����������װ����װ��XML�ļ���
	@param[in]  Return_Info retInfo ���ؽ��
	@param[out]  construct  ����XML��
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);

		
};

}
#endif



