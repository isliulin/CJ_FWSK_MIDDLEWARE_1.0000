/*! \file  DataTransformFunc.cpp
\brief    数据转换函数
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
	pDataUserInfo->m_Nsrsbh = pUserInfo->m_Nsrsbh;		/**< 纳税人识别号 */
	pDataUserInfo->m_Nsrmc = pUserInfo->m_Nsrmc;		/**< 纳税人名称 */
	pDataUserInfo->m_Kpjhm = pUserInfo->m_Kpjhm;		/**< 开票机号码 */
	pDataUserInfo->m_zfFlag = pUserInfo->m_zfFlag;      /**<主分机标志 0代表主机 1代表分机*/
	pDataUserInfo->m_Nsrxz = pUserInfo->m_Nsrxz;		/**< 纳税人企业性质 */
	pDataUserInfo->m_Hylx = pUserInfo->m_Hylx;			/**< 行业类型 */
	pDataUserInfo->m_Jspsbh = pUserInfo->m_Jspsbh;		/**< 金税盘设备号 */
	pDataUserInfo->m_Gsdjh = pUserInfo->m_Gsdjh;		/**< 工商登记号 */
	pDataUserInfo->m_Khyh = pUserInfo->m_Khyh;			/**< 开户银行 */
	pDataUserInfo->m_Khzh = pUserInfo->m_Khzh;			/**< 开户账号 */
	pDataUserInfo->m_Djzcdz = pUserInfo->m_Djzcdz;		/**< 登记注册地址 */
	pDataUserInfo->m_Swjgdm = pUserInfo->m_Swjgdm;		/**< 主管税务机关代码 */
	pDataUserInfo->m_Swjgmc = pUserInfo->m_Swjgmc;		/**< 主管税务机关名称 */
	pDataUserInfo->m_Slgs = pUserInfo->m_Slgs;			/**< 普票授权税率个数 */
	pDataUserInfo->m_Kpjsl = pUserInfo->m_Kpjsl;		/**< 开票机数量 */
	pDataUserInfo->m_qysj = pUserInfo->m_qysj;			/**< 启用时间 YYYYMMDDHHMMSS */
	pDataUserInfo->m_jqbh = pUserInfo->m_jqbh;			/**< 机器编号 */
	pDataUserInfo->m_backup = pUserInfo->m_backup;		/**< 备用 */
	
	pDataUserInfo->m_bbh = pUserInfo->m_bbh;			/**< 版本号 */
	pDataUserInfo->m_blxx = pUserInfo->m_blxx;			/**< 保留信息 */
	pDataUserInfo->m_fplxdm = pUserInfo->m_fplxdm;  	/**< 发票类型代码 */
	pDataUserInfo->m_qtkzxx = pUserInfo->m_qtkzxx;   	/**< 其他扩展信息 */
	pDataUserInfo->m_sksbkl = pUserInfo->m_sksbkl;   	/**< 税控设备口令 */
	pDataUserInfo->m_Fplxgs = pUserInfo->m_Fplxgs;		/**< 发票类型个数 */
	pDataUserInfo->m_Fplxsz = pUserInfo->m_Fplxsz;		/**< 发票类型 */
	pDataUserInfo->m_bspbh = pUserInfo->m_bspbh;		/**< 报税盘编号 */

	return;
}

