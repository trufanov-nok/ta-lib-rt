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

    /* this is not the most efficient way of creating an array
     * it creates much too many mortals
     * I have copied it from SWIG example but a better way is in 
     * the typemap for OUT_ARRAY
     * TODO: optimize it here (an in the following two typemaps)
     */
    svs = (SV **) malloc(array_size1 * sizeof(SV *));
    for (i = 0; i < array_size1 ; i++) {
	svs[i] = sv_newmortal();
	sv_setnv((SV*)svs[i],$1[i]);
    };
    myav = av_make(array_size1,svs);
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
    myav =  av_make(array_size1,svs);
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
    myav =  av_make(array_size1,svs);
    free(svs);
    $result = newRV((SV*)myav);
    sv_2mortal($result);
    argvi++;    
}

#endif  /* SWIGPERL */

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

#ifdef SWIGPERL

/* START_IDX and END_IDX are always the first two arguments of all functions.
 * They create two local (auto) variables, startIdx1 and endIdx2
 * Other typemaps depend on them to allocate properly sized C arrays.
 */
%typemap(in) int START_IDX (int startIdx) 
{
    $1 = (int) SvIV($input);
    if ($1 < 0) $1 = 0;                 /* ensure valid array range */
    startIdx = $1;
}

%typemap(in) int END_IDX (int endIdx)
{
    $1 = (int) SvIV($input);
    if ($1 < startIdx1) $1 = startIdx1;  /* ensure valid array range */
    endIdx = $1;
}

/* Input arrays are passed by references, otherwise they would loose
 * their identity.  Besides, it is more effiecient.
 * As it is implemented now, startIdx and endIdx values overrule the actual
 * array size; eventual missing elements are created and set to zero.
 */
%typemap(in) const double *IN_ARRAY, const float *IN_ARRAY 
{
    int array_size = endIdx2 + 1;
    AV *av;
    I32 len;
    int idx;
    SV **sv;

    if (!SvROK($input) || SvTYPE(SvRV($input)) != SVt_PVAV) {
        SWIG_croak("Expected an array reference as argument $argnum of $symname");
    }
    av = (AV*)SvRV($input);
    $1 = ($1_ltype) calloc(array_size, sizeof($*1_ltype));
    len = av_len(av);
    if (len >= array_size) len = array_size - 1;
    for (idx = 0; idx <= len; idx++) {
        sv = av_fetch(av, idx, 0);	
        $1[idx] = ($*1_ltype) SvNV(*sv);
    }
}

%typemap(freearg) const double *IN_ARRAY, const float *IN_ARRAY
    "free($1);";

/* After the input arrays, optional parameters come.
 * If not provided or given as 'undef', they will be translated to
 * TA_INTEGER_DEFAULT or TA_REAL_DEFAULT, depending on the type.
 */
%typemap(default) int OPT_INT
    "$1 = TA_INTEGER_DEFAULT;"

%typemap(in) int OPT_INT 
%{
    if (SvOK($input)) {
        $1 = (int) SvIV($input);
    }
%}

%typemap(default) double OPT_REAL
    "$1 = TA_REAL_DEFAULT;"

%typemap(in) double OPT_REAL 
%{
    if (SvOK($input)) {
        $1 = (int) SvNV($input);
    }
%}


/* outBegIdx is handled just as a regular OUTPUT parameter, except that
 * if the function failed, undef is returned
 */
%typemap(in,numinputs=0) int *BEG_IDX(int temp = 0)
    "$1 = &temp;";

%typemap(argout) int *BEG_IDX
{
    if (argvi >= items) {
        EXTEND(sp,1);
    }
    $result = sv_newmortal();
    if (result == TA_SUCCESS) {
        sv_setiv($result,(IV) *($1));
    } else {
        sv_setsv($result, &PL_sv_undef);
    }
    argvi++;
}


/* Parameter outNbElement is an out value, but is not passed back to Perl.
 * It is used to construct OUT_ARRAY of proper length.
 * Its position within the parameter list varies, so we cannot use
 * local variables declared in the same way as for startIdx and endIdx.
 * Taking advantage of that 'arginit' typemaps are the very first ones in
 * the wrapper function, we declare an explicitly named local variable.
 */
%typemap(arginit) int *OUT_SIZE
    "int outNbElement = 0;";

%typemap(in,numinputs=0) int *OUT_SIZE
    "$1 = &outNbElement;";

/* As last, output arrays come.  Since they are only output, numinputs=0 is
 * given so that they do not have to be provided in the function call from Perl.
 * However, in such case, they are placed at the very top of the wrapper 
 * function, before other inputs (SWIG bug?), making startIdx and endIdx
 * not accessible in the 'in' typemap.
 * Therefore the 'in' typemap does not generate any code, 
 * but the array allocation is done in the 'check' typemap.
 */
%typemap(in,numinputs=0) double *OUT_ARRAY, float *OUT_ARRAY 
    "/* $1 ignored on input */";

%typemap(check) double *OUT_ARRAY, float *OUT_ARRAY
{
    int array_size = endIdx2 - startIdx1 + 1;
    $1 = ($1_ltype) calloc(array_size, sizeof($*1_ltype));
}

/* On output, the arrays are converted to Perl arrays and returned as
 * Perl references on the output stack
 */
%typemap(argout) double *OUT_ARRAY, float *OUT_ARRAY 
{
    AV *av;
    int idx;
    SV *sv;

    av = newAV();
    if ( result == TA_SUCCESS && outNbElement > 0) {
        av_extend(av, outNbElement-1);
        for (idx = 0; idx < outNbElement; idx++) {
            sv = newSVnv($1[idx]);
            if (av_store(av, idx, sv) == 0) SvREFCNT_dec(sv);	
        }
    }
    if (argvi >= items) {
        EXTEND(sp,1);
    }
    $result = newRV((SV*)av);
    sv_2mortal($result);
    argvi++;
}

/* It is safer to have a separate typemap for cleanup rather than doing it
 * at the end of the 'argout' typemap.
 * If there were SWIG_croak() between the inlined typemap 'check' and 
 * the typemap 'argout', memory leak could occur.
 * The code of the typemap 'freearg' will always be executed.
 */
%typemap(freearg) double *OUT_ARRAY, float *OUT_ARRAY
    "free($1);";


#endif /* SWIGPERL */

%apply int OPT_INT { TA_MAType OPT_MATYPE };

/* %include "../../../../../c/include/ta_func.h" */
TA_RetCode TA_MAX( int           START_IDX,
                   int           END_IDX,
                   const double *IN_ARRAY,
                   int           OPT_INT,
                   int          *BEG_IDX,
                   int          *OUT_SIZE,
                   double       *OUT_ARRAY );



/** ta_pm *******************************************************************/
/* untested */

/* TA_PMArray has array fields of TA_Timestamp and TA_Real
 * We can reuse typemaps defined for TA_History
 */
%typemap(check) TA_PMArray* (unsigned int array_size)
    "array_size = ($1 != NULL)? (unsigned int)($1->nbData) : 0;"

%apply const TA_Real *ARRAY { const TA_Real *data }




%include "../../../../../c/include/ta_pm.h"
