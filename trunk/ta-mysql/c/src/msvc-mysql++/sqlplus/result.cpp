#include <windows.h>

#include "result3.hh"

//--------------------------------------------------------------
ResUse::ResUse (MYSQL_RES *result, Connection *m, bool te)
  : mysql(m), throw_exceptions(te), initialized(false), _fields(this)
{
	if (!result) {
		mysql_res=0; _types=0; _names=0; return;
	}
	mysql_res=result;
	_names= new FieldNames(this);
	if (_names)
		_types= new FieldTypes(this);
	_table = fields(0).table;
	initialized = true;
}
//---------------------------------------------------------------
ResUse::~ResUse ()
{
  if (mysql) mysql->unlock(); purge();
}
//------------------------------------------------------------------
Row ResUse::fetch_row()
{
    if (!mysql_res)
    {
       if (throw_exceptions) throw BadQuery("Results not fetched");
       else return Row();
    }
    MYSQL_ROW row = mysql_fetch_row(mysql_res);
    unsigned int* length = (unsigned int*) mysql_fetch_lengths(mysql_res);
    if (!row || !length)
    {
       if (throw_exceptions) throw BadQuery("Bad row");
       else return Row();
    }
    return Row(row, this, length, throw_exceptions);
}
//---------------------------------------------------------------------------
unsigned int  ResUse::num_fields() const
{
       unsigned int num = mysql_num_fields(mysql_res);
       return num ;
}
//-------------------------------------------------------------------
void ResUse::purge(void)
{
     if (mysql_res) mysql_free_result(mysql_res);
     mysql_res=0;
     if (_names) delete _names;
     if (_types) delete _types;
     _names=0; _types=0;
     _table.erase();
}
//---------------------------------------------------------------------
void ResUse::copy(const ResUse& other)
{
     if (!other.mysql_res)
     {
        mysql_res=0; _types=0; _names=0; return;
     }
     if (initialized) purge();
     throw_exceptions = other.throw_exceptions;
     mysql_res = other.mysql_res;
     _fields   = other._fields;
     if (other._names) _names = new FieldNames(*other._names);
     else _names     = NULL;

     if (other._types) _types = new FieldTypes(*other._types);
     else _types     = NULL;
     mysql = other.mysql;
     initialized = true;
}
//================================================================
