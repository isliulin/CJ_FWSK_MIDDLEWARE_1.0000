/*! \file    YWXML_SKSBQTYXXCX.h
   \brief    款机调用的中间件接口 业务: 税控设备其他信息查询
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef YWXML_SKSBQTYXXCX_H
#define YWXML_SKSBQTYXXCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"

#include "CInvVol.h"


namespace middleware
{
/**
 *@class CSksbqtxxcx
 *@brief 税控设备其他信息查询
 */
class CSksbqtxxcx : public CYWXmlBase
{

public:

	CSksbqtxxcx(XMLConstruct *construct, XMLParse *parse);
	~CSksbqtxxcx();
	
	INT32 Execute(); 

private:

	/*!
	@brief 购票信息查询：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT8 &xxlx);
	
	/*! 
	@brief 购票信息查询：输出参数组装（组装成XML文件） 
	@param[out] construct  XML构造类
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, string sksbxx, Return_Info *retInfo);	
};

}
#endif



