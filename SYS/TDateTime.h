/*! \file    TDateTime.h
   \brief    ����ʱ��ӿڷ�װ
   \author   zyk
   \date     2005-04-04
 */

#ifndef _LIB_POS_DATETIME_ZYK_H_
#define _LIB_POS_DATETIME_ZYK_H_
#include <string>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>

#ifndef WIN32
#include <sys/ioctl.h>
#include <linux/rtc.h>
#include <sys/ioctl.h>

#include <sys/types.h>
#include <sys/timeb.h>
#include <unistd.h>
#endif

using namespace std;

namespace middleware
{


/** @brief ö�����ͣ���������ʱ���ʽ */
enum TDateTimeFormat {  
			YYYYMMDDHHMMSS,		/**< ��(4λ)����ʱ���� */
			YYMMDDHHMMSS,		/**< ������ʱ���� */
			YYYYMMDD,			/**< ��(4λ)���� */
			YYMMDD,				/**< ������ */
			HHMMSS,				/**< ʱ���� */
			YYYYMMDDHHMM		/**< ��(4λ)����ʱ�� */
};

/** @brief ö�����ͣ�����ʱ���ʽ��־  */
enum TDateTimeFlag {DATE_POS, TIME_POS, DATETIME_POS};


/*!
@class TDateTime
@brief ����ʱ����
*/
class TDateTime
{
public:
	
	/*!
	@brief ���캯������ʼһ����Чʱ�䡣
	*/
	TDateTime();

	/*!
	@brief ���캯������������TDateTime��ʱ�䡣
	*/
	TDateTime(const TDateTime& src);

	/*!
	@brief ���캯������ʼ��Ϊ�������ַ���ʱ�䡣
	*/
	TDateTime(const char * src, TDateTimeFlag flag = DATE_POS);

	/*!
	@brief ���캯������ʼΪ��������������ֵ��
	*/
	TDateTime(unsigned int   year, unsigned int   month, unsigned int   day);

	/*!
	@brief ���캯������ʼΪ������ʱ������ֵ��
	*/
	TDateTime(unsigned int   hour, unsigned int   min, unsigned int   sec,unsigned int   timeflag);

	/*!
	@brief ���캯������ʼΪ������������ʱ������ֵ��
	*/
	TDateTime(unsigned int   year, unsigned int   month, unsigned int   day,
		  unsigned int   hour, unsigned int   min, unsigned int   sec);
	
	/*!
	@brief ���캯������ʼΪ������������ʱ������������ֵ��
	*/
    TDateTime(unsigned int date, unsigned int time);


	/*!
	@brief ȡ��ǰ����ʱ��	
	@return  ��ǰ����ʱ�䣨TDateTime���ͣ�
	*/
	static TDateTime CurrentDateTime();

	/*!
	@brief ȡ��ǰ����	
	@return  ��ǰ���ڣ�TDateTime���ͣ�
	*/
	static TDateTime CurrentDate();

	/*!
	@brief ����������ʱ������Ϊϵͳ��ǰʱ��	
	@param[in] rhs ��ǰ����ʱ�䣨TDateTime���ͣ�
	@return  true-�ɹ���false-ʧ��
	*/
	static bool SetCurrentDateTime(TDateTime& rhs);
	
	/*!
	@brief ��������������Ϊϵͳ��ǰ����	��ʱ��Ĭ��Ϊ0:0:0��
	@param[in] rhs ��ǰ���ڣ�TDateTime���ͣ�
	@return  true-�ɹ���false-ʧ��
	*/
	static bool SetCurrentDate(TDateTime& rhs);



	/*!
	@brief ����������ʱ��ת��Ϊstring��ʽ�����
	@param[in] format �����ʽ�����ͣ�ʹ��TDateTimeFormatö��ֵ������
	@param[in] formatstr ָ������������ʽ��
	@note ���磺
	  formatstr="%04u-%02u-%02u %02u:%02u:%02u",format=YYYYMMDDHHMMSS��
	  formatstr="%u��%u��%u��", format=YYYYMMDD��
	  formatstr="%02u:%02u:%02u",format=HHMMSS��
	*/
	string FormatString(TDateTimeFormat format=YYYYMMDD,
			    const char *formatstr=NULL);

	/*!
	@brief ����������ʱ��ת��ΪUINT32���������
	@param[in] format �����ʽ�����ͣ�ʹ��TDateTimeFormatö��ֵ������
	@param[in] formatstr �˲�������
	@warning ����formatֻ����YYYYMMDD��HHMMSS��������
	*/
    unsigned int FormatInt(TDateTimeFormat format=YYYYMMDD,
			    const char *formatstr=NULL);


	/*!
	@brief �ж������Ƿ�Ϸ�
	@return 0-���Ϸ�; 
			1-�Ϸ�
	*/
	static int DateIsValid(unsigned int   year, unsigned int   month, unsigned int   day);

	/*!
	@brief �ж�ʱ���Ƿ�Ϸ�
	@return 0-���Ϸ�
			1-�Ϸ�
	*/
	static int TimeIsValid(unsigned int   hour, unsigned int   min, unsigned int   sec);

