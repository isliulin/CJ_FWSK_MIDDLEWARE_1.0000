/*! \file    CWrSysLog.h
   \brief    ϵͳ��־�����ඨ��
   \author   ZL
   \version  1.0
   \date     2011-8-17
 */

#ifndef __LIB_WR_SYSLOG_H
#define __LIB_WR_SYSLOG_H

#include "IncludeMe.h"

namespace middleware
{

#define		SYSLOG_FILE_NAME		"app_log.txt"
#define		SYSLOG_FILE_NAME_OLD	"app_log_old.txt"
#define		SYSLOG_ROLL_NUM			500

/**
* @class CWrSysLog
* @brief ϵͳ��־������
*/
class CWrSysLog
{														 
public:

	CWrSysLog();
	~CWrSysLog();

	/**
	 * @brief дϵͳ��־
	 * @param[in]  Eventtype �¼����ͺ�
	 * @param[in]  EventResult  �¼����
	 * @param[in]  Backup ��ע��Ϣ
	 * @return 1: SUCCESS, 0: FAILURE
	 */
	static INT32 WrSysLog(UINT8 Eventtype, UINT32 EventResult, string Backup);

	/**
	 * @brief LOG��������
	 * @return 1�����ɹ� 0����ʧ��
	 */
	static INT32 LogRollProc(string &strErr);



private:
	
	/**
	 * @brief �ж�LOG�ļ��Ƿ���Ҫ����
	 * @return 1����� 0����Ҫ����
	 */
	static INT32 isLogRoll();

	/**
	 * @brief ȡapp_log.txt�е����һ����¼���
	 * @param[in]  fp  ��־�ļ�
	 * @return ��¼��ţ� -1 ����
	 */
	static INT32 GetLogNum(FILE *fp);

};

}
#endif


