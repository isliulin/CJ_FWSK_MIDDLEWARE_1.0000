/*
 * ����ģ������ͷ�ļ�
 * ��������ģ�������������Ӧ�ù��̵ľ����������á�
*/

#ifndef	__H_NET_MODULE_CONFIG_
#define	__H_NET_MODULE_CONFIG_



//////////////////////////////////////////////////////////////////////////
//���뿪��
//////////////////////////////////////////////////////////////////////////
//���뷽ʽ
#define	_CONFIG_LAN_MODULE					1
#define	_CONFIG_ADSL_MODULE					1
#define	_CONFIG_3G_MODULE					1
#define	_CONFIG_M2M_MODULE					1
#define	_CONFIG_VPN_MODULE					0

//���䷽ʽ
#define	_TRANS_MODULE_CURL					0

//���߳�֧��
#define	_TRANS_THREAD_SUPPORT				1




//////////////////////////////////////////////////////////////////////////
//������
//////////////////////////////////////////////////////////////////////////

//Ĭ�ϴ��䷽ʽ
#define	TRANS_MODULE_DEF						TRANS_BY_TRANSPROC
#define	TRANS_APP_LAYER_DEF						APP_LAYER_HTTP
#define	TRANS_METHOD_DEF						SOCKET_TYPE
#define	TRANS_DATA_TYPE_DEF						DATA_IN_BUFF


//HTTPĬ��·��
#define SERVER_FILE_DEF						"/inside/ReceiveServlet"
#define SERVER_TIME							"/wlkpsl/servlet/TimeService"


//WMMP ��һЩĬ�ϲ���
#define WMMP_FLOW_DEFAULT						2
#define WMMP_TRANS_PACK_LEN						2048


//3G ��һЩĬ�ϲ���
#define _3G_AT_BUFF_LEN							512 



//SOCKET��һЩĬ�ϲ���
#define MAX_SOCKET_CONNECT_RETRY				7			//����SOCKET����ʧ��ʱ��������Դ���			
#define MAX_SOCKET_TRANS_RETRY					8			//SOCKETͨѶ����ʱ��������Դ���		
#define SOCKET_SEND_PACKLEN						2048		//ÿ��SOCKET���͵�������
#define SOCKET_RECV_PACKLEN						1024		//ÿ��SOCKET���յ�������



//�������ݷ���������Ƿ���һ��������	1-���û��棻0-�����û�����
#define SINGLE_TRANSBUFF_MODE					0


//Ĭ��ͨѶ�����С����ʹ��Ĭ�ϻ���ʱ����Ϊ1��
#define DEF_SENDBUFF_LEN					(1024*10)

#if (SINGLE_TRANSBUFF_MODE==0)
#define DEF_RECVBUFF_LEN					(1024*20)
#else
#define DEF_RECVBUFF_LEN						1		//��ģʽ���赥�����ý��ջ����С
#endif



//Ĭ�����ݴ���ʱ����ʱ�ļ�
#define	DEF_REQ_FILE						"XmlReqFile.xml"
#define	DEF_RSP_FILE						"XmlRspFile.xml"



//�����Ӳ��ԡ����ܵ�ִ�з�ʽ	1-SOCKET��ʽ	2-APP��ʽ������ݾ���Ӧ���޸�NetManageMenu.cpp�д��룩
#define TEST_CONNECT_TYPE						2			



//���ݴ����е�LOG����
#define	_DBG_PRINT_TRANSDATA					1


#endif


