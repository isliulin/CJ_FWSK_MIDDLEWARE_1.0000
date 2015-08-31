/*! \file  JSKManageProc.h
\brief    awe4000r 税控设备信息查询管理流程  2.1 ~ 2.5  2.9
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
*@brief 税控设备信息查询管理流程
*/
class CJSKManageProc  
{
	
public:

	CJSKManageProc();
	~CJSKManageProc();

	static void set_JSKPara(string jqbh, string sksbkl, string bspkl);

	/*!
	@brief 税控设备编号查询
	@param[in] 
	@param[out] sksbbh 税控设备编号
	@param[out] strErr   错误信息
	@return  
	*/
	static INT32 SKSBBH_Proc(string &sksbbh, string &strErr);
	
	/*!
	@brief 报税盘编号查询
	@param[in] 
	@param[out] sksbbh 税控设备编号
	@param[out] bspbh  报税盘编号
	@param[out] strErr   错误信息
	@return  
	*/
	static INT32 BSPBH_Proc(string &bspbh, string &strErr);
	
	/*!
	@brief 税控设备信息查询
	@param[in] 
	@param[out] pUserInfo 纳税户信息
	@param[out] strCurTime 当期时间
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 SKPXXCX_Proc(CDataUserInfo *pUserInfo, string &strCurTime, string &strErr);

	/*!
	@brief 报税盘信息查询
	@param[in] 
	@param[out] 
	@param[out] 
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 BSPXXCX_Proc(CDataUserInfo *pUserInfo, string &strErr);

	/*!
	@brief 监控数据查询
	@param[in] 
	@param[out] pUserInfo
	@param[out] pInvKind
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 JKSJCX_Proc(CDataInvKind *pInvKind, string &strErr);

	/*!
	@brief 授权税率查询
	@param[out] pTax 税率信息
	@param[out] taxNum	税率个数
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 SQSLCX_Proc(CDataTax *pTax, UINT8 &taxNum, string &strErr);

	/*!
	@brief 口令变更
	@param[in] oldPwd 旧密码
	@param[in] newPwd 新密码
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 KLBG_Proc(string oldPwd, string newPwd, string &strErr);

	/*!
	@brief 变更证书口令
	@param[in] oldPwd 旧密码
	@param[in] newPwd 新密码
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 BGZSKL_Proc(string oldPwd, string newPwd, string &strErr);

	/*!
	@brief 2.20.离线信息写盘
	@param[in] lxxxmw 离线信息密文
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 LXXXXP_Proc(string lxxxmw, string &strErr);


	/*!
	@brief 税控设备其他信息查询
	@param[in] xxlx 信息类型	0：输出的税控设备信息为3.2发票上传结果获取接口的输入项"其他信息"
	@param[in]					1：输出的税控设备信息为3.3网络抄税接口和3.4清零解锁的输入项"其他信息"
	@param[in]					2：输出的税控设备信息为3.5离线信息上传接口的输入项"其他信息"
	@param[in]					3：输出的税控设备信息为3.6网络领取发票接口的输入项"其他信息"
	@param[in]					4：输出的税控设备信息为3.7网络领取发票确认接口的输入项"其他信息"
	@param[out] sksbxx 税控设备信息
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 SKSBQTYXXCX_Proc(string fplxdm, UINT8 xxlx, string &sksbxx, string &strErr);

	/*!
	@brief 读取哈希税号
	@param[in] strHxsh 哈希税号
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 GetHashTaxNo(UINT8 HashFlag, string &strErr);

	/*!
	@brief 读取发行税号
	@param[in] strFxsh 发行税号
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 GetIssueTaxNo(string &strErr);

	static void Transformfplx(UINT32 nCount, string &strMsg);


	/*!
	@brief 网络参数维护
	@param[in] pNetPara 网络参数类
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 NetPara_Proc(CDataNetPara *pNetPara, string &strErr);

	/*!
	@brief 获取离线相关数据
	@param[out] fpzs   未上传的发票张数
	@param[out] fpsj   未上传发票时间（第一张未上传发票的开票日期YYYYMMDDHHMMSS）
	@param[out] fpljje 未上传发票累计金额（保留两位小数）
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 OffInvInfo_Proc(UINT32 &wscfpzs, string &wscfpsj, INT64 &wscfpljje, string &strErr);
};


#endif



