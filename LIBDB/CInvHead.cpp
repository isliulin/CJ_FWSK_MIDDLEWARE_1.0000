#include <string.h>
#include <stdio.h>
#include "CInvHead.h"

#include "VersionConfig.h"
#include "IncludeMe.h"
//#include "beep.h"
#include "commonFunc.h"

#include "LOGCTRL.h"
#define NO_POS_DEBUG
#include "pos_debug.h"

//#define PART_DEL
#ifdef PART_DEL
#define DEL_NUM 200
#else
#define DEL_NUM INV_HEAD_DEL_MAX
#endif

#define TRY_TIMES 3

CInvHead::CInvHead()
{
	m_roll = 1;
	
	m_fpdm = "";
	m_fphm = 0;
	m_kprq = 0;
	m_kpsj = 0;
	m_kplx = 0;
	m_kphjje = 0;
	m_yfpdm = "";
	m_yfphm = 0;
	m_fkdw = "";
	m_payerCode = "000000000000000";
	m_sky = "";
	m_sphsl = 0;
	m_fwm = "";
	m_fplb = 0;
	m_scbz = 0;
	m_fpsyh = "";
	m_hczt = "";
	m_casign = "";			/**< CAǩ��*/
	m_backup1 = "";
	m_backup2 = "";
	m_kpse = 0;				/**< ˰��*/
	m_kpje = 0;
	m_fplxdm = "";
	m_sl = 0;
	m_zsl = 0;
	m_xxpzlb = 0;
	m_dycs = 0;
	m_zfbz = 0;
	m_hyfl = "";
	m_fpzl = "c";
	m_gfdzdh = "";
	m_gfyhzh = "";
	m_jqbh = "";
	m_zyspmc = "";
	m_bsq = "";
	m_xfmc = "";
	m_xfsh = "";
	m_xfdzdh = "";
	m_xfyhzh = "";
	m_fhr = "";
	m_qdbz = "N";
	m_zskl = "";
	pHead = NULL;
	pEnd = NULL;
	m_pInvDet = &m_InvDet;
	m_CurTime="";
	m_zfsj = "";
	m_sksbbh = "";
	
	SET_TABLE_NAME("INV_HEAD");
	SET_FIELD_NUM(20);
	
	
	SET_FIELD_MEMBER(DB_UINT32, &m_no, "NO", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_fpdm, "FPDM", 0);
	SET_FIELD_MEMBER(DB_UINT32, &m_fphm, "FPHM", 0);
	SET_FIELD_MEMBER(DB_UINT32, &m_kprq, "KPRQ", 0);
	SET_FIELD_MEMBER(DB_UINT32, &m_kpsj, "KPSJ", 0);
	SET_FIELD_MEMBER(DB_UINT8, &m_kplx, "KPLX", 0);
	SET_FIELD_MEMBER(DB_INT64, &m_kphjje, "KPHJJE", 0);
	SET_FIELD_MEMBER(DB_INT64, &m_kpse, "KPSE", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_yfpdm, "YFPDM", 0);
	SET_FIELD_MEMBER(DB_UINT32, &m_yfphm, "YFPHM", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_fkdw, "FKDW", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_payerCode, "PAYER_CODE", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_sky, "SKY", 0);
	SET_FIELD_MEMBER(DB_UINT32, &m_sphsl, "SPHSL", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_fwm, "FMW", 0);
	SET_FIELD_MEMBER(DB_UINT8, &m_fplb, "FPLB", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_zfsj, "ZFSJ", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_fpsyh, "FPSYH", 0);
    SET_FIELD_MEMBER(DB_TEXT, &m_backup1, "BACKUP1", 0);
	SET_FIELD_MEMBER(DB_TEXT, &m_casign, "CA_SIGN", 0);
	
}

CInvHead::~CInvHead()
{
	m_pInvDet = NULL;
	
	//�ͷ�����ռ�
    DelList(); 
}

