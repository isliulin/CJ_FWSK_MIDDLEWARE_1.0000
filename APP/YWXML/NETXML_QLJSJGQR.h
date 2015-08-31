/*! \file   NETXML_QLJSJGQR.h
   \brief    ������õ��м���ӿ� ҵ��: 3.5.����������ȷ��
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_NETXML_QLJSJGQR_H
#define LIB_NETXML_QLJSJGQR_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "ServWlcb.h"

namespace middleware
{
/**
 *@class CQljsjgqr
 *@brief ����������ȷ��
 */
class CQljsjgqr: public CYWXmlBase
{

public:

	CQljsjgqr(XMLConstruct *construct, XMLParse *parse);
	~CQljsjgqr();
	
	INT32 Execute(); 


private:

	/*!
	@brief ��ػش��������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@param[out]  Kpjh		��Ʊ����
	@param[out]  FpmxCount	��Ʊ��ϸ��
	@param[out]  Qtxx	������Ϣ
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &Kpjh, UINT8 &FpmxCount, string &Qtxx);
	
	/*! 
	@brief ��ػش������������װ����װ��XML�ļ��� 
	@param[in] pInvVol ָ��Ʊ��Ϣ���ָ�� 
	@param[in] Fpjkmw ��Ʊ�������
	@param[in] Szjkmw ʱ�Ӽ������
	@param[in] Count �ϴ���Ʊ��ϸ����
	@param[out] construct  XML������
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct,UINT8 Count, Return_Info *retInfo);	
};

}
#endif



