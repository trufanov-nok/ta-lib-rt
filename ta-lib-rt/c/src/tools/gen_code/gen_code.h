#ifndef GEN_CODE_H
#define GEN_CODE_H

/* TA-LIB Copyright (c) 1999-2008, Mario Fortier
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither name of author nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* List of contributors:
 *
 *  Initial  Name/description
 *  -------------------------------------------------------------------
 *  MF       Mario Fortier (mfortier@ta-lib.org)
 *  ST       Steve Thames  (steve@softlife.com)
 *  AC       Angelo Ciceri
 *  RM       Robert Meier  (talib@meierlim.com)
 *  CM       Craig Miller  (c-miller@users.sourceforge.net)
 *  RG       Richard Gomes
 *  AB       Anatol Belski (ab@php.net)
 *
 * Change history:
 *
 *  MMDDYY BY    Description
 *  -------------------------------------------------------------------
 *  112400 MF    First version.
 *  052403 MF    Many modifications related to generate code that works
 *               with the windows .NET Managed C++ compiler.
 *  092103 MF    Now touch files only when there is really a change.
 *  101303 MF    Remove underscore from names.
 *  020804 MF,ST Fixes to make it work on Linux (Bug#873879).
 *  022904 MF    Add TA_GetLookback
 *  030604 MF    Add generation of "ta_func.swg"
 *  082004 AC    Add generation of candlestick functions declaration
 *  010405 RM    Change createProjTemplate to work with VS03 and VS05
 *  031805 MF    Add generation of MSVC project file.
 *  061805 MF    Changes related to .NET verifiable code.
 *  062505 MF    Fix 'out' attribute for .NET verifiable code.
 *  121705 MF    Complete Java port.
 *  012806 MF    Add call to Java post-processing.
 *  093006 MF    Add code generation for TA_FunctionDescription
 *  110206 AC    Change volume and open interest to double
 *  120106 MF    Add generation of java_defs.h
 *  122406 MF    Add generation of Makefile.am
 *  011707 CM    Add ta_pragma.h handles VC8 warnings, type conversion of strlen handles VC warning
 *  021807 MF    Add generation of VS2005 project file
 *  040107 MF,RG Add generation of CoreAnnotated.java
 *  091307 MF    Add generation of Intel C++ compiler project file (TA-Lib Pro only)
 *  052508 MF    Add generation of VS2008 project file
 *  061608 MF    Add code to preserve proprietary code marker for TA-Lib pro.
 *  071808 MF    Add generation for Add-Ins express product (TA-Lib Pro only).
 *  082712 AB    Implemented java code generation on linux.
 */

/* Description:
 *       Generates a lot of source code. Run "gen_code ?" for
 *       the list of file.
 *
 *       The generator use as input the interface definition
 *       of each of the TA functions. The interface is provided
 *       from static data in the TA-Abstract module.
 *       (See the 'table_x.c' files)
 *
 *       This utility is intended only to people integrating new
 *       TA functions in TA-Lib.
 *
 * Note: All directory in this code is relative to the 'bin'
 *       directory. You must run "gen_code" from ta-lib/c/bin.
 *
 */
#include "ta_pragma.h"		/* this must be the first inclusion */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#if !defined(__WIN32__) && !defined(__MSDOS__) && !defined(WIN32)
   #include <unistd.h>
#endif

#if defined (WIN32)
   #include <windows.h>
#endif

#include "ta_common.h"
#include "ta_abstract.h"
#include "ta_memory.h"

#if defined(__WIN32__) || defined(WIN32)
# define TA_FS_SLASH "\\"
# define TA_MCPP_EXE "..\\src\\tools\\gen_code\\mcpp.exe"
#else
# define TA_FS_SLASH "/"
/* XXX resolve this dynamically or take as param */
# define TA_MCPP_EXE "/usr/bin/mcpp"
#endif

extern int mcpp_main( int argc, char ** argv);

#define BUFFER_SIZE 16000

#define FILE_WRITE            0
#define WRITE_ON_CHANGE_ONLY  0

#define FILE_READ     0x00000001
#define WRITE_ALWAYS  0x00000002

