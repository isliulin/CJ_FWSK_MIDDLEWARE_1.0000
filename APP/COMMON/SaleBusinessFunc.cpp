
#include "SaleBusinessFunc.h"
#include "BusinessBase.h"
#include "commonFunc.h"

#if BUSINESS_TYPE_MODE == BUSINESS_JSK_MODE
#include "CGlobalArgLib.h"
#else
//#include "CGlobalArg.h"
#endif

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CSaleBusinessFunc::CSaleBusinessFunc()
{

}

CSaleBusinessFunc::~CSaleBusinessFunc()
{

}


INT32 CSaleBusinessFunc::GetCurInvInfo(CYWXML_GY &ywxml_gy, CDataInvVol *pInvVol, string &strErr)
{
	INT32 ret = SUCCESS;
	ret = g_pBusBase->GPXXCX_Business(ywxml_gy, pInvVol, strErr);

	return g_pBusBase->ErrParse(ret, strErr);
}

INT32 CSaleBusinessFunc::MakeNormalInv(CYWXML_GY &ywxml_gy, CDataInvHead *pInvHead, string &strErr)
{
	INT32 ret = SUCCESS;
	ret = g_pBusBase->FPKJ_Business(ywxml_gy, pInvHead, strErr);

	DBG_PRINT(("fpdm = %s", pInvHead->m_fpdm.c_str()));
	DBG_PRINT(("fphm = %08u", pInvHead->m_fphm));
	DBG_PRINT(("fwm = %s", pInvHead->m_fwm.c_str()));
	DBG_PRINT(("kprq= %u",pInvHead->m_kprq));

	return g_pBusBase->ErrParse(ret, strErr);
}

INT32 CSaleBusinessFunc::MakeWasteInv(CYWXML_GY &ywxml_gy, CDataInvHead *pInvHead, UINT8 zflx, string &strErr)
{
	INT32 ret = SUCCESS;

	pInvHead->m_xfsh = ywxml_gy.m_nsrsbh;
	pInvHead->m_xfmc = ywxml_gy.m_nsrmc;

	ret = g_pBusBase->FPZF_Business(ywxml_gy, pInvHead, zflx, strErr);
	ret = g_pBusBase->ErrParse(ret, strErr);
	
	DBG_PRINT(("fpdm = %s", pInvHead->m_fpdm.c_str()));
	DBG_PRINT(("fphm = %08u", pInvHead->m_fphm));
	DBG_PRINT(("m_kprq = %u", pInvHead->m_kprq));
	DBG_PRINT(("m_kpsj = %u", pInvHead->m_kpsj));
	DBG_PRINT(("fwm = %s", pInvHead->m_fwm.c_str()));
	
	return ret;
}

INT32 CSaleBusinessFunc::GetInvHeadInfo(CYWXML_GY &ywxml_gy, UINT8 cxfs, string cxtj, UINT32 &invNum, CDataInvHead *pInvhead, string &strErr)
{
	INT32 ret = SUCCESS;
	ret = g_pBusBase->FPCX_Business(ywxml_gy, cxfs, cxtj, invNum, pInvhead, strErr);
	
	return g_pBusBase->ErrParse(ret, strErr);
}

INT32 CSaleBusinessFunc::InvoiceUpload(CYWXML_GY &ywxml_gy, string &strErr)
{
	INT32 ret = SUCCESS;
	UINT8 upFlag = 0;
	UINT8 czlx = 0;
	UINT32 fpzx = 1;	//һ��ֻ�ϴ�һ�ŷ�Ʊ
	string strInvInfo("");
	string strMxjgmw("");
	UINT8 nCount = 0;
	UINT32 nTime = 1000;
	UINT32 nTimeCount = 5;
	UINT8 xxlx = SKSBQTYXXCX_XXLX_FPSCJGHQ;
	string strSksbxx("");
	string slxlh("");
	UINT8 errNetFlag=0;

	//�ӽ�˰�̻�ȡ�ϴ���Ʊ��Ϣ
	ret = g_pBusBase->FPSC_Business(ywxml_gy, czlx, fpzx, strInvInfo, strErr);
	DBG_PRINT(("ret = %d", ret));
	ret = g_pBusBase->ErrParse(ret, strErr);
	if(ret != SUCCESS)
	{
		return ret;
	}

	while(1)
	{
		if(nCount >= MAX_ERR_NUM)
		{
			break;
		}
		if(errNetFlag >= MAX_NET_ERR_NUM)
		{
#if BUSINESS_TYPE_MODE == BUSINESS_JSK_MODE
			g_globalArgLib->m_pthreadFlag = 0;
#else
//			g_globalArg->m_pthreadFlag = 0;
#endif
			break;
		}

		if(upFlag == 0)
		{
			//���������ϴ��ӿڣ��ϴ���Ʊ��Ϣ
			ret = g_pBusBase->NETFPSC_Business(ywxml_gy, strInvInfo, fpzx, slxlh, strErr);
			DBG_PRINT(("ret = %d", ret));
			if(ret < -255)
				errNetFlag++;
			ret = g_pBusBase->ErrParse(ret, strErr);
			if(ret != SUCCESS)
			{
				nCount++;
				CommonSleep(nCount*nTime);
				continue;
			}
			CommonSleep(3*nTime);
			errNetFlag = 0;
			upFlag = 1;
			nCount = 0;
		}
		else
		{
			ret = g_pBusBase->SKSBQTYXXCX_Business(ywxml_gy, xxlx, strSksbxx, strErr);
			ret = g_pBusBase->ErrParse(ret, strErr);
			if(ret != SUCCESS)
			{
				return FAILURE;
			}
			//��ȡ�ϴ��������
			ret = g_pBusBase->FPSCJGHQ_Business(ywxml_gy, strSksbxx, strMxjgmw, strErr);
			if(ret < -255)
				errNetFlag++;
			ret = g_pBusBase->ErrParse(ret, strErr);
			if( ret != SUCCESS )
			{
				nCount++;
				CommonSleep(nCount*nTimeCount*nTime);
				continue;
			}
			errNetFlag = 0;

			//���ϴ�������ĸ��µ���˰��
			ret = g_pBusBase->FPGX_Business(ywxml_gy, strMxjgmw, strErr);
			ret = g_pBusBase->ErrParse(ret, strErr);
			break;
		}

		CommonSleep(nTime);
	}

	return ret;
}

INT32 CSaleBusinessFunc::FpblProStart(CYWXML_GY &ywxml_gy, UINT32 SDate, UINT32 EDate, string &strErr)
{
	INT32 ret = SUCCESS;
	
	ret = g_pBusBase->FPBL_Business(ywxml_gy, SDate, EDate, strErr);
	ret = g_pBusBase->ErrParse(ret, strErr);
	
	return ret;
}

INT32 CSaleBusinessFunc::GetErrUpInvInfo(CYWXML_GY &ywxml_gy, CDataInvServ *pDataInvServ, UINT32 &nCount, string &strErr)
{
	INT32 ret = SUCCESS;
	
	ret = g_pBusBase->GetErrUpInvInfo(ywxml_gy, pDataInvServ, nCount, strErr);
	ret = g_pBusBase->ErrParse(ret, strErr);
	
	return ret;
}