This package provides the support of unixodbc for TA-Lib.

This works currently only on a Linux platform.

To use this package you have to:

(1) Link your application to ta-unixodbc\lib\ta_unixodbc_XXX.lib

(2) Link your application to ta-lib\c\lib\ta_libc_XXX.lib

(3) Link your application with unixODBC. You must indepedently
    download and install it on your system.

(4) Call TA_Initialize() of TA-Lib.

(5) Call TA_UNIXODBC_Initialize() of TA-unixodbc.

(6) Respect the unixODBC License.

For questions, visit http://ta-lib.org and use the mailing list.

