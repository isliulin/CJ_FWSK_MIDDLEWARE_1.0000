 /*! \file    NETXML_WLLQFP.cpp
   \brief    ������õ��м���ӿ� ҵ��3.6 ������ȡ��Ʊ
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "NETXML_WLLQFP.h"

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
CWllqfp::CWllqfp(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CWllqfp::~CWllqfp()
{

}

INT32 CWllqfp::XmlParse(XMLParse *parse, CInvVol *invvol, string &strQtxx)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;

	m_ywxml_gy.m_sksbbh = parse->GetAttr("skph");		//�̺�(���︳ֵ��˰���豸���)
	DBG_PRINT(("NETXML_WLLQFP: skph = %s", m_ywxml_gy.m_sksbbh.c_str()));	
	m_ywxml_gy.m_nsrsbh = parse->GetAttr("nsrsbh");		//��˰��ʶ���
	DBG_PRINT(("NETXML_WLLQFP: nsrsbh = %s", m_ywxml_gy.m_nsrsbh.c_str()));	
	
	m_ywxml_gy.m_kpjh = parse->GetAttr("kpjh");
	DBG_PRINT(("m_ywxml_gy.m_kpjh == %s", m_ywxml_gy.m_kpjh.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();		//��Ʊ���ʹ���
	invvol->m_fplxdm = m_ywxml_gy.m_fplxdm;
	DBG_PRINT(("NETXML_WLLQFP: fplxdm = %s", m_ywxml_gy.m_fplxdm.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fpdm");
	invvol->m_code = parse->GetText();		//��Ʊ����
	DBG_PRINT(("NETXML_WLLQFP: fpdm = %s", invvol->m_code.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fpqshm");
	invvol->m_isno = atoi(parse->GetText().c_str());		//��Ʊ��ʼ����
	DBG_PRINT(("NETXML_WLLQFP: fpqshm = %u", invvol->m_isno));

	parse->LocateNodeByName(parse->m_parentElement[2], "fpzzhm");
	invvol->m_ieno = atoi(parse->GetText().c_str());		//��Ʊ��ֹ����
	DBG_PRINT(("NETXML_WLLQFP: fpzzhm = %u", invvol->m_ieno));

	parse->LocateNodeByName(parse->m_parentElement[2], "zfs");
	invvol->m_fpzfs = atoi(parse->GetText().c_str());		//��Ʊ�ܷ���
	DBG_PRINT(("NETXML_WLLQFP: fpzfs = %u", invvol->m_fpzfs));

	parse->LocateNodeByName(parse->m_parentElement[2], "qtxx");
	strQtxx = parse->GetText();		//������Ϣ
	DBG_PRINT(("NETXML_WLLQFP: qtxx = %s", strQtxx.c_str()));

	return SUCCESS;
}

INT32 CWllqfp::XmlBuild(XMLConstruct *construct, Return_Info *retInfo, CInvVol *invvol)
{
	INT8 buf[256];
	memset(buf,0,sizeof(buf));
	//���body�ڵ�
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[2], "fplxdm");
	construct->AddText(m_ywxml_gy.m_fplxdm);	//��Ʊ���ʹ���
	DBG_PRINT(("NETXML_WLLQFP: fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));

	construct->AddNode(construct->m_parentElement[2], "fpdm");
	construct->AddText(invvol->m_code);	//��Ʊ����
	DBG_PRINT(("NETXML_WLLQFP: fpdm : %s", invvol->m_code.c_str()));

	construct->AddNode(construct->m_parentElement[2], "qshm");
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%08u", invvol->m_isno);
	construct->AddText(buf);	//��Ʊ��ʼ����
	DBG_PRINT(("NETXML_WLLQFP: qshm : %s", buf));

	construct->AddNode(construct->m_parentElement[2], "zzhm");
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%08u", invvol->m_ieno);
	construct->AddText(buf);	//��Ʊ��ֹ����
	DBG_PRINT(("NETXML_WLLQFP: zzhm : %s", buf));

	construct->AddNode(construct->m_parentElement[2], "fpfs");
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%u",  invvol->m_fpzfs);
	construct->AddText(buf);	//��Ʊ����
	DBG_PRINT(("NETXML_WLLQFP: fpfs : %s", buf));

	construct->AddNode(construct->m_parentElement[2], "lgrq");
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%u", invvol->m_date);
	construct->AddText(buf);	//�칺����(��ʱ�Թ������ڴ���),����ֵ
	DBG_PRINT(("NETXML_WLLQFP: lgrq : %s", buf));

	construct->AddNode(construct->m_parentElement[2], "gpxxmw");
	construct->AddText(invvol->m_fpjmw);	//��Ʊ��Ϣ���Ķ�Ӧ��Ʊ�����ؽ������ķ�Ʊ������Ϣ
	DBG_PRINT(("NETXML_WLLQFP: gpxxmw : %s", invvol->m_fpjmw.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);	//���ش���
	DBG_PRINT(("NETXML_WLLQFP: returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);		//������Ϣ
	DBG_PRINT(("NETXML_WLLQFP: returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
}


INT32 CWllqfp::Execute()
{
	//XML�������������
	CInvVol invvol;		//��Ʊ������Ϣ��
	string qtxx("");		//��Ʊ��Ϣ����
	XmlParse(m_pXmlParse, &invvol, qtxx);	//����XML��������
	invvol.m_FlagJSorXZ = 0; //��Ӧ��:��Ʊ������ҵ��
	invvol.m_gpsq = qtxx; //��Ʊ������ҵ���е�"��Ʊ��Ȩ"����3.6��������"������Ϣ"

	CStructOrganize structorgnize;
	CServFpjxzjs servfpjxz(&structorgnize);//��Ӧ��:��Ʊ������ҵ��
	string strErr("");
	INT32 retcode = 0;
	retcode = servfpjxz.CommunicationProc((void*)(&invvol), (void*)(&invvol), strErr);
	
	//XML��װ��Ҫ������	
	Return_Info retInfo;	//������Ϣ
	if(retcode != SUCCESS)
	{
// 		retInfo.m_retCode = JSK_COMMON_ERR_CODE;
// 		retInfo.m_retMsg = strErr;
		m_sslStrErr = strErr;
		return retcode;
	}
	else
	{
		servfpjxz.GetServRetInfo(retInfo.m_retCode, retInfo.m_retMsg);
	}

	XmlBuild(m_pXmlConstruct, &retInfo, &invvol);	//����XML��װ����

	return SUCCESS;
}


