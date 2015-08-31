 /*! \file    YWXML_BSPFPCX.cpp
   \brief    款机调用的中间件接口 业务2.14发票查询
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "YWXML_BSPFPCX.h"
#include "JSKInvManageProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CBspfpcx::CBspfpcx(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CBspfpcx::~CBspfpcx()
{

}

INT32 CBspfpcx::XmlParse(XMLParse *parse)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh= parse->GetText();		//税控收款机编号
	DBG_PRINT(("YWXML_BSPFPCX: jqbh = %s", m_ywxml_gy.m_jqbh.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "nsrsbh");
	m_ywxml_gy.m_nsrsbh= parse->GetText();		//纳税人识别号
	DBG_PRINT(("YWXML_BSPFPCX: nsrsbh = %s", m_ywxml_gy.m_nsrsbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "bspbh");
	m_ywxml_gy.m_sksbbh = parse->GetText();		//税控设备编号
	DBG_PRINT(("YWXML_BSPFPCX: sksbbh = %s", m_ywxml_gy.m_sksbbh.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "bspkl");
	m_ywxml_gy.m_sksbkl = parse->GetText();		//税控设备口令
	DBG_PRINT(("YWXML_BSPFPCX: sksbkl = %s", m_ywxml_gy.m_sksbkl.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();		//发票类型代码
	DBG_PRINT(("YWXML_BSPFPCX: fplxdm = %s", m_ywxml_gy.m_fplxdm.c_str()));

	return SUCCESS;
}

INT32 CBspfpcx::XmlBuild(XMLConstruct *construct, UINT32 invNum, CInvVol *invvol, string strLgry, Return_Info *retInfo)
{
	INT8 buf[256];
	memset(buf, 0, sizeof(buf));

	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[2], "fplxdm");
	construct->AddText(m_ywxml_gy.m_fplxdm);	//发票类型代码
	DBG_PRINT(("YWXML_BSPFPCX: fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));

	construct->AddNode(construct->m_parentElement[2], "fpdxx");
	construct->m_parentElement[3] = construct->m_NewElement;
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%u", invNum);
	construct->AddAttr("count", buf);

	for (INT32 temp_i = 0; temp_i < invNum; temp_i++)
	{
		construct->AddNode(construct->m_parentElement[3], "group");
		construct->m_parentElement[4] = construct->m_NewElement;
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "%d", temp_i);
		construct->AddAttr("xh", buf);

		construct->AddNode(construct->m_parentElement[4], "fpdm");
		construct->AddText(invvol[temp_i].m_code);	//发票代码
		DBG_PRINT(("YWXML_BSPFPCX: invvol[%d].code : %s",temp_i ,invvol[temp_i].m_code.c_str()));

		construct->AddNode(construct->m_parentElement[4], "qshm");
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "%08u", invvol[temp_i].m_isno);
		construct->AddText(buf);	//发票起始号码
		DBG_PRINT(("YWXML_BSPFPCX: invvol[%d].qshm : %s",temp_i , buf));

		construct->AddNode(construct->m_parentElement[4], "zzhm");
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "%08u", invvol[temp_i].m_ieno);
		construct->AddText(buf);	//发票终止号码
		DBG_PRINT(("YWXML_BSPFPCX: invvol[%d].zzhm : %s",temp_i , buf));

		construct->AddNode(construct->m_parentElement[4], "fpfs");
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "%u", invvol[temp_i].m_fpzfs);
		construct->AddText(buf);	//发票份数
		DBG_PRINT(("YWXML_BSPFPCX: invvol[%d].fpfs : %s",temp_i , buf));

		construct->AddNode(construct->m_parentElement[4], "syfs");
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "%u", invvol[temp_i].m_remain);
		construct->AddText(buf);	//剩余份数
		DBG_PRINT(("YWXML_BSPFPCX: invvol[%d].syfs : %s",temp_i , buf));

		construct->AddNode(construct->m_parentElement[4], "lgrq");
		construct->AddText(invvol[temp_i].m_buyDate.substr(0,8));	//领购日期
		DBG_PRINT(("YWXML_BSPFPCX: invvol[%d].lgrq : %s",temp_i , invvol[temp_i].m_buyDate.substr(0,8).c_str()));

		construct->AddNode(construct->m_parentElement[4], "lgry");
		construct->AddText(strLgry);	//领购人员
		DBG_PRINT(("YWXML_BSPFPCX: invvol[%d].lgry : %s",temp_i , strLgry.c_str()));
	}

	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);	//返回代码
	DBG_PRINT(("YWXML_BSPFPCX: returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);		//返回信息
	DBG_PRINT(("YWXML_BSPFPCX: returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
}


INT32 CBspfpcx::Execute()
{
	CInvVol invVol[MAX_INV_VOL_NUM];	//发票领用信息表
	string lgry("");	//领购人员
	Return_Info retInfo;//返回信息
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	UINT32 invNum = BSPFPCX_INVNUM;

	XmlParse(m_pXmlParse);	//调用XML解析函数
	CheckYWXmlPara(retInfo.m_retMsg);

	retcode = CJSKInvManageProc::BSPFPCX_Proc(m_ywxml_gy.m_fplxdm, invNum, invVol, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
		invNum = 0;
	}
	
	XmlBuild(m_pXmlConstruct, invNum, invVol, lgry, &retInfo);	//调用XML组装函数

	return SUCCESS;
}


