/*! \file    YWXML_TJXXCX.cpp
   \brief    ������õ��м���ӿ� ҵ��2.19ͳ����Ϣ��ѯ
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "YWXML_TJXXCX.h"
#include "JSKInvManageProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//���캯��
//-------------------------------------------------------------------------------------------
CTjxxcx::CTjxxcx(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//��������
//-------------------------------------------------------------------------------------------
CTjxxcx::~CTjxxcx()
{

}

INT32 CTjxxcx::XmlParse(XMLParse *parse, CTjxxhz *tjxxhz)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh= parse->GetText();		//˰���տ�����
	DBG_PRINT(("YWXML_TJXXCX: jqbh = %s", m_ywxml_gy.m_jqbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "nsrsbh");
	m_ywxml_gy.m_nsrsbh= parse->GetText();		//��˰��ʶ���
	DBG_PRINT(("YWXML_TJXXCX: nsrsbh = %s", m_ywxml_gy.m_nsrsbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "sksbbh");
	m_ywxml_gy.m_sksbbh= parse->GetText();		//˰���豸���
	DBG_PRINT(("YWXML_TJXXCX: sksbbh = %s", m_ywxml_gy.m_sksbbh.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "sksbkl");
	m_ywxml_gy.m_sksbkl= parse->GetText();		//˰���豸����
	DBG_PRINT(("YWXML_TJXXCX: sksbkl = %s", m_ywxml_gy.m_sksbkl.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();		//��Ʊ���ʹ���
	DBG_PRINT(("YWXML_TJXXCX: fplxdm = %s", m_ywxml_gy.m_fplxdm.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "qsrq");
	tjxxhz[0].m_Qsrq = atoi(parse->GetText().c_str());		//��ʼ����
	DBG_PRINT(("YWXML_TJXXCX: qsrq = %u", tjxxhz[0].m_Qsrq));

	parse->LocateNodeByName(parse->m_parentElement[2], "zzrq");
	tjxxhz[0].m_Jzrq = atoi(parse->GetText().c_str());		//��ֹ����
	DBG_PRINT(("YWXML_TJXXCX: zzrq = %u", tjxxhz[0].m_Jzrq));
	
	return SUCCESS;
}

INT32 CTjxxcx::XmlBuild(XMLConstruct *construct, Return_Info *retInfo, CTjxxhz *tjxxhz, INT32 MonthCount)
{
	INT8 buf[256];
	memset(buf,0,sizeof(buf));
	float fRate = 1.0;
	
	//���body�ڵ�
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[2], "fplxdm");
	construct->AddText(m_ywxml_gy.m_fplxdm);	//��Ʊ���ʹ���
	DBG_PRINT(("YWXML_TJXXCX: fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));

	construct->AddNode(construct->m_parentElement[2], "tjxx");
	construct->m_parentElement[3] = construct->m_NewElement;
	memset(buf,0,sizeof(buf));
	sprintf(buf, "%d", MonthCount);
	construct->AddAttr("count",buf);
	DBG_PRINT(("YWXML_TJXXCX: MonthCount : %s", buf));

	for (INT32 temp_i=0; temp_i<MonthCount; temp_i++)
	{
		construct->AddNode(construct->m_parentElement[3], "group");
		construct->m_parentElement[4] = construct->m_NewElement;
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%d", temp_i);
		construct->AddAttr("xh",buf);
		DBG_PRINT(("YWXML_TJXXCX: Month_xh : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "qsrq");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%u", tjxxhz[temp_i].m_Qsrq);
		construct->AddText(buf);	//��ʼ����
		DBG_PRINT(("YWXML_TJXXCX: qsrq : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "jzrq");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%u", tjxxhz[temp_i].m_Jzrq);
		construct->AddText(buf);	//��ֹ����
		DBG_PRINT(("YWXML_TJXXCX: jzrq : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "qckcfs");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%u", tjxxhz[temp_i].m_Qckcfs);
		construct->AddText(buf);	//�ڳ�������
		DBG_PRINT(("YWXML_TJXXCX: qckcfs : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "lgfpfs");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%u", tjxxhz[temp_i].m_Lgfpfs);
		construct->AddText(buf);	//�칺��Ʊ����
		DBG_PRINT(("YWXML_TJXXCX: lgfpfs : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "thfpfs");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%u", tjxxhz[temp_i].m_Thfpfs);
		construct->AddText(buf);	//�˻ط�Ʊ����
		DBG_PRINT(("YWXML_TJXXCX: thfpfs : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "zsfpfs");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%u", tjxxhz[temp_i].m_Zsfpfs);
		construct->AddText(buf);	//������Ʊ����
		DBG_PRINT(("YWXML_TJXXCX: zsfpfs : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "zffpfs");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%u", tjxxhz[temp_i].m_Zffpfs);
		construct->AddText(buf);	//���Ϸ�Ʊ����
		DBG_PRINT(("YWXML_TJXXCX: zffpfs : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "fsfpfs");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%u", tjxxhz[temp_i].m_Fsfpfs);
		construct->AddText(buf);	//������Ʊ����
		DBG_PRINT(("YWXML_TJXXCX: fsfpfs : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "fffpfs");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%u", tjxxhz[temp_i].m_Fffpfs);
		construct->AddText(buf);	//���Ϸ�Ʊ����
		DBG_PRINT(("YWXML_TJXXCX: fffpfs : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "kffpfs");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%u", tjxxhz[temp_i].m_Kffpfs);
		construct->AddText(buf);	//�շϷ�Ʊ����
		DBG_PRINT(("YWXML_TJXXCX: kffpfs : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "qmkcfs");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%u", tjxxhz[temp_i].m_Qmkcfs);
		construct->AddText(buf);	//��ĩ������
		DBG_PRINT(("YWXML_TJXXCX: qmkcfs : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "zsfpljje");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%.2f", ((double)tjxxhz[temp_i].m_Zsfpljje * fRate)/SUM_EXTENSION);
		construct->AddText(buf);	//������Ʊ�ۼƽ��
		DBG_PRINT(("YWXML_TJXXCX: zsfpljje : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "zsfpljse");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%.2f", ((double)tjxxhz[temp_i].m_Zsfpljse * fRate)/SUM_EXTENSION);
		construct->AddText(buf);	//������Ʊ�ۼ�˰��
		DBG_PRINT(("YWXML_TJXXCX: zsfpljse : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "zffpljje");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%.2f", ((double)tjxxhz[temp_i].m_Zffpljje * fRate)/SUM_EXTENSION);
		construct->AddText(buf);	//���Ϸ�Ʊ�ۼƽ��
		DBG_PRINT(("YWXML_TJXXCX: zffpljje : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "zffpljse");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%.2f", ((double)tjxxhz[temp_i].m_Zffpljse * fRate)/SUM_EXTENSION);
		construct->AddText(buf);	//���Ϸ�Ʊ�ۼ�˰��
		DBG_PRINT(("YWXML_TJXXCX: zffpljse : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "fsfpljje");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%.2f", ((double)tjxxhz[temp_i].m_Fsfpljje * fRate)/SUM_EXTENSION);
		construct->AddText(buf);	//������Ʊ�ۼƽ��
		DBG_PRINT(("YWXML_TJXXCX: fsfpljje : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "fsfpljse");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%.2f", ((double) tjxxhz[temp_i].m_Fsfpljse * fRate)/SUM_EXTENSION);
		construct->AddText(buf);	//������Ʊ�ۼ�˰��
		DBG_PRINT(("YWXML_TJXXCX: fsfpljse : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "fffpljje");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%.2f", ((double) tjxxhz[temp_i].m_Fffpljje * fRate)/SUM_EXTENSION);
		construct->AddText(buf);	//���Ϸ�Ʊ�ۼƽ��
		DBG_PRINT(("YWXML_TJXXCX: fffpljje : %s", buf));

		construct->AddNode(construct->m_parentElement[4], "fffpljse");
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%.2f", ((double) tjxxhz[temp_i].m_Fffpljse * fRate)/SUM_EXTENSION);
		construct->AddText(buf);	//���Ϸ�Ʊ�ۼ�˰��
		DBG_PRINT(("YWXML_TJXXCX: fffpljse : %s", buf));
	}
	
	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);	//���ش���
	DBG_PRINT(("YWXML_TJXXCX: returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);		//������Ϣ
	DBG_PRINT(("YWXML_TJXXCX: returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
}


INT32 CTjxxcx::Execute()
{
	Return_Info retInfo;	//	������Ϣ�����
	CTjxxhz tjxxhz[TJXXCX_MONTHMAX];		//ͳ����Ϣ������
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	INT32 MonthCount = TJXXCX_MONTHMAX;//֧�ֵ�����ѯ����

	XmlParse(m_pXmlParse, tjxxhz);	//����XML��������
	CheckYWXmlPara(retInfo.m_retMsg);

	DBG_PRINT(("YWXML_TJXXCX: fplxdm = %s", m_ywxml_gy.m_fplxdm.c_str()));
	retcode = CJSKInvManageProc::TJXXCX_Proc(m_ywxml_gy.m_fplxdm, MonthCount, tjxxhz, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
		MonthCount = 0;
	}

	XmlBuild(m_pXmlConstruct, &retInfo, tjxxhz, MonthCount);	//����XML��װ����

	return SUCCESS;
}

