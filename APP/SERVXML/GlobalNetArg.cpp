
/*! \file     GlobalNetArg.cpp
   \brief   �����ֶ˽�����ȫ�ֱ���
   \author   yy
   \version  1.0
   \date     2015 
*/

#include "VersionConfig.h"
#include "commonFunc.h"
#include "GlobalNetArg.h"


#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

CGlobalNetArg* CGlobalNetArg::m_gNetArg = NULL;
CGlobalNetArg *g_gNetArg = NULL;



CGlobalNetArg::CGlobalNetArg()
{
	DBG_PRINT(("����CGlobalNetArg::CGlobalNetArg()"));
	//-----------------------------------
	m_nsrsbh = "";			/**< ��ҵ˰�� */
	m_fxsh = "";				/**< ����˰�� */
	m_hxsh = "";				/**< ��ϣ˰�� */
	m_kpjh = "";				/**< ��Ʊ���ţ�û�п�Ʊ����ʱֵΪ0 */
	m_sbbh = "";				/**< ˰���豸��� */
	m_slxlh = "";			/**< �������к� (ȡ��Ʊ�ϴ������)*/
	m_addrno = "";
	m_dcbb = "";
	m_servIP = "";
	m_servPort = "";
	m_servAddr = "";
	m_strzskl = "";
	
	DBG_PRINT(("�˳�CGlobalNetArg::CGlobalNetArg()"));
}

CGlobalNetArg::~CGlobalNetArg()
{
	if(m_gNetArg != NULL)
	{
		delete m_gNetArg;
		m_gNetArg = NULL;
	}
}

CGlobalNetArg* CGlobalNetArg::GetInstance()
{
	if (m_gNetArg == NULL)
	{
		m_gNetArg = new CGlobalNetArg();
	}

	DBG_RETURN(m_gNetArg);
}

//--------------------------------------------------
//��ʼ����������ֵ
//--------------------------------------------------
UINT8 CGlobalNetArg::InitGlobalNetArg(string nsrsbh, string fxsh, string hxsh,				
								string  kpjh, string sbbh,	string slxlh)			
{
	DBG_PRINT(("InitGlobalNetArg"));
	
	m_nsrsbh = nsrsbh;			/**< ��ҵ˰�� */
	m_fxsh = fxsh;				/**< ����˰�� */
	m_hxsh = hxsh;				/**< ��ϣ˰�� */
	m_kpjh = kpjh;				/**< ��Ʊ���ţ�û�п�Ʊ����ʱֵΪ0 */
	m_sbbh = sbbh;				/**< ˰���豸��� */
	m_slxlh = slxlh;			/**< �������к� (ȡ��Ʊ�ϴ������)*/

	DBG_PRINT(("�˳�InitGlobalNetArg����"));
	DBG_RETURN(SUCCESS);
}

void CGlobalNetArg::SetBaseInfo(string nsrsbh, string kpjh, string sbbh)
{
	m_nsrsbh = nsrsbh;			/**< ��ҵ˰�� */
	m_kpjh = kpjh;				/**< ��Ʊ���ţ�û�п�Ʊ����ʱֵΪ0 */
	m_sbbh = sbbh;				/**< ˰���豸��� */
}
void CGlobalNetArg::SetHashNo(string hxsh, string addrNo)
{
	m_hxsh = hxsh;				/**< ��ϣ˰�� */
	m_addrno = addrNo;
}
void CGlobalNetArg::SetIssueNo(string fxsh)
{
	m_fxsh = fxsh;
}
void CGlobalNetArg::SetDcbb(string dcbb)
{
	m_dcbb = dcbb;
}
void CGlobalNetArg::SetSlxlh(string slxlh)
{
	m_slxlh = slxlh;			/**< �������к� (ȡ��Ʊ�ϴ������)*/
}

void CGlobalNetArg::SetZskl(string zskl)
{
	m_strzskl = zskl;
}
void CGlobalNetArg::SetServId(string servId)
{
	m_servId = servId;
}
void CGlobalNetArg::SetNsrsbh(string nsrsbh)
{
	m_nsrsbh = nsrsbh;
}

void CGlobalNetArg::SetServPara(string servip, string servport, string servaddr)
{
	m_servIP = servip;
	m_servPort = servport;
	m_servAddr = servaddr;
}









