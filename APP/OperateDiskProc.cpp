
#include "OperateDiskProc.h"
#include "YWXmlBase.h"
#include "CGlobalArgLib.h"
#include "GlobalNetArg.h"
#include "commonFunc.h"
#include "VersionConfig.h"

/*
#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
#include "YWXML_SKSBBHCX.h"
#include "YWXML_SKPXXCX.h"
#include "YWXML_BSPXXCX.h"
#include "YWXML_SQSLCX.h"
#include "YWXML_GPXXCX.h"
#include "YWXML_KLBG.h"
#include "YWXML_JKSJCX.h"
#include "YWXML_GPXXXP.h"
#include "YWXML_GPXXXPJS.h"
#include "YWXML_FPKJ.h"
#include "YWXML_FPZF.h"
#include "YWXML_FPCX.h"
#include "YWXML_SKPBSP.h"
#include "YWXML_BSPFPFF.h"
#include "YWXML_BSPFPSH.h"
#include "YWXML_SJCB.h"
#include "YWXML_JKHC.h"
#include "YWXML_TJXXCX.h"
#include "YWXML_LXXXXP.h"
#include "YWXML_FPSSSC.h"
#include "YWXML_FPGX.h"
#include "YWXML_FPDR.h"
#include "YWXML_FJTH.h"
#include "YWXML_BSPFPCX.h"
#include "YWXML_SKSBQTYXXCX.h"
#include "YWXML_BGZSKL.h"
#include "YWXML_FPBL.h"
#include "YWXML_HQLXSJ.h"
#include "YWXML_ERRUPINV.h"

#include "NETXML_WLLQFPJGQR.h"
#include "NETXML_WLLQFP.h"
#include "NETXML_LXXXSC.h"
#endif
*/
#include "NETXML_FPSCJGHQ.h"
#include "NETXML_FPSC.h"
#include "NETXML_QLJS.h"
#include "NETXML_QLJSJGQR.h"
#include "NETXML_WLCB.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

static int g_initParaFlag = 0;

#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
int InitPara(string &strErr)
{
	DBG_PRINT(("==============InitPara Begin================"));
	if(g_initParaFlag == 0)
	{
		CDB *m_db = CDB::GetInstance();
		m_db->Open();
		m_db->Init();
		CommonSleep(300);
		
		UINT8 index;
		for(index = 0; index<DET_ARRAY_LEN; index++)
		{
			s_DetArray[index] = new CInvDet;
			//DBG_PRINT(("s_DetArray[%d] = %x", index, s_DetArray[index]));
			DBG_ASSERT_EXIT((s_DetArray[index] != NULL), (" s_DetArray[index] == NULL!"));
		}
		
		g_globalArgLib = CGlobalArgLib::GetInstance();
		g_gNetArg = CGlobalNetArg::GetInstance();
		g_globalArgLib->InitGlobalArg();
		
		INT8 tmpbuf[64];
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%u", g_globalArgLib->m_corpInfo->m_Kpjhm);
		g_gNetArg->InitGlobalNetArg(g_globalArgLib->m_corpInfo->m_Nsrsbh, "", g_globalArgLib->m_strHashNo, tmpbuf, g_globalArgLib->m_corpInfo->m_Jspsbh, "");
		g_gNetArg->SetZskl(g_globalArgLib->m_strZskl);

		g_initParaFlag = 1;
	}
	DBG_PRINT(("==============InitPara End================"));
}
#endif

