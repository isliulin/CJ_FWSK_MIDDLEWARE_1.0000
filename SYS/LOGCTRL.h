/*! \file LOGCTRL.h
   \brief ���ļ�������һЩ����LOG����ĺ꿪��
   \note ���ļ���������Ӧ����poslog.h��pos_debug.h֮ǰ
   \author zyk
 */


#ifndef LIB_VER_POS_ZYK_H
#define LIB_VER_POS_ZYK_H
//-----------------------------------------
//�˴��ĺ궨�岻���޸�
#ifdef NO_POS_DEBUG
#undef NO_POS_DEBUG
#endif

#ifdef POS_ENTER_ON
#undef POS_ENTER_ON
#endif
#ifdef POS_DBGPRN_ON
#undef POS_DBGPRN_ON
#endif
#ifdef POS_ASSERT_ON
#undef POS_ASSERT_ON
#endif

#ifdef POS_DEBUG_TO_FILE
#undef POS_DEBUG_TO_FILE
#endif
#ifdef POS_DEBUG_TO_SERIAL
#undef POS_DEBUG_TO_SERIAL
#endif
#ifdef POS_DEBUG_TO_TTY
#undef POS_DEBUG_TO_TTY
#endif
//-----------------------------------------
//���º궨������޸�
//#define NO_POS_DEBUG //�ر��������̵�log��Ϣ

//#define POS_ENTER_ON
#define POS_DBGPRN_ON
#define POS_ASSERT_ON

//#define POS_DEBUG_TO_FILE
//#define POS_DEBUG_TO_SERIAL
#define POS_DEBUG_TO_TTY

//���ݿ���ʵ�Ԫ���Կ���
#define POS_DBA_UNIT_TEST

#endif 
