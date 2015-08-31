#include "IncludeMe.h"
#include "VersionConfig.h"
#include "OperateDiskProc.h"
#include "CGlobalArgLib.h"
#include "commonFunc.h"

#include "StructOrganize.h"
#include "ServXml_NsrPara.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

#if PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ
#else
#include "BusinessBase.h"
#include "SerialProtocol.h"
#include "CUniversialSerialCommunicate.h"
#include "YWXMLGY.h"
#include "commonFunc.h"

#include "ManageBusinessFunc.h"
#include "DeclareBusinessFunc.h"
#include "SaleBusinessFunc.h"
#include "InvBusinessFunc.h"


int main()
{
	DBG_PRINT(("Programe started !!!"));

	char buf[64];
	int ret = access("LIBAWE", 0);
	if (-1 == ret)
	{
		if (-1==access("sqlite3", 0) || -1==access("libawe.sql", 0))
		{
			DBG_PRINT(("NO DATABASE !!!"));
			exit(-1);
		}
		
		memset(buf, 0x00, sizeof(buf));
		sprintf(buf, "./sqlite3 LIBAWE < libawe.sql");
		system(buf);
		usleep(500000);
	}

	CDB *m_db = CDB::GetInstance();
	m_db->Open();
	m_db->Init();
	CommonSleep(300);
	
	UINT8 index;
	for(index = 0; index<DET_ARRAY_LEN; index++)
	{
		s_DetArray[index] = new CInvDet;
		DBG_ASSERT_EXIT((s_DetArray[index] != NULL), (" s_DetArray[index] == NULL!"));
	}

	CBusinessBase::InitBusiness();
	g_globalArgLib = CGlobalArgLib::GetInstance();
	g_globalArgLib->InitGlobalArg();
	g_YwXmlArg = CYWXML_GY::GetInstance();
	g_gNetArg = g_gNetArg->GetInstance();

	INT8 tmpbuf[32];
	memset(tmpbuf, 0, sizeof(tmpbuf));
	sprintf(tmpbuf, "%u", g_globalArgLib->m_corpInfo->m_Kpjhm);
	g_gNetArg->SetBaseInfo(g_globalArgLib->m_corpInfo->m_Nsrsbh, tmpbuf, g_globalArgLib->m_corpInfo->m_Jspsbh);
	g_gNetArg->SetServPara(g_globalArgLib->m_netPara->m_ServIP, g_globalArgLib->m_netPara->m_ServPort,g_globalArgLib->m_netPara->m_ServAddr);
	g_gNetArg->SetZskl(g_globalArgLib->m_strZskl);

	if(g_globalArgLib->m_corpInfo->m_jqbh != "")
	{
		CManageBusinessFunc manFunc;
		g_YwXmlArg->m_jqbh = g_globalArgLib->m_corpInfo->m_jqbh;
		g_YwXmlArg->m_sksbkl = g_globalArgLib->m_strSksbkl;
		manFunc.UpdateUploadInvInfo(*g_YwXmlArg);
	}

	pthread_t threadWrt;   /**< 接收线程 */
	DBG_PRINT(("已初始化，启动次线程前"));
	pthread_create(&threadWrt, NULL, PthreadInvUpLoad, NULL);
	DBG_PRINT(("已初始化，启动次线程后"));

	SerialProtocol *pSerialProtocol = SerialProtocol::getInstance();
	CUniversialSerialCommunicate uniSerCommunicate;
	
	DBG_PRINT(("g_globalArgLib->m_netPara->m_IsDhcp = %u", g_globalArgLib->m_netPara->m_IsDhcp));
	DBG_PRINT(("g_globalArgLib->m_netPara->m_LocalIP = %s", g_globalArgLib->m_netPara->m_LocalIP.c_str()));
	DBG_PRINT(("g_globalArgLib->m_netPara->m_LocalMask = %s", g_globalArgLib->m_netPara->m_LocalMask.c_str()));
	DBG_PRINT(("g_globalArgLib->m_netPara->m_LocalGate = %s", g_globalArgLib->m_netPara->m_LocalGate.c_str()));
	DBG_PRINT(("g_globalArgLib->m_netPara->m_LocalDNS = %s", g_globalArgLib->m_netPara->m_LocalDNS.c_str()));
	uniSerCommunicate.setNetWork(g_globalArgLib->m_netPara->m_IsDhcp, g_globalArgLib->m_netPara->m_LocalIP.c_str(), g_globalArgLib->m_netPara->m_LocalMask.c_str(), g_globalArgLib->m_netPara->m_LocalGate.c_str(), g_globalArgLib->m_netPara->m_LocalDNS.c_str());
	
	//蓝牙串口必须是115200
#if COMMUNICATE_VERSION==BLUETOOTH_VERSION
	g_globalArgLib->m_serialBaudRate = 115200;
#endif
	
	DBG_PRINT(("g_globalArgLib->m_serialBaudRate = %u", g_globalArgLib->m_serialBaudRate));

#if COMMUNICATE_VERSION != NET_VERSION
	ret = access("zhhserver", 0);
	if (-1 == ret)
	{
		DBG_PRINT(("NO zhhserver PROGRAME !!!"));
		m_db->Close();
		CommonSleep(300);
		exit(-1);
	}
	else
	{
		pid_t fpid;
		memset(buf, 0x00, sizeof(buf));
		fpid = fork();
		if (0 > fpid)
		{
			DBG_PRINT(("fork has error"));
			exit(-1);
		}
		if (0==fpid)
		{
			sprintf(buf, "%d", g_globalArgLib->m_serialBaudRate);
//			DBG_PRINT(("child process"));
			execl("./zhhserver", SERIAL_DEVICE, buf,  NULL);
		}else 
		{
//			DBG_PRINT(("parent process"));
		}

//		sprintf(buf, "./zhhserver %s %d &", SERIAL_DEVICE, g_globalArgLib->m_strSerialBaudRate);
//		system(buf);
	}
#endif

	if (SUCCESS != pSerialProtocol->InitPort(SERIAL_DEVICE, g_globalArgLib->m_serialBaudRate))
	{
		DBG_PRINT(("open serial failed"));
		return 0;
	}
#if COMMUNICATE_VERSION==BLUETOOTH_VERSION || PROJECT_TYPE_MODE == PROJECT_TYPE_A5_YTJ
	if (SUCCESS != pSerialProtocol->InitPrinterPort(PRINTER_SERIAL_DEVICE, 9600))
	{
		DBG_PRINT(("open printer serial failed"));
	}
#endif

	INT8 verbuf[64];
	memset(verbuf, 0, sizeof(verbuf));
	sprintf(verbuf, "serial wait for data 版本号:%.6f", SOFTWARE_VERSION);
	while(1) {
		DBG_PRINT(("%s", verbuf));
		if (SERCMD_SUCCESS == pSerialProtocol->revData())
		{
			uniSerCommunicate.handleSerialCMD();
		}	
	}
}
#endif

