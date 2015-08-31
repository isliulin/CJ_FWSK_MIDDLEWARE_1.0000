/****************************************************************************
�ļ���           ��DeclareBusinessFunc.h
����             ��awe4000r����ҵ�������̺�����
��ʼ����         ��
����             �� 
****************************************************************************/

#ifndef DECLARE_BUSINESS_FUNC_H
#define DECLARE_BUSINESS_FUNC_H

#include "YWXMLGY.h"

class CDeclareBusinessFunc
{
public:
	CDeclareBusinessFunc();
	~CDeclareBusinessFunc();

public:

	/*!
	@brief ���糭��
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 NetDeclareProc(CYWXML_GY &ywxml_gy, string &strErr);

	/*!
	@brief ���ʳ���������ʱ��ʾѡ���˰�̻��߱�˰�̣�
	@param[in] jzlx ��������  1����˰�� 2����˰�� 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 DeclareProc(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strErr);

	/*!
	@brief �����忨
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 NetUpdateTaxProc(CYWXML_GY &ywxml_gy, string &strErr);

	/*!
	@brief ��˰���忨
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 UpdateTaxProc(CYWXML_GY &ywxml_gy, string &strErr);

};


#endif


