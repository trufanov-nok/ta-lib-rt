#!/usr/bin/perl

# This script is intended ONLY for maintainers doing a TA-Lib release.
#
# This script must be run on Linux. It generates the packages for the linux 
# version of TA-Lib.
# 
# It requires SourceForge CVS access to TA-Lib. You will need to change 
# the $root_cvs with your user name.
# 
# In my setup, Linux runs in a VMWare machine and access the
# host windows file system through /mnt/hgfs. If you wish to
# do diferently, adjust the "_dir" variables.
# 
# This script requires myUtil.pm and, of course, the GCC compiler.

use Cwd;
use myUtil;

sub Main
{
   # Adapt these to your setup
   $release_dir = "/mnt/hgfs/Release/";  # Where packaged release is put.
   $unix_dir    = "/home/buzzo/";        # User home directory.
   $root_cvs = ":ext:fortier\@cvs.sourceforge.net:/cvsroot/ta-lib"; # CVS access   

   # Get the "x.y.z" string for this release. This is done by compiling and
   # running the TA-Lib function returning the version.
   $versionSuffix = &libversion();
   
   print "Packaging ".$versionSuffix."\n";

   # Clean-up destination directory.
   execProgForce( $release_dir, "rm -r -f ta-lib-*.tar.gz" );
   execProgForce( $release_dir, "rm -r -f ta-unixodbc-*.tar.gz" );

   # Clean-up release directory on unix.
   # The source code tree and builds are done in that directory.
   removeRelease( $unix_dir );
   execProgForce( $unix_dir."build", "rm -r -f ta-lib-*" );
   mkdir( $unix_dir."release" );
   mkdir( $unix_dir."release/build" );

   # Make the ta-unixodbc package.
   $a = "cvs -z3 -q -d".$root_cvs." export -Dtomorrow ta-unixodbc";
   execProg( $unix_dir."release/build", $a );
   execProg( $unix_dir."release/build", "tar cvf ta-unixodbc-".$versionSuffix."-src.tar ta-unixodbc >tar.out" );
   execProg( $unix_dir."release/build", "gzip ta-unixodbc-".$versionSuffix."-src.tar" );

   execProg( $unix_dir."release/build/", "cp ta-unixodbc-".$versionSuffix."-src.tar.gz ".$release_dir );

   # Get the ta-lib package from CVS
   $a = "cvs -z3 -q -d".$root_cvs." export -Dtomorrow ta-lib";
   execProg( $unix_dir."release/build", $a );

   # Remove Win32 Binaries from the local view.
   $a = "rm ".$unix_dir."release/build/ta-lib/excel/ta-lib.xll";
   execProg( $unix_dir."release/build", $a );
   $a = "rm ".$unix_dir."release/build/ta-lib/swig/lib/perl/ta.dll";
   execProg( $unix_dir."release/build", $a );
   $a = "rm ".$unix_dir."release/build/ta-lib/swig/lib/perl/Finance/TA.pm";
   execProg( $unix_dir."release/build", $a );

   # Build the Source Package
   execProg( $unix_dir."release/build", "tar cvf ta-lib-".$versionSuffix."-src.tar ta-lib >tar.out" );
   execProg( $unix_dir."release/build", "gzip ta-lib-".$versionSuffix."-src.tar" );

   # Run tests
   testGCC( $unix_dir."release/build/ta-lib/", "cmd", 0, 0, $release_dir."log/", 0 );
   testGCC( $unix_dir."release/build/ta-lib/", "csd", 0, 0, $release_dir."log/", 0 );
   testGCC( $unix_dir."release/build/ta-lib/", "cmr", 0, 0, $release_dir."log/", 0 );
   testGCC( $unix_dir."release/build/ta-lib/", "csr", 0, 0, $release_dir."log/", 0 );

   execProg( $unix_dir."release/build/", "cp ta-lib-".$versionSuffix."-src.tar.gz ".$release_dir );

   print "*** Unix Packaging Completed";
}

&Main;
