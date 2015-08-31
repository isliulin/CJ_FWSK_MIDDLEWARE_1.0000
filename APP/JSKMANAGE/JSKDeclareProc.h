/*! \file  JSKDeclareProc.h
\brief    awe4000r ���ݳ�������ػش�
\author   zfj
\version  1.0
\date     2015-04-16
*/

#ifndef LIB_JSK_DECLARE_PROC_H
#define LIB_JSK_DECLARE_PROC_H

#include "JSKManageProc.h"
#include "IncludeMe.h"
#include "JSKInfoDef.h"
#include "JSKInfoFunc.h"


/**
*@class CJSKDeclareProc
*@brief ˰���豸��Ϣ��ѯ��������
*/
class CJSKDeclareProc  
{
	
public:

	CJSKDeclareProc();
	~CJSKDeclareProc();

	/*!
	@brief ���ݳ���
	@param[in] fplxdm ��Ʊ���ʹ���
	@param[out] sqBuff ����
	@param[out] fphzBuff  ����������Ϣ
	@param[out] strErr   ������Ϣ
	@return  
	*/
	//static INT32 SJCB_Proc(string fplxdm, UINT8 *sqBuff, UINT8 *fphzBuff, string &strErr);
	static INT32 SJCB_Proc(string fplxdm, UINT8 jzlx, string &strSQ, string &strFphz, string &strErr);
	
	/*!
	@brief ��ػش�
	@param[in] fplxdm ��Ʊ���ʹ���
	@param[in] strFpjkmw 128�ֽ��忨���ݣ����ģ�
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 JKHC_Proc(string fplxdm, string strFpjkmw, string &strErr);

	/*!
	@brief ˰���豸��˰����ϲ���
	@param[in] fplxdm ��Ʊ���ʹ���
	@param[in] czlx ��������
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 SKPBSP_Proc(string fplxdm, UINT8 czlx, string &strErr);

	static INT32 DeclareAuthority(string &strErr);


	static INT32 DelUploadInv();


};


#endif



