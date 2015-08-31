/*! \file    YWXML_BSPFPSH.h
   \brief    ������õ��м���ӿ� ҵ��2.16 ��Ʊ�ջ�
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_BSPFPSH_H
#define LIB_YWXML_BSPFPSH_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvVol.h"

namespace middleware
{
/**
 *@class CBspfpsh
 *@brief ��Ʊ�ջ�
 */
class CBspfpsh: public CYWXmlBase
{


public:

	CBspfpsh(XMLConstruct *construct, XMLParse *parse);
	~CBspfpsh();
	
	INT32 Execute(); 


private:
	/*!
	@������: XmlParse
	@brief ��Ʊ�ջأ������������������XML�ļ���
	@param[in]  parse		XML������
	@param[out]  invvol		��Ʊ������Ϣ
	@param[out]  strJzlx	��������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, CInvVol *invvol, UINT8 &jzlx);

	/*!
	@������: XmlBuild
	@brief ��Ʊ�ջأ����������װ����װXML�ļ���
	@param[in]  construct		XML��װ��
	@param[in]  retInfo		������Ϣ��
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);

		
};

}
#endif












































