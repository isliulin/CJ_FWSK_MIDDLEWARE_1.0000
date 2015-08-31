

#include "StructOrganize.h"
#include "ProtocolCommon.h"
#include "ProtocolCrc.h"
#include "ServXml_Root.h"
// #include "Test1Xml_yw.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

INT8 g_Xml_OutBuf[PROTOCOL_OUT_BUFF_LEN];
INT8 g_Xml_ExchangeBuf[PROTOCOL_OUT_BUFF_LEN];
INT8 g_Xml_OutBuf_Inv[PROTOCOL_OUT_BUFF_LEN];
INT8 g_Xml_ExchangeBuf_Inv[PROTOCOL_OUT_BUFF_LEN];


CStructOrganize::CStructOrganize()
{
}

CStructOrganize::~CStructOrganize()
{
}

INT32 CStructOrganize::Build(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	INT32 ret=0;

	AppProtocol *protocol = pre; 
	protocol = new ProtocolGZip(protocol);
	protocol = new ProtocolMd5(protocol);
	protocol = new ProtocolBase64(protocol);

	protocol = new CServXml_Root(protocol);
	
	ret = protocol->MakeData(pBusiness, pData, pNote, strErr);
	DBG_PRINT(("pData->outLen = %d", pData->outLen));

	delete protocol;
	return ret;
}
	
INT32 CStructOrganize::Parse(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	INT32 ret=0;

	AppProtocol *protocol = pre; 
	protocol = new ProtocolGZip(protocol);
	protocol = new ProtocolMd5(protocol);
	protocol = new ProtocolBase64(protocol);

	protocol = new CServXml_Root(protocol);

	ret = protocol->ObtainData(pBusiness, pData, pNote, strErr);
	DBG_PRINT(("ret = %d", ret));

	delete protocol;
	return ret;
}










