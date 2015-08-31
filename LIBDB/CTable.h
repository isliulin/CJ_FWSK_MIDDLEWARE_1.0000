#ifndef __CTABLE_H
#define __CTABLE_H

#include "IncludeMe.h"
#include "CDB.h"

namespace middleware
{
#define PRIMARY 1
#define UN_PRIMARY 0
#define MAX_NUM 20
 
/**
 *@enum DB_TYPE 
 *@brief ��������
 */
typedef enum
{
	DB_UINT32 = 1,
	DB_INT64,
	DB_UINT16,
	DB_UINT8,
	DB_TEXT,
	DB_BLOB,
	DB_FLOAT,
	DB_DOUBLE,
	DB_DATETIME
}DB_TYPE;


/**
 *@class CTable 
 *@brief �����ࣩ
 *@brief 
 */
class CTable
{
public:
	
    /*!
	@brief ���캯��	
	@attention ���ݿ�Ĭ��Ϊ����״̬
	*/ 
	CTable();

	/*!
	@brief ��������	
	@attention ���ݿ�Ĭ��Ϊ����״̬
	*/ 
	~CTable();

//------------------
    /*!
	@brief ���ñ���	
    @param[in] name: ����
	*/
	void SetTableName(const string name);

	/*!
	@brief ����SQL���	
	@param[in] sql: SQL���
	*/
	void SetSQL(const string sql);

	/*!
	@brief ���SQL���	
	@return  SQL���
	*/
	string GetSQL(void) const;

    /*!
	@brief ��ȡ����	
	@return ����
	*/
	string GetTableName(void) const;

//-----------------
	/*!
	@brief �����¼�������벻�ɹ������Զ�����3�Σ�	
	@return sqlite����ִ�н������
	*/
	INT32 AddNew(void);

	/*!
	@brief �����¼һ��	
	@return sqlite����ִ�н������
	*/
	INT32 AddNewOnce(void);

	/*!
	@brief ��ѯ��¼
	@return sqlite����ִ�н������
	*/
	INT32 Requery(void);

	/*!
	@brief ɾ����¼	
	@return sqlite����ִ�н������
	*/
	INT32 Delete(void);

	/*!
	@brief ���¼�¼	
	@return strsql ���²�����������䣨��where NO = 1��
	@warning �����������������ַ������һ������ΪNULL���Ҳ���ȱ�١�
			 ����ڶ��������������string���ͣ�û�д������ַ������ɳ����ж�(Abort)��
	@note ���磺
	CInvHead invhead;
	char sqlbuf[128];
	sprintf(sqlbuf,"where NO = %u ", 1);
	invhead.m_payer = "����";
	invhead.m_opId = 5;
	invhead.m_moneySum = 100000;
	invhead.Update(sqlbuf, &invhead.m_payer, &invhead.m_opId, &invhead.m_moneySum, NULL);
	*/
	INT32 Update(string strsql, ...);

	/*!
	@brief ִ��SQL��䣨������ִ�У�	
	@return sqlite����ִ�н������
	*/
	INT32 ExecuteSQL(void);
    
	/*!
	@brief ִ��SQL��䣨��������ִ�У�	
	@return sqlite����ִ�н������
	*/
	INT32 SQlite3EXec(void);

    /*!
	@brief ͳ�Ʊ����ĳ�޶������ļ�¼��Ŀ	
	@return >=0: ��¼��Ŀ; -1: ͳ��ʧ��
	@attention ���øú���ǰֻ�����ú��޶�������m_filter��
	*/
    INT32 GetRecordNum(void);


	/*!
	@brief ִ����һ������ֵ��sql���
	@param[in]  ntype  ��������
	@param[out] pValue ���
	@return �������
	@attention ����sql���ִ�к�ֻ��һ�������
	           ���ô˺���ǰ�����������ú�������sql��䣨m_sql����
	*/
	INT32 GetOneResult(DB_TYPE ntype, void* pValue);
    
	/*!
	@brief ִ���ж������ֵ��sql���
	@param[in]  ntype  ������������
	@param[in]  nColNum  ���������
	@param[out] pValue ���
	@param[out] nRowCount ���������
	@return     SQLITE_OK ִ�гɹ����������������
	@attention ����sql���ִ�к��ж�����,
	           ���ô˺���ǰ�����������ú�������sql��䣨m_sql����
	*/
	INT32 GetMultiResult(DB_TYPE *ntype, void* pValue[], UINT8 nColNum, INT32 &nRowCount);

