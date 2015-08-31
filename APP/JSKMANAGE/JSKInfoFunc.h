  /*! \file  JSKInfoFunc.h
\brief    awe4000rJSK操作函数
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


//款机金税盘业务接口错误码定义
typedef struct TJSKerrInfo
{
    UINT32  errID;                  //错误号
	INT8  *errName;          	    //错误描述            
	
};


/**
*@class CJSKInfoFunc
*@brief JSK操作函数信息
*/
class CJSKInfoFunc 
{
public:

// 	static string m_jskNo;              //金税盘号
public:
	/*!
		@brief new发送和接收Buf
	@return
	*/
	static void JSK_NewBuf(UINT8 **pSendBuf,UINT8 **pRevBuf);
		/*!
	@brief delete发送和接收Buf
	@return
	*/
	static void JSK_DelBuf(UINT8 *pSendBuf,UINT8 *pRevBuf);

	/*!
	@brief 初始化金税盘号
	@return
	*/
	//static void Set_jskNo(string jskNo) {m_jskNo.assign(jskNo);}

	/*!
	@brief 锁定互斥体	
	@return  
	*/ 
	static void MutexLock(void);

	/*!
	@brief 解锁互斥体	
	*/ 
	static void MutexUnlock(void);

	/*!
	@brief 金税盘关,卡打开操作主函数
    @param[in] UINT8 *Code  CA口令密码(9字符，口令长度不足9，填充数字0，例如"88888888")+金税盘口令(9字符，口令长度不足9，填充数字0，例如"88888888")
	@param[in]UINT16 Size   字符串长度
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号；成功，返回0
	*/
    static INT32 JSK_Open_Proc(UINT8 *Code,UINT16 Size,string &strErr);
	/*!
	@brief 金税盘关卡，操作主函数
	@param[in] pp1 对应调用不同金税盘功能
	@param[in] pp2 配合pp1，调用金税盘功能
	@param[in] InLen 输入数据的长度
	@param[out] OutLen 返回数据的长度
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号；成功，返回0
	*/
	static INT32 JSK_Proc(UINT8 pp1,UINT8 pp2,UINT8 *pInBuf,UINT16 InLen, UINT8 *pOutBuf,UINT16 &OutLen,string &strErr);
	
	/*!
	@brief 金税盘关卡，关闭操作主函数
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号；成功，返回0
	*/
	static INT32 JSK_Close_Proc(string &strErr);
	
	/*!
	@brief 查找错误描述函数
	@param[in] UINT32 nErrID 错误号
	@param[out] strErrInfo  错误描述信息
	@return 
	*/
	static void Find_ErrInfo(INT32 nErrID, string &strErrInfo);
	

	
	CJSKInfoFunc();
	~CJSKInfoFunc();
	
	//static string m_cakl;		//CA口令
	static string m_jqbh;		//税控收款机机器编号
	static string m_jspkl;		//金税盘口令
	static string m_bspkl;		//报税盘口令
	static void set_Para(string jqbh, string jspkl, string bspkl);

	/*!
	@brief 发票数据转换金税盘中发票明细数据
	@param[in]  CDataInvHead *pInvHead
	@param[out] UINT8 *pDataPtr,UINT32 nDataLen 
	@return 
	*/
	static void InvDetail2Data(CDataInvHead *pInvHead,UINT8 *pDataPtr,UINT32 &nDataLen);

	/*!
	@brief 金税盘中发票明细数据转换发票数据
	@param[in] UINT8 *pDataPtr
	@param[out]  CDataInvHead *pInvHead
	@return 
	*/
	static void Data2InvDetail(INT8 *pDataPtr,CDataInvHead *pInvHead, UINT8 flag=0);

	static void ParseData(INT8 *dest);


