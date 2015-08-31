

#ifndef LIB_STRUCT_ORGANIZE__
#define LIB_STRUCT_ORGANIZE__

#include "IncludeMe.h"
#include "AppProtocol.h"



class CStructOrganize : public ProtocolOrganize
{
public:
	CStructOrganize(); 
	~CStructOrganize();

	INT32 Build(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);
	INT32 Parse(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);


};


#endif






