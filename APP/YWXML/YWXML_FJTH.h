/*! \file    YWXML_FJTH.h
   \brief    款机调用的中间件接口 业务2.24 分机退回
   \author   zfj
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_FJTH_H
#define LIB_YWXML_FJTH_H


#include "IncludeMe.h"
#include "YWXmlBase.h"

namespace middleware
{

/**
 *@class CFjth
 *@brief 分机退回
 */
class CYWXMLFjth : public CYWXmlBase
{


public:

	CYWXMLFjth(XMLConstruct *construct, XMLParse *parse);
	~CYWXMLFjth();
	
	INT32 Execute(); 


private:
	/*!
	@brief 分机退回：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT8 &jzlx);
	
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo);

		
};

}
#endif



