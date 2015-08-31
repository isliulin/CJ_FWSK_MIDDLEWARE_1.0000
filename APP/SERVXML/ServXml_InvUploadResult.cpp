/*! \file   ServXml_InvUploadResult.cpp
   \brief    网络接口 业务: 发票上传结果下载接口
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "ServXml_InvUploadResult.h"
#if SSL_USE_TYPE == 1
#include "uniAcceptFrameworkApi.h"
#endif

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "GlobalNetArg.h"

CInvUpResultOutinfo::CInvUpResultOutinfo()
{
	m_IfSuccFlag = 0;
}

CInvUpResultOutinfo::~CInvUpResultOutinfo()
{

}

CInvUpResult::CInvUpResult(ProtocolOrganize *p):ProtocolXML(p)
{
	setXmlSaveFile(XML_DEF_BUSSINESS_REQFILE, XML_DEF_BUSSINESS_RSPFILE); 
	setUpdateFile(XML_RESPONSE_FILE,  GBK_CHAR_TYPE);
}

CInvUpResult::~CInvUpResult()
{
	DBG_PRINT(("in ~CNsrPara()"))
}

INT32 CInvUpResult::XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr)
{
// 	DBG_PRINT(("IN CInvUpResult::XmlBusinessBuild"));
// 	DBG_ASSERT_EXIT((pBusiness != NULL), (" pData == NULL!"));

	UINT8 i = 0;

	pXmlBuild->LocateNodeByName(pXmlBuild->m_RootElement, "body");
	pXmlBuild->m_parentElement[1] = pXmlBuild->m_Child;
	UINT32 FpmxCount = (UINT8)atoi(pXmlBuild->GetAttr("count").c_str());	//解析XML后得到明细个数
	DBG_PRINT(("FpmxCount == %u", FpmxCount));

	pXmlBuild->LocateNodeByName(pXmlBuild->m_parentElement[1], "input");
	pXmlBuild->m_parentElement[2] = pXmlBuild->m_Child;

	for (i=0; i<FpmxCount; i++)
	{
		//得到group节点
		pXmlBuild->LocateNodeByName(pXmlBuild->m_parentElement[2], "group", i);
		pXmlBuild->m_parentElement[3] = pXmlBuild->m_Child;

		DBG_PRINT(("g_gNetArg->m_slxlh = %s", g_gNetArg->m_slxlh.c_str()));
		pXmlBuild->LocateNodeByName(pXmlBuild->m_parentElement[3], "slxlh");
		pXmlBuild->UpdateText(g_gNetArg->m_slxlh);
	}

	DBG_PRINT(("g_gNetArg->m_fxsh = %s", g_gNetArg->m_fxsh.c_str()));
	pXmlBuild->LocateNodeByName(pXmlBuild->m_parentElement[2], "qtxx");
	pXmlBuild->UpdateText(g_gNetArg->m_fxsh);

	return SUCCESS;
}

INT32 CInvUpResult::XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("CInvUpResult::XmlBusinessParse Begin"));
/*	UINT8 res = 0;
	string tmpCode;
	string tmpMess;

	CInvUpResultOutinfo *p = (CInvUpResultOutinfo *)pBusiness;
	INT32 layer = pXmlParse->m_signNodeLayer;
	
	pXmlParse->LocateNodeByName(pXmlParse->m_signNode, "OUTPUT");
	pXmlParse->m_parentElement[layer+1] = pXmlParse->m_Child;

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+1], "CODE");
	tmpCode = pXmlParse->GetText();

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+1], "MESS");
	tmpMess = pXmlParse->GetText();
	SetServRetInfo(tmpCode, tmpMess);

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+1], "DATA");
	pXmlParse->m_parentElement[layer+2] = pXmlParse->m_Child;

// 	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "NSRSBH");
// 	tmpStr = pXmlParse->GetText();
// 
// 	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "KPJH");
// 	tmpStr = pXmlParse->GetText();
// 	
// 	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "SBBH");
// 	tmpStr = pXmlParse->GetText();
	

	res = pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "FP_SUCC");
	if (SUCCESS == res)
	{
		pXmlParse->m_parentElement[layer+3] = pXmlParse->m_Child;
		
		string tempStr;
		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+3], "FPXX");
		tempStr = pXmlParse->GetText();
		p->m_FpSucc.m_fpdm = tempStr.substr(0, 12);
		p->m_FpSucc.m_fphm = tempStr.substr(13, 8);
		
		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+3], "FLAG");
		p->m_FpSucc.m_scbzFlag = pXmlParse->GetText();

	}
	else//发票上传结果下载失败
	{
		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "FP_ERR");
		
		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+3], "FP");
		pXmlParse->m_parentElement[layer+4] = pXmlParse->m_Child;
		
		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+4], "FPDM");
		p->m_FpErr.m_fpdm = pXmlParse->GetText();
		
		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+4], "FPHM");
		p->m_FpErr.m_fphm = pXmlParse->GetText();
		
		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+4], "CODE");
		p->m_FpErr.m_errCode = pXmlParse->GetText();
		
		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+4], "MESS");
		p->m_FpErr.m_errInfo = pXmlParse->GetText();
	}
*/

	memset(g_Xml_ExchangeBuf_Inv, 0, PROTOCOL_OUT_BUFF_LEN);
	memcpy(g_Xml_ExchangeBuf_Inv, pData->pBuff, pData->outLen);
	pData->fill(g_Xml_ExchangeBuf_Inv, pData->outLen);
	memset(g_Xml_ExchangeBuf_Inv, 0, PROTOCOL_OUT_BUFF_LEN);

	return SUCCESS;
}

