#ifndef __LIB_JSKINFODEF_H
#define __LIB_JSKINFODEF_H

#include <string.h>
#include "JSKInfoDef.h"
#include "VersionConfig.h"

#define MAX_SEND_BUFF_LEN	5*1024
#define MAX_BUFF_LEN	   10*1024


#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
#define PTHREAD_KPMUTEX_OPEN	0	//�̻߳���
#else
#define PTHREAD_KPMUTEX_OPEN	1	//�̻߳���
#endif

#define JSK_SUCCESS    0
#define JSK_FAILURE    -1

#define GET_CORP_INFO						0X01    //��ȡ��˰����Ϣ
#define GET_JSP_INFO                        0X02    //��ȡ��˰�̲�����Ϣ
#define GET_BSP_INFO                        0X15    //��ȡ��˰�̲�����Ϣ
#define GET_OFF_LIMIT_INFO					0X14    //��ȡ��˰�����߿��Ʋ���
#define JSP_PASSWORD_MANAGE				    0X16	//��˰��(֤��)�������
#define BSP_REGISTER                        0X17    //��˰��ע��
#define UPDATE_JSK_CLOCK                    0X18    //�޸Ľ�˰��ʱ��
#define UPDATE_CORP_INFO					0X03    //������ҵ��Ϣ
#define READ_CORP_INFO                      0X10    //��ȡ��ҵ��Ϣ
#define SET_UPLOAD_FLAG                     0X11    //���÷�Ʊ�ϴ�״̬
#define COPY_TAX_FUN						0X04    //��˰����
#define CLEAR_CARD_FUN						0X12    //�忨����
#define GET_NET_INVOL_INFO					0X05    //�����¹���Ʊ
#define GET_JSK_INVOL_INFO					0X06    //��ȡ��˰�̿��÷�Ʊ����Ϣ(����Ʊ��Ϣ��ѯ)
#define MAKE_INVOICE_FUN					0X07    //��Ʊ
#define INVOICE_WASTE_FUN					0X09    //�ѿ�Ʊ����
#define GET_CUR_INVIOCE_INFO				0X08    //��ȡ��ǰ��Ʊ����Ϣ
#define HOST_TO_INVVOL						0X0A    //������Ʊ
#define INVVOL_RET_INFO						0X0B    //��Ʊ�˻أ����ֻ�һ����
#define HOST_GET_INVVOL						0X0C    //��������ֻ��˻ط�Ʊ
#define GET_INVIOCE_INFO					0X0F    //��Ʊ��ѯ
#define GET_LOCK_DATE				    	0X19    //��������
#define GET_MONTH_COUNT_DATE				0X1A    //��ѯ��ͳ������


#define JSK_FP_JZLX_BSP			1			//��˰��
#define JSK_FP_JZLX_JSP			2			//˰���豸(��˰��)

#define NEWLINE_LEN      1
#define NEWLINE_COMMAND  "\n"
#define INVKIND_NAME  'c'

#define JSK_UPDATE_CLOCK                        7      //�޸Ľ�˰��ʱ�ӳ���
#define JSK_PASSWORD_LEN                        9      //��˰��ǰ����(9)
#define JSK_PASSWORD_SUM_LEN                    18      //��˰��ǰ����(9)+�¿���(9)
#define JSK_NET_GET_INV_LEN                     16      //���繺Ʊ������Ϣ
#define JSK_NET_INV_CON_LEN                     40      //���繺Ʊȷ����Ϣ����
#define JSK_NET_RUN_NO_LEN                      16      //������ˮ�ų���
#define JSK_FISCAL_CODE_LEN                     20      //˰���볤��           
#define JSK_SUM_INFO_LEN						320      //������Ϣ����
#define JSK_COPY_TAX_INFO_LEN					320      //��˰��Ϣ����
#define JSK_CLEAR_CARD_INFO_LEN                 128      //�忨��Ϣ����
#define JSK_NET_CRYP_DATA_LEN					144      //ͨ������Ӻ�̨��ȡ�ĵ��ӷ�Ʊ���ݰ������ģ�����
#define JSK_RUN_NO_LEN                          16      //��ˮ�ų���
#define JSK_NO_LEN								16      //��˰/��˰�̺ų���
#define JSK_HASH_NO_LEN							24      //��ϣ˰�ų���
#define JSK_ADDR_NO_LEN							 8     //������ų���
#define JSK_PZ_NO								 2      //Ʊ�ָ���
#define JSK_QUERY_DATE_LEN                       6      //��ѯ��Ʊ�������ڳ���
#define JSK_OTHER_INFO_LEN						500		//������Ϣ����
#define JSK_LXXXMW_LEN							512		//������Ϣ���ĳ���
#define JSK_GPXXMW_LEN							256		//��Ʊ��Ϣ���ĳ���
#define JSK_ISSUE_NO_LEN						15		//����˰�ų���
#define JSK_MAX_JQBH_LEN						12		//˰���տ��������ų���
#define JSK_MAKE_INV_SIGN_LEN					1024		//��Ʊǩ������


