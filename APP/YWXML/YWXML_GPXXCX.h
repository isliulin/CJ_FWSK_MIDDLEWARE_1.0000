/*! \file    YWXML_GPXXCX.h
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ��Ϣ��ѯ
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_GPXXCX_H
#define LIB_YWXML_GPXXCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"

#include "CInvVol.h"


namespace middleware
{
/**
 *@class CGpxxcx
 *@brief ��Ʊ��Ϣ��ѯ
 */
class CGpxxcx : public CYWXmlBase
{

public:

	CGpxxcx(XMLConstruct *construct, XMLParse *parse);
	~CGpxxcx();
	
	INT32 Execute(); 

private:

	/*!
	@brief ��Ʊ��Ϣ��ѯ�������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);
	
	/*! 
	@brief ��Ʊ��Ϣ��ѯ�����������װ����װ��XML�ļ��� 
	@param[in] pInvVol ָ��Ʊ��Ϣ���ָ�� 
	@param[in] retInfo ������Ϣָ��Ϣ�����
	@param[out] construct  XML������
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, CInvVol *pInvVol, Return_Info *retInfo);	
};

}
#endif



