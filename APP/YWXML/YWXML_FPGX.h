/*! \file    YWXML_FPGX.h
   \brief    款机调用的中间件接口 业务2.22.发票更新
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_FPGX_H
#define LIB_YWXML_FPGX_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CFpgx
 *@brief 2.22.发票更新
 */
class CFpgx : public CYWXmlBase
{


public:

	CFpgx(XMLConstruct *construct, XMLParse *parse);
	~CFpgx();
	
	INT32 Execute(); 


private:
	/*!
	@brief 发票读入：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@param[out]  strScqrbw  上传成功确认报文
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &strScqrbw);
	
	/*!
	@brief 发票读入：输出参数组装（组装成XML文件）
	@param[in]  retInfo 返回结果
	@param[out]  construct  构造XML类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);

		
};

}
#endif



