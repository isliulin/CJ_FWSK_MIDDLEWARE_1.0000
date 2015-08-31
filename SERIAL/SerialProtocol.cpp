#include <string>
#include <stdlib.h>
#include "arithmetic.h"
#include <unistd.h>
#include "TDateTime.h"
#include "SerialProtocol.h"
#include "commonFunc.h"
using namespace std;

#include "IncludeMe.h"
#include "LOGCTRL.h"
#define NO_POS_DEBUG
#include "pos_debug.h"

SerialProtocol::SerialProtocol()
{
	resetAll();
}

SerialProtocol::~SerialProtocol()
{
	ReleasePort();
}

void SerialProtocol::resetRevStruct(){
	m_revCmd = &m_cRevCmd;
	memset (m_revCmd, 0, sizeof(rev_cmdStruct));
	m_cRevCmd.revData = businessData;
}

void SerialProtocol::resetRspStruct() {
	m_rspCmd = &m_cRspCmd;
	memset (m_rspCmd, 0, sizeof(rsp_cmdStruct));
	m_rspCmd->rspData = businessData;
}

void SerialProtocol::resetAll() {
	memset (m_revBuf, 0, SERIAL_BUFFER_MAX_LEN);
	memset (m_rspBuf, 0, SERIAL_BUFFER_MAX_LEN);
	memset (businessData, 0, BUSINESS_DATA_BUF_MAX_LEN);
	resetRevStruct();
	resetRspStruct();
	m_fill_count = 0;
	m_get_count = 0;
	packageNo = 0;

	m_type_err_flag = 0;

	newCmd = true;
}

/*!
@brief init serial port. private.
*/
bool SerialProtocol::InitPort(INT8 *devpath, int baud)
{
	m_devfd = openPort(devpath, baud);
	return (0 < m_devfd) ? SUCCESS : FAILURE;
}

bool SerialProtocol::ReleasePort()
{
	closePort();
	return SUCCESS;
}


UINT8 SerialProtocol::sendData(UINT8 type, UINT8 cmd){

}

UINT8 SerialProtocol::revData()
{
	UINT8 ret = 0;
	UINT8 headLen = 0;
	do 
	{
		ret = Rev_Pack();
		DBG_PRINT(("Rev_Pack ret = %u", ret));
		if (SERCMD_SUCCESS != ret)
		{
			resetRevStruct();
			cleanSerial();
			newCmd = true;
			//if (SERCMD_OVERTIME_ERR != ret)
			//{
				Rsp_ERR(ret);
			//}
			break;
		}
		else 
		{
			headLen = ZC_PROTOCOL==m_revCmd->cmdType? REVPACK_ZC_HEAD_LENGTH: REVPACK_AISINO_HEAD_LENGTH;
#if COMMUNICATE_VERSION==BLUETOOTH_VERSION || PROJECT_TYPE_MODE == PROJECT_TYPE_A5_YTJ
			DBG_PRINT(("m_revCmd->cmdType = %x", m_revCmd->cmdType));
			if (PRN_PROTOCOL == m_revCmd->cmdType)
			{
				DBG_NPRINT_HEX((m_revBuf+headLen), m_revCmd->cmdLen-headLen);
				PrintLine((m_revBuf+headLen), m_revCmd->cmdLen-headLen);
			} 
			else
#endif
			{
			memcpy((void *)(businessData+m_revCmd->dataLen), (void *)(m_revBuf+headLen), m_revCmd->cmdLen-headLen);
			m_revCmd->dataLen += (m_revCmd->cmdLen-headLen);
		}
		}
	} while (0 != m_revCmd->PackNo);

	return ret;
}