void CDataTransformFunc::Data2UserInfo(CDataUserInfo *pDataUserInfo, CUserInfo *pUserInfo)
{
	pUserInfo->m_Nsrsbh = pDataUserInfo->m_Nsrsbh;		/**< 纳税人识别号 */
	pUserInfo->m_Nsrmc = pDataUserInfo->m_Nsrmc;		/**< 纳税人名称 */
	pUserInfo->m_Kpjhm = pDataUserInfo->m_Kpjhm;		/**< 开票机号码 */
	pUserInfo->m_zfFlag = pDataUserInfo->m_zfFlag;      /**<主分机标志 0代表主机 1代表分机*/
	pUserInfo->m_Nsrxz = pDataUserInfo->m_Nsrxz;		/**< 纳税人企业性质 */
	pUserInfo->m_Hylx = pDataUserInfo->m_Hylx;			/**< 行业类型 */
	pUserInfo->m_Jspsbh = pDataUserInfo->m_Jspsbh;		/**< 金税盘设备号 */
	pUserInfo->m_Gsdjh = pDataUserInfo->m_Gsdjh;		/**< 工商登记号 */
	pUserInfo->m_Khyh = pDataUserInfo->m_Khyh;			/**< 开户银行 */
	pUserInfo->m_Khzh = pDataUserInfo->m_Khzh;			/**< 开户账号 */
	pUserInfo->m_Djzcdz = pDataUserInfo->m_Djzcdz;		/**< 登记注册地址 */
	pUserInfo->m_Swjgdm = pDataUserInfo->m_Swjgdm;		/**< 主管税务机关代码 */
	pUserInfo->m_Swjgmc = pDataUserInfo->m_Swjgmc;		/**< 主管税务机关名称 */
	pUserInfo->m_Slgs = pDataUserInfo->m_Slgs;			/**< 普票授权税率个数 */
	pUserInfo->m_Kpjsl = pDataUserInfo->m_Kpjsl;		/**< 开票机数量 */
	pUserInfo->m_qysj = pDataUserInfo->m_qysj;			/**< 启用时间 YYYYMMDDHHMMSS */
	pUserInfo->m_jqbh = pDataUserInfo->m_jqbh;			/**< 机器编号 */
	pUserInfo->m_backup = pDataUserInfo->m_backup;		/**< 备用 */
	
	pUserInfo->m_bbh = pDataUserInfo->m_bbh;			/**< 版本号 */
	pUserInfo->m_blxx = pDataUserInfo->m_blxx;			/**< 保留信息 */
	pUserInfo->m_fplxdm = pDataUserInfo->m_fplxdm;  	/**< 发票类型代码 */
	pUserInfo->m_qtkzxx = pDataUserInfo->m_qtkzxx;   	/**< 其他扩展信息 */
	pUserInfo->m_sksbkl = pDataUserInfo->m_sksbkl;   	/**< 税控设备口令 */
	pUserInfo->m_Fplxgs = pDataUserInfo->m_Fplxgs;		/**< 发票类型个数 */
	pUserInfo->m_Fplxsz = pDataUserInfo->m_Fplxsz;		/**< 发票类型 */
	pUserInfo->m_bspbh = pDataUserInfo->m_bspbh;		/**< 报税盘编号 */
	
	return;
}


void CDataTransformFunc::InvKind2Data(CInvKind *pInvKind, CDataInvKind *pDataInvKind)
{
	pDataInvKind->m_fplx = pInvKind->m_fplx;			/**< 发票类型 */
	pDataInvKind->m_Lxssr = pInvKind->m_Lxssr;			/**< 离线锁死日（每月的第几天） */
	pDataInvKind->m_Lxkjsj = pInvKind->m_Lxkjsj;		/**< 离线开具时间（单位小时） */
	pDataInvKind->m_maxSign = pInvKind->m_maxSign;		/**< 单张发票限额 */
	pDataInvKind->m_maxSum = pInvKind->m_maxSum;		/**< 离线正数发票累计限额 */
	pDataInvKind->m_backup = pInvKind->m_backup;		/**< 备用字段 */
	pDataInvKind->m_fplxdm = pInvKind->m_fplxdm;		/**< 发票类型代码 */
	pDataInvKind->m_bsqsrq = pInvKind->m_bsqsrq;		/**< 数据报送起始日期YYYYMMDDHHMMSS */
	pDataInvKind->m_bszzrq = pInvKind->m_bszzrq;		/**< 数据报送终止日期 YYYYMMDDHHMMSS*/
	pDataInvKind->m_kpjzrq = pInvKind->m_kpjzrq;		/**< 开票截止日期 */
	
	return;
}
void CDataTransformFunc::Data2InvKind(CDataInvKind *pDataInvKind, CInvKind *pInvKind)
{
	pInvKind->m_fplx = pDataInvKind->m_fplx;			/**< 发票类型 */
	pInvKind->m_Lxssr = pDataInvKind->m_Lxssr;			/**< 离线锁死日（每月的第几天） */
	pInvKind->m_Lxkjsj = pDataInvKind->m_Lxkjsj;		/**< 离线开具时间（单位小时） */
	pInvKind->m_maxSign = pDataInvKind->m_maxSign;		/**< 单张发票限额 */
	pInvKind->m_maxSum = pDataInvKind->m_maxSum;		/**< 离线正数发票累计限额 */
	pInvKind->m_backup = pDataInvKind->m_backup;		/**< 备用字段 */
	pInvKind->m_fplxdm = pDataInvKind->m_fplxdm;		/**< 发票类型代码 */
	pInvKind->m_bsqsrq = pDataInvKind->m_bsqsrq;		/**< 数据报送起始日期YYYYMMDDHHMMSS */
	pInvKind->m_bszzrq = pDataInvKind->m_bszzrq;		/**< 数据报送终止日期 YYYYMMDDHHMMSS*/
	pInvKind->m_kpjzrq = pDataInvKind->m_kpjzrq;		/**< 开票截止日期 */
	
	return;
}

