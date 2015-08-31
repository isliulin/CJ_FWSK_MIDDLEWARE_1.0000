

#ifndef __LIB_PROTOCOL_CRC_
#define __LIB_PROTOCOL_CRC_

#include "ProtocolStream.h"

#define AES_KEY_LEN		16
#define AES_KEY_CONTENT		"lxdyccb123456wjh"		//ÃØÔ¿
#define AES_VECTOR_CONTENT	"wjhyccb123456lxd"		//Æ«ÒÆÁ¿


class ProtocolMd5 : public ProtocolStream 
{
public:
	ProtocolMd5(AppProtocol *p); 
	~ProtocolMd5();

	INT32 EncodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr);
	INT32 DecodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr);
};

class ProtocolAes : public ProtocolStream 
{
public:
	ProtocolAes(AppProtocol *p); 
	~ProtocolAes();
	
	INT32 EncodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr);
	INT32 DecodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr);

private:
	UINT8 m_aeskey[AES_KEY_LEN+1];
	UINT8 m_vector[AES_KEY_LEN+1];

};


#endif






