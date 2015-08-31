#ifndef __CGLOBAL_ARG_H
#define __CGLOBAL_ARG_H

#include "IncludeMe.h"
#include "SysMacDef.h"
#include "TDateTime.h"
#include "CInvVol.h"
#include "CUserInfo.h"
#include "CUserMore.h"
#include "CInvKind.h"
#include "JSKInfoFunc.h"
#include "CNetPara.h"

class CGlobalArgLib;

/*! 系统常用参数变量类对象，整个应用程序共有一个 */
extern CGlobalArgLib *g_globalArgLib;


/**
 *@class CGlobalArg 
 *@brief 常用全局变量与系统参数
 *@brief 该类在程序启动以后，只会产生一个全局对象。
 *@brief 对象的成员变量包含应用程序常用的全局变量和系统参数。
 */
class CGlobalArgLib
{
public:

	/**
	 * brief 初始化公共参数值
	 * @param void
	 * @return UINT8 
	 */
	INT32 InitGlobalArg();
	/**
	 * brief 计算申报期内的正票、红票累计金额；发票卷正红票累计金额
	 * @param void
	 * @return UINT8 
	 */
	UINT8 CalculateSum(void);

	/*!
	*@brief 部分数据库内容滚动
	)@param[out] nIfRolled 是否实施了滚动操作 1：是，0：否
	*@return  1： 成功； 其它：失败
	*/
	UINT8 RollData(UINT8 &nIfRolled);

	/**
	 * brief 得到CGlobalArg的唯一对象
	 * @param void
	 * @return static CGlobalArg* 
	 */
	static CGlobalArgLib* GetInstance(void);

	/**
	 * brief 初始化各个系统值
	 * @param void
	 * @return UINT8 
	 */
	UINT8 InitSysArg(void);

	
	//-----------------------------------
	// 系统参数区
	//-----------------------------------
	UINT8  m_initFlag;			/**< 初始化标志 */
	UINT32 m_initDate;			/**< 机器初始化日期 */
	UINT32 m_updateDate;		/**< 更新权限日期 */
	UINT8  m_invDeliverFlag;	/**< 抄报标志 */
	UINT8  m_decFlag;			/**< 申报标志 */
	UINT32 m_startDecDate;		/**< 申报起始日期 */
	UINT32 m_decDate;			/**< 申报截止日期 */

	UINT8  m_decMedium;			/**< 申报介质 */
	//zcy edit 添加每卷张数全局变量
	UINT32  m_perReccount;    /**< 每卷张数*/

	UINT8  m_fjh;				//分机号
	UINT8  m_netOn;            /**< 登录验证是否成功 1：成功，0：失败 */
	UINT8  m_pthreadFlag;		/**< 次线程运行标志 1：运行  0停止 */
	string m_pthreadErr;		/**< 次线程返回错误 */
	string m_pthreadNsrsbh;
	string m_pthreadJqbh;
	string m_pthreadSksbbh;
	string m_pthreadSksbkl;
	string m_pthreadFplxdm;
	string m_pthreadKpjh;

	//-----------------------------------
	// 销售限额参数区
	//-----------------------------------
	INT64  m_normalSum;			/**< 申报期正票累计金额 */
	INT64  m_returnSum;			/**< 申报期红票累计金额 */
	INT64  m_normalVolSum;		/**< 发票卷正票累计金额 */
	INT64  m_returnVolSum;		/**< 发票卷红票累计金额 */
	
	//-----------------------------------
	// 公共参数区
	//-----------------------------------
	UINT8		m_bootStatus;	/**< 款机启动检测状态 */

	CInvVol		*m_curInvVol;	/**< 当前卷信息 */
	CUserInfo	*m_corpInfo;	/**< 纳税户信息 */
	CUserMore   *m_usermore;    /**< 纳税户补充信息*/
	CInvKind    *m_invKind;     /**< 票种信息*/
	CNetPara    *m_netPara;		/**< 网络参数 */

	string		m_strSlxlh;			/**< 受理序列号 */
	UINT32      m_InvServNum;        /**< 当前缓存发票数量 */
	INT64       m_InvServSum;		/**< 当前缓存发票金额 */
	string		m_strHashNo;		/**< 哈希税号 */


	//-----------------------------------
	// 滚动参数区
	//-----------------------------------
	INT32 m_invCount;			/**< INV_HEAD表的当前记录条数 */
	INT32 m_rtInvCount;			/**< RT_INV表的当前记录条数 */
	INT32 m_invSumCount;		/**< INV_SUM表的当前记录条数 */

	INT32 m_clientCount;		/**< CLIENT表的当前记录条数 */
	INT32 m_operatorCount;		/**< OPERATOR表的当前记录条数 */
	INT32 m_pluCount;			/**< PLU表的当前记录条数 */

	
	//-----------------------------------
	// 税控设备参数区
	//-----------------------------------
	UINT8   m_initParaFlag;		/**< 税控设备参数初始化标志 */
	string	m_strSksbbh;		/**< 税控设备编号 */
	string	m_strSksbkl;		/**< 税控设备口令 */
	string	m_strBspbh;			/**< 报税盘编号 */
	UINT32  m_serialBaudRate;	/**< 串口波特率 */	
	string  m_strZskl;          /**< 证书口令 */


private:
	/**
	 * CGlobalArg
	 * @return 
	 */
	CGlobalArgLib();

	/**
	 * ~CGlobalArg
	 * @return 
	 */
	~CGlobalArgLib();
	
	static CGlobalArgLib *m_globalArgLib;	/**< CGlobalArg对象，静态 */
	
};



/*! 系统常用参数变量类对象，整个应用程序共有一个 */
extern CGlobalArgLib *g_globalArgLib;


#endif
