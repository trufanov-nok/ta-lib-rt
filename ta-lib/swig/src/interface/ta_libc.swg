/* File : ta_libc.i */

%module "Finance::TA"

%{
#include "../../../../c/include/ta_libc.h"
%}


%include "typemaps.i"


/* Strip all const qualifies, they are not relevant to Perl,
 * but may prevent SWIG release memory in proxy classes.
 * This is safe because TA-Lib never sets returned const char pointers
 * to anything in static (data) area by itself.
 */
%clear const char *;


/** ta_defs *****************************************************************/

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


/** ta_common ***************************************************************/

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


/** ta_data *****************************************************************/
/* under development */

#ifdef SWIGPERL

/* typemaps for TA_UDBaseAlloc */

/* typedef unsigned int TA_UDBase; */

/* pass as reference (Perl specific, maybe more convenient)
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
	if (temp) {
		SWIG_croak("Expected a reference to undef variable as argument $argnum of $symname");
	}
    $1 = &temp;
}

%typemap(argout) TA_UDBase **newUDBase {
	SV *tempsv;
	tempsv = SvRV($input);
	SWIG_MakePtr(tempsv, (void *) *$1, $*1_descriptor, 0);
}


/* typemaps for TA_HistoryAlloc */

/* pass as argout (just to be different than TA_UDBaseAlloc ;-)
 * Example:
 * @res = TA_HistoryAlloc($udb, "US.NASDAQ.STOCK", 
 *                              "LNUX", $TA_DAILY, undef, undef,
 *                              $TA_ALL);
 * $history = $res[1] if $res[0] == $TA_SUCCESS;
 *
 * Clumsy, huh?
 * However in practice, you will use 'new' anyway...
 */

%typemap(in,numinputs=0) TA_History **history(TA_History *temp) 
	"$1 = &temp;";

%typemap(argout) TA_History **history {
	if (argvi >= items) {
		EXTEND(sp,1);
	}
	$result = sv_newmortal();
	SWIG_MakePtr($result, (void *) *$1, $*1_descriptor, SWIG_SHADOW|SWIG_OWNER);
	argvi++;
}

/* accessing members of TA_History */

%typemap(out) TA_Real * {
	AV *myav;
	SV **svs;
	int i = 0;
    int len; 	
    /* How to figure out how many elements we have? 
     * We use a dirty trick knowing that TA_Real* in ta_data.h is used only
     * inside struct TA_History.  I know no better way.  If we were wrong, 
     * compiler error would occur.
     */
    len = arg1->nbBars;  /* hugh... */

	svs = (SV **) malloc(len*sizeof(SV *));
	for (i = 0; i < len ; i++) {
	    svs[i] = sv_newmortal();
	    sv_setnv((SV*)svs[i],$1[i]);
	};
	myav =	av_make(len,svs);
	free(svs);
    $result = newRV((SV*)myav);
    sv_2mortal($result);
    argvi++;    
}

%typemap(out) TA_Integer * {
	AV *myav;
	SV **svs;
	int i = 0;
    int len; 	
    /* How to figure out how many elements we have? 
     * As above.
     */
    len = arg1->nbBars;  /* hugh... */

	svs = (SV **) malloc(len*sizeof(SV *));
	for (i = 0; i < len ; i++) {
	    svs[i] = sv_newmortal();
	    sv_setiv((SV*)svs[i],$1[i]);
	};
	myav =	av_make(len,svs);
	free(svs);
    $result = newRV((SV*)myav);
    sv_2mortal($result);
    argvi++;    
}

%typemap(out) TA_Timestamp * {
	AV *myav;
	SV **svs;
	int i = 0;
    int len; 	
    /* How to figure out how many elements we have? 
     * As above.
     */
    len = arg1->nbBars;  /* hugh... */

	svs = (SV **) malloc(len*sizeof(SV *));
	for (i = 0; i < len ; i++) {
	    svs[i] = sv_newmortal();
        SWIG_MakePtr((SV*)svs[i], (void *) &$1[i], $1_descriptor, SWIG_SHADOW);
	    /* sv_setiv((SV*)svs[i],$1[i]); */
	};
	myav =	av_make(len,svs);
	free(svs);
    $result = newRV((SV*)myav);
    sv_2mortal($result);
    argvi++;    
}

#endif

/* TA_History cannot be created in a standard way.  Use TA_HistoryAlloc
 * and TA_HistoryFree.  Perl module wraps them in a custom constructor
 * and destructor.
 */
%nodefault TA_History;

/* nbBars must not be modified, otherwise segmentation fault may occur */
%immutable nbBars;

/* It is generally also good to make the other member immutable as well */
/* to prevent memory leaks */
%immutable timestamp;
%immutable open;
%immutable high;
%immutable low;
%immutable close;
%immutable volume;
%immutable openInterest;

/* hiddenData should not be accessible from Perl at all */
%ignore hiddenData;

%include "../../../../../c/include/ta_data.h"

/* restore mutability for other header files, if needed */
%mutable timestamp;
%mutable open;
%mutable high;
%mutable low;
%mutable close;
%mutable volume;
%mutable openInterest;

/* we better also get rid of the TA_History-specific typemaps for TA_Real* etc.*/
%clear TA_Real *, TA_Integer *, TA_Timestamp *;

/** ta_func *****************************************************************/
/* untested */

%include "../../../../../c/include/ta_func.h"


/** ta_pm *******************************************************************/
/* untested */

%include "../../../../../c/include/ta_pm.h"