/*!
@brief receive a pack. private	 
*/
UINT8 SerialProtocol::Rev_Pack()
{
	int readLen=0, rev_Len=0;
	INT64 overtime=0;
	UINT8 cmdType = 0, cmdno = 0, packageno = 0;
	UINT8 headLen=0;
	static UINT8 lastType=0;
	UINT16 datalen=0;
	UINT16 revcrc=0, calcrc=0;
	
	//接收两字节包头
	while(1) 
	{
		readLen = readBytes(m_revBuf+rev_Len, 2-rev_Len);
		if (newCmd && (0==readLen || -1==readLen))
		{
			CommonSleep(TIME_MS);
			continue;
		}
		rev_Len += readLen;
		DBG_PRINT(("step3: 读取的累加长度rev_Len = %d", rev_Len));
		if (2 <= rev_Len)
		{
			DBG_PRINT(("pakage cmdno is %x %x", m_revBuf[0], m_revBuf[1]));
			//判断包起始标志
			DBG_PRINT(("step4: 第一个字节是否为1B ? 结果：%x", m_revBuf[0]));
			if (0x1B != m_revBuf[0] || 
				(BUSINESS_COMMON_TYPE != m_revBuf[1] && BUSINESS_XML_TYPE != m_revBuf[1] && BUSINESS_CA_TYPE != m_revBuf[1] &&BUSINESS_PRINT_TYPE != m_revBuf[1]))
			{

				m_type_err_flag = 1;

				DBG_PRINT(("head cmd error"));
				return SERCMD_HEAD_ERR;
			}
			headLen = ZC_PROTOCOL==m_revBuf[1]? REVPACK_ZC_HEAD_LENGTH: REVPACK_AISINO_HEAD_LENGTH;
			break;
		} 
		else 
		{
			if (0 == readLen)
			{
				if (overtime > SERIAL_OVERTIME_COUNT)
				{
					DBG_PRINT(("rev head time out"));
					return SERCMD_OVERTIME_ERR;
				}
				else
				{
					overtime ++;
					DBG_PRINT(("overtime ++ = %lld", overtime++));
					CommonSleep(TIME_MS);
					continue;
				}
			} 
			else
			{
				overtime = 0;
				continue;
			}
		}
	}
	DBG_PRINT(("headLen = %u", headLen));

	overtime=0;
	while(1)
	{
		readLen = readBytes(m_revBuf+rev_Len, headLen-rev_Len);
		DBG_PRINT(("step4 readLen = %d", readLen));
		rev_Len += readLen;
		DBG_PRINT(("rev_Len=%u", rev_Len));
		if (headLen <= rev_Len)
		{	
			break;
		} 
		else 
		{
			if (0 == readLen)
			{
				if (overtime > SERIAL_OVERTIME_COUNT)
				{
					DBG_PRINT(("rev head time out"));
					return SERCMD_OVERTIME_ERR;
				}else
				{
					overtime++;
					CommonSleep(TIME_MS);
					continue;
				}
			} 
			else
			{
				overtime = 0;
				continue;
			}
		}
	}

	cmdType = m_revBuf[1];
	cmdno = m_revBuf[2];
	packageno = m_revBuf[3];
	datalen = ZC_PROTOCOL == cmdType? m_revBuf[4]:getShort(m_revBuf+4);
	DBG_PRINT(("cmdType=%u, cmdno=%u, packageno=%u, datalen=%u", cmdType, cmdno, packageno, datalen));
	DBG_PRINT(("lastType=%u, lastpackageno=%u, lastcmdno=%u", lastType, m_revCmd->PackNo, m_revCmd->cmdNo));
	if (SERIAL_BUFFER_MAX_LEN < datalen+CRC_LEN)
	{
		DBG_PRINT(("package data is too long!!!"));
		return SERCMD_HEAD_PARA_ERR;
	}
	//如果是多包发送，要保证命令类型、名字字和之前一致，且包序号为递增
	if (0 < packageno)
	{
		if (1 == packageno)
		{
			lastType = cmdType;
		} 
		else
		{
			if (lastType != cmdType || (lastType == cmdType && (packageno != m_revCmd->PackNo+1 || cmdno != m_revCmd->cmdNo)))	//判断包头是否正确
			{
				lastType = 0;			//不考虑重复的情况下，一旦出错即复位
				DBG_PRINT(("head cmd para is error"));
				return SERCMD_HEAD_PARA_ERR;
			}
		}
	} 
	else
	{
		if (0 != lastType)
		{
			if (lastType != cmdType || (lastType == cmdType && cmdno != m_revCmd->cmdNo))
			{
				lastType = 0;			//不考虑重复的情况下，一旦出错即复位
				DBG_PRINT(("head cmd para is error 2"));
				return SERCMD_HEAD_PARA_ERR;
			}
			lastType = 0;
		}
	}

	m_revCmd->cmdLen = datalen;
	m_revCmd->cmdNo = cmdno;
	m_revCmd->cmdType = cmdType;
	m_revCmd->PackNo = packageno;

	//接收剩余数据
	readLen = 0;
	rev_Len = headLen;
	overtime=0;
	while(1)
	{
		readLen = readBytes(m_revBuf+rev_Len, datalen+CRC_LEN-rev_Len);
		rev_Len += readLen;
		if (datalen+CRC_LEN <= rev_Len)
		{	
			break;
		} 
		else
		{
			if (0 == readLen)
			{
				if (overtime > SERIAL_OVERTIME_COUNT)
				{
					DBG_PRINT(("rev head time out"));
					return SERCMD_OVERTIME_ERR;
				}
				else
				{
					overtime++;
					CommonSleep(TIME_MS);
					continue;
				}
			} 
			else
			{
				overtime = 0;
				continue;
			}
		}
	}

	//读取完整包数据，校验CRC
	DBG_PRINT(("datalen = %u, rev_Len = %u", datalen, rev_Len));
	DBG_NPRINT_HEX(m_revBuf, rev_Len);
	calcrc = Cal_CRC(m_revBuf, datalen);
	DBG_PRINT(("calcrc = %u ", calcrc));
	revcrc = getShort(m_revBuf+datalen);
	DBG_PRINT(("revcrc = %u ", revcrc));
	if (calcrc != revcrc)
	{
		DBG_PRINT(("crc error"));
		return SERCMD_CRC_ERR;
	}

	if (0 != packageno)
	{
		Rsp_NP(packageno);
		newCmd = false;
	}

	return SERCMD_SUCCESS;	
}

