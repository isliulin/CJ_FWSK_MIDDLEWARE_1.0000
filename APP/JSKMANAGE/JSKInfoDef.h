#ifndef __LIB_JSKINFODEF_H
#define __LIB_JSKINFODEF_H

#include <string.h>
#include "JSKInfoDef.h"
#include "VersionConfig.h"

#define MAX_SEND_BUFF_LEN	5*1024
#define MAX_BUFF_LEN	   10*1024


#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
#define PTHREAD_KPMUTEX_OPEN	0	//线程互斥
#else
#define PTHREAD_KPMUTEX_OPEN	1	//线程互斥
#endif

#define JSK_SUCCESS    0
#define JSK_FAILURE    -1

#define GET_CORP_INFO						0X01    //获取纳税户信息
#define GET_JSP_INFO                        0X02    //获取金税盘参数信息
#define GET_BSP_INFO                        0X15    //获取报税盘参数信息
#define GET_OFF_LIMIT_INFO					0X14    //获取金税盘离线控制参数
#define JSP_PASSWORD_MANAGE				    0X16	//金税盘(证书)口令管理
#define BSP_REGISTER                        0X17    //报税盘注册
#define UPDATE_JSK_CLOCK                    0X18    //修改金税盘时钟
#define UPDATE_CORP_INFO					0X03    //更新企业信息
#define READ_CORP_INFO                      0X10    //读取企业信息
#define SET_UPLOAD_FLAG                     0X11    //设置发票上传状态
#define COPY_TAX_FUN						0X04    //抄税功能
#define CLEAR_CARD_FUN						0X12    //清卡功能
#define GET_NET_INVOL_INFO					0X05    //读入新购发票
#define GET_JSK_INVOL_INFO					0X06    //获取金税盘可用发票卷信息(即购票信息查询)
#define MAKE_INVOICE_FUN					0X07    //开票
#define INVOICE_WASTE_FUN					0X09    //已开票作废
#define GET_CUR_INVIOCE_INFO				0X08    //获取当前发票号信息
#define HOST_TO_INVVOL						0X0A    //主机分票
#define INVVOL_RET_INFO						0X0B    //发票退回（主分机一样）
#define HOST_GET_INVVOL						0X0C    //主机读入分机退回发票
#define GET_INVIOCE_INFO					0X0F    //发票查询
#define GET_LOCK_DATE				    	0X19    //锁死日期
#define GET_MONTH_COUNT_DATE				0X1A    //查询月统计数据


#define JSK_FP_JZLX_BSP			1			//报税盘
#define JSK_FP_JZLX_JSP			2			//税控设备(金税盘)

#define NEWLINE_LEN      1
#define NEWLINE_COMMAND  "\n"
#define INVKIND_NAME  'c'

#define JSK_UPDATE_CLOCK                        7      //修改金税盘时钟长度
#define JSK_PASSWORD_LEN                        9      //金税盘前口令(9)
#define JSK_PASSWORD_SUM_LEN                    18      //金税盘前口令(9)+新口令(9)
#define JSK_NET_GET_INV_LEN                     16      //网络购票申请信息
#define JSK_NET_INV_CON_LEN                     40      //网络购票确认信息长度
#define JSK_NET_RUN_NO_LEN                      16      //网络流水号长度
#define JSK_FISCAL_CODE_LEN                     20      //税控码长度           
#define JSK_SUM_INFO_LEN						320      //汇总信息长度
#define JSK_COPY_TAX_INFO_LEN					320      //抄税信息长度
#define JSK_CLEAR_CARD_INFO_LEN                 128      //清卡信息长度
#define JSK_NET_CRYP_DATA_LEN					144      //通过网络从后台获取的电子发票数据包（密文）长度
#define JSK_RUN_NO_LEN                          16      //流水号长度
#define JSK_NO_LEN								16      //金税/报税盘号长度
#define JSK_HASH_NO_LEN							24      //哈希税号长度
#define JSK_ADDR_NO_LEN							 8     //地区编号长度
#define JSK_PZ_NO								 2      //票种个数
#define JSK_QUERY_DATE_LEN                       6      //查询发票输入日期长度
#define JSK_OTHER_INFO_LEN						500		//其他信息长度
#define JSK_LXXXMW_LEN							512		//离线信息密文长度
#define JSK_GPXXMW_LEN							256		//购票信息密文长度
#define JSK_ISSUE_NO_LEN						15		//发行税号长度
#define JSK_MAX_JQBH_LEN						12		//税控收款机机器编号长度
#define JSK_MAKE_INV_SIGN_LEN					1024		//开票签名长度


