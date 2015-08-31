/*! \file    NETXML_LXXXSC.h
   \brief    款机调用的中间件接口 业务3.5 离线信息上传
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_NETXML_LXXXSC_H
#define LIB_NETXML_LXXXSC_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvKind.h"
#include "SysMacDef.h"
#include "arithmetic.h"

namespace middleware
{
/**
 *@class CLxxxsc
 *@brief 离线信息上传
 */
class CLxxxsc : public CYWXmlBase
{


public:

	CLxxxsc(XMLConstruct *construct, XMLParse *parse);
	~CLxxxsc();
	
	INT32 Execute(); 


private:
	/*!
	@函数名: XmlParse
	@brief 发票分发：输入参数解析（解析XML文件）
	@param[in]  parse		XML解析类
	@param[out]  invkind	纳税人票种表
	@param[out]  strScjzrq	上传截止日期
	@param[out]  strLxkpsc	离线开票时长
	@param[out]  strQtxx	其他信息,该信息将在SERVXML中被组装传往局端
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, CInvKind *invkind, string &strScjzrq, string &strLxkpsc, string &strQtxx);

	/*!
	@函数名: XmlBuild
	@brief 发票分发：输出参数组装（组装XML文件）
	@param[in]  construct		XML组装类
	@param[in]  retInfo		返回信息类
	@param[in]  strLzkzxx		离线控制信息
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo, string strLzkzxx);

		
};

}
#endif


