/*!
@brief wait "NP cmd" function.	 
*/
/*
UINT8 SerialProtocol::Wait_NP_Pack()
{
	UINT8 revbuf[8];
	UINT16 packageLen=0;
	UINT16 crc;
	UINT8 offset=0;
	UINT8 readLen;
	UINT8 times=0;

	packageLen = ZC_PROTOCOL==m_revCmd->cmdType? 5:6;

	while(times<10) {
		readLen = readBytes(revbuf+offset, packageLen+CRC_LEN-offset);
		offset += readLen;
		if (offset >= packageLen+CRC_LEN)
		{
			break;
		}
		else {
			CommonSleep(TIME_MS);
			times++;
		}
	}
	if (offset < packageLen+CRC_LEN)
	{
		DBG_PRINT(("wait np time out"));
		return SERCMD_OVERTIME_ERR;
	}

	if (!(revbuf[0]=='N' && revbuf[1]=='P') || 0x00 != revbuf[2] || packageNo != revbuf[packageLen-1])
	{
		DBG_PRINT(("wait np head error"));
		return SERCMD_HEAD_PARA_ERR;
	}
	if (ZC_PROTOCOL==m_revCmd->cmdType)
	{
		if (packageLen != revbuf[3])
		{
			DBG_PRINT(("wait np head para error"));
			return SERCMD_HEAD_PARA_ERR;
		}
	} else {
		if (packageLen != getShort(revbuf+3))
		{
			return SERCMD_HEAD_PARA_ERR;
		}
	}

	//检查校验码
	crc = Cal_CRC(revbuf, packageLen);
	if (!(revbuf[packageLen]==(UINT8)(crc>>8) && revbuf[packageLen+1]==(UINT8)(crc&0xff) ))
	{
		DBG_PRINT(("wait np crc error"));
		return SERCMD_CRC_ERR;	
	}

	return SERCMD_SUCCESS;
}

UINT8 SerialProtocol::Wait_OK_Pack()
{
	UINT8 revbuf[8];
	UINT16 packageLen=0;
	UINT16 crc;
	UINT8 offset=0;
	UINT8 readLen;
	UINT8 times=0;

	packageLen = ZC_PROTOCOL==m_revCmd->cmdType? 4:5;

	while(times<10) {
		readLen = readBytes(revbuf+offset, packageLen+CRC_LEN-offset);
		offset += readLen;
		if (offset >= packageLen+CRC_LEN)
		{
			break;
		}
		else {
			CommonSleep(TIME_MS);
			times++;
		}
	}
	if (offset < packageLen+CRC_LEN)
	{
		DBG_PRINT(("wait ok time out"));
		return SERCMD_OVERTIME_ERR;
	}

	if (!(revbuf[0]=='O' && revbuf[1]=='K') || 0x00 != revbuf[2])
	{
		DBG_PRINT(("wait ok head error"));
		return SERCMD_HEAD_PARA_ERR;
	}
	if (ZC_PROTOCOL==m_revCmd->cmdType)
	{
		if (packageLen != revbuf[3])
		{
			DBG_PRINT(("wait ok head para error"));
			return SERCMD_HEAD_PARA_ERR;
		}
	} else {
		if (packageLen != getShort(revbuf+3))
		{
			return SERCMD_HEAD_PARA_ERR;
		}
	}

	//检查校验码
	crc = Cal_CRC(revbuf, packageLen);
	if (!(revbuf[packageLen]==(UINT8)(crc>>8) && revbuf[packageLen+1]==(UINT8)(crc&0xff) ))
	{
		DBG_PRINT(("wait ok crc error"));
		return SERCMD_CRC_ERR;	
	}

	return SERCMD_SUCCESS;
}
*/

