/*! \file    YWXML_FPDR.h
   \brief    款机调用的中间件接口 业务2.23.发票读入
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_FPDR_H
#define LIB_YWXML_FPDR_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CFpdr
 *@brief 2.23.发票读入
 */
class CFpdr : public CYWXmlBase
{


public:

	CFpdr(XMLConstruct *construct, XMLParse *parse);
	~CFpdr();
	
	INT32 Execute(); 


private:
	/*!
	@brief 发票读入：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@param[out]  jzlx		介质类型
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT8 &jzlx);
	
	/*!
	@brief 发票读入：输出参数组装（组装成XML文件）
	@param[in]   retInfo	返回结果
	@param[out]  construct  构造XML类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);

		
};

}
#endif



