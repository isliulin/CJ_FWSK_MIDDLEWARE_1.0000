

#ifndef __LIB_PROTOCOL_STREAM
#define __LIB_PROTOCOL_STREAM

#include "AppProtocol.h"


class ProtocolStream : public AppProtocol 
{
public:
	ProtocolStream(AppProtocol *p); 
	~ProtocolStream();

	INT32 MakeData(void *pBusiness, DataOutType *pData, void *pNote, string &strErr);
	INT32 ObtainData(void *pBusiness, DataOutType *pData, void *pNote, string &strErr);

private:
	virtual INT32 EncodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr)=0;
	virtual INT32 DecodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr)=0;

};



#endif


