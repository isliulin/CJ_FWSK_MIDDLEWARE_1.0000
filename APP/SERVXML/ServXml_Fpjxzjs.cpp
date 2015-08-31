/*! \file    ServXml_Fpjxzjs.cpp
   \brief    ������õ��м���ӿ� (����ӿ�)ҵ���: ��Ʊ������/�����ӿ�(0013ר��Ʊ)
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
	pXmlBuild->AddText(g_gNetArg->m_nsrsbh);//��˰��ʶ���/��ҵ˰��
	DBG_PRINT(("NSRSBH : %s", g_gNetArg->m_nsrsbh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "HASH");
	pXmlBuild->AddText(g_gNetArg->m_hxsh);//��ϣ˰��
	DBG_PRINT(("HASH : %s", g_gNetArg->m_hxsh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "YSSH");
	pXmlBuild->AddText(g_gNetArg->m_fxsh);//ѹ��˰��,����ֵ
	DBG_PRINT(("YSSH : %s", g_gNetArg->m_fxsh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "DQBH");
	pXmlBuild->AddText(g_gNetArg->m_addrno);//�������,����ֵ
	DBG_PRINT(("DQBH : %s", g_gNetArg->m_addrno.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "KPJH");
	pXmlBuild->AddText(g_gNetArg->m_kpjh);//��Ʊ����
	DBG_PRINT(("KPJH : %s", g_gNetArg->m_kpjh.c_str()));
	
	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "SBBH");
	pXmlBuild->AddText(g_gNetArg->m_sbbh);//˰���豸���
	DBG_PRINT(("SBBH : %s", g_gNetArg->m_sbbh.c_str()));

	pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "DCBB");
	pXmlBuild->AddText(g_gNetArg->m_dcbb);//�ײ�汾,����ֵ
	DBG_PRINT(("DCBB : %s", g_gNetArg->m_dcbb.c_str()));

	CJSKInvManageProc::fplxdm2fplx(p->m_fplxdm, p->m_invtype);
	if (1 == p->m_FlagJSorXZ)//��Ʊ�������ʶ
	{
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "FPJS");//��Ʊ����������ܲ����ڣ��ֶ����ȴ��������Ʊ��
		pXmlBuild->m_parentElement[2] = pXmlBuild->m_NewElement;

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "FPZL");
		memset(tmpBuf, 0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%u", p->m_invtype);
		pXmlBuild->AddText(tmpBuf);//��Ʊ����0����ר���� 2�����գ��� 11�����ˣ��� 12����������
		DBG_PRINT(("FPZL : %s", tmpBuf));

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "LBDM");
		pXmlBuild->AddText(p->m_code);//������
		DBG_PRINT(("LBDM : %s", p->m_code.c_str()));

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "QSHM");
		memset(tmpBuf, 0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%08u", p->m_isno);
		pXmlBuild->AddText(tmpBuf);//��ʼ����
		DBG_PRINT(("QSHM : %s", tmpBuf));

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "FPFS");
		memset(tmpBuf, 0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%u", p->m_fpzfs);
		pXmlBuild->AddText(tmpBuf);//��Ʊ����
		DBG_PRINT(("FPFS : %s", tmpBuf));

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "FLAG");
		pXmlBuild->AddText(p->m_flag);//д��������Ʊ��������Ϣ 40�ֽڣ�Ҫ��base64
		DBG_PRINT(("FLAG : %s", p->m_flag.c_str()));
	}
	
	else if (0 == p->m_FlagJSorXZ)//��Ʊ�����ر�ʶ
	{
		pXmlBuild->AddNode(pXmlBuild->m_parentElement[1], "FPXZ");//��Ʊ�����أ����ܲ�����
		pXmlBuild->m_parentElement[2] = pXmlBuild->m_NewElement;

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "FPZL");
		memset(tmpBuf, 0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%u", p->m_invtype);
		pXmlBuild->AddText(tmpBuf);//��Ʊ����0����ר���� 2�����գ��� 11�����ˣ��� 12����������,����ֵ
		DBG_PRINT(("FPZL : %s", tmpBuf));

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "LBDM");
		pXmlBuild->AddText(p->m_code);//������,����ֵ
		DBG_PRINT(("LBDM : %s", p->m_code.c_str()));

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "QSHM");
		memset(tmpBuf, 0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%08u", p->m_isno);
		pXmlBuild->AddText(tmpBuf);//��ʼ����
		DBG_PRINT(("QSHM : %s", tmpBuf));

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "FPFS");
		memset(tmpBuf, 0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%u", p->m_fpzfs);
		pXmlBuild->AddText(tmpBuf);//��Ʊ����
		DBG_PRINT(("FPFS : %s", tmpBuf));

		pXmlBuild->AddNode(pXmlBuild->m_parentElement[2], "GPSQ");
		pXmlBuild->AddText(p->m_gpsq);//��Ʊ��Ȩ 16�ֽڣ�Ҫ��base64
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
	int tempret;//20150501���,linzihao
	string tmpCode="";
	string tmpMess="";

	CDataInvVol *p = (CDataInvVol *)pBusiness;
	INT32 layer = pXmlParse->m_signNodeLayer;
	
	pXmlParse->LocateNodeByName(pXmlParse->m_signNode, "OUTPUT");
	pXmlParse->m_parentElement[layer+1] = pXmlParse->m_Child;

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+1], "CODE");
	tmpCode= pXmlParse->GetText();//���������0000�ɹ�������ʧ��
	res = atoi(tmpCode.c_str());
	DBG_PRINT(("CODE = %s", tmpCode.c_str()));
	
	if(res != 0)
	{
		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+1], "MESS");
		tmpMess = pXmlParse->GetText();//������Ϣ
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
	g_gNetArg->m_nsrsbh = pXmlParse->GetText();//��˰��ʶ���/��ҵ˰��
	DBG_PRINT(("NSRSBH = %s", g_gNetArg->m_nsrsbh.c_str()));

	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "KPJH");
	g_gNetArg->m_kpjh = pXmlParse->GetText();//��Ʊ����
	DBG_PRINT(("KPJH = %s", g_gNetArg->m_kpjh.c_str()));
	
	pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "SBBH");
	g_gNetArg->m_sbbh= pXmlParse->GetText();//�豸���
	DBG_PRINT(("SBBH = %s", g_gNetArg->m_sbbh.c_str()));

	tempret = pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "FPJS");//��Ʊ����������ܲ����ڣ���Ʊ������ȴ����������������ײ�
	if (tempret == SUCCESS)
	{
		pXmlParse->m_parentElement[layer+3] = pXmlParse->m_Child;

		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+3], "FPJJSMW");
		p->m_fpjjsmw = pXmlParse->GetText();//��Ʊ��������ģ�����Base64
		DBG_PRINT(("FPJJSMW = %s", p->m_fpjjsmw.c_str()));
	}
	else
	{
		DBG_PRINT(("tempret = %d",tempret));
		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+2], "FPXZ");//��Ʊ�����أ����ܲ����ڣ���Ʊ������ȴ����������������ײ�
		pXmlParse->m_parentElement[layer+3] = pXmlParse->m_Child;

		pXmlParse->LocateNodeByName(pXmlParse->m_parentElement[layer+3], "FPJMW");
		p->m_fpjmw = pXmlParse->GetText();//��Ʊ��Ʊ������Ϣ������Base64
		DBG_PRINT(("FPJMW = %s", p->m_fpjmw.c_str()));
	}
	
	return SUCCESS;
}

INT32 CServFpjxzjs::CommunicationProc(void* pDataIn, void* pDataOut, string &strErr)
{
	INT32 res = 0;

	NoteData_Para noteData;//����һ���ṹ��
	noteData.m_appType = NET_FPJXZJS;	//�˴�����ҵ������
	DataOutType dataOut(g_Xml_OutBuf, PROTOCOL_OUT_BUFF_LEN);//��ʼ��һ��DataOutType�����, extern INT8 g_Xml_OutBuf[];һ��ȫ�ֱ���
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
		strErr = "����ͨ�Ŵ���!";
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


