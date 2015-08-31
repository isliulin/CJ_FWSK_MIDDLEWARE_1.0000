
/*! \file     ServWlcb.cpp
   \brief   网络抄报和网络清卡共用数据类
   \author   yy
   \version  1.0
   \date     2015 
*/



#include "ServWlcb.h"


#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"



CServWlcb::CServWlcb()
{
	DBG_PRINT(("进入CServWlcb::CServWlcb()"));
	//-----------------------------------
	m_cssj = "";			/**< 抄税时间 */
	m_islock = "";		/**< 金税盘是否为锁死期(Y/N) */
	m_zqbs = "";			/**< 是否为征期报税 */
	m_hzxx = "";			/**< 汇总信息（密文） */
	m_qkxx = "";			/**< 清卡信息（密文）*/
	m_ssqrs = "";		/**< 锁死期日数 */
	m_fplxdm = "";
	
	DBG_PRINT(("退出CServWlcb::~CServWlcb()"));
}

CServWlcb::~CServWlcb()
{

}













