

#ifndef LIB_GET_RESULT_ORGANIZE__
#define LIB_GET_RESULT_ORGANIZE__

#include "IncludeMe.h"
#include "AppProtocol.h"



class CGetResultOrganize : public ProtocolOrganize
{
public:
	CGetResultOrganize(); 
	~CGetResultOrganize();

	INT32 Build(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);
	INT32 Parse(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);


};


#endif






