/*! \file  JSKInfoFunc.cpp
\brief    awe4000rJSK����������Ϣ
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
	{3001,    "���˰��ͨѶ�쳣"		},
	{3003,    "�ӿ����������"			},
	{3065,    "��˰��ͨѶУ��ʹ�"		},
	{3072,    "��˰�̾����"			},
	{4000,    "һ�����"				},
	{4001,    "û���ҵ���˰��"			},
	{4002,    "�ҵ������˰��"			},
	{4003,    "�򿪷���ʧ��"			},
	{4004,    "�޴�����"				},
	{4005,    "��������"				},
	{4006,    "���ݴ���"				},
	{4007,	  "��������֤ʧ��"		},
	{6000,	  "��6000��ͷ�Ĵ����,ΪCA��ش���"},
	{8000,    "�Ƿ�����"				},
	{10000,    "δʵ�ֽӿ�"				},
	{449,    "����˰�����˰�ʵľ���ֵӦС��0.625"    },
	{452,    "���������Ч"    },
	{459,    "�ײ�汾��֧������Ʊ�ֿ���" },
	{506,    "��˰��ʱ���쳣"			},
	{511,	 "��Ʊ���ʹ���"				},
	{552,	 "���ֻ���ƥ��"				},
	{554,    "������Ʊ�޶�"			},
	{559,    "˰�ʳ���"					},
	{562,    "��Ʊ��ϸ����64K��"    },
	{701,    "��˰�����ڱ�˰��,���ܿ�Ʊ"    },
	{702,    "��˰������������,���ܿ�Ʊ"    },
	{706,    "��˰�������ѿ���,�������½���"    },
	{712,	 "��˰���˻ط�Ʊ����"			},
	{713,	 "��˰�̷��䷢Ʊ����"			},
	{754,	 "�ֻ����߱��˹���"			},
	{767,	 "��˰�̸�������"			},
	{768,    "����ʱ�䳬������ʱ��"    },
	{769,    "���߿�Ʊ����"    },
	{771,	 "�ֻ���Ʊ����"			},
	{772,	 "��˰����Ʊ����"			},
	{781,    "�ѵ�����������,���ܿ�Ʊ"    },
	{784,    "��Ʊ��ϸ�з�Ʊ����������Ʊ�治һ��"    },
	{790,	 "���²�ѯ��Ʊ��ϸʱ������Ʊ"			},
	{800,	 "��˰�̳�˰���ݲ�һ��"			},
	{1,    "�����������"    },
	{2,    "ʱ��û��Ӧ"    },
	{3,    "ʱ��ֹͣ"    },
	{4,    "��˰��״̬�쳣,���˳�ϵͳ���½���"    },
	{5,    "��¼��������"    },
	{6,    "��¼���������������"    },
	{7,    "˰���豸���ֻ���ƥ��"    },
	{8,    "��˰�̹�Ʊ������"    },
	{9,    "��˰����Ʊ������"    },
	{10,    "�þ�Ʊ���ѹ���"    },
	{15,    "�ֻ���˰�������˻ط�Ʊ��"    },
	{19,    "����ճ�˰��ʾ"    },
	{27,    "������˰δ��,�ֻ��˻ط�Ʊ��򳷻���Ʊ���ɶ�������"    },
	{21,    "��˰������δ��˰����,���ܿ�Ʊ"    },
	{36,    "��¼����Ч��������ַԽ��"    },
	{56,    "����(��)��Ʊ��������,��˰��ʾ"    },
	{57,    "����˰���豸�ͷֻ�˰���豸��֤ʧ��"    },
	{68,    "��Ҫ����ԱȨ��"    },
	{71,    "����ִ����������"    },
	{72,    "���ܳ�ʼ��ʱ��"    },
	{75,    "��˰��ʼʱ����ڽ�ֹʱ��"    },
	{79,    "�������Ȩ��¼"    },
	{80,    "��Ʊ��ѯʱ��Ʊ�����뷢Ʊ�����ͱ�־��һ��"    },
	{82,    "רƱ��������޶�"    },
	{83,    "��ѯʱ����ڵ�ǰʱ��"    },
	{84,    "��ѯʱ�����"    },
	{85,    "����յ�,��ֹ����������˻ط�Ʊ��"    },
	{86,    "����ʱ���"    },
	{87,    "˰���豸(��˰�̡���˰��)�з�Ʊ��ʱ���"    },
	{88,    "������������"    },
	{89,    "δ�ҵ�ָ����Ʊ��ϸ"    },
	{91,    "������������"    },
	{98,    "δ������Ʊ����ʼʱ��"    },
	{99,    "��Ʊ����������"    },
	{100,    "ʱ�Ӳ�����ǰ��"    },
	{101,    "û��⵽�洢��"    },
	{102,    "�洢��EDC��"    },
	{103,    "�洢����żУ���"    },
	{104,    "�洢�����Ӵ�"    },
	{105,    "�洢��������������"    },
	{106,    "�洢��ѡ���ļ���"    },
	{107,    "�洢����������"    },
	{108,    "�洢��д������"    },
	{109,    "�洢��У��PIN��"    },
	{110,    "�洢��ȡ�������"    },
	{111,    "�洢���ⲿ��֤��"    },
	{112,    "�洢�����ճ��ȴ�"    },
	{113,    "�洢����������"    },
	{114,    "�洢��������Կ��"    },
	{115,    "�洢��ͨ�ų�ʱ"    },
	{116,    "�洢��Э�����ʹ�"    },
	{117,    "�洢��Э������ʧ��"    },
	{119,    "flashECCУ���"    },
	{120,    "д�뷢Ʊ��ϸ����"    },
	{121,    "д��Flash����"    },
	{123,    "�޷�����FLASH�߼���"    },
	{125,    "дFLASH�߼��Ŵ�"    },
	{126,    "FLASHоƬ��"    },
	{129,    "EEPROM��ַ����"    },
	{131,    "�������Զ�д���ݲ�һ��"    },
	{132,    "��Ʊ��ϸ����"    },
	{133,    "��Ʊʱ��Ʊ��ϸ���ȴ���"    },
	{141,    "�ײ㷢Ʊ��ϸ��������"    },
	{148,    "���������ڷǷ�"    },
	{149,    "״̬�Ƿ����ܸ���������"    },
	{150,    "˰���豸(��˰�̡���˰��)��֤У��ʹ�"			},
	{151,    "˰���豸(��˰�̡���˰��)��֤˰�Ų�ƥ��"		},
	{152,    "˰���豸(��˰�̡���˰��)��֤ʱ�䲻ƥ��"		},
	{153,    "˰���豸(��˰�̡���˰��)��֤�������ƥ��"		},
	{155,    "˰���豸(��˰�̡���˰��)�忨У��ʹ�"			},
	{156,    "˰���豸(��˰�̡���˰��)�忨˰�Ų�ƥ��"		},
	{157,    "˰���豸(��˰�̡���˰��)�忨ʱ�䲻ƥ��"		},
	{158,    "˰���豸(��˰�̡���˰��)�忨�������ƥ��"		},
	{159,    "˰���豸(��˰�̡���˰��)�忨��ƥ��"			},
	{160,    "��˰�̻��˰�����˰�̲�ƥ��"					},
	{161,    "�ɿ���Ʊ�����������"							},
	{167,    "�������ͺͲ�����ƥ��"							},
	{176,    "�޿��÷�Ʊ"									},
	{181,    "Ӫ��������ʱ���ʽ��Ч"						},
	{182,    "��˰�����¹�����"								},
	{191,    "�赽����ճ�˰"								},
	{195,    "δ��˰,�޻�������"							},
	{199,    "�ð汾�����ڲ�֧��Զ�̳���"					},
	{204,    "˰���豸(��˰�̡���˰��)���б�˰�ɹ���־"		},
	{209,    "˰���豸(��˰�̡���˰��)�����˾�"				},
	{210,    "û��Ʊ����Ȩ"									},
	{219,    "�䳤��Ʊ��ϸ��"								},
	{220,    "���������������߼�����������"				},
	{222,    "˰���豸(��˰�̡���˰��)�����¾�,�޷���˰"   },
	{223,    "��������ָ���·����ô���Ϣ(���ѵ������,��Ҫ��˰����ܲ�ѯ�������ô�)"    },
	{229,    "��־λ����У��ʹ�"							},
	{231,    "˰���豸(��˰�̡���˰��)��Ȩ����(û��Ȩ)"   },
	{232,    "����У��ʹ�"									},
	{233,    "��Ȩ��Ϣ�Ƿ�"									},
	{234,    "��Ʊ��ϸ���ݻ���"								},
	{235,    "�޸Ŀ���ȹ��������ݰ����ȴ�"				},
	{236,    "����Ա��¼�������"							},
	{237,    "����Ա�������"								},
	{238,    "����Ա����"									},
	{239,    "����Ȩ�޴���"									},
	{240,    "��Ʊ�쳣������ɷ�Ʊ��ϸ����"					},
	{241,    "��˰�쳣������ɽ�˰�����ݻ���"				},
	{242,    "��Ʊ������쳣������ɽ�˰�����ݻ���"			},
	{244,    "���籣����־����"								},
	{245,    "��Ʊ�ֶ���δ��˰���߳�˰"		},
	{246,    "��������������,�������ѿ�δ�ϴ���Ʊ"    },
	{247,    "���߷�Ʊ�ܽ������߿����޶�" },
	{248,    "��Ʊ��û��������ڳ���˰"		},
	{249,    "��Ʊʱǩ�����ıȶԲ�ͨ��"						},
	{250,    "������δ�ϴ���Ʊ,������Զ�̳���"				},
	{999,    "��������������˰��"							},
	{1000,    "δ���ӱ�˰��"								},
	{1001,    "û���ҵ���˰�̾��"							},
	{1002,    "��˰��״̬��־�쳣"							},
	{1005,    "��˰�̼�¼��������"							},
	{1006,    "��˰�̼�¼���������������"					},
	{1036,    "��˰�̼�¼����Ч��������ַԽ��"			},
	{1179,    "��˰��û����Ȩ��Ϣ"							},
	{1050,    "��˰������Ʊ��Ϣ"    },
	{1051,    "��˰�̷�Ʊ����,����5��Ʊ"    },
	{1052,    "��˰�����¾���Ϣ"    },
	{1053,    "��˰�̷�������Խ��"    },
	{1054,    "��˰�̷��м�¼��"    },
	{1056,    "��˰��δ����"    },
	{1057,    "��˰�̺ͱ�˰�̲�ƥ��"    },
	{1058,    "��˰�̲���IC������"    },
	{1059,    "��˰��EPROM����"    },
	{1060,    "��˰�̿���������"    },
	{1061,    "��˰��FLASH��ʼ������"    },
	{1084,    "���ӱ�˰�̱�־����"    },
	{1085,    "��˰�̶��忨��Ϣʱ�ޱ�˰�ɹ���־(���忨��Ϣ)"    },
	{1086,    "��˰���Ѿ��г�˰����"    },
	{1087,    "������˰�̶Էֻ���˰��"    },
	{1088,    "��˰��������ȶԳ���"    },
	{1089,    "��˰��������Ϣ����,����˰�űȶԲ�ͨ��"    },
	{1090,    "���ӱ�˰�̱�־����"    },
	{1091,    "���ӱ�˰�̱�־����"    },
	{1092,    "��˰����֤ʱ�����"    },
	{1093,    "��˰����֤˰�Ŵ���"    },
	{1094,    "��˰��û����ϸ����"    },
	{1095,    "��˰����ϸ�Ѿ�����"    },
	{1096,    "��˰����ϸ���˳�����(��1����)"    },
	{1097,    "��ϸ��ų����ܱ��"    },
	{1098,    "��˰��У��ʹ���"    },
	{1101,    "��˰��û��⵽�洢����"    },
	{1102,    "��˰�̴洢����EDC��"    },
	{1103,    "��˰�̴洢������żУ���"    },
	{1104,    "��˰�̴洢�������Ӵ�"    },
	{1105,    "��˰�̴洢���ʷ�����������"    },
	{1106,    "��˰�̴洢����ѡ���ļ���"    },
	{1107,    "��˰�̴洢���ʶ�������"    },
	{1108,    "��˰�̴洢����д������"    },
	{1109,    "��˰�̴洢����У��PIN��"    },
	{1110,    "��˰�̴洢����ȡ�������"    },
	{1111,    "��˰�̴洢������֤��"    },
	{1112,    "��˰�̴洢���ʽ��ճ��ȴ�"    },
	{1113,    "��˰�̴洢������������"    },
	{1114,    "��˰�̴洢���ʸ�����Կ��"    },
	{1115,    "��˰�̴洢����ͨ�ų�ʱ"    },
	{1116,    "��˰�̴洢����Э�����ʹ�"    },
	{1117,    "��˰�̴洢����Э������ʧ��"    },
	{1120,    "��˰��д�뷢Ʊ��ϸ����"    },
	{1121,    "��˰��д��Flash����"    },
	{1123,    "��˰���޷�������ַ��"    },
	{1124,    "��˰�̲���Flashʧ��"    },
	{1126,    "��˰��FLASHоƬ��"							},
	{1128,    "��˰��дeepromʧ��"							},
	{1135,    "��˰��ecc error"								},
	{1179,    "��˰��û����Ȩ��Ϣ"							},
	{1159,    "��˰�̳����ѷ����ַ"						},
	{1160,    "��˰�̳����ɷ��䳭˰��"						},
	{1255,    "��������������˰��"						}	
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
//ͨѶ��
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
		sprintf(tmpbuf, "JSK%d:%s", nErrID,"��������");
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
	//��ʱ��ӽ�˰�̿����CA����
	char chBuf[128];  
	
	if( (pp1==MAKE_INVOICE_FUN) || (pp1==INVOICE_WASTE_FUN) )
	{
		JSK_Close_Proc(strErr);
	}
	
	//�����������δִ��open����,����������open����
	flag = 0;
	DBG_PRINT(("pp1=0x%02u, pp2= %u, InLen = %u",pp1,pp2, InLen));
	//ret = jsk_operate_r(pp1, pp2 ,( UINT8 *)pJSKSendBuf, InLen, ( UINT8 *)pJSKRevBuf,&OutLen);
	ret = jsk_operate_r(pp1, pp2 ,pInBuf, InLen, pOutBuf,&OutLen);
	DBG_PRINT(("ret= %d, OutLen= %u",ret,OutLen));
	if(ret != JSK_SUCCESS)
	{
		if ((ret == 3001)||(ret == 3065))	//����3001ʱ��Ҫ����open����
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
//����	����ȡ��˰����Ϣ
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetCorpInfo(CDataUserInfo *pUserInfo,CDataTax *pTax,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	DBG_ENTER("GetTaxCardInfo");
	
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	//��������
	ret =JSK_Proc(GET_CORP_INFO,0,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
    //�����������	
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
	
    //������� 0 ,�ֻ�����Ϊ0 ����Ϊ�ֻ�1 �ֻ���Ϊ�ֻ�������
	if (0 == pUserInfo->m_zfFlag)
	{
		//	pUserInfo->m_subMachNo = "0";
		pUserInfo->m_Kpjhm = 0;
	}
	DBG_PRINT(("pUserInfo->m_Kpjhm= %u",pUserInfo->m_Kpjhm));
	
	/*��˰����ҵ���� ����0��ʾһ����˰�ˣ�����1��ʾС��ģ��˰��*/
	pUserInfo->m_Nsrxz = pTaxCardInfo->CorpPorpertiy;
	DBG_PRINT(("pUserInfo->m_Nsrxz= %u",pUserInfo->m_Nsrxz));
	
    /*��ҵ���� ����0��ʾ���ض���ҵ������1��ʾ�ض���ҵ*/
	
	pUserInfo->m_Hylx = pTaxCardInfo->CorpType;
	DBG_PRINT(("pUserInfo->m_Hylx= %u",pUserInfo->m_Hylx));
	
	/*���̵ǼǺ�*/
	pUserInfo->m_Gsdjh  = (INT8 *)pTaxCardInfo->ResignNo;
	DBG_PRINT(("pUserInfo->m_Gsdjh= %s",pUserInfo->m_Gsdjh.c_str()));
	
	/*��������*/
	pUserInfo->m_Khyh= (INT8 *)pTaxCardInfo->DepositBank;
	DBG_PRINT(("pUserInfo->m_Khyh= %s",pUserInfo->m_Khyh.c_str()));
	
    /*�����˺�*/
	pUserInfo->m_Khzh = (INT8 *)pTaxCardInfo->DepositAccount;
	DBG_PRINT(("pUserInfo->m_Khzh= %s",pUserInfo->m_Khzh.c_str()));
	
	/*�Ǽ�ע���ַ*/
	pUserInfo->m_Djzcdz  = (INT8 *)pTaxCardInfo->ResignAddress;
	DBG_PRINT(("pUserInfo->m_Djzcdz= %s",pUserInfo->m_Djzcdz.c_str()));
	
    /*����˰����ش���*/
	pUserInfo->m_Swjgdm  = (INT8 *)pTaxCardInfo->TaxAuthorityNo;
	DBG_PRINT(("pUserInfo->m_Swjgdm= %s",pUserInfo->m_Swjgdm.c_str()));
	
    /*����˰���������*/
	pUserInfo->m_Swjgmc  = (INT8 *)pTaxCardInfo->TaxAuthorityName;
	DBG_PRINT(("pUserInfo->m_Swjgmc= %s",pUserInfo->m_Swjgmc.c_str()));
	
	   /* ��ҵ��˰��ʶ���*/
	pUserInfo->m_Nsrsbh  = (INT8 *)pTaxCardInfo->TaxCode;
	DBG_PRINT(("pUserInfo->m_Nsrsbh= %s",pUserInfo->m_Nsrsbh.c_str()));
	
	/*��Ʊ˰����Ȩ,��1�ֽڱ�ʾ��Ȩ˰�ʸ���,��2�ֽڿ�ʼΪ��Ȩ����Ʊ˰��*/
	UINT32 taxNum =pTaxCardInfo->AuthTaxRate[0];
	pUserInfo->m_Slgs = taxNum;
	DBG_PRINT(("pUserInfo->m_Slgs= %u",	pUserInfo->m_Slgs));
	if (pUserInfo->m_Slgs >MAX_TAX_NUM)
	{
		strErr="��ȡ��Ȩ˰�ʸ�������";
		return JSK_FAILURE;
	}
	UINT32 taxSL=0;
	for (int j=0; j<pUserInfo->m_Slgs; j++)
	{
		/*˰��*/
		taxSL=pTaxCardInfo->AuthTaxRate[j+1];
		
		DBG_PRINT(("taxSL= %u",taxSL));
		
		pTax[j].m_sl=(UINT32)(taxSL/10);
        DBG_PRINT(("pTax[%d].m_sl= %u",j,pTax[j].m_sl));	
		
	}
	
	
	/*��Ʊ����, ��1�ֽڱ�ʾ��Ʊ���͸���,��2�ֽڿ�ʼΪ��Ʊ����*/
	UINT32 typeNum =pTaxCardInfo->invName[0];
	pUserInfo->m_Fplxgs = typeNum;
	DBG_PRINT(("pUserInfo->m_Fplxgs= %u",	pUserInfo->m_Fplxgs));
	if (pUserInfo->m_Fplxgs >INVKIND_MAX_NUM)
	{
		strErr="��ȡ��Ʊ���͸�������";
		return JSK_FAILURE;
	}
	UINT32 uFplx=0;
	pUserInfo->m_Fplxsz = "";
	for (int k=0; k<pUserInfo->m_Fplxgs; k++)
	{
		/*��Ʊ����*/
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
//����	��ȡ��˰�̺���Ϣ
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetJSPNo(UINT8 *JSPNo,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//��������
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
//����	��ȡ��˰�̺ŵ�ǰʱ��
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetJSPCurDate(UINT8 *JSPDate,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//��������
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
//����	��ȡ��˰�̰汾��
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetJSPVer(UINT8 *JSPVer,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//��������
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
//����	��ȡ��˰������ʱ��
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetJSPOpenTime(UINT8 *JSPOTime,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//��������
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
//����	����ȡ��˰�����ݱ�����ʼʱ��
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetJSPSendTime(UINT8 *JSPSTime,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//��������
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
//����	��ȡ��ϣ˰�ź͵������
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetHashNo(UINT8 *HashNo,UINT8 *AddrNo,string &strErr, UINT8 HashFlag)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//��������
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
//����	��ȡ����˰��
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetIssueNo(UINT8 *IssueNo,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//��������
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
//����	����ȡ��һ�ŷ�Ʊ���߷�Ʊ�ķ�Ʊ���롢��Ʊ����ͷ�Ʊ������
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetFirstOffInvInfo(CDataInvHead *pInvHead,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//��������
	ret= JSK_Proc(GET_JSP_INFO,7,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret!=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	INT8 tmpBuf[16];
	
	//�����������
    TFirstOffInvInfo *pFirstOffInv = (TFirstOffInvInfo *)pJSKRevBuf;
	
	//��Ʊ����
	pInvHead->m_fpdm =pFirstOffInv->InvCode;
	DBG_PRINT(("pInvHead->m_fpdm= %s",pInvHead->m_fpdm.c_str()));
	
	//��Ʊ����
	pInvHead->m_fphm =pFirstOffInv->InvNo;
	DBG_PRINT(("pInvHead->m_fphm= %u",pInvHead->m_fphm));
	
	
	//��Ʊ������
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	sprintf(tmpBuf,"%u",pFirstOffInv->InvIndex);
	pInvHead->m_fpsyh =tmpBuf;
	DBG_PRINT(("pInvHead->m_fpsyh= %s",pInvHead->m_fpsyh.c_str()));
	
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;			
	
}
//----------------------------------------------------------
//����	����ѯ��˰���Ƿ��г�˰����
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetJSPCopyFlag(UINT8 &uCopyFlag,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//��������
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
//����	��ȡ��˰�̺���Ϣ
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetBSPNo(UINT8 *BSPNo,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//��������
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
//����	����ȡ��˰����ҵ��˰��ʶ���
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetBSPNsrsbh(UINT8 *BSPNsrsbh,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//��������
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
//����	����ȡ��˰�̰汾��
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetBSPVer(UINT8 *BSPVer,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//��������
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
//����	����ȡ��˰�̿�Ʊ����
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetBSPKpjh(UINT8 *BSPKpjh,string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//��������
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
//����	����ȡȨ����Ϣ
//����	��
//���	��
//����ֵ��
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
	
	//��������
    ret =JSK_Proc(GET_OFF_LIMIT_INFO,0,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if(ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	//�����������
	TOffLimintInfo *pOffLimintInfo = (TOffLimintInfo *)pJSKRevBuf;
	
	if (invKindNum < pOffLimintInfo->AuthLimitInfo.invNum)
	{
		strErr="��ȡƱ�ֵ���������";
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return JSK_FAILURE;
	}
	
	/* ��Ʊ������*/
    invKindNum =pOffLimintInfo->AuthLimitInfo.invNum;
	DBG_PRINT(("invKindNum= %u",invKindNum));
	for (int i=0; i<invKindNum; i++)
	{
		/*����������(ÿ�µĵڼ���)*/
		invKind[i].m_Lxssr = pOffLimintInfo->OffLineLockDay;
		DBG_PRINT(("pOffLimintInfo->OffLineLockDay= %u",pOffLimintInfo->OffLineLockDay));
		
		/*���߿�Ʊʱ��(��λСʱ*/
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
	
	//��������
    ret =JSK_Proc(GET_OFF_LIMIT_INFO,0,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if(ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	//�����������
	TOffLimintInfo *pOffLimintInfo = (TOffLimintInfo *)pJSKRevBuf;
	
	/* ��Ʊ������*/
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
//����	����˰�̿�����֤  
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::JSPPassW(UINT8* PassW, string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	memcpy((void *)pJSKSendBuf, (void *)PassW, JSK_PASSWORD_LEN);
	
	//��������
	// 	UINT32 nLen =sizeof(ModPassW);
	//	DBG_PRINT(("nLen= %u",nLen));
	ret =JSK_Proc(JSP_PASSWORD_MANAGE,0,pJSKSendBuf,JSK_PASSWORD_LEN,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;	
}
//----------------------------------------------------------
//����	����˰�̿������  
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::JSPModPassW(UINT8* ModPassW, string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	memcpy((void *)pJSKSendBuf, (void *)ModPassW, JSK_PASSWORD_SUM_LEN);
	
	//��������
	// 	UINT32 nLen =sizeof(ModPassW);
	//	DBG_PRINT(("nLen= %u",nLen));
	ret =JSK_Proc(JSP_PASSWORD_MANAGE,1,pJSKSendBuf,JSK_PASSWORD_SUM_LEN,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;	
}


//----------------------------------------------------------
//����	��֤��������  
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::ZSPassW(UINT8* ZSPassW, string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	memcpy((void *)pJSKSendBuf, (void *)ZSPassW, JSK_PASSWORD_SUM_LEN);
	
	//��������
	// 	UINT32 nLen =sizeof(ModPassW);
	//	DBG_PRINT(("nLen= %u",nLen));
	ret =JSK_Proc(JSP_PASSWORD_MANAGE,2,pJSKSendBuf,JSK_PASSWORD_SUM_LEN,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;	
}

//----------------------------------------------------------
//����	����˰��ע��
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::BSPRegister(string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	//��������
	ret= JSK_Proc(BSP_REGISTER,0,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
}


//----------------------------------------------------------
//����	���޸Ľ�˰��ʱ�� 
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::UpdateJSPClock(UINT8* JSPClock, string &strErr)
{
	
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	INT8 tmpBuf[32];

	//����
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Char2Hex((UINT8 *)tmpBuf,(INT8 *)JSPClock,JSK_PASSWORD_LEN);
	for (int i=0; i<JSK_UPDATE_CLOCK;i++)
	{
		DBG_PRINT(("tmpBuf[%d]= 0x%02x",i,tmpBuf[i]));
	}

	memcpy((void *)pJSKSendBuf, (void *)tmpBuf, JSK_PASSWORD_LEN);
	
	//��������
	
	ret =JSK_Proc(UPDATE_JSK_CLOCK,0,pJSKSendBuf,JSK_UPDATE_CLOCK,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;	
}
//----------------------------------------------------------
//����	��������ҵ��Ϣ 
//����	��
//���	��
//����ֵ��
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
	
	//��������
	ret =JSK_Proc(UPDATE_CORP_INFO,0,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
	
}


//----------------------------------------------------------
//����	����ȡ��ҵ��Ϣ  
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::ReadCorpInfo(UINT16 &outLen, UINT8* RCorpInfo, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	DBG_ENTER("GetCurInvInfo");
	
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//��������
	ret =JSK_Proc(READ_CORP_INFO,0,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret ==JSK_SUCCESS)
	{
		//�����������
		memcpy((void *)RCorpInfo,pJSKRevBuf,nOutLen);
		outLen = nOutLen;
		return ret;
	}
	
	
    
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
	
}

//----------------------------------------------------------
//����	�����÷�Ʊ�ϴ�״̬
//����	��
//���	��
//����ֵ��
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
	
	//��������
	ret =JSK_Proc(SET_UPLOAD_FLAG,0,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
}

//----------------------------------------------------------
//����	�����糭˰��Ϣ
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::NetCopyTax(UINT8 Type,UINT8 *StartDate,UINT8 *EndDate,UINT8 *NetTaxInfo,UINT32 &nTaxLen, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	int2hex(pJSKSendBuf,Type,1);
	
	//��������
	ret =JSK_Proc(COPY_TAX_FUN,0,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
    DBG_PRINT(("ret= %d",ret));
	if(ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
    DBG_PRINT(("nOutLen= %u",nOutLen));
	
	INT8 tmpBuf[32];
	
	//�����������
    TNetCopyTax	*pNetCopyTax = (TNetCopyTax *)pJSKRevBuf;
	
	//������ʼ����
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pNetCopyTax->StartDate,tmpBuf,7);
	//DBG_PRINT(("tmpBuf= %s",tmpBuf));
	//StartDate =(UINT8 *)tmpBuf;
	memcpy(StartDate, (UINT8 *)tmpBuf, sizeof(tmpBuf));
	DBG_PRINT(("StartDate= %s",StartDate));
	
	//���ͽ�������
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pNetCopyTax->EndDate,tmpBuf,7);
	//DBG_PRINT(("tmpBuf= %s",tmpBuf));
	//EndDate =(UINT8 *)tmpBuf;
	memcpy(EndDate, (UINT8 *)tmpBuf, sizeof(tmpBuf));
	DBG_PRINT(("EndDate= %s",EndDate));
	
	//��˰������Ϣ
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
	
	//��������
	ret =JSK_Proc(COPY_TAX_FUN,0,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
    DBG_PRINT(("ret= %d",ret));
	if(ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
    DBG_PRINT(("nOutLen= %u",nOutLen));
	
	INT8 tmpBuf[32];
	
	//�����������
    TNetCopyTax	*pNetCopyTax = (TNetCopyTax *)pJSKRevBuf;
	
	//������ʼ����
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pNetCopyTax->StartDate,tmpBuf,7);
	memcpy(StartDate, (UINT8 *)tmpBuf, sizeof(tmpBuf));
	DBG_PRINT(("StartDate= %s",StartDate));
	
	//���ͽ�������
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pNetCopyTax->EndDate,tmpBuf,7);
	memcpy(EndDate, (UINT8 *)tmpBuf, sizeof(tmpBuf));
	DBG_PRINT(("EndDate= %s",EndDate));
	
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;			
}
//----------------------------------------------------------
//����	����˰�̳�˰��Ϣ
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::JSPCopyTax(UINT8 Type,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	int2hex(pJSKSendBuf,Type,1);
	
	//��������
	ret =JSK_Proc(COPY_TAX_FUN,1,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
    DBG_PRINT(("ret= %d",ret));
	
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;			
}

//----------------------------------------------------------
//����	����˰�̳�˰��Ϣ
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::BSPCopyTax(UINT8 Type,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	int2hex(pJSKSendBuf,Type,1);
	
	//��������
	ret =JSK_Proc(COPY_TAX_FUN,2,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
    DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}

//----------------------------------------------------------
//����	�������忨
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::NetClearCard(UINT8 Type,UINT8 *CCardInfo,UINT32 nInfoLen,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//����������
	//ת�����ݽṹ  pJSKSendBuf
	
	TClearCardInfo *pTCCardInfo = (TClearCardInfo *)pJSKSendBuf;
	
	
	/*Ʊ�����*/
	pTCCardInfo->Type=Type;
	
	/*Ʊ�����*/
	memset(pTCCardInfo->CCardInfo, 0, sizeof(pTCCardInfo->CCardInfo));
	memcpy((void *)pTCCardInfo->CCardInfo, (void *)CCardInfo, nInfoLen);
	//	DBG_PRINT(("pTCCardInfo->CCardInfo= %s",pTCCardInfo->CCardInfo));
	
	
	//��������
	UINT32 nLen = nInfoLen+1;
	DBG_PRINT(("nLen= %u",nLen));
	
	ret =JSK_Proc(CLEAR_CARD_FUN,0,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
    DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
	
}

//----------------------------------------------------------
//����	����˰���忨
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::BSPClearCard(UINT8 Type,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	
	int2hex(pJSKSendBuf,Type,1);
	
	//��������
	ret =JSK_Proc(CLEAR_CARD_FUN,1,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
    DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}


//----------------------------------------------------------
//����	���������繺Ʊ
//����	��
//���	��
//����ֵ��
//---------------------------------------------------------
INT32 CJSKInfoFunc::AppNetInvVol(UINT8 Type,UINT16 &outLen,UINT8 *NetEmpowData, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;

	UINT8* pJSKSendBuf= NULL;
    UINT8* pJSKRevBuf= NULL;

	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	int2hex(pJSKSendBuf,Type,1);
	//��������
	ret= JSK_Proc(GET_NET_INVOL_INFO,1,pJSKSendBuf,1,pJSKRevBuf,nOutLen, strErr);
	DBG_PRINT(("ret= %d",ret));
	if(ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	DBG_PRINT(("nOutLen = %u", nOutLen));
	//�����������
	//   TNetInvVolInfo	*pTNetInvVolInfo = (TNetInvVolInfo *)pJSKRevBuf;
	
	/*���繺ƱԤ��Ȩ��Ϣ(����)*/
	memcpy((void *)NetEmpowData,(void *)pJSKRevBuf,	nOutLen);
	outLen = nOutLen;
	//	DBG_PRINT(("NetEmpowInfo= %s",NetEmpowInfo));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;	
}
//----------------------------------------------------------
//����	�����繺Ʊ���ݶ���
//����	��
//���	��
//����ֵ��
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
	
	//��������
	UINT32 nLen =JSK_NET_CRYP_DATA_LEN+1;
	DBG_PRINT(("nLen= %u",nLen));
	
	ret= JSK_Proc(GET_NET_INVOL_INFO,2,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
	
}

//----------------------------------------------------------
//����	�����繺Ʊ����ȷ������
//����	��
//���	��
//����ֵ��
//---------------------------------------------------------
INT32 CJSKInfoFunc::App2NetInvVol(UINT8 Type,UINT16 &outLen,UINT8 *NetCrypData,CDataInvVol *pInvVol,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
    int2hex(pJSKSendBuf,Type,1);
	
	//��������
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
	
	//�����������
	//   TNetInvVolInfo	*pTNetInvVolInfo = (TNetInvVolInfo *)pJSKRevBuf;
	DBG_PRINT(("nOutLen = %u", nOutLen));
	
	//�����������
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
//����	�����繺Ʊȷ��
//����	��
//���	��
//����ֵ��
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
	
	//��������
	UINT32 nLen =JSK_NET_INV_CON_LEN+1;
	DBG_PRINT(("nLen= %u",nLen));
	
	ret= JSK_Proc(GET_NET_INVOL_INFO,4,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}
//----------------------------------------------------------
//����	���ӽ�˰�̶����¹���Ʊ
//����	��
//���	��
//����ֵ��
//---------------------------------------------------------
INT32 CJSKInfoFunc::JSPGetInvVolInfo(UINT8 Type,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
    int2hex(pJSKSendBuf,Type,1);
	
	//��������
	ret =JSK_Proc(GET_NET_INVOL_INFO,5,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
    DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}

//----------------------------------------------------------
//����	���ӱ�˰�̶����¹���Ʊ
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::BSPGetInvVolInfo(UINT8 Type,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	int2hex(pJSKSendBuf,Type,1);
	//��������
	ret =JSK_Proc(GET_NET_INVOL_INFO,6,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
    DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}


//----------------------------------------------------------
//����	��������ȡ����ƱԴ��Ϣ(���繺Ʊ) ��Ʊ����
//����	��
//���	��
//����ֵ��
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
	
	
	
	//��������
	ret= JSK_Proc(GET_JSK_INVOL_INFO,0,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if(ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
	//�����������
    TInvVol	*pTInvVol = (TInvVol *)pJSKRevBuf;
	
	
	DBG_PRINT(("pTInvVol->InvNum = %u",pTInvVol->InvNum));
	DBG_PRINT(("pro_nInvNum= %u",nInvNum));
	
	if (nInvNum < pTInvVol->InvNum)
	{
		strErr="��ȡ��ƱԴ�����쳣";
		return JSK_FAILURE;
	}
	
	nInvNum =pTInvVol->InvNum;
	DBG_PRINT(("cur_nInvNum= %u",nInvNum));
	for (int i=0; i<nInvNum; i++)
	{
		UINT8 Type;		 /*��Ʊ���*/
		
		DBG_PRINT(("��%d��Ʊ��",i));
		
		/*��Ʊ���*/
		invVol[i].m_invtype =pTInvVol->InvVolum[i].Type;
		DBG_PRINT(("invVol[%d].m_invtype= %u",i,invVol[i].m_invtype));
		
		/*��Ʊ��ʼ��*/
		invVol[i].m_isno =pTInvVol->InvVolum[i].HeadCode;
		DBG_PRINT(("invVol[%d].pri_m_isno= %u",i,invVol[i].m_isno));
		
		/*��Ʊ�ܷ���*/
		invVol[i].m_fpzfs =(UINT32)pTInvVol->InvVolum[i].Count;
		DBG_PRINT(("invVol[%d].pri_Count= %u",i,invVol[i].m_fpzfs));
		
		/*��Ʊ������*/
		invVol[i].m_ieno =pTInvVol->InvVolum[i].HeadCode +pTInvVol->InvVolum[i].Count -1;
		DBG_PRINT(("invVol[%d].pri_m_ieno= %u",i,invVol[i].m_ieno));
		
		/*ʣ�����*/
		invVol[i].m_remain =pTInvVol->InvVolum[i].Remain;
		DBG_PRINT(("invVol[%d].m_remain= %u",i,invVol[i].m_remain));
		
		/*���÷�Ʊ��ʼ��*/
		INT32 nTmp = pTInvVol->InvVolum[i].Count - pTInvVol->InvVolum[i].Remain;
		//	DBG_PRINT(("nTmp= %d",nTmp));
		if (nTmp >0 )
		{
			invVol[i].m_isno += nTmp;
		}
		DBG_PRINT(("invVol[%d].m_isno= %u",i,invVol[i].m_isno));
		
		/*��������*/
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
		
		/*��Ʊ����10��12λASCII��*/
		invVol[i].m_code =pTInvVol->InvVolum[i].TypeCode;
		DBG_PRINT(("invVol[%d].m_code= %s",i,invVol[i].m_code.c_str()));
	}
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;			
}

//----------------------------------------------------------
//����	����ȡ��ǰ��Ʊ��
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::GetCurInvInfo(CDataInvVol *pInvVol,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	DBG_ENTER("GetCurInvInfo");
	
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//��������
	ret =JSK_Proc(GET_CUR_INVIOCE_INFO,0,pJSKSendBuf,0,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	if( ret !=JSK_SUCCESS)
	{
		JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
		return ret;
	}
	
    //�����������
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
//����	����Ʊ(��Ʊ,��Ʊ,�հ�����)
//����	��
//���	��
//����ֵ��
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
	
	
	// CDataInvHead �� TInvHead ת��
	//pTaxCardInvHead ��װ��Ʊ��Ϣbuf
	INT8 tmpBuf[JSK_MAKE_INV_SIGN_LEN];
	
    TInvHead *pTInvHead = (TInvHead *)pJSKSendBuf;
	
	/*9�ֽ�֤�����*/
	memset(pTInvHead->CAPassW, 0, sizeof(pTInvHead->CAPassW));
	memcpy((void *)pTInvHead->CAPassW, (void *)pInvHead->m_zskl.c_str(), JSK_PASSWORD_LEN);
	DBG_PRINT(("pTInvHead->CAPassW= %s",pTInvHead->CAPassW));
	
	
	/*10��12λASCII�뷢Ʊ����*/
	memset(pTInvHead->taxCardInvHead.TypeCode, 0, sizeof(pTInvHead->taxCardInvHead.TypeCode));
	memcpy((void *)pTInvHead->taxCardInvHead.TypeCode, (void *)pInvHead->m_fpdm.c_str(), pInvHead->m_fpdm.length());
	DBG_PRINT(("pInvHead->m_fpdm= %s",pInvHead->m_fpdm.c_str()));
	
	/*��Ʊ����*/ 
	pTInvHead->taxCardInvHead.InvNo =pInvHead->m_fphm;
	DBG_PRINT(("pInvHead->m_fphm= %u",pInvHead->m_fphm));
	
	/* ��Ʊ����*/
	Char2Hex((UINT8 *)pTInvHead->taxCardInvHead.Date,pInvHead->m_CurTime.c_str(),7);
	
	/*����˰��*/
	memset(pTInvHead->taxCardInvHead.BuyTaxCode, 0, sizeof(pTInvHead->taxCardInvHead.BuyTaxCode));
	memcpy((void *)pTInvHead->taxCardInvHead.BuyTaxCode, (void *)pInvHead->m_payerCode.c_str(), pInvHead->m_payerCode.length());
	
	
	/*���*/  
	DBG_PRINT(("pInvHead->m_kpje = %lld", pInvHead->m_kpje));
	memset(pTInvHead->taxCardInvHead.TotalSum, 0, sizeof(pTInvHead->taxCardInvHead.TotalSum));
	sprintf(pTInvHead->taxCardInvHead.TotalSum, "%.2f", ((double) pInvHead->m_kpje)/JSK_SUM_EXTENSION);
#ifdef DEGUG_PRN
	for (int i=0; i<20; i++)
	{
		DBG_PRINT(("pTInvHead->taxCardInvHead.TotalSum[%d]=0x%02x",i,pTInvHead->taxCardInvHead.TotalSum[i]));
	}
#endif
	
	/*˰��*/
	DBG_PRINT(("pInvHead->m_kpse = %lld", pInvHead->m_kpse));
	memset(pTInvHead->taxCardInvHead.Tax, 0, sizeof(pTInvHead->taxCardInvHead.Tax));
	sprintf(pTInvHead->taxCardInvHead.Tax, "%.2f", ((double) pInvHead->m_kpse)/JSK_SUM_EXTENSION);
	
	
	/*��Ʊ���*/
	pTInvHead->taxCardInvHead.Type=pInvHead->m_fplb;
	
	/*��Ʊ��־*/ 
	pTInvHead->taxCardInvHead.invFlag=pInvHead->m_kplx;
	DBG_PRINT(("pInvHead->m_kplx= %u",pInvHead->m_kplx));
	
	/*������Ʊ��Ӧ��������Ʊ�Ĵ���*/
	memset(pTInvHead->taxCardInvHead.NegToPosTypeCode, 0, sizeof(pTInvHead->taxCardInvHead.NegToPosTypeCode));
	memcpy((void *)pTInvHead->taxCardInvHead.NegToPosTypeCode, (void *)pInvHead->m_yfpdm.c_str(), pInvHead->m_yfpdm.length());
	
	/*������Ʊ��Ӧ��������Ʊ�ĺ���*/
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
	
	//��������
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
	
    tmpLen += 1; //�ָ���'\0'
	
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
//����	���ѿ���Ʊ����
//����	��
//���	��
//����ֵ��
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
	
	
	// CDataInvHead �� TaxCardInvCancel ת��
	//pTaxCardInvHead ��װ��Ʊ��Ϣbuf
	INT8 tmpBuf[JSK_MAKE_INV_SIGN_LEN];
	
    TInvCancel *pTInvCancel = (TInvCancel *)pJSKSendBuf;
	
	/*9�ֽ�֤�����*/
	memset(pTInvCancel->CAPassW, 0, sizeof(pTInvCancel->CAPassW));
	memcpy((void *)pTInvCancel->CAPassW, (void *)pInvHead->m_zskl.c_str(), JSK_PASSWORD_LEN);
	DBG_PRINT(("pTInvCancel->CAPassW= %s",pTInvCancel->CAPassW));
	
	
	/*10��12λASCII�뷢Ʊ����*/
	memset(pTInvCancel->taxCardInvCancel.TypeCode, 0, sizeof(pTInvCancel->taxCardInvCancel.TypeCode));
	memcpy((void *)pTInvCancel->taxCardInvCancel.TypeCode, (void *)pInvHead->m_fpdm.c_str(), pInvHead->m_fpdm.length());
	
	/*��Ʊ����*/ 
	pTInvCancel->taxCardInvCancel.InvNo =pInvHead->m_fphm;
	
	/*��Ʊ����*/
	pTInvCancel->taxCardInvCancel.Type=pInvHead->m_fplb;
	
	
	/*��Ʊ��־*/ 
	pTInvCancel->taxCardInvCancel.invFlag=pInvHead->m_kplx;
	
	/*��Ʊ������*/
	memset(pTInvCancel->taxCardInvCancel.InvAcess, 0, sizeof(pTInvCancel->taxCardInvCancel.InvAcess));
	Char2Hex((UINT8 *)pTInvCancel->taxCardInvCancel.InvAcess,pInvHead->m_fpsyh.c_str(),4);
	
	
	//��������
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
	//ǩ������
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
	
	
	//��Ʊ������
    memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char((UINT8 *)(pJSKRevBuf+tmpLen),tmpBuf,4);
	pInvHead->m_fpsyh=tmpBuf;
	DBG_PRINT(("pInvHead->m_fpsyh= %s",pInvHead->m_fpsyh.c_str()));
	tmpLen +=4;
	
	
	//��������
    memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
    Hex2Char((UINT8 *)(pJSKRevBuf+tmpLen),tmpBuf,7);
	pInvHead->m_zfsj = tmpBuf;
	DBG_PRINT(("pInvHead->m_zfsj= %s",pInvHead->m_zfsj.c_str()));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;	
	
}
//----------------------------------------------------------
//����	��������Ʊ(���ֻ���˰�̷�Ʊ)
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::HostToInvBSP(CDataInvVol *pInvVol, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//����������
	// THostToInv ת�����ݽṹ  pJSKSendBuf
	
	THostToInv *pTHostAllotInv = (THostToInv *)pJSKSendBuf;
	
	/*��Ʊ����*/ 
	pTHostAllotInv->InvNo =pInvVol->m_isno;
	DBG_PRINT(("pTHostAllotInv->InvNo= %u",pTHostAllotInv->InvNo));
	
	   /*char���͵�16B��Ʊ����*/
	memset(pTHostAllotInv->InvCode, 0, sizeof(pTHostAllotInv->InvCode));
	memcpy((void *)pTHostAllotInv->InvCode, (void *)pInvVol->m_code.c_str(), pInvVol->m_code.length());
	DBG_PRINT(("THostToInv->InvCode= %s",pTHostAllotInv->InvCode));
	
	/*unsigned short��Ʊ���� */ 
	pTHostAllotInv->InvNum =(UINT16)pInvVol->m_fpzfs;
	DBG_PRINT(("THostToInv->InvNum= %u",pTHostAllotInv->InvNum));
	
	/*��Ʊ���� */
	pTHostAllotInv->InvType =pInvVol->m_invtype;
	DBG_PRINT(("THostToInv->InvType= %u",pTHostAllotInv->InvType));
	
	//��������
	UINT32 nLen =sizeof(THostToInv);
	DBG_PRINT(("nLen= %u",nLen));
	
	ret =JSK_Proc(HOST_TO_INVVOL,0,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}

//----------------------------------------------------------
//����	��������Ʊ(���ֻ���˰�̷�Ʊ)
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::HostToInvJSP(CDataInvVol *pInvVol, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//����������
	// THostToInv ת�����ݽṹ  pJSKSendBuf
	
	THostToInv *pTHostAllotInv = (THostToInv *)pJSKSendBuf;
	
	/*��Ʊ����*/ 
	pTHostAllotInv->InvNo =pInvVol->m_isno;
	DBG_PRINT(("pTHostAllotInv->InvNo= %u",pTHostAllotInv->InvNo));
	
	   /*char���͵�16B��Ʊ����*/
	memset(pTHostAllotInv->InvCode, 0, sizeof(pTHostAllotInv->InvCode));
	memcpy((void *)pTHostAllotInv->InvCode, (void *)pInvVol->m_code.c_str(), pInvVol->m_code.length());
	DBG_PRINT(("THostToInv->InvCode= %s",pTHostAllotInv->InvCode));
	
	/*unsigned short��Ʊ���� */ 
	pTHostAllotInv->InvNum =(UINT16)pInvVol->m_fpzfs;
	DBG_PRINT(("THostToInv->InvNum= %u",pTHostAllotInv->InvNum));
	
	/*��Ʊ���� */
	pTHostAllotInv->InvType =pInvVol->m_invtype;
	DBG_PRINT(("THostToInv->InvType= %u",pTHostAllotInv->InvType));
	
	
	//��������
	UINT32 nLen =sizeof(THostToInv);
	DBG_PRINT(("nLen= %u",nLen));
	
	ret =JSK_Proc(HOST_TO_INVVOL,1,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}

//----------------------------------------------------------
//����	����Ʊ��˰���˻�(���ֻ�һ��)
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::InvVolRetBSP(CDataInvVol *pInvVol, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//����������
	// TInvRetInfo ת�����ݽṹ  pJSKSendBuf
	
	TInvRetInfo *pTInvRetInfo = (TInvRetInfo *)pJSKSendBuf;
	
	/*��Ʊ����*/ 
	pTInvRetInfo->InvNo =pInvVol->m_isno;
	DBG_PRINT(("pTInvRetInfo->InvNo= %u",pTInvRetInfo->InvNo));
	
	   /*char���͵�16B��Ʊ����*/
	memset(pTInvRetInfo->InvCode, 0, sizeof(pTInvRetInfo->InvCode));
	memcpy((void *)pTInvRetInfo->InvCode, (void *)pInvVol->m_code.c_str(), pInvVol->m_code.length());
	DBG_PRINT(("pTInvRetInfo->InvCode= %s",pTInvRetInfo->InvCode));
	
	/*unsigned short��Ʊ���� */ 
	pTInvRetInfo->InvNum =(UINT16)pInvVol->m_fpzfs;
	DBG_PRINT(("pTInvRetInfo->InvNum= %u",pTInvRetInfo->InvNum));
	
	/*��Ʊ���� */
	pTInvRetInfo->InvType =pInvVol->m_invtype;
	DBG_PRINT(("pTInvRetInfo->InvType= %u",pTInvRetInfo->InvType));
	
	
	//��������
	UINT32 nLen =sizeof(TInvRetInfo);
	DBG_PRINT(("nLen= %u",nLen));
	
	ret =JSK_Proc(INVVOL_RET_INFO,0,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}

//----------------------------------------------------------
//����	����Ʊ��˰���˻�(���ֻ�һ��)
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::InvVolRetJSP(CDataInvVol *pInvVol, string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	//����������
	// TInvRetInfo ת�����ݽṹ  pJSKSendBuf
	
	TInvRetInfo *pTInvRetInfo = (TInvRetInfo *)pJSKSendBuf;
	
	/*��Ʊ����*/ 
	pTInvRetInfo->InvNo =pInvVol->m_isno;
	DBG_PRINT(("pTInvRetInfo->InvNo= %u",pTInvRetInfo->InvNo));
	
	   /*char���͵�16B��Ʊ����*/
	memset(pTInvRetInfo->InvCode, 0, sizeof(pTInvRetInfo->InvCode));
	memcpy((void *)pTInvRetInfo->InvCode, (void *)pInvVol->m_code.c_str(), pInvVol->m_code.length());
	DBG_PRINT(("pTInvRetInfo->InvCode= %s",pTInvRetInfo->InvCode));
	
	/*unsigned short��Ʊ���� */ 
	pTInvRetInfo->InvNum =(UINT16)pInvVol->m_fpzfs;
	DBG_PRINT(("pTInvRetInfo->InvNum= %u",pTInvRetInfo->InvNum));
	
	/*��Ʊ���� */
	pTInvRetInfo->InvType =pInvVol->m_invtype;
	DBG_PRINT(("pTInvRetInfo->InvType= %u",pTInvRetInfo->InvType));
	
	//��������
	UINT32 nLen =sizeof(TInvRetInfo);
	DBG_PRINT(("nLen= %u",nLen));
	
	ret =JSK_Proc(INVVOL_RET_INFO,1,pJSKSendBuf,nLen,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
				
}

//----------------------------------------------------------
//����	����������ֻ���˰���˻ط�Ʊ
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
INT32 CJSKInfoFunc::HostGetInvBSP(UINT8 Type,string &strErr)
{
	INT32 ret=JSK_SUCCESS;
	UINT16 nOutLen=0;
	UINT8 *pJSKSendBuf =NULL;
    UINT8 *pJSKRevBuf =NULL;
	JSK_NewBuf(&pJSKSendBuf,&pJSKRevBuf);
	
	
	/*��Ʊ���� */
	int2hex(pJSKSendBuf,Type,1);
	
	ret =JSK_Proc(HOST_GET_INVVOL,0,pJSKSendBuf,1,pJSKRevBuf,nOutLen,strErr);
	DBG_PRINT(("ret= %d",ret));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return ret;
	
}

//----------------------------------------------------------
//����	����������ֻ���˰���˻ط�Ʊ
//����	��
//���	��
//����ֵ��
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
//����	����������
//����	��
//���	��
//����ֵ��
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
//����	��ͨ����Ʊ����,��Ʊ����������Ų�ѯ��Ʊ��Ϣ
//����	��
//���	��
//����ֵ��
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
	
	/*��Ʊ����*/ 
	pQueryInfo->InvNo =pInvHead->m_fphm;
	DBG_PRINT(("pQueryInfo->InvNo = %u",pQueryInfo->InvNo ));
	
	/*10��12λASCII�뷢Ʊ����*/
	memset(pQueryInfo->InvCode, 0, sizeof(pQueryInfo->InvCode));
	memcpy((void *)pQueryInfo->InvCode, (void *)pInvHead->m_fpdm.c_str(), pInvHead->m_fpdm.length());
	DBG_PRINT(("pQueryInfo->InvCode = %s",pQueryInfo->InvCode ));
	
	/*��Ʊ������*/ 
	
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
	
	
	//�����������
    TInvDetail *pInvDetail = (TInvDetail *)pJSKRevBuf;
	
#ifdef DEGUG_PRN
	DBG_PRINT(("��������"));
	for (int i=0; i<nOutLen;i++)
	{
		DBG_PRINT(("pJSKRevBuf[%d]=Ox%x",i,pJSKRevBuf[i]));
	}
#endif
	
    /*10��12λASCII�뷢Ʊ����*/
	pInvHead->m_fpdm =pInvDetail->TypeCode;
	DBG_PRINT(("pInvHead->m_fpdm= %s",pInvHead->m_fpdm.c_str()));
	
    /*��Ʊ����*/ 
    pInvHead->m_fphm =pInvDetail->InvNo;
	DBG_PRINT(("pInvHead->m_fpdm= %u",pInvHead->m_fphm));
	
	/* ��Ʊ����*/
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pInvDetail->Date,tmpBuf,7);
	//DBG_PRINT(("tmpBuf= %s",tmpBuf));
	pInvHead->m_CurTime= tmpBuf;
	DBG_PRINT(("pInvHead->m_CurTime=%s",pInvHead->m_CurTime.c_str()));
	pInvHead->m_kprq = atoi((pInvHead->m_CurTime.substr(0, 8)).c_str());
	pInvHead->m_kpsj = atoi((pInvHead->m_CurTime.substr(8, 6)).c_str());
	DBG_PRINT(("pInvHead->m_kprq= %u",pInvHead->m_kprq));
	DBG_PRINT(("pInvHead->m_kpsj= %u",pInvHead->m_kpsj));
	
    /*����˰��*/
	pInvHead->m_payerCode= pInvDetail->BuyTaxCode;
	
    /*���,����˰��*/ 
	pInvHead->m_kpje = double2int(atof(pInvDetail->TotalSum) * JSK_SUM_EXTENSION);
	DBG_PRINT(("pInvHead->m_kpje= %lld",pInvHead->m_kpje));
	
	/*˰��*/
	pInvHead->m_kpse = double2int(atof(pInvDetail->Tax) * JSK_SUM_EXTENSION);
	DBG_PRINT(("pInvHead->m_kpse= %lld",pInvHead->m_kpse));
	
	/*��Ʊ����*/
	pInvHead->m_fplb =pInvDetail->Type;
	DBG_PRINT(("pInvHead->m_fplb= %u",pInvHead->m_fplb));
	
	/*��Ʊ��־�����������������ϡ����ϡ��հ׷�*/
    pInvHead->m_kplx =pInvDetail->invFlag;
	DBG_PRINT(("pInvHead->m_kplx= %u",pInvHead->m_kplx));
	if( (pInvHead->m_kplx==JSK_WASTE_NOR) || (pInvHead->m_kplx==JSK_WASTE_RET) )
	{
		pInvHead->m_zfsj = pInvHead->m_CurTime;
	}
	
	//unsigned int DataLen;  /*��Ʊ���ݳ���*/
	//unsigned char *DataPtr; /*��Ʊ������ϸ*/
	
	memset((void *)JSK_InvBuf,0x00,sizeof(JSK_InvBuf));
	
	
//	DBG_PRINT(("pInvDetail->DataPtr= 0x%02x",pInvDetail->DataPtr));
	DBG_PRINT(("pInvDetail->DataLen= %u",pInvDetail->DataLen));
	
	memcpy((void *)JSK_InvBuf,(void *)pInvDetail->DataPtr,pInvDetail->DataLen);
//	printf("-------------------\n%s\n--------------------\n",JSK_InvBuf);
	
	MutexLock();
	Data2InvDetail(JSK_InvBuf,pInvHead);
	MutexUnlock();
	
	/*ǩ������*/
	INT8 signBuf[JSK_MAKE_INV_SIGN_LEN];
	memset(signBuf, 0, sizeof(signBuf));
	memcpy(signBuf, (INT8 *)pInvDetail->SignPtr, pInvDetail->SignLen);
#if CA_SIGN_BASE64 == 1
	Base64_Encode_2((UINT8 *)signBuf, pInvDetail->SignLen);
#endif
	pInvHead->m_casign=signBuf;
//	DBG_PRINT(("pInvHead->m_casign= %s",pInvHead->m_casign.c_str()));
	
	
	/*20λУ���� */
	pInvHead->m_fwm =pInvDetail->CheckCode;
	DBG_PRINT(("pInvHead->m_fwm= %s",pInvHead->m_fwm.c_str()));
	
	/*��Ʊ������ */ 
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pInvDetail->Adress,tmpBuf,4);
	pInvHead->m_fpsyh=tmpBuf;
	DBG_PRINT(("pInvHead->m_fpsyh= %s",pInvHead->m_fpsyh.c_str()));
	
	
	/*��Ʊ�ϴ���־��1-���ϴ���0-δ�ϴ�*/
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
	
	/*��Ʊ����*/ 
	pQueryInfo->InvNo =pInvHead->m_fphm;
	DBG_PRINT(("pQueryInfo->InvNo = %u",pQueryInfo->InvNo ));
	
	/*10��12λASCII�뷢Ʊ����*/
	memset(pQueryInfo->InvCode, 0, sizeof(pQueryInfo->InvCode));
	memcpy((void *)pQueryInfo->InvCode, (void *)pInvHead->m_fpdm.c_str(), pInvHead->m_fpdm.length());
	DBG_PRINT(("pQueryInfo->InvCode = %s",pQueryInfo->InvCode ));
	
	/*��Ʊ������*/ 
	
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
	
	
	//�����������
    TInvDetail *pInvDetail = (TInvDetail *)pJSKRevBuf;
	
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pInvDetail->Date,tmpBuf,7);
	pInvHead->m_CurTime= tmpBuf;
	DBG_PRINT(("pInvHead->m_CurTime=%s",pInvHead->m_CurTime.c_str()));
	pInvHead->m_kprq = atoi((pInvHead->m_CurTime.substr(0, 8)).c_str());
	pInvHead->m_kpsj = atoi((pInvHead->m_CurTime.substr(8, 6)).c_str());
	DBG_PRINT(("pInvHead->m_kprq= %u",pInvHead->m_kprq));
	DBG_PRINT(("pInvHead->m_kpsj= %u",pInvHead->m_kpsj));
	
	/*��Ʊ����*/
	pInvHead->m_fplb =pInvDetail->Type;
	DBG_PRINT(("pInvHead->m_fplb= %u",pInvHead->m_fplb));
	
	/*��Ʊ��־�����������������ϡ����ϡ��հ׷�*/
    pInvHead->m_kplx =pInvDetail->invFlag;
	DBG_PRINT(("pInvHead->m_kplx= %u",pInvHead->m_kplx));
	if( (pInvHead->m_kplx==JSK_WASTE_NOR) || (pInvHead->m_kplx==JSK_WASTE_RET) || (pInvHead->m_kplx==JSK_WASTE_INV) )
	{
		pInvHead->m_zfsj = pInvHead->m_CurTime;
		DBG_PRINT(("pInvHead->m_zfsj = %s", pInvHead->m_zfsj.c_str()));
	}
	
	invLen = pInvDetail->DataLen;
	memcpy((void *)invBuff,(void *)pInvDetail->DataPtr,pInvDetail->DataLen);
	
	/*ǩ������*/
	//	pInvHead->m_casign=(INT8 *)pInvDetail->SignPtr;
	INT8 signBuf[JSK_MAKE_INV_SIGN_LEN];
	memset(signBuf, 0, sizeof(signBuf));
	memcpy(signBuf, (INT8 *)pInvDetail->SignPtr, pInvDetail->SignLen);
#if CA_SIGN_BASE64 == 1
	Base64_Encode_2((UINT8 *)signBuf, pInvDetail->SignLen);
#endif
	pInvHead->m_casign = signBuf;
//	DBG_PRINT(("pInvHead->m_casign= %s",pInvHead->m_casign.c_str()));
	
	
	/*20λУ���� */
	pInvHead->m_fwm =pInvDetail->CheckCode;
	DBG_PRINT(("pInvHead->m_fwm= %s",pInvHead->m_fwm.c_str()));
	
	
	/*��Ʊ�ϴ���־��1-���ϴ���0-δ�ϴ�*/
    pInvHead->m_scbz =pInvDetail->UpFlag;
	DBG_PRINT(("pInvHead->m_scbz= %u",pInvHead->m_scbz));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;	
}

//----------------------------------------------------------
//����	��ͨ���������ڲ�ѯ��Ʊ��Ϣ
//����	��
//���	��
//����ֵ��
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
	
	
	/*��*/ 
	pDateQueryInfo->InvYear =atoi((INT8 *)chDate)/100;
	DBG_PRINT(("pDateQueryInfo->InvYear = %u",pDateQueryInfo->InvYear));
	
	/*��*/ 
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
	//�����������
	memcpy((void *)&uInvFlag,(void *)pJSKRevBuf,1);
	DBG_PRINT(("uInvFalg= %u",uInvFlag));
	
	TInvDetail *pInvDetail = (TInvDetail *)(pJSKRevBuf+1);
	
    /*10��12λASCII�뷢Ʊ����*/
	pInvHead->m_fpdm =pInvDetail->TypeCode;
	DBG_PRINT(("pInvHead->m_fpdm= %s",pInvHead->m_fpdm.c_str()));
	
    /*��Ʊ����*/ 
    pInvHead->m_fphm =pInvDetail->InvNo;
	DBG_PRINT(("pInvHead->m_fphm= %u",pInvHead->m_fphm));
	
	/* ��Ʊ����*/
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pInvDetail->Date,tmpBuf,7);
	//DBG_PRINT(("tmpBuf= %s",tmpBuf));
	pInvHead->m_CurTime= tmpBuf;
	DBG_PRINT(("pInvHead->m_CurTime=%s",pInvHead->m_CurTime.c_str()));
	pInvHead->m_kprq = atoi((pInvHead->m_CurTime.substr(0, 8)).c_str());
	pInvHead->m_kpsj = atoi((pInvHead->m_CurTime.substr(8, 6)).c_str());
	DBG_PRINT(("pInvHead->m_kprq= %u",pInvHead->m_kprq));
	DBG_PRINT(("pInvHead->m_kpsj= %u",pInvHead->m_kpsj));
	
    /*����˰��*/
	pInvHead->m_payerCode= pInvDetail->BuyTaxCode;
	
    /*���,����˰��*/ 
	pInvHead->m_kpje = double2int(atof(pInvDetail->TotalSum) * JSK_SUM_EXTENSION);
	DBG_PRINT(("pInvHead->m_kpje= %lld",pInvHead->m_kpje));
	
	/*˰��*/
	pInvHead->m_kpse = double2int(atof(pInvDetail->Tax) * JSK_SUM_EXTENSION);
	DBG_PRINT(("pInvHead->m_kpse= %lld",pInvHead->m_kpse));
	
	/*��Ʊ����*/
	pInvHead->m_fplb =pInvDetail->Type;
	DBG_PRINT(("pInvHead->m_fplb= %u",pInvHead->m_fplb));
	
	/*��Ʊ��־�����������������ϡ����ϡ��հ׷�*/
    pInvHead->m_kplx =pInvDetail->invFlag;
	DBG_PRINT(("pInvHead->m_kplx= %u",pInvHead->m_kplx));
	
	//unsigned int DataLen;  /*��Ʊ���ݳ���*/
	//unsigned char *DataPtr; /*��Ʊ������ϸ*/
    memset((void *)JSK_InvBuf,0x00,sizeof(JSK_InvBuf));
	
	memcpy((void *)JSK_InvBuf,(void *)pInvDetail->DataPtr,pInvDetail->DataLen);
	
	MutexLock();
	Data2InvDetail(JSK_InvBuf,pInvHead);
	MutexUnlock();
	
	/*ǩ������*/
	pInvHead->m_casign=(INT8 *)pInvDetail->SignPtr;
//	DBG_PRINT(("pInvHead->m_casign= %s",pInvHead->m_casign.c_str()));
	
	
	/*20λУ���� */
	pInvHead->m_fwm =pInvDetail->CheckCode;
	DBG_PRINT(("pInvHead->m_fwm= %s",pInvHead->m_fwm.c_str()));
	
	/*��Ʊ������ */ 
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	Hex2Char(pInvDetail->Adress,tmpBuf,4);
	pInvHead->m_fpsyh=tmpBuf;
	DBG_PRINT(("pInvHead->m_fpsyh= %s",pInvHead->m_fpsyh.c_str()));
	
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;	
}


//----------------------------------------------------------
//����	����ѯ��ͳ������
//����	��
//���	��
//����ֵ��
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
	
	/*��*/ 
	uInvYear = iDate/100;
	DBG_PRINT(("uInvYear = %u",uInvYear));
	memcpy((void *)pJSKSendBuf,(void *)&uInvYear,2);
	
	/*��*/ 
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
	
	//�����������
	DBG_PRINT(("��������"));
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
			DBG_PRINT(("pTjxxhz[%d].m_Type= %u",i,pTjxxhz->m_Type)) ;/*��Ʊ����*/
			
			pTjxxhz->m_Qckcfs =pSumInvCount->invCount[i].OpenInventory;		 /*�ڳ����*/
			DBG_PRINT(("pTjxxhz[%d].m_Qckcfsm_OpenInventory= %u",i,pTjxxhz->m_Qckcfs)) ;
			
			pTjxxhz->m_Lgfpfs =pSumInvCount->invCount[i].NewBuy; 			/*�����¹�*/ 
			DBG_PRINT(("pTjxxhz[%d].m_Lgfpfs= %u",i,pTjxxhz->m_Lgfpfs));
			
			pTjxxhz->m_Qmkcfs =pSumInvCount->invCount[i].EndInventory; 		/*��ĩ���*/
			DBG_PRINT(("pTjxxhz[%d].m_Qmkcfs= %u",i,pTjxxhz->m_Qmkcfs));
			
			pTjxxhz->m_Thfpfs =pSumInvCount->invCount[i].ReBack; 				/*�����˻�*/
			DBG_PRINT(("pTjxxhz[%d].m_Thfpfs= %u",i,pTjxxhz->m_Thfpfs)) ;
			
			pTjxxhz->m_Zsfpfs=pSumInvCount->invCount[i].InvNum; 	/*������Ʊ���߷���*/
			DBG_PRINT(("pTjxxhz[%d].m_Zsfpfs= %u",i,pTjxxhz->m_Zsfpfs)) ;
			
			pTjxxhz->m_Zffpfs =pSumInvCount->invCount[i].InvCancelNum; /*������Ʊ���Ϸ���*/
			DBG_PRINT(("pTjxxhz[%d].m_Zffpfs= %u",i,pTjxxhz->m_Zffpfs)) ;
			
			pTjxxhz->m_Fsfpfs =pSumInvCount->invCount[i].NegInvNum; /*������Ʊ���߷���*/
			DBG_PRINT(("pTjxxhz[%d].m_Fsfpfs= %u",i,pTjxxhz->m_Fsfpfs)) ;
			
			pTjxxhz->m_Fffpfs=pSumInvCount->invCount[i].NegInvCancelNum;/*������Ʊ���Ϸ���*/
			DBG_PRINT(("pTjxxhz[%d].m_Fffpfs= %u",i,pTjxxhz->m_Fffpfs)) ;
			
			pTjxxhz->m_Zsfpljje = double2int(atof(pSumInvCount->invCount[i].InvSum)*JSK_SUM_EXTENSION);
			DBG_PRINT(("pTjxxhz[%d].m_Zsfpljje  = %lld", i,pTjxxhz->m_Zsfpljje));		
			
			
			pTjxxhz->m_Zsfpljse = double2int(atof(pSumInvCount->invCount[i].InvTax)*JSK_SUM_EXTENSION);
			DBG_PRINT(("pTjxxhz[%d].m_Zsfpljse  = %lld", i,pTjxxhz->m_Zsfpljse));
			
			pTjxxhz->m_Fsfpljje = double2int(atof(pSumInvCount->invCount[i].NegInvSum)*JSK_SUM_EXTENSION);
			DBG_PRINT(("pTjxxhz[%d].m_Fsfpljje  = %lld", i,pTjxxhz->m_Fsfpljje));
			
			pTjxxhz->m_Fsfpljse = double2int(atof(pSumInvCount->invCount[i].NegInvTax)*JSK_SUM_EXTENSION);/*������Ʊ�ۼ�˰��*/	
			DBG_PRINT(("pTjxxhz[%d].m_Fsfpljse  = %lld", i,pTjxxhz->m_Fsfpljse));
			
			break;
		}			
	}
	JSK_DelBuf(pJSKSendBuf,pJSKRevBuf);
	return JSK_SUCCESS;	
}

//----------------------------------------------------------
//����	����Ʊ����ת����˰���з�Ʊ��ϸ����
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
void CJSKInfoFunc::InvDetail2Data(CDataInvHead *pInvHead, UINT8 *pDataPtr,UINT32 &nDataLen)
{
	UINT8 i = 0;
	UINT8 j = 0;
	INT32 tmpLen = 0;
	
	INT8 tmpBuf[512];
	UINT32 outLen=0;
	
	//	1-��Ʊ����\n 
	*(pDataPtr+tmpLen) = INVKIND_NAME;
	tmpLen += NEWLINE_LEN;
	
    memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	DBG_PRINT(("tmpLen= %u",tmpLen));
	
	DBG_PRINT(("pInvHead->m_fpdm= %s",pInvHead->m_fpdm.c_str()));
	//2-������\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_fpdm.c_str(),pInvHead->m_fpdm.length());
	tmpLen +=pInvHead->m_fpdm.length();
	DBG_PRINT(("tmpLen= %d",tmpLen));
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//3-��Ʊ����
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
    sprintf(tmpBuf, "%08u", pInvHead->m_fphm);
    memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf, strlen(tmpBuf));
	tmpLen += strlen(tmpBuf);
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	
	//4-��˰������\n 
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	sprintf(tmpBuf, "%u", pInvHead->m_kprq);
	memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf, strlen(tmpBuf));
	tmpLen +=strlen(tmpBuf);
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	
	//5-��������\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_fkdw.c_str(),pInvHead->m_fkdw.length());
	tmpLen +=pInvHead->m_fkdw.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//6-����˰��\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_payerCode.c_str(),pInvHead->m_payerCode.length());
	tmpLen +=pInvHead->m_payerCode.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//7-������ַ�绰\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_gfdzdh.c_str(),pInvHead->m_gfdzdh.length());
	tmpLen +=pInvHead->m_gfdzdh.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//8-���������˺�\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_gfyhzh.c_str(),pInvHead->m_gfyhzh.length());
	tmpLen +=pInvHead->m_gfyhzh.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//9-�������\n 
	// 	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_jqbh.c_str(),pInvHead->m_jqbh.length());
	// 	tmpLen +=pInvHead->m_jqbh.length();
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_sksbbh.c_str(),pInvHead->m_sksbbh.length());
	tmpLen +=pInvHead->m_sksbbh.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//10-��Ҫ��Ʒ����\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_zyspmc.c_str(),pInvHead->m_zyspmc.length());
	tmpLen +=pInvHead->m_zyspmc.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//11-��˰��\n 
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
	
	//12-��������\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_xfmc.c_str(),pInvHead->m_xfmc.length());
	tmpLen +=pInvHead->m_xfmc.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	
	//13-����˰��\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_xfsh.c_str(),pInvHead->m_xfsh.length());
	tmpLen +=pInvHead->m_xfsh.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	
	//14-������ַ�绰\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_xfdzdh.c_str(),pInvHead->m_xfdzdh.length());
	tmpLen +=pInvHead->m_xfdzdh.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//15-���������˺�\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_xfyhzh.c_str(),pInvHead->m_xfyhzh.length());
	tmpLen +=pInvHead->m_xfyhzh.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//16-��Ʊ��\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_sky.c_str(),pInvHead->m_sky.length());
	tmpLen +=pInvHead->m_sky.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	
	//17-������\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_fhr.c_str(),pInvHead->m_fhr.length());
	tmpLen +=pInvHead->m_fhr.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//18-�տ���\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_sky.c_str(),pInvHead->m_sky.length());
	tmpLen +=pInvHead->m_sky.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//19-��ע(Base64����)\n 
	memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
	memcpy((void *)tmpBuf,(void *)(pInvHead->m_backup1.c_str()), pInvHead->m_backup1.length());
	Base64_Encode_2((UINT8 *)tmpBuf, strlen(tmpBuf));
	memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf,strlen(tmpBuf));
	tmpLen +=strlen(tmpBuf);
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	
	if( (pInvHead->m_kplx == JSK_RETURN_INV) || (pInvHead->m_kplx == JSK_WASTE_RET) )
	{
		//20-�ϼƽ��\n 
		DBG_PRINT(("pInvHead->m_kpje= %lld",pInvHead->m_kpje));
		memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
		sprintf(tmpBuf, "-%.2f", ((double)pInvHead->m_kpje)/JSK_SUM_EXTENSION);
		memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf, strlen(tmpBuf));
		tmpLen += strlen(tmpBuf);
		
		memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
		tmpLen +=NEWLINE_LEN;
		
		
		//21-�ϼ�˰��\n 
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
		//20-�ϼƽ��\n 
		DBG_PRINT(("pInvHead->m_kpje= %lld",pInvHead->m_kpje));
		memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
		sprintf(tmpBuf, "%.2f", ((double)pInvHead->m_kpje)/JSK_SUM_EXTENSION);
		memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf, strlen(tmpBuf));
		tmpLen += strlen(tmpBuf);
		
		memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
		tmpLen +=NEWLINE_LEN;
		
		
		//21-�ϼ�˰��\n 
		DBG_PRINT(("pInvHead->m_kpse= %lld",pInvHead->m_kpse));
		memset((void *)tmpBuf,0x00,sizeof(tmpBuf));
		sprintf(tmpBuf, "%.2f", ((double)pInvHead->m_kpse)/JSK_SUM_EXTENSION);
		memcpy((void *)(pDataPtr+tmpLen),(void *)tmpBuf, strlen(tmpBuf));
		tmpLen += strlen(tmpBuf);
	}
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//22-�嵥��־("Y"��"N")\n 
	memcpy((void *)(pDataPtr+tmpLen),pInvHead->m_qdbz.c_str(),pInvHead->m_qdbz.length());
	tmpLen +=pInvHead->m_qdbz.length();
	
	memcpy((void *)(pDataPtr+tmpLen),NEWLINE_COMMAND, NEWLINE_LEN);
	tmpLen +=NEWLINE_LEN;
	
	//��Ʊ��ϸ���嵥�и�ʽ 
	//��Ʒ����(92)+ ����ͺ�(40)+ ������λ(22)+ ����(����18,���21)+ ����(����18,���21)+ ���(����2λС��,���18)+ ˰��(6)+ ˰��(����2λС��,���18)+ ���(8)+ ��Ʊ������(3)+ ��˰�۱�־(3)

	vector<CDataInvDet>::iterator pTempDep;
	for (pTempDep=pInvHead->m_gvector.begin(); pTempDep!=pInvHead->m_gvector.end(); ++pTempDep)
	{
		//��Ʒ����(92)
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPMC_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)pTempDep->m_spmc.c_str(), pTempDep->m_spmc.length());
		tmpLen += JSK_SPMC_LEN;
		//tmpLen +=  pTempDep->m_spmc.length();
		
		//+ ����ͺ�(40)
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_GGXH_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)pTempDep->m_ggxh.c_str(), pTempDep->m_ggxh.length());
		tmpLen += JSK_GGXH_LEN;
		
		//������λ(22)
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_JLDW_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)pTempDep->m_spdw.c_str(), pTempDep->m_spdw.length());
		tmpLen += JSK_JLDW_LEN;
        
		if( (pInvHead->m_kplx == JSK_RETURN_INV) || (pInvHead->m_kplx == JSK_WASTE_RET) )
		{
			//����(����18,���21)
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
			//����(����18,���21)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf,"%.3f",pTempDep->m_spsl);
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPSL_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SPSL_LEN;
		}
		
		//����(����18,���21)
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
			//���(����2λС��,���18)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf, "-%.2f", ((double) pTempDep->m_je)/JSK_SUM_EXTENSION);
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPJE_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SPJE_LEN;
		}
		else
		{
			//���(����2λС��,���18)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf, "%.2f", ((double) pTempDep->m_je)/JSK_SUM_EXTENSION);
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPJE_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SPJE_LEN;
		}
		
		//˰��(6)
		memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
		sprintf(tmpBuf,"%.2f",pTempDep->m_sl);
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SL_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
		tmpLen += JSK_SL_LEN;
		
		if( (pInvHead->m_kplx == JSK_RETURN_INV) || (pInvHead->m_kplx == JSK_WASTE_RET) )
		{
			//˰��(����2λС��,���18)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf, "-%.2f", ((double) pTempDep->m_spse)/JSK_SUM_EXTENSION);
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SE_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SE_LEN;
		}
		else
		{
			//˰��(����2λС��,���18)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf, "%.2f", ((double) pTempDep->m_spse)/JSK_SUM_EXTENSION);			
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SE_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SE_LEN;
		}
		
		// ���(8)
		DBG_PRINT(("pTempDep->m_sphxh = %u", pTempDep->m_sphxh));
		memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
		sprintf(tmpBuf,"%u",pTempDep->m_sphxh);
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPXH_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
		tmpLen += JSK_SPXH_LEN;
		
		//��Ʊ������(3)
		memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
		sprintf(tmpBuf,"%u",pTempDep->m_property);
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_FPXZ_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
		tmpLen += JSK_FPXZ_LEN;
		
		//��˰�۱�־(3)
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
		//��Ʒ����(92)
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPMC_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)pTempDep->m_spmc.c_str(), pTempDep->m_spmc.length());
		tmpLen += JSK_SPMC_LEN;
		
		//+ ����ͺ�(40)
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_GGXH_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)pTempDep->m_ggxh.c_str(), pTempDep->m_ggxh.length());
		tmpLen += JSK_GGXH_LEN;
		
		//������λ(22)
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_JLDW_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)pTempDep->m_spdw.c_str(), pTempDep->m_spdw.length());
		tmpLen += JSK_JLDW_LEN;
        
		if( (pInvHead->m_kplx == JSK_RETURN_INV) || (pInvHead->m_kplx == JSK_WASTE_RET) )
		{
			//����(����18,���21)
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
			//����(����18,���21)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf,"%.3f",pTempDep->m_spsl);
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPSL_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SPSL_LEN;
		}
		
		//����(����18,���21)
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
			//���(����2λС��,���18)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf, "-%.2f", ((double) pTempDep->m_je)/JSK_SUM_EXTENSION);
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPJE_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SPJE_LEN;
		}
		else
		{
			//���(����2λС��,���18)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf, "%.2f", ((double) pTempDep->m_je)/JSK_SUM_EXTENSION);
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPJE_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SPJE_LEN;
		}
		
		//˰��(6)
		memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
		sprintf(tmpBuf,"%.2f",pTempDep->m_sl);
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SL_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
		tmpLen += JSK_SL_LEN;
		
		if( (pInvHead->m_kplx == JSK_RETURN_INV) || (pInvHead->m_kplx == JSK_WASTE_RET) )
		{
			//˰��(����2λС��,���18)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf, "-%.2f", ((double) pTempDep->m_spse)/JSK_SUM_EXTENSION);
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SE_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SE_LEN;
		}
		else
		{
			//˰��(����2λС��,���18)
			memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
			sprintf(tmpBuf, "%.2f", ((double) pTempDep->m_spse)/JSK_SUM_EXTENSION);			
			memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SE_LEN);
			memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
			tmpLen += JSK_SE_LEN;
		}
		
		// ���(8)
		DBG_PRINT(("pTempDep->m_sphxh = %u", pTempDep->m_sphxh));
		memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
		sprintf(tmpBuf,"%u",pTempDep->m_sphxh);
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_SPXH_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
		tmpLen += JSK_SPXH_LEN;
		
		//��Ʊ������(3)
		memset((void *)(tmpBuf), 0x00, sizeof(tmpBuf));
		sprintf(tmpBuf,"%u",pTempDep->m_property);
		memset((void *)(pDataPtr+tmpLen), 0x20, JSK_FPXZ_LEN);
		memcpy((void *)(pDataPtr+tmpLen), (void *)tmpBuf, strlen(tmpBuf));
		tmpLen += JSK_FPXZ_LEN;
		
		//��˰�۱�־(3)
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
//����	����˰���з�Ʊ��ϸ����ת����Ʊ����
//����	��
//���	��
//����ֵ��
//----------------------------------------------------------
void CJSKInfoFunc::Data2InvDetail(INT8 *pDataPtr,CDataInvHead *pInvHead, UINT8 flag)
{
	INT8 chBackupBuf[256];
	memset((void*)chBackupBuf, 0, sizeof(chBackupBuf));	
	UINT8 maxLineNum = 23;		//�����ӽ�˰�̶�ȡ���ݽ�������
	if(flag == 1)
		maxLineNum += 9;		//���ӷ�Ʊ�ϴ�ʱ����Ľ�������
	
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
		case 1: //��Ʊ����
			pInvHead->m_fpzl=tmpStr;
			DBG_PRINT(("pInvHead->m_fpzl= %s",pInvHead->m_fpzl.c_str()));
			break;
		case 2: //��Ʊ����
			pInvHead->m_fpdm=tmpStr;
			DBG_PRINT(("pInvHead->m_fpdm= %s",pInvHead->m_fpdm.c_str()));
			break;
		case 3://��Ʊ����
			pInvHead->m_fphm=atoi(tmpStr.c_str());
			DBG_PRINT(("pInvHead->m_fphm= %u",pInvHead->m_fphm));
			break;
		case 4: //��˰������
			//pInvHead->m_kprq=atoi(tmpStr.c_str());
			break;
		case 5: //��������
			pInvHead->m_fkdw=tmpStr;
			DBG_PRINT(("pInvHead->m_fkdw = %s", pInvHead->m_fkdw.c_str()));
			break;
		case 6: //����˰��
			pInvHead->m_payerCode=tmpStr;
			break;
		case 7: //������ַ�绰
			pInvHead->m_gfdzdh=tmpStr;
			break;
		case 8: //���������˺�
			pInvHead->m_gfyhzh=tmpStr;
			break;
		case 9://�������
			pInvHead->m_jqbh=tmpStr;
			break;
		case 10: //��Ҫ��Ʒ����
			pInvHead->m_zyspmc=tmpStr;
			break;
		case 11: //��˰��
			pInvHead->m_bsq=tmpStr;
			break;	
		case 12: //��������
			pInvHead->m_xfmc=tmpStr;
			break;
		case 13: //����˰��
			pInvHead->m_xfsh=tmpStr;
			break;
		case 14: //������ַ�绰
			pInvHead->m_xfdzdh=tmpStr;
			break;
		case 15: //���������˺�
			pInvHead->m_xfyhzh=tmpStr;
			break;
		case 16://��Ʊ��
			pInvHead->m_sky=tmpStr;
			break;
		case 17://������
			pInvHead->m_fhr=tmpStr;
			break;
		case 18: //�տ���
			pInvHead->m_sky=tmpStr;
			break;
		case 19: //��ע(Base64����)
			sprintf(chBackupBuf, "%s", tmpStr.c_str());
			Base64_Decode_2(chBackupBuf, (int *)&tmpLen);
			pInvHead->m_backup1 = (INT8 *)chBackupBuf;
			//DBG_PRINT(("pInvHead->m_backup1 = %s", pInvHead->m_backup1.c_str()));
			break;
		case 20: //�ϼƽ��
			pInvHead->m_kpje = double2int(atof(tmpStr.c_str()) * JSK_SUM_EXTENSION);
			DBG_PRINT(("pInvHead->m_kpje = %lld", pInvHead->m_kpje));
			break;
		case 21: //�ϼ�˰��
			pInvHead->m_kpse=double2int(atof(tmpStr.c_str()) * JSK_SUM_EXTENSION);
			DBG_PRINT(("pInvHead->m_kpse = %lld", pInvHead->m_kpse));
			break;
		case 22: //�嵥��־("Y"��"N")
			pInvHead->m_qdbz=tmpStr;
			break;
		case 23: //��Ʊ��ϸ��Ϣ
			sprintf(chBuf, "%s", tmpStr.c_str());
			break;
			
		case 24: //��Ʊ����
			pInvHead->m_kprq=atoi(tmpStr.c_str());
			DBG_PRINT(("pInvHead->m_kprq= %u",pInvHead->m_kprq));
			break;
		case 25: //��Ʊʱ��
			pInvHead->m_kpsj=atoi(tmpStr.c_str());
			DBG_PRINT(("pInvHead->m_kpsj= %u",pInvHead->m_kpsj));
			break;
		case 26: //��Ʊ���ʹ���
			pInvHead->m_fplb=atoi(tmpStr.c_str());
			DBG_PRINT(("pInvHead->m_fplb= %u",pInvHead->m_fplb));
			break;
		case 27: //��Ʊ����
			pInvHead->m_kplx=atoi(tmpStr.c_str());
			DBG_PRINT(("pInvHead->m_kplx= %u",pInvHead->m_kplx));
			break;
		case 28: //ԭ��Ʊ����
			pInvHead->m_yfpdm=tmpStr.c_str();
			DBG_PRINT(("pInvHead->m_yfpdm= %s",pInvHead->m_yfpdm.c_str()));
			break;
		case 29: //ԭ��Ʊ����
			pInvHead->m_yfphm=atoi(tmpStr.c_str());
			DBG_PRINT(("pInvHead->m_yfphm= %u",pInvHead->m_yfphm));
			break;
		case 30: //��α��
			pInvHead->m_fwm = tmpStr;
			DBG_PRINT(("pInvHead->m_fwm= %s",pInvHead->m_fwm.c_str()));
			break;
		case 31: //ǩ��
			pInvHead->m_casign = tmpStr;
			//DBG_PRINT(("pInvHead->m_casign= %s",pInvHead->m_casign.c_str()));
			break;
		case 32: //����ʱ��
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
	
	//��Ʊ��Ϣ��ϸ
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
		//��Ʊ����
		pInvDet->m_fpdm = pInvHead->m_fpdm;
		
		//��Ʊ����
        pInvDet->m_fpdm = pInvHead->m_fpdm;
		pInvDet->m_kprq = pInvHead->m_kprq;
		pInvDet->m_kpsj = pInvHead->m_kpsj;
		pInvDet->m_kplx = pInvHead->m_kplx;
		
		//��Ʒ����(92)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Fpmc, JSK_SPMC_LEN);
		ParseData(chBackupBuf);
		pInvDet->m_spmc = chBackupBuf;
		DBG_PRINT(("pInvDet->m_spmc=%s",pInvDet->m_spmc.c_str()));
		
		//����ͺ�(40)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Ggxh, JSK_GGXH_LEN);
		ParseData(chBackupBuf);
		pInvDet->m_ggxh = chBackupBuf;
		DBG_PRINT(("pInvDet->m_ggxh=%s",pInvDet->m_ggxh.c_str()));
		
		//������λ(22)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Jldw, JSK_JLDW_LEN);
		ParseData(chBackupBuf);
		pInvDet->m_spdw = chBackupBuf;
		DBG_PRINT(("pInvDet->m_spdw=%s",pInvDet->m_spdw.c_str()));
		
		//����(����18,���21)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Spsl, JSK_SPSL_LEN);
		pInvDet->m_spsl =atof(chBackupBuf);
		DBG_PRINT(("pInvDet->m_spsl=%.3f",pInvDet->m_spsl));
		
		//����(����18,���21)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Spdj, JSK_SPDJ_LEN);
		tmpdj =atof(chBackupBuf);
		DBG_PRINT(("tmpdj=%.3f",tmpdj));
		
		//���(����2λС��,���18)
		pInvDet->m_je = double2int(atof(pFpmxSum->fpmx[i].Spje) * JSK_SUM_EXTENSION);
		DBG_PRINT(("pInvDet->m_je=%lld",pInvDet->m_je));
		
		// ˰��(6)
		pInvDet->m_sl =atof(pFpmxSum->fpmx[i].SL);
		DBG_PRINT(("pInvDet->m_sl=%.3f",pInvDet->m_sl));
		
		//˰��(����2λС��,���18)
		pInvDet->m_spse = double2int(atof(pFpmxSum->fpmx[i].SE) * JSK_SUM_EXTENSION);
		DBG_PRINT(("pInvDet->m_spse=%lld",pInvDet->m_spse));
		
		//���(8)
		pInvDet->m_sphxh =atoi(pFpmxSum->fpmx[i].Spxh);
		DBG_PRINT(("pInvDet->m_sphxh=%u",pInvDet->m_sphxh));
		
		//��Ʊ������(3)
		pInvDet->m_property =atoi(pFpmxSum->fpmx[i].Fpxz);
		DBG_PRINT(("pInvDet->m_property=%u",pInvDet->m_property));
		
		//��˰�۱�־(3)
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
		
		//��Ʊ����
		pInvDet->m_fpdm = pInvHead->m_fpdm;
		
		//��Ʊ����
        pInvDet->m_fpdm = pInvHead->m_fpdm;
		
		//��Ʒ����(92)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Fpmc, JSK_SPMC_LEN);
		ParseData(chBackupBuf);
		pInvDet->m_spmc = chBackupBuf;
		DBG_PRINT(("pInvDet->m_spmc=%s",pInvDet->m_spmc.c_str()));
		
		//����ͺ�(40)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Ggxh, JSK_GGXH_LEN);
		ParseData(chBackupBuf);
		pInvDet->m_ggxh = chBackupBuf;
		
		//������λ(22)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Jldw, JSK_JLDW_LEN);
		ParseData(chBackupBuf);
		pInvDet->m_spdw = chBackupBuf;
		
		//����(����18,���21)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Spsl, JSK_SPSL_LEN);
		pInvDet->m_spsl =atof(chBackupBuf);
		DBG_PRINT(("pInvDet->m_spsl=%.3f",pInvDet->m_spsl));
		
		//����(����18,���21)
		memset(chBackupBuf, 0, sizeof(chBackupBuf));
		memcpy(chBackupBuf, pFpmxSum->fpmx[i].Spdj, JSK_SPDJ_LEN);
		tmpdj =atof(chBackupBuf);
		DBG_PRINT(("tmpdj=%.3f",tmpdj));
		
		//���(����2λС��,���18)
		pInvDet->m_je = double2int(atof(pFpmxSum->fpmx[i].Spje) * JSK_SUM_EXTENSION);
		DBG_PRINT(("pInvDet->m_je=%lld",pInvDet->m_je));
		
		// ˰��(6)
		pInvDet->m_sl =atof(pFpmxSum->fpmx[i].SL);
		DBG_PRINT(("pInvDet->m_sl=%.3f",pInvDet->m_sl));
		
		//˰��(����2λС��,���18)
		pInvDet->m_spse = double2int(atof(pFpmxSum->fpmx[i].SE) * JSK_SUM_EXTENSION);
		DBG_PRINT(("pInvDet->m_spse=%lld",pInvDet->m_spse));
		
		//���(8)
		pInvDet->m_sphxh =atoi(pFpmxSum->fpmx[i].Spxh);
		DBG_PRINT(("pInvDet->m_sphxh=%u",pInvDet->m_sphxh));
		
		//��Ʊ������(3)
		pInvDet->m_property =atoi(pFpmxSum->fpmx[i].Fpxz);
		DBG_PRINT(("pInvDet->m_property=%u",pInvDet->m_property));
		
		//��˰�۱�־(3)
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