#define INVVOL_MAX_NUM  100            //��Ʊ���������
#define INVKIND_MAX_NUM 10              //��Ʊ�����������
#define MAX_TAX_NUM		20			//���˰�ʸ���

#define MAX_SKSBBH_LEN		12			//˰���豸��ų���
#define MAX_SKSBKL_LEN		8			//˰���豸�����
#define MAX_NSRSBH_LEN		20			//��˰��ʶ��ų���
#define MAX_NSRMC_LEN		80			//��˰�����Ƴ���
#define MAX_SWJGDM_LEN		11			//˰����ش��볤��
#define MAX_FPLXDM_LEN		3			//��Ʊ���ʹ��볤��
#define MAX_FPDM_LEN		12			//��Ʊ���볤��
#define MAX_SKM_LEN			20			//˰���볤��
#define MAX_VER_LEN			10			//�汾�ų���
#define MAX_DATETIME_LEN	14			//ʱ�䳤��
#define	MAX_KPJH_LEN		5			//��Ʊ���ų���
#define MAX_PWD_LEN			18			//��˰��ǰ����(9)+�¿���(9)

#define MAX_INV_INFO_LEN	1024*4		//��Ʊ��ϸ���ݳ���

#define CA_SIGN_BASE64		1

//��ϣ˰�ų���
#define HASH_NO_FLAG_16		1			//��ҵ�������ء����糭��
#define HASH_NO_FLAG_24		2			//��Ʊ������/�����ӿ�

#define DEFAULT_FPLB_NO		41
#define FPLX_NO_1			41
#define FPLX_DM_1			"025"

#define MIDDLEWARE_SAVE_DB		1

//2.25.˰���豸������Ϣ��ѯ��Ϣ���Ͷ���
#define SKSBQTYXXCX_XXLX_WLCB			0
#define SKSBQTYXXCX_XXLX_QLJS			1
#define SKSBQTYXXCX_XXLX_LXXXSC			2
#define SKSBQTYXXCX_XXLX_WLLQFP			3
#define SKSBQTYXXCX_XXLX_WLLQFPJGQR		4
#define SKSBQTYXXCX_XXLX_FPSCJGHQ		5

//˰���̱�˰����ϲ������Ͷ���
#define SKPBSP_CZLX_SJCB		1	//���ݳ���
#define SKPBSP_CZLX_QLJS		2	//�������
#define SKPBSP_CZLX_FXGPXX		3	//��д��Ʊ��Ϣ
#define SKPBSP_CZLX_JZSZ		4	//У׼˰���豸ʱ��

#define MAX_ERR_MSG_LEN			200

#define JSK_COMMON_ERR_NO		-101
#define JSK_COMMON_ERR_CODE		"-101"

#define JSK_NORMAL_INV						1		//������Ʊ--��ӦNORMAL_INV
#define JSK_RETURN_INV						2		//���˷�Ʊ--��ӦRETURN_INV
#define JSK_WASTE_NOR						3       //����--��ӦWASTE_NOR
#define JSK_WASTE_RET                       4       //����--��ӦWASTE_RET
#define JSK_WASTE_INV						5		//�հ�����--��ӦWASTE_INV


#define JSK_DETAIL_BUF_LEN            4*1024     //�洢��Ʒ��ϸ���ݳ���
#define JSK_SPMC_LEN					92		//��Ʒ���Ƴ���
#define JSK_GGXH_LEN					40		//����ͺų���
#define JSK_JLDW_LEN                    22          //������λ����
#define JSK_SPSL_LEN					21		//����������18�����21������
#define JSK_SPDJ_LEN					21		//���ۣ�����18�����21������
#define JSK_SPJE_LEN					18		  //������2λС�������18��
#define JSK_SL_LEN						6		//˰�ʣ�6������
#define JSK_SE_LEN						18		//˰�����2λС�������18������
#define JSK_SPXH_LEN					8		//��ţ�8������
#define JSK_FPXZ_LEN				    3		//��Ʊ�����ʣ�3������
#define JSK_HSBZ_LEN				    3		//��˰�۱�־��3������

