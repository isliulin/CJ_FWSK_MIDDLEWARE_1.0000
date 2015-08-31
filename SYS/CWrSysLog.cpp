/*! \file    CWrSysLog.cpp
   \brief    ϵͳ��־�������ʵ��
   \author   ZL
   \version  1.0
   \date     2011-8-17
 */

#include "SYSModuleHeader.h"
#include "TDateTime.h"
#include "CWrSysLog.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

static INT32 s_SysLogNum = 0;
static INT32 s_LastLogNo = 0;

CWrSysLog::CWrSysLog()
{
	s_SysLogNum = 0;
}

CWrSysLog::~CWrSysLog()
{
}

INT32 CWrSysLog::WrSysLog(UINT8 Eventtype, UINT32 EventResult, string Backup)
{
#if (SYSLOG_FUN_ON==1)
	string curDate(""), curTime("");
	TDateTime curDateTime = TDateTime::CurrentDateTime();
	FILE *fp;
	
	//׷�Ӵ�
	fp = fopen(SYSLOG_FILE_NAME, "a+");
	if (fp==NULL)
		return FAILURE;
	fseek(fp, 0, SEEK_END);

	//д
	s_SysLogNum ++;
	s_LastLogNo ++;
	curDate = curDateTime.FormatString(YYYYMMDD,"%u%02u%02u");
	curTime = curDateTime.FormatString(HHMMSS,"%02u%02u%02u");
	fprintf(fp, "%d	%s	%s	%02X	%02X	%s\n", s_LastLogNo, curDate.c_str(), curTime.c_str(), 
											Eventtype, EventResult, Backup.c_str());

	//�ر�
	fclose(fp);

#endif	//SYSLOG_FUN_ON

	return SUCCESS;
}

INT32 CWrSysLog::GetLogNum(FILE *fp)
{
	INT8 logNo[8];
	INT8 tmpBuf[512];

	DBG_ASSERT_EXIT((fp != NULL), (" fp == NULL!"));

	while (!feof(fp))
	{
		if (fgets(tmpBuf, sizeof(tmpBuf), fp) == NULL)
			break;
	//	DBG_PRINT(("tmpBuf=%s", tmpBuf));
		sscanf(tmpBuf, "%s", logNo);
		s_SysLogNum++;
	}
	DBG_PRINT(("logNo=%s", logNo));
	DBG_PRINT(("s_SysLogNum=%d", s_SysLogNum));
	s_LastLogNo = atoi(logNo);

	return SUCCESS;
}

INT32 CWrSysLog::isLogRoll()
{
	if (s_SysLogNum > SYSLOG_ROLL_NUM)
		return SUCCESS;
	else
		return FAILURE;
}

INT32 CWrSysLog::LogRollProc(string &strErr)
{
	INT8 tmpbuf[64];
	FILE *fp=NULL, *fp_old=NULL;

	fp = fopen(SYSLOG_FILE_NAME, "r");
	DBG_PRINT(("fp = %x", fp));
	if (fp==NULL)
	{	
		fp_old = fopen(SYSLOG_FILE_NAME_OLD, "r");	//�����ļ�ʱ����������־�ļ�����Ӹ��ļ�ȡ���
		DBG_PRINT(("fp_old = %x", fp_old));
		if (fp_old!=NULL)
		{
			if (GetLogNum(fp_old) != SUCCESS)
			{
				strErr = "��ȡ����־�ļ�����";
			}
			fclose(fp_old);

			s_SysLogNum = 0;	//������־�ļ������Լ�¼������Ȼ��0
		}
		else
		{
			s_SysLogNum = 0;
			s_LastLogNo = 0;
		}
	}
	else
	{
		if (GetLogNum(fp) != SUCCESS)
		{
			fclose(fp);
			strErr = "��ȡ��־��������";
			return FAILURE;
		}
		fclose(fp);
	}

	if (isLogRoll() == SUCCESS)	//��Ҫ����
	{
		sprintf(tmpbuf, "rm %s", SYSLOG_FILE_NAME_OLD);
		system(tmpbuf);
		sprintf(tmpbuf, "mv %s %s", SYSLOG_FILE_NAME, SYSLOG_FILE_NAME_OLD);
		if (system(tmpbuf) != 0)
		{
			strErr = "��־�ļ���������";
			return FAILURE;
		}
	}

	return SUCCESS;
}

