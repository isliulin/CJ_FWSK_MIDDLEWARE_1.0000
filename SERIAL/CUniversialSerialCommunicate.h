#ifndef _UNIVERSAL_SERIAL_COMMUNICATION_H
#define _UNIVERSAL_SERIAL_COMMUNICATION_H

#include <string>
#include <string.h>
#include <stdio.h>
#include "StructDesign.h"
#include "SerialProtocol.h"
#include "ManageBusinessFunc.h"
#include "SaleBusinessFunc.h"
#include "InvBusinessFunc.h"
#include "DeclareBusinessFunc.h"
#include "YWXMLGY.h"
#include "selfTest.h"

using namespace std;

class CUniversialSerialCommunicate {
private:
	UINT8 ret;

	CManageBusinessFunc manageFunc;
	CSaleBusinessFunc saleFunc;
	CDeclareBusinessFunc decFunc;
	CInvBusinessFunc invFunc;

	string sksbbhstr;
	string bspbhstr;
	string qtxx;
	string strErr;

	SerialProtocol* m_serialProtocol;
	//��������
	UINT8 onLine();
	//˰���̱�Ų�ѯ
	UINT8 skpbhcx();
	//��˰�̱�Ų�ѯ
	UINT8 bspbhcx();
	//˰������Ϣ��ѯ
	UINT8 skpxxcx();
	//��˰����Ϣ��ѯ
	UINT8 bspxxcx();
	//������ݲ�ѯ
	UINT8 jksjcx();
	//��Ȩ˰�ʲ�ѯ
	UINT8 sqslcx();
	//��Ʊ��Ϣ��ѯ
	UINT8 gpxxcx();
	//�������
	UINT8 sksbklgg();
	//��Ʊ����
	UINT8 fpkj();
	//��Ʊ����
	UINT8 fpzf();
	//��Ʊ��ѯ
	UINT8 fpcx();
	//˰���̱�˰����ϲ���
	UINT8 skpbspzhcz();
	//��˰�̷�Ʊ��ѯ
	UINT8 bspfpcx();
	//��Ʊ�ַ�
	UINT8 fpff();
	//��Ʊ����
	UINT8 fphs();
	//���ݳ���
	UINT8 sjcb();
	//�����ػش�
	UINT8 wljkhc();
	//��Ʊͳ����Ϣ��ѯ
	UINT8 fptjcx();
	//��ҵ��Ϣ����
	UINT8 qyxxgx();
	//����Ȩ�޸���
	UINT8 lxqxgx();
	//��Ʊʵʱ�ϴ�
	UINT8 fpsssc();
	//�������ά��
	UINT8 wlcswh();
	//���ô��ڲ�����
	UINT8 setBaudRate();
	//��Ʊ����
	UINT8 fpdr();
	//�ֻ��˻�
	UINT8 fjth();
	//���繺Ʊ
	UINT8 wlgp();
	//֤��������
	UINT8 zsklgg();
	//��Ʊ��¼
	UINT8 fpbl();
	//��ȡ�����������
	UINT8 hqlxsj();
	//ת�������
	UINT8 zhqqk();
	//��ȡ�ϴ�����Ʊ��Ϣ
	UINT8 getErrUpInv();
	//��ȫͨ�����Ӳ���
	UINT8 sslConnectTest();

    //Ӧ������
	UINT8 programUpdate();
	//ϵͳ�Լ�
	UINT8 sysTest();
	//��дMAC
	UINT8 writeMAC();
	//��д�������
	UINT8 writeMachineNo();

	//����IP��ַ����
	int ifConfig(const char *ifname,  const char *ipaddr,const char *netmask, const char *gwip, const char *dns);
	int getLocalIP();
	int if_a_string_is_a_valid_ipv4_address(const char *str);

	void FilterSpace(string &str);
public:
	CUniversialSerialCommunicate();
	~CUniversialSerialCommunicate();

	UINT8 handleSerialCMD();
	int setNetWork(unsigned char isdhcp, const char *ipaddr, const char *netmask, const char *gwip, const char *dns);
};

#ifndef WIN32
//------�߳����--------//
void * PthreadInvUpLoad(void *arg);
#endif


#endif
