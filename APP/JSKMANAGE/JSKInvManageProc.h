/*! \file  JSKManageProc.h
\brief    awe4000r 发票管理流程
\author   zfj
\version  1.0
\date     2015-04-16
*/

#ifndef LIB_JSK_INV_MANAGE_PROC_H
#define LIB_JSK_INV_MANAGE_PROC_H

#include "JSKManageProc.h"
#include "IncludeMe.h"
#include "JSKInfoDef.h"
#include "JSKInfoFunc.h"
#include "DataClassDesign.h"

/**
*@class CJSKInvManageProc
*@brief 税控设备信息查询管理流程
*/
class CJSKInvManageProc  
{
	
public:

	CJSKInvManageProc();
	~CJSKInvManageProc();

	/*!
	@brief 2.7.购票信息写盘
	@param[in] fplxdm 发票类型代码
	@param[in] gpxxmw 购票信息密文
	@param[out] strErr   错误信息
	@return  
	*/
	static INT32 GPXXXP_Proc(string fplxdm, string gpxxmw, string &strErr);
	
	/*!
	@brief 2.8.购票信息写盘解锁
	@param[in] fplxdm 发票类型代码
	@param[in] wslpjsxx 网上领票解锁信息
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 GPXXXPJS_Proc(string fplxdm, string wslpjsxx, string &strErr);


	/*!
	@brief 2.14.报税盘发票查询
	@param[in] fplxdm 发票类型代码
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 BSPFPCX_Proc(string fplxdm, UINT32 &invNum, CDataInvVol *pInvVol, string &strErr);

	/*!
	@brief 2.15.发票分发
	@param[in] jzlx 介质类型
	@param[in] pInvVol 发票信息类
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 BSPFPFF_Proc(UINT8 jzlx, CDataInvVol *pInvVol, string &strErr);

	/*!
	@brief 2.16.发票收回
	@param[in] jzlx 介质类型
	@param[in] pInvVol 发票信息类
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 BSPFPSH_Proc(UINT8 jzlx, CDataInvVol *pInvVol, string &strErr);

	/*!
	@brief 2.23.发票读入
	@param[in] jzlx 介质类型
	@param[in] fplxdm 发票类型代码
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 FPDR_Proc(UINT8 jzlx, string fplxdm, string &strErr);

	/*!
	@brief 2.24.分机退回
	@param[in] jzlx 介质类型
	@param[in] fplxdm 发票类型代码
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 FJTH_Proc(UINT8 jzlx, string fplxdm, string &strErr);

	/*!
	@brief 2.19.发票统计信息查询
	@param[in] strFplxdm 发票类型代码
	@param[in/out] pTjxxhz 统计信息汇总类
	@param[out] MonthCount 查询月数
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 TJXXCX_Proc(string strFplxdm, INT32 &MonthCount, CDataTjxxhz *pTjxxhz, string &strErr);

	

	/*!
	@brief 发票类型转换发票类型代码
	@param[in]	fplx	发票类型
	@param[out] fpzldm	发票类型代码
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 fplx2fplxdm(UINT8 fplx, string &fplxdm);

	/*!
	@brief 发票类型代码转换发票类型
	@param[in] fpzldm	发票类型代码
	@param[out]	fplx	发票类型
	@return 如果不成功，返回错误号及错误描述；成功，返回JSK_SUCCESS
	*/
	static INT32 fplxdm2fplx(string fplxdm, UINT8 &fplx);

};


#endif



