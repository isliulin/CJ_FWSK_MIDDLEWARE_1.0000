/*! \file pos_debug.h
   \brief ���ļ���Ҫ������һЩͨ�õ��Խӿ�,����������ڡ����ڵ��Խӿ�
		  ��ͨ������Ϣ��ӡ�ӿڣ����Խӿ�
   \author zyk
 */


#ifdef __cplusplus 
extern "C" {  
#endif
#include <stdlib.h>

#ifdef	DBG_PRN
#undef	DBG_PRN
#endif
#ifdef	DBG_ASSERT_EXIT
#undef	DBG_ASSERT_EXIT
#endif
#ifdef	DBG_ASSERT_WARNING
#undef	DBG_ASSERT_WARNING
#endif
#ifdef	DBG_ENTER
#undef	DBG_ENTER
#endif
#ifdef	DBG_LEAVE
#undef	DBG_LEAVE
#endif
#ifdef	DBG_RETURN
#undef	DBG_RETURN
#endif
#ifdef	DBG_VOID_RETURN
#undef	DBG_VOID_RETURN
#endif
	

#ifdef NO_POS_DEBUG
#undef POS_ENTER_ON
#undef POS_DBGPRN_ON
#undef POS_ASSERT_ON
#endif

#if !defined(POS_ENTER_ON) && !defined(POS_DBGPRN_ON) && !defined(POS_ASSERT_ON)
#define NO_POS_DEBUG
#endif
	
#ifndef NO_POS_DEBUG
	/*! ������Ϣ��ӡ�ӿڿ��أ�0���رգ�1���� */
	extern int _g_dbg_on_;
	/*! ������ڡ����ڵ��Կ��أ�0���رգ�1����*/
	extern int _g_dbg_enter_exit_on_;
	/*! ���Ե��Կ��أ�0���رգ�1����*/
	extern int _g_assert_on_;

	/*! \brief ��¼������������ӡ���������Ϣ
		\param[in] _func_name_ ��������
		\param[in] _file_name_ �ļ���
		\param[in] _line_no_ �к�
		\param[out] _sfunc_name_ ���Ҫ��¼�ĺ�����
	*/
	extern void _dbg_enter_ (const char *_func_name_,
				  const char *_file_name_,
				  unsigned int _line_no_,
				  const char **_sfunc_name_);
    /*! \brief ��ӡ����������Ϣ
		\param[in] _file_name_ �ļ���
		\param[in] _line_no_ �к�
		\param[int] _sfunc_name_ ������
    */
	extern void _dbg_return_ (const char *_file_name_,
				   unsigned int _line_no_,
				   const char ** _sfunc_name_);

	/*! \brief ��¼�ļ������кš��ؼ�����Ϣ
		\param[in] _keyword_ �ؼ���
		\param[in] _file_name_ �ļ���
		\param[in] _line_no_ �к�
	*/
	extern void _dbg_pargs_ (const char * _keyword_,
				  const char * _file_name_,
				  unsigned int _line_no_);
	/*! \brief ��ӡ������Ϣ
		\param[in] fmt ��ʽ������ĸ�ʽ��
		\param[in] ... �ɱ������
	*/
	extern void _dbg_prnt_ (const char *fmt,...);
#endif

//-----------------------------------------------------------------
#ifndef POS_ENTER_ON
#	define DBG_ENTER(f1)
#	define DBG_RETURN(a1) return(a1)
#	define DBG_VOID_RETURN return
#else
	/*! \def DBG_ENTER(f1)
		\brief ��¼�ʹ�ӡ������ڵ�����Ϣ
		\param f1 ������
		\attention ����DBG_ENTER �ں�����ջ�ռ��Ϸ���ռ䣬
		���������������п�ִ�����֮ǰִ��
	*/
#	define DBG_ENTER(f1) \
	const char *_dbg_func_name_=NULL; \
	_dbg_enter_ (f1,__FILE__,__LINE__,&_dbg_func_name_) 
	/*! \def DBG_LEAVE
		\brief ��ӡ����������Ϣ
	*/
#	define DBG_LEAVE \
	(_dbg_return_(__FILE__,__LINE__,&_dbg_func_name_))
    /*! \def DBG_RETURN(a1)
		\brief ��ӡ�з���ֵ�ĺ����ĳ�����Ϣ
	    \param [in] �����ķ���ֵ   
	*/
#	define DBG_RETURN(a1) return(DBG_LEAVE, a1)
    /*! \def DBG_VOID_RETURN 
		\brief ��ӡ�з���ֵ�ĺ����ĳ�����Ϣ
	*/
#	define DBG_VOID_RETURN {DBG_LEAVE; return;}
#endif

//------------------------------------------------------------------//
#ifndef POS_DBGPRN_ON
#	define DBG_PRN(keyword,arglist)
#else
    /*! \def DBG_RETURN(a1)
		\brief ��ӡ�з���ֵ�ĺ����ĳ�����Ϣ
	*/
#	define DBG_PRN(keyword,arglist) \
	{ if(_g_dbg_on_ !=0 ) { _dbg_pargs_(keyword,__FILE__,__LINE__); _dbg_prnt_ arglist ; }}

#endif

//---------------------------------------------------------------------//
#ifndef  POS_ASSERT_ON
#	define DBG_ASSERT_EXIT(condition, arglist)
#	define DBG_ASSERT_WARNING(condition, arglist)
#else
	/*! \def  DBG_ASSERT_EXIT(condition,arglist)
		\brief �����������,���������Ϊ�����˳�����
		\param[in] condition ��������
		\param[in] arglist �ɱ������
	*/
#	define DBG_ASSERT_EXIT(condition,arglist) \
	{ \
		if(_g_assert_on_) \
		{ \
			if(condition) { NULL;} \
			else{_dbg_pargs_("ASSERT ERROR",__FILE__,__LINE__); _dbg_prnt_ arglist; exit(1) ;} \
		} \
	}
	/*! \def  DBG_ASSERT_WARNING(condition,arglist)
		\brief һ�㾯�����,���������Ϊ�����������
		\param[in] condition ��������
		\param[in] arglist �ɱ������
	*/	
#   define DBG_ASSERT_WARNING(condition,arglist) \
	{ \
		if(_g_assert_on_) \
		{ \
			if(condition) { NULL;} \
			else{_dbg_pargs_("ASSERT WARNING",__FILE__,__LINE__); _dbg_prnt_ arglist ; } \
		} \
	}
#endif
	

#ifdef __cplusplus 
} 
#endif


