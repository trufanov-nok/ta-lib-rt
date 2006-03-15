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

   $root_dir = "p:\\";

   if( $ARGV[0] eq "-fast" )
   {
	print "Fast Option Set: Skipping clean-up and some tests\n";
	$fastOption = 1;
   }
   elsif( $ARGV[0] eq "-clean" )
   {
      print "Just cleaning up\n";
      system( "perl sync.pl" );
      removeAllTempFile("..\\ta-lib\\");
      removeAllBinFile("..\\ta-lib\\", 0 );
      removeAllBinFile( "..\\ta-unixodbc\\", 0 );
      removeAllTempFile( "..\\ta-unixodbc\\" );
      removeAllBinFile( "..\\ta-mysql\\", 0 );
      removeAllTempFile( "..\\ta-mysql\\" );
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
      removeAllTempFile("..\\ta-lib\\");
      removeAllBinFile("..\\ta-lib\\", 0);
      removeAllBinFile( "..\\ta-unixodbc\\", 0 );
      removeAllTempFile( "..\\ta-unixodbc\\" );
      removeAllBinFile( "..\\ta-mysql\\", 0 );
      removeAllTempFile( "..\\ta-mysql\\" );

      # Generate TA-Lib WIN32 Makefiles
      $dir = cwd;
      chdir( "..\\ta-lib\\c\\make\\gen_make" );
      system( "perl gen_make.pl" );
      chdir( $dir );

      # Generate TA-MySQL Makefiles
      $dir = cwd;
      chdir( "..\\ta-mysql\\c\\make\\gen_make" );
      system( "perl gen_make.pl" );
      chdir( $dir );

      # Generate TA-unixODBC Makefiles
      $dir = cwd;
      chdir( "..\\ta-unixodbc\\c\\make\\gen_make" );
      system( "perl gen_make.pl" );
      chdir( $dir );

      # Bring all text file to the unix format.
      system( "perl sync.pl" );
   }

   # Test one build of each compiler for TA-Lib. Allows to detect early on compile errors.
   # Remaining library variant are tested later.
   testMSVC("..\\ta-lib\\", "cdr", $fastOption, 0, $root_dir."release\\log\\", 0 );
   testBorland("..\\ta-lib\\", "cmd", $fastOption, 0, $root_dir."release\\log\\", 0 );
   
   # Build for TA-MySQL, no test performed of the library.
   buildMSVC( "..\\ta-mysql\\", "cdr", 0, $root_dir."release\\log\\", "ta_mysql" );
   buildMSVC( "..\\ta-mysql\\", "cdd", 0, $root_dir."release\\log\\", "ta_mysql" );

   # TA-MySQL for Borland is not supported for now.
   # buildBorland( "..\\ta-mysql\\", "cdr", 0, $root_dir."release\\log\\", "ta_mysql" );
   # buildBorland( "..\\ta-mysql\\", "cdd", 0, $root_dir."release\\log\\", "ta_mysql" );

   # Test remaining MSVC variant
   if( $fastOption eq 0 )
   {
      # Compile and test all remaining variant.
      testMSVC("..\\ta-lib\\", "csd", $fastOption, 0, $root_dir."release\\log\\", 0 );
      testMSVC("..\\ta-lib\\", "cmd", $fastOption, 0, $root_dir."release\\log\\", 0 );
      testMSVC("..\\ta-lib\\", "csr", $fastOption, 0, $root_dir."release\\log\\", 0 );
      testMSVC("..\\ta-lib\\", "cdd", $fastOption, 0, $root_dir."release\\log\\", 0 );
      testMSVC("..\\ta-lib\\", "cmr", $fastOption, 0, $root_dir."release\\log\\", 0 );
   }
   else
   {
      # Just compile a few variant.
      testMSVC("..\\ta-lib\\", "cmr", $fastOption, 0, $root_dir."release\\log\\", 1 );
      testMSVC("..\\ta-lib\\", "csd", $fastOption, 0, $root_dir."release\\log\\", 1 );
   }

   # Test remaining Borland variant
   if( $fastOption eq 0 )
   {
      # Compile and test all remaining variant.
      testBorland("..\\ta-lib\\", "csd", $fastOption, 0, $root_dir."release\\log\\", 0 );
      testBorland("..\\ta-lib\\", "cmr", $fastOption, 0, $root_dir."release\\log\\", 0 );
      testBorland("..\\ta-lib\\", "csr", $fastOption, 0, $root_dir."release\\log\\", 0 );
   }
   else
   {
      # Just compile a variant.
      testBorland("..\\ta-lib\\", "csr", $fastOption, 0, $root_dir."release\\log\\", 1 );
   }

   # Check for warnings.
   execProgForce( "..\\release\\log",  'find "arning" *.txt' );

   # Clean-up everything because usually the test are followed
   # with a sync with the remote CVS repository.
   removeAllBinFile( "..\\ta-lib\\", 0 );
   removeAllTempFile( "..\\ta-lib\\" );

   removeAllBinFile( "..\\ta-unixodbc\\", 0 );
   removeAllTempFile( "..\\ta-unixodbc\\" );

   removeAllBinFile( "..\\ta-mysql\\", 0 );
   removeAllTempFile( "..\\ta-mysql\\" );

   print( "\n* Testing Completed with Success *\n" );
}

&Main;
