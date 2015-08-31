#include "CUniversialSerialCommunicate.h"
#include "SerialConfig.h"
#include "CGlobalArgLib.h"
#include "commonFunc.h"
#include "SysArgMac.h"
#include "CSysArg.h"
#include "DataDesign.h"
#include "IncludeMe.h"
#include "GlobalNetArg.h"
#include "ClearDepotFunc.h"
#include "CInvServ.h"
#include "USBMount.h"
#include "DataClassDesign.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>
//#include <net/if.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/stat.h>
#include <unistd.h>
#include <termios.h>
#include <linux/route.h>
#include <sys/vfs.h>  
#include <signal.h> 
#include <ifaddrs.h> 

CUniversialSerialCommunicate::CUniversialSerialCommunicate() {
	m_serialProtocol = SerialProtocol::getInstance();
}

CUniversialSerialCommunicate::~CUniversialSerialCommunicate() {

}

UINT8 CUniversialSerialCommunicate::handleSerialCMD(){

	switch (m_serialProtocol->m_revCmd->cmdNo)
	{
	case SERIAL_ONLINE_CMD:
		onLine();
		break;
	case SERIAL_SKPBHCX_CMD:
		skpbhcx();
		break;
	case SERIAL_BSPBHCX_CMD:
		bspbhcx();
		break;
	case SERIAL_SKPXXCX_CMD:
		skpxxcx();
		break;
	case SERIAL_BSPXXCX_CMD:
		bspxxcx();
		break;
	case SERIAL_JKSJCX_CMD:
		jksjcx();
		break;
	case SERIAL_SQSLCX_CMD:
		sqslcx();
		break;
	case SERIAL_GPXXCX_CMD:
		gpxxcx();
		break;
	case SERIAL_SKSBKLGG_CMD:
		sksbklgg();
		break;
	case SERIAL_FPKJ_CMD:
		fpkj();
		break;
	case SERIAL_FPZF_CMD:
		fpzf();
		break;
	case SERIAL_FPCX_CMD:
		fpcx();
		break;
	case SERIAL_SKPBSPZHCZ_CMD:
		skpbspzhcz();
		break;
	case SERIAL_BSPFPCX_CMD:
		bspfpcx();
		break;
	case SERIAL_FPFF_CMD:
		fpff();
		break;
	case SERIAL_FPHS_CMD:
		fphs();
		break;
	case SERIAL_SJCB_CMD:
		sjcb();
		break;
	case SERIAL_WLJKHC_CMD:
		wljkhc();
		break;
	case SERIAL_FPTJXXCX_CMD:
		fptjcx();
		break;
	case SERIAL_QYXXGX_CMD:
		qyxxgx();
		break;
	case SERIAL_LXQXGX_CMD:
		lxqxgx();
		break;
	case SERIAL_FPSSSC_CMD:
		fpsssc();
		break;
	case SERIAL_WLCSWH_CMD:
		wlcswh();
		break;
	case SERIAL_SZCKBTL_CMD:
		setBaudRate();
		break;
	case SERIAL_FPDR_CMD:
		fpdr();
		break;
	case SERIAL_FJTH_CMD:
		fjth();
		break;
	case SERIAL_WLGP_CMD:
		wlgp();
		break;
	case SERIAL_ZSKLGG_CMD:
		zsklgg();
		break;
	case SERIAL_FPBL_CMD:
		fpbl();
		break;
	case SERIAL_HQLXSJ_CMD:
		hqlxsj();
		break;
	case SERIAL_ZHQQK_CMD:
		zhqqk();
		break;
	case SERIAL_ERRUPINV_CMD:
		getErrUpInv();
		break;
	case SERIAL_CONNECT_TEST_CMD:
		sslConnectTest();
		break;
        case SERIAL_YYSJ_CMD:
		programUpdate();
		break;
	case SERIAL_SYSTEST_CMD:
		sysTest();
		break;
	case SERIAL_WMAC_CMD:
		writeMAC();
		break;
	case SERIAL_WJQBH_CMD:
		writeMachineNo();
		break;
	default:
		m_serialProtocol->Rsp_ERR(SERCMD_CMDNO_ERR);
		break;
	}
	return SUCCESS;
}

//联机函数
UINT8 CUniversialSerialCommunicate::onLine(){
	DBG_PRINT(("----------联机----------"));
	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//税控盘编号查询
UINT8 CUniversialSerialCommunicate::skpbhcx(){
	DBG_PRINT(("----------税控盘编号查询----------"));
	INT8 jqbh[JQBH_LEN+1];
	memset(jqbh, 0x00, sizeof(jqbh));
	memcpy(jqbh, m_serialProtocol->m_revCmd->revData, JQBH_LEN);
	DBG_PRINT(("jqbh = %s", jqbh));

	g_YwXmlArg->m_sksbkl = "";
	g_YwXmlArg->m_jqbh = jqbh;
	ret = manageFunc.GetSksbbh(*g_YwXmlArg, sksbbhstr, bspbhstr, qtxx, strErr);
	DBG_PRINT(("GetSksbbh ret = %u", ret));
	if (SUCCESS == ret)
	{
		m_serialProtocol->FillParament(sksbbhstr, sksbbhstr.length());
		m_serialProtocol->Rsp_OK();
	} 
	else
	{
		m_serialProtocol->Rsp_ERR(strErr);
	}
	
	return SUCCESS;
}
//报税盘编号查询
UINT8 CUniversialSerialCommunicate::bspbhcx(){
	DBG_PRINT(("----------报税盘编号查询----------"));
	INT8 jqbh[JQBH_LEN+1];
	memset(jqbh, 0x00, sizeof(jqbh));
	memcpy(jqbh, m_serialProtocol->m_revCmd->revData, JQBH_LEN);
	DBG_PRINT(("jqbh = %s", jqbh));

	g_YwXmlArg->m_sksbkl = "";
	g_YwXmlArg->m_jqbh = jqbh;
	ret = manageFunc.GetSksbbh(*g_YwXmlArg, sksbbhstr, bspbhstr, qtxx, strErr);
	if (SUCCESS == ret)
	{
		m_serialProtocol->FillParament(bspbhstr, bspbhstr.length());
		m_serialProtocol->Rsp_OK();
	} 
	else
	{
		m_serialProtocol->Rsp_ERR(strErr);
	}

	return SUCCESS;
}
//税控盘信息查询
UINT8 CUniversialSerialCommunicate::skpxxcx(){
	DBG_PRINT(("----------税控盘信息查询----------"));
	JSPDeviceInfo_Request request;
	memset(&request, 0x00, sizeof(JSPDeviceInfo_Request));
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData, KOULING_LEN);
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+KOULING_LEN, JQBH_LEN);
	DBG_PRINT(("skpkl = %s", (INT8 *)request.skpkl));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));

	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);

	CDataUserInfo dataUserInfo;
	ret = manageFunc.GetTaxpayerInfo(*g_YwXmlArg, dataUserInfo, qtxx, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}
	CDataTransformFunc::Data2UserInfo(&dataUserInfo, g_globalArgLib->m_corpInfo);

	JSPDevice_Response  jspxx;
	memset((void *)&jspxx, 0x00, sizeof(JSPDevice_Response));
	if (SBBH_LEN < g_globalArgLib->m_corpInfo->m_Jspsbh.length())
	{
		strncpy((INT8 *)jspxx.skpbh, g_globalArgLib->m_corpInfo->m_Jspsbh.c_str(), SBBH_LEN);
	} 
	else
	{
		strcpy((INT8 *)jspxx.skpbh, g_globalArgLib->m_corpInfo->m_Jspsbh.c_str());
	}
	
	if (NSRSBH_LEN < g_globalArgLib->m_corpInfo->m_Nsrsbh.length())
	{
		strncpy((INT8 *)jspxx.nsrsbh, g_globalArgLib->m_corpInfo->m_Nsrsbh.c_str(), NSRSBH_LEN);
	} 
	else
	{
		strcpy((INT8 *)jspxx.nsrsbh, g_globalArgLib->m_corpInfo->m_Nsrsbh.c_str());
	}
	
	if (NSRMC_LEN < g_globalArgLib->m_corpInfo->m_Nsrmc.length())
	{
		strncpy((INT8 *)jspxx.nsrmc, g_globalArgLib->m_corpInfo->m_Nsrmc.c_str(), NSRMC_LEN);
	} 
	else
	{
		strcpy((INT8 *)jspxx.nsrmc, g_globalArgLib->m_corpInfo->m_Nsrmc.c_str());
	}
	
	if (SWJGDM_LEN < g_globalArgLib->m_corpInfo->m_Swjgdm.length())
	{
		strncpy((INT8 *)jspxx.swjgdm, g_globalArgLib->m_corpInfo->m_Swjgdm.c_str(), SWJGDM_LEN);
	} 
	else
	{
		strcpy((INT8 *)jspxx.swjgdm, g_globalArgLib->m_corpInfo->m_Swjgdm.c_str());
	}
	
	if (SWJGMC_LEN < g_globalArgLib->m_corpInfo->m_Swjgmc.length())
	{
		strncpy((INT8 *)jspxx.swjgmc, g_globalArgLib->m_corpInfo->m_Swjgmc.c_str(), SWJGMC_LEN);
	}
	else 
	{
		strcpy((INT8 *)jspxx.swjgmc, g_globalArgLib->m_corpInfo->m_Swjgmc.c_str());
	}
	
	if (FPLXDM_A_LEN < g_globalArgLib->m_corpInfo->m_fplxdm.length())
	{
		strncpy((INT8 *)jspxx.fplxdm, g_globalArgLib->m_corpInfo->m_fplxdm.c_str(), FPLXDM_A_LEN);
	} 
	else
	{
		strcpy((INT8 *)jspxx.fplxdm, g_globalArgLib->m_corpInfo->m_fplxdm.c_str());
	}
	
	if (SZSJ_LEN < qtxx.length())
	{
		strncpy((INT8 *)jspxx.dqsz, qtxx.c_str(), SZSJ_LEN);
	} 
	else
	{
		strcpy((INT8 *)jspxx.dqsz, qtxx.c_str());
	}
	
	if (SZSJ_LEN < g_globalArgLib->m_corpInfo->m_qysj.length())
	{
		strncpy((INT8 *)jspxx.qysj, g_globalArgLib->m_corpInfo->m_qysj.c_str(), SZSJ_LEN);
	} 
	else
	{
		strcpy((INT8 *)jspxx.qysj, g_globalArgLib->m_corpInfo->m_qysj.c_str());
	}
	
	if (BBH_LEN < g_globalArgLib->m_corpInfo->m_bbh.length())
	{
		strncpy((INT8 *)jspxx.bbh, g_globalArgLib->m_corpInfo->m_bbh.c_str(), BBH_LEN);
	} 
	else
	{
		strcpy((INT8 *)jspxx.bbh, g_globalArgLib->m_corpInfo->m_bbh.c_str());
	}
	
	sprintf((INT8 *)jspxx.kpjh, "%u", g_globalArgLib->m_corpInfo->m_Kpjhm);
	sprintf((INT8 *)jspxx.qylx, "%03u", g_globalArgLib->m_corpInfo->m_Hylx);
	
	if (BLXX_LEN < g_globalArgLib->m_corpInfo->m_blxx.length())
	{
		strncpy((INT8 *)jspxx.blxx, g_globalArgLib->m_corpInfo->m_blxx.c_str(), BLXX_LEN);
	} 
	else
	{
		strcpy((INT8 *)jspxx.blxx, g_globalArgLib->m_corpInfo->m_blxx.c_str());
	}
	
	if (KZXX_LEN < g_globalArgLib->m_corpInfo->m_qtkzxx.length())
	{
		strncpy((INT8 *)jspxx.qtkzxx, g_globalArgLib->m_corpInfo->m_qtkzxx.c_str(), KZXX_LEN);
	} 
	else
	{
		strcpy((INT8 *)jspxx.qtkzxx, g_globalArgLib->m_corpInfo->m_qtkzxx.c_str());
	}

	g_gNetArg->SetBaseInfo((INT8 *)jspxx.nsrsbh, (INT8 *)jspxx.kpjh, (INT8 *)jspxx.skpbh);

	m_serialProtocol->FillParament(jspxx.skpbh, SBBH_LEN);
	m_serialProtocol->FillParament(jspxx.nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(jspxx.nsrmc, NSRMC_LEN);
	m_serialProtocol->FillParament(jspxx.swjgdm, SWJGDM_LEN);
	m_serialProtocol->FillParament(jspxx.swjgmc, SWJGMC_LEN);
	m_serialProtocol->FillParament(jspxx.fplxdm, FPLXDM_A_LEN);
	m_serialProtocol->FillParament(jspxx.dqsz, SZSJ_LEN);
	m_serialProtocol->FillParament(jspxx.qysj, SZSJ_LEN);
	m_serialProtocol->FillParament(jspxx.bbh, BBH_LEN);
	m_serialProtocol->FillParament(jspxx.kpjh, KPJH_LEN);
	m_serialProtocol->FillParament(jspxx.qylx, QYLX_LEN);
	m_serialProtocol->FillParament(jspxx.blxx, BLXX_LEN);
	m_serialProtocol->FillParament(jspxx.qtkzxx, KZXX_LEN);

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//报税盘信息查询
UINT8 CUniversialSerialCommunicate::bspxxcx(){
	DBG_PRINT(("----------报税盘信息查询----------"));
	BSPDeviceInfo_Request request;
	memset(&request, 0x00, sizeof(BSPDeviceInfo_Request));
	memcpy(request.bspkl, m_serialProtocol->m_revCmd->revData, KOULING_LEN);
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+KOULING_LEN, JQBH_LEN);
	DBG_PRINT(("skpkl = %s", (INT8 *)request.bspkl));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));

	CDataUserInfo userInfo;
	g_YwXmlArg->m_bspkl = (INT8 *)(request.bspkl);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.bspkl);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);
	ret = manageFunc.GetBSPInfo(*g_YwXmlArg, userInfo, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	string curTimeStr="";
//	m_serialProtocol->FillParament(qtxx, SBBH_LEN);
	m_serialProtocol->FillParament(userInfo.m_bspbh, SBBH_LEN);
	m_serialProtocol->FillParament(userInfo.m_Nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(userInfo.m_Nsrmc, NSRMC_LEN);
	m_serialProtocol->FillParament(userInfo.m_Swjgdm, SWJGDM_LEN);
	m_serialProtocol->FillParament(userInfo.m_Swjgmc, SWJGMC_LEN);
	m_serialProtocol->FillParament(curTimeStr, SZSJ_LEN);
	m_serialProtocol->FillParament(userInfo.m_qysj, SZSJ_LEN);
	m_serialProtocol->FillParament(userInfo.m_ffbz, 2);
	m_serialProtocol->FillParament(userInfo.m_bbh, BBH_LEN);
	INT8 tempbuf[KPJH_LEN+1];
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", userInfo.m_Kpjhm);
	m_serialProtocol->FillParament(tempbuf, KPJH_LEN);
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%03u", userInfo.m_Hylx);
	m_serialProtocol->FillParament(tempbuf, QYLX_LEN);
	m_serialProtocol->FillParament(userInfo.m_blxx, BLXX_LEN);

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//监控数据查询
UINT8 CUniversialSerialCommunicate::jksjcx(){
	DBG_PRINT(("----------监控数据查询----------"));
	Common_Request request;
//	memcpy(&request, m_serialProtocol->m_revCmd->revData, sizeof(Common_Request));
	memset(&request, 0x00, sizeof(Common_Request));
	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData, NSRSBH_LEN);
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN, SBBH_LEN);
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN, KOULING_LEN);
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN, FPLXDM_S_LEN);
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN+FPLXDM_S_LEN, JQBH_LEN);
	DBG_PRINT(("nsrsbh = %s", (INT8 *)request.nsrsbh));
	DBG_PRINT(("skpbh = %s", (INT8 *)request.skpbh));
	DBG_PRINT(("skpkl = %s", (INT8 *)request.skpkl));
	DBG_PRINT(("fplxdm = %s", (INT8 *)request.fplxdm));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));

	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);

	CDataInvKind dataInvKind;
	ret = manageFunc.GetJKSJ(*g_YwXmlArg, dataInvKind, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}
	CDataTransformFunc::Data2InvKind(&dataInvKind, g_globalArgLib->m_invKind);

	INT8 tempbuf[ZDYXX_LEN+1];
	//发票类型
	m_serialProtocol->FillParament(g_globalArgLib->m_invKind->m_fplxdm, FPLXDM_S_LEN);
	//开票截止日期
	memset(tempbuf, 0x00, sizeof(tempbuf));
