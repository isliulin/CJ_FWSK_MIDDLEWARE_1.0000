
#ifndef DATA_CLASS_DESIGN_H
#define DATA_CLASS_DESIGN_H

#include <vector>
#include "IncludeMe.h"

/**
 *@class CDataUserInfo 
 *@brief 用户信息类
 */
class CDataUserInfo
{
public:
    
	CDataUserInfo();
	~CDataUserInfo();

	string m_Nsrsbh;		/**< 纳税人识别号 */
	string m_Nsrmc;			/**< 纳税人名称 */
	UINT32 m_Kpjhm;			/**< 开票机号码 */
	UINT8  m_zfFlag;        /**<主分机标志 0代表主机 1代表分机*/
	UINT8  m_Nsrxz;			/**< 纳税人企业性质 */
	UINT8  m_Hylx;			/**< 行业类型 */
	string m_Jspsbh;		/**< 金税盘设备号 */
	string m_Gsdjh;			/**< 工商登记号 */
	string m_Khyh;			/**< 开户银行 */
	string m_Khzh;			/**< 开户账号 */
	string m_Djzcdz;		/**< 登记注册地址 */
	string m_Swjgdm;		/**< 主管税务机关代码 */
	string m_Swjgmc;		/**< 主管税务机关名称 */
	UINT32 m_Slgs;			/**< 普票授权税率个数 */
	UINT32 m_Kpjsl;			/**< 开票机数量 */
	string m_qysj;			/**< 启用时间 YYYYMMDDHHMMSS */
	string m_jqbh;			/**< 机器编号 */
	string m_backup;		/**< 备用 */

	string m_bbh;			/**< 版本号 */
	string m_blxx;			/**< 保留信息 */
	string m_fplxdm;  		/**< 发票类型代码 */
	string m_qtkzxx;   		/**< 其他扩展信息 */
	string m_sksbkl;   		/**< 税控设备口令 */
	UINT32 m_Fplxgs;		/**< 发票类型个数 */
	string m_Fplxsz;		/**< 发票类型 */
	string m_bspbh;			/**< 报税盘编号 */
};

/**
 *@class CDataTax 
 *@brief 行业信息类
 */
class CDataTax
{
public:

	CDataTax();
	~CDataTax();

    UINT32 m_no;			/**< 序号 */
	UINT32 m_sl;			/**< 税率 */
	string m_backup;		/**< 备用 */	
};

/**
 *@class CDataInvVol 
 *@brief 发票领用信息类
 */
class CDataInvVol
{
public:
    
	CDataInvVol();
	~CDataInvVol();

	UINT8  m_invtype;		/**< 发票类别 */
	string m_code;			/**< 发票代码 */
	UINT32 m_isno;			/**< 发票起始号码 */
	UINT32 m_ieno;			/**< 发票终止号码 */
	UINT32 m_remain;		/**< 剩余份数 */
	UINT32 m_fpzfs;			/**< 发票总份数 */
	UINT8  m_usedflag;		/**< 使用标志 */
	UINT8  m_overflag;		/**< 用完标志 */
	string m_kindcode;		/**< 发票种类代码 */
	UINT32 m_date;			/**< 购买日期 */	
	UINT32 m_backup1;		/**< 备用字段1 */
	string m_backup2;		/**< 备用字段2 */
	string m_fplxdm;		/**< 发票类型代码 */

	UINT32 m_curInvNo;		/**< 当前发票号，不存库 */
	string m_buyDate;		/**< 购买日期(盘上获取的时间)*/
	UINT32 m_FlagJSorXZ;	/**< 业务九:发票卷解锁or下载标识，1表示解锁，0表示下载*/
	UINT32 m_fpzl;			/**< 发票种类*/
	string m_lbdm;			/**< 类别代码*/
	string m_flag;			/**< 写盘锁死发票卷密文信息*/
	string m_gpsq;			/**< 购票授权*/
	string m_yssh;			/**<压缩税号*/
	string m_dqbh;			/**<地区编号*/
	string m_dcbb;			/**<底层版本*/
	string m_fpjjsmw;		/**<发票卷解锁密文*/
	string m_fpjmw;			/**<发票密文信息*/
};

/**
 *@class CDataInvKind
 *@brief 纳税人票种类
 */
class CDataInvKind
{
public:
    
