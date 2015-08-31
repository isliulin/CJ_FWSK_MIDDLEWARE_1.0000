/*! \file    YWXML_ERRUPINV.h
   \brief    款机调用的中间件接口 业务2.29.获取上传出错发票信息
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_ERRUPINV_H
#define LIB_YWXML_ERRUPINV_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvServ.h"

#define BSPFPCX_INVNUM 10
namespace middleware
{
/**
 *@class CErrUpInv
 *@brief 获取上传出错发票信息
 */
class CErrUpInv : public CYWXmlBase
{


public:

	CErrUpInv(XMLConstruct *construct, XMLParse *parse);
	~CErrUpInv();
	
	INT32 Execute(); 


private:
	/*!
	@函数名: XmlParse
	@brief 获取上传出错发票信息
	@param[in]  parse		XML解析类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);

	/*!
	@函数名: XmlBuild
	@brief 获取上传出错发票信息
	@param[in]  construct		XML组装类
	@param[in]  invvol		发票领用信息表
	@param[in]  strLgry		领购人员
	@param[in]  retInfo		返回信息类
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, UINT32 invNum, CDataInvServ *DataInvServ, Return_Info *retInfo);

		
};

}
#endif