	/*!
	@brief 获取纳税户信息
	@param[in] 
	@param[out]CUserInfo *pUserInfo 纳税户信息
	@param[out]CDataTax *pTax 税率
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 GetCorpInfo(CDataUserInfo *pUserInfo,CDataTax *pTax,string &strErr);


	/*!
	@brief 获取金税盘机器编号
	@param[in] 
	@param[out] UINT8 *JSPNo OUTBUFF[16]：金税盘机器编号（字符串，例如"661400011858"）
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 GetJSPNo(UINT8 *JSPNo,string &strErr);

	/*!
	@brief 获取金税盘当前时间
	@param[in] 
	@param[out] UINT8 *JSPDate 返回当前时间 OUTBUFF[15]：YYYYMMDDHHMMSS（例如"20150413185600"）
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 GetJSPCurDate(UINT8 *JSPDate,string &strErr);

   /*!
	@brief 获取金税盘版本号
	@param[in] 
	@param[out] UINT8 *JSPVer OUTBUFF[10]：金税盘版本号（字符串，例如"SKN6K08K0"）
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 GetJSPVer(UINT8 *JSPVer,string &strErr);


	/*!
	@brief 获取金税盘启用时间
	@param[in] 
	@param[out] UINT8 *JSPOTime OUTBUFF[15]：YYYYMMDDHHMMSS（例如"20150413185600"）
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 GetJSPOpenTime(UINT8 *JSPOTime,string &strErr);

	/*!
	@brief 获取金税盘数据报送起始时间
	@param[in] 
	@param[out] UINT8 *JSPDataSendTime  OUTBUFF[15]：YYYYMMDDHHMMSS（例如"20150413185600"）
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 GetJSPSendTime(UINT8 *JSPSTime,string &strErr);

	/*!
	@brief 取哈希税号
	@param[in] 
	@param[out] UINT8 *HashNo
	@param[out]UINT8 *AddrNo
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 GetHashNo(UINT8 *HashNo,UINT8 *AddrNo,string &strErr, UINT8 HashFlag=HASH_NO_FLAG_16);

	/*!
	@brief 取发行税号
	@param[in] 
	@param[out] UINT8 *IssueNo
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 GetIssueNo(UINT8 *IssueNo,string &strErr);

	/*!获取第一张发票离线发票的发票号码、发票代码和发票索引号
	@brief 取发行税号
	@param[in] 
	@param[out] OUTBUFF：16字节发票代码（10或12位ASCII码）+4字节发票号码+4字节发票索引号
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 GetFirstOffInvInfo(CDataInvHead *pInvHead,string &strErr);
	
	/*!
	@brief 查询金税盘是否有抄税资料
	@param[in] 
	@param[out] UINT8 uCopyFlag 0-无，1-有
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 GetJSPCopyFlag(UINT8 &uCopyFlag,string &strErr);

	/*!
	@brief 获取报税盘机器编号
	@param[in] 
	@param[out] UINT8 *BSPNo OUTBUFF[16]：报税盘机器编号（字符串，例如"661400011858"）
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 GetBSPNo(UINT8 *BSPNo,string &strErr);

	/*!
	@brief 获取报税盘企业纳税人识别号
	@param[in] 
	@param[out] UINT8 *BSPNsrsbh OUTBUFF[21]：（字符串，例如"140301000000009"）
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 GetBSPNsrsbh(UINT8 *BSPNsrsbh,string &strErr);
	
	/*!
	@brief 获取报税盘版本号
	@param[in] 
	@param[out] UINT8 *BSPVer OUTBUFF[10]：报税盘版本号（字符串，例如"BSN6K05B"）
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 GetBSPVer(UINT8 *BSPVer,string &strErr);

	/*!
	@brief 获取报税盘开票机号
	@param[in] 
	@param[out] UINT8 *BSPNo OUTBUFF[2]：WORD类型，0表示主机，非0表示分机
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 GetBSPKpjh(UINT8 *BSPKpjh,string &strErr);


	/*!
	@brief 获取金税盘离线控制参数
	@param[in] 
	@param[in] CUserInfo* pUserinfo 离线限制条件
	@param[out] CInvKind invKind[]
	@param[out] UINT32 invNum
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 GetOffLimitInfo(CDataInvKind *invKind,UINT32 &invNum, string &strErr);
    static INT32 GetOffLimitInfo(UINT8 fplx, CDataInvKind *invKind,string &strErr);

    /*!
	@brief 金税盘口令认证  
	@param[in] UINT8* PassW,INBUFF[9] ：当前口令（字符串，例如"12345678"）
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 JSPPassW(UINT8* PassW, string &strErr);

    /*!
	@brief 金税盘口令更改  
	@param[in] UINT8* ModPassW,INBUFF[18] ：当前口令(9)+新口令(9)（字符串，例如"12345678"+"87654321"）
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 JSPModPassW(UINT8* ModPassW, string &strErr);

	/*!
	@brief 证书口令更改  
	@param[in] UINT8* ZSPassW,INBUFF[18] ：当前口令(9)+新口令(9)（字符串，例如"12345678"+"87654321"）
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 ZSPassW(UINT8* ZSPassW, string &strErr);

	/*!
	@brief 报税盘注册
	@param[in] 
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 BSPRegister(string &strErr);

	/*!
	@brief 更新企业信息  
	@param[in] UINT8* UpCorpInfo, INBUFF[] 为通过网络从处理获取的权限信息(密文)
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 UpdateCorpInfo(UINT8* UpCorpInfo, UINT32 nLen, string &strErr);

	/*!
	@brief 读取企业信息  
	@param[out]UINT8* RCorpInfo, OUTBUFF[] 为从金税盘读取的权限信息(密文)
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 ReadCorpInfo(UINT16 &outLen, UINT8* RCorpInfo, string &strErr);

	/*!
	@brief 设置发票上传状态
	@param[in]  INBUFF[] 为通过网络从处理获取到发票上传状态信息包（密文）
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 SetUpLoadFlag(UINT8 *upInfo,UINT32 nLen, string &strErr);
	
	/*!
	@brief 网络抄税信息
	@param[in]  UINT8 Type 票种类别
	@param[out] UINT8 *StartDate  抄税起始时间
	@param[out] UINT8 *EndDate    抄税截至时间
	@param[out] UINT8 *NetTaxInfo 抄税汇总信息
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 NetCopyTax(UINT8 Type,UINT8 *StartDate,UINT8 *EndDate,UINT8 *NetTaxInfo, UINT32 &nTaxLen, string &strErr);
    static INT32 NetCopyTaxDate(UINT8 Type,UINT8 *StartDate,UINT8 *EndDate,string &strErr);

	/*!
	@brief 金税盘抄税信息
	@param[in] UINT8 Type 票种类别
	@param[out] 
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 JSPCopyTax(UINT8 Type,string &strErr);

	/*!
	@brief 报税盘抄税信息
	@param[in] UINT8 Type 票种类别
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 BSPCopyTax(UINT8 Type,string &strErr);

	

	/*!
	@brief 网络清卡
	@param[in]  UINT8 Type 票种类别
	@param[out] UINT8 *CCardInfo 清卡信息
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 NetClearCard(UINT8 Type,UINT8 *CCardInfo,UINT32 nInfoLen,string &strErr);

	/*!
	@brief 报税盘清卡
	@param[in]  UINT8 Type 票种类别
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 BSPClearCard(UINT8 Type,string &strErr);

	
	/*!
	@brief 申请网络购票
	@param[in]  UINT8 Type 发票类型
	@param[out] NetEmpowData OUTBU 16字节网络购票申请信息（密文）
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 AppNetInvVol(UINT8 Type,UINT16 &outLen,UINT8 *NetEmpowData, string &strErr);
	
	/*!
	@brief 2）网络购票数据读入
	@param[in]  UINT8 Type 发票类型
	@param[in]  UINT8 * NetCrypData INBUFF[144] 通过网络从后台获取的电子发票数据包（密文）
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 ReadNetInvVol(UINT8 Type,UINT8 *NetCrypData,string &strErr);
	

	/*!
	@brief 网络购票读入确认申请
	@param[in]  UINT8 Type 发票类型
	@param[out]  UINT8 * NetCrypData OUTBUFF 40字节金税盘网络购票读入确认数据包（密文）
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 App2NetInvVol(UINT8 Type,UINT16 &outLen,UINT8 *NetCrypData,CDataInvVol *invVol,string &strErr);

	/*!
	@brief 网络购票确认
	@param[in]  UINT8 * NetCrypData NBUFF 通过网络从后台获取的40字节网络购票确认数据包（密文）
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 ConNetInvVol(UINT8 Type, UINT8 *NetCrypData,string &strErr);

	/*!
	@brief 从金税盘读入新购发票
	@param[in]  UINT8 Type 票种类别
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 JSPGetInvVolInfo(UINT8 Type,string &strErr);

	/*!
	@brief 从报税盘读入新购发票
	@param[in]  UINT8 Type 票种类别
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 BSPGetInvVolInfo(UINT8 Type,string &strErr);

	
	/*!
	@brief 获取盘上票源信息
	@param[in] 
	@param[out] CInvVol *pInvVol
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 GetJSKInvVolInfo(CDataInvVol *invVol,UINT32 &nInvNum,string &strErr);
	
/*!
	@brief 开票(正票,红票,空白作废)
	@param[in] 开票信息 CDataInvHead *pInvHead
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 MakeInvHandInfo(CDataInvHead *pInvHead , string &strErr);
	
	
	/*!
	@brief 已开发票作废(正废,红废)
	@param[in] CDataInvHead *pInvHead 
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 WasteInvHandInfo(CDataInvHead *pInvHead ,string &strErr);
	
	/*!
	@brief 获取当前发票号
	@param[in] 
	@param[out] CInvVol *pInvVol
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 GetCurInvInfo(CDataInvVol *pInvVol,string &strErr);

	/*!
	@brief  取流水号
	@param[in] 
	@param[out] UINT8 *RunNo
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
    static INT32 GetRunNoInfo(UINT8 *RunNo,string &strErr);
	

	 /*!
	@brief 给分机报税盘分票
	@param[in] CInvVol *pInvVol
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 HostToInvBSP(CDataInvVol *pInvVol, string &strErr);

	 /*!
	@brief 给分机金税盘分票
	@param[in] CInvVol *pInvVol
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 HostToInvJSP(CDataInvVol *pInvVol, string &strErr);


	 /*!
	@brief 用报税盘退回
	@param[in] CInvVol *pInvVol
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 InvVolRetBSP(CDataInvVol *pInvVol,string &strErr);

		 /*!
	@brief 用金税盘退回
	@param[in] CInvVol *pInvVol
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 InvVolRetJSP(CDataInvVol *pInvVol,string &strErr);

	 /*!
	@brief 主机读入分机报税盘退回发票
	@param[in] UINT8 Type 发票类型
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 HostGetInvBSP(UINT8 Type,string &strErr);

	/*!
	@brief 主机读入分机金税盘退回发票
	@param[in] UINT8 Type 发票类型
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 HostGetInvJSP(UINT8 Type,string &strErr);

	/*!
	@brief 获取锁死日期
	@param[in] UINT8 Type 发票类型
	@param[out] UINT8 *pLockDate  OUTBUFF[9]：YYYYMMDD（例如"20150520"）
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 GetLockDate(UINT8 Type,UINT8 *pLockDate,string &strErr);

	/*!
	@brief 发票查询
	@param[in] CDataInvHead *pInvHead  INBUFF[24]  unsigned int发票起始号;16B发票代码; unsigned int发票索引号（可选，若上层数据库无此字段，填充4字节0xFF）
	@param[out]  CDataInvHead *pInvHead  查询的发票信息
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 GetInvDetailInfoNO(CDataInvHead *pInvHead,string &strErr);
	static INT32 GetInvDetailInfoNO(CDataInvHead *pInvHead, UINT8 *invBuff, UINT32 &invLen, string &strErr);


	/*!
	@brief 发票查询
	@param[in]UINT8 *chDate  查询日期6位（年月）201505
    @param[out]  uInvFlag  1字节接收后续发票标志（数字1表示有后续发票需要接收；数字0表示无）+单张发票明细
     @param[out]  CDataInvHead *pInvHead  查询的发票信息
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 GetInvDetailInfoDate(UINT8 *chDate,CDataInvHead *pInvHead,UINT8 &uInvFlag,string &strErr);


	/*!
	@brief 发票查询
	@param[in]   UINT32 iDate  查询日期6位（年月）201505
    @param[out]  FpType  所要查询的发票类型
     @param[out] CTjxxhz *pTjxxhz 查询的发票信息
	@param[out] string &strErr 错误信息
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 GetMonthCountDate(UINT32 iDate,UINT8 FpType,CDataTjxxhz *pTjxxhz,string &strErr);


	static void ParseInvCode(string str, string &fpdm, UINT32 &fphm);
};


#endif



