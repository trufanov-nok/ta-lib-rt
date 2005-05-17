#!/usr/bin/perl -p
#
# Script generating the UnixODBC-enabled ta_sql
#

$_ .= "#include \"ta_unixodbc.h\"\n" if /^#include "ta_libc\.h"$/;
$_ .= "   if (retCode == TA_SUCCESS) retCode = TA_UNIXODBC_Initialize();\n" if /\bTA_Initialize\b/;
