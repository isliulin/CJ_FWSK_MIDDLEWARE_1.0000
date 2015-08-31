/*! \file    YWXML_BSPFPCX.h
   \brief    ������õ��м���ӿ� ҵ��2.14 ��˰�̷�Ʊ��ѯ
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_BSPFPCX_H
#define LIB_YWXML_BSPFPCX_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvVol.h"

#define BSPFPCX_INVNUM 100 //20150517_linzihao
namespace middleware
{
/**
 *@class CBspfpcx
 *@brief ��˰�̷�Ʊ��ѯ
 */
class CBspfpcx : public CYWXmlBase
{


public:

	CBspfpcx(XMLConstruct *construct, XMLParse *parse);
	~CBspfpcx();
	
	INT32 Execute(); 


private:
	/*!
	@������: XmlParse
	@brief ��Ʊ�ַ��������������������XML�ļ���
	@param[in]  parse		XML������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);

	/*!
	@������: XmlBuild
	@brief ��Ʊ�ַ������������װ����װXML�ļ���
	@param[in]  construct		XML��װ��
	@param[in]  invvol		��Ʊ������Ϣ��
	@param[in]  strLgry		�칺��Ա
	@param[in]  retInfo		������Ϣ��
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, UINT32 invNum, CInvVol *invvol, string strLgry, Return_Info *retInfo);

		
};

}
#endif