UINT8 SerialProtocol::Wait_Next_Cmd_Pack()
{
	UINT8 revbuf[32];
	UINT16 packageLen=0;
	UINT16 crc;
	UINT8 offset=0;
	UINT8 readLen = 0;
	UINT8 times=0;

	while(times<SERIAL_OVERTIME_COUNT) {
		readLen = readBytes(revbuf+offset, 2-offset);
		offset += readLen;
		if (offset >= 2)
		{
			break;
		}
		else {
			CommonSleep(TIME_MS);
			times++;
		}
	}
	DBG_PRINT(("offset = %u", offset));
	if (offset < 2)
	{
		DBG_PRINT(("wait next package time out"));
		return SERCMD_OVERTIME_ERR;
	}

	if (revbuf[0]=='O' && revbuf[1]=='K')
	{
		DBG_PRINT(("OK package!!!"));
		packageLen = ZC_PROTOCOL==m_revCmd->cmdType? 4:5;
	}
	if (revbuf[0]=='N' && revbuf[1]=='P')
	{
		DBG_PRINT(("NP package!!!"));
		packageLen = ZC_PROTOCOL==m_revCmd->cmdType? 5:6;
	}
	if (revbuf[0]=='E' && revbuf[1]=='R')
	{
		DBG_PRINT(("ER package!!!"));
		packageLen = ZC_PROTOCOL==m_revCmd->cmdType? 5:6;
	}

	times = 0;
	while(times<SERIAL_OVERTIME_COUNT) {
		readLen = readBytes(revbuf+offset, packageLen+CRC_LEN-offset);
		offset += readLen;
		if (offset >= packageLen+CRC_LEN)
		{
			break;
		}
		else {
			CommonSleep(TIME_MS);
			times++;
		}
	}
	if (offset < packageLen+CRC_LEN)
	{
		DBG_PRINT(("wait next package time out"));
		return SERCMD_OVERTIME_ERR;
	}

	if (revbuf[0]=='N' && revbuf[1]=='P')
	{
		if (0x00 != revbuf[2] || packageNo != revbuf[packageLen-1])
		{
			DBG_PRINT(("wait next package head error 1"));
			return SERCMD_HEAD_PARA_ERR;
		}
		if (ZC_PROTOCOL==m_revCmd->cmdType)
		{
			if (packageLen != revbuf[3])
			{
				DBG_PRINT(("wait next package head para error 2"));
				return SERCMD_HEAD_PARA_ERR;
			}
		} else {
			if (packageLen != getShort(revbuf+3))
			{
				return SERCMD_HEAD_PARA_ERR;
			}
		}
	}
	if (revbuf[0]=='O' && revbuf[1]=='K')
	{

	}
	if (revbuf[0]=='E' && revbuf[1]=='R')
	{

	}

	//检查校验码
	crc = Cal_CRC(revbuf, packageLen);
	if (!(revbuf[packageLen]==(UINT8)(crc>>8) && revbuf[packageLen+1]==(UINT8)(crc&0xff) ))
	{
		DBG_PRINT(("wait next package crc error"));
		return SERCMD_CRC_ERR;	
	}

	if (revbuf[0]=='N' && revbuf[1]=='P')
	{
		return NP_PACKAGE_TYPE;
	}
	if (revbuf[0]=='O' && revbuf[1]=='K')
	{
		return OK_PACKAGE_TYPE;
	}
	if (revbuf[0]=='E' && revbuf[1]=='R')
	{
		return ER_PACKAGE_TYPE;
	}

	return SERCMD_SUCCESS;
}

