#ifndef __CUSERMORE_H
#define __CUSERMORE_H

#include "CTable.h"
#include "CDB.h"

namespace middleware
{
/**
 *@class CUserMore 
 *@brief �����û���Ϣ��
 *@brief 
 */
class CUserMore : public CTable
{
public:
    
	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	CUserMore();

    /*!
	@brief ��������	
	*/
	~CUserMore();

    void  ResetMember(); //��ո�������

	string m_backup1;			/**< ���� */
	string m_backup2;			/**< ���� */
	string m_backup3;			/**< ���� */
	string m_backup4;			/**< ���� */
	string m_backup5;			/**< ���� */
	string m_backup6;			/**< ���� */
	string m_backup7;			/**< ���� */
};
}
#endif

