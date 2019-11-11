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

#include "gen_code.h"
#include "print_funcs.h"


char *ta_fs_path(int count, ...) {
    char *path = (char *)malloc(16000); /* XXX quick and dirty */
    char *p; 
    va_list argp;
    int j;

    va_start(argp, count);

    p = path;
    for (j = 0; j < count; j++) {
        int i;
        char *part;

        part = va_arg(argp, char *); 
        i = strlen(part);

        memmove(p, part, i); 
        p += i;  

        memmove(p, TA_FS_SLASH, 1); 
        p++;
    }   
    *--p = '\0';

    va_end(argp);

    return path;
}


/* Set this variable to 1 whenever you wish to output a
 * prefix to all generated line.
 */
int genPrefix = 0;

void print( FILE *out, const char *text, ... )
{
   va_list arglist;
   memset(gTempBufForPrint,0,sizeof(gTempBufForPrint));

   va_start(arglist,text);
   vsprintf(gTempBufForPrint,text,arglist);
   va_end(arglist);

   if( strlen(gTempBufForPrint) >= BUFFER_SIZE-strlen("/* Generated */ ") )
   {
      printf( "Lines length exceed internal buffers (%lu,%lu)\n",
              (unsigned long)strlen(gTempBufForPrint),
              (unsigned long)(BUFFER_SIZE-strlen("/* Generated */ ")) );
      exit(-1);
   }
   if( genPrefix )
      fprintf( out, "/* Generated */ %s", gTempBufForPrint );
   else
      fprintf( out, "%s", gTempBufForPrint );
}

void printIndent( FILE *out, unsigned int indent )
{
   unsigned int i;
   
   if( genPrefix )
      fprintf( out, "/* Generated */ " );

   for( i=0; i < indent; i++ )
   {
      fprintf( out, " " );
   }
}


int main(int argc, char* argv[])
{
   int retValue;
   TA_RetCode retCode;

   if( argc > 1 )
   {
         /* There is no parameter needed for this tool. */
         printf( "\n" );
         printf( "gen_code V%s - Updates many TA-Lib source files\n", TA_GetVersionString() );
         printf( "\n" );
         printf( "Usage: gen_code\n");
         printf( "\n" );         
         printf( "  No parameter needed.\n" );
         printf( "\n" );         
         printf( "  This utility is useful only for developers adding new TA\n" );
         printf( "  functions to TA-Lib.\n" );
         printf( "\n" );         
         printf( "  The interface definitions in c/src/ta_abstract/tables\n" );
         printf( "  are used to generate code, documentation and some more.\n" );
         printf( "\n" );
         printf( "  The following files are updated or regenerated:\n" );
         printf( "     1) ta-lib/c/include/ta_func.h\n" );
         printf( "     2) ta-lib/c/include/ta_defs.h\n" );
         printf( "     3) ta-lib/ta_func_list.txt\n" );
         printf( "     4) ta-lib/c/src/ta_common/ta_retcode.*\n" );
         printf( "     5) ta-lib/c/src/ta_abstract/ta_group_idx.c\n");     
         printf( "     6) ta-lib/c/src/ta_abstract/frames/*.*\n");
         printf( "     7) ta-lib/swig/src/interface/ta_func.swg\n" );
         printf( "     8) ta-lib/dotnet/src/Core/TA-Lib-Core.vcproj (Win32 only)\n" );
         printf( "     9) ta-lib/dotnet/src/Core/TA-Lib-Core.h (Win32 only)\n" );
         printf( "    10) ta-lib/c/src/ta_abstract/excel_glue.c (Win32 only)\n" );
         printf( "    11) ta-lib/c/src/ta_abstract/java_defs.h (Win32 only)\n" );
         printf( "    12) ta-lib/c/ide/msvc/lib_proj/ta_func/ta_func.dsp (Win32 only)\n" );
         printf( "    13) ta-lib/java/src/com/tictactec/ta/lib/Core.java (Win32 only)\n" );
         printf( "    14) ta-lib/java/src/com/tictactec/ta/lib/CoreAnnotated.java (Win32 only)\n" );
         printf( "    15) ta-lib/ta_func_api.xml\n" );
         printf( "    16) ta-lib/c/src/ta_abstract/ta_func_api.c\n" );
         printf( "    17) ... and more ...");
         printf( "\n" );
         printf( "  The function header, parameters and validation code of all TA\n" );
         printf( "  function in c/src/ta_func are also updated.\n" );
         printf( "\n" );
         printf( "** Must be directly run from the 'bin' directory.\n" );
         exit(-1);
   }

   printf( "gen_code V%s\n", TA_GetVersionString() );

   retCode = TA_Initialize();
   if( retCode != TA_SUCCESS )
   {
      printf( "\nCannot initialize the library\n");
      return -1;
   }

   printf( "Now updating source code...\n" );

   retValue = genCode( argc, argv );

   retCode = TA_Shutdown();
   if( retCode != TA_SUCCESS )
   {
      printf( "Shutdown failed (%d)\n", retCode );
   }

   return retValue;
}


/* The following I/O function allows to manipulate
 * more easily files.
 *
 * When opening the file, the caller can specifiy a
 * path relative to the position of the binary.
 * That is: ta-lib\c\bin
 *
 * 'templateFile' allows to create a new file using
 * a template. This template must contain one
 * line starting with '%%%GENCODE%%%'.
 * All character before this string are added to the output
 * file on fileOpen, and all character after this string are
 * added to the output file on fileClose. Obviously, all
 * character added to the file between fileOpen/fileClose
 * will replace the "%%%GENCODE%%%" line.
 *
 * 'templateFile' is ignored when FILE_READ is specified.
 *
 * Another advantage to use fileOpen and fileClose is that
 * the writing to the file is done "silently" in a temporary
 * file and the target file is touch only if there was actually
 * a modification to it.
 *
 * On failure, simply exit the software.
 */
void init_gToOpen( const char *filePath, const char *suffix )
{
   strcpy( gToOpen, filePath );
   if( suffix )
      strcat( gToOpen, suffix );
}


 FileHandle *fileOpen( const char *fileToOpen,
                              const char *templateFile,
                              int flags )
{
   FileHandle *retValue;

   if( (fileToOpen == NULL) ||
       ((flags&FILE_READ) && (templateFile != NULL)) )
   {
      printf( "Internal error line %d", __LINE__ );
      return (FileHandle *)NULL;
   }

   retValue = TA_Malloc( sizeof(FileHandle) );
   if( !retValue )
   {
      printf( "Memory alloc error line %d", __LINE__ );
      return (FileHandle *)NULL;
   }

   memset( retValue, 0, sizeof(FileHandle) );

   retValue->flags = flags;

   init_gToOpen( fileToOpen, NULL );
   strcpy( retValue->f1_name, gToOpen );
   
   /* First let's try to open the file. Might fail when
    * for writing but that is ok. (the file might not exist).
    */
   if( flags&FILE_READ )
   {      
      retValue->file = fopen( gToOpen, "r" );
      if( retValue->file == NULL )
      {
         memset( retValue, 0, sizeof(FileHandle) );
         TA_Free( retValue );
         return (FileHandle *)NULL;
      }
   }
   else if( flags&WRITE_ALWAYS )
   {
      retValue->file = fopen( gToOpen, "w" );
      if( retValue->file == NULL )
      {
         memset( retValue, 0, sizeof(FileHandle) );
         TA_Free( retValue );
         return (FileHandle *)NULL;
      }
   }
   else
   {
      retValue->file = fopen( gToOpen, "r" );

      if( retValue->file )
      {
         /* Move pointer to fileTarget.  The file
          * ptr will become the temporary file who
          * is going to be truly write enabled.
          */
         retValue->fileTarget = retValue->file;
         init_gToOpen( fileToOpen, ".tmp" );
         strcpy( retValue->f2_name, gToOpen );
         retValue->file = fopen( gToOpen, "w" );
         if( !retValue->file )
         {
            fclose( retValue->fileTarget );
            memset( retValue, 0, sizeof(FileHandle) );
            TA_Free( retValue );
            return (FileHandle *)NULL;
         }
       }
       else
       {
         /* File does not exist, directly open for write
          * no temporary will be used.
          */
         retValue->fileTarget = NULL;
         retValue->file = fopen( gToOpen, "w" );

         if( retValue->file == NULL )
         {
            memset( retValue, 0, sizeof(FileHandle) );
            TA_Free( retValue );
            return (FileHandle *)NULL;
         }
      }
   }

   if( !(flags&FILE_READ) )
   {
      /* Handle the template. */
      if( templateFile )
      {
         init_gToOpen( templateFile, NULL );
         retValue->templateFile = fopen( gToOpen, "r" );
         if( retValue->templateFile == NULL )
         {
            if(retValue->fileTarget)   fclose( retValue->fileTarget );
            if(retValue->file)         fclose( retValue->file );
            if(retValue->templateFile) fclose( retValue->templateFile );
            memset( retValue, 0, sizeof(FileHandle) );
            TA_Free( retValue );
            printf( "\nCannot open template [%s]\n", gToOpen );
            return (FileHandle *)NULL;
         }

         /* Copy the header part of the template. */
         if( skipToGenCode( fileToOpen, retValue->file, retValue->templateFile ) != 0 )
         {
            if(retValue->fileTarget)   fclose( retValue->fileTarget );
            if(retValue->file)         fclose( retValue->file );
            if(retValue->templateFile) fclose( retValue->templateFile );
            memset( retValue, 0, sizeof(FileHandle) );
            TA_Free( retValue );
            return (FileHandle *)NULL;
         }
      }
   }

   return retValue;
}

void fileClose( FileHandle *handle )
{
   if( !handle ) return;

   /* Write remaining template info. */
   if( handle->templateFile && handle->file )
   {
      while( fgets( gTempBuf, BUFFER_SIZE, handle->templateFile ) != NULL )
      {
         if( fputs( gTempBuf, handle->file ) == EOF )
         {
            printf( "Cannot write to output file! Disk Full? " );
            break;
         }
      }

      #if 0
         /* Make sure the last line of the output 
          * finish with a carriage return. This may
          * avoid warning from some compilers.
          */
         if( gTempBuf[0] != '\n' )
	     {
            fprintf( handle->file, "\n" );
	     }
      #endif
   }

   if(handle->fileTarget)   fclose( handle->fileTarget );
   if(handle->templateFile) fclose( handle->templateFile );
   if(handle->file)         fclose( handle->file );

   if( !(handle->flags&FILE_READ) && !(handle->flags&WRITE_ALWAYS) && (handle->fileTarget != NULL))
   {
      if( !areFileSame( handle->f1_name, handle->f2_name ) )
         copyFile( handle->f2_name, handle->f1_name );

      fileDelete( handle->f2_name );      
   }

   memset( handle, 0, sizeof(FileHandle) );   
   TA_Free( handle );
}

void fileDelete( const char *fileToDelete )
{
   init_gToOpen( fileToDelete, NULL );

   #if defined (WIN32)
      DeleteFile (fileToDelete);
   #else
      unlink (fileToDelete);
   #endif
}

int genCode(int argc, char* argv[])
{
   TA_RetCode retCode;
   unsigned int nbGroup;
   FileHandle *tempFile;

   FileHandle *tempFileOut;

   (void)argc; /* Get ride of compiler warning */
   (void)argv; /* Get ride of compiler warning */

   #ifdef _MSC_VER
      /* Create .NET project files template */
      #define FILE_NET_PROJ ta_fs_path(6, "..", "..", "dotnet", "src", "Core", "TA-Lib-Core.vcproj")
      #define FILE_NET_PROJ_TMP ta_fs_path(3, "..", "temp", "dotnetproj.tmp")
      gOutProjFile = fileOpen( FILE_NET_PROJ, NULL, FILE_READ );
      if( gOutProjFile == NULL )   
      {
         printf( "\nCannot access [%s]\n", gToOpen );
         return -1;
      }
      tempFile = fileOpen( FILE_NET_PROJ_TMP, NULL, FILE_WRITE|WRITE_ALWAYS );
      if( tempFile == NULL )
      {
         printf( "Cannot create temporary .NET project file!\n" );
         return -1;
      }
      if( createProjTemplate( gOutProjFile, tempFile ) != 0 )
      {
         printf( "Failed to parse and write the temporary .NET project file!\n" );
         return -1;
      }
      fileClose(gOutProjFile);
      fileClose(tempFile);

      /* Create MSVC project files template */
      #define FILE_MSVC_PROJ     ta_fs_path(8, "..", "..", "c", "ide", "msvc", "lib_proj", "ta_func", "ta_func.dsp")
      #define FILE_MSVC_PROJ_TMP ta_fs_path(3, "..", "temp", "ta_func_dsp.tmp")
      gOutMSVCProjFile = fileOpen( FILE_MSVC_PROJ, NULL, FILE_READ );
      if( gOutMSVCProjFile == NULL )   
      {
         printf( "\nCannot access [%s]\n", gToOpen );
         return -1;
      }
      tempFile = fileOpen( FILE_MSVC_PROJ_TMP, NULL, FILE_WRITE|WRITE_ALWAYS );
      if( tempFile == NULL )
      {
         printf( "Cannot create temporary MSVC project file!\n" );
         return -1;
      }
      if( createMSVCProjTemplate( gOutMSVCProjFile, tempFile ) != 0 )
      {
         printf( "Failed to parse and write the temporary MSVC project file!\n" );
         return -1;
      }
      fileClose(gOutMSVCProjFile);
      fileClose(tempFile);

      /* Create VS2005 project files template */
      #define FILE_VS2005_PROJ     ta_fs_path(8, "..", "..", "c", "ide", "vs2005", "lib_proj", "ta_func", "ta_func.vcproj")
      #define FILE_VS2005_PROJ_TMP ta_fs_path(3, "..", "temp", "ta_func_vcproj05.tmp")
      gOutVS2005ProjFile = fileOpen( FILE_VS2005_PROJ, NULL, FILE_READ );
      if( gOutVS2005ProjFile == NULL )   
      {
         printf( "\nCannot access [%s]\n", gToOpen );
         return -1;
      }
      tempFile = fileOpen( FILE_VS2005_PROJ_TMP, NULL, FILE_WRITE|WRITE_ALWAYS );
      if( tempFile == NULL )
      {
         printf( "Cannot create temporary VS2005 project file!\n" );
         return -1;
      }
      if( createVS2005ProjTemplate( gOutVS2005ProjFile, tempFile ) != 0 )
      {
         printf( "Failed to parse and write the temporary VS2005 project file!\n" );
         return -1;
      }
      fileClose(gOutVS2005ProjFile);
      fileClose(tempFile);

      /* Create VS2008 project files template */
      #define FILE_VS2008_PROJ     ta_fs_path(8, "..", "..", "c", "ide", "vs2008", "lib_proj", "ta_func", "ta_func.vcproj")
      #define FILE_VS2008_PROJ_TMP ta_fs_path(3, "..", "temp", "ta_func_vcproj08.tmp")
      gOutVS2008ProjFile = fileOpen( FILE_VS2008_PROJ, NULL, FILE_READ );
      if( gOutVS2008ProjFile == NULL )   
      {
         printf( "\nCannot access [%s]\n", gToOpen );
         return -1;
      }
      tempFile = fileOpen( FILE_VS2008_PROJ_TMP, NULL, FILE_WRITE|WRITE_ALWAYS );
      if( tempFile == NULL )
      {
         printf( "Cannot create temporary VS2008 project file!\n" );
         return -1;      
	  }
	  /* VS2008 Project file the same as VS2005 for creating the template. */
      if( createVS2005ProjTemplate( gOutVS2008ProjFile, tempFile ) != 0 )
      {
         printf( "Failed to parse and write the temporary VS2008 project file!\n" );
         return -1;
      }
      fileClose(gOutVS2008ProjFile);
      fileClose(tempFile);

#ifdef TA_LIB_PRO
      /* Section for code distributed with TA-Lib Pro only. */
#endif

   #endif

   /* Create Java template for Core.java */
   #define FILE_CORE_JAVA     ta_fs_path(9, "..", "..", "java", "src", "com", "tictactec", "ta", "lib", "Core.java")
   #define FILE_CORE_JAVA_TMP ta_fs_path(3, "..", "temp", "CoreJava.tmp")
   #define FILE_CORE_JAVA_UNF ta_fs_path(3, "..", "temp", "CoreJavaUnformated.tmp")
   gOutCore_Java = fileOpen( FILE_CORE_JAVA, NULL, FILE_READ );
   if( gOutCore_Java == NULL )   
   {
         printf( "\nCannot access [%s]\n", gToOpen );
         return -1;
   }
   tempFile = fileOpen( FILE_CORE_JAVA_TMP, NULL, FILE_WRITE|WRITE_ALWAYS );
   if( tempFile == NULL )
   {
         printf( "Cannot create temporary Core.java project file!\n" );
         return -1;
   }
   if( createTemplate( gOutCore_Java, tempFile ) != 0 )
   {
         printf( "Failed to parse and write the temporary Core.java project file!\n" );
         return -1;
   }
   fileClose(gOutCore_Java);
   fileClose(tempFile);

   /* Create the .NET interface file template */
   #ifdef _MSC_VER
   #define FILE_NET_HEADER     ta_fs_path(6, "..", "..", "dotnet", "src", "Core", "TA-Lib-Core.h")
   #define FILE_NET_HEADER_TMP ta_fs_path(3, "..", "temp", "dotneth.tmp")
   gOutDotNet_H = fileOpen( FILE_NET_HEADER, NULL, FILE_READ );
   if( gOutDotNet_H == NULL )   
   {
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }
   tempFile = fileOpen( FILE_NET_HEADER_TMP, NULL, FILE_WRITE|WRITE_ALWAYS );
   if( tempFile == NULL )
   {
      printf( "Cannot create temporary .NET header file!\n" );
      return -1;
   }
   if( createTemplate( gOutDotNet_H, tempFile ) != 0 )
   {
      printf( "Failed to parse and write the temporary .NET header file!\n" );
      return -1;
   }
   fileClose(gOutDotNet_H);
   fileClose(tempFile);
   #endif

   /* Create ta_retcode.c */
   if( gen_retcode() != 0 )
   {
      printf( "\nCannot generate src/ta_common/ta_retcode.c\n" );
      return -1;
   }

   /* Create "ta_func.h" */
   gOutFunc_H = fileOpen( ta_fs_path(3, "..", "include", "ta_func.h"),
                          ta_fs_path(5, "..", "src", "ta_abstract", "templates", "ta_func.h.template"),
                          FILE_WRITE|WRITE_ON_CHANGE_ONLY );

   if( gOutFunc_H == NULL )
   {
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }

   gOutFunc_XML = fileOpen( ta_fs_path(3, "..", "..", "ta_func_api.xml"), NULL, FILE_WRITE|WRITE_ON_CHANGE_ONLY );
   if(gOutFunc_XML == NULL)
   {
	   printf( "\nCannot access ta_func_api.xml" );
   }


   /* Create "ta_func.swg" */
   gOutFunc_SWG = fileOpen( ta_fs_path(6, "..", "..", "swig", "src", "interface", "ta_func.swg"),
                            ta_fs_path(5, "..", "src", "ta_abstract", "templates", "ta_func.swg.template"),
                          FILE_WRITE|WRITE_ON_CHANGE_ONLY );

   if( gOutFunc_SWG == NULL )
   {
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }

   /* Create the "ta_func_list.txt" */
   gOutFuncList_TXT = fileOpen( ta_fs_path(3, "..", "..", "ta_func_list.txt"),
                                NULL,
                                FILE_WRITE|WRITE_ON_CHANGE_ONLY );

   if( gOutFuncList_TXT == NULL )
   {
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }


   /* Create the "ta_frame.h" */
   gOutFrame_H = fileOpen( ta_fs_path(5, "..", "src", "ta_abstract", "frames", "ta_frame.h"),
                           ta_fs_path(5, "..", "src", "ta_abstract", "templates", "ta_frame.h.template"),
                           FILE_WRITE|WRITE_ON_CHANGE_ONLY );

   if( gOutFrame_H == NULL )
   {
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }

   /* Create the "ta_frame.c" */
   gOutFrame_C = fileOpen( ta_fs_path(5, "..", "src", "ta_abstract", "frames", "ta_frame.c"),
                           ta_fs_path(5, "..", "src", "ta_abstract", "templates", "ta_frame.c.template"),
                           FILE_WRITE|WRITE_ON_CHANGE_ONLY );

   if( gOutFrame_C == NULL )
   {
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }

   /* Create the "Makefile.am" */
   gOutMakefile_AM = fileOpen( ta_fs_path(4, "..", "src", "ta_func", "Makefile.am"),
                               ta_fs_path(5, "..", "src", "ta_abstract", "templates", "Makefile.am.template"),
                               FILE_WRITE|WRITE_ON_CHANGE_ONLY );

   if( gOutMakefile_AM == NULL )
   {
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }

      /* Create "java_defs.h" */
      gOutJavaDefs_H = fileOpen( ta_fs_path(4, "..", "src", "ta_abstract", "ta_java_defs.h"),
                             ta_fs_path(5, "..", "src", "ta_abstract", "templates", "ta_java_defs.h.template"),
                             FILE_WRITE|WRITE_ON_CHANGE_ONLY );
                              

      if( gOutJavaDefs_H == NULL )
      {
         printf( "\nCannot access [%s]\n", gToOpen );
         return -1;
      }


   #ifdef _MSC_VER
      /* Create "excel_glue.c" */
      gOutExcelGlue_C = fileOpen( ta_fs_path(4, "..", "src", "ta_abstract", "excel_glue.c"),
                              ta_fs_path(5, "..", "src", "ta_abstract", "templates", "excel_glue.c.template"),
                              FILE_WRITE|WRITE_ON_CHANGE_ONLY );

      if( gOutExcelGlue_C == NULL )
      {
         printf( "\nCannot access [%s]\n", gToOpen );
         return -1;
      }

      /* Re-open the .NET project template. */
      gOutProjFile = fileOpen( FILE_NET_PROJ, FILE_NET_PROJ_TMP, FILE_WRITE|WRITE_ON_CHANGE_ONLY );
      if( gOutProjFile == NULL )
      {
         printf( "Cannot update [%s]\n", FILE_NET_PROJ );
         return -1;
      }

      /* Re-open the MSVC project template. */
      gOutMSVCProjFile = fileOpen( FILE_MSVC_PROJ, FILE_MSVC_PROJ_TMP, FILE_WRITE|WRITE_ON_CHANGE_ONLY );
      if( gOutMSVCProjFile == NULL )
      {
         printf( "Cannot update [%s]\n", FILE_MSVC_PROJ );
         return -1;
      }

      /* Re-open the VS2005 project template. */
      gOutVS2005ProjFile = fileOpen( FILE_VS2005_PROJ, FILE_VS2005_PROJ_TMP, FILE_WRITE|WRITE_ON_CHANGE_ONLY );
      if( gOutVS2005ProjFile == NULL )
      {
         printf( "Cannot update [%s]\n", FILE_VS2005_PROJ );
         return -1;
      }


      /* Re-open the VS2008 project template. */
      gOutVS2008ProjFile = fileOpen( FILE_VS2008_PROJ, FILE_VS2008_PROJ_TMP, FILE_WRITE|WRITE_ON_CHANGE_ONLY );
      if( gOutVS2008ProjFile == NULL )
      {
         printf( "Cannot update [%s]\n", FILE_VS2008_PROJ );
         return -1;
      }

#ifdef TA_LIB_PRO
      /* Section for code distributed with TA-Lib Pro only. */
#endif

   #endif

      /* Create "CoreAnnotated.java" */
      gOutFunc_Annotation = fileOpen( ta_fs_path(9, "..", "..", "java", "src", "com", "tictactec", "ta", "lib", "CoreAnnotated.java"),
                                      ta_fs_path(5, "..", "src", "ta_abstract", "templates", "CoreAnnotated.java.template"), 
                                      FILE_WRITE|WRITE_ON_CHANGE_ONLY );

      if(gOutFunc_Annotation == NULL)
      {
	      printf( "\nCannot access CoreAnnotated.java" );
      }

   /* Re-open the Core.java template. */
   gOutCore_Java = fileOpen( FILE_CORE_JAVA_UNF, FILE_CORE_JAVA_TMP, FILE_WRITE|WRITE_ON_CHANGE_ONLY );
   if( gOutCore_Java == NULL )
   {
      printf( "Cannot update [%s]\n", FILE_CORE_JAVA_UNF );
      return -1;
   }

   /* Re-open the .NET interface template. */
   #ifdef _MSC_VER
   gOutDotNet_H = fileOpen( FILE_NET_HEADER, FILE_NET_HEADER_TMP, FILE_WRITE|WRITE_ON_CHANGE_ONLY );
   if( gOutDotNet_H == NULL )
   {
      printf( "Cannot update [%s]\n", FILE_NET_HEADER );
      return -1;
   }
   #endif

   /* Process each functions. Two phase. */
   TA_ForEachFunc( doForEachFunctionPhase1, NULL );
   TA_ForEachFunc( doForEachFunctionPhase2, NULL );

   /* Leave empty line for Makefile.am */
   fprintf( gOutMakefile_AM->file, "\n" );

   /* Seperate generation of xml description file */
   fprintf(gOutFunc_XML->file, "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n");
   fprintf(gOutFunc_XML->file, "<FinancialFunctions>\n");
   retCode = TA_ForEachFunc( doForEachFunctionXml, NULL );
   fprintf(gOutFunc_XML->file, "</FinancialFunctions>\n");

   /* Append some "hard coded" prototype for ta_func */
   appendToFunc( gOutFunc_H->file );
   appendToFunc( gOutFunc_SWG->file );

#ifdef TA_LIB_PRO
      /* Section for code distributed with TA-Lib Pro only. */
#endif

   /* Close all files who were updated with the list of TA functions. */
   fileClose( gOutFuncList_TXT );
   fileClose( gOutFunc_H );
   fileClose( gOutFunc_SWG );
   fileClose( gOutFrame_H );
   fileClose( gOutFrame_C );
   fileClose( gOutFunc_XML );
   fileClose( gOutMakefile_AM );
   fileClose( gOutCore_Java );
   fileClose( gOutJavaDefs_H );
   fileClose( gOutFunc_Annotation );
   fileDelete( FILE_CORE_JAVA_TMP );

   #ifdef _MSC_VER
      fileClose( gOutDotNet_H );
      fileClose( gOutVS2005ProjFile );
      fileClose( gOutVS2008ProjFile );
      fileClose( gOutProjFile );
      fileClose( gOutMSVCProjFile );
      fileClose( gOutExcelGlue_C );

#ifdef TA_LIB_PRO
      /* Section for code distributed with TA-Lib Pro only. */
#endif

   #endif

   if( retCode != TA_SUCCESS )
   {
      printf( "Failed [%d]\n", retCode );
      return -1;
   }

   /* Create the "ta_group_idx.c" file. */
   genPrefix = 1;
   gOutGroupIdx_C = fileOpen( ta_fs_path(4, "..", "src", "ta_abstract", "ta_group_idx.c"),
                              ta_fs_path(5, "..", "src", "ta_abstract", "templates", "ta_group_idx.c.template"),
                              FILE_WRITE|WRITE_ON_CHANGE_ONLY );

   if( gOutGroupIdx_C == NULL )
   {
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }

   retCode = TA_ForEachFunc( printExternReferenceForEachFunction, NULL );
   if( retCode != TA_SUCCESS )
   {
      fileClose( gOutGroupIdx_C );
      return -1;
   }

   nbGroup = forEachGroup( printPerGroupList, NULL );

   print( gOutGroupIdx_C->file, "const TA_FuncDef **TA_PerGroupFuncDef[%d] = {\n", nbGroup );
   forEachGroup( printGroupListAddress, NULL );
   print( gOutGroupIdx_C->file, "};\n\n" );

   print( gOutGroupIdx_C->file, "const unsigned int TA_PerGroupSize[%d] = {\n", nbGroup );
   forEachGroup( printGroupSize, NULL );
   print( gOutGroupIdx_C->file, "};\n\n" );

   print( gOutGroupIdx_C->file, "const unsigned int TA_TotalNbFunction =\n" );
   forEachGroup( printGroupSizeAddition, NULL );

   fileClose( gOutGroupIdx_C );
   genPrefix = 0;

   /* Update "ta_defs.h" */
   doDefsFile();
 
   /* Convert the xml description file into a format embedded in the library. */
   if( generateFuncAPI_C() != 1 )
   {
      return -1; /*  Failed. */
   }


   /* Run Java Post-Processing.   
    * On Success, the Java program create a file named "java_success". 
    */
      printf( "\nPost-Processing Java Code\n" );
      # define JAVA_SUCCESS_FILE     ta_fs_path(3, "..", "temp", "java_success")
      #define JAVA_PRETTY_TEMP_FILE ta_fs_path(3, "..", "temp", "CoreJavaPretty.tmp")
      fileDelete( JAVA_SUCCESS_FILE );

#ifdef _MSC_VER 
      system( "javac -cp . -d . \".." TA_FS_SLASH "src" TA_FS_SLASH "tools" TA_FS_SLASH "gen_code" TA_FS_SLASH "java" TA_FS_SLASH "PrettyCode.java" );
      system( "javac -cp . -d . \".." TA_FS_SLASH "src" TA_FS_SLASH "tools" TA_FS_SLASH "gen_code" TA_FS_SLASH "java" TA_FS_SLASH "Main.java" );
#else
      system( "javac -cp . -d . .." TA_FS_SLASH "src" TA_FS_SLASH "tools" TA_FS_SLASH "gen_code" TA_FS_SLASH "java" TA_FS_SLASH "PrettyCode.java" );
      system( "javac -cp . -d . .." TA_FS_SLASH "src" TA_FS_SLASH "tools" TA_FS_SLASH "gen_code" TA_FS_SLASH "java" TA_FS_SLASH "Main.java" );
#endif
      system( "java -cp . Main" );
      tempFile = fileOpen(JAVA_SUCCESS_FILE,NULL,FILE_READ );
      fileDelete( FILE_CORE_JAVA_UNF );

      if( tempFile == NULL )
      {                  
         printf( "\nWarning: Java code NOT updated.\n" );
      }
      else
      {

         fileClose( tempFile );

         /* Java processing done. Overwrite the original Core.java ONLY if there
          * is changes (re-use fileOpen/fileClose even if not efficient).
          */
         tempFile = fileOpen( JAVA_PRETTY_TEMP_FILE, NULL, FILE_READ );
         tempFileOut = fileOpen( FILE_CORE_JAVA, NULL,
                                 FILE_WRITE|WRITE_ON_CHANGE_ONLY );

         if( (tempFile == NULL) || (tempFileOut == NULL) )
         {
            printf( "\nError: Java code update failed.\n" );
            return -1;
         }
         else
         {
            
            while( fgets( gTempBuf, BUFFER_SIZE, tempFile->file ) )
               fputs(gTempBuf,tempFileOut->file);            

            fileClose(tempFile);
            fileClose(tempFileOut);
         }      
      }
      fileDelete( JAVA_SUCCESS_FILE );
      fileDelete( JAVA_PRETTY_TEMP_FILE );

   /* Remove temporary files. */
   #ifdef _MSC_VER   
      fileDelete( FILE_NET_PROJ_TMP );
      fileDelete( FILE_MSVC_PROJ_TMP );
      fileDelete( FILE_NET_HEADER_TMP );   
   #endif

   printf( "\n** Update completed with success **\n");

   return 0;
}

