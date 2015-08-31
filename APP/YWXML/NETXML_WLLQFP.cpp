 /*! \file    NETXML_WLLQFP.cpp
   \brief    款机调用的中间件接口 业务3.6 网络领取发票
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "NETXML_WLLQFP.h"

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
CWllqfp::CWllqfp(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CWllqfp::~CWllqfp()
{

}

INT32 CWllqfp::XmlParse(XMLParse *parse, CInvVol *invvol, string &strQtxx)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;

	m_ywxml_gy.m_sksbbh = parse->GetAttr("skph");		//盘号(这里赋值给税控设备编号)
	DBG_PRINT(("NETXML_WLLQFP: skph = %s", m_ywxml_gy.m_sksbbh.c_str()));	
	m_ywxml_gy.m_nsrsbh = parse->GetAttr("nsrsbh");		//纳税人识别号
	DBG_PRINT(("NETXML_WLLQFP: nsrsbh = %s", m_ywxml_gy.m_nsrsbh.c_str()));	
	
	m_ywxml_gy.m_kpjh = parse->GetAttr("kpjh");
	DBG_PRINT(("m_ywxml_gy.m_kpjh == %s", m_ywxml_gy.m_kpjh.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;

	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();		//发票类型代码
	invvol->m_fplxdm = m_ywxml_gy.m_fplxdm;
	DBG_PRINT(("NETXML_WLLQFP: fplxdm = %s", m_ywxml_gy.m_fplxdm.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fpdm");
	invvol->m_code = parse->GetText();		//发票代码
	DBG_PRINT(("NETXML_WLLQFP: fpdm = %s", invvol->m_code.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fpqshm");
	invvol->m_isno = atoi(parse->GetText().c_str());		//发票起始号码
	DBG_PRINT(("NETXML_WLLQFP: fpqshm = %u", invvol->m_isno));

	parse->LocateNodeByName(parse->m_parentElement[2], "fpzzhm");
	invvol->m_ieno = atoi(parse->GetText().c_str());		//发票终止号码
	DBG_PRINT(("NETXML_WLLQFP: fpzzhm = %u", invvol->m_ieno));

	parse->LocateNodeByName(parse->m_parentElement[2], "zfs");
	invvol->m_fpzfs = atoi(parse->GetText().c_str());		//发票总份数
	DBG_PRINT(("NETXML_WLLQFP: fpzfs = %u", invvol->m_fpzfs));

	parse->LocateNodeByName(parse->m_parentElement[2], "qtxx");
	strQtxx = parse->GetText();		//其他信息
	DBG_PRINT(("NETXML_WLLQFP: qtxx = %s", strQtxx.c_str()));

	return SUCCESS;
}

INT32 CWllqfp::XmlBuild(XMLConstruct *construct, Return_Info *retInfo, CInvVol *invvol)
{
	INT8 buf[256];
	memset(buf,0,sizeof(buf));
	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[2], "fplxdm");
	construct->AddText(m_ywxml_gy.m_fplxdm);	//发票类型代码
	DBG_PRINT(("NETXML_WLLQFP: fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));

	construct->AddNode(construct->m_parentElement[2], "fpdm");
	construct->AddText(invvol->m_code);	//发票代码
	DBG_PRINT(("NETXML_WLLQFP: fpdm : %s", invvol->m_code.c_str()));

	construct->AddNode(construct->m_parentElement[2], "qshm");
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%08u", invvol->m_isno);
	construct->AddText(buf);	//发票起始号码
	DBG_PRINT(("NETXML_WLLQFP: qshm : %s", buf));

	construct->AddNode(construct->m_parentElement[2], "zzhm");
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%08u", invvol->m_ieno);
	construct->AddText(buf);	//发票终止号码
	DBG_PRINT(("NETXML_WLLQFP: zzhm : %s", buf));

	construct->AddNode(construct->m_parentElement[2], "fpfs");
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%u",  invvol->m_fpzfs);
	construct->AddText(buf);	//发票份数
	DBG_PRINT(("NETXML_WLLQFP: fpfs : %s", buf));

	construct->AddNode(construct->m_parentElement[2], "lgrq");
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%u", invvol->m_date);
	construct->AddText(buf);	//领购日期(暂时以购买日期代替),待赋值
	DBG_PRINT(("NETXML_WLLQFP: lgrq : %s", buf));

	construct->AddNode(construct->m_parentElement[2], "gpxxmw");
	construct->AddText(invvol->m_fpjmw);	//购票信息密文对应发票卷下载解析出的发票密文信息
	DBG_PRINT(("NETXML_WLLQFP: gpxxmw : %s", invvol->m_fpjmw.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);	//返回代码
	DBG_PRINT(("NETXML_WLLQFP: returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);		//返回信息
	DBG_PRINT(("NETXML_WLLQFP: returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
}


INT32 CWllqfp::Execute()
{
	//XML解析输出的数据
	CInvVol invvol;		//发票领用信息表
	string qtxx("");		//购票信息密文
	XmlParse(m_pXmlParse, &invvol, qtxx);	//调用XML解析函数
	invvol.m_FlagJSorXZ = 0; //对应九:发票卷下载业务
	invvol.m_gpsq = qtxx; //发票卷下载业务中的"购票授权"来自3.6解析出的"其他信息"

	CStructOrganize structorgnize;
	CServFpjxzjs servfpjxz(&structorgnize);//对应九:发票卷下载业务
	string strErr("");
	INT32 retcode = 0;
	retcode = servfpjxz.CommunicationProc((void*)(&invvol), (void*)(&invvol), strErr);
	
	//XML组装需要的数据	
	Return_Info retInfo;	//返回信息
	if(retcode != SUCCESS)
	{
// 		retInfo.m_retCode = JSK_COMMON_ERR_CODE;
// 		retInfo.m_retMsg = strErr;
		m_sslStrErr = strErr;
		return retcode;
	}
	else
	{
		servfpjxz.GetServRetInfo(retInfo.m_retCode, retInfo.m_retMsg);
	}

	XmlBuild(m_pXmlConstruct, &retInfo, &invvol);	//调用XML组装函数

	return SUCCESS;
}