//	sprintf(tempbuf, "%u", g_globalArgLib->m_invKind->m_Lxssr);
	m_serialProtocol->FillParament(tempbuf, DATE_LEN);
//	m_serialProtocol->FillParament(g_globalArgLib->m_invKind->m_kpjzrq.substr(0, SZSJ_LEN), SZSJ_LEN);
	//报税起始、截止日期
	m_serialProtocol->FillParament(g_globalArgLib->m_invKind->m_bsqsrq.substr(0, SZSJ_LEN), SZSJ_LEN);
	m_serialProtocol->FillParament(g_globalArgLib->m_invKind->m_bszzrq.substr(0, SZSJ_LEN), SZSJ_LEN);
	//单张发票限额
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%.2f", (double)(g_globalArgLib->m_invKind->m_maxSign/100.0));
	m_serialProtocol->FillParament(tempbuf, XIANE_LEN);
	//最新报税日期
	memset(tempbuf, 0x00, sizeof(tempbuf));
	m_serialProtocol->FillParament(tempbuf, SZSJ_LEN);
	//剩余容量
	memset(tempbuf, 0x00, sizeof(tempbuf));
	m_serialProtocol->FillParament(tempbuf, SYRL_LEN);
	//上传截止日期
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", g_globalArgLib->m_invKind->m_Lxssr);
	m_serialProtocol->FillParament(tempbuf, SCJZRQ_LEN);
	//离线开票时长
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", g_globalArgLib->m_invKind->m_Lxkjsj);
	m_serialProtocol->FillParament(tempbuf, LXKPSC_LEN);
	//离线开票正数累计金额
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%.2f", (double)(g_globalArgLib->m_invKind->m_maxSum/100.0));
	m_serialProtocol->FillParament(tempbuf, XIANE_LEN);
	//离线开票扩展信息
	m_serialProtocol->FillParament(g_globalArgLib->m_invKind->m_backup, LXKZXX_LEN);
	//自定义信息
	memset(tempbuf, 0x00, sizeof(tempbuf));
	m_serialProtocol->FillParament(tempbuf, ZDYXX_LEN);

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//授权税率查询
UINT8 CUniversialSerialCommunicate::sqslcx(){
	DBG_PRINT(("----------授权税率查询----------"));
	Common_Request request;
	//	memcpy(&request, m_serialProtocol->m_revCmd->revData, sizeof(Common_Request));
	memset(&request, 0x00, sizeof(Common_Request));
	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData, NSRSBH_LEN);
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN, SBBH_LEN);
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN, KOULING_LEN);
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN, FPLXDM_S_LEN);
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN+FPLXDM_S_LEN, JQBH_LEN);
	DBG_PRINT(("nsrsbh = %s", (INT8 *)request.nsrsbh));
	DBG_PRINT(("skpbh = %s", (INT8 *)request.skpbh));
	DBG_PRINT(("skpkl = %s", (INT8 *)request.skpkl));
	DBG_PRINT(("fplxdm = %s", (INT8 *)request.fplxdm));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));

	CDataTax taxArray[MAX_TAX_NUM];
	UINT8 taxNum;
	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);
	ret = manageFunc.GetTaxRateInfo(*g_YwXmlArg, taxArray, taxNum, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	INT8 tempbuf[TAXRATE_LEN+1];
	//发票类型
	m_serialProtocol->FillParament(request.fplxdm, FPLXDM_S_LEN);
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%03u", taxNum);
	m_serialProtocol->FillParament(tempbuf, TAXRATE_NUM_LEN);
	for (int i=0; i<taxNum; i++)
	{
		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%.2f", (double)taxArray[i].m_sl/100);
		m_serialProtocol->FillParament(tempbuf, TAXRATE_LEN);
	}

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//购票信息查询
UINT8 CUniversialSerialCommunicate::gpxxcx(){
	DBG_PRINT(("----------购票信息查询----------"));
	Common_Request request;
	//	memcpy(&request, m_serialProtocol->m_revCmd->revData, sizeof(Common_Request));
	memset(&request, 0x00, sizeof(Common_Request));
	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData, NSRSBH_LEN);
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN, SBBH_LEN);
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN, KOULING_LEN);
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN, FPLXDM_S_LEN);
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN+FPLXDM_S_LEN, JQBH_LEN);
	DBG_PRINT(("nsrsbh = %s", (INT8 *)request.nsrsbh));
	DBG_PRINT(("skpbh = %s", (INT8 *)request.skpbh));
	DBG_PRINT(("skpkl = %s", (INT8 *)request.skpkl));
	DBG_PRINT(("fplxdm = %s", (INT8 *)request.fplxdm));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));

	CDataInvVol invVol;
	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);
	ret = saleFunc.GetCurInvInfo(*g_YwXmlArg, &invVol, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	m_serialProtocol->FillParament(invVol.m_fplxdm, FPLXDM_S_LEN);
	m_serialProtocol->FillParament(invVol.m_code, FPDM_LEN);
	INT8 tempbuf[FPDM_LEN+1];
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%08u", invVol.m_curInvNo);
	m_serialProtocol->FillParament(tempbuf, FPHM_LEN);
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", invVol.m_remain);
	m_serialProtocol->FillParament(tempbuf, FPFS_LEN);

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//口令更改
UINT8 CUniversialSerialCommunicate::sksbklgg(){
	DBG_PRINT(("----------口令更改----------"));
	ChangePWD_Request request;
	memset(&request, 0x00, sizeof(ChangePWD_Request));
	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData, NSRSBH_LEN);
	memcpy(request.sbbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN, SBBH_LEN);
	memcpy(request.ykl, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN, KOULING_LEN);
	memcpy(request.xkl, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN, KOULING_LEN);
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN+KOULING_LEN, JQBH_LEN);
	DBG_PRINT(("nsrsbh = %s", (INT8 *)request.nsrsbh));
	DBG_PRINT(("skpbh = %s", (INT8 *)request.sbbh));
	DBG_PRINT(("ykl = %s", (INT8 *)request.ykl));
	DBG_PRINT(("xkl = %s", (INT8 *)request.xkl));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));

	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.sbbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.ykl);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);
	string ykl = (INT8 *)(request.ykl);
	string xkl = (INT8 *)(request.xkl);
	ret = manageFunc.SKPKLBG(*g_YwXmlArg, ykl, xkl, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//发票开具
UINT8 CUniversialSerialCommunicate::fpkj(){
	DBG_PRINT(("----------发票开具----------"));
	UINT32 offset=0;
	FPKJ_Request request;
	CDataInvHead invHead;
	INT8 tempbuf[32];
	memset((void *)&request, 0x00, sizeof(FPKJ_Request));

	memcpy(request.zskl, m_serialProtocol->m_revCmd->revData+offset, ZSKOULING_LEN);
	offset += ZSKOULING_LEN;
	DBG_PRINT(("证书口令 = %s ", (INT8 *)request.zskl));
	invHead.m_zskl = (INT8 *)(request.zskl);

	memcpy(request.xhdwdm, m_serialProtocol->m_revCmd->revData+offset, NSRSBH_LEN);
	offset += NSRSBH_LEN;
	DBG_PRINT(("销货单位识别号 = %s ", (INT8 *)request.xhdwdm));
	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.xhdwdm);
	invHead.m_xfsh = (INT8 *)(request.xhdwdm);
	
	memcpy(request.xhdwmc, m_serialProtocol->m_revCmd->revData+offset, NSRMC_LEN);
	offset += NSRMC_LEN;
	DBG_PRINT(("销货单位名称 = %s ", (INT8 *)request.xhdwmc));
	g_YwXmlArg->m_nsrmc = (INT8 *)(request.xhdwmc);
	invHead.m_xfmc = (INT8 *)(request.xhdwmc);

	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	DBG_PRINT(("税控盘编号 = %s ", (INT8 *)request.skpbh));
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	invHead.m_sksbbh = (INT8 *)(request.skpbh);

	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	DBG_PRINT(("税控盘口令 = %s ", (INT8 *)request.skpkl));
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);

	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+offset, FPLXDM_S_LEN);
	offset += FPLXDM_S_LEN;
	DBG_PRINT(("发票类型代码 = %s ", (INT8 *)request.fplxdm));
	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
	invHead.m_fplxdm = (INT8 *)(request.fplxdm);

	request.kplx = m_serialProtocol->m_revCmd->revData[offset];
	offset++;
	DBG_PRINT(("开票类型 = %u ", request.kplx));
