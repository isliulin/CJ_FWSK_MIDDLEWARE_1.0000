

#ifndef __LIB_APP_PROTOCOL_DEF
#define __LIB_APP_PROTOCOL_DEF

#include "IncludeMe.h" 




//////////////////////////////////////////////////////////////////////////
// XMLЭ�����ض���
//////////////////////////////////////////////////////////////////////////

#define		XML_DEF_VERSION						"1.0"
#define		XML_DEF_ENCODING					"GBK"
#define		XML_DEF_ROOTNAME					"FPXT"
#define		XML_DEF_REQFILE						"XmlNetReqFile.xml"
#define		XML_DEF_RSPFILE						"XmlNetRspFile.xml"
#define		XML_DEF_BUSSINESS_REQFILE			"XmlNetReqBussiness.xml"
#define		XML_DEF_BUSSINESS_RSPFILE			"XmlNetRspBussiness.xml"
#define		TMP_REQ_ZIP_FILE_NAME				"tmpzipReq.gz"
#define		TMP_RSP_ZIP_FILE_NAME				"tmpzipRsp.gz"


#define		XML_DEF_INVUPLOAD_REQFILE			"XmlNetReqInvUpload.xml"
#define		XML_DEF_INV_BUSSINESS_RSPFILE		"XmlNetRspInvBussiness.xml"

#define		XML_DEF_YCCB_REQFILE				"XmlNetReqYccb.xml"
#define		XML_DEF_YCCBHX_REQFILE				"XmlNetReqYccbHx.xml"


//////////////////////////////////////////////////////////////////////////
// ����BUFF�Ķ���
//////////////////////////////////////////////////////////////////////////
#define		PROTOCOL_OUT_BUFF_LEN						(1024*10)		
#define		PROTOCOL_EXHCANGE_BUFF_LEN					(1024*10)	
	
extern INT8 g_Xml_OutBuf[];
extern INT8 g_Xml_ExchangeBuf[];
extern INT8 g_Xml_OutBuf_Inv[];
extern INT8 g_Xml_ExchangeBuf_Inv[];


//////////////////////////////////////////////////////////////////////////
// ��ҵ����صĶ���
//////////////////////////////////////////////////////////////////////////
typedef struct {
	string m_appType;
	UINT8  m_md5Buf[64]; 
} NoteData_Para;


#define SK_TYPE_JSP				"JSP"
#define SK_TYPE_SKP				"SKP"

#define NET_QYCSXZ		"0001"  //������ҵ�������ؽӿ�
#define NET_FPSC		"0003"  //������Ʊ�ϴ��ӿ�
#define NET_FPSCJGXZ	"0004"  //�ġ���Ʊ�ϴ�������ؽӿ�
#define NET_YCCB		"0013"	//����Զ�̳����ӿ�
#define NET_QKXXXZ 		"0014"  //�ߡ��忨��Ϣ���ؽӿ�
#define NET_FPJXZJS		"0020"	//�š���Ʊ������/�����ӿ�




//////////////////////////////////////////////////////////////////////////
// ���Կ���
//////////////////////////////////////////////////////////////////////////

#define		XML_ORGANIZE_TYPE			1


#endif






