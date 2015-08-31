/*! \file  DataTransformFunc.cpp
\brief    ����ת������
\author   zfj
\version  1.0
\date     2015-04-16
*/

#include "DataTransformFunc.h"
#include "CGlobalArgLib.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

CDataTransformFunc::CDataTransformFunc()
{
}
CDataTransformFunc::~CDataTransformFunc()
{
}

void CDataTransformFunc::UserInfo2Data(CUserInfo *pUserInfo, CDataUserInfo *pDataUserInfo)
{
	pDataUserInfo->m_Nsrsbh = pUserInfo->m_Nsrsbh;		/**< ��˰��ʶ��� */
	pDataUserInfo->m_Nsrmc = pUserInfo->m_Nsrmc;		/**< ��˰������ */
	pDataUserInfo->m_Kpjhm = pUserInfo->m_Kpjhm;		/**< ��Ʊ������ */
	pDataUserInfo->m_zfFlag = pUserInfo->m_zfFlag;      /**<���ֻ���־ 0�������� 1����ֻ�*/
	pDataUserInfo->m_Nsrxz = pUserInfo->m_Nsrxz;		/**< ��˰����ҵ���� */
	pDataUserInfo->m_Hylx = pUserInfo->m_Hylx;			/**< ��ҵ���� */
	pDataUserInfo->m_Jspsbh = pUserInfo->m_Jspsbh;		/**< ��˰���豸�� */
	pDataUserInfo->m_Gsdjh = pUserInfo->m_Gsdjh;		/**< ���̵ǼǺ� */
	pDataUserInfo->m_Khyh = pUserInfo->m_Khyh;			/**< �������� */
	pDataUserInfo->m_Khzh = pUserInfo->m_Khzh;			/**< �����˺� */
	pDataUserInfo->m_Djzcdz = pUserInfo->m_Djzcdz;		/**< �Ǽ�ע���ַ */
	pDataUserInfo->m_Swjgdm = pUserInfo->m_Swjgdm;		/**< ����˰����ش��� */
	pDataUserInfo->m_Swjgmc = pUserInfo->m_Swjgmc;		/**< ����˰��������� */
	pDataUserInfo->m_Slgs = pUserInfo->m_Slgs;			/**< ��Ʊ��Ȩ˰�ʸ��� */
	pDataUserInfo->m_Kpjsl = pUserInfo->m_Kpjsl;		/**< ��Ʊ������ */
	pDataUserInfo->m_qysj = pUserInfo->m_qysj;			/**< ����ʱ�� YYYYMMDDHHMMSS */
	pDataUserInfo->m_jqbh = pUserInfo->m_jqbh;			/**< ������� */
	pDataUserInfo->m_backup = pUserInfo->m_backup;		/**< ���� */
	
	pDataUserInfo->m_bbh = pUserInfo->m_bbh;			/**< �汾�� */
	pDataUserInfo->m_blxx = pUserInfo->m_blxx;			/**< ������Ϣ */
	pDataUserInfo->m_fplxdm = pUserInfo->m_fplxdm;  	/**< ��Ʊ���ʹ��� */
	pDataUserInfo->m_qtkzxx = pUserInfo->m_qtkzxx;   	/**< ������չ��Ϣ */
	pDataUserInfo->m_sksbkl = pUserInfo->m_sksbkl;   	/**< ˰���豸���� */
	pDataUserInfo->m_Fplxgs = pUserInfo->m_Fplxgs;		/**< ��Ʊ���͸��� */
	pDataUserInfo->m_Fplxsz = pUserInfo->m_Fplxsz;		/**< ��Ʊ���� */
	pDataUserInfo->m_bspbh = pUserInfo->m_bspbh;		/**< ��˰�̱�� */

	return;
}

