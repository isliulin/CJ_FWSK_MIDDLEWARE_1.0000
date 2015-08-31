/*! \file    YWXML_HQLXSJ.h
   \brief    款机调用的中间件接口 业务2.28.获取离线相关数据
   \author   MYF
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_HQLXSJ_H
#define LIB_YWXML_HQLXSJ_H

#include "IncludeMe.h"
#include "YWXmlBase.h"

namespace middleware
{
/**
 *@class HQLXSJ
 *@brief 获取离线相关数据
 */
class CHqlxsj : public CYWXmlBase
{


public:

	CHqlxsj(XMLConstruct *construct, XMLParse *parse);
	~CHqlxsj();
	
	INT32 Execute(); 


private:
	/*!
	@函数名: XmlParse
	@brief 获取离线相关数据：输入参数解析（解析XML文件）
	@param[in]  parse		XML解析类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);

	/*!
	@函数名: XmlBuild
	@brief 获取离线相关数据：输出参数组装（组装XML文件）
	@param[in]  construct		XML组装类
	@param[in]  invvol		发票领用信息表
	@param[in]  strLgry		领购人员
	@param[in]  retInfo		返回信息类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, UINT32 &wscfpzs, string &wscfpsj, INT64 &wscfpljje, Return_Info *retInfo);

		
};

}
#endif



