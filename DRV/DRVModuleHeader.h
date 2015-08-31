/*! \file DRVModuleHeader.h
   \brief ���ļ�������DRVģ��ĸ������ú꿪��
 */

#ifndef	__LIB_H_DRV_MODULE_MACRO_DEF_
#define	__LIB_H_DRV_MODULE_MACRO_DEF_


//////////////////////////////////////////////////////////////////////////
//Ϊ���ò�����Ĭ��ֵ��
//���DRVModuleConfig.h�ļ���û�ж�ĳ���������壬�����ʱ��ʹ��Ĭ��ֵ��
//��ֲʱ��Ҫ�޸��ⲿ�ֶ��塣
//////////////////////////////////////////////////////////////////////////
//#include "DRVModuleConfig.h"

//��ģ��ı��뿪��

#ifndef USE_HW_DRV
#define USE_HW_DRV							1
#endif

#ifndef USE_SCANNER_DRV
#define USE_SCANNER_DRV						1
#endif

#ifndef USE_RTC_DRV
#define USE_RTC_DRV							1
#endif


#ifndef USE_VFD_DRV
#define USE_VFD_DRV							1
#endif


#ifndef USE_POWOFF_PROTECT_DRV
#define USE_POWOFF_PROTECT_DRV				0
#endif


#endif	//__H_DRV_MODULE_MACRO_DEF_

