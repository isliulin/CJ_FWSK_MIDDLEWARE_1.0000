/*! \file   NETXML_WLCB.h
   \brief    ������õ��м���ӿ� ҵ��: ���糭��
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef SKJ_NETXML_WLCB_H
#define SKJ_NETXML_WLCB_H

#include "IncludeMe.h"
#include "SKJYWXmlBase.h"


/**
 *@class CWlcb
 *@brief ���糭��
 */
class CSKJWlcb: public CSKJYWXmlBase
{

public:
	/*!
	@param[in]  Sq		����
	@param[in]  Fphzsj	��Ʊ��������
	@param[in]  FpmxCount	��Ʊ��ϸ��
	@param[in]  Qtxx	������Ϣ
	*/
	CSKJWlcb(CYWXML_GY &ywxml_gy, string Sq, string Fphzsj, string Qtxx);
	~CSKJWlcb();
	
	/*!
	@brief ���糭�������������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*! 
	@brief ���糭���������������������XML�ļ���
	@param[in] pInvVol ָ��Ʊ��Ϣ���ָ�� 
	@param[in] Count �ϴ���Ʊ��ϸ����
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlParse();	

	UINT32 m_Count;
	string m_Sq;
	string m_Fphzsj;
	UINT32 m_FpCount;
	string m_Qtxx;
};

#endif