#define INVVOL_MAX_NUM  100            //发票卷最大条数
#define INVKIND_MAX_NUM 10              //发票种类最大条数
#define MAX_TAX_NUM		20			//最大税率个数

#define MAX_SKSBBH_LEN		12			//税控设备编号长度
#define MAX_SKSBKL_LEN		8			//税控设备口令长度
#define MAX_NSRSBH_LEN		20			//纳税人识别号长度
#define MAX_NSRMC_LEN		80			//纳税人名称长度
#define MAX_SWJGDM_LEN		11			//税务机关代码长度
#define MAX_FPLXDM_LEN		3			//发票类型代码长度
#define MAX_FPDM_LEN		12			//发票代码长度
#define MAX_SKM_LEN			20			//税控码长度
#define MAX_VER_LEN			10			//版本号长度
#define MAX_DATETIME_LEN	14			//时间长度
#define	MAX_KPJH_LEN		5			//开票机号长度
#define MAX_PWD_LEN			18			//金税盘前口令(9)+新口令(9)

#define MAX_INV_INFO_LEN	1024*4		//发票明细数据长度

#define CA_SIGN_BASE64		1

//哈希税号长度
#define HASH_NO_FLAG_16		1			//企业参数下载、网络抄报
#define HASH_NO_FLAG_24		2			//发票卷下载/解锁接口

#define DEFAULT_FPLB_NO		41
#define FPLX_NO_1			41
#define FPLX_DM_1			"025"

#define MIDDLEWARE_SAVE_DB		1

//2.25.税控设备其他信息查询信息类型定义
#define SKSBQTYXXCX_XXLX_WLCB			0
#define SKSBQTYXXCX_XXLX_QLJS			1
#define SKSBQTYXXCX_XXLX_LXXXSC			2
#define SKSBQTYXXCX_XXLX_WLLQFP			3
#define SKSBQTYXXCX_XXLX_WLLQFPJGQR		4
#define SKSBQTYXXCX_XXLX_FPSCJGHQ		5

//税控盘报税盘组合操作类型定义
#define SKPBSP_CZLX_SJCB		1	//数据抄报
#define SKPBSP_CZLX_QLJS		2	//清零解锁
#define SKPBSP_CZLX_FXGPXX		3	//反写购票信息
#define SKPBSP_CZLX_JZSZ		4	//校准税控设备时钟

#define MAX_ERR_MSG_LEN			200

#define JSK_COMMON_ERR_NO		-101
#define JSK_COMMON_ERR_CODE		"-101"

#define JSK_NORMAL_INV						1		//正常发票--对应NORMAL_INV
#define JSK_RETURN_INV						2		//已退发票--对应RETURN_INV
#define JSK_WASTE_NOR						3       //正废--对应WASTE_NOR
#define JSK_WASTE_RET                       4       //负废--对应WASTE_RET
#define JSK_WASTE_INV						5		//空白作废--对应WASTE_INV


#define JSK_DETAIL_BUF_LEN            4*1024     //存储商品明细内容长度
#define JSK_SPMC_LEN					92		//商品名称长度
#define JSK_GGXH_LEN					40		//规格型号长度
#define JSK_JLDW_LEN                    22          //计量单位长度
#define JSK_SPSL_LEN					21		//数量（精度18，宽度21）长度
#define JSK_SPDJ_LEN					21		//单价（精度18，宽度21）长度
#define JSK_SPJE_LEN					18		  //金额（保留2位小数，宽度18）
#define JSK_SL_LEN						6		//税率（6）长度
#define JSK_SE_LEN						18		//税额（保留2位小数，宽度18）长度
#define JSK_SPXH_LEN					8		//序号（8）长度
#define JSK_FPXZ_LEN				    3		//发票行性质（3）长度
#define JSK_HSBZ_LEN				    3		//含税价标志（3）长度

#define JSK_SUM_EXTENSION					100		//金额放大倍数

//权限信息
typedef struct _TInvSixLimit
{
	UINT8 invName;						/*票种*/
	UINT8   invLimit[6];					/*单张发票限额 */
    UINT8  OffLinePosTotalLimit[6];		/*离线正数发票累计限额*/			
} __attribute__ ((packed)) TInvSixLimit;

