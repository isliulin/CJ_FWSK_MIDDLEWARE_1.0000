
#include <string.h>
#include "base64.h"
#include "gZip.h"
#include "ProtocolCommon.h"

#include "LOGCTRL.h"
#define NO_POS_DEBUG
#include "pos_debug.h"

#pragma comment(lib,"zlib.lib")


ProtocolBase64::ProtocolBase64(AppProtocol *p):ProtocolStream(p)
{
}

ProtocolBase64::~ProtocolBase64()
{
	DBG_PRINT(("in ~ProtocolBase64()"))
}

INT32 ProtocolBase64::EncodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr)
{
	INT32 tmpLen=0, maxLen=*dLen;

	Base64_Encode_2((UINT8 *)pd, sLen);
	tmpLen = strlen(pd);
 	DBG_PRINT(("base64 encode Length: %d", tmpLen));
	if (tmpLen > maxLen)
	{
		strErr="Base64�����ڴ����";
		return FAILURE;
	}
	*dLen = tmpLen;
	DBG_PRINT(("Base64::EncodeData() complete."))
	return SUCCESS;
}

INT32 ProtocolBase64::DecodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr)
{
	Base64_Decode_2(pd, (int *)dLen);
 	DBG_PRINT(("base64 decode Length: %d", *dLen));
	if (*dLen == 0)
	{
		strErr = "Base64�������";
		return FAILURE;
	}
	DBG_PRINT(("Base64::DecodeData() complete"))
	return SUCCESS;
}


//////////////////////////////////////////////////////////////////////////


ProtocolZLib::ProtocolZLib(AppProtocol *p):ProtocolStream(p)
{
	setExchangeBuff(g_Xml_ExchangeBuf, PROTOCOL_EXHCANGE_BUFF_LEN);
}

ProtocolZLib::~ProtocolZLib()
{
	DBG_PRINT(("in ~ProtocolZLib()"))
}

INT32 ProtocolZLib::EncodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr)
{
	INT32 ret=0;
	unsigned long nZipLen=compressBound(sLen);	
	
	ret = compress((UINT8 *)pd, &nZipLen, (const UINT8 *)ps, sLen);
	if (ret != Z_OK)
	{
		strErr = "zLibѹ��ʧ��";
		return FAILURE;
	}
	*dLen = nZipLen;
	DBG_PRINT(("zLib length = %u", *dLen));
	DBG_PRINT(("ZLib::EncodeData() complete."))
		
	return SUCCESS;
}

INT32 ProtocolZLib::DecodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr)
{
	INT32 ret=0, maxLen=*dLen;
	unsigned long unZipLen = *dLen;	
	
	ret = uncompress((UINT8 *)pd, &unZipLen, (const UINT8 *)ps, sLen);
	if (ret != Z_OK)
	{
		strErr = "zLib��ѹʧ��";
		return FAILURE;
	}
	if (unZipLen>maxLen)
	{
		strErr="zLib��ѹ�ڴ����";
		return FAILURE;		
	}
	*dLen = unZipLen;
	DBG_PRINT(("zLib length = %u", *dLen));
	DBG_PRINT(("ZLib::DecodeData() complete."))
		
	return SUCCESS;
}


//////////////////////////////////////////////////////////////////////////

ProtocolGZip::ProtocolGZip(AppProtocol *p):ProtocolStream(p)
{
	setGzipTmpFile(TMP_REQ_ZIP_FILE_NAME, TMP_RSP_ZIP_FILE_NAME);
}

ProtocolGZip::~ProtocolGZip()
{
	DBG_PRINT(("in ~ProtocolGZip()"))
}

INT32 ProtocolGZip::EncodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr)
{
	INT32 ret=0;

#ifndef WIN32
	//��ps�����ݴ�Ϊ��ʱ�ļ�
	ret = writefile(m_gzipReqFile.c_str(), pd, sLen, strErr);
	if (ret != SUCCESS)
	{
		return FAILURE;
	}

	//ִ��gzѹ��
	ret = compress_one_file(m_gzipReqFile.c_str(), (INT8 *)m_gzipRspFile.c_str());
	if (ret != 0)
	{
		strErr = "GZipѹ������";
		return FAILURE;
	}

	//��ȡѹ���ļ���pData
	ret = readfile(m_gzipRspFile.c_str(), pd, dLen, strErr);
	if (ret != SUCCESS)
	{
		return FAILURE;
	}
#endif

	DBG_PRINT(("GZip::EncodeData() complete."))
	return SUCCESS;
}

INT32 ProtocolGZip::DecodeData(INT8 *ps, INT32 sLen, INT8 *pd, INT32 *dLen, void *pNote, string &strErr)
{
	INT32 ret=0;
	
#ifndef WIN32
	//��ps�����ݴ�Ϊ��ʱ�ļ�
	ret = writefile(m_gzipReqFile.c_str(), pd, sLen, strErr);
	if (ret != SUCCESS)
	{
		return FAILURE;
	}
	
	//ִ��gz��ѹ��
	ret = decompress_one_file(m_gzipReqFile.c_str(), (INT8 *)m_gzipRspFile.c_str());
	if (ret != 0)
	{
		strErr = "GZip��ѹ������";
		return FAILURE;
	}
	
	//��ȡѹ���ļ���pData
	ret = readfile(m_gzipRspFile.c_str(), pd, dLen, strErr);
	if (ret != SUCCESS)
	{
		return FAILURE;
	}
#endif

	DBG_PRINT(("GZip::DecodeData() complete."))
	return SUCCESS;
}

void ProtocolGZip::setGzipTmpFile(string ReqFile, string RspFile)
{
	m_gzipReqFile = ReqFile ;
	m_gzipRspFile = RspFile;
}