INT32 CInvHead::InsertNode(CInvDet* pNew)
{
	DBG_ENTER("CInvHead::InsertNode");
	DBG_PRINT(("����InsertNode����"));
	
	//��Ϊ������
	if (pHead == NULL) 
	{
		pHead = pNew;
		pNew->pNext = NULL;
		pEnd = pNew;
		DBG_PRINT(("��һ��Node"));
		DBG_PRINT(("�˳�InsertNode����"));
		DBG_RETURN(SUCCESS);
	}
	
    //��Ϊ�ǿ�����
	pEnd->pNext = pNew;
	pNew->pNext = NULL;
	pEnd = pNew;
	
	DBG_PRINT(("�˳�InsertNode����"));
	DBG_RETURN(SUCCESS);
}

INT32 CInvHead::ShowList()
{
	DBG_ENTER("CInvHead::ShowList");
	CInvDet *p = pHead;
	
    //��Ϊ������
	if (pHead == NULL)
	{
		DBG_ASSERT_WARNING(false,("The list is empty!"));
		DBG_RETURN(FAILURE);
	}
	
    //��Ϊ�ǿ�����
	while (p)
	{
		DBG_PRINT(("m_spbm = %s,", p->m_spbm.c_str() ));
		p = p->pNext;
	}
	DBG_RETURN(SUCCESS);	
}

INT32 CInvHead::DelNode(string &pCode)
{
	DBG_ENTER("CInvHead::DelNode");
	//��Ϊ������
	if (pHead == NULL)
	{
		DBG_ASSERT_WARNING(false,("The list is empty!"));
		DBG_RETURN(0);	
	}
	
    CInvDet *p, *s;
	p = pHead;
	s = pHead;
	
	while ((p != NULL)&&((pCode.compare(p->m_spbm))!=0))
	{
		s = p;
		p = p->pNext;
	}
	
	if ((pCode.compare(p->m_spbm))==0) //�ҵ��ýڵ�
	{
		if (p == pHead)//����ͷ�ڵ�
		{
			pHead = p->pNext;
		}
		else //����ͷ�ڵ�
		{
			s->pNext = p->pNext;
		}
		
		if (pEnd == p) //����β�ڵ�
		{
			pEnd = s;
		}
		//		delete p; //�ͷŸýڵ���ռ�ռ�
		p->FreeInvDet();//�ͷŸýڵ���ռ�ռ�
		p = NULL;
	}	
	else //δ�ҵ��ýڵ�
	{
		DBG_ASSERT_WARNING(false,("Can not find the node!"));
		DBG_RETURN(FAILURE);	
	}
	
	DBG_RETURN(SUCCESS);
}

//xsr ��������Ǳ�ע���ģ����Ҳ�֪��Ϊ�ε�ʱע�����ˡ����ڰ����򿪡�
//xsr ��������ע��������
// INT32 CInvHead::DelNode(UINT8 dpNo)
// {
// 	DBG_ENTER("CInvHead::DelNode");
// 	//��Ϊ������
// 	if (pHead == NULL)
// 	{
// 		DBG_ASSERT_WARNING(false,("The list is empty!"));
// 		DBG_RETURN(0);	
// 	}
// 	
//     CInvDet *p, *s;
// 	p = pHead;
// 	s = pHead;
// 
// 	while ((p != NULL)&&(p->m_dpNo != dpNo))
// 	{
// 		s = p;
// 		p = p->pNext;
// 	}
// 	
// 	if (p->m_dpNo == dpNo) //�ҵ��ýڵ�
// 	{
// 		if (p == pHead)//����ͷ�ڵ�
// 		{
// 			pHead = p->pNext;		    
// 		}
// 		else //����ͷ�ڵ�
// 		{
// 			s->pNext = p->pNext;
// 		}
// 
// 		if (pEnd == p) //����β�ڵ�
// 		{
// 			pEnd = s;
// 		}
// //		delete p; //�ͷŸýڵ���ռ�ռ�
// 		p->FreeInvDet();//�ͷŸýڵ���ռ�ռ�
// 		p = NULL;
// 	}	
//     else //δ�ҵ��ýڵ�
// 	{
// 		DBG_ASSERT_WARNING(false,("Can not find the node!"));
// 		DBG_RETURN(FAILURE);	
// 	}
//     
// 	DBG_RETURN(SUCCESS);
// }