void CDataTransformFunc::Tax2Data(CTax *pTax, CDataTax *pDataTax)
{
	pDataTax->m_sl = pTax->m_sl;			/**< 税率 */
	pDataTax->m_backup = pTax->m_backup;	/**< 备用 */
	
	return;
}
void CDataTransformFunc::Data2Tax(CDataTax *pDataTax, CTax *pTax)
{
	pTax->m_sl = pDataTax->m_sl;			/**< 税率 */
	pTax->m_backup = pDataTax->m_backup;	/**< 备用 */
	
	return;
}

void CDataTransformFunc::InvVol2Data(CInvVol *pInvVol, CDataInvVol *pDataInvVol)
{
	pDataInvVol->m_invtype = pInvVol->m_invtype;		/**< 发票类别 */
	pDataInvVol->m_code = pInvVol->m_code;				/**< 发票代码 */
	pDataInvVol->m_isno = pInvVol->m_isno;				/**< 发票起始号码 */
	pDataInvVol->m_ieno = pInvVol->m_ieno;				/**< 发票终止号码 */
	pDataInvVol->m_remain = pInvVol->m_remain;			/**< 剩余份数 */
	pDataInvVol->m_fpzfs = pInvVol->m_fpzfs;			/**< 发票总份数 */
	pDataInvVol->m_usedflag = pInvVol->m_usedflag;		/**< 使用标志 */
	pDataInvVol->m_overflag = pInvVol->m_overflag;		/**< 用完标志 */
	pDataInvVol->m_kindcode = pInvVol->m_kindcode;		/**< 发票种类代码 */
	pDataInvVol->m_date = pInvVol->m_date;				/**< 购买日期 */	
	pDataInvVol->m_backup1 = pInvVol->m_backup1;		/**< 备用字段1 */
	pDataInvVol->m_backup2 = pInvVol->m_backup2;		/**< 备用字段2 */
	pDataInvVol->m_fplxdm = pInvVol->m_fplxdm;			/**< 发票类型代码 */
	
	pDataInvVol->m_curInvNo = pInvVol->m_curInvNo;		/**< 当前发票号，不存库 */
	pDataInvVol->m_buyDate = pInvVol->m_buyDate;		/**< 购买日期(盘上获取的时间)*/
	pDataInvVol->m_FlagJSorXZ = pInvVol->m_FlagJSorXZ;	/**< 业务九:发票卷解锁or下载标识，1表示解锁，0表示下载*/
	pDataInvVol->m_fpzl = pInvVol->m_fpzl;				/**< 发票种类*/
	pDataInvVol->m_lbdm = pInvVol->m_lbdm;				/**< 类别代码*/
	pDataInvVol->m_flag = pInvVol->m_flag;				/**< 写盘锁死发票卷密文信息*/
	pDataInvVol->m_gpsq = pInvVol->m_gpsq;				/**< 购票授权*/
	pDataInvVol->m_yssh = pInvVol->m_yssh;				/**<压缩税号*/
	pDataInvVol->m_dqbh = pInvVol->m_dqbh;				/**<地区编号*/
	pDataInvVol->m_dcbb = pInvVol->m_dcbb;				/**<底层版本*/
	pDataInvVol->m_fpjjsmw = pInvVol->m_fpjjsmw;		/**<发票卷解锁密文*/
	pDataInvVol->m_fpjmw = pInvVol->m_fpjmw;			/**<发票密文信息*/
	
	return;
}
void CDataTransformFunc::Data2InvVol(CDataInvVol *pDataInvVol, CInvVol *pInvVol)
{
	pInvVol->m_invtype = pDataInvVol->m_invtype;		/**< 发票类别 */
	pInvVol->m_code = pDataInvVol->m_code;				/**< 发票代码 */
	pInvVol->m_isno = pDataInvVol->m_isno;				/**< 发票起始号码 */
	pInvVol->m_ieno = pDataInvVol->m_ieno;				/**< 发票终止号码 */
	pInvVol->m_remain = pDataInvVol->m_remain;			/**< 剩余份数 */
	pInvVol->m_fpzfs = pDataInvVol->m_fpzfs;			/**< 发票总份数 */
	pInvVol->m_usedflag = pDataInvVol->m_usedflag;		/**< 使用标志 */
	pInvVol->m_overflag = pDataInvVol->m_overflag;		/**< 用完标志 */
	pInvVol->m_kindcode = pDataInvVol->m_kindcode;		/**< 发票种类代码 */
	pInvVol->m_date = pDataInvVol->m_date;				/**< 购买日期 */	
	pInvVol->m_backup1 = pDataInvVol->m_backup1;		/**< 备用字段1 */
	pInvVol->m_backup2 = pDataInvVol->m_backup2;		/**< 备用字段2 */
	pInvVol->m_fplxdm = pDataInvVol->m_fplxdm;			/**< 发票类型代码 */
	
	pInvVol->m_curInvNo = pDataInvVol->m_curInvNo;		/**< 当前发票号，不存库 */
	pInvVol->m_buyDate = pDataInvVol->m_buyDate;		/**< 购买日期(盘上获取的时间)*/
	pInvVol->m_FlagJSorXZ = pDataInvVol->m_FlagJSorXZ;	/**< 业务九:发票卷解锁or下载标识，1表示解锁，0表示下载*/
	pInvVol->m_fpzl = pDataInvVol->m_fpzl;				/**< 发票种类*/
	pInvVol->m_lbdm = pDataInvVol->m_lbdm;				/**< 类别代码*/
	pInvVol->m_flag = pDataInvVol->m_flag;				/**< 写盘锁死发票卷密文信息*/
	pInvVol->m_gpsq = pDataInvVol->m_gpsq;				/**< 购票授权*/
	pInvVol->m_yssh = pDataInvVol->m_yssh;				/**<压缩税号*/
	pInvVol->m_dqbh = pDataInvVol->m_dqbh;				/**<地区编号*/
	pInvVol->m_dcbb = pDataInvVol->m_dcbb;				/**<底层版本*/
	pInvVol->m_fpjjsmw = pDataInvVol->m_fpjjsmw;		/**<发票卷解锁密文*/
	pInvVol->m_fpjmw = pDataInvVol->m_fpjmw;			/**<发票密文信息*/
	
	return;
}

