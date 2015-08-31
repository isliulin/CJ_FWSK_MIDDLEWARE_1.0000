/*! \file   USBMount.h
   \brief   USB�ӿ�����
   \author  zl
*/
#ifndef __USB_MOUNT_H
#define __USB_MOUNT_H

#ifdef __cplusplus
extern "C"
{
#endif

/*!
@brief  ����USB��
@param[in]  �豸�� Ĭ��ΪNULL
@return true �ɹ� false ʧ��
*/
unsigned char UsbDiskMount(char* dev);

/*!
@brief  ж��USB��
@return true �ɹ� false ʧ��
*/
unsigned char UsbDiskUnMount();

/*!
@brief  ���صڶ���USB��
@param[in]  �豸�� Ĭ��ΪNULL
@return true �ɹ� false ʧ��
*/
unsigned char UsbDiskMount2(char* dev);

/*!
@brief  ж�صڶ���USB��
@return true �ɹ� false ʧ��
*/
unsigned char UsbDiskUnMount2();


#ifdef __cplusplus
}
#endif

#endif
