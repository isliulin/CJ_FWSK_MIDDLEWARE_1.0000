/*! \file    YWXML_SKSBBHCX.h
   \brief    ������õ��м���ӿ� ҵ��2.1 ˰���豸��Ų�ѯ
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_SKSBBHCX_H
#define LIB_YWXML_SKSBBHCX_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"

namespace middleware
{

/**
 *@class CSksbbhcx
 *@brief 2.1.˰���豸��Ų�ѯ
 */
class CSksbbhcx : public CYWXmlBase
{


public:

	CSksbbhcx(XMLConstruct *construct, XMLParse *parse);
	~CSksbbhcx();
	
	INT32 Execute(); 


private:
	/*!
	@brief 2.1.˰���豸��Ų�ѯ�������������������XML�ļ���
	@param[in]  pXmlParse XML������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);
	
	/*!
	@brief ˰���豸��Ų�ѯ�����������װ����װ��XML�ļ���
	@param[in]  sksbbh ˰���豸���
	@param[in]  bspbh ��˰��
	@param[in]  qtxx   ������Ϣ
	@param[in]  retInfo ������Ϣ
	@param[out]  construct  ����XML��
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, string sksbbh, string bspbh, string qtxx, Return_Info *retInfo);

		
};

}
#endif



