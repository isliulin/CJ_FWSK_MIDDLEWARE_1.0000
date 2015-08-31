/*! \file    YWXML_FPKJ.h
   \brief    款机调用的中间件接口 业务: 发票开具
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_FPKJ_H
#define LIB_YWXML_FPKJ_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvHead.h"
#include "CInvDet.h"
#include "arithmetic.h"

namespace middleware
{
/**
 *@class CFpkj
 *@brief 发票开具
 */
class CFpkj: public CYWXmlBase
{

public:

	CFpkj(XMLConstruct *construct, XMLParse *parse);
	~CFpkj();
	
	INT32 Execute(); 


private:

	/*!
	@brief 发票开具：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@param[out]  pInvInfo  发票内容
	@param[out]  hyfl	  行业分类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, CInvHead *pInvInfo);
	
	/*! 
	@brief 发票开具：输出参数组装（组装成XML文件） 
	@param[in] pInvVol 指向发票信息表的指针 
	@param[in] retInfo 返回信息指针息类对象
	@param[out] construct  XML构造类
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, CInvHead *pInvInfo, Return_Info *retInfo);	
};

}
#endif