INT32 CInvHead::DelLastNode()
{
	DBG_ENTER("CInvHead::DelLastNode");
	//��Ϊ������
	if (pHead == NULL)
	{
		DBG_ASSERT_WARNING(false,("The list is empty!"));
		DBG_RETURN(FAILURE);	
	}
	
	if (pEnd == NULL)
	{
		DBG_ASSERT_WARNING(false,("pHead != NULL, pEnd == NULL!"));
		DBG_RETURN(FAILURE);	
	}
	
    CInvDet *p, *s;
	p = pHead;
	//��������ֻ��һ���ڵ�
	if (p == pEnd)
	{
		pHead =NULL;
		pEnd = NULL;
		//		delete p; //�ͷŸýڵ���ռ�ռ�
		p->FreeInvDet();//�ͷŸýڵ���ռ�ռ�
		DBG_RETURN(SUCCESS);
	}
    
	//���������ж���ڵ�
	while (p != pEnd)
	{
		s = p;
		p = p->pNext;
	}
	pEnd = s;
	s->pNext = NULL;
	//	delete p; //�ͷŸýڵ���ռ�ռ�
	p->FreeInvDet();//�ͷŸýڵ���ռ�ռ�
	DBG_RETURN(SUCCESS);
}

//-------------------------------------------------
//ɾ�������ͷ�����ռ�
//-------------------------------------------------
INT32 CInvHead::DelList()
{
	DBG_PRINT(("����DelList����"));
	DBG_ENTER("CInvHead::DelList");
	CInvDet *p = pHead;
	CInvDet *s;
	
	while (p)
	{
		DBG_PRINT(("delete CInvDet: DP_NO = %s!", p->m_spbm.c_str()));
		s = p;
		p = p->pNext;
		//delete s;
		s->FreeInvDet();//�ͷŸýڵ���ռ�ռ�
	}
	pHead = NULL;
	pEnd = NULL;
	
	DBG_PRINT(("�˳�DelList����"));
    DBG_RETURN(SUCCESS);
}

CInvDet* CInvHead::SearchNode(string &pCode)
{
	DBG_ENTER("CInvHead::SearchNode");
	//��Ϊ������
	if (pHead == NULL)
	{
		DBG_ASSERT_WARNING(false,("The list is empty!"));
		DBG_RETURN(0);	
	}
	
	CInvDet *p;
	p = pHead;
	DBG_PRINT((" begin to search"));
	while ((p != NULL)&&((pCode.compare(p->m_spbm))!=0))
	{
		p = p->pNext;
		DBG_PRINT((" p = p->pNext"));
	}
	if (NULL == p ) 
	{
		DBG_PRINT((" not find this node"));
		DBG_RETURN(NULL);	
	}
	
	if ((pCode.compare(p->m_spbm))==0) //�ҵ��ýڵ�
	{
		DBG_PRINT((" found this node"));
		DBG_RETURN(p);
	}	
	//    else //δ�ҵ��ýڵ�
	//	{
	//		DBG_PRINT((" not find this node"));
	//		DBG_RETURN(NULL);	
	//	}
}

// CInvDet* CInvHead::SearchNode(UINT8 dpNo)
// {
// 	DBG_ENTER("CInvHead::SearchNode");
// 	
// 	//��Ϊ������
// 	if (pHead == NULL)
// 	{
// 		DBG_ASSERT_WARNING(false,("The list is empty!"));
// 		DBG_RETURN(0);	
// 	}
// 
//     CInvDet *p;
// 	p = pHead;
// 
// 	while ((p != NULL)&&(p->m_dpNo != dpNo))
// 	{
// 		p = p->pNext;
// 		DBG_PRINT((" next"));
// 	}
// 
// 	if (NULL == p ) 
// 	{
// 		DBG_PRINT((" not find this node"));
// 		DBG_RETURN(NULL);	
// 	}
// 	
// 	if (p->m_dpNo == dpNo) //�ҵ��ýڵ�
// 	{
// 		DBG_PRINT((" found this node"));
// 		DBG_RETURN(p);
// 	}	
// //    else //δ�ҵ��ýڵ�
// //	{
// //		DBG_PRINT((" not find this node"));
// //		DBG_RETURN(NULL);	
// //	}
// }

