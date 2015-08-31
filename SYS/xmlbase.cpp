/*! \file    xmlbase.cpp
   \brief    xml�ӿڲ�ʵ��
   \author   zl
 */

#include "IncludeMe.h"
#include "commonFunc.h"
#include "xmlbase.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


#if (USE_XML_FUNC!=0)



XMLParse::XMLParse()
{
	m_signNode = NULL;
	m_signNodeLayer = 0;
}

XMLParse::~XMLParse()
{
	
}

int XMLParse::XMLParseBegin( const char *file, int charType )
{
	//����һ��XML���ĵ�����
    m_myDocument = new TiXmlDocument(file);
	m_myDocument->SetCharType(charType);
    m_myDocument->LoadFile();

    //��ø�Ԫ�أ���
    m_RootElement = m_myDocument->RootElement();
	m_parentElement[0] = m_RootElement;
	
	if (m_RootElement == NULL)
		return FAILURE;
	else
		return SUCCESS;
}

void XMLParse::XMLParseEnd()
{	
	if (NULL != m_myDocument)
	{
		delete m_myDocument;
		m_myDocument = NULL;
	}	
	return;
}

int XMLParse::LocateNode( TiXmlElement *ParentElement, int ChildNo )
{
	int j;
	
	if( ParentElement == NULL)
	{
		DBG_PRINT(("ParentElement == NULL %d", ChildNo));
		return FAILURE;
	}

	m_Child = ParentElement->FirstChildElement();
		
	if( ChildNo > 0 ) //���ChildNo����0�����õ�ChildNo+1���ڵ�
	{
		for( j=0; j<ChildNo; j++ )
		{
			m_Child = m_Child->NextSiblingElement();
		}
	}

	if( m_Child==NULL )
	{
		return FAILURE;
	}
	else
	{
		return SUCCESS;
	}
}

int XMLParse::LocateNodeByName( TiXmlElement *ParentElement, char* strName, int ChildNo)
{
	int i;

	if( ParentElement == NULL)
	{
		DBG_PRINT(("ParentElement == NULL %s", strName));
		return FAILURE;
	}

	m_Child = ParentElement->FirstChildElement(strName);
	for (i=0;i<ChildNo;i++)
	{
		if (m_Child == NULL)
		{
			DBG_PRINT(("m_Child == NULL break i : %d", i));
			break;
		}
		m_Child = m_Child->NextSiblingElement(strName);
	}
	
	if( m_Child == NULL )
	{		
		DBG_PRINT(("m_Child == NULL %s", strName));
		return FAILURE;
	}

	return SUCCESS;
}

string XMLParse::GetText()
{
	string oriText("");
	string nodeText("");
	char *pout=NULL;

	if (m_Child == NULL)
		return nodeText;

	pout = (char *)m_Child->GetText();
	if(pout != NULL)
		oriText = pout;
	pout = NULL;
	
#if (USE_ICONV_LIB!=0)
	int ret;
	if(m_myDocument->m_charType == UTF8_CHAR_TYPE)
	{
		ret = code_convert("utf-8", "gbk", oriText.c_str(), oriText.length(), &pout);		
		if (ret != 0)
		{
			DBG_PRINT(("utf8תGBK����: %d", ret));
		}
		else
		{
			nodeText.assign(pout);
		}
	}
	else
	{
		nodeText = oriText;
	}

#else
	nodeText = oriText;
#endif		//USE_ICONV_LIB

	return nodeText;
}

//-------------------------------------------------------
//���ܣ���ýڵ������
//���룺������
//���������ֵ
//˵�����������ǻ�ȡLocateNodeָ��Ľڵ�����ԣ���m_Childָ��Ľڵ������
//������
//-------------------------------------------------------
string XMLParse::GetAttr( string AttrName )
{
	string AttrValue("");
	char *pout=NULL;
	
	if (m_Child != NULL)
	{
		pout = (char *)m_Child->Attribute(AttrName.c_str());
	}
		
	if (pout != NULL)
		AttrValue.assign(pout);

	return AttrValue;
}

int XMLParse::SignNode(TiXmlElement *node)
{
	int layer=-1;

	if (node == NULL)
	{
		return FAILURE;
	}
	m_signNode = node;

	layer = getNodeLayer(node);
	if (layer==-1)	
	{
		return FAILURE;
	}
	m_signNodeLayer = layer;

	return SUCCESS;
}

int XMLParse::getNodeLayer(TiXmlElement *node)
{
	int layer=0;
	TiXmlNode* p=NULL;

	if (node == m_RootElement)
	{
		layer = 0;
	}
	else
	{
		p = node;
		do {
			layer++;
			p = node->Parent();
		}while(p != m_RootElement);
	}
	return layer;
}



