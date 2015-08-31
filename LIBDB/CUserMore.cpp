#include "CUserMore.h"

#include "LOGCTRL.h"
#include "pos_debug.h"

CUserMore::CUserMore()
{

	SET_TABLE_NAME("USER_MORE");
	SET_FIELD_NUM(7);

	SET_FIELD_MEMBER(DB_TEXT, &m_backup1, "BACKUP1", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_backup2, "BACKUP2", 0);	
	SET_FIELD_MEMBER(DB_TEXT, &m_backup3, "BACKUP3", 0);	
	SET_FIELD_MEMBER(DB_TEXT, &m_backup4, "BACKUP4", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_backup5, "BACKUP5", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_backup6, "BACKUP6", 0);	
	SET_FIELD_MEMBER(DB_TEXT, &m_backup7, "BACKUP7", 0);
}

CUserMore::~CUserMore()
{

}

void CUserMore::ResetMember()
{

	m_backup1 = "";			/**< ���� */
	m_backup2 = "";			/**< ���� */
    m_backup3 = "";			/**< ���� */
	m_backup4 = "";			/**< ���� */
	m_backup5 = "";			/**< ���� */
	m_backup6 = "";			/**< ���� */
	m_backup7 = "";			/**< ���� */
}