// 	memset(tempbuf, 0x00, sizeof(tempbuf));
// 	sprintf(tempbuf, "%u", request.kplx);
//	invHead.m_kplx = atoi(tempbuf);
	invHead.m_kplx = request.kplx - 0x30;
	DBG_PRINT(("invHead.m_kplx = %u ", invHead.m_kplx));
	if( (invHead.m_kplx != 0 ) && (invHead.m_kplx != 1) )
	{
		strErr = "开票类型错误!";
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	memcpy(request.ghdwdm, m_serialProtocol->m_revCmd->revData+offset, NSRSBH_LEN);
	offset += NSRSBH_LEN;
	DBG_PRINT(("购货单位识别号 = %s ", (INT8 *)request.ghdwdm));
	invHead.m_payerCode = (INT8 *)(request.ghdwdm); 
	FilterSpace(invHead.m_payerCode);
	if(invHead.m_payerCode == "")
		invHead.m_payerCode = "000000000000000";
	
	memcpy(request.ghdwmc, m_serialProtocol->m_revCmd->revData+offset, NSRMC_LEN);
	offset += NSRMC_LEN;
	DBG_PRINT(("购货单位名称 = %s ", (INT8 *)request.ghdwmc));
	invHead.m_fkdw = (INT8 *)(request.ghdwmc);
	FilterSpace(invHead.m_fkdw);

//	request.xmgs = bin2int(m_serialProtocol->m_revCmd->revData+offset, 4);
	memset(tempbuf, 0x00, sizeof(tempbuf));
	memcpy(tempbuf, m_serialProtocol->m_revCmd->revData+offset, 4);
	offset += 4;
	request.xmgs = atoi(tempbuf);
	DBG_PRINT(("项目个数 = %u ", request.xmgs));
	invHead.m_sphsl = request.xmgs;

	CDataInvDet dataInvDet;
	XMItem item;
	for (int i=0; i<request.xmgs; i++)
	{
		memset(&item, 0x00, sizeof(XMItem));
		dataInvDet.m_sphxh = i+1;
		dataInvDet.m_hsbz = 1;
		dataInvDet.m_property = 0;
		dataInvDet.m_ggxh = "";
		dataInvDet.m_spdw = "件";

//		memcpy(request.items[i].xm, m_serialProtocol->m_revCmd->revData+offset, XMMC_LEN);
		memcpy(item.xm, m_serialProtocol->m_revCmd->revData+offset, XMMC_LEN);
		offset += XMMC_LEN;
		DBG_PRINT(("经营项目 = %s ", (INT8 *)item.xm));
		dataInvDet.m_spmc = (INT8 *)(item.xm);
		FilterSpace(dataInvDet.m_spmc);
		DBG_PRINT(("dataInvDet.m_spmc == %s", dataInvDet.m_spmc.c_str()));

//		memcpy(request.items[i].dj, m_serialProtocol->m_revCmd->revData+offset, DJ_LEN);
		memcpy(item.dj, m_serialProtocol->m_revCmd->revData+offset, DJ_LEN);
		offset += DJ_LEN;
		DBG_PRINT(("单价 = %s ", (INT8 *)item.dj));
		dataInvDet.m_dj = atof((INT8 *)item.dj);
		DBG_PRINT(("dataInvDet.m_dj == %lf", dataInvDet.m_dj));

		memcpy(item.sl, m_serialProtocol->m_revCmd->revData+offset, SL_LEN);
		offset += SL_LEN;
		DBG_PRINT(("数量 = %s ", (INT8 *)item.sl));
		dataInvDet.m_spsl = atof((INT8 *)item.sl);	
		DBG_PRINT(("dataInvDet.m_spsl == %lf", dataInvDet.m_spsl));

		memcpy(item.je, m_serialProtocol->m_revCmd->revData+offset, JE_LEN);
		offset += JE_LEN;
		DBG_PRINT(("金额 = %s ", (INT8 *)item.je));
		dataInvDet.m_je = double2int(atof((INT8 *)item.je)*SUM_EXTENSION);	
		DBG_PRINT(("dataInvDet.m_je == %lld", dataInvDet.m_je));

		memcpy(item.zsl, m_serialProtocol->m_revCmd->revData+offset, TAXRATE_LEN);
		offset += TAXRATE_LEN;
		DBG_PRINT(("税率 = %s ", (INT8 *)item.zsl));
		dataInvDet.m_sl = (float)atof((INT8 *)item.zsl);	
		DBG_PRINT(("dataInvDet.m_sl == %f", dataInvDet.m_sl));

		memcpy(item.se, m_serialProtocol->m_revCmd->revData+offset, TAX_LEN);
		offset += TAX_LEN;
		DBG_PRINT(("税额 = %s ", (INT8 *)item.se));
		dataInvDet.m_spse = double2int(atof((INT8 *)item.se)*SUM_EXTENSION);	
		DBG_PRINT(("dataInvDet.m_spse == %lld", dataInvDet.m_spse));

		//含税单价
		memcpy(item.hsdj, m_serialProtocol->m_revCmd->revData+offset, JE_LEN);
		offset += JE_LEN;
		DBG_PRINT(("含税单价 = %s ", (INT8 *)item.hsdj));
		dataInvDet.m_spdj = atof((INT8 *)item.hsdj);
		DBG_PRINT(("dataInvDet.m_spdj == %lf", dataInvDet.m_spdj));

		//含税金额
		memcpy(item.hsje, m_serialProtocol->m_revCmd->revData+offset, JE_LEN);
		offset += JE_LEN;
		DBG_PRINT(("含税金额 = %s ", (INT8 *)item.hsje));
		dataInvDet.m_spje = double2int(atof((INT8 *)item.hsje)*SUM_EXTENSION);	
		DBG_PRINT(("dataInvDet.m_spje == %lld", dataInvDet.m_spje));

		invHead.m_gvector.push_back(dataInvDet);
	}
	memcpy(request.hjje, m_serialProtocol->m_revCmd->revData+offset, JE_LEN);
	offset += JE_LEN;
	DBG_PRINT(("合计金额 = %s ", (INT8 *)request.hjje));
	invHead.m_kpje = double2int(atof((INT8 *)request.hjje)*SUM_EXTENSION);	
	DBG_PRINT(("invHead.m_kpje == %lld", invHead.m_kpje));

	memcpy(request.hjse, m_serialProtocol->m_revCmd->revData+offset, JE_LEN);
	offset += JE_LEN;
	DBG_PRINT(("合计税额 = %s ", (INT8 *)request.hjse));
	invHead.m_kpse = double2int(atof((INT8 *)request.hjse)*SUM_EXTENSION);	
	DBG_PRINT(("invHead.m_kpse == %lld", invHead.m_kpse));

	memcpy(request.jshj, m_serialProtocol->m_revCmd->revData+offset, JE_LEN);
	offset += JE_LEN;
	DBG_PRINT(("价税合计 = %s ", (INT8 *)request.jshj));
	invHead.m_kphjje = double2int(atof((INT8 *)request.jshj)*SUM_EXTENSION);	
	DBG_PRINT(("invHead.m_kphjje == %lld", invHead.m_kphjje));

	memcpy(request.bz, m_serialProtocol->m_revCmd->revData+offset, BZ_LEN);
	offset += BZ_LEN;
	DBG_PRINT(("备注 = %s ", (INT8 *)request.bz));
	invHead.m_backup1 = (INT8 *)request.bz;
	FilterSpace(invHead.m_backup1);

	memcpy(request.skr, m_serialProtocol->m_revCmd->revData+offset, RYMC_LEN);
	offset += RYMC_LEN;
	DBG_PRINT(("收款人 = %s ", (INT8 *)request.skr));
	invHead.m_sky = (INT8 *)request.skr;
	FilterSpace(invHead.m_sky);

//	if (KPLX_FSFP == request.kplx)
//	{
		memcpy(request.yfpdm, m_serialProtocol->m_revCmd->revData+offset, FPDM_LEN);
		offset += FPDM_LEN;
		DBG_PRINT(("原发票代码 = %s ", (INT8 *)request.yfpdm));
		invHead.m_yfpdm = (INT8 *)request.yfpdm;

		memcpy(request.yfphm, m_serialProtocol->m_revCmd->revData+offset, FPHM_LEN);
		offset += FPHM_LEN;
		DBG_PRINT(("原发票号码 = %s ", (INT8 *)request.yfphm));
		invHead.m_yfphm = atoi((INT8 *)request.yfphm);
//	}
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+offset, JQBH_LEN);
	offset += JQBH_LEN;
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);
	invHead.m_jqbh = (INT8 *)(request.jqbh);

	ret = saleFunc.MakeNormalInv(*g_YwXmlArg, &invHead, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	m_serialProtocol->FillParament(invHead.m_fplxdm, FPLXDM_S_LEN);
	m_serialProtocol->FillParament(invHead.m_fpdm, FPDM_LEN);
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%08u", invHead.m_fphm);
	m_serialProtocol->FillParament(tempbuf, FPHM_LEN);
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%08u%06u", invHead.m_kprq, invHead.m_kpsj);

	m_serialProtocol->FillParament(tempbuf, SZSJ_LEN);

	m_serialProtocol->FillParament(invHead.m_fwm, SKM_SHORT_LEN);
	//签名值
	m_serialProtocol->FillParament(invHead.m_casign, SIGN_LEN);

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//发票作废
UINT8 CUniversialSerialCommunicate::fpzf(){
	DBG_PRINT(("----------发票作废----------"));
	UINT32 offset=0;
	FPZF_Request request;
	memset((void *)&request, 0x00, sizeof(FPZF_Request));

	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData+offset, NSRSBH_LEN);
	offset += NSRSBH_LEN;
	DBG_PRINT(("纳税人识别号 = %s ", (INT8 *)request.nsrsbh));
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	DBG_PRINT(("税控盘编号 = %s ", (INT8 *)request.skpbh));
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	DBG_PRINT(("税控盘口令 = %s ", (INT8 *)request.skpkl));
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+offset, FPLXDM_S_LEN);
	offset += FPLXDM_S_LEN;
	DBG_PRINT(("发票类型代码 = %s ", (INT8 *)request.fplxdm));

	memcpy(request.zskl, m_serialProtocol->m_revCmd->revData+offset, ZSKOULING_LEN);
	offset += ZSKOULING_LEN;
	DBG_PRINT(("证书口令 = %s ", (INT8 *)request.zskl));

	request.zflx = m_serialProtocol->m_revCmd->revData[offset];
	offset++;
	request.zflx = request.zflx - 0x30;
	DBG_PRINT(("作废类型 = %u ", request.zflx));
	if( (request.zflx != 0 ) && (request.zflx != 1) )
	{
		strErr = "作废类型错误!";
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	memcpy(request.fpdm, m_serialProtocol->m_revCmd->revData+offset, FPDM_LEN);
	offset += FPDM_LEN;
	DBG_PRINT(("发票代码 = %s ", (INT8 *)request.fpdm));
	memcpy(request.fphm, m_serialProtocol->m_revCmd->revData+offset, FPHM_LEN);
	offset += FPHM_LEN;
	DBG_PRINT(("发票号码 = %s ", (INT8 *)request.fphm));

	memcpy(request.zfr, m_serialProtocol->m_revCmd->revData+offset, RYMC_LEN);
	offset += RYMC_LEN;
	DBG_PRINT(("作废人 = %s ", (INT8 *)request.zfr));
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+offset, JQBH_LEN);
	offset += JQBH_LEN;
	DBG_PRINT(("机器编号 = %s ", (INT8 *)request.jqbh));
	
	CDataInvHead invHead;
	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);
	invHead.m_fplxdm = (INT8 *)(request.fplxdm);
	invHead.m_jqbh = (INT8 *)(request.jqbh);
	invHead.m_sksbbh = (INT8 *)(request.skpbh);
	if (WASTE_YKFP == request.zflx)
	{
		invHead.m_fpdm = (INT8 *)request.fpdm;
		invHead.m_fphm = atoi((INT8 *)request.fphm);
	}
	invHead.m_zskl = (INT8 *)(request.zskl);
	invHead.m_sky = (INT8 *)request.zfr;

	ret = saleFunc.MakeWasteInv(*g_YwXmlArg, &invHead, request.zflx, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	m_serialProtocol->FillParament(invHead.m_fplxdm, FPLXDM_S_LEN);
	INT8 tempbuf[32];
	memset(tempbuf, 0x00, sizeof(tempbuf));
	m_serialProtocol->FillParament(invHead.m_fpdm, FPDM_LEN);
	sprintf(tempbuf, "%08u", invHead.m_fphm);
	m_serialProtocol->FillParament(tempbuf, FPHM_LEN);
	
// 	memset(tempbuf, 0x00, sizeof(tempbuf));
// 	sprintf(tempbuf, "%08u%06u", invHead.m_kprq, invHead.m_kpsj);
// 	m_serialProtocol->FillParament(tempbuf, SZSJ_LEN);
	m_serialProtocol->FillParament(invHead.m_zfsj, SZSJ_LEN);

	//签名值
	m_serialProtocol->FillParament(invHead.m_casign, SIGN_LEN);

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//发票查询
UINT8 CUniversialSerialCommunicate::fpcx(){
	DBG_PRINT(("----------发票查询----------"));
	UINT32 offset=0;
	FPCX_Request request;
	memset((void *)&request, 0x00, sizeof(FPCX_Request));

	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData+offset, NSRSBH_LEN);
	offset += NSRSBH_LEN;
	DBG_PRINT(("纳税人识别号 = %s ", (INT8 *)request.nsrsbh));
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	DBG_PRINT(("税控盘编号 = %s ", (INT8 *)request.skpbh));
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	DBG_PRINT(("税控盘口令 = %s ", (INT8 *)request.skpkl));
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+offset, FPLXDM_S_LEN);
	offset += FPLXDM_S_LEN;
	DBG_PRINT(("发票类型代码 = %s ", (INT8 *)request.fplxdm));
	request.cxfs = m_serialProtocol->m_revCmd->revData[offset];
	offset++;
	DBG_PRINT(("查询方式 = %u ", request.cxfs));
	request.cxfs = request.cxfs - 0x30;
	memcpy(request.cxtj, m_serialProtocol->m_revCmd->revData+offset, CXTJ_LEN);
	offset += CXTJ_LEN;
	DBG_PRINT(("查询条件 = %s ", (INT8 *)request.cxtj));

	UINT32 invNum;
	CDataInvHead invHead;
	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
	string cxtj = (INT8 *)request.cxtj;

	ret = saleFunc.GetInvHeadInfo(*g_YwXmlArg, request.cxfs, cxtj, invNum, &invHead, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	INT8 tempbuf[32];
	m_serialProtocol->FillParament(invHead.m_fpdm, FPDM_LEN);
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%08u", invHead.m_fphm);
	m_serialProtocol->FillParament(tempbuf, FPHM_LEN);
	UINT8 fpzt=0;
	switch(invHead.m_kplx)
	{
	case JSK_NORMAL_INV:
		fpzt = 0;
		break;
	case JSK_RETURN_INV:
		fpzt = 1;
		break;
	case JSK_WASTE_INV:
		fpzt = 2;
		break;
	case JSK_WASTE_NOR:
		fpzt = 3;
		break;
	case JSK_WASTE_RET:
		fpzt = 4;
		break;
	}
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%02u", fpzt);
	m_serialProtocol->FillParament(tempbuf, 2);
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%02u", invHead.m_scbz);
	m_serialProtocol->FillParament(tempbuf, 2);
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%08u", invHead.m_kprq);
	m_serialProtocol->FillParament(tempbuf, DATE_LEN);
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%06u", invHead.m_kpsj);
	m_serialProtocol->FillParament(tempbuf, TIME_LEN);

	m_serialProtocol->FillParament(invHead.m_fwm, SKM_SHORT_LEN);
	//税控设备编号
	m_serialProtocol->FillParament(g_YwXmlArg->m_sksbbh, SBBH_LEN);

	//收款单位
//	m_serialProtocol->FillParament(g_globalArgLib->m_corpInfo->m_Nsrmc, NSRMC_LEN);
	m_serialProtocol->FillParament(g_globalArgLib->m_corpInfo->m_Nsrsbh, NSRSBH_LEN);
	m_serialProtocol->FillParament(g_globalArgLib->m_corpInfo->m_Nsrmc, NSRMC_LEN);
	m_serialProtocol->FillParament(invHead.m_payerCode, NSRSBH_LEN);
	m_serialProtocol->FillParament(invHead.m_fkdw, NSRMC_LEN);
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", invHead.m_sphsl);
	m_serialProtocol->FillParament(tempbuf, 4);
// 	CInvDet *pInvDet = invHead.pHead;
// 	for (int j=1; j<=invHead.m_sphsl; j++, pInvDet = pInvDet->pNext)
	vector<CDataInvDet>::iterator pInvDet;
	for (pInvDet=invHead.m_gvector.begin(); pInvDet!=invHead.m_gvector.end(); ++pInvDet)
	{
		DBG_PRINT(("pInvDetp->m_spmc : %s", pInvDet->m_spmc.c_str()));
		m_serialProtocol->FillParament(pInvDet->m_spmc, XMMC_LEN);

		memset(tempbuf, 0, sizeof(tempbuf));
		sprintf(tempbuf, "%.3lf", pInvDet->m_dj);
		DBG_PRINT(("pInvDet->m_dj : %s", tempbuf));
		m_serialProtocol->FillParament(tempbuf, DJ_LEN);

		memset(tempbuf, 0, sizeof(tempbuf));
		sprintf(tempbuf, "%.3lf", pInvDet->m_spsl);
		DBG_PRINT(("pInvDet->m_spsl : %s", tempbuf));
		m_serialProtocol->FillParament(tempbuf, SL_LEN);

		memset(tempbuf, 0, sizeof(tempbuf));
		sprintf(tempbuf, "%.2lf", ((double)pInvDet->m_je*1.0)/SUM_EXTENSION);
		DBG_PRINT(("pInvDet->m_je : %s", tempbuf));
		m_serialProtocol->FillParament(tempbuf, JE_LEN);

		memset(tempbuf, 0, sizeof(tempbuf));
		sprintf(tempbuf, "%.2lf", (double)pInvDet->m_sl);
		DBG_PRINT(("pInvDet->m_sl : %s", tempbuf));
		m_serialProtocol->FillParament(tempbuf, TAXRATE_LEN);

		memset(tempbuf, 0, sizeof(tempbuf));
		sprintf(tempbuf, "%.2lf", ((double)pInvDet->m_spse*1.0)/SUM_EXTENSION);
		DBG_PRINT(("pInvDet->m_spse : %s", tempbuf));
		m_serialProtocol->FillParament(tempbuf, TAX_LEN);

		memset(tempbuf, 0, sizeof(tempbuf));
		sprintf(tempbuf, "%.3lf", pInvDet->m_spdj);
		DBG_PRINT(("pInvDet->m_spdj : %s", tempbuf));
		m_serialProtocol->FillParament(tempbuf, JE_LEN);

		memset(tempbuf, 0, sizeof(tempbuf));
		sprintf(tempbuf, "%.2lf", ((double)pInvDet->m_spje*1.0)/SUM_EXTENSION);
		DBG_PRINT(("pInvDet->m_spje : %s", tempbuf));
		m_serialProtocol->FillParament(tempbuf, JE_LEN);
	}
	
	memset(tempbuf, 0, sizeof(tempbuf));
	sprintf(tempbuf, "%.2lf", ((double)invHead.m_kpje*1.0)/SUM_EXTENSION);
	DBG_PRINT(("pInvInfo->m_kpje : %s", tempbuf));
	m_serialProtocol->FillParament(tempbuf, JE_LEN);

	memset(tempbuf, 0, sizeof(tempbuf));
	sprintf(tempbuf, "%.2lf", ((double)invHead.m_kpse*1.0)/SUM_EXTENSION);
	DBG_PRINT(("pInvInfo->m_kpse : %s", tempbuf));
	m_serialProtocol->FillParament(tempbuf, JE_LEN);

	memset(tempbuf, 0, sizeof(tempbuf));
	sprintf(tempbuf, "%.2lf", ((double)invHead.m_kphjje*1.0)/SUM_EXTENSION);
	DBG_PRINT(("pInvInfo->m_kphjje : %s", tempbuf));
	m_serialProtocol->FillParament(tempbuf, JE_LEN);

	DBG_PRINT(("pInvInfo->m_backup1 : %s", invHead.m_backup1.c_str()));
	m_serialProtocol->FillParament(invHead.m_backup1, BZ_LEN);

	DBG_PRINT(("pInvInfo->m_sky : %s", invHead.m_sky.c_str()));
	m_serialProtocol->FillParament(invHead.m_sky, RYMC_LEN);

	// 		construct->AddNode(construct->m_parentElement[4], "kpr");
	// 		construct->AddText(pInvInfo->m_sky);
	// 		DBG_PRINT(("pInvInfo->m_sky : %s", pInvInfo->m_sky.c_str()));

	DBG_PRINT(("pInvInfo->m_yfpdm : %s", invHead.m_yfpdm.c_str()));
	m_serialProtocol->FillParament(invHead.m_yfpdm, FPDM_LEN);

	memset(tempbuf, 0, sizeof(tempbuf));
	sprintf(tempbuf, "%08u",invHead.m_yfphm);
	DBG_PRINT(("pInvInfo->m_yfphm : %s", tempbuf));
	m_serialProtocol->FillParament(tempbuf, FPHM_LEN);

	//作废日期
	memset(tempbuf, 0, sizeof(tempbuf));
	if( (invHead.m_kplx == JSK_WASTE_INV) || (invHead.m_kplx == JSK_WASTE_NOR) || (invHead.m_kplx == JSK_WASTE_RET) )
	{
		sprintf(tempbuf, "%08u%06u",invHead.m_kprq, invHead.m_kpsj);
	}
	DBG_PRINT(("buf : %s", tempbuf));
	m_serialProtocol->FillParament(tempbuf, SZSJ_LEN);

	//作废人
	m_serialProtocol->FillParament(invHead.m_sky, RYMC_LEN);

	//已开负数金额	
	memset(tempbuf, 0, sizeof(tempbuf));
	if(invHead.m_kplx == JSK_RETURN_INV)
	{
		sprintf(tempbuf, "%.2f", ((double)invHead.m_kphjje)/SUM_EXTENSION);
	}
	DBG_PRINT(("buf : %s", tempbuf));
	m_serialProtocol->FillParament(tempbuf, JE_LEN);

	//签名值
	m_serialProtocol->FillParament(invHead.m_casign, SIGN_LEN);
	
	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//税控盘报税盘组合操作
UINT8 CUniversialSerialCommunicate::skpbspzhcz(){
	DBG_PRINT(("----------税控盘报税盘组合操作----------"));
	UINT32 offset=0;
	JSPBSPZHCZ_Request request;
	memset((void *)&request, 0x00, sizeof(JSPBSPZHCZ_Request));

	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData+offset, NSRSBH_LEN);
	offset += NSRSBH_LEN;
	DBG_PRINT(("纳税人识别号 = %s ", (INT8 *)request.nsrsbh));
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	DBG_PRINT(("税控盘编号 = %s ", (INT8 *)request.skpbh));
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	DBG_PRINT(("税控盘口令 = %s ", (INT8 *)request.skpkl));
	memcpy(request.bspbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	DBG_PRINT(("报税盘编号 = %s ", (INT8 *)request.bspbh));
	memcpy(request.bspkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	DBG_PRINT(("报税盘口令 = %s ", (INT8 *)request.bspkl));

	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+offset, FPLXDM_S_LEN);
	offset += FPLXDM_S_LEN;
	DBG_PRINT(("发票类型代码 = %s ", (INT8 *)request.fplxdm));

	request.czlx = m_serialProtocol->m_revCmd->revData[offset];
	offset++;
	DBG_PRINT(("request.czlx = %u ", request.czlx));
	UINT8 jzlx = request.czlx - 0x30;
	DBG_PRINT(("操作类型 = = %u",jzlx));

	memcpy(request.hzxx, m_serialProtocol->m_revCmd->revData+offset, HZXX_LEN);
	offset += HZXX_LEN;
	DBG_PRINT(("汇总信息 = %s ", (INT8 *)request.hzxx));
	memcpy(request.qtxx, m_serialProtocol->m_revCmd->revData+offset, ZH_QTXX_LEN);
	offset += ZH_QTXX_LEN;
	DBG_PRINT(("汇总信息 = %s ", (INT8 *)request.qtxx));

	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+offset, JQBH_LEN);
	offset += JQBH_LEN;
	DBG_PRINT(("机器编号 = %s ", (INT8 *)request.jqbh));

	
	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_bspbh = (INT8 *)(request.bspbh);
	g_YwXmlArg->m_bspkl = (INT8 *)(request.bspkl);
	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);

	DBG_PRINT(("jzlx= %u",jzlx));
	if (jzlx ==SKPBSP_CZLX_SJCB)
	{
		//1：数据抄报(报税盘)
		ret = decFunc.DeclareProc(*g_YwXmlArg, jzlx, strErr);
	}
	else if (jzlx ==SKPBSP_CZLX_QLJS)
	{
		//2：清零解锁
		ret = decFunc.UpdateTaxProc(*g_YwXmlArg, strErr);
	}
	else if (jzlx ==SKPBSP_CZLX_FXGPXX)
	{	
		//3：反写购票信息
		strErr = "金税盘不支持该操作";
		ret = FAILURE;
	}
	else if (jzlx ==SKPBSP_CZLX_JZSZ)
	{
		//4：校准税控设备时钟
		strErr = "金税盘不支持该操作";
		ret = FAILURE;
	}

	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}
	
	m_serialProtocol->Rsp_OK();
	return SUCCESS;

}
//报税盘发票查询
UINT8 CUniversialSerialCommunicate::bspfpcx(){
	DBG_PRINT(("----------报税盘发票查询----------"));
	BSPFPCX_Request request;
	memset(&request, 0x00, sizeof(BSPFPCX_Request));
	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData, NSRSBH_LEN);
	memcpy(request.bspbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN, SBBH_LEN);
	memcpy(request.bspkl, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN, KOULING_LEN);
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN, FPLXDM_S_LEN);
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN+FPLXDM_S_LEN, JQBH_LEN);
	DBG_PRINT(("nsrsbh = %s", (INT8 *)request.nsrsbh));
	DBG_PRINT(("bspbh = %s", (INT8 *)request.bspbh));
	DBG_PRINT(("bspkl = %s", (INT8 *)request.bspkl));
	DBG_PRINT(("fplxdm = %s", (INT8 *)request.fplxdm));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));

	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.bspbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.bspkl);
	g_YwXmlArg->m_bspbh = (INT8 *)(request.bspbh);
	g_YwXmlArg->m_bspkl = (INT8 *)(request.bspkl);
	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);
	CDataInvVol invVol[INV_MAX_NUM];
	UINT32 volCount = INV_MAX_NUM;
	UINT8 i=0;
	for (i=0; i< volCount; i++)
	{
		invVol[i].ResetVol();
	}
	ret = invFunc.BSPFPCXPro(*g_YwXmlArg, volCount, invVol, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	INT8 tempbuf[32];
	DBG_PRINT(("获取的发票卷数为：volCount = %u", volCount));
	m_serialProtocol->FillParament(invVol[0].m_fplxdm, FPLXDM_S_LEN);
	DBG_PRINT(("发票类型代码：%s", invVol[0].m_fplxdm.c_str()));
	
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%03u", volCount);
	m_serialProtocol->FillParament(tempbuf, FPJFS_LEN);
	DBG_PRINT(("数量： %s", tempbuf));

	for(i=0; i<volCount; i++)
	{

		m_serialProtocol->FillParament(invVol[i].m_code, FPDM_LEN);
		DBG_PRINT(("发票代码：invVol[%u].m_code %s", i, invVol[i].m_code.c_str()));

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%08u", invVol[i].m_isno);
		m_serialProtocol->FillParament(tempbuf, FPHM_LEN);
		DBG_PRINT(("发票起始号码：%s", tempbuf));

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%08u", invVol[i].m_ieno);
		m_serialProtocol->FillParament(tempbuf, FPHM_LEN);
		DBG_PRINT(("发票终止号码：%s", tempbuf));

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%u", invVol[i].m_fpzfs);
		m_serialProtocol->FillParament(tempbuf, FPFS_LEN);
		DBG_PRINT(("发票领购份数： %s", tempbuf));

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%u", invVol[i].m_remain);
		m_serialProtocol->FillParament(tempbuf, FPFS_LEN);
		DBG_PRINT(("剩余份数：%s", tempbuf));

// 		memset(tempbuf, 0x00, sizeof(tempbuf));
// 		sprintf(tempbuf, "%u", invVol[i].m_buyDate);
		m_serialProtocol->FillParament(invVol[i].m_buyDate, DATE_LEN);
		DBG_PRINT(("领购日期：%s", tempbuf));
	
		memset(tempbuf, 0x00, sizeof(tempbuf));
		m_serialProtocol->FillParament(tempbuf, RYMC_LEN);
		DBG_PRINT(("领购人员：%s", tempbuf));
	}

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//发票分发
UINT8 CUniversialSerialCommunicate::fpff(){
	DBG_PRINT(("----------发票分发----------"));
	UINT32 offset=0;
	FPFF_Request request;
	memset((void *)&request, 0x00, sizeof(FPFF_Request));

	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData+offset, NSRSBH_LEN);
	offset += NSRSBH_LEN;
	DBG_PRINT(("纳税人识别号 = %s ", (INT8 *)request.nsrsbh));
	request.jzlx = m_serialProtocol->m_revCmd->revData[offset];
	request.jzlx -= 0x30;
	offset++;
	DBG_PRINT(("介质类型 = %u ", request.jzlx));
	memcpy(request.bspbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	DBG_PRINT(("报税盘编号 = %s ", (INT8 *)request.bspbh));
	memcpy(request.bspkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	DBG_PRINT(("报税盘口令 = %s ", (INT8 *)request.bspkl));
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	DBG_PRINT(("税控盘编号 = %s ", (INT8 *)request.skpbh));
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	DBG_PRINT(("税控盘口令 = %s ", (INT8 *)request.skpkl));
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+offset, FPLXDM_S_LEN);
	offset += FPLXDM_S_LEN;
	DBG_PRINT(("发票类型代码 = %s ", (INT8 *)request.fplxdm));
	memcpy(request.fpdm, m_serialProtocol->m_revCmd->revData+offset, FPDM_LEN);
	offset += FPDM_LEN;
	DBG_PRINT(("发票代码 = %s ", (INT8 *)request.fpdm));
	memcpy(request.qshm, m_serialProtocol->m_revCmd->revData+offset, FPHM_LEN);
	offset += FPHM_LEN;
	DBG_PRINT(("起始号码 = %s ", (INT8 *)request.qshm));
	memcpy(request.fpfs, m_serialProtocol->m_revCmd->revData+offset, FPFS_LEN);
	offset += FPFS_LEN;
	DBG_PRINT(("发票份数 = %s ", (INT8 *)request.fpfs));
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+offset, JQBH_LEN);
	offset += JQBH_LEN;
	DBG_PRINT(("机器编号 = %s ", (INT8 *)request.jqbh));

	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_bspbh = (INT8 *)(request.bspbh);
	g_YwXmlArg->m_bspkl = (INT8 *)(request.bspkl);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);
	CDataInvVol invVol;
	invVol.m_fplxdm = (INT8 *)(request.fplxdm);
	invVol.m_code = (INT8 *)request.fpdm;
	invVol.m_isno = atoi((INT8 *)request.qshm);
	invVol.m_fpzfs = atoi((INT8 *)request.fpfs);
	ret = invFunc.ZJInvDistribute(*g_YwXmlArg, &invVol, request.jzlx, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//发票回收
UINT8 CUniversialSerialCommunicate::fphs(){
	DBG_PRINT(("----------发票回收----------"));
	UINT32 offset=0;
	FPHS_Request request;
	memset((void *)&request, 0x00, sizeof(FPHS_Request));

	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData+offset, NSRSBH_LEN);
	offset += NSRSBH_LEN;
	DBG_PRINT(("纳税人识别号 = %s ", (INT8 *)request.nsrsbh));
	request.jzlx = m_serialProtocol->m_revCmd->revData[offset];
	request.jzlx -= 0x30;
	offset++;
	DBG_PRINT(("介质类型 = %u ", request.jzlx));
	memcpy(request.bspbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	DBG_PRINT(("报税盘编号 = %s ", (INT8 *)request.bspbh));
	memcpy(request.bspkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	DBG_PRINT(("报税盘口令 = %s ", (INT8 *)request.bspkl));
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	DBG_PRINT(("税控盘编号 = %s ", (INT8 *)request.skpbh));
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	DBG_PRINT(("税控盘口令 = %s ", (INT8 *)request.skpkl));
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+offset, FPLXDM_S_LEN);
	offset += FPLXDM_S_LEN;
	DBG_PRINT(("发票类型代码 = %s ", (INT8 *)request.fplxdm));
	memcpy(request.fpdm, m_serialProtocol->m_revCmd->revData+offset, FPDM_LEN);
	offset += FPDM_LEN;
	DBG_PRINT(("发票代码 = %s ", (INT8 *)request.fpdm));
	memcpy(request.qshm, m_serialProtocol->m_revCmd->revData+offset, FPHM_LEN);
	offset += FPHM_LEN;
	DBG_PRINT(("起始号码 = %s ", (INT8 *)request.qshm));
	memcpy(request.fpfs, m_serialProtocol->m_revCmd->revData+offset, FPFS_LEN);
	offset += FPFS_LEN;
	DBG_PRINT(("发票份数 = %s ", (INT8 *)request.fpfs));
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+offset, JQBH_LEN);
	offset += JQBH_LEN;
	DBG_PRINT(("机器编号 = %s ", (INT8 *)request.jqbh));

	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_bspbh = (INT8 *)(request.bspbh);
	g_YwXmlArg->m_bspkl = (INT8 *)(request.bspkl);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);
	CDataInvVol invVol;
	invVol.m_fplxdm = (INT8 *)(request.fplxdm);
	invVol.m_code = (INT8 *)request.fpdm;
	invVol.m_isno = atoi((INT8 *)request.qshm);
	invVol.m_fpzfs = atoi((INT8 *)request.fpfs);
	if(invVol.m_fpzfs <= 0)
	{
		m_serialProtocol->Rsp_ERR("发票份数不能为0!");
		return FAILURE;
	}
	ret = invFunc.ZJInvRecover(*g_YwXmlArg, &invVol, request.jzlx, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//数据抄报
UINT8 CUniversialSerialCommunicate::sjcb(){
	DBG_PRINT(("----------数据抄报----------"));
	Common_Request request;
	UINT8 jzlx=0;
	memset(&request, 0x00, sizeof(Common_Request));
	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData, NSRSBH_LEN);
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN, SBBH_LEN);
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN, KOULING_LEN);
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN, FPLXDM_S_LEN);
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN+FPLXDM_S_LEN, JQBH_LEN);
	jzlx = m_serialProtocol->m_revCmd->revData[NSRSBH_LEN+SBBH_LEN+KOULING_LEN+FPLXDM_S_LEN+JQBH_LEN];
	jzlx = jzlx - 0x30;
	memcpy(request.kpjh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN+FPLXDM_S_LEN+JQBH_LEN+1, KPJH_LEN);
	DBG_PRINT(("nsrsbh = %s", (INT8 *)request.nsrsbh));
	DBG_PRINT(("skpbh = %s", (INT8 *)request.skpbh));
	DBG_PRINT(("skpkl = %s", (INT8 *)request.skpkl));
	DBG_PRINT(("fplxdm = %s", (INT8 *)request.fplxdm));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));
	DBG_PRINT(("jzlx = %u", jzlx));
	DBG_PRINT(("kpjh = %s", (INT8 *)request.kpjh));

	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);
	g_YwXmlArg->m_kpjh = (INT8 *)(request.kpjh);
