#include "CNetPara.h"
#include "LOGCTRL.h"
#include "pos_debug.h"


CNetPara::CNetPara()
{
	
	SET_TABLE_NAME("NETPARA");
	SET_FIELD_NUM(12);

	SET_FIELD_MEMBER(DB_UINT8, &m_IsDhcp, "ISDHCP", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_LocalIP, "LOCIP", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_LocalGate, "LOCGATE", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_LocalMask, "LOCMASK", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_LocalDNS, "LOCDNS", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_ServIP, "SERVIP", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_ServPort, "SERVPORT", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_ServAddr, "SERVADDR", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_FtpIP, "FTPIP", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_FtpPort, "FTPPORT", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_FtpUser, "FTPUSER", 0);		
	SET_FIELD_MEMBER(DB_TEXT, &m_FtpPwd, "FTPPWD", 0);		

	ResetMember();
}

CNetPara::~CNetPara()
{
}

void CNetPara::ResetMember(void)
{
	m_IsDhcp = 0;			/**< �Ƿ��Զ�����IP ģʽ 0:�ֹ� 1:�Զ� */
	m_LocalIP = "";			/**< ����IP */
	m_LocalGate = "";		/**< �������� */
	m_LocalMask = "";		/**< �������� */
	m_LocalDNS = "";		/**< DNS */
	m_ServIP = "";			/**< ������IP��ַ */
	m_ServPort = "";		/**< �������˿ں� */
	m_ServAddr = "";		/**< ����������·�� */
	m_FtpIP = "";			/**< ftp��������ַ */
	m_FtpPort = "";			/**< ftp�˿ں� */
	m_FtpUser = "";			/**< �û��� */
	m_FtpPwd = "";			/**< ���� */
}

