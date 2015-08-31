/*! \file    commonFunc.h
   \brief    ͨ�ú����Ķ����ļ�
   \author   zl
 */

#ifndef LIB_COMMON_FUNCTION_H
#define LIB_COMMON_FUNCTION_H

#include "comdatatype.h"
#include "SYSModuleHeader.h"

#ifdef __cplusplus
extern "C"
{
#endif


/*!
@brief ��Сд���ת���ɴ�д���
@param[in] Amount �������λΪ��
@param[in] outBuffLen ָ�����������outBuff�Ĵ�С������С��64
@param[out] outBuff �����д���,��С��64�ֽ�
@return  NULL-ʧ�ܣ�����ɹ�������ָ���д���ľ��
*/
char *ChineseAmount(INT64 Amount, char *outBuff,UINT8 outBuffLen);


/*!
@brief ��ʱ������ʹ��nanosleep����alarm��Ϻ�����ʣ�����ʱ
@param[in] ms ��ʱ���ȣ���λ����
*/
void CommonSleep(int ms);


#if (USE_ICONV_LIB!=0)
/*!
@brief �ַ���ת������
@param[in] from_charset ԭ�ַ������ͣ���"gbk"��
@param[in] to_charset Ŀ���ַ������ͣ���"utf-8"��
@param[in] inStr ������ַ���
@param[in] inlen �����ַ����ĳ���
@param[out] **outStr �����ַ������贫��ָ�������
@return 0 - �ɹ���-1 - open����-2 - ת������
*/
int code_convert(char *from_charset, char *to_charset, 
				 const char *inStr, int inlen, char **outStr);

#endif	//USE_ICONV_LIB


#ifdef __cplusplus
}
#endif

#endif	//COMMON_FUNCTION_H
