/****************************************************************************
�ļ���           ��InvBusinessFunc.h
����             ��awe4000r��Ʊҵ�������̺������������ֻ���Ʊ����
��ʼ����         ��
����             �� 
****************************************************************************/

#ifndef INV_BUSINESS_FUNC_H
#define INV_BUSINESS_FUNC_H

#include "YWXMLGY.h"
#include "DataClassDesign.h"

class CInvBusinessFunc
{
public:
	CInvBusinessFunc();
	~CInvBusinessFunc();


	/*!
	@brief ��˰�̷�Ʊ��ѯ����Ʊ����Ϣ��ѯ��
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 BSPFPCXPro(CYWXML_GY &ywxml_gy, UINT32 &InvCount, CDataInvVol *pInvVol, string &strErr);


	/*!
	@brief ��Ʊ�ַ�����������Ʊ�ַ����ֻ����豣֤����˰���豸ͬʱ���ӿ����
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 ZJInvDistribute(CYWXML_GY &ywxml_gy, CDataInvVol *pInvVol, UINT8 strJzlx, string &strErr);

	/*!
	@brief ��Ʊ�˻أ��ֻ�����Ʊ��ƱԴ�˻ظ���˰����
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 ZJInvRecover(CYWXML_GY &ywxml_gy, CDataInvVol *pInvVol, UINT8 strJzlx, string &strErr);

	/*!
	@brief ��Ʊ�ջأ��������ֻ���˰���ķ�Ʊ�����Լ���ƱԴ�����豣֤����˰���豸ͬʱ���ӿ����
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 FJInvReturn(CYWXML_GY &ywxml_gy, UINT8 strJzlx, string &strErr);

	/*!
	@brief ͳ����Ϣ��ѯ
	@param[in/out] pTjxxhz ͳ����Ϣ������
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 TJXXCXPro(CYWXML_GY &ywxml_gy, INT32 &monthcount, CDataTjxxhz *pTjxxhz, string &strErr);


	/*!
	@brief ���ʹ�Ʊ(��Ʊ����)
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 InvReadIn(CYWXML_GY &ywxml_gy, UINT8 strJzlx, string &strErr);

	/*!
	@brief ������ȡ��Ʊ�������������繺Ʊ�󣬵��ý��ʹ�Ʊ���룩
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 WLLQFPPro(CYWXML_GY &ywxml_gy, CDataInvVol *pInvVol, string &strErr);

	/*!
	@brief ������ȡ��Ʊ���ȷ�ϣ�������
	@param[in] 
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	INT32 WLLQFPJGQRPro(CYWXML_GY &ywxml_gy, CDataInvVol *pInvVol, string &strErr);


};


#endif


