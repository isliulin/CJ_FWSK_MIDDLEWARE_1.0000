/*! \file    YWXML_LXXXXP.h
   \brief    款机调用的中间件接口 业务2.20.离线信息写盘
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_LXXXXP_H
#define LIB_YWXML_LXXXXP_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"

namespace middleware
{

/**
 *@class CLxxxxp
 *@brief 2.20.离线信息写盘
 */
class CLxxxxp : public CYWXmlBase
{


public:

	CLxxxxp(XMLConstruct *construct, XMLParse *parse);
	~CLxxxxp();
	
	INT32 Execute(); 


private:
	/*!
	@brief 离线信息写盘：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@param[out]  strLxxxmw 离线信息密文
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &strLxxxmw);
	
	/*!
	@brief 离线信息写盘：输出参数组装（组装成XML文件）
	@param[in]  Return_Info retInfo 返回结果
	@param[out]  construct  构造XML类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);

		
};

}
#endif



