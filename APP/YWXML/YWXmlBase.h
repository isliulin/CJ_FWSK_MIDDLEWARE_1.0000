#ifndef __LIB_YW_XML_BASE_H
#define __LIB_YW_XML_BASE_H

#include <string.h>
#include "IncludeMe.h"
#include "xmlbase.h"

#include "JSKInfoFunc.h"

namespace middleware
{

#define XML_REQUEST_FILE		"XmlReqFile.xml"
#define XML_RESPONSE_FILE		"XmlRspFile.xml"


//金税盘模式类型
#define MODE_TYPE_JSP		1	//1：直连


#define MAX_SEND_BUF_LEN		1024*10

#define XML_BUSINESS		"business"
#define XML_BUSINESS_ID		"id"


#define BUSINESS_YWID_SKSBBH		"SKSBBH"			//税控设备编号查询
#define BUSINESS_YWID_SKPXXCX		"SKPXXCX"			//税控设备信息查询
#define BUSINESS_YWID_SKSBQTYXXCX	"SKSBQTYXXCX"		//税控设备其他信息查询
#define BUSINESS_YWID_BSPXXCX		"BSPXXCX"			//报税盘信息查询
#define BUSINESS_YWID_JKSJCX		"JKSJCX"			//监控信息查询
#define BUSINESS_YWID_SQSLCX		"SQSLCX"			//授权税率查询
#define BUSINESS_YWID_GPXXCX		"GPXXCX"			//购票信息查询
#define BUSINESS_YWID_GPXXXP		"GPXXXP"			//购票信息写盘
#define BUSINESS_YWID_GPXXXPJS		"GPXXXPJS"			//购票信息写盘解锁
#define BUSINESS_YWID_KLBG			"KLBG"				//口令变更
#define BUSINESS_YWID_FPKJ			"FPKJ"				//发票开具
#define BUSINESS_YWID_FPZF			"FPZF"				//发票作废
#define BUSINESS_YWID_FPCX			"FPCX"				//发票查询
#define BUSINESS_YWID_SKPBSP		"SKPBSP"			//税控设备报税盘组合操作
#define BUSINESS_YWID_BSPFPCX		"BSPFPCX"			//报税盘发票查询
#define BUSINESS_YWID_BSPFPFF		"BSPFPFF"			//发票分发
#define BUSINESS_YWID_BSPFPSH		"BSPFPSH"			//发票收回
#define BUSINESS_YWID_SJCB			"SJCB"				//数据抄报
#define BUSINESS_YWID_JKHC			"JKHC"				//监控回传
#define BUSINESS_YWID_TJXXCX		"TJXXCX"			//发票统计信息查询
#define BUSINESS_YWID_LXXXXP		"LXXXXP"			//离线信息写盘
#define BUSINESS_YWID_FPSC			"FPSC"				//发票上传
#define BUSINESS_YWID_FPGX			"FPGX"				//发票更新
#define BUSINESS_YWID_FPDR			"FPDR"				//发票读入
#define BUSINESS_YWID_FJTH			"FJTH"				//分机退回
#define BUSINESS_YWID_BGZSKL		"BGZSKL"		    //变更证书口令
#define BUSINESS_YWID_FPBL			"FPBL"				//发票补录
#define BUSINESS_YWID_ERRUPINV		"ERRUPINV"			//获取上传出错发票信息
#define BUSINESS_YWID_HQLXSJ		"HQLXSJ"			//获取离线相关数据

#define BUSINESS_NETID_FPSSSC		"FPSSSC"			//发票实时上传
#define BUSINESS_NETID_FPSCJGHQ		"FPSCJGHQ"			//发票上传结果获取
#define BUSINESS_NETID_WLCB			"WLCB"				//网络抄报
#define BUSINESS_NETID_QLJS			"QLJS"				//清零解锁
#define BUSINESS_NETID_QLJSJGQR		"QLJSJGQR"			//清零解锁结果确认
#define BUSINESS_NETID_LXXXSC		"LXXXSC"			//离线信息上传
#define BUSINESS_NETID_WLLQFP		"WLLQFP"			//网络领取发票
#define BUSINESS_NETID_WLLQFPJGQR	"WLLQFPJGQR"		//网络领取发票结果确认
#define BUSINESS_NETID_QYCSXZKJ		"QYCSXZ_KJ"			//企业参数下载


#define CHECK_ID_NULL		0
#define CHECK_ID_NARSBH		1
#define CHECK_ID_SKSBBH		2
#define CHECK_ID_BSPBH		3

class CLIBYWXML_GY
{
public:
	string m_jqbh;			//税控收款机编号
	string m_nsrsbh;		//纳税人识别号
	string m_nsrmc;			//纳税人名称
	string m_sksbbh;		//税控设备编号
	string m_sksbkl;		//税控设备口令
	string m_fplxdm;		//发票类型代码
	string m_bspbh;			//报税盘编号
	string m_bspkl;			//报税盘口令
	string m_kpjh;			//开票机号 0：主机 其他：分机
public:
	CLIBYWXML_GY()
	{
		m_jqbh = "";
		m_nsrsbh = "";
		m_nsrmc = "";
		m_sksbbh = "";
		m_sksbkl = "";
		m_fplxdm = "";
		m_bspbh = "";
		m_bspkl = "";
		m_kpjh = "";
	}
};

class Return_Info
{
public:
	string m_retCode;
	string m_retMsg;
public:
	Return_Info(){m_retCode="0";m_retMsg="成功";}
};

class CYWXmlBase  
{
	
public:
	CYWXmlBase(XMLConstruct *construct, XMLParse *parse);
	~CYWXmlBase();

	static INT32 StartYWXml(string strInput, XMLParse *parse, XMLConstruct *construct, string &ywlx);
	static INT32 OverYWXml(XMLParse *parse, XMLConstruct *construct, string &strOutput);
	static INT32 OverYWXml(XMLParse *parse, XMLConstruct *construct);
	static INT32 ErrYWXml(XMLParse *parse, XMLConstruct *construct, Return_Info *retInfo, string &strOutput);

	virtual INT32 Execute()=0;

	CLIBYWXML_GY m_ywxml_gy;
	string m_sslStrErr;

protected:
	XMLConstruct *m_pXmlConstruct;
	XMLParse *m_pXmlParse;;

	INT32 CheckYWXmlPara(string &strErr, UINT8 uFlag=CHECK_ID_NULL);

private:
	static string m_ywlx;

};

}
#endif

