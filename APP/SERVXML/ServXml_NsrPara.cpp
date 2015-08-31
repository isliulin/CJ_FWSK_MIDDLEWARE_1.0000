/*! \file    ServXml_NsrPara.cpp
   \brief    款机调用的中间件接口 (网络接口)业务二: 企业参数下载
   \author   zfj & myf & lzh
   \version  1.0
   \date     2015
 */


#include "ServXml_NsrPara.h"
#if SSL_USE_TYPE == 1
#include "uniAcceptFrameworkApi.h"
#endif

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CNsrPara::CNsrPara(ProtocolOrganize *p):ProtocolXML(p)
{
	setDeclaration(XML_DEF_VERSION, XML_DEF_ENCODING, GBK_CHAR_TYPE);
	setXmlSaveFile(XML_DEF_BUSSINESS_REQFILE, XML_DEF_BUSSINESS_RSPFILE); 
}

CNsrPara::~CNsrPara()
{
	DBG_PRINT(("in ~CNsrPara()"))
}

INT32 CNsrPara::XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("IN CNsrPara::XmlBusinessBuild"));
	DBG_ASSERT_EXIT((pBusiness != NULL), (" pData == NULL!"));

	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "INPUT");
	pXmlBuild->m_parentElement[1] = pXmlBuild->m_NewElement;
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "NSRSBH");
	pXmlBuild->AddText(g_gNetArg->m_nsrsbh);//纳税人识别号/企业税号
	DBG_PRINT(("NSRSBH : %s", g_gNetArg->m_nsrsbh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "FXSH");
	pXmlBuild->AddText(g_gNetArg->m_fxsh);//发行税号
	DBG_PRINT(("FXSH : %s", g_gNetArg->m_fxsh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "HSSH");
	pXmlBuild->AddText(g_gNetArg->m_hxsh);//哈希税号
	DBG_PRINT(("HSSH : %s", g_gNetArg->m_hxsh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "KPJH");
	pXmlBuild->AddText(g_gNetArg->m_kpjh);//开票机号
	DBG_PRINT(("KPJH : %s", g_gNetArg->m_kpjh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "SBBH");
	pXmlBuild->AddText(g_gNetArg->m_sbbh);//税控设备编号
	DBG_PRINT(("SBBH : %s", g_gNetArg->m_sbbh.c_str()));
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "SQXX");
	pXmlBuild->AddText((const char *)pBusiness);//票种/税率/离线时限/离线金额/离线锁死期等信息（从底层读取后Base64）
	DBG_PRINT(("SQXX : %s", pBusiness));
	
	return SUCCESS;
}

INT32 CNsrPara::XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("CNsrPara::XmlBusinessParse Begin"));

	int res = 0;
	string tmpCode;
	string tmpMess;

	CNsrParaOutInfo *p = (CNsrParaOutInfo *)pBusiness;

	INT32 layer = pXmlParse->m_signNodeLayer;//初始化为0
	
	pXmlParse->LocateNodeByName(pXmlParse->m_signNode, "OUTPUT");
	pXmlParse->m_parentElement[layer+1] = pXmlParse->m_Child;

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+1], "CODE");
	tmpCode = pXmlParse->GetText();
	res = atoi(tmpCode.c_str());
	DBG_PRINT(("CODE = %s", tmpCode.c_str()));

	if(res != 0)
	{
		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+1], "MESS");
		tmpMess = pXmlParse->GetText();
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
	g_gNetArg->m_nsrsbh = pXmlParse->GetText();
	DBG_PRINT(("NSRSBH = %s", g_gNetArg->m_nsrsbh.c_str()));

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "KPJH");
	g_gNetArg->m_kpjh = pXmlParse->GetText();
	DBG_PRINT(("KPJH = %s", g_gNetArg->m_kpjh.c_str()));
	
	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "SBBH");
	g_gNetArg->m_sbbh = pXmlParse->GetText();
	DBG_PRINT(("SBBH = %s", g_gNetArg->m_sbbh.c_str()));
	
	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "SQXX");
	p->m_sqxx = pXmlParse->GetText();
	DBG_PRINT(("SQXX = %s", p->m_sqxx.c_str()));
	
	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "SCCS");
	p->m_sccs = pXmlParse->GetText();
	DBG_PRINT(("SCCS = %s", p->m_sccs.c_str()));
	
	return SUCCESS;
}

INT32 CNsrPara::CommunicationProc(void* pDataIn, void* pDataOut, string &strErr)
{
	INT32 res = 0;

	NoteData_Para noteData;
	noteData.m_appType = NET_QYCSXZ;	//此处设置业务类型
	DataOutType dataOut(g_Xml_OutBuf, PROTOCOL_OUT_BUFF_LEN);
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
	pTechMsg.m_servId = TECH_MSG_SERV_ID_PARA;
	if(g_gNetArg->m_servId != "")
	{
		pTechMsg.m_servId = g_gNetArg->m_servId;
	}
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
	printf("--------------------------CNsrPara rec begin-----------------------------------\n");
	DBG_PRINT(("rec_len = %d", rec_len));
	printf("%s\n", g_Xml_OutBuf);
	printf("\n------------------------CNsrPara rec end-------------------------------------\n");
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

INT32 CNsrPara::SSLConnectTest(string nsrsbh, string strZskl, string &strErr)
{
#if SSL_USE_TYPE == 1
	int rec_len = PROTOCOL_OUT_BUFF_LEN;
	CTechnologyMsg pTechMsg;
	string strTechMsg("");
	
	pTechMsg.m_nsrsbh = nsrsbh;
	pTechMsg.m_servIP = g_gNetArg->m_servIP;
	pTechMsg.m_servPort = g_gNetArg->m_servPort;
	pTechMsg.m_passWord = strZskl;
	pTechMsg.m_certPwd = strZskl;
	GetTechMsgStrTest(&pTechMsg, strTechMsg);
	UINT8 errBuf[1024];
	memset(errBuf, 0, sizeof(errBuf));
	
	string bizMsg="hello,I am here";
	int retval = 0;
#if NET_LOCK_FLAG == 1
	CJSKInfoFunc::MutexLock();
#endif
	retval=aisino_ssl_transfer_call(SSL_AUTH_CODE,(char*)strTechMsg.c_str(),strTechMsg.size(),
		(unsigned char*)bizMsg.c_str(),bizMsg.size(),(unsigned char*)g_Xml_ExchangeBuf,&rec_len,errBuf);
#if NET_LOCK_FLAG == 1
	CJSKInfoFunc::MutexUnlock();
#endif
	DBG_PRINT(("retval = %d", retval));
	if( retval != 0)
	{
		DBG_PRINT(("errBuf = %s", errBuf));
		strErr = (INT8 *)errBuf;
		return retval;
	}
	string strRet = g_Xml_ExchangeBuf;
	if( (rec_len==2) && (strRet=="ok") )
	{
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
	
#endif
}
