/* File : ta_libc.perl.swg 
 * Perl typemaps for all TA interfaces
 */

/* Adittional typemap not found in the standard set */
/* Not working with ActivePerl, alas
%typemap(perl5,in) FILE * {
   $1 = IoIFP(sv_2io($input));
   $1 = PerlIO_exportFILE(IoIFP(sv_2io($input)), 0);
}
*/



/* Handles are created and released only by appropriate calls to TA-Lib functions
 * They have no accessible fields
 * To obtain a handle in Perl, use references
 * Example: 
 *   $retCode = TA_HandleAlloc(\$handle);
 *   $retCode = TA_HandleFree($handle);
 *
 * However, for all TA handles, Perl shadow classes are defined, simplifying
 * creaction and destruction.
 */
%define HANDLE(TYPE, NAME)

%typemap(in) TYPE **NAME($*1_ltype temp) 
{
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

%typemap(argout) TYPE **NAME 
{
    SV *tempsv;
    tempsv = SvRV($input);
    SWIG_MakePtr(tempsv, (void *) *$1, $*1_descriptor, SWIG_SHADOW);
}

/* Don't create default constructors/destructors. 
 */
%nodefault TYPE;

%enddef /* HANDLE */


/* typemaps for TA objects like TA_History */

/* Objects are created as argout (just to be different than handles ;-)
 * Example:
 * @res = TA_HistoryAlloc($udb, $history_param);
 * $history = $res[1] if $res[0] == $TA_SUCCESS;
 *
 * Clumsy, huh?
 * However in practice, you will use 'new' anyway...
 */

%define OBJECT(TYPE, NAME)

%typemap(in,numinputs=0) TYPE **NAME($*1_ltype temp = 0) 
	"$1 = &temp;";

%typemap(argout) TYPE **NAME 
%{
    if (*$1) {
	if (argvi >= items) {
	    EXTEND(sp,1);
	}
	$result = sv_newmortal();
	SWIG_MakePtr($result, (void *) *$1, $*1_descriptor, SWIG_SHADOW|SWIG_OWNER);
	argvi++;
    }
%}

/* Don't create default constructors/destructors. 
 */
%nodefault TYPE;

%enddef  /* OBJECT */

