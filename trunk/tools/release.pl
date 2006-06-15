#!/usr/perl/bin

# This script get the latest source from SVN and build from scratch all 
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

   $root_dir = "..\\";

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
   }
   else
   {
      removeRelease( $root_dir );

      # Get a clean copy locally
      $a = "svn export https://svn.sourceforge.net/svnroot/ta-lib/trunk/ta-lib .\\ta-lib";
      execProg( $root_dir."release\\build\\", $a );
   }

   ###########################################################################
   # Package ta_lib
   ###########################################################################
   # Make the 'src' package
   $packageName = "ta-lib-".$versionSuffix."-src.zip";
   $a = "zip -r -o -q ..\\".$packageName." ta-lib\\*.*";
   execProg( $root_dir."release\\build\\", $a );

   # Remove the Excel/Perl/.NET binaries from the package.
   # These binaries were not build, they are coming from 
   # the CVS import.
   removeBinFromPackage( $root_dir, $packageName );

   # Log dire relative to the makefiles.
   my $log_dir = "..\\..\\..\\..\\..\\..\\..\\..\\release\\log\\";
   
   # Make the MSVC package
   my $keepTheLib =1;
   my $skipAllTests = $fastOption;
   testMSVC($root_dir."release\\build\\ta-lib\\", "cdr", $fastOption,
	    $keepTheLib, $log_dir, $skipAllTests );
    
   testMSVC($root_dir."release\\build\\ta-lib\\", "csd", $fastOption,
	    $keepTheLib, $log_dir, $skipAllTests );
    
   testMSVC($root_dir."release\\build\\ta-lib\\", "cmd", $fastOption,
	    $keepTheLib, $log_dir, $skipAllTests );
    
   testMSVC($root_dir."release\\build\\ta-lib\\", "cmr", $fastOption,
	    $keepTheLib, $log_dir, $skipAllTests );
    
   testMSVC($root_dir."release\\build\\ta-lib\\", "cdd", $fastOption,
	    $keepTheLib, $log_dir, $skipAllTests );
    
   testMSVC($root_dir."release\\build\\ta-lib\\", "csr", $fastOption,
	    $keepTheLib, $log_dir, $skipAllTests );
    
   removeAllTempFile($root_dir."release\\build\\ta-lib\\");

   $packageName = "ta-lib-".$versionSuffix."-msvc.zip";
   
   $a = "zip -r -o -q ..\\".$packageName." ta-lib\\*.*";
   execProg( $root_dir."release\\build\\", $a );

   removeAllBinFile($root_dir."release\\build\\ta-lib\\", 0 );

   # Make the Borland package (1 means 'keep the lib')
   testBorland($root_dir."release\\build\\ta-lib\\", "csd", $fastOption,
	       $keepTheLib, $log_dir, $skipAllTests );
       
   testBorland($root_dir."release\\build\\ta-lib\\", "cmd", $fastOption,
	       $keepTheLib, $log_dir, $skipAllTests );
       
   testBorland($root_dir."release\\build\\ta-lib\\", "cmr", $fastOption,
	       $keepTheLib, $log_dir, $skipAllTests );
       
   testBorland($root_dir."release\\build\\ta-lib\\", "csr", $fastOption,
	       $keepTheLib, $log_dir, $skipAllTests );
       
   removeAllTempFile($root_dir."release\\build\\ta-lib\\");

   $packageName = "ta-lib-".$versionSuffix."-borl.zip";
   

   $a = "zip -r -o -q ..\\".$packageName." ta-lib\\*.*";
   execProg( $root_dir."release\\build\\", $a );

   execProg( $root_dir."release\\build\\ta-lib\\", "copy CHANGELOG.TXT ..\\.." );
   execProg( $root_dir."release\\build\\ta-lib\\", "copy HISTORY.TXT ..\\.." );

   print "\n* Packaging completed with Success *\n";
}

&Main;
