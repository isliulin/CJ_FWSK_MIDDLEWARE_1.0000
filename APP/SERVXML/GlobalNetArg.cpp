
/*! \file     GlobalNetArg.cpp
   \brief   款机与局端交互的全局变量
   \author   yy
   \version  1.0
   \date     2015 
*/

#include "VersionConfig.h"
#include "commonFunc.h"
#include "GlobalNetArg.h"


#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

CGlobalNetArg* CGlobalNetArg::m_gNetArg = NULL;
CGlobalNetArg *g_gNetArg = NULL;



CGlobalNetArg::CGlobalNetArg()
{
	DBG_PRINT(("进入CGlobalNetArg::CGlobalNetArg()"));
	//-----------------------------------
	m_nsrsbh = "";			/**< 企业税号 */
	m_fxsh = "";				/**< 发行税号 */
	m_hxsh = "";				/**< 哈希税号 */
	m_kpjh = "";				/**< 开票机号，没有开票机号时值为0 */
	m_sbbh = "";				/**< 税控设备编号 */
	m_slxlh = "";			/**< 受理序列号 (取发票上传结果用)*/
	m_addrno = "";
	m_dcbb = "";
	m_servIP = "";
	m_servPort = "";
	m_servAddr = "";
	m_strzskl = "";
	
	DBG_PRINT(("退出CGlobalNetArg::CGlobalNetArg()"));
}

CGlobalNetArg::~CGlobalNetArg()
{
	if(m_gNetArg != NULL)
	{
		delete m_gNetArg;
		m_gNetArg = NULL;
	}
}

CGlobalNetArg* CGlobalNetArg::GetInstance()
{
	if (m_gNetArg == NULL)
	{
		m_gNetArg = new CGlobalNetArg();
	}

	DBG_RETURN(m_gNetArg);
}

//--------------------------------------------------
//初始化公共参数值
//--------------------------------------------------
UINT8 CGlobalNetArg::InitGlobalNetArg(string nsrsbh, string fxsh, string hxsh,				
								string  kpjh, string sbbh,	string slxlh)			
{
	DBG_PRINT(("InitGlobalNetArg"));
	
	m_nsrsbh = nsrsbh;			/**< 企业税号 */
	m_fxsh = fxsh;				/**< 发行税号 */
	m_hxsh = hxsh;				/**< 哈希税号 */
	m_kpjh = kpjh;				/**< 开票机号，没有开票机号时值为0 */
	m_sbbh = sbbh;				/**< 税控设备编号 */
	m_slxlh = slxlh;			/**< 受理序列号 (取发票上传结果用)*/

	DBG_PRINT(("退出InitGlobalNetArg函数"));
	DBG_RETURN(SUCCESS);
}

void CGlobalNetArg::SetBaseInfo(string nsrsbh, string kpjh, string sbbh)
{
	m_nsrsbh = nsrsbh;			/**< 企业税号 */
	m_kpjh = kpjh;				/**< 开票机号，没有开票机号时值为0 */
	m_sbbh = sbbh;				/**< 税控设备编号 */
}
void CGlobalNetArg::SetHashNo(string hxsh, string addrNo)
{
	m_hxsh = hxsh;				/**< 哈希税号 */
	m_addrno = addrNo;
}
void CGlobalNetArg::SetIssueNo(string fxsh)
{
	m_fxsh = fxsh;
}
void CGlobalNetArg::SetDcbb(string dcbb)
{
	m_dcbb = dcbb;
}
void CGlobalNetArg::SetSlxlh(string slxlh)
{
	m_slxlh = slxlh;			/**< 受理序列号 (取发票上传结果用)*/
}

void CGlobalNetArg::SetZskl(string zskl)
{
	m_strzskl = zskl;
}
void CGlobalNetArg::SetServId(string servId)
{
	m_servId = servId;
}
void CGlobalNetArg::SetNsrsbh(string nsrsbh)
{
	m_nsrsbh = nsrsbh;
}

void CGlobalNetArg::SetServPara(string servip, string servport, string servaddr)
{
	m_servIP = servip;
	m_servPort = servport;
	m_servAddr = servaddr;
}









