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
	//联机函数
	UINT8 onLine();
	//税控盘编号查询
	UINT8 skpbhcx();
	//报税盘编号查询
	UINT8 bspbhcx();
	//税控盘信息查询
	UINT8 skpxxcx();
	//报税盘信息查询
	UINT8 bspxxcx();
	//监控数据查询
	UINT8 jksjcx();
	//授权税率查询
	UINT8 sqslcx();
	//购票信息查询
	UINT8 gpxxcx();
	//口令更改
	UINT8 sksbklgg();
	//发票开具
	UINT8 fpkj();
	//发票作废
	UINT8 fpzf();
	//发票查询
	UINT8 fpcx();
	//税控盘报税盘组合操作
	UINT8 skpbspzhcz();
	//报税盘发票查询
	UINT8 bspfpcx();
	//发票分发
	UINT8 fpff();
	//发票回收
	UINT8 fphs();
	//数据抄报
	UINT8 sjcb();
	//网络监控回传
	UINT8 wljkhc();
	//发票统计信息查询
	UINT8 fptjcx();
	//企业信息更新
	UINT8 qyxxgx();
	//离线权限更新
	UINT8 lxqxgx();
	//发票实时上传
	UINT8 fpsssc();
	//网络参数维护
	UINT8 wlcswh();
	//设置串口波特率
	UINT8 setBaudRate();
	//发票读入
	UINT8 fpdr();
	//分机退回
	UINT8 fjth();
	//网络购票
	UINT8 wlgp();
	//证书口令更改
	UINT8 zsklgg();
	//发票补录
	UINT8 fpbl();
	//获取离线相关数据
	UINT8 hqlxsj();
	//转换器清库
	UINT8 zhqqk();
	//获取上传出错发票信息
	UINT8 getErrUpInv();
	//安全通道连接测试
	UINT8 sslConnectTest();

    //应用升级
	UINT8 programUpdate();
	//系统自检
	UINT8 sysTest();
	//烧写MAC
	UINT8 writeMAC();
	//烧写机器编号
	UINT8 writeMachineNo();

	//配置IP地址函数
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
//------线程相关--------//
void * PthreadInvUpLoad(void *arg);
#endif


#endif
