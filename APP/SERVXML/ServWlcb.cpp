
/*! \file     ServWlcb.cpp
   \brief   ���糭���������忨����������
   \author   yy
   \version  1.0
   \date     2015 
*/



#include "ServWlcb.h"


#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"



CServWlcb::CServWlcb()
{
	DBG_PRINT(("����CServWlcb::CServWlcb()"));
	//-----------------------------------
	m_cssj = "";			/**< ��˰ʱ�� */
	m_islock = "";		/**< ��˰���Ƿ�Ϊ������(Y/N) */
	m_zqbs = "";			/**< �Ƿ�Ϊ���ڱ�˰ */
	m_hzxx = "";			/**< ������Ϣ�����ģ� */
	m_qkxx = "";			/**< �忨��Ϣ�����ģ�*/
	m_ssqrs = "";		/**< ���������� */
	m_fplxdm = "";
	
	DBG_PRINT(("�˳�CServWlcb::~CServWlcb()"));
}

CServWlcb::~CServWlcb()
{

}