unsigned int forEachGroup( TA_ForEachGroup forEachGroupFunc,
                                  void *opaqueData )
{
   TA_RetCode retCode;
   TA_StringTable *table;
   unsigned int i;   

   (void)opaqueData; /* Get ride of compiler warning */

   retCode = TA_GroupTableAlloc( &table );
   if( retCode != TA_SUCCESS )
      return 0;

   for( i=0; i < table->size; i++ )
   {
      forEachGroupFunc( table->string[i],
                        i,
                        i==0? 1:0,
                        i==(table->size-1)? 1:0 );
   }
   
   retCode = TA_GroupTableFree( table );
   if( retCode != TA_SUCCESS )
      return 0;

   return i;
}

/* Replaces reserved xml characters with the appropriate escape sequence. */
void ReplaceReservedXmlCharacters(const char *input, char *output )
{
	char *currentPosition;
	char tempString[8*1024];

	if((input == NULL) || (output == NULL))
	{
		return;
	}

	strcpy(output, input);

	/*Replace '&' with "&amp;"
	 *Note1: '&' has to be processed first as otherwise we replace the
	 *       '&' in the escaped characters.
	 *Note2: We assume that the input string does not have any escaped
	 *       characters already.
     */
	currentPosition = output;
	while((currentPosition = strchr(currentPosition, '&')) != NULL)
	{
		tempString[0] = '\0';
		if(strlen(currentPosition) > 1)
		{
			strcpy(tempString, currentPosition+1);
		}
		sprintf(currentPosition, "&amp;%s", tempString);
	}

	/* Replace '<' with "&lt;" */
	currentPosition = output;
	while((currentPosition = strchr(currentPosition, '<')) != NULL)
	{
		tempString[0] = '\0';
		if(strlen(currentPosition) > 1)
		{
			strcpy(tempString, currentPosition+1);
		}
		sprintf(currentPosition, "&lt;%s", tempString);
	}

	/* Replace '>' with "&gt;" */
	currentPosition = output;
	while((currentPosition = strchr(currentPosition, '>')) != NULL)
	{
		tempString[0] = '\0';
		if(strlen(currentPosition) > 1)
		{
			strcpy(tempString, currentPosition+1);
		}
		sprintf(currentPosition, "&gt;%s", tempString);
	}

    /* Replace ''' with "&apos;" */
	currentPosition = output;
	while((currentPosition = strchr(currentPosition, '\'')) != NULL)
	{
		tempString[0] = '\0';
		if(strlen(currentPosition) > 1)
		{
			strcpy(tempString, currentPosition+1);
		}
		sprintf(currentPosition, "&apos;%s", tempString);
	}

	/* Replace '"' with "&quot;" */
	currentPosition = output;
	while((currentPosition = strchr(currentPosition, '"')) != NULL)
	{
		tempString[0] = '\0';
		if(strlen(currentPosition) > 1)
		{
			strcpy(tempString, currentPosition+1);
		}
		sprintf(currentPosition, "&quot;%s", tempString);
	}
}

void doForEachFunctionXml(const TA_FuncInfo *funcInfo,
								 void *opaqueData)
{
    TA_RetCode retCode;
	const TA_InputParameterInfo *inputInfo;
	const TA_OptInputParameterInfo *optInputInfo;
	const TA_OutputParameterInfo *outputInfo;
	char tempString[8*1024];
	unsigned int i;

    (void)opaqueData;

	/* General stuff about function */
	fprintf(gOutFunc_XML->file, "	<!-- %s -->\n", funcInfo->name);
	fprintf(gOutFunc_XML->file, "	<FinancialFunction>\n");
    fprintf(gOutFunc_XML->file, "		<Abbreviation>%s</Abbreviation>\n", (funcInfo->name == NULL)? "" : funcInfo->name);
    fprintf(gOutFunc_XML->file, "		<CamelCaseName>%s</CamelCaseName>\n", (funcInfo->camelCaseName == NULL)? "" : funcInfo->camelCaseName);
	ReplaceReservedXmlCharacters(funcInfo->hint, tempString);
    fprintf(gOutFunc_XML->file, "		<ShortDescription>%s</ShortDescription>\n", (funcInfo->hint == NULL)? "" : tempString);
    fprintf(gOutFunc_XML->file, "		<GroupId>%s</GroupId>\n", funcInfo->group);

	/* Optional function flags */
	if(funcInfo->flags & (TA_FUNC_FLG_OVERLAP | TA_FUNC_FLG_VOLUME | TA_FUNC_FLG_CANDLESTICK | TA_FUNC_FLG_UNST_PER))
	{
	    fprintf(gOutFunc_XML->file, "		<Flags>\n");
		if(funcInfo->flags & TA_FUNC_FLG_OVERLAP)
		{
			fprintf(gOutFunc_XML->file, "			<Flag>Overlap</Flag>\n");
		}
		if(funcInfo->flags & TA_FUNC_FLG_VOLUME)
		{
			fprintf(gOutFunc_XML->file, "			<Flag>Volume</Flag>\n");
		}
		if(funcInfo->flags & TA_FUNC_FLG_CANDLESTICK)
		{
			fprintf(gOutFunc_XML->file, "			<Flag>Candlestick</Flag>\n");
		}
		if(funcInfo->flags & TA_FUNC_FLG_UNST_PER)
		{
			fprintf(gOutFunc_XML->file, "			<Flag>Unstable Period</Flag>\n");
		}
		
	    fprintf(gOutFunc_XML->file, "		</Flags>\n");
	}


	/* Required input arguments */
    fprintf(gOutFunc_XML->file, "		<RequiredInputArguments>\n");
	for(i=0; i<funcInfo->nbInput; i++)
	{
		retCode = TA_GetInputParameterInfo( funcInfo->handle, i, &inputInfo);

        if( retCode != TA_SUCCESS )
        {
           printf( "Error in TA_GetInputParameterInfo (%d)\n", retCode );
           return;
        }

		if(inputInfo->type == TA_Input_Price)
		{
			if(inputInfo->flags & TA_IN_PRICE_OPEN)
			{
				fprintf(gOutFunc_XML->file, "			<RequiredInputArgument>\n");
				fprintf(gOutFunc_XML->file, "				<Type>Open</Type>\n");
				fprintf(gOutFunc_XML->file, "				<Name>Open</Name>\n");
				fprintf(gOutFunc_XML->file, "			</RequiredInputArgument>\n");
			}
			if(inputInfo->flags & TA_IN_PRICE_HIGH)
			{
				fprintf(gOutFunc_XML->file, "			<RequiredInputArgument>\n");
				fprintf(gOutFunc_XML->file, "				<Type>High</Type>\n");
				fprintf(gOutFunc_XML->file, "				<Name>High</Name>\n");
				fprintf(gOutFunc_XML->file, "			</RequiredInputArgument>\n");
			}
			if(inputInfo->flags & TA_IN_PRICE_LOW)
			{
				fprintf(gOutFunc_XML->file, "			<RequiredInputArgument>\n");
				fprintf(gOutFunc_XML->file, "				<Type>Low</Type>\n");
				fprintf(gOutFunc_XML->file, "				<Name>Low</Name>\n");
				fprintf(gOutFunc_XML->file, "			</RequiredInputArgument>\n");
			}
			if(inputInfo->flags & TA_IN_PRICE_CLOSE)
			{
				fprintf(gOutFunc_XML->file, "			<RequiredInputArgument>\n");
				fprintf(gOutFunc_XML->file, "				<Type>Close</Type>\n");
				fprintf(gOutFunc_XML->file, "				<Name>Close</Name>\n");
				fprintf(gOutFunc_XML->file, "			</RequiredInputArgument>\n");
			}
			if(inputInfo->flags & TA_IN_PRICE_VOLUME)
			{
				fprintf(gOutFunc_XML->file, "			<RequiredInputArgument>\n");
				fprintf(gOutFunc_XML->file, "				<Type>Volume</Type>\n");
				fprintf(gOutFunc_XML->file, "				<Name>Volume</Name>\n");
				fprintf(gOutFunc_XML->file, "			</RequiredInputArgument>\n");
			}
			if(inputInfo->flags & TA_IN_PRICE_OPENINTEREST)
			{
				fprintf(gOutFunc_XML->file, "			<RequiredInputArgument>\n");
				fprintf(gOutFunc_XML->file, "				<Type>Open Interest</Type>\n");
				fprintf(gOutFunc_XML->file, "				<Name>Open Interest</Name>\n");
				fprintf(gOutFunc_XML->file, "			</RequiredInputArgument>\n");
			}
			if(inputInfo->flags & TA_IN_PRICE_TIMESTAMP)
			{
				fprintf(gOutFunc_XML->file, "			<RequiredInputArgument>\n");
				fprintf(gOutFunc_XML->file, "				<Type>Timestamp</Type>\n");
				fprintf(gOutFunc_XML->file, "				<Name>Timestamp</Name>\n");
				fprintf(gOutFunc_XML->file, "			</RequiredInputArgument>\n");
			}
		}
		else
		{
			fprintf(gOutFunc_XML->file, "			<RequiredInputArgument>\n");
			if(inputInfo->type == TA_Input_Real)
			{
				fprintf(gOutFunc_XML->file, "				<Type>Double Array</Type>\n");
			}
			else if(inputInfo->type == TA_Input_Integer)
			{
				fprintf(gOutFunc_XML->file, "				<Type>Integer Array</Type>\n");
			}
			else
			{
				printf("Unknown input type detected.\n");
			}
			fprintf(gOutFunc_XML->file, "				<Name>%s</Name>\n", inputInfo->paramName);
			fprintf(gOutFunc_XML->file, "			</RequiredInputArgument>\n");
		}
	}
    fprintf(gOutFunc_XML->file, "		</RequiredInputArguments>\n");

	/* Optional input arguments */
	if(funcInfo->nbOptInput > 0)
	{

		fprintf(gOutFunc_XML->file, "		<OptionalInputArguments>\n");
		for(i=0; i<funcInfo->nbOptInput; i++)
		{
			retCode = TA_GetOptInputParameterInfo( funcInfo->handle, i, &optInputInfo );

            if( retCode != TA_SUCCESS )
            {
               printf( "Error in TA_GetOptInputParameterInfo (%d)\n", retCode );
               return;
            }

			fprintf(gOutFunc_XML->file, "			<OptionalInputArgument>\n");
			fprintf(gOutFunc_XML->file, "				<Name>%s</Name>\n", optInputInfo->displayName);
			ReplaceReservedXmlCharacters(optInputInfo->hint, tempString);
			fprintf(gOutFunc_XML->file, "				<ShortDescription>%s</ShortDescription>\n", (optInputInfo->hint == NULL)? "" : tempString);
			if(optInputInfo->flags != 0)
			{
				fprintf(gOutFunc_XML->file, "				<Flags>\n");

				if(optInputInfo->flags & TA_OPTIN_IS_PERCENT)
				{
					fprintf(gOutFunc_XML->file, "					<Flag>Percent</Flag>\n");
				}
				if(optInputInfo->flags & TA_OPTIN_IS_DEGREE)
				{
					fprintf(gOutFunc_XML->file, "					<Flag>Degree</Flag>\n");
				}
				if(optInputInfo->flags & TA_OPTIN_IS_CURRENCY)
				{
					fprintf(gOutFunc_XML->file, "					<Flag>Currency</Flag>\n");
				}
				if(optInputInfo->flags & TA_OPTIN_ADVANCED)
				{
					fprintf(gOutFunc_XML->file, "					<Flag>Advanced</Flag>\n");
				}

				fprintf(gOutFunc_XML->file, "				</Flags>\n");
			}

			if(optInputInfo->type == TA_OptInput_RealRange)
			{
				TA_RealRange *doubleRange;
					
				doubleRange= (TA_RealRange*)optInputInfo->dataSet;
				fprintf(gOutFunc_XML->file, "				<Type>Double</Type>\n");
				fprintf(gOutFunc_XML->file, "				<Range>\n");
				fprintf(gOutFunc_XML->file, "					<Minimum>%s</Minimum>\n", doubleToStr(doubleRange->min));
				fprintf(gOutFunc_XML->file, "					<Maximum>%s</Maximum>\n", doubleToStr(doubleRange->max));
				fprintf(gOutFunc_XML->file, "					<Precision>%d</Precision>\n", doubleRange->precision);
				fprintf(gOutFunc_XML->file, "					<SuggestedStart>%s</SuggestedStart>\n", doubleToStr(doubleRange->suggested_start));
				fprintf(gOutFunc_XML->file, "					<SuggestedEnd>%s</SuggestedEnd>\n", doubleToStr(doubleRange->suggested_end));
				fprintf(gOutFunc_XML->file, "					<SuggestedIncrement>%s</SuggestedIncrement>\n", doubleToStr(doubleRange->suggested_increment));
				fprintf(gOutFunc_XML->file, "				</Range>\n");
				fprintf(gOutFunc_XML->file, "				<DefaultValue>%s</DefaultValue>\n", doubleToStr(optInputInfo->defaultValue));
			}
			else if(optInputInfo->type == TA_OptInput_IntegerRange)
			{
				TA_IntegerRange *integerRange;
				
				integerRange = (TA_IntegerRange*)optInputInfo->dataSet;
				fprintf(gOutFunc_XML->file, "				<Type>Integer</Type>\n");
				fprintf(gOutFunc_XML->file, "				<Range>\n");
				fprintf(gOutFunc_XML->file, "					<Minimum>%d</Minimum>\n", integerRange->min);
				fprintf(gOutFunc_XML->file, "					<Maximum>%d</Maximum>\n", integerRange->max);
				fprintf(gOutFunc_XML->file, "					<SuggestedStart>%d</SuggestedStart>\n", integerRange->max);
				fprintf(gOutFunc_XML->file, "					<SuggestedEnd>%d</SuggestedEnd>\n", integerRange->max);
				fprintf(gOutFunc_XML->file, "					<SuggestedIncrement>%d</SuggestedIncrement>\n", integerRange->max);
				fprintf(gOutFunc_XML->file, "				</Range>\n");
				fprintf(gOutFunc_XML->file, "				<DefaultValue>%d</DefaultValue>\n", (int)optInputInfo->defaultValue);
			}
			else if(optInputInfo->type == TA_OptInput_IntegerList)
			{
				TA_IntegerList *intList;
					
				intList = (TA_IntegerList*) optInputInfo->dataSet;
				fprintf(gOutFunc_XML->file, "				<Type>MA Type</Type>\n");
				fprintf(gOutFunc_XML->file, "				<DefaultValue>%d</DefaultValue>\n", (int)optInputInfo->defaultValue);
				if( intList != (TA_IntegerList*) TA_DEF_UI_MA_Method.dataSet )
				{
					printf("Integer lists are not supported.\n");
				}
			}
			else
			{
				printf("Unknown optional input type detected.\n");
			}

			fprintf(gOutFunc_XML->file, "			</OptionalInputArgument>\n");
		}
		fprintf(gOutFunc_XML->file, "		</OptionalInputArguments>\n");
	}

	/* Output arguments */
	fprintf(gOutFunc_XML->file, "		<OutputArguments>\n");
	for(i=0; i<funcInfo->nbOutput; i++)
	{
		retCode = TA_GetOutputParameterInfo( funcInfo->handle, i, &outputInfo );

        if( retCode != TA_SUCCESS )
        {
           printf( "Error in TA_GetOutputParameterInfo (%d)\n", retCode );
           return;
        }

		fprintf(gOutFunc_XML->file, "			<OutputArgument>\n");
		if(outputInfo->type == TA_Output_Integer)
		{
			fprintf(gOutFunc_XML->file, "				<Type>Integer Array</Type>\n");
		}
		else if(outputInfo->type == TA_Output_Real)
		{
			fprintf(gOutFunc_XML->file, "				<Type>Double Array</Type>\n");
		}
		else
		{
			printf("Unknown output type detected.\n");
		}
		fprintf(gOutFunc_XML->file, "				<Name>%s</Name>\n", outputInfo->paramName);
		if(outputInfo->flags != 0)
		{
			fprintf(gOutFunc_XML->file, "				<Flags>\n");

			if(outputInfo->flags & TA_OUT_LINE)
			{
				fprintf(gOutFunc_XML->file, "					<Flag>Line</Flag>\n");
			}
			if(outputInfo->flags & TA_OUT_DOT_LINE)
			{
				fprintf(gOutFunc_XML->file, "					<Flag>Dotted Line</Flag>\n");
			}
			if(outputInfo->flags & TA_OUT_DASH_LINE)
			{
				fprintf(gOutFunc_XML->file, "					<Flag>Dashed Line</Flag>\n");
			}
			if(outputInfo->flags & TA_OUT_DOT)
			{
				fprintf(gOutFunc_XML->file, "					<Flag>Dots</Flag>\n");
			}
			if(outputInfo->flags & TA_OUT_HISTO)
			{
				fprintf(gOutFunc_XML->file, "					<Flag>Histogram</Flag>\n");
			}
			if(outputInfo->flags & TA_OUT_PATTERN_BOOL)
			{
				fprintf(gOutFunc_XML->file, "					<Flag>Pattern Bool</Flag>\n");
			}
			if(outputInfo->flags & TA_OUT_PATTERN_BULL_BEAR)
			{
				fprintf(gOutFunc_XML->file, "					<Flag>Pattern Bull Bear</Flag>\n");
			}
			if(outputInfo->flags & TA_OUT_PATTERN_STRENGTH)
			{
				fprintf(gOutFunc_XML->file, "					<Flag>Pattern Strength</Flag>\n");
			}
			if(outputInfo->flags & TA_OUT_POSITIVE)
			{
				fprintf(gOutFunc_XML->file, "					<Flag>Positive</Flag>\n");
			}
			if(outputInfo->flags & TA_OUT_NEGATIVE)
			{
				fprintf(gOutFunc_XML->file, "					<Flag>Negative</Flag>\n");
			}
			if(outputInfo->flags & TA_OUT_ZERO)
			{
				fprintf(gOutFunc_XML->file, "					<Flag>Zero</Flag>\n");
			}
			if(outputInfo->flags & TA_OUT_UPPER_LIMIT)
			{
				fprintf(gOutFunc_XML->file, "					<Flag>Upper Limit</Flag>\n");
			}
			if(outputInfo->flags & TA_OUT_LOWER_LIMIT)
			{
				fprintf(gOutFunc_XML->file, "					<Flag>Lower Limit</Flag>\n");
			}

			fprintf(gOutFunc_XML->file, "				</Flags>\n");
		}
		fprintf(gOutFunc_XML->file, "			</OutputArgument>\n");
	}
	fprintf(gOutFunc_XML->file, "		</OutputArguments>\n");
    fprintf(gOutFunc_XML->file, "	</FinancialFunction>\n");
	fprintf(gOutFunc_XML->file, "\n");
	fprintf(gOutFunc_XML->file, "\n");
}

void doForEachFunctionPhase1( const TA_FuncInfo *funcInfo,
                               void *opaqueData )
{
	(void)opaqueData;

      /* Run the func file through the pre-processor to generate the Java code. */
      genJavaCodePhase1( funcInfo );      
}

int firstTime = 1;

