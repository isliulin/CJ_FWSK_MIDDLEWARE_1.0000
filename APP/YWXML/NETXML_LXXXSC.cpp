 /*! \file    NETXML_LXXXSC.cpp
   \brief    款机调用的中间件接口 业务3.5 离线信息上传
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "NETXML_LXXXSC.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"
#include "StructOrganize.h"
#include "ServXml_NsrPara.h"
#include "JSKInfoDef.h"

//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CLxxxsc::CLxxxsc(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CLxxxsc::~CLxxxsc()
{

}

INT32 CLxxxsc::XmlParse(XMLParse *parse, CInvKind *invkind, string &strScjzrq, string &strLxkpsc, string &strQtxx)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	m_ywxml_gy.m_sksbbh = parse->GetAttr("skph");		//盘号(这里赋值给税控设备编号)
	DBG_PRINT(("NETXML_LXXXSC: skph = %s", m_ywxml_gy.m_sksbbh.c_str()));	
	m_ywxml_gy.m_nsrsbh = parse->GetAttr("nsrsbh");		//纳税人识别号
	DBG_PRINT(("NETXML_LXXXSC: nsrsbh = %s", m_ywxml_gy.m_nsrsbh.c_str()));	
	
	m_ywxml_gy.m_kpjh = parse->GetAttr("kpjh");
	DBG_PRINT(("m_ywxml_gy.m_kpjh == %s", m_ywxml_gy.m_kpjh.c_str()));
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[2], "scjzrq");
	strScjzrq = parse->GetText();		//上传截止日期
	DBG_PRINT(("NETXML_LXXXSC: scjzrq = %s", strScjzrq.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "lxkpsc");
	strLxkpsc = parse->GetText();		//离线开票时长
	DBG_PRINT(("NETXML_LXXXSC: lxkpsc = %s", strLxkpsc.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "lxzsljje");
	invkind->m_maxSum = double2int(atof(parse->GetText().c_str()) * SUM_EXTENSION); //离线正数累计金额
	if (invkind->m_maxSum < 0)
	{
		invkind->m_maxSum = -invkind->m_maxSum;
	}
	DBG_PRINT(("NETXML_LXXXSC: lxzsljje = %d", invkind->m_maxSum));

	parse->LocateNodeByName(parse->m_parentElement[2], "qtxx");
	strQtxx = parse->GetText();		//其他信息
	DBG_PRINT(("NETXML_LXXXSC: qtxx = %s", strQtxx.c_str()));

	return SUCCESS;
}

INT32 CLxxxsc::XmlBuild(XMLConstruct *construct, Return_Info *retInfo, string strLzkzxx)
{
	INT8 buf[256];
	memset(buf,0,sizeof(buf));
	INT32 temp_count = 1;//离线信息条数，应由外界传入，暂时定义为局部变量,待赋值

	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;
	sprintf(buf, "%d", temp_count);
	construct->AddAttr("count", buf);
	construct->AddAttr("skph", m_ywxml_gy.m_sksbbh);//盘号,仍以税控设备编号代替
	construct->AddAttr("nsrsbh", m_ywxml_gy.m_nsrsbh);//纳税人识别号

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);	//返回代码
	DBG_PRINT(("NETXML_LXXXSC: returncode : %s", retInfo->m_retCode.c_str()));

	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);		//返回信息
	DBG_PRINT(("NETXML_LXXXSC: returnmsg : %s", retInfo->m_retMsg.c_str()));

	for (INT32 temp_i=1; temp_i<=temp_count; temp_i++)
	{
		construct->AddNode(construct->m_parentElement[2], "group");
		construct->m_parentElement[3] = construct->m_NewElement;
		memset(buf,0,sizeof(buf));
		sprintf(buf, "%d", temp_i);
		construct->AddAttr("xh", buf);

		construct->AddNode(construct->m_parentElement[3], "fplxdm");
		construct->AddText(m_ywxml_gy.m_fplxdm);		//发票类型代码,待赋值
		DBG_PRINT(("NETXML_LXXXSC: fplxdm : %s", m_ywxml_gy.m_fplxdm.c_str()));

		construct->AddNode(construct->m_parentElement[3], "lxkzxx");
		construct->AddText(strLzkzxx);		//离线控制信息
		DBG_PRINT(("NETXML_LXXXSC: lxkzxx : %s", strLzkzxx.c_str()));
	}
	
	return SUCCESS;
}


INT32 CLxxxsc::Execute()
{
	//XML解析输出的数据
	CInvKind invkind;		//纳税人票种表
	string scjzrq("");		//上传截止日期
	string lxkpsc("");		//离线开票时长
	string qtxx("");		//其他信息
	XmlParse(m_pXmlParse, &invkind, scjzrq, lxkpsc, qtxx);	//调用XML解析函数,m_pXmlParse(基类成员)已被初始化为xmlInput
	//const char *temp_qtxx =  qtxx.c_str();//将3.5解析出的"其他信息"转换为企业参数下载中的"授权信息"

	CStructOrganize structorgnize;
	CNsrPara nsrpara(&structorgnize);
	CNsrParaOutInfo CNsrParaOutInfo;
	string strErr("");
	INT32 retcode = 0;
	retcode = nsrpara.CommunicationProc((void*)qtxx.c_str(), (void*)(&CNsrParaOutInfo), strErr);

	//XML组装需要的数据
	Return_Info retInfo;	//返回信息
	string lzkzxx = CNsrParaOutInfo.m_sqxx;		//将企业参数下载中的"授权信息"赋值给3.5中的"离线控制信息"
	if(retcode != SUCCESS)
	{
// 		retInfo.m_retCode = JSK_COMMON_ERR_CODE;
// 		retInfo.m_retMsg = strErr;
		m_sslStrErr = strErr;
		return retcode;
	}
	else
	{
		nsrpara.GetServRetInfo(retInfo.m_retCode, retInfo.m_retMsg);
	}
	XmlBuild(m_pXmlConstruct, &retInfo, lzkzxx);	//调用XML组装函数,m_pXmlConstruct(基类成员)已被初始化为xmlOutput

	return SUCCESS;
}

