

#ifndef LIB_YCCB_ORGANIZE__
#define LIB_YCCB_ORGANIZE__

#include "IncludeMe.h"
#include "AppProtocol.h"



class CYccbOrganize : public ProtocolOrganize
{
public:
	CYccbOrganize(); 
	~CYccbOrganize();

	INT32 Build(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);
	INT32 Parse(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr);


};


#endif






