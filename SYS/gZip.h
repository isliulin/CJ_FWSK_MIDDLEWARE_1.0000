/*! \file    gZip.h
   \brief    gz��ʽ��ѹ�����ѹ�ӿڶ���
   \author   zl
 */

#ifndef __LIB_GZIP_H_
#define __LIB_GZIP_H_

#include "SYSModuleHeader.h"
#include "zlib.h"

#if (USE_GZIP_LIB != 0)


#ifdef __cplusplus
extern "C"
{
#endif

/*!
@brief ���ļ�ѹ��Ϊgz�ļ�
@param[in] infilename  ԭʼ�ļ���
@param[in] outfilename  ָ��ѹ������ļ���
@return  0-ѹ���ɹ���<0���� 
*/
int compress_one_file(const char *infilename, char *outfilename);

/*!
@brief ��gz��ʽ���ļ���ѹ
@param[in] infilename  gz�ļ���
@param[in] outfilename  ָ����ѹ����ļ���
@return  0-ѹ���ɹ���<0���� 
*/
int decompress_one_file(const char *infilename, const char *outfilename);



/*!
@brief ��һ���ֽ����е�����ѹ��Ϊzlib��ʽ
@param[in] source  ԭʼ�ֽ���
@param[in] sourceLen  ԭʼ�ֽ����ĳ���
@param[out] dest   ���ѹ������ֽ���
@param[in,out] destLen  ����dest�������󳤶ȣ����ʵ��ѹ����ĳ���
@return  0-�ɹ������� - ���� 
*/
int compress_zlib(unsigned char *dest, unsigned long *destLen, 
				  const unsigned char *source, unsigned int sourceLen);

/*!
@brief ��zlib��ʽ���ֽ�����ѹ
@param[in] source  ԭʼ�ֽ���
@param[in] sourceLen  ԭʼ�ֽ����ĳ���
@param[out] dest   �����ѹ����ֽ���
@param[in,out] destLen  ����dest�������󳤶ȣ����ʵ�ʽ�ѹ��ĳ���
@return  0-�ɹ������� - ���� 
*/
int uncompress_zlib(unsigned char *dest, unsigned long *destLen, 
					const unsigned char *source, unsigned int sourceLen);

/*!
@brief Ԥ��zlibѹ����ĳ���
@param[in] sourceLen  ԭʼ�ֽ����ĳ���
@return  ѹ���󳤶ȵĹ���ֵ
*/
unsigned int compressBound_zlib(unsigned int sourceLen);


#ifdef __cplusplus
}
#endif


#endif	//USE_GZIP_LIB

#endif	//__GZIP_H_
