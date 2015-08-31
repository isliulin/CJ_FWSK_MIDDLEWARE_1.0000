#include "VersionConfig.h"

#include "TDateTime.h"
#include "commonFunc.h"

#include "SysArgMac.h"
#include "JSKInfoFunc.h"

#include "CSysArg.h"
#include "CInvHead.h"
#include "CRtInv.h"
#include "CInvServ.h"

#include "CGlobalArgLib.h"
#include "JSKManageProc.h"
#include "JSKInvManageProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

CGlobalArgLib* CGlobalArgLib::m_globalArgLib = NULL;
CGlobalArgLib *g_globalArgLib = NULL;
extern UINT8 bidirection;


CGlobalArgLib::CGlobalArgLib()
{
	DBG_PRINT(("进入CGlobalArg::CGlobalArg()"));
	m_corpInfo = new CUserInfo();
	m_curInvVol = new CInvVol();

	m_usermore = new CUserMore();
	m_invKind = new CInvKind();
	m_netPara = new CNetPara();
	
	m_bootStatus = 0;
	m_netOn = 0;

	m_InvServNum = 0;
	m_InvServSum = 0;

	m_updateDate=0;
	m_pthreadFlag = 0;
	m_pthreadErr = "";
	m_pthreadNsrsbh = "";
	m_pthreadJqbh = "";
	m_pthreadSksbbh = "";
	m_pthreadSksbkl = "";
	m_pthreadFplxdm = "";
	m_pthreadKpjh = "";
	
	DBG_PRINT(("退出CGlobalArg::CGlobalArg()"));
}

CGlobalArgLib::~CGlobalArgLib()
{
	if (m_corpInfo != NULL)
	{
		delete m_corpInfo;
		m_corpInfo = NULL;
	}

	if (m_usermore != NULL)
	{
		delete m_usermore;
		m_usermore = NULL;
	}
	
	if (m_curInvVol != NULL)
	{
		delete m_curInvVol;
		m_curInvVol = NULL;
	}

	if (m_invKind != NULL)
	{
		delete m_invKind;
		m_invKind = NULL;
	}

	if (m_netPara != NULL)
	{
		delete m_netPara;
		m_netPara = NULL;
	}
	
	if (m_globalArgLib != NULL)
	{
		delete m_globalArgLib;
		m_globalArgLib = NULL;
	}
}

CGlobalArgLib* CGlobalArgLib::GetInstance()
{
	if (m_globalArgLib == NULL)
	{
		m_globalArgLib = new CGlobalArgLib();
	}

	DBG_RETURN(m_globalArgLib);
}

//--------------------------------------------------
//初始化公共参数值
//--------------------------------------------------
INT32 CGlobalArgLib::InitGlobalArg()
{
	DBG_PRINT(("进入InitGlobalArg函数"));
	
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	string strCurTime;
	
	g_globalArgLib->m_corpInfo->Requery();
	g_globalArgLib->m_corpInfo->LoadOneRecord();
	DBG_PRINT(("m_Nsrsbh = %s", g_globalArgLib->m_corpInfo->m_Nsrsbh.c_str()));
	DBG_PRINT(("m_Nsrmc = %s", g_globalArgLib->m_corpInfo->m_Nsrmc.c_str()));

	g_globalArgLib->m_invKind->Requery();
	g_globalArgLib->m_invKind->LoadOneRecord();
	DBG_PRINT(("m_maxSign = %lld", g_globalArgLib->m_invKind->m_maxSign));
	DBG_PRINT(("m_maxSum = %lld", g_globalArgLib->m_invKind->m_maxSum));
	DBG_PRINT(("m_Lxkjsj = %u", g_globalArgLib->m_invKind->m_Lxkjsj));
	DBG_PRINT(("m_Lxssr = %u", g_globalArgLib->m_invKind->m_Lxssr));

	
	g_globalArgLib->m_netPara->Requery();
	g_globalArgLib->m_netPara->LoadOneRecord();

	InitSysArg();
	CalculateSum();


	//获取可滚动表的记录数
	UINT8 errorcode=0;
    UINT8 nIfRolled=0;
	errorcode = RollData(nIfRolled);
	if(errorcode!= SUCCESS)
	{
		DBG_PRINT((" Roll() error !"));
		DBG_RETURN(errorcode);	
	}


	DBG_PRINT(("退出InitGlobalArg函数"));
	DBG_RETURN(JSK_SUCCESS);
}

