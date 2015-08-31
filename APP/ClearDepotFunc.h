/*! \file    ClearDepotFunc.h
   \brief    ת������⺯��
   \author   zfj
   \version  1.0
   \date     2015-7-25
 */


#ifndef CLEAR_DEPOT_FUNC_H
#define CLEAR_DEPOT_FUNC_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string>

#include "comdatatype.h"

using namespace std;

/**
 *@class CClearDepotFunc 
 *@brief ��⺯��
 */
class CClearDepotFunc
{

public:

	/*!
	@brief ���캯��	
	*/
	CClearDepotFunc();

	/*!
	@brief ��������	
	*/
	~CClearDepotFunc();
    
	/*!
	@brief ����������
	@param[in] strInfo   ��ʾ����Ϣ
	@return  1: SUCCESS; 0: FAILURE
	*/
	UINT8 ClearDepot(string &strErr);

	 
};

#endif