void CDataTransformFunc::Data2UserInfo(CDataUserInfo *pDataUserInfo, CUserInfo *pUserInfo)
{
	pUserInfo->m_Nsrsbh = pDataUserInfo->m_Nsrsbh;		/**< ��˰��ʶ��� */
	pUserInfo->m_Nsrmc = pDataUserInfo->m_Nsrmc;		/**< ��˰������ */
	pUserInfo->m_Kpjhm = pDataUserInfo->m_Kpjhm;		/**< ��Ʊ������ */
	pUserInfo->m_zfFlag = pDataUserInfo->m_zfFlag;      /**<���ֻ���־ 0�������� 1����ֻ�*/
	pUserInfo->m_Nsrxz = pDataUserInfo->m_Nsrxz;		/**< ��˰����ҵ���� */
	pUserInfo->m_Hylx = pDataUserInfo->m_Hylx;			/**< ��ҵ���� */
	pUserInfo->m_Jspsbh = pDataUserInfo->m_Jspsbh;		/**< ��˰���豸�� */
	pUserInfo->m_Gsdjh = pDataUserInfo->m_Gsdjh;		/**< ���̵ǼǺ� */
	pUserInfo->m_Khyh = pDataUserInfo->m_Khyh;			/**< �������� */
	pUserInfo->m_Khzh = pDataUserInfo->m_Khzh;			/**< �����˺� */
	pUserInfo->m_Djzcdz = pDataUserInfo->m_Djzcdz;		/**< �Ǽ�ע���ַ */
	pUserInfo->m_Swjgdm = pDataUserInfo->m_Swjgdm;		/**< ����˰����ش��� */
	pUserInfo->m_Swjgmc = pDataUserInfo->m_Swjgmc;		/**< ����˰��������� */
	pUserInfo->m_Slgs = pDataUserInfo->m_Slgs;			/**< ��Ʊ��Ȩ˰�ʸ��� */
	pUserInfo->m_Kpjsl = pDataUserInfo->m_Kpjsl;		/**< ��Ʊ������ */
	pUserInfo->m_qysj = pDataUserInfo->m_qysj;			/**< ����ʱ�� YYYYMMDDHHMMSS */
	pUserInfo->m_jqbh = pDataUserInfo->m_jqbh;			/**< ������� */
	pUserInfo->m_backup = pDataUserInfo->m_backup;		/**< ���� */
	
	pUserInfo->m_bbh = pDataUserInfo->m_bbh;			/**< �汾�� */
	pUserInfo->m_blxx = pDataUserInfo->m_blxx;			/**< ������Ϣ */
	pUserInfo->m_fplxdm = pDataUserInfo->m_fplxdm;  	/**< ��Ʊ���ʹ��� */
	pUserInfo->m_qtkzxx = pDataUserInfo->m_qtkzxx;   	/**< ������չ��Ϣ */
	pUserInfo->m_sksbkl = pDataUserInfo->m_sksbkl;   	/**< ˰���豸���� */
	pUserInfo->m_Fplxgs = pDataUserInfo->m_Fplxgs;		/**< ��Ʊ���͸��� */
	pUserInfo->m_Fplxsz = pDataUserInfo->m_Fplxsz;		/**< ��Ʊ���� */
	pUserInfo->m_bspbh = pDataUserInfo->m_bspbh;		/**< ��˰�̱�� */
	
	return;
}


void CDataTransformFunc::InvKind2Data(CInvKind *pInvKind, CDataInvKind *pDataInvKind)
{
	pDataInvKind->m_fplx = pInvKind->m_fplx;			/**< ��Ʊ���� */
	pDataInvKind->m_Lxssr = pInvKind->m_Lxssr;			/**< ���������գ�ÿ�µĵڼ��죩 */
	pDataInvKind->m_Lxkjsj = pInvKind->m_Lxkjsj;		/**< ���߿���ʱ�䣨��λСʱ�� */
	pDataInvKind->m_maxSign = pInvKind->m_maxSign;		/**< ���ŷ�Ʊ�޶� */
	pDataInvKind->m_maxSum = pInvKind->m_maxSum;		/**< ����������Ʊ�ۼ��޶� */
	pDataInvKind->m_backup = pInvKind->m_backup;		/**< �����ֶ� */
	pDataInvKind->m_fplxdm = pInvKind->m_fplxdm;		/**< ��Ʊ���ʹ��� */
	pDataInvKind->m_bsqsrq = pInvKind->m_bsqsrq;		/**< ���ݱ�����ʼ����YYYYMMDDHHMMSS */
	pDataInvKind->m_bszzrq = pInvKind->m_bszzrq;		/**< ���ݱ�����ֹ���� YYYYMMDDHHMMSS*/
	pDataInvKind->m_kpjzrq = pInvKind->m_kpjzrq;		/**< ��Ʊ��ֹ���� */
	
	return;
}
void CDataTransformFunc::Data2InvKind(CDataInvKind *pDataInvKind, CInvKind *pInvKind)
{
	pInvKind->m_fplx = pDataInvKind->m_fplx;			/**< ��Ʊ���� */
	pInvKind->m_Lxssr = pDataInvKind->m_Lxssr;			/**< ���������գ�ÿ�µĵڼ��죩 */
	pInvKind->m_Lxkjsj = pDataInvKind->m_Lxkjsj;		/**< ���߿���ʱ�䣨��λСʱ�� */
	pInvKind->m_maxSign = pDataInvKind->m_maxSign;		/**< ���ŷ�Ʊ�޶� */
	pInvKind->m_maxSum = pDataInvKind->m_maxSum;		/**< ����������Ʊ�ۼ��޶� */
	pInvKind->m_backup = pDataInvKind->m_backup;		/**< �����ֶ� */
	pInvKind->m_fplxdm = pDataInvKind->m_fplxdm;		/**< ��Ʊ���ʹ��� */
	pInvKind->m_bsqsrq = pDataInvKind->m_bsqsrq;		/**< ���ݱ�����ʼ����YYYYMMDDHHMMSS */
	pInvKind->m_bszzrq = pDataInvKind->m_bszzrq;		/**< ���ݱ�����ֹ���� YYYYMMDDHHMMSS*/
	pInvKind->m_kpjzrq = pDataInvKind->m_kpjzrq;		/**< ��Ʊ��ֹ���� */
	
	return;
}

