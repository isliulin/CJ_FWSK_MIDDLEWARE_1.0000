/*! \file   NETXML_WLCB.h
   \brief    ������õ��м���ӿ� ҵ��: ���糭��
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_NETXML_WLCB_H
#define LIB_NETXML_WLCB_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CWlcb
 *@brief ���糭��
 */
class CWlcb: public CYWXmlBase
{

public:

	CWlcb(XMLConstruct *construct, XMLParse *parse);
	~CWlcb();
	
	INT32 Execute(); 


private:

	/*!
	@brief ���糭���������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@param[out]  Sq		����
	@param[out]  Fpmx	��Ʊ��ϸ
	@param[out]  Fpdxx	��Ʊ����Ϣ
	@param[out]  Fphzsj	��Ʊ��������
	@param[out]  FpmxCount	��Ʊ��ϸ��
	@param[out]  Qtxx	������Ϣ
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &Sq, string &Fpmx, string &Fpdxx, string &Fphzsj, string &Szfphz, UINT8 &FpmxCount, string &Qtxx);
	
	/*! 
	@brief ���糭�������������װ����װ��XML�ļ��� 
	@param[in] pInvVol ָ��Ʊ��Ϣ���ָ�� 
	@param[in] Count �ϴ���Ʊ��ϸ����
	@param[out] construct  XML������
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, UINT8 Count, Return_Info *retInfo);	
};

}
#endif



