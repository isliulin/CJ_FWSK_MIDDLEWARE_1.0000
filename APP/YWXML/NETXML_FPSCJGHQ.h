/*! \file    NETXML_FPSCJGHQ.h
   \brief    款机调用的中间件接口 业务: 发票明细上传结果获取
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_NETXML_FPSCJGHQ_H
#define LIB_NETXML_FPSCJGHQ_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CFpscjghq
 *@brief 发票明细上传结果获取
 */
class CFpscjghq: public CYWXmlBase
{

public:

	CFpscjghq(XMLConstruct *construct, XMLParse *parse);
	~CFpscjghq();
	
	INT32 Execute(); 


private:

	/*!
	@brief 发票明细上传结果获取：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@param[out]  FpmxCount	发票明细数
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT8 &FpmxCount, string &qtxx);
	
	/*! 
	@brief 发票明细上传结果获取：输出参数组装（组装成XML文件） 
	@param[in] Mxjgmw 加密后的明细上传结果密文 
	@param[in] Count 上传发票明细个数
	@param[out] construct  XML构造类
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, string Mxjgmw, UINT8 Count, Return_Info *retInfo);	
};

}
#endif



