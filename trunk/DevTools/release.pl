#!/usr/perl/bin

# This script get the latest source from CVS and build from scratch all 
# the files that are part of a release.

# You will need CVS access and modify the following.
# On windows you can use PuTTY pageant for handling the password.
$root_cvs = ":ext:fortier\@cvs.sourceforge.net:/cvsroot/ta-lib";

use Cwd;
use File::DosGlob 'glob';
use myUtil;

sub Main
{   
   $versionSuffix = &libversion();
   print "Packaging ".$versionSuffix."\n";

   $root_dir = "p:\\";

   if( $ARGV[0] eq "-fast" )
   {
	print "Fast Option Set: Skipping clean-up and some tests\n";
	$fastOption = 1;
   }
   
   # Clean-up packaging directory
   if( $fastOption eq 1 )
   {
      removeAllTempFile( $root_dir."release\\build\\ta-lib\\" );
      removeAllBinFile ( $root_dir."release\\build\\ta-lib\\", 0 );
      removeAllBinFile ( $root_dir."release\\build\\ta-unixodbc\\", 0 );
      removeAllTempFile( $root_dir."release\\build\\ta-unixodbc\\" );
      removeAllBinFile ( $root_dir."release\\build\\ta-mysql\\", 0 );
      removeAllTempFile( $root_dir."release\\build\\ta-mysql\\" );
   }
   else
   {
      removeRelease( $root_dir );

      # Copy CVS locally
      $a = "cvs -z3 -q -d".$root_cvs." export -Dtomorrow ta-mysql";
      execProgForce( $root_dir."release\\build\\", $a );
      $a = "cvs -z3 -q -d".$root_cvs." export -Dtomorrow ta-lib";
      execProg( $root_dir."release\\build\\", $a );
   }

   ###########################################################################
   # Package ta_mysql
   ###########################################################################
   $ta_mysql_dir = $root_dir."release\\build\\ta-mysql\\";

   buildMSVC($ta_mysql_dir, "cdr", 1, $root_dir."release\\log\\", "ta_mysql" );
   buildMSVC($ta_mysql_dir, "cdd", 1, $root_dir."release\\log\\", "ta_mysql" );
   removeAllTempFile($ta_mysql_dir);

   $a = "zip -r -o -q ".$root_dir."release\\ta-mysql-".$versionSuffix."-msvc.zip ta-mysql\\*.*";
   execProg( $root_dir."release\\build\\", $a );
   removeAllBinFile($ta_mysql_dir, 0 );

   #buildBorland($ta_mysql_dir, "cdr", 1, $root_dir."release\\log\\", "ta_mysql" );
   #buildBorland($ta_mysql_dir, "cdd", 1, $root_dir."release\\log\\", "ta_mysql" );
   #removeAllTempFile($ta_mysql_dir);
   #$a = "zip -r -o -q ".$root_dir."release\\ta-mysql-".$versionSuffix."-borl.zip ta-mysql\\*.*";
   #execProg( $ta_mysql_dir, $a );
   #removeAllBinFile($ta_mysql_dir, 0 );
   
   ###########################################################################
   # Package ta_lib
   ###########################################################################
   # Make the 'src' package
   $a = "zip -r -o -q ".$root_dir."release\\ta-lib-".$versionSuffix."-src.zip ta-lib\\*.*";
   execProg( $root_dir."release\\build\\", $a );

   # Make the MSVC package
   my $keepTheLib =1;
   my $skipAllTests = $fastOption;
   testMSVC($root_dir."release\\build\\ta-lib\\", "cdr", $fastOption,
	    $keepTheLib, $root_dir."release\\log\\", $skipAllTests );
    
   testMSVC($root_dir."release\\build\\ta-lib\\", "csd", $fastOption,
	    $keepTheLib, $root_dir."release\\log\\", $skipAllTests );
    
   testMSVC($root_dir."release\\build\\ta-lib\\", "cmd", $fastOption,
	    $keepTheLib, $root_dir."release\\log\\", $skipAllTests );
    
   testMSVC($root_dir."release\\build\\ta-lib\\", "cmr", $fastOption,
	    $keepTheLib, $root_dir."release\\log\\", $skipAllTests );
    
   testMSVC($root_dir."release\\build\\ta-lib\\", "cdd", $fastOption,
	    $keepTheLib, $root_dir."release\\log\\", $skipAllTests );
    
   testMSVC($root_dir."release\\build\\ta-lib\\", "csr", $fastOption,
	    $keepTheLib, $root_dir."release\\log\\", $skipAllTests );
    
   removeAllTempFile($root_dir."release\\build\\ta-lib\\");

   $a = "zip -r -o -q ".$root_dir."release\\ta-lib-".$versionSuffix."-msvc.zip ta-lib\\*.*";
   execProg( $root_dir."release\\build\\", $a );

   # Keep a copy of WebFetch.exe, ta_yahoo.exe and ta_sql.exe
   execProg( $root_dir."release\\build\\ta-lib\\C\\BIN\\", "copy ta_yahoo.exe ".$root_dir."release" );
   execProg( $root_dir."release\\build\\ta-lib\\C\\BIN\\", "copy WebFetch.exe ".$root_dir."release" );
   execProg( $root_dir."release\\build\\ta-lib\\C\\BIN\\", "copy ta_sql.exe ".$root_dir."release" );

   removeAllBinFile($root_dir."release\\build\\ta-lib\\", 0 );

   # Make the Borland package (1 means 'keep the lib')
   testBorland($root_dir."release\\build\\ta-lib\\", "csd", $fastOption,
	       $keepTheLib, $root_dir."release\\log\\", $skipAllTests );
       
   testBorland($root_dir."release\\build\\ta-lib\\", "cmd", $fastOption,
	       $keepTheLib, $root_dir."release\\log\\", $skipAllTests );
       
   testBorland($root_dir."release\\build\\ta-lib\\", "cmr", $fastOption,
	       $keepTheLib, $root_dir."release\\log\\", $skipAllTests );
       
   testBorland($root_dir."release\\build\\ta-lib\\", "csr", $fastOption,
	       $keepTheLib, $root_dir."release\\log\\", $skipAllTests );
       
   removeAllTempFile($root_dir."release\\build\\ta-lib\\");

   $a = "zip -r -o -q ".$root_dir."release\\ta-lib-".$versionSuffix."-borl.zip ta-lib\\*.*";
   execProg( $root_dir."release\\build\\", $a );

   execProg( $root_dir."release\\build\\ta-lib\\", "copy CHANGELOG.TXT ".$root_dir."release" );
   execProg( $root_dir."release\\build\\ta-lib\\", "copy HISTORY.TXT ".$root_dir."release" );

   print "\n* Packaging completed with Success *\n";
}

&Main;
