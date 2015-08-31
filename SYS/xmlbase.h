/*! \file    xmlbase.h
   \brief    xml�ӿڲ㶨��
   \author   zl
 */
#ifndef LIB_TIXML_BASE_INCLUDED
#define LIB_TIXML_BASE_INCLUDED

#include <string>
#include "SYSModuleHeader.h"
#include "tinyxml.h"
#include "VersionConfig.h"
using namespace std;

#if (USE_XML_FUNC!=0)



#define XML_SET_TEXT_CDATA		1
#define XML_SET_TEXT_NORMAL		0

#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
namespace middleware
{
#endif

/*!
@class XMLParse
@brief ����XML����
*/
class XMLParse
{
public:
	
	XMLParse();	
	~XMLParse();

	/*!
	@brief ��ʼ��һ��XML�ļ��Ľ���
	@param[in] file XML�ļ���
	@param[in] charType �ַ������ͣ�GBK_CHAR_TYPE��UTF8_CHAR_TYPE
	*/
	int XMLParseBegin( const char *file, int charType = GBK_CHAR_TYPE );

	/*!
	@brief ������ǰ��XML����
	*/
	void XMLParseEnd();

	/*!
	@brief ������Ŷ�λһ���ӽڵ�
	@param[in] ParentElement ���ڵ�ָ��
	@param[in] ChildNo �ӽڵ���ţ���0Ϊ��ʼ��0��ʾ��һ���ӽڵ㣬1��ʾ�ڶ�����
	@return  1 - �ҵ���ָ�����ӽڵ�  0 - δ�ҵ� 
	*/
	int LocateNode( TiXmlElement *ParentElement, int ChildNo=0 );

	/*!
	@brief �������ƺ���Ŷ�λһ���ӽڵ㣬����λ���ϸ������Ƶĵ�N���ڵ㡣
	@param[in] ParentElement ���ڵ�ָ��
	@param[in] strName �ӽ������
	@param[in] ChildNo �ӽڵ���ţ���0Ϊ��ʼ��0��ʾ��һ���ӽڵ㣬1��ʾ�ڶ�����
	@return  1 - �ҵ���ָ�����ӽڵ�  0 - δ�ҵ� 
	*/
	int LocateNodeByName( TiXmlElement *ParentElement, char* strName, int ChildNo=0);

	/*!
	@brief ȡ��ǰ��λ�ڵ��ֵ
	@return  �ڵ�ֵ 
	*/
	string GetText();

	/*!
	@brief ȡ��ǰ��λ�ڵ��ĳ������
	@param[in] AttrName ��������
	@return  ����ֵ 
	*/
	string GetAttr( string AttrName );

	int SignNode(TiXmlElement *ParentElement);

private:
	int getNodeLayer(TiXmlElement *node);

public:
	TiXmlDocument *m_myDocument;			/**< XML�ĵ����	*/
	TiXmlElement *m_RootElement;			/**< ���ڵ��ָ�롣����ڵ��ǵ�0�㣬����һ���ǵ�1�㡣	*/
	TiXmlElement *m_parentElement[11];		/**< �����ָ�룬����ÿһ���Ӧһ��ָ�롣�����1���ָ����m_parentElement[1]����ָ������ڸò�����нڵ����ƶ���	*/
	TiXmlElement *m_Child;					/**< ���ӽڵ��ָ��	*/

	TiXmlElement *m_signNode;
	int m_signNodeLayer;

};


/*!
@class XMLConstruct
@brief ����XML��װ
*/
class XMLConstruct
{
public:
	
	XMLConstruct();
	~XMLConstruct();

	/*!
	@brief ��ʼ��װһ��XML�ļ�����������ʹ��Ĭ��ֵ��
	@param[in] charType �ַ������ͣ�Ĭ��ΪGBK_CHAR_TYPE
	*/
	void XMLConstructBegin( int charType = GBK_CHAR_TYPE);

	/*!
	@brief ��ʼ��װһ��XML�ļ�����������ʹ�ô������
	@param[in] ver �汾����
	@param[in] character �ַ������ԣ���UTF-8����GBK��
	@param[in] rootName ���ڵ�����
	@param[in] charType �ַ������ͣ�Ӧ��characterֵ���Ӧ��Ĭ��ΪGBK_CHAR_TYPE
	*/
	void XMLConstructBegin(string ver, string character, string rootName, int charType = GBK_CHAR_TYPE);

