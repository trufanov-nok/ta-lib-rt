#!/usr/bin/perl

use Cwd;
use myUtil;

sub Main
{
   $workdir = &getWorkdir();
   $tempdir = $workdir.'temp/unix/';

   if( $ARGV[0] eq "-fast" )
   {
      print "Fast Option Set: Skipping some tests\n";
      $fastOption = 1;
   }
   else
   {
      $fastOption = 0;
   }

   print $workdir;
   open(OLD_STDERR,">&STDERR") or die "Failed to save STDERR";
   open(OLD_STDOUT,">&STDOUT") or die "Failed to save STDOUT";   
   open(STDOUT, ">".$workdir."log/stdout_unix.txt" ) or die;
   open(STDERR, ">".$workdir."log/stderr_unix.txt" ) or die;
   
   
   # Clean-up working directory
   createWorkdir();

   # Make a copy of ta-lib into the user directory.
   if( $fastOption eq 0 )
   {     
     # If the directory "temp/win32/sourcecopy" exists in the workdir, 
     # use it instead of making a copy from the source tree.
     # 
     # This is a speed optimization on my setup when I do test on unix 
     # following successful tests on win32.
     if( -e $workdir.'temp/win32/sourcecopy' )
     {
        $tempdir = $workdir.'temp/win32/sourcecopy/';
     }
     else
     { 
       system( 'cp -r ../ta-lib '.$tempdir );
     }
    
     # Clean-up possible temp files
     removeAllTempFile( $tempdir );
     removeAllBinFile( $tempdir );
   }

   testGCC( $tempdir.'ta-lib/', "cmd", $fastOption, 0, $workdir."log/", 0 );
   testGCC( $tempdir.'ta-lib/', "csr", $fastOption, 0, $workdir."log/", 0 );

   if( $fastOption eq 0 )
   {
      testGCC( $tempdir.'ta-lib/', "cmr", $fastOption, 0, $workdir."log/", 0 );
      testGCC( $tempdir.'ta-lib/', "csd", $fastOption, 0, $workdir."log/", 0 );
   }

   print "\n*** Success - All Unix Tests Completed ***\n";
   close STDOUT;
   close STDERR;
   open(STDOUT,">&OLD_STDOUT") or warn "Failed to restore STDOUT";
   open(STDERR,">&OLD_STDERR") or warn "Failed to restore STDERR";
   print "\n*** Success - All Unix Tests Completed ***\n";
}

&Main;				 
