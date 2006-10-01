#!/usr/perl/bin

# I like to maintain all my files in unix format (even on Win32).
# This allows me to share easily my Win32 directories with a Linux
# guess running on the same machine (using VMWare).
#
# This script perform this "to Unix" conversion. At the same time,
# verify to make sure that no unexpected binary files are left in
# the development directory.
#
use File::DosGlob 'glob';
use myUtil;

sub Main
{
   # Bring all text file to the unix format.
   cleanupFile( '..\ta-lib\*.txt' );
   cleanupFile( '..\ta-lib\*\*.txt' );
   cleanupFile( '..\ta-lib\*\*\*.txt' );
   cleanupFile( '..\ta-lib\*\*\*\*.txt' );

   cleanupFile( '..\ta-lib\c\src\ta_abstract\templates\*.*.template' );
   
   cleanupFile( '..\ta-lib\c\src\*.c' );
   cleanupFile( '..\ta-lib\c\src\*\*.c' );

   cleanupFile( '..\ta-lib\c\src\*.h' );
   cleanupFile( '..\ta-lib\c\src\*\*.h' );

   cleanupFile( '..\ta-lib\c\README' );
   cleanupFile( '..\ta-lib\c\*\README' );
   cleanupFile( '..\ta-lib\c\*\*\README' );

   # Remove temporary and backup files.
   removeFile( '..\ta-lib\c\temp\*.*' );
   removeFile( '..\ta-lib\c\temp\*\*.*' );

   removeFile( '..\ta-lib\*\*.bak' );
   removeFile( '..\ta-lib\*\*\*.bak' );
   removeFile( '..\ta-lib\*\*\*\*.bak' );

   removeFile( '..\ta-lib\*\*.~*' );
   removeFile( '..\ta-lib\*\*\*.~*' );
   removeFile( '..\ta-lib\*\*\*\*.~*' );

   removeFile( '..\ta-lib\*\*.*~' );
   removeFile( '..\ta-lib\*\*\*.*~' );
   removeFile( '..\ta-lib\*\*\*\*.*~' );

   removeFile( '..\ta-lib\*\.*.swp' );
   removeFile( '..\ta-lib\*\*\.*.swp' );
   removeFile( '..\ta-lib\*\*\*\.*.swp' );

   # Clean-up MSVC project directory.
   removeFile( '..\ta-lib\c\ide\msvc\*\*.ncb' );
   removeFile( '..\ta-lib\c\ide\msvc\*\*.opt' );
   removeFile( '..\ta-lib\c\ide\msvc\*\*\*.ncb' );
   removeFile( '..\ta-lib\c\ide\msvc\*\*\*.opt' );
   removeFile( '..\ta-lib\c\ide\msvc\*\*\*.plg' );

   removeFile( '..\ta-lib\excel\src\*.ncb' );
   removeFile( '..\ta-lib\excel\src\*.opt' );
   removeFile( '..\ta-lib\excel\src\*.plg' );

   removeFile( '..\ta-lib\excel\src\xlw_for_talib\*.ncb' );
   removeFile( '..\ta-lib\excel\src\xlw_for_talib\*.opt' );
   removeFile( '..\ta-lib\excel\src\xlw_for_talib\*.plg' );

   # Clean-up any binaries files that I can think of. We
   # wish to keep the development directory to contains 
   # only the files to rebuild from scratch.
   #
   # (the .NET dll and excel xll files are exceptions).
   #  
   removeFile( '..\ta-lib\*\.*.lib' );
   removeFile( '..\ta-lib\*\*\.*.lib' );
   removeFile( '..\ta-lib\*\*\*\.*.lib' );

   removeFile( '..\ta-lib\*\.*.obj' );
   removeFile( '..\ta-lib\*\*\.*.obj' );
   removeFile( '..\ta-lib\*\*\*\.*.obj' );

   removeFile( '..\ta-lib\*\.*.exe' );
   removeFile( '..\ta-lib\*\*\.*.exe' );
   removeFile( '..\ta-lib\*\*\*\.*.exe' );

   removeFile( '..\ta-lib\*\.*.dat' );
   removeFile( '..\ta-lib\*\*\.*.dat' );
   removeFile( '..\ta-lib\*\*\*\.*.dat' );

   removeFile( '..\ta-lib\*\.*.zip' );
   removeFile( '..\ta-lib\*\*\.*.zip' );
   removeFile( '..\ta-lib\*\*\*\.*.zip' );

   removeFile( '..\ta-lib\*\.*.rar' );
   removeFile( '..\ta-lib\*\*\.*.rar' );
   removeFile( '..\ta-lib\*\*\*\.*.rar' );
   removeFile( '..\ta-lib\*\*\*\*\.*.rar' );

   removeFile( '..\ta-lib\*\.*.jpg' );
   removeFile( '..\ta-lib\*\*\.*.jpg' );
   removeFile( '..\ta-lib\*\*\*\.*.jpg' );
   removeFile( '..\ta-lib\*\*\*\*\.*.jpg' );

   removeFile( '..\ta-lib\*\.*.mpg' );
   removeFile( '..\ta-lib\*\*\.*.mpg' );
   removeFile( '..\ta-lib\*\*\*\.*.mpg' );
   removeFile( '..\ta-lib\*\*\*\*\.*.mpg' );

   removeFile( '..\ta-lib\*\.*.jpeg' );
   removeFile( '..\ta-lib\*\*\.*.jpeg' );
   removeFile( '..\ta-lib\*\*\*\.*.jpeg' );
   removeFile( '..\ta-lib\*\*\*\*\.*.jpeg' );

   removeFile( '..\ta-lib\*\.*.mpeg' );
   removeFile( '..\ta-lib\*\*\.*.mpeg' );
   removeFile( '..\ta-lib\*\*\*\.*.mpeg' );
   removeFile( '..\ta-lib\*\*\*\*\.*.mpeg' );

   removeFile( '..\ta-lib\*\.*.gif' );
   removeFile( '..\ta-lib\*\*\.*.gif' );
   removeFile( '..\ta-lib\*\*\*\.*.gif' );
   removeFile( '..\ta-lib\*\*\*\*\.*.gif' );

   removeFile( '..\ta-lib\*\.*.wmv' );
   removeFile( '..\ta-lib\*\*\.*.wmv' );
   removeFile( '..\ta-lib\*\*\*\.*.wmv' );
   removeFile( '..\ta-lib\*\*\*\*\.*.wmv' );

   removeFile( '..\ta-lib\*\.*.asx' );
   removeFile( '..\ta-lib\*\*\.*.asx' );
   removeFile( '..\ta-lib\*\*\*\.*.asx' );
   removeFile( '..\ta-lib\*\*\*\*\.*.asx' );
}

sub cleanupFile
{
   @files = glob $_[0];

   foreach $z (@files)
   {
      $cmd = "./UDDU/dos2unix/Release/dos2unix ".$z;

      if(    ($z =~ /ta_regtest\/sampling/)
          or ($z =~ /\.svn/) ) 
      { 
          print "Skipping ".$z."\n";
      }
      else
      {
         system( $cmd );
      }
   }
}

&Main;
