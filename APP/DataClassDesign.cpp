
#include "DataClassDesign.h"

CDataUserInfo::CDataUserInfo()
{
	m_Nsrsbh = "";			/**< 纳税人识别号 */
	m_Nsrmc = "";			/**< 纳税人名称 */
	m_Kpjhm = 0;			/**< 开票机号码 */
	m_zfFlag = 0;           /**<主分机标志 0代表主机 1代表分机*/
	m_Nsrxz = 0;			/**< 纳税人企业性质 */
	m_Hylx = 0;				/**< 行业类型 */
	m_Jspsbh = "";			/**< 金税盘设备号 */
	m_Gsdjh = "";			/**< 工商登记号 */
	m_Khyh = "";			/**< 开户银行 */
	m_Khzh = "";			/**< 开户账号 */
	m_Djzcdz = "";			/**< 登记注册地址 */
	m_Swjgdm = "";			/**< 主管税务机关代码 */
	m_Swjgmc = "";			/**< 主管税务机关名称 */
	m_Slgs = 0;				/**< 普票授权税率个数 */
	m_Kpjsl = 0;			/**< 开票机数量 */
	m_backup = "";			/**< 备用 */
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
	m_sl= 0;				/**< 税率 */
	m_backup= "";			/**< 备用 */
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
	m_date = 0;				/**< 购买日期 */	
	m_backup1 = 0;			/**< 备用字段1 */
	m_backup2 = "";			/**< 备用字段2 */	
	
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
	m_Lxssr = 0;			/**< 离线锁死日（每月的第几天） */
	m_Lxkjsj = 0;			/**< 离线开具时间（单位小时） */
	m_maxSign = 0;
	m_maxSum = 0;			/**< 最大发票金额 */
	m_backup = "";			/**< 备用字段 */
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
	m_spdw = "件";
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
	m_casign = "";			/**< CA签名*/
	m_backup1 = "";
	m_backup2 = "";
	m_kpse = 0;				/**< 税额*/
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
	m_IsDhcp = 0;			/**< 是否自动分配IP */
	m_LocalIP = "";			/**< 本机IP */
	m_LocalGate = "";		/**< 本机网关 */
	m_LocalMask = "";		/**< 子网掩码 */
	m_LocalDNS = "";		/**< DNS */
	m_ServIP = "";			/**< 服务器IP地址 */
	m_ServPort = "";		/**< 服务器端口号 */
	m_ServAddr = "";		/**< 服务器部署路径 */
	m_FtpIP = "";			/**< ftp服务器地址 */
	m_FtpPort = "";			/**< ftp端口号 */
	m_FtpUser = "";			/**< 用户名 */
	m_FtpPwd = "";			/**< 密码 */
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
	m_sq = "";				//属期
	m_fpmx = "";			//发票明细数据
	m_fpdxx = "";			//发票段信息
	m_fphz = "";			//税控设备汇总数据
	m_szfphz = "";			//安全芯片汇总数据
	m_qtxx = "";			//其它信息
}
CDataDeclare::~CDataDeclare()
{

}

