/*! \file    YWXML_BSPXXCX.h
   \brief    款机调用的中间件接口 业务: 报税盘信息查询
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_BSPXXCX_H
#define LIB_YWXML_BSPXXCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CUserInfo.h"


namespace middleware
{
/**
 *@class CBspxxcx
 *@brief 报税盘信息查询
 */
class CBspxxcx : public CYWXmlBase
{

public:

	CBspxxcx(XMLConstruct *construct, XMLParse *parse);
	~CBspxxcx();
	
	INT32 Execute(); 

private:

	/*!
	@brief 报税盘信息查询：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);
	
	/*! 
	@brief 报税盘信息查询：输出参数组装（组装成XML文件） 
	@param[in] pUserinfo 指向用户信息表的指针 
	@param[in] bspbh 报税盘编号 
	@param[in] retInfo 返回信息指针
	@param[in] dqsz 当前时钟
	@param[out] construct  XML构造类
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, CUserInfo *pUserinfo, string dqsz, Return_Info *retInfo);
};

}
#endif



