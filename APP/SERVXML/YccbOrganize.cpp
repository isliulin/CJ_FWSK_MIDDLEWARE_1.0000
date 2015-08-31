

#include "YccbOrganize.h"
#include "ProtocolCommon.h"
#include "ProtocolCrc.h"
#include "ServXml_Root.h"
#include "ServXml_Zip.h"
#include "ServXml_YccbEx.h"
#include "ServXml_YccbHx.h"
// #include "Test1Xml_yw.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


CYccbOrganize::CYccbOrganize()
{
}

CYccbOrganize::~CYccbOrganize()
{
}

INT32 CYccbOrganize::Build(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	INT32 ret=0;

	AppProtocol *protocol = pre; 

	protocol = new ProtocolAes(protocol);
	protocol = new ProtocolBase64(protocol);
// 	protocol = new CServYccbHx(protocol);
// 	protocol = new ProtocolBase64(protocol);
	protocol = new CServYccbEx(protocol);
	protocol = new ProtocolBase64(protocol);
	protocol = new CServXml_Zip(protocol);

	ret = protocol->MakeData(pBusiness, pData, pNote, strErr);
	DBG_PRINT(("pData->outLen = %d", pData->outLen));

	delete protocol;
	return ret;
}
	
INT32 CYccbOrganize::Parse(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	INT32 ret=0;

	AppProtocol *protocol = pre; 

// 	protocol = new CServYccbHx(protocol);
 	protocol = new CServYccbEx(protocol);
//	protocol = new ProtocolBase64(protocol);
	protocol = new CServXml_Zip(protocol);

	ret = protocol->ObtainData(pBusiness, pData, pNote, strErr);
	DBG_PRINT(("ret = %d", ret));

	delete protocol;
	return ret;
}