// 	INT8 tmpbuf[32];
// 	memset(tmpbuf, 0, sizeof(tmpbuf));
// 	sprintf(tmpbuf, "%u", g_globalArgLib->m_corpInfo->m_Kpjhm);
// 	g_YwXmlArg->m_kpjh = tmpbuf;

	if(jzlx == 1)
	{
		ret = decFunc.NetDeclareProc(*g_YwXmlArg, strErr);
	}
	else if(jzlx ==2)
	{
		ret = decFunc.DeclareProc(*g_YwXmlArg, jzlx, strErr);
	}
	DBG_PRINT(("ret = %d", ret));
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//网络监控回传
UINT8 CUniversialSerialCommunicate::wljkhc(){
	DBG_PRINT(("----------网络监控回传----------"));
	Common_Request request;
	memset(&request, 0x00, sizeof(Common_Request));
	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData, NSRSBH_LEN);
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN, SBBH_LEN);
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN, KOULING_LEN);
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN, FPLXDM_S_LEN);
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN+FPLXDM_S_LEN, JQBH_LEN);
	memcpy(request.kpjh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN+FPLXDM_S_LEN+JQBH_LEN, KPJH_LEN);
	DBG_PRINT(("nsrsbh = %s", (INT8 *)request.nsrsbh));
	DBG_PRINT(("skpbh = %s", (INT8 *)request.skpbh));
	DBG_PRINT(("skpkl = %s", (INT8 *)request.skpkl));
	DBG_PRINT(("fplxdm = %s", (INT8 *)request.fplxdm));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));
	DBG_PRINT(("kpjh = %s", (INT8 *)request.kpjh));

	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);
	g_YwXmlArg->m_kpjh = (INT8 *)(request.kpjh);
