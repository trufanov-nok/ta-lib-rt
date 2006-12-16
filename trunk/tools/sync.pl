#!/usr/perl/bin

# This script is used to clean-up my working SVN view.
# 
# It removes unecessary files, temporary and backup files.
#
# The script also verifies that some SVN properties are
# correctly set (base on the file extension).
use File::DosGlob 'glob';
use myUtil;

sub Main
{   
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

   # Clean-up files that would be unexpected. We wish to keep the 
   # development directory to contains only the files to rebuild 
   # from scratch.
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

   # No Media files expected
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

   # Text files needs a SVN property to be set.
   # This property allows proper end of line conversion
   # between UNIX/DOS.
   
   makePortableEOL( '..\ta-lib\*.xml' );
   makePortableEOL( '..\ta-lib\*.xsd' );
   
   makePortableEOL( '..\ta-lib\c\make\*\*\*\Makefile' );
   makePortableEOL( '..\ta-lib\c\make\*\*\*\*\Makefile' );

   makePortableEOL( '..\ta-lib\c\*.c' );
   makePortableEOL( '..\ta-lib\c\*\*.c' );
   makePortableEOL( '..\ta-lib\c\*\*\*.c' );
   makePortableEOL( '..\ta-lib\c\*\*\*\*.c' );

   makePortableEOL( '..\ta-lib\c\*.h' );
   makePortableEOL( '..\ta-lib\c\*\*.h' );
   makePortableEOL( '..\ta-lib\c\*\*\*.h' );
   makePortableEOL( '..\ta-lib\c\*\*\*\*.h' );

   makePortableEOL( '..\ta-lib\c\*.am' );
   makePortableEOL( '..\ta-lib\c\*\*.am' );
   makePortableEOL( '..\ta-lib\c\*\*\*.am' );
   makePortableEOL( '..\ta-lib\c\*\*\*\*.am' );

   # Some path goes 6 directory deep under ta-lib
   # in the java directory.
   makePortableEOL( '..\ta-lib\*.TXT' );
   makePortableEOL( '..\ta-lib\*\*\*.TXT' );
   makePortableEOL( '..\ta-lib\*\*\*\*.TXT' );
   makePortableEOL( '..\ta-lib\*\*\*\*\*.TXT' );
   makePortableEOL( '..\ta-lib\*\*\*\*\*\*.TXT' );
   makePortableEOL( '..\ta-lib\*\*\*\*\*\*\*.TXT' );
   
   makePortableEOL( '..\ta-lib\*\*.java' );
   makePortableEOL( '..\ta-lib\*\*\*\*.java' );
   makePortableEOL( '..\ta-lib\*\*\*\*\*.java' );
   makePortableEOL( '..\ta-lib\*\*\*\*\*\*.java' );
   makePortableEOL( '..\ta-lib\*\*\*\*\*\*\*.java' );   
}

# Verify that SVN properties are set as expected.
sub makePortableEOL
{
   @files = glob $_[0];

   foreach $z (@files)
   {
      # print "[".$z."]\n";
      $cmd = "svn propset --quiet svn:eol-style native ".$z;
      system( $cmd );
   }
}

&Main;