void doForEachFunctionPhase2( const TA_FuncInfo *funcInfo,
                               void *opaqueData )
{


   (void)opaqueData; /* Get ride of compiler warning */

   /* Add this function to the "ta_func_list.txt" */
   genPrefix = 0;
   fprintf( gOutFuncList_TXT->file, "%-20s%s\n", funcInfo->name, funcInfo->hint );
  
   fprintf( gOutFunc_H->file, "\n" );
   fprintf( gOutFunc_SWG->file, "\n" );

   printf( "Processing [TA_%s]\n", funcInfo->name );

   fprintf( gOutFunc_H->file, "/*\n" );
   printFuncHeaderDoc( gOutFunc_H->file, funcInfo, " * " );
   fprintf( gOutFunc_H->file, " */\n" );

   fprintf( gOutFunc_SWG->file, "/*\n" );
   printFuncHeaderDoc( gOutFunc_SWG->file, funcInfo, " * " );
   fprintf( gOutFunc_SWG->file, " */\n" );

   /* Generate the defines corresponding to this function. */
   printDefines( gOutFunc_H->file, funcInfo );
   printDefines( gOutFunc_SWG->file, funcInfo );

   /* Generate the function prototype. */
   printFunc( gOutFunc_H->file, "TA_LIB_API ", funcInfo, pfs_prototype | pfs_semiColonNeeded );
   fprintf( gOutFunc_H->file, "\n" );

   printFunc( gOutFunc_H->file, "TA_LIB_API ", funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_inputIsSinglePrecision);
   fprintf( gOutFunc_H->file, "\n" );

   /* Generate the SWIG interface. */
   printFunc( gOutFunc_SWG->file, NULL, funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_outputForSWIG);
   fprintf( gOutFunc_SWG->file, "\n" );

   /* Generate the corresponding lookback function prototype. */
   printFunc( gOutFunc_H->file, "TA_LIB_API ", funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_lookbackSignature );
   fprintf( gOutFunc_H->file, "\n" );
   printFunc( gOutFunc_SWG->file, NULL, funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_lookbackSignature );
   fprintf( gOutFunc_SWG->file, "\n" );

   /* Generate the corresponding state struct declaration. */
   printFunc( gOutFunc_H->file, "TA_LIB_API ", funcInfo, pfs_prototype | pfs_stateStruct );
   fprintf( gOutFunc_H->file, "\n" );
   printFunc( gOutFunc_SWG->file, NULL, funcInfo, pfs_prototype | pfs_stateStruct );
   fprintf( gOutFunc_SWG->file, "\n" );

   /* Generate the corresponding state init function prototype. */
   printFunc( gOutFunc_H->file, "TA_LIB_API ", funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_stateInitSignature );
   fprintf( gOutFunc_H->file, "\n" );
   printFunc( gOutFunc_SWG->file, NULL, funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_stateInitSignature );
   fprintf( gOutFunc_SWG->file, "\n" );

   /* Generate the corresponding state function prototype. */
   printFunc( gOutFunc_H->file, "TA_LIB_API ", funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_stateFuncSignature );
   fprintf( gOutFunc_H->file, "\n" );
   printFunc( gOutFunc_SWG->file, NULL, funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_stateFuncSignature );
   fprintf( gOutFunc_SWG->file, "\n" );

   /* Generate the corresponding state free function prototype. */
   printFunc( gOutFunc_H->file, "TA_LIB_API ", funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_stateFreeSignature );
   printFunc( gOutFunc_SWG->file, NULL, funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_stateFreeSignature );

   /* Generate the corresponding state save function prototype. */
   printFunc( gOutFunc_H->file, "TA_LIB_API ", funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_stateSaveSignature );
   printFunc( gOutFunc_SWG->file, NULL, funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_stateSaveSignature );

   /* Generate the corresponding state load function prototype. */
   printFunc( gOutFunc_H->file, "TA_LIB_API ", funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_stateLoadSignature );
   printFunc( gOutFunc_SWG->file, NULL, funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_stateLoadSignature );


   genPrefix = 1;
   printStateTestFunc( gOutFunc_H->file, funcInfo);
   genPrefix = 0;

   /* Create the frame definition (ta_frame.c) and declaration (ta_frame.h) */
   genPrefix = 1;
   printFrameHeader( gOutFrame_H->file, funcInfo, 0 );
   fprintf( gOutFrame_H->file, ";\n" );
   printFrameHeader( gOutFrame_H->file, funcInfo, pfs_lookbackSignature );
   fprintf( gOutFrame_H->file, ";\n" );
   printFrameHeader( gOutFrame_H->file, funcInfo, pfs_stateInitSignature );
   fprintf( gOutFrame_H->file, ";\n" );
   printFrameHeader( gOutFrame_H->file, funcInfo, pfs_stateFuncSignature );
   fprintf( gOutFrame_H->file, ";\n" );
   printFrameHeader( gOutFrame_H->file, funcInfo, pfs_stateFreeSignature );
   fprintf( gOutFrame_H->file, ";\n" );
   printFrameHeader( gOutFrame_H->file, funcInfo, pfs_stateSaveSignature );
   fprintf( gOutFrame_H->file, ";\n" );
   printFrameHeader( gOutFrame_H->file, funcInfo, pfs_stateLoadSignature );
   fprintf( gOutFrame_H->file, ";\n\n" );
   printCallFrame( gOutFrame_C->file, funcInfo );

   /* Add this function to the Makefile.am */
   if( firstTime )
      fprintf( gOutMakefile_AM->file, "\tta_%s.c", funcInfo->name );
   else
      fprintf( gOutMakefile_AM->file, " " TA_FS_SLASH "\n\tta_%s.c", funcInfo->name );
   
   #ifdef _MSC_VER
      /* Add the entry in the .NET project file. */
      fprintf( gOutProjFile->file, "				<File\n" );
      fprintf( gOutProjFile->file, "					RelativePath=\".." TA_FS_SLASH ".." TA_FS_SLASH ".." TA_FS_SLASH "c" TA_FS_SLASH "src" TA_FS_SLASH "ta_func" TA_FS_SLASH "ta_%s.c\">\n", funcInfo->name );
      fprintf( gOutProjFile->file, "					<FileConfiguration\n" );
      fprintf( gOutProjFile->file, "						Name=\"Debug|Win32\">\n" );
      fprintf( gOutProjFile->file, "						<Tool\n" );
      fprintf( gOutProjFile->file, "							Name=\"VCCLCompilerTool\"\n" );
      fprintf( gOutProjFile->file, "							AdditionalIncludeDirectories=\"\"\n" );
      fprintf( gOutProjFile->file, "							UsePrecompiledHeader=\"0\"\n" );
      fprintf( gOutProjFile->file, "							CompileAs=\"2\"/>\n" );
      fprintf( gOutProjFile->file, "					</FileConfiguration>\n" );
      fprintf( gOutProjFile->file, "					<FileConfiguration\n" );
      fprintf( gOutProjFile->file, "						Name=\"Release|Win32\">\n" );
      fprintf( gOutProjFile->file, "						<Tool\n" );
      fprintf( gOutProjFile->file, "							Name=\"VCCLCompilerTool\"\n" );
      fprintf( gOutProjFile->file, "							AdditionalIncludeDirectories=\"\"\n" );
      fprintf( gOutProjFile->file, "							UsePrecompiledHeader=\"0\"\n" );
      fprintf( gOutProjFile->file, "							CompileAs=\"2\"/>\n" );
      fprintf( gOutProjFile->file, "					</FileConfiguration>\n" );
      fprintf( gOutProjFile->file, "					<FileConfiguration\n" );
      fprintf( gOutProjFile->file, "						Name=\"Debug SubArray|Win32\">\n" );
      fprintf( gOutProjFile->file, "						<Tool\n" );
      fprintf( gOutProjFile->file, "							Name=\"VCCLCompilerTool\"\n" );
      fprintf( gOutProjFile->file, "							AdditionalIncludeDirectories=\"\"\n" );
      fprintf( gOutProjFile->file, "							UsePrecompiledHeader=\"0\"\n" );
      fprintf( gOutProjFile->file, "							CompileAs=\"2\"/>\n" );
      fprintf( gOutProjFile->file, "					</FileConfiguration>\n" );
      fprintf( gOutProjFile->file, "					<FileConfiguration\n" );
      fprintf( gOutProjFile->file, "						Name=\"Release SubArray|Win32\">\n" );
      fprintf( gOutProjFile->file, "						<Tool\n" );
      fprintf( gOutProjFile->file, "							Name=\"VCCLCompilerTool\"\n" );
      fprintf( gOutProjFile->file, "							AdditionalIncludeDirectories=\"\"\n" );
      fprintf( gOutProjFile->file, "							UsePrecompiledHeader=\"0\"\n" );
      fprintf( gOutProjFile->file, "							CompileAs=\"2\"/>\n" );
      fprintf( gOutProjFile->file, "					</FileConfiguration>\n" );
      fprintf( gOutProjFile->file, "				</File>\n" );

      /* Add the entry in the MSVC project file. */
      fprintf( gOutMSVCProjFile->file, "# Begin Source File\n" );
      fprintf( gOutMSVCProjFile->file, "\n" );
      fprintf( gOutMSVCProjFile->file, "SOURCE=.." TA_FS_SLASH ".." TA_FS_SLASH ".." TA_FS_SLASH ".." TA_FS_SLASH "src" TA_FS_SLASH "ta_func" TA_FS_SLASH "ta_%s.c\n", funcInfo->name );
      fprintf( gOutMSVCProjFile->file, "# End Source File\n" );

      /* Add the entry in the VS2005 project file. */
	  printVS2005FileNode( gOutVS2005ProjFile->file, funcInfo->name );

	  /* Add the entry in the VS2008 project file. Same format as VS2005. */
	  printVS2005FileNode( gOutVS2008ProjFile->file, funcInfo->name );


#ifdef TA_LIB_PRO
      /* Section for code distributed with TA-Lib Pro only. */
#endif

      /* Generate the excel glue code */
      printExcelGlueCode( gOutExcelGlue_C->file, funcInfo );
	#endif

      /* Generate CoreAnnotated */
      printJavaFunctionAnnotation( funcInfo );

   #ifdef _MSC_VER
      /* Generate the functions declaration for the .NET interface. */
      printFunc( gOutDotNet_H->file, NULL, funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_lookbackSignature | pfs_managedCPPCode | pfs_managedCPPDeclaration );

	  fprintf( gOutDotNet_H->file, "         #if defined( _MANAGED ) && defined( USE_SUBARRAY )\n" );   

	  // SubArray<double> declaration
      printFunc( gOutDotNet_H->file, NULL, funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_managedCPPCode | pfs_managedCPPDeclaration | pfs_useSubArrayObject);
	  fprintf( gOutDotNet_H->file, "\n" );

	  // SubArray<float> declaration
      printFunc( gOutDotNet_H->file, NULL, funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_managedCPPCode | pfs_managedCPPDeclaration | pfs_inputIsSinglePrecision | pfs_useSubArrayObject );
	  fprintf( gOutDotNet_H->file, "\n" );

	  // cli_array<double> to SubArray<double> conversion 
      printFunc( gOutDotNet_H->file, NULL, funcInfo, pfs_prototype | pfs_managedCPPCode | pfs_managedCPPDeclaration );
	  fprintf( gOutDotNet_H->file, "         { return " );
      printFunc( gOutDotNet_H->file, NULL, funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_managedCPPDeclaration | pfs_useSubArrayObject | pfs_arrayToSubArrayCnvt );
	  fprintf( gOutDotNet_H->file, "         }\n" );

	  // cli_array<float> to SubArray<float> conversion 
      printFunc( gOutDotNet_H->file, NULL, funcInfo, pfs_prototype | pfs_managedCPPCode | pfs_managedCPPDeclaration | pfs_inputIsSinglePrecision );
	  fprintf( gOutDotNet_H->file, "         { return " );
      printFunc( gOutDotNet_H->file, NULL, funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_managedCPPCode | pfs_inputIsSinglePrecision | pfs_useSubArrayObject | pfs_arrayToSubArrayCnvt );
	  fprintf( gOutDotNet_H->file, "         }\n" );

	  fprintf( gOutDotNet_H->file, "         #elif defined( _MANAGED )\n" );
      printFunc( gOutDotNet_H->file, NULL, funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_managedCPPCode | pfs_managedCPPDeclaration );
      printFunc( gOutDotNet_H->file, NULL, funcInfo, pfs_prototype | pfs_semiColonNeeded | pfs_managedCPPCode | pfs_managedCPPDeclaration | pfs_inputIsSinglePrecision );
	  fprintf( gOutDotNet_H->file, "         #endif\n" );

	  fprintf( gOutDotNet_H->file, "\n" );
	  fprintf( gOutDotNet_H->file, "         #define TA_%s Core::%s\n", funcInfo->name, funcInfo->camelCaseName );
	  fprintf( gOutDotNet_H->file, "         #define TA_%s_Lookback Core::%sLookback\n\n", funcInfo->name, funcInfo->camelCaseName );
   #endif

   doFuncFile( funcInfo );

      /* Run the func file through the pre-processor to generate the Java code. */
      genJavaCodePhase2( funcInfo );   

   firstTime = 0;
}

void doForEachUnstableFunction( const TA_FuncInfo *funcInfo,
                                       void *opaqueData )
{
   unsigned int *i;

   i = (unsigned int *)opaqueData;

   if( funcInfo->flags & TA_FUNC_FLG_UNST_PER )
   {
      print( gOutDefs_H->file, "    /* %03d */  ENUM_DEFINE( TA_FUNC_UNST_%s, %s),\n", *i, funcInfo->name, funcInfo->camelCaseName );
      (*i)++;
   }
}

void printDefines( FILE *out, const TA_FuncInfo *funcInfo )
{
   TA_RetCode retCode;
   const TA_OptInputParameterInfo *optInputParamInfo;
   unsigned int i, j;
   unsigned int paramNb;
   const char *paramName;
   const char *defaultParamName;
   TA_IntegerList *intList;
   TA_RealList    *realList;

   /* Go through the optional parameter and print
    * the corresponding define for the TA_OptInput_IntegerList
    * and TA_OptInput_RealList having a string.
    */
   paramNb = 0;
   for( i=0; i < funcInfo->nbOptInput; i++ )
   {
      retCode = TA_GetOptInputParameterInfo( funcInfo->handle,
                                             i, &optInputParamInfo );

      if( retCode != TA_SUCCESS )
      {
         printf( "[%s] invalid 'optional input' information\n", funcInfo->name );
         return;
      }

      paramName = optInputParamInfo->paramName;

      /* TA_MA: Value for parameter */

      switch( optInputParamInfo->type )
      {
      case TA_OptInput_RealList:
         defaultParamName = "optInReal";
         break;
      case TA_OptInput_IntegerList:
         defaultParamName = "optInInteger";
         break;
      default:
         paramNb++;
         continue; /* Skip other type of parameter */
      }

      if( !paramName )
         paramName = defaultParamName;

      /* Output a comment to guide the user. */
         switch( optInputParamInfo->type )
         {
         case TA_OptInput_IntegerList:
            intList = (TA_IntegerList *)optInputParamInfo->dataSet;
            if( intList != (TA_IntegerList *)TA_DEF_UI_MA_Method.dataSet )
            {
               fprintf( out, "\n/* TA_%s: Optional Parameter %s */\n",
                        funcInfo->name, paramName );
               for( j=0; j < intList->nbElement; j++ )
               {
                  strcpy( gTempBuf, intList->data[j].string );
                  cnvtChar( gTempBuf, ' ', '_' );
                  trimWhitespace( gTempBuf );
                  cnvtToUpperCase( gTempBuf );
                  fprintf( out, "#define TA_%s_%s %d\n",
                           funcInfo->name,
                           gTempBuf,
                           intList->data[j].value );

               }
               fprintf( out, "\n" );
            }
            break;
         case TA_OptInput_RealList:
            fprintf( out, "\n/* TA_%s: Optional Parameter %s */\n",
                     funcInfo->name, paramName );

            realList = (TA_RealList *)optInputParamInfo->dataSet;
            for( j=0; j < realList->nbElement; j++ )
            {
               strcpy( gTempBuf, realList->data[j].string );
               cnvtChar( gTempBuf, ' ', '_' );
               trimWhitespace( gTempBuf );
               cnvtToUpperCase( gTempBuf );
               fprintf( out, "#define TA_%s_%s %s\n",
                        funcInfo->name,
                        gTempBuf,
                        doubleToStr(realList->data[j].value) );

            }
            fprintf( out, "\n" );
            break;
         default:
            /* Do nothing */
            break;
         }

      paramNb++;
   }
}

