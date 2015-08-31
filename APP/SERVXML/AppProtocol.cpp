#include <string.h>
#include <stdio.h>
#include "AppProtocol.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"





AppProtocol::AppProtocol(AppProtocol *p)
{
	m_pProtocol=p;
	m_pExchangeBuff=NULL;
	m_exchangeBuffLen=0;
}

AppProtocol::~AppProtocol()
{
	DBG_PRINT(("in ~AppProtocol()"))
	if (m_pProtocol != NULL)	
	{
		if (m_pProtocol->m_pProtocol != NULL)//需保留第一个m_pProtocol在业务层删除
		{
			delete m_pProtocol;
			m_pProtocol = NULL;
		}
	}
}
	
void AppProtocol::setExchangeBuff(INT8 *buf, INT32 len) 
{
	m_pExchangeBuff=buf; 
	m_exchangeBuffLen=len;
}

INT32 AppProtocol::readfile(const INT8 *path, void *pOut, INT32 *oLen, string &strErr)
{
	INT32 fileLen=0;
	FILE *fp=NULL;

	if( (fp = fopen(path, "rb")) == NULL )
	{
		strErr = "打开读文件失败";
		return FAILURE;
	}

	fseek( fp, 0L, SEEK_END );	
	fileLen = ftell( fp );
	DBG_PRINT(("filelen: %u", fileLen));
	if (fileLen > *oLen)
	{
		strErr = "目标文件超长";
		return FAILURE;
	}

	memset(pOut, 0, *oLen);
	fseek( fp, 0L, SEEK_SET );	
	fread( (void *)pOut, fileLen, 1, fp);
	fclose(fp);
	*oLen = fileLen;

	return SUCCESS;
}

INT32 AppProtocol::writefile(const INT8 *path, void *pIn, INT32 iLen, string &strErr)
{
	FILE *fp=NULL;

	if( (fp = fopen(path, "wb")) == NULL )
	{
		strErr = "打开写文件失败";
		return FAILURE;
	}
	fwrite( (void *)pIn, iLen, 1, fp);
	fclose(fp);
	return SUCCESS;
}


//////////////////////////////////////////////////////////////////////////



DataOutType::DataOutType()
{
	clear();
}
DataOutType::DataOutType(INT8 *p, INT32 maxlen)
{
	clear();
	pBuff=p;
	maxLen=maxlen;
}
DataOutType::~DataOutType()
{
}

void DataOutType::clear()
{
	pBuff=NULL; 
	maxLen=0;
	outLen=0;	
	type = STREAM;
	memset(point, 0, sizeof(point));
}

void DataOutType::setBuff(INT8 *p, INT32 maxlen)
{
	pBuff=p;
	maxLen=maxlen;
	outLen=0;
}

void DataOutType::clrBuff()
{
	if (pBuff)
		memset(pBuff, 0, maxLen);
}

void DataOutType::setPoint(INT32 *p)
{
	INT8 *pTmp = point;	
	*((INT32 *)pTmp) = (INT32)p;//将一个指针转换为整型数赋值给point[]的第一个元素?
	type = POINT;
}

INT32* DataOutType::getPoint()
{
	INT8 *pTmp = point;
	return (INT32 *)(*((INT32 *)pTmp));
}

INT32 DataOutType::movRight(INT32 pos)
{
	INT8 *p = pBuff+outLen-1;
	INT8 *q = p+pos;
	
	if (outLen==0)
		return SUCCESS;
	if (outLen+pos > maxLen)
		return FAILURE;

	while (p!=pBuff)
		*q-- = *p--;
	*q=*p;
	memset(p, '-', pos);
	outLen += pos;

	return SUCCESS;
}

INT32 DataOutType::getmax()
{
	return maxLen;
}
INT8* DataOutType::getBuff()
{
	return pBuff;
}
INT32* DataOutType::getLen_p()
{
	return &outLen;
}
INT32 DataOutType::fill(INT8 *p, INT32 num)
{
	if (num > maxLen)
		return FAILURE;
	memset(pBuff, 0, maxLen);
	memcpy(pBuff, p, num);
	outLen = num;
	return SUCCESS;
}








