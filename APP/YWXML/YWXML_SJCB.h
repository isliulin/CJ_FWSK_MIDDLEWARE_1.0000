/*! \file    YWXML_SJCB.h
   \brief    ������õ��м���ӿ� ҵ��2.17���ݳ���
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_SJCB_H
#define LIB_YWXML_SJCB_H

#include "IncludeMe.h"
#include "YWXmlBase.h"

namespace middleware
{

/**
 *@class CSjcb
 *@brief ���ݳ���
 */
class CSjcb : public CYWXmlBase
{


public:

	CSjcb(XMLConstruct *construct, XMLParse *parse);
	~CSjcb();
	
	INT32 Execute(); 


private:
	/*!
	@������: XmlParse
	@brief ���ݳ����������������������XML�ļ���
	@param[in]  parse		XML������
	@param[out]  jzlx		��������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT8 &jzlx);

	/*!
	@������: XmlBuild
	@brief ���ݳ��������������װ����װXML�ļ���
	@param[in]  construct	XML��װ��
	@param[in]  chSq		����
	@param[in]  chFpmx		��Ʊ��ϸ
	@param[in]  chFpdxx		��Ʊ����Ϣ
	@param[in]  chFphz		��Ʊ��������
	@param[in]  chQtxx		������Ϣ
	@param[in]  retInfo		������Ϣ��
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, string strSQ, string strFpmx, string strFpdxx, string strFphz, string strQtxx, Return_Info *retInfo);

		
};

}

#endif























