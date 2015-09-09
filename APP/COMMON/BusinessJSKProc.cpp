
#include "BusinessJSKProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

#if BUSINESS_TYPE_MODE == BUSINESS_JSK_MODE

#include "JSKManageProc.h"
#include "JSKInvManageProc.h"
#include "JSKMakeInvoice.h"
#include "JSKDeclareProc.h"
#include "GlobalNetArg.h"
#include "CGlobalArgLib.h"

#include "StructOrganize.h"
#include "InvUploadOrganize.h"
#include "YccbOrganize.h"
#include "GetResultOrganize.h"
#include "ServXml_InvUpload.h"
#include "ServXml_InvUploadResult.h"
#include "ServXml_Fpjxzjs.h"
#include "ServXml_NsrPara.h"
#include "ServXml_Qkxxxz.h"
#include "ServXml_Yccb.h"
#include "ServWlcb.h"

#include "SKJNETXML_FPSC.h"
#include "SKJNETXML_FPSCJGHQ.h"
#include "SKJNETXML_WLCB.h"
#include "SKJNETXML_QLJS.h"
#include "SKJNETXML_QLJSJGQR.h"

CBusinessJSKProc::CBusinessJSKProc()
{

}

CBusinessJSKProc::~CBusinessJSKProc()
{

}

//˰���豸��Ų�ѯ
INT32 CBusinessJSKProc::SKSBBH_Business(CYWXML_GY &ywxml_gy, string &sksbbh, string &bspbh, string &qtxx, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKManageProc::SKSBBH_Proc(sksbbh, strErr);
	string tmpStr("");
	CJSKManageProc::BSPBH_Proc(bspbh, tmpStr);

	return ret;
}

//��˰�̱�Ų�ѯ
// INT32 CBusinessJSKProc::BSPBH_Business(CYWXML_GY &ywxml_gy, string &bspbh, string &strErr)
// {
// 	INT32 ret = JSK_SUCCESS;
// 	ret = CJSKManageProc::BSPBH_Proc(bspbh, strErr);
// 	
// 	return ret;
// }

INT32 CBusinessJSKProc::SKPXXCX_Business(CYWXML_GY &ywxml_gy, CDataUserInfo *pUserInfo, string &strCurTime, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKManageProc::SKPXXCX_Proc(pUserInfo, strCurTime, strErr);
	
	return ret;
}

//˰���豸������Ϣ��ѯ
INT32 CBusinessJSKProc::SKSBQTYXXCX_Business(CYWXML_GY &ywxml_gy, UINT8 xxlx, string &sksbxx, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKManageProc::SKSBQTYXXCX_Proc(ywxml_gy.m_fplxdm, xxlx, sksbxx, strErr);
	
	return ret;
}

//��˰����Ϣ��ѯ
INT32 CBusinessJSKProc::BSPXXCX_Business(CYWXML_GY &ywxml_gy, CDataUserInfo *pUserInfo, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKManageProc::BSPXXCX_Proc(pUserInfo, strErr);
	
	return ret;
}

//������ݲ�ѯ
INT32 CBusinessJSKProc::JKSJCX_Business(CYWXML_GY &ywxml_gy, CDataInvKind *pInvKind, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKManageProc::JKSJCX_Proc(pInvKind, strErr);
	
	return ret;
}

//��Ȩ˰�ʲ�ѯ
INT32 CBusinessJSKProc::SQSLCX_Business(CYWXML_GY &ywxml_gy, CDataTax *pTax, UINT8 &taxNum, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKManageProc::SQSLCX_Proc(pTax, taxNum, strErr);
	
	return ret;
}

//��Ʊ��Ϣ��ѯ
INT32 CBusinessJSKProc::GPXXCX_Business(CYWXML_GY &ywxml_gy, CDataInvVol *pInvVol, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKMakeInvoice::GPXXCX_Proc(pInvVol, strErr);
	
	return ret;
}

//��Ʊ��Ϣд��
INT32 CBusinessJSKProc::GPXXXP_Business(CYWXML_GY &ywxml_gy, string gpxxmw, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKInvManageProc::GPXXXP_Proc(ywxml_gy.m_fplxdm, gpxxmw, strErr);
	
	return ret;
}

