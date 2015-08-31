#ifndef __CDB_H
#define __CDB_H

#include <pthread.h>
#include "IncludeMe.h"
#include "VersionConfig.h"

#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
#include "sqlite3_34.h"
#else
#include "sqlite3_38.h"
#endif

namespace middleware
{
#define DB_ERRMSG_POS(x) DBG_ASSERT_WARNING(false,("code=%d errmsg=%s",sqlite3_errcode(x),sqlite3_errmsg(x)));

typedef struct sqlite3 DB_CON;

#define PTHREAD_MUTEX_OPEN		1

/**
 *@class CDB 
 *@brief ���ݿ⣨���ࣩ
 *@brief 
 */
class CDB
{
public:
   /*!
	@brief �����ݿ�	
	@return   true  �ɹ��� false ʧ��
	*/   
	bool Open(void);

	/*!
	@brief �������ݿ⣿����	

	@return  
	*/ 
	DB_CON* GetConnect(void);

	/*!
	@brief �ر����ݿ�	
	@return   true  �ɹ��� false ʧ��
	*/ 
	bool Close(void);

	/*!
	@brief �������ݿ�	
	@return   true  ֮ǰ�������� false ֮ǰδ��������������
	*/ 
	bool Lock(void);

	/*!
	@brief �������ݿ�	
	*/ 
	void Unlock(void);

	/*!
	@brief ���ݿ��Ƿ���������״̬	
	@return   true  �ǣ� false ��
	*/
	bool IfLock(void);

	/*!
	@brief ������ݿ����	
	@return   ���ݿ����ָ��
	@attention ��������ֻ������һ�����ݿ������û�����ݿ���󣬸ú�����
	           �½�һ�����ݿ���������ݿ�����Ѵ��ڣ��ú�������ָ��ö����ָ�롣
	*/ 
	static CDB* GetInstance(void);

	static void Init();

	/*!
	@brief ����������	
	@return  
	*/ 
	void MutexLock(void);

	/*!
	@brief ����������	
	*/ 
	void MutexUnlock(void);

	pthread_mutex_t     *m_rwcs;     /**< ���ݿ⻥����*/

private:

    /*!
	@brief ���캯��	
	@attention ���ݿ�Ĭ��Ϊ����״̬
	*/ 
	CDB();

    /*!
	@brief ��������	
	*/
	~CDB();
	
	static CDB*			m_db;		/**< ���ݿ���󣨾�̬�� */
	static const string	m_name;		/**< ���ݿ����ƣ���̬�� */
	DB_CON				*m_con; 	/**< SQLITE3���ݿ�ָ�� */
	bool				m_lock;		/**< ���ݿ�����־ */
	int					countNum;
};

}
#endif


