#include <windows.h>

#include <string>
using namespace std;

#include "const_string3.hh"
#include "coldata4.hh"

template class mysql_ColData<string>;
template class mysql_ColData<const_string>;
