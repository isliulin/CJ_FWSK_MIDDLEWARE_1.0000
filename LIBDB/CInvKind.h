#ifndef __INV_KIND_H
#define __INV_KIND_H

#include "CTable.h"
#include "CDB.h"


namespace middleware
{
/**
 *@class CInvKind
 *@brief ��˰��Ʊ�ֱ�
 *@brief 
 */
class CInvKind : public CTable
{
public:
    
	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	CInvKind();

    /*!
	@brief ��������	
	*/
	~CInvKind();

    /*!
	@brief ��λ����Ա	
	*/
	UINT8 ResetKind();

    /*!
	@brief �ж�����Ʊ�ֵ���Ϣ�Ƿ���ͬ	
	*/
	UINT8 CompareInvKind(CInvKind *p1, CInvKind *p2);


	UINT32 m_No; 			/**< ������ */
	UINT8  m_fplx;			/**< ��Ʊ���� */
	UINT32 m_Lxssr;			/**< ���������գ�ÿ�µĵڼ��죩 */
	UINT32 m_Lxkjsj;		/**< ���߿���ʱ�䣨��λСʱ�� */
	INT64 m_maxSign;		/**< ���ŷ�Ʊ�޶� */
	INT64 m_maxSum;			/**< ����������Ʊ�ۼ��޶� */
	string m_backup;		/**< �����ֶ� */
	string m_fplxdm;		/**< ��Ʊ���ʹ��� */


	string m_bsqsrq;	/**< ���ݱ�����ʼ����YYYYMMDDHHMMSS */
	string m_bszzrq;	/**< ���ݱ�����ֹ���� YYYYMMDDHHMMSS*/
	string m_kpjzrq;		/**< ��Ʊ��ֹ���� */
};

}
#endif