void printFunc( FILE *out,
                       const char *prefix, /* Can be NULL */
                       const TA_FuncInfo *funcInfo,
                       unsigned int settings // set of printFuncSettings
                      )
{
   TA_RetCode retCode;
   unsigned int i, j, k, lastParam;
   int indent;
   unsigned int paramNb;
   const char *paramName;
   const char *defaultParamName;
   const TA_InputParameterInfo *inputParamInfo;
   const TA_OptInputParameterInfo *optInputParamInfo;
   const TA_OutputParameterInfo *outputParamInfo;
   const char *typeString;
   const char *inputDoubleArrayType;
   const char *inputIntArrayType;
   const char *outputDoubleArrayType;
   const char *outputIntArrayType;
   const char *outputIntParam;
   const char *arrayBracket;
   const char *funcName;
   int excludeFromManaged;
   int isMAType;

   const char *startIdxString;
   const char *endIdxString;
   const char *outNbElementString;
   const char *outBegIdxString;
   char funcNameBuffer[1024]; /* Not safe, but 1024 is realistic, */

   // read settings
   #define SETTING_DECL(setting_name) unsigned int setting_name = settings & pfs_##setting_name;
   SETTING_DECL(prototype);
   SETTING_DECL(frame);
   SETTING_DECL(semiColonNeeded);
   SETTING_DECL(validationCode);
   SETTING_DECL(lookbackSignature);
   SETTING_DECL(managedCPPCode);
   SETTING_DECL(managedCPPDeclaration);
   SETTING_DECL(inputIsSinglePrecision);
   SETTING_DECL(outputForSWIG);
   SETTING_DECL(outputForJava);
   SETTING_DECL(lookbackValidationCode);
   SETTING_DECL(useSubArrayObject);
   SETTING_DECL(arrayToSubArrayCnvt);
   SETTING_DECL(stateStruct);
   SETTING_DECL(stateInitSignature);
   SETTING_DECL(stateFuncSignature);
   SETTING_DECL(stateFreeSignature);
   SETTING_DECL(stateTestSignature);
   SETTING_DECL(stateLoadSignature);
   SETTING_DECL(stateSaveSignature);

   #define ANY_SIGNATURE_PARAM (lookbackSignature || stateInitSignature || stateFuncSignature || stateFreeSignature || stateLoadSignature || stateSaveSignature)


   // init text constants begin

   if( arrayToSubArrayCnvt )
   {
      inputIntArrayType     = "int";
      if( inputIsSinglePrecision )
	  {
	      inputDoubleArrayType = "float";
	  }
	  else
	  {
		  inputDoubleArrayType  = "double";
	  }
      outputDoubleArrayType = "double";
      outputIntArrayType    = "int";
      outputIntParam        = " ";
      arrayBracket          = " ";
      startIdxString        = "startIdx";
      endIdxString          = "endIdx";
      outNbElementString    = "outNBElement";
      outBegIdxString       = "outBegIdx";
      funcName              = funcInfo->camelCaseName;
   }
   else if( managedCPPCode )
   {
      if( inputIsSinglePrecision )
	  {
          inputDoubleArrayType  = useSubArrayObject? "SubArray<float>^":"cli::array<float>^";
	  }
	  else
	  {
          inputDoubleArrayType  = useSubArrayObject? "SubArray<double>^":"cli::array<double>^";
	  }

      inputIntArrayType     = useSubArrayObject? "SubArray<int>^"   : "cli::array<int>^";
      outputDoubleArrayType = useSubArrayObject? "SubArray<double>^": "cli::array<double>^";
      outputIntArrayType    = useSubArrayObject? "SubArray<int>^"   : "cli::array<int>^";
      outputIntParam        = "[Out]int%";
      arrayBracket          = "";
      startIdxString        = "startIdx";
      endIdxString          = "endIdx";
      outNbElementString    = "outNBElement";
      outBegIdxString       = "outBegIdx";
      funcName              = funcInfo->camelCaseName;
   }
   else if( outputForSWIG )
   {
      if( inputIsSinglePrecision )
         inputDoubleArrayType  = (stateStruct)? "float *" : "const float  *";
      else
         inputDoubleArrayType  = (stateStruct)? "double *" : "const double *";
      inputIntArrayType     = "const int    *";
      outputIntArrayType    = "int";
      outputDoubleArrayType = "double";
      outputIntParam        = "int";
      arrayBracket          = "";
      startIdxString        = "       START_IDX";
      endIdxString          = "       END_IDX";
      outNbElementString    = "OUT_SIZE";
      outBegIdxString       = "BEG_IDX";
      funcName              = funcInfo->name;
   }
   else if( outputForJava )
   {
      if( inputIsSinglePrecision )
         inputDoubleArrayType  = "float";
      else
         inputDoubleArrayType  = "double";
      inputIntArrayType     = "int";
      outputDoubleArrayType = "double";
      outputIntArrayType    = "int";
      outputIntParam        = "MInteger";
      arrayBracket          = "[]";
      startIdxString        = "startIdx";
      endIdxString          = "endIdx";
      outNbElementString    = "outNBElement";
      outBegIdxString       = "outBegIdx";
      funcName              = funcNameBuffer;

      /* For Java, first letter is always lowercase. */
      strcpy( funcNameBuffer, funcInfo->camelCaseName );
      funcNameBuffer[0] = tolower(funcNameBuffer[0]);      
   }
   else
   {
      if( inputIsSinglePrecision )
         inputDoubleArrayType  = (stateStruct)? "float" : "const float";
      else
         inputDoubleArrayType  = (stateStruct)? "double" : "const double";
      inputIntArrayType     = "const int";
      outputDoubleArrayType = "double";
      outputIntArrayType    = "int";
      outputIntParam        = "int";
      arrayBracket          = "[]";
      startIdxString        = "startIdx";
      endIdxString          = "endIdx";
      outNbElementString    = "outNBElement";
      outBegIdxString       = "outBegIdx";
      funcName              = funcInfo->name;
   }

   typeString = "";
   defaultParamName = "";

   // print the beginning of function declaration with given suffix

#define PRINT_STRUCT_NAME(prefix, funcName, suffix) { \
    if( managedCPPCode ) \
    { \
       sprintf( gTempBuf, "%spublic struct TA_%s_%s ", \
                prefix? prefix:"", \
                funcName, suffix ); \
    } \
    else if( outputForJava ) \
    { \
       sprintf( gTempBuf, "%sclass TA_%s_%s", \
                prefix? prefix:"", \
                funcName, suffix ); \
    } \
    else \
    { \
       sprintf( gTempBuf, "%sstruct TA_%s_%s", \
                prefix? prefix:"", \
                funcName, suffix ); \
    } \
    print( out, gTempBuf ); \
    indent = (unsigned int)strlen(gTempBuf) - 2; \
}

   if (stateStruct && !validationCode)
   {
       PRINT_STRUCT_NAME("", funcName, "Data {\n"); //forward declaration of memory struct
   } else
   if( prototype )
   {

       #define PRINT_SIGNATURE(funcSuffix, returnInt) \
       { \
           if( managedCPPCode ) \
           {        \
              sprintf( gTempBuf, "%s%s%s %s%s%s( ", \
                       prefix? prefix:"", \
                       managedCPPDeclaration? "         static ":"", \
                       returnInt? "int":"Core::RetCode", \
                       managedCPPDeclaration? "":"Core::", \
                       funcName, funcSuffix ); \
           } \
           else if( outputForJava ) \
           {          \
              sprintf( gTempBuf, "%spublic %s %s%s( ", \
                       prefix? prefix:"", \
                       returnInt? "int":"RetCode", \
                       funcName, funcSuffix ); \
           } \
           else \
           { \
              sprintf( gTempBuf, "%s%s TA_%s_%s( ", \
                       prefix? prefix:"", \
                       returnInt? "int":"TA_RetCode", \
                       funcName, funcSuffix ); \
           } \
           print( out, gTempBuf ); \
           indent = (unsigned int)strlen(gTempBuf) - 2; \
       }


      if( lookbackSignature )      
        { PRINT_SIGNATURE("Lookback", 1); }
      else
      if( stateInitSignature )
        { PRINT_SIGNATURE("StateInit", 0); }
      else
      if( stateFuncSignature )
        { PRINT_SIGNATURE("State", 0); }
      else
      if( stateFreeSignature )
        { PRINT_SIGNATURE("StateFree", 0); }
      else
      if( stateLoadSignature )
        { PRINT_SIGNATURE("StateLoad", 0); }
      else
      if( stateSaveSignature )
        { PRINT_SIGNATURE("StateSave", 0); }
      else
      {
         if( arrayToSubArrayCnvt )
		 {			 
             sprintf( gTempBuf, "%s%s%s%s( %s, ", stateTestSignature?"static ":"", prefix? prefix:"", funcName, stateTestSignature?"_StateTest":"", startIdxString );
		 }
         else if( managedCPPCode )
         {
            sprintf( gTempBuf, "%s%s%senum class %sRetCode %s%s%s( int    %s,\n",
                     stateTestSignature?"static ":"",
                     prefix? prefix:"",
                     managedCPPDeclaration? "         static ":"",
                     managedCPPDeclaration? "":"Core::",
                     managedCPPDeclaration? "":"Core::",
                     funcName,
                     stateTestSignature?"_StateTest":"",
                     startIdxString );
         }
         else if( outputForJava )
         {
               sprintf( gTempBuf, "%s%spublic RetCode %s%s( int    %s,\n",
                        stateTestSignature?"static ":"",
                        prefix? prefix:"",                        
                        funcName,
                        stateTestSignature?"_StateTest":"",
                        startIdxString );
         }
         else
         {
            if( inputIsSinglePrecision )
               sprintf( gTempBuf, "%s%sTA_RetCode TA_S_%s%s( int    %s,\n",
                        stateTestSignature?"static ":"",
                        prefix? prefix:"",
                        funcName,
                        stateTestSignature?"_StateTest":"",
                        startIdxString );
            else  
               sprintf( gTempBuf, "%s%sTA_RetCode TA_%s%s( int    %s,\n",
                        stateTestSignature?"static ":"",
                        prefix? prefix:"",                        
                        funcName,
                        stateTestSignature?"_StateTest":"",
                        startIdxString );
         }
         print( out, gTempBuf );
         indent = (unsigned int)strlen(gTempBuf);
         
         if( outputForSWIG )
            indent -= 25;
         else
            indent -= 17;

		 if( indent < 0 ) indent = 0;		 

         printIndent( out, indent );
         if( arrayToSubArrayCnvt )
            fprintf( out, "%s,\n", endIdxString );
		 else
			fprintf( out, "int    %s,\n", endIdxString );
      }
   }
   else if( frame )
   {
      indent = (unsigned int)strlen(funcName);
      if( lookbackSignature )
      {
         print( out, "%sTA_%s_Lookback(", prefix == NULL? "" : prefix, funcName );
         indent += 12;
      } else
      if( stateInitSignature )
      {
         print( out, "%sTA_%s_StateInit(", prefix == NULL? "" : prefix, funcName );
         indent += 12;
      } else
      if( stateFuncSignature )
      {
         print( out, "%sTA_%s_State(", prefix == NULL? "" : prefix, funcName );
         indent += 12;
      } else
      if( stateFreeSignature )
      {
         print( out, "%sTA_%s_StateFree(", prefix == NULL? "" : prefix, funcName );
         indent += 12;
      } else
      if( stateSaveSignature )
      {
         print( out, "%sTA_%s_StateSave(", prefix == NULL? "" : prefix, funcName );
         indent += 12;
      } else
      if( stateLoadSignature )
      {
         print( out, "%sTA_%s_StateLoad(", prefix == NULL? "" : prefix, funcName );
         indent += 12;
      }
      else
      {  
         print( out, "%sTA_%s(", prefix == NULL? "" : prefix, funcName );
         indent += 4;
      }
   }
   else if( validationCode )
   {
      indent = 3;
   }
   else
   {
      printf( "printFunc has nothing to do?\n" );
      return;
   }

   if( prefix )
      indent += (unsigned int)strlen(prefix);
   if( frame )
      indent -= 5;

   if( frame && !ANY_SIGNATURE_PARAM && !stateStruct )
   {
      printIndent( out, indent );
      fprintf( out, "%s,\n", startIdxString );
      printIndent( out, indent );
      fprintf( out, "%s,\n", endIdxString );
   }


   if (stateInitSignature || stateFuncSignature || stateFreeSignature || stateSaveSignature || stateLoadSignature)
   {
       unsigned int last_arg = stateFreeSignature || (!(stateFuncSignature || stateSaveSignature || stateLoadSignature) && funcInfo->nbOptInput == 0);

       if (frame)
           fprintf( out, " %s(struct TA_%s_State**) &params->_state%s\n", (stateFuncSignature||stateSaveSignature)?"*":"", funcName, last_arg?"":"," );
       else
       if (!validationCode) {
       fprintf( out, "struct TA_%s_State*", funcName );
       if (!stateFuncSignature && !stateSaveSignature) fprintf( out, "*");
       fprintf( out, " _state");
       if (!last_arg)
           fprintf( out, ",\n"); // hope that will be more params later
       } else {

           if (!stateSaveSignature && !stateLoadSignature )
           {
               printIndent( out, indent );
               fprintf( out, "if (_state == NULL)\n");
               printIndent( out, indent+6 );
               fprintf( out, "return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);\n");
           } else
           if (stateSaveSignature) {
               printIndent( out, indent );
               fprintf( out, " int io_res; int state_is_null; state_is_null = (_state == NULL);\n");
               printIndent( out, indent );
               fprintf( out, "io_res = fwrite(&state_is_null,sizeof(state_is_null),1,_file);\n");
               printIndent( out, indent );
               fprintf( out, "if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);\n");
               printIndent( out, indent );
               fprintf( out, "if (state_is_null) return ENUM_VALUE(RetCode,TA_SUCCESS,Success);\n");
           } else {
               printIndent( out, indent );
               fprintf( out, "int io_res; int state_is_null;\n");
               printIndent( out, indent );
               fprintf( out, "io_res = fread(&state_is_null,sizeof(state_is_null),1,_file);\n");
               printIndent( out, indent );
               fprintf( out, "if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);\n");
               printIndent( out, indent );
               fprintf( out, "if (state_is_null) return ENUM_VALUE(RetCode,TA_SUCCESS,Success);\n");
           }

//           if (stateInitSignature)
//           is moved close to optIn
       if (stateFreeSignature) {
           printIndent( out, indent );
           fprintf( out, "if (STATE != NULL) {\n");
           printIndent( out, indent+6 );
           fprintf( out, "if (MEM_P != NULL) TA_Free(MEM_P);\n");
           printIndent( out, indent+6 );
           fprintf( out, "TA_Free(STATE); STATE = NULL;}\n");
       } else
           if (stateSaveSignature)
           {

               printIndent( out, indent );
               fprintf( out, "io_res = fwrite(&STATE.mem_index,sizeof(STATE.mem_index),1,_file);\n");
               printIndent( out, indent );
               fprintf( out, "if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);\n");
               printIndent( out, indent );
               fprintf( out, "io_res = fwrite(&STATE.mem_size,sizeof(STATE.mem_size),1,_file);\n");
               printIndent( out, indent );
               fprintf( out, "if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);\n");
               printIndent( out, indent );
               fprintf( out, "int memory_allocated;\n");
               printIndent( out, indent );
               fprintf( out, "memory_allocated = STATE.memory != NULL;\n");
               printIndent( out, indent );
               fprintf( out, "io_res = fwrite(&memory_allocated,sizeof(memory_allocated),1,_file);\n");
               printIndent( out, indent );
               fprintf( out, "if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);\n");
               printIndent( out, indent );
               fprintf( out, "if (memory_allocated && STATE.mem_size > 0) { io_res = fwrite(STATE.memory,sizeof(struct TA_%s_Data),STATE.mem_size,_file);\n", funcName);
               printIndent( out, indent );
               fprintf( out, "if (io_res < (int) STATE.mem_size) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed); }\n");

                   for( i=0; i < funcInfo->nbOptInput; i++ )
                   {
                      retCode = TA_GetOptInputParameterInfo( funcInfo->handle,
                                                          i, &optInputParamInfo );

                      if( retCode != TA_SUCCESS )
                      {
                         printf( "[%s] invalid 'input' information (%d,%d)\n", funcName, i, paramNb );
                         return;
                      }

                      printIndent( out, indent );
                      fprintf( out, "io_res = fwrite(&STATE.%s,sizeof(STATE.%s),1,_file);\n", optInputParamInfo->paramName, optInputParamInfo->paramName);
                      printIndent( out, indent );
                      fprintf( out, "if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);\n");

                   }

               for( i=0; i < funcInfo->nbStructParams; i++ )
               {
                  retCode = TA_GetStructParameterInfo( funcInfo->handle,
                                                      i, &inputParamInfo );

                  if( retCode != TA_SUCCESS )
                  {
                     printf( "[%s] invalid 'opt input' information (%d,%d)\n", funcName, i, paramNb );
                     return;
                  }

                  if ( inputParamInfo->type != TA_Input_Pointer)
                  {
                      printIndent( out, indent );
                      fprintf( out, "io_res = fwrite(&STATE.%s,sizeof(STATE.%s),1,_file);\n", inputParamInfo->paramName, inputParamInfo->paramName);
                      printIndent( out, indent );
                      fprintf( out, "if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);\n");

                  } else {
                      printIndent( out, indent );
                      fprintf( out, "// Warning: STATE.%s must be saved manually!\n", inputParamInfo->paramName);
                  }
               }

           } else
               if (stateLoadSignature)
               {
                   printIndent( out, indent );
                   fprintf( out, "if (STATE != NULL) return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);\n");
                   printIndent( out, indent );
                   fprintf( out, "STATE = TA_Calloc(1, sizeof(struct TA_%s_State));\n", funcName);
                   printIndent( out, indent );
                   fprintf( out, "io_res = fread(&STATE_P.mem_index,sizeof(STATE_P.mem_index),1,_file);\n");
                   printIndent( out, indent );
                   fprintf( out, "if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);\n");
                   printIndent( out, indent );
                   fprintf( out, "io_res = fread(&STATE_P.mem_size,sizeof(STATE_P.mem_size),1,_file);\n");
                   printIndent( out, indent );
                   fprintf( out, "if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);\n");
                   printIndent( out, indent );
                   fprintf( out, "int memory_allocated;\n");
                   printIndent( out, indent );
                   fprintf( out, "io_res = fread(&memory_allocated,sizeof(memory_allocated),1,_file);\n");
                   printIndent( out, indent );
                   fprintf( out, "if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);\n");
                   printIndent( out, indent );
                   fprintf( out, "if (STATE_P.mem_size > 0 && memory_allocated) { STATE_P.memory = TA_Calloc(STATE_P.mem_size, sizeof(struct TA_%s_Data));\n", funcName);
                   printIndent( out, indent );
                   fprintf( out, "io_res = fread(STATE_P.memory,sizeof(struct TA_%s_Data),STATE_P.mem_size,_file);\n", funcName);
                   printIndent( out, indent );
                   fprintf( out, "if (io_res < (int) STATE_P.mem_size) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed); } \n");

                   for( i=0; i < funcInfo->nbOptInput; i++ )
                   {
                      retCode = TA_GetOptInputParameterInfo( funcInfo->handle,
                                                          i, &optInputParamInfo );

                      if( retCode != TA_SUCCESS )
                      {
                         printf( "[%s] invalid 'opt input' information (%d,%d)\n", funcName, i, paramNb );
                         return;
                      }

                      printIndent( out, indent );
                      fprintf( out, "io_res = fread(&STATE_P.%s,sizeof(STATE_P.%s),1,_file);\n", optInputParamInfo->paramName, optInputParamInfo->paramName);
                      printIndent( out, indent );
                      fprintf( out, "if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);\n");

                   }

                   for( i=0; i < funcInfo->nbStructParams; i++ )
                   {
                      retCode = TA_GetStructParameterInfo( funcInfo->handle,
                                                          i, &inputParamInfo );

                      if( retCode != TA_SUCCESS )
                      {
                         printf( "[%s] invalid 'input' information (%d,%d)\n", funcName, i, paramNb );
                         return;
                      }

                      if ( inputParamInfo->type != TA_Input_Pointer)
                      {
                          printIndent( out, indent );
                          fprintf( out, "io_res = fread(&STATE_P.%s,sizeof(STATE_P.%s),1,_file);\n", inputParamInfo->paramName, inputParamInfo->paramName);
                          printIndent( out, indent );
                          fprintf( out, "if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);\n");

                      } else {
                          printIndent( out, indent );
                          fprintf( out, "// Warning: STATE_P.%s must be loaded manually!\n", inputParamInfo->paramName);
                      }
                   }

               }

       }
   }

   /* Go through all the input. */

   int nbInputArgsBufferLen = 0;
   char nbInputArgsBuffer[500];


   if( !lookbackSignature && !lookbackValidationCode && !stateInitSignature && !stateFreeSignature && !stateSaveSignature && !stateLoadSignature)
   {
      if( validationCode )
      {
         printIndent( out, indent );
         fprintf( out, "#if !defined(_JAVA)\n" );
      }

      paramNb = 0;
      for( i=0; i < funcInfo->nbInput; i++ )
      {
         retCode = TA_GetInputParameterInfo( funcInfo->handle,
                                             i, &inputParamInfo );


         if( retCode != TA_SUCCESS )
         {
            printf( "[%s] invalid 'input' information (%d,%d)\n", funcName, i, paramNb );
            return;
         }

         paramName = inputParamInfo->paramName;

         switch( inputParamInfo->type )
         {
         case TA_Input_Price:
            /* Find how many component are requested. */
            j = 0;
            if( inputParamInfo->flags & TA_IN_PRICE_TIMESTAMP )
               j++;
            if( inputParamInfo->flags & TA_IN_PRICE_OPEN )
               j++;
            if( inputParamInfo->flags & TA_IN_PRICE_HIGH )
               j++;
            if( inputParamInfo->flags & TA_IN_PRICE_LOW )
               j++;
            if( inputParamInfo->flags & TA_IN_PRICE_CLOSE )
               j++;
            if( inputParamInfo->flags & TA_IN_PRICE_VOLUME )
               j++;
            if( inputParamInfo->flags & TA_IN_PRICE_OPENINTEREST )
               j++;

            if( j == 0 )
            {
               printf( "[%s] invalid 'price input' information (%d,%d)\n", funcName, i, paramNb );
               return;
            }

            if( validationCode )
            {
               printIndent( out, indent );
               fprintf( out, "/* Verify required price component. */\n" );
               printIndent( out, indent );
               fprintf( out, "if(" );
               k = 0;
               if( inputParamInfo->flags & TA_IN_PRICE_TIMESTAMP )
               {
                  k++;
                  fprintf( out, "!inTimestamp%s", k != j? "||":")");
                  if (stateFuncSignature)
                      nbInputArgsBufferLen = sprintf(((char *)nbInputArgsBuffer)+nbInputArgsBufferLen, "%s%s", (nbInputArgsBufferLen)?",":"", "inTimestamp") + nbInputArgsBufferLen;
               }

               if( inputParamInfo->flags & TA_IN_PRICE_OPEN )
               {
                  k++;
                  fprintf( out, "!inOpen%s", k != j? "||":")");
                  if (stateFuncSignature)
                      nbInputArgsBufferLen = sprintf(((char *)nbInputArgsBuffer)+nbInputArgsBufferLen, "%s%s ", (nbInputArgsBufferLen)?",":"", "inOpen") + nbInputArgsBufferLen;
               }
               
               if( inputParamInfo->flags & TA_IN_PRICE_HIGH )
               {
                  k++;
                  fprintf( out, "!inHigh%s", k != j? "||":")");
                  if (stateFuncSignature)
                      nbInputArgsBufferLen = sprintf(((char *)nbInputArgsBuffer)+nbInputArgsBufferLen, "%s%s ", (nbInputArgsBufferLen)?",":"", "inHigh") + nbInputArgsBufferLen;
               }

               if( inputParamInfo->flags & TA_IN_PRICE_LOW )
               {
                  k++;
                  fprintf( out, "!inLow%s", k != j? "||":")");
                  if (stateFuncSignature)
                      nbInputArgsBufferLen = sprintf(((char *)nbInputArgsBuffer)+nbInputArgsBufferLen, "%s%s ", (nbInputArgsBufferLen)?",":"", "inLow") + nbInputArgsBufferLen;
               }

               if( inputParamInfo->flags & TA_IN_PRICE_CLOSE )
               {
                  k++;
                  fprintf( out, "!inClose%s", k != j? "||":")");
                  if (stateFuncSignature)
                      nbInputArgsBufferLen = sprintf(((char *)nbInputArgsBuffer)+nbInputArgsBufferLen, "%s%s ", (nbInputArgsBufferLen)?",":"", "inClose") + nbInputArgsBufferLen;
               }

               if( inputParamInfo->flags & TA_IN_PRICE_VOLUME )
               {
                  k++;
                  fprintf( out, "!inVolume%s", k != j? "||":")");
                  if (stateFuncSignature)
                      nbInputArgsBufferLen = sprintf(((char *)nbInputArgsBuffer)+nbInputArgsBufferLen, "%s%s ", (nbInputArgsBufferLen)?",":"", "inVolume") + nbInputArgsBufferLen;
               }

               if( inputParamInfo->flags & TA_IN_PRICE_OPENINTEREST )
               {
                  k++;
                  fprintf( out, "!inOpenInterest%s", k != j? "||":")");
                  if (stateFuncSignature)
                      nbInputArgsBufferLen = sprintf(((char *)nbInputArgsBuffer)+nbInputArgsBufferLen, "%s%s ", (nbInputArgsBufferLen)?",":"", "inOpenInterest") + nbInputArgsBufferLen;
               }

               fprintf( out, "\n" );
               printIndent( out, indent );
               fprintf( out, "   return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);\n" );
               print( out, "\n" );
            }
            else
            {
               if( inputParamInfo->flags & TA_IN_PRICE_OPEN )
               {
                  printIndent( out, indent );
                  if( frame )
                     fprintf( out, "%sparams->in[%d].data.inPrice.open, /*", stateFuncSignature?"*":"", paramNb );
                  if( arrayToSubArrayCnvt )
				  {
                     fprintf( out, "              gcnew SubArrayFrom1D<%s>(inOpen,0)", inputDoubleArrayType );
				  }
				  else
				  {
                  fprintf( out, "%-*s%s%s%s",
                         prototype? 12 : 0,
                         prototype? inputDoubleArrayType : "",
                         outputForSWIG?"":" ",
                         outputForSWIG? "IN_ARRAY /* inOpen */": "inOpen",
                         (prototype && !stateFuncSignature && !stateStruct)? arrayBracket : "" );

				  }
                  fprintf( out, "%s\n",  stateStruct? ";": (frame? " */":",") );
               }

               if( inputParamInfo->flags & TA_IN_PRICE_HIGH )
               {
                  printIndent( out, indent );
                  if( frame )
                     fprintf( out, "%sparams->in[%d].data.inPrice.high, /*", stateFuncSignature?"*":"", paramNb );
                  if( arrayToSubArrayCnvt )
				  {
                     fprintf( out, "              gcnew SubArrayFrom1D<%s>(inHigh,0)", inputDoubleArrayType );
				  }
				  else
				  {
                     fprintf( out, "%-*s%s%s%s",
                         prototype? 12 : 0,
                         prototype? inputDoubleArrayType : "",
                         outputForSWIG?"":" ",
                         outputForSWIG? "IN_ARRAY /* inHigh */":"inHigh",
                         (prototype && !stateFuncSignature && !stateStruct)? arrayBracket : "" );
				  }
                  fprintf( out, "%s\n", stateStruct? ";": (frame? " */":",") );
               }

               if( inputParamInfo->flags & TA_IN_PRICE_LOW )
               {
                  printIndent( out, indent );
                  if( frame )
                     fprintf( out, "%sparams->in[%d].data.inPrice.low, /*", stateFuncSignature?"*":"", paramNb );
                  if( arrayToSubArrayCnvt )
				  {
					  fprintf( out, "              gcnew SubArrayFrom1D<%s>(inLow,0)", inputDoubleArrayType );
				  }
				  else
				  {
					  fprintf( out, "%-*s%s%s%s",
                         prototype? 12 : 0,
                         prototype? inputDoubleArrayType : "",
                         outputForSWIG?"":" ",
                         outputForSWIG? "IN_ARRAY /* inLow */": "inLow",
                         (prototype && !stateFuncSignature && !stateStruct)? arrayBracket : "" );
				  }

                  fprintf( out, "%s\n", stateStruct? ";": (frame? " */":",") );
               }

               if( inputParamInfo->flags & TA_IN_PRICE_CLOSE )
               {
                  printIndent( out, indent );
                  if( frame )
                     fprintf( out, "%sparams->in[%d].data.inPrice.close, /*", stateFuncSignature?"*":"", paramNb );
                  if( arrayToSubArrayCnvt )
				  {
					  fprintf( out, "              gcnew SubArrayFrom1D<%s>(inClose,0)", inputDoubleArrayType );
				  }
				  else
				  {
					  fprintf( out, "%-*s%s%s%s",
                         prototype? 12 : 0,
                         prototype? inputDoubleArrayType : "",
                         outputForSWIG?"":" ",
                         outputForSWIG? "IN_ARRAY /* inClose */": "inClose",
                         (prototype && !stateFuncSignature && !stateStruct)? arrayBracket : "" );
				  }

                  fprintf( out, "%s\n", stateStruct? ";": (frame? " */":",") );
               }

               if( inputParamInfo->flags & TA_IN_PRICE_VOLUME )
               {
                  printIndent( out, indent );
                  if( frame )
                     fprintf( out, "%sparams->in[%d].data.inPrice.volume, /*", stateFuncSignature?"*":"", paramNb );
                  if( arrayToSubArrayCnvt )
				  {
					  fprintf( out, "              gcnew SubArrayFrom1D<%s>(inVolume,0)", inputDoubleArrayType );
				  }
				  else
				  {
					  fprintf( out, "%-*s%s%s%s",
                         prototype? 12 : 0,
                         prototype? inputDoubleArrayType : "",
                         outputForSWIG?"":" ",
                         outputForSWIG? "IN_ARRAY /* inVolume */": "inVolume",
                         (prototype && !stateFuncSignature && !stateStruct)? arrayBracket : "" );
				  }

                  fprintf( out, "%s\n", stateStruct? ";": (frame? " */":",") );
               }

               if( inputParamInfo->flags & TA_IN_PRICE_OPENINTEREST )
               {
                  printIndent( out, indent );
                  if( frame )
                     fprintf( out, "%sparams->in[%d].data.inPrice.openInterest, /*", stateFuncSignature?"*":"", paramNb );
                  if( arrayToSubArrayCnvt )
				  {
					  fprintf( out, "              gcnew SubArrayFrom1D<%s>(inOpenInterest,0)", inputDoubleArrayType );
				  }
				  else
				  {
					  fprintf( out, "%-*s%s%s%s",
                         prototype? 12 : 0,
                         prototype? inputDoubleArrayType : "",
                         outputForSWIG?"":" ",
                         outputForSWIG? "IN_ARRAY /* inOpenInterest */": "inOpenInterest",
                         (prototype && !stateFuncSignature && !stateStruct)? arrayBracket : "" );
				  }

                  fprintf( out, "%s\n", stateStruct? ";": (frame? " */":",") );
               }
            }
            break;
         case TA_Input_Real:
            typeString = inputDoubleArrayType;
            defaultParamName = outputForSWIG? "IN_ARRAY":"inReal";
            if (stateFuncSignature && validationCode)
                nbInputArgsBufferLen = sprintf(((char *)nbInputArgsBuffer)+nbInputArgsBufferLen, "%s%s ", (nbInputArgsBufferLen)?",":"", inputParamInfo->paramName) + nbInputArgsBufferLen;
            break;
         case TA_Input_Integer:
            typeString = inputIntArrayType;
            defaultParamName = outputForSWIG? "IN_ARRAY":"inInteger";
            if (stateFuncSignature && validationCode)
                nbInputArgsBufferLen = sprintf(((char *)nbInputArgsBuffer)+nbInputArgsBufferLen, "%s%s ", (nbInputArgsBufferLen)?",":"", inputParamInfo->paramName) + nbInputArgsBufferLen;
            break;
         case TA_Input_Pointer: ;
         default:
            if( !paramName )
               paramName = "inParam";
            printf( "[%s,%s,%d] invalid 'input' type(%d)\n",
                    funcName, paramName, paramNb,
                    inputParamInfo->type );
            return;
         }

         if( inputParamInfo->type != TA_Input_Price)
         {
            printIndent( out, indent );
            if( validationCode )
            {
               if (!stateFuncSignature)
               fprintf( out, "if( !%s ) return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);\n", inputParamInfo->paramName );
            }
            else
            {
				
               if( frame )
                  fprintf( out, "%sparams->in[%d].data.%s, /*", stateFuncSignature?"*":"", paramNb, defaultParamName );
               if( outputForSWIG )
                  fprintf( out, "%-*s%s%s /* %s */",
                           prototype? 12 : 0,
                           prototype? typeString : "",
                           defaultParamName,
                           (prototype && !stateFuncSignature && !stateStruct)? arrayBracket : "",
                           inputParamInfo->paramName );
               else
			   {
				   if( arrayToSubArrayCnvt )
				   {
                      fprintf( out, "              %-*sgcnew SubArrayFrom1D<%s>(%s,0)",
                           prototype? 12 : 0, "",                          
						   typeString,
                           inputParamInfo->paramName );
				   }
				   else
				   {
                      fprintf( out, "%-*s %s%s",
                           prototype? 12 : 0,
                           prototype? typeString : "",
                           inputParamInfo->paramName,
                           (prototype && !stateFuncSignature && !stateStruct)? arrayBracket : "" );
				   }
			   }
               fprintf( out, "%s\n", stateStruct?";":(frame? " */":",") );
            }
         }
         paramNb++;
      }

      if( validationCode )
      {
         printIndent( out, indent );
         fprintf( out, "#endif /* !defined(_JAVA)*/\n" );
      }
   }

   if (stateFuncSignature && validationCode) {
       printIndent( out, indent );
       fprintf( out, "size_t _cur_idx = STATE.mem_index++;\n");
       printIndent( out, indent );
       fprintf( out, "if (MEM_SIZE > 0) _cur_idx %%= MEM_SIZE;\n");
       printIndent( out, indent );
       fprintf( out, "UNUSED_VARIABLE(_cur_idx); // in case PUSH\\POP methods won't be used\n");
       printIndent( out, indent );
       fprintf( out, "#ifndef TA_%s_SUPPRESS_EXIT_ON_NOT_ENOUGH_DATA\n", funcName );
       printIndent( out, indent );
       fprintf( out, "if (NEED_MORE_DATA) {\n");

       int word_idx = 0;
       char word[500];
       nbInputArgsBufferLen = 0;
       while (1)
       {
           char c = nbInputArgsBuffer[nbInputArgsBufferLen++];

           if ((c == ',') || ( c == '\0'))
           {
               word[word_idx] = '\0';
               if (word_idx > 0)
               {
                printIndent( out, indent+6 );
                fprintf( out, "PUSH_TO_MEM(%s,%s);\n", word, word);
               }
               word_idx = 0;
               if (c == '\0') break;
           } else
               if (c != ' ')
               word[word_idx++] = c;
       }

 //            PUSH_TO_MEM(x,x);
 //            PUSH_TO_MEM(y,y);
 //            PUSH_TO_MEM(z,z);
       printIndent( out, indent );
       fprintf( out, "return ENUM_VALUE(RetCode,TA_NEED_MORE_DATA,NeedMoreData); }\n");
       printIndent( out, indent );
       fprintf( out, "#endif\n");

   }

   if (stateStruct)
   {
       printIndent( out, indent );
       print( out, "};\n"); //close Data struct
       //start main struct
       PRINT_STRUCT_NAME("", funcName, "State {\n");
       printIndent( out, indent );
       print( out, "size_t mem_size;\n");
       printIndent( out, indent );
       print( out, "size_t mem_index;\n");
       printIndent( out, indent );
       print( out, "struct TA_%s_Data* memory;\n", funcName);
   }

   /* Go through all the additional State params. */
   if( stateStruct )
   {
      for( i=0; i < funcInfo->nbStructParams; i++ )
      {
         retCode = TA_GetStructParameterInfo( funcInfo->handle,
                                             i, &inputParamInfo );

         if( retCode != TA_SUCCESS )
         {
            printf( "[%s] invalid 'input' information (%d,%d)\n", funcName, i, paramNb );
            return;
         }

         switch( inputParamInfo->type )
         {
         case TA_Input_Real:
            typeString = inputDoubleArrayType;
            break;
         case TA_Input_Integer:
            typeString = "int";
            break;
         case TA_Input_Pointer:
            typeString = "void*";
            break;
         default:
            typeString = inputDoubleArrayType;
         }
         paramName = inputParamInfo->paramName;
         printIndent( out, indent );
         fprintf( out, "%-*s %s;\n",
              prototype? 12 : 0,
              prototype? typeString:"",
              inputParamInfo->paramName);
      }
   }




   /* Go through all the optional input */
   paramNb = 0;
   lastParam = 0;


   char nbOptInputArgsBuffer[1024]; /* Not safe, but 1024 is realistic, */
   nbOptInputArgsBuffer[0] = '\0';
   int nbOptInputArgsBufferLen = 0;

   if (!stateFreeSignature && !stateFuncSignature && !stateSaveSignature && !stateLoadSignature)
   for( i=0; i < funcInfo->nbOptInput; i++ )
   {
      excludeFromManaged = 0;

      if( (i == (funcInfo->nbOptInput-1)) && (lookbackSignature || stateInitSignature) )
         lastParam = 1;

      retCode = TA_GetOptInputParameterInfo( funcInfo->handle,
                                             i, &optInputParamInfo );

      if( retCode != TA_SUCCESS )
      {
         printf( "[%s] invalid 'optional input' information\n", funcName );
         return;
      }

      paramName = optInputParamInfo->paramName;

	  /* Boolean to detect special TA_MAType enumeration. */
	  if( optInputParamInfo->dataSet == TA_DEF_UI_MA_Method.dataSet )
	     isMAType = 1;
	  else
         isMAType = 0;

      switch( optInputParamInfo->type )
      {
      case TA_OptInput_RealRange:
      case TA_OptInput_RealList:
         typeString = "double";
         defaultParamName = outputForSWIG? "OPT_REAL":"optInReal";
         break;
      case TA_OptInput_IntegerRange:
         typeString = "int";
         defaultParamName = outputForSWIG? "OPT_INT":"optInInteger";
         break;
      case TA_OptInput_IntegerList:
         if( isMAType && !frame )
         {
            typeString = managedCPPCode||outputForJava? "MAType":"TA_MAType";
            defaultParamName = outputForSWIG? "OPT_MATYPE":"optInMAType";
            excludeFromManaged = 1;
         }
         else
         {
            typeString = "int";
            defaultParamName = outputForSWIG? "OPT_INT":"optInInteger";
         }
         break;
      default:
         if( !paramName )
            paramName = "optInParam";
         printf( "[%s,%s,%d] invalid 'optional input' type(%d)\n",
                 funcName, paramName, paramNb,
                 optInputParamInfo->type );         
         return;
      }

	  if( arrayToSubArrayCnvt )
	     typeString = "";

      if( !paramName )
         paramName = defaultParamName;
      
      if( validationCode )
      {
         if( excludeFromManaged )
         {
             printIndent( out, indent );
             fprintf( out, "#if !defined(_MANAGED) && !defined(_JAVA)\n" );
         }

         printOptInputValidation( out, paramName, optInputParamInfo, lookbackValidationCode );
         if (stateInitSignature)
             nbOptInputArgsBufferLen = sprintf(((char *)nbOptInputArgsBuffer)+nbOptInputArgsBufferLen, "%s%s ", paramName, lastParam?"":",") + nbOptInputArgsBufferLen;

         if( excludeFromManaged )
         {
             printIndent( out, indent );
             fprintf( out, "#endif /* !defined(_MANAGED) && !defined(_JAVA)*/\n" );
         }
      }
      else
      {
         if( !(lookbackSignature && (i == 0 )) )
            printIndent( out, indent );

         if( frame )
         {
            fprintf( out, "%sparams->optIn[%d].data.%s%s /*",
				     isMAType?"(TA_MAType)":"",
                     paramNb, defaultParamName,
                     (lookbackSignature || stateInitSignature)&&lastParam?"":"," );
         }
         if( outputForSWIG )
            fprintf( out, "%-*s %s /* %s */",
                     prototype? 13 : 0,
                     prototype? typeString : "",
                     defaultParamName, paramName );
         else
            fprintf( out, "%-*s %s",
                     prototype? 13 : 0,
                     prototype? typeString : "",
                     paramName );
                
         if( frame )
         {
            if( (lookbackSignature || stateInitSignature) && lastParam )
               fprintf( out, "*/ )%s\n", semiColonNeeded? ";":"" );
            else
               fprintf( out, "*/\n" );
         }
         else            
         {
            switch( optInputParamInfo->type )
            {
            case TA_OptInput_RealRange:
               if( (lookbackSignature || stateInitSignature) && lastParam )
                  fprintf( out, " )%s ", semiColonNeeded? ";":"" );
               else
                  fprintf( out, stateStruct?";":"," );

               if( ((TA_RealRange *)(optInputParamInfo->dataSet))->min == TA_REAL_MIN )
                  fprintf( out, " /* From TA_REAL_MIN" );
               else
                  fprintf( out, " /* From %.*g",
                         ((TA_RealRange *)(optInputParamInfo->dataSet))->precision,
                         ((TA_RealRange *)(optInputParamInfo->dataSet))->min );

               if( ((TA_RealRange *)(optInputParamInfo->dataSet))->max == TA_REAL_MAX )
                  fprintf( out, " to TA_REAL_MAX */\n" );
               else
               {
                  fprintf( out, " to %.*g%s */\n", 
                        ((TA_RealRange *)(optInputParamInfo->dataSet))->precision,
                        ((TA_RealRange *)(optInputParamInfo->dataSet))->max,
                        optInputParamInfo->flags & TA_OPTIN_IS_PERCENT? " %":"" );
               }
               break;
            case TA_OptInput_IntegerRange:
               if( (lookbackSignature || stateInitSignature) && lastParam )
                  fprintf( out, " )%s ", semiColonNeeded? ";":"" );
               else
                  fprintf( out, stateStruct?";":"," );

               if( ((TA_IntegerRange *)(optInputParamInfo->dataSet))->min == TA_INTEGER_MIN )
                  fprintf( out, " /* From TA_INTEGER_MIN" );
               else
               {
                  fprintf( out, " /* From %d",
                         ((TA_IntegerRange *)(optInputParamInfo->dataSet))->min );
               }

               if( ((TA_IntegerRange *)(optInputParamInfo->dataSet))->max == TA_INTEGER_MAX )
                  fprintf( out, " to TA_INTEGER_MAX */\n" );
               else
               {
                  fprintf( out, " to %d */\n", 
                         ((TA_IntegerRange *)(optInputParamInfo->dataSet))->max );
               }
               break;
            default:
               if( (lookbackSignature || stateInitSignature) && lastParam )
                  fprintf( out, " )%s ", semiColonNeeded? ";":"" );
               else
                  fprintf( out, stateStruct?";":"," );
            }
         }
      }

      paramNb++;
   }

   if (validationCode && stateInitSignature) {
       printIndent( out, indent);
       fprintf( out, "STATE = TA_Calloc(1, sizeof(struct TA_%s_State));\n", funcName);
       printIndent( out, indent);
       fprintf( out, "STATE_P.mem_index = 0;\n");

       int word_idx = 0;
       char word[500];
       nbOptInputArgsBufferLen = 0;
       while (1)
       {
           char c = nbOptInputArgsBuffer[nbOptInputArgsBufferLen++];

           if ((c == ',') || ( c == '\0'))
           {
               word[word_idx] = '\0';
               if (word_idx > 0)
               {
                printIndent( out, indent );
                fprintf( out, "STATE_P.%s = %s;\n", word, word);
               }
               word_idx = 0;
               if (c == '\0') break;
           } else
               if (c != ' ')
               word[word_idx++] = c;
       }

       printIndent( out, indent );
       fprintf( out, "MEM_SIZE_P = TA_%s_Lookback(%s);\n", funcName, nbOptInputArgsBuffer);
       printIndent( out, indent );
       fprintf( out, "#ifndef TA_%s_SUPPRESS_MEMORY_ALLOCATION\n", funcName);
       printIndent( out, indent);
       fprintf( out, "if (MEM_SIZE_P > 0)\n");
       printIndent( out, indent+6 );
       fprintf( out, "MEM_P = TA_Calloc(MEM_SIZE_P, sizeof(struct TA_%s_Data));\n", funcName);
       printIndent( out, indent );
       fprintf( out, "else\n");
       printIndent( out, indent );
       fprintf( out, "#endif\n");
       printIndent( out, indent+6 );
       fprintf( out, "MEM_P = NULL;");
   }

   if (!validationCode)
   {
   if( ((lookbackSignature || stateInitSignature) && (funcInfo->nbOptInput == 0)) || stateFreeSignature)
   {
      if( frame || outputForJava || stateInitSignature || stateFreeSignature)
         fprintf( out, " )%s\n", semiColonNeeded? ";":"" );
      else      
         fprintf( out, "void )%s\n", semiColonNeeded? ";":"" );
   } else if (stateSaveSignature || stateLoadSignature)
   {
       printIndent( out, indent );
       if( frame  )
           fprintf( out, " _file )%s\n", semiColonNeeded? ";":"" );
       else
          fprintf( out, "FILE* _file )%s\n", semiColonNeeded? ";":"" );
   }
   }

   if (stateStruct)
   {
       printIndent( out, indent );
       fprintf( out, "};\n");
//       PRINT_STRUCT_NAME(prefix, funcName, "Struct; // trigger declaration\n");
   }

   /* Go through all the output */
   if( lookbackSignature || stateInitSignature || stateFreeSignature || stateStruct || stateSaveSignature || stateLoadSignature )
   {
      if( !frame )
         print( out, "\n" );
   }
   else if( !lookbackValidationCode  )
   {
      paramNb = 0;
      lastParam = 0;

      if( !validationCode && !stateFuncSignature)
      {
            printIndent( out, indent );
            if( frame )
               fprintf( out, "%s, ", outBegIdxString );
            else
               fprintf( out, "%-*s %s%s",
                      prototype? 12 : 0,
                      prototype? outputIntParam : "",
                      prototype&&!managedCPPCode&&!outputForJava? "*" : "",
                      outBegIdxString );

            fprintf( out, "%s\n", frame? "":"," );

            printIndent( out, indent );
            if( frame )
               fprintf( out, "%s, ", outNbElementString );
            else
               fprintf( out, "%-*s %s%s",
                      prototype? 12 : 0,
                      prototype? outputIntParam : "",
                      prototype&&!managedCPPCode&&!outputForJava? "*" : "",
                      outNbElementString );
            fprintf( out, "%s\n", frame? "":"," );
      }

      if( validationCode )
      {
         printIndent( out, indent );         
         fprintf( out, "#if !defined(_JAVA)\n" );
      }

      for( i=0; i < funcInfo->nbOutput; i++ )
      {
         if( i == (funcInfo->nbOutput-1) )
            lastParam = 1;

         retCode = TA_GetOutputParameterInfo( funcInfo->handle,
                                              i, &outputParamInfo );

         if( retCode != TA_SUCCESS )
         {
            printf( "[%s] invalid 'output' information\n", funcName );
            return;
         }

         paramName = outputParamInfo->paramName;

         switch( outputParamInfo->type )
         {
         case TA_Output_Real:
            typeString = outputDoubleArrayType;
            defaultParamName = outputForSWIG? "OUT_ARRAY":"outReal";
            break;
         case TA_Output_Integer:
            typeString = outputIntArrayType;;
            defaultParamName = outputForSWIG? "OUT_ARRAY":"outInteger";
            break;
         default:
            if( !paramName )
               paramName = "outParam";
            printf( "[%s,%s,%d] invalid 'output' type(%d)\n",
                    funcName, paramName, paramNb,
                    outputParamInfo->type );
            return;
         }

         if( !paramName )
            paramName = defaultParamName;

         if( validationCode )
         {
            print( out, "   if( !%s )\n", paramName );
            print( out, "      return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);\n" );
            print( out, "\n" );
         }
         else
         {
            printIndent( out, indent );
            if( frame )
               fprintf( out, "%sparams->out[%d].data.%s%s /*", stateFuncSignature?"":"",
                      paramNb, defaultParamName,
                      lastParam? "":"," );

            if( outputForSWIG )
               fprintf( out, "%-*s %s*%s%s /* %s */",
                        prototype? 12 : 0,
                        prototype? typeString : "",                     
                        stateFuncSignature?"*":"",
                        defaultParamName,
                        (prototype && !stateFuncSignature && !stateStruct)? arrayBracket : "",
                        paramName );
            else if( arrayToSubArrayCnvt )            
			{
               fprintf( out, "                gcnew SubArrayFrom1D<%s>(%s,0)", typeString, paramName );
			}
			else
			{
               fprintf( out, "%-*s  %s%s%s",
                        prototype? 12 : 0,
                        prototype? typeString : "",
                        stateFuncSignature?"*":"",
                        paramName,
                        (prototype && !stateFuncSignature && !stateStruct)? arrayBracket : "" );
			}

            if( !lastParam )
               fprintf( out, "%s\n", frame? " */":"," );
            else
            {
               fprintf( out, "%s )%s\n",
                      frame? " */": stateTestSignature?",\nFILE* _file":"",
                      semiColonNeeded? ";":"" );
            }
         }

         paramNb++;
      }

      if( validationCode )
      {
         printIndent( out, indent );
         fprintf( out, "#endif /* !defined(_JAVA) */\n" );
      }

   }

}

