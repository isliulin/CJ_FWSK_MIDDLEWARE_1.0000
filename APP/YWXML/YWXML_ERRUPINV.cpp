/*! \file    YWXML_ERRUPINV.h
   \brief    款机调用的中间件接口 业务2.29.获取上传出错发票信息
   \author   myf
   \version  1.0
   \date     2015 
*/

#include "YWXML_ERRUPINV.h"
#include "JSKMakeInvoice.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
#include "base64.h"


//-------------------------------------------------------------------------------------------
//构造函数
//-------------------------------------------------------------------------------------------
CErrUpInv::CErrUpInv(XMLConstruct *construct, XMLParse *parse):CYWXmlBase(construct, parse)
{
	
}

//-------------------------------------------------------------------------------------------
//析构函数
//-------------------------------------------------------------------------------------------
CErrUpInv::~CErrUpInv()
{

}

INT32 CErrUpInv::XmlParse(XMLParse *parse)
{
	parse->LocateNodeByName(parse->m_RootElement, "body");
	parse->m_parentElement[1] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[1], "input");
	parse->m_parentElement[2] = parse->m_Child;
	
	parse->LocateNodeByName(parse->m_parentElement[2], "jqbh");
	m_ywxml_gy.m_jqbh= parse->GetText();		//税控收款机编号
	DBG_PRINT(("YWXML_ERRUPINV: jqbh = %s", m_ywxml_gy.m_jqbh.c_str()));	
	
	parse->LocateNodeByName(parse->m_parentElement[2], "nsrsbh");
	m_ywxml_gy.m_nsrsbh= parse->GetText();		//纳税人识别号
	DBG_PRINT(("YWXML_ERRUPINV: nsrsbh = %s", m_ywxml_gy.m_nsrsbh.c_str()));	

	parse->LocateNodeByName(parse->m_parentElement[2], "bspbh");
	m_ywxml_gy.m_sksbbh = parse->GetText();		//税控设备编号
	DBG_PRINT(("YWXML_ERRUPINV: sksbbh = %s", m_ywxml_gy.m_sksbbh.c_str()));

	parse->LocateNodeByName(parse->m_parentElement[2], "bspkl");
	m_ywxml_gy.m_sksbkl = parse->GetText();		//税控设备口令
	DBG_PRINT(("YWXML_ERRUPINV: sksbkl = %s", m_ywxml_gy.m_sksbkl.c_str()));

	return SUCCESS;
}

INT32 CErrUpInv::XmlBuild(XMLConstruct *construct, UINT32 invNum, CDataInvServ *DataInvServ, Return_Info *retInfo)
{
	INT8 buf[256];
	memset(buf, 0, sizeof(buf));

	//添加body节点
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;

	construct->AddNode(construct->m_parentElement[2], "fpzs");//出错发票张数
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%u", invNum);
	construct->AddText(buf);
	DBG_PRINT(("YWXML_ERRUPINV: invNum = %u", invNum));

	for (INT32 temp_i = 0; temp_i < invNum; temp_i++)
	{
		construct->AddNode(construct->m_parentElement[2], "fpxx");
		construct->m_parentElement[3] = construct->m_NewElement;
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "%d", temp_i+1);
		construct->AddAttr("xh", buf);

		construct->AddNode(construct->m_parentElement[3], "fpdm");
		construct->AddText(DataInvServ[temp_i].m_fpdm);	//发票代码
		DBG_PRINT(("YWXML_ERRUPINV: DataInvServ[%d].m_fpdm : %s",temp_i ,DataInvServ[temp_i].m_fpdm.c_str()));

		construct->AddNode(construct->m_parentElement[3], "fphm");
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "%08u", DataInvServ[temp_i].m_fphm);
		construct->AddText(buf);	//发票号码
		DBG_PRINT(("YWXML_ERRUPINV: DataInvServ[%d].m_fphm : %s",temp_i , buf));

		construct->AddNode(construct->m_parentElement[3], "cwms");
		construct->AddText(DataInvServ[temp_i].m_errMsg);	//领购人员
		DBG_PRINT(("YWXML_ERRUPINV: DataInvServ[%d].m_errMsg : %s",temp_i , DataInvServ[temp_i].m_errMsg.c_str()));
	}

	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);	//返回代码
	DBG_PRINT(("YWXML_ERRUPINV: returncode : %s", retInfo->m_retCode.c_str()));
	
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);		//返回信息
	DBG_PRINT(("YWXML_ERRUPINV: returnmsg : %s", retInfo->m_retMsg.c_str()));
	
	return SUCCESS;
}


INT32 CErrUpInv::Execute()
{
	CDataInvServ dataInvServ[MAX_ERR_INV_COUNT];

	Return_Info retInfo;//返回信息
	INT32 retcode = 0;
	INT8 tmpbuf[64];
	UINT32 invNum = MAX_ERR_INV_COUNT;

	XmlParse(m_pXmlParse);	//调用XML解析函数
	CheckYWXmlPara(retInfo.m_retMsg);

	retcode =  CJSKMakeInvoice::GetErrUpInv(dataInvServ, invNum,  retInfo.m_retMsg);
	if(retcode != JSK_SUCCESS)
	{
		memset(tmpbuf, 0, sizeof(tmpbuf));
		sprintf(tmpbuf, "%d", retcode);
		retInfo.m_retCode = tmpbuf;
		invNum = 0;
	}
	
	XmlBuild(m_pXmlConstruct, invNum, dataInvServ, &retInfo);	//调用XML组装函数

	return SUCCESS;
}


