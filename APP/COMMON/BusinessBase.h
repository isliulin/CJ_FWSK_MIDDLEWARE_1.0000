/****************************************************************************
�ļ���           ��BusinessBase.h
����             ��awe4000rҵ�����̳�����
��ʼ����         ��
����             �� 
****************************************************************************/

#ifndef BUSINESS_BASE_H
#define BUSINESS_BASE_H

#include "YWXMLGY.h"
#include "YWXmlBase.h"
#include "VersionConfig.h"
#include "DataClassDesign.h"

//ҵ�����̵��ú����ӿڷ�ʽ
#ifndef BUSINESS_JSK_MODE
#define BUSINESS_JSK_MODE	1		//ת������ʽ���ý�˰�����̽ӿ�
#endif
#ifndef BUSINESS_XML_MODE
#define BUSINESS_XML_MODE	2		//ֱ����ʽ����ͳһxml�ӿ�
#endif
#ifndef BUSINESS_TYPE_MODE
#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
// #define BUSINESS_TYPE_MODE	BUSINESS_XML_MODE
#else
#define BUSINESS_TYPE_MODE	BUSINESS_JSK_MODE
#endif
#endif

#if BUSINESS_TYPE_MODE == BUSINESS_JSK_MODE
#include "CNetPara.h"
#else
//2.25.˰���豸������Ϣ��ѯ��Ϣ���Ͷ���
#define SKSBQTYXXCX_XXLX_WLCB			0
#define SKSBQTYXXCX_XXLX_QLJS			1
#define SKSBQTYXXCX_XXLX_LXXXSC			2
#define SKSBQTYXXCX_XXLX_WLLQFP			3
#define SKSBQTYXXCX_XXLX_WLLQFPJGQR		4
#define SKSBQTYXXCX_XXLX_FPSCJGHQ		5

//˰���̱�˰����ϲ������Ͷ���
#define SKPBSP_CZLX_SJCB		1	//���ݳ���
#define SKPBSP_CZLX_QLJS		2	//�������
#define SKPBSP_CZLX_FXGPXX		3	//��д��Ʊ��Ϣ
#define SKPBSP_CZLX_JZSZ		4	//У׼˰���豸ʱ��

#define MAX_ERR_MSG_LEN			100
#endif


//���ݳ����������Ͷ���
#define SJCB_JZLX_NET			1	//����
#define SJCB_JZLX_JSP			2	//��˰��
#define SJCB_JZLX_BSP			1	//��˰��


#ifndef JSK_FAILURE
#define JSK_FAILURE		-1
#endif
#ifndef XML_FAILURE
#define XML_FAILURE				-1
#endif


class CBusinessBase;
extern CBusinessBase *g_pBusBase;


class CBusinessBase
{
public:

	static void InitBusiness();

	INT32 ErrParse(INT32 retCode, string &retMsg);

	//˰���豸��Ų�ѯ
	virtual INT32 SKSBBH_Business(CYWXML_GY &ywxml_gy, string &sksbbh, string &bspbh, string &qtxx, string &strErr)=0;

	//��˰�̱�Ų�ѯ
//	virtual INT32 BSPBH_Business(CYWXML_GY &ywxml_gy, string &bspbh, string &strErr)=0;

	//˰���豸��Ϣ��ѯ
	virtual INT32 SKPXXCX_Business(CYWXML_GY &ywxml_gy, CDataUserInfo *pUserInfo, string &strCurTime, string &strErr)=0;

	//˰���豸������Ϣ��ѯ
	virtual INT32 SKSBQTYXXCX_Business(CYWXML_GY &ywxml_gy, UINT8 xxlx, string &sksbxx, string &strErr)=0;

	//��˰����Ϣ��ѯ
	virtual INT32 BSPXXCX_Business(CYWXML_GY &ywxml_gy, CDataUserInfo *pUserInfo, string &strErr)=0;

	//������ݲ�ѯ
	virtual INT32 JKSJCX_Business(CYWXML_GY &ywxml_gy, CDataInvKind *pInvKind, string &strErr)=0;

	//��Ȩ˰�ʲ�ѯ
	virtual INT32 SQSLCX_Business(CYWXML_GY &ywxml_gy, CDataTax *pTax, UINT8 &taxNum, string &strErr)=0;

	//��Ʊ��Ϣ��ѯ
	virtual INT32 GPXXCX_Business(CYWXML_GY &ywxml_gy, CDataInvVol *pInvVol, string &strErr)=0;

	//��Ʊ��Ϣд��
	virtual INT32 GPXXXP_Business(CYWXML_GY &ywxml_gy, string gpxxmw, string &strErr)=0;

	//��Ʊ��Ϣд�̽���
	virtual INT32 GPXXXPJS_Business(CYWXML_GY &ywxml_gy, string wslpjsxx, string &strErr)=0;

	//������
	virtual INT32 KLBG_Business(CYWXML_GY &ywxml_gy, string oldPwd, string newPwd, string &strErr)=0;

	//��Ʊ����
	virtual INT32 FPKJ_Business(CYWXML_GY &ywxml_gy, CDataInvHead *pInvhead, string &strErr)=0;
	
	//��Ʊ����
	virtual INT32 FPZF_Business(CYWXML_GY &ywxml_gy, CDataInvHead *pInvhead, UINT8 zflx, string &strErr)=0;

