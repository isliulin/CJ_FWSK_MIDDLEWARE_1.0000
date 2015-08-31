 /*! \file    YWXML_BSPFPSH.cpp
   \brief    款机调用的中间件接口 业务2.16发票收回
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "YWXML_BSPFPSH.h"
#include "JSKInvManageProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CBspfpsh::CBspfpsh(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CBspfpsh::~CBspfpsh()
{

}

INT32 CBspfpsh::XmlParse(XMLParse *parse, CInvVol *invvol, UINT8 &jzlx)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh= parse->GetText();		//税控收款机别号
	DBG_PRINT(("YWXML_BSPFPSH: jqbh = %s", m_ywxml_gy.m_jqbh.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "nsrsbh");
	m_ywxml_gy.m_nsrsbh= parse->GetText();		//纳税人识别号
	DBG_PRINT(("YWXML_BSPFPSH: nsrsbh = %s", m_ywxml_gy.m_nsrsbh.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "jzlx");
	jzlx = atoi(parse->GetText().c_str());		//介质类型
	DBG_PRINT(("YWXML_BSPFPSH: jzlx = %u", jzlx));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "bspbh");
	m_ywxml_gy.m_bspbh = parse->GetText();		//报税盘编号
	DBG_PRINT(("YWXML_BSPFPSH: bspbh = %s", m_ywxml_gy.m_bspbh.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "bspkl");
	m_ywxml_gy.m_bspkl = parse->GetText();		//报税盘口令
	DBG_PRINT(("YWXML_BSPFPSH: bspkl = %s", m_ywxml_gy.m_bspkl.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "sksbbh");
	m_ywxml_gy.m_sksbbh= parse->GetText();		//税控设备编号
	DBG_PRINT(("YWXML_BSPFPSH: sksbbh = %s", m_ywxml_gy.m_sksbbh.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "sksbkl");
	m_ywxml_gy.m_sksbkl= parse->GetText();		//税控设备口令
	DBG_PRINT(("YWXML_BSPFPSH: sksbkl = %s", m_ywxml_gy.m_sksbkl.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();		//发票类型代码
	invvol->m_fplxdm = m_ywxml_gy.m_fplxdm;
	DBG_PRINT(("YWXML_BSPFPSH: fplxdm = %s", m_ywxml_gy.m_fplxdm.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "fpdm");
	invvol->m_code = parse->GetText();		//发票代码
	DBG_PRINT(("YWXML_BSPFPSH: fpdm = %s", invvol->m_code.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "qshm");
	invvol->m_isno = atoi(parse->GetText().c_str());		//发票起始号码
	DBG_PRINT(("YWXML_BSPFPSH: qshm = %u", invvol->m_isno));
	
	parse->LocateNodeByName(parse->m_parentElement[2], "fpfs");
	invvol->m_fpzfs = atoi(parse->GetText().c_str());		//要退回的发票份数
	DBG_PRINT(("YWXML_BSPFPSH: fpfs = %u", invvol->m_fpzfs));

	return SUCCESS;
}

INT32 CBspfpsh::XmlBuild(XMLConstruct *construct, Return_Info *retInfo)
{
	
	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	
	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);	//返回代码
	DBG_PRINT(("YWXML_BSPFPSH: returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);		//返回信息
	DBG_PRINT(("YWXML_BSPFPSH: returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
}


INT32 CBspfpsh::Execute()
{
	CInvVol invVol;	//发票领用信息表
	UINT8 jzlx=2;		//介质类型
	Return_Info retInfo;//返回信息
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	
	XmlParse(m_pXmlParse, &invVol, jzlx);	//调用XML解析函数
	CheckYWXmlPara(retInfo.m_retMsg);
	
	retcode = CJSKInvManageProc::BSPFPSH_Proc(jzlx, &invVol, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}
	
	XmlBuild(m_pXmlConstruct, &retInfo);	//调用XML组装函数
	
	return SUCCESS;
}



