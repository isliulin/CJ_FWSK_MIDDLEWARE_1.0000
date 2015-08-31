/*! \file    YWXML_SQSLCX.h
   \brief    款机调用的中间件接口 业务:授权税率查询
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_SQSLCX_H
#define LIB_YWXML_SQSLCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"

#include "CTax.h"

namespace middleware
{

/**
 *@class CSqslcx
 *@brief 授权税率查询
 */
class CSqslcx : public CYWXmlBase
{

public:

	CSqslcx(XMLConstruct *construct, XMLParse *parse);
	~CSqslcx();
	
	INT32 Execute(); 

private:

	/*!
	@brief 授权税率查询：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);
	
	/*! 
	@brief 授权税率查询：输出参数组装（组装成XML文件） 
	@param[in] pTax     税率表的指针
	@param[in] slNum	税率的个数
	@param[in] retInfo 返回信息指针
	@param[out] construct  XML构造类
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, CTax *pTax, UINT8 slNum, Return_Info *retInfo);	
};

}
#endif



