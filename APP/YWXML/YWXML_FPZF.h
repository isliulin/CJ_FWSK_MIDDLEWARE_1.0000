/*! \file    YWXML_FPZF.h
   \brief    款机调用的中间件接口 业务: 发票作废
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_FPZF_H
#define LIB_YWXML_FPZF_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvHead.h"

namespace middleware
{
/**
 *@class CFpzf
 *@brief 发票作废
 */
class CFpzf: public CYWXmlBase
{

public:

	CFpzf(XMLConstruct *construct, XMLParse *parse);
	~CFpzf();
	
	INT32 Execute(); 


private:

	/*!
	@brief 发票作废：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@param[out]  pInvInfo  发票内容
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, CInvHead *pInvInfo, UINT8 &zflx);
	
	/*! 
	@brief 发票作废：输出参数组装（组装成XML文件） 
	@param[in] pInvVol 指向发票信息表的指针 
	@param[in] retInfo 返回信息指针息类对象
	@param[out] construct  XML构造类
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, CInvHead *pInvInfo, Return_Info *retInfo);	
};

}
#endif



