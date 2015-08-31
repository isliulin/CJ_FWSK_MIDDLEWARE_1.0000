  /*! \file  JSKInfoFunc.h
\brief    awe4000rJSK��������
\author   zcy
\version  1.0
\date     2014-05-03
*/

#ifndef LIB_JSK_INFO_FUNC_H
#define LIB_JSK_INFO_FUNC_H


#include "IncludeMe.h"
#include "JSKInfoDef.h"
#include "VersionConfig.h"
#include "CInvHead.h"
// #include "CUserInfo.h"
// #include "CInvVol.h"
// #include "CInvKind.h"
// #include "CTax.h"
// #include "CTjxxhz.h"
#include "TDateTime.h"
#include "DataClassDesign.h"


//extern unsigned char JSK_SendBuf[];
// extern unsigned char JSK_RevBuf[];


//�����˰��ҵ��ӿڴ����붨��
typedef struct TJSKerrInfo
{
    UINT32  errID;                  //�����
	INT8  *errName;          	    //��������            
	
};


/**
*@class CJSKInfoFunc
*@brief JSK����������Ϣ
*/
class CJSKInfoFunc 
{
public:

// 	static string m_jskNo;              //��˰�̺�
public:
	/*!
		@brief new���ͺͽ���Buf
	@return
	*/
	static void JSK_NewBuf(UINT8 **pSendBuf,UINT8 **pRevBuf);
		/*!
	@brief delete���ͺͽ���Buf
	@return
	*/
	static void JSK_DelBuf(UINT8 *pSendBuf,UINT8 *pRevBuf);

	/*!
	@brief ��ʼ����˰�̺�
	@return
	*/
	//static void Set_jskNo(string jskNo) {m_jskNo.assign(jskNo);}

	/*!
	@brief ����������	
	@return  
	*/ 
	static void MutexLock(void);

	/*!
	@brief ����������	
	*/ 
	static void MutexUnlock(void);

	/*!
	@brief ��˰�̹�,���򿪲���������
    @param[in] UINT8 *Code  CA��������(9�ַ�������Ȳ���9���������0������"88888888")+��˰�̿���(9�ַ�������Ȳ���9���������0������"88888888")
	@param[in]UINT16 Size   �ַ�������
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ţ��ɹ�������0
	*/
    static INT32 JSK_Open_Proc(UINT8 *Code,UINT16 Size,string &strErr);
	/*!
	@brief ��˰�̹ؿ�������������
	@param[in] pp1 ��Ӧ���ò�ͬ��˰�̹���
	@param[in] pp2 ���pp1�����ý�˰�̹���
	@param[in] InLen �������ݵĳ���
	@param[out] OutLen �������ݵĳ���
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ţ��ɹ�������0
	*/
	static INT32 JSK_Proc(UINT8 pp1,UINT8 pp2,UINT8 *pInBuf,UINT16 InLen, UINT8 *pOutBuf,UINT16 &OutLen,string &strErr);
	
	/*!
	@brief ��˰�̹ؿ����رղ���������
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ţ��ɹ�������0
	*/
	static INT32 JSK_Close_Proc(string &strErr);
	
	/*!
	@brief ���Ҵ�����������
	@param[in] UINT32 nErrID �����
	@param[out] strErrInfo  ����������Ϣ
	@return 
	*/
	static void Find_ErrInfo(INT32 nErrID, string &strErrInfo);
	

	
	CJSKInfoFunc();
	~CJSKInfoFunc();
	
	//static string m_cakl;		//CA����
	static string m_jqbh;		//˰���տ���������
	static string m_jspkl;		//��˰�̿���
	static string m_bspkl;		//��˰�̿���
	static void set_Para(string jqbh, string jspkl, string bspkl);

	/*!
	@brief ��Ʊ����ת����˰���з�Ʊ��ϸ����
	@param[in]  CDataInvHead *pInvHead
	@param[out] UINT8 *pDataPtr,UINT32 nDataLen 
	@return 
	*/
	static void InvDetail2Data(CDataInvHead *pInvHead,UINT8 *pDataPtr,UINT32 &nDataLen);

	/*!
	@brief ��˰���з�Ʊ��ϸ����ת����Ʊ����
	@param[in] UINT8 *pDataPtr
	@param[out]  CDataInvHead *pInvHead
	@return 
	*/
	static void Data2InvDetail(INT8 *pDataPtr,CDataInvHead *pInvHead, UINT8 flag=0);

	static void ParseData(INT8 *dest);


