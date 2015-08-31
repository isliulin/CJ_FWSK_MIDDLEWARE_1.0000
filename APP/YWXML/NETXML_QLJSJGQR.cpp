/*! \file     NETXML_QLJSJGQR.cpp
   \brief    ������õ��м���ӿ� ҵ��: 3.5.����������ȷ��
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "NETXML_QLJSJGQR.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"
#include "GetResultOrganize.h"
#include "ServXml_Qljsjgqr.h"
#include "JSKInfoDef.h"
#include "GlobalNetArg.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CQljsjgqr::CQljsjgqr(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CQljsjgqr::~CQljsjgqr()
{

}


INT32 CQljsjgqr::XmlParse(XMLParse *parse, string &Kpjh, UINT8 &FpmxCount, string &Qtxx)
{

	UINT8 i = 0;

	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	FpmxCount = (UINT8)atoi(parse->GetAttr("count").c_str());	//����XML��õ���ϸ����
	DBG_PRINT(("FpmxCount == %u", FpmxCount));

	m_ywxml_gy.m_sksbbh = parse->GetAttr("skph");//˰���豸�������	
	DBG_PRINT(("m_ywxml_gy.m_sksbbh == %s", m_ywxml_gy.m_sksbbh.c_str()));	

	m_ywxml_gy.m_nsrsbh = parse->GetAttr("nsrsbh");//��˰��ʶ�������	
	DBG_PRINT(("m_ywxml_gy.m_nsrsbh == %s", m_ywxml_gy.m_nsrsbh.c_str()))

	m_ywxml_gy.m_kpjh = parse->GetAttr("kpjh");
	DBG_PRINT(("m_ywxml_gy.m_kpjh == %s", m_ywxml_gy.m_kpjh.c_str()));

	Kpjh = parse->GetAttr("kpjh");//��Ʊ��������
	DBG_PRINT(("Kpjh == %s", Kpjh.c_str()))

	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;
/*
	for (i=0; i<FpmxCount; i++)
	{
		//�õ�group�ڵ�
		parse->LocateNodeByName(parse->m_parentElement[2], "group", i);
		parse->m_parentElement[3] = parse->m_Child;

		parse->LocateNodeByName(parse->m_parentElement[3], "fplxdm");
		m_ywxml_gy.m_fplxdm = parse->GetText();	//��Ʊ���ʹ���
		DBG_PRINT(("m_ywxml_gy.m_fplxdm == %s", m_ywxml_gy.m_fplxdm.c_str()));
	}
*/
	parse->LocateNodeByName(parse->m_parentElement[2], "qtxx");
	Qtxx = parse->GetText();	
	DBG_PRINT(("qtxx == %s", Qtxx.c_str()));

	return SUCCESS;
}

INT32 CQljsjgqr::XmlBuild(XMLConstruct *construct, UINT8 Count, Return_Info *retInfo)
{
	return SUCCESS;
}


INT32 CQljsjgqr::Execute()
{
	Return_Info retInfo;
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	string strErr = "";
	
	string Kpjh = "";
	string Qtxx = "";
	void *pBussness = NULL;

	CGetResultOrganize GetResultOrganize;
	CServQljsjgqr ServQljsjgqr(&GetResultOrganize);
	UINT8 FpmxCount = 0; 

	XmlParse(m_pXmlParse, Kpjh, FpmxCount, Qtxx);

	retcode = ServQljsjgqr.CommunicationProc((void *)pBussness, (void *)pBussness, strErr);
	if(retcode != SUCCESS)
	{
// 		retInfo.m_retCode = JSK_COMMON_ERR_CODE;
// 		retInfo.m_retMsg = strErr;
		m_sslStrErr = strErr;
		return retcode;
	}
	else
	{
		ServQljsjgqr.GetServRetInfo(retInfo.m_retCode, retInfo.m_retMsg);
	}
	
	XmlBuild(m_pXmlConstruct, FpmxCount, &retInfo);
	
	return SUCCESS;
}





