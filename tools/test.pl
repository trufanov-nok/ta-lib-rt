#!/usr/perl/bin

# This script performs an extensive number of tests for TA-Lib.
# 
# It builds multiple variant of the library and run the ta_regtest executable
# or script for each.
#
# This script is for Win32, another one called "test_unix.pl" is intended
# for Linux.
# 
# This script is intended for maintainers of TA-Lib, not for the
# end-user of TA-Lib.

use Cwd;
use File::DosGlob 'glob';
use myUtil;

sub Main
{
   $versionSuffix = &libversion();
   $fastOption    = 0;

   print "Testing ".$versionSuffix."\n";

   $root_dir = "..\\";

   if( $ARGV[0] eq "-fast" )
   {
	print "Fast Option Set: Skipping clean-up and some tests\n";
	$fastOption = 1;
   }
   elsif( $ARGV[0] eq "-clean" )
   {
      print "Just cleaning up\n";
      system( "perl sync.pl" );
      removeAllTempFile($root_dir."ta-lib\\");
      removeAllBinFile($root_dir."ta-lib\\", 0 );
      removeRelease($root_dir);
      exit(0);        
   }
   else
   {
     removeRelease($root_dir);   
   }

   open(STDOUT, ">".$root_dir."\\release\\log\\stdout.txt" ) or die;
   open(STDERR, ">".$root_dir."\\release\\log\\stderr.txt" ) or die;

   if( $fastOption eq 0 )
   {
      removeAllTempFile($root_dir."ta-lib\\");
      removeAllBinFile($root_dir."ta-lib\\", 0);

      # Generate TA-Lib WIN32 Makefiles
      $dir = cwd;
      chdir( $root_dir."ta-lib\\c\\make\\gen_make" );
      system( "perl gen_make.pl" );
      chdir( $dir );

      # Bring all text file to the unix format.
      system( "perl sync.pl" );
   }

   $testOutDir = "..\\..\\..\\..\\..\\..\\";
   # Test one build of each compiler for TA-Lib. Allows to detect early on compile errors.
   # Remaining library variant are tested later.
   testMSVC($root_dir."ta-lib\\", "cdr", $fastOption, 0, $testOutDir."release\\log\\", 0 );
   testBorland($root_dir."ta-lib\\", "cmd", $fastOption, 0, $testOutDir."release\\log\\", 0 );
   
   # Test remaining MSVC variant
   if( $fastOption eq 0 )
   {
      # Compile and test all remaining variant.
      testMSVC($root_dir."ta-lib\\", "csd", $fastOption, 0, $testOutDir."release\\log\\", 0 );
      testMSVC($root_dir."ta-lib\\", "cmd", $fastOption, 0, $testOutDir."release\\log\\", 0 );
      testMSVC($root_dir."ta-lib\\", "csr", $fastOption, 0, $testOutDir."release\\log\\", 0 );
      testMSVC($root_dir."ta-lib\\", "cdd", $fastOption, 0, $testOutDir."release\\log\\", 0 );
      testMSVC($root_dir."ta-lib\\", "cmr", $fastOption, 0, $testOutDir."release\\log\\", 0 );
   }
   else
   {
      # Just compile a few variant.
      testMSVC($root_dir."ta-lib\\", "cmr", $fastOption, 0, $testOutDir."release\\log\\", 1 );
      testMSVC($root_dir."ta-lib\\", "csd", $fastOption, 0, $testOutDir."release\\log\\", 1 );
   }

   # Test remaining Borland variant
   if( $fastOption eq 0 )
   {
      # Compile and test all remaining variant.
      testBorland($root_dir."ta-lib\\", "csd", $fastOption, 0, $testOutDir."release\\log\\", 0 );
      testBorland($root_dir."ta-lib\\", "cmr", $fastOption, 0, $testOutDir."release\\log\\", 0 );
      testBorland($root_dir."ta-lib\\", "csr", $fastOption, 0, $testOutDir."release\\log\\", 0 );
   }
   else
   {
      # Just compile a variant.
      testBorland($root_dir."ta-lib\\", "csr", $fastOption, 0, $testOutDir."release\\log\\", 1 );
   }

   # Check for warnings.
   execProgForce( $root_dir."release\\log",  'find "arning" *.txt' );

   # Clean-up everything because usually the test are followed
   # with a sync with the remote CVS repository.
   removeAllBinFile( $root_dir."ta-lib\\", 0 );
   removeAllTempFile( $root_dir."ta-lib\\" );

   print( "\n* Testing Completed with Success *\n" );
}

&Main;
