
#include "OperateDiskProc.h"
#include "YWXmlBase.h"
#include "CGlobalArgLib.h"
#include "GlobalNetArg.h"
#include "commonFunc.h"
#include "VersionConfig.h"

/*
#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
#include "YWXML_SKSBBHCX.h"
#include "YWXML_SKPXXCX.h"
#include "YWXML_BSPXXCX.h"
#include "YWXML_SQSLCX.h"
#include "YWXML_GPXXCX.h"
#include "YWXML_KLBG.h"
#include "YWXML_JKSJCX.h"
#include "YWXML_GPXXXP.h"
#include "YWXML_GPXXXPJS.h"
#include "YWXML_FPKJ.h"
#include "YWXML_FPZF.h"
#include "YWXML_FPCX.h"
#include "YWXML_SKPBSP.h"
#include "YWXML_BSPFPFF.h"
#include "YWXML_BSPFPSH.h"
#include "YWXML_SJCB.h"
#include "YWXML_JKHC.h"
#include "YWXML_TJXXCX.h"
#include "YWXML_LXXXXP.h"
#include "YWXML_FPSSSC.h"
#include "YWXML_FPGX.h"
#include "YWXML_FPDR.h"
#include "YWXML_FJTH.h"
#include "YWXML_BSPFPCX.h"
#include "YWXML_SKSBQTYXXCX.h"
#include "YWXML_BGZSKL.h"
#include "YWXML_FPBL.h"
#include "YWXML_HQLXSJ.h"
#include "YWXML_ERRUPINV.h"

#include "NETXML_WLLQFPJGQR.h"
#include "NETXML_WLLQFP.h"
#include "NETXML_LXXXSC.h"
#endif
*/
#include "NETXML_FPSCJGHQ.h"
#include "NETXML_FPSC.h"
#include "NETXML_QLJS.h"
#include "NETXML_QLJSJGQR.h"
#include "NETXML_WLCB.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

static int g_initParaFlag = 0;

#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
int InitPara(string &strErr)
{
	DBG_PRINT(("==============InitPara Begin================"));
	if(g_initParaFlag == 0)
	{
		CDB *m_db = CDB::GetInstance();
		m_db->Open();
		m_db->Init();
		CommonSleep(300);
		
		UINT8 index;
		for(index = 0; index<DET_ARRAY_LEN; index++)
		{
			s_DetArray[index] = new CInvDet;
			//DBG_PRINT(("s_DetArray[%d] = %x", index, s_DetArray[index]));
			DBG_ASSERT_EXIT((s_DetArray[index] != NULL), (" s_DetArray[index] == NULL!"));
		}
		
		g_globalArgLib = CGlobalArgLib::GetInstance();
		g_gNetArg = CGlobalNetArg::GetInstance();
		g_globalArgLib->InitGlobalArg();
		
		INT8 tmpbuf[64];
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%u", g_globalArgLib->m_corpInfo->m_Kpjhm);
		g_gNetArg->InitGlobalNetArg(g_globalArgLib->m_corpInfo->m_Nsrsbh, "", g_globalArgLib->m_strHashNo, tmpbuf, g_globalArgLib->m_corpInfo->m_Jspsbh, "");
		g_gNetArg->SetZskl(g_globalArgLib->m_strZskl);

		g_initParaFlag = 1;
	}
	DBG_PRINT(("==============InitPara End================"));
}
#endif

void OperateDisk(string sInputInfo, string &sOutputInfo)
{
/*
#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
	DBG_PRINT(("================= Begin OperateDisk() ================="));
	XMLParse xmlInput;
	XMLConstruct xmlOutput;
	string strID;
	Return_Info retInfo;
	INT32 ret = 0;
	INT8 tmpBuf[32];

	if(g_initParaFlag == 0)
	{
		InitPara(retInfo.m_retMsg);
		g_initParaFlag = 1;
	}

	ret = CYWXmlBase::StartYWXml(sInputInfo, &xmlInput, &xmlOutput, strID);
	if(ret != JSK_SUCCESS)
	{
		retInfo.m_retCode = JSK_COMMON_ERR_CODE;
		retInfo.m_retMsg = "解析请求数据错误";
		sOutputInfo = "";
		CYWXmlBase::ErrYWXml(&xmlInput, &xmlOutput, &retInfo, sOutputInfo);
		return;
	}
	DBG_PRINT(("strID ============= %s", strID.c_str()));

	CYWXmlBase *pXmlYW = NULL;

	//第2章 税控收款机与税控设备接口
	if(strID == BUSINESS_YWID_SKSBBH)			//税控设备编号
	{
		pXmlYW = new CSksbbhcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_SKPXXCX)		//税控设备信息查询
	{
		pXmlYW = new CSkpxxcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_SKSBQTYXXCX)	//税控设备其他信息查询
	{
		pXmlYW = new CSksbqtxxcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_BSPXXCX)		//报税盘信息查询
	{
		pXmlYW = new CBspxxcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_JKSJCX)		//监控数据查询
	{
		pXmlYW = new CJksjcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_SQSLCX)		//授权税率查询
	{
		pXmlYW = new CSqslcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_GPXXCX)		//购票信息查询
	{
		pXmlYW = new CGpxxcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_GPXXXP)		//购票信息写盘
	{
		pXmlYW = new CGpxxxp(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_GPXXXPJS)	//购票信息写盘解锁
	{
		pXmlYW = new CGpxxxpjs(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_KLBG)		//口令变更
	{
		pXmlYW = new CKlbg(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_FPKJ)		//发票开具
	{
		pXmlYW = new CFpkj(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_FPZF)		//发票作废
	{
		pXmlYW = new CFpzf(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_FPCX)		//发票查询
	{
		pXmlYW = new CFpcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_SKPBSP)		//税控设备报税盘组合操作
	{
		pXmlYW = new CSkpBsp(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_BSPFPCX)		//报税盘发票查询
	{
		pXmlYW = new CBspfpcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_BSPFPFF)		//发票分发
	{
		pXmlYW = new CBspfpff(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_BSPFPSH)		//发票收回
	{
		pXmlYW = new CBspfpsh(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_SJCB)		//数据抄报
	{
		pXmlYW = new CSjcb(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_JKHC)		//监控回传
	{
		pXmlYW = new CJkhc(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_TJXXCX)		//发票统计信息查询
	{
		pXmlYW = new CTjxxcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_LXXXXP)		//离线信息写盘
	{
		pXmlYW = new CLxxxxp(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_FPSC)		//发票上传
	{
		pXmlYW = new CFpsssc(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_FPGX)		//发票更新
	{
		pXmlYW = new CFpgx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_FPDR)		//发票读入
	{
		pXmlYW = new CFpdr(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_FJTH)		//分机退回
	{
		pXmlYW = new CYWXMLFjth(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_BGZSKL)		//变更证书口令
	{
		pXmlYW = new CBgzskl(&xmlOutput, &xmlInput);
	}
	
	else if(strID == BUSINESS_YWID_FPBL)		//发票补录
	{
		pXmlYW = new CFpbl(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_ERRUPINV)		//发票补录
	{
		pXmlYW = new CErrUpInv(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_HQLXSJ)		//发票补录
	{
		pXmlYW = new CHqlxsj(&xmlOutput, &xmlInput);
	}

	
	ret = pXmlYW->Execute();
	if(pXmlYW != NULL)
		delete pXmlYW;

	sOutputInfo = "";
	ret = CYWXmlBase::OverYWXml(&xmlInput, &xmlOutput, sOutputInfo);

	DBG_PRINT(("================= End OperateDisk() ================="));
#endif
*/
	return;
}

