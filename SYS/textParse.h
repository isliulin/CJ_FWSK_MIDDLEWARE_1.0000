/**
 @file  textParse.h
 @brief 定义字符串解析类。
 @author   zl
*/
#ifndef __TEXT_PARSE_H
#define __TEXT_PARSE_H

#include <string.h>
#include "IncludeMe.h"

using namespace std;


/**
 @class CTextParse 
 @brief 对字符串进行解析与处理。
 */
class CTextParse 
{
private:
	string m_text;
	string m_divideChar;
	string m_eraseChar;
	INT32 m_pos;

public:
	/*!
	@brief 复位字串解析游标。	
	@commit 字串内容保持不变。
	*/
	void reset();
	
	/*!
	@brief 设置待解析的字串。	
	@param[in] p 字串指针
	*/
	void setText(const INT8 *p);
	
	/*!
	@brief 设置解析的分割字符。	
	@param[in] p 分割符字串指针
	@commit 可设置多个分隔符，如" \t\n"。表示分隔符为：空格、TAB、换行符。
	*/
	void setDivideChar(const INT8 *p);

	/*!
	@brief 设置欲删除的字符。	
	@param[in] p 删除字符串指针
	@commit 可设置多个删除符，如" \t\r\n"。表示删除符为：空格、TAB、回车符、换行符。
	*/
	void setEraseChar(const INT8 *p);
	
	/*!
	@brief 根据已设置分隔符和当前解析位置提取字串。	
	@param[out] &dest 输出字串
	@return 0 - 成功；<0 - 失败（输出为空）
	@commit 若当前解析位置到字串末尾都没有分割符，则会返回一次成功，
			输出从当前位置到末尾的子串。
	*/
	INT32 getSubStr(string &dest);

	/*!
	@brief 获取从解析当前位置到给定标识串（flag）之间的字串。	
	@param[in] flag 标识字符串
	@param[out] &dest 输出字串
	@return 1 - 找到给定标识串；0 - 未找到
	@commit 若未找到标识字串，则输出当前位置到字串末尾的子串。
	*/
	INT32 getSubStrByFlag(string &dest, const INT8 *flag);

	/*!
	@brief 根据已设置删除符删除给定字串中符合条件的字符。	
	@param[in] &oriStr 带删除的字串
	*/
	void eraseCharacter(string &oriStr);


	CTextParse();
	~CTextParse();

};

#endif
