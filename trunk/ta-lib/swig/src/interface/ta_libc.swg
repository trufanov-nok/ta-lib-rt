/* File : ta_libc.i */

%module "Finance::TA"

%{
#include "../../../../c/include/ta_libc.h"
%}


%include "typemaps.i"



/* Adittional typemap not found in the standard set */
/* Not working...
%typemap(perl5,in) FILE * {
   $1 = IoIFP(sv_2io($input));
   $1 = PerlIO_exportFILE(IoIFP(sv_2io($input)), 0);
}
*/



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

/* hiddenData should not be accessible from Perl at all */
%ignore hiddenData;

/* TA_StringTable */
%typemap(in,numinputs=0) TA_StringTable** (TA_StringTable *temp = 0)
    "$1 = &temp;"

/* TA_StringTable** is used as output in TA_XxxAlloc() functions */
%typemap(perl5,argout) TA_StringTable** {
    /* Copy the strings from **$1 to a Perl array */
    if ( *$1 && (*$1)->size > 0) {
        int new_argvi = argvi + (*$1)->size;
        unsigned int elem;
	    if (new_argvi > items) {
		    EXTEND(sp,(new_argvi-items));
	    }
        for (elem = 0;  elem < (*$1)->size;  elem++) {
            ST(argvi) = sv_newmortal();
            if ((*$1)->string[elem]) {
                sv_setpv((SV*)ST(argvi++), (char *) (*$1)->string[elem]);
            } else {
                sv_setsv((SV*)ST(argvi++), &PL_sv_undef);
            }
        }
    }
    $symnameFree(*$1);
}


/* TA_StringTable* is out too but need not be deallocated */
%typemap(perl5,out) TA_StringTable* {
    /* Copy the strings from *$1 to a Perl array */
    if ( $1->size > 0) {
        int new_argvi = argvi + $1->size;
        unsigned int elem;
	    if (new_argvi > items) {
		    EXTEND(sp,(new_argvi-items));
	    }
        for (elem = 0;  elem < $1->size;  elem++) {
            ST(argvi) = sv_newmortal();
            if ($1->string[elem]) {
                sv_setpv((SV*)ST(argvi++), (char *) $1->string[elem]);
            } else {
                sv_setsv((SV*)ST(argvi++), &PL_sv_undef);
            }
        }
    }
}


/* we don't want just TA_StringTable classes around */
%nodefault TA_StringTable;

%include "../../../../../c/include/ta_common.h"

/* clearing typemaps to avoid potential future problems in other header files */
%clear unsigned int *year, unsigned int *month, unsigned int *day;
%clear unsigned int *hour, unsigned int *min, unsigned int *sec;
%clear unsigned int *delta;


/** ta_data *****************************************************************/
/* under development */

#ifdef SWIGPERL

/* typemaps for TA_UDBaseAlloc */

/* Don't create default constructors/destructors.  We will use our own that
 * rely on TA_UDBaseAlloc/TA_UDBBaseFree
 */
%nodefault TA_UDBase;

/* fool SWIG that TA_UDBase is a struct.  SWIG creates shadow classes only
 * for structs and classes.
 */
typedef struct {} TA_UDBase;

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
	SWIG_MakePtr(tempsv, (void *) *$1, $*1_descriptor, SWIG_SHADOW);
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

%typemap(in,numinputs=0) TA_History **history(TA_History *temp = 0) 
	"$1 = &temp;";

%typemap(argout) TA_History **history %{
    if (*$1) {
	    if (argvi >= items) {
		    EXTEND(sp,1);
	    }
	    $result = sv_newmortal();
	    SWIG_MakePtr($result, (void *) *$1, $*1_descriptor, SWIG_SHADOW|SWIG_OWNER);
	    argvi++;
    }
%}



/* accessing members of TA_History */

/* Each TA_History saves its size in array_size
 * This will later be needed when acessing the member arrays
 * This typemap does not perform a conversion, that's why it
 * cannot be type 'in'.
 */
%typemap(check) TA_History* (unsigned int array_size)
    "array_size = ($1 != NULL)? ($1->nbBars) : 0;"

