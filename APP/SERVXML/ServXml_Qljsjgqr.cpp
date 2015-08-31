/*! \file    ServXml_Qljsjgqr.cpp
   \brief    款机调用的中间件接口 (网络接口)业务七: 清零解锁结果确认接口(0014专普票)
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "ServXml_Qljsjgqr.h"
#include "GlobalNetArg.h"
#if SSL_USE_TYPE == 1
#include "uniAcceptFrameworkApi.h"
#endif


#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CServQljsjgqr::CServQljsjgqr(ProtocolOrganize *p):ProtocolXML(p)
{
	setXmlSaveFile(XML_DEF_BUSSINESS_REQFILE, XML_DEF_BUSSINESS_RSPFILE); 
	setUpdateFile(XML_RESPONSE_FILE,  GBK_CHAR_TYPE);
}

CServQljsjgqr::~CServQljsjgqr()
{
	DBG_PRINT(("in ~CServQljsjgqr()"))
}

INT32 CServQljsjgqr::XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("IN CServQljsjgqr::XmlBusinessBuild"));

	return SUCCESS;
}

INT32 CServQljsjgqr::XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("CServQljsjgqr::XmlBusinessParse Begin"));

	memset(g_Xml_ExchangeBuf, 0, PROTOCOL_OUT_BUFF_LEN);
	memcpy(g_Xml_ExchangeBuf, pData->pBuff, pData->outLen);
	pData->fill(g_Xml_ExchangeBuf, pData->outLen);
	memset(g_Xml_ExchangeBuf, 0, PROTOCOL_OUT_BUFF_LEN);

	return SUCCESS;
}

INT32 CServQljsjgqr::CommunicationProc(void* pDataIn, void* pDataOut, string &strErr)
{
	INT32 res = 0;

	NoteData_Para noteData;
	noteData.m_appType = NET_QKXXXZ;	//此处设置业务类型
	DataOutType dataOut(g_Xml_OutBuf, PROTOCOL_OUT_BUFF_LEN);
	res = BuildXml(pDataIn, &dataOut, &noteData, strErr);
	if (res != SUCCESS)
	{
		return res;
	}
	
	DBG_PRINT(("res = %u", res));
	DBG_PRINT(("outLen = %u", dataOut.outLen));

	//////////////////////////////////////////////////////////////////////////
	//此处为处理流程，将上面组织的数据发送给库SSL接口，接收到的数据放入g_Xml_OutBuf中。
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
	
#if NET_LOCK_FLAG == 1
	CJSKInfoFunc::MutexLock();
#endif
	int retval=aisino_ssl_transfer_call(SSL_AUTH_CODE,(char*)strTechMsg.c_str(),strTechMsg.size(),
		(unsigned char*)g_Xml_OutBuf,dataOut.outLen,(unsigned char*)g_Xml_ExchangeBuf,&rec_len,errBuf);
#if NET_LOCK_FLAG == 1
	CJSKInfoFunc::MutexUnlock();
#endif
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
	printf("--------------------------CServQljsjgqr rec begin-----------------------------------\n");
	DBG_PRINT(("rec_len = %d", rec_len));
	printf("%s\n", g_Xml_OutBuf);
	printf("\n------------------------CServQljsjgqr rec end-------------------------------------\n");
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



