void CDataTransformFunc::Tax2Data(CTax *pTax, CDataTax *pDataTax)
{
	pDataTax->m_sl = pTax->m_sl;			/**< ˰�� */
	pDataTax->m_backup = pTax->m_backup;	/**< ���� */
	
	return;
}
void CDataTransformFunc::Data2Tax(CDataTax *pDataTax, CTax *pTax)
{
	pTax->m_sl = pDataTax->m_sl;			/**< ˰�� */
	pTax->m_backup = pDataTax->m_backup;	/**< ���� */
	
	return;
}

void CDataTransformFunc::InvVol2Data(CInvVol *pInvVol, CDataInvVol *pDataInvVol)
{
	pDataInvVol->m_invtype = pInvVol->m_invtype;		/**< ��Ʊ��� */
	pDataInvVol->m_code = pInvVol->m_code;				/**< ��Ʊ���� */
	pDataInvVol->m_isno = pInvVol->m_isno;				/**< ��Ʊ��ʼ���� */
	pDataInvVol->m_ieno = pInvVol->m_ieno;				/**< ��Ʊ��ֹ���� */
	pDataInvVol->m_remain = pInvVol->m_remain;			/**< ʣ����� */
	pDataInvVol->m_fpzfs = pInvVol->m_fpzfs;			/**< ��Ʊ�ܷ��� */
	pDataInvVol->m_usedflag = pInvVol->m_usedflag;		/**< ʹ�ñ�־ */
	pDataInvVol->m_overflag = pInvVol->m_overflag;		/**< �����־ */
	pDataInvVol->m_kindcode = pInvVol->m_kindcode;		/**< ��Ʊ������� */
	pDataInvVol->m_date = pInvVol->m_date;				/**< �������� */	
	pDataInvVol->m_backup1 = pInvVol->m_backup1;		/**< �����ֶ�1 */
	pDataInvVol->m_backup2 = pInvVol->m_backup2;		/**< �����ֶ�2 */
	pDataInvVol->m_fplxdm = pInvVol->m_fplxdm;			/**< ��Ʊ���ʹ��� */
	
	pDataInvVol->m_curInvNo = pInvVol->m_curInvNo;		/**< ��ǰ��Ʊ�ţ������ */
	pDataInvVol->m_buyDate = pInvVol->m_buyDate;		/**< ��������(���ϻ�ȡ��ʱ��)*/
	pDataInvVol->m_FlagJSorXZ = pInvVol->m_FlagJSorXZ;	/**< ҵ���:��Ʊ�����or���ر�ʶ��1��ʾ������0��ʾ����*/
	pDataInvVol->m_fpzl = pInvVol->m_fpzl;				/**< ��Ʊ����*/
	pDataInvVol->m_lbdm = pInvVol->m_lbdm;				/**< ������*/
	pDataInvVol->m_flag = pInvVol->m_flag;				/**< д��������Ʊ��������Ϣ*/
	pDataInvVol->m_gpsq = pInvVol->m_gpsq;				/**< ��Ʊ��Ȩ*/
	pDataInvVol->m_yssh = pInvVol->m_yssh;				/**<ѹ��˰��*/
	pDataInvVol->m_dqbh = pInvVol->m_dqbh;				/**<�������*/
	pDataInvVol->m_dcbb = pInvVol->m_dcbb;				/**<�ײ�汾*/
	pDataInvVol->m_fpjjsmw = pInvVol->m_fpjjsmw;		/**<��Ʊ���������*/
	pDataInvVol->m_fpjmw = pInvVol->m_fpjmw;			/**<��Ʊ������Ϣ*/
	
	return;
}
void CDataTransformFunc::Data2InvVol(CDataInvVol *pDataInvVol, CInvVol *pInvVol)
{
	pInvVol->m_invtype = pDataInvVol->m_invtype;		/**< ��Ʊ��� */
	pInvVol->m_code = pDataInvVol->m_code;				/**< ��Ʊ���� */
	pInvVol->m_isno = pDataInvVol->m_isno;				/**< ��Ʊ��ʼ���� */
	pInvVol->m_ieno = pDataInvVol->m_ieno;				/**< ��Ʊ��ֹ���� */
	pInvVol->m_remain = pDataInvVol->m_remain;			/**< ʣ����� */
	pInvVol->m_fpzfs = pDataInvVol->m_fpzfs;			/**< ��Ʊ�ܷ��� */
	pInvVol->m_usedflag = pDataInvVol->m_usedflag;		/**< ʹ�ñ�־ */
	pInvVol->m_overflag = pDataInvVol->m_overflag;		/**< �����־ */
	pInvVol->m_kindcode = pDataInvVol->m_kindcode;		/**< ��Ʊ������� */
	pInvVol->m_date = pDataInvVol->m_date;				/**< �������� */	
	pInvVol->m_backup1 = pDataInvVol->m_backup1;		/**< �����ֶ�1 */
	pInvVol->m_backup2 = pDataInvVol->m_backup2;		/**< �����ֶ�2 */
	pInvVol->m_fplxdm = pDataInvVol->m_fplxdm;			/**< ��Ʊ���ʹ��� */
	
	pInvVol->m_curInvNo = pDataInvVol->m_curInvNo;		/**< ��ǰ��Ʊ�ţ������ */
	pInvVol->m_buyDate = pDataInvVol->m_buyDate;		/**< ��������(���ϻ�ȡ��ʱ��)*/
	pInvVol->m_FlagJSorXZ = pDataInvVol->m_FlagJSorXZ;	/**< ҵ���:��Ʊ�����or���ر�ʶ��1��ʾ������0��ʾ����*/
	pInvVol->m_fpzl = pDataInvVol->m_fpzl;				/**< ��Ʊ����*/
	pInvVol->m_lbdm = pDataInvVol->m_lbdm;				/**< ������*/
	pInvVol->m_flag = pDataInvVol->m_flag;				/**< д��������Ʊ��������Ϣ*/
	pInvVol->m_gpsq = pDataInvVol->m_gpsq;				/**< ��Ʊ��Ȩ*/
	pInvVol->m_yssh = pDataInvVol->m_yssh;				/**<ѹ��˰��*/
	pInvVol->m_dqbh = pDataInvVol->m_dqbh;				/**<�������*/
	pInvVol->m_dcbb = pDataInvVol->m_dcbb;				/**<�ײ�汾*/
	pInvVol->m_fpjjsmw = pDataInvVol->m_fpjjsmw;		/**<��Ʊ���������*/
	pInvVol->m_fpjmw = pDataInvVol->m_fpjmw;			/**<��Ʊ������Ϣ*/
	
	return;
}

