
#include "ManageBusinessFunc.h"
#include "ClearDepotFunc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

CManageBusinessFunc::CManageBusinessFunc()
{

}

CManageBusinessFunc::~CManageBusinessFunc()
{

}


INT32 CManageBusinessFunc::GetSksbbh(CYWXML_GY &ywxml_gy, string &sksbbh, string &bspbh, string &qtxx, string &strErr)
{
	INT32 ret = SUCCESS;

	ret = g_pBusBase->SKSBBH_Business(ywxml_gy, sksbbh, bspbh, qtxx, strErr);
	
	ret = g_pBusBase->ErrParse(ret, strErr);
	return ret;
}

INT32 CManageBusinessFunc::GetTaxpayerInfo(CYWXML_GY &ywxml_gy, CDataUserInfo &UserInfo, string &strCurTime, string &strErr)
{
	INT32 ret = SUCCESS;
	ret = g_pBusBase->SKPXXCX_Business(ywxml_gy, &UserInfo, strCurTime, strErr);

	return g_pBusBase->ErrParse(ret, strErr);
}


INT32 CManageBusinessFunc::GetBSPInfo(CYWXML_GY &ywxml_gy, CDataUserInfo &userInfo, string &strErr)
{
	INT32 ret = SUCCESS;
	ret = g_pBusBase->BSPXXCX_Business(ywxml_gy, &userInfo, strErr);
	
	return g_pBusBase->ErrParse(ret, strErr);
}

INT32 CManageBusinessFunc::GetJKSJ(CYWXML_GY &ywxml_gy, CDataInvKind &InvKind, string &strErr)
{
	INT32 ret = SUCCESS;
	ret = g_pBusBase->JKSJCX_Business(ywxml_gy, &InvKind, strErr);
	
	return g_pBusBase->ErrParse(ret, strErr);
}

INT32 CManageBusinessFunc::GetTaxRateInfo(CYWXML_GY &ywxml_gy, CDataTax *pTax, UINT8 &taxNum, string &strErr)
{
	INT32 ret = SUCCESS;
 	ret = g_pBusBase->SQSLCX_Business(ywxml_gy, pTax, taxNum, strErr);
	DBG_PRINT(("ret = %d", ret));
	ret = g_pBusBase->ErrParse(ret, strErr);
	
	return ret;
}

INT32 CManageBusinessFunc::SKPKLBG(CYWXML_GY &ywxml_gy, string ykl, string xkl, string &strErr)
{	
	INT32 ret = SUCCESS;
	ret = g_pBusBase->KLBG_Business(ywxml_gy, ykl, xkl, strErr);

	return g_pBusBase->ErrParse(ret, strErr);
}

INT32 CManageBusinessFunc::LXXXUpdatePro(CYWXML_GY &ywxml_gy, string &strErr)
{
	UINT8 xxlx = SKSBQTYXXCX_XXLX_LXXXSC;
	string sksbxx("");
	string lxkzxx("");
	INT32 ret = SUCCESS;
	CDataInvKind dataInvkind;

	ret = g_pBusBase->SKSBQTYXXCX_Business(ywxml_gy, xxlx, sksbxx, strErr);
	ret = g_pBusBase->ErrParse(ret, strErr);
	if(ret != SUCCESS)
	{
		return FAILURE;
	}

	ret = g_pBusBase->JKSJCX_Business(ywxml_gy, &dataInvkind, strErr);
	ret = g_pBusBase->ErrParse(ret, strErr);
	if(ret != SUCCESS)
	{
		return FAILURE;
	}

	ret = g_pBusBase->NETLXXXSC_Business(ywxml_gy, &dataInvkind, sksbxx, lxkzxx, strErr);
	ret = g_pBusBase->ErrParse(ret, strErr);
	if(ret != SUCCESS)
	{
		return FAILURE;
	}

	DBG_PRINT(("lxkzxx = %s", lxkzxx.c_str()));
	if(lxkzxx != "")
	{
		ret = g_pBusBase->LXXXXP_Business(ywxml_gy, lxkzxx, strErr);
		ret = g_pBusBase->ErrParse(ret, strErr);
	}

	return ret;
}

INT32 CManageBusinessFunc::BGZSKLProc(CYWXML_GY &ywxml_gy, string yzskl, string xzskl, string &strErr)
{	
	INT32 ret = SUCCESS;
	ret = g_pBusBase->BGZSKL_Business(ywxml_gy, yzskl, xzskl, strErr);
	ret = g_pBusBase->ErrParse(ret, strErr);
	
	return ret;
}


#if BUSINESS_TYPE_MODE == BUSINESS_JSK_MODE
INT32 CManageBusinessFunc::NetParaManage(CYWXML_GY &ywxml_gy, CDataNetPara *pNetPara, string &strErr)
{
	INT32 ret = SUCCESS;

	ret = g_pBusBase->NetPara_Business(ywxml_gy, pNetPara, strErr);
	ret = g_pBusBase->ErrParse(ret, strErr);

	return ret;
}
#endif

INT32 CManageBusinessFunc::GetOffLineInvInfo(CYWXML_GY &ywxml_gy, UINT32 &wscfpzs, string &wscfpsj, INT64 &wscfpljje, string &strErr)
{
	INT32 ret = SUCCESS;
	
	ret = g_pBusBase->OffInvInfo_Business(ywxml_gy, wscfpzs, wscfpsj, wscfpljje, strErr);
	ret = g_pBusBase->ErrParse(ret, strErr);
	
	return ret;
}



INT32 CManageBusinessFunc::UpdateUploadInvInfo(CYWXML_GY &ywxml_gy)
{
	INT32 ret = SUCCESS;
	
	g_pBusBase->UpdateUploadInv(ywxml_gy);
	
	return ret;
}

INT32 CManageBusinessFunc::SSLConnectTest(CYWXML_GY &ywxml_gy, string &strErr)
{
	INT32 ret = SUCCESS;
	
	ret = g_pBusBase->SSLConnectTest(ywxml_gy, strErr);
	
	return ret;
}


INT32 CManageBusinessFunc::ClearMidDepot(string &strErr)
{
	INT32 ret = SUCCESS;

	CClearDepotFunc clearfunc;
    ret = clearfunc.ClearDepot(strErr);
	
	return ret;
}


