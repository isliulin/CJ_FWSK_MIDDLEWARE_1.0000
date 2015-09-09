/*! \file  JSKInfoFunc.cpp
\brief    awe4000rJSK操作函数信息
\author   zcy
\version  1.0
\date     2014-05-03
*/

#include <pthread.h>
#include <errno.h>
#include "JSKInfoFunc.h"
#include "jsp_interface.h"
#include "arithmetic.h"
#include "base64.h"
#include "textParse.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

//#define DEGUG_PRN


INT8  JSK_InvBuf[JSK_DETAIL_BUF_LEN];


//struct TJSKerrInfo errInfo[JSK_ERROR_INFO_NUM] = 
struct TJSKerrInfo errInfo[] = 
{
	{3001,    "与金税盘通讯异常"		},
	{3003,    "接口输入参数错"			},
	{3065,    "金税盘通讯校验和错"		},
	{3072,    "金税盘句柄错"			},
	{4000,    "一般错误"				},
	{4001,    "没有找到金税盘"			},
	{4002,    "找到多个金税盘"			},
	{4003,    "打开分盘失败"			},
	{4004,    "无此命令"				},
	{4005,    "参数错误"				},
	{4006,    "数据错误"				},
	{4007,	  "款机编号认证失败"		},
	{6000,	  "以6000开头的错误号,为CA相关错误"},
	{8000,    "非法调用"				},
	{10000,    "未实现接口"				},
	{449,    "金额减税额除以税率的绝对值应小于0.625"    },
	{452,    "输入参数无效"    },
	{459,    "底层版本不支持特殊票种开具" },
	{506,    "金税卡时钟异常"			},
	{511,	 "发票类型错误"				},
	{552,	 "主分机不匹配"				},
	{554,    "金额超出开票限额"			},
	{559,    "税率超限"					},
	{562,    "发票明细超过64K错"    },
	{701,    "金税卡处于报税期,不能开票"    },
	{702,    "金税卡处于锁死期,不能开票"    },
	{706,    "金税卡运行已跨日,必须重新进入"    },
	{712,	 "报税盘退回发票已满"			},
	{713,	 "报税盘分配发票已满"			},
	{754,	 "分机不具备此功能"			},
	{767,	 "金税盘个数超限"			},
	{768,    "离线时间超过离线时长"    },
	{769,    "离线开票金额超限"    },
	{771,	 "分机分票已满"			},
	{772,	 "金税盘退票已满"			},
	{781,    "已到离线锁死期,不能开票"    },
	{784,    "开票明细中发票代码或号码与票面不一致"    },
	{790,	 "按月查询发票明细时该月无票"			},
	{800,	 "报税盘抄税数据不一致"			},
	{1,    "命令参数错误"    },
	{2,    "时钟没响应"    },
	{3,    "时钟停止"    },
	{4,    "金税盘状态异常,请退出系统重新进入"    },
	{5,    "记录区数据满"    },
	{6,    "记录区整理后数据仍满"    },
	{7,    "税控设备主分机不匹配"    },
	{8,    "金税盘购票区已满"    },
	{9,    "金税盘退票区已满"    },
	{10,    "该卷发票卷已购入"    },
	{15,    "分机报税盘中无退回发票卷"    },
	{19,    "会计日抄税提示"    },
	{27,    "主机有税未报,分机退回发票卷或撤回新票卷不可读入主机"    },
	{21,    "金税盘由于未报税锁死,不能开票"    },
	{36,    "记录区有效数据最大地址越界"    },
	{56,    "本月(期)开票数量已满,抄税提示"    },
	{57,    "主机税控设备和分机税控设备认证失败"    },
	{68,    "需要操作员权限"    },
	{71,    "不能执行生产测试"    },
	{72,    "不能初始化时钟"    },
	{75,    "抄税起始时间大于截止时间"    },
	{79,    "无相关授权记录"    },
	{80,    "开票查询时发票代码与发票卷类型标志不一致"    },
	{82,    "专票超过最大限额"    },
	{83,    "查询时间大于当前时间"    },
	{84,    "查询时间过早"    },
	{85,    "会计日到,禁止操作分配和退回发票卷"    },
	{86,    "检索时间错"    },
	{87,    "税控设备(金税盘、报税盘)中发票卷时间错"    },
	{88,    "检索参数错误"    },
	{89,    "未找到指定发票明细"    },
	{91,    "检索参数错误"    },
	{98,    "未到允许开票的起始时间"    },
	{99,    "开票数据有问题"    },
	{100,    "时钟不能往前改"    },
	{101,    "没检测到存储卡"    },
	{102,    "存储卡EDC错"    },
	{103,    "存储卡奇偶校验错"    },
	{104,    "存储卡链接错"    },
	{105,    "存储卡返回数据有误"    },
	{106,    "存储卡选择文件错"    },
	{107,    "存储卡读操作错"    },
	{108,    "存储卡写操作错"    },
	{109,    "存储卡校验PIN错"    },
	{110,    "存储卡取随机数错"    },
	{111,    "存储卡外部认证错"    },
	{112,    "存储卡接收长度错"    },
	{113,    "存储卡其他错误"    },
	{114,    "存储卡更新密钥错"    },
	{115,    "存储卡通信超时"    },
	{116,    "存储卡协议类型错"    },
	{117,    "存储卡协议请求失败"    },
	{119,    "flashECC校验错"    },
	{120,    "写入发票明细错误"    },
	{121,    "写入Flash错误"    },
	{123,    "无法创建FLASH逻辑表"    },
	{125,    "写FLASH逻辑号错"    },
	{126,    "FLASH芯片损坏"    },
	{129,    "EEPROM地址错误"    },
	{131,    "生产测试读写数据不一致"    },
	{132,    "发票明细有误"    },
	{133,    "开票时发票明细长度错误"    },
	{141,    "底层发票明细数据有误"    },
	{148,    "锁死日日期非法"    },
	{149,    "状态非法不能更改锁死日"    },
	{150,    "税控设备(金税盘、报税盘)认证校验和错"			},
	{151,    "税控设备(金税盘、报税盘)认证税号不匹配"		},
	{152,    "税控设备(金税盘、报税盘)认证时间不匹配"		},
	{153,    "税控设备(金税盘、报税盘)认证随机数不匹配"		},
	{155,    "税控设备(金税盘、报税盘)清卡校验和错"			},
	{156,    "税控设备(金税盘、报税盘)清卡税号不匹配"		},
	{157,    "税控设备(金税盘、报税盘)清卡时间不匹配"		},
	{158,    "税控设备(金税盘、报税盘)清卡随机数不匹配"		},
	{159,    "税控设备(金税盘、报税盘)清卡不匹配"			},
	{160,    "报税盘或金税盘与金税盘不匹配"					},
	{161,    "可开发票最大数量已满"							},
	{167,    "介质类型和操作不匹配"							},
	{176,    "无可用发票"									},
	{181,    "营改增启动时间格式无效"						},
	{182,    "金税盘无新购发卷"								},
	{191,    "需到会计日抄税"								},
	{195,    "未抄税,无汇总资料"							},
	{199,    "该版本非征期不支持远程抄报"					},
	{204,    "税控设备(金税盘、报税盘)上有报税成功标志"		},
	{209,    "税控设备(金税盘、报税盘)上有退卷"				},
	{210,    "没有票种授权"									},
	{219,    "变长发票明细错"								},
	{220,    "检索函数出错；或者检索不到数据"				},
	{222,    "税控设备(金税盘、报税盘)上有新卷,无法抄税"   },
	{223,    "检索不到指定月份领用存信息(若已到会计日,需要抄税后才能查询本月领用存)"    },
	{229,    "标志位数据校验和错"							},
	{231,    "税控设备(金税盘、报税盘)授权错误(没授权)"   },
	{232,    "数据校验和错"									},
	{233,    "授权信息非法"									},
	{234,    "发票明细数据混乱"								},
	{235,    "修改口令长度过长或数据包长度错"				},
	{236,    "管理员登录口令错误"							},
	{237,    "操作员口令错误"								},
	{238,    "操作员锁死"									},
	{239,    "操作权限错误"									},
	{240,    "开票异常掉电造成发票明细混乱"					},
	{241,    "抄税异常掉电造成金税盘数据混乱"				},
	{242,    "发票卷操作异常掉电造成金税盘数据混乱"			},
	{244,    "掉电保护标志区错"								},
	{245,    "有票种多期未抄税或者抄税"		},
	{246,    "到了离线锁死日,上月有已开未上传发票"    },
	{247,    "离线发票总金额超过离线开具限额" },
	{248,    "有票种没有完成征期抄报税"		},
	{249,    "开票时签名密文比对不通过"						},
	{250,    "有离线未上传发票,不允许远程抄报"				},
	{999,    "接入两个或多个报税盘"							},
	{1000,    "未连接报税盘"								},
	{1001,    "没有找到报税盘句柄"							},
	{1002,    "报税盘状态标志异常"							},
	{1005,    "报税盘记录区数据满"							},
	{1006,    "报税盘记录区整理后数据仍满"					},
	{1036,    "报税盘记录区有效数据最大地址越界"			},
	{1179,    "报税盘没有授权信息"							},
	{1050,    "报税盘无退票信息"    },
	{1051,    "报税盘发票区满,已有5卷发票"    },
	{1052,    "报税盘无新卷信息"    },
	{1053,    "报税盘发行数据越界"    },
	{1054,    "报税盘发行记录空"    },
	{1056,    "报税盘未发行"    },
	{1057,    "金税盘和报税盘不匹配"    },
	{1058,    "报税盘操作IC卡错误"    },
	{1059,    "报税盘EPROM错误"    },
	{1060,    "报税盘卡容量错误"    },
	{1061,    "报税盘FLASH初始化出错"    },
	{1084,    "主从报税盘标志错误"    },
	{1085,    "报税盘读清卡信息时无报税成功标志(无清卡信息)"    },
	{1086,    "报税盘已经有抄税资料"    },
	{1087,    "主机金税盘对分机报税盘"    },
	{1088,    "报税盘随机数比对出错"    },
	{1089,    "报税盘握手信息出错,明文税号比对不通过"    },
	{1090,    "主从报税盘标志错误"    },
	{1091,    "主从报税盘标志错误"    },
	{1092,    "报税盘认证时间错误"    },
	{1093,    "报税盘认证税号错误"    },
	{1094,    "报税盘没有明细资料"    },
	{1095,    "报税盘明细已经传完"    },
	{1096,    "报税盘明细编号顺序出错(从1递增)"    },
	{1097,    "明细编号超出总编号"    },
	{1098,    "报税盘校验和错误"    },
	{1101,    "报税盘没检测到存储介质"    },
	{1102,    "报税盘存储介质EDC错"    },
	{1103,    "报税盘存储介质奇偶校验错"    },
	{1104,    "报税盘存储介质链接错"    },
	{1105,    "报税盘存储介质返回数据有误"    },
	{1106,    "报税盘存储介质选择文件错"    },
	{1107,    "报税盘存储介质读操作错"    },
	{1108,    "报税盘存储介质写操作错"    },
	{1109,    "报税盘存储介质校验PIN错"    },
	{1110,    "报税盘存储介质取随机数错"    },
	{1111,    "报税盘存储介质认证错"    },
	{1112,    "报税盘存储介质接收长度错"    },
	{1113,    "报税盘存储介质其他错误"    },
	{1114,    "报税盘存储介质更新密钥错"    },
	{1115,    "报税盘存储介质通信超时"    },
	{1116,    "报税盘存储介质协议类型错"    },
	{1117,    "报税盘存储介质协议请求失败"    },
	{1120,    "报税盘写入发票明细错误"    },
	{1121,    "报税盘写入Flash错误"    },
	{1123,    "报税盘无法创建地址表"    },
	{1124,    "报税盘擦除Flash失败"    },
	{1126,    "报税盘FLASH芯片损坏"							},
	{1128,    "报税盘写eeprom失败"							},
	{1135,    "报税盘ecc error"								},
	{1179,    "报税盘没有授权信息"							},
	{1159,    "报税盘超出已分配地址"						},
	{1160,    "报税盘超出可分配抄税区"						},
	{1255,    "接入两个或多个报税盘"						}	
};

#if PTHREAD_KPMUTEX_OPEN == 1
pthread_mutex_t *g_kpmutex = new pthread_mutex_t;
pthread_mutexattr_t mattr;
int ret = pthread_mutexattr_init(&mattr);
int ret1 = pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_RECURSIVE_NP);
int ret2 = pthread_mutex_init(g_kpmutex, &mattr);
int ret3 = pthread_mutexattr_destroy(&mattr);
//static pthread_mutex_t	g_kpmutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
#endif

//string CJSKInfoFunc::m_cakl = "";
//string CJSKInfoFunc::m_jskNo = "";

string CJSKInfoFunc::m_jqbh = "";
string CJSKInfoFunc::m_jspkl = "";
string CJSKInfoFunc::m_bspkl = "";




//--------------------------------------------------------------------------
//通讯类
//--------------------------------------------------------------------------
CJSKInfoFunc::CJSKInfoFunc()
{	
	
}

CJSKInfoFunc::~CJSKInfoFunc()
{
	
}

void CJSKInfoFunc::JSK_NewBuf(UINT8 **pSendBuf,UINT8 **pRevBuf)
{
	*pSendBuf =new UINT8[MAX_SEND_BUFF_LEN];
	*pRevBuf = new UINT8[MAX_BUFF_LEN];
	
	memset((void *)(*pSendBuf), 0x00, MAX_SEND_BUFF_LEN);
	memset((void *)(*pRevBuf), 0x00,  MAX_BUFF_LEN);
	
	return;
}
void CJSKInfoFunc::JSK_DelBuf(UINT8 *pSendBuf,UINT8 *pRevBuf)
{
	if(NULL != pSendBuf)
	{
		delete[] pSendBuf;
		pSendBuf = NULL;
	}
	if(NULL != pRevBuf)
	{
		delete[] pRevBuf;
		pRevBuf = NULL;
    }
	return;
}
void CJSKInfoFunc::MutexLock(void)
{
#if PTHREAD_KPMUTEX_OPEN == 1
	DBG_ASSERT_EXIT((g_kpmutex != NULL), (" g_kpmutex == NULL!"));
	
	//while (pthread_mutex_trylock(g_kpmutex) == EBUSY)
	while (pthread_mutex_lock(g_kpmutex) != 0)
	{
		DBG_PRINT(("===FPKJ MUTEX LOCK ERROR"));
		//CommonSleep(800);
	}
	DBG_PRINT(("*******************Mutex Lock******************"));
#endif
}


void CJSKInfoFunc::MutexUnlock(void)
{
#if PTHREAD_KPMUTEX_OPEN == 1
	DBG_ASSERT_EXIT((g_kpmutex != NULL), (" g_kpmutex == NULL!"));
	
	int ret = 0;	
	DBG_PRINT(("*******************Mutex Unlock****************"));
	ret = pthread_mutex_unlock(g_kpmutex);
	if (ret != 0)
	{
		DBG_PRINT(("===FPKJ MUTEX UNLOCK %d====", ret));
	}
#endif
}

void CJSKInfoFunc::set_Para(string jqbh, string jspkl, string bspkl)
{
	MutexLock();
	DBG_PRINT(("========set_Para=========="));

	m_jqbh = jqbh;
	m_jspkl = jspkl;
	m_bspkl = bspkl;
	
	MutexUnlock();
}

void CJSKInfoFunc::Find_ErrInfo(INT32 nErrID, string &strErrInfo)
{
	INT8 tmpbuf[128];
	memset((void *)tmpbuf, 0x00, sizeof(tmpbuf));
	
	DBG_PRINT(("nErrID = %d", nErrID));
	
	UINT32 i=0;
	UINT32 nErrNum =sizeof(errInfo)/sizeof(TJSKerrInfo);
	//DBG_PRINT(("nErrNum= %u",nErrNum));
	while(i< nErrNum)
	{
		if (nErrID == errInfo[i].errID)
		{
			sprintf(tmpbuf, "JSK%d:%s", nErrID,errInfo[i].errName);
			strErrInfo =tmpbuf;
			DBG_PRINT(("strErrInfo= %s",strErrInfo.c_str()));
			return;
		}
		i++;
	}
	
   	if (i >= nErrNum)
	{
		sprintf(tmpbuf, "JSK%d:%s", nErrID,"其他错误");
		strErrInfo =tmpbuf;
	}
	
	// 	sprintf(tmpbuf, "JSK_errID:%d", nErrID);
	// 	strErrInfo =tmpbuf;
	// 	DBG_PRINT(("strErrInfo= %s",strErrInfo.c_str()));
	return;
}