	CDataInvKind();
	~CDataInvKind();

	UINT8  m_fplx;			/**< 发票类型 */
	UINT32 m_Lxssr;			/**< 离线锁死日（每月的第几天） */
	UINT32 m_Lxkjsj;		/**< 离线开具时间（单位小时） */
	INT64  m_maxSign;		/**< 单张发票限额 */
	INT64  m_maxSum;		/**< 离线正数发票累计限额 */
	string m_backup;		/**< 备用字段 */
	string m_fplxdm;		/**< 发票类型代码 */


	string m_bsqsrq;		/**< 数据报送起始日期YYYYMMDDHHMMSS */
	string m_bszzrq;		/**< 数据报送终止日期 YYYYMMDDHHMMSS*/
	string m_kpjzrq;		/**< 开票截止日期 */
};

/**
 *@class CDataInvDet 
 *@brief 发票明细信息类
 */
class CDataInvDet;
class CDataInvDet
{
public:
    
	CDataInvDet();
	~CDataInvDet();

	string m_fpdm;			/**< 发票代码 */
	UINT32 m_fphm;			/**< 发票号码 */
	
	UINT32 m_kprq;			/**< 开票日期 */
	UINT32 m_kpsj;			/**< 开票时间 */
	UINT8  m_kplx;			/**< 开票类型 */
	UINT8  m_opid;          /**< 操作员id */
	string m_sky;			/**< 收款员 */
	
	UINT32 m_sphxh;			/**< 商品行序号，从1开始 */
	string m_spbm;			/**< 商品编码 */
	string m_spmc;			/**< 商品名称 */
	double m_spdj;			/**< 商品单价(含税) */
	double m_spsl;			/**< 商品数量 */
	INT64  m_spje;			/**< 商品金额(含税) */
	float  m_sl;			/**< 税率 */
	UINT8  m_property;		/**< 商品行属性 */
	string m_spdw;			/**< 单位 */
	string m_ggxh;			/**< 规格型号 */

	INT64 m_spse;			/**< 商品税额 */
	double m_dj;			/**< 商品单价(不含税) */
	INT64  m_je;			/**< 商品金额(不含税) */
	
	INT32 m_dotNum;         /**< 数量四舍五入后的小数位数 */
	UINT8 m_useFlag;		/**< 是否可用标志，0==可用，1==不可用 */
	string m_backup;		/**< 备用 */
	UINT8 m_hsbz;			/**< 含税价标志(1:单价含税 0:单价不含税) */

// 	class CDataInvDet *pNext;	/**< 指向下一个商品明细信息表 */
};

/**
 *@class CDataInvHead 
 *@brief 发票整体信息类
 */
class CDataInvHead
{
public:
    
	CDataInvHead();
	~CDataInvHead();

	string m_fpdm;			/**< 发票代码 */
	UINT32 m_fphm;			/**< 发票号码 */
	UINT32 m_kprq;			/**< 开票日期 */
	UINT32 m_kpsj;			/**< 开票时间 */
	UINT8  m_kplx;			/**< 开票类型 */
	INT64  m_kphjje;		/**< 开票合计金额（含税） */
	string m_yfpdm;			/**< 原发票代码 */
	UINT32 m_yfphm;			/**< 原发票号码 */
	string m_fkdw;			/**< 付款单位 */
	string m_payerCode;     /**< 付款单位税号 */
	string m_sky;			/**< 收款员 */
	UINT32 m_sphsl;			/**< 商品行数量 */
	string  m_fwm;			/**< 防伪税控吗 */
	UINT8 m_fplb;		    /**< 发票类别 */
	UINT8  m_scbz;			/**< 上传标志 */
	string m_fpsyh;         /**< 发票索引号*/
	string m_zfsj;			/**< 作废时间 */
	
	string m_casign;		/**< CA签名*/
	
	string m_backup1;		/**< 备用1 */
	string m_backup2;		/**< 备用2 */

	INT64 m_kpse;			/**< 税额*/
	INT64 m_kpje;			/**< 金额(不含税额)*/
	string m_fplxdm;		/**< 发票类型代码 */

	UINT8  m_zfbz;			/**<  作废标志*/
	string m_hyfl;			/**< 行业分类 */

