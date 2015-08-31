/*! \file    YWXML_SKSBBHCX.h
   \brief    款机调用的中间件接口 业务2.1 税控设备编号查询
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_SKSBBHCX_H
#define LIB_YWXML_SKSBBHCX_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"

namespace middleware
{

/**
 *@class CSksbbhcx
 *@brief 2.1.税控设备编号查询
 */
class CSksbbhcx : public CYWXmlBase
{


public:

	CSksbbhcx(XMLConstruct *construct, XMLParse *parse);
	~CSksbbhcx();
	
	INT32 Execute(); 


private:
	/*!
	@brief 2.1.税控设备编号查询：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);
	
	/*!
	@brief 税控设备编号查询：输出参数组装（组装成XML文件）
	@param[in]  sksbbh 税控设备编号
	@param[in]  bspbh 报税盘
	@param[in]  qtxx   其他信息
	@param[in]  retInfo 返回信息
	@param[out]  construct  构造XML类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, string sksbbh, string bspbh, string qtxx, Return_Info *retInfo);

		
};

}
#endif



