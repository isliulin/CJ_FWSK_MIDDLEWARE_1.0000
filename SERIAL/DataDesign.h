#ifndef DATA_DESIGN
#define DATA_DESIGN

#define INV_MAX_NUM 100

//-----------------------------------------------------------------
//串口通信数据长度定义
//-----------------------------------------------------------------
#define JQBH_LEN			12				//机器编号长度
#define KOULING_LEN			8				//设备口令长度

#define ZSKOULING_LEN		8				//证书口令长度
#define SBBH_LEN			12				//设备编号长度
#define NSRSBH_LEN			20				//纳税人识别号长度
#define FKDWSH_LEN			20				//付款单位税号长度
#define NSRMC_LEN			80				//纳税人名称长度
#define SKDWMC_LEN			80				//收款单位名称长度
#define FKDWMC_LEN			80				//付款单位名称长度
#define SWJGDM_LEN			11				//税务机关代码长度
#define SWJGMC_LEN			80				//税务机关名称长度
#define FPLXDM_A_LEN		30				//发票类型代码数据长度
#define SZSJ_LEN			14				//时钟时间长度
#define BBH_LEN				10				//版本号长度
#define KPJH_LEN			5				//开票机号长度
#define QYLX_LEN			3				//企业类型长度
#define BLXX_LEN			16				//保留信息长度
#define KZXX_LEN			80				//扩展信息长度
#define SPHSL_LEN			4				//商品行数量长度

#define FPLXDM_S_LEN		3				//单个发票类型代码长度
#define DATE_LEN			8				//日期长度
#define TIME_LEN			6				//时间长度
#define XIANE_LEN			12				//限额数据长度
#define FSFPTS_LEN			4				//开具负数发票限定天数长度
#define SYRL_LEN			12				//剩余容量长度
#define SCJZRQ_LEN			2				//上传截止日期长度
#define LXXDGNBS_LEN		4				//离线限定功能标识长度
#define LXKPSC_LEN			5				//离线开票限定时长长度
#define LXKPZS_LEN			10				//离线开票张数长度
#define LXKZXX_LEN			160             //离线开票扩展信息长度
#define ZDYXX_LEN			100				//自定义信息长度

#define SZSMSYH_LEN			3				//税种税目索引号长度
#define SZSMDM_LEN			6				//税种税目代码长度
#define TAXRATE_LEN			6				//税率长度
#define SZSMMC_LEN			40				//税种税目名称长度

#define FPDM_LEN			12				//发票代码长度
#define FPHM_LEN			8				//发票号码长度
#define FPFS_LEN			12				//发票份数长度
#define FPZS_LEN			10				//发票张数长度
#define RYMC_LEN			20				//人员名称长度
#define FPJFS_LEN			3				//发票卷份数数长度
#define QTXX_LEN			500				//其他信息
#define HZXX_LEN			100				//汇总信息
#define ZH_QTXX_LEN			50				//税控设备报税盘组合操作：其他信息

#define ITEM_MAX_COUNT		10				//单张票最大项目数量
#define FPLG_MAX_COUNT		10				//发票领购最大份数

#define HYFL_LEN			20				//行业分类长度
#define XMMC_LEN			20				//项目名称长度
#define DJ_LEN				12				//单价长度
#define SL_LEN				12				//数量长度
#define JE_LEN				12				//金额长度
#define TAXRATE_NUM_LEN		3				//税率数量长度
#define TAXRATE_MAX_NUM		10				//税率最大个数
#define TAX_LEN				12				//税额长度
#define BZ_LEN				80				//备注长度
#define SKM_SHORT_LEN		20				//短税控码长度
#define SKM_LONG_LEN		190				//长税控码长度
#define SIGN_LEN			512				//签名长度

#define CXTJ_LEN			30				//查询条件长度
#define FPFS_LEN			12				//发票份数长度
#define ITEM_COUNT_LEN		3				//子项目数量长度

#define KPLX_ZSFP			0				//正数发票类型
#define KPLX_FSFP			1				//负数发票类型
#define WASTE_KBFP			0				//空白发票作废类型
#define WASTE_YKFP			1				//已开发票作废类型

#define	IFDTIP_LEN			1				//是否自动分配IP长度
#define	FFBZ_LEN			2				//分发标志长度

