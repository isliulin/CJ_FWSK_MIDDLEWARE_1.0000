#ifndef __SERIAL_CONFIG_H
#define __SERIAL_CONFIG_H

#include "DataTypeDesign.h"
//#include "error_code.h"
#include "VersionConfig.h"


#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ARM9)
#define USB_SERIAL_DEVICE						"/dev/ttyS5"
#elif (PROJECT_TYPE_MODE == PROJECT_TYPE_A5_ZHH)
#define USB_SERIAL_DEVICE						"/dev/ttyS1"
#define PRINTER_SERIAL_DEVICE				USB_SERIAL_DEVICE
#elif (PROJECT_TYPE_MODE == PROJECT_TYPE_A5_YTJ)
#define USB_SERIAL_DEVICE						"/dev/ttyS1"
#define PRINTER_SERIAL_DEVICE					"/dev/ttyS4"
#endif

#define BLUETOOTH_SERIAL_DEVICE				"/dev/ttyS2"

#if (COMMUNICATE_VERSION==NET_VERSION)
#define SERIAL_DEVICE						USB_SERIAL_DEVICE
#elif (COMMUNICATE_VERSION==NO_NET_VERSION)
#define SERIAL_DEVICE						USB_SERIAL_DEVICE
#elif (COMMUNICATE_VERSION==BLUETOOTH_VERSION)
#define SERIAL_DEVICE						BLUETOOTH_SERIAL_DEVICE
#endif

#define SERIAL_BUFFER_MAX_LEN				65535UL							//����Buf��󳤶�	
#define BUSINESS_DATA_BUF_MAX_LEN			1*1024*1024						//ҵ�񻺳�������

#define SERIAL_PACKAGE_ZC_MAX_LEN			255								//�ܲ�Э�����ݰ���󳤶�
#define SERIAL_PACKAGE_AISINO_MAX_LEN		SERIAL_BUFFER_MAX_LEN			//�����Զ������ݰ���󳤶�

#define SERIAL_OVERTIME_MAX					30000000UL
#define SERIAL_NODATA_MAX					50000UL
#define SERIAL_ERRNUM_MAX					0x40


#define TIME_MS								30
#define SERIAL_OVERTIME_COUNT				100


#define CRC_LEN								2								//CRCУ��λ����
#define REVPACK_ZC_HEAD_LENGTH				5								//�ܲ�Э��������ݰ���ͷ����
#define RSPPACK_ZC_HEAD_LENGTH				4								//�ܲ�Э����Ӧ���ݰ���ͷ����
#define REVPACK_AISINO_HEAD_LENGTH			6								//����Э��������ݰ���ͷ����
#define RSPPACK_AISINO_HEAD_LENGTH			5								//����Э����Ӧ���ݰ���ͷ����

enum ProtocolType
{
	ZC_PROTOCOL			= 0x10,				//�ܲ�Э���ͷ����
	XML_PROTOCOL		= 0x20,				//XML���ݰ�ͷ����
	CA_PROTOCOL			= 0x30,				//CAҵ�����ݰ�ͷ����
	PRN_PROTOCOL		= 0x40				//��ӡ���ݰ�ͷ����
};

typedef struct
{
	UINT8 cmdType;		//��������
	UINT8 cmdNo;		//�����
	UINT8 PackNo;		//�����
	UINT16 cmdLen;		//��������
	UINT32 dataLen;		//ҵ�����ݳ��ȣ��ۼ�
	UINT8 *revData;
} rev_cmdStruct;

typedef struct
{
	UINT8 head[2];
	UINT8 PackNo;
	UINT16 cmdLen;
	UINT8 *rspData;
	UINT8 crc[2];
} rsp_cmdStruct;

enum ByteOrder
{
	WEB_BYTEORDER		= 0x00,
	PC_BYTEODER			= 0x01
};

//error code define
#define	SERCMD_SUCCESS				0x00			//���������ȷ
#define	SERCMD_NO_DATA				0xF0			//��ʱΪδ�յ�����
#define	SERCMD_NOT_LASTPACK			0xF1			//���յİ����ǽ�����
#define SERCMD_HEAD_ERR				0x11			//��ͷ���ݸ�ʽ����
#define SERCMD_HEAD_PARA_ERR		0x12			//��ͷ���ݲ�������
#define SERCMD_CRC_ERR				0x1f			//����CRC��
#define	SERCMD_CMDNO_ERR			0x20			//������޷�ʶ��
#define SERCMD_PACKLEN_ERR			0x22			//����ȴ���
#define SERCMD_OVERTIME_ERR			0x30			//������ܳ�ʱ

#define BUSINESS_COMMON_TYPE		0x10			//�ܲδ���ͨ������
#define BUSINESS_XML_TYPE			0x20			//xml���ݴ�������
#define BUSINESS_CA_TYPE			0x30			//CA����ͨ������
#define BUSINESS_PRINT_TYPE			0x40			//��ӡ���ݴ�������

#define NP_PACKAGE_TYPE				0x01
#define OK_PACKAGE_TYPE				0x02
#define ER_PACKAGE_TYPE				0x03

#endif