INT32 CInvHead::Load()
{
	DBG_ENTER("CInvHead::Load");
	DBG_PRINT(("����CInvHead::Load����"));
	
	//�ͷ�������ռ�ռ�
	DelList();
	
	//��ѯINV_HEAD��
	CTable::Requery();
	INT32 returnVal = LoadOneRecord();
	
	if (returnVal == SQLITE_OK)
	{    
        DBG_PRINT(("NO, %d", m_no));
		DBG_PRINT(("m_fpdm, %s", m_fpdm.c_str()));
		DBG_PRINT(("m_fphm, %d", m_fphm));
		DBG_PRINT(("m_kprq, %lu", m_kprq));
		DBG_PRINT(("m_kpsj, %lu", m_kpsj));
		DBG_PRINT(("m_kplx, %d", m_kplx));
		
		DBG_PRINT(("m_kphjje, %lld", m_kphjje));
		DBG_PRINT(("m_yfphm, %d", m_yfphm));
		
		DBG_PRINT(("m_fkdw, %s", m_fkdw.c_str()));
		DBG_PRINT(("m_payerCode, %s", m_payerCode.c_str()));
		DBG_PRINT(("m_sky, %s", m_sky.c_str()));
		//		DBG_PRINT(("m_skyid, %u", m_skyid));
		DBG_PRINT(("m_fwm, %s", m_fwm.c_str()));
		
		// 	    DBG_PRINT(("m_ptype, %d", m_ptype));
		//DBG_NPRINT_HEX(m_fCode, 8);	    
		DBG_PRINT(("m_sphsl, %d", m_sphsl));
		DBG_PRINT(("BACKUP1, %s", m_backup1.c_str()));
		// 		DBG_PRINT(("BACKUP2, %s", m_backup2.c_str()));
		//		DBG_PRINT(("BACKUP3, %s", m_backup3.c_str()));
		
	}
	else if (returnVal == SQLITE_DONE)
	{
		DBG_PRINT((" CInvHead has no matched record! errorcode: %d", returnVal));
		return returnVal;
	}
	else
	{
		DBG_PRINT(("errorcode: %d", returnVal));
		return returnVal;
	}
	
	m_kpje = m_kphjje - m_kpse;
	
	//��ѯINV_DET��
	INT8 chFilter[256];
	memset((void *)chFilter, 0x00, sizeof(chFilter));
	sprintf(chFilter, "where FPDM = '%s' and FPHM = %u", m_fpdm.c_str(), m_fphm);
	DBG_PRINT(("chFilter = %s", chFilter));
	m_pInvDet->m_filter = chFilter;
	m_pInvDet->Requery();
	
	INT32 errorcode = m_pInvDet->MoveFirst();	
	if (errorcode != SQLITE_ROW) 
	{
		if ((errorcode == SQLITE_DONE)&&(m_sphsl==0)) //û����ϸ
		{
			m_pInvDet->MoveEnd();
			return SQLITE_OK;
		}
		else
		{
			DBG_PRINT(("errorcode: %d", errorcode));
			m_pInvDet->MoveEnd();
			return errorcode; //���ܷ���SQLITE_DONE,������������
		}	
	}
	
	CInvDet *p;
	while (errorcode == SQLITE_ROW)
	{
		//		p = new CInvDet;
		p = p->GetNewInvDet();//�Ӿ�̬�����ȡһ�����õ�CInvDet����
		
		p->m_no = m_pInvDet->m_no;
		p->m_fpdm = m_pInvDet->m_fpdm;
		p->m_fphm = m_pInvDet->m_fphm;
		
		p->m_kprq = m_pInvDet->m_kprq;
		p->m_kpsj = m_pInvDet->m_kpsj;
		p->m_kplx = m_pInvDet->m_kplx;
		
		p->m_sphxh = m_pInvDet->m_sphxh;
		p->m_spbm = m_pInvDet->m_spbm;
		p->m_spmc = m_pInvDet->m_spmc;
		p->m_spdj = m_pInvDet->m_spdj;
		p->m_spsl = m_pInvDet->m_spsl;
		p->m_spje = m_pInvDet->m_spje;
		p->m_spdw = m_pInvDet->m_spdw;
		
		p->m_sl = m_pInvDet->m_sl;
		p->m_spse = m_pInvDet->m_spse;
		p->m_property = m_pInvDet->m_property;
		p->m_dj = m_pInvDet->m_dj;
		p->m_je = m_pInvDet->m_je;
		
		InsertNode(p);	//����ڵ�	
		DBG_PRINT(("============================"));
		DBG_PRINT(("NO, %d", m_pInvDet->m_no));
		DBG_PRINT(("m_fpdm, %s", m_pInvDet->m_fpdm.c_str()));
		DBG_PRINT(("m_fphm, %d", m_pInvDet->m_fphm));
		DBG_PRINT(("m_sphxh, %d", m_pInvDet->m_sphxh));
		DBG_PRINT(("m_kprq, %lu", m_pInvDet->m_kprq));
		DBG_PRINT(("m_kpsj, %lu", m_pInvDet->m_kpsj));
		
		DBG_PRINT(("m_spbm, %s", m_pInvDet->m_spbm.c_str()));
		DBG_PRINT(("m_spmc, %s", m_pInvDet->m_spmc.c_str()));
		
		DBG_PRINT(("m_spdj, %f", m_pInvDet->m_spdj));
		DBG_PRINT(("m_spsl, %f", m_pInvDet->m_spsl));
		DBG_PRINT(("m_spje, %lld", m_pInvDet->m_spje));
		DBG_PRINT(("m_spse, %lld", m_pInvDet->m_spse));
		DBG_PRINT(("m_spdw, %s", m_pInvDet->m_spdw.c_str()));
		
		//	DBG_PRINT(("PRICE, %u", m_pInvDet->m_dpNo)); 	    	     
		errorcode = m_pInvDet->MoveNext();
	}
	
	m_pInvDet->MoveEnd();
	//m_db->MutexUnlock();
	
	
	if (errorcode==SQLITE_DONE) 
	{
		DBG_PRINT(("�˳�CInvHead::Load����"));
		return SQLITE_OK;
	}
	
	DBG_PRINT(("�˳�CInvHead::Load����"));
	return errorcode;
}

