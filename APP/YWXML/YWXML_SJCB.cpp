/*! \file    YWXML_SJCB.cpp
   \brief    款机调用的中间件接口 业务2.17数据抄报
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "YWXML_SJCB.h"
#include "JSKDeclareProc.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CSjcb::CSjcb(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CSjcb::~CSjcb()
{

}

INT32 CSjcb::XmlParse(XMLParse *parse, UINT8 &jzlx)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh= parse->GetText();		//税控收款机别号
	DBG_PRINT(("YWXML_SJCB: jqbh = %s", m_ywxml_gy.m_jqbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "nsrsbh");
	m_ywxml_gy.m_nsrsbh= parse->GetText();		//纳税人识别号
	DBG_PRINT(("YWXML_SJCB: nsrsbh = %s", m_ywxml_gy.m_nsrsbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "sksbbh");
	m_ywxml_gy.m_sksbbh= parse->GetText();		//税控设备编号
	DBG_PRINT(("YWXML_SJCB: sksbbh = %s", m_ywxml_gy.m_sksbbh.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "sksbkl");
	m_ywxml_gy.m_sksbkl= parse->GetText();		//税控设备口令
	DBG_PRINT(("YWXML_SJCB: sksbkl = %s", m_ywxml_gy.m_sksbkl.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "fplxdm");
	m_ywxml_gy.m_fplxdm = parse->GetText();		//发票类型代码
	DBG_PRINT(("YWXML_SJCB: fplxdm = %s", m_ywxml_gy.m_fplxdm.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "jzlx");
	jzlx = (UINT8)atoi(parse->GetText().c_str());		//介质类型
	DBG_PRINT(("YWXML_SJCB: jzlx = %u", jzlx));

	return SUCCESS;
}

//INT32 CSjcb::XmlBuild(XMLConstruct *construct, Return_Info *retInfo, INT8 *chSq, INT8 *chFphz, INT8 *chSzfphz, INT8 *chQtxx)
//INT32 CSjcb::XmlBuild(XMLConstruct *construct, INT8 *chSq, INT8 *chFpmx, INT8 *chFpdxx, INT8 *chFphz, INT8 *chQtxx, Return_Info *retInfo)
INT32 CSjcb::XmlBuild(XMLConstruct *construct, string strSQ, string strFpmx, string strFpdxx, string strFphz, string strQtxx, Return_Info *retInfo)
{
	
	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;
	
	construct->AddNode(construct->m_parentElement[2], "sq");
	construct->AddText(strSQ);	//属期
	DBG_PRINT(("YWXML_SJCB: sq : %s", strSQ.c_str()));

	construct->AddNode(construct->m_parentElement[2], "fpmx");
	construct->AddText(strFpmx);	//发票明细数据,待赋值
	DBG_PRINT(("YWXML_SJCB: fpmx : %s", strFpmx.c_str()));

	construct->AddNode(construct->m_parentElement[2], "fpdxx");
	construct->AddText(strFpdxx);	//发票段信息,待赋值
	DBG_PRINT(("YWXML_SJCB: fpdxx : %s", strFpdxx.c_str()));

	construct->AddNode(construct->m_parentElement[2], "fphz");
	construct->AddText(strFphz);	//发票汇总数据
	DBG_PRINT(("YWXML_SJCB: fphz : %s", strFphz.c_str()));

	construct->AddNode(construct->m_parentElement[2], "szfphz");
	construct->AddText("");		//时钟发票汇总数据,待赋值

	construct->AddNode(construct->m_parentElement[2], "qtxx");
	construct->AddText(strQtxx);		//其他信息
	DBG_PRINT(("YWXML_SJCB: qtxx : %s", strQtxx.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);	//返回代码
	DBG_PRINT(("YWXML_SJCB: returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);		//返回信息
	DBG_PRINT(("YWXML_SJCB: returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
}


INT32 CSjcb::Execute()
{
	Return_Info retInfo;	//	返回信息类对象
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	
	string strSQ("");
	string strFpmx("");
	string strFpdxx("");
	string strFphz("");
	string strQtxx("");
	UINT8 jzlx = 0;

	XmlParse(m_pXmlParse, jzlx);
	CheckYWXmlPara(retInfo.m_retMsg);

	retcode = CJSKDeclareProc::SJCB_Proc(m_ywxml_gy.m_fplxdm, jzlx, strSQ, strFphz, retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
	}

	XmlBuild(m_pXmlConstruct, strSQ, strFpmx, strFpdxx, strFphz, strQtxx, &retInfo);	//调用XML组装函数

	return SUCCESS;
}



