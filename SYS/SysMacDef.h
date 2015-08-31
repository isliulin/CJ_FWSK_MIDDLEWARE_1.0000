#ifndef __LIB_SYSMACDEF_H
#define __LIB_SYSMACDEF_H

#include "VersionConfig.h"

#define CORP_NAME_LEN					80		
#define PAYER_NAME_LEN					80		

#define TAX_ID_NUM						6		//˰��˰Ŀ����
#define MAX_INV_ITEM_NUM				32
#define TAX_CODE_LEN					20		//��ҵ˰�ų���
#define GOODS_NAME_LEN					20		//��Ʒ���Ƴ���
#define GOODS_CODE_LEN					3//16		//��Ʒ���볤��
#define CLENT_CODE_LEN                  3           //�ͻ����볤��
#define INV_TAX_CTRL_CODE_LEN			20//32//8		//��Ʊ˰���볤��
#define INV_TYPE_CODE_LEN				6//10		//��Ʊ���볤��(BCD)
#define DAY_SUM_SIGN_LEN				128		//�ջ��ܵ���ǩ������hex
#define INV_VOL_MAC_LEN					4		//��Ʊ���þ���ϢMAC����
#define DECLARE_MAC_LEN					4		//�걨MAC(BCD)�ĳ���
#define DEC_SIGN_LEN					128		//�걨����ǩ������hex
#define OPERATOR_NAME_LEN				10		//����Ա���Ƴ���
#define SOFT_VER_LEN					18		//����汾����
#define HARD_VER_LEN					18		//Ӳ���汾����
#define FCARD_NO_LEN					8		//˰�ؿ����(BCD)����
#define FCARD_PWD_LEN					8		//˰�ؿ�����(BCD)����
#define CORP_NO_LEN						8		//��˰�˱���(BCD)����
#define MACHINE_NO_LEN					16		//�������(ASC)����
#define CORP_ADDR_LEN					100		//��ҵ��ַ����
#define CORP_PHONE_LEN					24		//��ҵ�绰����

#define CORP_SBH_LEN					30		//��˰��ʶ���
#define CORP_DZDAH_LEN					20		//��˰�˵��ӵ�����
#define CORP_HYDM_LEN					6		//��˰����ҵ����
#define CORP_HYMC_LEN                   200      //��˰����ҵ����
#define CORP_JYXMZWMC_LEN				200		//��˰�˾�Ӫ��Ŀ��������
#define CORP_SWJGDM_LEN					40		//��˰��˰����ش���
#define CORP_ZGSWGY_LEN					20		//��˰������˰���Ա
#define CORP_KPGLY_LEN					50		//��Ʊ����Ա
#define CORP_KPGLY_PWD_LEN				8		//��Ʊ����Ա����
#define CORP_KPMSMC_LEN					20		//��Ʊģʽ����

//��Ʊ������Ϣ
#define INV_KIND_CODE_LEN                20       //��Ʊ�������
#define INV_KIND_NAME_LEN                 70       //��Ʊ��������         

#define PRICE_EXTENSION					100 	//�۸�Ŵ���
#define SUM_EXTENSION					100		//���Ŵ���

#define NORMAL_INV						1		//������Ʊ
#define RETURN_INV						2		//���˷�Ʊ
#define WASTE_NOR						3       //����
#define WASTE_RET                       4       //����
#define WASTE_INV						5		//�հ�����
#define RET_MANUAL_INV                  6       //�����ֹ���Ʊ���˻���
#define	RET_SPECIAL_INV                 7       //�������ⷢƱ


#define SYSTEM_ADMINISTRATOR			1		//ϵͳ����Ա
#define DIRECTOR_OPERATOR				2		//���ܲ���Ա
#define NORMAL_OPERATOR					3		//��ͨ����Ա
#define DEMO_OPERATOR					4		//ѧϰ����Ա
#define SYSTEM_OPERATOR_ID				200		//ϵͳ����ԱID
#define DIRECTOR_OPERATOR_ID			0		//���ܲ���ԱID
#define DEMO_OPERATOR_ID				99		//ѧϰ����ԱID

#define PRINT_TEMPLATE_NUMBER			12		//��ӡģ�����
#define CLEAN_VOL_THRESHOLD             600

#define TRADE_NO_LEN					6		/**< ��˰����ҵ���� */
#define TRADE_NAME_LEN					40		/**< ��˰����ҵ����*/
//#define BANK_NO_LEN						50		/**< ���������ʺ� */
//#define BANK_NAME_LEN					80		/**< ������������ */
//#define INDUS_REG_NO_LEN				60		/**< ���̵ǼǺ� */
#define INDUS_REG_ADDR_LEN				100		/**< �Ǽ�ע���ַ */

//Ʊ����ӡ
#define SALE_REMARKS_LEN                     80  //��ע����
//#define SELF_DEF_TAB_LEN                   30  //�Զ����ǩ����
//#define SELF_DEF_CONT_LEN                  30  //�Զ������ݳ���

#define SERIAL_BAUDRATE						9600		//ת����ͨ�Ŵ��ڲ�����


