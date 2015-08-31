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


//���ܣ�	��˰�̿�����ÿ�γ�ʼ��ʱ���ã�
//������	[IN]��˰�̿���[9]+������[12]
//		[IN]size-�����ܳ���30
//���أ�	0-�ɹ�����0-������
unsigned int jsk_open_r(unsigned char *code, unsigned short size);

//���ܣ� ��˰�̲�����ִ�о������ʱ����
//������ [IN]pp1-��Ӧ���ò�ͬ��˰�̹���
//	[IN]pp2-���pp1�����ý�˰�̹���
//	[IN]INBUFF-�������ݣ���СӦ���ڵ���inLen+1
//	[IN]inLen-�������ݳ���
//	[OUT]OUTBUFF-������ݣ���СӦ���ڵ���*outLen+1
//	[OUT]*outLen-������ݳ���
//���أ�	0-�ɹ�����0-������
unsigned int jsk_operate_r(IN unsigned char pp1, IN unsigned char pp2, IN unsigned char *INBUFF, IN unsigned short inLen, OUT unsigned char *OUTBUFF, OUT unsigned short *outLen);

//���ܣ�	��˰�̹ؿ���������ϵ���
//������	��
//���أ�	0-�ɹ�����0-������
unsigned int jsk_close_r();


// #ifdef __cplusplus
// }
// #endif
#endif


