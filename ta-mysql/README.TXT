This package provides the support of MySQL for TA-Lib.

It works currently only on a WIN32 platform.

You application needs to use the multithreaded DLL run-time library e.g. make sure the "Use run-time library" setting is "Multithreaded DLL"

To use this package you have to:

(1) Link your application to ta-mysql\lib\ta_mysql_cdr.lib

(2) Link your application to ta-lib\c\lib\ta_libc_cdr.lib

(3) Copy ta-mysql\c\src\msvc-mysql++\mysql\lib\libmySQL.dll 
    in the directory of your executable.

(4) Call TA_Initialize() of TA-Lib.

(5) Call TA_MYSQL_Initialize() of TA-MySQL.

(6) Respect the MySQL GPL License.

For questions, visit http://ta-lib.org and use the mailing list.

