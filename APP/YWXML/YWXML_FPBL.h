/*! \file    YWXML_FPBL.h
   \brief    款机调用的中间件接口 业务2.28.发票补录
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_FPBL_H
#define LIB_YWXML_FPBL_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CFpbl
 *@brief 2.28.发票补录
 */
class CFpbl : public CYWXmlBase
{


public:

	CFpbl(XMLConstruct *construct, XMLParse *parse);
	~CFpbl();
	
	INT32 Execute(); 


private:
	/*!
	@brief 发票补录：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@param[out]  StartDate		报税起始日期
	@param[out]  EndDate		报税截止日期
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT32 &StartDate, UINT32 &EndDate);
	
	/*!
	@brief 发票补录：输出参数组装（组装成XML文件）
	@param[in]   retInfo	返回结果
	@param[out]  construct  构造XML类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);

		
};

}
#endif



