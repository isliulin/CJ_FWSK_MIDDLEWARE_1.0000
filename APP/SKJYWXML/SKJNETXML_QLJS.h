/*! \file   NETXML_QLJS.h
   \brief    款机调用的中间件接口 业务: 监控回传, 进行清零解锁
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef SKJ_NETXML_QLJS_H
#define SKJ_NETXML_QLJS_H

#include "IncludeMe.h"
#include "SKJYWXmlBase.h"


/**
 *@class CQljs
 *@brief 进行清零解锁
 */
class CSKJQljs: public CSKJYWXmlBase
{

public:

	/*!
	@brief 进行清零解锁信息查询
	@param[in] ywlx 业务类型
	@param[in]  Kpjh		开票机号
	@param[in]  FpmxCount	发票明细数
	@param[out] Fpjkmw 发票监控密文
	@param[out] Szjkmw 时钟监控密文
	@param[out] Count 上传发票明细个数
	*/
	CSKJQljs(CYWXML_GY &ywxml_gy, string Qtxx,string &Fpjkmw);
	~CSKJQljs();

	/*!
	@brief 进行清零解锁：输入参数组装（组装成XML文件）
	@return 1  SUCCESS， 0  FAILURE
	*/
	INT32 XmlBuild();
	
	/*! 
	@brief 进行清零解锁：输出参数解析（解析XML文件） 
	@return 1 SUCCESS， 0 FAILURE 
	*/
	INT32 XmlParse();
	
	string &m_Fpjkmw;
	UINT32 m_Count;

	UINT32 m_FpCount;
	string m_Qtxx;
};


#endif