UINT8 CGlobalArgLib::CalculateSum()
{
	DBG_ENTER("CGlobalArg::CalculateSum");
	
	string strTmp;
	char chValue[256], chTmpValue[64];
	
	//-----------------------------------------------------------------
	// 计算缓存的正票累计金额
	//-----------------------------------------------------------------	
	//	未上传的正票金额
	CInvServ curInvServ;
	INT64 tmpSum;
	memset((void*)chValue, 0, sizeof(chValue));
	sprintf(chValue, "where I_TYPE = %u", NORMAL_INV);
	
	strTmp = "select sum(M_SUM) from INV_SERV ";
	strTmp.append(chValue);
    curInvServ.SetSQL(strTmp);
	curInvServ.GetOneResult(DB_INT64, (void*)&m_InvServSum); 
	DBG_PRINT(("缓存金额 m_InvServSum= %lld",  m_InvServSum));
	
	m_InvServNum = curInvServ.GetRecordNum();
	DBG_PRINT(("缓存张数 m_InvServNum= %u", m_InvServNum));
	DBG_RETURN(SUCCESS);
}

//------------------------------------------------------
//初始化各个系统值
//------------------------------------------------------
UINT8 CGlobalArgLib::InitSysArg()
{
	DBG_PRINT(("进入CGlobalArg::InitSysArg函数"));
	char tmpChar[32];
	CSysArg cSysArg, *sysArg;
	sysArg = &cSysArg;
	int ret=0;

	sprintf(tmpChar,  "where SA_ID = %d", SYS_MACHINE_INIT_FLAG);
	sysArg->m_filter.append(tmpChar);
	ret = sysArg->Requery();
	DBG_PRINT(("ret : %u", ret));
	ret = sysArg->LoadOneRecord();
	DBG_PRINT(("ret : %u", ret));
	m_initFlag = sysArg->m_vInt;
	DBG_PRINT(("m_initFlag : %u", m_initFlag));

	sprintf(tmpChar,  "where SA_ID = %d", SYS_INIT_DATE);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_initDate = sysArg->m_vInt;
	DBG_PRINT(("m_initDate : %lu", m_initDate));

	sprintf(tmpChar,  "where SA_ID = %d", SYS_INV_DELIVER_FLAG);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_invDeliverFlag = sysArg->m_vInt;
	DBG_PRINT(("m_invDeliverFlag : %u", m_invDeliverFlag));

	sprintf(tmpChar,  "where SA_ID = %d", SYS_DECLARE_FLAG);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_decFlag = sysArg->m_vInt;
	DBG_PRINT(("m_decFlag : %u", m_decFlag));

	sprintf(tmpChar,  "where SA_ID = %d", SYS_BLOCKAGE_DATE);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_decDate = sysArg->m_vInt;					//xsr 疑问：锁死期为啥用m_decDate？
	DBG_PRINT(("m_decDate : %lu", m_decDate));

	sprintf(tmpChar,  "where SA_ID = %d", SYS_FJH);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_fjh = sysArg->m_vInt;
	DBG_PRINT(("m_fjh : %u", m_fjh));

	//-------------------------------------------------------
	// SYSARG表增加二进制部分，日期可按整形或者string来存储
	//-------------------------------------------------------
	sprintf(tmpChar,  "where SA_ID = %d", SYS_INFO_UPDATE_DATE);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_updateDate = sysArg->m_vInt;
	DBG_PRINT(("m_updateDate : %u", m_updateDate));

	//税控设备口令
	sprintf(tmpChar,  "where SA_ID = %d", SYS_SKSB_PWD);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_strSksbkl = sysArg->m_vText;
	DBG_PRINT(("m_strSksbkl : %s", m_strSksbkl.c_str()));
	
	//串口波特率
	sprintf(tmpChar,  "where SA_ID = %d", SYS_SERIAL_BAUDRATE);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	if( sysArg->LoadOneRecord() == SQLITE_OK )
	{
		m_serialBaudRate = sysArg->m_vInt;
	}
	else
	{
		m_serialBaudRate = SERIAL_BAUDRATE;
	}
	DBG_PRINT(("m_serialBaudRate : %u", m_serialBaudRate));

	//证书口令
	sprintf(tmpChar,  "where SA_ID = %d", SYS_ZS_PWD);
	sysArg->m_filter.append(tmpChar);
	sysArg->Requery();
	sysArg->LoadOneRecord();
	m_strZskl = sysArg->m_vText;
	DBG_PRINT(("m_strZskl : %s", m_strZskl.c_str()));

	DBG_PRINT(("退出CGlobalArg::InitSysArg函数"));
	DBG_RETURN(SUCCESS);
}

