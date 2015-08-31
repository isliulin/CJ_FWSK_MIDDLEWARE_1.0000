
#include "DataClassDesign.h"

CDataUserInfo::CDataUserInfo()
{
	m_Nsrsbh = "";			/**< ��˰��ʶ��� */
	m_Nsrmc = "";			/**< ��˰������ */
	m_Kpjhm = 0;			/**< ��Ʊ������ */
	m_zfFlag = 0;           /**<���ֻ���־ 0�������� 1����ֻ�*/
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
CDataUserInfo::~CDataUserInfo()
{

}

CDataTax::CDataTax()
{
	m_sl= 0;				/**< ˰�� */
	m_backup= "";			/**< ���� */
}
CDataTax::~CDataTax()
{

}

CDataInvVol::CDataInvVol()
{
	m_invtype = 0;
	m_code = "";		
	m_isno = 0;			
	m_ieno = 0;			
	m_remain = 0;		
	m_fpzfs = 0;
	m_usedflag = 1;		
	m_overflag = 1;		
	m_kindcode = "";	
	m_date = 0;				/**< �������� */	
	m_backup1 = 0;			/**< �����ֶ�1 */
	m_backup2 = "";			/**< �����ֶ�2 */	
	
	m_fplxdm = "";
	m_curInvNo = 0;
	m_buyDate = "";
	m_FlagJSorXZ = 0;
	m_fpzl = 0;
	m_lbdm = "";
	m_flag = "";
	m_gpsq = "";
	m_yssh ="";
	m_dqbh ="";
	m_dcbb ="";
	m_fpjjsmw = "";
	m_fpjmw = "";
}
CDataInvVol::~CDataInvVol()
{

}

CDataInvKind::CDataInvKind()
{
	m_fplx = 0;
	m_Lxssr = 0;			/**< ���������գ�ÿ�µĵڼ��죩 */
	m_Lxkjsj = 0;			/**< ���߿���ʱ�䣨��λСʱ�� */
	m_maxSign = 0;
	m_maxSum = 0;			/**< ���Ʊ��� */
	m_backup = "";			/**< �����ֶ� */
	m_fplxdm = "";
	m_bsqsrq = "";
	m_bszzrq = "";
	m_kpjzrq = "";
}
CDataInvKind::~CDataInvKind()
{

}

CDataInvDet::CDataInvDet()
{
	m_fpdm = "";
	m_fphm = 0;
	m_kprq = 0;
	m_kpsj = 0;
	m_kplx = 0;
	m_opid = 0;
	m_sky = "";
	m_sphxh = 0;
	m_spbm = "";
	m_spmc = "";
	m_spdj = 0.0;
	m_spsl = 0.0;
	m_spje = 0;
	m_sl = 0;
	m_property =0;
	m_spdw = "��";
	m_ggxh = "";
	m_spse = 0;
	m_dj=0.0;
	m_je=0;
	m_dotNum = 0;
	m_useFlag = 0;
	
	m_backup = "";
	m_hsbz = 1;
//	pNext = NULL;
}
CDataInvDet::~CDataInvDet()
{

}

CDataInvHead::CDataInvHead()
{
	m_fpdm = "";
	m_fphm = 0;
	m_kprq = 0;
	m_kpsj = 0;
	m_kplx = 0;
	m_kphjje = 0;
	m_yfpdm = "";
	m_yfphm = 0;
	m_fkdw = "";
	m_payerCode = "000000000000000";
	m_sky = "";
	m_sphsl = 0;
	m_fwm = "";
	m_fplb = 0;
	m_scbz = 0;
	m_fpsyh = "";
	m_casign = "";			/**< CAǩ��*/
	m_backup1 = "";
	m_backup2 = "";
	m_kpse = 0;				/**< ˰��*/
	m_kpje = 0;
	m_fplxdm = "";
	m_zfbz = 0;
	m_hyfl = "";
	m_fpzl = "c";
	m_gfdzdh = "";
	m_gfyhzh = "";
	m_jqbh = "";
	m_zyspmc = "";
	m_bsq = "";
	m_xfmc = "";
	m_xfsh = "";
	m_xfdzdh = "";
	m_xfyhzh = "";
	m_fhr = "";
	m_qdbz = "N";
	m_zskl = "";
	m_CurTime="";
	m_zfsj = "";
	m_sksbbh = "";

	m_gvector.clear();
// 	pHead = NULL;
// 	pEnd = NULL;
// 	m_pInvDet = &m_InvDet;
}
CDataInvHead::~CDataInvHead()
{

}

CDataNetPara::CDataNetPara()
{
	m_IsDhcp = 0;			/**< �Ƿ��Զ�����IP */
	m_LocalIP = "";			/**< ����IP */
	m_LocalGate = "";		/**< �������� */
	m_LocalMask = "";		/**< �������� */
	m_LocalDNS = "";		/**< DNS */
	m_ServIP = "";			/**< ������IP��ַ */
	m_ServPort = "";		/**< �������˿ں� */
	m_ServAddr = "";		/**< ����������·�� */
	m_FtpIP = "";			/**< ftp��������ַ */
	m_FtpPort = "";			/**< ftp�˿ں� */
	m_FtpUser = "";			/**< �û��� */
	m_FtpPwd = "";			/**< ���� */
}
CDataNetPara::~CDataNetPara()
{

}

CDataTjxxhz::CDataTjxxhz()
{		
	m_Qsrq = 0;		
	m_Jzrq = 0;		
	m_Qckcfs = 0;		
	m_Lgfpfs = 0;	
	m_Thfpfs = 0;		
	m_Zsfpfs = 0;	
	m_Zffpfs = 0;		
	m_Fsfpfs = 0;	
	m_Fffpfs = 0;		
	m_Kffpfs = 0;	
	m_Qmkcfs = 0;
	
	m_Zsfpljje = 0;		
	m_Zsfpljse = 0;	
	m_Zffpljje = 0;		
	m_Zffpljse = 0;	
	m_Fsfpljje = 0;		
	m_Fsfpljse = 0;	
	m_Fffpljje = 0;		
	m_Fffpljse = 0;	
}
CDataTjxxhz::~CDataTjxxhz()
{

}

CDataDeclare::CDataDeclare()
{		
	m_sq = "";				//����
	m_fpmx = "";			//��Ʊ��ϸ����
	m_fpdxx = "";			//��Ʊ����Ϣ
	m_fphz = "";			//˰���豸��������
	m_szfphz = "";			//��ȫоƬ��������
	m_qtxx = "";			//������Ϣ
}
CDataDeclare::~CDataDeclare()
{

}

