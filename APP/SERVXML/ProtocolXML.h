

#ifndef LIB_APP_PROTOCOL_XML
#define LIB_APP_PROTOCOL_XML

#include "xmlbase.h"
#include "AppProtocol.h"
#include "YWXmlBase.h"


#define SERV_RET_INFO_SUCCESS		"0000"
#define XML_DEBUG_OUT


#define SSL_USE_TYPE				1
#define NET_LOCK_FLAG				1	//网络是否加互斥开关

#define SSL_AUTH_CODE				"htxx_test"
#define TECH_MSG_APP_ID				"zzs_fp_cgl_cj"
#define TECH_MSG_SERV_ID_INV		"jsp_skskj_cb"				//上传、结果下载、抄报、清卡
#define TECH_MSG_SERV_ID_PARA		"jsp_dzdz_cb_zzszp"			//企业参数下载
#define TECH_MSG_SERV_ID_GP			"dzdz_gpxx_xiazai_zzszp"	//购票信息下载
#define TECH_MSG_CERT_PWD			"88888888"
#define TECH_MSG_SERV_IP			"192.168.0.104"
#define TECH_MSG_SERV_PORT			"8002"
#define TECH_MSG_SEND_NAME			"aisino"

class ServRet_Info
{
public:
	string m_retCode;
	string m_retMsg;
public:
	ServRet_Info(){InitServRetInfo();}

	void InitServRetInfo(){m_retCode=SERV_RET_INFO_SUCCESS;	m_retMsg="成功";}

};

class CTechnologyMsg
{
public:
	CTechnologyMsg()
	{
		m_appId = TECH_MSG_APP_ID;
		m_servId = TECH_MSG_SERV_ID_INV;
		m_certPwd = TECH_MSG_CERT_PWD;
		m_passWord = TECH_MSG_CERT_PWD;
		m_servIP = TECH_MSG_SERV_IP;
		m_servPort = TECH_MSG_SERV_PORT;
		m_nsrsbh = "";
		m_sendName = TECH_MSG_SEND_NAME;
	}

	string m_appId;
	string m_servId;
	string m_servIP;
	string m_servPort;
	string m_certPwd;
	string m_passWord;
	string m_nsrsbh;
	string m_sendName;
};


class ProtocolXML : public AppProtocol 
{
public:
	ProtocolXML(AppProtocol *p); 
	ProtocolXML(ProtocolOrganize *p);
	~ProtocolXML();

	void setDeclaration(string ver, string character, int charType, int declarationFlag=1);
	void setRootName(string name);
	void setXmlSaveFile(string ReqFileName,  string RspFileName);
	void setUpdateFile(string updateFile, int charType, int declarationFlag=2);

	INT32 MakeData(void *pBusiness, DataOutType *pData, void *pNote, string &strErr);
	INT32 ObtainData(void *pBusiness, DataOutType *pData, void *pNote, string &strErr);

	virtual INT32 CommunicationProc(void* pDataIn, void* pDataOut, string &strErr){return SUCCESS;};	

	void SetServRetInfo(string retCode, string retMsg);
	UINT8 CheckServRetInfo();
	void GetServRetInfo(string &retCode, string &retMsg);

	void GetTechMsgStr(CTechnologyMsg *pTechMsg, string &strTechMsg);
	void GetTechMsgStrTest(CTechnologyMsg *pTechMsg, string &strTechMsg);

private:
	/*!
	@brief 业务XML构造	
	@attention   
	*/ 
	virtual INT32 XmlBusinessBuild(XMLConstruct *pXmlBuild, void *pBusiness, void *pData, void *pNote, string &strErr)=0;	

	/*!
	@brief 业务XML解析	
	@attention   
	*/ 
	virtual INT32 XmlBusinessParse(XMLParse *pXmlParse, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)=0;	

	void *getBusinessData_p(AppProtocol *protocol, DataOutType *pData);
	void reset();

protected:
	INT32 BuildXml(void *pBusiness, DataOutType *pData, void *pNote, string &strErr);	
	INT32 ParseXml(void *pBusiness, DataOutType *pData, void *pNote, string &strErr);
	
	INT32 signNode(TiXmlElement *pTiXmlNode, DataOutType *pData);
	
private:
	XMLConstruct m_XmlBuild;							
	XMLParse m_XmlParse;		
	
	string m_ver;
	string m_character;
	string m_rootName;
	INT32 m_charType;
	string m_xmlReqFile;
	string m_xmlRspFile;
	string m_xmlUpdateFile;

	INT32 m_declarationFlag;

protected:
	ProtocolOrganize *m_pOrganize;
	ServRet_Info m_servRetInfo;

};




#endif