//-----------------------------------------------------
//�洢���ݵ����ݿ⣨INV_HEAD��INV_DET��
//-----------------------------------------------------
INT32 CInvHead::Save()
{
	DBG_PRINT(("����Save����"));
	DBG_ENTER("CInvHead::Save");
	INT32 errcode;
	
	//���INV_HEAD��¼
	errcode = AddNew();
	//printf("512errcode= %d \n",errcode);
	if (errcode != SQLITE_OK)
	{
		DBG_PRINT(("INV_HEAD AddNew() wrong"));
		DBG_RETURN(FAILURE);
	}
    //printf("pHead= %x \n",pHead);
	//���INV_DET��¼
    CInvDet *p = pHead;
	if (p==NULL)
	{
		//printf("523 INV_DET here \n");
		DBG_PRINT(("INV_DET here"));
		DBG_ASSERT_WARNING(false,("List pointer: pHead = NULL!"));
	}
	while (p)
	{
		p->m_fpdm = m_fpdm;
		p->m_fphm = m_fphm;
		p->m_kplx = m_kplx;
		p->m_kprq = m_kprq;
		p->m_kpsj = m_kpsj;
		p->m_sky = m_sky;
		
		//printf("529INV_DET here \n");
		DBG_PRINT(("INV_DET here"));
		DBG_PRINT(("p->m_fphm = %u", p->m_fphm));
		DBG_PRINT(("p->m_spmc = %s", p->m_spmc.c_str()));
		DBG_PRINT(("p->m_spdj = %f", p->m_spdj));
		errcode = p->AddNew();
		//printf("534errcode= %d \n",errcode);
		if (errcode != SQLITE_OK)
		{
			DBG_PRINT(("INV_DET AddNew() wrong"));
			DBG_RETURN(FAILURE);
		}
		p = p->pNext;
		DBG_PRINT(("INV_DET AddNew()"));
	}	
	//printf("�˳�Save���� \n");
	DBG_PRINT(("�˳�Save����"));
	DBG_RETURN(SUCCESS);
}

