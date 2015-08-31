/*! \file   NETXML_QLJS.h
   \brief    ������õ��м���ӿ� ҵ��: ��ػش�, �����������
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef SKJ_NETXML_QLJSJGQR_H
#define SKJ_NETXML_QLJSJGQR_H

#include "IncludeMe.h"
#include "SKJYWXmlBase.h"


/**
 *@class CQljs
 *@brief �����������
 */
class CSKJQljsjgqr: public CSKJYWXmlBase
{

public:

	/*!
	@brief �������������Ϣ��ѯ
	@param[in] ywlx ҵ������
	@param[in]  Kpjh		��Ʊ����
	@param[in]  FpmxCount	��Ʊ��ϸ��
	@param[out] Fpjkmw ��Ʊ�������
	@param[out] Szjkmw ʱ�Ӽ������
	@param[out] Count �ϴ���Ʊ��ϸ����
	*/
	CSKJQljsjgqr(CYWXML_GY &ywxml_gy, string Qtxx);
	~CSKJQljsjgqr();

	/*!
	@brief ����������������������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*! 
	@brief ������������������������������XML�ļ��� 
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlParse();
	
	UINT32 m_Count;
	UINT32 m_FpCount;
	string m_Qtxx;
};


#endif