void CDataTransformFunc::InvHead2Data(CInvHead *pInvHead, CDataInvHead *pDataInvHead)
{
	pDataInvHead->m_fpdm = pInvHead->m_fpdm;			/**< 发票代码 */
	pDataInvHead->m_fphm = pInvHead->m_fphm;			/**< 发票号码 */
	pDataInvHead->m_kprq = pInvHead->m_kprq;			/**< 开票日期 */
	pDataInvHead->m_kpsj = pInvHead->m_kpsj;			/**< 开票时间 */
	pDataInvHead->m_kplx = pInvHead->m_kplx;			/**< 开票类型 */
	pDataInvHead->m_kphjje = pInvHead->m_kphjje;		/**< 开票合计金额（含税） */
	pDataInvHead->m_yfpdm = pInvHead->m_yfpdm;			/**< 原发票代码 */
	pDataInvHead->m_yfphm = pInvHead->m_yfphm;			/**< 原发票号码 */
	pDataInvHead->m_fkdw = pInvHead->m_fkdw;			/**< 付款单位 */
	pDataInvHead->m_payerCode = pInvHead->m_payerCode;	/**< 付款单位税号 */
	pDataInvHead->m_sky = pInvHead->m_sky;				/**< 收款员 */
	pDataInvHead->m_sphsl = pInvHead->m_sphsl;			/**< 商品行数量 */
	pDataInvHead-> m_fwm = pInvHead->m_fwm;				/**< 防伪税控吗 */
	pDataInvHead->m_fplb = pInvHead->m_fplb;		    /**< 发票类别 */
	pDataInvHead->m_scbz = pInvHead->m_scbz;			/**< 上传标志 */
	pDataInvHead->m_fpsyh = pInvHead->m_fpsyh;			/**< 发票索引号*/
	pDataInvHead->m_zfsj = pInvHead->m_zfsj;			/**< 作废时间 */
	pDataInvHead->m_casign = pInvHead->m_casign;		/**< CA签名*/
	pDataInvHead->m_backup1 = pInvHead->m_backup1;		/**< 备用1 */
	pDataInvHead->m_backup2 = pInvHead->m_backup2;		/**< 备用2 */
	pDataInvHead->m_kpse = pInvHead->m_kpse;			/**< 税额*/
	pDataInvHead->m_kpje = pInvHead->m_kpje;			/**< 金额(不含税额)*/
	pDataInvHead->m_fplxdm = pInvHead->m_fplxdm;		/**< 发票类型代码 */
	pDataInvHead->m_zfbz = pInvHead->m_zfbz;			/**<  作废标志*/
	pDataInvHead->m_hyfl = pInvHead->m_hyfl;			/**< 行业分类 */
	pDataInvHead->m_fpzl = pInvHead->m_fpzl;			/**< 发票种类 默认为"c" */
	pDataInvHead->m_gfdzdh = pInvHead->m_gfdzdh;		/**< 购方地址电话 */
	pDataInvHead->m_gfyhzh = pInvHead->m_gfyhzh;		/**< 购方银行账号 */
	pDataInvHead->m_zyspmc = pInvHead->m_zyspmc;		/**< 主要商品名称 */
    pDataInvHead->m_bsq = pInvHead->m_bsq;				/**< 报税期 */
	pDataInvHead->m_xfdzdh = pInvHead->m_xfdzdh;		/**< 销方地址电话 */
	pDataInvHead->m_xfyhzh = pInvHead->m_xfyhzh;		/**< 销方银行账号 */
	pDataInvHead->m_fhr = pInvHead->m_fhr; 				/**< 复核人 */
    pDataInvHead->m_qdbz = pInvHead->m_qdbz;			/**< 清单标志 */
	pDataInvHead->m_CurTime = pInvHead->m_CurTime;		/**< 当前时间*/
	pDataInvHead->m_jqbh = pInvHead->m_jqbh;

	pDataInvHead->m_xfmc = g_globalArgLib->m_corpInfo->m_Nsrmc;		/**< 销方名称 */
	pDataInvHead->m_xfsh = g_globalArgLib->m_corpInfo->m_Nsrsbh;	/**< 销方税号 */
	pDataInvHead->m_zskl = g_globalArgLib->m_strZskl;				/**< 证书口令 */
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
	pInvHead->m_fpdm = pDataInvHead->m_fpdm;			/**< 发票代码 */
	pInvHead->m_fphm = pDataInvHead->m_fphm;			/**< 发票号码 */
	pInvHead->m_kprq = pDataInvHead->m_kprq;			/**< 开票日期 */
	pInvHead->m_kpsj = pDataInvHead->m_kpsj;			/**< 开票时间 */
	pInvHead->m_kplx = pDataInvHead->m_kplx;			/**< 开票类型 */
	pInvHead->m_kphjje = pDataInvHead->m_kphjje;		/**< 开票合计金额（含税） */
	pInvHead->m_yfpdm = pDataInvHead->m_yfpdm;			/**< 原发票代码 */
	pInvHead->m_yfphm = pDataInvHead->m_yfphm;			/**< 原发票号码 */
	pInvHead->m_fkdw = pDataInvHead->m_fkdw;			/**< 付款单位 */
	pInvHead->m_payerCode = pDataInvHead->m_payerCode;	/**< 付款单位税号 */
	pInvHead->m_sky = pDataInvHead->m_sky;				/**< 收款员 */
	pInvHead->m_sphsl = pDataInvHead->m_sphsl;			/**< 商品行数量 */
	pInvHead-> m_fwm = pDataInvHead->m_fwm;				/**< 防伪税控吗 */
	pInvHead->m_fplb = pDataInvHead->m_fplb;		    /**< 发票类别 */
	pInvHead->m_scbz = pDataInvHead->m_scbz;			/**< 上传标志 */
	pInvHead->m_fpsyh = pDataInvHead->m_fpsyh;			/**< 发票索引号*/
	pInvHead->m_zfsj = pDataInvHead->m_zfsj;			/**< 作废时间 */
	pInvHead->m_casign = pDataInvHead->m_casign;		/**< CA签名*/
	pInvHead->m_backup1 = pDataInvHead->m_backup1;		/**< 备用1 */
	pInvHead->m_backup2 = pDataInvHead->m_backup2;		/**< 备用2 */
	pInvHead->m_kpse = pDataInvHead->m_kpse;			/**< 税额*/
	pInvHead->m_kpje = pDataInvHead->m_kpje;			/**< 金额(不含税额)*/
	pInvHead->m_fplxdm = pDataInvHead->m_fplxdm;		/**< 发票类型代码 */
	pInvHead->m_zfbz = pDataInvHead->m_zfbz;			/**<  作废标志*/
	pInvHead->m_hyfl = pDataInvHead->m_hyfl;			/**< 行业分类 */
	pInvHead->m_fpzl = pDataInvHead->m_fpzl;			/**< 发票种类 默认为"c" */
	pInvHead->m_gfdzdh = pDataInvHead->m_gfdzdh;		/**< 购方地址电话 */
	pInvHead->m_gfyhzh = pDataInvHead->m_gfyhzh;		/**< 购方银行账号 */
	pInvHead->m_jqbh = pDataInvHead->m_jqbh;			/**< 机器编号 */
	pInvHead->m_zyspmc = pDataInvHead->m_zyspmc;		/**< 主要商品名称 */
    pInvHead->m_bsq = pDataInvHead->m_bsq;				/**< 报税期 */
	pInvHead->m_sksbbh = pDataInvHead->m_sksbbh;		/**< 金税盘编号 */
	pInvHead->m_xfmc = pDataInvHead->m_xfmc;			/**< 销方名称 */
	pInvHead->m_xfsh = pDataInvHead->m_xfsh;			/**< 销方税号 */
	pInvHead->m_xfdzdh = pDataInvHead->m_xfdzdh;		/**< 销方地址电话 */
	pInvHead->m_xfyhzh = pDataInvHead->m_xfyhzh;		/**< 销方银行账号 */
	pInvHead->m_fhr = pDataInvHead->m_fhr; 				/**< 复核人 */
    pInvHead->m_qdbz = pDataInvHead->m_qdbz;			/**< 清单标志 */
	pInvHead->m_zskl = pDataInvHead->m_zskl;			/**< 证书口令 */
	pInvHead->m_CurTime = pDataInvHead->m_CurTime;		/**< 当前时间*/

	CInvDet *pInvDet = NULL;
	pInvHead->DelList();
	vector<CDataInvDet>::iterator iter;
	for (iter=pDataInvHead->m_gvector.begin(); iter!=pDataInvHead->m_gvector.end(); ++iter)
	{
		pInvDet = pInvDet->GetNewInvDet();

		pInvDet->m_fpdm = iter->m_fpdm;			/**< 发票代码 */
		pInvDet->m_fphm = iter->m_fphm;			/**< 发票号码 */
		pInvDet->m_kprq = iter->m_kprq;			/**< 开票日期 */
		pInvDet->m_kpsj = iter->m_kpsj;			/**< 开票时间 */
		pInvDet->m_kplx = iter->m_kplx;			/**< 开票类型 */
		pInvDet->m_opid = iter->m_opid;			/**< 操作员id */
		pInvDet->m_sky = iter->m_sky;			/**< 收款员 */

		pInvDet->m_sphxh = iter->m_sphxh;		/**< 商品行序号，从1开始 */
		pInvDet->m_spbm = iter->m_spbm;			/**< 商品编码 */
		pInvDet->m_spmc = iter->m_spmc;			/**< 商品名称 */
		pInvDet->m_spdj = iter->m_spdj;			/**< 商品单价(含税) */
		pInvDet->m_spsl = iter->m_spsl;			/**< 商品数量 */
		pInvDet->m_spje = iter->m_spje;			/**< 商品金额(含税) */
		pInvDet->m_sl = iter->m_sl;				/**< 税率 */
		pInvDet->m_property = iter->m_property;	/**< 商品行属性 */
		pInvDet->m_spdw = iter->m_spdw;			/**< 单位 */
		pInvDet->m_ggxh = iter->m_ggxh;			/**< 规格型号 */
		pInvDet->m_spse = iter->m_spse;			/**< 商品税额 */
		pInvDet->m_dj = iter->m_dj;				/**< 商品单价(不含税) */
		pInvDet->m_je = iter->m_je;				/**< 商品金额(不含税) */
		pInvDet->m_dotNum = iter->m_dotNum;     /**< 数量四舍五入后的小数位数 */
		pInvDet->m_backup = iter->m_backup;		/**< 备用 */
		pInvDet->m_hsbz = iter->m_hsbz;			/**< 含税价标志(1:单价含税 0:单价不含税) */

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
	pDataNetPara->m_IsDhcp = pNetPara->m_IsDhcp;			/**< 是否自动分配IP */
	pDataNetPara->m_LocalIP = pNetPara->m_LocalIP;			/**< 本机IP */
	pDataNetPara->m_LocalGate = pNetPara->m_LocalGate;		/**< 本机网关 */
	pDataNetPara->m_LocalMask = pNetPara->m_LocalMask;		/**< 子网掩码 */
	pDataNetPara->m_LocalDNS = pNetPara->m_LocalDNS;		/**< DNS */
	pDataNetPara->m_ServIP = pNetPara->m_ServIP;			/**< 服务器IP地址 */
	pDataNetPara->m_ServPort = pNetPara->m_ServPort;		/**< 服务器端口号 */
	pDataNetPara->m_ServAddr = pNetPara->m_ServAddr;		/**< 服务器部署路径 */
	pDataNetPara->m_FtpIP = pNetPara->m_FtpIP;				/**< ftp服务器地址 */
	pDataNetPara->m_FtpPort = pNetPara->m_FtpPort;			/**< ftp端口号 */
	pDataNetPara->m_FtpUser = pNetPara->m_FtpUser;			/**< 用户名 */
	pDataNetPara->m_FtpPwd = pNetPara->m_FtpPwd;			/**< 密码 */
	
	return;
}
void CDataTransformFunc::Data2NetPara(CDataNetPara *pDataNetPara, CNetPara *pNetPara)
{
	pNetPara->m_IsDhcp = pDataNetPara->m_IsDhcp;			/**< 是否自动分配IP */
	pNetPara->m_LocalIP = pDataNetPara->m_LocalIP;			/**< 本机IP */
	pNetPara->m_LocalGate = pDataNetPara->m_LocalGate;		/**< 本机网关 */
	pNetPara->m_LocalMask = pDataNetPara->m_LocalMask;		/**< 子网掩码 */
	pNetPara->m_LocalDNS = pDataNetPara->m_LocalDNS;		/**< DNS */
	pNetPara->m_ServIP = pDataNetPara->m_ServIP;			/**< 服务器IP地址 */
	pNetPara->m_ServPort = pDataNetPara->m_ServPort;		/**< 服务器端口号 */
	pNetPara->m_ServAddr = pDataNetPara->m_ServAddr;		/**< 服务器部署路径 */
	pNetPara->m_FtpIP = pDataNetPara->m_FtpIP;				/**< ftp服务器地址 */
	pNetPara->m_FtpPort = pDataNetPara->m_FtpPort;			/**< ftp端口号 */
	pNetPara->m_FtpUser = pDataNetPara->m_FtpUser;			/**< 用户名 */
	pNetPara->m_FtpPwd = pDataNetPara->m_FtpPwd;			/**< 密码 */
	
	return;
}