UINT8 CGlobalArgLib::RollData(UINT8 &nIfRolled)
{
	CInvHead curInvHead;
	CRtInv curRtInv;
	
	UINT8 ret = SUCCESS;
	
	UINT32 nInvDelDate = 0;
	UINT32 nRtDetNo = 0;
	nIfRolled = 0;
	m_invCount = curInvHead.GetInvHeadNum();
	m_rtInvCount = curRtInv.GetRecordNum();

	// 	DBG_PRINT(("第一条明细的日期invDet.m_kprq = %u", countDet.m_kprq));
	DBG_PRINT(("m_invCount = %u", m_invCount));
	DBG_PRINT(("m_rtInvCount = %u", m_rtInvCount));
	
	//TDateTime lastDate(g_globalArgLib->m_startDecDate, 000001);
	//lastDate--;
	UINT32 nRefDate=0;
   // nRefDate = lastDate.FormatInt(YYYYMMDD);//上次申报的截止日期
	
	//判断是否需要滚动，并计算需滚动的记录数量
	ret = curInvHead.CheckRoll(m_invCount, nRefDate,nInvDelDate);
	if (ret!=SUCCESS)
	{
		DBG_RETURN(FAILURE);
	}

	ret = curRtInv.CheckRoll(m_rtInvCount,nRtDetNo);
	if (ret!=SUCCESS)
	{
		DBG_RETURN(FAILURE);
	}

	//掉电保护 滚动数据
	//g_YW_PowerOffData->invRollPwOffData.invDatelimit = nInvDelDate;/**<InvHead表滚动删除的截止日期  */ 
    //g_YW_PowerOffData->invRollPwOffData.sumDatelimit = nSumDelDate;/**<InvSum表滚动删除的截止日期  */  
	//g_YW_PowerOffData->invRollPwOffData.rtNolimit = nRtDetNo;/**<RtInv表滚动删除的截止号码  */   
    //g_YW_PowerOffData->invRollPwOffData.nRefDate = nRefDate; /**<上次申报的截止日期  */ 
    //POWOFF_ENABLE();//开掉电中断	
	
	UINT8 retRoll;
	//BAR_DEF();

	//滚动
	if (nInvDelDate>0)
	{
		//DBG_PRINT(("发票信息整理中..... "));
		//BAR_SHOW("发票信息整理中.....");
		retRoll = curInvHead.Roll(nInvDelDate, nRefDate);//InvHead表滚动
		if (FAILURE==retRoll) 
		{
		//	BAR_SHOW("请重启机器以完成发票整理");
			while (1);
		}
		//CGlobalArg::SysLog(EVENT_INVOICE_ROLL , SUCCESS);		//写系统日志
		m_invCount = curInvHead.GetInvHeadNum();	//InvHead表记录数
		nIfRolled = 1;
	//	BAR_SHOW("发票信息整理完成!");
		DBG_PRINT(("发票信息整理完成!"));
	}	
	
	
	
	if (nRtDetNo>0)
	{
		//DBG_PRINT(("红票信息整理中..... "));
		//BAR_SHOW("红票信息整理中.....");
		curRtInv.Roll(nRtDetNo);//RtInv表滚动
	//	CGlobalArg::SysLog(EVENT_RTINV_ROLL , SUCCESS);//写系统日志
		m_rtInvCount = curRtInv.GetRecordNum();//RtInv表记录数
		nIfRolled = 1;
		//BAR_SHOW("红票信息整理完成!");
		DBG_PRINT(("红票信息整理完成!"));
	}
	
	
	DBG_RETURN(SUCCESS);
}







