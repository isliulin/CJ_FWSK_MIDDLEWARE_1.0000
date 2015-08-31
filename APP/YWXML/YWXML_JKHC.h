/*! \file    YWXML_JKHC.h
   \brief    款机调用的中间件接口 业务2.18监控回传
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_JKHC_H
#define LIB_YWXML_JKHC_H


#include "IncludeMe.h"
#include "YWXmlBase.h"

namespace middleware
{
/**
 *@class CJkhc
 *@brief 监控回传
 */
class CJkhc : public CYWXmlBase
{


public:

	CJkhc(XMLConstruct *construct, XMLParse *parse);
	~CJkhc();
	
	INT32 Execute(); 


private:
	/*!
	@函数名: XmlParse
	@brief 监控回传：输入参数解析（解析XML文件）
	@param[in]  parse		XML解析类
	@param[out]  strFpjkmw	发票监控密文
	@param[out]  strSzjkmw	时钟监控密文
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &strFpjkmw, string &strSzjkmw);

	/*!
	@函数名: XmlBuild
	@brief监控回传：输出参数组装（组装XML文件）
	@param[in]  construct		XML组装类
	@param[in]  retInfo		返回信息类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);

		
};

}
#endif































