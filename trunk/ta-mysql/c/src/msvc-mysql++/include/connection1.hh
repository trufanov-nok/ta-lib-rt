#ifndef __connection1_hh__
#define __connection1_hh__

#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
using namespace std ;

#include <mysql.h>
#include "define_short.h"
#include "bad_query.hh"
#include "query1.hh"
#include "result1.hh"

//The main database handle
class Connection
{
  friend ResNSel;
  friend ResUse;
  friend Query;

private:
  bool throw_exceptions;
  MYSQL mysql;
  bool is_connected;
  bool locked;
  bool Success;

public:
  Connection () : throw_exceptions(true), locked(false)
    {mysql_init(&mysql);} //:
  Connection (bool te) : throw_exceptions(te), is_connected(false), locked(true), Success(false) //:
    {mysql_init(&mysql);} //:
  Connection (const char *db, const char *host = "", const char *user = "",
	      const char *passwd = "", bool te = true); //:
  Connection (const char *db, const char *host, const char *user,
	      const char *passwd, uint port, my_bool compress = 1,
	      unsigned int connect_timeout = 5, bool te = true,
	      cchar *socket_name = ""); //:

  bool   real_connect (cchar *db = "", cchar *host = "",
		       cchar *user = "", cchar *passwd = "", uint port = 0,
		       my_bool compress = 0, unsigned int connect_timeout = 60,
		       cchar *socket_name= ""); //:

  ~Connection (); //:
  void         close() {mysql_close(&mysql);}	 //:
  string       info ();	//:

  bool   connected() const {return is_connected;}
  //: returns true if a successful connection was made

  bool   success() {return Success;}
  //: returns true of the last query was successful

  bool   connect (cchar *db = "", cchar *host = "",
		  cchar *user = "", cchar *passwd = "");
  //:

  bool   lock() {if (locked) return true; locked = true; return false;}
  void   unlock() {locked = false;}

  void purge (void) {mysql_close(&mysql); }
  //:

  inline Query query();
  //:

  operator bool () {return success();}                  //: returns success()
  string error () {return string(mysql_error(&mysql));} //: last error message()
	int errnum () {return mysql_errno(&mysql);}
	int   refresh (unsigned int refresh_options){ return mysql_refresh (&mysql,refresh_options); }
	int ping (void) { return mysql_ping(&mysql);}
	int kill (unsigned long pid) { return mysql_kill (&mysql,pid);}
  string clinet_info () {return string(mysql_get_client_info());} //:

  string host_info () {return string(mysql_get_host_info(&mysql));} //:

  int    proto_info () {return mysql_get_proto_info(&mysql);} //:

  string server_info () {return string(mysql_get_server_info(&mysql));} //:

  string stat() {return string(mysql_stat(&mysql));} //:

  Result  store(const string &str) {return store(str, throw_exceptions);} //:
  ResUse  use(const string &str)   {return use(str, throw_exceptions);} //:
  ResNSel execute(const string &str) {return execute(str, throw_exceptions);} //:
	bool exec (const string &str);
  Result  store(const string &str, bool te); //:
  ResUse  use(const string &str, bool te); //:
  ResNSel execute(const string &str, bool te); //:

  bool   create_db (string db) {return !(execute( "CREATE DATABASE " + db ));} //:
  bool   drop_db (string db) {return !(execute( "DROP DATABASE " + db ));} //:
  bool   select_db (string db) {return select_db(db.c_str());} //:
  bool   select_db (const char *db); //:
  bool   reload(); //:
  bool   shutdown (); //:
	string infoo (void) {return info ();}
	st_mysql_options get_options (void) const {return mysql.options;}
	int read_options(enum mysql_option option,const char *arg) {return  mysql_options(&mysql, option,arg);}
  int          affected_rows()  {return mysql_affected_rows((MYSQL*) &mysql);}
  int          insert_id () {return mysql_insert_id(&mysql);}


  // FIX:
  // implementation of template function must be done in the class definition
  // (instead of connection2.hh), otherwise Visual C++ gives template
  // matching errors

  template <class Sequence>
  void storein_sequence(Sequence &seq, const string &str) {
    ResUse result = use(str);
    while (1) {
	    MYSQL_ROW d = mysql_fetch_row(result.mysql_res);
		  if (!d) break;
	    Row row(d,&result,(unsigned int *)mysql_fetch_lengths(result.mysql_res),true);
		  if (!row) break;
      seq.push_back(/*typename*/ Sequence::value_type(row));
	  }
	}

  template <class Set>
  void storein_set(Set &sett, const string &str) {
    ResUse result = use(str);
	  while (1) {
	    MYSQL_ROW d = mysql_fetch_row(result.mysql_res);	
		  if (!d) return;
	    Row row(d,&result,(unsigned int *)mysql_fetch_lengths(result.mysql_res),true);
		  if (!row) break;
      sett.insert(typename Set::value_type(row));
	  }
  }

  //!dummy: void storein(TYPE &con, const string &s);
  //: Stores the results in TYPE.
  // Stores the result in TYPE. TYPE must be some sort of STL container.

  template <class T>        void storein(vector<T> &con, const string &s)
    {storein_sequence(con,s);}
  template <class T>        void storein(deque<T> &con, const string &s)
     {storein_sequence(con,s);}
  template <class T>        void storein(list<T> &con, const string &s)
    {storein_sequence(con,s);}
  template <class T>        void storein(set<T> &con, const string &s)
    {storein_set(con,s);}
  template <class T>        void storein(multiset<T> &con, const string &s)
    {storein_set(con,s);}
};

typedef Connection Mysql;

#endif





