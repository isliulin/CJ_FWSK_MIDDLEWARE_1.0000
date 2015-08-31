/****************************************************************************
�ļ���           ��ManageBusinessFunc.h
����             ��awe4000r����ҵ�������̺�������˰���豸��Ϣ��д��
��ʼ����         ��
����             �� 
****************************************************************************/

#ifndef MANAGE_BUSINESS_FUNC_H
#define MANAGE_BUSINESS_FUNC_H

#include "YWXMLGY.h"
#include "BusinessBase.h"
#include "DataClassDesign.h"

#if BUSINESS_TYPE_MODE == BUSINESS_JSK_MODE
#include "CNetPara.h"
#endif

class CManageBusinessFunc
{
public:
	CManageBusinessFunc();
	~CManageBusinessFunc();

public:

	/*!
	@brief ��ȡ˰���豸���		
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 GetSksbbh(CYWXML_GY &ywxml_gy, string &sksbbh, string &bspbh, string &qtxx, string &strErr);

	/*!
	@brief ��ȡ˰���豸��Ϣ		
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 GetTaxpayerInfo(CYWXML_GY &ywxml_gy, CDataUserInfo &UserInfo, string &strCurTime, string &strErr);
	
	/*!
	@brief ��ȡ��˰����Ϣ		
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 GetBSPInfo(CYWXML_GY &ywxml_gy, CDataUserInfo &userInfo, string &strErr);

	/*!
	@brief ��ȡ�������		
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 GetJKSJ(CYWXML_GY &ywxml_gy, CDataInvKind &InvKind, string &strErr);

	/*!
	@brief ��ȡ˰����Ϣ		
	@param[in] pTax ˰��������
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 GetTaxRateInfo(CYWXML_GY &ywxml_gy, CDataTax *pTax, UINT8 &taxNum, string &strErr);

	/*!
	@brief ��˰�̿�����
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 SKPKLBG(CYWXML_GY &ywxml_gy, string ykl, string xkl, string &strErr);

	/*!
	@brief ����������Ϣ		
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 LXXXUpdatePro(CYWXML_GY &ywxml_gy, string &strErr);

	/*!
	@brief ���֤�����
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 BGZSKLProc(CYWXML_GY &ywxml_gy, string yzskl, string xzskl, string &strErr);

#if BUSINESS_TYPE_MODE == BUSINESS_JSK_MODE
	/*!
	@brief �������ά��
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 NetParaManage(CYWXML_GY &ywxml_gy, CDataNetPara *pNetPara, string &strErr);
#endif

	/*!
	@brief ��ȡ�����������
	@param[in] 
	@param[out] fpzs   δ�ϴ��ķ�Ʊ����
	@param[out] fpsj   δ�ϴ���Ʊʱ�䣨��һ��δ�ϴ���Ʊ�Ŀ�Ʊ����YYYYMMDDHHMMSS��
	@param[out] fpljje δ�ϴ���Ʊ�ۼƽ�������λС����
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 GetOffLineInvInfo(CYWXML_GY &ywxml_gy, UINT32 &wscfpzs, string &wscfpsj, INT64 &wscfpljje, string &strErr);

	/*!
	@brief ����δ�ϴ���Ʊ��Ϣ
	@param[in] 
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 UpdateUploadInvInfo(CYWXML_GY &ywxml_gy);

	/*!
	@brief ��ȫͨ�����Ӳ���
	@param[in] 
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 SSLConnectTest(CYWXML_GY &ywxml_gy, string &strErr);


	/*!
	@brief �豸���
	@param[in] 
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 ClearMidDepot(string &strErr);


};


#endif