	/*!
	@brief ��ȡ��˰����Ϣ
	@param[in] 
	@param[out]CUserInfo *pUserInfo ��˰����Ϣ
	@param[out]CDataTax *pTax ˰��
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 GetCorpInfo(CDataUserInfo *pUserInfo,CDataTax *pTax,string &strErr);


	/*!
	@brief ��ȡ��˰�̻������
	@param[in] 
	@param[out] UINT8 *JSPNo OUTBUFF[16]����˰�̻�����ţ��ַ���������"661400011858"��
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 GetJSPNo(UINT8 *JSPNo,string &strErr);

	/*!
	@brief ��ȡ��˰�̵�ǰʱ��
	@param[in] 
	@param[out] UINT8 *JSPDate ���ص�ǰʱ�� OUTBUFF[15]��YYYYMMDDHHMMSS������"20150413185600"��
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 GetJSPCurDate(UINT8 *JSPDate,string &strErr);

   /*!
	@brief ��ȡ��˰�̰汾��
	@param[in] 
	@param[out] UINT8 *JSPVer OUTBUFF[10]����˰�̰汾�ţ��ַ���������"SKN6K08K0"��
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 GetJSPVer(UINT8 *JSPVer,string &strErr);


	/*!
	@brief ��ȡ��˰������ʱ��
	@param[in] 
	@param[out] UINT8 *JSPOTime OUTBUFF[15]��YYYYMMDDHHMMSS������"20150413185600"��
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 GetJSPOpenTime(UINT8 *JSPOTime,string &strErr);

	/*!
	@brief ��ȡ��˰�����ݱ�����ʼʱ��
	@param[in] 
	@param[out] UINT8 *JSPDataSendTime  OUTBUFF[15]��YYYYMMDDHHMMSS������"20150413185600"��
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 GetJSPSendTime(UINT8 *JSPSTime,string &strErr);

	/*!
	@brief ȡ��ϣ˰��
	@param[in] 
	@param[out] UINT8 *HashNo
	@param[out]UINT8 *AddrNo
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 GetHashNo(UINT8 *HashNo,UINT8 *AddrNo,string &strErr, UINT8 HashFlag=HASH_NO_FLAG_16);

	/*!
	@brief ȡ����˰��
	@param[in] 
	@param[out] UINT8 *IssueNo
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 GetIssueNo(UINT8 *IssueNo,string &strErr);

	/*!��ȡ��һ�ŷ�Ʊ���߷�Ʊ�ķ�Ʊ���롢��Ʊ����ͷ�Ʊ������
	@brief ȡ����˰��
	@param[in] 
	@param[out] OUTBUFF��16�ֽڷ�Ʊ���루10��12λASCII�룩+4�ֽڷ�Ʊ����+4�ֽڷ�Ʊ������
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 GetFirstOffInvInfo(CDataInvHead *pInvHead,string &strErr);
	
	/*!
	@brief ��ѯ��˰���Ƿ��г�˰����
	@param[in] 
	@param[out] UINT8 uCopyFlag 0-�ޣ�1-��
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 GetJSPCopyFlag(UINT8 &uCopyFlag,string &strErr);

	/*!
	@brief ��ȡ��˰�̻������
	@param[in] 
	@param[out] UINT8 *BSPNo OUTBUFF[16]����˰�̻�����ţ��ַ���������"661400011858"��
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 GetBSPNo(UINT8 *BSPNo,string &strErr);

	/*!
	@brief ��ȡ��˰����ҵ��˰��ʶ���
	@param[in] 
	@param[out] UINT8 *BSPNsrsbh OUTBUFF[21]�����ַ���������"140301000000009"��
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 GetBSPNsrsbh(UINT8 *BSPNsrsbh,string &strErr);
	
	/*!
	@brief ��ȡ��˰�̰汾��
	@param[in] 
	@param[out] UINT8 *BSPVer OUTBUFF[10]����˰�̰汾�ţ��ַ���������"BSN6K05B"��
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 GetBSPVer(UINT8 *BSPVer,string &strErr);

	/*!
	@brief ��ȡ��˰�̿�Ʊ����
	@param[in] 
	@param[out] UINT8 *BSPNo OUTBUFF[2]��WORD���ͣ�0��ʾ��������0��ʾ�ֻ�
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 GetBSPKpjh(UINT8 *BSPKpjh,string &strErr);


	/*!
	@brief ��ȡ��˰�����߿��Ʋ���
	@param[in] 
	@param[in] CUserInfo* pUserinfo ������������
	@param[out] CInvKind invKind[]
	@param[out] UINT32 invNum
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 GetOffLimitInfo(CDataInvKind *invKind,UINT32 &invNum, string &strErr);
    static INT32 GetOffLimitInfo(UINT8 fplx, CDataInvKind *invKind,string &strErr);

    /*!
	@brief ��˰�̿�����֤  
	@param[in] UINT8* PassW,INBUFF[9] ����ǰ����ַ���������"12345678"��
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 JSPPassW(UINT8* PassW, string &strErr);

    /*!
	@brief ��˰�̿������  
	@param[in] UINT8* ModPassW,INBUFF[18] ����ǰ����(9)+�¿���(9)���ַ���������"12345678"+"87654321"��
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 JSPModPassW(UINT8* ModPassW, string &strErr);

	/*!
	@brief ֤��������  
	@param[in] UINT8* ZSPassW,INBUFF[18] ����ǰ����(9)+�¿���(9)���ַ���������"12345678"+"87654321"��
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 ZSPassW(UINT8* ZSPassW, string &strErr);

	/*!
	@brief ��˰��ע��
	@param[in] 
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 BSPRegister(string &strErr);

	/*!
	@brief ������ҵ��Ϣ  
	@param[in] UINT8* UpCorpInfo, INBUFF[] Ϊͨ������Ӵ����ȡ��Ȩ����Ϣ(����)
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 UpdateCorpInfo(UINT8* UpCorpInfo, UINT32 nLen, string &strErr);

	/*!
	@brief ��ȡ��ҵ��Ϣ  
	@param[out]UINT8* RCorpInfo, OUTBUFF[] Ϊ�ӽ�˰�̶�ȡ��Ȩ����Ϣ(����)
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 ReadCorpInfo(UINT16 &outLen, UINT8* RCorpInfo, string &strErr);

	/*!
	@brief ���÷�Ʊ�ϴ�״̬
	@param[in]  INBUFF[] Ϊͨ������Ӵ����ȡ����Ʊ�ϴ�״̬��Ϣ�������ģ�
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 SetUpLoadFlag(UINT8 *upInfo,UINT32 nLen, string &strErr);
	
	/*!
	@brief ���糭˰��Ϣ
	@param[in]  UINT8 Type Ʊ�����
	@param[out] UINT8 *StartDate  ��˰��ʼʱ��
	@param[out] UINT8 *EndDate    ��˰����ʱ��
	@param[out] UINT8 *NetTaxInfo ��˰������Ϣ
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 NetCopyTax(UINT8 Type,UINT8 *StartDate,UINT8 *EndDate,UINT8 *NetTaxInfo, UINT32 &nTaxLen, string &strErr);
    static INT32 NetCopyTaxDate(UINT8 Type,UINT8 *StartDate,UINT8 *EndDate,string &strErr);

	/*!
	@brief ��˰�̳�˰��Ϣ
	@param[in] UINT8 Type Ʊ�����
	@param[out] 
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 JSPCopyTax(UINT8 Type,string &strErr);

	/*!
	@brief ��˰�̳�˰��Ϣ
	@param[in] UINT8 Type Ʊ�����
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 BSPCopyTax(UINT8 Type,string &strErr);

	

	/*!
	@brief �����忨
	@param[in]  UINT8 Type Ʊ�����
	@param[out] UINT8 *CCardInfo �忨��Ϣ
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 NetClearCard(UINT8 Type,UINT8 *CCardInfo,UINT32 nInfoLen,string &strErr);

	/*!
	@brief ��˰���忨
	@param[in]  UINT8 Type Ʊ�����
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 BSPClearCard(UINT8 Type,string &strErr);

	
	/*!
	@brief �������繺Ʊ
	@param[in]  UINT8 Type ��Ʊ����
	@param[out] NetEmpowData OUTBU 16�ֽ����繺Ʊ������Ϣ�����ģ�
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 AppNetInvVol(UINT8 Type,UINT16 &outLen,UINT8 *NetEmpowData, string &strErr);
	
	/*!
	@brief 2�����繺Ʊ���ݶ���
	@param[in]  UINT8 Type ��Ʊ����
	@param[in]  UINT8 * NetCrypData INBUFF[144] ͨ������Ӻ�̨��ȡ�ĵ��ӷ�Ʊ���ݰ������ģ�
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 ReadNetInvVol(UINT8 Type,UINT8 *NetCrypData,string &strErr);
	

	/*!
	@brief ���繺Ʊ����ȷ������
	@param[in]  UINT8 Type ��Ʊ����
	@param[out]  UINT8 * NetCrypData OUTBUFF 40�ֽڽ�˰�����繺Ʊ����ȷ�����ݰ������ģ�
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 App2NetInvVol(UINT8 Type,UINT16 &outLen,UINT8 *NetCrypData,CDataInvVol *invVol,string &strErr);

	/*!
	@brief ���繺Ʊȷ��
	@param[in]  UINT8 * NetCrypData NBUFF ͨ������Ӻ�̨��ȡ��40�ֽ����繺Ʊȷ�����ݰ������ģ�
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 ConNetInvVol(UINT8 Type, UINT8 *NetCrypData,string &strErr);

	/*!
	@brief �ӽ�˰�̶����¹���Ʊ
	@param[in]  UINT8 Type Ʊ�����
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 JSPGetInvVolInfo(UINT8 Type,string &strErr);

	/*!
	@brief �ӱ�˰�̶����¹���Ʊ
	@param[in]  UINT8 Type Ʊ�����
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 BSPGetInvVolInfo(UINT8 Type,string &strErr);

	
	/*!
	@brief ��ȡ����ƱԴ��Ϣ
	@param[in] 
	@param[out] CInvVol *pInvVol
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 GetJSKInvVolInfo(CDataInvVol *invVol,UINT32 &nInvNum,string &strErr);
	
/*!
	@brief ��Ʊ(��Ʊ,��Ʊ,�հ�����)
	@param[in] ��Ʊ��Ϣ CDataInvHead *pInvHead
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 MakeInvHandInfo(CDataInvHead *pInvHead , string &strErr);
	
	
	/*!
	@brief �ѿ���Ʊ����(����,���)
	@param[in] CDataInvHead *pInvHead 
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 WasteInvHandInfo(CDataInvHead *pInvHead ,string &strErr);
	
	/*!
	@brief ��ȡ��ǰ��Ʊ��
	@param[in] 
	@param[out] CInvVol *pInvVol
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 GetCurInvInfo(CDataInvVol *pInvVol,string &strErr);

	/*!
	@brief  ȡ��ˮ��
	@param[in] 
	@param[out] UINT8 *RunNo
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
    static INT32 GetRunNoInfo(UINT8 *RunNo,string &strErr);
	

	 /*!
	@brief ���ֻ���˰�̷�Ʊ
	@param[in] CInvVol *pInvVol
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 HostToInvBSP(CDataInvVol *pInvVol, string &strErr);

	 /*!
	@brief ���ֻ���˰�̷�Ʊ
	@param[in] CInvVol *pInvVol
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 HostToInvJSP(CDataInvVol *pInvVol, string &strErr);


	 /*!
	@brief �ñ�˰���˻�
	@param[in] CInvVol *pInvVol
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 InvVolRetBSP(CDataInvVol *pInvVol,string &strErr);

		 /*!
	@brief �ý�˰���˻�
	@param[in] CInvVol *pInvVol
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 InvVolRetJSP(CDataInvVol *pInvVol,string &strErr);

	 /*!
	@brief ��������ֻ���˰���˻ط�Ʊ
	@param[in] UINT8 Type ��Ʊ����
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 HostGetInvBSP(UINT8 Type,string &strErr);

	/*!
	@brief ��������ֻ���˰���˻ط�Ʊ
	@param[in] UINT8 Type ��Ʊ����
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 HostGetInvJSP(UINT8 Type,string &strErr);

	/*!
	@brief ��ȡ��������
	@param[in] UINT8 Type ��Ʊ����
	@param[out] UINT8 *pLockDate  OUTBUFF[9]��YYYYMMDD������"20150520"��
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 GetLockDate(UINT8 Type,UINT8 *pLockDate,string &strErr);

	/*!
	@brief ��Ʊ��ѯ
	@param[in] CDataInvHead *pInvHead  INBUFF[24]  unsigned int��Ʊ��ʼ��;16B��Ʊ����; unsigned int��Ʊ�����ţ���ѡ�����ϲ����ݿ��޴��ֶΣ����4�ֽ�0xFF��
	@param[out]  CDataInvHead *pInvHead  ��ѯ�ķ�Ʊ��Ϣ
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 GetInvDetailInfoNO(CDataInvHead *pInvHead,string &strErr);
	static INT32 GetInvDetailInfoNO(CDataInvHead *pInvHead, UINT8 *invBuff, UINT32 &invLen, string &strErr);


	/*!
	@brief ��Ʊ��ѯ
	@param[in]UINT8 *chDate  ��ѯ����6λ�����£�201505
    @param[out]  uInvFlag  1�ֽڽ��պ�����Ʊ��־������1��ʾ�к�����Ʊ��Ҫ���գ�����0��ʾ�ޣ�+���ŷ�Ʊ��ϸ
     @param[out]  CDataInvHead *pInvHead  ��ѯ�ķ�Ʊ��Ϣ
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 GetInvDetailInfoDate(UINT8 *chDate,CDataInvHead *pInvHead,UINT8 &uInvFlag,string &strErr);


	/*!
	@brief ��Ʊ��ѯ
	@param[in]   UINT32 iDate  ��ѯ����6λ�����£�201505
    @param[out]  FpType  ��Ҫ��ѯ�ķ�Ʊ����
     @param[out] CTjxxhz *pTjxxhz ��ѯ�ķ�Ʊ��Ϣ
	@param[out] string &strErr ������Ϣ
	@return ������ɹ������ش���ż������������ɹ�������JSK_SUCCESS
	*/
	static INT32 GetMonthCountDate(UINT32 iDate,UINT8 FpType,CDataTjxxhz *pTjxxhz,string &strErr);


	static void ParseInvCode(string str, string &fpdm, UINT32 &fphm);
};


#endif



