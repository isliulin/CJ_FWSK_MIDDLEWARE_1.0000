#ifndef __SYS_ARG_MAC_H
#define __SYS_ARG_MAC_H


//系统参数ID号-收款机初始化标志 0:未初始化 1:初始化
#define SYS_MACHINE_INIT_FLAG			50

//系统参数ID号-收款机初始化日期
#define SYS_INIT_DATE					51	

//系统参数ID号-抄报标志 1:已抄报 0:未抄报
#define SYS_INV_DELIVER_FLAG			52

//系统参数ID号-申报标志 1:已申报 0:未申报
#define SYS_DECLARE_FLAG				53	

//系统参数ID号-锁死期 */
#define SYS_BLOCKAGE_DATE				54	

//系统参数ID号-分机号
#define SYS_FJH							55

//系统参数ID号-上次更新权限日期
#define	SYS_INFO_UPDATE_DATE			56


//系统参数ID号-串口波特率
#define	SYS_SERIAL_BAUDRATE				61


//系统参数ID号-口令
#define	SYS_ZS_PWD					   100

//系统参数ID号-税控设备口令
#define	SYS_SKSB_PWD					101

#endif