void OperateDisk(string sInputInfo, string &sOutputInfo)
{
/*
#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
	DBG_PRINT(("================= Begin OperateDisk() ================="));
	XMLParse xmlInput;
	XMLConstruct xmlOutput;
	string strID;
	Return_Info retInfo;
	INT32 ret = 0;
	INT8 tmpBuf[32];

	if(g_initParaFlag == 0)
	{
		InitPara(retInfo.m_retMsg);
		g_initParaFlag = 1;
	}

	ret = CYWXmlBase::StartYWXml(sInputInfo, &xmlInput, &xmlOutput, strID);
	if(ret != JSK_SUCCESS)
	{
		retInfo.m_retCode = JSK_COMMON_ERR_CODE;
		retInfo.m_retMsg = "�����������ݴ���";
		sOutputInfo = "";
		CYWXmlBase::ErrYWXml(&xmlInput, &xmlOutput, &retInfo, sOutputInfo);
		return;
	}
	DBG_PRINT(("strID ============= %s", strID.c_str()));

	CYWXmlBase *pXmlYW = NULL;

	//��2�� ˰���տ����˰���豸�ӿ�
	if(strID == BUSINESS_YWID_SKSBBH)			//˰���豸���
	{
		pXmlYW = new CSksbbhcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_SKPXXCX)		//˰���豸��Ϣ��ѯ
	{
		pXmlYW = new CSkpxxcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_SKSBQTYXXCX)	//˰���豸������Ϣ��ѯ
	{
		pXmlYW = new CSksbqtxxcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_BSPXXCX)		//��˰����Ϣ��ѯ
	{
		pXmlYW = new CBspxxcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_JKSJCX)		//������ݲ�ѯ
	{
		pXmlYW = new CJksjcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_SQSLCX)		//��Ȩ˰�ʲ�ѯ
	{
		pXmlYW = new CSqslcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_GPXXCX)		//��Ʊ��Ϣ��ѯ
	{
		pXmlYW = new CGpxxcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_GPXXXP)		//��Ʊ��Ϣд��
	{
		pXmlYW = new CGpxxxp(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_GPXXXPJS)	//��Ʊ��Ϣд�̽���
	{
		pXmlYW = new CGpxxxpjs(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_KLBG)		//������
	{
		pXmlYW = new CKlbg(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_FPKJ)		//��Ʊ����
	{
		pXmlYW = new CFpkj(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_FPZF)		//��Ʊ����
	{
		pXmlYW = new CFpzf(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_FPCX)		//��Ʊ��ѯ
	{
		pXmlYW = new CFpcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_SKPBSP)		//˰���豸��˰����ϲ���
	{
		pXmlYW = new CSkpBsp(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_BSPFPCX)		//��˰�̷�Ʊ��ѯ
	{
		pXmlYW = new CBspfpcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_BSPFPFF)		//��Ʊ�ַ�
	{
		pXmlYW = new CBspfpff(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_BSPFPSH)		//��Ʊ�ջ�
	{
		pXmlYW = new CBspfpsh(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_SJCB)		//���ݳ���
	{
		pXmlYW = new CSjcb(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_JKHC)		//��ػش�
	{
		pXmlYW = new CJkhc(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_TJXXCX)		//��Ʊͳ����Ϣ��ѯ
	{
		pXmlYW = new CTjxxcx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_LXXXXP)		//������Ϣд��
	{
		pXmlYW = new CLxxxxp(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_FPSC)		//��Ʊ�ϴ�
	{
		pXmlYW = new CFpsssc(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_FPGX)		//��Ʊ����
	{
		pXmlYW = new CFpgx(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_FPDR)		//��Ʊ����
	{
		pXmlYW = new CFpdr(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_FJTH)		//�ֻ��˻�
	{
		pXmlYW = new CYWXMLFjth(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_BGZSKL)		//���֤�����
	{
		pXmlYW = new CBgzskl(&xmlOutput, &xmlInput);
	}
	
	else if(strID == BUSINESS_YWID_FPBL)		//��Ʊ��¼
	{
		pXmlYW = new CFpbl(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_ERRUPINV)		//��Ʊ��¼
	{
		pXmlYW = new CErrUpInv(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_YWID_HQLXSJ)		//��Ʊ��¼
	{
		pXmlYW = new CHqlxsj(&xmlOutput, &xmlInput);
	}

	
	ret = pXmlYW->Execute();
	if(pXmlYW != NULL)
		delete pXmlYW;

	sOutputInfo = "";
	ret = CYWXmlBase::OverYWXml(&xmlInput, &xmlOutput, sOutputInfo);

	DBG_PRINT(("================= End OperateDisk() ================="));
#endif
*/
	return;
}

