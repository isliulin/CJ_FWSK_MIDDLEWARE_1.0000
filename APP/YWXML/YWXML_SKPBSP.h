/*! \file    YWXML_SKPBSP.h
   \brief    款机调用的中间件接口 业务: 税控设备报税盘组合操作
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_SKPBSP_H
#define LIB_YWXML_SKPBSP_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CSkpBsp
 *@brief 税控设备报税盘组合操作
 */
class CSkpBsp: public CYWXmlBase
{

public:

	CSkpBsp(XMLConstruct *construct, XMLParse *parse);
	~CSkpBsp();
	
	INT32 Execute(); 

private:

	/*!
	@brief 税控设备报税盘组合操作：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@param[out]  Czlx 操作类型
	@param[out]  Hzxx 汇总信息
	@param[out]  Qtxx 其他信息
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT8 &Czlx, string &Hzxx, string &Qtxx);
	
	/*! 
	@brief 税控设备报税盘组合操作：输出参数组装（组装成XML文件） 
	@param[in] pInvVol 指向发票信息表的指针 
	@param[in] retInfo 返回信息指针息类对象
	@param[out] construct  XML构造类
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);	
};

}
#endif