typedef struct _TInvAuthLimitInfo
{
	UINT8 invNum;						/* 票种数*/
	TInvSixLimit InvSixLimit[10];
}__attribute__ ((packed)) TInvAuthLimitInfo;


typedef struct _TOffLimintInfo
{	
	UINT8 OffLineLockDay;	    /*离线锁死日(每月的第几天)*/
    UINT32 OffLineInvTime;	   /*离线开具时间 单位小时*/
	TInvAuthLimitInfo AuthLimitInfo;    /*离线控制参数*/

}__attribute__ ((packed)) TOffLimintInfo;

/*
（8）获取第一张发票离线发票的发票号码、发票代码和发票索引号
输入：参数pp2=7；
              INBUFF[] ：无
输出：OUTBUFF：16字节发票代码（10或12位ASCII码）+4字节发票号码+4字节发票索引号
*/

typedef struct _TFirstOffInvInfo
{
	INT8   InvCode[16];			    /* 发票代码 */
	UINT32  InvNo;					/* 发票号码 */
	UINT8 InvIndex[4];               /* 发票索引号*/

}__attribute__ ((packed)) TFirstOffInvInfo;


typedef struct _TaxCardInfo
{	
	UINT8 CorpName[100];					/* 企业名称 */
	UINT8 KPNo[2];  /*开票机号，对于主机标识其拥有的分机数；对于分机，标识分机号*/
	UINT8 zfFlag;							/*主分机标志 0代表主机 1代表分机 */
	UINT8 CorpPorpertiy;					/*纳税人企业性质 数字0表示一般纳税人；数字1表示小规模纳税人*/
	UINT8 CorpType;							/*行业类型 数字0表示非特定企业；数字1表示特定企业*/
	UINT8 ResignNo[50];						/*工商登记号*/
	UINT8 DepositBank[100];					/*开户银行*/
	UINT8 DepositAccount[50];				/*开户账号*/
	UINT8 ResignAddress[100];				/*登记注册地址*/
	UINT8 TaxAuthorityNo[20];				/*主管税务机关代码*/
	UINT8 TaxAuthorityName[100];			/*主管税务机关名称*/
	UINT8  TaxCode[25];						/* 企业纳税人识别号*/
    UINT8  AuthTaxRate[21]; /*税率授权,第1字节表示授权税率个数，第2字节开始为授权的普票税率，
						例如:金税盘有两个17%和3%两种税率授权，则AuthTaxRate的前3字节表示为0x02 0xA0 0x1E，其余字节填充数字0*/
    UINT8 invName[11]; /*发票类型, 第1字节表示发票类型个数，第2字节开始为发票类型*/
}__attribute__ ((packed)) TaxCardInfo;


/*
Case 0x09：已开发票作废
输入：pp2=0；
INBUFF ： 9字节证书口令（9字符，口令长度不足9，填充数字0，例如"88888888"） + 结构体TaxCardInvCancel
输出：OUTBUFF： 2字节签名长度+签名数据+4字节发票索引号+7字节作废日期（BCD码7字节，例如0x20 0x15 0x04 0x13 0x19 0x46 0x00）
*/

typedef struct _TaxCardInvCancel
{
	INT8    TypeCode[16];		/*10或12位ASCII码发票代码*/
	UINT32  InvNo;				/*发票号码*/   
	UINT8 Type;					/*发票类型*/
	UINT8 invFlag;				/*发票标志：正废、负废*/
	INT8    InvAcess[4];	/*发票索引号*/
		
}__attribute__ ((packed)) TaxCardInvCancel;


typedef struct _TInvCancel
{

  INT8   CAPassW[9];       /*ca口令*/
  TaxCardInvCancel  taxCardInvCancel;
		
}__attribute__ ((packed)) TInvCancel;


/*
Case 0x04：抄税（即规范"数据抄报"）
网络抄税
输入：参数pp2=0；
	  INBUFF 1字节发票类型
输出：OUTBUFF  7字节抄税起始时间（BCD格式，
例如0x20 0x15 0x04 0x13 0x19 0x46 0x00）
+7字节抄税截至时间（BCD格式，例如0x20 0x15 0x04 0x13 0x19 0x46 0x00）
+抄税汇总信息320B（密文）；
*/

typedef struct  _TNetCopyTax
{
    UINT8 StartDate[7];			/*抄税起始时间 */
    UINT8 EndDate[7];			/*抄税截至时间 */
    UINT8 CopyTax[JSK_SUM_INFO_LEN];			/*抄税汇总信息*/
}__attribute__ ((packed)) TNetCopyTax;


