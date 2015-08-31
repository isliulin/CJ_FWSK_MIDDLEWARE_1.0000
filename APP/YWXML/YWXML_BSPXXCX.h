/*! \file    YWXML_BSPXXCX.h
   \brief    ������õ��м���ӿ� ҵ��: ��˰����Ϣ��ѯ
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_BSPXXCX_H
#define LIB_YWXML_BSPXXCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CUserInfo.h"


namespace middleware
{
/**
 *@class CBspxxcx
 *@brief ��˰����Ϣ��ѯ
 */
class CBspxxcx : public CYWXmlBase
{

public:

	CBspxxcx(XMLConstruct *construct, XMLParse *parse);
	~CBspxxcx();
	
	INT32 Execute(); 

private:

	/*!
	@brief ��˰����Ϣ��ѯ�������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);
	
	/*! 
	@brief ��˰����Ϣ��ѯ�����������װ����װ��XML�ļ��� 
	@param[in] pUserinfo ָ���û���Ϣ���ָ�� 
	@param[in] bspbh ��˰�̱�� 
	@param[in] retInfo ������Ϣָ��
	@param[in] dqsz ��ǰʱ��
	@param[out] construct  XML������
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, CUserInfo *pUserinfo, string dqsz, Return_Info *retInfo);
};

}
#endif