#define JSK_SUM_EXTENSION					100		//���Ŵ���

//Ȩ����Ϣ
typedef struct _TInvSixLimit
{
	UINT8 invName;						/*Ʊ��*/
	UINT8   invLimit[6];					/*���ŷ�Ʊ�޶� */
    UINT8  OffLinePosTotalLimit[6];		/*����������Ʊ�ۼ��޶�*/			
} __attribute__ ((packed)) TInvSixLimit;

typedef struct _TInvAuthLimitInfo
{
	UINT8 invNum;						/* Ʊ����*/
	TInvSixLimit InvSixLimit[10];
}__attribute__ ((packed)) TInvAuthLimitInfo;


typedef struct _TOffLimintInfo
{	
	UINT8 OffLineLockDay;	    /*����������(ÿ�µĵڼ���)*/
    UINT32 OffLineInvTime;	   /*���߿���ʱ�� ��λСʱ*/
	TInvAuthLimitInfo AuthLimitInfo;    /*���߿��Ʋ���*/

}__attribute__ ((packed)) TOffLimintInfo;

/*
��8����ȡ��һ�ŷ�Ʊ���߷�Ʊ�ķ�Ʊ���롢��Ʊ����ͷ�Ʊ������
���룺����pp2=7��
              INBUFF[] ����
�����OUTBUFF��16�ֽڷ�Ʊ���루10��12λASCII�룩+4�ֽڷ�Ʊ����+4�ֽڷ�Ʊ������
*/

typedef struct _TFirstOffInvInfo
{
	INT8   InvCode[16];			    /* ��Ʊ���� */
	UINT32  InvNo;					/* ��Ʊ���� */
	UINT8 InvIndex[4];               /* ��Ʊ������*/

}__attribute__ ((packed)) TFirstOffInvInfo;


typedef struct _TaxCardInfo
{	
	UINT8 CorpName[100];					/* ��ҵ���� */
	UINT8 KPNo[2];  /*��Ʊ���ţ�����������ʶ��ӵ�еķֻ��������ڷֻ�����ʶ�ֻ���*/
	UINT8 zfFlag;							/*���ֻ���־ 0�������� 1����ֻ� */
	UINT8 CorpPorpertiy;					/*��˰����ҵ���� ����0��ʾһ����˰�ˣ�����1��ʾС��ģ��˰��*/
	UINT8 CorpType;							/*��ҵ���� ����0��ʾ���ض���ҵ������1��ʾ�ض���ҵ*/
	UINT8 ResignNo[50];						/*���̵ǼǺ�*/
	UINT8 DepositBank[100];					/*��������*/
	UINT8 DepositAccount[50];				/*�����˺�*/
	UINT8 ResignAddress[100];				/*�Ǽ�ע���ַ*/
	UINT8 TaxAuthorityNo[20];				/*����˰����ش���*/
	UINT8 TaxAuthorityName[100];			/*����˰���������*/
	UINT8  TaxCode[25];						/* ��ҵ��˰��ʶ���*/
    UINT8  AuthTaxRate[21]; /*˰����Ȩ,��1�ֽڱ�ʾ��Ȩ˰�ʸ�������2�ֽڿ�ʼΪ��Ȩ����Ʊ˰�ʣ�
						����:��˰��������17%��3%����˰����Ȩ����AuthTaxRate��ǰ3�ֽڱ�ʾΪ0x02 0xA0 0x1E�������ֽ��������0*/
    UINT8 invName[11]; /*��Ʊ����, ��1�ֽڱ�ʾ��Ʊ���͸�������2�ֽڿ�ʼΪ��Ʊ����*/
}__attribute__ ((packed)) TaxCardInfo;