/*
Case 0x06：获取盘上票源信息
输入：参数pp2=0 
输出：发票卷信息  前两字节（word）卷数 +结构体*卷数 
定义结构体InvVolume

  格式：发票类别：1-专用发票 2-普通发票
  发票起始号：123     HeadCode=123;
  发票代码：1100102140   10/12位发票代码  TypeCode="1100102140";
  
*/
typedef struct  _TInvVolume
{
	UINT8 Type;		 /*发票类别*/
	UINT32  HeadCode;	 /*发票起始号*/
	UINT16  Count;   /*张数 */
	UINT16  Remain;  /*剩余份数*/
    UINT8 BuyDate[7];	 /*购买日期BCD,例如0x20 0x15 0x04 0x13 0x19 0x46 0x00*/
	INT8 TypeCode[16]; /*发票代码10或12位ASCII码*/

}__attribute__ ((packed)) TInvVolume;


typedef struct  _TInvVol
{

	UINT16 InvNum;  /*两字节（word）卷数*/
    TInvVolume InvVolum[5];  /* 结构体*卷数*/

}__attribute__ ((packed)) TInvVol;



/*
申请网络购票
输入：参数pp2=1 
输出：OUTBUFF[32] 16B网络购票预授权信息（密文）+16B网络购票流水号；
*/
typedef struct  _TNetInvVolInfo
{
    UINT8 netEmpowInfo[16];			/*网络购票预授权信息（密文） */   
}__attribute__ ((packed)) TNetInvVolInfo;

/*
网络购票读入确认申请
输入：参数pp2=3 
输出：OUTBUFF 52字节金税盘网络购票读入确认数据包
（12字节明文（票种1+号码4+张数2+代码5）+40字节密文
*/
typedef struct  _TJSPNetInvVol
{
	UINT8 Type;		      /*发票类别*/
	UINT32  InvNO;	      /*发票起始号*/
	UINT16  Count;        /*张数 */
	INT8 TypeCode[5];     /*发票代码6*/
	UINT8 NetInvInfo[40]; /*金税盘网络购票读入确认密文*/
}__attribute__ ((packed)) TJSPNetInvVol;



/*
Case 0x07：开票
定义结构体 TaxCardInvHead
输入：pp2=0（正常开票）；
      pp2=1（空白作废）
      INBUFF ： 9字节证书口令（9字符，口令长度不足9，填充数字0，例如"88888888"） + 结构体TaxCardInvHead
	  
输出：OUTBUFF：2字节密文长度+密文data+'\0'+4字节发票索引号+2字节签名长度+签名数据
格式：发票代码：1100102140   10/12位发票代码  TypeCode="1100102140"
      发票号码：87654321  InvNo=87654321
      购方税号：14030100DK01232   20位购方税号 BuyTaxCode="14030100DK01232"或者为空
      金额 99.5  TotalSum=9950；
      税额 17.5   Tax=1750；
      发票类别 1-专用发票 2-普通发票
*/

typedef struct _TaxCardInvHead
{
	INT8   TypeCode[16];			 /*10或12位ASCII码发票代码*/
	UINT32  InvNo;					 /*发票号码*/   
	UINT8 Date[7];                   /* 开票日期，BCD,例如0x20 0x15 0x04 0x13 0x19 0x46 0x00*/
	INT8 BuyTaxCode[21];			 /*购方税号*/
	INT8 TotalSum[20];    /*金额，空白废金额为0*/  
 	INT8 Tax[20];        /*税额*/
	UINT8 Type;       /*发票类型*/
	UINT8 invFlag;    /*发票标志：正数、负数、空白废*/
	INT8 NegToPosTypeCode[16];   /*负数发票对应的正数发票的号码*/
    UINT32 NegToPosInvNo;   /*负数发票对应的正数发票的代码*/	
	UINT32 DataLen;  /*保存到金税盘中自定义发票数据长度*/
	UINT8 *DataPtr; /*开票时写入金税盘中发票数据缓冲区*/
					/*已开发票作废时为已开发票的发票数据*/	
}__attribute__ ((packed)) TaxCardInvHead;

typedef struct _TInvHead
{
	INT8   CAPassW[9];			    /*9字节证书口令*/
	TaxCardInvHead taxCardInvHead;   /*发票开具信息*/
	
}__attribute__ ((packed)) TInvHead;


