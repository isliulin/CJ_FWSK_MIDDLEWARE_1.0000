#ifndef __CUSERINFO_H
#define __CUSERINFO_H

#include "CTable.h"
#include "CDB.h"
#include "SysMacDef.h"

namespace middleware
{
/**
 *@class CUserInfo 
 *@brief �û���Ϣ��
 *@brief 
 */
class CUserInfo : public CTable
{
public:
    
	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	CUserInfo();

    /*!
	@brief ��������	
	*/
	~CUserInfo();

	/*!
	@brief ��λȫ���Ա���������㣩	
	*/
	void ResetMember(void);
	

	string m_Nsrsbh;			/**< ��˰��ʶ��� */
	string m_Nsrmc;				/**< ��˰������ */
	UINT32 m_Kpjhm;				/**< ��Ʊ������ */
	UINT8  m_zfFlag;            /**<���ֻ���־ 0�������� 1����ֻ�*/
	UINT8  m_Nsrxz;				/**< ��˰����ҵ���� */
	UINT8  m_Hylx;				/**< ��ҵ���� */
	string m_Jspsbh;			/**< ��˰���豸�� */
	string m_Gsdjh;				/**< ���̵ǼǺ� */
	string m_Khyh;				/**< �������� */
	string m_Khzh;				/**< �����˺� */
	string m_Djzcdz;			/**< �Ǽ�ע���ַ */
	string m_Swjgdm;			/**< ����˰����ش��� */
	string m_Swjgmc;			/**< ����˰��������� */
	UINT32 m_Slgs;				/**< ��Ʊ��Ȩ˰�ʸ��� */
	UINT32 m_Kpjsl;				/**< ��Ʊ������ */
	string m_qysj;				/**< ����ʱ�� YYYYMMDDHHMMSS */
	string m_jqbh;				/**< ������� */
	string m_backup;			/**< ���� */

	//�������ݿ�
	string m_ffbz;		/**< �ַ���־ */
	string m_bbh;		/**< �汾�� */
	string m_blxx;		/**< ������Ϣ */
	string m_fplxdm;    /**< ��Ʊ���ʹ��� */
	string m_qtkzxx;    /**< ������չ��Ϣ */
	string m_sksbkl;
	UINT32 m_Fplxgs;	/**< ��Ʊ���͸��� */
	string m_Fplxsz;	/**< ��Ʊ���� */
	string m_bspbh;		/**< ��˰�̱�� */
};
}
#endif