	//��Ʊ��ѯ
	virtual INT32 FPCX_Business(CYWXML_GY &ywxml_gy, UINT8 cxfs, string cxtj, UINT32 &invNum, CDataInvHead *pInvhead, string &strErr)=0;

	//˰���豸��˰����ϲ���
	virtual INT32 SKPBSP_Business(CYWXML_GY &ywxml_gy, UINT8 czlx, string &strErr)=0;

	//��Ʊ����Ϣ��ѯ(��˰�̷�Ʊ��ѯ)
	virtual INT32 BSPFPCX_Business(CYWXML_GY &ywxml_gy, UINT32 &invNum, CDataInvVol *pInvVol, string &strErr)=0;

	//��Ʊ�ַ�
	virtual INT32 BSPFPFF_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, CDataInvVol *pInvVol, string &strErr)=0;

	//��Ʊ�ջ�
	virtual INT32 BSPFPSH_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, CDataInvVol *pInvVol, string &strErr)=0;

	//���ݳ���
	virtual INT32 SJCB_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strSQ, string &strFphz, string &strErr)=0;

	//��ػش�
	virtual INT32 JKHC_Business(CYWXML_GY &ywxml_gy, string strFpjkmw, string &strErr)=0;

	//��Ʊͳ����Ϣ��ѯ
	virtual INT32 TJXXCX_Business(CYWXML_GY &ywxml_gy, INT32 &monthcount, CDataTjxxhz *pTjxxhz, string &strErr)=0;

	//������Ϣд��
	virtual INT32 LXXXXP_Business(CYWXML_GY &ywxml_gy, string lxxxmw, string &strErr)=0;

	//��Ʊʵʱ�ϴ�
	virtual INT32 FPSC_Business(CYWXML_GY &ywxml_gy, UINT8 czlx, UINT32 &fpzx, string &strInvInfo, string &strErr)=0;

	//��Ʊ����
	virtual INT32 FPGX_Business(CYWXML_GY &ywxml_gy, string scqrbw, string &strErr)=0;

	//��Ʊ����
	virtual INT32 FPDR_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strErr)=0;

	//�ֻ��˻�
	virtual INT32 FJTH_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strErr)=0;

	//���֤�����
	virtual INT32 BGZSKL_Business(CYWXML_GY &ywxml_gy, string oldPwd, string newPwd, string &strErr)=0;


	//3.1��Ʊ�ϴ�
	virtual INT32 NETFPSC_Business(CYWXML_GY &ywxml_gy, const string &Fpmx, UINT32 Fpzs, string &Slxlh, string &strErr)=0;

	//3.2��Ʊ�ϴ������ȡ
	virtual INT32 FPSCJGHQ_Business(CYWXML_GY &ywxml_gy, string qtxx, string &Mxjgmw, string &strErr)=0;

	//3.3���糭��
	virtual INT32 WLCB_Business(CYWXML_GY &ywxml_gy, string Sq, string Fphzsj, string Qtxx, string &strErr)=0;

	//3.4�������
	virtual	INT32 QLJS_Business(CYWXML_GY &ywxml_gy, string Qtxx,string &Fpjkmw, string &strErr)=0;

	//3.5����������ȷ��
	virtual	INT32 QLJSJGQR_Business(CYWXML_GY &ywxml_gy, string Qtxx, string &strErr)=0;
	
	//3.6������Ϣ�ϴ�
	virtual INT32 NETLXXXSC_Business(CYWXML_GY &ywxml_gy, CDataInvKind *invkind, string strQtxx, string &strLzkzxx, string &strErr)=0;

	//3.7������ȡ��Ʊ
	virtual INT32 WLLQFP_Business(CYWXML_GY &ywxml_gy, CDataInvVol *pInvvol, string strQtxx, string &strErr)=0;

	//3.8������ȡ��Ʊ���ȷ��
	virtual INT32 WLLQFPJGQR_Business(CYWXML_GY &ywxml_gy, CDataInvVol *pInvvol, string strQtxx, string &strErr)=0;

	//��Ʊ��¼
	virtual INT32 FPBL_Business(CYWXML_GY &ywxml_gy, UINT32 SDate, UINT32 EDate, string &strErr)=0;
	

#if BUSINESS_TYPE_MODE == BUSINESS_JSK_MODE
	//�������ά�� -- ת����
	virtual INT32 NetPara_Business(CYWXML_GY &ywxml_gy, CDataNetPara *pNetPara, string &strErr)=0;
#endif

	//��ȡ�����������
	virtual INT32 OffInvInfo_Business(CYWXML_GY &ywxml_gy, UINT32 &wscfpzs, string &wscfpsj, INT64 &wscfpljje, string &strErr)=0;


public:
	//����δ�ϴ���Ʊ��Ϣ
	virtual INT32 UpdateUploadInv(CYWXML_GY &ywxml_gy)=0;

	//��ȫͨ�����Ӳ���
	virtual INT32 SSLConnectTest(CYWXML_GY &ywxml_gy, string &strErr)=0;
	
	//��ȡ�ϴ�����Ʊ��Ϣ 
	virtual INT32 GetErrUpInvInfo(CYWXML_GY &ywxml_gy, CDataInvServ *pDataInvServ, UINT32 &nCount, string &strErr)=0;
	
};


#endif