//��Ʊ��Ϣд�̽���
INT32 CBusinessJSKProc::GPXXXPJS_Business(CYWXML_GY &ywxml_gy, string wslpjsxx, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKInvManageProc::GPXXXPJS_Proc(ywxml_gy.m_fplxdm, wslpjsxx, strErr);
	
	return ret;
}

//������
INT32 CBusinessJSKProc::KLBG_Business(CYWXML_GY &ywxml_gy, string oldPwd, string newPwd, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKManageProc::KLBG_Proc(oldPwd, newPwd, strErr);
	
	return ret;
}

//��Ʊ����
INT32 CBusinessJSKProc::FPKJ_Business(CYWXML_GY &ywxml_gy, CDataInvHead *pInvhead, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKMakeInvoice::FPKJ_Proc(pInvhead, strErr);
	
	return ret;
}

//��Ʊ����
INT32 CBusinessJSKProc::FPZF_Business(CYWXML_GY &ywxml_gy, CDataInvHead *pInvhead, UINT8 zflx, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKMakeInvoice::FPZF_Proc(pInvhead, zflx, strErr);
	
	return ret;
}

//��Ʊ��ѯ
INT32 CBusinessJSKProc::FPCX_Business(CYWXML_GY &ywxml_gy, UINT8 cxfs, string cxtj, UINT32 &invNum, CDataInvHead *pInvhead, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKMakeInvoice::FPCX_Proc(cxfs, cxtj, invNum, pInvhead, strErr);
	
	return ret;
}

//˰���豸��˰����ϲ���
INT32 CBusinessJSKProc::SKPBSP_Business(CYWXML_GY &ywxml_gy, UINT8 czlx, string qtxx,string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKDeclareProc::SKPBSP_Proc(ywxml_gy.m_fplxdm, czlx,qtxx, strErr);
	
	return ret;
}

//��Ʊ����Ϣ��ѯ(��˰�̷�Ʊ��ѯ)
INT32 CBusinessJSKProc::BSPFPCX_Business(CYWXML_GY &ywxml_gy, UINT32 &invNum, CDataInvVol *pInvVol, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKInvManageProc::BSPFPCX_Proc(ywxml_gy.m_fplxdm, invNum, pInvVol, strErr);
	
	return ret;
}

//��Ʊ�ַ�
INT32 CBusinessJSKProc::BSPFPFF_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, CDataInvVol *pInvVol, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKInvManageProc::BSPFPFF_Proc(jzlx, pInvVol, strErr);
	
	return ret;
}

//��Ʊ�ջ�
INT32 CBusinessJSKProc::BSPFPSH_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, CDataInvVol *pInvVol, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKInvManageProc::BSPFPSH_Proc(jzlx, pInvVol, strErr);
	
	return ret;
}

//���ݳ���
INT32 CBusinessJSKProc::SJCB_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strSQ, string &strFphz, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKDeclareProc::SJCB_Proc(ywxml_gy.m_fplxdm, jzlx, strSQ, strFphz, strErr);
	
	return ret;
}

//��ػش�
INT32 CBusinessJSKProc::JKHC_Business(CYWXML_GY &ywxml_gy, string strFpjkmw, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKDeclareProc::JKHC_Proc(ywxml_gy.m_fplxdm, strFpjkmw, strErr);
	
	return ret;
}

//��Ʊͳ����Ϣ��ѯ
INT32 CBusinessJSKProc::TJXXCX_Business(CYWXML_GY &ywxml_gy, INT32 &monthcount, CDataTjxxhz *pTjxxhz, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKInvManageProc::TJXXCX_Proc(ywxml_gy.m_fplxdm, monthcount, pTjxxhz, strErr);
	
	return ret;
}

//������Ϣд��
INT32 CBusinessJSKProc::LXXXXP_Business(CYWXML_GY &ywxml_gy, string lxxxmw, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKManageProc::LXXXXP_Proc(lxxxmw, strErr);
	
	return ret;
}

//��Ʊʵʱ�ϴ�
INT32 CBusinessJSKProc::FPSC_Business(CYWXML_GY &ywxml_gy, UINT8 czlx, UINT32 &fpzx, string &strInvInfo, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKMakeInvoice::FPSC_Proc(czlx, fpzx, strInvInfo, strErr);
	
	return ret;
}

//��Ʊ����
INT32 CBusinessJSKProc::FPGX_Business(CYWXML_GY &ywxml_gy, string scqrbw, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKMakeInvoice::FPGX_Proc(scqrbw, strErr);
	
	return ret;
}

