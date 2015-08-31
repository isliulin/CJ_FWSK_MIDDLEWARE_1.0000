/*! \file    ClearDepotFunc.cpp
   \brief    转换器清库函数
   \author   zfj
   \version  1.0
   \date     2015-7-25
 */

#include "ClearDepotFunc.h"
#include "CSysArg.h"
#include "SysArgMac.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


#define SQL_CMD "../sqlite3 LIBAWE < ../libawe.sql" //重建数据库命令
#define RM_CMD "rm -rf LIBAWE" //删除数据库文件命令
#define SAVEINFO_CMD "../sqlite3 LIBAWE < saveinfo.sql"
#define SAVEINFO_DIR "saveinfo.sql"  //写机器编码的文件


CClearDepotFunc::CClearDepotFunc()
{
}

CClearDepotFunc::~CClearDepotFunc()
{
}

UINT8 CClearDepotFunc::ClearDepot(string &strErr)
{
	UINT8 ret = SUCCESS;
	INT32 tmp, errorcode;
	CSysArg cSysArg, *sysArg;
	sysArg = &cSysArg;
	INT8 sqlbuf[256];
	string sqlstr = "";

// 	memset((void *)sqlbuf,0x00,sizeof(sqlbuf));
// 	sprintf(sqlbuf,  "where SA_ID = %d", SYS_SERIAL_BAUDRATE);
// 	sysArg->m_filter.append(sqlbuf);
// 	sysArg->Requery();
// 	errorcode = sysArg->LoadOneRecord();
// 	DBG_PRINT(("errorcode= %d",errorcode));
// 	if (errorcode == SQLITE_OK)
// 	{
// 		memset((void *)sqlbuf,0x00,sizeof(sqlbuf));
// 		sprintf(sqlbuf, "update SYSARG set V_INT = %d where SA_ID = %d;\n", 
// 			sysArg->m_vInt, SYS_SERIAL_BAUDRATE);
// 		sqlstr += sqlbuf;
// 		DBG_PRINT(("sqlstr = %s", sqlstr.c_str()));
// 	}

	memset((void *)sqlbuf,0x00,sizeof(sqlbuf));
	sprintf(sqlbuf,  "where SA_ID = %d", SYS_ZS_PWD);
	sysArg->m_filter.append(sqlbuf);
	sysArg->Requery();
	errorcode = sysArg->LoadOneRecord();
	DBG_PRINT(("errorcode= %d",errorcode));
	if (errorcode == SQLITE_OK)
	{
		memset((void *)sqlbuf,0x00,sizeof(sqlbuf));
		sprintf(sqlbuf, "update SYSARG set V_TEXT = '%s' where SA_ID = %d;\n", 
			sysArg->m_vText.c_str(), SYS_ZS_PWD);
		sqlstr += sqlbuf;
		DBG_PRINT(("sqlstr = %s", sqlstr.c_str()));
	}

	memset((void *)sqlbuf,0x00,sizeof(sqlbuf));
	sprintf(sqlbuf,  "where SA_ID = %d", SYS_SKSB_PWD);
	sysArg->m_filter.append(sqlbuf);
	sysArg->Requery();
	errorcode = sysArg->LoadOneRecord();
	DBG_PRINT(("errorcode= %d",errorcode));
	if (errorcode == SQLITE_OK)
	{
		memset((void *)sqlbuf,0x00,sizeof(sqlbuf));
		sprintf(sqlbuf, "update SYSARG set V_TEXT = '%s' where SA_ID = %d;\n", 
			sysArg->m_vText.c_str(), SYS_SKSB_PWD);
		sqlstr += sqlbuf;
		DBG_PRINT(("sqlstr = %s", sqlstr.c_str()));
	}

	FILE *fp1; 
	if( (fp1=fopen(SAVEINFO_DIR,"w"))==NULL ) 
	{ 
		fclose(fp1); 
		strErr = "打开saveinfo.sql文件错误！";
		DBG_PRINT((" 打开saveinfo.sql文件错误"));
		return FAILURE;
	} 

	INT32 nRealLen = sqlstr.length();
	INT32 nLen = 0;
	nLen = fwrite(sqlstr.c_str(),1, nRealLen,fp1); 
	if (nLen!=nRealLen) 
	{
		fclose(fp1); 
		strErr = "写saveinfo.sql文件错误！";
		DBG_PRINT((" 写saveinfo.sql文件错误"));
		return FAILURE;
	}
	
	fclose(fp1);

	//删除数据库文件
	system(RM_CMD);
	DBG_PRINT((" 删除数据库文件"));
	
	//重建数据库
	DBG_PRINT((" 重建数据库"));
	string strCmd = SQL_CMD;
	string strCmd2 = SAVEINFO_CMD;
	DBG_PRINT((" strCmd = %s", strCmd.c_str()));
	DBG_PRINT((" strCmd2 = %s", strCmd2.c_str()));
	if ( system(strCmd.c_str()) != 0 )
	{
		strErr = "清库错误！";	
        return FAILURE;
	}

	if ( system(strCmd2.c_str()) != 0 )
	{
		strErr = "写保留信息错误";	
        return FAILURE;
	}
	
	DBG_PRINT((" 清库完成!请重新启动机器"));
	return SUCCESS;
}




	



	

	


    



	
