/*! \file    SerXml_Yccb.cpp
   \brief    款机调用的中间件接口 (网络接口)业务六: 远程抄报接口(0013专普票)
   \author   lzh
   \version  1.0
   \date     2015
 */

#include "ServXml_YccbHx.h"
#include "ServWlcb.h"
#include "GlobalNetArg.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

CServYccbHx::CServYccbHx(AppProtocol *p):ProtocolXML(p)
{
	setDeclaration(XML_DEF_VERSION, XML_DEF_ENCODING, GBK_CHAR_TYPE);
	setXmlSaveFile(XML_DEF_YCCBHX_REQFILE, XML_DEF_BUSSINESS_RSPFILE); 
	setRootName("hydataFromHxClient");
}

CServYccbHx::~CServYccbHx()
{
	DBG_PRINT(("in ~CServYccbHx()"))
}

INT32 CServYccbHx::XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("IN CServYccbHx::XmlBusinessBuild"));
	DBG_ASSERT_EXIT((pBusiness != NULL), (" pBusiness == NULL!"));
	
	CServWlcb *p = (CServWlcb *)pBusiness;

	//操作类型:01,获取报税明文数据;02,获取清零解锁数据 可不传
	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "czlx");
	pXmlBuild->AddText("");

	//开票机号,必需项
	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "kpjh");
	pXmlBuild->AddText(g_gNetArg->m_kpjh);
	DBG_PRINT(("kpjh : %s", g_gNetArg->m_kpjh.c_str()));
	
	//报税时间,YYYY-MM-DD HH24:MI,必需项
	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "bssj");
	pXmlBuild->AddText(p->m_cssj);
	DBG_PRINT(("bssj : %s", p->m_cssj.c_str()));
	
	//加密报税数据,必需项
	DBG_ASSERT_EXIT((pData != NULL), (" pData == NULL!"));
	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "encryptedTaxData");
	pXmlBuild->AddText((INT8 *)pData);
	
	//票种授权代码 卷票:025 ,必需项
	pXmlBuild->AddNode(pXmlBuild->m_RootElement, "pzsqdm");
	pXmlBuild->AddText(p->m_fplxdm);
	DBG_PRINT(("pzsqdm : %s", p->m_fplxdm.c_str()));
	
	return SUCCESS;
}

INT32 CServYccbHx::XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	DBG_PRINT(("CServYccbHx::XmlBusinessParse Begin"));

	memset(g_Xml_ExchangeBuf, 0, PROTOCOL_OUT_BUFF_LEN);
	memcpy(g_Xml_ExchangeBuf, pData->pBuff, pData->outLen);
	pData->fill(g_Xml_ExchangeBuf, pData->outLen);
	memset(g_Xml_ExchangeBuf, 0, PROTOCOL_OUT_BUFF_LEN);
	

	return SUCCESS;
}


