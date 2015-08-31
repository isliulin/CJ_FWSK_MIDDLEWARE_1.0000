/*! \file    NETXML_WLLQFPJGQR.h
   \brief    ������õ��м���ӿ� ҵ��3.7 ������ȡ��Ʊ���ȷ��
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_NETXML_WLLQFPJGQR_H
#define LIB_NETXML_WLLQFPJGQR_H


#include "IncludeMe.h"
#include "YWXmlBase.h"

namespace middleware
{
/**
 *@class CWllqfpjgqr
 *@brief ������ȡ��Ʊ���ȷ��
 */
class CWllqfpjgqr : public CYWXmlBase
{


public:

	CWllqfpjgqr(XMLConstruct *construct, XMLParse *parse);
	~CWllqfpjgqr();
	
	INT32 Execute(); 


private:
	/*!
	@������: XmlParse
	@brief ������ȡ��Ʊ���ȷ�ϣ������������������XML�ļ���
	@param[in]  parse		XML������
	@param[out]  invvol	��Ʊ������Ϣ
	@param[in]  strQtxx	������Ϣ
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, CInvVol *invvol, string &strQtxx);

	/*!
	@������: XmlBuild
	@brief ������ȡ��Ʊ���ȷ�ϣ����������װ����װXML�ļ���
	@param[in]  construct		XML��װ��
	@param[in]  retInfo		������Ϣ��
	@param[in]  invvol	��Ʊ������Ϣ
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo, CInvVol *invvol);

		
};

}
#endif


























