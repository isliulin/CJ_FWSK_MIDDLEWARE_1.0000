/*! \file    NETXML_FPSCJGHQ.h
   \brief    ������õ��м���ӿ� ҵ��: ��Ʊ��ϸ�ϴ������ȡ
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef SKJ_NETXML_FPSCJGHQ_H
#define SKJ_NETXML_FPSCJGHQ_H

#include "IncludeMe.h"
#include "SKJYWXmlBase.h"


/**
 *@class CFpscjghq
 *@brief ��Ʊ��ϸ�ϴ������ȡ
 */
class CSKJFpscjghq: public CSKJYWXmlBase
{

public:


	/*!
	@brief ��Ʊ��ϸ�ϴ������ȡ
	@param[in] ywlx ҵ������
	@param[in]  FpmxCount	��Ʊ��ϸ��
	@param[out] Mxjgmw ���ܺ����ϸ�ϴ�������� 
	@param[out] Count �ϴ���Ʊ��ϸ����
	*/
	CSKJFpscjghq(CYWXML_GY &ywxml_gy, string qtxx, string &Mxjgmw);
	~CSKJFpscjghq();
	
	/*!
	@brief ��Ʊ��ϸ�ϴ������ȡ�����������װ����װ��XML�ļ���
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*! 
	@brief ��Ʊ��ϸ�ϴ������ȡ�������������������XML�ļ��� 
	@param[out] Mxjgmw ���ܺ����ϸ�ϴ�������� 
	@param[out] Count �ϴ���Ʊ��ϸ����
	@return 1 SUCCESS�� 0 FAILURE 
	*/
	INT32 XmlParse();
	
	string &m_Mxjgmw;
	UINT32 m_Count;
	UINT32 m_FpCount;
	string m_Slxlh;
	string m_Qtxx;
};


#endif



