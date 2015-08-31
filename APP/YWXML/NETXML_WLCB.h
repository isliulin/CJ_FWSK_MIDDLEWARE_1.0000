/*! \file   NETXML_WLCB.h
   \brief    款机调用的中间件接口 业务: 网络抄报
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_NETXML_WLCB_H
#define LIB_NETXML_WLCB_H

#include "IncludeMe.h"
#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CWlcb
 *@brief 网络抄报
 */
class CWlcb: public CYWXmlBase
{

public:

	CWlcb(XMLConstruct *construct, XMLParse *parse);
	~CWlcb();
	
	INT32 Execute(); 


private:

	/*!
	@brief 网络抄报：输入参数解析（解析XML文件）
	@param[in]  pXmlParse XML解析类
	@param[out]  Sq		属期
	@param[out]  Fpmx	发票明细
	@param[out]  Fpdxx	发票段信息
	@param[out]  Fphzsj	发票汇总数据
	@param[out]  FpmxCount	发票明细数
	@param[out]  Qtxx	其他信息
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, string &Sq, string &Fpmx, string &Fpdxx, string &Fphzsj, string &Szfphz, UINT8 &FpmxCount, string &Qtxx);
	
	/*! 
	@brief 网络抄报：输出参数组装（组装成XML文件） 
	@param[in] pInvVol 指向发票信息表的指针 
	@param[in] Count 上传发票明细个数
	@param[out] construct  XML构造类
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlBuild(XMLConstruct *construct, UINT8 Count, Return_Info *retInfo);	
};

}
#endif



