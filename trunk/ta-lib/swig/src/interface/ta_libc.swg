/****************************************************************************/
/* File : ta_libc.swg
 * This is the main SWIG file for the TA-Lib wrapper.
 * It includes other swg files, if needed.
 */

%module "Finance::TA"

%header %{
#include "ta_libc.h"
%}

/* include standard SWIG typemaps */
%include "typemaps.i"


/* include typemaps for all TA interfaces */
#ifdef SWIGPERL
  %include "ta_libc.perl.swg"
#endif
#ifdef SWIGPYTHON
  %include "ta_libc.python.swg"
#endif


/* Strip all const qualifies, they are not relevant to scripts,
 * but may prevent SWIG release memory in proxy classes.
 * This is safe because TA-Lib never sets returned const char pointers
 * to anything in static (data) area by itself (except in ta_abstract).
 * If needed, const members are made explicitly immutable.
 */
%clear const char *;

/* hiddenData should not be accessible for client code */
%ignore hiddenData;



/** ta_defs *****************************************************************/

/* The constants below are pulled out from <limits.h> and used by ta_defs.h 
 * to define some TA-specific constants.
 * They have to be redefined here otherwise SWIG would not be able
 * to determine the values of some TA constants and would skip them.
 * The limits.h constants themselves do not need to be exported by the module;
 * that's why they are tagged %ignore
 */

%ignore INT_MAX;
%ignore INT_MIN;
#define INT_MAX 2147483647
#define INT_MIN -INT_MAX-1


%include "ta_defs.h"


/** ta_common ***************************************************************/

/* fatal handler is not supported */
%ignore TA_SetFatalErrorHandler;

/* oputput parameters of TA_GetDate */
%apply unsigned int *OUTPUT { unsigned int *year, unsigned int *month, unsigned int *day };

/* oputput parameters of TA_GetTime */
%apply unsigned int *OUTPUT { unsigned int *hour, unsigned int *min, unsigned int *sec };

/* output parameter of TA_TimestampDeltaXxxx functions */
%apply unsigned int *OUTPUT { unsigned int *delta };

/* TA_StringTable** is used as output in TA_XxxAlloc() functions */
STRING_TABLE(TA_StringTable, size)

/* Sometimes it is used as output to constant strings */
CONST_STRING_TABLE(TA_StringTable, size)

/* typemaps for TA_FatalReportToBuffer are language specific, see ta_libc.XXX.swg */

%include "ta_common.h"


/* synthesized attributes for TA_Timestamp */

%extend TA_Timestamp {
    unsigned int year, month, day;
    unsigned int hours, minutes, seconds;
}

%{
unsigned int TA_Timestamp_year_get(const TA_Timestamp *ts)
{
    return TA_GetYear(ts);
}

void TA_Timestamp_year_set(TA_Timestamp *ts, unsigned int year)
{
    unsigned int y = 0, m = 0, d = 0;
    TA_GetDate(ts, &y, &m, &d);
    TA_SetDate(year, m, d, ts);
}

unsigned int TA_Timestamp_month_get(const TA_Timestamp *ts)
{
    return TA_GetMonth(ts);
}

void TA_Timestamp_month_set(TA_Timestamp *ts, unsigned int month)
{
    unsigned int y = 0, m = 0, d = 0;
    TA_GetDate(ts, &y, &m, &d);
    TA_SetDate(y, month, d, ts);
}

unsigned int TA_Timestamp_day_get(const TA_Timestamp *ts)
{
    return TA_GetDay(ts);
}

void TA_Timestamp_day_set(TA_Timestamp *ts, unsigned int day)
{
    unsigned int y = 0, m = 0, d = 0;
    TA_GetDate(ts, &y, &m, &d);
    TA_SetDate(y, m, day, ts);
}

unsigned int TA_Timestamp_hours_get(const TA_Timestamp *ts)
{
    return TA_GetHour(ts);
}

void TA_Timestamp_hours_set(TA_Timestamp *ts, unsigned int hours)
{
    unsigned int h = 0, m = 0, s = 0;
    TA_GetTime(ts, &h, &m, &s);
    TA_SetTime(hours, m, s, ts);
}

unsigned int TA_Timestamp_minutes_get(const TA_Timestamp *ts)
{
    return TA_GetMin(ts);
}

void TA_Timestamp_minutes_set(TA_Timestamp *ts, unsigned int minutes)
{
    unsigned int h = 0, m = 0, s = 0;
    TA_GetTime(ts, &h, &m, &s);
    TA_SetTime(h, minutes, s, ts);
}

unsigned int TA_Timestamp_seconds_get(const TA_Timestamp *ts)
{
    return TA_GetSec(ts);
}

void TA_Timestamp_seconds_set(TA_Timestamp *ts, unsigned int seconds)
{
    unsigned int h = 0, m = 0, s = 0;
    TA_GetTime(ts, &h, &m, &s);
    TA_SetTime(h, m, seconds, ts);
}

%}

