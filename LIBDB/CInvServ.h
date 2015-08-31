#ifndef __CINVSERV_H
#define __CINVSERV_H

#include "CTable.h"
#include "CDB.h"

#include "CInvHead.h"

namespace middleware
{
/**
 *@class CInvServ 
 *@brief ��Ʊ�����
 *@brief 
 */
class CInvServ : public CTable
{
public:
    
	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	CInvServ();

    /*!
	@brief ��������	
	*/
	~CInvServ();

	/*!
	@brief ����һ����¼
	@param[in]  pInv  ��Ʊ��¼
	@param[in]  upFlag  �ϴ���־ 0=δ�ϴ���1 = ���ϴ�
	@param[in]  backup  ��������
	@param[in]  caSign  CAǩ��+֤�����к�
	@param[out]  nNum  ���������������Inv_Serv��ģ�
	@return 1  �ɹ��� 0  ʧ��
	*/
	UINT8 Save(const CInvHead *pInv, UINT32 &nNum, INT64 &nSum, string &StrEr);

	UINT32 m_no; 			/**< ������ */
	string m_code;			/**< ��Ʊ���� */
	string m_fpsyh;         /**< ��Ʊ������*/
	UINT32 m_InvNo;			/**< ��Ʊ���� */
	UINT32 m_issueDate;		/**< ��Ʊ���� */
	UINT32 m_issueTime;		/**< ��Ʊʱ�� */
	UINT8  m_issuetype;		/**< ��Ʊ���� */
	INT64 m_moneySum;		/**< ��Ʊ�ܽ�� */
	UINT8 m_upFlag;			/**< �ϴ���־ 0=δ�ϴ���1 = ���ϴ�  */
	UINT8 m_wstFlag;		/**< ���ϱ�־  0=δ���ϣ� 1=������*/
	string m_caSign;		/**< CAǩ��+֤�����к�*/
	string m_backup;		/**< �����ֶ� */
	string m_errMsg;
};
}
#endif
