/*! \file    NETXML_WLLQFPJGQR.cpp
   \brief    ������õ��м���ӿ� ҵ��3.7 ������ȡ��Ʊ���ȷ��
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "NETXML_WLLQFPJGQR.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"
#include "StructOrganize.h"
#include "ServXml_Fpjxzjs.h"
#include "JSKInfoDef.h"

//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CWllqfpjgqr::CWllqfpjgqr(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CWllqfpjgqr::~CWllqfpjgqr()
{

}

INT32 CWllqfpjgqr::XmlParse(XMLParse *parse, CInvVol *invvol, string &strQtxx)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;

	m_ywxml_gy.m_sksbbh = parse->GetAttr("skph");		//�̺�(���︳ֵ��˰���豸���)
	DBG_PRINT(("NETXML_WLLQFPJGQR: skph = %s", m_ywxml_gy.m_sksbbh.c_str()));	
	m_ywxml_gy.m_nsrsbh = parse->GetAttr("nsrsbh");		//��˰��ʶ���
	DBG_PRINT(("NETXML_WLLQFPJGQR: nsrsbh = %s", m_ywxml_gy.m_nsrsbh.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();		//��Ʊ���ʹ���
	invvol->m_fplxdm = m_ywxml_gy.m_fplxdm;
	DBG_PRINT(("NETXML_WLLQFPJGQR: fplxdm = %s", m_ywxml_gy.m_fplxdm.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fpdm");
	invvol->m_code = parse->GetText();		//��Ʊ����
	DBG_PRINT(("NETXML_WLLQFPJGQR: fpdm = %s", invvol->m_code.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "qshm");
	invvol->m_isno = atoi(parse->GetText().c_str());		//��Ʊ��ʼ����
	DBG_PRINT(("NETXML_WLLQFPJGQR: qshm = %u", invvol->m_isno));

	parse->LocateNodeByName(parse->m_parentElement[2], "zzhm");
	invvol->m_ieno = atoi(parse->GetText().c_str());		//��Ʊ��ֹ����
	DBG_PRINT(("NETXML_WLLQFPJGQR: zzhm = %u", invvol->m_ieno));

	invvol->m_fpzfs = invvol->m_ieno - invvol->m_isno + 1;

	parse->LocateNodeByName(parse->m_parentElement[2], "qtxx");
	strQtxx = parse->GetText();		//������Ϣ
	DBG_PRINT(("NETXML_WLLQFPJGQR: qtxx = %s", strQtxx.c_str()));
	
	return SUCCESS;
}

INT32 CWllqfpjgqr::XmlBuild(XMLConstruct *construct, Return_Info *retInfo, CInvVol *invvol)
{
	//���body�ڵ�
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[2], "fplxdm");
	construct->AddText(m_ywxml_gy.m_fplxdm);	//��Ʊ���ʹ���,����ֵ
	DBG_PRINT(("NETXML_WLLQFPJGQR: fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));

	construct->AddNode(construct->m_parentElement[2], "gpxxjgqr");
	construct->AddText(invvol->m_fpjjsmw);	//��Ʊ��Ϣ���ȷ�϶�Ӧ��Ʊ������������ķ�Ʊ����������Ϣ
	DBG_PRINT(("NETXML_WLLQFPJGQR: gpxxjgqr : %s", invvol->m_fpjjsmw.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);	//���ش���
	DBG_PRINT(("NETXML_WLLQFPJGQR: returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);		//������Ϣ
	DBG_PRINT(("NETXML_WLLQFPJGQR: returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
}


INT32 CWllqfpjgqr::Execute()
{
	//XML�������������
	CInvVol invvol;		//��Ʊ������Ϣ��
	string qtxx("");		//��Ʊ��Ϣ����
	XmlParse(m_pXmlParse, &invvol, qtxx);	//����XML��������
	invvol.m_FlagJSorXZ = 1; //��Ӧ��:��Ʊ�����ҵ��
	invvol.m_flag = qtxx; //��Ʊ�����ҵ���е�"д��������Ʊ������"����3.7��������"������Ϣ"

	CStructOrganize structorgnize;
	CServFpjxzjs servfpjjs(&structorgnize);//��Ӧ��:��Ʊ�����ҵ��
	string strErr("");
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	retcode = servfpjjs.CommunicationProc((void*)(&invvol), (void*)(&invvol), strErr);

	Return_Info retInfo;	//	������Ϣ�����
	if(retcode != SUCCESS)
	{
// 		retInfo.m_retCode = JSK_COMMON_ERR_CODE;
// 		retInfo.m_retMsg = strErr;
		m_sslStrErr = strErr;
		return retcode;
	}
	else
	{
		servfpjjs.GetServRetInfo(retInfo.m_retCode, retInfo.m_retMsg);
	}

	XmlBuild(m_pXmlConstruct, &retInfo, &invvol); //����XML��װ����

	return SUCCESS;
}





