/* clearing typemaps to avoid potential future problems in other header files */
%clear unsigned int *year, unsigned int *month, unsigned int *day;
%clear unsigned int *hour, unsigned int *min, unsigned int *sec;
%clear unsigned int *delta;


/** ta_data *****************************************************************/


HANDLE(TA_UDBase, newUDBase)

/* fool SWIG that TA_UDBase is a struct.  SWIG creates shadow classes only
 * for structs and classes.
 */
typedef struct {} TA_UDBase;


OBJECT(TA_History, history)

/* accessing array members of TA_History requires to defile it as an array object */
ARRAY_OBJECT(TA_History, nbBars)

/* now apply the ARRAY typemaps to specific fields */
%apply const TA_Real *ARRAY { 
    TA_Real *open, 
    TA_Real *high, 
    TA_Real *low, 
    TA_Real *close 
};

%apply const TA_Integer *ARRAY { 
    TA_Integer *volume, 
    TA_Integer *openInterest 
};

%apply const TA_Timestamp *ARRAY { 
    TA_Timestamp *timestamp 
};


/* It is generally also good to make the members immutable */
/* to prevent memory leaks */
%immutable timestamp;
%immutable open;
%immutable high;
%immutable low;
%immutable close;
%immutable volume;
%immutable openInterest;
%immutable listOfSource;

/* Accessing symbol and category tables:
 * String tables are converted to native lists directly, so no need for
 * alloc/free scheme
 */
%rename(TA_CategoryTable) TA_CategoryTableAlloc;
%ignore TA_CategoryTableFree;
%rename(TA_SymbolTable) TA_SymbolTableAlloc;
%ignore TA_SymbolTableFree;

/* TA_ForEachSymbol doesn't make sense for scripting languages */
%ignore TA_ForEachSymbol;

%include "ta_data.h"

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

/* ta_func typemaps are target language specific, see ta_libc.XXX.swg */

/* Treat OPT_MATYPE as OPT_INT */
%apply int OPT_INT { TA_MAType OPT_MATYPE };

%include "ta_func.swg"



/** ta_pm *******************************************************************/

/* TA_TradeLog and TA_PM are handle types */
HANDLE(TA_TradeLog, allocatedTradeLog)
HANDLE(TA_PM, allocatedPM)

/* output of TA_PMValue */
%apply double *OUTPUT { TA_Real *value };


OBJECT(TA_PMArray, allocatedArray)

/* TA_PMArray has array fields of TA_Timestamp and TA_Real
 * So it is an array object (container), like TA_History
 */
ARRAY_OBJECT(TA_PMArray, nbData)
%apply const TA_Real *ARRAY { const TA_Real *data };
%apply const TA_Timestamp *ARRAY { const TA_Timestamp *data };

/* all fields of TA_PMArray are readonly */
%immutable nbData;
%immutable timestamp;
%immutable data;
%immutable arrayId;
%immutable grp;
%immutable period;

/* PM report */

/* TA_PMReport is never passed to the scripting language directly;
 * it is converted to a list of strings like TA_StringTable
 */
%ignore TA_PMReport;
%rename(TA_PMReport) TA_PMReportAlloc;
%ignore TA_PMReportFree;

STRING_BUFFER(TA_PMReport, nbLine, lineLength)


/* Reporting to file is of little use;
 * in a scripting language it is easy to output a string list to any file.
 */
%ignore TA_PMReportToFile;

/* PM Trade Report */
OBJECT(TA_TradeReport, tradeReportAllocated)

