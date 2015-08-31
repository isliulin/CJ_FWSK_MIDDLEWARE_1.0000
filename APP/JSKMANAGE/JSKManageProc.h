/*! \file  JSKManageProc.h
\brief    awe4000r ˰���豸��Ϣ��ѯ��������  2.1 ~ 2.5  2.9
\author   zfj
\version  1.0
\date     2015-04-16
*/

#ifndef LIB_JSK_MANAGE_PROC_H
#define LIB_JSK_MANAGE_PROC_H

#include "IncludeMe.h"
#include "JSKInfoDef.h"
#include "JSKInfoFunc.h"

#include "CUserInfo.h"
#include "CInvKind.h"
#include "CTax.h"
#include "CNetPara.h"
#include "DataClassDesign.h"

/**
*@class CJSKManageProc
*@brief ˰���豸��Ϣ��ѯ��������
*/
class CJSKManageProc  
{
	
public:

	CJSKManageProc();
	~CJSKManageProc();

	static void set_JSKPara(string jqbh, string sksbkl, string bspkl);

	/*!
	@brief ˰���豸��Ų�ѯ
	@param[in] 
	@param[out] sksbbh ˰���豸���
	@param[out] strErr   ������Ϣ
	@return  
	*/
	static INT32 SKSBBH_Proc(string &sksbbh, string &strErr);
	
	/*!
	@brief ��˰�̱�Ų�ѯ
	@param[in] 
	@param[out] sksbbh ˰���豸���
	@param[out] bspbh  ��˰�̱��
	@param[out] strErr   ������Ϣ
	@return  
	*/
	static INT32 BSPBH_Proc(string &bspbh, string &strErr);
	
	/*!
	@brief ˰���豸��Ϣ��ѯ
	@param[in] 
	@param[out] pUserInfo ��˰����Ϣ
	@param[out] strCurTime ����ʱ��
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 SKPXXCX_Proc(CDataUserInfo *pUserInfo, string &strCurTime, string &strErr);

	/*!
	@brief ��˰����Ϣ��ѯ
	@param[in] 
	@param[out] 
	@param[out] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 BSPXXCX_Proc(CDataUserInfo *pUserInfo, string &strErr);

	/*!
	@brief ������ݲ�ѯ
	@param[in] 
	@param[out] pUserInfo
	@param[out] pInvKind
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 JKSJCX_Proc(CDataInvKind *pInvKind, string &strErr);

	/*!
	@brief ��Ȩ˰�ʲ�ѯ
	@param[out] pTax ˰����Ϣ
	@param[out] taxNum	˰�ʸ���
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 SQSLCX_Proc(CDataTax *pTax, UINT8 &taxNum, string &strErr);

	/*!
	@brief ������
	@param[in] oldPwd ������
	@param[in] newPwd ������
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 KLBG_Proc(string oldPwd, string newPwd, string &strErr);

	/*!
	@brief ���֤�����
	@param[in] oldPwd ������
	@param[in] newPwd ������
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 BGZSKL_Proc(string oldPwd, string newPwd, string &strErr);

	/*!
	@brief 2.20.������Ϣд��
	@param[in] lxxxmw ������Ϣ����
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 LXXXXP_Proc(string lxxxmw, string &strErr);


	/*!
	@brief ˰���豸������Ϣ��ѯ
	@param[in] xxlx ��Ϣ����	0�������˰���豸��ϢΪ3.2��Ʊ�ϴ������ȡ�ӿڵ�������"������Ϣ"
	@param[in]					1�������˰���豸��ϢΪ3.3���糭˰�ӿں�3.4���������������"������Ϣ"
	@param[in]					2�������˰���豸��ϢΪ3.5������Ϣ�ϴ��ӿڵ�������"������Ϣ"
	@param[in]					3�������˰���豸��ϢΪ3.6������ȡ��Ʊ�ӿڵ�������"������Ϣ"
	@param[in]					4�������˰���豸��ϢΪ3.7������ȡ��Ʊȷ�Ͻӿڵ�������"������Ϣ"
	@param[out] sksbxx ˰���豸��Ϣ
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 SKSBQTYXXCX_Proc(string fplxdm, UINT8 xxlx, string &sksbxx, string &strErr);

	/*!
	@brief ��ȡ��ϣ˰��
	@param[in] strHxsh ��ϣ˰��
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 GetHashTaxNo(UINT8 HashFlag, string &strErr);

	/*!
	@brief ��ȡ����˰��
	@param[in] strFxsh ����˰��
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 GetIssueTaxNo(string &strErr);

	static void Transformfplx(UINT32 nCount, string &strMsg);


	/*!
	@brief �������ά��
	@param[in] pNetPara ���������
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 NetPara_Proc(CDataNetPara *pNetPara, string &strErr);

	/*!
	@brief ��ȡ�����������
	@param[out] fpzs   δ�ϴ��ķ�Ʊ����
	@param[out] fpsj   δ�ϴ���Ʊʱ�䣨��һ��δ�ϴ���Ʊ�Ŀ�Ʊ����YYYYMMDDHHMMSS��
	@param[out] fpljje δ�ϴ���Ʊ�ۼƽ�������λС����
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 OffInvInfo_Proc(UINT32 &wscfpzs, string &wscfpsj, INT64 &wscfpljje, string &strErr);
};


#endif



