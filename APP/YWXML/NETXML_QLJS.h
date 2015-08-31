/*! \file   NETXML_QLJS.h
   \brief    款机调用的中间件接口 业务: 3.4.清零解锁
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_NETXML_QLJS_H
#define LIB_NETXML_QLJS_H

#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "ServWlcb.h"

namespace middleware
{
/**
 *@class CQljs
 *@brief 监控回传
 */
class CQljs: public CYWXmlBase
{

public:

	CQljs(XMLConstruct *construct, XMLParse *parse);
	~CQljs();
	
	INT32 Execute(); 


private:

	/*!
	@brief 监控回传：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@param[out]  Kpjh		开票机号
	@param[out]  FpmxCount	发票明细数
	@param[out]  Qtxx	其他信息
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &Kpjh, UINT8 &FpmxCount, string &Qtxx);
	
	/*! 
	@brief 监控回传：输出参数组装（组装成XML文件） 
	@param[in] pInvVol 指向发票信息表的指针 
	@param[in] Fpjkmw 发票监控密文
	@param[in] Szjkmw 时钟监控密文
	@param[in] Count 上传发票明细个数
	@param[out] construct  XML构造类
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, CServWlcb *ServWlcb, UINT8 Count, Return_Info *retInfo);	
};

}
#endif



