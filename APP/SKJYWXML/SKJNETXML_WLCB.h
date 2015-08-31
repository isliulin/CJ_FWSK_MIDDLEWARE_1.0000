/*! \file   NETXML_WLCB.h
   \brief    款机调用的中间件接口 业务: 网络抄报
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef SKJ_NETXML_WLCB_H
#define SKJ_NETXML_WLCB_H

#include "IncludeMe.h"
#include "SKJYWXmlBase.h"


/**
 *@class CWlcb
 *@brief 网络抄报
 */
class CSKJWlcb: public CSKJYWXmlBase
{

public:
	/*!
	@param[in]  Sq		属期
	@param[in]  Fphzsj	发票汇总数据
	@param[in]  FpmxCount	发票明细数
	@param[in]  Qtxx	其他信息
	*/
	CSKJWlcb(CYWXML_GY &ywxml_gy, string Sq, string Fphzsj, string Qtxx);
	~CSKJWlcb();
	
	/*!
	@brief 网络抄报：输入参数组装（组装成XML文件）
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*! 
	@brief 网络抄报：输出参数解析（解析XML文件）
	@param[in] pInvVol 指向发票信息表的指针 
	@param[in] Count 上传发票明细个数
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlParse();	

	UINT32 m_Count;
	string m_Sq;
	string m_Fphzsj;
	UINT32 m_FpCount;
	string m_Qtxx;
};

#endif



