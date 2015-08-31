/*! \file    YWXML_BSPFPCX.h
   \brief    款机调用的中间件接口 业务2.14 报税盘发票查询
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_BSPFPCX_H
#define LIB_YWXML_BSPFPCX_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvVol.h"

#define BSPFPCX_INVNUM 100 //20150517_linzihao
namespace middleware
{
/**
 *@class CBspfpcx
 *@brief 报税盘发票查询
 */
class CBspfpcx : public CYWXmlBase
{


public:

	CBspfpcx(XMLConstruct *construct, XMLParse *parse);
	~CBspfpcx();
	
	INT32 Execute(); 


private:
	/*!
	@函数名: XmlParse
	@brief 发票分发：输入参数解析（解析XML文件）
	@param[in]  parse		XML解析类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);

	/*!
	@函数名: XmlBuild
	@brief 发票分发：输出参数组装（组装XML文件）
	@param[in]  construct		XML组装类
	@param[in]  invvol		发票领用信息表
	@param[in]  strLgry		领购人员
	@param[in]  retInfo		返回信息类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, UINT32 invNum, CInvVol *invvol, string strLgry, Return_Info *retInfo);

		
};

}
#endif



