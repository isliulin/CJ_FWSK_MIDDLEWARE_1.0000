/*! \file    YWXML_TJXXCX.h
   \brief    ������õ��м���ӿ� ҵ��2.19ͳ����Ϣ��ѯ
   \author   lzh
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_TJXXCX_H
#define LIB_YWXML_TJXXCX_H


#include "IncludeMe.h"
#include "YWXmlBase.h"
#include "CTjxxhz.h"
#include "SysMacDef.h"

#define  TJXXCX_MONTHMAX 6

namespace middleware
{
/**
 *@class CTjxxcx
 *@brief ͳ����Ϣ��ѯ
 */
class CTjxxcx : public CYWXmlBase
{


public:

	CTjxxcx(XMLConstruct *construct, XMLParse *parse);
	~CTjxxcx();
	
	INT32 Execute(); 


private:
	/*!
	@������: XmlParse
	@brief ͳ����Ϣ��ѯ�������������������XML�ļ���
	@param[in]  parse		XML������
	@param[out]  tjxxhz	ͳ����Ϣ������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, CTjxxhz *tjxxhz);

	/*!
	@������: XmlBuild
	@brief ͳ����Ϣ��ѯ�����������װ����װXML�ļ���
	@param[in]  construct		XML��װ��
	@param[in]  retInfo		������Ϣ��
	@param[in]  tjxxhz			ͳ����Ϣ������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, Return_Info *retInfo, CTjxxhz *tjxxhz, INT32 MonthCount);

		
};

}
#endif