// 	INT8 tmpbuf[32];
// 	memset(tmpbuf, 0, sizeof(tmpbuf));
// 	sprintf(tmpbuf, "%u", g_globalArgLib->m_corpInfo->m_Kpjhm);
// 	g_YwXmlArg->m_kpjh = tmpbuf;

	ret = decFunc.NetUpdateTaxProc(*g_YwXmlArg, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//发票统计信息查询
UINT8 CUniversialSerialCommunicate::fptjcx(){
	DBG_PRINT(("----------发票统计信息查询----------"));
	FPTJ_Request request;
	memset(&request, 0x00, sizeof(FPTJ_Request));
	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData, NSRSBH_LEN);
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN, SBBH_LEN);
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN, KOULING_LEN);
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN, FPLXDM_S_LEN);
	memcpy(request.qsrq, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN+FPLXDM_S_LEN, DATE_LEN);
	memcpy(request.zzrq, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN+FPLXDM_S_LEN+DATE_LEN, DATE_LEN);
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN+FPLXDM_S_LEN+DATE_LEN+DATE_LEN, JQBH_LEN);
	DBG_PRINT(("nsrsbh = %s", (INT8 *)request.nsrsbh));
	DBG_PRINT(("skpbh = %s", (INT8 *)request.skpbh));
	DBG_PRINT(("skpkl = %s", (INT8 *)request.skpkl));
	DBG_PRINT(("fplxdm = %s", (INT8 *)request.fplxdm));
	DBG_PRINT(("qsrq = %s", (INT8 *)request.qsrq));
	DBG_PRINT(("zzrq = %s", (INT8 *)request.zzrq));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));

	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);

	CDataTjxxhz Tjxxhz[12];

	Tjxxhz[0].m_Qsrq = (UINT32)atoi((INT8 *)request.qsrq);
	Tjxxhz[0].m_Jzrq = (UINT32)atoi((INT8 *)request.zzrq);
	INT32 Monthcount = 12;

	FPTJ_Reponse response;
	memset(&response, 0x00, sizeof(FPTJ_Reponse));
// 	CInvVol invVol;
// 	invVol.m_fplxdm = (INT8 *)(request.fplxdm);
// 	invVol.m_code = (INT8 *)request.fpdm;
// 	invVol.m_isno = atoi((INT8 *)request.qshm);
// 	invVol.m_fpzfs = atoi((INT8 *)request.fpfs);

	ret = invFunc.TJXXCXPro(*g_YwXmlArg, Monthcount, Tjxxhz, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}
	INT8 tempbuf[ZDYXX_LEN+1];
	m_serialProtocol->FillParament(g_YwXmlArg->m_fplxdm, FPLXDM_S_LEN);
	m_serialProtocol->FillParament(response.sl, ITEM_COUNT_LEN);
	for (INT32 tempi=0; tempi<Monthcount; tempi++)
	{
		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%u", Tjxxhz[tempi].m_Qsrq);
		m_serialProtocol->FillParament(tempbuf, DATE_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%u", Tjxxhz[tempi].m_Jzrq);
		m_serialProtocol->FillParament(tempbuf, DATE_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%u", Tjxxhz[tempi].m_Qckcfs);
		m_serialProtocol->FillParament(tempbuf, FPZS_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%u", Tjxxhz[tempi].m_Lgfpfs);
		m_serialProtocol->FillParament(tempbuf, FPZS_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%u", Tjxxhz[tempi].m_Thfpfs);
		m_serialProtocol->FillParament(tempbuf, FPZS_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%u", Tjxxhz[tempi].m_Zsfpfs);
		m_serialProtocol->FillParament(tempbuf, FPZS_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%u", Tjxxhz[tempi].m_Zffpfs);
		m_serialProtocol->FillParament(tempbuf, FPZS_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%u", Tjxxhz[tempi].m_Fsfpfs);
		m_serialProtocol->FillParament(tempbuf, FPZS_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%u", Tjxxhz[tempi].m_Fffpfs);
		m_serialProtocol->FillParament(tempbuf, FPZS_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%u", Tjxxhz[tempi].m_Kffpfs);
		m_serialProtocol->FillParament(tempbuf, FPZS_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%u", Tjxxhz[tempi].m_Qmkcfs);
		m_serialProtocol->FillParament(tempbuf, FPZS_LEN);

		DBG_PRINT(("Tjxxhz[%d].m_Zsfpljje= %lld",tempi,Tjxxhz[tempi].m_Zsfpljje));
		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%.2f", ((double)Tjxxhz[tempi].m_Zsfpljje/SUM_EXTENSION));
		m_serialProtocol->FillParament(tempbuf, JE_LEN);

		DBG_PRINT(("Tjxxhz[%d].m_Zsfpljse= %lld",tempi,Tjxxhz[tempi].m_Zsfpljse));
		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%.2f", ((double)Tjxxhz[tempi].m_Zsfpljse/SUM_EXTENSION));
		m_serialProtocol->FillParament(tempbuf, JE_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%.2f", ((double)Tjxxhz[tempi].m_Zffpljje/SUM_EXTENSION));
		m_serialProtocol->FillParament(tempbuf, JE_LEN);
		
		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%.2f", ((double)Tjxxhz[tempi].m_Zffpljse/SUM_EXTENSION));
		m_serialProtocol->FillParament(tempbuf, JE_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%.2f", ((double)Tjxxhz[tempi].m_Fsfpljje/SUM_EXTENSION));
		m_serialProtocol->FillParament(tempbuf, JE_LEN);
		
		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%.2f", ((double)Tjxxhz[tempi].m_Fsfpljse/SUM_EXTENSION));
		m_serialProtocol->FillParament(tempbuf, JE_LEN);
		
		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%.2f", ((double)Tjxxhz[tempi].m_Fffpljje/SUM_EXTENSION));
		m_serialProtocol->FillParament(tempbuf, JE_LEN);
		
		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%.2f", ((double)Tjxxhz[tempi].m_Fffpljse/SUM_EXTENSION));
		m_serialProtocol->FillParament(tempbuf, JE_LEN);
	}

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//企业信息更新
UINT8 CUniversialSerialCommunicate::qyxxgx(){
	DBG_PRINT(("----------企业信息更新----------"));
	Common_Request request;
	memset(&request, 0x00, sizeof(Common_Request));
	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData, NSRSBH_LEN);
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN, SBBH_LEN);
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN, KOULING_LEN);
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN, FPLXDM_S_LEN);
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN+FPLXDM_S_LEN, JQBH_LEN);
	DBG_PRINT(("nsrsbh = %s", (INT8 *)request.nsrsbh));
	DBG_PRINT(("skpbh = %s", (INT8 *)request.skpbh));
	DBG_PRINT(("skpkl = %s", (INT8 *)request.skpkl));
	DBG_PRINT(("fplxdm = %s", (INT8 *)request.fplxdm));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//离线权限更新
UINT8 CUniversialSerialCommunicate::lxqxgx(){
	DBG_PRINT(("----------离线权限更新----------"));
	LXQXGX_Request request;
	memset(&request, 0x00, sizeof(LXQXGX_Request));
	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData, NSRSBH_LEN);
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN, SBBH_LEN);
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN, KOULING_LEN);
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN, FPLXDM_S_LEN);
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN+FPLXDM_S_LEN, JQBH_LEN);
	memcpy(request.kpjh, m_serialProtocol->m_revCmd->revData+NSRSBH_LEN+SBBH_LEN+KOULING_LEN+FPLXDM_S_LEN+JQBH_LEN, KPJH_LEN);
	DBG_PRINT(("nsrsbh = %s", (INT8 *)request.nsrsbh));
	DBG_PRINT(("skpbh = %s", (INT8 *)request.skpbh));
	DBG_PRINT(("skpkl = %s", (INT8 *)request.skpkl));
	DBG_PRINT(("fplxdm = %s", (INT8 *)request.fplxdm));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));
	DBG_PRINT(("kpjh = %s", (INT8 *)request.kpjh));

	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);
	g_YwXmlArg->m_kpjh = (INT8 *)(request.kpjh);
// 	INT8 tmpbuf[32];
// 	memset(tmpbuf, 0, sizeof(tmpbuf));
// 	sprintf(tmpbuf, "%u", g_globalArgLib->m_corpInfo->m_Kpjhm);
// 	g_YwXmlArg->m_kpjh = tmpbuf;

	ret = manageFunc.LXXXUpdatePro(*g_YwXmlArg, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	m_serialProtocol->Rsp_OK();
	return SUCCESS;

}
//发票实时上传
UINT8 CUniversialSerialCommunicate::fpsssc(){
	DBG_PRINT(("----------发票实时上传----------"));
	FPSSSC_Request request;
	UINT32 offset=0;
	memset(&request, 0x00, sizeof(FPSSSC_Request));

	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData, NSRSBH_LEN);
	offset += NSRSBH_LEN;
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+offset, FPLXDM_S_LEN);
	offset += FPLXDM_S_LEN;
	memcpy(request.fpzs, m_serialProtocol->m_revCmd->revData+offset, FPZS_LEN);
	offset += FPZS_LEN;
	request.czlx = m_serialProtocol->m_revCmd->revData[offset];
	request.czlx -= 0x30;
	offset++;
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+offset, JQBH_LEN);
	offset += JQBH_LEN;
	memcpy(request.kpjh, m_serialProtocol->m_revCmd->revData+offset, KPJH_LEN);
	DBG_PRINT(("nsrsbh = %s", (INT8 *)request.nsrsbh));
	DBG_PRINT(("skpbh = %s", (INT8 *)request.skpbh));
	DBG_PRINT(("skpkl = %s", (INT8 *)request.skpkl));
	DBG_PRINT(("fplxdm = %s", (INT8 *)request.fplxdm));
	DBG_PRINT(("fpzs = %s", (INT8 *)request.fpzs));
	DBG_PRINT(("czlx = %u", request.czlx));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));
	DBG_PRINT(("kpjh = %s", (INT8 *)request.kpjh));

