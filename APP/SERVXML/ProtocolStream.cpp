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

	//�ȵ���ǰһ����MakeData
	DBG_ASSERT_EXIT((m_pProtocol != NULL), (" m_pProtocol == NULL!"));
	ret = m_pProtocol->MakeData(pBusiness, pData, pNote, strErr);
	if (ret != SUCCESS)
	{
		return ret;
	}

	//���ñ����ı��뺯��
	DBG_ASSERT_EXIT((pData->type == DataOutType::STREAM), ("pData type error !"));
	if (m_pExchangeBuff != NULL)
	{
		if (pData->outLen > PROTOCOL_EXHCANGE_BUFF_LEN)		//��pData�����ݿ����������ڴ� 
		{
			strErr = "������̽������治��";
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

	//���ñ����Ľ��뺯��
	DBG_ASSERT_EXIT((pData->type == DataOutType::STREAM), ("pData type error !"));
	if (m_pExchangeBuff != NULL)
	{
		if (pData->outLen > PROTOCOL_EXHCANGE_BUFF_LEN)		//��pData�����ݿ����������ڴ� 
		{
			strErr = "������̽������治��";
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

	//���ú�һ����ObtainData
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








