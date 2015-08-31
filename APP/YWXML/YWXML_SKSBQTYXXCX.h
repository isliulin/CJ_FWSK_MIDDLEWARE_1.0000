/*! \file    YWXML_SKSBQTYXXCX.h
   \brief    ������õ��м���ӿ� ҵ��: ˰���豸������Ϣ��ѯ
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_SKSBQTYXXCX_H
#define YWXML_SKSBQTYXXCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"

#include "CInvVol.h"


namespace middleware
{
/**
 *@class CSksbqtxxcx
 *@brief ˰���豸������Ϣ��ѯ
 */
class CSksbqtxxcx : public CYWXmlBase
{

public:

	CSksbqtxxcx(XMLConstruct *construct, XMLParse *parse);
	~CSksbqtxxcx();
	
	INT32 Execute(); 

private:

	/*!
	@brief ��Ʊ��Ϣ��ѯ�������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT8 &xxlx);
	
	/*! 
	@brief ��Ʊ��Ϣ��ѯ�����������װ����װ��XML�ļ��� 
	@param[out] construct  XML������
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, string sksbxx, Return_Info *retInfo);	
};

}
#endif



