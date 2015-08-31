/*! \file    YWXML_FPSSSC.h
   \brief    款机调用的中间件接口 业务2.21.发票实时上传
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_FPSSSC_H
#define LIB_YWXML_FPSSSC_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CFpsssc
 *@brief 2.21.发票实时上传
 */
class CFpsssc : public CYWXmlBase
{


public:

	CFpsssc(XMLConstruct *construct, XMLParse *parse);
	~CFpsssc();
	
	INT32 Execute(); 


private:
	/*!
	@brief 发票读入：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@param[out]  nFpzs	发票张数
	@param[out]  czlx	操作类型
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT32 &nFpzs, UINT8 &czlx);
	
	/*!
	@brief 发票读入：输出参数组装（组装成XML文件）
	@param[in]  pUserinfo 纳税户信息
	@param[in]  strCurTime 当前时间YYYYMMDDHHMMSS
	@param[in]  Return_Info retInfo 返回结果
	@param[out]  construct  构造XML类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, UINT32 nFpzs, UINT8 czlx, 
						string strFpmx, Return_Info *retInfo);

		
};

}
#endif



