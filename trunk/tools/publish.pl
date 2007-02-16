#!/usr/perl/bin

# On my setup, I run this in a VMWare machine.
# 
# After running release.pl and release_unix.pl with success, the
# "release" directory contains all files that should be available
# to user for download.
#
# This script FTP these files on SourceForge.

$ip = "66.35.250.221"; # For upload.sourceforge.net
execProg( "/mnt/hgfs/ta-lib-user/ta-lib-work/dist", "ncftpput $ip incoming *" );

sub execProg
{
   $dir = cwd;

   chdir( $_[0] );
   system( $_[1] );

   $exit_value  = $? >> 8;
   $signal_num  = $? & 127;
   $dumped_core = $? & 128;

   if( ($exit_value) or
       ($signal_num) or
       ($dumped_code) )
   {
     print "\nProg      = ".$_[1];
     print "\nExitValue = ".$exit_value;
     print "\nSignalNum = ".$signal_num;
     print "\nDumpCore  = ".$dumped_core."\n";
   }

   not $exit_value or die "Script Abort";
   not $signal_num or die "Script Abort";
   not $dumped_code or die "Script Abort";

   chdir( $dir );
}
										     
