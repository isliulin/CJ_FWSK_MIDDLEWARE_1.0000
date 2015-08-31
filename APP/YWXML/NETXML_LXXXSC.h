/*! \file    NETXML_LXXXSC.h
   \brief    ������õ��м���ӿ� ҵ��3.5 ������Ϣ�ϴ�
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_NETXML_LXXXSC_H
#define LIB_NETXML_LXXXSC_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvKind.h"
#include "SysMacDef.h"
#include "arithmetic.h"

namespace middleware
{
/**
 *@class CLxxxsc
 *@brief ������Ϣ�ϴ�
 */
class CLxxxsc : public CYWXmlBase
{


public:

	CLxxxsc(XMLConstruct *construct, XMLParse *parse);
	~CLxxxsc();
	
	INT32 Execute(); 


private:
	/*!
	@������: XmlParse
	@brief ��Ʊ�ַ��������������������XML�ļ���
	@param[in]  parse		XML������
	@param[out]  invkind	��˰��Ʊ�ֱ�
	@param[out]  strScjzrq	�ϴ���ֹ����
	@param[out]  strLxkpsc	���߿�Ʊʱ��
	@param[out]  strQtxx	������Ϣ,����Ϣ����SERVXML�б���װ�����ֶ�
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, CInvKind *invkind, string &strScjzrq, string &strLxkpsc, string &strQtxx);

	/*!
	@������: XmlBuild
	@brief ��Ʊ�ַ������������װ����װXML�ļ���
	@param[in]  construct		XML��װ��
	@param[in]  retInfo		������Ϣ��
	@param[in]  strLzkzxx		���߿�����Ϣ
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo, string strLzkzxx);

		
};

}
#endif


































