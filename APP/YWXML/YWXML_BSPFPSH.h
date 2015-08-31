/*! \file    YWXML_BSPFPSH.h
   \brief    款机调用的中间件接口 业务2.16 发票收回
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_BSPFPSH_H
#define LIB_YWXML_BSPFPSH_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvVol.h"

namespace middleware
{
/**
 *@class CBspfpsh
 *@brief 发票收回
 */
class CBspfpsh: public CYWXmlBase
{


public:

	CBspfpsh(XMLConstruct *construct, XMLParse *parse);
	~CBspfpsh();
	
	INT32 Execute(); 


private:
	/*!
	@函数名: XmlParse
	@brief 发票收回：输入参数解析（解析XML文件）
	@param[in]  parse		XML解析类
	@param[out]  invvol		发票领用信息
	@param[out]  strJzlx	介质类型
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, CInvVol *invvol, UINT8 &jzlx);

	/*!
	@函数名: XmlBuild
	@brief 发票收回：输出参数组装（组装XML文件）
	@param[in]  construct		XML组装类
	@param[in]  retInfo		返回信息类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);

		
};

}
#endif












































