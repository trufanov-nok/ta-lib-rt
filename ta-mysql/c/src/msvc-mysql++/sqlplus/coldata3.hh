#ifndef __coldata3_hh__
#define __coldata3_hh__

#include <string>
using namespace std ;

#include <mysql.h>
#include "coldata2.hh"
#include "convert3.hh"
#include "null3.hh"

template <class Str, class T, class B> 
mysql_ColData<Str>::operator Null<T,B> () const {
  if ((*this)[0] == 'N' && (*this)[1] == 'U' && 
      (*this)[2] == 'U' && (*this)[3] == 'L' && size() == 4)
    return Null<T,B>(null);
  else return Null<T,B>(conv(T()));
}

#endif
