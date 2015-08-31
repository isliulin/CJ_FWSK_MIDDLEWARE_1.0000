/*! \file    NETXML_WLLQFPJGQR.h
   \brief    款机调用的中间件接口 业务3.7 网络领取发票结果确认
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_NETXML_WLLQFPJGQR_H
#define LIB_NETXML_WLLQFPJGQR_H


#include "IncludeMe.h"
#include "YWXmlBase.h"

namespace middleware
{
/**
 *@class CWllqfpjgqr
 *@brief 网络领取发票结果确认
 */
class CWllqfpjgqr : public CYWXmlBase
{


public:

	CWllqfpjgqr(XMLConstruct *construct, XMLParse *parse);
	~CWllqfpjgqr();
	
	INT32 Execute(); 


private:
	/*!
	@函数名: XmlParse
	@brief 网络领取发票结果确认：输入参数解析（解析XML文件）
	@param[in]  parse		XML解析类
	@param[out]  invvol	发票领用信息
	@param[in]  strQtxx	其他信息
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, CInvVol *invvol, string &strQtxx);

	/*!
	@函数名: XmlBuild
	@brief 网络领取发票结果确认：输出参数组装（组装XML文件）
	@param[in]  construct		XML组装类
	@param[in]  retInfo		返回信息类
	@param[in]  invvol	发票领用信息
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo, CInvVol *invvol);

		
};

}
#endif


























