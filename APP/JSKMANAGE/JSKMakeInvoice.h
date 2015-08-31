/*! \file  JSKMakeInvoice.h
\brief    awe4000r �м��������  ��Ʊ����������� 2.10 ~ 2.12  2.21 ~ 2.22
\author   zfj
\version  1.0
\date     2015-04-16
*/

#ifndef LIB_JSK_MAKE_INVOICE_H
#define LIB_JSK_MAKE_INVOICE_H

#include "JSKManageProc.h"
#include "IncludeMe.h"
#include "CInvHead.h"
#include "CInvServ.h"
#include "CRtInv.h"
#include "DataClassDesign.h"

#define XML_FPSCJGHQ_FILE		"fqscjghq.xml"
#define XML_FILE_NAME_CGLPLBL	"CGLPLBL_"
#define XML_FILE_NAME_KFSBM		"ZZ_"				//��Ʊ��������̱���
#define XML_FILE_NAME_ENCODE	"9999_"				//4λ�ӽ����㷨�汾��

//��Ʊ�ϴ���־
#define INV_UPLOAD_FLAG0	0		//δ�ϴ�
#define INV_UPLOAD_FLAG1	1		//���ϴ���δ���ؽ���ɹ�
#define INV_UPLOAD_FLAG2	2		//�ϴ���Ʊ����

typedef struct _JSKInvDet
{
	string m_spbm;			/**< ��Ʒ���� */
	string m_spmc;			/**< ��Ʒ���� */
	double m_spdj;			/**< ��Ʒ����(Ԫ������2λС��) */
	double m_spsl;			/**< ��Ʒ���� �Ǹ���*/
	INT64  m_spje;			/**< ��Ʒ���(��) ���ۿ��н��Ϊ����*/
	UINT8  m_property;		/**< ��Ʒ������ 0:һ����Ʒ�У�1:�ۿ���*/
}JSKInvDet;

typedef struct _JSKInvHead
{
	string m_fpdm;			/**< ��Ʊ���� */
	UINT32 m_fphm;			/**< ��Ʊ���� */
	UINT32 m_kprq;			/**< ��Ʊ���� */
	UINT32 m_kpsj;			/**< ��Ʊʱ�� */

	UINT8  m_kplx;			/**< ��Ʊ���� 1-��Ʊ 2-��Ʊ 3-�հ׷�*/
	INT64  m_kphjje;			/**< ��Ʊ�ϼƽ��(��)���Ǹ��� */
	string m_yfpdm;			/**< ԭ��Ʊ���� */
	UINT32 m_yfphm;			/**< ԭ��Ʊ���� */

	string m_fkdw;			/**< ���λ */
	string m_payerCode;     /**< ���λ˰��ʶ��� */
	string m_sky;			/**< �տ�Ա */
	UINT32 m_sphsl;			/**< ��Ʒ������ �Ǹ���*/

	string  m_fwm;			/**< ��α˰���� */
	string m_backup1;		/**< ����1 */

	JSKInvDet m_invDet[6];		/**< ��Ʒ����Ϣ���� */
} JSKInvHead;

/**
*@class CJSKMakeInvoice
*@brief ����Ʊ����
*/
class CJSKMakeInvoice  
{
	
public:

	CJSKMakeInvoice();
	~CJSKMakeInvoice();

	
	/*!
	@brief ��ȡ��ǰƱ��		
	@param[in] 
	@param[out] pInvVol  ��Ʊ��Ϣ��
	@param[out] strErr   ������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 GPXXCX_Proc(CDataInvVol *pInvVol, string &strErr);

	/*!
	@brief ��Ʊ��������Ʊ����Ʊ��		
	@param[in] invhead			��Ʊͷ��Ϣ
	@param[out] taxCode   	˰���루20�ֽڣ�
	@param[out] strErr   		������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 FPKJ_Proc(CDataInvHead *pInvHead, string &strErr, UINT8 wasteflag=0);

	/*!
	@brief ��Ʊ���հ׷�Ʊ���ѿ�Ʊ���ϣ�
	@param[in] invhead	��Ʊͷ��Ϣ
	@param[in] zflx   ��������	0���հ׷�Ʊ����	1���ѿ���Ʊ����
	@param[out] strErr   		������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 FPZF_Proc(CDataInvHead *pInvHead, UINT8 zflx, string &strErr);

	/*!
	@brief ��Ʊ��ѯ
	@param[in] cxfs	��ѯ��ʽ
	@param[in] cxtj	��ѯ����
	@param[out] invNum  ��Ʊ����
	@param[in/out] invhead	��Ʊͷ��Ϣ
	@param[out] strErr   		������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 FPCX_Proc(UINT8 cxfs, string cxtj, UINT32 &invNum, CDataInvHead *pInvHead, string &strErr);

	/*!
	@brief ��Ʊʵʱ�ϴ�
	@param[in/out] fpzx	��Ʊ����
	@param[out] strInvInfo	��Ʊ��ϸ
	@param[out] strErr   		������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 FPSC_Proc(UINT8 czlx, UINT32 &fpzx, string &strInvInfo, string &strErr);

	/*!
	@brief ��Ʊ����
	@param[in] invhead	��Ʊͷ��Ϣ
	@param[out] strErr   		������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 FPGX_Proc(string scqrbw, string &strErr);

	/*!
	@brief ��Ʊ��¼
	@param[in] nsrsbh  ��˰��ʶ���
	@param[in] sksbbh  ˰���豸���
	@param[in] SDate  ��ʼ����
	@param[in] EDate  ��ֹ����
	@param[out] strErr   		������Ϣ
	@return  1 SUCCESS�� 0  FAILURE
	*/
	static INT32 FPBL_Proc(string nsrsbh, string sksbbh, UINT32 SDate, UINT32 EDate, string &strErr);


	/*!
	@brief ��Ʊ����ת����˰���з�Ʊ��ϸ����
	@param[in]  CInvHead *pInvHead
	@param[out] UINT8 *pDataPtr,UINT32 nDataLen 
	@return 
	*/
	static void AddInvDetail2Data(CDataInvHead *pInvHead,UINT8 *pDataPtr,UINT32 &nDataLen);
	static void Str2InvHead(INT8 *pDataPtr,CDataInvHead *pInvHead);

	/*!
	@brief �����ַ���ǰ����Ŀո�
	@param[in/out] str
	@return 
	*/
	static void FilterSpace(string &str);

	/*!
	@brief ��ȡ�ϴ�����Ʊ��Ϣ
	@param[in/out] str
	@return 
	*/
	static INT32 GetErrUpInv(CDataInvServ *pDataInvServ, UINT32 &nCount, string &strErr);

private:

	/*!
	@brief ��ƱȨ�޿���
	@param[in]  kplx ��Ʊ����
	@param[in]  nSum ��Ʊ���
	@param[out] 
	@return 
	*/
	static INT32 MakeInvAuthority(CDataInvHead *pInvHead, string& strErr);

	static INT32 ParseFpscjg(string scqrbw, string &mxjgmw, string &strErr);
	
};


#endif



