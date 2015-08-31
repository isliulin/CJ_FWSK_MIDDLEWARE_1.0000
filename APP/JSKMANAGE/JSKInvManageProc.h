/*! \file  JSKManageProc.h
\brief    awe4000r ��Ʊ��������
\author   zfj
\version  1.0
\date     2015-04-16
*/

#ifndef LIB_JSK_INV_MANAGE_PROC_H
#define LIB_JSK_INV_MANAGE_PROC_H

#include "JSKManageProc.h"
#include "IncludeMe.h"
#include "JSKInfoDef.h"
#include "JSKInfoFunc.h"
#include "DataClassDesign.h"

/**
*@class CJSKInvManageProc
*@brief ˰���豸��Ϣ��ѯ��������
*/
class CJSKInvManageProc  
{
	
public:

	CJSKInvManageProc();
	~CJSKInvManageProc();

	/*!
	@brief 2.7.��Ʊ��Ϣд��
	@param[in] fplxdm ��Ʊ���ʹ���
	@param[in] gpxxmw ��Ʊ��Ϣ����
	@param[out] strErr   ������Ϣ
	@return  
	*/
	static INT32 GPXXXP_Proc(string fplxdm, string gpxxmw, string &strErr);
	
	/*!
	@brief 2.8.��Ʊ��Ϣд�̽���
	@param[in] fplxdm ��Ʊ���ʹ���
	@param[in] wslpjsxx ������Ʊ������Ϣ
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 GPXXXPJS_Proc(string fplxdm, string wslpjsxx, string &strErr);


	/*!
	@brief 2.14.��˰�̷�Ʊ��ѯ
	@param[in] fplxdm ��Ʊ���ʹ���
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 BSPFPCX_Proc(string fplxdm, UINT32 &invNum, CDataInvVol *pInvVol, string &strErr);

	/*!
	@brief 2.15.��Ʊ�ַ�
	@param[in] jzlx ��������
	@param[in] pInvVol ��Ʊ��Ϣ��
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 BSPFPFF_Proc(UINT8 jzlx, CDataInvVol *pInvVol, string &strErr);

	/*!
	@brief 2.16.��Ʊ�ջ�
	@param[in] jzlx ��������
	@param[in] pInvVol ��Ʊ��Ϣ��
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 BSPFPSH_Proc(UINT8 jzlx, CDataInvVol *pInvVol, string &strErr);

	/*!
	@brief 2.23.��Ʊ����
	@param[in] jzlx ��������
	@param[in] fplxdm ��Ʊ���ʹ���
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 FPDR_Proc(UINT8 jzlx, string fplxdm, string &strErr);

	/*!
	@brief 2.24.�ֻ��˻�
	@param[in] jzlx ��������
	@param[in] fplxdm ��Ʊ���ʹ���
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 FJTH_Proc(UINT8 jzlx, string fplxdm, string &strErr);

	/*!
	@brief 2.19.��Ʊͳ����Ϣ��ѯ
	@param[in] strFplxdm ��Ʊ���ʹ���
	@param[in/out] pTjxxhz ͳ����Ϣ������
	@param[out] MonthCount ��ѯ����
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 TJXXCX_Proc(string strFplxdm, INT32 &MonthCount, CDataTjxxhz *pTjxxhz, string &strErr);

	

	/*!
	@brief ��Ʊ����ת����Ʊ���ʹ���
	@param[in]	fplx	��Ʊ����
	@param[out] fpzldm	��Ʊ���ʹ���
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 fplx2fplxdm(UINT8 fplx, string &fplxdm);

	/*!
	@brief ��Ʊ���ʹ���ת����Ʊ����
	@param[in] fpzldm	��Ʊ���ʹ���
	@param[out]	fplx	��Ʊ����
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 fplxdm2fplx(string fplxdm, UINT8 &fplx);

};


#endif



