/*! \file     GlobalNetArg.h
   \brief   款机与局端交互的全局变量
   \author	  yy
   \version  1.0
   \date     2015 
*/

#ifndef __LIB_CGLOBAL_NET_ARG__H
#define __LIB_CGLOBAL_NET_ARG__H

#include "IncludeMe.h"
#include "SysMacDef.h"


class CGlobalNetArg;

/*! 款机与局端交互的全局变量类对象，整个应用程序共有一个 */
extern CGlobalNetArg *g_gNetArg;


/**
 *@class CGlobalNetArg 
 *@brief 款机与局端交互的全局变量
 *@brief 该类在程序启动以后，只会产生一个全局对象。
 *@brief 对象的成员变量包含应用程序常用的全局变量和系统参数。
 */
class CGlobalNetArg
{
public:

	/**
	 * brief 初始化公共参数值
	 * @param void
	 * @return UINT8 
	 */
	UINT8 InitGlobalNetArg(string nsrsbh, string fxsh, string hxsh,				
								string  kpjh, string sbbh,	string slxlh);
	
		/**
	 * brief 设置基本信息
	 * @param void
	 * @return UINT8 
	 */
	void SetBaseInfo(string nsrsbh, string kpjh, string sbbh);
	/**
	 * brief 设置哈希税号
	 * @param void
	 * @return UINT8 
	 */
	void SetHashNo(string hxsh, string addrNo);
	/**
	 * brief 设置发行税号
	 * @param void
	 * @return UINT8 
	 */
	void SetIssueNo(string fxsh);
	/**
	 * brief 底层版本
	 * @param void
	 * @return UINT8 
	 */
	void SetDcbb(string dcbb);
	/**
	 * brief 设置受理序列号
	 * @param void
	 * @return UINT8 
	 */
	void SetSlxlh(string slxlh);

	/**
	 * brief 设置证书口令
	 * @param void
	 * @return UINT8 
	 */
	void SetZskl(string zskl);
	void SetServId(string servId);
	void SetNsrsbh(string nsrsbh);
	/**
	 * brief 设置服务器网络参数
	 * @param void
	 * @return UINT8 
	 */
	void SetServPara(string servip, string servport, string servaddr);

	/**
	 * brief 得到CGlobalArg的唯一对象
	 * @param void
	 * @return static CGlobalArg* 
	 */
	static CGlobalNetArg* GetInstance(void);


	//-----------------------------------
	// 参数区
	//-----------------------------------
	string  m_nsrsbh;			/**< 企业税号 */
	string  m_kpjh;				/**< 开票机号，没有开票机号时值为0 */
	string  m_sbbh;				/**< 税控设备编号 */

	string  m_fxsh;				/**< 发行税号 */
	string  m_addrno;			/**< 地区编号 */
	string  m_hxsh;				/**< 哈希税号 */
	string  m_dcbb;				/**< 底层版本 */
	
	string  m_slxlh;			/**< 受理序列号 (取发票上传结果用)*/

	string  m_strzskl;			/**< 证书口令 */
	string  m_servId;			/**< 服务器ID */
	string  m_servIP;
	string  m_servPort;
	string  m_servAddr;

private:
	/**
	 * CGlobalNetArg
	 * @return 
	 */
	CGlobalNetArg();

	/**
	 * ~CGlobalNetArg
	 * @return 
	 */
	~CGlobalNetArg();
	
	static CGlobalNetArg *m_gNetArg;	/**< CGlobalNetArg对象，静态 */
	
};



/*! 系统常用参数变量类对象，整个应用程序共有一个 */
extern CGlobalNetArg *g_gNetArg;


#endif
