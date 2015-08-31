/*! \file    ServXml_Qkxxxz.cpp
   \brief    款机调用的中间件接口 (网络接口)业务七: 清卡信息下载接口(0014专普票)
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "ServXml_Qkxxxz.h"
#include "ServWlcb.h"
#include "GlobalNetArg.h"
#if SSL_USE_TYPE == 1
#include "uniAcceptFrameworkApi.h"
#endif


#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CServQkxxxz::CServQkxxxz(ProtocolOrganize *p):ProtocolXML(p)
{
	setXmlSaveFile(XML_DEF_BUSSINESS_REQFILE, XML_DEF_BUSSINESS_RSPFILE); 
	setUpdateFile(XML_RESPONSE_FILE,  GBK_CHAR_TYPE);
}

CServQkxxxz::~CServQkxxxz()
{
	DBG_PRINT(("in ~CServQkxxxz()"))
}

INT32 CServQkxxxz::XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("IN CServQkxxxz::XmlBusinessBuild"));
//	DBG_ASSERT_EXIT((pBusiness != NULL), (" pBusiness == NULL!"));
/*	
	CServWlcb *p = (CServWlcb *)pBusiness;

	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "INPUT");
	pXmlBuild->m_parentElement[1] = pXmlBuild->m_NewElement;
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "NSRSBH");
	pXmlBuild->AddText(g_gNetArg->m_nsrsbh);//纳税人识别号
	DBG_PRINT(("NSRSBH : %s", g_gNetArg->m_nsrsbh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "KPJH");
	pXmlBuild->AddText(g_gNetArg->m_kpjh);//开机票号
	DBG_PRINT(("KPJH : %s", g_gNetArg->m_kpjh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "SBBH");
	pXmlBuild->AddText(g_gNetArg->m_sbbh);//设备编号
	DBG_PRINT(("SBBH : %s", g_gNetArg->m_sbbh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "HASH");
	pXmlBuild->AddText(g_gNetArg->m_hxsh);//哈希税号
	DBG_PRINT(("HASH : %s", g_gNetArg->m_hxsh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "CSSJ"); 
	pXmlBuild->AddText(p->m_cssj);//抄税时间 待赋值
	DBG_PRINT(("CSSJ : %s", p->m_cssj.c_str()));
*/
	return SUCCESS;
}

INT32 CServQkxxxz::XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("CServQkxxxz::XmlBusinessParse Begin"));
/*	int res = 0;
	string tmpCode="";
	string tmpMess="";

	CServWlcb *p = (CServWlcb *)pBusiness;
	INT32 layer = pXmlParse->m_signNodeLayer;
	
	pXmlParse->LocateNodeByName(pXmlParse->m_signNode, "OUTPUT");
	pXmlParse->m_parentElement[layer+1] = pXmlParse->m_Child;

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+1], "CODE");
	tmpCode = pXmlParse->GetText();
	DBG_PRINT(("CODE = %s", tmpCode.c_str()));

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+1], "MESS");
	tmpMess = pXmlParse->GetText();
	DBG_PRINT(("MESS = %s", tmpMess.c_str()));
	SetServRetInfo(tmpCode, tmpMess);//将SSL通道的返回信息赋值给m_servRetInfo对象
	
	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+1], "DATA");
	pXmlParse->m_parentElement[layer+2] = pXmlParse->m_Child;
	
	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "NSRSBH");
	g_gNetArg->m_nsrsbh = pXmlParse->GetText();//纳税人识别号
	DBG_PRINT(("NSRSBH = %s", g_gNetArg->m_nsrsbh.c_str()));
	
	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "KPJH");
	g_gNetArg->m_kpjh = pXmlParse->GetText();//开票机号
	DBG_PRINT(("KPJH = %s", g_gNetArg->m_kpjh.c_str()));
	
	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "SBBH");
	g_gNetArg->m_sbbh = pXmlParse->GetText();//设备编号
	DBG_PRINT(("SBBH = %s",g_gNetArg->m_sbbh.c_str()));
	
	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "HASH");
	g_gNetArg->m_hxsh = pXmlParse->GetText();//哈希税号
	DBG_PRINT(("HASH = %s", g_gNetArg->m_hxsh.c_str()));
	
	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "CSSJ");
	p->m_cssj = pXmlParse->GetText();//抄税时间
	DBG_PRINT(("CSSJ = %s", p->m_cssj.c_str()));

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "QKXX");
	p->m_qkxx = pXmlParse->GetText();//清卡信息
	DBG_PRINT(("QKXX = %s", p->m_qkxx.c_str()));
*/

	memset(g_Xml_ExchangeBuf, 0, PROTOCOL_OUT_BUFF_LEN);
	memcpy(g_Xml_ExchangeBuf, pData->pBuff, pData->outLen);
	pData->fill(g_Xml_ExchangeBuf, pData->outLen);
	memset(g_Xml_ExchangeBuf, 0, PROTOCOL_OUT_BUFF_LEN);

	return SUCCESS;
}

INT32 CServQkxxxz::CommunicationProc(void* pDataIn, void* pDataOut, string &strErr)
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
	printf("--------------------------CServQkxxxz rec begin-----------------------------------\n");
	DBG_PRINT(("rec_len = %d", rec_len));
	printf("%s\n", g_Xml_OutBuf);
	printf("\n------------------------CServQkxxxz rec end-------------------------------------\n");
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



























