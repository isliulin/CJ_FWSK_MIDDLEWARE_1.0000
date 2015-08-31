


drop table IF EXISTS USERINFO;
drop table IF EXISTS USER_MORE;
drop table IF EXISTS INV_VOL;
drop table IF EXISTS INV_HEAD;
drop table IF EXISTS INV_DET;
drop table IF EXISTS RT_INV;
drop table IF EXISTS SYSARG;
drop table IF EXISTS INV_SERV;
drop table IF EXISTS INV_KIND;
drop table IF EXISTS TAX;
drop table IF EXISTS NETPARA;


--
-- Dumping data for table `MACHINE`
--

--#########创建企业信息表#####################
--#     纳税人识别号					varchar(30)
--#     纳税人名称            varchar(200) 
--#     开票机号码							varchar(50)
--#     主分机标志					varchar(50)
--#     纳税人企业性质							varchar(6)
--#     行业类型			varchar(40)
--#     金税盘设备号							char
--#     工商登记号						char
--#     开户银行			char
--#     开户账号				char
--#     登记注册地址					varchar(2)
--#     主管税务机关代码				char
--#     主管税务机关名称						varchar(50)
--#     普票授权税率个数     				varchar(200)
--#     开票机数量						int
--#     备用						int
--############################################
--
-- Table structure for table `USERINFO`
--

CREATE TABLE USERINFO (
  NSRSBH		varchar(25)		NOT NULL,
  NSRMC			varchar(200)		NOT NULL,
  KPJHM                 int                     NOT NULL,
  ZFFLAG                char			NOT NULL,
  NSRXZ                 char			NOT NULL,
  HY_LX                 char			NOT NULL,
  JSPSBH                varchar(12)		NOT NULL,
  GSDJH                 varchar(50),
  KHYH                  varchar(100),
  KHZH                  varchar(50),
  DJZCDZ                varchar(100),
  SWJGDM		varchar(20),		
  SWJGMC		varchar(100),
  SLGS                  int			NOT NULL,
  KPJSL			int			NOT NULL,
  QYSJ			varchar(20),
  JQBH			varchar(20),
  BACKUP	        varchar(20)
);

--
-- Dumping data for table `USERINFO`
--

--#########创建额外用户信息表#################
--#		备用1		varchar(20)
--#		备用2		varchar(20)
--#		备用3		varchar(20)
--#		备用4		varchar(20)
--#		备用5		varchar(20)
--#		备用6		varchar(20)
--#		备用7		varchar(20)

--############################################
--
-- Table structure for table `USER_MORE`
--

CREATE TABLE USER_MORE (
	BACKUP1	 varchar(20),
	BACKUP2	 varchar(20),
	BACKUP3	 varchar(20),
	BACKUP4	 varchar(20),
	BACKUP5	 varchar(20),
	BACKUP6	 varchar(20),
	BACKUP7	 varchar(20)	
) ;



--
-- Dumping data for table `CLIENT`
--

--#########创建纳税人发票领用信息表#################
--#     自增       					INTEGER
--#     发票类别         			char
--#     发票代码         		varchar(20)
--#     发票起始号码        varchar(10)	
--#     发票终止号码				varchar(10)
--#     剩余份数						int
--#     使用标志						char
--#     用完标志						char
--#     发票种类代码				varchar(6)
--#     购买日期						char
--#     备用1						char
--#     备用2						char
--############################################
--
-- Table structure for table `INV_VOL`
--

CREATE TABLE INV_VOL (
	NO			INTEGER 		PRIMARY KEY,
	INV_TYPE		char			NOT NULL,
	CODE			varchar(20)		NOT NULL,
	IS_NO			int			NOT NULL,
	IE_NO			int			NOT NULL,
	REMAIN			int			NOT NULL,
	FPZFS			int			NOT NULL,
	USED_FLAG		char			NOT NULL,
	OVER_FLAG		char			NOT NULL,
	KIND_CODE		varchar(6)		NOT NULL,	
	RQ                    int,	
	BACKUP1                  int,
	BACKUP2                  varchar(10),
	UNIQUE  (CODE,IS_NO)
);

--
-- Dumping data for table `INV_VOL`
--

--#########创建发票开具表#################	
--#     自增						INTEGER
--#     发票代码				varchar(20)    
--#     发票号码				int
--#			开票日期				int              
--#     开票时间				int
--#     开票类型				char
--#     开票合计金额（含税）		Big int       
--#     税额		Big int   
--#     原发票代码			varchar(20)
--#     原发票号码			int			
--#     付款单位      	varchar(200)	
--#			收款员					varchar(30)
--#     收款员ID				varchar(30)		
--#			付款方式				char
--#			商品行数量			int		
--#			行业名称				varchar(40)		
--#			税控码					varchar(1000)
--#			发票种类代码		varchar(5)
--#			付款方税号  varchar(32)
--#			税率						float
--#			票种类别				int
--#			发票类别				char
--#			上传标志				char
--#			备注扩展				varchar(4)
--#			验旧状态				varchar(4)
--#			备用字段				varchar(20)
--#			CA签名				varchar(20)
--############################################
--
-- Table structure for table `INV_HEAD`
--

