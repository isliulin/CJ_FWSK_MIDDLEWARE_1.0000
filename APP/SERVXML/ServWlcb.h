/*! \file     ServWlcb.h
   \brief   ���糭���������忨����������
   \author	  yy
   \version  1.0
   \date     2015 
*/

#ifndef __LIB_SERV_WLCB_H
#define __LIB_SERV_WLCB_H

#include "IncludeMe.h"
#include "SysMacDef.h"


class CServWlcb;




/**
 *@class CServWlcb 
 *@brief ���糭���������忨����������
 */
class CServWlcb
{
public:

	/**
	 * brief ��ʼ����������ֵ
	 * @param void
	 * @return UINT8 
	 */
// 	UINT8 InitGlobalNetArg(string nsrsbh, string fxsh, string hxsh,				
// 								string  kpjh, string sbbh,	string slxlh);
	


	//-----------------------------------
	// ������
	//-----------------------------------
	string  m_cssj;			/**< ��˰ʱ�� */
	string  m_islock;		/**< ��˰���Ƿ�Ϊ������(Y/N) */
	string  m_zqbs;			/**< �Ƿ�Ϊ���ڱ�˰ */
	string  m_hzxx;			/**< ������Ϣ�����ģ� */
	string  m_qkxx;			/**< �忨��Ϣ�����ģ�*/
	string  m_ssqrs;		/**< ���������� */
	string  m_fplxdm;		/**< ��Ʊ���ʹ��� */

	/**
	 * CServWlcb
	 * @return 
	 */
	CServWlcb();

	/**
	 * ~CServWlcb
	 * @return 
	 */
	~CServWlcb();
	
	
};





#endif