/*
Case 0x09���ѿ���Ʊ����
���룺pp2=0��
INBUFF �� 9�ֽ�֤����9�ַ�������Ȳ���9���������0������"88888888"�� + �ṹ��TaxCardInvCancel
�����OUTBUFF�� 2�ֽ�ǩ������+ǩ������+4�ֽڷ�Ʊ������+7�ֽ��������ڣ�BCD��7�ֽڣ�����0x20 0x15 0x04 0x13 0x19 0x46 0x00��
*/

typedef struct _TaxCardInvCancel
{
	INT8    TypeCode[16];		/*10��12λASCII�뷢Ʊ����*/
	UINT32  InvNo;				/*��Ʊ����*/   
	UINT8 Type;					/*��Ʊ����*/
	UINT8 invFlag;				/*��Ʊ��־�����ϡ�����*/
	INT8    InvAcess[4];	/*��Ʊ������*/
		
}__attribute__ ((packed)) TaxCardInvCancel;


typedef struct _TInvCancel
{

  INT8   CAPassW[9];       /*ca����*/
  TaxCardInvCancel  taxCardInvCancel;
		
}__attribute__ ((packed)) TInvCancel;


/*
Case 0x04����˰�����淶"���ݳ���"��
���糭˰
���룺����pp2=0��
	  INBUFF 1�ֽڷ�Ʊ����
�����OUTBUFF  7�ֽڳ�˰��ʼʱ�䣨BCD��ʽ��
����0x20 0x15 0x04 0x13 0x19 0x46 0x00��
+7�ֽڳ�˰����ʱ�䣨BCD��ʽ������0x20 0x15 0x04 0x13 0x19 0x46 0x00��
+��˰������Ϣ320B�����ģ���
*/

typedef struct  _TNetCopyTax
{
    UINT8 StartDate[7];			/*��˰��ʼʱ�� */
    UINT8 EndDate[7];			/*��˰����ʱ�� */
    UINT8 CopyTax[JSK_SUM_INFO_LEN];			/*��˰������Ϣ*/
}__attribute__ ((packed)) TNetCopyTax;


/*
Case 0x06����ȡ����ƱԴ��Ϣ
���룺����pp2=0 
�������Ʊ����Ϣ  ǰ���ֽڣ�word������ +�ṹ��*���� 
����ṹ��InvVolume

  ��ʽ����Ʊ���1-ר�÷�Ʊ 2-��ͨ��Ʊ
  ��Ʊ��ʼ�ţ�123     HeadCode=123;
  ��Ʊ���룺1100102140   10/12λ��Ʊ����  TypeCode="1100102140";
  
*/
typedef struct  _TInvVolume
{
	UINT8 Type;		 /*��Ʊ���*/
	UINT32  HeadCode;	 /*��Ʊ��ʼ��*/
	UINT16  Count;   /*���� */
	UINT16  Remain;  /*ʣ�����*/
    UINT8 BuyDate[7];	 /*��������BCD,����0x20 0x15 0x04 0x13 0x19 0x46 0x00*/
	INT8 TypeCode[16]; /*��Ʊ����10��12λASCII��*/

}__attribute__ ((packed)) TInvVolume;


typedef struct  _TInvVol
{

	UINT16 InvNum;  /*���ֽڣ�word������*/
    TInvVolume InvVolum[5];  /* �ṹ��*����*/

}__attribute__ ((packed)) TInvVol;



/*
�������繺Ʊ
���룺����pp2=1 
�����OUTBUFF[32] 16B���繺ƱԤ��Ȩ��Ϣ�����ģ�+16B���繺Ʊ��ˮ�ţ�
*/
typedef struct  _TNetInvVolInfo
{
    UINT8 netEmpowInfo[16];			/*���繺ƱԤ��Ȩ��Ϣ�����ģ� */   
}__attribute__ ((packed)) TNetInvVolInfo;

/*
���繺Ʊ����ȷ������
���룺����pp2=3 
�����OUTBUFF 52�ֽڽ�˰�����繺Ʊ����ȷ�����ݰ�
��12�ֽ����ģ�Ʊ��1+����4+����2+����5��+40�ֽ�����
*/
typedef struct  _TJSPNetInvVol
{
	UINT8 Type;		      /*��Ʊ���*/
	UINT32  InvNO;	      /*��Ʊ��ʼ��*/
	UINT16  Count;        /*���� */
	INT8 TypeCode[5];     /*��Ʊ����6*/
	UINT8 NetInvInfo[40]; /*��˰�����繺Ʊ����ȷ������*/
}__attribute__ ((packed)) TJSPNetInvVol;



