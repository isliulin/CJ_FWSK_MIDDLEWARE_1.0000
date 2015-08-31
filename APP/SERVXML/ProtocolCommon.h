

#ifndef __LIB_PROTOCOL_COMMON_
#define __LIB_PROTOCOL_COMMON_

#include "ProtocolStream.h"


class ProtocolBase64 : public ProtocolStream 
{
public:
	ProtocolBase64(AppProtocol *p); 
	~ProtocolBase64();

	INT32 EncodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr);
	INT32 DecodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr);
};

class ProtocolZLib : public ProtocolStream 
{
public:
	ProtocolZLib(AppProtocol *p);
	~ProtocolZLib();

	INT32 EncodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr);
	INT32 DecodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr);
};

class ProtocolGZip : public ProtocolStream 
{
public:
	ProtocolGZip(AppProtocol *p);
	~ProtocolGZip();

	INT32 EncodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr);
	INT32 DecodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr);

	void setGzipTmpFile(string ReqFile, string RspFile);

private:
	string m_gzipReqFile;
	string m_gzipRspFile;

};




#endif