	void XMLConstructBeginSimple(string rootName, int charType);

	int XMLConstructBeginUpdate(const char *file, int charType = GBK_CHAR_TYPE);

	/*!
	@brief ������ǰXML����װ������Ϊ�ļ���
	@param[in] XmlPath ���ɵ�XML�ļ�����·��
	@return  1 - �ɹ�  0 - ʧ��
	*/
	int XMLConstructEnd(const char *XmlPath );

	void XMLConstructDelete( );

	/*!
	@brief ���һ���ӽڵ�
	@param[in] ParentElement ���ڵ�ָ��
	@param[in] nodeName �ӽڵ�����
	@return  0 - �ɹ� 
	*/
	int AddNode( TiXmlElement *ParentElement, string nodeName );

	/*!
	@brief ����AddNode���Ľڵ����ֵ
	@param[in] TextValue �ڵ�ֵ
	@param[in] type �ڵ�ֵ���ͣ�XML_SET_TEXT_NORMAL��XML_SET_TEXT_CDATA
	@return  0 - �ɹ� 
	*/
	int AddText( string TextValue, int type=XML_SET_TEXT_NORMAL );

	/*!
	@brief ����AddNode���Ľڵ��������
	@param[in] AttrName ��������
	@param[in] AttrValue ����ֵ
	@return  0 - �ɹ� 
	*/
	int AddAttr( string AttrName, string AttrValue );

	int InsertNode(TiXmlElement *pParent, TiXmlElement *pNode);
	int InsertAllChildNode(TiXmlElement *pParent, TiXmlElement *pNode);


	/*!
	@brief �������ƺ���Ŷ�λһ���ӽڵ㣬����λ���ϸ������Ƶĵ�N���ڵ㡣
	@param[in] ParentElement ���ڵ�ָ��
	@param[in] strName �ӽ������
	@param[in] ChildNo �ӽڵ���ţ���0Ϊ��ʼ��0��ʾ��һ���ӽڵ㣬1��ʾ�ڶ�����
	@return  1 - �ҵ���ָ�����ӽڵ�  0 - δ�ҵ� 
	*/
	int LocateNodeByName( TiXmlElement *ParentElement, char* strName, int ChildNo=0);

	/*!
	@brief ȡ��ǰ��λ�ڵ��ֵ
	@return  �ڵ�ֵ 
	*/
	string GetText();

	/*!
	@brief ȡ��ǰ��λ�ڵ��ĳ������
	@param[in] AttrName ��������
	@return  ����ֵ 
	*/
	string GetAttr( string AttrName );

	/*!
	@brief ����AddNode���Ľڵ����ֵ
	@param[in] TextValue �ڵ�ֵ
	@param[in] type �ڵ�ֵ���ͣ�XML_SET_TEXT_NORMAL��XML_SET_TEXT_CDATA
	@return  0 - �ɹ� 
	*/
	int UpdateText( string TextValue, int type=XML_SET_TEXT_NORMAL );

public:
    TiXmlDocument *m_myDocument;			/**< XML�ĵ����	*/
	TiXmlDeclaration *m_xmlDeclaration;		/**< XML�ĵ�����	*/
	TiXmlElement *m_RootElement;			/**< ���ڵ��ָ�롣����ڵ��ǵ�0�㣬����һ���ǵ�1�㡣	*/
	TiXmlElement *m_parentElement[11];		/**< �����ָ�룬����ÿһ���Ӧһ��ָ�롣�����1���ָ����m_parentElement[1]����ָ������ڸò�����нڵ����ƶ���	*/
	TiXmlElement *m_NewElement;				/**< �¼ӽڵ��ָ��	*/
	TiXmlText *m_Content;					/**< �ڵ�ֵ����	*/
	TiXmlElement *m_Child;					/**< ���ӽڵ��ָ��	*/



};

#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
}
#endif

#endif		//USE_XML_FUNC

#endif		//TIXML_BASE_INCLUDED
