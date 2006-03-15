#!/usr/bin/perl

# A lot more of initial clean-up is done by
# the script run on the "windows" side (see release.pl).
#
# Before an offical release, make sure release.pl was
# run with success first.
# 

use Cwd;
use myUtil;

sub Main
{
   $source_dir  = "/mnt/hgfs/Shared/";
   $release_dir = "/mnt/hgfs/Release/";
   $user_dir    = "/home/buzzo/";
   $top_dir     = $user_dir."temp/";

   open(STDOUT, ">".$release_dir."log/stdout_unix.txt" ) or die;
   open(STDERR, ">".$release_dir."log/stderr_unix.txt" ) or die;

   if( $ARGV[0] eq "-fast" )
   {
      print "Fast Option Set: Skipping some tests\n";
      $fastOption = 1;
   }
   else
   {
      $fastOption = 0;
   }

   # Clean-up release directory
   # removeRelease( '/mnt/hgfs/Shared/');   

   # Clean-up possible temp files
   # removeAllTempFile( '/mnt/hgfs/Shared/ta-lib/' );
   # removeAllBinFile( '/mnt/hgfs/Shared/ta-lib/' );

   # Make a copy of ta-lib into the user directory.
   if( $fastOption eq 0 )
   {
     execProg( $user_dir, 'rm -r -f '.$top_dir );
     execProg( $user_dir, 'mkdir '.$top_dir );
     execProg( $top_dir,  "cp -r ".$source_dir."ta-lib ." );
   }

   testGCC( $top_dir."ta-lib/", "cmd", $fastOption, 0, $release_dir."log/", 0 );
   testGCC( $top_dir."ta-lib/", "csr", $fastOption, 0, $release_dir."log/", 0 );

   if( $fastOption eq 0 )
   {
      testGCC( $top_dir."ta-lib/", "cmr", $fastOption, 0, $release_dir."log/", 0 );
      testGCC( $top_dir."ta-lib/", "csd", $fastOption, 0, $release_dir."log/", 0 );
   }

   print "\n*** Success - All Unix Tests Completed ***\n";
}

&Main;				 
