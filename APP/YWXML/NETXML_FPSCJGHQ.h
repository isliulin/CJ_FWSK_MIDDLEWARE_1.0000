/*! \file    NETXML_FPSCJGHQ.h
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ��ϸ�ϴ������ȡ
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_NETXML_FPSCJGHQ_H
#define LIB_NETXML_FPSCJGHQ_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CFpscjghq
 *@brief ��Ʊ��ϸ�ϴ������ȡ
 */
class CFpscjghq: public CYWXmlBase
{

public:

	CFpscjghq(XMLConstruct *construct, XMLParse *parse);
	~CFpscjghq();
	
	INT32 Execute(); 


private:

	/*!
	@brief ��Ʊ��ϸ�ϴ������ȡ�������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@param[out]  FpmxCount	��Ʊ��ϸ��
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT8 &FpmxCount, string &qtxx);
	
	/*! 
	@brief ��Ʊ��ϸ�ϴ������ȡ�����������װ����װ��XML�ļ��� 
	@param[in] Mxjgmw ���ܺ����ϸ�ϴ�������� 
	@param[in] Count �ϴ���Ʊ��ϸ����
	@param[out] construct  XML������
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, string Mxjgmw, UINT8 Count, Return_Info *retInfo);	
};

}
#endif



