/* This program simply output the string hard coded in the library */
#include <stdio.h>

#ifdef _WIN32
   #include "..\ta-lib\c\src\ta_common\ta_version.c"
#else
   #include "/mnt/hgfs/Shared/ta-lib/c/src/ta_common/ta_version.c"
#endif

int main( int argc, char *argv[] )
{
   (void)argc;
   (void)argv;

   printf( TA_GetVersionString() );

   return 0;
}

