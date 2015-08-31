/*! \file    YWXML_BSPFPFF.h
   \brief    ������õ��м���ӿ� ҵ��2.15 ��Ʊ�ַ�
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_BSPFPFF_H
#define LIB_YWXML_BSPFPFF_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvVol.h"

namespace middleware
{
/**
 *@class CBspfpff
 *@brief ��Ʊ�ַ�
 */
class CBspfpff : public CYWXmlBase
{


public:

	CBspfpff(XMLConstruct *construct, XMLParse *parse);
	~CBspfpff();
	
	INT32 Execute(); 


private:
	/*!
	@������: XmlParse
	@brief ��Ʊ�ַ��������������������XML�ļ���
	@param[in]  parse		XML������
	@param[out]  invvol		��Ʊ������Ϣ
	@param[out]  jzlx	��������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, CInvVol *invvol, UINT8 &jzlx);

	/*!
	@������: XmlBuild
	@brief ��Ʊ�ַ������������װ����װXML�ļ���
	@param[in]  construct		XML��װ��
	@param[in]  retInfo		������Ϣ��
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);

		
};

}
#endif













































