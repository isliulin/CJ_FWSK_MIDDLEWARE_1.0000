/*! \file    YWXML_GPXXXPJS.h
   \brief    款机调用的中间件接口 业务: 购票信息写盘解锁
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_GPXXXPJS_H
#define LIB_YWXML_GPXXXPJS_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CGpxxxpjs
 *@brief 购票信息写盘解锁
 */
class CGpxxxpjs: public CYWXmlBase
{

public:

	CGpxxxpjs(XMLConstruct *construct, XMLParse *parse);
	~CGpxxxpjs();
	
	INT32 Execute(); 

private:

	/*!
	@brief 购票信息写盘解锁：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@param[out] wslpjsxx		网上领票解锁信息
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &wslpjsxx);
	
	/*! 
	@brief 购票信息写盘解锁：输出参数组装（组装成XML文件） 
	@param[in] sksbbh 税控设备编号 
	@param[in] bspbh 报税盘编号 
	@param[in] retInfo 返回信息指针
	@param[out] construct  XML构造类
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);		
};

}
#endif



