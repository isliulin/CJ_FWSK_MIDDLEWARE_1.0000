#ifndef __CSYSARG_H
#define __CSYSARG_H

#include "CTable.h"
#include "CDB.h"

namespace middleware
{
#define SYS_ARG_BLOB_LEN	20

/**
 *@class CSysArg 
 *@brief ϵͳ������
 *@brief 
 */
class CSysArg : public CTable
{
public:

	/*!
	@brief ���캯��	
	*/
	CSysArg();

	/*!
	@brief ��������	
	*/
	~CSysArg();

	UINT8 	m_said;		/**< ϵͳ������ */
	string	m_name;		/**< ϵͳ�������� */
	UINT32	m_vInt;		/**< ϵͳ��������ֵ */
	string	m_vText;	/**< ϵͳ�����ַ���ֵ */
	UINT8	m_vBlob[SYS_ARG_BLOB_LEN];	/**< ϵͳ��������ֵ */
};
}
#endif

