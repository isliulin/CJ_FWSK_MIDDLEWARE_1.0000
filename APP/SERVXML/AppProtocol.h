

#ifndef __LIB_APP_PROTOCOL_HEADER
#define __LIB_APP_PROTOCOL_HEADER

#include "IncludeMe.h"
#include "AppProtocolDef.h"


//#define	OUTTYPE_POINT_KEYWORD				"#Key-point:"

class DataOutType;

class AppProtocol
{
public:
	AppProtocol(AppProtocol *p);
	virtual ~AppProtocol();
	
	void setExchangeBuff(INT8 *buf, INT32 len);

	virtual INT32 MakeData(void *pBusiness, DataOutType *pData, void *pNote, string &strErr) = 0;
	virtual INT32 ObtainData(void *pBusiness, DataOutType *pData, void *pNote, string &strErr) = 0;

protected:
	INT32 readfile(const INT8 *path, void *pOut, INT32 *oLen, string &strErr);
	INT32 writefile(const INT8 *path, void *pIn, INT32 iLen, string &strErr);
	
	AppProtocol *m_pProtocol;

	INT8 *m_pExchangeBuff;
	INT32 m_exchangeBuffLen;
};



class ProtocolOrganize
{
public:
	virtual INT32 Build(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr) = 0;
	virtual INT32 Parse(AppProtocol *pre, void *pBusiness, DataOutType *pData, void *pNote, string &strErr) = 0;

};


class DataOutType
{
public:
	DataOutType();
	DataOutType(INT8 *p, INT32 maxlen);
	~DataOutType();

	void clear();
	void setBuff(INT8 *p, INT32 maxlen);
	void clrBuff();
	void setPoint(INT32 *p);
	INT32 *getPoint();
	INT32 movRight(INT32 pos);
	INT32 getmax();

	INT8 *getBuff();
	INT32 *getLen_p();
	INT32 fill(INT8 *p, INT32 num);

public:
	INT8 *pBuff;
	INT32 outLen; 
	INT32 type; 

	enum{
		STREAM,
		POINT
	};


private:
	INT32 maxLen;
	INT8 point[6];

};


#endif



