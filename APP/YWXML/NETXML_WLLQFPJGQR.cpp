/*! \file    NETXML_WLLQFPJGQR.cpp
   \brief    款机调用的中间件接口 业务3.7 网络领取发票结果确认
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "NETXML_WLLQFPJGQR.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"
#include "StructOrganize.h"
#include "ServXml_Fpjxzjs.h"
#include "JSKInfoDef.h"

//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CWllqfpjgqr::CWllqfpjgqr(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CWllqfpjgqr::~CWllqfpjgqr()
{

}

INT32 CWllqfpjgqr::XmlParse(XMLParse *parse, CInvVol *invvol, string &strQtxx)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;

	m_ywxml_gy.m_sksbbh = parse->GetAttr("skph");		//盘号(这里赋值给税控设备编号)
	DBG_PRINT(("NETXML_WLLQFPJGQR: skph = %s", m_ywxml_gy.m_sksbbh.c_str()));	
	m_ywxml_gy.m_nsrsbh = parse->GetAttr("nsrsbh");		//纳税人识别号
	DBG_PRINT(("NETXML_WLLQFPJGQR: nsrsbh = %s", m_ywxml_gy.m_nsrsbh.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();		//发票类型代码
	invvol->m_fplxdm = m_ywxml_gy.m_fplxdm;
	DBG_PRINT(("NETXML_WLLQFPJGQR: fplxdm = %s", m_ywxml_gy.m_fplxdm.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fpdm");
	invvol->m_code = parse->GetText();		//发票代码
	DBG_PRINT(("NETXML_WLLQFPJGQR: fpdm = %s", invvol->m_code.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "qshm");
	invvol->m_isno = atoi(parse->GetText().c_str());		//发票起始号码
	DBG_PRINT(("NETXML_WLLQFPJGQR: qshm = %u", invvol->m_isno));

	parse->LocateNodeByName(parse->m_parentElement[2], "zzhm");
	invvol->m_ieno = atoi(parse->GetText().c_str());		//发票终止号码
	DBG_PRINT(("NETXML_WLLQFPJGQR: zzhm = %u", invvol->m_ieno));

	invvol->m_fpzfs = invvol->m_ieno - invvol->m_isno + 1;

	parse->LocateNodeByName(parse->m_parentElement[2], "qtxx");
	strQtxx = parse->GetText();		//其他信息
	DBG_PRINT(("NETXML_WLLQFPJGQR: qtxx = %s", strQtxx.c_str()));
	
	return SUCCESS;
}

INT32 CWllqfpjgqr::XmlBuild(XMLConstruct *construct, Return_Info *retInfo, CInvVol *invvol)
{
	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[2], "fplxdm");
	construct->AddText(m_ywxml_gy.m_fplxdm);	//发票类型代码,待赋值
	DBG_PRINT(("NETXML_WLLQFPJGQR: fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));

	construct->AddNode(construct->m_parentElement[2], "gpxxjgqr");
	construct->AddText(invvol->m_fpjjsmw);	//购票信息结果确认对应发票卷解锁解析出的发票解锁密文信息
	DBG_PRINT(("NETXML_WLLQFPJGQR: gpxxjgqr : %s", invvol->m_fpjjsmw.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);	//返回代码
	DBG_PRINT(("NETXML_WLLQFPJGQR: returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);		//返回信息
	DBG_PRINT(("NETXML_WLLQFPJGQR: returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
}


INT32 CWllqfpjgqr::Execute()
{
	//XML解析输出的数据
	CInvVol invvol;		//发票领用信息表
	string qtxx("");		//购票信息密文
	XmlParse(m_pXmlParse, &invvol, qtxx);	//调用XML解析函数
	invvol.m_FlagJSorXZ = 1; //对应九:发票卷解锁业务
	invvol.m_flag = qtxx; //发票卷解锁业务中的"写盘锁死发票卷密文"来自3.7解析出的"其他信息"

	CStructOrganize structorgnize;
	CServFpjxzjs servfpjjs(&structorgnize);//对应九:发票卷解锁业务
	string strErr("");
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	retcode = servfpjjs.CommunicationProc((void*)(&invvol), (void*)(&invvol), strErr);

	Return_Info retInfo;	//	返回信息类对象
	if(retcode != SUCCESS)
	{
// 		retInfo.m_retCode = JSK_COMMON_ERR_CODE;
// 		retInfo.m_retMsg = strErr;
		m_sslStrErr = strErr;
		return retcode;
	}
	else
	{
		servfpjjs.GetServRetInfo(retInfo.m_retCode, retInfo.m_retMsg);
	}

	XmlBuild(m_pXmlConstruct, &retInfo, &invvol); //调用XML组装函数

	return SUCCESS;
}





























