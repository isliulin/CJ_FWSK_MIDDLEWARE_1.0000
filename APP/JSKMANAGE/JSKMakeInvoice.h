/*! \file  JSKMakeInvoice.h
\brief    awe4000r 中间件操作类  发票开具相关流程 2.10 ~ 2.12  2.21 ~ 2.22
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
#define XML_FILE_NAME_KFSBM		"ZZ_"				//开票软件开发商编码
#define XML_FILE_NAME_ENCODE	"9999_"				//4位加解密算法版本号

//发票上传标志
#define INV_UPLOAD_FLAG0	0		//未上传
#define INV_UPLOAD_FLAG1	1		//已上传，未下载结果成功
#define INV_UPLOAD_FLAG2	2		//上传发票错误

typedef struct _JSKInvDet
{
	string m_spbm;			/**< 商品编码 */
	string m_spmc;			/**< 商品名称 */
	double m_spdj;			/**< 商品单价(元，保留2位小数) */
	double m_spsl;			/**< 商品数量 非负数*/
	INT64  m_spje;			/**< 商品金额(分) ，折扣行金额为负数*/
	UINT8  m_property;		/**< 商品行属性 0:一般商品行，1:折扣行*/
}JSKInvDet;

typedef struct _JSKInvHead
{
	string m_fpdm;			/**< 发票代码 */
	UINT32 m_fphm;			/**< 发票号码 */
	UINT32 m_kprq;			/**< 开票日期 */
	UINT32 m_kpsj;			/**< 开票时间 */

	UINT8  m_kplx;			/**< 开票类型 1-正票 2-红票 3-空白废*/
	INT64  m_kphjje;			/**< 开票合计金额(分)，非负数 */
	string m_yfpdm;			/**< 原发票代码 */
	UINT32 m_yfphm;			/**< 原发票号码 */

	string m_fkdw;			/**< 付款单位 */
	string m_payerCode;     /**< 付款单位税务识别号 */
	string m_sky;			/**< 收款员 */
	UINT32 m_sphsl;			/**< 商品行数量 非负数*/

	string  m_fwm;			/**< 防伪税控码 */
	string m_backup1;		/**< 备用1 */

	JSKInvDet m_invDet[6];		/**< 商品行信息数组 */
} JSKInvHead;

/**
*@class CJSKMakeInvoice
*@brief 处理开票过程
*/
class CJSKMakeInvoice  
{
	
public:

	CJSKMakeInvoice();
	~CJSKMakeInvoice();

	
	/*!
	@brief 获取当前票号		
	@param[in] 
	@param[out] pInvVol  发票信息类
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 GPXXCX_Proc(CDataInvVol *pInvVol, string &strErr);

	/*!
	@brief 开票（包含正票、红票）		
	@param[in] invhead			发票头信息
	@param[out] taxCode   	税控码（20字节）
	@param[out] strErr   		错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 FPKJ_Proc(CDataInvHead *pInvHead, string &strErr, UINT8 wasteflag=0);

	/*!
	@brief 开票（空白废票、已开票作废）
	@param[in] invhead	发票头信息
	@param[in] zflx   作废类型	0：空白发票作废	1：已开发票作废
	@param[out] strErr   		错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 FPZF_Proc(CDataInvHead *pInvHead, UINT8 zflx, string &strErr);

	/*!
	@brief 发票查询
	@param[in] cxfs	查询方式
	@param[in] cxtj	查询条件
	@param[out] invNum  发票张数
	@param[in/out] invhead	发票头信息
	@param[out] strErr   		错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 FPCX_Proc(UINT8 cxfs, string cxtj, UINT32 &invNum, CDataInvHead *pInvHead, string &strErr);

	/*!
	@brief 发票实时上传
	@param[in/out] fpzx	发票张数
	@param[out] strInvInfo	发票明细
	@param[out] strErr   		错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 FPSC_Proc(UINT8 czlx, UINT32 &fpzx, string &strInvInfo, string &strErr);

	/*!
	@brief 发票更新
	@param[in] invhead	发票头信息
	@param[out] strErr   		错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 FPGX_Proc(string scqrbw, string &strErr);

	/*!
	@brief 发票补录
	@param[in] nsrsbh  纳税人识别号
	@param[in] sksbbh  税控设备编号
	@param[in] SDate  起始日期
	@param[in] EDate  截止日期
	@param[out] strErr   		错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 FPBL_Proc(string nsrsbh, string sksbbh, UINT32 SDate, UINT32 EDate, string &strErr);


	/*!
	@brief 发票数据转换金税盘中发票明细数据
	@param[in]  CInvHead *pInvHead
	@param[out] UINT8 *pDataPtr,UINT32 nDataLen 
	@return 
	*/
	static void AddInvDetail2Data(CDataInvHead *pInvHead,UINT8 *pDataPtr,UINT32 &nDataLen);
	static void Str2InvHead(INT8 *pDataPtr,CDataInvHead *pInvHead);

	/*!
	@brief 过滤字符串前、后的空格
	@param[in/out] str
	@return 
	*/
	static void FilterSpace(string &str);

	/*!
	@brief 获取上传出错发票信息
	@param[in/out] str
	@return 
	*/
	static INT32 GetErrUpInv(CDataInvServ *pDataInvServ, UINT32 &nCount, string &strErr);

private:

	/*!
	@brief 开票权限控制
	@param[in]  kplx 开票类型
	@param[in]  nSum 开票金额
	@param[out] 
	@return 
	*/
	static INT32 MakeInvAuthority(CDataInvHead *pInvHead, string& strErr);

	static INT32 ParseFpscjg(string scqrbw, string &mxjgmw, string &strErr);
	
};


#endif



