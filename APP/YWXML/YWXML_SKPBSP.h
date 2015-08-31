/*! \file    YWXML_SKPBSP.h
   \brief    ������õ��м���ӿ� ҵ��: ˰���豸��˰����ϲ���
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_SKPBSP_H
#define LIB_YWXML_SKPBSP_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CSkpBsp
 *@brief ˰���豸��˰����ϲ���
 */
class CSkpBsp: public CYWXmlBase
{

public:

	CSkpBsp(XMLConstruct *construct, XMLParse *parse);
	~CSkpBsp();
	
	INT32 Execute(); 

private:

	/*!
	@brief ˰���豸��˰����ϲ����������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@param[out]  Czlx ��������
	@param[out]  Hzxx ������Ϣ
	@param[out]  Qtxx ������Ϣ
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT8 &Czlx, string &Hzxx, string &Qtxx);
	
	/*! 
	@brief ˰���豸��˰����ϲ��������������װ����װ��XML�ļ��� 
	@param[in] pInvVol ָ��Ʊ��Ϣ���ָ�� 
	@param[in] retInfo ������Ϣָ��Ϣ�����
	@param[out] construct  XML������
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);	
};

}
#endif



