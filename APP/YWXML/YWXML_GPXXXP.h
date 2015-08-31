/*! \file    YWXML_GPXXXP.h
   \brief    款机调用的中间件接口 业务: 购票信息写盘
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_GPXXXP_H
#define LIB_YWXML_GPXXXP_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CGpxxxp
 *@brief 购票信息写盘
 */
class CGpxxxp: public CYWXmlBase
{

public:

	CGpxxxp(XMLConstruct *construct, XMLParse *parse);
	~CGpxxxp();
	
	INT32 Execute(); 

private:

	/*!
	@brief 购票信息写盘：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@param[out] gpxxmw		购票信息密文
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &gpxxmw);
	
	/*! 
	@brief 购票信息写盘：输出参数组装（组装成XML文件） 
	@param[in] retInfo 返回信息指针
	@param[out] construct  XML构造类
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);	
};

}
#endif



