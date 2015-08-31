/*! \file    YWXML_GPXXCX.h
   \brief    款机调用的中间件接口 业务: 购票信息查询
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_GPXXCX_H
#define LIB_YWXML_GPXXCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"

#include "CInvVol.h"


namespace middleware
{
/**
 *@class CGpxxcx
 *@brief 购票信息查询
 */
class CGpxxcx : public CYWXmlBase
{

public:

	CGpxxcx(XMLConstruct *construct, XMLParse *parse);
	~CGpxxcx();
	
	INT32 Execute(); 

private:

	/*!
	@brief 购票信息查询：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);
	
	/*! 
	@brief 购票信息查询：输出参数组装（组装成XML文件） 
	@param[in] pInvVol 指向发票信息表的指针 
	@param[in] retInfo 返回信息指针息类对象
	@param[out] construct  XML构造类
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, CInvVol *pInvVol, Return_Info *retInfo);	
};

}
#endif