INT32 CInvHead::CheckRoll(INT32 nCount, UINT32 strRefDate, UINT32 &nDelDate)
{
	DBG_ENTER("CInvHead::Roll");
	
	INT32 nNoStart, nNoEnd;
	char value[128];
	UINT32 strEndDate;
	nDelDate = 0;
	
	if (nCount>=INV_HEAD_MAX) //������������¼��
	{
		//�õ���һ����¼�����
		Requery();
		if (LoadOneRecord() == SQLITE_OK)
		{
			nNoStart = m_no;
		}
		else
		{
			DBG_ASSERT_WARNING(false,("Can not load the first record!"));
			DBG_RETURN(FAILURE);
		}
		
		//��ѯ��ֹ��������IE_DATE�ֶ�
		nNoEnd = nNoStart + DEL_NUM - 1;
		sprintf(value, "WHERE NO = %d", nNoEnd);		
		m_filter.append(value);
        Requery();
		if (LoadOneRecord() == SQLITE_OK)
		{
			strEndDate = m_kprq;
		}
		else
		{
			DBG_ASSERT_WARNING(false,("Can not load the first record!"));
			DBG_RETURN(FAILURE);
		}
		
		DBG_PRINT(("strRefDate = %u and  strEndDate = %u",strRefDate, strEndDate));
		//		//�Ƚ������ֶΣ�ȷ��ɾ������	    
		//		if(strRefDate <= strEndDate)
		//		{
		//			nDelDate = strRefDate;
		//		}
		//		else
		//		{
		nDelDate = strEndDate;  
		//		}
		
		DBG_RETURN(SUCCESS);
	}
	
	DBG_RETURN(SUCCESS);
}


INT32 CInvHead::Roll(UINT32 nDelDate, UINT32 strRefDate)
{
	
#ifdef PART_DEL
#endif
	
#ifndef PART_DEL
	
	//����ɾ����¼
	return (DeleteRecord(nDelDate));
	
#endif
	
}


INT8 CInvHead::DeleteRecord(UINT32 nDelDate)
{
	INT8 value[128];
	UINT8 ret;
	UINT8 nIndex = 0;
	if (nDelDate>0) //Ҫ����
	{
		sprintf(value,"WHERE KPRQ <= %lu", nDelDate);
		m_filter = value;
		m_pInvDet->m_filter = m_filter;
		ret = Delete(); 
		//		FOR_DELAY(0xFFFFFF);//delay for some time
		//		FOR_DELAY(0xFFFFFF);//delay for some time
		if (SQLITE_OK != ret)
		{
			//Beep_On();
			nIndex = 0;
			do 
			{
				nIndex++;
				m_filter = value;
				ret = Delete(); 
				//				FOR_DELAY(0xFFFFFF);//delay for some time
				//				FOR_DELAY(0xFFFFFF);//delay for some time
			} while((SQLITE_OK != ret)&&(nIndex<TRY_TIMES));
		}
		if(SQLITE_IOERR==ret)
		{
			return FAILURE;// ����ʧ�ܣ�disk IO error��������
		}
		
        //ɾ��INV_DET�ļ�¼
        ret = m_pInvDet->Roll();
		//		FOR_DELAY(0xFFFFFF);
		//		FOR_DELAY(0xFFFFFF);//delay for some time
		if (SQLITE_OK != ret)
		{
			nIndex = 0;
			do 
			{
				nIndex++;
				m_pInvDet->m_filter = value;
				ret = m_pInvDet->Roll(); 
				//				FOR_DELAY(0xFFFFFF);//delay for some time
				//				FOR_DELAY(0xFFFFFF);//delay for some time
			} while((SQLITE_OK != ret)&&(nIndex<TRY_TIMES));
		}
		if(SQLITE_IOERR==ret)
		{
			return FAILURE;// ����ʧ�ܣ�disk IO error��������
		}
	}
	DBG_RETURN(SUCCESS);
}