void printCallFrame( FILE *out, const TA_FuncInfo *funcInfo )
{
   genPrefix = 1;

   printFrameHeader( out, funcInfo, 0 );
   print( out, "{\n" );
   printFunc( out, "   return ", funcInfo, pfs_frame | pfs_semiColonNeeded );
   print( out, "}\n" );

   printFrameHeader( out, funcInfo, pfs_lookbackSignature );
   print( out, "{\n" );
   if( funcInfo->nbOptInput == 0 )
      print( out, "   (void)params;\n" );
   printFunc( out, "   return ", funcInfo, pfs_frame | pfs_semiColonNeeded | pfs_lookbackSignature);
   print( out, "}\n" );

   printFrameHeader( out, funcInfo, pfs_stateInitSignature );
   print( out, "{\n" );
   if( funcInfo->nbOptInput == 0 )
      print( out, "   (void)params;\n" );
   printFunc( out, "   return ", funcInfo, pfs_frame | pfs_semiColonNeeded | pfs_stateInitSignature);
   print( out, "}\n" );

   printFrameHeader( out, funcInfo, pfs_stateFuncSignature );
   print( out, "{\n" );
   if( funcInfo->nbOptInput == 0 )
      print( out, "   (void)params;\n" );
   printFunc( out, "   return ", funcInfo, pfs_frame | pfs_semiColonNeeded | pfs_stateFuncSignature);
   print( out, "}\n" );

   printFrameHeader( out, funcInfo, pfs_stateFreeSignature );
   print( out, "{\n" );
   if( funcInfo->nbOptInput == 0 )
      print( out, "   (void)params;\n" );
   printFunc( out, "   return ", funcInfo, pfs_frame | pfs_semiColonNeeded | pfs_stateFreeSignature);
   print( out, "}\n" );

   printFrameHeader( out, funcInfo, pfs_stateSaveSignature );
   print( out, "{\n" );
   if( funcInfo->nbOptInput == 0 )
      print( out, "   (void)params;\n" );
   printFunc( out, "   return ", funcInfo, pfs_frame | pfs_semiColonNeeded | pfs_stateSaveSignature);
   print( out, "}\n" );

   printFrameHeader( out, funcInfo, pfs_stateLoadSignature );
   print( out, "{\n" );
   if( funcInfo->nbOptInput == 0 )
      print( out, "   (void)params;\n" );
   printFunc( out, "   return ", funcInfo, pfs_frame | pfs_semiColonNeeded | pfs_stateLoadSignature);
   print( out, "}\n" );
   
   genPrefix = 0;
}


void printFrameHeader( FILE *out, const TA_FuncInfo *funcInfo, unsigned int settings )
{
   if( settings & pfs_lookbackSignature )
   {
      print( out, "unsigned int TA_%s_FramePPLB( const TA_ParamHolderPriv *params )\n", funcInfo->name );
   }
   else
   if( settings & pfs_stateInitSignature )
   {
      print( out, "unsigned int TA_%s_FramePPSI( const TA_ParamHolderPriv *params )\n", funcInfo->name );
   }
   else
   if( settings & pfs_stateFuncSignature )
   {
      print( out, "unsigned int TA_%s_FramePPS( const TA_ParamHolderPriv *params )\n", funcInfo->name );
   }
   else
   if( settings & pfs_stateFreeSignature )
   {
      print( out, "unsigned int TA_%s_FramePPSF( const TA_ParamHolderPriv *params )\n", funcInfo->name );
   }
   else
   if( settings & pfs_stateSaveSignature )
   {
      print( out, "unsigned int TA_%s_FramePPSS( const TA_ParamHolderPriv *params, FILE* _file )\n", funcInfo->name );
   }
   else
   if( settings & pfs_stateLoadSignature )
   {
      print( out, "unsigned int TA_%s_FramePPSL( const TA_ParamHolderPriv *params, FILE* _file )\n", funcInfo->name );
   }
   else
   {
      print( out, "TA_RetCode TA_%s_FramePP( const TA_ParamHolderPriv *params,\n", funcInfo->name );
      print( out, "                          int            startIdx,\n" );
      print( out, "                          int            endIdx,\n" );
      print( out, "                          int           *outBegIdx,\n" );
      print( out, "                          int           *outNBElement )\n" );
   }
}

void printExternReferenceForEachFunction( const TA_FuncInfo *info,
                                                 void *opaqueData )
{
   (void)opaqueData; /* Get ride of compiler warning */

   fprintf( gOutGroupIdx_C->file, "extern const TA_FuncDef TA_DEF_%s;\n", info->name );
}

void printPerGroupList( const char *groupName,
                               unsigned int index,
                               unsigned int isFirst,
                               unsigned int isLast
                             )
{
   (void)isLast; /* Get ride of compiler warning. */
   (void)isFirst; /* Get ride of compiler warning. */

   fprintf( gOutGroupIdx_C->file,
           "\nconst TA_FuncDef *TA_PerGroupFunc_%d[] = {\n", index );

   gCurrentGroupName = groupName;
   TA_ForEachFunc( printFunctionAddress, NULL );
   fprintf( gOutGroupIdx_C->file, "NULL };\n" );

   fprintf( gOutGroupIdx_C->file,
      "#define SIZE_GROUP_%d ((sizeof(TA_PerGroupFunc_%d)/sizeof(const TA_FuncDef *))-1)\n",
      index, index );
}

void printFunctionAddress( const TA_FuncInfo *info,
                                  void *opaqueData )
{
   (void)opaqueData; /* Get ride of compiler warning. */

   if( strcmp( info->group, gCurrentGroupName ) == 0 )
      fprintf( gOutGroupIdx_C->file, "&TA_DEF_%s,\n", info->name );
}

void printGroupListAddress( const char *groupName,
                                   unsigned int index,
                                   unsigned int isFirst,
                                   unsigned int isLast
                                  )
{
   (void)isFirst;   /* Get ride of compiler warning. */

   if( groupName == NULL )
      fprintf( gOutGroupIdx_C->file, "NULL%s", isLast? "" : "," );
   else fprintf( gOutGroupIdx_C->file, "&TA_PerGroupFunc_%d[0]%s\n",
                 index, isLast? "" : "," );
}

void printGroupSize( const char *groupName,
                            unsigned int index,
                            unsigned int isFirst,
                            unsigned int isLast
                           )
{
   (void)isFirst;   /* Get ride of compiler warning. */
   (void)groupName; /* Get ride of compiler warning. */

   fprintf( gOutGroupIdx_C->file, "SIZE_GROUP_%d%s\n",
            index, isLast? "" : "," );
}

void printGroupSizeAddition( const char *groupName,
                                    unsigned int index,
                                    unsigned int isFirst,
                                    unsigned int isLast
                                   )
{
   (void)isFirst;   /* Get ride of compiler warning. */
   (void)groupName; /* Get ride of compiler warning. */

   fprintf( gOutGroupIdx_C->file, "SIZE_GROUP_%d%s",
            index, isLast? ";" : "+\n" );
}

void doFuncFile( const TA_FuncInfo *funcInfo )
{

   FileHandle *tempFile1;
   
   unsigned int useTempFile;
   FILE *logicIn;
   FILE *logicTmp;
   char localBuf1[500];

   #define TEMPLATE_PASS1   ".." TA_FS_SLASH "temp" TA_FS_SLASH "pass1.tmp"
   #define TEMPLATE_PASS2   ".." TA_FS_SLASH "temp" TA_FS_SLASH "pass2.tmp"
   #define TEMPLATE_DEFAULT ".." TA_FS_SLASH "src" TA_FS_SLASH "ta_abstract" TA_FS_SLASH "templates" TA_FS_SLASH "ta_x.c.template"
   #define LOGIC_TEMP       ".." TA_FS_SLASH "temp" TA_FS_SLASH "logic.tmp"

   /* Check if the file already exist. */
   sprintf( localBuf1, ".." TA_FS_SLASH "src" TA_FS_SLASH "ta_func" TA_FS_SLASH "ta_%s.c", funcInfo->name );

   gOutFunc_C = fileOpen( localBuf1, NULL, FILE_READ);
   if( gOutFunc_C == NULL )
      useTempFile = 0;
   else
   {
      useTempFile = 1;
      /* Create a temporary template using it. */
      tempFile1 = fileOpen( TEMPLATE_PASS1, NULL, FILE_WRITE|WRITE_ALWAYS );
      if( tempFile1 == NULL )
      {
         printf( "Cannot create temporary file!\n" );
         return;
      }

      createTemplate( gOutFunc_C, tempFile1 );

      fileClose( tempFile1 );
      fileClose( gOutFunc_C );
   }

   /* Open the file using the template. */
   if( useTempFile )
      gOutFunc_C = fileOpen( TEMPLATE_PASS2, TEMPLATE_PASS1, FILE_WRITE|WRITE_ALWAYS );
   else
      gOutFunc_C = fileOpen( TEMPLATE_PASS2, TEMPLATE_DEFAULT, FILE_WRITE|WRITE_ALWAYS );

   if( gOutFunc_C == NULL )
   {
      printf( "Cannot create [%s]\n", localBuf1 );
      return;
   }

   /* Generate. 1st Pass */
   writeFuncFile( funcInfo );

   fileClose( gOutFunc_C );

   if( !useTempFile )
   {
      /* When the file is new, the first pass becomes the 
       * original.
       */
      if( !copyFile( TEMPLATE_PASS2, localBuf1 ) )
      {
         printf( "Cannot copy %s to %s\n", TEMPLATE_PASS2, localBuf1 );
         return;
      }
   }

   /* Extract the TA function code in a temporary file */
   init_gToOpen( localBuf1, NULL );
   logicIn = fopen( gToOpen, "r" );   
   if( !logicIn )
   {
      printf( "Cannot open [%s] for extracting TA logic\n", localBuf1 );
      return;
   }
   init_gToOpen( LOGIC_TEMP, NULL );
   logicTmp = fopen( gToOpen, "w" );
   if( !logicTmp )
   {
      fclose(logicIn);
      printf( "Cannot open logic.tmp\n" );
      return;
   }
   extractTALogic( logicIn, logicTmp );
   fclose(logicIn);
   fclose(logicTmp);

   /* Insert the TA function code in the single-precision frame 
    * using the template generated from the first pass.
    */
   gOutFunc_C = fileOpen( localBuf1, TEMPLATE_PASS2, FILE_WRITE|WRITE_ON_CHANGE_ONLY );
   if( gOutFunc_C == NULL )
   {
      printf( "Cannot complete 2nd pass with [%s]\n", localBuf1 );
      return;
   }

   /* Duplicate the function, but using float this time */
   print( gOutFunc_C->file, "\n" );
   print( gOutFunc_C->file, "#define  USE_SINGLE_PRECISION_INPUT\n" );
   print( gOutFunc_C->file, "#undef  TA_LIB_PRO\n" );
   print( gOutFunc_C->file, "#if !defined( _MANAGED ) && !defined( _JAVA )\n" );
   print( gOutFunc_C->file, "   #undef   TA_PREFIX\n" );
   print( gOutFunc_C->file, "   #define  TA_PREFIX(x) TA_S_##x\n" );
   print( gOutFunc_C->file, "#endif\n" );
   print( gOutFunc_C->file, "#undef   INPUT_TYPE\n" );
   print( gOutFunc_C->file, "#define  INPUT_TYPE float\n" );

   print( gOutFunc_C->file, "#if defined( _MANAGED ) && defined( USE_SUBARRAY )\n" );   
   printFunc( gOutFunc_C->file, NULL, funcInfo, pfs_prototype | pfs_managedCPPCode | pfs_inputIsSinglePrecision | pfs_useSubArrayObject);
   print( gOutFunc_C->file, "#elif defined( _MANAGED )\n" );
   printFunc( gOutFunc_C->file, NULL, funcInfo, pfs_prototype | pfs_managedCPPCode | pfs_inputIsSinglePrecision );
   print( gOutFunc_C->file, "#elif defined( _JAVA )\n" );
   printFunc( gOutFunc_C->file, NULL, funcInfo, pfs_prototype | pfs_inputIsSinglePrecision | pfs_outputForJava );
   print( gOutFunc_C->file, "#else\n" );
   printFunc( gOutFunc_C->file, NULL, funcInfo,  pfs_prototype | pfs_inputIsSinglePrecision );
   print( gOutFunc_C->file, "#endif\n" );

   /* Insert the internal logic of the function */
   init_gToOpen( LOGIC_TEMP, NULL );
   logicTmp = fopen( gToOpen, "r" );
   if( !logicTmp )
   {
      fileClose( gOutFunc_C );
      printf( "Cannot read open logic.tmp\n" );
      return;
   }
   while( fgets(gTempBuf,BUFFER_SIZE,logicTmp) )
      fputs( gTempBuf, gOutFunc_C->file );
   fclose(logicTmp);
   print( gOutFunc_C->file, "\n" );

   /* Add the suffix at the end of the file. */
   print( gOutFunc_C->file, "#if defined( _MANAGED )\n" );
   print( gOutFunc_C->file, "}}} // Close namespace TicTacTec.TA.Lib\n" );
   print( gOutFunc_C->file, "#endif\n" );

   fileClose( gOutFunc_C );
   fileDelete( LOGIC_TEMP );
   fileDelete( TEMPLATE_PASS1 );
   fileDelete( TEMPLATE_PASS2 );
}

void doDefsFile( void )
{

   FileHandle *tempFile;
   FILE *out;
   
   #define FILE_TA_DEFS_H    ".." TA_FS_SLASH "include" TA_FS_SLASH "ta_defs.h"
   #define FILE_TA_DEFS_TMP  ".." TA_FS_SLASH "temp" TA_FS_SLASH "ta_defs.tmp"

   /* Check if the file already exist. If not, this is an error. */
   gOutDefs_H = fileOpen( FILE_TA_DEFS_H, NULL, FILE_READ );
   if( gOutDefs_H == NULL )
   {
      printf( "ta_defs.h must exist for being updated!\n" );
      exit(-1);
   }

   /* Create the template. The template is just the original file content
    * with the GENCODE SECTION emptied (so they can be re-generated)
    */
   tempFile = fileOpen( FILE_TA_DEFS_TMP, NULL, FILE_WRITE|WRITE_ALWAYS );
   if( tempFile == NULL )
   {
      printf( "Cannot create temporary file!\n" );
      exit(-1);
   }

   createTemplate( gOutDefs_H, tempFile );

   fileClose( tempFile );
   fileClose( gOutDefs_H );

   /* Re-open the file using the template. */
   gOutDefs_H = fileOpen( FILE_TA_DEFS_H, FILE_TA_DEFS_TMP, FILE_WRITE|WRITE_ON_CHANGE_ONLY );
                                                    
   if( gOutDefs_H == NULL )
   {
      printf( "Cannot create ta_defs.h\n" );
      exit(-1);
   }

   /* Generate the GENCODE SECTION */
   out = gOutDefs_H->file;
   
   genPrefix = 1;
   addUnstablePeriodEnum( out );
   print( out, "\n" );
   genPrefix = 0;

   fileClose( gOutDefs_H );
   fileDelete( FILE_TA_DEFS_TMP );
   #undef FILE_TA_DEFS_H
   #undef FILE_TA_DEFS_TMP
}

#ifdef _MSC_VER
int createProjTemplate( FileHandle *in, FileHandle *out )
{
   FILE *inFile;
   FILE *outFile;
   unsigned int skipSection;
   unsigned int sectionDone;
   unsigned int step;

   inFile = in->file;
   outFile = out->file;

   skipSection = 0;
   sectionDone = 0;
   step        = 0;

   while( fgets( gTempBuf, BUFFER_SIZE, inFile ) )
   {
      if( !skipSection )
      {
         fputs( gTempBuf, outFile );
         if( !strstr( gTempBuf, "<Filter" ) )
            continue;

         if( !fgets( gTempBuf2, BUFFER_SIZE, inFile ) )
         {
            printf( "Unexpected end-of-file\n" );
            return -1;
         }
         fputs( gTempBuf2, outFile );

         if( !strstr( gTempBuf2, "Name=\"ta_func\"" ) )
            continue;            

         if( !fgets( gTempBuf3, BUFFER_SIZE, inFile ) )
         {
            printf( "Unexpected end-of-file\n" );
            return -1;
         }

         fputs( gTempBuf3, outFile );

         if( !strstr( gTempBuf3, ">" ) )
            continue;            

         skipSection = 1;
         fputs( "%%%GENCODE%%%\n", outFile );
      }
      else if( strstr( gTempBuf, "</Filter>" ) )
      {
         skipSection = 0;
         fputs( gTempBuf, outFile );
         sectionDone++;
      }
   }

   return 0;
}

