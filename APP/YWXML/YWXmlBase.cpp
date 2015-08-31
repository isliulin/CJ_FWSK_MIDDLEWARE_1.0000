
#include "YWXmlBase.h"
#include "CGlobalArgLib.h"
#include "JSKManageProc.h"
#include "AppProtocolDef.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

string CYWXmlBase::m_ywlx = "";

CYWXmlBase::CYWXmlBase(XMLConstruct *construct, XMLParse *parse)
{
	m_pXmlConstruct = construct;
	m_pXmlParse = parse;
	m_sslStrErr = "";
}
CYWXmlBase::~CYWXmlBase()
{
}

INT32 CYWXmlBase::StartYWXml(string strInput, XMLParse *parse, XMLConstruct *construct, string &ywlx)
{
	FILE *fp;	
	INT8 tmpBuff[MAX_SEND_BUF_LEN];

	memset(tmpBuff, 0, sizeof(tmpBuff));
	sprintf((INT8 *)tmpBuff, "%s", strInput.c_str());
	UINT32 tmpLen = strInput.length();
	DBG_PRINT(("tmpLen = %u", tmpLen));

	//接收数据写文件
	if( (fp = fopen(XML_RESPONSE_FILE, "wb")) == NULL )
	{
		return JSK_FAILURE;
	}

	DBG_PRINT(("2 生成XmlRspFile.xml文件"));
	fwrite( (void *)tmpBuff, tmpLen, 1, fp);
	fclose(fp);
//	printf("\n%s\n",tmpBuff);

	//解析传入的XML参数
	char *pout=NULL;
	
	int ret = parse->XMLParseBegin(XML_RESPONSE_FILE);
	DBG_PRINT(("ret = %d", ret));
	pout = (char *)parse->m_RootElement->Attribute(XML_BUSINESS_ID);
	if (pout == NULL)
		return JSK_FAILURE;
	
	ywlx.assign(pout);
	m_ywlx = ywlx;
	DBG_PRINT(("ywlx = %s", ywlx.c_str()));

	if( (ywlx==BUSINESS_NETID_FPSSSC) || (ywlx==BUSINESS_NETID_FPSCJGHQ) ||
		(ywlx==BUSINESS_NETID_WLCB) || (ywlx==BUSINESS_NETID_QLJS) || (ywlx==BUSINESS_NETID_QLJSJGQR) )
	{
		//construct->XMLConstructBeginUpdate(XML_DEF_BUSSINESS_RSPFILE, GBK_CHAR_TYPE);
	}
	else
	{
		//组织传出的XML参数
		construct->XMLConstructBegin("1.0", "gbk", XML_BUSINESS);
		construct->m_RootElement->SetAttribute(XML_BUSINESS_ID, ywlx.c_str());
	}

	return JSK_SUCCESS;
}