#define	IP_LEN			    20				//IP长度
#define	GATE_LEN			20				//网关长度
#define	MASK_LEN			20				//子网掩码长度
#define	DNS_LEN				20				//DNS长度
#define	PORT_LEN			6				//端口号长度
#define	FWQBSLJ_LEN			50				//服务器部署路径长度
#define	USERNAME_LEN		16				//用户名长度
#define	PASSWORD_LEN		16				//密码长度

#define	WSCFPZS_LEN			8				//未上传发票张数
#define	SCZS_LEN			5				//上传张数
#define	SCSJJG_LEN			10				//上传时间间隔
#define CWMS_LEN			128				//错误描述

//-----------------------------------------------------------------
//串口通信命令字定义
//-----------------------------------------------------------------
#define SERIAL_ONLINE_CMD			0x01		//联机命令
#define SERIAL_SKPBHCX_CMD			0x02		//税控盘编号查询命令
#define SERIAL_BSPBHCX_CMD			0x03		//报税盘编号查询命令
#define SERIAL_SKPXXCX_CMD			0x04		//税控盘信息查询命令
#define SERIAL_BSPXXCX_CMD			0x05		//报税盘信息查询命令
#define SERIAL_JKSJCX_CMD			0x06		//监控数据查询命令
#define SERIAL_SQSLCX_CMD			0x07		//授权税率查询命令
#define SERIAL_GPXXCX_CMD			0x08		//购票信息查询命令
#define SERIAL_SKSBKLGG_CMD			0x09		//口令更改命令
#define SERIAL_FPKJ_CMD				0x0A		//发票开具命令
#define SERIAL_FPZF_CMD				0x0B		//发票作废命令
#define SERIAL_FPCX_CMD				0x0C		//发票查询命令
#define SERIAL_SKPBSPZHCZ_CMD		0x0D		//税控盘报税盘组合操作命令
#define SERIAL_BSPFPCX_CMD			0x0E		//报税盘发票查询命令
#define SERIAL_FPFF_CMD				0x0F		//发票分发命令
#define SERIAL_FPHS_CMD				0x10		//发票回收命令
#define SERIAL_SJCB_CMD				0x11		//数据抄报命令
#define SERIAL_WLJKHC_CMD			0x12		//网络监控回传命令
#define SERIAL_FPTJXXCX_CMD			0x13		//发票统计信息查询命令
#define SERIAL_QYXXGX_CMD			0x14		//企业信息更新命令
#define SERIAL_LXQXGX_CMD			0x15		//离线权限更新命令
#define SERIAL_FPSSSC_CMD			0x16		//发票实时上传命令
#define SERIAL_WLCSWH_CMD			0x17		//网络参数维护命令
#define SERIAL_SZCKBTL_CMD			0x18		//设置串口波特率命令
#define SERIAL_FPDR_CMD				0x19		//发票读入命令
#define SERIAL_FJTH_CMD				0x1A		//分机退回命令
#define SERIAL_WLGP_CMD				0x1B		//网络购票命令
#define SERIAL_ZSKLGG_CMD			0x1C		//证书口令更改命令
#define SERIAL_FPBL_CMD				0x1D		//发票补录命令
#define SERIAL_HQLXSJ_CMD			0x30		//获取离线数据命令

#define SERIAL_ERRUPINV_CMD			0x31		//获取上传出错发票信息
#define SERIAL_CONNECT_TEST_CMD		0x32		//安全通道连接测试
#define SERIAL_ZHQQK_CMD			0x99		//转换器清库

#define SERIAL_YYSJ_CMD				0xFE		//应用升级命令
#define SERIAL_SYSTEST_CMD			0xFD		//系统自检命令
#define SERIAL_WMAC_CMD				0xFC		//烧写MAC命令
#define SERIAL_WJQBH_CMD			0xFB		//烧写机器编号命令


//     weichao
#define SQL_CMD "../sqlite3 LIBAWE < ../libawe.sql"     //重建数据库命令
#define RMLIB_CMD "rm -rf LIBAWE"                     //删除数据库文件命令
#define REBOOT_CMD "reboot -f"                        //重启
#define MOUNT_CMD "mount /dev/sda1 /mnt"              //挂载
#define CPAWE_CMD "cp /mnt/awe4000r ../awe4000rbak"		//备份
#define CPSQL_CMD "cp /mnt/libawe.sql ../libawe.sql"	//备份
#define RMAWE_CMD "rm -f ../awe4000r"                   //删除
#define MVAWE_CMD "mv ../awe4000rbak ../awe4000r"       //重命名
#define UMOUNT_CMD "umount /mnt"                      //解挂载

#endif