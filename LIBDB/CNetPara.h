#ifndef __CNETPARA_H
#define __CNETPARA_H

#include "CTable.h"
#include "CDB.h"
#include "SysMacDef.h"

namespace middleware
{
/**
 *@class CNetPara 
 *@brief �û���Ϣ��
 *@brief 
 */
class CNetPara : public CTable
{
public:
    
	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	CNetPara();

    /*!
	@brief ��������	
	*/
	~CNetPara();

	/*!
	@brief ��λȫ���Ա���������㣩	
	*/
	void ResetMember(void);
	

	UINT8  m_IsDhcp;			/**< �Ƿ��Զ�����IP ģʽ 0:�ֹ� 1:�Զ� */
	string m_LocalIP;			/**< ����IP */
	string m_LocalGate;			/**< �������� */
	string m_LocalMask;			/**< �������� */
	string m_LocalDNS;			/**< DNS */
	string m_ServIP;			/**< ������IP��ַ */
	string m_ServPort;			/**< �������˿ں� */
	string m_ServAddr;			/**< ����������·�� */
	string m_FtpIP;				/**< ftp��������ַ */
	string m_FtpPort;			/**< ftp�˿ں� */
	string m_FtpUser;			/**< �û��� */
	string m_FtpPwd;			/**< ���� */

};
}
#endif

