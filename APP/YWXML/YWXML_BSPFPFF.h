/*! \file    YWXML_BSPFPFF.h
   \brief    款机调用的中间件接口 业务2.15 发票分发
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_BSPFPFF_H
#define LIB_YWXML_BSPFPFF_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvVol.h"

namespace middleware
{
/**
 *@class CBspfpff
 *@brief 发票分发
 */
class CBspfpff : public CYWXmlBase
{


public:

	CBspfpff(XMLConstruct *construct, XMLParse *parse);
	~CBspfpff();
	
	INT32 Execute(); 


private:
	/*!
	@函数名: XmlParse
	@brief 发票分发：输入参数解析（解析XML文件）
	@param[in]  parse		XML解析类
	@param[out]  invvol		发票领用信息
	@param[out]  jzlx	介质类型
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, CInvVol *invvol, UINT8 &jzlx);

	/*!
	@函数名: XmlBuild
	@brief 发票分发：输出参数组装（组装XML文件）
	@param[in]  construct		XML组装类
	@param[in]  retInfo		返回信息类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);

		
};

}
#endif













































