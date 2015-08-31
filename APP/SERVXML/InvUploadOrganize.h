

#ifndef LIB_INV_UPLOAD_ORGANIZE__
#define LIB_INV_UPLOAD_ORGANIZE__

#include "IncludeMe.h"
#include "AppProtocol.h"



class CInvUploadOrganize : public ProtocolOrganize
{
public:
	CInvUploadOrganize(); 
	~CInvUploadOrganize();

	INT32 Build(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);
	INT32 Parse(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);


};


#endif