/*
Case 0x07����Ʊ
����ṹ�� TaxCardInvHead
���룺pp2=0��������Ʊ����
      pp2=1���հ����ϣ�
      INBUFF �� 9�ֽ�֤����9�ַ�������Ȳ���9���������0������"88888888"�� + �ṹ��TaxCardInvHead
	  
�����OUTBUFF��2�ֽ����ĳ���+����data+'\0'+4�ֽڷ�Ʊ������+2�ֽ�ǩ������+ǩ������
��ʽ����Ʊ���룺1100102140   10/12λ��Ʊ����  TypeCode="1100102140"
      ��Ʊ���룺87654321  InvNo=87654321
      ����˰�ţ�14030100DK01232   20λ����˰�� BuyTaxCode="14030100DK01232"����Ϊ��
      ��� 99.5  TotalSum=9950��
      ˰�� 17.5   Tax=1750��
      ��Ʊ��� 1-ר�÷�Ʊ 2-��ͨ��Ʊ
*/

typedef struct _TaxCardInvHead
{
	INT8   TypeCode[16];			 /*10��12λASCII�뷢Ʊ����*/
	UINT32  InvNo;					 /*��Ʊ����*/   
	UINT8 Date[7];                   /* ��Ʊ���ڣ�BCD,����0x20 0x15 0x04 0x13 0x19 0x46 0x00*/
	INT8 BuyTaxCode[21];			 /*����˰��*/
	INT8 TotalSum[20];    /*���հ׷Ͻ��Ϊ0*/  
 	INT8 Tax[20];        /*˰��*/
	UINT8 Type;       /*��Ʊ����*/
	UINT8 invFlag;    /*��Ʊ��־���������������հ׷�*/
	INT8 NegToPosTypeCode[16];   /*������Ʊ��Ӧ��������Ʊ�ĺ���*/
    UINT32 NegToPosInvNo;   /*������Ʊ��Ӧ��������Ʊ�Ĵ���*/	
	UINT32 DataLen;  /*���浽��˰�����Զ��巢Ʊ���ݳ���*/
	UINT8 *DataPtr; /*��Ʊʱд���˰���з�Ʊ���ݻ�����*/
					/*�ѿ���Ʊ����ʱΪ�ѿ���Ʊ�ķ�Ʊ����*/	
}__attribute__ ((packed)) TaxCardInvHead;

typedef struct _TInvHead
{
	INT8   CAPassW[9];			    /*9�ֽ�֤�����*/
	TaxCardInvHead taxCardInvHead;   /*��Ʊ������Ϣ*/
	
}__attribute__ ((packed)) TInvHead;


/*
Case 0x08����ȡ��ǰ��Ʊ��
���룺pp2=0��
���:  16B��Ʊ���루�ַ�����ʽ��+4�ֽڷ�Ʊ���루dword�������ݣ�+1�ֽڷ�Ʊ���
��ʽ����Ʊ���룺1100102140   10/12λ��Ʊ����  "1100102140"
      ��Ʊ���룺87654321
	  ��Ʊ���1=��ֵ˰ר�÷�Ʊ��2=��ֵ˰��ͨ��Ʊ
*/
typedef struct _TCurInvInfo
{
	INT8   InvCode[16];			    /* ��Ʊ���� */
	UINT32  InvNo;					/* ��Ʊ���� */
	INT8    Type;                   /* ��Ʊ���*/
	UINT16  Remain;					/*ʣ�����*/

}__attribute__ ((packed)) TCurInvInfo;

/*
Case 0x0f����Ʊ��ѯ

���ݷ�Ʊ����+��Ʊ����+�����ţ���ѡ����ѯ��Ʊ
���룺����pp2=0��
     INBUFF[24]  unsigned int��Ʊ��ʼ��;16B��Ʊ����; 
	 unsigned int��Ʊ�����ţ���ѡ�����ϲ����ݿ��޴��ֶΣ����4�ֽ�0xFF��
 
 ��������ŷ�Ʊ��ϸ������ṹ�� TInvDetail
*/

typedef struct _TQueryInfo
{
	UINT32  InvNo;					/* ��Ʊ���� */
	INT8   InvCode[16];			    /* ��Ʊ���� */
	UINT8 InvIndex[4];               /* ��Ʊ������*/

}__attribute__ ((packed)) TQueryInfo;

