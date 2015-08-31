/*! \file    NETXML_WLLQFP.h
   \brief    ������õ��м���ӿ� ҵ��3.6 ������ȡ��Ʊ
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_NETXML_WLLQFP_H
#define LIB_NETXML_WLLQFP_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvVol.h"

namespace middleware
{
/**
 *@class CWllqfp
 *@brief ������ȡ��Ʊ
 */
class CWllqfp : public CYWXmlBase
{


public:

	CWllqfp(XMLConstruct *construct, XMLParse *parse);
	~CWllqfp();
	
	INT32 Execute(); 


private:
	/*!
	@������: XmlParse
	@brief ������ȡ��Ʊ�������������������XML�ļ���
	@param[in]  parse		XML������
	@param[out]  invvol	��Ʊ������Ϣ
	@param[out]  strQtxx	������Ϣ
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, CInvVol *invvol, string &strQtxx);

	/*!
	@������: XmlBuild
	@brief ������ȡ��Ʊ�����������װ����װXML�ļ���
	@param[in]  construct		XML��װ��
	@param[in]  retInfo		������Ϣ��
	@param[in]  invvol			��Ʊ������Ϣ��
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo, CInvVol *invvol);

		
};

}
#endif







