CREATE TABLE INV_HEAD (
	NO			INTEGER			PRIMARY KEY,
	FPDM			varchar(20)		NOT NULL,
	FPHM			int				NOT NULL,
	KPRQ			int				NOT NULL,
	KPSJ			int				NOT NULL,
	KPLX			char			NOT NULL,
	KPHJJE			Big int			NOT NULL,
	KPSE			Big int			NOT NULL,
	YFPDM			varchar(20),
	YFPHM			int				NOT NULL,
	FKDW			varchar(200)	NOT NULL,
	PAYER_CODE		varchar(20)		NOT NULL,
	SKY				varchar(30),
	SPHSL			int				NOT NULL,
	FMW				varchar(32)		NOT NULL,
	FPLB			char,
	ZFSJ			char(20),
--	BZ_KZ       varchar(20),
--	ZT				varchar(4),
	FPSYH			varchar(10),
	BACKUP1			varchar(20),
	CA_SIGN         varchar(512)    NOT NULL,

	UNIQUE  (FPDM,FPHM)
);

--
-- Dumping data for table `INV_HEAD`
--

--#########创建发票开具明细表#################
--#     自增					INTEGER          
--#     发票代码			varchar(20)
--#			发票号码			int		
--#     开票类型				char
--#     操作员ID      char
--#			商品行序号		int
--#			开票日期			int					
--#			开票时间			int						
--#			商品编码
--#			商品名称			varchar(100)
--#			商品单价			double
--#			商品数量			double
--#			商品金额			Big int
--#			商品税额			Big int
--#			税率					float
--#     		商品行属性    char
--#			商品单位				float
--#		备用字段			varchar(20)	
--############################################
--
-- Table structure for table `INV_DET `
--

CREATE TABLE INV_DET (
	NO		INTEGER				PRIMARY KEY,
	FPDM		varchar(20)			NOT NULL,
	FPHM		int				NOT NULL,
	KPLX		char			NOT NULL,
--	OP_ID		char        NOT NULL, 
	SKY			varchar(30),
	SPHXH		int				NOT NULL,
	KPRQ		int				NOT NULL,
	KPSJ		int				NOT NULL,
	SPBM		varchar(16)  			NOT NULL,
	SPMC		varchar(100)			NOT NULL,
	SPDJ		double,
	SPSL		double,
	SPJE		Big int				NOT NULL,
	SPSE		Big int				NOT NULL,
	SL		float,
	DJ		double,
	JE		Big int				NOT NULL,
	PROP		char				NOT NULL,
	SP_DW		varchar(10),
	BACKUP		varchar(20),
	UNIQUE(FPDM,FPHM,SPHXH)
);

--
-- Dumping data for table `INV_DET `
--

--#########创建退票表#########################
--#     自增						INTEGER
--#     发票代码				varchar(20)
--#     发票号码			int(8)
--############################################
--
-- Table structure for table `RT_INV`
--

CREATE TABLE RT_INV (
     NO     		INTEGER 		PRIMARY KEY,
     FPDM		varchar(20)		NOT NULL,
     FPHM		int			NOT NULL,
     UNIQUE  (FPDM,FPHM)
);

--
-- Dumping data for table `RT_INV`
--

--#########创建抄报汇总表####################
--#			编号				INTEGER	
--#			所属期				int
--#			所属期起			int
--#			所属期止			int
--#			正票份数			int
--#			正票开票金额			Big int
--#			红票份数			int
--#			红票开票金额			Big int
--#			废票份数			int
--#			废票开票金额			Big int
--#			红废份数			int
--#			红废开票金额			Big int
--#			空白发票份数			int
--#			抄报日期			int
--#			抄报成功日期			int
--#			失败原因			varchar(100)
--#			抄报类型			char
--#			报税成功标志			char
--#			报送介质标志			char
--#			本期未上传的发票份数		int
--############################################
--
-- Table structure for table `CB_HZ`
--

--CREATE TABLE CB_HZ (
--	NO			INTEGER				PRIMARY KEY,
--	SSQ			int					NOT NULL,
--	SSQ_Q			int				NOT NULL,
--	SSQ_Z			int				NOT NULL,
--	ZPFS			int				NOT NULL,
--	ZPKPJE			Big int			NOT NULL,
--	HPFS			int				NOT NULL,
--	HPKPJE			Big int			NOT NULL,
--	ZFFS			int				NOT NULL,
--	ZFKPJE			Big int			NOT NULL,
--	HFFS			int				NOT NULL,
--	HFKPJE			Big int			NOT NULL,
--	KBFPFS			int				NOT NULL,
--	BSRQ			int				NOT NULL,
--	BSCGRQ			int				NOT NULL,
--	BSSBYY			varchar(100),
--	BSLX			char			NOT NULL,
--	BSCGBZ			char			NOT NULL,
--	BSJZBZ			char			NOT NULL,
--	WSCFPS			int				NOT NULL,
--	UNIQUE (SSQ)
--);

