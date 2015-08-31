 /*! \file    NETXML_LXXXSC.cpp
   \brief    ������õ��м���ӿ� ҵ��3.5 ������Ϣ�ϴ�
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "NETXML_LXXXSC.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"
#include "StructOrganize.h"
#include "ServXml_NsrPara.h"
#include "JSKInfoDef.h"

//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CLxxxsc::CLxxxsc(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CLxxxsc::~CLxxxsc()
{

}

INT32 CLxxxsc::XmlParse(XMLParse *parse, CInvKind *invkind, string &strScjzrq, string &strLxkpsc, string &strQtxx)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	m_ywxml_gy.m_sksbbh = parse->GetAttr("skph");		//�̺�(���︳ֵ��˰���豸���)
	DBG_PRINT(("NETXML_LXXXSC: skph = %s", m_ywxml_gy.m_sksbbh.c_str()));	
	m_ywxml_gy.m_nsrsbh = parse->GetAttr("nsrsbh");		//��˰��ʶ���
	DBG_PRINT(("NETXML_LXXXSC: nsrsbh = %s", m_ywxml_gy.m_nsrsbh.c_str()));	
	
	m_ywxml_gy.m_kpjh = parse->GetAttr("kpjh");
	DBG_PRINT(("m_ywxml_gy.m_kpjh == %s", m_ywxml_gy.m_kpjh.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[2], "scjzrq");
	strScjzrq = parse->GetText();		//�ϴ���ֹ����
	DBG_PRINT(("NETXML_LXXXSC: scjzrq = %s", strScjzrq.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "lxkpsc");
	strLxkpsc = parse->GetText();		//���߿�Ʊʱ��
	DBG_PRINT(("NETXML_LXXXSC: lxkpsc = %s", strLxkpsc.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "lxzsljje");
	invkind->m_maxSum = double2int(atof(parse->GetText().c_str()) * SUM_EXTENSION); //���������ۼƽ��
	if (invkind->m_maxSum < 0)
	{
		invkind->m_maxSum = -invkind->m_maxSum;
	}
	DBG_PRINT(("NETXML_LXXXSC: lxzsljje = %d", invkind->m_maxSum));

	parse->LocateNodeByName(parse->m_parentElement[2], "qtxx");
	strQtxx = parse->GetText();		//������Ϣ
	DBG_PRINT(("NETXML_LXXXSC: qtxx = %s", strQtxx.c_str()));

	return SUCCESS;
}

INT32 CLxxxsc::XmlBuild(XMLConstruct *construct, Return_Info *retInfo, string strLzkzxx)
{
	INT8 buf[256];
	memset(buf,0,sizeof(buf));
	INT32 temp_count = 1;//������Ϣ������Ӧ����紫�룬��ʱ����Ϊ�ֲ�����,����ֵ

	//���body�ڵ�
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;
	sprintf(buf, "%d", temp_count);
	construct->AddAttr("count", buf);
	construct->AddAttr("skph", m_ywxml_gy.m_sksbbh);//�̺�,����˰���豸��Ŵ���
	construct->AddAttr("nsrsbh", m_ywxml_gy.m_nsrsbh);//��˰��ʶ���

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);	//���ش���
	DBG_PRINT(("NETXML_LXXXSC: returncode : %s", retInfo->m_retCode.c_str()));

	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);		//������Ϣ
	DBG_PRINT(("NETXML_LXXXSC: returnmsg : %s", retInfo->m_retMsg.c_str()));

	for (INT32 temp_i=1; temp_i<=temp_count; temp_i++)
	{
		construct->AddNode(construct->m_parentElement[2], "group");
		construct->m_parentElement[3] = construct->m_NewElement;
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%d", temp_i);
		construct->AddAttr("xh", buf);

		construct->AddNode(construct->m_parentElement[3], "fplxdm");
		construct->AddText(m_ywxml_gy.m_fplxdm);		//��Ʊ���ʹ���,����ֵ
		DBG_PRINT(("NETXML_LXXXSC: fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));

		construct->AddNode(construct->m_parentElement[3], "lxkzxx");
		construct->AddText(strLzkzxx);		//���߿�����Ϣ
		DBG_PRINT(("NETXML_LXXXSC: lxkzxx : %s", strLzkzxx.c_str()));
	}
	
	return SUCCESS;
}


INT32 CLxxxsc::Execute()
{
	//XML�������������
	CInvKind invkind;		//��˰��Ʊ�ֱ�
	string scjzrq("");		//�ϴ���ֹ����
	string lxkpsc("");		//���߿�Ʊʱ��
	string qtxx("");		//������Ϣ
	XmlParse(m_pXmlParse, &invkind, scjzrq, lxkpsc, qtxx);	//����XML��������,m_pXmlParse(�����Ա)�ѱ���ʼ��ΪxmlInput
	//const char *temp_qtxx =  qtxx.c_str();//��3.5��������"������Ϣ"ת��Ϊ��ҵ���������е�"��Ȩ��Ϣ"

	CStructOrganize structorgnize;
	CNsrPara nsrpara(&structorgnize);
	CNsrParaOutInfo CNsrParaOutInfo;
	string strErr("");
	INT32 retcode = 0;
	retcode = nsrpara.CommunicationProc((void*)qtxx.c_str(), (void*)(&CNsrParaOutInfo), strErr);

	//XML��װ��Ҫ������
	Return_Info retInfo;	//������Ϣ
	string lzkzxx = CNsrParaOutInfo.m_sqxx;		//����ҵ���������е�"��Ȩ��Ϣ"��ֵ��3.5�е�"���߿�����Ϣ"
	if(retcode != SUCCESS)
	{
// 		retInfo.m_retCode = JSK_COMMON_ERR_CODE;
// 		retInfo.m_retMsg = strErr;
		m_sslStrErr = strErr;
		return retcode;
	}
	else
	{
		nsrpara.GetServRetInfo(retInfo.m_retCode, retInfo.m_retMsg);
	}
	XmlBuild(m_pXmlConstruct, &retInfo, lzkzxx);	//����XML��װ����,m_pXmlConstruct(�����Ա)�ѱ���ʼ��ΪxmlOutput

	return SUCCESS;
}

