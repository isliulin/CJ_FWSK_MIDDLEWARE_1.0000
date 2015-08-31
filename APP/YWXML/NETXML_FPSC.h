/*! \file    NETXML_FPSC.h
   \brief    款机调用的中间件接口 业务: 发票上传
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_NETXML_FPSC_H
#define LIB_NETXML_FPSC_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CFpsc
 *@brief 发票上传
 */
class CFpsc: public CYWXmlBase
{

public:

	CFpsc(XMLConstruct *construct, XMLParse *parse);
	~CFpsc();
	
	INT32 Execute(); 


private:

	/*!
	@brief 发票明细上传：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@param[out]  Fpmx	发票明细
	@param[out]  FpmxCount	发票明细数
	@param[out]  Fpzs		发票明张数
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &Fpmx, UINT8 &FpmxCount, UINT32 &Fpzs);
	
	/*! 
	@brief 发票明细上传：输出参数组装（组装成XML文件） 
	@param[in] pInvVol 指向发票信息表的指针 
	@param[in] Count 上传发票明细个数
	@param[out] construct  XML构造类
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, UINT8 Count, Return_Info *retInfo);	
};

}
#endif