//OperateDisk函数调用测试
int main2()
{
	string sInputInfo;
	string sOutputInfo;
	
	FILE *fp;
	INT8 tmpBuff[2048];
	
	//读取XML文件至BUFF
	if( (fp = fopen("test.xml", "rb")) == NULL )
	{
		printf("open file error!!!\n");
		return FAILURE;
	}
	fseek( fp, 0L, SEEK_END );	
	int dataLen = ftell( fp );				
	printf("Req filelen: %d\n", dataLen);
	
	fseek( fp, 0L, SEEK_SET );	
	fread( (void *)tmpBuff, dataLen, 1, fp);
	fclose(fp);
	
	sInputInfo = tmpBuff;

	DBG_PRINT((" 1 读入的XML文件sInputInfo: "))
	printf("\n%s\n", sInputInfo.c_str());
	
	OperateDisk(sInputInfo, sOutputInfo);
	
	DBG_PRINT((" 6 输出的XML文件sOutputInfo: "))
	printf("\n%s\n", sOutputInfo.c_str());
}

//ServXml测试
int main1()
{
	struct NsrInfoData tmpData;
	strcpy(tmpData.nsrdzdah, "X111100000001");
	strcpy(tmpData.nsrmc, "AISINO");
	strcpy(tmpData.nsrsbh, "66667777888");
	strcpy(tmpData.password, "******");
	
	struct NsrInfoData outData;
	
	CStructOrganize test1_origanize;
	CNsrPara Test1Xml((ProtocolOrganize *)&test1_origanize);// = new Test1XML_YW((ProtocolOrganize *)&test1_origanize);
	INT32 ret=0;
	string strErr("");
	
	ret = Test1Xml.CommunicationProc(&tmpData, &outData, strErr);
	DBG_PRINT(("ret = %u", ret));
	DBG_PRINT(("pTest1Xml : %x", &Test1Xml));
	
	if (ret == SUCCESS)
	{
		DBG_PRINT(("nsrdzdah: %s", outData.nsrdzdah))
		DBG_PRINT(("nsrmc: %s", outData.nsrmc))
		DBG_PRINT(("nsrsbh: %s", outData.nsrsbh))
		DBG_PRINT(("password: %s", outData.password))
	}
	else
	{
		DBG_PRINT(("strErr: %s", strErr.c_str()))
	}
	
	
	DBG_PRINT(("main() finish."));
	return 1;
}

