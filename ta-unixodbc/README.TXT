This package provides the support of unixodbc for TA-Lib.

This works currently only on a Linux platform.
(Windows users can enjoy a build-in ODBC support in TA-lib).

To use this package you have to:

(1) Link your application to ta-unixodbc/lib/ta_unixodbc_XXX.lib

(2) Link your application to ta-lib/c/lib/ta_libc_XXX.lib

(3) Link your application with unixODBC (add -lodbc option). You must
    indepedently download and install unixODBC on your system.

(4) Call TA_Initialize() of TA-Lib.

(5) Call TA_UNIXODBC_Initialize() of ta-unixodbc.

(6) Respect the unixODBC License.

See also ta-unixodbc/c/src/demo/ta_sql for an example.

For questions, visit http://ta-lib.org and use the mailing list.

============
Tested Setup
============
Debian GNU/Linux 3.1 (sarge)
unixodbc 3.52, version 2.2.4
gcc 3.3
libmyodbc version 2.50.39

This is not a requirement list, this library is expected to work
with other setups as well.
