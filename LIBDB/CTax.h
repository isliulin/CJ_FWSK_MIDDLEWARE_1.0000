#ifndef __CTax_H
#define __CTax_H

#include "CTable.h"
#include "CDB.h"

namespace middleware
{
/**
 *@class CTax 
 *@brief ��ҵ��Ϣ��
 *@brief ��ҵ��Ϣ
 */
class CTax : public CTable
{
public:

	/*!
	@brief ���캯��	
	@attention   ���ע��
	*/ 
	CTax();

    /*!
	@brief ��������	
	*/
	~CTax();

	 /*!
	@brief ��������	
	*/
	void ResetTax();

    UINT32 m_no;		/**< ��� */
	UINT32 m_sl;        /**< ˰�� */
	string m_backup;    /**< ���� */	
};
}
#endif



