/*! \file    YWXML_JKSJCX.h
\brief    款机调用的中间件接口 业务: 监控数据查询
\author   myf
\version  1.0
\date     2015 
*/

#ifndef LIB_YWXML_JKSJCX_H
#define LIB_YWXML_JKSJCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CUserInfo.h"
#include "CInvKind.h"
#include "JSKManageProc.h"

namespace middleware
{
/**
 *@class CJksjcx
 *@brief 监控数据查询
 */
class CJksjcx: public CYWXmlBase
{

public:

	CJksjcx(XMLConstruct *construct, XMLParse *parse);
	~CJksjcx();
	
	INT32 Execute(); 

private:

	/*!
	@brief 监控数据查询：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);
	
	/*! 
	@brief 监控数据查询：输出参数组装（组装成XML文件） 
	@param[in] pUserinfo 指向纳税户信息的指针 
	@param[in] pInvkind  指向发票种类信息的指针 
	@param[in] retInfo 返回信息指针
	@param[out] construct  XML构造类
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, CInvKind *pInvKind, Return_Info *retInfo);	
};

}
#endif