// 	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
// 	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
// 	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
// 	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
// 	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);
	g_globalArgLib->m_pthreadNsrsbh = (INT8 *)(request.nsrsbh);
	g_globalArgLib->m_pthreadSksbbh = (INT8 *)(request.skpbh);
	g_globalArgLib->m_pthreadSksbkl = (INT8 *)(request.skpkl);
	g_globalArgLib->m_pthreadFplxdm = (INT8 *)(request.fplxdm);
	g_globalArgLib->m_pthreadJqbh = (INT8 *)(request.jqbh);
	g_globalArgLib->m_pthreadKpjh = (INT8 *)(request.kpjh);

	if(g_globalArgLib->m_InvServNum <= 0)
	{
		strErr = "所有发票都已上传!";
		m_serialProtocol->Rsp_ERR(strErr);
		return SUCCESS;
	}

	if(	g_globalArgLib->m_pthreadFlag == 0)
	{
		g_globalArgLib->m_pthreadFlag = 1;
	}
	else
	{
		g_globalArgLib->m_pthreadFlag = 0;
		strErr = "停止发票上传";
		m_serialProtocol->Rsp_ERR(strErr);
		return SUCCESS;
	}

	DBG_PRINT(("g_globalArgLib->m_pthreadFlag = %u", g_globalArgLib->m_pthreadFlag));
// 	ret = saleFunc.InvoiceUpload(*g_YwXmlArg, strErr);
// 	if (SUCCESS != ret)
// 	{
// 		m_serialProtocol->Rsp_ERR(strErr);
// 		return FAILURE;
// 	}

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//网络参数维护
UINT8 CUniversialSerialCommunicate::wlcswh(){
	DBG_PRINT(("----------设置网络参数----------"));
	NetWorkInfo_Request request;
	UINT32 offset=0;
	memset(&request, 0x00, sizeof(NetWorkInfo_Request));

	request.isdhcp = m_serialProtocol->m_revCmd->revData[offset];
	request.isdhcp -= 0x30;
	offset++;
	memcpy(request.local_ip, m_serialProtocol->m_revCmd->revData+offset, IP_LEN);
	offset += IP_LEN;
	memcpy(request.local_defaultgate, m_serialProtocol->m_revCmd->revData+offset, GATE_LEN);
	offset += GATE_LEN;
	memcpy(request.local_netmask, m_serialProtocol->m_revCmd->revData+offset, MASK_LEN);
	offset += MASK_LEN;
	memcpy(request.local_dnsnameip, m_serialProtocol->m_revCmd->revData+offset, DNS_LEN);
	offset += DNS_LEN;
	memcpy(request.server_ipaddr, m_serialProtocol->m_revCmd->revData+offset, IP_LEN);
	offset += IP_LEN;
	memcpy(request.server_port, m_serialProtocol->m_revCmd->revData+offset, PORT_LEN);
	offset += PORT_LEN;
	memcpy(request.application_name, m_serialProtocol->m_revCmd->revData+offset, FWQBSLJ_LEN);
	offset += FWQBSLJ_LEN;
	memcpy(request.ftp_serverip, m_serialProtocol->m_revCmd->revData+offset, IP_LEN);
	offset += IP_LEN;
	memcpy(request.ftp_port, m_serialProtocol->m_revCmd->revData+offset, PORT_LEN);
	offset += PORT_LEN;
	memcpy(request.ftp_username, m_serialProtocol->m_revCmd->revData+offset, USERNAME_LEN);
	offset += USERNAME_LEN;
	memcpy(request.ftp_passwd, m_serialProtocol->m_revCmd->revData+offset, PASSWORD_LEN);

	DBG_PRINT(("request.isdhcp = %u", request.isdhcp));
	DBG_PRINT(("request.local_ip = %s", request.local_ip));
	DBG_PRINT(("request.local_defaultgate = %s", request.local_defaultgate));
	DBG_PRINT(("request.local_netmask = %s", request.local_netmask));
	DBG_PRINT(("request.local_dnsnameip = %s", request.local_dnsnameip));
	DBG_PRINT(("request.server_ipaddr = %s", request.server_ipaddr));
	DBG_PRINT(("request.server_port = %s", request.server_port));
	DBG_PRINT(("request.application_name = %s", request.application_name));
	DBG_PRINT(("request.ftp_serverip = %s", request.ftp_serverip));
	DBG_PRINT(("request.ftp_port = %s", request.ftp_port));
	DBG_PRINT(("request.ftp_username = %s", request.ftp_username));
	DBG_PRINT(("request.ftp_passwd = %s", request.ftp_passwd));

	if (0 == request.isdhcp)
	{
		if (0 >= if_a_string_is_a_valid_ipv4_address((INT8 *)(request.local_ip)))
		{
			m_serialProtocol->Rsp_ERR("local_ip is unvalid");
			return FAILURE;
		}
		if (0 >= if_a_string_is_a_valid_ipv4_address((INT8 *)(request.local_defaultgate)))
		{
			m_serialProtocol->Rsp_ERR("local_defaultgate is unvalid");
			return FAILURE;
		}
		if (0 >= if_a_string_is_a_valid_ipv4_address((INT8 *)(request.local_netmask)))
		{
			m_serialProtocol->Rsp_ERR("local_netmask is unvalid");
			return FAILURE;
		}
		if (0 >= if_a_string_is_a_valid_ipv4_address((INT8 *)(request.local_dnsnameip)))
		{
			m_serialProtocol->Rsp_ERR("local_dnsnameip is unvalid");
			return FAILURE;
		}
		if (0 >= if_a_string_is_a_valid_ipv4_address((INT8 *)(request.server_ipaddr)))
		{
			m_serialProtocol->Rsp_ERR("server_ipaddr is unvalid");
			return FAILURE;
		}
		if (0 >= if_a_string_is_a_valid_ipv4_address((INT8 *)(request.ftp_serverip)))
		{
			m_serialProtocol->Rsp_ERR("ftp_serverip is unvalid");
			return FAILURE;
		}
	}

	g_globalArgLib->m_netPara->m_IsDhcp = request.isdhcp;
	g_globalArgLib->m_netPara->m_LocalIP = (INT8 *)(request.local_ip);
	g_globalArgLib->m_netPara->m_LocalGate = (INT8 *)(request.local_defaultgate);
	g_globalArgLib->m_netPara->m_LocalMask = (INT8 *)(request.local_netmask);
	g_globalArgLib->m_netPara->m_LocalDNS = (INT8 *)(request.local_dnsnameip);
	g_globalArgLib->m_netPara->m_ServIP = (INT8 *)(request.server_ipaddr);
	g_globalArgLib->m_netPara->m_ServPort = (INT8 *)(request.server_port);
	g_globalArgLib->m_netPara->m_ServAddr = (INT8 *)(request.application_name);
	g_globalArgLib->m_netPara->m_FtpIP = (INT8 *)(request.ftp_serverip);
	g_globalArgLib->m_netPara->m_FtpPort = (INT8 *)(request.ftp_port);
	g_globalArgLib->m_netPara->m_FtpUser = (INT8 *)(request.ftp_username);
	g_globalArgLib->m_netPara->m_FtpPwd = (INT8 *)(request.ftp_passwd);

	CDataNetPara dataNetPara;
	CDataTransformFunc::NetPara2Data(g_globalArgLib->m_netPara, &dataNetPara);
	ret = manageFunc.NetParaManage(*g_YwXmlArg, g_globalArgLib->m_netPara, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	//设置本机网络
	setNetWork(request.isdhcp, (INT8 *)request.local_ip, (INT8 *)request.local_netmask, (INT8 *)request.local_defaultgate, (INT8 *)request.local_dnsnameip);
	g_gNetArg->SetServPara(g_globalArgLib->m_netPara->m_ServIP, g_globalArgLib->m_netPara->m_ServPort, g_globalArgLib->m_netPara->m_ServAddr);

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}
//设置串口波特率
UINT8 CUniversialSerialCommunicate::setBaudRate(){
	DBG_PRINT(("----------设置波特率----------"));
	INT8 btl[16];
	int baud=0, i=0;
	int speed_arr[] = {B115200, B57600, B38400, B19200, B9600, B4800, B2400, B1200, B300};
	int name_arr[] = {115200, 57600, 38400,  19200,  9600,  4800,  2400,  1200,  300};

	memset(btl, 0x00, sizeof(btl));
	memcpy(btl, m_serialProtocol->m_revCmd->revData, 6);
	baud = atoi(btl);
	DBG_PRINT(("baud = %d", baud));

	for (i= 0; i < sizeof(speed_arr)/sizeof(int); i++)
	{
		if  (baud == name_arr[i])
		{
			DBG_PRINT(("找到了波特率name_arr[%d] = %d", i, name_arr[i]));
			break;
		}
	}
	if (i >= sizeof(speed_arr) / sizeof(int))
	{

		DBG_PRINT(("没有该波特率!!!!!!!!!!!!!!!!!!!!!"));
		m_serialProtocol->Rsp_ERR("转换器没找到该波特率!");
		return FAILURE;
	} 

		CSysArg sysArg;
		INT8 sqlbuf[128];
		sysArg.m_vInt = baud;
		memset(sqlbuf, 0, sizeof(sqlbuf));
		sprintf(sqlbuf, "where SA_ID = %u", SYS_SERIAL_BAUDRATE);
	if(sysArg.Update(sqlbuf, &sysArg.m_vInt, NULL) != SQLITE_OK)
	{
		m_serialProtocol->Rsp_ERR("串口波特率保存失败");
		return FAILURE;
	}
		
	g_globalArgLib->m_serialBaudRate = baud;

	m_serialProtocol->Rsp_OK();

	//关闭并重新打开串口
	m_serialProtocol->ReleasePort();
	INT8 ret = m_serialProtocol->InitPort(SERIAL_DEVICE, baud); 
	if(ret != SUCCESS)
	{
		DBG_PRINT(("open serial failed"));
		return FAILURE;
	}
	
	return SUCCESS;
}

//发票读入
UINT8 CUniversialSerialCommunicate::fpdr(){
	DBG_PRINT(("----------发票读入----------"));
	FPDR_Request request;
	UINT32 offset=0;
	memset(&request, 0x00, sizeof(FPDR_Request));

	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData, NSRSBH_LEN);
	offset += NSRSBH_LEN;
	request.jzlx = m_serialProtocol->m_revCmd->revData[offset];
	request.jzlx -= 0x30;
	offset++;
	memcpy(request.bspbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	memcpy(request.bspkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+offset, FPLXDM_S_LEN);
	offset += FPLXDM_S_LEN;
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+offset, JQBH_LEN);

	DBG_PRINT(("nsrsbh = %s", (INT8 *)(request.nsrsbh)));
	DBG_PRINT(("jzlx = %u", (INT8 *)(request.jzlx)));
	DBG_PRINT(("bspbh = %s", (INT8 *)(request.bspbh)));
	DBG_PRINT(("bspkl = %s", (INT8 *)(request.bspkl)));
	DBG_PRINT(("skpbh = %s", (INT8 *)(request.skpbh)));
	DBG_PRINT(("skpkl = %s", (INT8 *)(request.skpkl)));
	DBG_PRINT(("fplxdm = %s", (INT8 *)(request.fplxdm)));
	DBG_PRINT(("jqbh = %s", (INT8 *)(request.jqbh)));

	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_bspbh = (INT8 *)(request.bspbh);
	g_YwXmlArg->m_bspkl = (INT8 *)(request.bspkl);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);

	ret = invFunc.InvReadIn(*g_YwXmlArg, request.jzlx, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}

