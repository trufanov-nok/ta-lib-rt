/* File : ta_libc.i */

%module "Finance::TA"

%{
#include "../../../../c/include/ta_libc.h"
%}


%include "typemaps.i"


/* Strip all const qualifies, they are not relevant to Perl,
 * but may prevent SWIG release memory in proxy classes.
 * This is safe cecause TA-Lib never sets returned const char pointers
 * to anything in static (data) area by itself.
 */
#define const


/************************************************************************/

/* The constants below are pulled out from <limits.h> and used by ta_defs.h 
 * to define some TA-specific constants.
 * They have to be redefined here otherwise Swig would not be able
 * to determine the values of some TA constants and would skip them.
 * The limit.h constants themselves do not need to be exported by the module;
 * that's why they are tagged %ignore
 */

%ignore INT_MAX;
%ignore INT_MIN;
#define INT_MAX 2147483647
#define INT_MIN -INT_MAX-1

%include "../../../../../c/include/ta_defs.h"


/************************************************************************/

/* fatal handler is not supported (yet) */
%ignore TA_FatalReport;
%ignore TA_FatalReportToBuffer;
%ignore TA_SetFatalErrorHandler;

/* oputput parameters of TA_GetDate */
%apply unsigned int *OUTPUT { unsigned int *year, unsigned int *month, unsigned int *day };

/* oputput parameters of TA_GetTime */
%apply unsigned int *OUTPUT { unsigned int *hour, unsigned int *min, unsigned int *sec };

/* output parameter of TA_TimestampDeltaXxxx functions */
%apply unsigned int *OUTPUT { unsigned int *delta }

%include "../../../../../c/include/ta_common.h"

/* clearing typemaps to avoid potential future problems in other header files */
%clear unsigned int *year, unsigned int *month, unsigned int *day;
%clear unsigned int *hour, unsigned int *min, unsigned int *sec;
%clear unsigned int *delta;


/************************************************************************/
/* under test */

%ignore TA_WebFetch;

typedef unsigned int TA_UDBase;

#ifdef SWIGPERL

/* typemaps for TA_UDBaseAlloc */

/* as argout (my first try)
 * Example:
 * @res = TA_UDBaseAlloc();
 * $udb = $res[1] if $res[0] == $TA_SUCCESS;

%typemap(arginit) TA_UDBase **newUDBase(TA_UDBase *temp) 
	"$1 = &temp;";

%typemap(argout) TA_UDBase **newUDBase {
	if (argvi >= items) {
		EXTEND(sp,1);
	}
	$result = sv_newmortal();
	SWIG_MakePtr($result, (void *) *$1, $*1_descriptor, 0);
	argvi++;
}
*/

/* as reference (Perl specific, maybe more convenient)
 * Example:
 * $ret = TA_UDBaseAlloc(\$udb);
 */
%typemap(in) TA_UDBase **newUDBase($*1_ltype temp) {
	SV *tempsv;
	if (!SvROK($input)) {
		SWIG_croak("Expected a reference as argument $argnum of $symname");
	}
	tempsv = SvRV($input);
	if (SWIG_ConvertPtr(tempsv, (void **) &temp, $*1_descriptor, 0) < 0) {
		SWIG_croak("Type error in argument $argnum of $symname. Expected $*1_mangle");
	}
    $1 = &temp;
}

%typemap(argout) TA_UDBase **newUDBase {
	SV *tempsv;
	tempsv = SvRV($input);
	SWIG_MakePtr(tempsv, (void *) *$1, $*1_descriptor, 0);
}

#endif

%ignore hiddenData;
%ignore new_TA_History;

%include "../../../../../c/include/ta_data.h"


/************************************************************************/
/* untested */

%include "../../../../../c/include/ta_func.h"


/************************************************************************/
/* untested */

%include "../../../../../c/include/ta_pm.h"
