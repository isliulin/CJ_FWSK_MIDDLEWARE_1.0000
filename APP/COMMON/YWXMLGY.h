#ifndef __YW_XML_GY_H
#define __YW_XML_GY_H

#include <string.h>
#include "IncludeMe.h"

class CYWXML_GY;
extern CYWXML_GY *g_YwXmlArg;

class CYWXML_GY
{
public:
	string m_strID;			//ҵ��ID
	string m_jqbh;			//˰���տ�����
	string m_nsrsbh;		//��˰��ʶ���
	string m_nsrmc;			//��˰������
	string m_sksbbh;		//˰���豸���
	string m_sksbkl;		//˰���豸����
	string m_fplxdm;		//��Ʊ���ʹ���
	string m_bspbh;			//��˰�̱��
	string m_bspkl;			//��˰�̿���
	string m_kpjh;			//��Ʊ���� 0������ �������ֻ�
	string m_zskl;			//֤�����

public:
	CYWXML_GY();
	~CYWXML_GY();

	static CYWXML_GY* GetInstance(void);

private:
	static CYWXML_GY *m_YwXmlArg;	/**< CGlobalArg���󣬾�̬ */

};


#endif