	/*!
	@brief ȡ��һ����¼	
	@return 
	*/
	INT32 MoveFirst(void);

	/*!
	@brief ȡ��һ����¼	
	@return 
	*/
	INT32 MoveNext(void);

	/*!
	@brief ��ֹ��ѯ	
	@return 1 SUCCESS��0 FAILURE
	@attention ��;������MoveFirst()��MoveNext()����SQLITE_ROWʱȴ��ֹͣ��ѯ��
	*/
	INT32 MoveEnd(void);

	/*!
	@brief ȡ��һ����¼	
	@param[in]  strsql  ��Ҫ��ѯ���ݵ��������
	@note �������MoveFirst()��MoveNext()����������
	@return 
	*/
	INT32 Foreach(string strsql="");
	/*!
	@brief ��ֹ��ѯ	
	@return 1 SUCCESS��0 FAILURE
	@attention ��;��Foreach()����SQLITE_ROWʱȴ��ֹͣ��ѯ��
	*/
	INT32 ForeachEnd();

	/*!
	@brief ��ȡһ����¼	
	@return 
	*/
	INT32 LoadOneRecord(void);

	/*!
	@brief ��ȡһ����¼	
	@param[in]  strsql ��ѯ��������䣨��where NO = 1��
	@return 
	*/
	INT32 LoadOneRecordBySql(string strsql="");

	/*!
	@brief ��ȡ���ݿ�����Ĵ�����뼰����
	@return 
	*/
	INT32 getErrMsg(string &errmsg);

	string  m_filter;

	/*!
	@brief ������ʼ	
	@return 
	*/
	INT32 BeginTransaction();
	/*!
	@brief ���������
	@return 
	*/
	INT32 EndTransaction();

protected:
    
	/*!
	@brief ע�����	
	@param[in] name  ����
	*/
	void SET_TABLE_NAME(const string name);

	/*!
	@brief ע����Ŀ����	
	@param[in] num  ���� 
	*/
	void SET_FIELD_NUM(const INT32 num);

	/*!
	@brief ע����Ŀ�����Ϣ	
	@param[in] type         �������� 
	@param[in] fieldPtr     �������ݴ�ŵĵ�ַ
	@param[in] fieldNameDB  ����Ŀ�����ݿ��е�����
	@param[in] typeSize     ���ͳ���
	*/
	void SET_FIELD_MEMBER(DB_TYPE type, void* fieldPtr, 
						  string fieldNameDB, INT32 typeSize);

	void SET_FIELD_MEMBER(UINT32* fieldPtr, string fieldNameDB);
	void SET_FIELD_MEMBER(UINT16* fieldPtr, string fieldNameDB);
	void SET_FIELD_MEMBER(UINT8* fieldPtr, string fieldNameDB);
	void SET_FIELD_MEMBER(INT64* fieldPtr, string fieldNameDB);
	void SET_FIELD_MEMBER(string* fieldPtr, string fieldNameDB);
	void SET_FIELD_MEMBER(float* fieldPtr, string fieldNameDB);
	void SET_FIELD_MEMBER(double* fieldPtr, string fieldNameDB);
	void SET_FIELD_MEMBER(UINT8* fieldPtr, string fieldNameDB, INT32 typeSize);

	virtual void SynFunc() {}
	
private:

	string		m_name;
	string		m_sql;
	INT32		m_fieldNum;
	INT32		m_tmpNum;
	INT32		m_rowCount;
	DB_TYPE		*m_fieldType;
	INT32		*m_fieldTypeSize;
	UINT32		*m_fieldPtr;
	string		*m_fieldNameDB;
	UINT8       *m_fieldKey;
	DB_CON		*m_con;
	CDB			*m_db;
	sqlite3_stmt *m_sqstmt;

	/*!
	@brief ��װ��ѯ���SQL���	
	*/

	void CreateRequerySQL(void);

	/*!
	@brief ��װ������SQL���	
	*/
	void CreateAddSQL(void);

	/*!
	@brief �����жϺ���������ڱ�����ӵ��ֶγ��������ʵ���ֶ��������˳���
	*/
	void AbnormalExit();

protected:
	/*!
	@���Ƿ���й��������ԣ�1=������0=������	
	*/
	INT32        m_roll;
};

string strfmt(const char *fmt,...);
}
#endif


