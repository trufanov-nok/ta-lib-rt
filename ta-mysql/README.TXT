This package provides the support of MySQL for TA-Lib.

It works currently only on a WIN32 platform.
Only the cdr and cdd variants of TA-Lib are currently supported.

You application needs to use the multithreaded DLL run-time
library e.g. make sure the  "Use run-time library" setting 
is "Multithreaded DLL" (for cdr) or "Debug Multithreaded DLL"
(for cdd).

To prepare this package you have to:

(1) Compile a cdr or cdd version of the library by running nmake
    in directories ta-mysql\c\make\cdr\win32\msvc or
    ta-mysql\c\make\cdd\win32\msvc respectively

To use this package you have to:

(1) Link your application to ta-mysql\c\lib\ta_mysql_cdr.lib
    or ta-mysql\c\lib\ta_mysql_cdd.lib

(2) Link your application to ta-lib\c\lib\ta_libc_cdr.lib
    ta-lib\c\lib\ta_libc_cdd.lib

(3) Copy ta-mysql\c\src\msvc-mysql++\mysql\lib\libmySQL.dll 
    in the directory of your executable or a directory available on your
    search path.

(4) In your app, include "ta_libc.h" and call TA_Initialize(). 

(5) In your app, include "ta_mysql.h" and call TA_MYSQL_Initialize().

(6) Respect the MySQL GPL License.

For questions, visit http://ta-lib.org and use the mailing list.

==========
Test Setup
==========
 - tested with mysql++ version 1.7.1 for Visual C++ (available in
   subdirectory ta-mysql\c\src\msvc-mysql++).