/*! ������������ */
#define BOOT_NO_CARD					1
#define BOOT_CARD_NOT_MATCH				2
#define BOOT_FISCAL_PIN_ERR				3
#define BOOT_DAY_SUM_ERR				4
#define BOOT_NO_TEMPLATE				5
#define BOOT_INVALID_TEMPLATE			6
#define BOOT_CARD_ERR					7

/* printer .c .h ���貹�� (ZL) */
#define FORWARD_LINES			8			//ǰ����ֽ����
#define REPORT_LINE_SPACE		12			//�м��1
#define REPORT_LINE_SPACE2		5			//�м��2

//#define GOODS_CODE_LEN					16		//��Ʒ���볤��
#define MACHINE_NO_LEN					16		//�������(ASC)����
#define FKDW_NAME_LEN					PAYER_NAME_LEN		//���λ���Ƴ���
#define INV_GOODS_MAX_COUNT				6        //MAX_NUM_LIST_SINGLE ��Ʊ��Ʒ���������
#define TAX_ITEM_MAX_COUNT				6		//��ǰʹ�õ�˰��˰Ŀ������
#define TAX_ITME_CODE_LEN				4		//˰��˰Ŀ���볤��

/*��Ʒ��ϸ������*/
#define  DETAIL_GENERAL_GOODS			0	/* һ����Ʒ��					*/
#define  DETAIL_DISCOUNT				1	/* �ۿ���						*/
#define  DETAIL_GOODS_DISCOUNT			2	/* ���ۿ۵���Ʒ��				*/
#define  DETAIL_SERVICE_FEE				3	/* �������						*/
#define  DETAIL_EMPTY					4	/* ����							*/
#define  DETAIL_GOODS_REDUCT			6	/* �����õ���Ʒ��	            */
#define  DETAIL_REDUCTION_TEMPLATE		 5		/* ������			*/
#define  DETAIL_SERVICE_TEMPLATE		 4		/* �ӳ���			*/


//SYSLOG �¼�����
#define EVENT_DOWNLOAD_MACHINE_NO		0x00    /**< ���ػ������*/
#define EVENT_LOGIN_SYSTEM				0x01	/**< ��¼ϵͳ*/
#define EVENT_UPDATE_SYSTEM				0x02	/**< ����ϵͳ*/
#define EVENT_UPDATE_TEMPLATE			0x03	/**< ����ģ��*/
#define EVENT_POWER_OFF					0x04	/**< ����*/
#define EVENT_PULL_CARD					0x05	/**< �ο�*/
#define EVENT_ADD_OPERATOR				0x06	/**< ���Ӳ���Ա*/
#define EVENT_DEL_OPERATOR				0x07	/**< ɾ������Ա*/
#define EVENT_EDIT_OPERATOR				0x08	/**< �༭����Ա*/
#define EVENT_INVOICE_ROLL				0x09	/**< ��Ʊ��Ϣ����*/
#define EVENT_VOLUME_ROLL				0x0A	/**< ��Ʊ����Ϣ����*/
#define EVENT_SYSLOG_ROLL				0x0B	/**< ϵͳ��־����*/
#define EVENT_UPDATE_MACHINE_INFO		0x0C	/**< ���»�����Ϣ*/
#define EVENT_ILLEGAL_USER_CARD			0x0D	/**< �Ƿ��û���*/
#define EVENT_ILLEGAL_FISCAL_CARD		0x0E	/**< �Ƿ�˰�ؿ�*/
#define EVENT_ILLEGAL_MANAGE_CARD		0x0F	/**< �Ƿ�����*/
#define EVENT_ILLEGAL_PIN				0x10	/**< �Ƿ�PIN��*/
#define EVENT_INITIALIZATION			0x11	/**< ��ʼ��*/
#define EVENT_DISTRIBUTE				0x12	/**< ��Ʊ�ַ�*/
#define EVENT_MAKE_INVOICE				0x13	/**< ����Ʊ*/
#define EVENT_RTINV_ROLL				0x14	/**< ��Ʊ��Ϣ�����*/
#define EVENT_SET_TIME					0x15	/**< ����ʱ��*/
#define EVENT_DECLARE_TAX				0x16	/**< ��˰*/
#define EVENT_UPDATE_CORP				0x17	/**< ��˰*/
#define EVENT_CHECK_TAX					0x18	/**< ����*/
#define EVENT_UPDATE_USER_INFO			0x19	/**< �����û���Ϣ*/
#define EVENT_IMPORT_INVOICE			0x1A	/**< ��Ʊ����*/
#define EVENT_POWEROFF_INITMACH			0x1B	/**< ���籣������ʼ������*/
#define EVENT_POWEROFF_FPFF				0x1C	/**< ���籣������Ʊ�ַ�*/
#define EVENT_POWEROFF_FPDR				0x1D	/**< ���籣������Ʊ����*/
#define EVENT_POWEROFF_INV				0x1E	/**< ���籣������Ʊ*/
#define EVENT_POWEROFF_ROLL				0x1F	/**< ���籣��������*/
#define EVENT_POWEROFF_DECLARE			0x20	/**< ���籣������˰*/
#define EVENT_POWEROFF_PAY_TAX			0x21	/**< ���籣������˰*/
#define EVENT_MAKE_RET_INVOICE			0x22	/**< ����Ʊ*/
#define EVENT_MAKE_WAS_INVOICE			0x23	/**< ����Ʊ*/