//��Ʊ����
INT32 CBusinessJSKProc::FPDR_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKInvManageProc::FPDR_Proc(jzlx, ywxml_gy.m_fplxdm, strErr);
	
	return ret;
}

//�ֻ��˻�
INT32 CBusinessJSKProc::FJTH_Business(CYWXML_GY &ywxml_gy, UINT8 jzlx, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKInvManageProc::FJTH_Proc(jzlx, ywxml_gy.m_fplxdm, strErr);
	
	return ret;
}

//���֤�����
INT32 CBusinessJSKProc::BGZSKL_Business(CYWXML_GY &ywxml_gy, string oldPwd, string newPwd, string &strErr)
{
	INT32 ret = JSK_SUCCESS;
	
	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	ret = CJSKManageProc::BGZSKL_Proc(oldPwd, newPwd, strErr);
	
	return ret;
}

//3.1��Ʊ�ϴ�
INT32 CBusinessJSKProc::NETFPSC_Business(CYWXML_GY &ywxml_gy, const string &Fpmx, UINT32 Fpzs, string &Slxlh, string &strErr)
{
// 	INT32 ret = JSK_SUCCESS;
// 	CInvHead invHead;	
//  	void *pDateOut = NULL;
// 	string strErrCode("");
// 
// 	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
// 	
// 	CInvUploadOrganize InvUploadOrganize;
// 	CInvUpload InvUpload(&InvUploadOrganize);
// 	
// 	CJSKMakeInvoice::Str2InvHead((INT8 *)Fpmx.c_str(), &invHead);
// 
// 	InvUpload.SetOperFlag();
// 	ret = InvUpload.CommunicationProc((void *)&invHead, pDateOut, strErr);
// 	if(ret != SUCCESS)
// 	{
// 		InvUpload.GetServRetInfo(strErrCode, strErr);
// 		ret = atoi(strErrCode.c_str());
// 	}
// 	
// 	return ret;

	INT32 ret = JSK_SUCCESS;
	ywxml_gy.m_strID = BUSINESS_NETID_FPSC;
	CSKJFpsc SKJFpsc(ywxml_gy, Fpmx, Fpzs, Slxlh);

	ret = SKJFpsc.NETXml_Proc(strErr);
	
	return ret;

}
//3.2��Ʊ�ϴ������ȡ
INT32 CBusinessJSKProc::FPSCJGHQ_Business(CYWXML_GY &ywxml_gy, string qtxx, string &Mxjgmw, string &strErr)
{
// 	INT32 ret = JSK_SUCCESS;
// 	string strErrCode("");
// 	void *pBussness = NULL; 
// 	CInvUpResultOutinfo InvUpResultOutinfo;
// 	
// 	CGetResultOrganize GetResultOrganize;
// 	CInvUpResult InvUpResult(&GetResultOrganize);
// 	
// 	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
// 	
// 	ret = InvUpResult.CommunicationProc(pBussness, (void *)&InvUpResultOutinfo, strErr);
// 	if(ret != SUCCESS)
// 	{
// 		InvUpResult.GetServRetInfo(strErrCode, strErr);
// 		ret = atoi(strErrCode.c_str());
// 	}
// 	
// 	Mxjgmw = InvUpResultOutinfo.m_FpSucc.m_scbzFlag;
// 
// 	return ret;

	INT32 ret = JSK_SUCCESS;
	ywxml_gy.m_strID = BUSINESS_NETID_FPSCJGHQ;
	CSKJFpscjghq Fpscjghq(ywxml_gy, qtxx, Mxjgmw);
	
	ret = Fpscjghq.NETXml_Proc(strErr);
	
	return ret;
}
//3.3���糭��
INT32 CBusinessJSKProc::WLCB_Business(CYWXML_GY &ywxml_gy, string Sq, string Fphzsj, string Qtxx, string &strErr)
{
// 	INT32 ret = JSK_SUCCESS;
// 	string strErrCode("");
// 	CServWlcb servwlcb;
// 	servwlcb.m_hzxx = Fphzsj;//��3.3���糭���е�"��Ʊ��������"��ֵ��Զ�̳����е�"������Ϣ"
// 	servwlcb.m_cssj = Sq.substr(14, 14);
// 	servwlcb.m_ssqrs = Qtxx;
// 	g_gNetArg->m_hxsh = Qtxx;
// 	
// 	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
// 	
// 	CYccbOrganize YccbOrganize;
// 	CServYccb ServYccb(&YccbOrganize);
// 	
// 	ret = ServYccb.CommunicationProc((void *)(&servwlcb), (void *)(&servwlcb), strErr);
// 	if(ret != SUCCESS)
// 	{
// 		ServYccb.GetServRetInfo(strErrCode, strErr);
// 		ret = atoi(strErrCode.c_str());
// 	}
// 
// 	return ret;

	INT32 ret = JSK_SUCCESS;
	ywxml_gy.m_strID = BUSINESS_NETID_WLCB;
	CSKJWlcb Wlcb(ywxml_gy, Sq, Fphzsj, Qtxx);
	
	ret = Wlcb.NETXml_Proc(strErr);
	DBG_PRINT(("ret = %d", ret));
	return ret;

}
//3.4�������
INT32 CBusinessJSKProc::QLJS_Business(CYWXML_GY &ywxml_gy, string Qtxx,string &Fpjkmw, string &strErr)
{
// 	INT32 ret = JSK_SUCCESS;
// 	string strErrCode("");
// 
// 	CServWlcb ServWlcb;
// 	
// 	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
// 	
// 	CGetResultOrganize GetResultOrganize;
// 	CServQkxxxz ServQkxxxz(&GetResultOrganize);
// 	UINT8 FpmxCount = 0; 
// 	
// 	ServWlcb.m_cssj = Qtxx;
// 	
// 	ret = ServQkxxxz.CommunicationProc((void *)&ServWlcb, (void *)&ServWlcb, strErr);
// 	if(ret != SUCCESS)
// 	{
// 		ServQkxxxz.GetServRetInfo(strErrCode, strErr);
// 		ret = atoi(strErrCode.c_str());
// 	}
// 	Fpjkmw = ServWlcb.m_qkxx;
// 
// 	return ret;

	INT32 ret = JSK_SUCCESS;
	
	ywxml_gy.m_strID = BUSINESS_NETID_QLJS;
	CSKJQljs Qljs(ywxml_gy, Qtxx, Fpjkmw);
	
	ret = Qljs.NETXml_Proc(strErr);
	
	return ret;
}
//3.5����������ȷ��
INT32 CBusinessJSKProc::QLJSJGQR_Business(CYWXML_GY &ywxml_gy, string Qtxx, string &strErr)
{
	INT32 ret = JSK_SUCCESS;
	
	ywxml_gy.m_strID = BUSINESS_NETID_QLJSJGQR;
	CSKJQljsjgqr Qljsjgqr(ywxml_gy, Qtxx);
	
	ret = Qljsjgqr.NETXml_Proc(strErr);
	
	return ret;
}