//分机退回
UINT8 CUniversialSerialCommunicate::fjth(){
	DBG_PRINT(("----------分机退回----------"));
	FJTH_Request request;
	UINT32 offset=0;
	memset(&request, 0x00, sizeof(FJTH_Request));

	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData, NSRSBH_LEN);
	offset += NSRSBH_LEN;
	request.jzlx = m_serialProtocol->m_revCmd->revData[offset];
	request.jzlx -= 0x30;
	offset++;
	memcpy(request.bspbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	memcpy(request.bspkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+offset, FPLXDM_S_LEN);
	offset += FPLXDM_S_LEN;
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+offset, JQBH_LEN);

	DBG_PRINT(("nsrsbh = %s", (INT8 *)request.nsrsbh));
	DBG_PRINT(("jzlx = %u", (INT8 *)request.jzlx));
	DBG_PRINT(("bspbh = %s", (INT8 *)request.bspbh));
	DBG_PRINT(("bspkl = %s", (INT8 *)request.bspkl));
	DBG_PRINT(("skpbh = %s", (INT8 *)request.skpbh));
	DBG_PRINT(("skpkl = %s", (INT8 *)request.skpkl));
	DBG_PRINT(("fplxdm = %s", (INT8 *)request.fplxdm));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));

	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_bspbh = (INT8 *)(request.bspbh);
	g_YwXmlArg->m_bspkl = (INT8 *)(request.bspkl);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);

	ret = invFunc.FJInvReturn(*g_YwXmlArg, request.jzlx, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}

//网络购票
UINT8 CUniversialSerialCommunicate::wlgp(){
	DBG_PRINT(("----------网络购票----------"));
	WLGP_Request request;
	UINT32 offset=0;
	memset(&request, 0x00, sizeof(WLGP_Request));

	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData, NSRSBH_LEN);
	offset += NSRSBH_LEN;
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+offset, FPLXDM_S_LEN);
	offset += FPLXDM_S_LEN;
	memcpy(request.fpdm, m_serialProtocol->m_revCmd->revData+offset, FPDM_LEN);
	offset += FPDM_LEN;
	memcpy(request.fpqshm, m_serialProtocol->m_revCmd->revData+offset, FPHM_LEN);
	offset += FPHM_LEN;
	memcpy(request.fpzzhm, m_serialProtocol->m_revCmd->revData+offset, FPHM_LEN);
	offset += FPHM_LEN;
	memcpy(request.fpzfs, m_serialProtocol->m_revCmd->revData+offset, FPFS_LEN);
	offset += FPFS_LEN;
	memcpy(request.qtxx, m_serialProtocol->m_revCmd->revData+offset, QTXX_LEN);
	offset += QTXX_LEN;
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+offset, JQBH_LEN);
	offset += JQBH_LEN;
	memcpy(request.kpjh, m_serialProtocol->m_revCmd->revData+offset, KPJH_LEN);


	DBG_PRINT(("nsrsbh = %s", (INT8 *)request.nsrsbh));
	DBG_PRINT(("skpbh = %s", (INT8 *)request.skpbh));
	DBG_PRINT(("skpkl = %s", (INT8 *)request.skpkl));
	DBG_PRINT(("fplxdm = %s", (INT8 *)request.fplxdm));
	DBG_PRINT(("fpdm = %s", (INT8 *)request.fpdm));
	DBG_PRINT(("fpqshm = %s", (INT8 *)request.fpqshm));
	DBG_PRINT(("fpzzhm = %s", (INT8 *)request.fpzzhm));
	DBG_PRINT(("fpzfs = %s", (INT8 *)request.fpzfs));
	DBG_PRINT(("qtxx = %s", (INT8 *)request.qtxx));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));
	DBG_PRINT(("kpjh = %s", (INT8 *)request.kpjh));

	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);
	g_YwXmlArg->m_kpjh = (INT8 *)(request.kpjh);
// 	INT8 tmpbuf[32];
// 	memset(tmpbuf, 0, sizeof(tmpbuf));
// 	sprintf(tmpbuf, "%u", g_globalArgLib->m_corpInfo->m_Kpjhm);
// 	g_YwXmlArg->m_kpjh = tmpbuf;

	CDataInvVol invVol;
	invVol.m_fplxdm = (INT8 *)(request.fplxdm);
	invVol.m_code = (INT8 *)(request.fpdm);
	invVol.m_isno = atoi((INT8 *)(request.fpqshm));
	invVol.m_ieno = atoi((INT8 *)(request.fpzzhm));
	invVol.m_fpzfs = atoi((INT8 *)(request.fpzfs));

	ret = invFunc.WLLQFPPro(*g_YwXmlArg, &invVol, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}

//ifname是网卡名，比如eth0,ipaddr是IP地址
int CUniversialSerialCommunicate::ifConfig(const char *ifname,  const char *ipaddr,const char *netmask, const char *gwip, const char *dns)
{
	struct   sockaddr_in   sin;
	struct   ifreq   ifr;
	int   fd;
	char buff[128];

	bzero(&ifr,   sizeof(struct   ifreq));
	if   (ifname   ==   NULL)
		return   (-1);
	if   (ipaddr   ==   NULL)
		return   (-1);
	if(gwip == NULL)
		return(-1);
	fd   =   socket(AF_INET,   SOCK_DGRAM,   0);
	if   (fd   ==   -1)
	{
		perror( "Not   create   network   socket   connection\n ");
		return   (-1);
	}
	strncpy(ifr.ifr_name,   ifname,   IFNAMSIZ);
	ifr.ifr_name[IFNAMSIZ   -   1]   =   0;
	memset(&sin,   0,   sizeof(sin));
	sin.sin_family   =   AF_INET;
	sin.sin_addr.s_addr   =   inet_addr(ipaddr);
	memcpy(&ifr.ifr_addr,   &sin,   sizeof(sin));
	if   (ioctl(fd,   SIOCSIFADDR,   &ifr)   <   0)
	{
		perror( "Not   setup   interface\n ");
		return   (-1);
	}
	///////////////////////////////////////////
	bzero(&ifr,   sizeof(struct   ifreq));
	strncpy(ifr.ifr_name,   ifname,   IFNAMSIZ);
	ifr.ifr_name[IFNAMSIZ   -   1]   =   0;
	memset(&sin,   0,   sizeof(sin));
	sin.sin_family   =   AF_INET;
	sin.sin_addr.s_addr   =   inet_addr(netmask);
	memcpy(&ifr.ifr_addr,   &sin,   sizeof(sin));
	if(ioctl(fd, SIOCSIFNETMASK, &ifr ) < 0)
	{
		perror("net mask ioctl error/n");
		return (-1);
	}
	/////////////////////////////////
	struct rtentry rm;
	bzero(&rm,   sizeof(struct rtentry));
	rm.rt_dst.sa_family = AF_INET;
	rm.rt_gateway.sa_family = AF_INET;
	rm.rt_genmask.sa_family = AF_INET;
	memset(&sin,   0,   sizeof(sin));
	sin.sin_family   =   AF_INET;
	sin.sin_addr.s_addr   =   inet_addr(gwip);
	memcpy(&rm.rt_gateway, &sin,   sizeof(sin));
	rm.rt_dev = (char *)ifname;
	rm.rt_flags = RTF_UP | RTF_GATEWAY ;
	if(ioctl(fd, SIOCADDRT, &rm ) < 0)
	{
		perror("gateway ioctl error/n");
		return (-1);
	}
	/////////////////////////////////
	ifr.ifr_flags   |=   IFF_UP   |   IFF_RUNNING;
	if   (ioctl(fd,   SIOCSIFFLAGS,   &ifr)   <   0)
	{
		perror( "SIOCSIFFLAGS ");
		return   (-1);
	}


	memset(buff, 0x00, sizeof(buff));
	sprintf(buff, "echo \"nameserver %s \" >> /etc/resolv.conf", dns);
	system(buff);

	memset(buff, 0x00, sizeof(buff));
	sprintf(buff, "/etc/init.d/network restart");
//	sprintf(buff, "service network restart");
	system(buff);

	return   (0);
}

int CUniversialSerialCommunicate::setNetWork(unsigned char isdhcp, const char *ipaddr,const char *netmask, const char *gwip, const char *dns)
{
	char buff[128];

	if (1 == isdhcp)
	{
		memset(buff, 0x00, sizeof(buff));
		//sprintf(buff, "dhcpcd");
		sprintf(buff, "/sbin/udhcpc -b");
		system(buff);
	} 
	else
	{
		memset(buff, 0x00, sizeof(buff));
		sprintf(buff, "ifconfig eth0 %s netmask %s", ipaddr, netmask);
		system(buff);
		memset(buff, 0x00, sizeof(buff));
		sprintf(buff, "route add default gw %s", gwip);
		system(buff);
		memset(buff, 0x00, sizeof(buff));
		sprintf(buff, "echo \"nameserver %s \" >> /etc/resolv.conf", dns);
		system(buff);

		//	memset(buff, 0x00, sizeof(buff));
		//	sprintf(buff, "/etc/init.d/network restart");
		//	sprintf(buff, "service network restart");
		//	system(buff);
	}

	return 0;
}

int CUniversialSerialCommunicate::getLocalIP()
{
	struct ifaddrs * ifAddrStruct=NULL;  
	void * tmpAddrPtr=NULL;  

	getifaddrs(&ifAddrStruct);  

	while (ifAddrStruct!=NULL)   
	{  
		if (ifAddrStruct->ifa_addr->sa_family==AF_INET)  
		{   // check it is IP4  
			// is a valid IP4 Address  
			tmpAddrPtr = &((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;  
			char addressBuffer[INET_ADDRSTRLEN];  
			inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);  
			DBG_PRINT(("%s IPV4 Address %s\n", ifAddrStruct->ifa_name, addressBuffer));   
		}  
		else if (ifAddrStruct->ifa_addr->sa_family==AF_INET6)  
		{   // check it is IP6  
			// is a valid IP6 Address  
			tmpAddrPtr=&((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;  
			char addressBuffer[INET6_ADDRSTRLEN];  
			inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);  
			DBG_PRINT(("%s IPV6 Address %s", ifAddrStruct->ifa_name, addressBuffer));   
		}   
		ifAddrStruct = ifAddrStruct->ifa_next;  
	} 

	return 0;
}

int CUniversialSerialCommunicate::if_a_string_is_a_valid_ipv4_address(const char *str)
{
	struct in_addr addr;
	int ret;
	volatile int local_errno;

	errno = 0;
	ret = inet_pton(AF_INET, str, &addr);

	local_errno = errno;
	if (ret > 0){
		DBG_PRINT(("\"%s\" is a valid IPv4 address", str));
	} else if (ret < 0) {
		DBG_PRINT(("EAFNOSUPPORT: %s", strerror(local_errno)));
	} else {
		DBG_PRINT(("\"%s\" is not a valid IPv4 address", str));
	}

	return ret;
}

//证书口令更改
UINT8 CUniversialSerialCommunicate::zsklgg(){
	DBG_PRINT(("----------证书口令更改----------"));
	ZSKLGG_Request request;
	UINT32 offset=0;
	memset(&request, 0x00, sizeof(ZSKLGG_Request));

	memcpy(request.yzskl, m_serialProtocol->m_revCmd->revData, KOULING_LEN);
	offset += KOULING_LEN;
	memcpy(request.xzskl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+offset, JQBH_LEN);

	DBG_PRINT(("yzskl = %s", (INT8 *)request.yzskl));
	DBG_PRINT(("xzskl = %s", (INT8 *)request.xzskl));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));

	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);

	ret = manageFunc.BGZSKLProc(*g_YwXmlArg, (INT8 *)request.yzskl, (INT8 *)request.xzskl, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	g_YwXmlArg->m_zskl = (INT8 *)request.xzskl;
	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}