void SerialProtocol::Send_Pack(){
	DBG_PRINT(("m_rspCmd->cmdLen=%u", m_rspCmd->cmdLen));
	DBG_NPRINT_HEX(m_rspBuf, m_rspCmd->cmdLen);
	INT32 ret = sendBytes(m_rspBuf, m_rspCmd->cmdLen);
	DBG_PRINT(("向款机发送数据后的返回值 ret = %d", ret));
}

void SerialProtocol::Send_Pack(UINT16 len){
	sendBytes(m_rspBuf, len);
}

/*!
@brief respond a normal "OK cmd"	 
*/
void SerialProtocol::Rsp_OK()
{
	UINT16 crc;
	UINT16 templen;
	UINT8 tempbytes[2];
	UINT8 headLen;
	UINT16 bufLen;
	
	packageNo = 0;
	DBG_PRINT(("m_revCmd->cmdType = %x", m_revCmd->cmdType));
	headLen = ZC_PROTOCOL==m_revCmd->cmdType? RSPPACK_ZC_HEAD_LENGTH: RSPPACK_AISINO_HEAD_LENGTH;
#if COMMUNICATE_VERSION==BLUETOOTH_VERSION
	bufLen = 90;
#else
	bufLen = ZC_PROTOCOL==m_revCmd->cmdType? SERIAL_PACKAGE_ZC_MAX_LEN: SERIAL_PACKAGE_AISINO_MAX_LEN;
#endif
	
	DBG_PRINT(("m_fill_count=%u, headLen=%u, bufLen=%u", m_fill_count, headLen, bufLen));
	if (m_fill_count+headLen+CRC_LEN <= bufLen)
	{
		m_rspBuf[0] = 'O';
		m_rspBuf[1] = 'K';
		m_rspBuf[2] = packageNo;
		if (ZC_PROTOCOL==m_revCmd->cmdType)
		{
			m_rspBuf[3] = m_fill_count+headLen;
		} 
		else
		{
			getBytes(m_fill_count+headLen, tempbytes);
			m_rspBuf[3] = tempbytes[0];
			m_rspBuf[4] = tempbytes[1];
		}
		memcpy((void *)(m_rspBuf+headLen), businessData, m_fill_count);
		crc = Cal_CRC(m_rspBuf, m_fill_count+headLen);	
		m_rspBuf[m_fill_count+headLen] = (UINT8)(crc>>8);
		m_rspBuf[m_fill_count+headLen+1] = (UINT8)(crc&0xff);
		m_rspCmd->cmdLen = m_fill_count+headLen+CRC_LEN;
		DBG_PRINT(("m_rspCmd->cmdLen=%u", m_rspCmd->cmdLen));

		Send_Pack();
	} 
	else
	{
		packageNo = 1;
		m_get_count = 0;
		while(m_get_count < m_fill_count) {
			m_rspBuf[0] = 'O';
			m_rspBuf[1] = 'K';
			if (m_fill_count-m_get_count + headLen + CRC_LEN > bufLen)
			{
				templen = bufLen - headLen - CRC_LEN;
			} 
			else
			{
				templen = m_fill_count-m_get_count;
				packageNo = 0;
			}
			m_rspBuf[2] = packageNo;
			if (ZC_PROTOCOL==m_revCmd->cmdType)
			{
				m_rspBuf[3] = templen + headLen;
			} 
			else
			{
				getBytes(templen+headLen, tempbytes);
				m_rspBuf[3] = tempbytes[0];
				m_rspBuf[4] = tempbytes[1];
			}

			memcpy((void *)(m_rspBuf+headLen), businessData+m_get_count, templen);
			crc = Cal_CRC(m_rspBuf, templen+headLen);	
			m_rspBuf[templen+headLen] = (UINT8)(crc>>8);
			m_rspBuf[templen+headLen+1] = (UINT8)(crc&0xff);
			m_get_count += templen;
			m_rspCmd->cmdLen = templen+headLen+CRC_LEN;

			Send_Pack();

			//等待下一包请求
/*			if (0 != packageNo)
			{
				if (SERCMD_SUCCESS != Wait_NP_Pack())
					break;
				packageNo++;
			} */
			if (NP_PACKAGE_TYPE != Wait_Next_Cmd_Pack())
			{
				break;
			}
			packageNo++;
		}
	}

	resetAll();
//	clearSerial();
}

