#ifndef __CRT_INV_H
#define __CRT_INV_H

#include "CTable.h"
#include "CDB.h"

namespace middleware
{
/**
 *@class CRtInv 
 *@brief ���˷�Ʊ��Ϣ��
 *@brief 
 */
class CRtInv : public CTable
{
public:
    
	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	CRtInv();

    /*!
	@brief ��������	
	*/
	~CRtInv();

	/*!
	@brief �����жϣ������ڼ�¼̫��ʱ���Ƿ�ɾ�����ּ�¼
	@param[in] nCount ��ʵ�ʴ洢�ļ�¼����
	@param[out] nDelNo ʵ��Ҫɾ����¼�Ľ�ֹ���
	@return  0 ʧ�ܣ�  1 �ɹ�
	*/
	INT32 CheckRoll(INT32 nCount, UINT32 &nDelNo);

	/*!
	@brief �����������ڼ�¼̫��ʱ��ɾ�����ּ�¼
	@param[in] nDelNo ʵ��Ҫɾ����¼�Ľ�ֹ���
	@return  0 ʧ�ܣ�  1 �ɹ�
	*/
	INT32 Roll(UINT32 nDelNo);
  
	
	UINT32 m_no; 		/**< ������ */	
	string m_fpdm;		/**< ��Ʊ���� */
	UINT32 m_fphm;		/**< ��Ʊ���� */
};

}
#endif
