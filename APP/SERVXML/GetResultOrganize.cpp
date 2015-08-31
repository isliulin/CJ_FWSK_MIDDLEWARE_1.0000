

#include "GetResultOrganize.h"
#include "ServXml_Zip.h"
#include "ProtocolCommon.h"
// #include "Test1Xml_yw.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CGetResultOrganize::CGetResultOrganize()
{
}

CGetResultOrganize::~CGetResultOrganize()
{
}

INT32 CGetResultOrganize::Build(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	INT32 ret=0;

	AppProtocol *protocol = pre; 

	protocol = new ProtocolBase64(protocol);
	protocol = new CServXml_Zip(protocol);

	ret = protocol->MakeData(pBusiness, pData, pNote, strErr);
	DBG_PRINT(("pData->outLen = %d", pData->outLen));

	delete protocol;
	return ret;
}
	
INT32 CGetResultOrganize::Parse(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	INT32 ret=0;

	AppProtocol *protocol = pre; 

//	protocol = new ProtocolBase64(protocol);
	protocol = new CServXml_Zip(protocol);

	ret = protocol->ObtainData(pBusiness, pData, pNote, strErr);
	DBG_PRINT(("ret = %d", ret));

	delete protocol;
	return ret;
}