void CDataTransformFunc::InvHead2Data(CInvHead *pInvHead, CDataInvHead *pDataInvHead)
{
	pDataInvHead->m_fpdm = pInvHead->m_fpdm;			/**< ��Ʊ���� */
	pDataInvHead->m_fphm = pInvHead->m_fphm;			/**< ��Ʊ���� */
	pDataInvHead->m_kprq = pInvHead->m_kprq;			/**< ��Ʊ���� */
	pDataInvHead->m_kpsj = pInvHead->m_kpsj;			/**< ��Ʊʱ�� */
	pDataInvHead->m_kplx = pInvHead->m_kplx;			/**< ��Ʊ���� */
	pDataInvHead->m_kphjje = pInvHead->m_kphjje;		/**< ��Ʊ�ϼƽ���˰�� */
	pDataInvHead->m_yfpdm = pInvHead->m_yfpdm;			/**< ԭ��Ʊ���� */
	pDataInvHead->m_yfphm = pInvHead->m_yfphm;			/**< ԭ��Ʊ���� */
	pDataInvHead->m_fkdw = pInvHead->m_fkdw;			/**< ���λ */
	pDataInvHead->m_payerCode = pInvHead->m_payerCode;	/**< ���λ˰�� */
	pDataInvHead->m_sky = pInvHead->m_sky;				/**< �տ�Ա */
	pDataInvHead->m_sphsl = pInvHead->m_sphsl;			/**< ��Ʒ������ */
	pDataInvHead-> m_fwm = pInvHead->m_fwm;				/**< ��α˰���� */
	pDataInvHead->m_fplb = pInvHead->m_fplb;		    /**< ��Ʊ��� */
	pDataInvHead->m_scbz = pInvHead->m_scbz;			/**< �ϴ���־ */
	pDataInvHead->m_fpsyh = pInvHead->m_fpsyh;			/**< ��Ʊ������*/
	pDataInvHead->m_zfsj = pInvHead->m_zfsj;			/**< ����ʱ�� */
	pDataInvHead->m_casign = pInvHead->m_casign;		/**< CAǩ��*/
	pDataInvHead->m_backup1 = pInvHead->m_backup1;		/**< ����1 */
	pDataInvHead->m_backup2 = pInvHead->m_backup2;		/**< ����2 */
	pDataInvHead->m_kpse = pInvHead->m_kpse;			/**< ˰��*/
	pDataInvHead->m_kpje = pInvHead->m_kpje;			/**< ���(����˰��)*/
	pDataInvHead->m_fplxdm = pInvHead->m_fplxdm;		/**< ��Ʊ���ʹ��� */
	pDataInvHead->m_zfbz = pInvHead->m_zfbz;			/**<  ���ϱ�־*/
	pDataInvHead->m_hyfl = pInvHead->m_hyfl;			/**< ��ҵ���� */
	pDataInvHead->m_fpzl = pInvHead->m_fpzl;			/**< ��Ʊ���� Ĭ��Ϊ"c" */
	pDataInvHead->m_gfdzdh = pInvHead->m_gfdzdh;		/**< ������ַ�绰 */
	pDataInvHead->m_gfyhzh = pInvHead->m_gfyhzh;		/**< ���������˺� */
	pDataInvHead->m_zyspmc = pInvHead->m_zyspmc;		/**< ��Ҫ��Ʒ���� */
    pDataInvHead->m_bsq = pInvHead->m_bsq;				/**< ��˰�� */
	pDataInvHead->m_xfdzdh = pInvHead->m_xfdzdh;		/**< ������ַ�绰 */
	pDataInvHead->m_xfyhzh = pInvHead->m_xfyhzh;		/**< ���������˺� */
	pDataInvHead->m_fhr = pInvHead->m_fhr; 				/**< ������ */
    pDataInvHead->m_qdbz = pInvHead->m_qdbz;			/**< �嵥��־ */
	pDataInvHead->m_CurTime = pInvHead->m_CurTime;		/**< ��ǰʱ��*/
	pDataInvHead->m_jqbh = pInvHead->m_jqbh;

	pDataInvHead->m_xfmc = g_globalArgLib->m_corpInfo->m_Nsrmc;		/**< �������� */
	pDataInvHead->m_xfsh = g_globalArgLib->m_corpInfo->m_Nsrsbh;	/**< ����˰�� */
	pDataInvHead->m_zskl = g_globalArgLib->m_strZskl;				/**< ֤����� */
	pDataInvHead->m_sksbbh = g_globalArgLib->m_corpInfo->m_Jspsbh;

	CDataInvDet dataInvDet;
	CInvDet *pInvDet = NULL;
	pInvDet = pInvHead->pHead;
	while (pInvDet != NULL)
	{
// 		dataInvDet.m_fpdm = pInvDet->m_fpdm;
// 		dataInvDet.m_fphm = pInvDet->m_fphm;
// 		dataInvDet.m_kprq = pInvDet->m_kprq;
// 		dataInvDet.m_kpsj = pInvDet->m_kpsj;
// 		dataInvDet.m_kplx = pInvDet->m_kplx;
// 		dataInvDet.m_opid = pInvDet->m_opid;
// 		dataInvDet.m_sky = pInvDet->m_sky;
		dataInvDet.m_fpdm = pInvHead->m_fpdm;
		dataInvDet.m_fphm = pInvHead->m_fphm;
		dataInvDet.m_kprq = pInvHead->m_kprq;
		dataInvDet.m_kpsj = pInvHead->m_kpsj;
		dataInvDet.m_kplx = pInvHead->m_kplx;
		dataInvDet.m_sky = pInvHead->m_sky;

		dataInvDet.m_sphxh = pInvDet->m_sphxh;
		dataInvDet.m_spbm = pInvDet->m_spbm;
		dataInvDet.m_spmc = pInvDet->m_spmc;
		dataInvDet.m_spdj = pInvDet->m_spdj;
		dataInvDet.m_spsl = pInvDet->m_spsl;
		dataInvDet.m_spje = pInvDet->m_spje;
		dataInvDet.m_sl = pInvDet->m_sl;
		dataInvDet.m_property =pInvDet->m_property;
		dataInvDet.m_spdw = pInvDet->m_spdw;
		dataInvDet.m_ggxh = pInvDet->m_ggxh;
		dataInvDet.m_spse = pInvDet->m_spse;
		dataInvDet.m_dj = pInvDet->m_dj;
		dataInvDet.m_je = pInvDet->m_je;
		dataInvDet.m_dotNum = pInvDet->m_dotNum;
		dataInvDet.m_backup = pInvDet->m_backup;
		dataInvDet.m_hsbz = pInvDet->m_hsbz;

		pDataInvHead->m_gvector.push_back(dataInvDet);

		pInvDet = pInvDet->pNext;
	}

	return;
}
void CDataTransformFunc::Data2InvHead(CDataInvHead *pDataInvHead, CInvHead *pInvHead)
{
	DBG_PRINT(("Data2InvHead Begin"));
	pInvHead->m_fpdm = pDataInvHead->m_fpdm;			/**< ��Ʊ���� */
	pInvHead->m_fphm = pDataInvHead->m_fphm;			/**< ��Ʊ���� */
	pInvHead->m_kprq = pDataInvHead->m_kprq;			/**< ��Ʊ���� */
	pInvHead->m_kpsj = pDataInvHead->m_kpsj;			/**< ��Ʊʱ�� */
	pInvHead->m_kplx = pDataInvHead->m_kplx;			/**< ��Ʊ���� */
	pInvHead->m_kphjje = pDataInvHead->m_kphjje;		/**< ��Ʊ�ϼƽ���˰�� */
	pInvHead->m_yfpdm = pDataInvHead->m_yfpdm;			/**< ԭ��Ʊ���� */
	pInvHead->m_yfphm = pDataInvHead->m_yfphm;			/**< ԭ��Ʊ���� */
	pInvHead->m_fkdw = pDataInvHead->m_fkdw;			/**< ���λ */
	pInvHead->m_payerCode = pDataInvHead->m_payerCode;	/**< ���λ˰�� */
	pInvHead->m_sky = pDataInvHead->m_sky;				/**< �տ�Ա */
	pInvHead->m_sphsl = pDataInvHead->m_sphsl;			/**< ��Ʒ������ */
	pInvHead-> m_fwm = pDataInvHead->m_fwm;				/**< ��α˰���� */
	pInvHead->m_fplb = pDataInvHead->m_fplb;		    /**< ��Ʊ��� */
	pInvHead->m_scbz = pDataInvHead->m_scbz;			/**< �ϴ���־ */
	pInvHead->m_fpsyh = pDataInvHead->m_fpsyh;			/**< ��Ʊ������*/
	pInvHead->m_zfsj = pDataInvHead->m_zfsj;			/**< ����ʱ�� */
	pInvHead->m_casign = pDataInvHead->m_casign;		/**< CAǩ��*/
	pInvHead->m_backup1 = pDataInvHead->m_backup1;		/**< ����1 */
	pInvHead->m_backup2 = pDataInvHead->m_backup2;		/**< ����2 */
	pInvHead->m_kpse = pDataInvHead->m_kpse;			/**< ˰��*/
	pInvHead->m_kpje = pDataInvHead->m_kpje;			/**< ���(����˰��)*/
	pInvHead->m_fplxdm = pDataInvHead->m_fplxdm;		/**< ��Ʊ���ʹ��� */
	pInvHead->m_zfbz = pDataInvHead->m_zfbz;			/**<  ���ϱ�־*/
	pInvHead->m_hyfl = pDataInvHead->m_hyfl;			/**< ��ҵ���� */
	pInvHead->m_fpzl = pDataInvHead->m_fpzl;			/**< ��Ʊ���� Ĭ��Ϊ"c" */
	pInvHead->m_gfdzdh = pDataInvHead->m_gfdzdh;		/**< ������ַ�绰 */
	pInvHead->m_gfyhzh = pDataInvHead->m_gfyhzh;		/**< ���������˺� */
	pInvHead->m_jqbh = pDataInvHead->m_jqbh;			/**< ������� */
	pInvHead->m_zyspmc = pDataInvHead->m_zyspmc;		/**< ��Ҫ��Ʒ���� */
    pInvHead->m_bsq = pDataInvHead->m_bsq;				/**< ��˰�� */
	pInvHead->m_sksbbh = pDataInvHead->m_sksbbh;		/**< ��˰�̱�� */
	pInvHead->m_xfmc = pDataInvHead->m_xfmc;			/**< �������� */
	pInvHead->m_xfsh = pDataInvHead->m_xfsh;			/**< ����˰�� */
	pInvHead->m_xfdzdh = pDataInvHead->m_xfdzdh;		/**< ������ַ�绰 */
	pInvHead->m_xfyhzh = pDataInvHead->m_xfyhzh;		/**< ���������˺� */
	pInvHead->m_fhr = pDataInvHead->m_fhr; 				/**< ������ */
    pInvHead->m_qdbz = pDataInvHead->m_qdbz;			/**< �嵥��־ */
	pInvHead->m_zskl = pDataInvHead->m_zskl;			/**< ֤����� */
	pInvHead->m_CurTime = pDataInvHead->m_CurTime;		/**< ��ǰʱ��*/

	CInvDet *pInvDet = NULL;
	pInvHead->DelList();
	vector<CDataInvDet>::iterator iter;
	for (iter=pDataInvHead->m_gvector.begin(); iter!=pDataInvHead->m_gvector.end(); ++iter)
	{
		pInvDet = pInvDet->GetNewInvDet();

		pInvDet->m_fpdm = iter->m_fpdm;			/**< ��Ʊ���� */
		pInvDet->m_fphm = iter->m_fphm;			/**< ��Ʊ���� */
		pInvDet->m_kprq = iter->m_kprq;			/**< ��Ʊ���� */
		pInvDet->m_kpsj = iter->m_kpsj;			/**< ��Ʊʱ�� */
		pInvDet->m_kplx = iter->m_kplx;			/**< ��Ʊ���� */
		pInvDet->m_opid = iter->m_opid;			/**< ����Աid */
		pInvDet->m_sky = iter->m_sky;			/**< �տ�Ա */

		pInvDet->m_sphxh = iter->m_sphxh;		/**< ��Ʒ����ţ���1��ʼ */
		pInvDet->m_spbm = iter->m_spbm;			/**< ��Ʒ���� */
		pInvDet->m_spmc = iter->m_spmc;			/**< ��Ʒ���� */
		pInvDet->m_spdj = iter->m_spdj;			/**< ��Ʒ����(��˰) */
		pInvDet->m_spsl = iter->m_spsl;			/**< ��Ʒ���� */
		pInvDet->m_spje = iter->m_spje;			/**< ��Ʒ���(��˰) */
		pInvDet->m_sl = iter->m_sl;				/**< ˰�� */
		pInvDet->m_property = iter->m_property;	/**< ��Ʒ������ */
		pInvDet->m_spdw = iter->m_spdw;			/**< ��λ */
		pInvDet->m_ggxh = iter->m_ggxh;			/**< ����ͺ� */
		pInvDet->m_spse = iter->m_spse;			/**< ��Ʒ˰�� */
		pInvDet->m_dj = iter->m_dj;				/**< ��Ʒ����(����˰) */
		pInvDet->m_je = iter->m_je;				/**< ��Ʒ���(����˰) */
		pInvDet->m_dotNum = iter->m_dotNum;     /**< ��������������С��λ�� */
		pInvDet->m_backup = iter->m_backup;		/**< ���� */
		pInvDet->m_hsbz = iter->m_hsbz;			/**< ��˰�۱�־(1:���ۺ�˰ 0:���۲���˰) */

		DBG_PRINT(("m_sphxh = %u", pInvDet->m_sphxh));
		DBG_PRINT(("m_spmc = %s", pInvDet->m_spmc.c_str()));
		DBG_PRINT(("m_spdj = %.3f", pInvDet->m_spdj));
		DBG_PRINT(("m_spsl = %.3f", pInvDet->m_spsl));
		DBG_PRINT(("m_spje = %lld", pInvDet->m_spje));
		DBG_PRINT(("m_sl = %.3f", pInvDet->m_sl));
		DBG_PRINT(("m_spse = %lld", pInvDet->m_spse));
		DBG_PRINT(("m_dj = %.3f", pInvDet->m_dj));
		DBG_PRINT(("m_je = %lld", pInvDet->m_je));

		pInvHead->InsertNode(pInvDet);
		pInvDet = NULL;
	}

	return;
}

