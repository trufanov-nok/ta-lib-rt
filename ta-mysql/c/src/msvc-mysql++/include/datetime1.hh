#ifndef __datetime1_hh__
#define __datetime1_hh__

#include <string>
#include <strstream>
#include <iostream>
using namespace std ;

#include "defs.h"
#include "define_short.h"
#include "coldata1.hh"
#include "stream2string1.hh"
#include "tiny_int1.hh"

//-------------------------------------------------------------------------
struct mysql_dt_base
{
  virtual ostream& out_stream(ostream&) const = 0;

  operator string () const;
};

//--------------------------------------------------------------------------
template <class T>
struct MysqlDTbase
{
  virtual short int compare(const T &other) const = 0;

  bool operator == (const T &other) const {return !compare(other);}
  bool operator != (const T &other) const {return compare(other);}
  bool operator <  (const T &other) const {return compare(other) < 0;}
  bool operator <= (const T &other) const {return compare(other) <= 0;}
  bool operator >  (const T &other) const {return compare(other) > 0;}
  bool operator >= (const T &other) const {return compare(other) >= 0;}
};
//-------------------------------------------------------------------------
struct mysql_date : virtual public mysql_dt_base
{
  short int year;
  tiny_int  month;
  tiny_int  day;

  ostream& out_stream(ostream&) const;
  cchar* convert (cchar*);
  string& convert (string&);

protected:
  short int compare(const mysql_date *other) const;
};
//-------------------------------------------------------------------------
//: A special type for holding mysql Dates.
// Date, a comparable data structures for holding mysql Dates.  It also
// responds to the stream extraction and insertion operator.

struct Date : public mysql_date, public MysqlDTbase<Date>
{
  Date () {};
  Date (cchar* str) {convert(str);}
  Date (const ColData &str);
  Date (const string &str);

  short int compare(const Date& other) const
    {return mysql_date::compare(&other);}
};
//-----------------------------------------------------------------------
inline ostream& operator << (ostream& s, const Date& d)
                                                  {return d.out_stream(s);}
//-------------------------------------------------------------------------
struct mysql_time : virtual public mysql_dt_base
{
  tiny_int hour;
  tiny_int minute;
  tiny_int second;

  ostream& out_stream(ostream&) const;
  cchar* convert (cchar*);
  string& convert (string&);
protected:
  short int compare(const mysql_time *other) const;
};
//-------------------------------------------------------------------------
//: A special type for holding mysql Time.
// Time, a comparable data structures for holding mysql Times.  It also
// responds to the stream extraction and insertion operator.
struct Time : public mysql_time, public MysqlDTbase<Time>
{
  Time () {};
  Time (cchar* str) {convert(str);}
  Time (const ColData &str);
  Time (const string &str);

  short int compare(const Time& other) const
    {return mysql_time::compare(&other);}
};
//-------------------------------------------------------------------------

inline ostream& operator << (ostream& s, const Time& d)
  {return d.out_stream(s);}
//-------------------------------------------------------------------------
//: A combinate of Date and Time for holding mysql DateTime's
//!dummy: struct DateTime {};
struct DateTime : public mysql_date, public mysql_time,
		       public MysqlDTbase<DateTime>
{
  DateTime () {}
  DateTime (cchar* str) {convert(str);}
  DateTime (const ColData &str);
  DateTime (const string &str);

  short int compare(const DateTime& other) const;

  ostream& out_stream(ostream&) const;
  cchar* convert (cchar*);
  string& convert (string&);
};
//-------------------------------------------------------------------------
inline ostream& operator << (ostream& s, const DateTime& d)
                                                   {return d.out_stream(s);}
//-------------------------------------------------------------------------
#endif

