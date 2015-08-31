/*! \file    YWXML_KLBG.h
   \brief    款机调用的中间件接口 业务: 口令变更
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_KLBG_H
#define LIB_YWXML_KLBG_H

#include "IncludeMe.h"
#include "YWXmlBase.h"

namespace middleware
{

/**
 *@class CKlbg
 *@brief 口令变更
 */
class CKlbg: public CYWXmlBase
{

public:

	CKlbg(XMLConstruct *construct, XMLParse *parse);
	~CKlbg();
	
	INT32 Execute(); 

private:

	/*!
	@brief 口令变更：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@param[out] ykl 原口令 
	@param[out] xkl 新口令
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &ykl, string &xkl);
	
	/*! 
	@brief 口令变更：输出参数组装（组装成XML文件） 
	@param[in] retInfo 返回信息指针
	@param[out] construct  XML构造类
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);	
};

}
#endif