void SerialProtocol::clearSerial(){
	UINT8 temp;
	while(readBytes(&temp, 1));
}

/*!
@brief respond a "ER cmd"	 
*/
void SerialProtocol::Rsp_ERR(UINT8 err)
{
	UINT16 crc;
	
	m_rspBuf[0] = 'E';
	m_rspBuf[1] = 'R';
	m_rspBuf[2] = 0x00;
//	if (ZC_PROTOCOL==m_revCmd->cmdType)
	DBG_PRINT(("m_revBuf[1] = 0x%x", m_revBuf[1]));
	DBG_PRINT(("m_revCmd->cmdType = 0x%x", m_revCmd->cmdType));
	if (ZC_PROTOCOL==m_revBuf[1] || ZC_PROTOCOL==m_revCmd->cmdType || 1==m_type_err_flag)
	{
		m_rspBuf[3] = 0x05;
		m_rspBuf[4] = err;
		crc = Cal_CRC(m_rspBuf, 5);	
		m_rspBuf[5] = (UINT8)(crc>>8);
		m_rspBuf[6] = (UINT8)(crc&0xff);	
		Send_Pack(7);
	} 
	else
	{
		m_rspBuf[3] = 0x00;
		m_rspBuf[4] = 0x06;
		m_rspBuf[5] = err;
		crc = Cal_CRC(m_rspBuf, 6);	
		m_rspBuf[6] = (UINT8)(crc>>8);
		m_rspBuf[7] = (UINT8)(crc&0xff);	
		Send_Pack(8);
	}

	resetAll();
//	clearSerial();
}

