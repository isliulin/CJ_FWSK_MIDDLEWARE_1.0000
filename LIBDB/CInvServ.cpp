#include <string.h>
#include <stdio.h>
#include "CInvServ.h"
#include "SysMacDef.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

CInvServ::CInvServ()
{
	m_roll = 1;

	SET_TABLE_NAME("INV_SERV");
	SET_FIELD_NUM(12);

	SET_FIELD_MEMBER(DB_UINT32, &m_no, "NO", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_code, "FPDM", 0);
    SET_FIELD_MEMBER(DB_UINT32, &m_InvNo, "FPHM", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_fpsyh, "FPSYH", 0);
   SET_FIELD_MEMBER(DB_UINT32, &m_issueDate, "I_DATE", 0);
    SET_FIELD_MEMBER(DB_UINT32, &m_issueTime, "I_TIME", 0);
    SET_FIELD_MEMBER(DB_UINT8, &m_issuetype, "I_TYPE", 0);
    SET_FIELD_MEMBER(DB_INT64, &m_moneySum, "M_SUM", 0);
    SET_FIELD_MEMBER(DB_UINT8, &m_upFlag, "UP_FLAG", 0);
    SET_FIELD_MEMBER(DB_UINT8, &m_wstFlag, "WST_FLAG", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_errMsg, "ERRMSG", 0);
    SET_FIELD_MEMBER(DB_TEXT, &m_backup, "BACKUP", 0);

	m_code = "";			/**< 发票代码 */ 
	m_InvNo = 0;			/**< 发票号码 */
	m_fpsyh = "";
	m_issueDate = 0;		/**< 开票日期 */
	m_issueTime = 0;		/**< 开票时间 */
	m_issuetype = 0;		/**< 开票类型 */	
	m_moneySum = 0;			/**< 开票总金额 */
	m_upFlag = 0;			/**< 上传标志 0=未上传，1 = 上传  */
	m_wstFlag = 0;			/**< 作废标志  0=未作废， 1=已作废*/
	m_caSign = "";
	m_backup = "";			/**< 备用字段 */
	m_errMsg = "";
    
}

CInvServ::~CInvServ()
{
}


UINT8 CInvServ::Save(const CInvHead *pInv, UINT32 &nNum, INT64 &nSum, string &StrErr)
{
	m_InvNo = pInv->m_fphm;			/**< 发票号码 */
	m_code =  pInv->m_fpdm;			/**< 发票代码 */
	m_issueDate = pInv->m_kprq;		/**< 开票日期 */
	m_issueTime = pInv->m_kpsj;		/**< 开票时间 */
	m_issuetype = pInv->m_kplx;		/**< 开票类型 */
	m_upFlag = 0;					/**< 上传标志 0=未上传，1 = 上传  */
	m_wstFlag = 0;					/**< 作废标志  0=未作废， 1=已作废*/
	m_backup = "";					/**< 备用字段 */
	m_fpsyh = pInv->m_fpsyh;

	INT8 chFilter[128];
	memset((void*)chFilter, 0, sizeof(chFilter));
	INT8 reqType = 0;//查询类型
	INT32 errCode = 0;
	string sqlStr("");
	UINT8 saveFlag = 0;

	switch(m_issuetype) 
	{
	case WASTE_NOR:
		m_moneySum = 0;
		reqType = NORMAL_INV;
		break;
	case WASTE_RET:
		m_moneySum = 0;
		reqType = RETURN_INV;
		break;
	case RETURN_INV:
		m_moneySum = 0;
		break;
	case WASTE_INV:
		m_moneySum = 0;
		break;
	default:
		m_moneySum = pInv->m_kphjje;		/**< 开票总金额 */
		break;
	}

	DBG_PRINT(("m_moneySum = %lld", m_moneySum));

	//若被作废的票也在缓存中，则该票缓存记录的金额请零
	if ((WASTE_NOR == m_issuetype)||(WASTE_RET == m_issuetype))
	{
		sprintf(chFilter, "where FPDM = '%s' and FPHM = %u and I_TYPE = %u ",
			pInv->m_fpdm.c_str(), pInv->m_fphm, reqType);
		m_filter = chFilter;
		DBG_PRINT(("chFilter = %s", chFilter));
		Requery();
		errCode = LoadOneRecord();
		DBG_PRINT((" 查询对应缓存票 errcode = %u", errCode));
		if( errCode == SQLITE_OK )		
		{
			DBG_PRINT(("m_InvNo = %u", m_InvNo));
			DBG_PRINT(("m_code = %s", m_code.c_str()));
			DBG_PRINT(("m_issueTime = %u", m_issueTime));
			DBG_PRINT(("m_moneySum = %ld", m_moneySum));

			memset((void *)chFilter, 0, sizeof(chFilter));
			sprintf(chFilter, "update INV_SERV set M_SUM = 0, I_TYPE=%u, UP_FLAG=0 where FPDM = '%s' and FPHM = %u and I_TYPE = %u",
				pInv->m_kplx, pInv->m_fpdm.c_str(), pInv->m_fphm, reqType);
			sqlStr = chFilter;
			DBG_PRINT(("sqlStr = %s", sqlStr.c_str()));
			SetSQL(sqlStr);
			errCode = ExecuteSQL();
			if (SQLITE_OK != errCode)
			{
				DBG_PRINT(("Save to Inv_Serv FAILURE!"));
				//StrErr = "修改缓存发票表失败";
				//return FAILURE;
			}
			DBG_PRINT(("更改缓存发票金额 errCode = %u", errCode));

			if (NORMAL_INV == reqType) 
			{
				nSum -= m_moneySum;
			}
			saveFlag = 1;
		}
		else if (SQLITE_DONE != errCode)
		{
			DBG_PRINT(("Save to Inv_Serv FAILURE!"));
			StrErr = "查询缓存发票表失败";
		//	return FAILURE;
		}
	}
	else if (NORMAL_INV == m_issuetype)
	{
		nSum += m_moneySum; //缓存金额增加
	}

	if(0 == saveFlag)
	{
		errCode = AddNew();//存入缓存发票表
		if (SQLITE_OK != errCode)
		{
			DBG_PRINT(("Save to Inv_Serv FAILURE!"));
			//StrErr = "存入缓存发票表失败";
			//return FAILURE;
		}
		nNum++;	//缓存记录数增加
	}
	
	DBG_PRINT(("缓存发票 nSum = %llu, nNum = %u", nSum, nNum));

	return SUCCESS;
}

