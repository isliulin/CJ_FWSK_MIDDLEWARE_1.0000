/*! \file    NETXML_WLLQFP.h
   \brief    款机调用的中间件接口 业务3.6 网络领取发票
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_NETXML_WLLQFP_H
#define LIB_NETXML_WLLQFP_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvVol.h"

namespace middleware
{
/**
 *@class CWllqfp
 *@brief 网络领取发票
 */
class CWllqfp : public CYWXmlBase
{


public:

	CWllqfp(XMLConstruct *construct, XMLParse *parse);
	~CWllqfp();
	
	INT32 Execute(); 


private:
	/*!
	@函数名: XmlParse
	@brief 网络领取发票：输入参数解析（解析XML文件）
	@param[in]  parse		XML解析类
	@param[out]  invvol	发票领用信息
	@param[out]  strQtxx	其他信息
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, CInvVol *invvol, string &strQtxx);

	/*!
	@函数名: XmlBuild
	@brief 网络领取发票：输出参数组装（组装XML文件）
	@param[in]  construct		XML组装类
	@param[in]  retInfo		返回信息类
	@param[in]  invvol			发票领用信息表
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo, CInvVol *invvol);

		
};

}
#endif







