/*
3�����繺Ʊ����ȷ�����루��ѯ����Ʊ�Ѽ���δ����״̬��
���룺����pp2=3 
INBUFF  1�ֽ�Ʊ������
�����OUTBUFF 63�ֽڽ�˰�����繺Ʊ����ȷ�����ݰ���40�ֽ����ģ����ڹ淶��3.7�����������+23�ֽ����ģ�Ʊ��1+����4+����2+����16������
�����˰������������δ���������繺Ʊ��Ʊ����Ϣ��������س���0�� 
*/

typedef struct _TApp2NetInfo
{
	UINT8  NetInvInfo[40];             /*40�ֽ�����*/
	UINT8  InvType;                /*Ʊ��*/
	UINT32  InvNo;					/* ��Ʊ���� */
	UINT16 Count;                  /* ��Ʊ����*/
	INT8   InvCode[16];			    /* ��Ʊ���� */

}__attribute__ ((packed)) TApp2NetInfo;

/*
Case 0x0f����Ʊ��ѯ

      �������²�ѯָ���·ݵķ�Ʊ���˽ӿ�ÿ�η���һ�ŷ�Ʊ����ϸ����ѯָ���·ݵ�ȫ����Ʊ��ѭ�����ô˽ӿڣ�
���룺����pp2=1��
              INBUFF[6]  unsigned int��; unsigned short �¡� 
�����1�ֽڽ��պ�����Ʊ��־������1��ʾ�к�����Ʊ��Ҫ���գ�����0��ʾ�ޣ�+���ŷ�Ʊ��ϸ������ṹ��

*/
typedef struct _TDateQueryInfo
{
	UINT32  InvYear;					/* �� */
	UINT16  InvMonth;			    /* �� */

}__attribute__ ((packed)) TDateQueryInfo;

typedef struct _TInvDetail
{
	INT8    TypeCode[16];	    /*10��12λASCII�뷢Ʊ����*/
	UINT32     InvNo;			/*��Ʊ����*/   
	UINT8     Date[7];       /* ��Ʊ����*/
	INT8      BuyTaxCode[21];		/*����˰��*/
	INT8 TotalSum[20];    /*���*/  
	INT8 Tax[20];   		/*˰��*/
	UINT8 Type;					/*��Ʊ���*/
	UINT8 invFlag;    /*��Ʊ��־�����������������ϡ����ϡ��հ׷�*/	
	UINT32 DataLen;  /*��Ʊ���ݳ���*/
	UINT8 *DataPtr; /*��Ʊ������ϸ*/
    UINT32 SignLen; /*ǩ������*/
    UINT8 *SignPtr; /*ǩ������*/
	INT8    CheckCode[21];		 /*20λУ���� */
	UINT8 Adress[4];   /*��Ʊ������ */ 
	UINT8   UpFlag;      /*��Ʊ�ϴ���־��1-���ϴ���0-δ�ϴ�*/

}__attribute__ ((packed)) TInvDetail;

//typedef struct _TInvRecover
//{
//	UINT8 invNum;				/*�޸�����*/
//	TInvDetail InvDetail[2];   /*��Ʊ��ϸ*/
// }__attribute__ ((packed)) TInvRecover;


/*
Case 0x0a��������Ʊ

 (1).���ֻ���˰�̷�Ʊ
���룺����pp2=0��
      INBUFF[22]  unsigned int��Ʊ��ʼ��;16B��Ʊ����;unsigned short��Ʊ���� 
�������

(2).���ֻ���˰�̷�Ʊ
���룺����pp2=1��
      INBUFF[22]  unsigned int��Ʊ��ʼ��;16B��Ʊ����;unsigned short��Ʊ���� 
�������

��ʽ����Ʊ��ʼ�ţ�123   
      ��Ʊ���룺1100102140   10/12λ��Ʊ����  "1100102140"
  */

typedef struct  _THostToInv
{
	UINT32  InvNo;					/* ��Ʊ���� */
	INT8   InvCode[16];			    /* ��Ʊ���� */
	UINT16   InvNum;				/* ��Ʊ����*/
	UINT8    InvType;               /* ��Ʊ����*/
	
}__attribute__ ((packed)) THostToInv;