void OperateNet(char* pin,string ip,string port,string serverpath,char* service_id,string nsrsbh, 
				string sInputInfo, string &sOutputInfo,string& Err)
{
#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
	g_gNetArg->SetZskl(pin);
	g_gNetArg->SetNsrsbh(nsrsbh);
	g_gNetArg->SetServId(service_id);
	g_gNetArg->SetServPara(ip, port, serverpath);
#endif

	DBG_PRINT(("================= Begin OperateNet() ================="));
	XMLParse xmlInput;
	XMLConstruct xmlOutput;
	string strID;
	Return_Info retInfo;
	INT32 ret = 0;
	INT8 tmpBuf[32];

	ret = CYWXmlBase::StartYWXml(sInputInfo, &xmlInput, &xmlOutput, strID);
	if(ret != JSK_SUCCESS)
	{
		retInfo.m_retCode = JSK_COMMON_ERR_CODE;
		retInfo.m_retMsg = "�����������ݴ���";
		sOutputInfo = "";
		CYWXmlBase::ErrYWXml(&xmlInput, &xmlOutput, &retInfo, sOutputInfo);
		return;
	}
	DBG_PRINT(("strID ============= %s", strID.c_str()));

	CYWXmlBase *pXmlYW = NULL;

	//��3�� ˰���տ����ͳһ����ƽ̨�ӿ�
	if(strID == BUSINESS_NETID_FPSSSC)		//��Ʊʵʱ�ϴ�
	{
		pXmlYW = new CFpsc(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_NETID_FPSCJGHQ)	//��Ʊ�ϴ������ȡ
	{
		pXmlYW = new CFpscjghq(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_NETID_WLCB)		//���糭��
	{
		pXmlYW = new CWlcb(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_NETID_QLJS)		//�������
	{
		pXmlYW = new CQljs(&xmlOutput, &xmlInput);
	}
	else if(strID == BUSINESS_NETID_QLJSJGQR)	//����������ȷ��
	{
		pXmlYW = new CQljsjgqr(&xmlOutput, &xmlInput);
	}
#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
// 	else if(strID == BUSINESS_NETID_LXXXSC)		//������Ϣ�ϴ�
// 	{
// 		pXmlYW = new CLxxxsc(&xmlOutput, &xmlInput);
// 	}
// 	else if(strID == BUSINESS_NETID_WLLQFP)		//������ȡ��Ʊ
// 	{
// 		pXmlYW = new CWllqfp(&xmlOutput, &xmlInput);
// 	}
// 	else if(strID == BUSINESS_NETID_WLLQFPJGQR)	//������ȡ��Ʊ���ȷ��
// 	{
// 		pXmlYW = new CWllqfpjgqr(&xmlOutput, &xmlInput);
// 	}
// 	else if(strID == BUSINESS_NETID_QYCSXZKJ)	//��ҵ��������
// 	{
// 		;
// 	}
#endif
	
	sOutputInfo = "";
	ret = pXmlYW->Execute();
	if(ret != SUCCESS)
	{
		if(pXmlYW->m_sslStrErr.length() > MAX_ERR_MSG_LEN)
			pXmlYW->m_sslStrErr.erase(MAX_ERR_MSG_LEN, pXmlYW->m_sslStrErr.length()-MAX_ERR_MSG_LEN);

		INT8 tmpErrBuf[256];
		memset(tmpErrBuf, 0, sizeof(tmpErrBuf));
		sprintf(tmpErrBuf, "%d:%s", ret, pXmlYW->m_sslStrErr.c_str());
		Err = tmpErrBuf;
//		Err = pXmlYW->m_sslStrErr;
		DBG_PRINT(("Err = %s", Err.c_str()));
		ret = CYWXmlBase::OverYWXml(&xmlInput, &xmlOutput);
	}
	else
	{
		ret = CYWXmlBase::OverYWXml(&xmlInput, &xmlOutput, sOutputInfo);
	}
	if(pXmlYW != NULL)
		delete pXmlYW;


	DBG_PRINT(("================= End OperateNet() ================="));
	return;
}



