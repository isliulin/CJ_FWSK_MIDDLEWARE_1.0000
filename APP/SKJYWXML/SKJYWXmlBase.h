#ifndef __YW_XML_BASE_H
#define __YW_XML_BASE_H

#include <string>
#include <cstring>
#include "IncludeMe.h"
#include "xmlbase.h"
#include "pos_debug.h"
#include "YWXMLGY.h"


#define KJ_XML_REQUEST_FILE		"KJXmlReqFile.xml"
#define KJ_XML_RESPONSE_FILE	"KJXmlRspFile.xml"


#define MAX_SEND_BUF_LEN		1024*5

#define XML_BUSINESS		"business"
#define XML_BUSINESS_ID		"id"


#define MAX_TAX_NUM			20
#define INVVOL_MAX_NUM  100            //��Ʊ���������20150519linzihao


#define BUSINESS_YWID_SKSBBH		"SKSBBH"			//˰���豸��Ų�ѯ
#define BUSINESS_YWID_SKPXXCX		"SKPXXCX"			//˰���豸��Ϣ��ѯ
#define BUSINESS_YWID_SKSBQTYXXCX	"SKSBQTYXXCX"		//˰���豸������Ϣ��ѯ
#define BUSINESS_YWID_BSPXXCX		"BSPXXCX"			//��˰����Ϣ��ѯ
#define BUSINESS_YWID_JKSJCX		"JKSJCX"			//�����Ϣ��ѯ
#define BUSINESS_YWID_SQSLCX		"SQSLCX"			//��Ȩ˰�ʲ�ѯ
#define BUSINESS_YWID_GPXXCX		"GPXXCX"			//��Ʊ��Ϣ��ѯ
#define BUSINESS_YWID_GPXXXP		"GPXXXP"			//��Ʊ��Ϣд��
#define BUSINESS_YWID_GPXXXPJS		"GPXXXPJS"			//��Ʊ��Ϣд�̽���
#define BUSINESS_YWID_KLBG			"KLBG"				//������
#define BUSINESS_YWID_FPKJ			"FPKJ"				//��Ʊ����
#define BUSINESS_YWID_FPZF			"FPZF"				//��Ʊ����
#define BUSINESS_YWID_FPCX			"FPCX"				//��Ʊ��ѯ
#define BUSINESS_YWID_SKPBSP		"SKPBSP"			//˰���豸��˰����ϲ���
#define BUSINESS_YWID_BSPFPCX		"BSPFPCX"			//��˰�̷�Ʊ��ѯ
#define BUSINESS_YWID_BSPFPFF		"BSPFPFF"			//��Ʊ�ַ�
#define BUSINESS_YWID_BSPFPSH		"BSPFPSH"			//��Ʊ�ջ�
#define BUSINESS_YWID_SJCB			"SJCB"				//���ݳ���
#define BUSINESS_YWID_JKHC			"JKHC"				//��ػش�
#define BUSINESS_YWID_TJXXCX		"TJXXCX"			//��Ʊͳ����Ϣ��ѯ
#define BUSINESS_YWID_LXXXXP		"LXXXXP"			//������Ϣд��
#define BUSINESS_YWID_FPSC			"FPSC"				//��Ʊ�ϴ�
#define BUSINESS_YWID_FPGX			"FPGX"				//��Ʊ����
#define BUSINESS_YWID_FPDR			"FPDR"				//��Ʊ����
#define BUSINESS_YWID_FPBL			"FPBL"				//��Ʊ��¼
#define BUSINESS_YWID_FJTH			"FJTH"				//�ֻ��˻�
#define BUSINESS_YWID_BGZSKL        "BGZSKL"            //���֤�����

#define BUSINESS_NETID_FPSC			"FPSSSC"			//��Ʊʵʱ�ϴ�
#define BUSINESS_NETID_FPSCJGHQ		"FPSCJGHQ"			//��Ʊ�ϴ������ȡ
#define BUSINESS_NETID_WLCB			"WLCB"				//���糭��
#define BUSINESS_NETID_QLJS			"QLJS"				//�������
#define BUSINESS_NETID_QLJSJGQR		"QLJSJGQR"			//����������ȷ��
#define BUSINESS_NETID_LXXXSC		"LXXXSC"			//������Ϣ�ϴ�
#define BUSINESS_NETID_WLLQFP		"WLLQFP"			//������ȡ��Ʊ
#define BUSINESS_NETID_WLLQFPJGQR	"WLLQFPJGQR"		//������ȡ��Ʊ���ȷ��
#define BUSINESS_NETID_QYCSXZKJ		"qycsxz_kj"			//��ҵ��������


#define XML_SUCCESS				0
#define XML_FAILURE				-1
#define XML_INTERNAL_ERR_NO		-110

class CReturnInfo
{
public:
	string m_retCode;
	string m_retMsg;
public:
	CReturnInfo(){m_retCode="0";m_retMsg="�ɹ�";}
};

class CSKJYWXmlBase  
{
	
public:
	CSKJYWXmlBase(CYWXML_GY &ywxml_gy);
	~CSKJYWXmlBase();

	INT32 YWXml_Proc(string &strErr);
	INT32 NETXml_Proc(string &strErr);
	void SetServInfo(string ip, string port, string path);

	CYWXML_GY &m_ywxml_gy;

protected:
	XMLConstruct m_pXmlConstruct;
	XMLParse m_pXmlParse;
	CReturnInfo m_retInfo;
	string m_ywlx;

	string m_servip;
	string m_servport;
	string m_servpath;
	string m_pin;
	string m_Err;
	string m_nsrsbh;
	string m_servId;

	virtual INT32 XmlBuild()=0;
	virtual INT32 XmlParse()=0;
	
private:
	INT32 BuildProc();
	INT32 ParseProc();

};


#endif

