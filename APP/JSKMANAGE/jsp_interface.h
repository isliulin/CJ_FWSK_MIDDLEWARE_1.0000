/********************************************************************
	filename: 	jsp_interface.h
	author:		lijinyan@aisino.com
	
	purpose:	
*********************************************************************/
#ifndef _LIB_JSP_INTERFACE_H_
#define _JSP_INTERFACE_H_

#include <stdio.h>
#ifndef IN
#define IN
#define OUT
#define IN_OUT
#endif

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

//#define __int64 long long

// #ifdef __cplusplus
// extern "C" {
// #endif


//功能：	金税盘开卡：每次初始化时调用；
//参数：	[IN]金税盘口令[9]+款机编号[12]
//		[IN]size-口令总长度30
//返回：	0-成功；非0-错误码
unsigned int jsk_open_r(unsigned char *code, unsigned short size);

//功能： 金税盘操作，执行具体操作时调用
//参数： [IN]pp1-对应调用不同金税盘功能
//	[IN]pp2-配合pp1，调用金税盘功能
//	[IN]INBUFF-输入数据，大小应大于等于inLen+1
//	[IN]inLen-输入数据长度
//	[OUT]OUTBUFF-输出数据，大小应大于等于*outLen+1
//	[OUT]*outLen-输出数据长度
//返回：	0-成功；非0-错误码
unsigned int jsk_operate_r(IN unsigned char pp1, IN unsigned char pp2, IN unsigned char *INBUFF, IN unsigned short inLen, OUT unsigned char *OUTBUFF, OUT unsigned short *outLen);

//功能：	金税盘关卡，操作完毕调用
//参数：	无
//返回：	0-成功；非0-错误码
unsigned int jsk_close_r();


// #ifdef __cplusplus
// }
// #endif
#endif