/* TA_TradeReport is an array container */
ARRAY_OBJECT(TA_TradeReport, nbTrades)
MEMBER_PTRARRAY(TA_Trade)
%apply const TA_Trade **ARRAY { const TA_Trade **trades };

/* ...and a read-only too */
%immutable nbTrades;
%immutable trades;

%include "ta_pm.h"

%clear TA_Real *value;
%clear TA_Trade **trades;

%mutable nbData;
%mutable timestamp;
%mutable data;
%mutable arrayId;
%mutable grp;
%mutable period;
%mutable nbTrades;
%mutable trades;



/** ta_abstract *************************************************************/

%rename(TA_GroupTable) TA_GroupTableAlloc;
%rename(TA_FuncTable)  TA_FuncTableAlloc;
%ignore TA_FuncTableFree;
%ignore TA_GroupTableFree;

CONST_HANDLE(TA_FuncHandle, handle)
CONST_HANDLE(TA_FuncInfo, funcInfo)
CONST_HANDLE(TA_InputParameterInfo, info)
CONST_HANDLE(TA_OptInputParameterInfo, info)
CONST_HANDLE(TA_OutputParameterInfo, info)

/* Fool SWIG that TA_FuncHandle is a struct.  SWIG creates shadow classes only
 * for structs and classes.
 */
typedef struct {} TA_FuncHandle;

/* For the rest TA_FuncHandle is as TA_UDBase, more or less... */
/* similarly other const structs here */


/* TA_ForEachFunc is not needed, use 'map' or 'grep' on the list (in Perl) */
%ignore TA_ForEachFunc;

/* None of TA_FuncInfo fields may be modified, especially const char* */
/* The same applies to other structs */
%immutable name;
%immutable group;
%immutable hint;
%immutable helpFile;
%immutable flags;
%immutable nbInput;
%immutable nbOptInput;
%immutable nbOutput;
%immutable handle;
%immutable type;
%immutable paramName;
%immutable displayName;
%immutable dataSet;
%immutable defaultValue;

/* The field 'dataSet' is a tricky one; it has to be recast from const void*
 * to something sensible depending on the value of 'type'
 * It is target language dependant; typemap defined in la_libc.XXX.swg
 */

/* The following structs are never created; 
 * Only pointers to const structs can be obtained through 'dataSet' access
 */
%nodefault TA_RealRange;
%nodefault TA_IntegerRange;
%nodefault TA_RealDataPair;
%nodefault TA_IntegerDataPair;
%nodefault TA_RealList;
%nodefault TA_IntegerList;


/* Again, the structs are read only */
%immutable min;
%immutable max;
%immutable precision;
%immutable suggested_start;
%immutable suggested_end;
%immutable suggested_increment;
%immutable value;
%immutable string;
%immutable data;
%immutable nbElement;


/* Accessing 'data' of TA_RealList and TA_IntegerList is similar to 
 * array access in TA_History 
 */
ARRAY_OBJECT(TA_RealList, nbElement)
ARRAY_OBJECT(TA_IntegerList, nbElement)
MEMBER_ARRAY(TA_RealDataPair)
MEMBER_ARRAY(TA_IntegerDataPair)
%apply const TA_RealDataPair *ARRAY { const TA_RealDataPair *data };
%apply const TA_IntegerDataPair *ARRAY { const TA_IntegerDataPair *data };

/* The functions supporting abstract calling are not wrapped.
 * There is no need for that; in Perl, you can already call 
 * any function by name and with any parameter list you like
 * Any decent scripting language supports the same.
 */

%ignore TA_ParamHolder;
%ignore TA_ParamHolderAlloc;
%ignore TA_ParamHolderFree;
%ignore TA_SetInputParamIntegerPtr;
%ignore TA_SetInputParamRealPtr;
%ignore TA_SetInputParamPricePtr;
%ignore TA_SetOptInputParamInteger;
%ignore TA_SetOptInputParamReal;
%ignore TA_SetOutputParamIntegerPtr;
%ignore TA_SetOutputParamRealPtr;
%ignore TA_GetLookback;
%ignore TA_CallFunc;

%include "ta_abstract.h"

/* ta_abstract is the last module, so we do not have to clean up 
 * the definitions specific to this file.
 * I hope that some day there will be a SWIG version that is able to process
 * several interface files for one library.
 */

/****************************************************************************/