int createMSVCProjTemplate( FileHandle *in, FileHandle *out )
{
   FILE *inFile;
   FILE *outFile;
   unsigned int skipSection;

   inFile = in->file;
   outFile = out->file;

   skipSection = 0;

   while( !skipSection && fgets( gTempBuf, BUFFER_SIZE, inFile ) )
   {
      if( strstr( gTempBuf, "# Begin Source File") )
         skipSection = 1;
      else
         fputs( gTempBuf, outFile );
   }

   if( !skipSection )
   {
      printf( "Unexpected end-of-file\n" );
      return -1;
   }

   fputs( "%%%GENCODE%%%\n", outFile );

   while( fgets( gTempBuf, BUFFER_SIZE, inFile ) )
   {
      if( strstr( gTempBuf, "# End Group" ) )
      {
         /* Add the "non TA function" source files. */
         fprintf( outFile, "# Begin Source File\n");
         fprintf( outFile, "\n");
         fprintf( outFile, "SOURCE=.." TA_FS_SLASH ".." TA_FS_SLASH ".." TA_FS_SLASH ".." TA_FS_SLASH "src" TA_FS_SLASH "ta_func" TA_FS_SLASH "ta_utility.c\n");
         fprintf( outFile, "# End Source File\n");
         fprintf( outFile, "# End Group\n");
         break;
      }
   }

   while( fgets( gTempBuf, BUFFER_SIZE, inFile ) )
      fputs( gTempBuf, outFile );

   return 0;
}

#ifdef TA_LIB_PRO
      /* Section for code distributed with TA-Lib Pro only. */
#endif


int createVS2005ProjTemplate( FileHandle *in, FileHandle *out )
{
   // This function works also for VS2008
   FILE *inFile;
   FILE *outFile;
   unsigned int skipSection;

   inFile = in->file;
   outFile = out->file;

   skipSection = 0;

   while( !skipSection && fgets( gTempBuf, BUFFER_SIZE, inFile ) )
   {
      if( strstr( gTempBuf, "<Files>") )
         skipSection = 1;
      else
         fputs( gTempBuf, outFile );
   }

   if( !skipSection )
   {
      printf( "Unexpected end-of-file. Missing \"<Files>\"\n" );
      return -1;
   }


   fputs( gTempBuf, outFile );

   skipSection = 0;

   while( !skipSection && fgets( gTempBuf, BUFFER_SIZE, inFile ) )
   {
      if( strstr( gTempBuf, "<File") )
         skipSection = 1;
      else
         fputs( gTempBuf, outFile );
   }

   if( !skipSection )
   {
      printf( "Unexpected end-of-file. Missing \"<File\"\n" );
      return -1;
   }

   fputs( "%%%GENCODE%%%\n", outFile );

   while( fgets( gTempBuf, BUFFER_SIZE, inFile ) )
   {
      if( strstr( gTempBuf, "</Filter>" ) )
      {
         /* Add the "non TA function" source files. */
	     printVS2005FileNode( outFile, "utility" );
         fprintf( outFile, "			</Filter>\n");
         break;
      }
   }

   while( fgets( gTempBuf, BUFFER_SIZE, inFile ) )
      fputs( gTempBuf, outFile );

   return 0;
}

void printVS2005FileNode( FILE *out, const char *name )
{
   // This function works also for VS2008
   fprintf( out, "				<File\n" );
   fprintf( out, "					RelativePath=\".." TA_FS_SLASH ".." TA_FS_SLASH ".." TA_FS_SLASH ".." TA_FS_SLASH "src" TA_FS_SLASH "ta_func" TA_FS_SLASH "ta_%s.c\"\n", name );
   fprintf( out, "					>\n" );
/*
   fprintf( out, "					<FileConfiguration\n" );
   fprintf( out, "						Name=\"cdd|Win32\"\n" );
   fprintf( out, "						>\n" );
   fprintf( out, "						<Tool\n" );
   fprintf( out, "							Name=\"VCCLCompilerTool\"\n" );
   fprintf( out, "							AdditionalIncludeDirectories=\"\"\n" );
   fprintf( out, "							PreprocessorDefinitions=\"\"\n" );
   fprintf( out, "						/>\n" );
   fprintf( out, "					</FileConfiguration>\n" );
   fprintf( out, "					<FileConfiguration\n" );
   fprintf( out, "						Name=\"cdr|Win32\"\n" );
   fprintf( out, "						>\n" );
   fprintf( out, "						<Tool\n" );
   fprintf( out, "							Name=\"VCCLCompilerTool\"\n" );
   fprintf( out, "							AdditionalIncludeDirectories=\"\"\n" );
   fprintf( out, "							PreprocessorDefinitions=\"\"\n" );
   fprintf( out, "						/>\n" );
   fprintf( out, "					</FileConfiguration>\n" );
   fprintf( out, "					<FileConfiguration\n" );
   fprintf( out, "						Name=\"cmr|Win32\"\n" );
   fprintf( out, "						>\n" );
   fprintf( out, "						<Tool\n" );
   fprintf( out, "							Name=\"VCCLCompilerTool\"\n" );
   fprintf( out, "							AdditionalIncludeDirectories=\"\"\n" );
   fprintf( out, "							PreprocessorDefinitions=\"\"\n" );
   fprintf( out, "						/>\n" );
   fprintf( out, "					</FileConfiguration>\n" );
   fprintf( out, "					<FileConfiguration\n" );
   fprintf( out, "						Name=\"cmd|Win32\"\n" );
   fprintf( out, "						>\n" );
   fprintf( out, "						<Tool\n" );
   fprintf( out, "							Name=\"VCCLCompilerTool\"\n" );
   fprintf( out, "							AdditionalIncludeDirectories=\"\"\n" );
   fprintf( out, "							PreprocessorDefinitions=\"\"\n" );
   fprintf( out, "						/>\n" );
   fprintf( out, "					</FileConfiguration>\n" );
   fprintf( out, "					<FileConfiguration\n" );
   fprintf( out, "						Name=\"csr|Win32\"\n" );
   fprintf( out, "						>\n" );
   fprintf( out, "						<Tool\n" );
   fprintf( out, "							Name=\"VCCLCompilerTool\"\n" );
   fprintf( out, "							AdditionalIncludeDirectories=\"\"\n" );
   fprintf( out, "							PreprocessorDefinitions=\"\"\n" );
   fprintf( out, "						/>\n" );
   fprintf( out, "					</FileConfiguration>\n" );
   fprintf( out, "					<FileConfiguration\n" );
   fprintf( out, "						Name=\"csd|Win32\"\n" );
   fprintf( out, "						>\n" );
   fprintf( out, "						<Tool\n" );
   fprintf( out, "							Name=\"VCCLCompilerTool\"\n" );
   fprintf( out, "							AdditionalIncludeDirectories=\"\"\n" );
   fprintf( out, "							PreprocessorDefinitions=\"\"\n" );
   fprintf( out, "						/>\n" );
   fprintf( out, "					</FileConfiguration>\n" );
*/
   fprintf( out, "				</File>\n" );
}
#endif

int createTemplate( FileHandle *in, FileHandle *out )
{
   FILE *inFile;
   FILE *outFile;
   char *inTheLinePtr;
   unsigned int skipSection;
   unsigned int sectionDone;

   inFile = in->file;
   outFile = out->file;

   skipSection = 0;
   sectionDone = 0;
   while( fgets( gTempBuf, BUFFER_SIZE, inFile ) )
   {
      inTheLinePtr = gTempBuf;
      /* Skip leading whitespace. */
      while( isspace(*inTheLinePtr) ) inTheLinePtr++;

      if( strncmp( inTheLinePtr, "/**** START GENCODE SECTION", 27 ) == 0 )
      {
         skipSection = 1;
         fputs( gTempBuf, outFile );
         fputs( "%%%GENCODE%%%\n", outFile );
      }

      else if( strncmp( inTheLinePtr, "/**** END GENCODE SECTION", 25 ) == 0 )
      {
         if( skipSection )
         {
            skipSection = 0;
            sectionDone++;
         }
      }

      if( !skipSection )
      {
         if( fputs( gTempBuf, outFile ) == EOF )
         {
            printf( "Cannot write tmp file\n" );
            return -1;
         }
      }
   }

   return 0;
}

void writeFuncFile( const TA_FuncInfo *funcInfo )
{
   FILE *out;

   out = gOutFunc_C->file;
   fprintf( out, "/* All code within this section is automatically\n" );
   fprintf( out, " * generated by gen_code. Any modification will be lost\n" );
   fprintf( out, " * next time gen_code is run.\n" );
   fprintf( out, " */\n" );

   // section 1 begin
   genPrefix = 1;
   print( out, "\n" );
   print( out, "#if defined( _MANAGED )\n" );
   print( out, "   #include \"TA-Lib-Core.h\"\n" );
   print( out, "   #define TA_INTERNAL_ERROR(Id) (RetCode::InternalError)\n" );
   print( out, "   namespace TicTacTec { namespace TA { namespace Library {\n" );
   print( out, "#elif defined( _JAVA )\n" );
   print( out, "   #include \"ta_defs.h\"\n" );
   print( out, "   #include \"ta_java_defs.h\"\n" );
   print( out, "   #define TA_INTERNAL_ERROR(Id) (RetCode.InternalError)\n" );
   print( out, "#else\n" );
   print( out, "   #include <string.h>\n" );
   print( out, "   #include <math.h>\n" );
   print( out, "   #include \"ta_func.h\"\n" );   
   print( out, "#endif\n" );
   print( out, "\n" );
   print( out, "#ifndef TA_UTILITY_H\n" );
   print( out, "   #include \"ta_utility.h\"\n" );
   print( out, "#endif\n" );
   print( out, "\n" );
   print( out, "#ifndef TA_MEMORY_H\n" );
   print( out, "   #include \"ta_memory.h\"\n" );
   print( out, "#endif\n" );
   print( out, "\n" );
   print( out, "#define TA_PREFIX(x) TA_##x\n" );
   print( out, "#define INPUT_TYPE   double\n" );
   print( out, "\n" );
   print( out, "#if defined( _MANAGED )\n" );
   printFunc( out, NULL, funcInfo,  pfs_prototype | pfs_lookbackSignature | pfs_managedCPPCode);
   print( out, "#elif defined( _JAVA )\n" );
   printFunc( out, NULL, funcInfo, pfs_prototype | pfs_lookbackSignature | pfs_outputForJava);
   print( out, "#else\n" );
   printFunc( out, "TA_LIB_API ", funcInfo, pfs_prototype | pfs_lookbackSignature );
   print( out, "#endif\n" );
   //section 1 end

   genPrefix = 0;
   skipToGenCode( funcInfo->name, gOutFunc_C->file, gOutFunc_C->templateFile );

   //section 2 begin
   genPrefix = 1;
   if( funcInfo->nbOptInput != 0 )
      print( out, "#ifndef TA_FUNC_NO_RANGE_CHECK\n" );
   printFunc( out, NULL, funcInfo, pfs_validationCode | pfs_lookbackValidationCode );
   if( funcInfo->nbOptInput != 0 )     
     print( out, "#endif /* TA_FUNC_NO_RANGE_CHECK */\n" );
   else   
     print( out, "/* No parameters to validate. */\n" ); 
   //section 2 end

   genPrefix = 0;
   skipToGenCode( funcInfo->name, gOutFunc_C->file, gOutFunc_C->templateFile );

   // section 3 begin
   genPrefix = 1;
   fprintf( out, "/*\n" );
   printFuncHeaderDoc( out, funcInfo, " * " );
   fprintf( out, " */\n" );
   print( out, "\n" );
   print( out, "#if defined( _MANAGED ) && defined( USE_SUBARRAY )\n" );   
   printFunc( out, NULL, funcInfo, pfs_prototype | pfs_managedCPPCode | pfs_useSubArrayObject );
   print( out, "#elif defined( _MANAGED )\n" );
   printFunc( out, NULL, funcInfo, pfs_prototype | pfs_managedCPPCode );
   print( out, "#elif defined( _JAVA )\n" );

   /* Handle special case to avoid duplicate definition of min,max */
   if( strcmp( funcInfo->camelCaseName, "Min" ) == 0 ) {
      print( out, "#undef min\n" );
   } else if( strcmp( funcInfo->camelCaseName, "Max" ) == 0 ) {
      print( out, "#undef max\n" );
   }

   printFunc( out, NULL, funcInfo, pfs_prototype | pfs_outputForJava );
   print( out, "#else\n" );
   printFunc( out, "TA_LIB_API ", funcInfo, pfs_prototype );
   print( out, "#endif\n" );
   //section 3 end

   genPrefix = 0;
   skipToGenCode( funcInfo->name, gOutFunc_C->file, gOutFunc_C->templateFile );

   //section 4 begin
   genPrefix = 1;
   print( out, "\n" );
   print( out, "#ifndef TA_FUNC_NO_RANGE_CHECK\n" );
   print( out, "\n" );
   print( out, "   /* Validate the requested output range. */\n" );
   print( out, "   if( startIdx < 0 )\n" );
   print( out, "      return ENUM_VALUE(RetCode,TA_OUT_OF_RANGE_START_INDEX,OutOfRangeStartIndex);\n" );
   print( out, "   if( (endIdx < 0) || (endIdx < startIdx))\n" );
   print( out, "      return ENUM_VALUE(RetCode,TA_OUT_OF_RANGE_END_INDEX,OutOfRangeEndIndex);\n" );
   print( out, "\n" );
   /* Generate the code for checking the parameters.
    * Also generates the code for setting up the
    * default values.
    */
   printFunc( out, NULL, funcInfo, pfs_validationCode );

   print( out, "#endif /* TA_FUNC_NO_RANGE_CHECK */\n" );
   print( out, "\n" );
   //section 4 end

   genPrefix = 0;
   skipToGenCode( funcInfo->name, gOutFunc_C->file, gOutFunc_C->templateFile );

   // section 5 begin
   genPrefix = 1;
   print( out, "\n" );
   print( out, "#if defined( _MANAGED )\n" );
   printFunc( out, NULL, funcInfo, pfs_prototype | pfs_stateInitSignature | pfs_managedCPPCode );
   print( out, "#elif defined( _JAVA )\n" );
   /* Handle special case to avoid duplicate definition of min,max */
   if( strcmp( funcInfo->camelCaseName, "Min" ) == 0 ) {
      print( out, "#undef min\n" );
   } else if( strcmp( funcInfo->camelCaseName, "Max" ) == 0 ) {
      print( out, "#undef max\n" );
   }
   printFunc( out, NULL, funcInfo, pfs_prototype | pfs_stateInitSignature | pfs_outputForJava );
   print( out, "#else\n" );
   printFunc( out, "TA_LIB_API ", funcInfo, pfs_prototype | pfs_stateInitSignature );
   print( out, "#endif\n" );
   //section 5 end

   genPrefix = 0;
   skipToGenCode( funcInfo->name, gOutFunc_C->file, gOutFunc_C->templateFile );

   //section 6 begin
   genPrefix = 1;
   print( out, "\n" );
   print( out, "#ifndef TA_FUNC_NO_RANGE_CHECK\n" );
   print( out, "\n" );
   /* Generate the code for checking the parameters.
    * Also generates the code for setting up the
    * default values.
    */
   printFunc( out, NULL, funcInfo, pfs_stateInitSignature | pfs_validationCode );
   print( out, "#endif /* TA_FUNC_NO_RANGE_CHECK */\n" );
   print( out, "\n" );
   //section 6 end

   genPrefix = 0;
   skipToGenCode( funcInfo->name, gOutFunc_C->file, gOutFunc_C->templateFile );

   // section 7 begin
   genPrefix = 1;
   print( out, "\n" );
   print( out, "#if defined( _MANAGED )\n" );
   printFunc( out, NULL, funcInfo, pfs_prototype | pfs_stateFuncSignature | pfs_managedCPPCode );
   print( out, "#elif defined( _JAVA )\n" );
   /* Handle special case to avoid duplicate definition of min,max */
   if( strcmp( funcInfo->camelCaseName, "Min" ) == 0 ) {
      print( out, "#undef min\n" );
   } else if( strcmp( funcInfo->camelCaseName, "Max" ) == 0 ) {
      print( out, "#undef max\n" );
   }
   printFunc( out, NULL, funcInfo, pfs_prototype | pfs_stateFuncSignature | pfs_outputForJava );
   print( out, "#else\n" );
   printFunc( out, "TA_LIB_API ", funcInfo, pfs_prototype | pfs_stateFuncSignature );
   print( out, "#endif\n" );
   //section 7 end

   genPrefix = 0;
   skipToGenCode( funcInfo->name, gOutFunc_C->file, gOutFunc_C->templateFile );

   //section 8 begin
   genPrefix = 1;
   print( out, "\n" );
   print( out, "#ifndef TA_FUNC_NO_RANGE_CHECK\n" );
   print( out, "\n" );
   /* Generate the code for checking the parameters.
    * Also generates the code for setting up the
    * default values.
    */
   printFunc( out, NULL, funcInfo, pfs_stateFuncSignature | pfs_validationCode );
   print( out, "#endif /* TA_FUNC_NO_RANGE_CHECK */\n" );
   print( out, "\n");
   //section 8 end

   genPrefix = 0;
   skipToGenCode( funcInfo->name, gOutFunc_C->file, gOutFunc_C->templateFile );

   // section 9 begin
   genPrefix = 1;
   print( out, "\n" );
   print( out, "#if defined( _MANAGED )\n" );
   printFunc( out, NULL, funcInfo, pfs_prototype | pfs_stateFreeSignature | pfs_managedCPPCode );
   print( out, "#elif defined( _JAVA )\n" );
   /* Handle special case to avoid duplicate definition of min,max */
   if( strcmp( funcInfo->camelCaseName, "Min" ) == 0 ) {
      print( out, "#undef min\n" );
   } else if( strcmp( funcInfo->camelCaseName, "Max" ) == 0 ) {
      print( out, "#undef max\n" );
   }
   printFunc( out, NULL, funcInfo, pfs_prototype | pfs_stateFreeSignature | pfs_outputForJava );
   print( out, "#else\n" );
   printFunc( out, "TA_LIB_API ", funcInfo, pfs_prototype | pfs_stateFreeSignature );
   print( out, "#endif\n" );
   //section 9 end

   genPrefix = 0;
   skipToGenCode( funcInfo->name, gOutFunc_C->file, gOutFunc_C->templateFile );

   //section 10 begin
   genPrefix = 1;
   print( out, "\n" );
   print( out, "#ifndef TA_FUNC_NO_RANGE_CHECK\n" );
   print( out, "\n" );
   /* Generate the code for checking the parameters.
    * Also generates the code for setting up the
    * default values.
    */
   printFunc( out, NULL, funcInfo, pfs_stateFreeSignature | pfs_validationCode );
   print( out, "#endif /* TA_FUNC_NO_RANGE_CHECK */\n" );
   print( out, "\n" );
   //section 10 end


   genPrefix = 0;
   skipToGenCode( funcInfo->name, gOutFunc_C->file, gOutFunc_C->templateFile );

   // section 11 begin
   genPrefix = 1;
   print( out, "\n" );
   print( out, "#if defined( _MANAGED )\n" );
   printFunc( out, NULL, funcInfo, pfs_prototype | pfs_stateSaveSignature | pfs_managedCPPCode );
   print( out, "#elif defined( _JAVA )\n" );
   /* Handle special case to avoid duplicate definition of min,max */
   if( strcmp( funcInfo->camelCaseName, "Min" ) == 0 ) {
      print( out, "#undef min\n" );
   } else if( strcmp( funcInfo->camelCaseName, "Max" ) == 0 ) {
      print( out, "#undef max\n" );
   }
   printFunc( out, NULL, funcInfo, pfs_prototype | pfs_stateSaveSignature | pfs_outputForJava );
   print( out, "#else\n" );
   printFunc( out, "TA_LIB_API ", funcInfo, pfs_prototype | pfs_stateSaveSignature );
   print( out, "#endif\n" );
   //section 11 end

   genPrefix = 0;
   skipToGenCode( funcInfo->name, gOutFunc_C->file, gOutFunc_C->templateFile );

   //section 12 begin
   genPrefix = 1;
   print( out, "\n" );
   print( out, "#ifndef TA_FUNC_NO_RANGE_CHECK\n" );
   print( out, "\n" );
   /* Generate the code for checking the parameters.
    * Also generates the code for setting up the
    * default values.
    */
   printFunc( out, NULL, funcInfo, pfs_stateSaveSignature | pfs_validationCode );
   print( out, "#endif /* TA_FUNC_NO_RANGE_CHECK */\n" );
   print( out, "\n" );
   //section 12 end

   genPrefix = 0;
   skipToGenCode( funcInfo->name, gOutFunc_C->file, gOutFunc_C->templateFile );

   // section 13 begin
   genPrefix = 1;
   print( out, "\n" );
   print( out, "#if defined( _MANAGED )\n" );
   printFunc( out, NULL, funcInfo, pfs_prototype | pfs_stateLoadSignature | pfs_managedCPPCode );
   print( out, "#elif defined( _JAVA )\n" );
   /* Handle special case to avoid duplicate definition of min,max */
   if( strcmp( funcInfo->camelCaseName, "Min" ) == 0 ) {
      print( out, "#undef min\n" );
   } else if( strcmp( funcInfo->camelCaseName, "Max" ) == 0 ) {
      print( out, "#undef max\n" );
   }
   printFunc( out, NULL, funcInfo, pfs_prototype | pfs_stateLoadSignature | pfs_outputForJava );
   print( out, "#else\n" );
   printFunc( out, "TA_LIB_API ", funcInfo, pfs_prototype | pfs_stateLoadSignature );
   print( out, "#endif\n" );
   //section 13 end

   genPrefix = 0;
   skipToGenCode( funcInfo->name, gOutFunc_C->file, gOutFunc_C->templateFile );

   //section 14 begin
   genPrefix = 1;
   print( out, "\n" );
   print( out, "#ifndef TA_FUNC_NO_RANGE_CHECK\n" );
   print( out, "\n" );
   /* Generate the code for checking the parameters.
    * Also generates the code for setting up the
    * default values.
    */
   printFunc( out, NULL, funcInfo, pfs_stateLoadSignature | pfs_validationCode );
   print( out, "#endif /* TA_FUNC_NO_RANGE_CHECK */\n" );
   print( out, "\n" );
   //section 14 end

   // section 15?
   /* Put a marker who is going to be used in the second pass */
//   fprintf( out, "%%%%%%GENCODE%%%%%%\n" );
}

void printOptInputValidation( FILE *out,
                                     const char *name,                                     
                                     const TA_OptInputParameterInfo *optInputParamInfo,
                                     int lookbackValidationCode /* Boolean */ )
{
   int minInt, maxInt;
   double minReal, maxReal;
   unsigned int i;
   int isMAType;

   const TA_RealList     *realList;
   const TA_IntegerList  *integerList;
   const TA_RealRange *realRange;
   const TA_IntegerRange *integerRange;

   minInt  = maxInt  = (int)0;
   minReal = maxReal = (double)0.0;

   switch( optInputParamInfo->type )
   {
   case TA_OptInput_RealRange:
      realRange = (const TA_RealRange *)optInputParamInfo->dataSet;
      minReal = realRange->min;
      maxReal = realRange->max;
      break;
   case TA_OptInput_IntegerRange:
      integerRange = (const TA_IntegerRange *)optInputParamInfo->dataSet;
      minInt = integerRange->min;
      maxInt = integerRange->max;
      break;
   case TA_OptInput_RealList:
      /* Go through the list to find the min/max. */
      realList = (const TA_RealList *)optInputParamInfo->dataSet;
      minReal = realList->data[0].value;
      maxReal = realList->data[0].value;
      for( i=0; i < realList->nbElement; i++ )
      {
         minReal = min( realList->data[i].value, minReal );
         maxReal = max( realList->data[i].value, maxReal );
      }
      break;
   case TA_OptInput_IntegerList:
      /* Go through the list to find the min/max. */
      integerList = (const TA_IntegerList *)optInputParamInfo->dataSet;
      minInt = integerList->data[0].value;
      maxInt = integerList->data[0].value;
      for( i=0; i < integerList->nbElement; i++ )
      {
         minInt = min( integerList->data[i].value, minInt );
         maxInt = max( integerList->data[i].value, maxInt );
      }
      break;
   }

  /* Boolean to detect special TA_MAType enumeration. */
  if( optInputParamInfo->dataSet == TA_DEF_UI_MA_Method.dataSet )
     isMAType = 1;
  else
     isMAType = 0;

   switch( optInputParamInfo->type )
   {
   case TA_OptInput_RealList:
      print( out, "   /* min/max are checked for %s. */\n", name );
   case TA_OptInput_RealRange:
      print( out, "   if( %s == TA_REAL_DEFAULT )\n", name  );
      print( out, "      %s = %s;\n", name, doubleToStr(optInputParamInfo->defaultValue) );
      print( out, "   else if( (%s < %s) ||", name, doubleToStr(minReal) );
      print( out, " (%s > %s) )\n", name, doubleToStr(maxReal) );              
      break;
   case TA_OptInput_IntegerRange:
      print( out, "   /* min/max are checked for %s. */\n", name );
   case TA_OptInput_IntegerList:
      print( out, "   if( (int)%s == TA_INTEGER_DEFAULT )\n", name );
	  print( out, "      %s = %s%d;\n", name, isMAType?"(TA_MAType)":"", (int)optInputParamInfo->defaultValue );
      print( out, "   else if( ((int)%s < %d) || ((int)%s > %d) )\n",
              name, minInt,
              name, maxInt );
      break;
   }

   if( lookbackValidationCode )
      print( out, "      return -1;\n" );
   else
      print( out, "      return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);\n" );

   print( out, "\n" );
}


