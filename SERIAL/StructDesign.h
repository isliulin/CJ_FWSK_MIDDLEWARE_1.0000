#ifndef STRUCT_DESIGN
#define STRUCT_DESIGN

#include "DataTypeDesign.h"
#include "DataDesign.h"

//˰���豸����˰�̣���ѯ������Ϣ
typedef struct Struct_JSPDeviceInfo_Request{
	UINT8 skpkl[KOULING_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
} JSPDeviceInfo_Request;

//˰���豸����˰�̣���ѯ��Ӧ��Ϣ
typedef struct Struct_JSPDeviceInfo_Reponse{
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 nsrmc[NSRMC_LEN+1];
	UINT8 swjgdm[SWJGDM_LEN+1];
	UINT8 swjgmc[SWJGMC_LEN+1];
	UINT8 fplxdm[FPLXDM_A_LEN+1];
	UINT8 dqsz[SZSJ_LEN+1];
	UINT8 qysj[SZSJ_LEN+1];
	UINT8 bbh[BBH_LEN+1];
	UINT8 kpjh[KPJH_LEN+1];
	UINT8 qylx[QYLX_LEN+1];
	UINT8 blxx[BLXX_LEN+1];
	UINT8 qtkzxx[KZXX_LEN+1];
} JSPDevice_Response;

//��˰����Ϣ��ѯ������Ϣ
typedef struct Struct_BSPDeviceInfo_Request{
	UINT8 bspkl[KOULING_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
} BSPDeviceInfo_Request;

//��˰�̲�ѯ��Ӧ��Ϣ
typedef struct Struct_BSPDeviceInfo_Reponse{
	UINT8 bspbh[SBBH_LEN+1];
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 nsrmc[NSRMC_LEN+1];
	UINT8 swjgdm[SWJGDM_LEN+1];
	UINT8 swjgmc[SWJGMC_LEN+1];
	UINT8 dqsz[SZSJ_LEN+1];
	UINT8 qysj[SZSJ_LEN+1];
	UINT8 ffbz[2+1];
	UINT8 bbh[BBH_LEN+1];
	UINT8 kpjh[KPJH_LEN+1];
	UINT8 qylx[QYLX_LEN+1];
	UINT8 blxx[BLXX_LEN+1];
} BSPDevice_Reponse;

//�����������
typedef struct Struct_Common_Request{
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
	UINT8 kpjh[KPJH_LEN+1];
} Common_Request;

//���������Ӧ��Ϣ
typedef struct Struct_JKDataInfo_Response{
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 kpjzsj[DATE_LEN+1];
	UINT8 bsqsrq[DATE_LEN+1];
	UINT8 bszzrq[DATE_LEN+1];
	UINT8 dzkpxe[XIANE_LEN+1];
	UINT8 zxbsrq[DATE_LEN+1];
	UINT8 syrl[SYRL_LEN+1];
	UINT8 scjzrq[SCJZRQ_LEN+1];
	UINT8 lxkpsc[LXKPSC_LEN+1];
	UINT8 lxzsljje[XIANE_LEN+1];
	UINT8 lxkzxx[LXKZXX_LEN+1];
	UINT8 zdyxx[ZDYXX_LEN+1];
} JKData_Response;

//��Ȩ˰����Ϣ
typedef struct Struct_TaxItemInfo_Response{
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 sl[TAXRATE_NUM_LEN+1];
	UINT8 taxrate[TAXRATE_LEN*TAXRATE_MAX_NUM+1];
} TaxItem_Response;

//��Ʊ��Ϣ
typedef struct Struct_GPInfo_Response {
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 dqfpdm[FPDM_LEN+1];
	UINT8 dqfphm[FPHM_LEN+1];
	UINT8 zsyfs[FPFS_LEN+1];
} GPXXInfo_Response;

//�޸Ŀ�����������
typedef struct Struct_ChangePWD_Request{
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 sbbh[SBBH_LEN+1];
	UINT8 ykl[KOULING_LEN+1];
	UINT8 xkl[KOULING_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
} ChangePWD_Request;

//��Ʊ������������
typedef struct Struct_XMItem {
	UINT8 xm[XMMC_LEN+1];
	UINT8 dj[DJ_LEN+1];
	UINT8 sl[SL_LEN+1];
	UINT8 je[JE_LEN+1];
	UINT8 zsl[TAXRATE_LEN+1];
	UINT8 se[TAX_LEN+1];
	UINT8 hsdj[JE_LEN+1];
	UINT8 hsje[JE_LEN+1];
} XMItem;
typedef struct Struct_FPKJ_Request{
	UINT8 zskl[ZSKOULING_LEN+1];
	UINT8 xhdwdm[NSRSBH_LEN+1];
	UINT8 xhdwmc[NSRMC_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 kplx;
	UINT8 ghdwdm[NSRSBH_LEN+1];
	UINT8 ghdwmc[NSRMC_LEN+1];
	UINT32 xmgs;
	XMItem items[ITEM_MAX_COUNT];
	UINT8 hjje[JE_LEN+1];
	UINT8 hjse[JE_LEN+1];
	UINT8 jshj[JE_LEN+1];
	UINT8 bz[BZ_LEN+1];
	UINT8 skr[RYMC_LEN+1];
	UINT8 yfpdm[FPDM_LEN+1];
	UINT8 yfphm[FPHM_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
} FPKJ_Request;

//��Ʊ������Ӧ����
typedef struct Struct_FPKJ_Response{
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 fpdm[FPDM_LEN+1];
	UINT8 fphm[FPHM_LEN+1];
	UINT8 kprq[SZSJ_LEN+1];
	UINT8 skm[SKM_SHORT_LEN+1];
	UINT8 qmz[SIGN_LEN+1];
} FPKJ_Response;

//��Ʊ������������
typedef struct Struct_FPZF_Request{
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 zskl[ZSKOULING_LEN+1];
	UINT8 zflx;
	UINT8 fpdm[FPDM_LEN+1];
	UINT8 fphm[FPHM_LEN+1];
	UINT8 zfr[RYMC_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
} FPZF_Request;

//��Ʊ������Ӧ����
typedef struct Struct_FPZF_Response{
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 fpdm[FPDM_LEN+1];
	UINT8 fphm[FPHM_LEN+1];
	UINT8 zfrq[SZSJ_LEN+1];
} FPZF_Response;

//��Ʊ��ѯ��������
typedef struct Struct_FPCX_Request{
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 cxfs;
	UINT8 cxtj[CXTJ_LEN+1];
} FPCX_Request;

//��Ʊ��ѯ��Ӧ����
typedef struct Struct_FPCX_Reponse{
	UINT8 fpdm[FPDM_LEN+1];
	UINT8 fphm[FPHM_LEN+1];
	UINT16 fpzt;
	UINT16 scbz;
	UINT8 kprq[DATE_LEN+1];
	UINT8 kpsj[TIME_LEN+1];
	UINT8 skm[SKM_SHORT_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skdwmc[SKDWMC_LEN+1];
	UINT8 xhdwdm[NSRSBH_LEN+1];
	UINT8 xhdwmc[NSRMC_LEN+1];
	UINT8 ghdwdm[NSRSBH_LEN+1];
	UINT8 ghdwmc[NSRMC_LEN+1];
	INT32 xmgs;
	XMItem items[ITEM_MAX_COUNT];
	UINT8 hjje[JE_LEN+1];
	UINT8 hjse[JE_LEN+1];
	UINT8 jshj[JE_LEN+1];
	UINT8 bz[BZ_LEN+1];
	UINT8 skr[RYMC_LEN+1];
	UINT8 yfpdm[FPDM_LEN+1];
	UINT8 yfphm[FPHM_LEN+1];
	UINT8 zfrq[DATE_LEN+1];
	UINT8 zfr[RYMC_LEN+1];
	UINT8 ykfsje[JE_LEN+1];
} FPCX_Reponse;

//��˰�̱�˰����ϲ�����������
typedef struct Struc_JSPBSPZHCZ_Request{
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];
	UINT8 bspbh[SBBH_LEN+1];
	UINT8 bspkl[KOULING_LEN+1];
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 czlx;
	UINT8 hzxx[HZXX_LEN+1];
	UINT8 qtxx[ZH_QTXX_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
} JSPBSPZHCZ_Request;

//��˰�̷�Ʊ��ѯ��������
typedef struct Struct_BSPFPCX_Request{
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 bspbh[SBBH_LEN+1];
	UINT8 bspkl[KOULING_LEN+1];
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
} BSPFPCX_Request;

//��˰�̷�Ʊ��ѯ��Ӧ����
typedef struct Struct_FPLG_Item {
	UINT8 fpdm[FPDM_LEN+1];
	UINT8 qshm[FPHM_LEN+1];
	UINT8 zzhm[FPHM_LEN+1];
	UINT8 fpfs[FPFS_LEN+1];
	UINT8 syfs[FPFS_LEN+1];
	UINT8 lgrq[DATE_LEN+1];
	UINT8 lgry[RYMC_LEN+1];
} FPLG_Item;
typedef struct Struct_BSPFPCX_Reponse{
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 sl[ITEM_COUNT_LEN+1];
	FPLG_Item fplgItems[FPLG_MAX_COUNT];
} BSPFPCX_Reponse;

//��˰�̷�Ʊ�ַ���������
typedef struct Struct_FPFF_Request{
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 jzlx;
	UINT8 bspbh[SBBH_LEN+1];
	UINT8 bspkl[KOULING_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];	
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 fpdm[FPDM_LEN+1];
	UINT8 qshm[FPHM_LEN+1];
	UINT8 fpfs[FPFS_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
} FPFF_Request;

//��˰�̷�Ʊ������������
typedef struct Struct_FPHS_Request{
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 jzlx;
	UINT8 bspbh[SBBH_LEN+1];
	UINT8 bspkl[KOULING_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];	
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 fpdm[FPDM_LEN+1];
	UINT8 qshm[FPHM_LEN+1];
	UINT8 fpfs[FPFS_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
} FPHS_Request;

//���ݳ�����������
typedef struct Struct_SJCB_Request {
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];	
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
	UINT8 jzlx;
} SJCB_Request;

//�����ػش���������
typedef struct Struct_WLJKHC_Request {
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];	
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
} WLJKHC_Request;

//��Ʊͳ����Ϣ��ѯ��������
typedef struct Struct_FPTJ_Request {
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];	
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 qsrq[DATE_LEN+1];
	UINT8 zzrq[DATE_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
} FPTJ_Request;

//��Ʊͳ����Ϣ��ѯ��Ӧ����
typedef struct Struct_FPTJ_Reponse {
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 sl[ITEM_COUNT_LEN+1];
	UINT8 qsrq[DATE_LEN+1];
	UINT8 jzrq[DATE_LEN+1];
	UINT8 qckcfs[FPZS_LEN+1];
	UINT8 lgfpfs[FPZS_LEN+1];
	UINT8 thfpfs[FPZS_LEN+1];
	UINT8 zsfpfs[FPZS_LEN+1];
	UINT8 zffpfs[FPZS_LEN+1];
	UINT8 fsfpfs[FPZS_LEN+1];
	UINT8 fffpfs[FPZS_LEN+1];
	UINT8 kffpfs[FPZS_LEN+1];
	UINT8 qmkcfs[FPZS_LEN+1];
	UINT8 zsfpljje[JE_LEN+1];
	UINT8 zsfpljse[JE_LEN+1];
	UINT8 zffpljje[JE_LEN+1];
	UINT8 zffpljse[JE_LEN+1];
	UINT8 fsfpljje[JE_LEN+1];
	UINT8 fsfpljse[JE_LEN+1];
	UINT8 fffpljje[JE_LEN+1];
	UINT8 fffpljse[JE_LEN+1];
} FPTJ_Reponse;

//��ҵ��Ϣ������������
typedef struct Struct_QYXXGX_Request {
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];	
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
} QYXXGX_Request;

//����Ȩ����Ϣ������������
typedef struct Struct_LXQXGX_Request {
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];	
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
	UINT8 kpjh[KPJH_LEN+1];
} LXQXGX_Request;

//��Ʊʵʱ�ϴ���������
typedef struct Struct_FPSSSC_Request {
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];	
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 fpzs[FPZS_LEN+1];
	UINT8 czlx;
	UINT8 jqbh[JQBH_LEN+1];
	UINT8 kpjh[KPJH_LEN+1];
} FPSSSC_Request;

//�������ά����������
typedef struct Struct_NetWorkInfo_Request {
	UINT8 isdhcp;
	UINT8 local_ip[20];
	UINT8 local_defaultgate[20];
	UINT8 local_netmask[20];
	UINT8 local_dnsnameip[20];
	UINT8 server_ipaddr[20];
	UINT8 server_port[6];
	UINT8 application_name[50];
	UINT8 ftp_serverip[20];
	UINT8 ftp_port[6];
	UINT8 ftp_username[16];
	UINT8 ftp_passwd[16];
} NetWorkInfo_Request;

//��Ʊ��������
typedef struct Struct_FPDR_Request{
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 jzlx;
	UINT8 bspbh[SBBH_LEN+1];
	UINT8 bspkl[KOULING_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];	
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
} FPDR_Request;

//�ֻ��˻�����
typedef struct Struct_FJTH_Request{
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 jzlx;
	UINT8 bspbh[SBBH_LEN+1];
	UINT8 bspkl[KOULING_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];	
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
} FJTH_Request;

//���繺Ʊ����
typedef struct Struct_WLGP_Request{
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];	
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 fpdm[FPDM_LEN+1];
	UINT8 fpqshm[FPHM_LEN+1];
	UINT8 fpzzhm[FPHM_LEN+1];
	UINT8 fpzfs[FPFS_LEN+1];
	UINT8 qtxx[QTXX_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
	UINT8 kpjh[KPJH_LEN+1];
} WLGP_Request;

//֤������������
typedef struct Struct_ZSKLGG_Request{
	UINT8 yzskl[KOULING_LEN+1];
	UINT8 xzskl[KOULING_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
} ZSKLGG_Request;

//��Ʊ��¼����
typedef struct Struct_FPBL_Request{
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];	
	UINT8 fplxdm[FPLXDM_S_LEN+1];
	UINT8 bsqsrq[DATE_LEN+1];
	UINT8 bsjzrq[DATE_LEN+1];
	UINT8 jqbh[JQBH_LEN+1];
} FPBL_Request;

//��ȡ���������������
typedef struct Struct_HQLXSJ_Request{
	UINT8 wscfpzs[8+1];
	UINT8 wscfpsj[SZSJ_LEN+1];
	UINT8 wscfpljje[JE_LEN+1];	
	UINT8 sczs[5+1];
	UINT8 scsjjg[10+1];
} HQLXSJ_Request;

//��ȫͨ�����Ӳ���
typedef struct Struct_CONNECTTEST_Request{
	UINT8 nsrsbh[NSRSBH_LEN+1];
	UINT8 skpbh[SBBH_LEN+1];
	UINT8 skpkl[KOULING_LEN+1];	
	UINT8 jqbh[JQBH_LEN+1];
	UINT8 zskl[KOULING_LEN+1];	
} CONNECTTEST_Request;


#endif