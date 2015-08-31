/*! \file    md5c.h
   \brief    ����md5ǩ��
 */

#ifndef __LIB_MD5C_H
#define __LIB_MD5C_H

#include <stdio.h>
#include "comdatatype.h"
#include "SYSModuleHeader.h"

#if (USE_MD5_FUNC!=0)


#ifdef __cplusplus
extern "C"
{
#endif

/* MD5 context. */
typedef struct 
{
	UINT32 state[4];                                   	/* state (ABCD) */
	UINT32 count[2];        							/* number of bits, modulo 2^64 (lsb first) */
	UINT8  buffer[64];                        		 	/* input buffer */
} MD5_CTX;


/*!
@brief MD5�㷨��ʼ����
@param[out] MD5_CTX*  ���md5�������
*/
void MD5Init_skj (MD5_CTX *);

/*!
@brief ����MD5ǩ����
@param[in] MD5_CTX*  md5�������
@param[in] UINT8*  ��ǩ�����ִ�
@param[in] UINT32  ��ǩ�����ĳ���
*/
void MD5Update_skj (MD5_CTX *, UINT8 *, UINT32);

/*!
@brief MD5ǩ����������
@param[out] UINT8*  ���MD5ǩ�����
@param[in] MD5_CTX*  md5�������
*/
void MD5Final_skj (UINT8 *, MD5_CTX *);


extern MD5_CTX *g_MD5_CTX;			/**< ������md5���������ȫ�ֱ���	*/


#ifdef __cplusplus
}
#endif


#endif	//USE_MD5_FUNC

#endif	//__MD5C_H

