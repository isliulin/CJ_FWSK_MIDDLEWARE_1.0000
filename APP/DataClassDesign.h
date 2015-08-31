
#ifndef DATA_CLASS_DESIGN_H
#define DATA_CLASS_DESIGN_H

#include <vector>
#include "IncludeMe.h"

/**
 *@class CDataUserInfo 
 *@brief �û���Ϣ��
 */
class CDataUserInfo
{
public:
    
	CDataUserInfo();
	~CDataUserInfo();

	string m_Nsrsbh;		/**< ��˰��ʶ��� */
	string m_Nsrmc;			/**< ��˰������ */
	UINT32 m_Kpjhm;			/**< ��Ʊ������ */
	UINT8  m_zfFlag;        /**<���ֻ���־ 0�������� 1����ֻ�*/
	UINT8  m_Nsrxz;			/**< ��˰����ҵ���� */
	UINT8  m_Hylx;			/**< ��ҵ���� */
	string m_Jspsbh;		/**< ��˰���豸�� */
	string m_Gsdjh;			/**< ���̵ǼǺ� */
	string m_Khyh;			/**< �������� */
	string m_Khzh;			/**< �����˺� */
	string m_Djzcdz;		/**< �Ǽ�ע���ַ */
	string m_Swjgdm;		/**< ����˰����ش��� */
	string m_Swjgmc;		/**< ����˰��������� */
	UINT32 m_Slgs;			/**< ��Ʊ��Ȩ˰�ʸ��� */
	UINT32 m_Kpjsl;			/**< ��Ʊ������ */
	string m_qysj;			/**< ����ʱ�� YYYYMMDDHHMMSS */
	string m_jqbh;			/**< ������� */
	string m_backup;		/**< ���� */

	string m_bbh;			/**< �汾�� */
	string m_blxx;			/**< ������Ϣ */
	string m_fplxdm;  		/**< ��Ʊ���ʹ��� */
	string m_qtkzxx;   		/**< ������չ��Ϣ */
	string m_sksbkl;   		/**< ˰���豸���� */
	UINT32 m_Fplxgs;		/**< ��Ʊ���͸��� */
	string m_Fplxsz;		/**< ��Ʊ���� */
	string m_bspbh;			/**< ��˰�̱�� */
};

/**
 *@class CDataTax 
 *@brief ��ҵ��Ϣ��
 */
class CDataTax
{
public:

	CDataTax();
	~CDataTax();

    UINT32 m_no;			/**< ��� */
	UINT32 m_sl;			/**< ˰�� */
	string m_backup;		/**< ���� */	
};

/**
 *@class CDataInvVol 
 *@brief ��Ʊ������Ϣ��
 */
class CDataInvVol
{
public:
    
	CDataInvVol();
	~CDataInvVol();

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

	UINT32 m_curInvNo;		/**< ��ǰ��Ʊ�ţ������ */
	string m_buyDate;		/**< ��������(���ϻ�ȡ��ʱ��)*/
	UINT32 m_FlagJSorXZ;	/**< ҵ���:��Ʊ�����or���ر�ʶ��1��ʾ������0��ʾ����*/
	UINT32 m_fpzl;			/**< ��Ʊ����*/
	string m_lbdm;			/**< ������*/
	string m_flag;			/**< д��������Ʊ��������Ϣ*/
	string m_gpsq;			/**< ��Ʊ��Ȩ*/
	string m_yssh;			/**<ѹ��˰��*/
	string m_dqbh;			/**<�������*/
	string m_dcbb;			/**<�ײ�汾*/
	string m_fpjjsmw;		/**<��Ʊ���������*/
	string m_fpjmw;			/**<��Ʊ������Ϣ*/
};

/**
 *@class CDataInvKind
 *@brief ��˰��Ʊ����
 */
class CDataInvKind
{
public:
    
	CDataInvKind();
	~CDataInvKind();

	UINT8  m_fplx;			/**< ��Ʊ���� */
	UINT32 m_Lxssr;			/**< ���������գ�ÿ�µĵڼ��죩 */
	UINT32 m_Lxkjsj;		/**< ���߿���ʱ�䣨��λСʱ�� */
	INT64  m_maxSign;		/**< ���ŷ�Ʊ�޶� */
	INT64  m_maxSum;		/**< ����������Ʊ�ۼ��޶� */
	string m_backup;		/**< �����ֶ� */
	string m_fplxdm;		/**< ��Ʊ���ʹ��� */


