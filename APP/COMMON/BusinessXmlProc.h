/****************************************************************************
�ļ���           ��BusinessBase.h
����             ��awe4000rҵ�����̳�Ѫ��
��ʼ����         ��
����             �� 
****************************************************************************/

#ifndef BUSINESS_XML_PROC_H
#define BUSINESS_XML_PROC_H

#include "BusinessBase.h"

#if BUSINESS_TYPE_MODE == BUSINESS_XML_MODE

class CBusinessXmlProc : public CBusinessBase
{
public:

	CBusinessXmlProc();
	~CBusinessXmlProc();

	//˰���豸��Ų�ѯ
	INT32 SKSBBH_Business(CYWXML_GY &ywxml_gy, string &sksbbh, string &bspbh, string &qtxx, string &strErr);
	
	//��˰�̱�Ų�ѯ
//	INT32 BSPBH_Business(CYWXML_GY &ywxml_gy, string &bspbh, string &strErr);
	
	//˰���豸��Ϣ��ѯ
	INT32 SKPXXCX_Business(CYWXML_GY &ywxml_gy, CDataUserInfo *pUserInfo, string &strCurTime, string &strErr);
	
	//˰���豸������Ϣ��ѯ
	INT32 SKSBQTYXXCX_Business(CYWXML_GY &ywxml_gy, UINT8 xxlx, string &sksbxx, string &strErr);
	
	//��˰����Ϣ��ѯ
	INT32 BSPXXCX_Business(CYWXML_GY &ywxml_gy, CDataUserInfo *pUserInfo, string &strErr);
	
	//������ݲ�ѯ
	INT32 JKSJCX_Business(CYWXML_GY &ywxml_gy, CDataInvKind *pInvKind, string &strErr);
	
	//��Ȩ˰�ʲ�ѯ
	INT32 SQSLCX_Business(CYWXML_GY &ywxml_gy, CDataTax *pTax, UINT8 &taxNum, string &strErr);
	
	//��Ʊ��Ϣ��ѯ
	INT32 GPXXCX_Business(CYWXML_GY &ywxml_gy, CDataInvVol *pInvVol, string &strErr);
	
	//��Ʊ��Ϣд��
	INT32 GPXXXP_Business(CYWXML_GY &ywxml_gy, string gpxxmw, string &strErr);
	
	//��Ʊ��Ϣд�̽���
	INT32 GPXXXPJS_Business(CYWXML_GY &ywxml_gy, string wslpjsxx, string &strErr);
	
	//������
	INT32 KLBG_Business(CYWXML_GY &ywxml_gy, string oldPwd, string newPwd, string &strErr);
	
	//��Ʊ����
	INT32 FPKJ_Business(CYWXML_GY &ywxml_gy, CDataInvHead *pInvhead, string &strErr);
	
	//��Ʊ����
	INT32 FPZF_Business(CYWXML_GY &ywxml_gy, CDataInvHead *pInvhead, UINT8 zflx, string &strErr);
	
	//��Ʊ��ѯ
	INT32 FPCX_Business(CYWXML_GY &ywxml_gy, UINT8 cxfs, string cxtj, UINT32 &invNum, CDataInvHead *pInvhead, string &strErr);
	
	//˰���豸��˰����ϲ���
	INT32 SKPBSP_Business(CYWXML_GY &ywxml_gy, UINT8 czlx, string &strErr);
	
	//��Ʊ����Ϣ��ѯ(��˰�̷�Ʊ��ѯ)
	INT32 BSPFPCX_Business(CYWXML_GY &ywxml_gy, UINT32 &invNum, CDataInvVol *pInvVol, string &strErr);
	
	//��Ʊ�ַ�
	INT32 BSPFPFF_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, CDataInvVol *pInvVol, string &strErr);
	
	//��Ʊ�ջ�
	INT32 BSPFPSH_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, CDataInvVol *pInvVol, string &strErr);
	
	//���ݳ���
	INT32 SJCB_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strSQ, string &strFphz, string &strErr);
	
	//��ػش�
	INT32 JKHC_Business(CYWXML_GY &ywxml_gy, string strFpjkmw, string &strErr);
	
	//��Ʊͳ����Ϣ��ѯ
	INT32 TJXXCX_Business(CYWXML_GY &ywxml_gy, INT32 &monthcount, CDataTjxxhz *pTjxxhz, string &strErr);
	
	//������Ϣд��
	INT32 LXXXXP_Business(CYWXML_GY &ywxml_gy, string lxxxmw, string &strErr);
	
	//��Ʊʵʱ�ϴ�
	INT32 FPSC_Business(CYWXML_GY &ywxml_gy, UINT8 czlx, UINT32 &fpzx, string &strInvInfo, string &strErr);
	
	//��Ʊ����
	INT32 FPGX_Business(CYWXML_GY &ywxml_gy, string scqrbw, string &strErr);
	
	//��Ʊ����
	INT32 FPDR_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strErr);
	
	//�ֻ��˻�
	INT32 FJTH_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strErr);
	
	//���֤�����
	INT32 BGZSKL_Business(CYWXML_GY &ywxml_gy, string oldPwd, string newPwd, string &strErr);

	//3.1��Ʊ�ϴ�
	INT32 NETFPSC_Business(CYWXML_GY &ywxml_gy, const string &Fpmx, UINT32 Fpzs, string &Slxlh, string &strErr);
	
	//3.2��Ʊ�ϴ������ȡ
	INT32 FPSCJGHQ_Business(CYWXML_GY &ywxml_gy, string qtxx, string &Mxjgmw, string &strErr);
	
	//3.3���糭��
	INT32 WLCB_Business(CYWXML_GY &ywxml_gy, string Sq, string Fphzsj, string Qtxx, string &strErr);
	
	//3.4�������
	INT32 QLJS_Business(CYWXML_GY &ywxml_gy, string Qtxx,string &Fpjkmw, string &strErr);
	
	//3.5����������ȷ��
	INT32 QLJSJGQR_Business(CYWXML_GY &ywxml_gy, string Qtxx, string &strErr);
	
	//3.6������Ϣ�ϴ�
	INT32 NETLXXXSC_Business(CYWXML_GY &ywxml_gy, CDataInvKind *invkind, string strQtxx, string &strLzkzxx, string &strErr);
	
	//3.7������ȡ��Ʊ
	INT32 WLLQFP_Business(CYWXML_GY &ywxml_gy, CDataInvVol *pInvvol, string strQtxx, string &strErr);
	
	//3.8������ȡ��Ʊ���ȷ��
	INT32 WLLQFPJGQR_Business(CYWXML_GY &ywxml_gy, CDataInvVol *pInvvol, string strQtxx, string &strErr);
	
	//��Ʊ��¼
	INT32 FPBL_Business(CYWXML_GY &ywxml_gy, UINT32 SDate, UINT32 EDate, string &strErr);
	
public:
	//����δ�ϴ���Ʊ��Ϣ
	INT32 UpdateUploadInv(CYWXML_GY &ywxml_gy);

	//��ȫͨ�����Ӳ���
	INT32 SSLConnectTest(CYWXML_GY &ywxml_gy, string &strErr);

	//��ȡ�����������
	INT32 OffInvInfo_Business(CYWXML_GY &ywxml_gy, UINT32 &wscfpzs, string &wscfpsj, INT64 &wscfpljje, string &strErr);

	//2.29.��ȡ�ϴ�����Ʊ��Ϣ
	INT32 GetErrUpInvInfo(CYWXML_GY &ywxml_gy, CDataInvServ *pDataInvServ, UINT32 &nCount, string &strErr);
};

#endif
#endif


