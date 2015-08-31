/**
 @file  textParse.h
 @brief �����ַ��������ࡣ
 @author   zl
*/
#ifndef __TEXT_PARSE_H
#define __TEXT_PARSE_H

#include <string.h>
#include "IncludeMe.h"

using namespace std;


/**
 @class CTextParse 
 @brief ���ַ������н����봦��
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
	@brief ��λ�ִ������αꡣ	
	@commit �ִ����ݱ��ֲ��䡣
	*/
	void reset();
	
	/*!
	@brief ���ô��������ִ���	
	@param[in] p �ִ�ָ��
	*/
	void setText(const INT8 *p);
	
	/*!
	@brief ���ý����ķָ��ַ���	
	@param[in] p �ָ���ִ�ָ��
	@commit �����ö���ָ�������" \t\n"����ʾ�ָ���Ϊ���ո�TAB�����з���
	*/
	void setDivideChar(const INT8 *p);

	/*!
	@brief ������ɾ�����ַ���	
	@param[in] p ɾ���ַ���ָ��
	@commit �����ö��ɾ��������" \t\r\n"����ʾɾ����Ϊ���ո�TAB���س��������з���
	*/
	void setEraseChar(const INT8 *p);
	
	/*!
	@brief ���������÷ָ����͵�ǰ����λ����ȡ�ִ���	
	@param[out] &dest ����ִ�
	@return 0 - �ɹ���<0 - ʧ�ܣ����Ϊ�գ�
	@commit ����ǰ����λ�õ��ִ�ĩβ��û�зָ������᷵��һ�γɹ���
			����ӵ�ǰλ�õ�ĩβ���Ӵ���
	*/
	INT32 getSubStr(string &dest);

	/*!
	@brief ��ȡ�ӽ�����ǰλ�õ�������ʶ����flag��֮����ִ���	
	@param[in] flag ��ʶ�ַ���
	@param[out] &dest ����ִ�
	@return 1 - �ҵ�������ʶ����0 - δ�ҵ�
	@commit ��δ�ҵ���ʶ�ִ����������ǰλ�õ��ִ�ĩβ���Ӵ���
	*/
	INT32 getSubStrByFlag(string &dest, const INT8 *flag);

	/*!
	@brief ����������ɾ����ɾ�������ִ��з����������ַ���	
	@param[in] &oriStr ��ɾ�����ִ�
	*/
	void eraseCharacter(string &oriStr);


	CTextParse();
	~CTextParse();

};

#endif