#ifndef min
   #define min(a, b)  (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
   #define max(a, b)  (((a) > (b)) ? (a) : (b))
#endif

typedef struct
{
   FILE *file;
   FILE *fileTarget;
   FILE *templateFile;
   char f1_name[BUFFER_SIZE];
   char f2_name[BUFFER_SIZE];

   int flags;
} FileHandle;


FileHandle *gOutFunc_H;        /* For "ta_func.h"  */
FileHandle *gOutFrame_H;       /* For "ta_frame.h" */
FileHandle *gOutFrame_C;       /* For "ta_frame.c" */
FileHandle *gOutGroupIdx_C;    /* For "ta_group_idx.c" */
FileHandle *gOutFunc_C;        /* For "ta_x.c" where 'x' is TA function name. */
FileHandle *gOutRetCode_C;     /* For "ta_retcode.c" */
FileHandle *gOutRetCode_CSV;   /* For "ta_retcode.csv" */
FileHandle *gOutFuncList_TXT;  /* For "ta_func_list.txt" */
FileHandle *gOutDefs_H;        /* For "ta_defs.h" */
FileHandle *gOutFunc_SWG;      /* For SWIG */
FileHandle *gOutFunc_XML;      /* For "ta_func_api.xml" */
FileHandle *gOutFuncAPI_C;     /* For "ta_func_api.c" */
FileHandle *gOutMakefile_AM;   /* For "Makefile.am" */

FileHandle *gOutCore_Java;       /* For Core.Java */
FileHandle *gOutJavaDefs_H;      /* For "java_defs.h" */
FileHandle *gOutFunc_Annotation; /* For "CoreAnnotated.java" */

#ifdef _MSC_VER
/* The following files are generated only on Windows platform. */
FileHandle *gOutDotNet_H;      /* For .NET interface file */
FileHandle *gOutProjFile;        /* For .NET project file */
FileHandle *gOutMSVCProjFile;    /* For MSVC project file */
FileHandle *gOutVS2005ProjFile;  /* For VS2005 project file */
FileHandle *gOutVS2008ProjFile;  /* For VS2008 project file */

#ifdef TA_LIB_PRO
      /* Section for code distributed with TA-Lib Pro only. */
#endif

FileHandle *gOutExcelGlue_C;     /* For "excel_glue.c" */

void printExcelGlueCode( FILE *out, const TA_FuncInfo *funcInfo );
#endif

void genJavaCodePhase1( const TA_FuncInfo *funcInfo );
void genJavaCodePhase2( const TA_FuncInfo *funcInfo );

/* To generate CoreAnnotated.java */
void printJavaFunctionAnnotation(const TA_FuncInfo *funcInfo);


typedef void (*TA_ForEachGroup)( const char *groupName,
                                 unsigned int index,
                                 unsigned int isFirst, /* Boolean */
                                 unsigned int isLast   /* Boolean */
                                );

unsigned int forEachGroup( TA_ForEachGroup forEachGroupfunc,
                                  void *opaqueData );

void doForEachFunctionPhase1( const TA_FuncInfo *funcInfo,
                               void *opaqueData );

void doForEachFunctionPhase2( const TA_FuncInfo *funcInfo,
                               void *opaqueData );

void doForEachFunctionXml( const TA_FuncInfo *funcInfo,
                                  void *opaqueData );

void doForEachUnstableFunction( const TA_FuncInfo *funcInfo,
                                       void *opaqueData );

#ifdef TA_LIB_PRO
      /* Section for code distributed with TA-Lib Pro only. */
#endif

void doDefsFile( void );

int gen_retcode( void );


extern int genPrefix;

void print( FILE *out, const char *text, ... );

void printIndent( FILE *out, unsigned int indent );