void OperateNet(char* pin,string ip,string port,string serverpath,char* service_id,string nsrsbh, 
				string sInputInfo, string &sOutputInfo,string& Err)
{
#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
	g_gNetArg->SetZskl(pin);
	g_gNetArg->SetNsrsbh(nsrsbh);
	g_gNetArg->SetServId(service_id);
	g_gNetArg->SetServPara(ip, port, serverpath);
#endif

	DBG_PRINT(("================= Begin OperateNet() ================="));
	XMLParse xmlInput;
	XMLConstruct xmlOutput;
	string strID;
	Return_Info retInfo;
	INT32 ret = 0;
	INT8 tmpBuf[32];

	ret = CYWXmlBase::StartYWXml(sInputInfo, &xmlInput, &xmlOutput, strID);
	if(ret != JSK_SUCCESS)
	{
		retInfo.m_retCode = JSK_COMMON_ERR_CODE;
		retInfo.m_retMsg = "解析请求数据错误";
		sOutputInfo = "";
		CYWXmlBase::ErrYWXml(&xmlInput, &xmlOutput, &retInfo, sOutputInfo);
		return;
	}
	DBG_PRINT(("strID ============= %s", strID.c_str()));

	CYWXmlBase *pXmlYW = NULL;

	//第3章 税控收款机与统一受理平台接口
	if(strID == BUSINESS_NETID_FPSSSC)		//发票实时上传
	{
		pXmlYW = new CFpsc(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_NETID_FPSCJGHQ)	//发票上传结果获取
	{
		pXmlYW = new CFpscjghq(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_NETID_WLCB)		//网络抄报
	{
		pXmlYW = new CWlcb(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_NETID_QLJS)		//清零解锁
	{
		pXmlYW = new CQljs(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_NETID_QLJSJGQR)	//清零解锁结果确认
	{
		pXmlYW = new CQljsjgqr(&xmlOutput, &xmlInput);
	}
#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
// 	else if(strID == BUSINESS_NETID_LXXXSC)		//离线信息上传
// 	{
// 		pXmlYW = new CLxxxsc(&xmlOutput, &xmlInput);
// 	}
// 	else if(strID == BUSINESS_NETID_WLLQFP)		//网络领取发票
// 	{
// 		pXmlYW = new CWllqfp(&xmlOutput, &xmlInput);
// 	}
// 	else if(strID == BUSINESS_NETID_WLLQFPJGQR)	//网络领取发票结果确认
// 	{
// 		pXmlYW = new CWllqfpjgqr(&xmlOutput, &xmlInput);
// 	}
// 	else if(strID == BUSINESS_NETID_QYCSXZKJ)	//企业参数下载
// 	{
// 		;
// 	}
#endif
	
	sOutputInfo = "";
	ret = pXmlYW->Execute();
	if(ret != SUCCESS)
	{
		if(pXmlYW->m_sslStrErr.length() > MAX_ERR_MSG_LEN)
			pXmlYW->m_sslStrErr.erase(MAX_ERR_MSG_LEN, pXmlYW->m_sslStrErr.length()-MAX_ERR_MSG_LEN);

		INT8 tmpErrBuf[256];
		memset(tmpErrBuf, 0, sizeof(tmpErrBuf));
		sprintf(tmpErrBuf, "%d:%s", ret, pXmlYW->m_sslStrErr.c_str());
		Err = tmpErrBuf;
//		Err = pXmlYW->m_sslStrErr;
		DBG_PRINT(("Err = %s", Err.c_str()));
		ret = CYWXmlBase::OverYWXml(&xmlInput, &xmlOutput);
	}
	else
	{
		ret = CYWXmlBase::OverYWXml(&xmlInput, &xmlOutput, sOutputInfo);
	}
	if(pXmlYW != NULL)
		delete pXmlYW;


	DBG_PRINT(("================= End OperateNet() ================="));
	return;
}



