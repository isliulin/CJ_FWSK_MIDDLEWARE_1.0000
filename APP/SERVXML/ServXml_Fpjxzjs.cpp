/*! \file    ServXml_Fpjxzjs.cpp
   \brief    款机调用的中间件接口 (网络接口)业务九: 发票卷下载/解锁接口(0013专普票)
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "ServXml_Fpjxzjs.h"
#if SSL_USE_TYPE == 1
#include "uniAcceptFrameworkApi.h"
#endif

#include "JSKInvManageProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "GlobalNetArg.h"
#include "DataClassDesign.h"

CServFpjxzjs::CServFpjxzjs(ProtocolOrganize *p):ProtocolXML(p)
{
	setDeclaration(XML_DEF_VERSION, XML_DEF_ENCODING, GBK_CHAR_TYPE);
	setXmlSaveFile(XML_DEF_BUSSINESS_REQFILE, XML_DEF_BUSSINESS_RSPFILE); 
}

CServFpjxzjs::~CServFpjxzjs()
{
	DBG_PRINT(("in ~CServFpjxzjs()"))
}

INT32 CServFpjxzjs::XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("IN CServFpjxzjs::XmlBusinessBuild"));
	DBG_ASSERT_EXIT((pBusiness != NULL), (" pBusiness == NULL!"));
	
	char tmpBuf[256];
	CDataInvVol *p = (CDataInvVol *)pBusiness;

	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "INPUT");
	pXmlBuild->m_parentElement[1] = pXmlBuild->m_NewElement;
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "NSRSBH");
	pXmlBuild->AddText(g_gNetArg->m_nsrsbh);//纳税人识别号/企业税号
	DBG_PRINT(("NSRSBH : %s", g_gNetArg->m_nsrsbh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "HASH");
	pXmlBuild->AddText(g_gNetArg->m_hxsh);//哈希税号
	DBG_PRINT(("HASH : %s", g_gNetArg->m_hxsh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "YSSH");
	pXmlBuild->AddText(g_gNetArg->m_fxsh);//压缩税号,待赋值
	DBG_PRINT(("YSSH : %s", g_gNetArg->m_fxsh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "DQBH");
	pXmlBuild->AddText(g_gNetArg->m_addrno);//地区编号,待赋值
	DBG_PRINT(("DQBH : %s", g_gNetArg->m_addrno.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "KPJH");
	pXmlBuild->AddText(g_gNetArg->m_kpjh);//开票机号
	DBG_PRINT(("KPJH : %s", g_gNetArg->m_kpjh.c_str()));
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "SBBH");
	pXmlBuild->AddText(g_gNetArg->m_sbbh);//税控设备编号
	DBG_PRINT(("SBBH : %s", g_gNetArg->m_sbbh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "DCBB");
	pXmlBuild->AddText(g_gNetArg->m_dcbb);//底层版本,待赋值
	DBG_PRINT(("DCBB : %s", g_gNetArg->m_dcbb.c_str()));

	CJSKInvManageProc::fplxdm2fplx(p->m_fplxdm, p->m_invtype);
	if (1 == p->m_FlagJSorXZ)//发票卷解锁标识
	{
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "FPJS");//发票卷解锁，可能不存在，局端优先处理解锁发票卷
		pXmlBuild->m_parentElement[2] = pXmlBuild->m_NewElement;

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "FPZL");
		memset(tmpBuf, 0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%u", p->m_invtype);
		pXmlBuild->AddText(tmpBuf);//发票种类0（增专）、 2（增普）、 11（货运）、 12（机动车）
		DBG_PRINT(("FPZL : %s", tmpBuf));

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "LBDM");
		pXmlBuild->AddText(p->m_code);//类别代码
		DBG_PRINT(("LBDM : %s", p->m_code.c_str()));

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "QSHM");
		memset(tmpBuf, 0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%08u", p->m_isno);
		pXmlBuild->AddText(tmpBuf);//起始号码
		DBG_PRINT(("QSHM : %s", tmpBuf));

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "FPFS");
		memset(tmpBuf, 0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%u", p->m_fpzfs);
		pXmlBuild->AddText(tmpBuf);//发票份数
		DBG_PRINT(("FPFS : %s", tmpBuf));

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "FLAG");
		pXmlBuild->AddText(p->m_flag);//写盘锁死发票卷密文信息 40字节，要做base64
		DBG_PRINT(("FLAG : %s", p->m_flag.c_str()));
	}
	
	else if (0 == p->m_FlagJSorXZ)//发票卷下载标识
	{
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "FPXZ");//发票卷下载，可能不存在
		pXmlBuild->m_parentElement[2] = pXmlBuild->m_NewElement;

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "FPZL");
		memset(tmpBuf, 0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%u", p->m_invtype);
		pXmlBuild->AddText(tmpBuf);//发票种类0（增专）、 2（增普）、 11（货运）、 12（机动车）,待赋值
		DBG_PRINT(("FPZL : %s", tmpBuf));

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "LBDM");
		pXmlBuild->AddText(p->m_code);//类别代码,待赋值
		DBG_PRINT(("LBDM : %s", p->m_code.c_str()));

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "QSHM");
		memset(tmpBuf, 0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%08u", p->m_isno);
		pXmlBuild->AddText(tmpBuf);//起始号码
		DBG_PRINT(("QSHM : %s", tmpBuf));

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "FPFS");
		memset(tmpBuf, 0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%u", p->m_fpzfs);
		pXmlBuild->AddText(tmpBuf);//发票份数
		DBG_PRINT(("FPFS : %s", tmpBuf));

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "GPSQ");
		pXmlBuild->AddText(p->m_gpsq);//购票授权 16字节，要做base64
		DBG_PRINT(("GPSQ : %s", p->m_gpsq.c_str()));
	}
	else
	{
		DBG_PRINT(("FlagJSorXZ Error : %d", p->m_FlagJSorXZ));
	}
	return SUCCESS;
}

INT32 CServFpjxzjs::XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("CServFpjxzjs::XmlBusinessParse Begin"));
	int res = 0;
	int tempret;//20150501添加,linzihao
	string tmpCode="";
	string tmpMess="";

	CDataInvVol *p = (CDataInvVol *)pBusiness;
	INT32 layer = pXmlParse->m_signNodeLayer;
	
	pXmlParse->LocateNodeByName(pXmlParse->m_signNode, "OUTPUT");
	pXmlParse->m_parentElement[layer+1] = pXmlParse->m_Child;

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+1], "CODE");
	tmpCode= pXmlParse->GetText();//操作结果：0000成功；其它失败
	res = atoi(tmpCode.c_str());
	DBG_PRINT(("CODE = %s", tmpCode.c_str()));
	
	if(res != 0)
	{
		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+1], "MESS");
		tmpMess = pXmlParse->GetText();//描述信息
		DBG_PRINT(("MESS = %s", tmpMess.c_str()));

		INT8 tmpBuf[512];
		memset(tmpBuf, 0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%s:%s", tmpCode.c_str(), tmpMess.c_str());
		strErr = tmpBuf;
		//SetServRetInfo(tmpCode, tmpMess);
		return FAILURE;
	}
	
	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+1], "DATA");
	pXmlParse->m_parentElement[layer+2] = pXmlParse->m_Child;

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "NSRSBH");
	g_gNetArg->m_nsrsbh = pXmlParse->GetText();//纳税人识别号/企业税号
	DBG_PRINT(("NSRSBH = %s", g_gNetArg->m_nsrsbh.c_str()));

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "KPJH");
	g_gNetArg->m_kpjh = pXmlParse->GetText();//开票机号
	DBG_PRINT(("KPJH = %s", g_gNetArg->m_kpjh.c_str()));
	
	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "SBBH");
	g_gNetArg->m_sbbh= pXmlParse->GetText();//设备编号
	DBG_PRINT(("SBBH = %s", g_gNetArg->m_sbbh.c_str()));

	tempret = pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "FPJS");//发票卷解锁，可能不存在，开票软件优先处理，将解锁包传给底层
	if (tempret == SUCCESS)
	{
		pXmlParse->m_parentElement[layer+3] = pXmlParse->m_Child;

		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+3], "FPJJSMW");
		p->m_fpjjsmw = pXmlParse->GetText();//发票卷解锁密文，经过Base64
		DBG_PRINT(("FPJJSMW = %s", p->m_fpjjsmw.c_str()));
	}
	else
	{
		DBG_PRINT(("tempret = %d",tempret));
		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "FPXZ");//发票卷下载，可能不存在，开票软件优先处理，将解锁包传给底层
		pXmlParse->m_parentElement[layer+3] = pXmlParse->m_Child;

		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+3], "FPJMW");
		p->m_fpjmw = pXmlParse->GetText();//发票发票密文信息，经过Base64
		DBG_PRINT(("FPJMW = %s", p->m_fpjmw.c_str()));
	}
	
	return SUCCESS;
}

INT32 CServFpjxzjs::CommunicationProc(void* pDataIn, void* pDataOut, string &strErr)
{
	INT32 res = 0;

	NoteData_Para noteData;//这是一个结构体
	noteData.m_appType = NET_FPJXZJS;	//此处设置业务类型
	DataOutType dataOut(g_Xml_OutBuf, PROTOCOL_OUT_BUFF_LEN);//初始化一个DataOutType类对象, extern INT8 g_Xml_OutBuf[];一个全局变量
	res = BuildXml(pDataIn, &dataOut, &noteData, strErr);
	if (res != SUCCESS)
	{
		return res;
	}
	
	DBG_PRINT(("res = %u", res));
	DBG_PRINT(("outLen = %u", dataOut.outLen));

#if SSL_USE_TYPE == 1
	int rec_len = PROTOCOL_OUT_BUFF_LEN;
	CTechnologyMsg pTechMsg;
	string strTechMsg("");
	
	pTechMsg.m_nsrsbh = g_gNetArg->m_nsrsbh;
	pTechMsg.m_servIP = g_gNetArg->m_servIP;
	pTechMsg.m_servPort = g_gNetArg->m_servPort;
	pTechMsg.m_passWord = g_gNetArg->m_strzskl;
	pTechMsg.m_certPwd = g_gNetArg->m_strzskl;
	if(g_gNetArg->m_servId != "")
	{
		pTechMsg.m_servId = g_gNetArg->m_servId;
	}
	pTechMsg.m_servId = TECH_MSG_SERV_ID_GP;
	GetTechMsgStr(&pTechMsg, strTechMsg);
	UINT8 errBuf[1024];
	memset(errBuf, 0, sizeof(errBuf));
	
	int retval = 0;
#if NET_LOCK_FLAG == 1
	CJSKInfoFunc::MutexLock();
#endif
	retval=aisino_ssl_transfer_call(SSL_AUTH_CODE,(char*)strTechMsg.c_str(),strTechMsg.size(),
		(unsigned char*)g_Xml_OutBuf,dataOut.outLen,(unsigned char*)g_Xml_ExchangeBuf,&rec_len,errBuf);
#if NET_LOCK_FLAG == 1
	CJSKInfoFunc::MutexUnlock();
#endif
	DBG_PRINT(("retval = %d", retval));
	if( retval != 0)
	{
		DBG_PRINT(("errBuf = %s", errBuf));
		//strErr = (INT8 *)errBuf;
		strErr = "网络通信错误!";
		return retval;
	}

	DBG_PRINT(("rec_len = %d", rec_len));
	dataOut.fill(g_Xml_ExchangeBuf, rec_len);
	memset(g_Xml_ExchangeBuf, 0, PROTOCOL_OUT_BUFF_LEN);

#ifdef XML_DEBUG_OUT
	printf("--------------------------CServFpjxzjs rec begin-----------------------------------\n");
	DBG_PRINT(("rec_len = %d", rec_len));
	printf("%s\n", g_Xml_OutBuf);
	printf("\n------------------------CServFpjxzjs rec end-------------------------------------\n");
#endif
#endif

	res = ParseXml(pDataOut, &dataOut, &noteData, strErr);
	DBG_PRINT(("res = %u", res));
	if (res != SUCCESS)
	{
		return res;
	}
	return SUCCESS;
}


