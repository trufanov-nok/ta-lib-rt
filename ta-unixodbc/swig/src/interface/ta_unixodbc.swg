/* SWIG inteface file for TA-Lib compiled with UnixODBC support
 *
 * Tested with SWIG v1.3.21
 */

/* First, swig all the inteface of the original TA-Lib */
%include "ta_libc.swg"

/* Then, swig the additional ODBC interface */
%header %{
#include "ta_unixodbc.h"
%}

%include "ta_unixodbc.h"

