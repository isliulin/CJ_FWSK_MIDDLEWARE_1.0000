/*! \file    YWXML_SKPXXCX.h
   \brief    ������õ��м���ӿ� ҵ��2.2.˰���豸��Ϣ��ѯ
   \author   YY
   \version  1.0
   \date     2015 
*/

#ifndef LIB_YWXML_SKPXXCX_H
#define LIB_YWXML_SKPXXCX_H


#include "IncludeMe.h"

#include "YWXmlBase.h"
#include "CUserInfo.h"

namespace middleware
{
/**
 *@class CSkpxxcx
 *@brief 2.2.˰���豸��Ϣ��ѯ
 */
class CSkpxxcx:  public CYWXmlBase
{


public:

	CSkpxxcx(XMLConstruct *construct, XMLParse *parse);
	~CSkpxxcx();
	
	INT32 Execute(); 


private:
	/*!
	@brief ˰���豸��Ϣ��ѯ�������������������XML�ļ���
	@param[in]  parse XML������
	@param[out]  strSksbkl  ˰���豸����
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlParse(XMLParse *parse);
	
	/*!
	@brief ˰���豸��Ϣ��ѯ�����������װ����װ��XML�ļ���
	@param[in]  pUserinfo ��˰����Ϣ
	@param[in]  strCurTime ��ǰʱ��YYYYMMDDHHMMSS
	@param[in]  retcode ���ش���
	@param[in]  retmsg ������Ϣ
	@param[out]  construct  ����XML��
	@return 1  SUCCESS�� 0  FAILURE
	*/
	INT32 XmlBuild(XMLConstruct *construct, CUserInfo *pUserinfo, string strCurTime, Return_Info *retInfo);

		
};

}
#endif