//发票补录
UINT8 CUniversialSerialCommunicate::fpbl(){
	DBG_PRINT(("----------发票补录----------"));
	FPBL_Request request;
	UINT32 offset=0;
	memset(&request, 0x00, sizeof(FPBL_Request));

	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData, NSRSBH_LEN);
	offset += NSRSBH_LEN;
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	memcpy(request.fplxdm, m_serialProtocol->m_revCmd->revData+offset, FPLXDM_S_LEN);
	offset += FPLXDM_S_LEN;
	memcpy(request.bsqsrq, m_serialProtocol->m_revCmd->revData+offset, DATE_LEN);
	offset += DATE_LEN;
	memcpy(request.bsjzrq, m_serialProtocol->m_revCmd->revData+offset, DATE_LEN);
	offset += DATE_LEN;
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+offset, JQBH_LEN);


	DBG_PRINT(("nsrsbh = %s", (INT8 *)request.nsrsbh));
	DBG_PRINT(("skpbh = %s", (INT8 *)request.skpbh));
	DBG_PRINT(("skpkl = %s", (INT8 *)request.skpkl));
	DBG_PRINT(("fplxdm = %s", (INT8 *)request.fplxdm));
	DBG_PRINT(("fpdm = %s", (INT8 *)request.bsqsrq));
	DBG_PRINT(("fpqshm = %s", (INT8 *)request.bsjzrq));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));

	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_fplxdm = (INT8 *)(request.fplxdm);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);
	
	UINT32 bsqsrq = (UINT32)atoi((const char*)request.bsqsrq);
	UINT32 bszzrq = (UINT32)atoi((const char*)request.bsjzrq);
	DBG_PRINT(("bsqsrq = %u", bsqsrq));
	DBG_PRINT(("bszzrq = %u", bszzrq));
	ret = saleFunc.FpblProStart(*g_YwXmlArg, bsqsrq, bszzrq, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}

//获取离线相关数据
UINT8 CUniversialSerialCommunicate::hqlxsj(){
	DBG_PRINT(("----------获取离线相关数据----------"));
	HQLXSJ_Request request;
	UINT32 offset=0;
	memset(&request, 0x00, sizeof(HQLXSJ_Request));

	UINT32 wscfpzs=0;
	string wscfpsj="";
	INT64  wscfpljje=0;

	ret = manageFunc.GetOffLineInvInfo(wscfpzs, wscfpsj, wscfpljje, strErr);
	if (SUCCESS != ret)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	INT8 tempbuf[ZDYXX_LEN+1];
	//未上传的发票张数
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", wscfpzs);
	DBG_PRINT(("wscfpzs = %s", tempbuf));
	m_serialProtocol->FillParament(tempbuf, WSCFPZS_LEN);
	//未上传发票时间
	DBG_PRINT(("wscfpsj = %s", wscfpsj.c_str()));
	m_serialProtocol->FillParament(wscfpsj, SZSJ_LEN);
	//未上传发票累计金额
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%.2f", (double)(wscfpljje/100.0));
	DBG_PRINT(("wscfpljje = %s", tempbuf));
	m_serialProtocol->FillParament(tempbuf, JE_LEN);

	//上传张数
	memset(tempbuf, 0x00, sizeof(tempbuf));
	m_serialProtocol->FillParament(tempbuf, SCZS_LEN);
	
	//上传时间间隔（分钟）
	memset(tempbuf, 0x00, sizeof(tempbuf));
	m_serialProtocol->FillParament(tempbuf, SCSJJG_LEN);
	
	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}

void CUniversialSerialCommunicate::FilterSpace(string &str)
{
/*	INT8 tmpBuf[512];
	int nCount = 0;
	int nLen = str.length();
	
	memset(tmpBuf, 0, sizeof(tmpBuf));
	sprintf(tmpBuf, "%s", str.c_str());
	
	for(int i=nLen-1; i>=0; i--)
	{
		if(tmpBuf[i] == ' ')
		{
			nCount++;
			continue;
		}
		break;
	}
	if(nCount >= nLen)
	{
		str = "";
		return;
	}
	
	if(nCount > 0)
		str.erase(nLen-nCount, nCount);
	
	nCount = 0;
	for(int i=0; i<nLen; i++)
	{
		if(tmpBuf[i] == ' ')
		{
			nCount++;
			continue;
		}
		break;
	}
	if(nCount > 0)
		str.erase(0, nCount);
*/	

	str.erase(str.find_last_not_of(" ") + 1);
	str.erase(0, str.find_first_not_of(" "));

	return;
}

//转换器清库函数
UINT8 CUniversialSerialCommunicate::zhqqk(){
	DBG_PRINT(("----------转换器清库----------"));

	CClearDepotFunc clearfunc;
	UINT8 ret = clearfunc.ClearDepot(strErr);
	if(ret != SUCCESS)
	{
		m_serialProtocol->Rsp_ERR(strErr);
	}

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}

//获取上传出错发票信息
UINT8 CUniversialSerialCommunicate::getErrUpInv()
{
	DBG_PRINT(("----------获取上传出错发票信息----------"));
	CONNECTTEST_Request request;
	UINT32 offset=0;
	memset(&request, 0x00, sizeof(FPBL_Request));
	
	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData, NSRSBH_LEN);
	offset += NSRSBH_LEN;
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+offset, JQBH_LEN);
	offset += JQBH_LEN;	
	
	DBG_PRINT(("nsrsbh = %s", (INT8 *)request.nsrsbh));
	DBG_PRINT(("skpbh = %s", (INT8 *)request.skpbh));
	DBG_PRINT(("skpkl = %s", (INT8 *)request.skpkl));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));
	
	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);

	CDataInvServ dataInvServ[MAX_ERR_INV_COUNT];
	UINT32 nCount = 0;
	if(saleFunc.GetErrUpInvInfo(*g_YwXmlArg, dataInvServ, nCount, strErr) != SUCCESS)
	{
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	if(nCount <= 0)
	{
		strErr = "无上传错误发票信息;";
		m_serialProtocol->Rsp_ERR(strErr);
		return FAILURE;
	}

	INT8 tempbuf[128];
	memset(tempbuf, 0x00, sizeof(tempbuf));
	sprintf(tempbuf, "%u", nCount);
	m_serialProtocol->FillParament(tempbuf, WSCFPZS_LEN);
	for(int i=0; i<nCount; i++)
	{
		m_serialProtocol->FillParament(dataInvServ[i].m_fpdm, FPDM_LEN);

		memset(tempbuf, 0x00, sizeof(tempbuf));
		sprintf(tempbuf, "%08u", dataInvServ[i].m_fphm);
		m_serialProtocol->FillParament(tempbuf, FPHM_LEN);

		m_serialProtocol->FillParament(dataInvServ[i].m_errMsg, CWMS_LEN);
	}

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}


//安全通道连接测试
UINT8 CUniversialSerialCommunicate::sslConnectTest()
{
	DBG_PRINT(("----------安全通道连接测试----------"));
	CONNECTTEST_Request request;
	UINT32 offset=0;
	memset(&request, 0x00, sizeof(FPBL_Request));
	
	memcpy(request.nsrsbh, m_serialProtocol->m_revCmd->revData, NSRSBH_LEN);
	offset += NSRSBH_LEN;
	memcpy(request.skpbh, m_serialProtocol->m_revCmd->revData+offset, SBBH_LEN);
	offset += SBBH_LEN;
	memcpy(request.skpkl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	memcpy(request.jqbh, m_serialProtocol->m_revCmd->revData+offset, JQBH_LEN);
	offset += JQBH_LEN;
	memcpy(request.zskl, m_serialProtocol->m_revCmd->revData+offset, KOULING_LEN);
	offset += KOULING_LEN;
	
	
	DBG_PRINT(("nsrsbh = %s", (INT8 *)request.nsrsbh));
	DBG_PRINT(("skpbh = %s", (INT8 *)request.skpbh));
	DBG_PRINT(("skpkl = %s", (INT8 *)request.skpkl));
	DBG_PRINT(("jqbh = %s", (INT8 *)request.jqbh));
	DBG_PRINT(("zskl = %s", (INT8 *)request.zskl));
	
	g_YwXmlArg->m_nsrsbh = (INT8 *)(request.nsrsbh);
	g_YwXmlArg->m_sksbbh = (INT8 *)(request.skpbh);
	g_YwXmlArg->m_sksbkl = (INT8 *)(request.skpkl);
	g_YwXmlArg->m_jqbh = (INT8 *)(request.jqbh);
	g_YwXmlArg->m_zskl = (INT8 *)(request.zskl);

	ret = manageFunc.SSLConnectTest(*g_YwXmlArg, strErr);
	if (SUCCESS != ret)
	{
		INT8 errbuf[64];
		memset(errbuf, 0, sizeof(errbuf));
		sprintf(errbuf, "%d", ret);
		m_serialProtocol->Rsp_ERR(errbuf);
		return FAILURE;
	}

	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}

#ifndef WIN32
void * PthreadInvUpLoad(void *arg)
{
	CSaleBusinessFunc saleFunc;
	CYWXML_GY ywXml_Gy;
	INT32 ret = SUCCESS;
	string strErr;
	UINT32 nTime = 10000;

	while(1)
	{
		if( (g_globalArgLib->m_pthreadFlag == 1) )
		{
			ywXml_Gy.m_nsrsbh = g_globalArgLib->m_pthreadNsrsbh;
			ywXml_Gy.m_sksbbh = g_globalArgLib->m_pthreadSksbbh;
			ywXml_Gy.m_sksbkl = g_globalArgLib->m_pthreadSksbkl;
			ywXml_Gy.m_fplxdm = g_globalArgLib->m_pthreadFplxdm;
			ywXml_Gy.m_jqbh = g_globalArgLib->m_pthreadJqbh;
			ywXml_Gy.m_kpjh = g_globalArgLib->m_pthreadKpjh;
			ywXml_Gy.m_zskl = g_globalArgLib->m_strZskl;

			ret = saleFunc.InvoiceUpload(ywXml_Gy, strErr);
			if (SUCCESS != ret)
			{
				DBG_PRINT(("strErr = %s", strErr.c_str()));
				g_globalArgLib->m_pthreadFlag = 0;
				g_globalArgLib->m_pthreadErr = strErr;
				CommonSleep(3*nTime);
			}
		}
		else
		{
			CommonSleep(3*nTime);
		}
	}
}

#endif

//应用升级
UINT8 CUniversialSerialCommunicate::programUpdate(){
	DBG_PRINT(("----------应用升级----------"));

	DBG_PRINT(("----------挂载----------"));
// 	if (system(MOUNT_CMD) != 0)
// 	{
// 		DBG_PRINT(("----------挂载错误----------"));
// 		m_serialProtocol->Rsp_ERR("没有找到U盘!\n");
// 		return FAILURE;
// 	}
	INT8 tmpBuf[128];
	memset(tmpBuf, 0, sizeof(tmpBuf));
	UINT8 ret = UsbDiskMount(tmpBuf);
	if (SUCCESS != ret)
	{
		DBG_PRINT(("----------挂载错误----------"));
		m_serialProtocol->Rsp_ERR("没有找到U盘!\n");
		UsbDiskUnMount();
		return FAILURE;
	}

	DBG_PRINT(("----------拷贝----------"));
	if (system(CPAWE_CMD) != 0)
	{
		DBG_PRINT(("----------拷贝失败----------"));
		m_serialProtocol->Rsp_ERR("文件复制失败!\n");
		return FAILURE;
	}

	if (system(CPSQL_CMD) != 0)
	{
		DBG_PRINT(("----------拷贝失败----------"));
		m_serialProtocol->Rsp_ERR("脚本复制失败!\n");
		return FAILURE;
	}
	
	DBG_PRINT(("----------删除并更名----------"));
	system(RMAWE_CMD);
	system(MVAWE_CMD);
	//system(UMOUNT_CMD);
	UsbDiskUnMount();

	DBG_PRINT(("----------升级成功!重启----------"));
	m_serialProtocol->FillParament("升级成功!重启！\n", strlen("升级成功!重启！\n"));
	m_serialProtocol->Rsp_OK();
	system(REBOOT_CMD);
	return SUCCESS;
}


//系统自检
UINT8 CUniversialSerialCommunicate::sysTest(){
	DBG_PRINT(("----------系统自检----------"));

	DBG_PRINT(("----------网络测试----------"));
	if(netTest() != 0)
	{
		DBG_PRINT(("网络测试失败!"));
		m_serialProtocol->FillParament("网络测试失败!", strlen("网络测试失败!"));
	}
	else
	{
		DBG_PRINT(("网络测试成功!"));
		m_serialProtocol->FillParament("网络测试成功!", strlen("网络测试成功!"));
	}

	DBG_PRINT(("----------串口测试----------"));
	if(uartTest() != 0)
	{
		DBG_PRINT(("串口测试失败!"));
		//m_serialProtocol->Rsp_ERR("串口测试失败!");
		m_serialProtocol->FillParament("串口测试失败!", strlen("串口测试失败!"));
	}
	else
	{
		DBG_PRINT(("串口测试成功!"));
		m_serialProtocol->FillParament("串口测试成功!", strlen("串口测试成功!"));

		//m_serialProtocol->Rsp_OK();
	}


	DBG_PRINT(("----------金税盘测试----------"));
	if(udiskTest() != 0)
	{
		DBG_PRINT(("金税盘测试失败!"));
		//m_serialProtocol->Rsp_ERR("JSP Test Failed");
		m_serialProtocol->FillParament("金税盘测试失败!", strlen("金税盘测试失败!"));
	}
	else
	{
		DBG_PRINT(("金税盘测试成功!"));
		m_serialProtocol->FillParament("金税盘测试成功!", strlen("金税盘测试成功!"));
		m_serialProtocol->Rsp_OK();
	}
	m_serialProtocol->Rsp_OK();
	return SUCCESS;
}

//烧写MAC
UINT8 CUniversialSerialCommunicate::writeMAC(){
	DBG_PRINT(("----------烧写MAC----------"));
	return SUCCESS;
}

//烧写机器编号
UINT8 CUniversialSerialCommunicate::writeMachineNo(){
	DBG_PRINT(("----------烧写机器编号----------"));
	return SUCCESS;
}