//3.6������Ϣ�ϴ�
INT32 CBusinessJSKProc::NETLXXXSC_Business(CYWXML_GY &ywxml_gy, CDataInvKind *invkind, string strQtxx, string &strLzkzxx, string &strErr)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	
	CStructOrganize structorgnize;
	CNsrPara nsrpara(&structorgnize);
	CNsrParaOutInfo CNsrParaOutInfo;
	ret = nsrpara.CommunicationProc((void*)strQtxx.c_str(), (void*)(&CNsrParaOutInfo), strErr);
	if(ret != SUCCESS)
	{
		if(ret == FAILURE)
			ret = JSK_FAILURE;
		return ret;
	}
	strLzkzxx = CNsrParaOutInfo.m_sqxx;		//����ҵ���������е�"��Ȩ��Ϣ"��ֵ��3.5�е�"���߿�����Ϣ"

	return JSK_SUCCESS;
}
//3.7������ȡ��Ʊ
INT32 CBusinessJSKProc::WLLQFP_Business(CYWXML_GY &ywxml_gy, CDataInvVol *pInvvol, string strQtxx, string &strErr)
{
	INT32 ret = JSK_SUCCESS;
	string strErrCode("");

	pInvvol->m_FlagJSorXZ = 0; //��Ӧ��:��Ʊ������ҵ��
	pInvvol->m_gpsq = strQtxx; //��Ʊ������ҵ���е�"��Ʊ��Ȩ"����3.6��������"������Ϣ"
	
	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	
	CStructOrganize structorgnize;
	CServFpjxzjs servfpjxz(&structorgnize);//��Ӧ��:��Ʊ������ҵ��


	 g_gNetArg->SetBaseInfo(ywxml_gy.m_nsrsbh,ywxml_gy.m_kpjh,ywxml_gy.m_sksbbh);
	ret = servfpjxz.CommunicationProc((void*)pInvvol, (void*)pInvvol, strErr);
	if(ret != SUCCESS)
	{
		if(ret == FAILURE)
			ret = JSK_FAILURE;
		return ret;
	}
	
	return JSK_SUCCESS;
}
//3.8������ȡ��Ʊ���ȷ��
INT32 CBusinessJSKProc::WLLQFPJGQR_Business(CYWXML_GY &ywxml_gy, CDataInvVol *pInvvol, string strQtxx, string &strErr)
{
	INT32 ret = JSK_SUCCESS;
	string strErrCode("");
	
	pInvvol->m_FlagJSorXZ = 1; //��Ӧ��:��Ʊ�����ҵ��
	pInvvol->m_flag = strQtxx; //��Ʊ�����ҵ���е�"д��������Ʊ������"����3.7��������"������Ϣ"
	
	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, ywxml_gy.m_bspkl);
	
	CStructOrganize structorgnize;
	CServFpjxzjs servfpjjs(&structorgnize);//��Ӧ��:��Ʊ�����ҵ��
	INT8 tmpbuf[64];
	ret = servfpjjs.CommunicationProc((void*)pInvvol, (void*)pInvvol, strErr);
	if(ret != SUCCESS)
	{
		if(ret == FAILURE)
			ret = JSK_FAILURE;
		return ret;
	}

	return JSK_SUCCESS;
}