/*
Case 0x0b����Ʊ�˻أ����ֻ�һ����

(1).�ñ�˰���˻�
���룺����pp2=0��
      INBUFF[22]  unsigned int��Ʊ��ʼ��;16B��Ʊ����; unsigned short��Ʊ���� 
�������
(2).�ý�˰���˻�
���룺����pp2=1��
      INBUFF[22]  unsigned int��Ʊ��ʼ��;16B��Ʊ����; unsigned short��Ʊ���� 
�������

��ʽ����Ʊ��ʼ�ţ�HeadCode=123    
      ��Ʊ���룺1100102140   10/12λ��Ʊ����  "1100102140"

  */

typedef struct  _TInvRetInfo
{
	UINT32  InvNo;					/* ��Ʊ���� */
	INT8   InvCode[16];			    /* ��Ʊ���� */
	UINT16   InvNum;				/* ��Ʊ����*/
	UINT8    InvType;               /* ��Ʊ����*/
	
}__attribute__ ((packed)) TInvRetInfo;


typedef struct _TClearCardInfo
{
	UINT8 Type;						/* Ʊ������*/
	INT8 CCardInfo[128];            /* 128�ֽ��忨����*/
}__attribute__ ((packed)) TClearCardInfo;

/*
Case 0x1A����ѯ��ͳ������
���룺����pp2=0��
INBUFF�� 2�ֽ���ݣ�WORD���ͣ�+2�ֽ��·ݣ�WORD���ͣ�
�����1�ֽڷ�Ʊ��������N+N����ͳ�����ݽṹ��TInvCount 
��ʽ��
������Ʊ���߷�����100�ţ�InvNum=100
֤�鷢Ʊ�ۼƽ�� 99.5  InvSum="99.50"
*/
typedef struct  _TInvCount
{
	UINT8 	    Type;       			/*��Ʊ����*/
	UINT32	    OpenInventory;			/*�ڳ����*/  
	UINT32     	NewBuy; 				/*�����¹�*/ 
	UINT32     	EndInventory; 			/*��ĩ���*/
	UINT32     	ReBack; 				/*�����˻�*/
	UINT32     	InvNum; 			    /*������Ʊ���߷���*/
	UINT32      InvCancelNum; 		    /*������Ʊ���Ϸ���*/
	UINT32      NegInvNum; 			    /*������Ʊ���߷���*/
	UINT32      NegInvCancelNum; 		/*������Ʊ���Ϸ���*/
	INT8     	InvSum[20]; 			/*������Ʊ�ۼƽ��*/
	INT8     	InvTax[20]; 			/*������Ʊ�ۼ�˰��*/
	INT8     	NegInvSum[20]; 			/*������Ʊ�ۼƽ��*/
	INT8     	NegInvTax[20]; 			/*������Ʊ�ۼ�˰��*/
	
}__attribute__ ((packed)) TInvCount;


typedef struct  _TSumInvCount
{
	UINT8 uTypeNum;
	TInvCount invCount[8];

}__attribute__ ((packed)) TSumInvCount;


typedef struct  _TFpmx
{
	
	INT8 Fpmc[JSK_SPMC_LEN];			    /*��Ʒ���ƣ�92��*/ 
	INT8 Ggxh[JSK_GGXH_LEN];			    /*����ͺţ�40��*/ 
	INT8 Jldw[JSK_JLDW_LEN];				/*������λ��22��*/ 
	INT8 Spsl[JSK_SPSL_LEN];				/*����������18�����21��*/ 
	INT8 Spdj[JSK_SPDJ_LEN];				/*���ۣ�����18�����21��*/ 
	INT8 Spje[JSK_SPJE_LEN];				/*������2λС�������18��*/ 
	INT8 SL[JSK_SL_LEN];				    /*˰�ʣ�6��*/ 
	INT8 SE[JSK_SE_LEN];				    /*˰�����2λС�������18��*/ 
	INT8 Spxh[JSK_SPXH_LEN];				/*��ţ�8��*/ 
	INT8 Fpxz[JSK_FPXZ_LEN];				/*��Ʊ�����ʣ�3��*/ 
	INT8 Hsbz[JSK_HSBZ_LEN];				/*��˰�۱�־��3��*/
}__attribute__ ((packed)) TFpmx;


typedef struct  _TFpmxSum
{
    TFpmx fpmx[6];     /* �ṹ��*/

}__attribute__ ((packed)) TFpmxSum;



#endif


