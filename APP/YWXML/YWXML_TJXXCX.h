/*! \file    YWXML_TJXXCX.h
   \brief    款机调用的中间件接口 业务2.19统计信息查询
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_TJXXCX_H
#define LIB_YWXML_TJXXCX_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CTjxxhz.h"
#include "SysMacDef.h"

#define  TJXXCX_MONTHMAX 6

namespace middleware
{
/**
 *@class CTjxxcx
 *@brief 统计信息查询
 */
class CTjxxcx : public CYWXmlBase
{


public:

	CTjxxcx(XMLConstruct *construct, XMLParse *parse);
	~CTjxxcx();
	
	INT32 Execute(); 


private:
	/*!
	@函数名: XmlParse
	@brief 统计信息查询：输入参数解析（解析XML文件）
	@param[in]  parse		XML解析类
	@param[out]  tjxxhz	统计信息汇总类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, CTjxxhz *tjxxhz);

	/*!
	@函数名: XmlBuild
	@brief 统计信息查询：输出参数组装（组装XML文件）
	@param[in]  construct		XML组装类
	@param[in]  retInfo		返回信息类
	@param[in]  tjxxhz			统计信息汇总类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo, CTjxxhz *tjxxhz, INT32 MonthCount);

		
};

}
#endif