	string m_fpzl;			/**< 发票种类 默认为"c" */
	string m_gfdzdh;		/**< 购方地址电话 */
	string m_gfyhzh;		/**< 购方银行账号 */
	string m_jqbh;			/**< 机器编号 */
	string m_zyspmc;		/**< 主要商品名称 */
    string m_bsq;			/**< 报税期 */
	string m_sksbbh;		/**< 金税盘编号 */

	string m_xfmc;			/**< 销方名称 */
	string m_xfsh;			/**< 销方税号 */
	string m_xfdzdh;		/**< 销方地址电话 */
	string m_xfyhzh;		/**< 销方银行账号 */
	string m_fhr; 			/**< 复核人 */
    string m_qdbz;			/**< 清单标志 */

	string m_zskl;			/**< 证书口令 */
	string m_CurTime;		/**< 当前时间*/

	vector<CDataInvDet> m_gvector;
//	CDataInvDet *pHead;		/**< 商品明细链表头 */
// 	CDataInvDet *pEnd;		/**< 商品明细链表尾？ */
// 	CDataInvDet m_InvDet;	/**< 商品明细子表 */
// 	CDataInvDet *m_pInvDet;	/**< 商品明细子表指针 */

};

/**
 *@class CDataNetPara 
 *@brief 网络参数类
 */
class CDataNetPara
{
public:
    
	CDataNetPara();
	~CDataNetPara();

	UINT8  m_IsDhcp;			/**< 是否自动分配IP */
	string m_LocalIP;			/**< 本机IP */
	string m_LocalGate;			/**< 本机网关 */
	string m_LocalMask;			/**< 子网掩码 */
	string m_LocalDNS;			/**< DNS */
	string m_ServIP;			/**< 服务器IP地址 */
	string m_ServPort;			/**< 服务器端口号 */
	string m_ServAddr;			/**< 服务器部署路径 */
	string m_FtpIP;				/**< ftp服务器地址 */
	string m_FtpPort;			/**< ftp端口号 */
	string m_FtpUser;			/**< 用户名 */
	string m_FtpPwd;			/**< 密码 */
};


/**
 *@class CDataTjxxhz
 *@brief 统计信息汇总类
 */
class CDataTjxxhz
{
public:
    
	CDataTjxxhz();
	~CDataTjxxhz();
		
public:
	UINT8  m_Type;			/**< 发票类型*/
	UINT32  m_Qsrq;			/**< 起始日期*/
	UINT32  m_Jzrq;			/**< 截止日期*/
	UINT32  m_Qckcfs;		/**< 期初库存份数 */
	UINT32  m_Lgfpfs;		/**< 领购发票份数 */
	UINT32  m_Thfpfs;		/**< 退回发票份数 */
	UINT32  m_Zsfpfs;		/**< 正数发票份数 */
	UINT32  m_Zffpfs;		/**< 正废发票份数 */
	UINT32  m_Fsfpfs;		/**< 负数发票份数 */
	UINT32  m_Fffpfs;		/**< 负废发票份数 */
	UINT32  m_Kffpfs;		/**< 空废发票份数 */
	UINT32  m_Qmkcfs;		/**< 期末库存份数 */
	INT64	m_Zsfpljje;		/**< 正数发票累计金额 */
	INT64	m_Zsfpljse;		/**< 正数发票累计税额 */
	INT64	m_Zffpljje;		/**< 正废发票累计金额 */
	INT64	m_Zffpljse;		/**< 正废发票累计税额 */
	INT64	m_Fsfpljje;		/**< 负数发票累计金额 */
	INT64	m_Fsfpljse;		/**< 负数发票累计税额 */
	INT64	m_Fffpljje;		/**< 负废发票累计金额 */
	INT64	m_Fffpljse;		/**< 负废发票累计税额 */

};

/**
 *@class CDeclare
 *@brief 数据抄报信息汇总类
 */
class CDataDeclare
{
public:
    
	CDataDeclare();
	~CDataDeclare();
		
public:
	string m_sq;			//属期
	string m_fpmx;			//发票明细数据
	string m_fpdxx;			//发票段信息
	string m_fphz;			//税控设备汇总数据
	string m_szfphz;		//安全芯片汇总数据
	string m_qtxx;			//其它信息
	
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
	
	string m_fpdm;			/**< 发票代码 */
	UINT32 m_fphm;			/**< 发票号码 */
	string m_errMsg;		/**< 错误描述 */
};





#endif
