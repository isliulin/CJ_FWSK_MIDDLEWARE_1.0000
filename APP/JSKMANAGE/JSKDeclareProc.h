/*! \file  JSKDeclareProc.h
\brief    awe4000r 数据抄报、监控回传
\author   zfj
\version  1.0
\date     2015-04-16
*/

#ifndef LIB_JSK_DECLARE_PROC_H
#define LIB_JSK_DECLARE_PROC_H

#include "JSKManageProc.h"
#include "IncludeMe.h"
#include "JSKInfoDef.h"
#include "JSKInfoFunc.h"


/**
*@class CJSKDeclareProc
*@brief 税控设备信息查询管理流程
*/
class CJSKDeclareProc  
{
	
public:

	CJSKDeclareProc();
	~CJSKDeclareProc();

	/*!
	@brief 数据抄报
	@param[in] fplxdm 发票类型代码
	@param[out] sqBuff 属期
	@param[out] fphzBuff  抄报汇总信息
	@param[out] strErr   错误信息
	@return  
	*/
	//static INT32 SJCB_Proc(string fplxdm, UINT8 *sqBuff, UINT8 *fphzBuff, string &strErr);
	static INT32 SJCB_Proc(string fplxdm, UINT8 jzlx, string &strSQ, string &strFphz, string &strErr);
	
	/*!
	@brief 监控回传
	@param[in] fplxdm 发票类型代码
	@param[in] strFpjkmw 128字节清卡数据（密文）
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 JKHC_Proc(string fplxdm, string strFpjkmw, string &strErr);

	/*!
	@brief 税控设备报税盘组合操作
	@param[in] fplxdm 发票类型代码
	@param[in] czlx 操作类型
	@param[out] strErr   错误信息
	@return  1 SUCCESS； 0  FAILURE
	*/
	static INT32 SKPBSP_Proc(string fplxdm, UINT8 czlx, string &strErr);

	static INT32 DeclareAuthority(string &strErr);


	static INT32 DelUploadInv();


};


#endif