int skipToGenCode( const char *dstName, FILE *out, FILE *templateFile )
{
   unsigned int headerWritten = 0;

   while( fgets( gTempBuf, BUFFER_SIZE, templateFile ) )
   {
      if( strncmp( gTempBuf, "%%%GENCODE%%%", 13 ) == 0 )
      {
         headerWritten = 1;
         break;
      }
      if( out && (fputs( gTempBuf, out ) == EOF) )
      {
         printf( "Cannot write to [%s]\n", dstName );
         return -1;
      }
   }

   if( !headerWritten )
   {
      printf( "Line with string %%%%%%GENCODE%%%%%% Missing in [%s]", dstName );
      return -1;
   }

   return 0;
}

void printFuncHeaderDoc( FILE *out,
                                const TA_FuncInfo *funcInfo,
                                const char *prefix )
{
   TA_RetCode retCode;
   unsigned int paramNb;
   const char *paramName;
   const char *defaultParamName;
   const TA_InputParameterInfo *inputParamInfo;
   const TA_OptInputParameterInfo *optInputParamInfo;
   const TA_OutputParameterInfo *outputParamInfo;
   int first;

   fprintf( out, "%sTA_%s - %s\n", prefix, funcInfo->name, funcInfo->hint );
   fprintf( out, "%s\n", prefix );

   fprintf( out, "%sInput  = ", prefix );
   for( paramNb=0; paramNb < funcInfo->nbInput; paramNb++ )
   {
      retCode = TA_GetInputParameterInfo( funcInfo->handle,
                                          paramNb, &inputParamInfo );

      if( retCode != TA_SUCCESS )
      {
         printf( "[%s] invalid 'input' information\n", funcInfo->name );
         return;
      }

      switch( inputParamInfo->type )
      {
      case TA_Input_Pointer: break; // only for stateStruct declaration
      case TA_Input_Price:
         first = 1;
         #define PRICE_PARAM(upperParam,lowerParam) \
         { \
            if( inputParamInfo->flags & TA_IN_PRICE_##upperParam ) \
            { \
               if( !first ) fprintf( out, ", " ); \
               fprintf( out, lowerParam ); \
               first = 0; \
            } \
         }

         PRICE_PARAM( OPEN,         "Open" );
         PRICE_PARAM( HIGH,         "High" );
         PRICE_PARAM( LOW,          "Low" );
         PRICE_PARAM( CLOSE,        "Close" );
         PRICE_PARAM( VOLUME,       "Volume" );
         PRICE_PARAM( OPENINTEREST, "OpenInterest" );
         PRICE_PARAM( TIMESTAMP,    "Timestamp" );

         #undef PRICE_PARAM

         break;
      case TA_Input_Integer:
         fprintf( out, "int" );
         break;
      case TA_Input_Real:
         fprintf( out, "double" );
         break;
      }
      if( paramNb+1 == funcInfo->nbInput )
         fprintf( out, "\n" );
      else
         fprintf( out, ", " );
   }

   fprintf( out, "%sOutput = ", prefix );
   for( paramNb=0; paramNb < funcInfo->nbOutput; paramNb++ )
   {
      retCode = TA_GetOutputParameterInfo( funcInfo->handle,
                                           paramNb, &outputParamInfo );

      if( retCode != TA_SUCCESS )
      {
         printf( "[%s] invalid 'output' information\n", funcInfo->name );
         return;
      }

      switch( outputParamInfo->type )
      {
      case TA_Output_Real:
         fprintf( out, "double" );
         break;
      case TA_Output_Integer:
         fprintf( out, "int" );
         break;
      }
      if( paramNb+1 == funcInfo->nbOutput )
         fprintf( out, "\n" );
      else
         fprintf( out, ", " );
   }

   if( funcInfo->nbOptInput != 0 )
   {
      fprintf( out, "%s\n", prefix );
      fprintf( out, "%sOptional Parameters\n", prefix );
      fprintf( out, "%s-------------------\n", prefix );
  
      for( paramNb=0; paramNb < funcInfo->nbOptInput; paramNb++ )
      {
         retCode = TA_GetOptInputParameterInfo( funcInfo->handle,
                                                paramNb, &optInputParamInfo );

         if( retCode != TA_SUCCESS )
         {
            printf( "[%s] invalid 'optional input' information\n", funcInfo->name );
            return;
         }

         paramName = optInputParamInfo->paramName;

         switch( optInputParamInfo->type )
         {
         case TA_OptInput_RealRange:
         case TA_OptInput_RealList:
            defaultParamName = "optInReal";
            break;
         case TA_OptInput_IntegerRange:
         case TA_OptInput_IntegerList:
            defaultParamName = "optInInteger";
            break;
         default:
            if( !paramName )
               paramName = "optInParam";
            printf( "[%s,%s,%d] invalid 'optional input' type(%d)\n",
                    funcInfo->name, paramName, paramNb,
                    optInputParamInfo->type );
            return;
         }

         if( !paramName )
            paramName = defaultParamName;

         fprintf( out, "%s%s:", prefix, paramName );
         switch( optInputParamInfo->type )
         {
         case TA_OptInput_RealRange:
               if( ((TA_RealRange *)(optInputParamInfo->dataSet))->min == TA_REAL_MIN )
                  fprintf( out, "(From TA_REAL_MIN" );
               else
               {
                  fprintf( out, "(From %.*g",
                           ((TA_RealRange *)(optInputParamInfo->dataSet))->precision,
                           ((TA_RealRange *)(optInputParamInfo->dataSet))->min );
               }

               if( ((TA_RealRange *)(optInputParamInfo->dataSet))->max == TA_REAL_MAX )
                  fprintf( out, " to TA_REAL_MAX)\n" );
               else
               {
                  fprintf( out, " to %.*g%s)\n", 
                          ((TA_RealRange *)(optInputParamInfo->dataSet))->precision,
                          ((TA_RealRange *)(optInputParamInfo->dataSet))->max,
                          optInputParamInfo->flags & TA_OPTIN_IS_PERCENT? " %":"" );
               }
               break;
         case TA_OptInput_IntegerRange:
               if( ((TA_IntegerRange *)(optInputParamInfo->dataSet))->min == TA_INTEGER_MIN )
                  fprintf( out, "(From TA_INTEGER_MIN" );
               else
               {
                  fprintf( out, "(From %d",
                           ((TA_IntegerRange *)(optInputParamInfo->dataSet))->min );
               }

               if( ((TA_IntegerRange *)(optInputParamInfo->dataSet))->max == TA_INTEGER_MAX )
                  fprintf( out, " to TA_INTEGER_MAX)\n" );
               else
               {
                  fprintf( out, " to %d)\n", 
                          ((TA_IntegerRange *)(optInputParamInfo->dataSet))->max );
               }
               break;
         default:
             fprintf( out, "\n" );
         }
         fprintf( out, "%s   %s\n", prefix, optInputParamInfo->hint );
         fprintf( out, "%s\n", prefix );
      }
   }

   fprintf( out, "%s\n", prefix );
}

int addUnstablePeriodEnum( FILE *out )
{
   TA_RetCode retCode;
   unsigned int id;

   print( out, "\n" );
   print( out, "ENUM_BEGIN( FuncUnstId )\n");

   /* Enumerate the function having an "unstable period". Give
    * to each a unique identifier.
    */
   id = 0;
   retCode = TA_ForEachFunc( doForEachUnstableFunction, &id );

   print( out, "               ENUM_DEFINE( TA_FUNC_UNST_ALL, FuncUnstAll),\n");
   print( out, "               ENUM_DEFINE( TA_FUNC_UNST_NONE, FuncUnstNone) = -1\n" );
   print( out, "ENUM_END( FuncUnstId )\n");

   if( retCode != TA_SUCCESS )
      return -1;

   return 0;
}

int gen_retcode( void )
{
   FileHandle *inHdr;
   char *ptr1, *ptr2;
   int step1Done;
   int retValue;
   TA_RetCode retCodeValue;
   char *retCodeEnum, *retCodeInfo;

   retValue = -1;

   /* Create "ta_retcode.c" */
   gOutRetCode_C = fileOpen( ta_fs_path(4, "..", "src", "ta_common", "ta_retcode.c"),
                             ta_fs_path(5, "..", "src", "ta_abstract", "templates", "ta_retcode.c.template"),
                             FILE_WRITE|WRITE_ON_CHANGE_ONLY );

   if( gOutRetCode_C == NULL )
   {
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }

   /* Create "ta_retcode.csv" */
   gOutRetCode_CSV = fileOpen( ta_fs_path(4, "..", "src", "ta_common", "ta_retcode.csv"),
                               NULL,
                               FILE_WRITE|WRITE_ON_CHANGE_ONLY );

   if( gOutRetCode_CSV == NULL )
   {
      fileClose( gOutRetCode_C );
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }

   inHdr = fileOpen( ta_fs_path(3, "..", "include", "ta_defs.h"),
                     NULL,
                     FILE_READ );
   if( inHdr == NULL )
   {
      fileClose( gOutRetCode_C );
      fileClose( gOutRetCode_CSV );
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }

   step1Done = 0;
   while( fgets( gTempBuf, sizeof( gTempBuf ), inHdr->file ) )
   {
      if( !step1Done )
      {
         if( strstr( gTempBuf, "ENUM_BEGIN( RetCode )" ) != NULL )
            step1Done = 1;
      }
      else
      {
         if( strstr( gTempBuf, "TA_UNKNOWN_ERR" ) != NULL )
         {
            retValue = 0;
            goto gen_retcode_exit;
         }

         ptr1 = strstr( gTempBuf, "/*" );
         ptr2 = strstr( gTempBuf, "/***" );
         if( ptr1 && !ptr2 )
         {
            ptr1 += 2;
            retCodeValue = (TA_RetCode)atoi(ptr1);
            ptr1 = strstr( ptr1, "TA_" );
            if( !ptr1 )
            {
               printf( "Can't find TA_" );
               goto gen_retcode_exit;
            }
            retCodeEnum = ptr1;

            retCodeInfo = NULL;
            while( isdigit(*ptr1) || isalpha(*ptr1) || *ptr1 == '_' )
               ptr1++;
            if( *ptr1 != '\0' )
            {
               *ptr1 = '\0';
               ptr1++;
               if( *ptr1 != '\0' )
               {
                  retCodeInfo = strstr( ptr1, "/* " );
                  if( retCodeInfo )
                  {
                     retCodeInfo += 3;
                     ptr1 = strstr( retCodeInfo, "*/" );
                     if( ptr1 == NULL )
                        retCodeInfo = NULL;
                     else
                        *ptr1 = '\0';
                  }
               }                  
            }

            if( !retCodeInfo )
               retCodeInfo = "No Info";

            strcpy( gTempBuf, retCodeEnum );
            ptr1 = trimWhitespace( gTempBuf );
            fprintf( gOutRetCode_C->file, "         {(TA_RetCode)%d,\"%s\",", retCodeValue, ptr1 );                     
            fprintf( gOutRetCode_CSV->file, "%d,%s", retCodeValue, ptr1 );
            strcpy( gTempBuf, retCodeInfo );
            ptr1 = trimWhitespace( gTempBuf );
            fprintf( gOutRetCode_C->file, "\"%s\"},\n", ptr1 );
            fprintf( gOutRetCode_CSV->file, ",%s\n", ptr1 );
         }
      }
   }

gen_retcode_exit:
   fileClose( inHdr );
   fileClose( gOutRetCode_C );
   fileClose( gOutRetCode_CSV );

   return retValue; /* Success. */
}

const char *doubleToStr( double value )
{
   int length;
   int i, outIdx;
   sprintf( gTempDoubleToStr, "%e", value );

   /* Remove extra "0" added by Microsoft in the
    * exponential part.
    */
   length = (int)strlen( gTempDoubleToStr );
   outIdx = 0;
   for( i=0; i < length; i++ )
   {
      /* Will skip two leading zero in the exponent */
      if( (i >= 2) &&
          (toupper(gTempDoubleToStr[i-2]) == 'E') &&
          ((gTempDoubleToStr[i-1] == '+')||(gTempDoubleToStr[i-1] == '-')) &&
          (gTempDoubleToStr[i] == '0') &&
          (gTempDoubleToStr[i+1] == '0') &&
          (isdigit(gTempDoubleToStr[i+2])) )
      {
         i++;
         continue;
      }

      /* Will skip one leading zero in the exponent */
      if( (i >= 2) &&
          (toupper(gTempDoubleToStr[i-2]) == 'E') &&
          ((gTempDoubleToStr[i-1] == '+')||(gTempDoubleToStr[i-1] == '-')) &&
          (gTempDoubleToStr[i] == '0') &&
          (isdigit(gTempDoubleToStr[i+1])))
      {
         continue;
      }

      gTempDoubleToStr[outIdx++] = gTempDoubleToStr[i];
   }
   gTempDoubleToStr[outIdx] = '\0';

   return gTempDoubleToStr;
}

void cnvtToUpperCase( char *str )
{
   char c;

   if( !str ) return;

   c = *str; 
   while( c != '\0' )
   {
      *str = (char)toupper(c);
      str++;
      c = *str;
   }      
}

char *trimWhitespace( char *str )
{
   int i;

   if( !str ) return str;

   while( isspace(*str) ) str++;
   if( *str == '\0' ) return str;

   for( i=(int)strlen(str)-1; i >= 0; i-- )
   {
      if( !isspace(str[i]) )
         return str;
      str[i] = '\0';      
   }

   return str;
}

void cnvtChar( char *str, char from, char to )
{
   char c;

   if( !str ) return;
   
   c = *str;
   while( c != '\0' )
   {
      if( c == from ) *str = to;
      str++;
      c = *str;
   }
}

#ifdef _MSC_VER
void printExcelGlueCode( FILE *out, const TA_FuncInfo *funcInfo )
{
   /*fprintf( out, "#include \"ta_%s.c\"\n", funcInfo->name );
   fprintf( out, "#include \"ta_%s_frame.c\"\n", funcInfo->name );   */
   int nbParam;
   unsigned int i;
   TA_RetCode retCode;
   const TA_InputParameterInfo *inputParamInfo;

   nbParam = funcInfo->nbOptInput;

   for( i=0; i < funcInfo->nbInput; i++ )
   {
      retCode = TA_GetInputParameterInfo( funcInfo->handle,
                                          i, &inputParamInfo );

      if( retCode != TA_SUCCESS )
      {
         printf( "[%s] invalid 'input' information (%d,%d)\n", funcInfo->name, i, nbParam );
         return;
      }

      if( inputParamInfo->type != TA_Input_Price )
         nbParam++;
      else
      {
         if( inputParamInfo->flags & TA_IN_PRICE_TIMESTAMP )
            nbParam++;
         if( inputParamInfo->flags & TA_IN_PRICE_OPEN )
            nbParam++;
         if( inputParamInfo->flags & TA_IN_PRICE_HIGH )
            nbParam++;
         if( inputParamInfo->flags & TA_IN_PRICE_LOW )
            nbParam++;
         if( inputParamInfo->flags & TA_IN_PRICE_CLOSE )
            nbParam++;
         if( inputParamInfo->flags & TA_IN_PRICE_VOLUME )
            nbParam++;
         if( inputParamInfo->flags & TA_IN_PRICE_OPENINTEREST )         
            nbParam++;
      }
   }

   fprintf( out, "EXCEL_GLUE_CODE_WITH_%d_PARAM(%s)\n", 
           nbParam,
           funcInfo->name );
}
#endif


void extractTALogic( FILE *inFile, FILE *outFile )
{
   int i, length, nbCodeChar;
   int commentBlock, commentFirstCharFound, outIdx;

   #define START_DELIMITATOR "/**** END GENCODE SECTION 3"
   #define STOP_DELIMITATOR  "/**** START GENCODE SECTION 5"

   /* Find the begining of the function */
   while( fgets( gTempBuf, BUFFER_SIZE, inFile ) )
   {
      length = (int)strlen(gTempBuf);
      if( length > BUFFER_SIZE )
         return;

      if( strncmp( gTempBuf, START_DELIMITATOR, strlen(START_DELIMITATOR) ) == 0)
         break;
   }

   /* Copy until the end of the function.
    * At the same time, eliminate all empty line and
    * comments to avoid confusion with original code.
    */
   commentBlock = 0;
   commentFirstCharFound = 0;
   while( fgets( gTempBuf, BUFFER_SIZE, inFile ) )
   {
      length = (int)strlen(gTempBuf);
      if( length > BUFFER_SIZE )
         return;

      if( strncmp( gTempBuf, STOP_DELIMITATOR, strlen(STOP_DELIMITATOR) ) == 0)
         break;

      /* Process the whole line and put it in gTempBuf2 */
      outIdx = 0;
      nbCodeChar = 0;
      for( i=0; i < length; i++ )
      {
         if( !commentBlock )
         {
            if( !commentFirstCharFound )
            {
               if( gTempBuf[i] == '/' )
                  commentFirstCharFound = 1;
               else
               {
                  gTempBuf2[outIdx++] = gTempBuf[i];
                  if( !isspace(gTempBuf[i]) )
                     nbCodeChar++;
               }
            }
            else
            {
               commentFirstCharFound = 0;
               if( gTempBuf[i] == '*' )
                  commentBlock = 1;
               else 
               {
                  gTempBuf2[outIdx++] = '/';
                  nbCodeChar++;
                  if( gTempBuf[i] == '/' )
                     commentFirstCharFound = 1;
                  else
                  {
                     gTempBuf2[outIdx++] = gTempBuf[i];
                     if( !isspace(gTempBuf[i]) )
                        nbCodeChar++;
                  }
               }
            }            
         }
         else
         {
            if( !commentFirstCharFound )
            {
               if( gTempBuf[i] == '*' )
                  commentFirstCharFound = 1;
            }
            else
            {
               commentFirstCharFound = 0;
               if( gTempBuf[i] == '/' )
                  commentBlock = 0;
               else if( gTempBuf[i] == '*' )
                  commentFirstCharFound = 1;
            }            
         }
      }

      /* Preserve markers for proprietary code. */
      #define BEG_PROP_MARKER "* Begin Proprietary *"
	  #define END_PROP_MARKER "* End Proprietary *"
	  if( strstr( gTempBuf, BEG_PROP_MARKER ) )
	  {
         fputs( "/* Generated */ /", outFile );
         fputs( BEG_PROP_MARKER, outFile );
         fputs( "/\n", outFile );
	  }
	  else if( strstr( gTempBuf, END_PROP_MARKER ) )
	  {
         fputs( "/* Generated */ /", outFile );
         fputs( END_PROP_MARKER, outFile );
         fputs( "/\n", outFile );
	  }
      else if( nbCodeChar != 0 )
      {
         gTempBuf2[outIdx] = '\0';
		 /* Write the code */
         fputs( "/* Generated */ ", outFile );
         fputs( gTempBuf2, outFile );
      }
   }
}

int copyFile( const char *src, const char *dest )
{
   FILE *in;
   FILE *out;

   init_gToOpen( src, NULL );
   in = fopen( gToOpen, "rb" );   
   if( !in )
      return 0;

   init_gToOpen( dest, NULL );
   out = fopen( gToOpen, "wb" );
   if( !out )
   {
      fclose( in );
      return 0;
   }

   while( fgets( gTempBuf, BUFFER_SIZE, in ) )
   {
      fputs(gTempBuf,out);
   }

   fclose(in);
   fclose(out);
   return 1;
}

int areFileSame( const char *file1, const char *file2 )
{
   /* Text comparison of both files */
   unsigned int i;

   FILE *f1;
   FILE *f2;


   init_gToOpen( file1, NULL );
   f1 = fopen( gToOpen, "r" );
   if( !f1 )
      return 0;

   init_gToOpen( file2, NULL );
   f2 = fopen( gToOpen, "r" );
   if( !f2 )
   {
      fclose( f1 );
      return 0;
   }
   
   memset( gTempBuf,  0, sizeof(gTempBuf ) );
   memset( gTempBuf2, 0, sizeof(gTempBuf2) );

   while( fgets( gTempBuf, BUFFER_SIZE, f1 ) )
   {
      if( !fgets( gTempBuf2, BUFFER_SIZE, f2 ) )
      {
         fclose(f1);
         fclose(f2);
         return 0;
      } 
      
      for( i=0; i < sizeof(gTempBuf); i++ )
      {
         if( gTempBuf[i] != gTempBuf2[i] )
         {
            fclose(f1);
            fclose(f2);
            return 0;
         }          
         if( gTempBuf[i] == '\0' )
            i = sizeof(gTempBuf);
      }

      memset( gTempBuf,  0, sizeof(gTempBuf ) );
      memset( gTempBuf2, 0, sizeof(gTempBuf2) );
   }

   if( fgets( gTempBuf2, BUFFER_SIZE, f2 ) )
   {
      fclose(f1);
      fclose(f2);
      return 0;
   }
   
   fclose(f1);
   fclose(f2);
   return 1;
}


void appendToFunc( FILE *out )
{
   fprintf( out, "\n" );
   fprintf( out, "/* Some TA functions takes a certain amount of input data\n" );
   fprintf( out, " * before stabilizing and outputing meaningful data. This is\n" );
   fprintf( out, " * a behavior pertaining to the algo of some TA functions and\n" );
   fprintf( out, " * is not particular to the TA-Lib implementation.\n" );
   fprintf( out, " * TA-Lib allows you to automatically strip off these unstabl\n" );
   fprintf( out, " * data from your output and from any internal processing.\n" );
   fprintf( out, " * (See documentation for more info)\n" );
   fprintf( out, " *\n" );
   fprintf( out, " * Examples:\n" );
   fprintf( out, " *      TA_SetUnstablePeriod( TA_FUNC_UNST_EMA, 30 );\n" );
   fprintf( out, " *           Always strip off 30 price bar for the TA_EMA function.\n" );
   fprintf( out, " *\n" );
   fprintf( out, " *      TA_SetUnstablePeriod( TA_FUNC_UNST_ALL, 30 );\n" );
   fprintf( out, " *           Always strip off 30 price bar from ALL functions\n" );
   fprintf( out, " *           having an unstable period.\n" );
   fprintf( out, " *\n" );
   fprintf( out, " * See ta_defs.h for the enumeration TA_FuncUnstId\n" );
   fprintf( out, " */\n" );
   fprintf( out, "\n" );
   fprintf( out, "TA_RetCode TA_SetUnstablePeriod( TA_FuncUnstId id,\n" );
   fprintf( out, "                                 unsigned int  unstablePeriod );\n" );
   fprintf( out, "\n" );
   fprintf( out, "unsigned int TA_GetUnstablePeriod( TA_FuncUnstId id );\n" );
   fprintf( out, "\n" );
   fprintf( out, "/* You can change slightly the behavior of the TA functions\n" );
   fprintf( out, " * by requesting compatibiliy with some existing software.\n" );
   fprintf( out, " *\n" );
   fprintf( out, " * By default, the behavior is as close as the original \n" );
   fprintf( out, " * author of the TA functions intend it to be.\n" );
   fprintf( out, " *\n" );
   fprintf( out, " * See ta_defs.h for the enumeration TA_Compatibility.\n" );
   fprintf( out, " */\n" );
   fprintf( out, "TA_RetCode TA_SetCompatibility( TA_Compatibility value );\n" );
   fprintf( out, "TA_Compatibility TA_GetCompatibility( void );\n" );
   fprintf( out, "\n" );
   fprintf( out, "/* Candlesticks struct and functions\n" );
   fprintf( out, " * Because candlestick patterns are subjective, it is necessary \n" );
   fprintf( out, " * to allow the user to specify what should be the meaning of \n" );
   fprintf( out, " * 'long body', 'short shadows', etc.\n" );
   fprintf( out, " */\n" );
   fprintf( out, "\n" );
   fprintf( out, "/* Call TA_SetCandleSettings to set that when comparing a candle \n" );
   fprintf( out, " * basing on settingType it must be compared with the average \n" );
   fprintf( out, " * of the last avgPeriod candles' rangeType multiplied by factor.\n" );
   fprintf( out, " * This setting is valid until TA_RestoreCandleDefaultSettings is called\n" );
   fprintf( out, " */\n" );
   fprintf( out, "TA_RetCode TA_SetCandleSettings( TA_CandleSettingType settingType, \n" );
   fprintf( out, "                                 TA_RangeType rangeType, \n" );
   fprintf( out, "                                 int avgPeriod, \n" );
   fprintf( out, "                                 double factor );\n" );
   fprintf( out, "\n" );
   fprintf( out, "/* Call TA_RestoreCandleDefaultSettings after using custom settings \n" );
   fprintf( out, " * to restore the default settings for the specified settingType\n" );
   fprintf( out, " */\n" );
   fprintf( out, "TA_RetCode TA_RestoreCandleDefaultSettings( TA_CandleSettingType settingType );\n" );
}

void genJavaCodePhase1( const TA_FuncInfo *funcInfo )
{
   fprintf( gOutJavaDefs_H->file, "#define TA_%s_Lookback %c%sLookback\n", funcInfo->name, tolower(funcInfo->camelCaseName[0]), &funcInfo->camelCaseName[1] );
   fprintf( gOutJavaDefs_H->file, "#define TA_%s %c%s\n", funcInfo->name, tolower(funcInfo->camelCaseName[0]), &funcInfo->camelCaseName[1] );   
   fprintf( gOutJavaDefs_H->file, "#define TA_%s_StateInit %c%s\n", funcInfo->name, tolower(funcInfo->camelCaseName[0]), &funcInfo->camelCaseName[1] );
   fprintf( gOutJavaDefs_H->file, "#define TA_%s_State %c%s\n", funcInfo->name, tolower(funcInfo->camelCaseName[0]), &funcInfo->camelCaseName[1] );
   fprintf( gOutJavaDefs_H->file, "#define TA_%s_StateFree %c%s\n", funcInfo->name, tolower(funcInfo->camelCaseName[0]), &funcInfo->camelCaseName[1] );
}

void genJavaCodePhase2( const TA_FuncInfo *funcInfo )
{
   FILE *logicTmp;
   char buffer[500];
   int idx, again;
   int firstTime = 1;

   if( firstTime == 1 )
   {
      /* Clean-up jus tin case. */
      fileDelete( ta_fs_path(3, "..", "temp", "CoreJavaCode1.tmp") );
      fileDelete( ta_fs_path(3, "..", "temp", "CoreJavaCode2.tmp") );
      firstTime = 0;
   }

   init_gToOpen(ta_fs_path(3, "..", "temp", "CoreJavaCode1.tmp"), NULL );
   logicTmp = fopen( gToOpen, "w" );
   if( !logicTmp )
   {
      printf( "Cannot open CoreJavaCode1.tmp\n" );
      return;
   }
   fprintf( logicTmp, "#include \"ta_java_defs.h\"\n" );
   fclose(logicTmp);
   
#ifdef _MSC_VER
   sprintf( buffer, TA_MCPP_EXE " -c -+ -z -P -I.." TA_FS_SLASH "src" TA_FS_SLASH "ta_common -I.." TA_FS_SLASH "src" TA_FS_SLASH "ta_abstract -I.." TA_FS_SLASH "include -D _JAVA .." TA_FS_SLASH "src" TA_FS_SLASH "ta_func" TA_FS_SLASH "TA_%s.c >>.." TA_FS_SLASH "temp" TA_FS_SLASH "CoreJavaCode1.tmp ", funcInfo->name);
   system( buffer );

   sprintf( buffer, TA_MCPP_EXE " -c -+ -z -P -I.." TA_FS_SLASH "src" TA_FS_SLASH "ta_common -I.." TA_FS_SLASH "src" TA_FS_SLASH "ta_abstract -I.." TA_FS_SLASH "include -D _JAVA .." TA_FS_SLASH "temp" TA_FS_SLASH "CoreJavaCode1.tmp >.." TA_FS_SLASH "temp" TA_FS_SLASH "CoreJavaCode2.tmp " );
   system( buffer );
#else
   /* The options are the quite same, but on linux it still outputs the #include lines,
	didn't find anything better that to cut them with the sed ... a hack for now. */
   sprintf( buffer, TA_MCPP_EXE " -@compat -+ -z -P -I.." TA_FS_SLASH "src" TA_FS_SLASH "ta_common -I.." TA_FS_SLASH "src" TA_FS_SLASH "ta_abstract -I.." TA_FS_SLASH "include -D _JAVA .." TA_FS_SLASH "src" TA_FS_SLASH "ta_func" TA_FS_SLASH "ta_%s.c | sed '/^#include/d' >> .." TA_FS_SLASH "temp" TA_FS_SLASH "CoreJavaCode1.tmp ", funcInfo->name);
   system( buffer );

   sprintf( buffer, TA_MCPP_EXE " -@compat -+ -z -P -I.." TA_FS_SLASH "src" TA_FS_SLASH "ta_common -I.." TA_FS_SLASH "src" TA_FS_SLASH "ta_abstract -I.." TA_FS_SLASH "include -D _JAVA .." TA_FS_SLASH "temp" TA_FS_SLASH "CoreJavaCode1.tmp | sed '/^#include/d' > .." TA_FS_SLASH "temp" TA_FS_SLASH "CoreJavaCode2.tmp " );
   system( buffer );
#endif

   /* Append the output of the C pre-processor to the Core.Java file. */
   init_gToOpen( ta_fs_path(3, "..", "temp", "CoreJavaCode2.tmp"), NULL );
   logicTmp = fopen( gToOpen, "r" );
   if( !logicTmp )
   {
      printf( "Cannot open CoreJavaCode2.tmp\n" );
      return;
   }
   while( fgets(gTempBuf,BUFFER_SIZE,logicTmp) )
   {
      /* Remove empty lines and lines with only a ';' */
      idx = 0;
      again = 1;
      while( again && gTempBuf[idx] != '\0' )
      {
         if( !isspace(gTempBuf[idx]) && !(gTempBuf[idx] == ';') )
            again = 0;
         idx++;
      }
      if( (again == 0) && (idx > 0) )
         fputs( gTempBuf, gOutCore_Java->file );
   }

   /* Clean-up */
   fclose(logicTmp);
   print( gOutCore_Java->file, "\n" );   
   fileDelete( ta_fs_path(3, "..", "temp", "CoreJavaCode1.tmp") );
   fileDelete( ta_fs_path(3, "..", "temp", "CoreJavaCode2.tmp") );
}


int generateFuncAPI_C()
{
   FileHandle *inFile;
   FILE *out;
   FILE *in;

   #define FILE_INPUT           ta_fs_path(3, "..", "..", "ta_func_api.xml")
   #define FILE_OUTPUT          ta_fs_path(4, "..", "src", "ta_abstract", "ta_func_api.c")
   #define FILE_OUTPUT_TEMPLATE ta_fs_path(5, "..", "src", "ta_abstract", "templates", "ta_func_api.c.template")

   inFile = fileOpen( FILE_INPUT, NULL, FILE_READ );
   if( inFile == NULL )   
   {
      printf( "\nCannot access [%s]\n", gToOpen );
      return -1;
   }
   gOutFuncAPI_C = fileOpen( FILE_OUTPUT, FILE_OUTPUT_TEMPLATE, FILE_WRITE|WRITE_ON_CHANGE_ONLY );
   if( gOutFuncAPI_C == NULL )
   {
      printf( "\nCannot write to [%s]\n", gToOpen );
      return -1;
   }

   out = gOutFuncAPI_C->file;
   in  = inFile->file;
 
   convertFileToCArray(in, out);

   fileClose(gOutFuncAPI_C);
   fileClose(inFile);

   return 1;
}

void convertFileToCArray( FILE *in, FILE *out )
{
    int c;
    int position;
    
    position = 0;
    c = getc(in);
    while( c != EOF )
    {
       if( position == 0 )
          fprintf( out, "0x%02X", (char)c );
       else
       {
          fprintf( out, ",0x%02X", (char)c );
          if( (position % 20) == 0 )
             fprintf( out, "\n" );
       }       
       position++;
       c = getc(in);
   }
 
}

void printJavaFunctionAnnotation(const TA_FuncInfo *funcInfo)
{
    TA_RetCode retCode;
	TA_InputParameterInfo *inputInfo;
	TA_OptInputParameterInfo *optInputInfo;
	TA_OutputParameterInfo *outputInfo;
    TA_RealRange *doubleRange;
    TA_IntegerRange *integerRange;
    TA_IntegerList *intList;
	unsigned int i, j;
    #define FUNCNAME_SIZE 100
	char funcName[FUNCNAME_SIZE];
	   
    memset(funcName, 0, FUNCNAME_SIZE);
    if( strlen(funcInfo->name) > (FUNCNAME_SIZE-1) )
    {
        printf( "\n*** Error buffer size exceeded (printJavaFunctionAnnotation)\n" );
        strcpy( funcName, "1A2"); /* Substitute name. Will cause Java compilation to fail */
    }
    else
    {	   
	   if (funcInfo->camelCaseName==NULL) {
	      strcpy(funcName, funcInfo->name);
		  for (i=0; funcName[i]; i++) {
			funcName[i] = tolower(funcName[i]);
		  }
	   } else {
	     strcpy(funcName, funcInfo->camelCaseName);
         funcName[0] = tolower(funcName[0]);
	   }
    }


	/*
	 * Generate Lookback method
	 */
    fprintf(gOutFunc_Annotation->file, "public int %sLookback(\n", funcName);
	for(i=0; i<funcInfo->nbOptInput; i++)
	{
		retCode = TA_GetOptInputParameterInfo( funcInfo->handle, i, (void*)&optInputInfo );

        if( retCode != TA_SUCCESS )
        {
           printf( "Error in TA_GetOptInputParameterInfo (%d)\n", retCode );
           return;
        }

		if(optInputInfo->type == TA_OptInput_RealRange)
		{
			fprintf(gOutFunc_Annotation->file, "        double %s", optInputInfo->paramName);
		}
		else if(optInputInfo->type == TA_OptInput_IntegerRange)
		{
			fprintf(gOutFunc_Annotation->file, "        int %s", optInputInfo->paramName);
		}
		else if(optInputInfo->type == TA_OptInput_IntegerList)
		{
			fprintf(gOutFunc_Annotation->file, "        MAType %s", optInputInfo->paramName);
		}
		else
		{
			printf( "Unexpected error 1 (doForEachFunctionAnnotation)\n");
		}
		if (i<funcInfo->nbOptInput-1) fprintf(gOutFunc_Annotation->file, ",\n");
	}
    fprintf(gOutFunc_Annotation->file, ") {\n");
    fprintf(gOutFunc_Annotation->file, "    return super.%sLookback(\n", funcName);
	for(i=0; i<funcInfo->nbOptInput; i++)
	{
		retCode = TA_GetOptInputParameterInfo( funcInfo->handle, i, (void*)&optInputInfo );

        if( retCode != TA_SUCCESS )
        {
           printf( "Error in TA_GetOptInputParameterInfo (%d)\n", retCode );
           return;
        }

		fprintf(gOutFunc_Annotation->file, "        %s", optInputInfo->paramName);
		if (i<funcInfo->nbOptInput-1) fprintf(gOutFunc_Annotation->file, ",\n");
	}    
    fprintf(gOutFunc_Annotation->file, "); }\n\n");

	/*
	 * Annotate Function
	 */
    fprintf(gOutFunc_Annotation->file, "@FuncInfo(\n");
    fprintf(gOutFunc_Annotation->file, "        name  = \"%s\",\n", funcInfo->name);
    fprintf(gOutFunc_Annotation->file, "        group = \"%s\",\n", funcInfo->group);
    fprintf(gOutFunc_Annotation->file, "        flags = %d,\n", funcInfo->flags); /* TODO: should be like: FuncFlags.TA_FUNC_FLG_OVERLAP | FuncFlags.TA_FUNC_FLG_UNST_PER */
    /*fprintf(gOutFunc_Annotation->file, "        hint     = \"%s\",\n", funcInfo->hint);*/
    /*fprintf(gOutFunc_Annotation->file, "        helpFile = \"%s\",\n", funcInfo->helpFile);*/
    fprintf(gOutFunc_Annotation->file, "        nbInput    = %d,\n", funcInfo->nbInput);
    fprintf(gOutFunc_Annotation->file, "        nbOptInput = %d,\n", funcInfo->nbOptInput);
    fprintf(gOutFunc_Annotation->file, "        nbOutput   = %d\n", funcInfo->nbOutput);
    fprintf(gOutFunc_Annotation->file, ")\n");
    fprintf(gOutFunc_Annotation->file, "public RetCode %s(\n", funcName);
    
    fprintf(gOutFunc_Annotation->file, "            int startIdx,\n");
	fprintf(gOutFunc_Annotation->file, "            int endIdx,\n");
    

	/*
	 * Anotate Input parameters
	 */
	for(i=0; i<funcInfo->nbInput; i++)
	{
		char idx = ' ';
		/*if (funcInfo->nbInput>1) idx='0'+i;*/ /* TODO: compile Java code and see if it is necessary to distinguish parameters*/

		retCode = TA_GetInputParameterInfo( funcInfo->handle, i, (void*)&inputInfo);

        if( retCode != TA_SUCCESS )
        {
           printf( "Error in TA_GetInputParameterInfo (%d)\n", retCode );
           return;
        }

		if(inputInfo->type == TA_Input_Price)
		{
			fprintf(gOutFunc_Annotation->file, "            @InputParameterInfo(\n");
	        fprintf(gOutFunc_Annotation->file, "                paramName = \"%s\",\n", inputInfo->paramName);
	        fprintf(gOutFunc_Annotation->file, "                flags     = %d,\n", inputInfo->flags);
		    /*fprintf(gOutFunc_Annotation->file, "                hint     = \"%s\",\n", inputInfo->hint);*/
		    /*fprintf(gOutFunc_Annotation->file, "                helpFile = \"%s\",\n", inputInfo->helpFile);*/
	        fprintf(gOutFunc_Annotation->file, "                type = InputParameterType.TA_Input_Price\n");
	        fprintf(gOutFunc_Annotation->file, "            )\n");

			if(inputInfo->flags & TA_IN_PRICE_OPEN)
			{
				fprintf(gOutFunc_Annotation->file, "            double inOpen%c[],\n",idx);
			}
			if(inputInfo->flags & TA_IN_PRICE_HIGH)
			{
				fprintf(gOutFunc_Annotation->file, "            double inHigh%c[],\n",idx);
			}
			if(inputInfo->flags & TA_IN_PRICE_LOW)
			{
				fprintf(gOutFunc_Annotation->file, "            double inLow%c[],\n",idx);
			}
			if(inputInfo->flags & TA_IN_PRICE_CLOSE)
			{
				fprintf(gOutFunc_Annotation->file, "            double inClose%c[],\n",idx);
			}
			if(inputInfo->flags & TA_IN_PRICE_VOLUME)
			{
				fprintf(gOutFunc_Annotation->file, "            double inVolume%c[],\n",idx);
			}
			if(inputInfo->flags & TA_IN_PRICE_OPENINTEREST)
			{
				fprintf(gOutFunc_Annotation->file, "            double inOpenInterest%c[],\n",idx); /* FIXME: does it exist? */
			}
			if(inputInfo->flags & TA_IN_PRICE_TIMESTAMP)
			{
				fprintf(gOutFunc_Annotation->file, "            long inTimestamp%c[],\n",idx); /* FIXME: does it exist? */
			}
		}
		else
		{
			if(inputInfo->type == TA_Input_Real)
			{
				fprintf(gOutFunc_Annotation->file, "            @InputParameterInfo(\n");
		        fprintf(gOutFunc_Annotation->file, "                paramName = \"%s\",\n", inputInfo->paramName);
		        fprintf(gOutFunc_Annotation->file, "                flags     = %d,\n", inputInfo->flags);
		        fprintf(gOutFunc_Annotation->file, "                type = InputParameterType.TA_Input_Real\n");
		        fprintf(gOutFunc_Annotation->file, "            )\n");
				fprintf(gOutFunc_Annotation->file, "            double %s[],\n", inputInfo->paramName);
			}
			else if(inputInfo->type == TA_Input_Integer)
			{
				fprintf(gOutFunc_Annotation->file, "            @InputParameterInfo(\n");
		        fprintf(gOutFunc_Annotation->file, "                paramName = \"%s\",\n", inputInfo->paramName);
		        fprintf(gOutFunc_Annotation->file, "                flags     = %d,\n", inputInfo->flags);
		        fprintf(gOutFunc_Annotation->file, "                type = InputParameterType.TA_Input_Integer\n");
		        fprintf(gOutFunc_Annotation->file, "            )\n");
				fprintf(gOutFunc_Annotation->file, "            int %s[],\n", inputInfo->paramName);
			}
			else
			{
			    printf( "Unexpected error 2(doForEachFunctionAnnotation)\n"); /*  FIXME: fatal error! */
			}
		}
	}



	/*
	 * Annotate Optional input parameters
	 */
	for(i=0; i<funcInfo->nbOptInput; i++)
	{
		retCode = TA_GetOptInputParameterInfo( funcInfo->handle, i, (void*)&optInputInfo );

        if( retCode != TA_SUCCESS )
        {
           printf( "Error in TA_GetOptInputParameterInfo (%d)\n", retCode );
           return;
        }

		fprintf(gOutFunc_Annotation->file, "            @OptInputParameterInfo(\n");
        fprintf(gOutFunc_Annotation->file, "                paramName    = \"%s\",\n", optInputInfo->paramName);
		fprintf(gOutFunc_Annotation->file, "                displayName  = \"%s\",\n", optInputInfo->displayName);
        fprintf(gOutFunc_Annotation->file, "                flags        = %d,\n", optInputInfo->flags);
	    /*fprintf(gOutFunc_Annotation->file, "                hint     = \"%s\",\n", optInputInfo->hint);*/
	    /*fprintf(gOutFunc_Annotation->file, "                helpFile = \"%s\",\n", optInputInfo->helpFile);*/
		if(optInputInfo->type == TA_OptInput_RealRange)
		{
	        fprintf(gOutFunc_Annotation->file, "                type    = OptInputParameterType.TA_OptInput_RealRange,\n");
	        fprintf(gOutFunc_Annotation->file, "                dataSet = com.tictactec.ta.lib.meta.annotation.RealRange.class\n");
	        fprintf(gOutFunc_Annotation->file, "            )\n");			
			doubleRange= (TA_RealRange*)optInputInfo->dataSet;
			fprintf(gOutFunc_Annotation->file, "            @RealRange(\n");
        	fprintf(gOutFunc_Annotation->file, "                    paramName    = \"%s\",\n", optInputInfo->paramName);
		    fprintf(gOutFunc_Annotation->file, "                    defaultValue = %.5f,\n", (double)optInputInfo->defaultValue);
			fprintf(gOutFunc_Annotation->file, "                    min          = %.5f,\n", doubleRange->min);
			fprintf(gOutFunc_Annotation->file, "                    max          = %.5f,\n", doubleRange->max);
			fprintf(gOutFunc_Annotation->file, "                    precision    = %d,\n", doubleRange->precision);
			fprintf(gOutFunc_Annotation->file, "                    suggested_start     = %.5f,\n", doubleRange->suggested_start);
			fprintf(gOutFunc_Annotation->file, "                    suggested_end       = %.5f,\n", doubleRange->suggested_end);
			fprintf(gOutFunc_Annotation->file, "                    suggested_increment = %.5f\n",  doubleRange->suggested_increment);
			fprintf(gOutFunc_Annotation->file, "            )\n");
			fprintf(gOutFunc_Annotation->file, "            double %s,\n", optInputInfo->paramName);
		}
		else if(optInputInfo->type == TA_OptInput_IntegerRange)
		{
	        fprintf(gOutFunc_Annotation->file, "                type    = OptInputParameterType.TA_OptInput_IntegerRange,\n");
	        fprintf(gOutFunc_Annotation->file, "                dataSet = com.tictactec.ta.lib.meta.annotation.IntegerRange.class\n");
	        fprintf(gOutFunc_Annotation->file, "            )\n");			
			integerRange= (TA_IntegerRange*)optInputInfo->dataSet;
			fprintf(gOutFunc_Annotation->file, "            @IntegerRange(\n");
        	fprintf(gOutFunc_Annotation->file, "                    paramName    = \"%s\",\n", optInputInfo->paramName);
		    fprintf(gOutFunc_Annotation->file, "                    defaultValue = %d,\n", (int)optInputInfo->defaultValue);
			fprintf(gOutFunc_Annotation->file, "                    min          = %d,\n", integerRange->min);
			fprintf(gOutFunc_Annotation->file, "                    max          = %d,\n", integerRange->max);
			fprintf(gOutFunc_Annotation->file, "                    suggested_start     = %d,\n", integerRange->suggested_start);
			fprintf(gOutFunc_Annotation->file, "                    suggested_end       = %d,\n", integerRange->suggested_end);
			fprintf(gOutFunc_Annotation->file, "                    suggested_increment = %d\n",  integerRange->suggested_increment);
			fprintf(gOutFunc_Annotation->file, "            )\n");
			fprintf(gOutFunc_Annotation->file, "            int %s,\n", optInputInfo->paramName);
		}
		else if(optInputInfo->type == TA_OptInput_IntegerList)
		{
	        fprintf(gOutFunc_Annotation->file, "                type    = OptInputParameterType.TA_OptInput_IntegerList,\n");
	        fprintf(gOutFunc_Annotation->file, "                dataSet = com.tictactec.ta.lib.meta.annotation.IntegerList.class\n");
	        fprintf(gOutFunc_Annotation->file, "            )\n");
			intList = (TA_IntegerList*) optInputInfo->dataSet;
			/*if( intList != (TA_IntegerList*) TA_DEF_UI_MA_Method.dataSet )
			 *{
			 *
			 *}
             */
			fprintf(gOutFunc_Annotation->file, "            @IntegerList(\n");
        	fprintf(gOutFunc_Annotation->file, "                    paramName    = \"%s\",\n", optInputInfo->paramName);
		    fprintf(gOutFunc_Annotation->file, "                    defaultValue = %d,\n", (int)optInputInfo->defaultValue);

			if (intList->nbElement>0) {
				fprintf(gOutFunc_Annotation->file, "                    value  = { ");
				for (j=0; j<intList->nbElement-1; j++) {
					fprintf(gOutFunc_Annotation->file, "%d, ", intList->data[j].value);
				}
				fprintf(gOutFunc_Annotation->file, "%d },\n", intList->data[intList->nbElement-1].value);
				fprintf(gOutFunc_Annotation->file, "                    string = { ");
				for (j=0; j<intList->nbElement-1; j++) {
					fprintf(gOutFunc_Annotation->file, "\"%s\", ", intList->data[j].string);
				}
				fprintf(gOutFunc_Annotation->file, "\"%s\" }\n", intList->data[intList->nbElement-1].string);
			}
			
			fprintf(gOutFunc_Annotation->file, "            )\n");
			fprintf(gOutFunc_Annotation->file, "            MAType %s,\n", optInputInfo->paramName);
		}
		else
		{
           printf( "Unexpected error 2(doForEachFunctionAnnotation)\n"); /*  FIXME: fatal error! */
		}
	}

	fprintf(gOutFunc_Annotation->file, "            MInteger     outBegIdx,\n");
	fprintf(gOutFunc_Annotation->file, "            MInteger     outNBElement,\n");


	/*
	 * Annotate Output parameters
	 */
	for(i=0; i<funcInfo->nbOutput; i++)
	{
		retCode = TA_GetOutputParameterInfo( funcInfo->handle, i, (void*)&outputInfo );

        if( retCode != TA_SUCCESS )
        {
           printf( "Error in TA_GetOutputParameterInfo (%d)\n", retCode );
           return;
        }

		if(outputInfo->type == TA_Output_Integer)
		{
			fprintf(gOutFunc_Annotation->file, "            @OutputParameterInfo(\n");
	        fprintf(gOutFunc_Annotation->file, "                paramName = \"%s\",\n", outputInfo->paramName);
	        fprintf(gOutFunc_Annotation->file, "                flags     = %d,\n", outputInfo->flags);
		    /*fprintf(gOutFunc_Annotation->file, "                hint     = \"%s\",\n", outputInfo->hint);*/
		    /*fprintf(gOutFunc_Annotation->file, "                helpFile = \"%s\",\n", outputInfo->helpFile);*/
	        fprintf(gOutFunc_Annotation->file, "                type = OutputParameterType.TA_Output_Integer\n");
	        fprintf(gOutFunc_Annotation->file, "            )\n");
			fprintf(gOutFunc_Annotation->file, "            int %s[]\n", outputInfo->paramName);
		}
		else if(outputInfo->type == TA_Output_Real)
		{
			fprintf(gOutFunc_Annotation->file, "            @OutputParameterInfo(\n");
	        fprintf(gOutFunc_Annotation->file, "                paramName = \"%s\",\n", outputInfo->paramName);
	        fprintf(gOutFunc_Annotation->file, "                flags     = %d,\n", outputInfo->flags);
	        fprintf(gOutFunc_Annotation->file, "                type = OutputParameterType.TA_Output_Real\n");
	        fprintf(gOutFunc_Annotation->file, "            )\n");
			fprintf(gOutFunc_Annotation->file, "            double %s[]", outputInfo->paramName);
		}
		else
		{
				printf( "Unexpected error 3(doForEachFunctionAnnotation)\n"); /*  FIXME: fatal error!*/
		}

		if (i<funcInfo->nbOutput-1) {
			fprintf(gOutFunc_Annotation->file, ",");
		}
		fprintf(gOutFunc_Annotation->file, "\n");

	}

    fprintf(gOutFunc_Annotation->file, ") {\n");
    fprintf(gOutFunc_Annotation->file, "    return super.%s (\n", funcName);

	fprintf(gOutFunc_Annotation->file, "        startIdx,\n");
	fprintf(gOutFunc_Annotation->file, "        endIdx,\n");
    
	for(i=0; i<funcInfo->nbInput; i++)
	{
		retCode = TA_GetInputParameterInfo(funcInfo->handle, i, (void*)&inputInfo);

        if( retCode != TA_SUCCESS )
        {
           printf( "Error in TA_GetInputParameterInfo (%d)\n", retCode );
           return;
        }

		if(inputInfo->type == TA_Input_Price)
		{
			char idx = ' ';
			/*if (funcInfo->nbInput>1) idx='0'+i;*/ /* TODO: compile Java code and see if it is necessary to distinguish parameters */
		
			if(inputInfo->flags & TA_IN_PRICE_OPEN)
			{
				fprintf(gOutFunc_Annotation->file, "        inOpen%c,\n", idx);
			}
			if(inputInfo->flags & TA_IN_PRICE_HIGH)
			{
				fprintf(gOutFunc_Annotation->file, "        inHigh%c,\n", idx);
			}
			if(inputInfo->flags & TA_IN_PRICE_LOW)
			{
				fprintf(gOutFunc_Annotation->file, "        inLow%c,\n", idx);
			}
			if(inputInfo->flags & TA_IN_PRICE_CLOSE)
			{
				fprintf(gOutFunc_Annotation->file, "        inClose%c,\n", idx);
			}
			if(inputInfo->flags & TA_IN_PRICE_VOLUME)
			{
				fprintf(gOutFunc_Annotation->file, "        inVolume%c,\n", idx);
			}
			if(inputInfo->flags & TA_IN_PRICE_OPENINTEREST)
			{
				fprintf(gOutFunc_Annotation->file, "        inOpenInterest%c,\n", idx); /*  FIXME: does it exist?*/
			}
			if(inputInfo->flags & TA_IN_PRICE_TIMESTAMP)
			{
				fprintf(gOutFunc_Annotation->file, "        inTimestamp%c,\n", idx); /* FIXME: does it exist? */
			}
		} else {
			fprintf(gOutFunc_Annotation->file, "        %s,\n", inputInfo->paramName);
		}
	}
	
	for(i=0; i<funcInfo->nbOptInput; i++)
	{
		retCode = TA_GetOptInputParameterInfo(funcInfo->handle, i, (void*)&optInputInfo);

        if( retCode != TA_SUCCESS )
        {
           printf( "Error in TA_GetOptInputParameterInfo (%d)\n", retCode );
           return;
        }

        fprintf(gOutFunc_Annotation->file, "        %s,\n", optInputInfo->paramName);
	}

	fprintf(gOutFunc_Annotation->file, "        outBegIdx,\n");
	fprintf(gOutFunc_Annotation->file, "        outNBElement,\n");

	for(i=0; i<funcInfo->nbOutput-1; i++)
	{
		retCode = TA_GetOutputParameterInfo(funcInfo->handle, i, (void*)&outputInfo);

        if( retCode != TA_SUCCESS )
        {
           printf( "Error in TA_GetOutputParameterInfo (%d)\n", retCode );
           return;
        }

        fprintf(gOutFunc_Annotation->file, "        %s,\n", outputInfo->paramName);
	}

	retCode = TA_GetOutputParameterInfo(funcInfo->handle, funcInfo->nbOutput-1, (void*)&outputInfo);

    if( retCode != TA_SUCCESS )
    {
       printf( "Error in TA_GetOutputParameterInfo (%d)\n", retCode );
       return;
    }

    fprintf(gOutFunc_Annotation->file, "        %s\n", outputInfo->paramName);

    fprintf(gOutFunc_Annotation->file, "); }\n\n\n");
}
#ifdef TA_LIB_PRO
      /* Section for code distributed with TA-Lib Pro only. */
#endif