//�������ά�� -- ת����
INT32 CBusinessJSKProc::NetPara_Business(CYWXML_GY &ywxml_gy, CDataNetPara *pNetPara, string &strErr)
{
	INT32 ret = JSK_SUCCESS;
	
	ret = CJSKManageProc::NetPara_Proc(pNetPara, strErr);
	
	return ret;
}

INT32 CBusinessJSKProc::FPBL_Business(CYWXML_GY &ywxml_gy, UINT32 SDate, UINT32 EDate, string &strErr)
{
	INT32 ret = JSK_SUCCESS;
	
	ret =  CJSKMakeInvoice::FPBL_Proc(ywxml_gy.m_nsrsbh, ywxml_gy.m_sksbbh, SDate, EDate, strErr);
	
	return ret;
}

INT32 CBusinessJSKProc::OffInvInfo_Business(CYWXML_GY &ywxml_gy, UINT32 &wscfpzs, string &wscfpsj, INT64 &wscfpljje, string &strErr)
{
	INT32 ret = JSK_SUCCESS;
	
	ret = CJSKManageProc::OffInvInfo_Proc(wscfpzs, wscfpsj, wscfpljje, strErr);
	
	return ret;
}

INT32 CBusinessJSKProc::UpdateUploadInv(CYWXML_GY &ywxml_gy)
{
	INT32 ret = JSK_SUCCESS;

	CJSKManageProc::set_JSKPara(ywxml_gy.m_jqbh, ywxml_gy.m_sksbkl, "");
	ret = CJSKDeclareProc::DelUploadInv();
	
	return ret;
}

//��ȫͨ�����Ӳ���
INT32 CBusinessJSKProc::SSLConnectTest(CYWXML_GY &ywxml_gy, string &strErr)
{
	INT32 ret = JSK_SUCCESS;
	
	CStructOrganize structorgnize;
	CNsrPara nsrpara(&structorgnize);
	ret = nsrpara.SSLConnectTest(ywxml_gy.m_nsrsbh, ywxml_gy.m_zskl, strErr);
	if(ret != SUCCESS)
	{
		return ret;
	}
	
	return ret;
}

INT32 CBusinessJSKProc::GetErrUpInvInfo(CYWXML_GY &ywxml_gy, CDataInvServ *pDataInvServ, UINT32 &nCount, string &strErr)
{
	INT32 ret = JSK_SUCCESS;
	
	ret = CJSKMakeInvoice::GetErrUpInv(pDataInvServ, nCount, strErr);
	
	return ret;
}

#endif

