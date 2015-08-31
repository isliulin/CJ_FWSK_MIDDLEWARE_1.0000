/*! \file    base64.h
   \brief    base64������뺯���Ķ����ļ�
   \author   zl
 */

#ifndef __LIB_BASE64_H_
#define __LIB_BASE64_H_

#ifdef __cplusplus
extern "C"
{
#endif


/*!
@brief �����޸ĵ�Base64���뺯��������ǰ��ʹ��ͬһ��BUFF�Խ�ʡ�ڴ档
@param[in,out] buf  ����ԭʼ���ݣ����Base64����������
@param[in] vlen  ԭʼ���ݳ���
@warning ����֮�����ݳ��Ȼ�����Լ4/3��������ڵ���ǰ��ȷ�ϸ���BUF�㹻��
*/
void Base64_Encode_2(unsigned char *buf, int vlen);


/*!
@brief �����޸ĵ�Base64���뺯��������ǰ��ʹ��ͬһ��BUFF�Խ�ʡ�ڴ档
@param[in,out] value  ����Base64��������ݣ��������������
@param[in] rlen  ���������ݳ���
*/
void Base64_Decode_2(char *value, int *rlen);	


/*!
@brief ԭʼ��Base64���뺯����
@param[in] value  ԭʼ����
@param[in] vlen  ԭʼ���ݳ���
@param[out] pcBase64Value  Base64�������������
@note �����ڴ����ƣ�����ƽ̨��ҵ������δʹ�ô˺�����
*/
void Base64_Encode(unsigned char *value, int vlen, char *pcBase64Value);  

/*!
@brief ԭʼ��Base64���뺯����
@param[in] value  Base64���������
@param[out] result  Base64�������������
@param[out] rlen  Base64������������ݳ���
@note �����ڴ����ƣ�����ƽ̨��ҵ������δʹ�ô˺�����
*/
void Base64_Decode(char *value, unsigned char *result, int *rlen);  



#ifdef __cplusplus
}
#endif

#endif	//__BASE64_H_


