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


//��˰��ģʽ����
#define MODE_TYPE_JSP		1	//1��ֱ��


#define MAX_SEND_BUF_LEN		1024*10

#define XML_BUSINESS		"business"
#define XML_BUSINESS_ID		"id"


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
#define BUSINESS_YWID_FJTH			"FJTH"				//�ֻ��˻�
#define BUSINESS_YWID_BGZSKL		"BGZSKL"		    //���֤�����
#define BUSINESS_YWID_FPBL			"FPBL"				//��Ʊ��¼
#define BUSINESS_YWID_ERRUPINV		"ERRUPINV"			//��ȡ�ϴ�����Ʊ��Ϣ
#define BUSINESS_YWID_HQLXSJ		"HQLXSJ"			//��ȡ�����������

#define BUSINESS_NETID_FPSSSC		"FPSSSC"			//��Ʊʵʱ�ϴ�
#define BUSINESS_NETID_FPSCJGHQ		"FPSCJGHQ"			//��Ʊ�ϴ������ȡ
#define BUSINESS_NETID_WLCB			"WLCB"				//���糭��
#define BUSINESS_NETID_QLJS			"QLJS"				//�������
#define BUSINESS_NETID_QLJSJGQR		"QLJSJGQR"			//����������ȷ��
#define BUSINESS_NETID_LXXXSC		"LXXXSC"			//������Ϣ�ϴ�
#define BUSINESS_NETID_WLLQFP		"WLLQFP"			//������ȡ��Ʊ
#define BUSINESS_NETID_WLLQFPJGQR	"WLLQFPJGQR"		//������ȡ��Ʊ���ȷ��
#define BUSINESS_NETID_QYCSXZKJ		"QYCSXZ_KJ"			//��ҵ��������


#define CHECK_ID_NULL		0
#define CHECK_ID_NARSBH		1
#define CHECK_ID_SKSBBH		2
#define CHECK_ID_BSPBH		3

class CLIBYWXML_GY
{
public:
	string m_jqbh;			//˰���տ�����
	string m_nsrsbh;		//��˰��ʶ���
	string m_nsrmc;			//��˰������
	string m_sksbbh;		//˰���豸���
	string m_sksbkl;		//˰���豸����
	string m_fplxdm;		//��Ʊ���ʹ���
	string m_bspbh;			//��˰�̱��
	string m_bspkl;			//��˰�̿���
	string m_kpjh;			//��Ʊ���� 0������ �������ֻ�
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
	Return_Info(){m_retCode="0";m_retMsg="�ɹ�";}
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

