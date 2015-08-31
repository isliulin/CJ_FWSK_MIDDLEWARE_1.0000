#include <string.h>
#include "ProtocolStream.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


ProtocolStream::ProtocolStream(AppProtocol *p):AppProtocol(p)
{
}

ProtocolStream::~ProtocolStream()
{
	DBG_PRINT(("in ~ProtocolStream()"))
}

INT32 ProtocolStream::MakeData(void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	INT32 ret=0;
	INT8 *psBuf=NULL, *pdBuf=NULL;
	INT32 sLen=0, dLen=0;

	//先调用前一级的MakeData
	DBG_ASSERT_EXIT((m_pProtocol != NULL), (" m_pProtocol == NULL!"));
	ret = m_pProtocol->MakeData(pBusiness, pData, pNote, strErr);
	if (ret != SUCCESS)
	{
		return ret;
	}

	//调用本级的编码函数
	DBG_ASSERT_EXIT((pData->type == DataOutType::STREAM), ("pData type error !"));
	if (m_pExchangeBuff != NULL)
	{
		if (pData->outLen > PROTOCOL_EXHCANGE_BUFF_LEN)		//将pData中数据拷贝至交换内存 
		{
			strErr = "编码过程交换缓存不足";
			return FAILURE;
		}
		memcpy(m_pExchangeBuff, pData->pBuff, pData->outLen);
		pData->clrBuff();

		psBuf = m_pExchangeBuff;
	}
	else
	{
		psBuf = NULL;
	}
	sLen = pData->outLen;
	pdBuf = pData->pBuff;
	dLen = pData->getmax();

	ret = EncodeData(psBuf, sLen, pdBuf, &dLen, pNote, strErr);
	if (ret != SUCCESS)
	{
		return FAILURE;
	}

	pData->outLen = dLen;
	DBG_PRINT(("EncodeData outLen = %u", pData->outLen));
	DBG_PRINT(("---------End of ProtocolStream::MakeData---------"))
	return SUCCESS;
}

INT32 ProtocolStream::ObtainData(void *pBusiness, DataOutType *pData, void *pNote, string &strErr)
{
	INT32 ret=0;
	INT8 *psBuf=NULL, *pdBuf=NULL;
	INT32 sLen=0, dLen=0;

	//调用本级的解码函数
	DBG_ASSERT_EXIT((pData->type == DataOutType::STREAM), ("pData type error !"));
	if (m_pExchangeBuff != NULL)
	{
		if (pData->outLen > PROTOCOL_EXHCANGE_BUFF_LEN)		//将pData中数据拷贝至交换内存 
		{
			strErr = "解码过程交换缓存不足";
			return FAILURE;
		}
		memcpy(m_pExchangeBuff, pData->pBuff, pData->outLen);
		pData->clrBuff();

		psBuf = m_pExchangeBuff;
	}
	else
	{
		psBuf = NULL;
	}
	sLen = pData->outLen;
	pdBuf = pData->pBuff;
	dLen = pData->getmax();

	ret = DecodeData(psBuf, sLen, pdBuf, &dLen, pNote, strErr);
	if (ret != SUCCESS)
	{
		return FAILURE;
	}
	
 	pData->outLen = dLen;
	DBG_PRINT(("DecodeData outLen = %u", pData->outLen));
	DBG_PRINT(("---------End of ProtocolStream::ObtainData---------"))

	//调用后一级的ObtainData
	if (m_pProtocol != NULL)
	{
		ret = m_pProtocol->ObtainData(pBusiness, pData, pNote, strErr);
		if (ret != SUCCESS)
		{
			return ret;
		}
	}	

	return SUCCESS;
}








