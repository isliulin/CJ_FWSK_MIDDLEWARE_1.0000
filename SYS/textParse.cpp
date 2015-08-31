#include "textParse.h"

#include "LOGCTRL.h"
#define NO_POS_DEBUG
#include "pos_debug.h"

CTextParse::CTextParse()
{
	m_text = "";
	m_divideChar = "";
	m_pos = 0;
}

CTextParse::~CTextParse()
{
}


void CTextParse::reset()
{
	m_pos = 0;
}

void CTextParse::setText(const INT8 *p)
{
	m_text.assign(p);
	m_pos = 0;
}

void CTextParse::setDivideChar(const INT8 *p)
{
	m_divideChar.assign(p);
}

void CTextParse::setEraseChar(const INT8 *p)
{
	m_eraseChar.assign(p);
}


INT32 CTextParse::getSubStr(string &dest)
{
	INT32 subBeginPos=0, subLen=0;
	INT32 tmpPos=m_pos;
	
	dest.assign("");

	if (tmpPos >= m_text.length()-1)
	{
		DBG_PRINT(("In end of text."));
		return -1;
	}

	tmpPos = m_text.find_first_not_of(m_divideChar, tmpPos);
	if (tmpPos == string::npos)
	{
		DBG_PRINT(("can't find normal char!"));
		return -1;
	}
	subBeginPos = tmpPos;

	tmpPos = m_text.find_first_of(m_divideChar, tmpPos);
	if (tmpPos == string::npos)
	{
		DBG_PRINT(("can't find divide char!"));
		subLen = m_text.length()-subBeginPos;
		tmpPos = m_text.length()-1;
	}
	else
	{
		subLen = tmpPos-subBeginPos;
		tmpPos++;
	}

	m_pos = tmpPos;
	dest = m_text.substr(subBeginPos, subLen);

	return 0;
}

INT32 CTextParse::getSubStrByFlag(string &dest, const INT8 *flag)
{
	INT32 subBeginPos=0, subLen=0;
	INT32 tmpPos = m_pos;

	dest.assign("");
	subBeginPos = tmpPos;
	tmpPos = m_text.find(flag, tmpPos);
	if (tmpPos == string::npos)
	{
		subLen = m_text.length()-subBeginPos;
		tmpPos = m_text.length()-1;
		m_pos = tmpPos;
		dest = m_text.substr(subBeginPos, subLen);
		return 0;
	}
	else
	{
		subLen = tmpPos - subBeginPos;
		tmpPos += strlen(flag);
		m_pos = tmpPos;
		dest = m_text.substr(subBeginPos, subLen);
		return 1;
	}
}

void CTextParse::eraseCharacter(string &oriStr) 
{
	INT32 pos=0;
	while ( (pos=oriStr.find_first_of(m_eraseChar, pos)) != string::npos )
	{
		oriStr.erase(pos,1);
	}
}