	string m_bsqsrq;		/**< ���ݱ�����ʼ����YYYYMMDDHHMMSS */
	string m_bszzrq;		/**< ���ݱ�����ֹ���� YYYYMMDDHHMMSS*/
	string m_kpjzrq;		/**< ��Ʊ��ֹ���� */
};

/**
 *@class CDataInvDet 
 *@brief ��Ʊ��ϸ��Ϣ��
 */
class CDataInvDet;
class CDataInvDet
{
public:
    
	CDataInvDet();
	~CDataInvDet();

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
	double m_dj;			/**< ��Ʒ����(����˰) */
	INT64  m_je;			/**< ��Ʒ���(����˰) */
	
	INT32 m_dotNum;         /**< ��������������С��λ�� */
	UINT8 m_useFlag;		/**< �Ƿ���ñ�־��0==���ã�1==������ */
	string m_backup;		/**< ���� */
	UINT8 m_hsbz;			/**< ��˰�۱�־(1:���ۺ�˰ 0:���۲���˰) */

// 	class CDataInvDet *pNext;	/**< ָ����һ����Ʒ��ϸ��Ϣ�� */
};

/**
 *@class CDataInvHead 
 *@brief ��Ʊ������Ϣ��
 */
class CDataInvHead
{
public:
    
	CDataInvHead();
	~CDataInvHead();

	string m_fpdm;			/**< ��Ʊ���� */
	UINT32 m_fphm;			/**< ��Ʊ���� */
	UINT32 m_kprq;			/**< ��Ʊ���� */
	UINT32 m_kpsj;			/**< ��Ʊʱ�� */
	UINT8  m_kplx;			/**< ��Ʊ���� */
	INT64  m_kphjje;		/**< ��Ʊ�ϼƽ���˰�� */
	string m_yfpdm;			/**< ԭ��Ʊ���� */
	UINT32 m_yfphm;			/**< ԭ��Ʊ���� */
	string m_fkdw;			/**< ���λ */
	string m_payerCode;     /**< ���λ˰�� */
	string m_sky;			/**< �տ�Ա */
	UINT32 m_sphsl;			/**< ��Ʒ������ */
	string  m_fwm;			/**< ��α˰���� */
	UINT8 m_fplb;		    /**< ��Ʊ��� */
	UINT8  m_scbz;			/**< �ϴ���־ */
	string m_fpsyh;         /**< ��Ʊ������*/
	string m_zfsj;			/**< ����ʱ�� */
	
	string m_casign;		/**< CAǩ��*/
	
	string m_backup1;		/**< ����1 */
	string m_backup2;		/**< ����2 */

	INT64 m_kpse;			/**< ˰��*/
	INT64 m_kpje;			/**< ���(����˰��)*/
	string m_fplxdm;		/**< ��Ʊ���ʹ��� */

	UINT8  m_zfbz;			/**<  ���ϱ�־*/
	string m_hyfl;			/**< ��ҵ���� */

	string m_fpzl;			/**< ��Ʊ���� Ĭ��Ϊ"c" */
	string m_gfdzdh;		/**< ������ַ�绰 */
	string m_gfyhzh;		/**< ���������˺� */
	string m_jqbh;			/**< ������� */
	string m_zyspmc;		/**< ��Ҫ��Ʒ���� */
    string m_bsq;			/**< ��˰�� */
	string m_sksbbh;		/**< ��˰�̱�� */

	string m_xfmc;			/**< �������� */
	string m_xfsh;			/**< ����˰�� */
	string m_xfdzdh;		/**< ������ַ�绰 */
	string m_xfyhzh;		/**< ���������˺� */
	string m_fhr; 			/**< ������ */
    string m_qdbz;			/**< �嵥��־ */

	string m_zskl;			/**< ֤����� */
	string m_CurTime;		/**< ��ǰʱ��*/