/*
Case 0x08：获取当前发票号
输入：pp2=0；
输出:  16B发票代码（字符串格式）+4字节发票号码（dword类型数据）+1字节发票类别
格式：发票代码：1100102140   10/12位发票代码  "1100102140"
      发票号码：87654321
	  发票类别：1=增值税专用发票；2=增值税普通发票
*/
typedef struct _TCurInvInfo
{
	INT8   InvCode[16];			    /* 发票代码 */
	UINT32  InvNo;					/* 发票号码 */
	INT8    Type;                   /* 发票类别*/
	UINT16  Remain;					/*剩余份数*/

}__attribute__ ((packed)) TCurInvInfo;

/*
Case 0x0f：发票查询

根据发票号码+发票代码+索引号（可选）查询发票
输入：参数pp2=0；
     INBUFF[24]  unsigned int发票起始号;16B发票代码; 
	 unsigned int发票索引号（可选，若上层数据库无此字段，填充4字节0xFF）
 
 输出：单张发票明细，定义结构体 TInvDetail
*/

typedef struct _TQueryInfo
{
	UINT32  InvNo;					/* 发票号码 */
	INT8   InvCode[16];			    /* 发票代码 */
	UINT8 InvIndex[4];               /* 发票索引号*/

}__attribute__ ((packed)) TQueryInfo;

/*
3）网络购票读入确认申请（查询网购票已加载未解锁状态）
输入：参数pp2=3 
INBUFF  1字节票种类型
输出：OUTBUFF 63字节金税盘网络购票读入确认数据包（40字节密文（用于规范的3.7的输入参数）+23字节明文（票种1+号码4+张数2+代码16））；
如果金税盘内无已下载未解锁的网络购票发票卷信息，输出返回长度0； 
*/

typedef struct _TApp2NetInfo
{
	UINT8  NetInvInfo[40];             /*40字节密文*/
	UINT8  InvType;                /*票种*/
	UINT32  InvNo;					/* 发票号码 */
	UINT16 Count;                  /* 发票张数*/
	INT8   InvCode[16];			    /* 发票代码 */

}__attribute__ ((packed)) TApp2NetInfo;

/*
Case 0x0f：发票查询

      根据年月查询指定月份的发票（此接口每次返回一张发票的明细，查询指定月份的全部发票需循环调用此接口）
输入：参数pp2=1；
              INBUFF[6]  unsigned int年; unsigned short 月。 
输出：1字节接收后续发票标志（数字1表示有后续发票需要接收；数字0表示无）+单张发票明细，定义结构体

*/
typedef struct _TDateQueryInfo
{
	UINT32  InvYear;					/* 年 */
	UINT16  InvMonth;			    /* 月 */

}__attribute__ ((packed)) TDateQueryInfo;

typedef struct _TInvDetail
{
	INT8    TypeCode[16];	    /*10或12位ASCII码发票代码*/
	UINT32     InvNo;			/*发票号码*/   
	UINT8     Date[7];       /* 开票日期*/
	INT8      BuyTaxCode[21];		/*购方税号*/
	INT8 TotalSum[20];    /*金额*/  
	INT8 Tax[20];   		/*税额*/
	UINT8 Type;					/*发票类别*/
	UINT8 invFlag;    /*发票标志：正数、负数、正废、负废、空白废*/	
	UINT32 DataLen;  /*发票数据长度*/
	UINT8 *DataPtr; /*发票数据明细*/
    UINT32 SignLen; /*签名长度*/
    UINT8 *SignPtr; /*签名数据*/
	INT8    CheckCode[21];		 /*20位校验码 */
	UINT8 Adress[4];   /*发票索引号 */ 
	UINT8   UpFlag;      /*发票上传标志：1-已上传；0-未上传*/

}__attribute__ ((packed)) TInvDetail;

//typedef struct _TInvRecover
//{
//	UINT8 invNum;				/*修复张数*/
//	TInvDetail InvDetail[2];   /*发票明细*/
// }__attribute__ ((packed)) TInvRecover;


/*
Case 0x0a：主机分票

 (1).给分机报税盘分票
输入：参数pp2=0；
      INBUFF[22]  unsigned int发票起始号;16B发票代码;unsigned short发票张数 
输出：无

(2).给分机金税盘分票
输入：参数pp2=1；
      INBUFF[22]  unsigned int发票起始号;16B发票代码;unsigned short发票张数 
输出：无

格式：发票起始号：123   
      发票代码：1100102140   10/12位发票代码  "1100102140"
  */

