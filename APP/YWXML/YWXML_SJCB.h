/*! \file    YWXML_SJCB.h
   \brief    款机调用的中间件接口 业务2.17数据抄报
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_SJCB_H
#define LIB_YWXML_SJCB_H

#include "IncludeMe.h"
#include "YWXmlBase.h"

namespace middleware
{

/**
 *@class CSjcb
 *@brief 数据抄报
 */
class CSjcb : public CYWXmlBase
{


public:

	CSjcb(XMLConstruct *construct, XMLParse *parse);
	~CSjcb();
	
	INT32 Execute(); 


private:
	/*!
	@函数名: XmlParse
	@brief 数据抄报：输入参数解析（解析XML文件）
	@param[in]  parse		XML解析类
	@param[out]  jzlx		介质类型
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT8 &jzlx);

	/*!
	@函数名: XmlBuild
	@brief 数据抄报：输出参数组装（组装XML文件）
	@param[in]  construct	XML组装类
	@param[in]  chSq		属期
	@param[in]  chFpmx		发票明细
	@param[in]  chFpdxx		发票段信息
	@param[in]  chFphz		发票汇总数据
	@param[in]  chQtxx		其他信息
	@param[in]  retInfo		返回信息类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, string strSQ, string strFpmx, string strFpdxx, string strFphz, string strQtxx, Return_Info *retInfo);

		
};

}

#endif