/*!
@brief respond a "ER cmd"	 
*/
void SerialProtocol::Rsp_ERR(string errstr)
{
	UINT16 crc;
	UINT16 errlen=0;

	m_rspBuf[0] = 'E';
	m_rspBuf[1] = 'R';
	m_rspBuf[2] = 0x00;
	
	if (ZC_PROTOCOL==m_revCmd->cmdType)
	{
		if (errstr.length()+4+CRC_LEN > SERIAL_PACKAGE_ZC_MAX_LEN)
		{
			errlen = SERIAL_PACKAGE_ZC_MAX_LEN - 4 - CRC_LEN;
		} 
		else
		{
			errlen = errstr.length();
		}
		m_rspBuf[3] = errlen+4;
		memcpy(m_rspBuf+4, errstr.c_str(), errlen);
		
		crc = Cal_CRC(m_rspBuf, errlen+4);	
		m_rspBuf[errlen+4] = (UINT8)(crc>>8);
		m_rspBuf[errlen+5] = (UINT8)(crc&0xff);	
		Send_Pack(errlen+6);
	} 
	else
	{
		if (errstr.length()+5+CRC_LEN > SERIAL_PACKAGE_AISINO_MAX_LEN)
		{
			errlen = SERIAL_PACKAGE_AISINO_MAX_LEN - 5 - CRC_LEN;
		} 
		else
		{
			errlen = errstr.length();
		}
		UINT8 lenarray[2];
		memset(lenarray, 0x00, sizeof(lenarray));
		getBytes(errlen+4, lenarray);
		m_rspBuf[3] = lenarray[0];
		m_rspBuf[4] = lenarray[1];
		memcpy(m_rspBuf+5, errstr.c_str(), errlen);
		crc = Cal_CRC(m_rspBuf, errlen+5);	
		m_rspBuf[errlen+5] = (UINT8)(crc>>8);
		m_rspBuf[errlen+6] = (UINT8)(crc&0xff);	
		Send_Pack(errlen+7);
	}

	resetAll();
	//	clearSerial();
}

/*!
@brief respond a "WT cmd"	 
*/
void SerialProtocol::Rsp_WT()
{
	UINT16 crc;
	
	m_rspBuf[0] = 'W';
	m_rspBuf[1] = 'T';
	m_rspBuf[2] = 0x00;
	if (ZC_PROTOCOL==m_revCmd->cmdType)
	{
		m_rspBuf[3] = 0x04;
		crc = Cal_CRC(m_rspBuf, 4);	
		m_rspBuf[4] = (UINT8)(crc>>8);
		m_rspBuf[5] = (UINT8)(crc&0xff);	
		Send_Pack(6);
	} 
	else
	{
		m_rspBuf[3] = 0x00;
		m_rspBuf[4] = 0x05;
		crc = Cal_CRC(m_rspBuf, 5);	
		m_rspBuf[5] = (UINT8)(crc>>8);
		m_rspBuf[6] = (UINT8)(crc&0xff);	
		Send_Pack(7);
	}
}

/*!
@brief respond a "NP cmd"	 
*/
void SerialProtocol::Rsp_NP(UINT8 packageNo)
{
	UINT16 crc;
	
	DBG_PRINT(("send NP!!!"));
	
	m_rspBuf[0] = 'N';
	m_rspBuf[1] = 'P';
	m_rspBuf[2] = 0x00;
	if (ZC_PROTOCOL==m_revCmd->cmdType)
	{
		m_rspBuf[3] = 0x05;
		m_rspBuf[4] = packageNo;
		crc = Cal_CRC(m_rspBuf, 5);	
		m_rspBuf[5] = (UINT8)(crc>>8);
		m_rspBuf[6] = (UINT8)(crc&0xff);
		DBG_NPRINT_HEX(m_rspBuf, 7);
		Send_Pack(7);
	} 
	else
	{
		m_rspBuf[3] = 0x00;
		m_rspBuf[4] = 0x06;
		m_rspBuf[5] = packageNo;
		crc = Cal_CRC(m_rspBuf, 6);	
		m_rspBuf[6] = (UINT8)(crc>>8);
		m_rspBuf[7] = (UINT8)(crc&0xff);
		Send_Pack(8);
	}
}

