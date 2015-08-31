/*! \file    YWXML_HQLXSJ.h
   \brief    ������õ��м���ӿ� ҵ��2.28.��ȡ�����������
   \author   MYF
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_HQLXSJ_H
#define LIB_YWXML_HQLXSJ_H

#include "IncludeMe.h"
#include "YWXmlBase.h"

namespace middleware
{
/**
 *@class HQLXSJ
 *@brief ��ȡ�����������
 */
class CHqlxsj : public CYWXmlBase
{


public:

	CHqlxsj(XMLConstruct *construct, XMLParse *parse);
	~CHqlxsj();
	
	INT32 Execute(); 


private:
	/*!
	@������: XmlParse
	@brief ��ȡ����������ݣ������������������XML�ļ���
	@param[in]  parse		XML������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);

	/*!
	@������: XmlBuild
	@brief ��ȡ����������ݣ����������װ����װXML�ļ���
	@param[in]  construct		XML��װ��
	@param[in]  invvol		��Ʊ������Ϣ��
	@param[in]  strLgry		�칺��Ա
	@param[in]  retInfo		������Ϣ��
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, UINT32 &wscfpzs, string &wscfpsj, INT64 &wscfpljje, Return_Info *retInfo);

		
};

}
#endif



