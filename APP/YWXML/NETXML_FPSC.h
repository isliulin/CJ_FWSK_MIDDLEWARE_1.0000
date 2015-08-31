/*! \file    NETXML_FPSC.h
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ�ϴ�
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_NETXML_FPSC_H
#define LIB_NETXML_FPSC_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CFpsc
 *@brief ��Ʊ�ϴ�
 */
class CFpsc: public CYWXmlBase
{

public:

	CFpsc(XMLConstruct *construct, XMLParse *parse);
	~CFpsc();
	
	INT32 Execute(); 


private:

	/*!
	@brief ��Ʊ��ϸ�ϴ��������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@param[out]  Fpmx	��Ʊ��ϸ
	@param[out]  FpmxCount	��Ʊ��ϸ��
	@param[out]  Fpzs		��Ʊ������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &Fpmx, UINT8 &FpmxCount, UINT32 &Fpzs);
	
	/*! 
	@brief ��Ʊ��ϸ�ϴ������������װ����װ��XML�ļ��� 
	@param[in] pInvVol ָ��Ʊ��Ϣ���ָ�� 
	@param[in] Count �ϴ���Ʊ��ϸ����
	@param[out] construct  XML������
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, UINT8 Count, Return_Info *retInfo);	
};

}
#endif



