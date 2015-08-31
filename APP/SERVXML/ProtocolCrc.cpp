
#include <string.h>
#include "md5c.h"
#include "ProtocolCrc.h"
#include "arithmetic.h"
#include "aes.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

ProtocolMd5::ProtocolMd5(AppProtocol *p):ProtocolStream(p)
{
}

ProtocolMd5::~ProtocolMd5()
{
	DBG_PRINT(("in ~ProtocolMd5()"))
}

INT32 ProtocolMd5::EncodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr)
{
	UINT8 tmpMD5[64];
	UINT32 tmpLen = 0;

	memset((void *)g_MD5_CTX, 0x00, sizeof(MD5_CTX));
	memset(tmpMD5,0,sizeof(tmpMD5));
	MD5Init_skj(g_MD5_CTX);
	MD5Update_skj(g_MD5_CTX, (UINT8 *)pd, sLen);
	MD5Final_skj(tmpMD5, g_MD5_CTX);

	//tmpLen = strlen((INT8 *)tmpMD5);
	tmpLen = 16;
	DBG_PRINT(("tmpLen = %u", tmpLen));
	NoteData_Para *note = (NoteData_Para *)pNote;
	memset(note->m_md5Buf, 0, sizeof(note->m_md5Buf));
	bin2char(tmpMD5, (INT8 *)note->m_md5Buf, tmpLen);
	
	*dLen = sLen;

	DBG_PRINT(("Md5 = %s", note->m_md5Buf));
	DBG_PRINT(("Md5::EncodeData() complete."))
	return SUCCESS;
}

INT32 ProtocolMd5::DecodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr)
{

	DBG_PRINT(("Md5::DecodeData() complete"))
	return SUCCESS;
}


ProtocolAes::ProtocolAes(AppProtocol *p):ProtocolStream(p)
{
	memset(m_aeskey, 0, sizeof(m_aeskey));
	memset(m_vector, 0, sizeof(m_vector));
	memcpy(m_aeskey, AES_KEY_CONTENT, AES_KEY_LEN);
	memcpy(m_vector, AES_VECTOR_CONTENT, AES_KEY_LEN);
}

ProtocolAes::~ProtocolAes()
{
	DBG_PRINT(("in ~ProtocolAes()"))
}

INT32 ProtocolAes::EncodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr)
{
	aes_encrypt_cbc( (UINT8 *)m_aeskey, (UINT8 *)m_vector, (UINT8 *)pd, (UINT32)sLen, (UINT8 *)pd, (UINT32 *)dLen);
	
	DBG_PRINT(("dLen = %u", *dLen));
	DBG_PRINT(("Aes::EncodeData() complete."))
	return SUCCESS;
}

INT32 ProtocolAes::DecodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr)
{
	aes_decrypt_cbc( (UINT8 *)m_aeskey, (UINT8 *)m_vector, (UINT8 *)pd, (UINT32)sLen, (UINT8 *)pd, (UINT32 *)dLen);

	DBG_PRINT(("Aes::DecodeData() complete"))
	return SUCCESS;
}








