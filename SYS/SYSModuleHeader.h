/*! \file SYSModuleHeader.h
   \brief ���ļ�������SYSģ��ĸ������ú꿪��
 */

#ifndef	__LIB_H_SYS_MODULE_MACRO_DEF_
#define	__LIB_H_SYS_MODULE_MACRO_DEF_







//////////////////////////////////////////////////////////////////////////
//Ϊ���ò�����Ĭ��ֵ��
//���SYSModuleConfig.h�ļ���û�ж�ĳ���������壬�����ʱ��ʹ��Ĭ��ֵ��
//��ֲʱ��Ҫ�޸��ⲿ�ֶ��塣
//////////////////////////////////////////////////////////////////////////
//#include "SYSModuleConfig.h"

//��ģ��ı��뿪��
#ifndef USE_ICONV_LIB
#define USE_ICONV_LIB						0
#endif

#ifndef USE_XML_FUNC
#define USE_XML_FUNC						1
#endif

#ifndef USE_JSON_FUNC
#define USE_JSON_FUNC						0
#endif

#ifndef USE_GZIP_LIB
#define USE_GZIP_LIB						1
#endif

#ifndef USE_MD5_FUNC
#define USE_MD5_FUNC						1
#endif

#ifndef USE_DES_FUNC
#define USE_DES_FUNC						0
#endif

#ifndef USE_RSA_FUNC
#define USE_RSA_FUNC						0
#endif

#ifndef USE_SERIAL_PROTOCOL
#define USE_SERIAL_PROTOCOL					0
#endif

#ifndef USE_AES_FUNC
#define USE_AES_FUNC						1
#endif


//һЩģ������ò���
#ifndef SYSLOG_FUN_ON
#define	SYSLOG_FUN_ON						0		/**< �Ƿ�дϵͳ��־���ء�1-д��0-��д */		
#endif

#ifndef ICONV_CONVERT_BUF_LEN
#define	ICONV_CONVERT_BUF_LEN				4096			/**< ICONV������ʹ�õĻ����С */
#endif



#endif	//__H_SYS_MODULE_MACRO_DEF_