	/*!
	@brief �ж��Ƿ���ƽ�� 
	@return 
	  0-����
	  1-��
	*/
	static int IsLeapYear(unsigned int   year);

	static double ComposeDate(unsigned int   year, unsigned int   month, unsigned int   day);

	static double ComposeTime(unsigned int   hour, unsigned int   min, unsigned int   sec);	 

	static int DecodeDateString(const char *src,
				    unsigned  int &year,
				    unsigned  int &month,
				    unsigned  int &day);

	static int DecodeTimeString(const char *src,
				    unsigned  int &hour,
				    unsigned  int &min,
				    unsigned  int &sec);

	static int DecodeDateTimeString(const char *src,
					unsigned  int &year,
					unsigned  int &month,
					unsigned  int &day,
					unsigned  int &hour,
					unsigned  int &min,
					unsigned  int &sec);

	int DateIsValid(void);

	int TimeIsValid(void);

	int DateTimeIsValid(void);

	int IsLeapYear();

	TDateTime MonthBegin(const TDateTime& rhs);

	TDateTime MonthEnd(const TDateTime& rhs);

	TDateTime MonthAdd(const TDateTime& rhs, int Months);

	TDateTime HourAdd(const TDateTime& rhs, int addHours);


	int DayOfWeek()const;

	unsigned int DayOfMonth(void)const;

	unsigned int Year(void)const;

	unsigned int Month(void)const;

	unsigned int Hour(void)const;

	unsigned int Minute(void)const;

	unsigned int Second(void)const;

	TDateTime& operator =(const TDateTime& rhs)
		{
			Val = rhs.Val;
			return *this;
		};

 	TDateTime& operator +=(const int days)
 		{
 			Val += days;
 			return *this;
 		};

	TDateTime& operator -=(const int days)
		{
			Val -= days;
			return *this;
		};
	
	TDateTime& operator ++()
		{
			Val++;
			return *this;
		};
	
	TDateTime operator ++(int)
		{
			TDateTime tmp(*this);
			Val++;
			return tmp;
		};
	
	TDateTime& operator --()
		{
			Val--;
			return *this;
		};

	TDateTime operator --(int)
		{
			TDateTime tmp(*this);
			Val--;
			return tmp;
		};
	

	TDateTime operator +(const int days)const
		{
			return Val + days;
		};
	
	int  operator -(const TDateTime& rhs)const
		{
			return int(Val - rhs.Val);
		};
	

	bool operator ==(const TDateTime& rhs)const ;
        /*
	  {
	  return Val == rhs.Val;
	  };
        */
	
/*
  bool operator !=(const TDateTime& rhs)const
  {
  return Val != rhs.Val;
  };
  bool operator >(const TDateTime& rhs)const
  {
  return Val > rhs.Val;
  };
  bool operator <(const TDateTime& rhs)const
  {
  return Val < rhs.Val;
  };
  bool operator >= (const TDateTime& rhs)const
  {
  return Val >= rhs.Val;
  };
  bool operator <= (const TDateTime& rhs)const
  {
  return Val <= rhs.Val;
  };
*/
	bool operator !=(const TDateTime& rhs)const;
	bool operator >(const TDateTime& rhs)const;
	bool operator <(const TDateTime& rhs)const;
	bool operator >= (const TDateTime& rhs)const;
	bool operator <= (const TDateTime& rhs)const;

	///////////////////////////////////////////////////////////////////
 public:
	static const int AggregatedDaysInMonths[2][13];
	static const int DaysInMonths[2][13];
	static const char *Days[2][7];
	static const char *Months[2][12];
 public:
        double Val;
	void DecodeDate(unsigned int  & year, unsigned int  & month, unsigned int  & day)const;
	void DecodeTime(unsigned int  & hour, unsigned int  & min, unsigned int  & sec)const;
	TDateTime(const double src)
		{
			Val = src;
		
		};
	TDateTime(const int src)
		{
			Val = src;
		};	
	TDateTime& operator =(const double rhs)
		{
			Val = rhs;
			return *this;
		};
	
	TDateTime& operator = (const int rhs)
		{
			Val = rhs;
			return *this;
		};
	

	TDateTime& operator +=(const double rhs)
		{
			Val += rhs;
			return *this;
		};
	


	TDateTime& operator -=(const TDateTime& rhs)
		{
			Val -= rhs.Val;
			return *this;
		};

	TDateTime& operator -=(const double rhs)
		{
			Val -= rhs;
			return *this;
		}; 
	
	TDateTime operator +(const TDateTime& rhs)const
		{
			return Val + rhs.Val;
		};
	TDateTime operator +(const double rhs)const
		{
			return Val + rhs;
		};
	TDateTime operator -(const double rhs)
		{
			return Val - rhs;
		};
	
	TDateTime operator -(const int rhs)
		{
			return Val -rhs;
		};
	operator double()const
		{
			return Val;
		};

	operator int()const
		{
			return (int)Val;
		};
};

}
#endif
