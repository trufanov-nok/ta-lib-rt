#!/usr/perl/bin

# This script performs an extensive clean-up, code generation and tests for TA-Lib.
# 
# It builds multiple variant of the library and runs ta_regtest for each.
# 
# This script is for Win32, another one called "test_unix.pl" is intended
# for unix.
# 
# This script is intended for maintainers of TA-Lib, not for the
# end-user of TA-Lib.
# 
# The script assume the following directory structure:
#      ta-lib/tools
#      ta-lib/ta-lib/c
#
# The script must be run from the tools directory.
# 
# Temporary files are put in the user home directory ("Documents And Settings\UserName").

use Cwd;
use myUtil;

sub Main
{
   $versionSuffix = &libversion();
   $fastOption    = 0;

   print "Testing ".$versionSuffix."\n";

   $root_dir = "..\\";
   $workdir = &getWorkdir;

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
      createWorkdir();
      exit(0);        
   }
   else
   {
     createWorkdir();   
   }

   open(OLD_STDERR,">&STDERR") or die "Failed to save STDERR";
   open(OLD_STDOUT,">&STDOUT") or die "Failed to save STDOUT";
   open(STDOUT, ">".$workdir."log\\stdout_win32.txt" ) or die;
   open(STDERR, ">".$workdir."log\\stderr_win32.txt" ) or die;

   if( $fastOption eq 0 )
   {
      # Update version info in some files.
      replaceLine( $root_dir."ta-lib\\c\\ta-lib.spec.in", "define ta_ver", "%define ta_ver ".$versionSuffix );
      replaceLine( $root_dir."ta-lib\\swig\\src\\interface\\perl.pm", "VERSION =", "our \$VERSION = v".$versionSuffix.";" );
      replaceLine( $root_dir."ta-lib\\swig\\src\\tools\\test_perl\\ta_common.t", "use Finance::", "use Finance::TA v".$versionSuffix.";" );   
      replaceLine( $root_dir."ta-lib\\swig\\src\\tools\\test_perl\\ta_abstract.t", "use Finance::", "use Finance::TA v".$versionSuffix.";" );   
      replaceLine( $root_dir."ta-lib\\swig\\src\\tools\\test_perl\\ta_defs.t", "use Finance::", "use Finance::TA v".$versionSuffix.";" );   
      replaceLine( $root_dir."ta-lib\\swig\\src\\tools\\test_perl\\ta_func.t", "use Finance::", "use Finance::TA v".$versionSuffix.";" );

	   
      removeAllTempFile($workdir."ta-lib\\");
      removeAllBinFile($workdir."ta-lib\\", 0);

      # Generate TA-Lib WIN32 Makefiles
      $dir = cwd;
      chdir( $root_dir."ta-lib\\c\\make\\gen_make" );
      system( "perl gen_make.pl" );
      chdir( $dir );

      # Bring all text file to the unix format.
      system( "perl sync.pl" );
   }

   # Test one build of each compiler for TA-Lib. Allows to detect early on compile errors.
   # Remaining library variant are tested later.
   testMSVC($root_dir."ta-lib\\", "cdr", $fastOption, 0, $workdir."log\\", 0 );
   testBorland($root_dir."ta-lib\\", "cmd", $fastOption, 0, $workdir."log\\", 0 );
   
   # Test remaining MSVC variant
   if( $fastOption eq 0 )
   {
      # Compile and test all remaining variant.
      testMSVC($root_dir."ta-lib\\", "csd", $fastOption, 0, $workdir."log\\", 0 );
      testMSVC($root_dir."ta-lib\\", "cmd", $fastOption, 0, $workdir."log\\", 0 );
      testMSVC($root_dir."ta-lib\\", "csr", $fastOption, 0, $workdir."log\\", 0 );
      testMSVC($root_dir."ta-lib\\", "cdd", $fastOption, 0, $workdir."log\\", 0 );
      testMSVC($root_dir."ta-lib\\", "cmr", $fastOption, 0, $workdir."log\\", 0 );
   }
   else
   {
      # Just compile a few variant.
      testMSVC($root_dir."ta-lib\\", "cmr", $fastOption, 0, $workdir."log\\", 1 );
      testMSVC($root_dir."ta-lib\\", "csd", $fastOption, 0, $workdir."log\\", 1 );
   }

   # Test remaining Borland variant
   if( $fastOption eq 0 )
   {
      # Compile and test all remaining variant.
      testBorland($root_dir."ta-lib\\", "csd", $fastOption, 0, $workdir."log\\", 0 );
      testBorland($root_dir."ta-lib\\", "cmr", $fastOption, 0, $workdir."log\\", 0 );
      testBorland($root_dir."ta-lib\\", "csr", $fastOption, 0, $workdir."log\\", 0 );
   }
   else
   {
      # Just compile a variant.
      testBorland($root_dir."ta-lib\\", "csr", $fastOption, 0, $workdir."log\\", 1 );
   }

   # Check for warnings.
   execProgForce( $workdir."log\\",  'find "arning" *.txt' );


   # Clean-up everything because usually the test are followed
   # with a sync with the remote SVN repository.
   removeAllBinFile( $root_dir."ta-lib\\", 0 );
   removeAllTempFile( $root_dir."ta-lib\\" );

   print( "\n* Testing Completed with Success *\n" );
   close STDOUT;
   close STDERR;
   open(STDOUT,">&OLD_STDOUT") or warn "Failed to restore STDOUT";
   open(STDERR,">&OLD_STDERR") or warn "Failed to restore STDERR";   
   print( "\n* Testing Completed with Success *\n" );
}

&Main;