#define EVENT_DATABASE_LOCKED			0x30	/**< ���ݿ�����*/
#define EVENT_DATABASE_PREPARE_ER		0x31	/**< ����sqlite3_prepare()����*/
#define EVENT_DATABASE_FILEDTYPE_ER		0x32	/**< sqlite3_bindʱ�д���*/
#define EVENT_DATABASE_STEP_ER			0x33	/**< ����sqlite3_step()����*/
#define EVENT_DATABASE_FINALIZE_ER		0x34	/**< ����sqlite3_finalize()����*/
#define EVENT_DATABASE_EXEC_ER			0x35	/**< sqlite3_exec()����*/


//������������ ���
#define PRODUCT_TYPE		0		/**< 1����������ֻ��1λ  0����������Ϊ2λ*/
#if PRODUCT_TYPE == 1
#define PRODUCT_TYPE_CODE                0x20       /**< ��������*/
#else
#define PRODUCT_TYPE_CODE_BYTE1                0x02       /**< �������� �ֽ�1*/
#define PRODUCT_TYPE_CODE_BYTE2          0x00       /**< �������� �ֽ�2*/
#endif
#define MACHINE_S_VER                    "0.0"       /**< ��������*/

//MAC��ַ���� ��� by yy 20120524
#define MAC_LEN	                 18	 /**< �洢MAC��ַ�Ļ��泤��*/


#define DAYSUM_LIMIT_DAYS       2000			/**< ��������Ʊ������*/
#define DEC_LIMIT_DAYS          100				/**< ���������걨�������*/
#define SG_MONEY_LMT            0XFFFFFFFFU     /**< ���ſ�Ʊ�޶�Ĭ��ֵ*/
#define ISSUE_END_DATE          20990101		/**< ��Ʊ��ֹ����Ĭ��ֵ*/
#define MAX_MONEY               0XFFFFFFFFU		/**< �������޶�*/
#define DEFAULTE_VOL_NUM        100           /**< ÿ��Ĭ�Ϸ�Ʊ�������ַ�����ʽ�����ڿؼ���ʾ��*/


//---������Ʊר�ã���Ʊ��ɣ�--//
#define OLD_HEAD_NUM                     32
#define OLD_INFO_NUM                     64
//---������Ʊר�ã���Ʊ��ɣ�--//

//----���Ϻ�̨ר��-----//
#define MAX_INV_VOL_NUM         100             /**< �����������*/
#define VOL_PYCODE              "301301"        /**< Ʊ������*/
//----���Ϻ�̨ר��-----//

//---�����˰��̨ר��----//
#define MAX_MESSAGE_NUM			10    /**< ��ʾ֪ͨ��Ϣ������ */

//ProgressBar����
#if (LANGCHAO_LIB == 0)
#define	BAR_DEF()			CaProgressBar info("")
#define	BAR_SHOW(x)			{info.SetText(x);info.Show();}
#else
#define	BAR_DEF()
#define	BAR_SHOW(x)
#endif

//---�����˰��̨ר��----//


#define ISSUE_TYPE  0 /**< 0 = �򵥰���Զ���Ʊ��1 = 15���������Ե��Զ���Ʊ*/
 
//#endif

//��¼���� ���
#define  INV_HEAD_DEL_MAX   3000//5000  /**< INV_HEAD����ʱɾ��������¼�� */
#define  INV_HEAD_MAX		20000//35000  /**< INV_HEAD��������������¼��	 */
#define  INV_SUM_DEL_MAX   500  /**< INV_SUM����ʱɾ��������¼�� */
#define  INV_SUM_MAX		1000  /**< INV_SUM��������������¼��	 */
#define  RT_INV_DEL_MAX   500  /**< RT_INV����ʱɾ��������¼�� */
#define  RT_INV_MAX		1000  /**< RT_INV��������������¼��	 */
#define  SYSLOG_DEL_MAX   2000  /**< SYSLOG����ʱɾ��������¼�� */
#define  SYSLOG_MAX		20000  /**< SYSLOG��������������¼��	 */

#define PLU_MAX        5000		/**< PLU��������������¼��	 */
#define CLIENT_MAX     50		/**< CLIENT��������������¼��	 */
#define OPERATOR_MAX   100		/**< OPERATOR��������������¼��	 */

//�����ƶ�ƽ̨�Ĵ�����
#define M2M_NO_INV        0x11 //�޷�Ʊ
#define M2M_EXCD_SV_TIME  0x13 //��������ʱ��
#define M2M_EXCD_SV_SUM   0x14 //����������
#define M2M_IMEI_LEN	16

//-----3G��� by yy 20120529
//3G��������
#define EVDO_CARD			1		//����
#define UNICOM_CARD			2		//��ͨ

#endif
