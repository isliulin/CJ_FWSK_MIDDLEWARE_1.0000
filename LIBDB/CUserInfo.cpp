#include "CUserInfo.h"
#include "LOGCTRL.h"
#include "pos_debug.h"


CUserInfo::CUserInfo()
{
	
	SET_TABLE_NAME("USERINFO");
	SET_FIELD_NUM(18);

	SET_FIELD_MEMBER(DB_TEXT, &m_Nsrsbh, "NSRSBH", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_Nsrmc, "NSRMC", 0);
	SET_FIELD_MEMBER(DB_UINT32, &m_Kpjhm, "KPJHM", 0);
	SET_FIELD_MEMBER(DB_UINT8, &m_zfFlag, "ZFFLAG", 0);
	SET_FIELD_MEMBER(DB_UINT8, &m_Nsrxz, "NSRXZ", 0);
	SET_FIELD_MEMBER(DB_UINT8, &m_Hylx, "HY_LX", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_Jspsbh, "JSPSBH", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_Gsdjh, "GSDJH", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_Khyh, "KHYH", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_Khzh, "KHZH", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_Djzcdz, "DJZCDZ", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_Swjgdm, "SWJGDM", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_Swjgmc, "SWJGMC", 0);
	SET_FIELD_MEMBER(DB_UINT32, &m_Slgs, "SLGS", 0);
	SET_FIELD_MEMBER(DB_UINT32, &m_Kpjsl, "KPJSL", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_qysj, "QYSJ", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_jqbh, "JQBH", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_backup, "BACKUP", 0);		

	ResetMember();
}

CUserInfo::~CUserInfo()
{
}

void CUserInfo::ResetMember(void)
{
	m_Nsrsbh = "";			/**< ��˰��ʶ��� */
	m_Nsrmc = "";			/**< ��˰������ */
	m_Kpjhm = 0;			/**< ��Ʊ������ */
	m_zfFlag = 0;            /**<���ֻ���־ 0�������� 1����ֻ�*/
	m_Nsrxz = 0;			/**< ��˰����ҵ���� */
	m_Hylx = 0;				/**< ��ҵ���� */
	m_Jspsbh = "";			/**< ��˰���豸�� */
	m_Gsdjh = "";			/**< ���̵ǼǺ� */
	m_Khyh = "";			/**< �������� */
	m_Khzh = "";			/**< �����˺� */
	m_Djzcdz = "";			/**< �Ǽ�ע���ַ */
	m_Swjgdm = "";			/**< ����˰����ش��� */
	m_Swjgmc = "";			/**< ����˰��������� */
	m_Slgs = 0;				/**< ��Ʊ��Ȩ˰�ʸ��� */
	m_Kpjsl = 0;			/**< ��Ʊ������ */
	m_backup = "";			/**< ���� */
	m_qysj = "";
	m_ffbz = "";
	m_bbh = "";
	m_blxx = "";
	m_fplxdm = "";
	m_qtkzxx = "";
	m_sksbkl = "";
	m_Fplxgs = 0;
	m_Fplxsz = "";
	m_jqbh = "";
	m_bspbh = "";
}

