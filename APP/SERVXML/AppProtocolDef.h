

#ifndef __LIB_APP_PROTOCOL_DEF
#define __LIB_APP_PROTOCOL_DEF

#include "IncludeMe.h" 




//////////////////////////////////////////////////////////////////////////
// XML协议的相关定义
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
// 过程BUFF的定义
//////////////////////////////////////////////////////////////////////////
#define		PROTOCOL_OUT_BUFF_LEN						(1024*10)		
#define		PROTOCOL_EXHCANGE_BUFF_LEN					(1024*10)	
	
extern INT8 g_Xml_OutBuf[];
extern INT8 g_Xml_ExchangeBuf[];
extern INT8 g_Xml_OutBuf_Inv[];
extern INT8 g_Xml_ExchangeBuf_Inv[];


//////////////////////////////////////////////////////////////////////////
// 与业务相关的定义
//////////////////////////////////////////////////////////////////////////
typedef struct {
	string m_appType;
	UINT8  m_md5Buf[64]; 
} NoteData_Para;


#define SK_TYPE_JSP				"JSP"
#define SK_TYPE_SKP				"SKP"

#define NET_QYCSXZ		"0001"  //二、企业参数下载接口
#define NET_FPSC		"0003"  //三、发票上传接口
#define NET_FPSCJGXZ	"0004"  //四、发票上传结果下载接口
#define NET_YCCB		"0013"	//六、远程抄报接口
#define NET_QKXXXZ 		"0014"  //七、清卡信息下载接口
#define NET_FPJXZJS		"0020"	//九、发票卷下载/解锁接口




//////////////////////////////////////////////////////////////////////////
// 调试开关
//////////////////////////////////////////////////////////////////////////

#define		XML_ORGANIZE_TYPE			1


#endif