INT32 CInvHead::GetInvoiceSum(UINT32 &norInv, UINT32 &recInv, UINT32 &canInv)
{
	DBG_ENTER("CInvHead::GetInvoiceSum");
	
	INT32 nNum;
	string strSql = "select count(*), KPLX from INV_HEAD ";
	
	strSql.append(m_filter);
    strSql.append(" group by KPLX");
	DBG_PRINT(("strSql = %s ",strSql.c_str()));
	SetSQL(strSql);
	
	UINT32 value[7][2] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	UINT32 *p[14];
	UINT8 i, j;
	DB_TYPE  nType[2] = {DB_UINT32, DB_UINT8};
	for(i=0; i<7; i++)
	{
		for(j = 0; j<2; j++)
		{
			p[i*2 +j] = &(value[i][j]);
		}
	}
	
	//	nNum = GetMultiResult(nType, (void **)p, 2);
	INT32 errCode = GetMultiResult(nType, (void **)p, 2, nNum);
	if (SQLITE_OK != errCode)
	{
		DBG_PRINT(("GetMultiResult err: errCode = %d ", errCode));
		DBG_RETURN(errCode);
	}
	DBG_PRINT(("nNum = %d ", nNum));
    
	norInv = 0;
	recInv = 0;
	canInv = 0;
	for(i = 0; i<nNum; i++)
	{
		switch(value[i][1]) 
		{
		case NORMAL_INV:
			norInv = value[i][0];
			break;
		case RETURN_INV:
		case RET_MANUAL_INV:
		case RET_SPECIAL_INV:
			recInv += value[i][0];
			break;
		case WASTE_INV:
		case WASTE_NOR:
		case WASTE_RET:
			canInv += value[i][0];
			break;
		default:;
		}
		DBG_PRINT(("value[%u][0] = %u ", i, value[i][0]));
	}
	
	//	DBG_RETURN(nNum);
	DBG_RETURN(errCode);
}


INT32 CInvHead::GetInvHeadNum()
{
	INT32 nNoStart = 0;
	INT32 nNoEnd = 0;
	INT32 nCount = 0;
	INT32 errcode;
	string filter, strlimit;
	
	filter = m_filter;
	strlimit = " limit 1";
	m_filter += strlimit;
	Requery();
	errcode = LoadOneRecord();
	
	if (errcode == SQLITE_OK)
	{
		nNoStart = m_no; //��ʼ��¼�����
	}
	else if (errcode == SQLITE_DONE) 
	{
		nCount = 0;
		DBG_RETURN(nCount);	//�ձ��޼�¼		
	}
	else 
	{
		DBG_PRINT(("Can not load the first record!"));
		DBG_RETURN(-1);
	}
	
	strlimit = " order by NO desc limit 1";
	m_filter = filter;
	m_filter += strlimit;
	
	Requery();
	if (LoadOneRecord() == SQLITE_OK)
	{
		nNoEnd = m_no; //ĩβ��¼�����
	}
	else
	{
		DBG_PRINT(("Can not load the last record!"));
		DBG_RETURN(-1);
	}
	
	nCount = nNoEnd - nNoStart + 1; //INV_HEAD��ļ�¼��
	if (nCount<0) 
	{
		DBG_PRINT(("INV_HEAD��nCount<0!"));
		DBG_RETURN(-1);
	}
	
	DBG_RETURN(nCount);
	
	
}

UINT32 CInvHead::GetInvNumByDate()
{
	UINT32 nNum;
	string strSql = "select count(*) from INV_HEAD ";
	strSql.append(m_filter);
	
	DBG_PRINT(("strSql = %s", strSql.c_str()));
	SetSQL(strSql);
	GetOneResult(DB_UINT32, (void*)&nNum); 
	
	return nNum;
}
