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

	m_code = "";			/**< ��Ʊ���� */ 
	m_InvNo = 0;			/**< ��Ʊ���� */
	m_fpsyh = "";
	m_issueDate = 0;		/**< ��Ʊ���� */
	m_issueTime = 0;		/**< ��Ʊʱ�� */
	m_issuetype = 0;		/**< ��Ʊ���� */	
	m_moneySum = 0;			/**< ��Ʊ�ܽ�� */
	m_upFlag = 0;			/**< �ϴ���־ 0=δ�ϴ���1 = �ϴ�  */
	m_wstFlag = 0;			/**< ���ϱ�־  0=δ���ϣ� 1=������*/
	m_caSign = "";
	m_backup = "";			/**< �����ֶ� */
	m_errMsg = "";
    
}

CInvServ::~CInvServ()
{
}


UINT8 CInvServ::Save(const CInvHead *pInv, UINT32 &nNum, INT64 &nSum, string &StrErr)
{
	m_InvNo = pInv->m_fphm;			/**< ��Ʊ���� */
	m_code =  pInv->m_fpdm;			/**< ��Ʊ���� */
	m_issueDate = pInv->m_kprq;		/**< ��Ʊ���� */
	m_issueTime = pInv->m_kpsj;		/**< ��Ʊʱ�� */
	m_issuetype = pInv->m_kplx;		/**< ��Ʊ���� */
	m_upFlag = 0;					/**< �ϴ���־ 0=δ�ϴ���1 = �ϴ�  */
	m_wstFlag = 0;					/**< ���ϱ�־  0=δ���ϣ� 1=������*/
	m_backup = "";					/**< �����ֶ� */
	m_fpsyh = pInv->m_fpsyh;

	INT8 chFilter[128];
	memset((void*)chFilter, 0, sizeof(chFilter));
	INT8 reqType = 0;//��ѯ����
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
		m_moneySum = pInv->m_kphjje;		/**< ��Ʊ�ܽ�� */
		break;
	}

	DBG_PRINT(("m_moneySum = %lld", m_moneySum));

	//�������ϵ�ƱҲ�ڻ����У����Ʊ�����¼�Ľ������
	if ((WASTE_NOR == m_issuetype)||(WASTE_RET == m_issuetype))
	{
		sprintf(chFilter, "where FPDM = '%s' and FPHM = %u and I_TYPE = %u ",
			pInv->m_fpdm.c_str(), pInv->m_fphm, reqType);
		m_filter = chFilter;
		DBG_PRINT(("chFilter = %s", chFilter));
		Requery();
		errCode = LoadOneRecord();
		DBG_PRINT((" ��ѯ��Ӧ����Ʊ errcode = %u", errCode));
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
				//StrErr = "�޸Ļ��淢Ʊ��ʧ��";
				//return FAILURE;
			}
			DBG_PRINT(("���Ļ��淢Ʊ��� errCode = %u", errCode));

			if (NORMAL_INV == reqType) 
			{
				nSum -= m_moneySum;
			}
			saveFlag = 1;
		}
		else if (SQLITE_DONE != errCode)
		{
			DBG_PRINT(("Save to Inv_Serv FAILURE!"));
			StrErr = "��ѯ���淢Ʊ��ʧ��";
		//	return FAILURE;
		}
	}
	else if (NORMAL_INV == m_issuetype)
	{
		nSum += m_moneySum; //����������
	}

	if(0 == saveFlag)
	{
		errCode = AddNew();//���뻺�淢Ʊ��
		if (SQLITE_OK != errCode)
		{
			DBG_PRINT(("Save to Inv_Serv FAILURE!"));
			//StrErr = "���뻺�淢Ʊ��ʧ��";
			//return FAILURE;
		}
		nNum++;	//�����¼������
	}
	
	DBG_PRINT(("���淢Ʊ nSum = %llu, nNum = %u", nSum, nNum));

	return SUCCESS;
}