/*!
@brief calculate CRC code	 
*/
UINT16 SerialProtocol::Cal_CRC(UINT8 *ptr, UINT16 len)
{
	unsigned char i;
	unsigned int crc=0;
	while(len--!=0)
	{
    	for(i=0x80; i!=0; i/=2)
		{
      		if((crc&0x8000)!=0) 
			{
				crc*=2;
				crc^=0x18005;
			}
        	else
			{
				crc*=2;
			}
			if((*ptr&i)!=0) crc^=0x18005; 
    	}
    	ptr++;
  	}
  	return(crc);	
}

/*!
@brief fill a byte parament to rsp buffer	 
*/
INT8 SerialProtocol::FillParament(UINT8 byte)
{
	if (m_fill_count + 1 > BUSINESS_DATA_BUF_MAX_LEN)
		return FAILURE;

	businessData[m_fill_count] = byte;
	m_fill_count++;

	return SUCCESS;
}

/*!
@brief fill a value parament to rsp buffer. 0-web order 
*/
INT8 SerialProtocol::FillParament(INT64 x, UINT8 len, bool order)
{
	INT8 i;
	INT8 *p=(INT8 *)&x;

	if (m_fill_count +len > BUSINESS_DATA_BUF_MAX_LEN)
		return FAILURE;
	
	if (len!=2 && len!=4 && len!=8)
		return FAILURE;

	for (i=0; i<len; i++)
	{
		if (order == 1)
			*(businessData+m_fill_count+i) = *(p+i);
		else
			*(businessData+m_fill_count+len-i-1) = *(p+i);
	}

	m_fill_count += len;

	return SUCCESS;
}

/*!
@brief fill buffer parament to rsp buffer	 
*/
INT8 SerialProtocol::FillParament(UINT8 *buf, UINT8 len)
{
	if (m_fill_count +len > BUSINESS_DATA_BUF_MAX_LEN)
		return FAILURE;

	memcpy(businessData+m_fill_count, buf, len );
	m_fill_count += len;

	return SUCCESS;
}

/*!
@brief fill a "string" parament to rsp buffer	 
*/
INT8 SerialProtocol::FillParament(string str, UINT32 maxlen)
{
	UINT32 len=0;

	len = str.length()>maxlen? maxlen : str.length();
	if (m_fill_count + maxlen > BUSINESS_DATA_BUF_MAX_LEN)
		return FAILURE;

	memset(businessData+m_fill_count, 0, maxlen );
	strncpy ( (char *)businessData+m_fill_count, str.c_str(), len);
	m_fill_count += maxlen;

	return SUCCESS;
}

/*!
@brief delay function for serial. private.
*/
void SerialProtocol::ser_delay(UINT32 Msecs)
{
	UINT32  i;

   	for(; Msecs>0; Msecs--) 
      	for(i=0; i<2500; i++);
    return;
}

#if COMMUNICATE_VERSION==BLUETOOTH_VERSION || PROJECT_TYPE_MODE == PROJECT_TYPE_A5_YTJ
bool SerialProtocol::InitPrinterPort(INT8 *devpath, int baud)
{
	m_printerfd = openPrinterPort(devpath, baud);
	return (0 < m_printerfd) ? SUCCESS : FAILURE;
}
bool SerialProtocol::ReleasePrinterPort()
{
	closePrinterPort();
	return SUCCESS;
}
UINT8 SerialProtocol::PrintLine(UINT8 *printdata, INT32 printlen)
{
	printLine(printdata, printlen);
	return SUCCESS;
}
#endif
