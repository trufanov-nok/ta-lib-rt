#!/usr/perl/bin

# The following relative directory structure is assumed:
#   <Your Directory>/tools
#   <Your Directory>/ta-lib/*
#   <Your Directory>/ta-lib/c
#   <Your Directory>/ta-lib/c/src
#   etc...
#
# You must run this script from the ta-lib/tools directory.
# BTW, this is the same as the SVN repository structure.

# This script get the latest source from SVN and build from scratch all 
# the files that are part of a release.

use Cwd;
use File::DosGlob 'glob';
use myUtil;
use userSetup;

sub Main
{   
   $versionSuffix = &libversion();
   print "Packaging ".$versionSuffix."\n";

   open(OLD_STDERR,">&STDERR") or die "Failed to save STDERR";
   open(OLD_STDOUT,">&STDOUT") or die "Failed to save STDOUT";
   open(STDOUT, ">".&getLogdir."stdout_release_win32.txt" ) or die;
   open(STDERR, ">".&getLogdir."stderr_release_win32.txt" ) or die;
   
   $root_dir = "..\\";

   if( $ARGV[0] eq "-fast" )
   {
	print "Fast Option Set: Skipping clean-up and some tests\n";
	$fastOption = 1;
   }
   else
   {
        $fastOption = 0;
   }
     
   # Get a SVN copy locally
   $a = "svn export --force ".&getSVNRoot." .\\ta-lib";
   execProg( &getTempdir, $a );

   ###########################################################################
   # Package ta_lib
   ###########################################################################
   # Make the 'src' package
   # No more SRC package. Developer must use SVN instead.
   # 
   # $packageName = "ta-lib-".$versionSuffix."-src.zip";
   # $a = "zip -r -o -q ..\\".$packageName." ta-lib\\*.*";
   # execProg( $root_dir."release\\build\\", $a );

   # Remove the Excel/Perl/.NET binaries from the package.
   # These binaries are coming from the SVN import.
   # removeBinFromPackage( $root_dir, $packageName );

   # Make the MSVC package
   my $keepTheLib =1;
   my $skipAllTests = $fastOption;
   testMSVC(&getTempdir."ta-lib\\", "cdr", $fastOption,
	    $keepTheLib, &getLogdir, $skipAllTests );

   testMSVC(&getTempdir."ta-lib\\", "csd", $fastOption,
	    $keepTheLib, &getLogdir, $skipAllTests );
    
   testMSVC(&getTempdir."ta-lib\\", "cmd", $fastOption,
	    $keepTheLib, &getLogdir, $skipAllTests );
    
   testMSVC(&getTempdir."ta-lib\\", "cmr", $fastOption,
	    $keepTheLib, &getLogdir, $skipAllTests );
    
   testMSVC(&getTempdir."ta-lib\\", "cdd", $fastOption,
	    $keepTheLib, &getLogdir, $skipAllTests );
    
   testMSVC(&getTempdir."ta-lib\\", "csr", $fastOption,
	    $keepTheLib, &getLogdir, $skipAllTests );
    
   removeAllTempFile(&getTempdir."ta-lib\\");

   $packageName = "ta-lib-".$versionSuffix."-msvc.zip";
   
   $a = "zip a -tzip -r ".&getReleasedir.$packageName." ta-lib\\*";
   execProg( &getTempdir, $a );

   removeAllBinFile(&getTempdir."ta-lib\\", 0 );

   # Make the Borland package (1 means 'keep the lib')
   testBorland(&getTempdir."ta-lib\\", "csd", $fastOption,
	       $keepTheLib, &getLogdir, $skipAllTests );
       
   testBorland(&getTempdir."ta-lib\\", "cmd", $fastOption,
	       $keepTheLib, &getLogdir, $skipAllTests );
       
   testBorland(&getTempdir."ta-lib\\", "cmr", $fastOption,
	       $keepTheLib, &getLogdir, $skipAllTests );
       
   testBorland(&getTempdir."ta-lib\\", "csr", $fastOption,
	       $keepTheLib, &getLogdir, $skipAllTests );
       
   removeAllTempFile(&getTempdir."ta-lib\\");

   $packageName = "ta-lib-".$versionSuffix."-borl.zip";
 
   $a = "zip a -tzip -r ".&getReleasedir.$packageName." ta-lib\\*";
   execProg( &getTempdir, $a );

   execProg( &getTempdir."ta-lib\\", "copy CHANGELOG.TXT ".&getReleasedir );
   execProg( &getTempdir."ta-lib\\", "copy HISTORY.TXT ".&getReleasedir );

   print "\n* Packaging completed with Success *\n";
   close STDOUT;
   close STDERR;
   open(STDOUT,">&OLD_STDOUT") or warn "Failed to restore STDOUT";
   open(STDERR,">&OLD_STDERR") or warn "Failed to restore STDERR";
   print "\n* Packaging completed with Success *\n";
}

&Main;