XMLConstruct::XMLConstruct()
{
	
}

XMLConstruct::~XMLConstruct()
{
	
}

void XMLConstruct::XMLConstructBegin(int charType)
{
	
	//����һ��XML���ĵ�����
    m_myDocument = new TiXmlDocument();
	m_xmlDeclaration = new TiXmlDeclaration("1.0", "gbk", "");

	m_myDocument->SetCharType(charType);
    //����һ����Ԫ�ز����ӡ�
    m_RootElement = new TiXmlElement("root");
	m_myDocument->LinkEndChild(m_xmlDeclaration);
    m_myDocument->LinkEndChild(m_RootElement);

	//��ʱm_RootElement���Ǹ��ڵ��ָ��
	m_parentElement[0] = m_RootElement;
	
	return;
}

void XMLConstruct::XMLConstructBegin(string ver, string character, string rootName,int charType)
{
	//����һ��XML���ĵ�����
    m_myDocument = new TiXmlDocument();
	m_xmlDeclaration = new TiXmlDeclaration(ver.c_str(), character.c_str(), "");

	m_myDocument->SetCharType(charType);

    //����һ����Ԫ�ز����ӡ�
    m_RootElement = new TiXmlElement(rootName.c_str());
	m_myDocument->LinkEndChild(m_xmlDeclaration);
    m_myDocument->LinkEndChild(m_RootElement);

	//��ʱm_RootElement���Ǹ��ڵ��ָ��
	m_parentElement[0] = m_RootElement;
	
	return;
}

void XMLConstruct::XMLConstructBeginSimple(string rootName, int charType)
{	
	//����һ��XML���ĵ�����
    m_myDocument = new TiXmlDocument();

	m_myDocument->SetCharType(charType);
    //����һ����Ԫ�ز����ӡ�
    m_RootElement = new TiXmlElement(rootName.c_str());
    m_myDocument->LinkEndChild(m_RootElement);
	m_parentElement[0] = m_RootElement;
	
	return;
}

int XMLConstruct::XMLConstructBeginUpdate(const char *file, int charType)
{
	//����һ��XML���ĵ�����
    m_myDocument = new TiXmlDocument(file);
	m_myDocument->SetCharType(charType);
    m_myDocument->LoadFile();
	
    //��ø�Ԫ�أ���
    m_RootElement = m_myDocument->RootElement();
	m_parentElement[0] = m_RootElement;
	
	if (m_RootElement == NULL)
		return FAILURE;
	else
		return SUCCESS;
}

int XMLConstruct::XMLConstructEnd(const char *XmlPath )
{
	INT32 ret;
    //���浽�ļ�
    if( true == m_myDocument->SaveFile(XmlPath) )
	{		
		ret = SUCCESS;
	}
	else
	{
		ret = FAILURE;
	}
	
	if (NULL != m_myDocument)
	{
		delete m_myDocument;
		m_myDocument = NULL;
	}

	return ret;
}

void XMLConstruct::XMLConstructDelete( )
{	
	if (NULL != m_myDocument)
	{
		delete m_myDocument;
		m_myDocument = NULL;
	}
	return;
}

int XMLConstruct::AddNode( TiXmlElement *ParentElement, string nodeName )
{
	//����һ����ΪnodeName��Ԫ�ز����ӵ����ڵ��ϡ�
    m_NewElement = new TiXmlElement(nodeName.c_str());
    ParentElement->LinkEndChild(m_NewElement);
	//��ʱm_NewElement�����½ڵ��ָ�롣

	return SUCCESS;
}

int XMLConstruct::InsertNode(TiXmlElement *pParent, TiXmlElement *pNode)
{
	if (pParent->InsertEndChild(*pNode) != NULL)
		return SUCCESS;
	else
		return FAILURE;
}

int XMLConstruct::InsertAllChildNode(TiXmlElement *pParent, TiXmlElement *pNode)
{
	if (pNode->Type() != TiXmlNode::ELEMENT)			//�����޷��ų����ָ��pNode��Type()ֵ����Ϊ0x01�����
	{
		printf("!!! pNode is not a TiXmlElement point !! \n");	
		printf("Error in function \"InsertAllChildNode()\" \n");	
		exit(-1);
	}

	TiXmlElement* m_Child = pNode->FirstChildElement();
	
	while( m_Child != NULL )
	{
		if (pParent->InsertEndChild(*m_Child) == NULL)
			return FAILURE;
		
		m_Child = m_Child->NextSiblingElement();
	}
	
	return SUCCESS;
}

