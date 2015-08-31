#ifndef __CINV_DET_H
#define __CINV_DET_H

#include "CTable.h"
#include "CDB.h"

namespace middleware
{
#define DET_ARRAY_LEN      64     //s_DetArray[]��̬����ĳ���

class CInvDet;
extern CInvDet *s_DetArray[DET_ARRAY_LEN];

/**
 *@class CInvDet 
 *@brief ��Ʊ��ϸ��Ϣ��
 *@brief 
 */
class CInvDet : public CTable
{
public:
    
	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	CInvDet();

    /*!
	@brief ��������	
	*/
	~CInvDet();

	/*!
	@brief �����������ڼ�¼̫��ʱ��ɾ�����ּ�¼
	@return   SQLITE_OK �ɹ��� ���� sqlite3�Ĵ����
	*/
	INT32 Roll(void);
    
	/*!
	@brief ͳ��ĳ�޶�������˰��˰Ŀ�ķ��࿪Ʊ���
	@param[in]  taxIDNum ˰��˰Ŀ�����Ŀ
	@param[in] taxID ˰��˰Ŀ�������ʼ��ַ
	@param[out] Money ����������������ʼ��ַ
	@return  ʵ�ʿ�Ʊ��˰��˰Ŀ����
	@attention ��m_filter�����޶����� 
	*/
//	UINT32 GetMoneySum(UINT32 *Money, UINT8 *taxID, UINT8 taxIDNum);

	/*!
	@brief ͳ��ĳ�޶������¿�Ʊ���
	@return  ĳ�޶������¿�Ʊ���
	@attention ��m_filter�����޶����� 
	*/
	INT64 PartMoneySum();

	/*!
	@brief ��ȡs_DetArray[]��һ�����õ�CInvDet�����
	@return  CInvDet* ���õ�CInvDet������ָ��
	@attention ���޿��ö����򷵻�NULL 
	*/
	CInvDet* GetNewInvDet(void);

	/*!
	@brief �ָ�s_DetArray[]��һ��CInvDet�����Ϊ����״̬
	@return  SUCCESS �ɹ�
	*/
	UINT8 FreeInvDet();
    
	INT32  m_no; 			/**< ���� */
	string m_fpdm;			/**< ��Ʊ���� */
	UINT32 m_fphm;			/**< ��Ʊ���� */
	
	UINT32 m_kprq;			/**< ��Ʊ���� */
	UINT32 m_kpsj;			/**< ��Ʊʱ�� */
	UINT8  m_kplx;			/**< ��Ʊ���� */
	UINT8  m_opid;          /**< ����Աid */
	string m_sky;			/**< �տ�Ա */
	
	UINT32 m_sphxh;			/**< ��Ʒ����ţ���1��ʼ */
	string m_spbm;			/**< ��Ʒ���� */
	string m_spmc;			/**< ��Ʒ���� */
	double m_spdj;			/**< ��Ʒ����(��˰) */
	double m_spsl;			/**< ��Ʒ���� */
	INT64  m_spje;			/**< ��Ʒ���(��˰) */
	float  m_sl;			/**< ˰�� */
	UINT8  m_property;		/**< ��Ʒ������ */
	string m_spdw;			/**< ��λ */
	string m_ggxh;			/**< ����ͺ� */

	INT64 m_spse;			/**< ��Ʒ˰�� */
	double m_dj;		/**< ��Ʒ����(����˰) */
	INT64  m_je;		/**< ��Ʒ���(����˰) */
	
	INT32 m_dotNum;         /**< ��������������С��λ�� */
	class CInvDet *pNext;	/**< ָ����һ����Ʒ��ϸ��Ϣ�� */
	UINT8 m_useFlag;		/**< �Ƿ���ñ�־��0==���ã�1==������ */

	string m_backup;		/**< ���� */
	
	//�������ݿ�
	UINT8 m_hsbz;         /**< ��˰�۱�־(1:���ۺ�˰ 0:���۲���˰) */

};

}
#endif
