/*! \file    SerXml_Yccb.cpp
   \brief    ������õ��м���ӿ� (����ӿ�)ҵ����: Զ�̳����ӿ�(0013ר��Ʊ)
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "ServXml_Yccb.h"
#include "ServWlcb.h"
#include "GlobalNetArg.h"
#if SSL_USE_TYPE == 1
#include "uniAcceptFrameworkApi.h"
#endif

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

CServYccb::CServYccb(ProtocolOrganize *p):ProtocolXML(p)
{
	setDeclaration(XML_DEF_VERSION, XML_DEF_ENCODING, GBK_CHAR_TYPE);
	setXmlSaveFile(XML_DEF_YCCB_REQFILE, XML_DEF_BUSSINESS_RSPFILE); 
	setRootName("hzData");
}

CServYccb::~CServYccb()
{
	DBG_PRINT(("in ~CServYccb()"))
}

INT32 CServYccb::XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("IN CServYccb::XmlBusinessBuild"));
	DBG_ASSERT_EXIT((pBusiness != NULL), (" pBusiness == NULL!"));
	
	char tmpBuf[256];
	CServWlcb *p = (CServWlcb *)pBusiness;

	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "nsrsbh");
	pXmlBuild->AddText(g_gNetArg->m_nsrsbh);//��˰��ʶ���,������
	DBG_PRINT(("nsrsbh : %s", g_gNetArg->m_nsrsbh.c_str()));
	
	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "hxsh");
	pXmlBuild->AddText(g_gNetArg->m_hxsh);//��ϣ˰��,������
	DBG_PRINT(("hxsh : %s", g_gNetArg->m_hxsh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "sbbh");
	pXmlBuild->AddText(g_gNetArg->m_sbbh);//˰���̻��˰���豸���,������
	DBG_PRINT(("sbbh : %s", g_gNetArg->m_sbbh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "fplxdm");
	pXmlBuild->AddText(p->m_fplxdm);//��Ʊ���ʹ��� 025 ��Ʊ �ɲ���
	
	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "ssq");
	memset(tmpBuf, 0, sizeof(tmpBuf));
	sprintf(tmpBuf, "%02d", (atoi(p->m_ssqrs.c_str()))%100);
	pXmlBuild->AddText(tmpBuf);//����������,������
	DBG_PRINT(("ssq : %s", g_gNetArg->m_hxsh.c_str()));

 	DBG_PRINT(("hzsj : %s", p->m_hzxx.c_str()));
	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "hzsj");
	pXmlBuild->AddText(p->m_hzxx);//��������,������

	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "bssj");
	pXmlBuild->AddText(p->m_cssj);//��˰ʱ��yyyy-MM-dd HH:mm��ʽ �ɲ���
	
	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "kpjh");
	pXmlBuild->AddText(g_gNetArg->m_kpjh);//��Ʊ���� �ɲ���
	
	return SUCCESS;
}

INT32 CServYccb::XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("CServYccb::XmlBusinessParse Begin"));
	
	memset(g_Xml_ExchangeBuf, 0, PROTOCOL_OUT_BUFF_LEN);
	memcpy(g_Xml_ExchangeBuf, pData->pBuff, pData->outLen);
	pData->fill(g_Xml_ExchangeBuf, pData->outLen);
	memset(g_Xml_ExchangeBuf, 0, PROTOCOL_OUT_BUFF_LEN);
	

	return SUCCESS;
}

INT32 CServYccb::CommunicationProc(void* pDataIn, void* pDataOut, string &strErr)
{
	INT32 res = 0;

	NoteData_Para noteData;
	noteData.m_appType = NET_YCCB;	//�˴�����ҵ������
	DataOutType dataOut(g_Xml_OutBuf, PROTOCOL_OUT_BUFF_LEN);
	res = BuildXml(pDataIn, &dataOut, &noteData, strErr);
	if (res != SUCCESS)
	{
		return res;
	}
	
	DBG_PRINT(("res = %u", res));
	DBG_PRINT(("outLen = %u", dataOut.outLen));

	//////////////////////////////////////////////////////////////////////////
	//�˴�Ϊ�������̣���������֯�����ݷ��͸���SSL�ӿڣ����յ������ݷ���g_Xml_OutBuf�С�
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
		strErr = "����ͨ�Ŵ���!";
		return retval;
	}

	DBG_PRINT(("rec_len = %d", rec_len));
	dataOut.fill(g_Xml_ExchangeBuf, rec_len);
	memset(g_Xml_ExchangeBuf, 0, PROTOCOL_OUT_BUFF_LEN);

#ifdef XML_DEBUG_OUT
	printf("--------------------------CServYccb rec begin-----------------------------------\n");
	DBG_PRINT(("rec_len = %d", rec_len));
	printf("%s\n", g_Xml_OutBuf);
	printf("\n------------------------CServYccb rec end-------------------------------------\n");
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


