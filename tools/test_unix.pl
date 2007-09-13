#!/usr/bin/perl

use Cwd;
use myUtil;

sub Main
{
   if( $ARGV[0] eq "-fast" )
   {
      print "Fast Option Set: Skipping some tests\n";
      $fastOption = 1;
   }
   else
   {
      $fastOption = 0;
   }

   #print $workdir;
   #open(OLD_STDERR,">&STDERR") or die "Failed to save STDERR";
   #open(OLD_STDOUT,">&STDOUT") or die "Failed to save STDOUT";   
   #open(STDOUT, ">".$workdir."log/stdout_unix.txt" ) or die;
   #select(STDOUT);
   #open(STDERR, ">".$workdir."log/stderr_unix.txt" ) or die;
   #select(STDERR);
   
   # Clean-up working directory
   createWorkdir();

   $workdir = &getWorkdir();
   $tempdir = &getTempdir();

   # Make a copy of ta-lib into the user directory.
   if( $fastOption eq 0 )
   {
     system( 'rsync -r -v --exclude=*.obj --exclude=*.lib --exclude=*.exe --exclude=.svn --exclude=java --exclude=excel --exclude=dotnet --exclude=*~ --exclude=*.ncb --delete-excluded ../ta-lib '.$tempdir );
    
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
   #close STDOUT;
   #close STDERR;
   #open(STDOUT,">&OLD_STDOUT") or warn "Failed to restore STDOUT";
   #open(STDERR,">&OLD_STDERR") or warn "Failed to restore STDERR";
   #print "\n*** Success - All Unix Tests Completed ***\n";
}

&Main;				 
