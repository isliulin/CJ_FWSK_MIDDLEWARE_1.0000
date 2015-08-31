/*! \file     ServWlcb.h
   \brief   网络抄报和网络清卡共用数据类
   \author	  yy
   \version  1.0
   \date     2015 
*/

#ifndef __LIB_SERV_WLCB_H
#define __LIB_SERV_WLCB_H

#include "IncludeMe.h"
#include "SysMacDef.h"


class CServWlcb;




/**
 *@class CServWlcb 
 *@brief 网络抄报和网络清卡共用数据类
 */
class CServWlcb
{
public:

	/**
	 * brief 初始化公共参数值
	 * @param void
	 * @return UINT8 
	 */
// 	UINT8 InitGlobalNetArg(string nsrsbh, string fxsh, string hxsh,				
// 								string  kpjh, string sbbh,	string slxlh);
	


	//-----------------------------------
	// 参数区
	//-----------------------------------
	string  m_cssj;			/**< 抄税时间 */
	string  m_islock;		/**< 金税盘是否为锁死期(Y/N) */
	string  m_zqbs;			/**< 是否为征期报税 */
	string  m_hzxx;			/**< 汇总信息（密文） */
	string  m_qkxx;			/**< 清卡信息（密文）*/
	string  m_ssqrs;		/**< 锁死期日数 */
	string  m_fplxdm;		/**< 发票类型代码 */

	/**
	 * CServWlcb
	 * @return 
	 */
	CServWlcb();

	/**
	 * ~CServWlcb
	 * @return 
	 */
	~CServWlcb();
	
	
};





#endif