INT32 CJSKInfoFunc::JSK_Open_Proc(UINT8 *Code,UINT16 Size,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	ret= jsk_open_r(Code,Size);
	DBG_PRINT(("ret= %d",ret));
	
	return ret;
	// 	if(ret != JSK_SUCCESS)
	// 	{
	// 		Find_ErrInfo(ret,strErr);
	// 		return JSK_FAILURE;
	// 	}
	// 	
	//	return JSK_SUCCESS;
}

INT32 CJSKInfoFunc::JSK_Proc(UINT8 pp1,UINT8 pp2,UINT8 *pInBuf,UINT16 InLen, UINT8 *pOutBuf,UINT16 &OutLen,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	INT32 flag = 0;
	int Size = 0;
	
	MutexLock();
	//临时添加金税盘口令和CA口令
	char chBuf[128];  
	
	if( (pp1==MAKE_INVOICE_FUN) || (pp1==INVOICE_WASTE_FUN) )
	{
		JSK_Close_Proc(strErr);
	}
	
	//如果金穗盘尚未执行open操作,则主动调用open函数
	flag = 0;
	DBG_PRINT(("pp1=0x%02u, pp2= %u, InLen = %u",pp1,pp2, InLen));
	//ret = jsk_operate_r(pp1, pp2 ,( UINT8 *)pJSKSendBuf, InLen, ( UINT8 *)pJSKRevBuf,&OutLen);
	ret = jsk_operate_r(pp1, pp2 ,pInBuf, InLen, pOutBuf,&OutLen);
	DBG_PRINT(("ret= %d, OutLen= %u",ret,OutLen));
	if(ret != JSK_SUCCESS)
	{
		if ((ret == 3001)||(ret == 3065))	//返回3001时需要调用open操作
		{
			JSK_Close_Proc(strErr);
			
			DBG_PRINT(("m_jspkl = %s", m_jspkl.c_str()));
			DBG_PRINT(("m_jqbh = %s", m_jqbh.c_str()));
			
			memset((void *)chBuf,0x00,sizeof(chBuf));
			sprintf(chBuf, "%s", m_jspkl.c_str());
			sprintf(chBuf+JSK_PASSWORD_LEN, "%s", m_jqbh.c_str());
			Size=JSK_PASSWORD_LEN+JSK_MAX_JQBH_LEN;
			DBG_PRINT(("Size = %d", Size));
			
			ret = JSK_Open_Proc((UINT8 *)chBuf,Size,strErr);
			DBG_PRINT(("ret= %d",ret))
				if (ret == JSK_SUCCESS)
				{
					//ret =jsk_operate_r(pp1, pp2, (UINT8 *)pJSKSendBuf, InLen, (UINT8 *)pJSKRevBuf, &OutLen);
					ret = jsk_operate_r(pp1, pp2 ,pInBuf, InLen, pOutBuf,&OutLen);
					DBG_PRINT(("pp1=%u, pp2= %u, InLen = %u, OutLen= %u",pp1,pp2, InLen,OutLen));
					if (ret == JSK_SUCCESS)
					{
						flag = 1;
					}
				}
		}
	}	
	else 
	{
		flag = 1;
	}
	
	MutexUnlock();
	
	if (flag == 0)
	{
		Find_ErrInfo(ret,strErr);
		return JSK_FAILURE;
	}
	else 
	{
		return JSK_SUCCESS;
	}
	
}

