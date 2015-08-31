/*! \file    YWXML_SKPXXCX.h
   \brief    款机调用的中间件接口 业务2.2.税控设备信息查询
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_SKPXXCX_H
#define LIB_YWXML_SKPXXCX_H


#include "IncludeMe.h"

#include "YWXmlBase.h"
#include "CUserInfo.h"

namespace middleware
{
/**
 *@class CSkpxxcx
 *@brief 2.2.税控设备信息查询
 */
class CSkpxxcx:  public CYWXmlBase
{


public:

	CSkpxxcx(XMLConstruct *construct, XMLParse *parse);
	~CSkpxxcx();
	
	INT32 Execute(); 


private:
	/*!
	@brief 税控设备信息查询：输入参数解析（解析XML文件）
	@param[in]  parse XML解析类
	@param[out]  strSksbkl  税控设备口令
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);
	
	/*!
	@brief 税控设备信息查询：输出参数组装（组装成XML文件）
	@param[in]  pUserinfo 纳税户信息
	@param[in]  strCurTime 当前时间YYYYMMDDHHMMSS
	@param[in]  retcode 返回代码
	@param[in]  retmsg 返回信息
	@param[out]  construct  构造XML类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, CUserInfo *pUserinfo, string strCurTime, Return_Info *retInfo);

		
};

}
#endif



