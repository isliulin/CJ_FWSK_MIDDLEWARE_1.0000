/*! \file     GlobalNetArg.h
   \brief   �����ֶ˽�����ȫ�ֱ���
   \author	  yy
   \version  1.0
   \date     2015 
*/

#ifndef __LIB_CGLOBAL_NET_ARG__H
#define __LIB_CGLOBAL_NET_ARG__H

#include "IncludeMe.h"
#include "SysMacDef.h"


class CGlobalNetArg;

/*! �����ֶ˽�����ȫ�ֱ������������Ӧ�ó�����һ�� */
extern CGlobalNetArg *g_gNetArg;


/**
 *@class CGlobalNetArg 
 *@brief �����ֶ˽�����ȫ�ֱ���
 *@brief �����ڳ��������Ժ�ֻ�����һ��ȫ�ֶ���
 *@brief ����ĳ�Ա��������Ӧ�ó����õ�ȫ�ֱ�����ϵͳ������
 */
class CGlobalNetArg
{
public:

	/**
	 * brief ��ʼ����������ֵ
	 * @param void
	 * @return UINT8 
	 */
	UINT8 InitGlobalNetArg(string nsrsbh, string fxsh, string hxsh,				
								string  kpjh, string sbbh,	string slxlh);
	
		/**
	 * brief ���û�����Ϣ
	 * @param void
	 * @return UINT8 
	 */
	void SetBaseInfo(string nsrsbh, string kpjh, string sbbh);
	/**
	 * brief ���ù�ϣ˰��
	 * @param void
	 * @return UINT8 
	 */
	void SetHashNo(string hxsh, string addrNo);
	/**
	 * brief ���÷���˰��
	 * @param void
	 * @return UINT8 
	 */
	void SetIssueNo(string fxsh);
	/**
	 * brief �ײ�汾
	 * @param void
	 * @return UINT8 
	 */
	void SetDcbb(string dcbb);
	/**
	 * brief �����������к�
	 * @param void
	 * @return UINT8 
	 */
	void SetSlxlh(string slxlh);

	/**
	 * brief ����֤�����
	 * @param void
	 * @return UINT8 
	 */
	void SetZskl(string zskl);
	void SetServId(string servId);
	void SetNsrsbh(string nsrsbh);
	/**
	 * brief ���÷������������
	 * @param void
	 * @return UINT8 
	 */
	void SetServPara(string servip, string servport, string servaddr);

	/**
	 * brief �õ�CGlobalArg��Ψһ����
	 * @param void
	 * @return static CGlobalArg* 
	 */
	static CGlobalNetArg* GetInstance(void);


	//-----------------------------------
	// ������
	//-----------------------------------
	string  m_nsrsbh;			/**< ��ҵ˰�� */
	string  m_kpjh;				/**< ��Ʊ���ţ�û�п�Ʊ����ʱֵΪ0 */
	string  m_sbbh;				/**< ˰���豸��� */

	string  m_fxsh;				/**< ����˰�� */
	string  m_addrno;			/**< ������� */
	string  m_hxsh;				/**< ��ϣ˰�� */
	string  m_dcbb;				/**< �ײ�汾 */
	
	string  m_slxlh;			/**< �������к� (ȡ��Ʊ�ϴ������)*/

	string  m_strzskl;			/**< ֤����� */
	string  m_servId;			/**< ������ID */
	string  m_servIP;
	string  m_servPort;
	string  m_servAddr;

private:
	/**
	 * CGlobalNetArg
	 * @return 
	 */
	CGlobalNetArg();

	/**
	 * ~CGlobalNetArg
	 * @return 
	 */
	~CGlobalNetArg();
	
	static CGlobalNetArg *m_gNetArg;	/**< CGlobalNetArg���󣬾�̬ */
	
};



/*! ϵͳ���ò����������������Ӧ�ó�����һ�� */
extern CGlobalNetArg *g_gNetArg;


#endif
