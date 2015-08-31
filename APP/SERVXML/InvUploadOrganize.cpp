

#include "InvUploadOrganize.h"
#include "ProtocolCommon.h"
#include "ProtocolCrc.h"
#include "ServXml_Root.h"
#include "ServXml_Zip.h"
#include "ServXml_InvUploadEx.h"
// #include "Test1Xml_yw.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CInvUploadOrganize::CInvUploadOrganize()
{
}

CInvUploadOrganize::~CInvUploadOrganize()
{
}

INT32 CInvUploadOrganize::Build(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	INT32 ret=0;

	AppProtocol *protocol = pre; 

	protocol = new ProtocolBase64(protocol);
	protocol = new CInvUploadEx(protocol);
	protocol = new ProtocolBase64(protocol);
	protocol = new CServXml_Zip(protocol);

	ret = protocol->MakeData(pBusiness, pData, pNote, strErr);
	DBG_PRINT(("pData->outLen = %d", pData->outLen));

	delete protocol;
	return ret;
}
	
INT32 CInvUploadOrganize::Parse(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	INT32 ret=0;

	AppProtocol *protocol = pre; 

 	protocol = new CInvUploadEx(protocol);
//	protocol = new ProtocolBase64(protocol);
	protocol = new CServXml_Zip(protocol);

	ret = protocol->ObtainData(pBusiness, pData, pNote, strErr);
	DBG_PRINT(("ret = %d", ret));

	delete protocol;
	return ret;
}