INT32 CYWXmlBase::OverYWXml(XMLParse *parse, XMLConstruct *construct, string &strOutput)
{
	//结束解析
	parse->XMLParseEnd();
	
	if( (m_ywlx==BUSINESS_NETID_FPSSSC) || (m_ywlx==BUSINESS_NETID_FPSCJGHQ) ||
		(m_ywlx==BUSINESS_NETID_WLCB) || (m_ywlx==BUSINESS_NETID_QLJS) || (m_ywlx==BUSINESS_NETID_QLJSJGQR) )
	{
		construct->XMLConstructBeginUpdate(XML_DEF_BUSSINESS_RSPFILE, GBK_CHAR_TYPE);
	}
	//组成完毕
	if( 1 != construct->XMLConstructEnd(XML_REQUEST_FILE) )
	{
		return JSK_FAILURE;
	}
	DBG_PRINT(("5 生成XmlReqFile.xml"));
	FILE *fp;
	INT8 tmpBuff[MAX_SEND_BUF_LEN];
	memset(tmpBuff, 0, sizeof(tmpBuff));
	
	//读取XML文件至BUFF
	if( (fp = fopen(XML_REQUEST_FILE, "rb")) == NULL )
	{
		//strErr = "未找到XML文件";
		return JSK_FAILURE;
	}
	fseek( fp, 0L, SEEK_END );	
	int dataLen = ftell( fp );				
	DBG_PRINT(("Req filelen: %d", dataLen));
	
	fseek( fp, 0L, SEEK_SET );	
	fread( (void *)tmpBuff, dataLen, 1, fp);
	fclose(fp);

	strOutput = tmpBuff;

	return JSK_SUCCESS;
}
INT32 CYWXmlBase::OverYWXml(XMLParse *parse, XMLConstruct *construct)
{
	//结束解析
	parse->XMLParseEnd();
	
	if( (m_ywlx==BUSINESS_NETID_FPSSSC) || (m_ywlx==BUSINESS_NETID_FPSCJGHQ) ||
		(m_ywlx==BUSINESS_NETID_WLCB) || (m_ywlx==BUSINESS_NETID_QLJS) || (m_ywlx==BUSINESS_NETID_QLJSJGQR) )
	{
		;
	}
	else
	{
		//组成完毕
		if( 1 != construct->XMLConstructEnd(XML_REQUEST_FILE) )
		{
			return JSK_FAILURE;
		}
	}
	
	return JSK_SUCCESS;
}
INT32 CYWXmlBase::ErrYWXml(XMLParse *parse, XMLConstruct *construct, Return_Info *retInfo, string &strOutput)
{
	//组织传出的XML参数
	construct->XMLConstructBegin("1.0", "gbk", XML_BUSINESS);
	construct->m_RootElement->SetAttribute(XML_BUSINESS_ID, "");
	
	//组装错误信息
	construct->AddNode(construct->m_RootElement, "body");
	construct->m_parentElement[1] = construct->m_NewElement;
	
	construct->AddNode(construct->m_parentElement[1], "output");
	construct->m_parentElement[2] = construct->m_NewElement;
	
	//添加returncode节点
	construct->AddNode(construct->m_parentElement[2], "returncode");
	construct->AddText(retInfo->m_retCode);

	//添加returnmsg节点
	construct->AddNode(construct->m_parentElement[2], "returnmsg");
	construct->AddText(retInfo->m_retMsg);
	
	//组成完毕
	if( 1 != construct->XMLConstructEnd(XML_REQUEST_FILE) )
	{
		return JSK_FAILURE;
	}
	
	FILE *fp;
	INT8 tmpBuff[MAX_SEND_BUF_LEN];
	
	//读取XML文件至BUFF
	if( (fp = fopen(XML_REQUEST_FILE, "rb")) == NULL )
	{
		return JSK_FAILURE;
	}
	fseek( fp, 0L, SEEK_END );	
	int dataLen = ftell( fp );				
	DBG_PRINT(("Req filelen: %d", dataLen));
	
	fseek( fp, 0L, SEEK_SET );	
	fread( (void *)tmpBuff, dataLen, 1, fp);
	fclose(fp);
	
	strOutput = tmpBuff;
	
	return JSK_SUCCESS;
}


INT32 CYWXmlBase::CheckYWXmlPara(string &strErr, UINT8 uFlag)
{
	if(m_ywxml_gy.m_sksbkl == "")
		m_ywxml_gy.m_sksbkl = g_globalArgLib->m_strSksbkl;
	CJSKManageProc::set_JSKPara(m_ywxml_gy.m_jqbh, m_ywxml_gy.m_sksbkl, m_ywxml_gy.m_bspkl);

	if(uFlag == CHECK_ID_NULL)
		return JSK_SUCCESS;

	if(g_globalArgLib->m_corpInfo->m_Nsrsbh != m_ywxml_gy.m_nsrsbh)
	{
		strErr = "纳税人识别号错误!";
		return JSK_FAILURE;
	}

	if(uFlag == CHECK_ID_NARSBH)
		return JSK_SUCCESS;

	if(g_globalArgLib->m_corpInfo->m_Jspsbh != m_ywxml_gy.m_sksbbh)
	{
		strErr = "税控设备编号错误!";
		return JSK_FAILURE;
	}

	if(uFlag == CHECK_ID_SKSBBH)
		return JSK_SUCCESS;

	if(g_globalArgLib->m_corpInfo->m_bspbh != m_ywxml_gy.m_bspbh)
	{
		strErr = "报税盘编号错误!";
		return JSK_FAILURE;
	}

	return JSK_SUCCESS;
}


