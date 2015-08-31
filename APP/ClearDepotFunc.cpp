/*! \file    ClearDepotFunc.cpp
   \brief    ת������⺯��
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


#define SQL_CMD "../sqlite3 LIBAWE < ../libawe.sql" //�ؽ����ݿ�����
#define RM_CMD "rm -rf LIBAWE" //ɾ�����ݿ��ļ�����
#define SAVEINFO_CMD "../sqlite3 LIBAWE < saveinfo.sql"
#define SAVEINFO_DIR "saveinfo.sql"  //д����������ļ�


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
		strErr = "��saveinfo.sql�ļ�����";
		DBG_PRINT((" ��saveinfo.sql�ļ�����"));
		return FAILURE;
	} 

	INT32 nRealLen = sqlstr.length();
	INT32 nLen = 0;
	nLen = fwrite(sqlstr.c_str(),1, nRealLen,fp1); 
	if (nLen!=nRealLen) 
	{
		fclose(fp1); 
		strErr = "дsaveinfo.sql�ļ�����";
		DBG_PRINT((" дsaveinfo.sql�ļ�����"));
		return FAILURE;
	}
	
	fclose(fp1);

	//ɾ�����ݿ��ļ�
	system(RM_CMD);
	DBG_PRINT((" ɾ�����ݿ��ļ�"));
	
	//�ؽ����ݿ�
	DBG_PRINT((" �ؽ����ݿ�"));
	string strCmd = SQL_CMD;
	string strCmd2 = SAVEINFO_CMD;
	DBG_PRINT((" strCmd = %s", strCmd.c_str()));
	DBG_PRINT((" strCmd2 = %s", strCmd2.c_str()));
	if ( system(strCmd.c_str()) != 0 )
	{
		strErr = "������";	
        return FAILURE;
	}

	if ( system(strCmd2.c_str()) != 0 )
	{
		strErr = "д������Ϣ����";	
        return FAILURE;
	}
	
	DBG_PRINT((" ������!��������������"));
	return SUCCESS;
}




	



	

	


    



	
