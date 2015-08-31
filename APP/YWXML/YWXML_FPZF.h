/*! \file    YWXML_FPZF.h
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ����
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_FPZF_H
#define LIB_YWXML_FPZF_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvHead.h"

namespace middleware
{
/**
 *@class CFpzf
 *@brief ��Ʊ����
 */
class CFpzf: public CYWXmlBase
{

public:

	CFpzf(XMLConstruct *construct, XMLParse *parse);
	~CFpzf();
	
	INT32 Execute(); 


private:

	/*!
	@brief ��Ʊ���ϣ������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@param[out]  pInvInfo  ��Ʊ����
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, CInvHead *pInvInfo, UINT8 &zflx);
	
	/*! 
	@brief ��Ʊ���ϣ����������װ����װ��XML�ļ��� 
	@param[in] pInvVol ָ��Ʊ��Ϣ���ָ�� 
	@param[in] retInfo ������Ϣָ��Ϣ�����
	@param[out] construct  XML������
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, CInvHead *pInvInfo, Return_Info *retInfo);	
};

}
#endif