enum printFuncSettings
{
    pfs_prototype =              1 << 0,
    pfs_frame =                  1 << 1,
    pfs_semiColonNeeded =        1 << 2,
    pfs_validationCode =         1 << 3,
    pfs_lookbackSignature =      1 << 4,
    pfs_managedCPPCode =         1 << 5,
    pfs_managedCPPDeclaration =  1 << 6,
    pfs_inputIsSinglePrecision = 1 << 7,
    pfs_outputForSWIG =          1 << 8,
    pfs_outputForJava =          1 << 9,
    pfs_lookbackValidationCode = 1 << 10,
    pfs_useSubArrayObject =      1 << 11,
    pfs_arrayToSubArrayCnvt =    1 << 12,
    pfs_stateStruct =            1 << 13,
    pfs_stateInitSignature =     1 << 14,
    pfs_stateFuncSignature =     1 << 15,
    pfs_stateFreeSignature =     1 << 16,
    pfs_stateTestSignature =     1 << 17,
    pfs_stateSaveSignature =     1 << 18,
    pfs_stateLoadSignature =     1 << 19
};


void printFunc(FILE *out,
                       const char *prefix,       /* Can be NULL */
                       const TA_FuncInfo *funcInfo,
                       unsigned int settings);

void printCallFrame  ( FILE *out, const TA_FuncInfo *funcInfo );
void printFrameHeader(FILE *out, const TA_FuncInfo *funcInfo, unsigned int settings );

void printExternReferenceForEachFunction( const TA_FuncInfo *info,
                                                 void *opaqueData );

void printFunctionAddress( const TA_FuncInfo *info,
                                  void *opaqueData );

void printPerGroupList( const char *groupName,
                               unsigned int index,
                               unsigned int isFirst,
                               unsigned int isLast
                             );

void printGroupListAddress(  const char *groupName,
                                    unsigned int index,
                                    unsigned int isFirst,
                                    unsigned int isLast
                                 );
void printGroupSize(  const char *groupName,
                             unsigned int index,
                             unsigned int isFirst,
                             unsigned int isLast
                           );
void printGroupSizeAddition(  const char *groupName,
                                     unsigned int index,
                                     unsigned int isFirst,
                                     unsigned int isLast
                                  );

int addUnstablePeriodEnum( FILE *out );

int createTemplate( FileHandle *in, FileHandle *out );

int generateFuncAPI_C( void );


#ifdef _MSC_VER
int createProjTemplate( FileHandle *in, FileHandle *out );
int createMSVCProjTemplate( FileHandle *in, FileHandle *out );
int createVS2005ProjTemplate( FileHandle *in, FileHandle *out );
void printVS2005FileNode( FILE *out, const char *name );
#ifdef TA_LIB_PRO
      /* Section for code distributed with TA-Lib Pro only. */
#endif
#endif

void writeFuncFile( const TA_FuncInfo *funcInfo );
void doFuncFile( const TA_FuncInfo *funcInfo );
void printOptInputValidation( FILE *out,
                                     const char *name,
                                     const TA_OptInputParameterInfo *optInputParamInfo,
                                     int lookbackValidationCode /* Boolean */ );
int skipToGenCode( const char *dstName, FILE *out, FILE *templateFile );
void printDefines( FILE *out, const TA_FuncInfo *funcInfo );

void printFuncHeaderDoc( FILE *out,
                                const TA_FuncInfo *funcInfo,
                                const char *prefix );


void extractTALogic( FILE *inFile, FILE *outFile );

void cnvtToUpperCase( char *str );
void cnvtChar( char *str, char from, char to );
char *trimWhitespace( char *str );

/* Return 1 on success */
int copyFile( const char *src, const char *dest );

/* Return 1 when identical */
int areFileSame( const char *file1, const char *file2 );

void fileDelete( const char *fileToDelete );

void appendToFunc( FILE *out );

void convertFileToCArray( FILE *in, FILE *out );

void ReplaceReservedXmlCharacters(const char *input, char *output );

char gToOpen[BUFFER_SIZE];
char gTempBuf[BUFFER_SIZE];
char gTempBuf2[BUFFER_SIZE];
char gTempBuf3[BUFFER_SIZE];
char gTempBufForPrint[BUFFER_SIZE];
char gTempDoubleToStr[200];

/* Because Microsoft and Borland does not display
 * the value of a double in the same way (%e), this
 * function attempts to eliminate difference. This
 * is done to avoid annoying difference with CVS.
 */
const char *doubleToStr( double value );

const char *gCurrentGroupName;

int genCode(int argc, char* argv[]);

extern const TA_OptInputParameterInfo TA_DEF_UI_MA_Method;

#endif // GEN_CODE_H