INT32 CInvUpResult::CommunicationProc(void* pDataIn, void* pDataOut, string &strErr)
{
	INT32 res = 0;

	NoteData_Para noteData;
	noteData.m_appType = NET_FPSCJGXZ;	//此处设置业务类型
	DataOutType dataOut(g_Xml_OutBuf_Inv, PROTOCOL_OUT_BUFF_LEN);
	res = BuildXml(pDataIn, &dataOut, &noteData, strErr);
	DBG_PRINT(("res = %d", res));
	if (res != SUCCESS)
	{
		return res;
	}
	
	DBG_PRINT(("outLen = %d", dataOut.outLen));

	//////////////////////////////////////////////////////////////////////////
	//此处为处理流程，将上面组织的数据发送给库SSL接口，接收到的数据放入g_Xml_OutBuf_Inv中。
	//////////////////////////////////////////////////////////////////////////
#if SSL_USE_TYPE == 1
	int rec_len = PROTOCOL_OUT_BUFF_LEN;
	CTechnologyMsg pTechMsg;
	string strTechMsg("");
	
	pTechMsg.m_nsrsbh = g_gNetArg->m_nsrsbh;
	pTechMsg.m_servIP = g_gNetArg->m_servIP;
	pTechMsg.m_servPort = g_gNetArg->m_servPort;
	pTechMsg.m_passWord = g_gNetArg->m_strzskl;
	pTechMsg.m_certPwd = g_gNetArg->m_strzskl;
	pTechMsg.m_servId = TECH_MSG_SERV_ID_INV;
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
		(unsigned char*)g_Xml_OutBuf_Inv,dataOut.outLen,(unsigned char*)g_Xml_ExchangeBuf_Inv,&rec_len,errBuf);
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
	dataOut.fill(g_Xml_ExchangeBuf_Inv, rec_len);
	memset(g_Xml_ExchangeBuf_Inv, 0, PROTOCOL_OUT_BUFF_LEN);

#ifdef XML_DEBUG_OUT
	printf("--------------------------CInvUpResultOutinfo rec begin-----------------------------------\n");
	DBG_PRINT(("rec_len = %d", rec_len));
	printf("%s\n", g_Xml_OutBuf_Inv);
	printf("\n------------------------CInvUpResultOutinfo rec end-------------------------------------\n");
#endif
#endif

	DBG_PRINT(("7 开始解析从SSL返回的XML文件"));
	res = ParseXml(pDataOut, &dataOut, &noteData, strErr);
	DBG_PRINT(("res = %d", res));
	if (res != SUCCESS)
	{
		return res;
	}


	
	return SUCCESS;
}

