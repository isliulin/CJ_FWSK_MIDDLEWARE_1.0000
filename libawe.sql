


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

--#########������ҵ��Ϣ��#####################
--#     ��˰��ʶ���					varchar(30)
--#     ��˰������            varchar(200) 
--#     ��Ʊ������							varchar(50)
--#     ���ֻ���־					varchar(50)
--#     ��˰����ҵ����							varchar(6)
--#     ��ҵ����			varchar(40)
--#     ��˰���豸��							char
--#     ���̵ǼǺ�						char
--#     ��������			char
--#     �����˺�				char
--#     �Ǽ�ע���ַ					varchar(2)
--#     ����˰����ش���				char
--#     ����˰���������						varchar(50)
--#     ��Ʊ��Ȩ˰�ʸ���     				varchar(200)
--#     ��Ʊ������						int
--#     ����						int
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

--#########���������û���Ϣ��#################
--#		����1		varchar(20)
--#		����2		varchar(20)
--#		����3		varchar(20)
--#		����4		varchar(20)
--#		����5		varchar(20)
--#		����6		varchar(20)
--#		����7		varchar(20)

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

--#########������˰�˷�Ʊ������Ϣ��#################
--#     ����       					INTEGER
--#     ��Ʊ���         			char
--#     ��Ʊ����         		varchar(20)
--#     ��Ʊ��ʼ����        varchar(10)	
--#     ��Ʊ��ֹ����				varchar(10)
--#     ʣ�����						int
--#     ʹ�ñ�־						char
--#     �����־						char
--#     ��Ʊ�������				varchar(6)
--#     ��������						char
--#     ����1						char
--#     ����2						char
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

--#########������Ʊ���߱�#################	
--#     ����						INTEGER
--#     ��Ʊ����				varchar(20)    
--#     ��Ʊ����				int
--#			��Ʊ����				int              
--#     ��Ʊʱ��				int
--#     ��Ʊ����				char
--#     ��Ʊ�ϼƽ���˰��		Big int       
--#     ˰��		Big int   
--#     ԭ��Ʊ����			varchar(20)
--#     ԭ��Ʊ����			int			
--#     ���λ      	varchar(200)	
--#			�տ�Ա					varchar(30)
--#     �տ�ԱID				varchar(30)		
--#			���ʽ				char
--#			��Ʒ������			int		
--#			��ҵ����				varchar(40)		
--#			˰����					varchar(1000)
--#			��Ʊ�������		varchar(5)
--#			���˰��  varchar(32)
--#			˰��						float
--#			Ʊ�����				int
--#			��Ʊ���				char
--#			�ϴ���־				char
--#			��ע��չ				varchar(4)
--#			���״̬				varchar(4)
--#			�����ֶ�				varchar(20)
--#			CAǩ��				varchar(20)
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

--#########������Ʊ������ϸ��#################
--#     ����					INTEGER          
--#     ��Ʊ����			varchar(20)
--#			��Ʊ����			int		
--#     ��Ʊ����				char
--#     ����ԱID      char
--#			��Ʒ�����		int
--#			��Ʊ����			int					
--#			��Ʊʱ��			int						
--#			��Ʒ����
--#			��Ʒ����			varchar(100)
--#			��Ʒ����			double
--#			��Ʒ����			double
--#			��Ʒ���			Big int
--#			��Ʒ˰��			Big int
--#			˰��					float
--#     		��Ʒ������    char
--#			��Ʒ��λ				float
--#		�����ֶ�			varchar(20)	
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

--#########������Ʊ��#########################
--#     ����						INTEGER
--#     ��Ʊ����				varchar(20)
--#     ��Ʊ����			int(8)
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

--#########�����������ܱ�####################
--#			���				INTEGER	
--#			������				int
--#			��������			int
--#			������ֹ			int
--#			��Ʊ����			int
--#			��Ʊ��Ʊ���			Big int
--#			��Ʊ����			int
--#			��Ʊ��Ʊ���			Big int
--#			��Ʊ����			int
--#			��Ʊ��Ʊ���			Big int
--#			��Ϸ���			int
--#			��Ͽ�Ʊ���			Big int
--#			�հ׷�Ʊ����			int
--#			��������			int
--#			�����ɹ�����			int
--#			ʧ��ԭ��			varchar(100)
--#			��������			char
--#			��˰�ɹ���־			char
--#			���ͽ��ʱ�־			char
--#			����δ�ϴ��ķ�Ʊ����		int
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


--#########����ϵͳ������#################
--#		��������			char			
--#		��������			varchar(20)		
--#		��������ֵ		int			
--#		�����ı�ֵ		varchar(64)		
--#		��������ֵ		blob			
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
--#########������Ʊ�����#################	
--#     ��Ʊ����		varchar(20)
--#     ��Ʊ����			int    
--#     ��Ʊ����			int
--#			��Ʊʱ��			int              
--#     ��Ʊ����			tinyint
--#     ��Ʊ�ܽ��		big int
--#     �ϴ���־      tinyint
--#     ���ϱ�־      tinyint
--#			CAǩ��			varchar(160)
--#			�����ֶ�			varchar(20)	
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
--#########Ʊ����Ϣ��#################	
--#     ��Ʊ����		varchar(10)
--#     ���������գ�ÿ�µĵڼ��죩	varchar(20)
--#     ���߿���ʱ�䣨��λСʱ��	varchar(20)
--#     ���ŷ�Ʊ�޶�		big int
--#     ����������Ʊ�ۼ��޶�	big int
--#	�����ֶ�		varchar(20)	
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



--#########��ҵ��###################
--#    ���          varchar(40)
--#     ˰��         	float
--#     ����		varchar(20)
--############################################
--
-- Table structure for table `TAX`
--

CREATE TABLE TAX(
	NO			INTEGER 		PRIMARY KEY,
	SL       	float    ,
	BACKUP   varchar(20)
);

--#########���������###################
--#	�Ƿ��Զ�����IP	char,
--#	����IP			varchar(20),
--#	��������		varchar(20),
--#	��������		varchar(20),
--#	DNS				varchar(20),
--#	������IP��ַ	varchar(20),
--#	�������˿ں�	varchar(6),
--#	����������·��	varchar(50),
--#	ftp��������ַ	varchar(20),
--#	ftp�˿ں�		varchar(6),
--#	�û���			varchar(16),
--#	����			varchar(16)
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



--����������
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


