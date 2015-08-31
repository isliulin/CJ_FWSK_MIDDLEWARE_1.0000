#ifndef __CGLOBAL_ARG_H
#define __CGLOBAL_ARG_H

#include "IncludeMe.h"
#include "SysMacDef.h"
#include "TDateTime.h"
#include "CInvVol.h"
#include "CUserInfo.h"
#include "CUserMore.h"
#include "CInvKind.h"
#include "JSKInfoFunc.h"
#include "CNetPara.h"

class CGlobalArgLib;

/*! ϵͳ���ò����������������Ӧ�ó�����һ�� */
extern CGlobalArgLib *g_globalArgLib;


/**
 *@class CGlobalArg 
 *@brief ����ȫ�ֱ�����ϵͳ����
 *@brief �����ڳ��������Ժ�ֻ�����һ��ȫ�ֶ���
 *@brief ����ĳ�Ա��������Ӧ�ó����õ�ȫ�ֱ�����ϵͳ������
 */
class CGlobalArgLib
{
public:

	/**
	 * brief ��ʼ����������ֵ
	 * @param void
	 * @return UINT8 
	 */
	INT32 InitGlobalArg();
	/**
	 * brief �����걨���ڵ���Ʊ����Ʊ�ۼƽ���Ʊ������Ʊ�ۼƽ��
	 * @param void
	 * @return UINT8 
	 */
	UINT8 CalculateSum(void);

	/*!
	*@brief �������ݿ����ݹ���
	)@param[out] nIfRolled �Ƿ�ʵʩ�˹������� 1���ǣ�0����
	*@return  1�� �ɹ��� ������ʧ��
	*/
	UINT8 RollData(UINT8 &nIfRolled);

	/**
	 * brief �õ�CGlobalArg��Ψһ����
	 * @param void
	 * @return static CGlobalArg* 
	 */
	static CGlobalArgLib* GetInstance(void);

	/**
	 * brief ��ʼ������ϵͳֵ
	 * @param void
	 * @return UINT8 
	 */
	UINT8 InitSysArg(void);

	
	//-----------------------------------
	// ϵͳ������
	//-----------------------------------
	UINT8  m_initFlag;			/**< ��ʼ����־ */
	UINT32 m_initDate;			/**< ������ʼ������ */
	UINT32 m_updateDate;		/**< ����Ȩ������ */
	UINT8  m_invDeliverFlag;	/**< ������־ */
	UINT8  m_decFlag;			/**< �걨��־ */
	UINT32 m_startDecDate;		/**< �걨��ʼ���� */
	UINT32 m_decDate;			/**< �걨��ֹ���� */

	UINT8  m_decMedium;			/**< �걨���� */
	//zcy edit ���ÿ������ȫ�ֱ���
	UINT32  m_perReccount;    /**< ÿ������*/

	UINT8  m_fjh;				//�ֻ���
	UINT8  m_netOn;            /**< ��¼��֤�Ƿ�ɹ� 1���ɹ���0��ʧ�� */
	UINT8  m_pthreadFlag;		/**< ���߳����б�־ 1������  0ֹͣ */
	string m_pthreadErr;		/**< ���̷߳��ش��� */
	string m_pthreadNsrsbh;
	string m_pthreadJqbh;
	string m_pthreadSksbbh;
	string m_pthreadSksbkl;
	string m_pthreadFplxdm;
	string m_pthreadKpjh;

	//-----------------------------------
	// �����޶������
	//-----------------------------------
	INT64  m_normalSum;			/**< �걨����Ʊ�ۼƽ�� */
	INT64  m_returnSum;			/**< �걨�ں�Ʊ�ۼƽ�� */
	INT64  m_normalVolSum;		/**< ��Ʊ����Ʊ�ۼƽ�� */
	INT64  m_returnVolSum;		/**< ��Ʊ���Ʊ�ۼƽ�� */
	
	//-----------------------------------
	// ����������
	//-----------------------------------
	UINT8		m_bootStatus;	/**< ����������״̬ */

	CInvVol		*m_curInvVol;	/**< ��ǰ����Ϣ */
	CUserInfo	*m_corpInfo;	/**< ��˰����Ϣ */
	CUserMore   *m_usermore;    /**< ��˰��������Ϣ*/
	CInvKind    *m_invKind;     /**< Ʊ����Ϣ*/
	CNetPara    *m_netPara;		/**< ������� */

	string		m_strSlxlh;			/**< �������к� */
	UINT32      m_InvServNum;        /**< ��ǰ���淢Ʊ���� */
	INT64       m_InvServSum;		/**< ��ǰ���淢Ʊ��� */
	string		m_strHashNo;		/**< ��ϣ˰�� */


	//-----------------------------------
	// ����������
	//-----------------------------------
	INT32 m_invCount;			/**< INV_HEAD��ĵ�ǰ��¼���� */
	INT32 m_rtInvCount;			/**< RT_INV��ĵ�ǰ��¼���� */
	INT32 m_invSumCount;		/**< INV_SUM��ĵ�ǰ��¼���� */

	INT32 m_clientCount;		/**< CLIENT��ĵ�ǰ��¼���� */
	INT32 m_operatorCount;		/**< OPERATOR��ĵ�ǰ��¼���� */
	INT32 m_pluCount;			/**< PLU��ĵ�ǰ��¼���� */

	
	//-----------------------------------
	// ˰���豸������
	//-----------------------------------
	UINT8   m_initParaFlag;		/**< ˰���豸������ʼ����־ */
	string	m_strSksbbh;		/**< ˰���豸��� */
	string	m_strSksbkl;		/**< ˰���豸���� */
	string	m_strBspbh;			/**< ��˰�̱�� */
	UINT32  m_serialBaudRate;	/**< ���ڲ����� */	
	string  m_strZskl;          /**< ֤����� */


private:
	/**
	 * CGlobalArg
	 * @return 
	 */
	CGlobalArgLib();

	/**
	 * ~CGlobalArg
	 * @return 
	 */
	~CGlobalArgLib();
	
	static CGlobalArgLib *m_globalArgLib;	/**< CGlobalArg���󣬾�̬ */
	
};



/*! ϵͳ���ò����������������Ӧ�ó�����һ�� */
extern CGlobalArgLib *g_globalArgLib;


#endif
