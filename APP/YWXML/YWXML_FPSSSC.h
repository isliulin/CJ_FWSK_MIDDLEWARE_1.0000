/*! \file    YWXML_FPSSSC.h
   \brief    ������õ��м���ӿ� ҵ��2.21.��Ʊʵʱ�ϴ�
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_FPSSSC_H
#define LIB_YWXML_FPSSSC_H


#include "IncludeMe.h"
//#include "xmlbase.h"

#include "YWXmlBase.h"


namespace middleware
{
/**
 *@class CFpsssc
 *@brief 2.21.��Ʊʵʱ�ϴ�
 */
class CFpsssc : public CYWXmlBase
{


public:

	CFpsssc(XMLConstruct *construct, XMLParse *parse);
	~CFpsssc();
	
	INT32 Execute(); 


private:
	/*!
	@brief ��Ʊ���룺�����������������XML�ļ���
	@param[in]  pXmlParse XML������
	@param[out]  nFpzs	��Ʊ����
	@param[out]  czlx	��������
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse, UINT32 &nFpzs, UINT8 &czlx);
	
	/*!
	@brief ��Ʊ���룺���������װ����װ��XML�ļ���
	@param[in]  pUserinfo ��˰����Ϣ
	@param[in]  strCurTime ��ǰʱ��YYYYMMDDHHMMSS
	@param[in]  Return_Info retInfo ���ؽ��
	@param[out]  construct  ����XML��
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, UINT32 nFpzs, UINT8 czlx, 
						string strFpmx, Return_Info *retInfo);

		
};

}
#endif



