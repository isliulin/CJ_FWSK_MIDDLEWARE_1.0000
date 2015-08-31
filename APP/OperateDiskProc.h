#ifndef __MAIN_PROC_H
#define __MAIN_PROC_H

#include <string>

using namespace std;

int InitPara(string &strErr);


/*!
@brief ��2�� ˰���տ����˰���豸�ӿ�
@param[in]  sInputInfo   ����XML��Ϣ
@param[out] sOutputInfo  ���ؽ��XML�ַ���
@return 
*/
void OperateDisk(string sInputInfo, string &sOutputInfo);


/*!
@brief ��3�� ˰���տ����ͳһ����ƽ̨�ӿ�
@param[in]  sInputInfo   ����XML��Ϣ
@param[out] sOutputInfo  ���ؽ��XML�ַ���
@return 
*/
void OperateNet(char* pin,string ip,string port,string serverpath,char*	service_id,string  nsrsbh,
				string sInputInfo, string &sOutputInfo,string&  Err);

#endif
