#ifndef __CINV_VOL_H
#define __CINV_VOL_H

#include "CTable.h"
#include "CDB.h"
#include "SysMacDef.h"

namespace middleware
{
/**
 *@class CInvVol 
 *@brief ��Ʊ������Ϣ��
 *@brief 
 *@update Ϊ����ҵ���:��Ʊ�����/����XML�ļ�
 *����װ�ͽ��������岻������ݳ�Ա_linzihao��20150418
 */
class CInvVol : public CTable
{
public:
    
	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	CInvVol();

    /*!
	@brief ��������	
	*/
	~CInvVol();

	/*!
	@brief ɾ��������ķ�Ʊ����Ϣ	
	*/
	void DelUsedVol();

	/*!
	@brief ɾ��������ķ�Ʊ����Ϣ	
	*/
	void ResetVol();

	UINT32 m_no; 			/**< ������ */
	UINT8  m_invtype;		/**< ��Ʊ��� */
	string m_code;			/**< ��Ʊ���� */
	UINT32 m_isno;			/**< ��Ʊ��ʼ���� */
	UINT32 m_ieno;			/**< ��Ʊ��ֹ���� */
	UINT32 m_remain;		/**< ʣ����� */
	UINT32 m_fpzfs;			/**< ��Ʊ�ܷ��� */
	UINT8  m_usedflag;		/**< ʹ�ñ�־ */
	UINT8  m_overflag;		/**< �����־ */
	string m_kindcode;		/**< ��Ʊ������� */
	UINT32 m_date;			/**< �������� */	
	UINT32 m_backup1;		/**< �����ֶ�1 */
	string m_backup2;		/**< �����ֶ�2 */
	string m_fplxdm;		/**< ��Ʊ���ʹ��� */

	//---�����----//
	UINT32 m_curInvNo;    /**< ��ǰ��Ʊ�ţ������ */
	string m_buyDate;    /**< ��������(���ϻ�ȡ��ʱ��)*/
	UINT32 m_FlagJSorXZ;		/**< ҵ���:��Ʊ�����or���ر�ʶ��1��ʾ������0��ʾ����*/
	UINT32 m_fpzl;		/**< ��Ʊ����*/
	string m_lbdm;		/**< ������*/
	string m_flag;		/**< д��������Ʊ��������Ϣ*/
	string m_gpsq;		/**< ��Ʊ��Ȩ*/
	string m_yssh;		/**<ѹ��˰��*/
	string m_dqbh;		/**<�������*/
	string m_dcbb;		/**<�ײ�汾*/
	string m_fpjjsmw;		/**<��Ʊ���������*/
	string m_fpjmw;		/**<��Ʊ������Ϣ*/
};

}
#endif