int XMLConstruct::AddText( string TextValue, int type )
{
	char *pout=NULL;
	string utf8Str("");

#if (USE_ICONV_LIB!=0)
	int ret;
	if(m_myDocument->m_charType == UTF8_CHAR_TYPE)
	{
		ret = code_convert("gbk", "utf-8", TextValue.c_str(), TextValue.length(), &pout);
		if (ret != 0)
		{
			DBG_PRINT(("GBKתutf8����: %d", ret));
		}
		else
		{
			utf8Str.assign(pout);
		}
	}
	else
	{
		utf8Str = TextValue;
	}
	
#else
	utf8Str = TextValue;
#endif	//USE_ICONV_LIB


	//����һ����ΪTextValue��Ԫ�ز����丳���ڵ㡣
    m_Content = new TiXmlText(utf8Str.c_str());
	if (type == XML_SET_TEXT_CDATA)
	{
		m_Content->SetCDATA(true);
	}
    m_NewElement->LinkEndChild(m_Content);
	//��ʱm_Content�����µ�TextValueԪ�ص�ָ�롣
	
	return SUCCESS;
}

int XMLConstruct::AddAttr( string AttrName, string AttrValue )
{    
    m_NewElement->SetAttribute(AttrName.c_str(), AttrValue.c_str());
	return SUCCESS;
}


int XMLConstruct::LocateNodeByName( TiXmlElement *ParentElement, char* strName, int ChildNo)
{
	int i;
	
	if( ParentElement == NULL)
	{
		DBG_PRINT(("ParentElement == NULL %s", strName));
		return FAILURE;
	}
	m_Child = ParentElement->FirstChildElement(strName);
	for (i=0;i<ChildNo;i++)
	{
		if (m_Child == NULL)
		{
			DBG_PRINT(("m_Child == NULL break i : %d", i));
			break;
		}
		m_Child = m_Child->NextSiblingElement(strName);
	}
	
	if( m_Child == NULL )
	{		
		DBG_PRINT(("m_Child == NULL %s", strName));
		return FAILURE;
	}
	
	return SUCCESS;
}
string XMLConstruct::GetText()
{
	string oriText("");
	string nodeText("");
	char *pout=NULL;
	
	if (m_Child == NULL)
		return nodeText;
	
	pout = (char *)m_Child->GetText();
	if(pout != NULL)
		oriText = pout;
	pout = NULL;
	
#if (USE_ICONV_LIB!=0)
	int ret;
	if(m_myDocument->m_charType == UTF8_CHAR_TYPE)
	{
		ret = code_convert("utf-8", "gbk", oriText.c_str(), oriText.length(), &pout);		
		if (ret != 0)
		{
			DBG_PRINT(("utf8תGBK����: %d", ret));
		}
		else
		{
			nodeText.assign(pout);
		}
	}
	else
	{
		nodeText = oriText;
	}
	
#else
	nodeText = oriText;
#endif		//USE_ICONV_LIB
	
	return nodeText;
}

//-------------------------------------------------------
//���ܣ���ýڵ������
//���룺������
//���������ֵ
//˵�����������ǻ�ȡLocateNodeָ��Ľڵ�����ԣ���m_Childָ��Ľڵ������
//������
//-------------------------------------------------------
string XMLConstruct::GetAttr( string AttrName )
{
	string AttrValue("");
	char *pout=NULL;
	
	if (m_Child != NULL)
	{
		pout = (char *)m_Child->Attribute(AttrName.c_str());
	}
	
	if (pout != NULL)
		AttrValue.assign(pout);
	
	return AttrValue;
}

int XMLConstruct::UpdateText( string TextValue, int type )
{
	char *pout=NULL;
	string utf8Str("");
	
#if (USE_ICONV_LIB!=0)
	int ret;
	if(m_myDocument->m_charType == UTF8_CHAR_TYPE)
	{
		ret = code_convert("gbk", "utf-8", TextValue.c_str(), TextValue.length(), &pout);
		if (ret != 0)
		{
			DBG_PRINT(("GBKתutf8����: %d", ret));
		}
		else
		{
			utf8Str.assign(pout);
		}
	}
	else
	{
		utf8Str = TextValue;
	}
	
#else
	utf8Str = TextValue;
#endif	//USE_ICONV_LIB
	
	TiXmlNode *m_childNode;
	TiXmlNode *m_bakNode;
	
	if (m_Child == NULL)
	{
		return FAILURE;
	}

    m_Content = new TiXmlText(utf8Str.c_str());
	if (type == XML_SET_TEXT_CDATA)
	{
		m_Content->SetCDATA(true);
	}

	m_bakNode = m_Child;
	m_childNode = m_Child->FirstChild();
	if (m_childNode==NULL)
	{
		m_bakNode->LinkEndChild(m_Content);
	}
	else
	{
		m_bakNode->ReplaceChild(m_childNode, *m_Content);
	}

	return SUCCESS;
}


#endif		//USE_XML_FUNC




