/*! \file    YWXML_ERRUPINV.h
   \brief    ������õ��м���ӿ� ҵ��2.29.��ȡ�ϴ�����Ʊ��Ϣ
   \author   myf
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_ERRUPINV_H
#define LIB_YWXML_ERRUPINV_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CInvServ.h"

#define BSPFPCX_INVNUM 10
namespace middleware
{
/**
 *@class CErrUpInv
 *@brief ��ȡ�ϴ�����Ʊ��Ϣ
 */
class CErrUpInv : public CYWXmlBase
{


public:

	CErrUpInv(XMLConstruct *construct, XMLParse *parse);
	~CErrUpInv();
	
	INT32 Execute(); 


private:
	/*!
	@������: XmlParse
	@brief ��ȡ�ϴ�����Ʊ��Ϣ
	@param[in]  parse		XML������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);

	/*!
	@������: XmlBuild
	@brief ��ȡ�ϴ�����Ʊ��Ϣ
	@param[in]  construct		XML��װ��
	@param[in]  invvol		��Ʊ������Ϣ��
	@param[in]  strLgry		�칺��Ա
	@param[in]  retInfo		������Ϣ��
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, UINT32 invNum, CDataInvServ *DataInvServ, Return_Info *retInfo);

		
};

}
#endif



