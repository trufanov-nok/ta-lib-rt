/****************************************************************************/
/* File : ta_libc.python.swg 
 * Python typemaps for all TA interfaces
 * !!! TODO: UNFINISHED !!!
 */

/* This file has to define the following typemap macros:
 *      STRING_TABLE
 *      CONST_STRING_TABLE
 *      STRING_BUFFER
 *      HANDLE
 *      CONST_HANDLE
 *      OBJECT
 *      ARRAY_OBJECT
 *
 * It has also to define typemaps for:
 *      TA_Real *ARRAY
 *      TA_Integer *ARRAY
 *      TA_Timestamp *ARRAY
 * and generic typemap macros for ARRAYs:
 *      MEMBER_ARRAY
 *      MEMBER_PTRARRAY
 * 
 * Also some typemaps have to be defined for specific TA interface files 
 * (see below).
 */

%define STRING_TABLE(TYPE, SIZE_FIELD)
/* TODO */
%ignore TYPE;
%enddef /* STRING_TABLE */



%define CONST_STRING_TABLE(TYPE, SIZE_FIELD)
/* TODO */
%ignore TYPE;
%enddef /* CONST_STRING_TABLE */



%define STRING_BUFFER(TYPE, SIZE_FIELD, LEN_FIELD)
/* TODO */
%ignore TYPE;
%enddef /* STRING_BUFFER */



%define HANDLE(TYPE, NAME)
/* TODO */
%nodefault TYPE;
%enddef /* HANDLE */



%define CONST_HANDLE(TYPE, NAME)
/* TODO */
%nodefault TYPE;
%enddef /* CONST_HANDLE */



%define OBJECT(TYPE, NAME)
/* TODO */
%nodefault TYPE;
%enddef  /* OBJECT */



%define ARRAY_OBJECT(TYPE, SIZE_FIELD)
/* TODO */
%immutable SIZE_FIELD;
%enddef /* ARRAY_OBJECT */



%define MEMBER_ARRAY(TYPE)
/* TODO */
%enddef /* MEMBER_ARRAY */



%define MEMBER_PTRARRAY(TYPE)
/* TODO */
%enddef /* MEMBER_PTRARRAY */



/* typemaps for ta_common ***************************************************/

/* complex typemap for TA_FatalReportToBuffer */
/* TODO */



/* typemaps for ta_func *****************************************************/

/* The following typemaps have to be defined:
    START_IDX, END_IDX,
    IN_ARRAY
    OPT_INT, OPT_REAL
    BEG_IDX, OUT_SIZE,
    OUT_ARRAY
*/
/* TODO */



/* typemaps for ta_abstract *************************************************/

/* complex typemap for dataSet */
/* TODO */

/****************************************************************************/