--
-- Dumping data for table `CB_HZ`
--


--#########创建系统参数表#################
--#		参数代码			char			
--#		参数名称			varchar(20)		
--#		参数整型值		int			
--#		参数文本值		varchar(64)		
--#		参数数组值		blob			
--############################################
--
-- Table structure for table `SYSARG`
--
CREATE TABLE SYSARG (
	SA_ID			char			NOT NULL,
	NAME			varchar(20) 		NOT NULL,
	V_INT			int,
	V_TEXT			varchar(64),
	V_BLOB			BLOB,
	PRIMARY KEY(SA_ID)
);

--
-- Dumping data for table `SYSARG`
--
--#########创建发票服务表#################	
--#     发票代码		varchar(20)
--#     发票号码			int    
--#     开票日期			int
--#			开票时间			int              
--#     开票类型			tinyint
--#     开票总金额		big int
--#     上传标志      tinyint
--#     作废标志      tinyint
--#			CA签名			varchar(160)
--#			备用字段			varchar(20)	
--############################################
--
-- Table structure for table `INV_SERV`
--

CREATE TABLE INV_SERV ( 
	NO        INTEGER PRIMARY KEY,
	FPDM		  varchar(20)				NOT NULL,
	FPHM		int(11)		NOT NULL,     
	FPSYH		varchar(4),
	I_DATE		int				NOT NULL,
	I_TIME		int				NOT NULL, 
	I_TYPE		char			NOT NULL,
	M_SUM		  big int		NOT NULL,
	UP_FLAG   char      NOT NULL,
	WST_FLAG  char      NOT NULL,
	ERRMSG   varchar(512),
	BACKUP		varchar(20)
--	UNIQUE  (CODE_NO, INV_NO)
) ;


--
-- Dumping data for table `INV_SERV`
--
--#########票种信息表#################	
--#     发票类型		varchar(10)
--#     离线锁死日（每月的第几天）	varchar(20)
--#     离线开具时间（单位小时）	varchar(20)
--#     单张发票限额		big int
--#     离线正数发票累计限额	big int
--#	备用字段		varchar(20)	
--############################################
--
-- Table structure for table `INV_KIND`
--

CREATE TABLE INV_KIND ( 
	NO        INTEGER PRIMARY KEY,
	FPLX		char		NOT NULL,	
	LX_SSR      int			NOT NULL,
	LX_KJSJ     int			NOT NULL,
	MAX_SING	big int		NOT NULL,	
	MAX_SUM	    big int		NOT NULL,	
	BACKUP		varchar(20),
	UNIQUE  (FPLX)
) ;

--
-- Dumping data for table `INV_KIND`
--



--#########行业表###################
--#    序号          varchar(40)
--#     税率         	float
--#     备用		varchar(20)
--############################################
--
-- Table structure for table `TAX`
--

CREATE TABLE TAX(
	NO			INTEGER 		PRIMARY KEY,
	SL       	float    ,
	BACKUP   varchar(20)
);

--#########网络参数表###################
--#	是否自动分配IP	char,
--#	本机IP			varchar(20),
--#	本机网关		varchar(20),
--#	子网掩码		varchar(20),
--#	DNS				varchar(20),
--#	服务器IP地址	varchar(20),
--#	服务器端口号	varchar(6),
--#	服务器部署路径	varchar(50),
--#	ftp服务器地址	varchar(20),
--#	ftp端口号		varchar(6),
--#	用户名			varchar(16),
--#	密码			varchar(16)
--############################################
CREATE TABLE NETPARA(
	ISDHCP		char,
	LOCIP		varchar(20),
	LOCGATE		varchar(20),
	LOCMASK		varchar(20),
	LOCDNS		varchar(20),
	SERVIP		varchar(20),
	SERVPORT	varchar(6),
	SERVADDR	varchar(50),
	FTPIP		varchar(20),
	FTPPORT		varchar(6),
	FTPUSER		varchar(16),
	FTPPWD		varchar(16)
);



--建立表索引
CREATE index HEAD_NO		on 		INV_HEAD(FPDM, FPHM);
CREATE index HEAD_DATE		on 		INV_HEAD(KPRQ);
CREATE index DET_NO			on 		INV_DET(FPHM);
CREATE index DET_DATE		on 		INV_DET(KPRQ);


--
-- init sysarg
--

insert into sysarg values(50,'',0,'',0);
insert into sysarg values(51,'',0,'',0);
insert into sysarg values(52,'',0,'',0);
insert into sysarg values(53,'',0,'',0);
insert into sysarg values(54,'',0,'',0);
insert into sysarg values(55,'',0,'',0);
insert into sysarg values(56,'',0,'',0);

insert into sysarg values(61,'',9600,'',0);
insert into sysarg values(100,'',0,'88888888',0);
insert into sysarg values(101,'',0,'23456789',0);


insert into NETPARA values(0,'192.168.2.134','192.168.2.1','255.255.255.0','0.0.0.0','192.168.0.104','8002','/temp/server', '0.0.0.0', '121', 'zzz', '000000');


