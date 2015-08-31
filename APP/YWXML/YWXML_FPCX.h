/*! \file    YWXML_FPCX.h
   \brief    款机调用的中间件接口 业务: 发票查询
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_FPCX_H
#define LIB_YWXML_FPCX_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvHead.h"
#include "CUserInfo.h"

namespace middleware
{

/**
 *@class CFpcx
 *@brief 发票查询
 */
class CFpcx: public CYWXmlBase
{

public:

	CFpcx(XMLConstruct *construct, XMLParse *parse);
	~CFpcx();
	
	INT32 Execute(); 

private:

	/*!
	@brief 发票查询：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@param[out]  cxfs	  查询方式
	@param[out]  cxtj     查询条件
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT8 &cxfs, string &cxtj);
	
	/*! 
	@brief 发票查询：输出参数组装（组装成XML文件） 
	@param[in] pInvInfo 指向发票信息的指针 
	@param[in] InvCOunt 查询到的发票张数 
	@param[in] pUserinfo 税控设备编号 
	@param[in] retInfo 返回信息指针息类对象
	@param[out] construct  XML构造类
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, CInvHead *pInvInfo, CUserInfo *pUserinfo, UINT8 InvCOunt, Return_Info *retInfo);	
};

}
#endif