void CDataTransformFunc::NetPara2Data(CNetPara *pNetPara, CDataNetPara *pDataNetPara)
{
	pDataNetPara->m_IsDhcp = pNetPara->m_IsDhcp;			/**< �Ƿ��Զ�����IP */
	pDataNetPara->m_LocalIP = pNetPara->m_LocalIP;			/**< ����IP */
	pDataNetPara->m_LocalGate = pNetPara->m_LocalGate;		/**< �������� */
	pDataNetPara->m_LocalMask = pNetPara->m_LocalMask;		/**< �������� */
	pDataNetPara->m_LocalDNS = pNetPara->m_LocalDNS;		/**< DNS */
	pDataNetPara->m_ServIP = pNetPara->m_ServIP;			/**< ������IP��ַ */
	pDataNetPara->m_ServPort = pNetPara->m_ServPort;		/**< �������˿ں� */
	pDataNetPara->m_ServAddr = pNetPara->m_ServAddr;		/**< ����������·�� */
	pDataNetPara->m_FtpIP = pNetPara->m_FtpIP;				/**< ftp��������ַ */
	pDataNetPara->m_FtpPort = pNetPara->m_FtpPort;			/**< ftp�˿ں� */
	pDataNetPara->m_FtpUser = pNetPara->m_FtpUser;			/**< �û��� */
	pDataNetPara->m_FtpPwd = pNetPara->m_FtpPwd;			/**< ���� */
	
	return;
}
void CDataTransformFunc::Data2NetPara(CDataNetPara *pDataNetPara, CNetPara *pNetPara)
{
	pNetPara->m_IsDhcp = pDataNetPara->m_IsDhcp;			/**< �Ƿ��Զ�����IP */
	pNetPara->m_LocalIP = pDataNetPara->m_LocalIP;			/**< ����IP */
	pNetPara->m_LocalGate = pDataNetPara->m_LocalGate;		/**< �������� */
	pNetPara->m_LocalMask = pDataNetPara->m_LocalMask;		/**< �������� */
	pNetPara->m_LocalDNS = pDataNetPara->m_LocalDNS;		/**< DNS */
	pNetPara->m_ServIP = pDataNetPara->m_ServIP;			/**< ������IP��ַ */
	pNetPara->m_ServPort = pDataNetPara->m_ServPort;		/**< �������˿ں� */
	pNetPara->m_ServAddr = pDataNetPara->m_ServAddr;		/**< ����������·�� */
	pNetPara->m_FtpIP = pDataNetPara->m_FtpIP;				/**< ftp��������ַ */
	pNetPara->m_FtpPort = pDataNetPara->m_FtpPort;			/**< ftp�˿ں� */
	pNetPara->m_FtpUser = pDataNetPara->m_FtpUser;			/**< �û��� */
	pNetPara->m_FtpPwd = pDataNetPara->m_FtpPwd;			/**< ���� */
	
	return;
}

