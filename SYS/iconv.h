/*! \file    iconv.h
   \brief    ��iconv��׼����GBK��UTF8ת������ش�����ȡ�������¿⡣
			 ҵ��㲻��ֱ�ӵ��ñ��ļ��еĽӿڣ��ɵ���commonFunc.h�е�code_convert����ʵ��ת��
   \author   ZL
   \version  1.0
   \date     2012-4-05
 */

#ifndef _LIB_ICONV_GBK_UTF8_H__
#define _LIB_ICONV_GBK_UTF8_H__

#include "iconv_lib.h"

#ifdef __cplusplus
extern "C"
{
#endif


                              
/*!
@brief ָ���ַ���ת������ʽ����ȡ�������
@param[in] from_charset ԭ�ַ������ͣ���"gbk"��
@param[in] to_charset Ŀ���ַ������ͣ���"utf-8"��
@return  �������
*/
iconv_t iconv_open(ICONV_CONST char* tocode, ICONV_CONST char* fromcode);

/*!
@brief ת������
@param[in] icd �������
@param[in] inbuf ԭ�ִ�
@param[in] inbytesleft ԭ�ִ���
@param[out] outbuf ����ִ�
@param[in,out] outbytesleft ���������������ȣ�����ʵ�ʳ���
*/                                    
size_t iconv (iconv_t icd,
              ICONV_CONST char* * inbuf, size_t *inbytesleft,
              char* * outbuf, size_t *outbytesleft);
              

/*!
@brief �ͷŲ������
@param[in] icd �������
*/
int iconv_close (iconv_t icd);
    
    
    
    
#ifdef __cplusplus
}
#endif

    
#endif
