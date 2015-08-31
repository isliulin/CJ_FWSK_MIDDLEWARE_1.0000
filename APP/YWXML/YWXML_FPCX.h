/*! \file    YWXML_FPCX.h
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ��ѯ
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_FPCX_H
#define LIB_YWXML_FPCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvHead.h"
#include "CUserInfo.h"

namespace middleware
{

/**
 *@class CFpcx
 *@brief ��Ʊ��ѯ
 */
class CFpcx: public CYWXmlBase
{

public:

	CFpcx(XMLConstruct *construct, XMLParse *parse);
	~CFpcx();
	
	INT32 Execute(); 

private:

	/*!
	@brief ��Ʊ��ѯ�������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@param[out]  cxfs	  ��ѯ��ʽ
	@param[out]  cxtj     ��ѯ����
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT8 &cxfs, string &cxtj);
	
	/*! 
	@brief ��Ʊ��ѯ�����������װ����װ��XML�ļ��� 
	@param[in] pInvInfo ָ��Ʊ��Ϣ��ָ�� 
	@param[in] InvCOunt ��ѯ���ķ�Ʊ���� 
	@param[in] pUserinfo ˰���豸��� 
	@param[in] retInfo ������Ϣָ��Ϣ�����
	@param[out] construct  XML������
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, CInvHead *pInvInfo, CUserInfo *pUserinfo, UINT8 InvCOunt, Return_Info *retInfo);	
};

}
#endif