	vector<CDataInvDet> m_gvector;
//	CDataInvDet *pHead;		/**< ��Ʒ��ϸ����ͷ */
// 	CDataInvDet *pEnd;		/**< ��Ʒ��ϸ����β�� */
// 	CDataInvDet m_InvDet;	/**< ��Ʒ��ϸ�ӱ� */
// 	CDataInvDet *m_pInvDet;	/**< ��Ʒ��ϸ�ӱ�ָ�� */

};

/**
 *@class CDataNetPara 
 *@brief ���������
 */
class CDataNetPara
{
public:
    
	CDataNetPara();
	~CDataNetPara();

	UINT8  m_IsDhcp;			/**< �Ƿ��Զ�����IP */
	string m_LocalIP;			/**< ����IP */
	string m_LocalGate;			/**< �������� */
	string m_LocalMask;			/**< �������� */
	string m_LocalDNS;			/**< DNS */
	string m_ServIP;			/**< ������IP��ַ */
	string m_ServPort;			/**< �������˿ں� */
	string m_ServAddr;			/**< ����������·�� */
	string m_FtpIP;				/**< ftp��������ַ */
	string m_FtpPort;			/**< ftp�˿ں� */
	string m_FtpUser;			/**< �û��� */
	string m_FtpPwd;			/**< ���� */
};


/**
 *@class CDataTjxxhz
 *@brief ͳ����Ϣ������
 */
class CDataTjxxhz
{
public:
    
	CDataTjxxhz();
	~CDataTjxxhz();
		
public:
	UINT8  m_Type;			/**< ��Ʊ����*/
	UINT32  m_Qsrq;			/**< ��ʼ����*/
	UINT32  m_Jzrq;			/**< ��ֹ����*/
	UINT32  m_Qckcfs;		/**< �ڳ������� */
	UINT32  m_Lgfpfs;		/**< �칺��Ʊ���� */
	UINT32  m_Thfpfs;		/**< �˻ط�Ʊ���� */
	UINT32  m_Zsfpfs;		/**< ������Ʊ���� */
	UINT32  m_Zffpfs;		/**< ���Ϸ�Ʊ���� */
	UINT32  m_Fsfpfs;		/**< ������Ʊ���� */
	UINT32  m_Fffpfs;		/**< ���Ϸ�Ʊ���� */
	UINT32  m_Kffpfs;		/**< �շϷ�Ʊ���� */
	UINT32  m_Qmkcfs;		/**< ��ĩ������ */
	INT64	m_Zsfpljje;		/**< ������Ʊ�ۼƽ�� */
	INT64	m_Zsfpljse;		/**< ������Ʊ�ۼ�˰�� */
	INT64	m_Zffpljje;		/**< ���Ϸ�Ʊ�ۼƽ�� */
	INT64	m_Zffpljse;		/**< ���Ϸ�Ʊ�ۼ�˰�� */
	INT64	m_Fsfpljje;		/**< ������Ʊ�ۼƽ�� */
	INT64	m_Fsfpljse;		/**< ������Ʊ�ۼ�˰�� */
	INT64	m_Fffpljje;		/**< ���Ϸ�Ʊ�ۼƽ�� */
	INT64	m_Fffpljse;		/**< ���Ϸ�Ʊ�ۼ�˰�� */

};

/**
 *@class CDeclare
 *@brief ���ݳ�����Ϣ������
 */
class CDataDeclare
{
public:
    
	CDataDeclare();
	~CDataDeclare();
		
public:
	string m_sq;			//����
	string m_fpmx;			//��Ʊ��ϸ����
	string m_fpdxx;			//��Ʊ����Ϣ
	string m_fphz;			//˰���豸��������
	string m_szfphz;		//��ȫоƬ��������
	string m_qtxx;			//������Ϣ
	
};


#define MAX_ERR_INV_COUNT	10
class CDataInvServ
{
public:
	
	CDataInvServ()
	{
		m_fpdm = "";
		m_fphm = 0;
		m_errMsg = "";
	}
	~CDataInvServ(){}
	
	string m_fpdm;			/**< ��Ʊ���� */
	UINT32 m_fphm;			/**< ��Ʊ���� */
	string m_errMsg;		/**< �������� */
};





#endif