INT32 CJSKInfoFunc::JSK_Close_Proc(string &strErr)
{	
	INT32 ret=JSK_SUCCESS;
	ret= jsk_close_r();
	DBG_PRINT(("ret= %d",ret));
	
	// 	if( ret !=JSK_SUCCESS)
	// 	{
	// 		Find_ErrInfo(ret,strErr);
	// 		return JSK_FAILURE;
	// 	}
	
	return JSK_SUCCESS;
}
//----------------------------------------------------------
//功能	：获取纳税户信息
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetCorpInfo(CDataUserInfo *pUserInfo,CDataTax *pTax,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	DBG_ENTER("GetTaxCardInfo");
	
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	//接收数据
	ret =JSK_Proc(GET_CORP_INFO,0,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
    //处理接收数据	
    TaxCardInfo	*pTaxCardInfo = (TaxCardInfo *)pJSKRevBuf;
	
	pUserInfo->m_Nsrmc=(INT8 *)pTaxCardInfo->CorpName;
	DBG_PRINT(("pUserInfo->m_Nsrmc= %s",pUserInfo->m_Nsrmc.c_str()));
	
	INT8 tmpBuf[32];
	memset((void *)tmpBuf,0,sizeof(tmpBuf));
	UINT32 tmpNo =0;
	memcpy((void *)&tmpNo,(void *)pTaxCardInfo->KPNo,2);
    DBG_PRINT(("tmpNo= %u",tmpNo));
	sprintf(tmpBuf,"%u",tmpNo);
	pUserInfo->m_Kpjhm =tmpNo;
	DBG_PRINT(("pUserInfo->m_Kpjhm= %u",pUserInfo->m_Kpjhm));
	
	pUserInfo->m_zfFlag=pTaxCardInfo->zfFlag;
	DBG_PRINT(("pUserInfo->m_zfFlag= %u",pUserInfo->m_zfFlag));
	
    //如果主机 0 ,分机号置为0 ；若为分机1 分机号为分机的数量
	if (0 == pUserInfo->m_zfFlag)
	{
		//	pUserInfo->m_subMachNo = "0";
		pUserInfo->m_Kpjhm = 0;
	}
	DBG_PRINT(("pUserInfo->m_Kpjhm= %u",pUserInfo->m_Kpjhm));
	
	/*纳税人企业性质 数字0表示一般纳税人；数字1表示小规模纳税人*/
	pUserInfo->m_Nsrxz = pTaxCardInfo->CorpPorpertiy;
	DBG_PRINT(("pUserInfo->m_Nsrxz= %u",pUserInfo->m_Nsrxz));
	
    /*行业类型 数字0表示非特定企业；数字1表示特定企业*/
	
	pUserInfo->m_Hylx = pTaxCardInfo->CorpType;
	DBG_PRINT(("pUserInfo->m_Hylx= %u",pUserInfo->m_Hylx));
	
	/*工商登记号*/
	pUserInfo->m_Gsdjh  = (INT8 *)pTaxCardInfo->ResignNo;
	DBG_PRINT(("pUserInfo->m_Gsdjh= %s",pUserInfo->m_Gsdjh.c_str()));
	
	/*开户银行*/
	pUserInfo->m_Khyh= (INT8 *)pTaxCardInfo->DepositBank;
	DBG_PRINT(("pUserInfo->m_Khyh= %s",pUserInfo->m_Khyh.c_str()));
	
    /*开户账号*/
	pUserInfo->m_Khzh = (INT8 *)pTaxCardInfo->DepositAccount;
	DBG_PRINT(("pUserInfo->m_Khzh= %s",pUserInfo->m_Khzh.c_str()));
	
	/*登记注册地址*/
	pUserInfo->m_Djzcdz  = (INT8 *)pTaxCardInfo->ResignAddress;
	DBG_PRINT(("pUserInfo->m_Djzcdz= %s",pUserInfo->m_Djzcdz.c_str()));
	
    /*主管税务机关代码*/
	pUserInfo->m_Swjgdm  = (INT8 *)pTaxCardInfo->TaxAuthorityNo;
	DBG_PRINT(("pUserInfo->m_Swjgdm= %s",pUserInfo->m_Swjgdm.c_str()));
	
    /*主管税务机关名称*/
	pUserInfo->m_Swjgmc  = (INT8 *)pTaxCardInfo->TaxAuthorityName;
	DBG_PRINT(("pUserInfo->m_Swjgmc= %s",pUserInfo->m_Swjgmc.c_str()));
	
	   /* 企业纳税人识别号*/
	pUserInfo->m_Nsrsbh  = (INT8 *)pTaxCardInfo->TaxCode;
	DBG_PRINT(("pUserInfo->m_Nsrsbh= %s",pUserInfo->m_Nsrsbh.c_str()));
	
	/*普票税率授权,第1字节表示授权税率个数,第2字节开始为授权的普票税率*/
	UINT32 taxNum =pTaxCardInfo->AuthTaxRate[0];
	pUserInfo->m_Slgs = taxNum;
	DBG_PRINT(("pUserInfo->m_Slgs= %u",	pUserInfo->m_Slgs));
	if (pUserInfo->m_Slgs >MAX_TAX_NUM)
	{
		strErr="获取授权税率个数超限";
		return JSK_FAILURE;
	}
	UINT32 taxSL=0;
	for (int j=0; j<pUserInfo->m_Slgs; j++)
	{
		/*税率*/
		taxSL=pTaxCardInfo->AuthTaxRate[j+1];
		
		DBG_PRINT(("taxSL= %u",taxSL));
		
		pTax[j].m_sl=(UINT32)(taxSL/10);
        DBG_PRINT(("pTax[%d].m_sl= %u",j,pTax[j].m_sl));	
		
	}
	
	
	/*发票类型, 第1字节表示发票类型个数,第2字节开始为发票类型*/
	UINT32 typeNum =pTaxCardInfo->invName[0];
	pUserInfo->m_Fplxgs = typeNum;
	DBG_PRINT(("pUserInfo->m_Fplxgs= %u",	pUserInfo->m_Fplxgs));
	if (pUserInfo->m_Fplxgs >INVKIND_MAX_NUM)
	{
		strErr="获取发票类型个数超限";
		return JSK_FAILURE;
	}
	UINT32 uFplx=0;
	pUserInfo->m_Fplxsz = "";
	for (int k=0; k<pUserInfo->m_Fplxgs; k++)
	{
		/*发票类型*/
		uFplx=pTaxCardInfo->invName[k+1];
		DBG_PRINT(("uFplx= %u",uFplx));
		
		memset((void *)tmpBuf,0,sizeof(tmpBuf));
		sprintf(tmpBuf,"%u ",uFplx);
        pUserInfo->m_Fplxsz.append(tmpBuf);
		DBG_PRINT(("pUserInfo->m_Fplxsz= %s",pUserInfo->m_Fplxsz.c_str()));	
		
	}
	pUserInfo->m_jqbh = m_jqbh;
	
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;			
}

//----------------------------------------------------------
//功能	：取金税盘号信息
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetJSPNo(UINT8 *JSPNo,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//接收数据
	ret= JSK_Proc(GET_JSP_INFO,0,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret==JSK_SUCCESS)
	{
		memcpy((void *)JSPNo,pJSKRevBuf,nOutLen);
		DBG_PRINT(("JSPNo = %s", JSPNo));
	}
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
}
//----------------------------------------------------------
//功能	：取金税盘号当前时间
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetJSPCurDate(UINT8 *JSPDate,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//接收数据
	ret= JSK_Proc(GET_JSP_INFO,1,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret==JSK_SUCCESS)
	{
		memcpy((void *)JSPDate,pJSKRevBuf,nOutLen);
		DBG_PRINT(("JSPDate = %s", JSPDate));
	}
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
}
//----------------------------------------------------------
//功能	：取金税盘版本号
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetJSPVer(UINT8 *JSPVer,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//接收数据
	ret= JSK_Proc(GET_JSP_INFO,2,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret==JSK_SUCCESS)
	{
		memcpy((void *)JSPVer,pJSKRevBuf,nOutLen);
		DBG_PRINT(("JSPVer = %s", JSPVer));
	}
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
}
//----------------------------------------------------------
//功能	：取金税盘启用时间
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetJSPOpenTime(UINT8 *JSPOTime,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//接收数据
	ret= JSK_Proc(GET_JSP_INFO,3,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret==JSK_SUCCESS)
	{
		memcpy((void *)JSPOTime,pJSKRevBuf,nOutLen);
		DBG_PRINT(("JSPOTime = %s", JSPOTime));	
	}
	
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
}//----------------------------------------------------------
//功能	：获取金税盘数据报送起始时间
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetJSPSendTime(UINT8 *JSPSTime,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//接收数据
	ret= JSK_Proc(GET_JSP_INFO,4,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret==JSK_SUCCESS)
	{
		memcpy((void *)JSPSTime,pJSKRevBuf,nOutLen);
		DBG_PRINT(("JSPSTime = %s", JSPSTime));
		
	}
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
    return ret;			
}

//----------------------------------------------------------
//功能	：取哈希税号和地区编号
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetHashNo(UINT8 *HashNo,UINT8 *AddrNo,string &strErr, UINT8 HashFlag)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//接收数据
	ret= JSK_Proc(GET_JSP_INFO,5,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret!=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	bin2char(pJSKRevBuf,(INT8 *)AddrNo,3);
	DBG_PRINT(("AddrNo = %s", AddrNo));
	
	if(HashFlag == HASH_NO_FLAG_16)
	{
		bin2char(pJSKRevBuf, (INT8 *)HashNo, 8);
	}
	else 
	{
		UINT32 nTmp=0;
		INT8 tmpBuf[32];
		for (int i=0; i<nOutLen;i++)
		{
			memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
			nTmp=hex2int(pJSKRevBuf+i,1);
			sprintf(tmpBuf,"%03u",nTmp);
			memcpy(HashNo+i*3,tmpBuf,3);
		}
	}
	DBG_PRINT(("HashNo = %s", HashNo));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;			
}


//----------------------------------------------------------
//功能	：取发行税号
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetIssueNo(UINT8 *IssueNo,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//接收数据
	ret= JSK_Proc(GET_JSP_INFO,6,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret==JSK_SUCCESS)
	{
		memcpy((void *)IssueNo,pJSKRevBuf,nOutLen);
		DBG_PRINT(("IssueNo = %s", IssueNo));
		
	}
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;		
}
//----------------------------------------------------------
//功能	：获取第一张发票离线发票的发票号码、发票代码和发票索引号
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetFirstOffInvInfo(CDataInvHead *pInvHead,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//接收数据
	ret= JSK_Proc(GET_JSP_INFO,7,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret!=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	INT8 tmpBuf[16];
	
	//处理接收数据
    TFirstOffInvInfo *pFirstOffInv = (TFirstOffInvInfo *)pJSKRevBuf;
	
	//发票代码
	pInvHead->m_fpdm =pFirstOffInv->InvCode;
	DBG_PRINT(("pInvHead->m_fpdm= %s",pInvHead->m_fpdm.c_str()));
	
	//发票号码
	pInvHead->m_fphm =pFirstOffInv->InvNo;
	DBG_PRINT(("pInvHead->m_fphm= %u",pInvHead->m_fphm));
	
	
	//发票索引号
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	sprintf(tmpBuf,"%u",pFirstOffInv->InvIndex);
	pInvHead->m_fpsyh =tmpBuf;
	DBG_PRINT(("pInvHead->m_fpsyh= %s",pInvHead->m_fpsyh.c_str()));
	
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;			
	
}
//----------------------------------------------------------
//功能	：查询金税盘是否有抄税资料
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetJSPCopyFlag(UINT8 &uCopyFlag,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//接收数据
	ret= JSK_Proc(GET_JSP_INFO,8,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret==JSK_SUCCESS)
	{
		uCopyFlag=hex2int(pJSKRevBuf,nOutLen);
		DBG_PRINT(("uCopyFlag = %u", uCopyFlag));
	}
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
}

//----------------------------------------------------------
//功能	：取报税盘号信息
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetBSPNo(UINT8 *BSPNo,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//接收数据
	ret= JSK_Proc(GET_BSP_INFO,0,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret==JSK_SUCCESS)
	{
		memcpy((void *)BSPNo,pJSKRevBuf,nOutLen);
		DBG_PRINT(("BSPNo = %s", BSPNo));
		
	}
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
}

//----------------------------------------------------------
//功能	：获取报税盘企业纳税人识别号
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetBSPNsrsbh(UINT8 *BSPNsrsbh,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//接收数据
	ret= JSK_Proc(GET_BSP_INFO,1,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret==JSK_SUCCESS)
	{
		memcpy((void *)BSPNsrsbh,pJSKRevBuf,nOutLen);
		DBG_PRINT(("BSPNsrsbh = %s", BSPNsrsbh));
		
	}
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
}

//----------------------------------------------------------
//功能	：获取报税盘版本号
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetBSPVer(UINT8 *BSPVer,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//接收数据
	ret= JSK_Proc(GET_BSP_INFO,2,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret==JSK_SUCCESS)
	{
		memcpy((void *)BSPVer,pJSKRevBuf,nOutLen);
		DBG_PRINT(("BSPVer = %s", BSPVer));
		
	}
	
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
}


//----------------------------------------------------------
//功能	：获取报税盘开票机号
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetBSPKpjh(UINT8 *BSPKpjh,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//接收数据
	ret= JSK_Proc(GET_BSP_INFO,3,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret==JSK_SUCCESS)
	{
		memcpy((void *)BSPKpjh,pJSKRevBuf,nOutLen);
		DBG_PRINT(("BSPKpjh = %s", BSPKpjh));
		
	}
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
}

//----------------------------------------------------------
//功能	：获取权限信息
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetOffLimitInfo(CDataInvKind *invKind,UINT32 &invKindNum, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	DBG_ENTER("GetOffLimitInfo");
	//DBG_ASSERT_EXIT(pInvVol != NULL), (" pInvVol == NULL "));
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;

	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	INT8 chValue[16];
	memset((void*)chValue, 0, sizeof(chValue));
	
	//接收数据
    ret =JSK_Proc(GET_OFF_LIMIT_INFO,0,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if(ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	//处理接收数据
	TOffLimintInfo *pOffLimintInfo = (TOffLimintInfo *)pJSKRevBuf;
	
	if (invKindNum < pOffLimintInfo->AuthLimitInfo.invNum)
	{
		strErr="获取票种的条数超限";
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return JSK_FAILURE;
	}
	
	/* 发票类型数*/
    invKindNum =pOffLimintInfo->AuthLimitInfo.invNum;
	DBG_PRINT(("invKindNum= %u",invKindNum));
	for (int i=0; i<invKindNum; i++)
	{
		/*离线锁死日(每月的第几天)*/
		invKind[i].m_Lxssr = pOffLimintInfo->OffLineLockDay;
		DBG_PRINT(("pOffLimintInfo->OffLineLockDay= %u",pOffLimintInfo->OffLineLockDay));
		
		/*离线开票时长(单位小时*/
		invKind[i].m_Lxkjsj = pOffLimintInfo->OffLineInvTime;
		DBG_PRINT(("pOffLimintInfo->OffLineInvTime= %u",pOffLimintInfo->OffLineInvTime));
		
		invKind[i].m_fplx = pOffLimintInfo->AuthLimitInfo.InvSixLimit[i].invName;
		DBG_PRINT(("InvSixLimit[%d].invName= %u",i,pOffLimintInfo->AuthLimitInfo.InvSixLimit[i].invName));
		
		invKind[i].m_maxSign=0;
		memcpy((void *)&invKind[i].m_maxSign,(void *)pOffLimintInfo->AuthLimitInfo.InvSixLimit[i].invLimit,6);
		
		invKind[i].m_maxSum=0;
		memcpy((void *)&invKind[i].m_maxSum,(void *)pOffLimintInfo->AuthLimitInfo.InvSixLimit[i].OffLinePosTotalLimit,6);
		
		DBG_PRINT(("invKind[%d].m_maxSign= %lld",i,invKind[i].m_maxSign));
		DBG_PRINT(("invKind[%d].m_maxSum= %lld",i,invKind[i].m_maxSum));
	}
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;			
}
INT32 CJSKInfoFunc::GetOffLimitInfo(UINT8 fplx, CDataInvKind *invKind,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	DBG_ENTER("GetOffLimitInfo");
	//DBG_ASSERT_EXIT(pInvVol != NULL), (" pInvVol == NULL "));
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	INT8 chValue[16];
	memset((void*)chValue, 0, sizeof(chValue));
	
	//接收数据
    ret =JSK_Proc(GET_OFF_LIMIT_INFO,0,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if(ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	//处理接收数据
	TOffLimintInfo *pOffLimintInfo = (TOffLimintInfo *)pJSKRevBuf;
	
	/* 发票类型数*/
	UINT8 invKindNum =pOffLimintInfo->AuthLimitInfo.invNum;
	DBG_PRINT(("invKindNum= %u",invKindNum));
	int i=0;
	for (i=0; i<invKindNum; i++)
	{
		if(fplx == pOffLimintInfo->AuthLimitInfo.InvSixLimit[i].invName)
		{
			invKind->m_fplx = pOffLimintInfo->AuthLimitInfo.InvSixLimit[i].invName;
			invKind->m_Lxssr = pOffLimintInfo->OffLineLockDay;
			invKind->m_Lxkjsj = pOffLimintInfo->OffLineInvTime;
			invKind->m_maxSign=0;
			memcpy((void *)&invKind->m_maxSign,(void *)pOffLimintInfo->AuthLimitInfo.InvSixLimit[i].invLimit,6);
			
			invKind->m_maxSum=0;
			memcpy((void *)&invKind->m_maxSum,(void *)pOffLimintInfo->AuthLimitInfo.InvSixLimit[i].OffLinePosTotalLimit,6);
			break;
		}
	}
	if(i >= invKindNum)
	{
		invKind->m_fplx = pOffLimintInfo->AuthLimitInfo.InvSixLimit[0].invName;
		invKind->m_Lxssr = pOffLimintInfo->OffLineLockDay;
		invKind->m_Lxkjsj = pOffLimintInfo->OffLineInvTime;
		invKind->m_maxSign=0;
		memcpy((void *)&invKind->m_maxSign,(void *)pOffLimintInfo->AuthLimitInfo.InvSixLimit[0].invLimit,6);
		
		invKind->m_maxSum=0;
		memcpy((void *)&invKind->m_maxSum,(void *)pOffLimintInfo->AuthLimitInfo.InvSixLimit[0].OffLinePosTotalLimit,6);
	}
	
	
	DBG_PRINT(("invKind->m_fplx= %u",invKind->m_fplx));
	DBG_PRINT(("invKind->m_Lxssr= %u",invKind->m_Lxssr));
	DBG_PRINT(("invKind->m_Lxkjsj= %u",invKind->m_Lxkjsj));
	DBG_PRINT(("invKind->m_maxSign= %lld",invKind->m_maxSign));
	DBG_PRINT(("invKind->m_maxSum= %lld",invKind->m_maxSum));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;			
}
//----------------------------------------------------------
//功能	：金税盘口令认证  
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::JSPPassW(UINT8* PassW, string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	memcpy((void *)pJSKSendBuf, (void *)PassW, JSK_PASSWORD_LEN);
	
	//接收数据
	// 	UINT32 nLen =sizeof(ModPassW);
	//	DBG_PRINT(("nLen= %u",nLen));
	ret =JSK_Proc(JSP_PASSWORD_MANAGE,0,pJSKSendBuf,JSK_PASSWORD_LEN,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;	
}
//----------------------------------------------------------
//功能	：金税盘口令更改  
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::JSPModPassW(UINT8* ModPassW, string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	memcpy((void *)pJSKSendBuf, (void *)ModPassW, JSK_PASSWORD_SUM_LEN);
	
	//接收数据
	// 	UINT32 nLen =sizeof(ModPassW);
	//	DBG_PRINT(("nLen= %u",nLen));
	ret =JSK_Proc(JSP_PASSWORD_MANAGE,1,pJSKSendBuf,JSK_PASSWORD_SUM_LEN,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;	
}


//----------------------------------------------------------
//功能	：证书口令更改  
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::ZSPassW(UINT8* ZSPassW, string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	memcpy((void *)pJSKSendBuf, (void *)ZSPassW, JSK_PASSWORD_SUM_LEN);
	
	//接收数据
	// 	UINT32 nLen =sizeof(ModPassW);
	//	DBG_PRINT(("nLen= %u",nLen));
	ret =JSK_Proc(JSP_PASSWORD_MANAGE,2,pJSKSendBuf,JSK_PASSWORD_SUM_LEN,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;	
}

//----------------------------------------------------------
//功能	：报税盘注册
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::BSPRegister(string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//接收数据
	ret= JSK_Proc(BSP_REGISTER,0,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
}


//----------------------------------------------------------
//功能	：修改金税盘时钟 
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::UpdateJSPClock(UINT8* JSPClock, string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	INT8 tmpBuf[32];

	//日期
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Char2Hex((UINT8 *)tmpBuf,(INT8 *)JSPClock,JSK_PASSWORD_LEN);
	for (int i=0; i<JSK_UPDATE_CLOCK;i++)
	{
		DBG_PRINT(("tmpBuf[%d]= 0x%02x",i,tmpBuf[i]));
	}

	memcpy((void *)pJSKSendBuf, (void *)tmpBuf, JSK_PASSWORD_LEN);
	
	//接收数据
	
	ret =JSK_Proc(UPDATE_JSK_CLOCK,0,pJSKSendBuf,JSK_UPDATE_CLOCK,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;	
}
//----------------------------------------------------------
//功能	：更新企业信息 
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::UpdateCorpInfo(UINT8* UpCorpInfo,UINT32 nLen, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	DBG_ENTER("GetCurInvInfo");
	
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	DBG_PRINT(("nLen = %u", nLen));
	memcpy((void *)pJSKSendBuf, (void *)UpCorpInfo,nLen);
	
	//接收数据
	ret =JSK_Proc(UPDATE_CORP_INFO,0,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
	
}


//----------------------------------------------------------
//功能	：读取企业信息  
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::ReadCorpInfo(UINT16 &outLen, UINT8* RCorpInfo, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	DBG_ENTER("GetCurInvInfo");
	
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//接收数据
	ret =JSK_Proc(READ_CORP_INFO,0,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret ==JSK_SUCCESS)
	{
		//处理接收数据
		memcpy((void *)RCorpInfo,pJSKRevBuf,nOutLen);
		outLen = nOutLen;
		return ret;
	}
	
	
    
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
	
}

//----------------------------------------------------------
//功能	：设置发票上传状态
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::SetUpLoadFlag(UINT8 *UpInfo, UINT32 nLen, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	DBG_ENTER("GetCurInvInfo");
	
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	DBG_PRINT(("nLen = %u", nLen));
	
	memcpy((void *)pJSKSendBuf, (void *)UpInfo,nLen);
	
	//接收数据
	ret =JSK_Proc(SET_UPLOAD_FLAG,0,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
}

//----------------------------------------------------------
//功能	：网络抄税信息
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::NetCopyTax(UINT8 Type,UINT8 *StartDate,UINT8 *EndDate,UINT8 *NetTaxInfo,UINT32 &nTaxLen, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	int2hex(pJSKSendBuf,Type,1);
	
	//接收数据
	ret =JSK_Proc(COPY_TAX_FUN,0,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
    DBG_PRINT(("ret= %d",ret));
	if(ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
    DBG_PRINT(("nOutLen= %u",nOutLen));
	
	INT8 tmpBuf[32];
	
	//处理接收数据
    TNetCopyTax	*pNetCopyTax = (TNetCopyTax *)pJSKRevBuf;
	
	//抄送起始日期
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pNetCopyTax->StartDate,tmpBuf,7);
	//DBG_PRINT(("tmpBuf= %s",tmpBuf));
	//StartDate =(UINT8 *)tmpBuf;
	memcpy(StartDate, (UINT8 *)tmpBuf, sizeof(tmpBuf));
	DBG_PRINT(("StartDate= %s",StartDate));
	
	//抄送截至日期
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pNetCopyTax->EndDate,tmpBuf,7);
	//DBG_PRINT(("tmpBuf= %s",tmpBuf));
	//EndDate =(UINT8 *)tmpBuf;
	memcpy(EndDate, (UINT8 *)tmpBuf, sizeof(tmpBuf));
	DBG_PRINT(("EndDate= %s",EndDate));
	
	//抄税汇总信息
	nTaxLen = nOutLen - 14;
    DBG_PRINT(("nTaxLen= %u",nTaxLen));
	//	memcpy((void *)NetTaxInfo,(void *)pNetCopyTax->CopyTax,nTaxLen);
	bin2char(pNetCopyTax->CopyTax, (INT8 *)NetTaxInfo, nTaxLen);
	DBG_PRINT(("NetTaxInfo = %s", NetTaxInfo));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;			
}
INT32 CJSKInfoFunc::NetCopyTaxDate(UINT8 Type,UINT8 *StartDate,UINT8 *EndDate,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	int2hex(pJSKSendBuf,Type,1);
	
	//接收数据
	ret =JSK_Proc(COPY_TAX_FUN,0,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
    DBG_PRINT(("ret= %d",ret));
	if(ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
    DBG_PRINT(("nOutLen= %u",nOutLen));
	
	INT8 tmpBuf[32];
	
	//处理接收数据
    TNetCopyTax	*pNetCopyTax = (TNetCopyTax *)pJSKRevBuf;
	
	//抄送起始日期
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pNetCopyTax->StartDate,tmpBuf,7);
	memcpy(StartDate, (UINT8 *)tmpBuf, sizeof(tmpBuf));
	DBG_PRINT(("StartDate= %s",StartDate));
	
	//抄送截至日期
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pNetCopyTax->EndDate,tmpBuf,7);
	memcpy(EndDate, (UINT8 *)tmpBuf, sizeof(tmpBuf));
	DBG_PRINT(("EndDate= %s",EndDate));
	
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;			
}
//----------------------------------------------------------
//功能	：金税盘抄税信息
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::JSPCopyTax(UINT8 Type,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	int2hex(pJSKSendBuf,Type,1);
	
	//接收数据
	ret =JSK_Proc(COPY_TAX_FUN,1,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
    DBG_PRINT(("ret= %d",ret));
	
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
}

//----------------------------------------------------------
//功能	：报税盘抄税信息
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::BSPCopyTax(UINT8 Type,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	int2hex(pJSKSendBuf,Type,1);
	
	//接收数据
	ret =JSK_Proc(COPY_TAX_FUN,2,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
    DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}

//----------------------------------------------------------
//功能	：网络清卡
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::NetClearCard(UINT8 Type,UINT8 *CCardInfo,UINT32 nInfoLen,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//处理发送数据
	//转换数据结构  pJSKSendBuf
	
	TClearCardInfo *pTCCardInfo = (TClearCardInfo *)pJSKSendBuf;
	
	
	/*票种类别*/
	pTCCardInfo->Type=Type;
	
	/*票种类别*/
	memset(pTCCardInfo->CCardInfo, 0, sizeof(pTCCardInfo->CCardInfo));
	memcpy((void *)pTCCardInfo->CCardInfo, (void *)CCardInfo, nInfoLen);
	//	DBG_PRINT(("pTCCardInfo->CCardInfo= %s",pTCCardInfo->CCardInfo));
	
	
	//接收数据
	UINT32 nLen = nInfoLen+1;
	DBG_PRINT(("nLen= %u",nLen));
	
	ret =JSK_Proc(CLEAR_CARD_FUN,0,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
    DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
	
}

//----------------------------------------------------------
//功能	：报税盘清卡
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::BSPClearCard(UINT8 Type,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	int2hex(pJSKSendBuf,Type,1);
	
	//接收数据
	ret =JSK_Proc(CLEAR_CARD_FUN,1,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
    DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}


//----------------------------------------------------------
//功能	：申请网络购票
//输入	：
//输出	：
//返回值：
//---------------------------------------------------------
INT32 CJSKInfoFunc::AppNetInvVol(UINT8 Type,UINT16 &outLen,UINT8 *NetEmpowData, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;

	UINT8* pJSKSendBuf= NULL;
    UINT8* pJSKRevBuf= NULL;

	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	int2hex(pJSKSendBuf,Type,1);
	//接收数据
	ret= JSK_Proc(GET_NET_INVOL_INFO,1,pJSKSendBuf,1,pJSKRevBuf,nOutLen, strErr);
	DBG_PRINT(("ret= %d",ret));
	if(ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	DBG_PRINT(("nOutLen = %u", nOutLen));
	//处理接收数据
	//   TNetInvVolInfo	*pTNetInvVolInfo = (TNetInvVolInfo *)pJSKRevBuf;
	
	/*网络购票预授权信息(密文)*/
	memcpy((void *)NetEmpowData,(void *)pJSKRevBuf,	nOutLen);
	outLen = nOutLen;
	//	DBG_PRINT(("NetEmpowInfo= %s",NetEmpowInfo));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;	
}
//----------------------------------------------------------
//功能	：网络购票数据读入
//输入	：
//输出	：
//返回值：
//---------------------------------------------------------
INT32 CJSKInfoFunc::ReadNetInvVol(UINT8 Type,UINT8 *NetCrypData,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	memcpy((void *)pJSKSendBuf, (void *)NetCrypData,JSK_NET_CRYP_DATA_LEN);
	
	
	int2hex((UINT8 *)(pJSKSendBuf+JSK_NET_CRYP_DATA_LEN),Type,1);
	
	//发送数据
	UINT32 nLen =JSK_NET_CRYP_DATA_LEN+1;
	DBG_PRINT(("nLen= %u",nLen));
	
	ret= JSK_Proc(GET_NET_INVOL_INFO,2,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
	
}

//----------------------------------------------------------
//功能	：网络购票读入确认申请
//输入	：
//输出	：
//返回值：
//---------------------------------------------------------
INT32 CJSKInfoFunc::App2NetInvVol(UINT8 Type,UINT16 &outLen,UINT8 *NetCrypData,CDataInvVol *pInvVol,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
    int2hex(pJSKSendBuf,Type,1);
	
	//接收数据
	ret= JSK_Proc(GET_NET_INVOL_INFO,3,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if(ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	if(nOutLen <= 0)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return JSK_SUCCESS;
	}
	
	//处理接收数据
	//   TNetInvVolInfo	*pTNetInvVolInfo = (TNetInvVolInfo *)pJSKRevBuf;
	DBG_PRINT(("nOutLen = %u", nOutLen));
	
	//处理接收数据
	TApp2NetInfo *pApp2NetInInfo = (TApp2NetInfo *)pJSKRevBuf;
	
	
	memcpy((void *)NetCrypData,(void *)pApp2NetInInfo->NetInvInfo,	JSK_NET_INV_CON_LEN);
	pInvVol->m_invtype= pApp2NetInInfo->InvType;
	pInvVol->m_fpzfs =pApp2NetInInfo->Count;
	pInvVol->m_isno =pApp2NetInInfo->InvNo;
	pInvVol->m_code =pApp2NetInInfo->InvCode;
	
	outLen = nOutLen;
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;	
}

//----------------------------------------------------------
//功能	：网络购票确认
//输入	：
//输出	：
//返回值：
//---------------------------------------------------------
INT32 CJSKInfoFunc::ConNetInvVol(UINT8 Type, UINT8 *NetCrypData,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//	DBG_PRINT(("NetCrypData = %s", NetCrypData));
	memcpy((void *)pJSKSendBuf, (void *)NetCrypData,JSK_NET_INV_CON_LEN);
	
	int2hex((UINT8 *)(pJSKSendBuf+JSK_NET_INV_CON_LEN),Type,1);
	
	//发送数据
	UINT32 nLen =JSK_NET_INV_CON_LEN+1;
	DBG_PRINT(("nLen= %u",nLen));
	
	ret= JSK_Proc(GET_NET_INVOL_INFO,4,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}
//----------------------------------------------------------
//功能	：从金税盘读入新购发票
//输入	：
//输出	：
//返回值：
//---------------------------------------------------------
INT32 CJSKInfoFunc::JSPGetInvVolInfo(UINT8 Type,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
    int2hex(pJSKSendBuf,Type,1);
	
	//接收数据
	ret =JSK_Proc(GET_NET_INVOL_INFO,5,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
    DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}

//----------------------------------------------------------
//功能	：从报税盘读入新购发票
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::BSPGetInvVolInfo(UINT8 Type,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	int2hex(pJSKSendBuf,Type,1);
	//接收数据
	ret =JSK_Proc(GET_NET_INVOL_INFO,6,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
    DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}


//----------------------------------------------------------
//功能	：主机获取网络票源信息(网络购票) 购票操作
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetJSKInvVolInfo(CDataInvVol *invVol, UINT32 &nInvNum, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	INT8 tmpBuf[64];
	string tmpStr("");
	//DBG_ENTER("GetJSKInvVolInfo");
	//DBG_ASSERT_EXIT(pInvVol != NULL), (" pInvVol == NULL "));
	
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//接收数据
	ret= JSK_Proc(GET_JSK_INVOL_INFO,0,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if(ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	//处理接收数据
    TInvVol	*pTInvVol = (TInvVol *)pJSKRevBuf;
	
	
	DBG_PRINT(("pTInvVol->InvNum = %u",pTInvVol->InvNum));
	DBG_PRINT(("pro_nInvNum= %u",nInvNum));
	
	if (nInvNum < pTInvVol->InvNum)
	{
		strErr="获取的票源条数异常";
		return JSK_FAILURE;
	}
	
	nInvNum =pTInvVol->InvNum;
	DBG_PRINT(("cur_nInvNum= %u",nInvNum));
	for (int i=0; i<nInvNum; i++)
	{
		UINT8 Type;		 /*发票类别*/
		
		DBG_PRINT(("第%d卷发票！",i));
		
		/*发票类别*/
		invVol[i].m_invtype =pTInvVol->InvVolum[i].Type;
		DBG_PRINT(("invVol[%d].m_invtype= %u",i,invVol[i].m_invtype));
		
		/*发票起始号*/
		invVol[i].m_isno =pTInvVol->InvVolum[i].HeadCode;
		DBG_PRINT(("invVol[%d].pri_m_isno= %u",i,invVol[i].m_isno));
		
		/*发票总份数*/
		invVol[i].m_fpzfs =(UINT32)pTInvVol->InvVolum[i].Count;
		DBG_PRINT(("invVol[%d].pri_Count= %u",i,invVol[i].m_fpzfs));
		
		/*发票截至号*/
		invVol[i].m_ieno =pTInvVol->InvVolum[i].HeadCode +pTInvVol->InvVolum[i].Count -1;
		DBG_PRINT(("invVol[%d].pri_m_ieno= %u",i,invVol[i].m_ieno));
		
		/*剩余份数*/
		invVol[i].m_remain =pTInvVol->InvVolum[i].Remain;
		DBG_PRINT(("invVol[%d].m_remain= %u",i,invVol[i].m_remain));
		
		/*可用发票起始号*/
		INT32 nTmp = pTInvVol->InvVolum[i].Count - pTInvVol->InvVolum[i].Remain;
		//	DBG_PRINT(("nTmp= %d",nTmp));
		if (nTmp >0 )
		{
			invVol[i].m_isno += nTmp;
		}
		DBG_PRINT(("invVol[%d].m_isno= %u",i,invVol[i].m_isno));
		
		/*购买日期*/
		memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
		Hex2Char(pTInvVol->InvVolum[i].BuyDate,tmpBuf,7);
		//DBG_PRINT(("tmpBuf= %s",tmpBuf));
		invVol[i].m_buyDate =tmpBuf;
		DBG_PRINT(("invVol[%d].m_buyDate = %s", i,invVol[i].m_buyDate.c_str()));
		if(invVol[i].m_buyDate.length() >= 8)
		{
			tmpStr = invVol[i].m_buyDate.substr(0,8);
			invVol[i].m_date = atoi(tmpStr.c_str());
		}
		
		/*发票代码10或12位ASCII码*/
		invVol[i].m_code =pTInvVol->InvVolum[i].TypeCode;
		DBG_PRINT(("invVol[%d].m_code= %s",i,invVol[i].m_code.c_str()));
	}
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;			
}

//----------------------------------------------------------
//功能	：获取当前发票号
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetCurInvInfo(CDataInvVol *pInvVol,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	DBG_ENTER("GetCurInvInfo");
	
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//接收数据
	ret =JSK_Proc(GET_CUR_INVIOCE_INFO,0,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
    //处理接收数据
	TCurInvInfo *pTCurInv = (TCurInvInfo *)pJSKRevBuf;
	
	pInvVol->m_curInvNo =  pTCurInv->InvNo;
	pInvVol->m_invtype =pTCurInv->Type;
	pInvVol->m_code =pTCurInv->InvCode;
	pInvVol->m_remain =pTCurInv->Remain;
	
	DBG_PRINT(("pInvVol->m_code= %s",pInvVol->m_code.c_str()));
	DBG_PRINT(("pInvVol->m_curInvNo= %u",pInvVol->m_curInvNo));
	DBG_PRINT(("pInvVol->m_invtype= %u",pInvVol->m_invtype));
	DBG_PRINT(("pInvVol->m_remain= %u",pInvVol->m_remain));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;			
}


//----------------------------------------------------------
//功能	：开票(正票,红票,空白作废)
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::MakeInvHandInfo(CDataInvHead *pInvHead, string &strErr)
{
	DBG_ENTER("MakeInvHandInfo");
	DBG_ASSERT_EXIT((pInvHead != NULL), (" pInvHead == NULL "));
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	// CDataInvHead 到 TInvHead 转换
	//pTaxCardInvHead 组装发票信息buf
	INT8 tmpBuf[JSK_MAKE_INV_SIGN_LEN];
	
    TInvHead *pTInvHead = (TInvHead *)pJSKSendBuf;
	
	/*9字节证书口令*/
	memset(pTInvHead->CAPassW, 0, sizeof(pTInvHead->CAPassW));
	memcpy((void *)pTInvHead->CAPassW, (void *)pInvHead->m_zskl.c_str(), JSK_PASSWORD_LEN);
	DBG_PRINT(("pTInvHead->CAPassW= %s",pTInvHead->CAPassW));
	
	
	/*10或12位ASCII码发票代码*/
	memset(pTInvHead->taxCardInvHead.TypeCode, 0, sizeof(pTInvHead->taxCardInvHead.TypeCode));
	memcpy((void *)pTInvHead->taxCardInvHead.TypeCode, (void *)pInvHead->m_fpdm.c_str(), pInvHead->m_fpdm.length());
	DBG_PRINT(("pInvHead->m_fpdm= %s",pInvHead->m_fpdm.c_str()));
	
	/*发票号码*/ 
	pTInvHead->taxCardInvHead.InvNo =pInvHead->m_fphm;
	DBG_PRINT(("pInvHead->m_fphm= %u",pInvHead->m_fphm));
	
	/* 开票日期*/
	Char2Hex((UINT8 *)pTInvHead->taxCardInvHead.Date,pInvHead->m_CurTime.c_str(),7);
	
	/*购方税号*/
	memset(pTInvHead->taxCardInvHead.BuyTaxCode, 0, sizeof(pTInvHead->taxCardInvHead.BuyTaxCode));
	memcpy((void *)pTInvHead->taxCardInvHead.BuyTaxCode, (void *)pInvHead->m_payerCode.c_str(), pInvHead->m_payerCode.length());
	
	
	/*金额*/  
	DBG_PRINT(("pInvHead->m_kpje = %lld", pInvHead->m_kpje));
	memset(pTInvHead->taxCardInvHead.TotalSum, 0, sizeof(pTInvHead->taxCardInvHead.TotalSum));
	sprintf(pTInvHead->taxCardInvHead.TotalSum, "%.2f", ((double) pInvHead->m_kpje)/JSK_SUM_EXTENSION);
#ifdef DEGUG_PRN
	for (int i=0; i<20; i++)
	{
		DBG_PRINT(("pTInvHead->taxCardInvHead.TotalSum[%d]=0x%02x",i,pTInvHead->taxCardInvHead.TotalSum[i]));
	}
#endif
	
	/*税额*/
	DBG_PRINT(("pInvHead->m_kpse = %lld", pInvHead->m_kpse));
	memset(pTInvHead->taxCardInvHead.Tax, 0, sizeof(pTInvHead->taxCardInvHead.Tax));
	sprintf(pTInvHead->taxCardInvHead.Tax, "%.2f", ((double) pInvHead->m_kpse)/JSK_SUM_EXTENSION);
	
	
	/*发票类别*/
	pTInvHead->taxCardInvHead.Type=pInvHead->m_fplb;
	
	/*发票标志*/ 
	pTInvHead->taxCardInvHead.invFlag=pInvHead->m_kplx;
	DBG_PRINT(("pInvHead->m_kplx= %u",pInvHead->m_kplx));
	
	/*负数发票对应的正数发票的代码*/
	memset(pTInvHead->taxCardInvHead.NegToPosTypeCode, 0, sizeof(pTInvHead->taxCardInvHead.NegToPosTypeCode));
	memcpy((void *)pTInvHead->taxCardInvHead.NegToPosTypeCode, (void *)pInvHead->m_yfpdm.c_str(), pInvHead->m_yfpdm.length());
	
	/*负数发票对应的正数发票的号码*/
	pTInvHead->taxCardInvHead.NegToPosInvNo=pInvHead->m_yfphm;
	
	
	memset((void *)JSK_InvBuf,0x00,sizeof(JSK_InvBuf));
    UINT32 tmpInvLen=0;
//	DBG_PRINT(("pTInvHead->taxCardInvHead.DataPtr=0x%02x",pTInvHead->taxCardInvHead.DataPtr));
	DBG_PRINT(("pTInvHead->taxCardInvHead.DataLen= %u",pTInvHead->taxCardInvHead.DataLen));
	MutexLock();
	InvDetail2Data(pInvHead,(UINT8 *)JSK_InvBuf,tmpInvLen);
	MutexUnlock();
//	printf("-------------------\n%s\n--------------------\n",JSK_InvBuf);
	
	pTInvHead->taxCardInvHead.DataPtr =(UINT8 *)JSK_InvBuf;
	pTInvHead->taxCardInvHead.DataLen = tmpInvLen;
    
//	DBG_PRINT(("pTInvHead->taxCardInvHead.DataPtr=0x%02x",pTInvHead->taxCardInvHead.DataPtr));
	DBG_PRINT(("pTInvHead->taxCardInvHead.DataLen= %u",pTInvHead->taxCardInvHead.DataLen));
	
	DBG_PRINT(("tmpInvLen= %u",tmpInvLen));
	
	//接收数据
	UINT32 nLen =sizeof(TInvHead);
	DBG_PRINT(("nLen= %u",nLen));
	
#ifdef DEGUG_PRN
	for (int i=0; i<nLen;i++)
	{
		DBG_PRINT(("pJSKSendBuf[%d]=Ox%x",i,pJSKSendBuf[i]));
	}
#endif
	
	DBG_PRINT(("m_kplx= %u",pInvHead->m_kplx ));
	if (pInvHead->m_kplx ==JSK_WASTE_INV)
	{
		ret =JSK_Proc(MAKE_INVOICE_FUN,1,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	}
	else
	{
		ret =JSK_Proc(MAKE_INVOICE_FUN,0,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	}
	
	DBG_PRINT(("ret= %d",ret));
	if( ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	UINT32 tmpLen=0;
	UINT32 nFiscalLen = 0;
	memcpy((void *)&nFiscalLen,(void *)(pJSKRevBuf+tmpLen),2);
	DBG_PRINT(("nFiscalLen= %u",nFiscalLen));
	tmpLen +=2;
	
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	memcpy((void *)tmpBuf,(void *)(pJSKRevBuf+tmpLen),nFiscalLen);
	
	pInvHead->m_fwm =tmpBuf;
	DBG_PRINT(("pInvHead->m_fwm= %s",pInvHead->m_fwm.c_str()));
	tmpLen +=nFiscalLen;
	
    tmpLen += 1; //分隔符'\0'
	
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char((UINT8 *)(pJSKRevBuf+tmpLen),tmpBuf,4);
	pInvHead->m_fpsyh=tmpBuf;
	
	DBG_PRINT(("pInvHead->m_fpsyh= %s",pInvHead->m_fpsyh.c_str()));
	tmpLen +=4;
	
	UINT32 nSignLen = 0;
	memcpy((void *)&nSignLen,(void *)(pJSKRevBuf+tmpLen),2);
	DBG_PRINT(("nSignLen= %u",nSignLen));
	tmpLen +=2;
	
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	memcpy((void *)tmpBuf,(void *)(pJSKRevBuf+tmpLen),nSignLen);
	
#if CA_SIGN_BASE64 == 1
	Base64_Encode_2((UINT8 *)tmpBuf, nSignLen);
#endif
	pInvHead->m_casign =tmpBuf;
//	DBG_PRINT(("pInvHead->m_casign= %s",pInvHead->m_casign.c_str()));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;			
}

//----------------------------------------------------------
//功能	：已开发票作废
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::WasteInvHandInfo(CDataInvHead *pInvHead,string &strErr)
{
	DBG_ENTER("WasteInvHandInfo");
	//	DBG_ASSERT_EXIT(pInvHead != NULL), (" pInvHead == NULL "));
	
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	// CDataInvHead 到 TaxCardInvCancel 转换
	//pTaxCardInvHead 组装发票信息buf
	INT8 tmpBuf[JSK_MAKE_INV_SIGN_LEN];
	
    TInvCancel *pTInvCancel = (TInvCancel *)pJSKSendBuf;
	
	/*9字节证书口令*/
	memset(pTInvCancel->CAPassW, 0, sizeof(pTInvCancel->CAPassW));
	memcpy((void *)pTInvCancel->CAPassW, (void *)pInvHead->m_zskl.c_str(), JSK_PASSWORD_LEN);
	DBG_PRINT(("pTInvCancel->CAPassW= %s",pTInvCancel->CAPassW));
	
	
	/*10或12位ASCII码发票代码*/
	memset(pTInvCancel->taxCardInvCancel.TypeCode, 0, sizeof(pTInvCancel->taxCardInvCancel.TypeCode));
	memcpy((void *)pTInvCancel->taxCardInvCancel.TypeCode, (void *)pInvHead->m_fpdm.c_str(), pInvHead->m_fpdm.length());
	
	/*发票号码*/ 
	pTInvCancel->taxCardInvCancel.InvNo =pInvHead->m_fphm;
	
	/*发票类型*/
	pTInvCancel->taxCardInvCancel.Type=pInvHead->m_fplb;
	
	
	/*发票标志*/ 
	pTInvCancel->taxCardInvCancel.invFlag=pInvHead->m_kplx;
	
	/*发票索引号*/
	memset(pTInvCancel->taxCardInvCancel.InvAcess, 0, sizeof(pTInvCancel->taxCardInvCancel.InvAcess));
	Char2Hex((UINT8 *)pTInvCancel->taxCardInvCancel.InvAcess,pInvHead->m_fpsyh.c_str(),4);
	
	
	//接收数据
	UINT32 nLen =sizeof(TInvCancel);
	DBG_PRINT(("nLen= %u",nLen));
	
	ret =JSK_Proc(INVOICE_WASTE_FUN,0,pJSKSendBuf,nLen, pJSKRevBuf,nOutLen,strErr);
	
	DBG_PRINT(("ret= %d",ret));
	if( ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	UINT32 tmpLen=0;
	//签名长度
	UINT32 nSignLen = 0;
	memcpy((void *)&nSignLen,(void *)(pJSKRevBuf+tmpLen),2);
	DBG_PRINT(("nSignLen= %u",nSignLen));
	tmpLen +=2;
	
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	memcpy((void *)tmpBuf,(void *)(pJSKRevBuf+tmpLen),nSignLen);
	
#if CA_SIGN_BASE64 == 1
	Base64_Encode_2((UINT8 *)tmpBuf, nSignLen);
#endif
	pInvHead->m_casign =tmpBuf;
//	DBG_PRINT(("pInvHead->m_casign= %s",pInvHead->m_casign.c_str()));
	tmpLen +=nSignLen;
	
	
	//发票索引号
    memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char((UINT8 *)(pJSKRevBuf+tmpLen),tmpBuf,4);
	pInvHead->m_fpsyh=tmpBuf;
	DBG_PRINT(("pInvHead->m_fpsyh= %s",pInvHead->m_fpsyh.c_str()));
	tmpLen +=4;
	
	
	//作废日期
    memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
    Hex2Char((UINT8 *)(pJSKRevBuf+tmpLen),tmpBuf,7);
	pInvHead->m_zfsj = tmpBuf;
	DBG_PRINT(("pInvHead->m_zfsj= %s",pInvHead->m_zfsj.c_str()));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;	
	
}
//----------------------------------------------------------
//功能	：主机分票(给分机报税盘分票)
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::HostToInvBSP(CDataInvVol *pInvVol, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//处理发送数据
	// THostToInv 转换数据结构  pJSKSendBuf
	
	THostToInv *pTHostAllotInv = (THostToInv *)pJSKSendBuf;
	
	/*发票号码*/ 
	pTHostAllotInv->InvNo =pInvVol->m_isno;
	DBG_PRINT(("pTHostAllotInv->InvNo= %u",pTHostAllotInv->InvNo));
	
	   /*char类型的16B发票代码*/
	memset(pTHostAllotInv->InvCode, 0, sizeof(pTHostAllotInv->InvCode));
	memcpy((void *)pTHostAllotInv->InvCode, (void *)pInvVol->m_code.c_str(), pInvVol->m_code.length());
	DBG_PRINT(("THostToInv->InvCode= %s",pTHostAllotInv->InvCode));
	
	/*unsigned short发票张数 */ 
	pTHostAllotInv->InvNum =(UINT16)pInvVol->m_fpzfs;
	DBG_PRINT(("THostToInv->InvNum= %u",pTHostAllotInv->InvNum));
	
	/*发票类型 */
	pTHostAllotInv->InvType =pInvVol->m_invtype;
	DBG_PRINT(("THostToInv->InvType= %u",pTHostAllotInv->InvType));
	
	//接收数据
	UINT32 nLen =sizeof(THostToInv);
	DBG_PRINT(("nLen= %u",nLen));
	
	ret =JSK_Proc(HOST_TO_INVVOL,0,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}

//----------------------------------------------------------
//功能	：主机分票(给分机金税盘分票)
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::HostToInvJSP(CDataInvVol *pInvVol, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//处理发送数据
	// THostToInv 转换数据结构  pJSKSendBuf
	
	THostToInv *pTHostAllotInv = (THostToInv *)pJSKSendBuf;
	
	/*发票号码*/ 
	pTHostAllotInv->InvNo =pInvVol->m_isno;
	DBG_PRINT(("pTHostAllotInv->InvNo= %u",pTHostAllotInv->InvNo));
	
	   /*char类型的16B发票代码*/
	memset(pTHostAllotInv->InvCode, 0, sizeof(pTHostAllotInv->InvCode));
	memcpy((void *)pTHostAllotInv->InvCode, (void *)pInvVol->m_code.c_str(), pInvVol->m_code.length());
	DBG_PRINT(("THostToInv->InvCode= %s",pTHostAllotInv->InvCode));
	
	/*unsigned short发票张数 */ 
	pTHostAllotInv->InvNum =(UINT16)pInvVol->m_fpzfs;
	DBG_PRINT(("THostToInv->InvNum= %u",pTHostAllotInv->InvNum));
	
	/*发票类型 */
	pTHostAllotInv->InvType =pInvVol->m_invtype;
	DBG_PRINT(("THostToInv->InvType= %u",pTHostAllotInv->InvType));
	
	
	//接收数据
	UINT32 nLen =sizeof(THostToInv);
	DBG_PRINT(("nLen= %u",nLen));
	
	ret =JSK_Proc(HOST_TO_INVVOL,1,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}

//----------------------------------------------------------
//功能	：发票报税盘退回(主分机一样)
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::InvVolRetBSP(CDataInvVol *pInvVol, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//处理发送数据
	// TInvRetInfo 转换数据结构  pJSKSendBuf
	
	TInvRetInfo *pTInvRetInfo = (TInvRetInfo *)pJSKSendBuf;
	
	/*发票号码*/ 
	pTInvRetInfo->InvNo =pInvVol->m_isno;
	DBG_PRINT(("pTInvRetInfo->InvNo= %u",pTInvRetInfo->InvNo));
	
	   /*char类型的16B发票代码*/
	memset(pTInvRetInfo->InvCode, 0, sizeof(pTInvRetInfo->InvCode));
	memcpy((void *)pTInvRetInfo->InvCode, (void *)pInvVol->m_code.c_str(), pInvVol->m_code.length());
	DBG_PRINT(("pTInvRetInfo->InvCode= %s",pTInvRetInfo->InvCode));
	
	/*unsigned short发票张数 */ 
	pTInvRetInfo->InvNum =(UINT16)pInvVol->m_fpzfs;
	DBG_PRINT(("pTInvRetInfo->InvNum= %u",pTInvRetInfo->InvNum));
	
	/*发票类型 */
	pTInvRetInfo->InvType =pInvVol->m_invtype;
	DBG_PRINT(("pTInvRetInfo->InvType= %u",pTInvRetInfo->InvType));
	
	
	//接收数据
	UINT32 nLen =sizeof(TInvRetInfo);
	DBG_PRINT(("nLen= %u",nLen));
	
	ret =JSK_Proc(INVVOL_RET_INFO,0,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}

//----------------------------------------------------------
//功能	：发票金税盘退回(主分机一样)
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::InvVolRetJSP(CDataInvVol *pInvVol, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//处理发送数据
	// TInvRetInfo 转换数据结构  pJSKSendBuf
	
	TInvRetInfo *pTInvRetInfo = (TInvRetInfo *)pJSKSendBuf;
	
	/*发票号码*/ 
	pTInvRetInfo->InvNo =pInvVol->m_isno;
	DBG_PRINT(("pTInvRetInfo->InvNo= %u",pTInvRetInfo->InvNo));
	
	   /*char类型的16B发票代码*/
	memset(pTInvRetInfo->InvCode, 0, sizeof(pTInvRetInfo->InvCode));
	memcpy((void *)pTInvRetInfo->InvCode, (void *)pInvVol->m_code.c_str(), pInvVol->m_code.length());
	DBG_PRINT(("pTInvRetInfo->InvCode= %s",pTInvRetInfo->InvCode));
	
	/*unsigned short发票张数 */ 
	pTInvRetInfo->InvNum =(UINT16)pInvVol->m_fpzfs;
	DBG_PRINT(("pTInvRetInfo->InvNum= %u",pTInvRetInfo->InvNum));
	
	/*发票类型 */
	pTInvRetInfo->InvType =pInvVol->m_invtype;
	DBG_PRINT(("pTInvRetInfo->InvType= %u",pTInvRetInfo->InvType));
	
	//接收数据
	UINT32 nLen =sizeof(TInvRetInfo);
	DBG_PRINT(("nLen= %u",nLen));
	
	ret =JSK_Proc(INVVOL_RET_INFO,1,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
				
}

//----------------------------------------------------------
//功能	：主机读入分机报税盘退回发票
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::HostGetInvBSP(UINT8 Type,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	/*发票类型 */
	int2hex(pJSKSendBuf,Type,1);
	
	ret =JSK_Proc(HOST_GET_INVVOL,0,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}

//----------------------------------------------------------
//功能	：主机读入分机金税盘退回发票
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::HostGetInvJSP(UINT8 Type,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	int2hex(pJSKSendBuf,Type,1);
	
	ret =JSK_Proc(HOST_GET_INVVOL,1,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
				
}
//----------------------------------------------------------
//功能	：锁死日期
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetLockDate(UINT8 Type,UINT8 *pLockDate,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	int2hex(pJSKSendBuf,Type,1);
	
	ret =JSK_Proc(GET_LOCK_DATE,0,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret ==JSK_SUCCESS)
	{
		DBG_PRINT(("nOutLen= %u",nOutLen));
		memcpy((void *)pLockDate,pJSKRevBuf,nOutLen);
		DBG_PRINT(("pLockDate= %s",pLockDate));
	}
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
	
}
//----------------------------------------------------------
//功能	：通过发票代码,发票号码和索引号查询发票信息
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------

INT32 CJSKInfoFunc::GetInvDetailInfoNO(CDataInvHead *pInvHead,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	TQueryInfo *pQueryInfo = (TQueryInfo *)pJSKSendBuf;
	
	INT8 tmpBuf[32];
	
	/*发票号码*/ 
	pQueryInfo->InvNo =pInvHead->m_fphm;
	DBG_PRINT(("pQueryInfo->InvNo = %u",pQueryInfo->InvNo ));
	
	/*10或12位ASCII码发票代码*/
	memset(pQueryInfo->InvCode, 0, sizeof(pQueryInfo->InvCode));
	memcpy((void *)pQueryInfo->InvCode, (void *)pInvHead->m_fpdm.c_str(), pInvHead->m_fpdm.length());
	DBG_PRINT(("pQueryInfo->InvCode = %s",pQueryInfo->InvCode ));
	
	/*发票索引号*/ 
	
	if (pInvHead->m_fpsyh =="")
	{
		memset((void *)tmpBuf,0xFF,sizeof(tmpBuf));
		memcpy((void *)pQueryInfo->InvIndex,(void *)tmpBuf,4);
	}
	else
	{
		Char2Hex(pQueryInfo->InvIndex,pInvHead->m_fpsyh.c_str(),4);
	}
	
	UINT16 nLen =sizeof(TQueryInfo);
	ret =JSK_Proc(GET_INVIOCE_INFO,0,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	
	//处理接收数据
    TInvDetail *pInvDetail = (TInvDetail *)pJSKRevBuf;
	
#ifdef DEGUG_PRN
	DBG_PRINT(("接收数据"));
	for (int i=0; i<nOutLen;i++)
	{
		DBG_PRINT(("pJSKRevBuf[%d]=Ox%x",i,pJSKRevBuf[i]));
	}
#endif
	
    /*10或12位ASCII码发票代码*/
	pInvHead->m_fpdm =pInvDetail->TypeCode;
	DBG_PRINT(("pInvHead->m_fpdm= %s",pInvHead->m_fpdm.c_str()));
	
    /*发票号码*/ 
    pInvHead->m_fphm =pInvDetail->InvNo;
	DBG_PRINT(("pInvHead->m_fpdm= %u",pInvHead->m_fphm));
	
	/* 开票日期*/
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pInvDetail->Date,tmpBuf,7);
	//DBG_PRINT(("tmpBuf= %s",tmpBuf));
	pInvHead->m_CurTime= tmpBuf;
	DBG_PRINT(("pInvHead->m_CurTime=%s",pInvHead->m_CurTime.c_str()));
	pInvHead->m_kprq = atoi((pInvHead->m_CurTime.substr(0, 8)).c_str());
	pInvHead->m_kpsj = atoi((pInvHead->m_CurTime.substr(8, 6)).c_str());
	DBG_PRINT(("pInvHead->m_kprq= %u",pInvHead->m_kprq));
	DBG_PRINT(("pInvHead->m_kpsj= %u",pInvHead->m_kpsj));
	
    /*购方税号*/
	pInvHead->m_payerCode= pInvDetail->BuyTaxCode;
	
    /*金额,不含税额*/ 
	pInvHead->m_kpje = double2int(atof(pInvDetail->TotalSum) * JSK_SUM_EXTENSION);
	DBG_PRINT(("pInvHead->m_kpje= %lld",pInvHead->m_kpje));
	
	/*税额*/
	pInvHead->m_kpse = double2int(atof(pInvDetail->Tax) * JSK_SUM_EXTENSION);
	DBG_PRINT(("pInvHead->m_kpse= %lld",pInvHead->m_kpse));
	
	/*发票类型*/
	pInvHead->m_fplb =pInvDetail->Type;
	DBG_PRINT(("pInvHead->m_fplb= %u",pInvHead->m_fplb));
	
	/*发票标志：正数、负数、正废、负废、空白废*/
    pInvHead->m_kplx =pInvDetail->invFlag;
	DBG_PRINT(("pInvHead->m_kplx= %u",pInvHead->m_kplx));
	if( (pInvHead->m_kplx==JSK_WASTE_NOR) || (pInvHead->m_kplx==JSK_WASTE_RET) )
	{
		pInvHead->m_zfsj = pInvHead->m_CurTime;
	}
	
	//unsigned int DataLen;  /*发票数据长度*/
	//unsigned char *DataPtr; /*发票数据明细*/
	
	memset((void *)JSK_InvBuf,0x00,sizeof(JSK_InvBuf));
	
	
//	DBG_PRINT(("pInvDetail->DataPtr= 0x%02x",pInvDetail->DataPtr));
	DBG_PRINT(("pInvDetail->DataLen= %u",pInvDetail->DataLen));
	
	memcpy((void *)JSK_InvBuf,(void *)pInvDetail->DataPtr,pInvDetail->DataLen);
//	printf("-------------------\n%s\n--------------------\n",JSK_InvBuf);
	
	MutexLock();
	Data2InvDetail(JSK_InvBuf,pInvHead);
	MutexUnlock();
	
	/*签名数据*/
	INT8 signBuf[JSK_MAKE_INV_SIGN_LEN];
	memset(signBuf, 0, sizeof(signBuf));
	memcpy(signBuf, (INT8 *)pInvDetail->SignPtr, pInvDetail->SignLen);
#if CA_SIGN_BASE64 == 1
	Base64_Encode_2((UINT8 *)signBuf, pInvDetail->SignLen);
#endif
	pInvHead->m_casign=signBuf;
//	DBG_PRINT(("pInvHead->m_casign= %s",pInvHead->m_casign.c_str()));
	
	
	/*20位校验码 */
	pInvHead->m_fwm =pInvDetail->CheckCode;
	DBG_PRINT(("pInvHead->m_fwm= %s",pInvHead->m_fwm.c_str()));
	
	/*发票索引号 */ 
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pInvDetail->Adress,tmpBuf,4);
	pInvHead->m_fpsyh=tmpBuf;
	DBG_PRINT(("pInvHead->m_fpsyh= %s",pInvHead->m_fpsyh.c_str()));
	
	
	/*发票上传标志：1-已上传；0-未上传*/
    pInvHead->m_scbz =pInvDetail->UpFlag;
	DBG_PRINT(("pInvHead->m_scbz= %u",pInvHead->m_scbz));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;	
}

INT32 CJSKInfoFunc::GetInvDetailInfoNO(CDataInvHead *pInvHead, UINT8 *invBuff, UINT32 &invLen, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	TQueryInfo *pQueryInfo = (TQueryInfo *)pJSKSendBuf;
	
	INT8 tmpBuf[32];
	
	/*发票号码*/ 
	pQueryInfo->InvNo =pInvHead->m_fphm;
	DBG_PRINT(("pQueryInfo->InvNo = %u",pQueryInfo->InvNo ));
	
	/*10或12位ASCII码发票代码*/
	memset(pQueryInfo->InvCode, 0, sizeof(pQueryInfo->InvCode));
	memcpy((void *)pQueryInfo->InvCode, (void *)pInvHead->m_fpdm.c_str(), pInvHead->m_fpdm.length());
	DBG_PRINT(("pQueryInfo->InvCode = %s",pQueryInfo->InvCode ));
	
	/*发票索引号*/ 
	
	if (pInvHead->m_fpsyh =="")
	{
		memset((void *)tmpBuf,0xFF,sizeof(tmpBuf));
		memcpy((void *)pQueryInfo->InvIndex,(void *)tmpBuf,4);
	}
	else
	{
		Char2Hex(pQueryInfo->InvIndex,pInvHead->m_fpsyh.c_str(),4);
	}
	
	
	UINT16 nLen =sizeof(TQueryInfo);
	
	ret =JSK_Proc(GET_INVIOCE_INFO,0,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	
	//处理接收数据
    TInvDetail *pInvDetail = (TInvDetail *)pJSKRevBuf;
	
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pInvDetail->Date,tmpBuf,7);
	pInvHead->m_CurTime= tmpBuf;
	DBG_PRINT(("pInvHead->m_CurTime=%s",pInvHead->m_CurTime.c_str()));
	pInvHead->m_kprq = atoi((pInvHead->m_CurTime.substr(0, 8)).c_str());
	pInvHead->m_kpsj = atoi((pInvHead->m_CurTime.substr(8, 6)).c_str());
	DBG_PRINT(("pInvHead->m_kprq= %u",pInvHead->m_kprq));
	DBG_PRINT(("pInvHead->m_kpsj= %u",pInvHead->m_kpsj));
	
	/*发票类型*/
	pInvHead->m_fplb =pInvDetail->Type;
	DBG_PRINT(("pInvHead->m_fplb= %u",pInvHead->m_fplb));
	
	/*发票标志：正数、负数、正废、负废、空白废*/
    pInvHead->m_kplx =pInvDetail->invFlag;
	DBG_PRINT(("pInvHead->m_kplx= %u",pInvHead->m_kplx));
	if( (pInvHead->m_kplx==JSK_WASTE_NOR) || (pInvHead->m_kplx==JSK_WASTE_RET) || (pInvHead->m_kplx==JSK_WASTE_INV) )
	{
		pInvHead->m_zfsj = pInvHead->m_CurTime;
		DBG_PRINT(("pInvHead->m_zfsj = %s", pInvHead->m_zfsj.c_str()));
	}
	
	invLen = pInvDetail->DataLen;
	memcpy((void *)invBuff,(void *)pInvDetail->DataPtr,pInvDetail->DataLen);
	
	/*签名数据*/
	//	pInvHead->m_casign=(INT8 *)pInvDetail->SignPtr;
	INT8 signBuf[JSK_MAKE_INV_SIGN_LEN];
	memset(signBuf, 0, sizeof(signBuf));
	memcpy(signBuf, (INT8 *)pInvDetail->SignPtr, pInvDetail->SignLen);
#if CA_SIGN_BASE64 == 1
	Base64_Encode_2((UINT8 *)signBuf, pInvDetail->SignLen);
#endif
	pInvHead->m_casign = signBuf;
//	DBG_PRINT(("pInvHead->m_casign= %s",pInvHead->m_casign.c_str()));
	
	
	/*20位校验码 */
	pInvHead->m_fwm =pInvDetail->CheckCode;
	DBG_PRINT(("pInvHead->m_fwm= %s",pInvHead->m_fwm.c_str()));
	
	
	/*发票上传标志：1-已上传；0-未上传*/
    pInvHead->m_scbz =pInvDetail->UpFlag;
	DBG_PRINT(("pInvHead->m_scbz= %u",pInvHead->m_scbz));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;	
}

//----------------------------------------------------------
//功能	：通过年月日期查询发票信息
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------

INT32 CJSKInfoFunc::GetInvDetailInfoDate(UINT8 *chDate,CDataInvHead *pInvHead,UINT8 &uInvFlag,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
    DBG_PRINT(("GetInvDetailInfoDate"));
	
	TDateQueryInfo *pDateQueryInfo = (TDateQueryInfo *)pJSKSendBuf;
	
	
	/*年*/ 
	pDateQueryInfo->InvYear =atoi((INT8 *)chDate)/100;
	DBG_PRINT(("pDateQueryInfo->InvYear = %u",pDateQueryInfo->InvYear));
	
	/*月*/ 
	pDateQueryInfo->InvMonth =atoi((INT8 *)chDate)%100;
	DBG_PRINT(("pDateQueryInfo->InvMonth = %u",pDateQueryInfo->InvMonth));
	
    UINT32 nLen =sizeof(TDateQueryInfo);
	DBG_PRINT(("nLen= %u",nLen));
	
	ret =JSK_Proc(GET_INVIOCE_INFO,1,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	
	INT8 tmpBuf[32];
	//处理接收数据
	memcpy((void *)&uInvFlag,(void *)pJSKRevBuf,1);
	DBG_PRINT(("uInvFalg= %u",uInvFlag));
	
	TInvDetail *pInvDetail = (TInvDetail *)(pJSKRevBuf+1);
	
    /*10或12位ASCII码发票代码*/
	pInvHead->m_fpdm =pInvDetail->TypeCode;
	DBG_PRINT(("pInvHead->m_fpdm= %s",pInvHead->m_fpdm.c_str()));
	
    /*发票号码*/ 
    pInvHead->m_fphm =pInvDetail->InvNo;
	DBG_PRINT(("pInvHead->m_fphm= %u",pInvHead->m_fphm));
	
	/* 开票日期*/
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pInvDetail->Date,tmpBuf,7);
	//DBG_PRINT(("tmpBuf= %s",tmpBuf));
	pInvHead->m_CurTime= tmpBuf;
	DBG_PRINT(("pInvHead->m_CurTime=%s",pInvHead->m_CurTime.c_str()));
	pInvHead->m_kprq = atoi((pInvHead->m_CurTime.substr(0, 8)).c_str());
	pInvHead->m_kpsj = atoi((pInvHead->m_CurTime.substr(8, 6)).c_str());
	DBG_PRINT(("pInvHead->m_kprq= %u",pInvHead->m_kprq));
	DBG_PRINT(("pInvHead->m_kpsj= %u",pInvHead->m_kpsj));
	
    /*购方税号*/
	pInvHead->m_payerCode= pInvDetail->BuyTaxCode;
	
    /*金额,不含税额*/ 
	pInvHead->m_kpje = double2int(atof(pInvDetail->TotalSum) * JSK_SUM_EXTENSION);
	DBG_PRINT(("pInvHead->m_kpje= %lld",pInvHead->m_kpje));
	
	/*税额*/
	pInvHead->m_kpse = double2int(atof(pInvDetail->Tax) * JSK_SUM_EXTENSION);
	DBG_PRINT(("pInvHead->m_kpse= %lld",pInvHead->m_kpse));
	
	/*发票类型*/
	pInvHead->m_fplb =pInvDetail->Type;
	DBG_PRINT(("pInvHead->m_fplb= %u",pInvHead->m_fplb));
	
	/*发票标志：正数、负数、正废、负废、空白废*/
    pInvHead->m_kplx =pInvDetail->invFlag;
	DBG_PRINT(("pInvHead->m_kplx= %u",pInvHead->m_kplx));
	
	//unsigned int DataLen;  /*发票数据长度*/
	//unsigned char *DataPtr; /*发票数据明细*/
    memset((void *)JSK_InvBuf,0x00,sizeof(JSK_InvBuf));
	
	memcpy((void *)JSK_InvBuf,(void *)pInvDetail->DataPtr,pInvDetail->DataLen);
	
	MutexLock();
	Data2InvDetail(JSK_InvBuf,pInvHead);
	MutexUnlock();
	
	/*签名数据*/
	pInvHead->m_casign=(INT8 *)pInvDetail->SignPtr;
//	DBG_PRINT(("pInvHead->m_casign= %s",pInvHead->m_casign.c_str()));
	
	
	/*20位校验码 */
	pInvHead->m_fwm =pInvDetail->CheckCode;
	DBG_PRINT(("pInvHead->m_fwm= %s",pInvHead->m_fwm.c_str()));
	
	/*发票索引号 */ 
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pInvDetail->Adress,tmpBuf,4);
	pInvHead->m_fpsyh=tmpBuf;
	DBG_PRINT(("pInvHead->m_fpsyh= %s",pInvHead->m_fpsyh.c_str()));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;	
}


//----------------------------------------------------------
//功能	：查询月统计数据
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------

INT32 CJSKInfoFunc::GetMonthCountDate(UINT32 iDate,UINT8 FpType,CDataTjxxhz *pTjxxhz,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
    JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
    DBG_PRINT(("GetInvDetailInfoDate"));
	
	UINT16 uInvYear=0, uInvMonth=0;
	
	/*年*/ 
	uInvYear = iDate/100;
	DBG_PRINT(("uInvYear = %u",uInvYear));
	memcpy((void *)pJSKSendBuf,(void *)&uInvYear,2);
	
	/*月*/ 
	uInvMonth = iDate%100;
	DBG_PRINT(("uInvMonth = %u",uInvMonth));
	memcpy((void *)(pJSKSendBuf+2),(void *)&uInvMonth,2);
	
    UINT32 nLen =4;
	DBG_PRINT(("nLen= %u",nLen));
	ret =JSK_Proc(GET_MONTH_COUNT_DATE,0,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	
	DBG_PRINT(("ret= %d",ret));
	if( ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	//处理接收数据
	DBG_PRINT(("接收数据"));
	TSumInvCount *pSumInvCount = (TSumInvCount *)pJSKRevBuf;
	
	UINT8 uTypeNum = pSumInvCount->uTypeNum ;
	DBG_PRINT(("uTypeNum= %u",uTypeNum));
	
	
	for (int i=0;i<uTypeNum;i++)
	{
		DBG_PRINT(("FpType = %u", FpType));
		DBG_PRINT(("pSumInvCount->invCount[%d].Type = %u", i, pSumInvCount->invCount[i].Type));
		if ( FpType==pSumInvCount->invCount[i].Type)
		{
			pTjxxhz->m_Type = pSumInvCount->invCount[i].Type;
			DBG_PRINT(("pTjxxhz[%d].m_Type= %u",i,pTjxxhz->m_Type)) ;/*发票类型*/
			
			pTjxxhz->m_Qckcfs =pSumInvCount->invCount[i].OpenInventory;		 /*期初库存*/
			DBG_PRINT(("pTjxxhz[%d].m_Qckcfsm_OpenInventory= %u",i,pTjxxhz->m_Qckcfs)) ;
			
			pTjxxhz->m_Lgfpfs =pSumInvCount->invCount[i].NewBuy; 			/*本期新购*/ 
			DBG_PRINT(("pTjxxhz[%d].m_Lgfpfs= %u",i,pTjxxhz->m_Lgfpfs));
			
			pTjxxhz->m_Qmkcfs =pSumInvCount->invCount[i].EndInventory; 		/*期末库存*/
			DBG_PRINT(("pTjxxhz[%d].m_Qmkcfs= %u",i,pTjxxhz->m_Qmkcfs));
			
			pTjxxhz->m_Thfpfs =pSumInvCount->invCount[i].ReBack; 				/*本期退回*/
			DBG_PRINT(("pTjxxhz[%d].m_Thfpfs= %u",i,pTjxxhz->m_Thfpfs)) ;
			
			pTjxxhz->m_Zsfpfs=pSumInvCount->invCount[i].InvNum; 	/*正数发票开具份数*/
			DBG_PRINT(("pTjxxhz[%d].m_Zsfpfs= %u",i,pTjxxhz->m_Zsfpfs)) ;
			
			pTjxxhz->m_Zffpfs =pSumInvCount->invCount[i].InvCancelNum; /*正数发票作废份数*/
			DBG_PRINT(("pTjxxhz[%d].m_Zffpfs= %u",i,pTjxxhz->m_Zffpfs)) ;
			
			pTjxxhz->m_Fsfpfs =pSumInvCount->invCount[i].NegInvNum; /*负数发票开具份数*/
			DBG_PRINT(("pTjxxhz[%d].m_Fsfpfs= %u",i,pTjxxhz->m_Fsfpfs)) ;
			
			pTjxxhz->m_Fffpfs=pSumInvCount->invCount[i].NegInvCancelNum;/*负数发票作废份数*/
			DBG_PRINT(("pTjxxhz[%d].m_Fffpfs= %u",i,pTjxxhz->m_Fffpfs)) ;
			
			pTjxxhz->m_Zsfpljje = double2int(atof(pSumInvCount->invCount[i].InvSum)*JSK_SUM_EXTENSION);
			DBG_PRINT(("pTjxxhz[%d].m_Zsfpljje  = %lld", i,pTjxxhz->m_Zsfpljje));		
			
			
			pTjxxhz->m_Zsfpljse = double2int(atof(pSumInvCount->invCount[i].InvTax)*JSK_SUM_EXTENSION);
			DBG_PRINT(("pTjxxhz[%d].m_Zsfpljse  = %lld", i,pTjxxhz->m_Zsfpljse));
			
			pTjxxhz->m_Fsfpljje = double2int(atof(pSumInvCount->invCount[i].NegInvSum)*JSK_SUM_EXTENSION);
			DBG_PRINT(("pTjxxhz[%d].m_Fsfpljje  = %lld", i,pTjxxhz->m_Fsfpljje));
			
			pTjxxhz->m_Fsfpljse = double2int(atof(pSumInvCount->invCount[i].NegInvTax)*JSK_SUM_EXTENSION);/*负数发票累计税额*/	
			DBG_PRINT(("pTjxxhz[%d].m_Fsfpljse  = %lld", i,pTjxxhz->m_Fsfpljse));
			
			break;
		}			
	}
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;	
}

//----------------------------------------------------------
//功能	：发票数据转换金税盘中发票明细数据
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
void CJSKInfoFunc::InvDetail2Data(CDataInvHead *pInvHead, UINT8 *pDataPtr,UINT32 &nDataLen)
{
	UINT8 i = 0;
	UINT8 j = 0;
	INT32 tmpLen = 0;
	
	INT8 tmpBuf[512];
	UINT32 outLen=0;
	
	//	1-发票种类\n 
	*(pDataPtr+tmpLen) = INVKIND_NAME;
	tmpLen += NEWLINE_LEN;
	
    memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	DBG_PRINT(("tmpLen= %u",tmpLen));
	
	DBG_PRINT(("pInvHead->m_fpdm= %s",pInvHead->m_fpdm.c_str()));
	//2-类别代码\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_fpdm.c_str(),pInvHead->m_fpdm.length());
	tmpLen +=pInvHead->m_fpdm.length();
	DBG_PRINT(("tmpLen= %d",tmpLen));
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//3-发票号码
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
    sprintf(tmpBuf, "%08u", pInvHead->m_fphm);
    memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf, strlen(tmpBuf));
	tmpLen += strlen(tmpBuf);
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	
	//4-金税卡日期\n 
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	sprintf(tmpBuf, "%u", pInvHead->m_kprq);
	memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf, strlen(tmpBuf));
	tmpLen +=strlen(tmpBuf);
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	
	//5-购方名称\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_fkdw.c_str(),pInvHead->m_fkdw.length());
	tmpLen +=pInvHead->m_fkdw.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//6-购方税号\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_payerCode.c_str(),pInvHead->m_payerCode.length());
	tmpLen +=pInvHead->m_payerCode.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//7-购方地址电话\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_gfdzdh.c_str(),pInvHead->m_gfdzdh.length());
	tmpLen +=pInvHead->m_gfdzdh.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//8-购方银行账号\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_gfyhzh.c_str(),pInvHead->m_gfyhzh.length());
	tmpLen +=pInvHead->m_gfyhzh.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//9-机器编号\n 
	// 	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_jqbh.c_str(),pInvHead->m_jqbh.length());
	// 	tmpLen +=pInvHead->m_jqbh.length();
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_sksbbh.c_str(),pInvHead->m_sksbbh.length());
	tmpLen +=pInvHead->m_sksbbh.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//10-主要商品名称\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_zyspmc.c_str(),pInvHead->m_zyspmc.length());
	tmpLen +=pInvHead->m_zyspmc.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//11-报税期\n 
	if(pInvHead->m_kplx == JSK_RETURN_INV)
	{
		memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
		sprintf(tmpBuf, "0@%s@%08u", pInvHead->m_yfpdm.c_str(), pInvHead->m_yfphm);
		memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf, strlen(tmpBuf));
		tmpLen += strlen(tmpBuf);
	}
	else
	{
		memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_bsq.c_str(),pInvHead->m_bsq.length());
		tmpLen +=pInvHead->m_bsq.length();
	}
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//12-销方名称\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_xfmc.c_str(),pInvHead->m_xfmc.length());
	tmpLen +=pInvHead->m_xfmc.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	
	//13-销方税号\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_xfsh.c_str(),pInvHead->m_xfsh.length());
	tmpLen +=pInvHead->m_xfsh.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	
	//14-销方地址电话\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_xfdzdh.c_str(),pInvHead->m_xfdzdh.length());
	tmpLen +=pInvHead->m_xfdzdh.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//15-销方银行账号\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_xfyhzh.c_str(),pInvHead->m_xfyhzh.length());
	tmpLen +=pInvHead->m_xfyhzh.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//16-开票人\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_sky.c_str(),pInvHead->m_sky.length());
	tmpLen +=pInvHead->m_sky.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	
	//17-复核人\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_fhr.c_str(),pInvHead->m_fhr.length());
	tmpLen +=pInvHead->m_fhr.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//18-收款人\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_sky.c_str(),pInvHead->m_sky.length());
	tmpLen +=pInvHead->m_sky.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//19-备注(Base64编码)\n 
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	memcpy((void *)tmpBuf,(void *)(pInvHead->m_backup1.c_str()), pInvHead->m_backup1.length());
	Base64_Encode_2((UINT8 *)tmpBuf, strlen(tmpBuf));
	memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf,strlen(tmpBuf));
	tmpLen +=strlen(tmpBuf);
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	
	if( (pInvHead->m_kplx == JSK_RETURN_INV) || (pInvHead->m_kplx == JSK_WASTE_RET) )
	{
		//20-合计金额\n 
		DBG_PRINT(("pInvHead->m_kpje= %lld",pInvHead->m_kpje));
		memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
		sprintf(tmpBuf, "-%.2f", ((double)pInvHead->m_kpje)/JSK_SUM_EXTENSION);
		memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf, strlen(tmpBuf));
		tmpLen += strlen(tmpBuf);
		
		memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
		tmpLen +=NEWLINE_LEN;
		
		
		//21-合计税额\n 
		DBG_PRINT(("pInvHead->m_kpse= %lld",pInvHead->m_kpse));
		memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
		if (pInvHead->m_kpse ==0)
		{
			sprintf(tmpBuf, "%.2f", ((double)pInvHead->m_kpse)/JSK_SUM_EXTENSION);
		}
		else
		{
			sprintf(tmpBuf, "-%.2f", ((double)pInvHead->m_kpse)/JSK_SUM_EXTENSION);
		}
		memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf, strlen(tmpBuf));
		tmpLen += strlen(tmpBuf);
	}
	else
	{
		//20-合计金额\n 
		DBG_PRINT(("pInvHead->m_kpje= %lld",pInvHead->m_kpje));
		memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
		sprintf(tmpBuf, "%.2f", ((double)pInvHead->m_kpje)/JSK_SUM_EXTENSION);
		memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf, strlen(tmpBuf));
		tmpLen += strlen(tmpBuf);
		
		memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
		tmpLen +=NEWLINE_LEN;
		
		
		//21-合计税额\n 
		DBG_PRINT(("pInvHead->m_kpse= %lld",pInvHead->m_kpse));
		memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
		sprintf(tmpBuf, "%.2f", ((double)pInvHead->m_kpse)/JSK_SUM_EXTENSION);
		memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf, strlen(tmpBuf));
		tmpLen += strlen(tmpBuf);
	}
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//22-清单标志("Y"或"N")\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_qdbz.c_str(),pInvHead->m_qdbz.length());
	tmpLen +=pInvHead->m_qdbz.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//发票明细和清单行格式 
	//商品名称(92)+ 规格型号(40)+ 计量单位(22)+ 数量(精度18,宽度21)+ 单价(精度18,宽度21)+ 金额(保留2位小数,宽度18)+ 税率(6)+ 税额(保留2位小数,宽度18)+ 序号(8)+ 发票行性质(3)+ 含税价标志(3)

	vector<CDataInvDet>::iterator pTempDep;
	for (pTempDep=pInvHead->m_gvector.begin(); pTempDep!=pInvHead->m_gvector.end(); ++pTempDep)
	{
		//商品名称(92)
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPMC_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)pTempDep->m_spmc.c_str(), pTempDep->m_spmc.length());
		tmpLen += JSK_SPMC_LEN;
		//tmpLen +=  pTempDep->m_spmc.length();
		
		//+ 规格型号(40)
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_GGXH_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)pTempDep->m_ggxh.c_str(), pTempDep->m_ggxh.length());
		tmpLen += JSK_GGXH_LEN;
		
		//计量单位(22)
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_JLDW_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)pTempDep->m_spdw.c_str(), pTempDep->m_spdw.length());
		tmpLen += JSK_JLDW_LEN;
        
		if( (pInvHead->m_kplx == JSK_RETURN_INV) || (pInvHead->m_kplx == JSK_WASTE_RET) )
		{
			//数量(精度18,宽度21)
			DBG_PRINT(("pTempDep->m_spsl = %.f", pTempDep->m_spsl));
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			if(pTempDep->m_spsl < 0.001)
			{
				sprintf(tmpBuf,"%.3f",pTempDep->m_spsl);
			}
			else
			{
				sprintf(tmpBuf,"-%.3f",pTempDep->m_spsl);
			}
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPSL_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SPSL_LEN;
		}
		else
		{
			//数量(精度18,宽度21)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf,"%.3f",pTempDep->m_spsl);
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPSL_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SPSL_LEN;
		}
		
		//单价(精度18,宽度21)
		memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
		DBG_PRINT(("m_hsbz = %u", pTempDep->m_hsbz));
		if(pTempDep->m_hsbz ==1)
		{
			sprintf(tmpBuf,"%.3f",pTempDep->m_spdj);
		}
		else
		{
			sprintf(tmpBuf,"%.3f",pTempDep->m_dj);
		}
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPDJ_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
		tmpLen += JSK_SPDJ_LEN;
		
		if( (pInvHead->m_kplx == JSK_RETURN_INV) || (pInvHead->m_kplx == JSK_WASTE_RET) )
		{
			//金额(保留2位小数,宽度18)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf, "-%.2f", ((double) pTempDep->m_je)/JSK_SUM_EXTENSION);
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPJE_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SPJE_LEN;
		}
		else
		{
			//金额(保留2位小数,宽度18)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf, "%.2f", ((double) pTempDep->m_je)/JSK_SUM_EXTENSION);
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPJE_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SPJE_LEN;
		}
		
		//税率(6)
		memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
		sprintf(tmpBuf,"%.2f",pTempDep->m_sl);
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SL_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
		tmpLen += JSK_SL_LEN;
		
		if( (pInvHead->m_kplx == JSK_RETURN_INV) || (pInvHead->m_kplx == JSK_WASTE_RET) )
		{
			//税额(保留2位小数,宽度18)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf, "-%.2f", ((double) pTempDep->m_spse)/JSK_SUM_EXTENSION);
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SE_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SE_LEN;
		}
		else
		{
			//税额(保留2位小数,宽度18)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf, "%.2f", ((double) pTempDep->m_spse)/JSK_SUM_EXTENSION);			
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SE_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SE_LEN;
		}
		
		// 序号(8)
		DBG_PRINT(("pTempDep->m_sphxh = %u", pTempDep->m_sphxh));
		memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
		sprintf(tmpBuf,"%u",pTempDep->m_sphxh);
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPXH_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
		tmpLen += JSK_SPXH_LEN;
		
		//发票行性质(3)
		memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
		sprintf(tmpBuf,"%u",pTempDep->m_property);
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_FPXZ_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
		tmpLen += JSK_FPXZ_LEN;
		
		//含税价标志(3)
		memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
		sprintf(tmpBuf,"%u",pTempDep->m_hsbz);
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_HSBZ_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
		tmpLen += JSK_HSBZ_LEN;
	}

/*
	CInvDet *pTempDep = NULL;
	pTempDep = pInvHead->pHead;
	while (pTempDep != NULL)
	{
		//商品名称(92)
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPMC_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)pTempDep->m_spmc.c_str(), pTempDep->m_spmc.length());
		tmpLen += JSK_SPMC_LEN;
		
		//+ 规格型号(40)
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_GGXH_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)pTempDep->m_ggxh.c_str(), pTempDep->m_ggxh.length());
		tmpLen += JSK_GGXH_LEN;
		
		//计量单位(22)
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_JLDW_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)pTempDep->m_spdw.c_str(), pTempDep->m_spdw.length());
		tmpLen += JSK_JLDW_LEN;
        
		if( (pInvHead->m_kplx == JSK_RETURN_INV) || (pInvHead->m_kplx == JSK_WASTE_RET) )
		{
			//数量(精度18,宽度21)
			DBG_PRINT(("pTempDep->m_spsl = %.f", pTempDep->m_spsl));
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			if(pTempDep->m_spsl < 0.001)
			{
				sprintf(tmpBuf,"%.3f",pTempDep->m_spsl);
			}
			else
			{
				sprintf(tmpBuf,"-%.3f",pTempDep->m_spsl);
			}
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPSL_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SPSL_LEN;
		}
		else
		{
			//数量(精度18,宽度21)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf,"%.3f",pTempDep->m_spsl);
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPSL_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SPSL_LEN;
		}
		
		//单价(精度18,宽度21)
		memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
		DBG_PRINT(("m_hsbz = %u", pTempDep->m_hsbz));
		if(pTempDep->m_hsbz ==1)
		{
			sprintf(tmpBuf,"%.3f",pTempDep->m_spdj);
		}
		else
		{
			sprintf(tmpBuf,"%.3f",pTempDep->m_dj);
		}
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPDJ_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
		tmpLen += JSK_SPDJ_LEN;
		
		if( (pInvHead->m_kplx == JSK_RETURN_INV) || (pInvHead->m_kplx == JSK_WASTE_RET) )
		{
			//金额(保留2位小数,宽度18)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf, "-%.2f", ((double) pTempDep->m_je)/JSK_SUM_EXTENSION);
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPJE_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SPJE_LEN;
		}
		else
		{
			//金额(保留2位小数,宽度18)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf, "%.2f", ((double) pTempDep->m_je)/JSK_SUM_EXTENSION);
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPJE_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SPJE_LEN;
		}
		
		//税率(6)
		memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
		sprintf(tmpBuf,"%.2f",pTempDep->m_sl);
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SL_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
		tmpLen += JSK_SL_LEN;
		
		if( (pInvHead->m_kplx == JSK_RETURN_INV) || (pInvHead->m_kplx == JSK_WASTE_RET) )
		{
			//税额(保留2位小数,宽度18)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf, "-%.2f", ((double) pTempDep->m_spse)/JSK_SUM_EXTENSION);
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SE_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SE_LEN;
		}
		else
		{
			//税额(保留2位小数,宽度18)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf, "%.2f", ((double) pTempDep->m_spse)/JSK_SUM_EXTENSION);			
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SE_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SE_LEN;
		}
		
		// 序号(8)
		DBG_PRINT(("pTempDep->m_sphxh = %u", pTempDep->m_sphxh));
		memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
		sprintf(tmpBuf,"%u",pTempDep->m_sphxh);
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPXH_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
		tmpLen += JSK_SPXH_LEN;
		
		//发票行性质(3)
		memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
		sprintf(tmpBuf,"%u",pTempDep->m_property);
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_FPXZ_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
		tmpLen += JSK_FPXZ_LEN;
		
		//含税价标志(3)
		memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
		sprintf(tmpBuf,"%u",pTempDep->m_hsbz);
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_HSBZ_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
		tmpLen += JSK_HSBZ_LEN;
		
		pTempDep = pTempDep->pNext;
		
	}
*/		
	DBG_PRINT(("tmpLen= %u",tmpLen));
	nDataLen =tmpLen;

	return ;
}


//----------------------------------------------------------
//功能	：金税盘中发票明细数据转换发票数据
//输入	：
//输出	：
//返回值：
//----------------------------------------------------------
void CJSKInfoFunc::Data2InvDetail(INT8 *pDataPtr,CDataInvHead *pInvHead, UINT8 flag)
{
	INT8 chBackupBuf[256];
	memset((void*)chBackupBuf, 0, sizeof(chBackupBuf));	
	UINT8 maxLineNum = 23;		//正常从金税盘读取数据解析行数
	if(flag == 1)
		maxLineNum += 9;		//增加发票上传时加入的解析行数
	
	INT8 chBuf[MAX_INV_INFO_LEN];
	memset((void*)chBuf, 0, sizeof(chBuf));	
	
	UINT8 nLine=0;
    UINT32 tmpLen=0;
	
	CTextParse textParse;
	INT32 strflag = 0;
	string tmpStr("");
	textParse.setText(pDataPtr);
	
	do
	{
		tmpStr = "";
		textParse.getSubStrByFlag(tmpStr, NEWLINE_COMMAND);
		nLine++;
		//  		DBG_PRINT(("nLine= %u",nLine));
		//  		DBG_PRINT(("tmpStr= %s",tmpStr.c_str()));
		switch(nLine)
		{
		case 1: //发票种类
			pInvHead->m_fpzl=tmpStr;
			DBG_PRINT(("pInvHead->m_fpzl= %s",pInvHead->m_fpzl.c_str()));
			break;
		case 2: //发票代码
			pInvHead->m_fpdm=tmpStr;
			DBG_PRINT(("pInvHead->m_fpdm= %s",pInvHead->m_fpdm.c_str()));
			break;
		case 3://发票号码
			pInvHead->m_fphm=atoi(tmpStr.c_str());
			DBG_PRINT(("pInvHead->m_fphm= %u",pInvHead->m_fphm));
			break;
		case 4: //金税卡日期
			//pInvHead->m_kprq=atoi(tmpStr.c_str());
			break;
		case 5: //购方名称
			pInvHead->m_fkdw=tmpStr;
			DBG_PRINT(("pInvHead->m_fkdw = %s", pInvHead->m_fkdw.c_str()));
			break;
		case 6: //购方税号
			pInvHead->m_payerCode=tmpStr;
			break;
		case 7: //购方地址电话
			pInvHead->m_gfdzdh=tmpStr;
			break;
		case 8: //购方银行账号
			pInvHead->m_gfyhzh=tmpStr;
			break;
		case 9://机器编号
			pInvHead->m_jqbh=tmpStr;
			break;
		case 10: //主要商品名称
			pInvHead->m_zyspmc=tmpStr;
			break;
		case 11: //报税期
			pInvHead->m_bsq=tmpStr;
			break;	
		case 12: //销方名称
			pInvHead->m_xfmc=tmpStr;
			break;
		case 13: //销方税号
			pInvHead->m_xfsh=tmpStr;
			break;
		case 14: //销方地址电话
			pInvHead->m_xfdzdh=tmpStr;
			break;
		case 15: //销方银行账号
			pInvHead->m_xfyhzh=tmpStr;
			break;
		case 16://开票人
			pInvHead->m_sky=tmpStr;
			break;
		case 17://复核人
			pInvHead->m_fhr=tmpStr;
			break;
		case 18: //收款人
			pInvHead->m_sky=tmpStr;
			break;
		case 19: //备注(Base64编码)
			sprintf(chBackupBuf, "%s", tmpStr.c_str());
			Base64_Decode_2(chBackupBuf, (int *)&tmpLen);
			pInvHead->m_backup1 = (INT8 *)chBackupBuf;
			//DBG_PRINT(("pInvHead->m_backup1 = %s", pInvHead->m_backup1.c_str()));
			break;
		case 20: //合计金额
			pInvHead->m_kpje = double2int(atof(tmpStr.c_str()) * JSK_SUM_EXTENSION);
			DBG_PRINT(("pInvHead->m_kpje = %lld", pInvHead->m_kpje));
			break;
		case 21: //合计税额
			pInvHead->m_kpse=double2int(atof(tmpStr.c_str()) * JSK_SUM_EXTENSION);
			DBG_PRINT(("pInvHead->m_kpse = %lld", pInvHead->m_kpse));
			break;
		case 22: //清单标志("Y"或"N")
			pInvHead->m_qdbz=tmpStr;
			break;
		case 23: //发票明细信息
			sprintf(chBuf, "%s", tmpStr.c_str());
			break;
			
		case 24: //开票日期
			pInvHead->m_kprq=atoi(tmpStr.c_str());
			DBG_PRINT(("pInvHead->m_kprq= %u",pInvHead->m_kprq));
			break;
		case 25: //开票时间
			pInvHead->m_kpsj=atoi(tmpStr.c_str());
			DBG_PRINT(("pInvHead->m_kpsj= %u",pInvHead->m_kpsj));
			break;
		case 26: //发票类型代码
			pInvHead->m_fplb=atoi(tmpStr.c_str());
			DBG_PRINT(("pInvHead->m_fplb= %u",pInvHead->m_fplb));
			break;
		case 27: //发票类型
			pInvHead->m_kplx=atoi(tmpStr.c_str());
			DBG_PRINT(("pInvHead->m_kplx= %u",pInvHead->m_kplx));
			break;
		case 28: //原发票代码
			pInvHead->m_yfpdm=tmpStr.c_str();
			DBG_PRINT(("pInvHead->m_yfpdm= %s",pInvHead->m_yfpdm.c_str()));
			break;
		case 29: //原发票号码
			pInvHead->m_yfphm=atoi(tmpStr.c_str());
			DBG_PRINT(("pInvHead->m_yfphm= %u",pInvHead->m_yfphm));
			break;
		case 30: //防伪码
			pInvHead->m_fwm = tmpStr;
			DBG_PRINT(("pInvHead->m_fwm= %s",pInvHead->m_fwm.c_str()));
			break;
		case 31: //签名
			pInvHead->m_casign = tmpStr;
			//DBG_PRINT(("pInvHead->m_casign= %s",pInvHead->m_casign.c_str()));
			break;
		case 32: //作废时间
			pInvHead->m_zfsj = tmpStr;
			DBG_PRINT(("pInvHead->m_zfsj= %s",pInvHead->m_zfsj.c_str()));
			break;
			
		default:
			break;
		}
	}while (nLine < maxLineNum);
	
	if(pInvHead->m_kplx == JSK_RETURN_INV)
	{
		ParseInvCode(pInvHead->m_bsq, pInvHead->m_yfpdm, pInvHead->m_yfphm);
		DBG_PRINT(("pInvHead->m_yfpdm = %s", pInvHead->m_yfpdm.c_str()));
		DBG_PRINT(("pInvHead->m_yfphm = %u", pInvHead->m_yfphm));
	}
	
	if(flag == 0)
	{
		if(pInvHead->m_kpje < 0)
			pInvHead->m_kpje = 0 - pInvHead->m_kpje;
		if(pInvHead->m_kpse < 0)
			pInvHead->m_kpse = 0 - pInvHead->m_kpse;
	}
	
	pInvHead->m_kphjje = pInvHead->m_kpje + pInvHead->m_kpse;
	DBG_PRINT(("pInvHead->m_kphjje = %lld", pInvHead->m_kphjje));
	
	DBG_PRINT(("nLine= %u",nLine));
	//DBG_PRINT(("chBuf=%s",chBuf));
	
	TFpmxSum	*pFpmxSum = (TFpmxSum *)chBuf;
	
	//发票信息明细
	UINT32 nDtailLen =strlen(chBuf);
	DBG_PRINT(("nDtailLen= %u",nDtailLen));
	int itSize= nDtailLen/sizeof(TFpmx);
	DBG_PRINT(("itSize= %d",itSize));
	pInvHead->m_sphsl =itSize; 
	double tmpdj = 0;

	CDataInvDet *pInvDet, dataInvDet;
	pInvDet = &dataInvDet;
	for (int i=0; i<itSize;i++)
	{
		//发票代码
		pInvDet->m_fpdm = pInvHead->m_fpdm;
		
		//发票号码
        pInvDet->m_fpdm = pInvHead->m_fpdm;
		pInvDet->m_kprq = pInvHead->m_kprq;
		pInvDet->m_kpsj = pInvHead->m_kpsj;
		pInvDet->m_kplx = pInvHead->m_kplx;
		
		//商品名称(92)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Fpmc, JSK_SPMC_LEN);
		ParseData(chBackupBuf);
		pInvDet->m_spmc = chBackupBuf;
		DBG_PRINT(("pInvDet->m_spmc=%s",pInvDet->m_spmc.c_str()));
		
		//规格型号(40)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Ggxh, JSK_GGXH_LEN);
		ParseData(chBackupBuf);
		pInvDet->m_ggxh = chBackupBuf;
		DBG_PRINT(("pInvDet->m_ggxh=%s",pInvDet->m_ggxh.c_str()));
		
		//计量单位(22)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Jldw, JSK_JLDW_LEN);
		ParseData(chBackupBuf);
		pInvDet->m_spdw = chBackupBuf;
		DBG_PRINT(("pInvDet->m_spdw=%s",pInvDet->m_spdw.c_str()));
		
		//数量(精度18,宽度21)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Spsl, JSK_SPSL_LEN);
		pInvDet->m_spsl =atof(chBackupBuf);
		DBG_PRINT(("pInvDet->m_spsl=%.3f",pInvDet->m_spsl));
		
		//单价(精度18,宽度21)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Spdj, JSK_SPDJ_LEN);
		tmpdj =atof(chBackupBuf);
		DBG_PRINT(("tmpdj=%.3f",tmpdj));
		
		//金额(保留2位小数,宽度18)
		pInvDet->m_je = double2int(atof(pFpmxSum->fpmx[i].Spje) * JSK_SUM_EXTENSION);
		DBG_PRINT(("pInvDet->m_je=%lld",pInvDet->m_je));
		
		// 税率(6)
		pInvDet->m_sl =atof(pFpmxSum->fpmx[i].SL);
		DBG_PRINT(("pInvDet->m_sl=%.3f",pInvDet->m_sl));
		
		//税额(保留2位小数,宽度18)
		pInvDet->m_spse = double2int(atof(pFpmxSum->fpmx[i].SE) * JSK_SUM_EXTENSION);
		DBG_PRINT(("pInvDet->m_spse=%lld",pInvDet->m_spse));
		
		//序号(8)
		pInvDet->m_sphxh =atoi(pFpmxSum->fpmx[i].Spxh);
		DBG_PRINT(("pInvDet->m_sphxh=%u",pInvDet->m_sphxh));
		
		//发票行性质(3)
		pInvDet->m_property =atoi(pFpmxSum->fpmx[i].Fpxz);
		DBG_PRINT(("pInvDet->m_property=%u",pInvDet->m_property));
		
		//含税价标志(3)
		pInvDet->m_hsbz = atoi(pFpmxSum->fpmx[i].Hsbz);
		DBG_PRINT(("pInvDet->m_hsbz=%u",pInvDet->m_hsbz));
		
		if(pInvDet->m_hsbz == 1)
		{
			pInvDet->m_spdj = tmpdj;
			INT64 nTmpSl = double2int(pInvDet->m_sl * JSK_SUM_EXTENSION);
			nTmpSl += JSK_SUM_EXTENSION;
			DBG_PRINT(("nTmpSl = %lld", nTmpSl));
			
			INT64 nTmpDj =double2int(tmpdj * JSK_SUM_EXTENSION);
			DBG_PRINT(("nTmpDj = %lld", nTmpDj));
			pInvDet->m_dj = (double)((nTmpDj*1.0) / nTmpSl);
			DBG_PRINT(("pInvDet->m_dj=%.3lf",pInvDet->m_dj));
			nTmpDj = double2int(pInvDet->m_dj*JSK_SUM_EXTENSION);
			DBG_PRINT(("nTmpDj = %lld", nTmpDj));
			pInvDet->m_dj = (double)nTmpDj/JSK_SUM_EXTENSION;
			DBG_PRINT(("pInvDet->m_dj=%.3lf",pInvDet->m_dj));
		}
		else
		{
			pInvDet->m_dj = tmpdj;
			
			INT64 nTmpSl = double2int(pInvDet->m_sl * JSK_SUM_EXTENSION);
			nTmpSl += JSK_SUM_EXTENSION;
			DBG_PRINT(("nTmpSl = %lld", nTmpSl));
			
			INT64 nTmpDj =double2int(tmpdj * JSK_SUM_EXTENSION);
			DBG_PRINT(("nTmpDj = %lld", nTmpDj));
			INT64 nTmpSpdj= nTmpDj * nTmpSl;
			DBG_PRINT(("nTmpSpdj = %lld", nTmpSpdj));
			
			pInvDet->m_spdj = (double)((nTmpSpdj*1.0) / (JSK_SUM_EXTENSION * JSK_SUM_EXTENSION));
			DBG_PRINT(("pInvDet->m_spdj=%.3lf",pInvDet->m_spdj));
		}
		
		if(flag == 0)
		{
			if(pInvDet->m_spsl < 0)
				pInvDet->m_spsl = 0 - pInvDet->m_spsl;
			if(pInvDet->m_je < 0)
				pInvDet->m_je = 0 - pInvDet->m_je;
			if(pInvDet->m_spse < 0)
				pInvDet->m_spse = 0 - pInvDet->m_spse;
		}
		
		pInvDet->m_spje = pInvDet->m_spse + pInvDet->m_je;
		DBG_PRINT(("pInvDet->m_spje=%lld",pInvDet->m_spje));

		pInvHead->m_gvector.push_back(dataInvDet);
	}

/*
	CInvDet *pInvDet = NULL;
	pInvHead->DelList();
	
	for (int i=0; i<itSize;i++)
	{
		pInvDet = pInvDet->GetNewInvDet();
		
		//发票代码
		pInvDet->m_fpdm = pInvHead->m_fpdm;
		
		//发票号码
        pInvDet->m_fpdm = pInvHead->m_fpdm;
		
		//商品名称(92)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Fpmc, JSK_SPMC_LEN);
		ParseData(chBackupBuf);
		pInvDet->m_spmc = chBackupBuf;
		DBG_PRINT(("pInvDet->m_spmc=%s",pInvDet->m_spmc.c_str()));
		
		//规格型号(40)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Ggxh, JSK_GGXH_LEN);
		ParseData(chBackupBuf);
		pInvDet->m_ggxh = chBackupBuf;
		
		//计量单位(22)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Jldw, JSK_JLDW_LEN);
		ParseData(chBackupBuf);
		pInvDet->m_spdw = chBackupBuf;
		
		//数量(精度18,宽度21)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Spsl, JSK_SPSL_LEN);
		pInvDet->m_spsl =atof(chBackupBuf);
		DBG_PRINT(("pInvDet->m_spsl=%.3f",pInvDet->m_spsl));
		
		//单价(精度18,宽度21)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Spdj, JSK_SPDJ_LEN);
		tmpdj =atof(chBackupBuf);
		DBG_PRINT(("tmpdj=%.3f",tmpdj));
		
		//金额(保留2位小数,宽度18)
		pInvDet->m_je = double2int(atof(pFpmxSum->fpmx[i].Spje) * JSK_SUM_EXTENSION);
		DBG_PRINT(("pInvDet->m_je=%lld",pInvDet->m_je));
		
		// 税率(6)
		pInvDet->m_sl =atof(pFpmxSum->fpmx[i].SL);
		DBG_PRINT(("pInvDet->m_sl=%.3f",pInvDet->m_sl));
		
		//税额(保留2位小数,宽度18)
		pInvDet->m_spse = double2int(atof(pFpmxSum->fpmx[i].SE) * JSK_SUM_EXTENSION);
		DBG_PRINT(("pInvDet->m_spse=%lld",pInvDet->m_spse));
		
		//序号(8)
		pInvDet->m_sphxh =atoi(pFpmxSum->fpmx[i].Spxh);
		DBG_PRINT(("pInvDet->m_sphxh=%u",pInvDet->m_sphxh));
		
		//发票行性质(3)
		pInvDet->m_property =atoi(pFpmxSum->fpmx[i].Fpxz);
		DBG_PRINT(("pInvDet->m_property=%u",pInvDet->m_property));
		
		//含税价标志(3)
		pInvDet->m_hsbz = atoi(pFpmxSum->fpmx[i].Hsbz);
		DBG_PRINT(("pInvDet->m_hsbz=%u",pInvDet->m_hsbz));
		
		if(pInvDet->m_hsbz == 1)
		{
			pInvDet->m_spdj = tmpdj;
			INT64 nTmpSl = double2int(pInvDet->m_sl * JSK_SUM_EXTENSION);
			nTmpSl += JSK_SUM_EXTENSION;
			DBG_PRINT(("nTmpSl = %lld", nTmpSl));
			
			INT64 nTmpDj =double2int(tmpdj * JSK_SUM_EXTENSION);
			DBG_PRINT(("nTmpDj = %lld", nTmpDj));
			pInvDet->m_dj = (double)((nTmpDj*1.0) / nTmpSl);
			DBG_PRINT(("pInvDet->m_dj=%.3lf",pInvDet->m_dj));
			nTmpDj = double2int(pInvDet->m_dj*JSK_SUM_EXTENSION);
			DBG_PRINT(("nTmpDj = %lld", nTmpDj));
			pInvDet->m_dj = (double)nTmpDj/JSK_SUM_EXTENSION;
			DBG_PRINT(("pInvDet->m_dj=%.3lf",pInvDet->m_dj));
		}
		else
		{
			pInvDet->m_dj = tmpdj;
			
			INT64 nTmpSl = double2int(pInvDet->m_sl * JSK_SUM_EXTENSION);
			nTmpSl += JSK_SUM_EXTENSION;
			DBG_PRINT(("nTmpSl = %lld", nTmpSl));
			
			INT64 nTmpDj =double2int(tmpdj * JSK_SUM_EXTENSION);
			DBG_PRINT(("nTmpDj = %lld", nTmpDj));
			INT64 nTmpSpdj= nTmpDj * nTmpSl;
			DBG_PRINT(("nTmpSpdj = %lld", nTmpSpdj));
			
			pInvDet->m_spdj = (double)((nTmpSpdj*1.0) / (JSK_SUM_EXTENSION * JSK_SUM_EXTENSION));
			DBG_PRINT(("pInvDet->m_spdj=%.3lf",pInvDet->m_spdj));
		}
		
		pInvDet->m_spje = pInvDet->m_spse + pInvDet->m_je;
		DBG_PRINT(("pInvDet->m_spje=%lld",pInvDet->m_spje));
		
		pInvHead->InsertNode(pInvDet);
		pInvDet = NULL;
	}
*/
}

void CJSKInfoFunc::ParseData(INT8 *dest)
{
	int tmpLen = strlen(dest);
	for(int i=tmpLen; i>0; i--)
	{
		if(dest[i-1] != 0x20)
		{
			memset(dest+i, 0x00, tmpLen-i);
			break;
		}
	}
	
	return;
}

void CJSKInfoFunc::ParseInvCode(string str, string &fpdm, UINT32 &fphm)
{
	// 	int nLen = str.find("@");
	// 	DBG_PRINT(("nLen = %d", nLen));
	// 	str.erase(0, nLen+1);
	// 	DBG_PRINT(("str = %s", str.c_str()));
	// 
	// 	nLen = str.find("@");
	// 	DBG_PRINT(("nLen = %d", nLen));
	// 	fpdm = str.substr(0, nLen);
	// 	DBG_PRINT(("fpdm = %s", fpdm.c_str()));
	// 	str.erase(0, nLen+1);
	// 	DBG_PRINT(("str = %s", str.c_str()));
	// 	fphm = atoi(str.c_str());
	// 	DBG_PRINT(("fphm = %u", fphm));
	
	INT8 tmpbuf[20];
	memset(tmpbuf, 0, sizeof(tmpbuf));
	
	sscanf(str.c_str(), "0@%[^@]@%u", tmpbuf, &fphm);
	
	fpdm = tmpbuf;
	DBG_PRINT(("fpdm = %s", fpdm.c_str()));
	DBG_PRINT(("fphm = %u", fphm));
	
	return;
}