/* How to figure out how many elements we have? 
 * This and the following two typemaps rely upon the encompassing structure
 * creating a local variable array_size.
 * We have seen above that TA_History does it.
 * If forgot to define it, a compile error will occur.
 */
%typemap(out) const TA_Real *ARRAY {
	AV *myav;
	SV **svs;
	unsigned int i = 0;

	svs = (SV **) malloc(array_size1 * sizeof(SV *));
	for (i = 0; i < array_size1 ; i++) {
	    svs[i] = sv_newmortal();
	    sv_setnv((SV*)svs[i],$1[i]);
	};
	myav =	av_make(array_size1,svs);
	free(svs);
    $result = newRV((SV*)myav);
    sv_2mortal($result);
    argvi++;    
}

%typemap(out) const TA_Integer *ARRAY {
	AV *myav;
	SV **svs;
	unsigned int i = 0;

	svs = (SV **) malloc(array_size1 * sizeof(SV *));
	for (i = 0; i < array_size1 ; i++) {
	    svs[i] = sv_newmortal();
	    sv_setiv((SV*)svs[i],$1[i]);
	};
	myav =	av_make(array_size1,svs);
	free(svs);
    $result = newRV((SV*)myav);
    sv_2mortal($result);
    argvi++;    
}

%typemap(out) const TA_Timestamp *ARRAY {
	AV *myav;
	SV **svs;
	unsigned int i = 0;

	svs = (SV **) malloc(array_size1 * sizeof(SV *));
	for (i = 0; i < array_size1 ; i++) {
	    svs[i] = sv_newmortal();
        SWIG_MakePtr((SV*)svs[i], (void *) &$1[i], $1_descriptor, SWIG_SHADOW);
	};
	myav =	av_make(array_size1,svs);
	free(svs);
    $result = newRV((SV*)myav);
    sv_2mortal($result);
    argvi++;    
}

#endif

/* now apply the defined timestamps to specific fields */
%apply const TA_Real *ARRAY { 
    const TA_Real *open, 
    const TA_Real *high, 
    const TA_Real *low, 
    const TA_Real *close 
};

%apply const TA_Integer *ARRAY { 
    const TA_Integer *volume, 
    const TA_Integer *openInterest 
};

%apply const TA_Timestamp *ARRAY { 
    const TA_Timestamp *timestamp 
};

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
%immutable listOfSource;

/* hiddenData should not be accessible from Perl at all */
%ignore hiddenData;

/* Accessing symbol and category tables:
 * String tables are converted to perl lists directly, so no need for
 * alloc/free scheme
 */
%rename(TA_CategoryTable) TA_CategoryTableAlloc;
%ignore TA_CategoryTableFree;
%rename(TA_SymbolTable) TA_SymbolTableAlloc;
%ignore TA_SymbolTableFree;

/* TA_ForEachSymbol doesn't make sense for scripting languages */
%ignore TA_ForEachSymbol;

%include "../../../../../c/include/ta_data.h"

/* restore mutability for other header files, if needed */
%mutable timestamp;
%mutable open;
%mutable high;
%mutable low;
%mutable close;
%mutable volume;
%mutable openInterest;
%mutable listOfSource;


/** ta_func *****************************************************************/
/* untested */

%include "../../../../../c/include/ta_func.h"


/** ta_pm *******************************************************************/
/* untested */

/* TA_PMArray has array fields of TA_Timestamp and TA_Real
 * We can reuse typemaps defined for TA_History
 */
%typemap(check) TA_PMArray* (unsigned int array_size)
    "array_size = ($1 != NULL)? (unsigned int)($1->nbData) : 0;"

%apply const TA_Real *ARRAY { const TA_Real *data }


/* TA_Transaction actually does not have an array of TA_Timestamp
 * but it does have a member TA_Timestamp timestamp;
 * Unfortunately, SWIG does not distinguiush structures and structure
 * pointers. I rely on the fact that TA_Transaction::timestamp is not const
 * Ideally, the TA_Timestamp field would have a different name than 
 * "timestamp" which is "reserved" for array members.
 */


%include "../../../../../c/include/ta_pm.h"
