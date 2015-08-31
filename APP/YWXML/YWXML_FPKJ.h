/*! \file    YWXML_FPKJ.h
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ����
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_FPKJ_H
#define LIB_YWXML_FPKJ_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvHead.h"
#include "CInvDet.h"
#include "arithmetic.h"

namespace middleware
{
/**
 *@class CFpkj
 *@brief ��Ʊ����
 */
class CFpkj: public CYWXmlBase
{

public:

	CFpkj(XMLConstruct *construct, XMLParse *parse);
	~CFpkj();
	
	INT32 Execute(); 


private:

	/*!
	@brief ��Ʊ���ߣ������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@param[out]  pInvInfo  ��Ʊ����
	@param[out]  hyfl	  ��ҵ����
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, CInvHead *pInvInfo);
	
	/*! 
	@brief ��Ʊ���ߣ����������װ����װ��XML�ļ��� 
	@param[in] pInvVol ָ��Ʊ��Ϣ���ָ�� 
	@param[in] retInfo ������Ϣָ��Ϣ�����
	@param[out] construct  XML������
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, CInvHead *pInvInfo, Return_Info *retInfo);	
};

}
#endif