typedef struct  _THostToInv
{
	UINT32  InvNo;					/* 发票号码 */
	INT8   InvCode[16];			    /* 发票代码 */
	UINT16   InvNum;				/* 发票张数*/
	UINT8    InvType;               /* 发票类型*/
	
}__attribute__ ((packed)) THostToInv;


/*
Case 0x0b：发票退回（主分机一样）

(1).用报税盘退回
输入：参数pp2=0；
      INBUFF[22]  unsigned int发票起始号;16B发票代码; unsigned short发票张数 
输出：无
(2).用金税盘退回
输入：参数pp2=1；
      INBUFF[22]  unsigned int发票起始号;16B发票代码; unsigned short发票张数 
输出：无

格式：发票起始号：HeadCode=123    
      发票代码：1100102140   10/12位发票代码  "1100102140"

  */

typedef struct  _TInvRetInfo
{
	UINT32  InvNo;					/* 发票号码 */
	INT8   InvCode[16];			    /* 发票代码 */
	UINT16   InvNum;				/* 发票张数*/
	UINT8    InvType;               /* 发票类型*/
	
}__attribute__ ((packed)) TInvRetInfo;


typedef struct _TClearCardInfo
{
	UINT8 Type;						/* 票种种类*/
	INT8 CCardInfo[128];            /* 128字节清卡数据*/
}__attribute__ ((packed)) TClearCardInfo;

/*
Case 0x1A：查询月统计数据
输入：参数pp2=0；
INBUFF： 2字节年份（WORD类型）+2字节月份（WORD类型）
输出：1字节发票种类数量N+N个月统计数据结构体TInvCount 
格式：
正数发票开具份数：100张，InvNum=100
证书发票累计金额 99.5  InvSum="99.50"
*/
typedef struct  _TInvCount
{
	UINT8 	    Type;       			/*发票类型*/
	UINT32	    OpenInventory;			/*期初库存*/  
	UINT32     	NewBuy; 				/*本期新购*/ 
	UINT32     	EndInventory; 			/*期末库存*/
	UINT32     	ReBack; 				/*本期退回*/
	UINT32     	InvNum; 			    /*正数发票开具份数*/
	UINT32      InvCancelNum; 		    /*正数发票作废份数*/
	UINT32      NegInvNum; 			    /*负数发票开具份数*/
	UINT32      NegInvCancelNum; 		/*负数发票作废份数*/
	INT8     	InvSum[20]; 			/*正数发票累计金额*/
	INT8     	InvTax[20]; 			/*正数发票累计税额*/
	INT8     	NegInvSum[20]; 			/*负数发票累计金额*/
	INT8     	NegInvTax[20]; 			/*负数发票累计税额*/
	
}__attribute__ ((packed)) TInvCount;


typedef struct  _TSumInvCount
{
	UINT8 uTypeNum;
	TInvCount invCount[8];

}__attribute__ ((packed)) TSumInvCount;


typedef struct  _TFpmx
{
	
	INT8 Fpmc[JSK_SPMC_LEN];			    /*商品名称（92）*/ 
	INT8 Ggxh[JSK_GGXH_LEN];			    /*规格型号（40）*/ 
	INT8 Jldw[JSK_JLDW_LEN];				/*计量单位（22）*/ 
	INT8 Spsl[JSK_SPSL_LEN];				/*数量（精度18，宽度21）*/ 
	INT8 Spdj[JSK_SPDJ_LEN];				/*单价（精度18，宽度21）*/ 
	INT8 Spje[JSK_SPJE_LEN];				/*金额（保留2位小数，宽度18）*/ 
	INT8 SL[JSK_SL_LEN];				    /*税率（6）*/ 
	INT8 SE[JSK_SE_LEN];				    /*税额（保留2位小数，宽度18）*/ 
	INT8 Spxh[JSK_SPXH_LEN];				/*序号（8）*/ 
	INT8 Fpxz[JSK_FPXZ_LEN];				/*发票行性质（3）*/ 
	INT8 Hsbz[JSK_HSBZ_LEN];				/*含税价标志（3）*/
}__attribute__ ((packed)) TFpmx;


typedef struct  _TFpmxSum
{
    TFpmx fpmx[6];     /* 结构体*/

}__attribute__ ((packed)) TFpmxSum;



#endif


