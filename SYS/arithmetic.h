/*! \file    arithmetic.h
   \brief    ����ת������ѧ����һ��ĺ�������
   \author   zl
 */

#ifndef LIB_ARITHMETHIC_H
#define LIB_ARITHMETHIC_H

#include "comdatatype.h"

#ifdef __cplusplus
extern "C"
{
#endif


/*!
@brief ��16����HEX�ִ�ת��Ϊ���ӵ�ASC�ִ���
@note ����0x12,0x45,0xbc  --->   "1245bc"
@param[in] bin ԭ16����HEX��
@param[in] length ԭ16����HEX���ĳ���
@param[out] asc �����ASC�ִ�
@warning Ŀ��ASC�ִ����Ƚ���ԭ�ִ�����һ����
		 Ŀ��ASC�ִ�û����ĩβ�Զ����'\0'�ֽڡ�
*/
void bin2char(unsigned char *bin,char *asc,UINT32 length);

/*!
@brief ��ASC�ִ�ת��Ϊ16����HEX�ִ���
@note ����"1245bc"  --->   0x12,0x45,0xbc
@param[in] asc ԭASC�ִ�
@param[in] length ת�����HEX���ĳ��ȣ�����ASC�ִ����ȣ���
@param[out] bin �����HEX��
@warning ASC�ִ��в��ܺ���0��9��a��f��A��F������ַ���
		 ASC�ִ����ȱ�����2�ı�����
*/
void char2bin(unsigned char *bin, const char *asc, UINT32 length);

/*!
@brief ��BCD��ʽ��10�����ִ�ת��Ϊ10��������ֵ��
@note ����  0x12,0x45   --->   1245
@param[in] bin  ԭBCD��
@param[in] length  BCD���ĳ���
@return  ����ֵ
@warning ת�����ֵ���ܳ������α�������
*/
INT32 bin2int(unsigned char *bin, UINT32 length);

/*!
@brief ��10��������ֵת��ΪBCD��ʽ��10�����ִ���
@note ����  1245   --->   0x12,0x45
@param[in] int_value  10��������ֵ
@param[in] length  ת�����BCD������
@param[out] bin  �����BCD��
*/
void int2bin(unsigned char *bin,INT32 int_value,UINT32 length);

/*!
@brief �������ֽ����HEX��ת��Ϊ����ֵ�������ֽ��򣩡�
@note ����  0x03,0xE8   --->   1000 
@param[in] hex  ԭhex��
@param[in] length  hex������
@return  ����ֵ
@warning ת�����ֵ���ܳ������α�������
*/
INT32 hex2int(unsigned char *hex,UINT32 length);



/*!
@brief ������ֵ�������ֽ���ת��Ϊ�����ֽ����HEX����
@note ����  1000    --->   0x03,0xE8
@param[in] int_value  ����ֵ�������ֽ���
@param[in] length  ת�����HEX������
@param[out] hex  �����HEX��
*/
void int2hex(unsigned char *hex,UINT32 int_value,UINT32 length);

/*!
@brief ͬbin2char������
@param[in] bin ԭ16����HEX��
@param[in] length ԭ16����HEX���ĳ���
@param[out] str �����ASC�ִ�
@see bin2char
*/
void Hex2Char(unsigned char *bin,char *str,unsigned int length);

/*!
@brief ͬchar2bin������
@param[in] str ԭASC�ִ�
@param[in] length ת�����HEX���ĳ��ȣ�����ASC�ִ����ȣ���
@param[out] bin �����HEX��
@see char2bin
*/
void Char2Hex(unsigned char *bin,const char *str,unsigned int length);


/*!
@brief ���ֽ�Ϊ��λ����������
@param[in] databuff �ֽ�������
@param[in] size �ֽ�������Ч����
@return  ������Ľ�� 
*/
UINT8 bcc(unsigned char *databuff, UINT32 size);

/*!
@brief �����㣬��bcc������ȫ��ͬ
@param[in] length �ֽ�������Ч����
@param[in] buffer �ֽ�������
@return  ������Ľ�� 
@see bcc
*/
unsigned char yihuo(UINT32 length, unsigned char *buffer);

/*!
@brief ����crc16
@param[in] ptr ��������ֽ�������
@param[in] len �ֽ�������Ч����
@return  crc16�ļ����� 
*/
unsigned short int cal_crc(UINT8 *ptr, UINT32 len);

/*!
@brief ����crc16����������cal_crc������ͬ
@param[in] length �ֽ�������Ч����
@param[in] buffer ��������ֽ�������
@param[out]  crc  ˫�ֽڵ�crc������
@see cal_crc
*/
void crcxdata(unsigned int length, unsigned char * buffer, unsigned char *crc);

/*!
@brief ˰����ת������8�ֽ�HEX��ʽ��˰����ת��20�ֽ�ASC��ʽ��˰����
@param[in] hex HEX��ʽ˰����
@param[out] asc ASC��ʽ��˰����
*/
void get_fiscal_code(unsigned char *hex, unsigned char *asc);

/*!
@brief ˰����ת������20�ֽ�ASC��ʽ��˰����ת��8�ֽ�HEX��ʽ��˰����
@param[out] hex HEX��ʽ˰����
@param[in] asc ASC��ʽ��˰����
*/
void fiscal_code_hex(unsigned char *hex, unsigned char *asc);

/*!
@brief �Լ����������������������봦��
@param[in,out] f ��Ҫ������ĸ�����
@return -1��������̫���޷��洢�� >=0 ��ʾС���������Чλ��
*/
INT32 AmountRound(double *f);

/*!
@brief ����������������ת��Ϊ����Ҫ�����������
@param[in] dotnum С�������Чλ�� ��Ҫ������ĸ�����
@param[in] f ��Ҫת���ĸ�����
@return ת���������
*/
UINT32 FormatAmount(UINT32 dotnum, double f);

/*!
@brief ��鸡������С��λ��
@param[in] f ��Ҫ���С��λ���ĸ�����
@return >=0 ��ʾС���������Чλ��
*/
INT32 CheckFloatBit(double f);

/*!
@brief ��������double����ת����INT64����
@param[in] input ��ת��������
@return  INT64���͵�����
*/
INT64 double2int(double input);


void getBytes(short data, UINT8* bytes);

short getShort(UINT8* bytes);

#ifdef __cplusplus
}
#endif

#endif	//ARITHMETHIC_H
