package myUtil;

use strict;
use base 'Exporter';
use Cwd;

our @EXPORT  = qw(removeFile execProg execProgForce libversion removeAllTempFile removeRelease removeAllBinFile testBorland testMSVC testGCC testPerl buildMSVC buildBorland removeBinFromPackage);

sub removeFile
{
   my @files = glob $_[0];

   foreach my $z (@files)
   {
      if( (not $z =~ /HOLDER/) 
           and (not $z =~ /Entries/) 
           and (not $z =~ /Repository/)
           and (not $z =~ /Root/)
           and (not $z =~ /TALib_Prefix.pch/) 
           and (not $z =~ /TA.pm/)
           and (not $z =~ /ta.dll/) )
      {
         unlink( $z );
      }
   }
}

sub removeFileAndDirectory
{
   my @files = glob $_[0];

   foreach my $z (@files)
   {
      unlink( $z );
      rmdir( $z );
   }
}

sub removeRelease
{
   my $base = $_[0];
   if( $^O ne "MSWin32" )
   {   
      execProgForce( $base, "rm -r -f release/build >/dev/null" );
      execProgForce( $base, "rm -r -f release/* >/dev/null" );
      execProgForce( $base, "mkdir release >/dev/null" );
      execProgForce( $base, "mkdir release/build >/dev/null" );
      execProgForce( $base, "mkdir release/log >/dev/null" );
   }
   else
   {
      removeFileAndDirectory( $base.'release\*\*\*\*\*\*\*\*\*\*\*\*\*' );
      removeFileAndDirectory( $base.'release\*\*\*\*\*\*\*\*\*\*\*\*' );
      removeFileAndDirectory( $base.'release\*\*\*\*\*\*\*\*\*\*\*' );
      removeFileAndDirectory( $base.'release\*\*\*\*\*\*\*\*\*\*' );
      removeFileAndDirectory( $base.'release\*\*\*\*\*\*\*\*\*' );
      removeFileAndDirectory( $base.'release\*\*\*\*\*\*\*\*' );
      removeFileAndDirectory( $base.'release\*\*\*\*\*\*\*' );
      removeFileAndDirectory( $base.'release\*\*\*\*\*\*' );
      removeFileAndDirectory( $base.'release\*\*\*\*\*' );
      removeFileAndDirectory( $base.'release\*\*\*\*' );
      removeFileAndDirectory( $base.'release\*\*\*' );
      removeFileAndDirectory( $base.'release\*\*' );
      removeFileAndDirectory( $base.'release\*' );

      mkdir( $base.'release' );
      mkdir( $base.'release\log' );
      mkdir( $base.'release\build' );
   }
}

sub removeAllTempFile
{
   # Remove all temporary files
   # Do not remove files who are
   # part of a package with 
   # binaries (like .exe, .lib)
   removeFile( $_[0].'c\temp\*.*' );
   removeFile( $_[0].'c\temp\*\*.*' );
   removeFile( $_[0].'c\temp\*\*\*.*' );
   removeFile( $_[0].'c\temp\*\*\*\*.*' );
   removeFile( $_[0].'c\temp\*\*\*\*\*.*' );

   removeFile( $_[0].'swig\temp\*.*' );
   removeFile( $_[0].'swig\temp\*\*.*' );
   removeFile( $_[0].'swig\temp\*\*\*.*' );
   
   removeFile( $_[0].'excel\temp\*.*' );

   removeFile( $_[0].'*\*.pdb' );
   removeFile( $_[0].'*\*\*.pdb' );
   removeFile( $_[0].'*\*\*\*.pdb' );
   removeFile( $_[0].'*\*\*\*\*.pdb' );
   removeFile( $_[0].'*\*\*\*\*\*.pdb' );
   removeFile( $_[0].'*\*\*\*\*\*\*.pdb' );

   removeFile( $_[0].'*\*.ncb' );
   removeFile( $_[0].'*\*\*.ncb' );
   removeFile( $_[0].'*\*\*\*.ncb' );
   removeFile( $_[0].'*\*\*\*\*.ncb' );
   removeFile( $_[0].'*\*\*\*\*\*.ncb' );
   removeFile( $_[0].'*\*\*\*\*\*\*.ncb' );

   removeFile( $_[0].'*\*.obj' );
   removeFile( $_[0].'*\*\*.obj' );
   removeFile( $_[0].'*\*\*\*.obj' );
   removeFile( $_[0].'*\*\*\*\*.obj' );
   removeFile( $_[0].'*\*\*\*\*\*.obj' );
   removeFile( $_[0].'*\*\*\*\*\*\*.obj' );


   removeFile( $_[0].'*\*.pch' );
   removeFile( $_[0].'*\*\*.pch' );
   removeFile( $_[0].'*\*\*\*.pch' );
   removeFile( $_[0].'*\*\*\*\*.pch' );
   removeFile( $_[0].'*\*\*\*\*\*.pch' );
   removeFile( $_[0].'*\*\*\*\*\*\*.pch' );

   removeFile( $_[0].'*\*.idb' );
   removeFile( $_[0].'*\*\*.idb' );
   removeFile( $_[0].'*\*\*\*.idb' );
   removeFile( $_[0].'*\*\*\*\*.idb' );
   removeFile( $_[0].'*\*\*\*\*\*.idb' );
   removeFile( $_[0].'*\*\*\*\*\*\*.idb' );

   removeFile( $_[0].'*\*.opt' );
   removeFile( $_[0].'*\*\*.opt' );
   removeFile( $_[0].'*\*\*\*.opt' );
   removeFile( $_[0].'*\*\*\*\*.opt' );
   removeFile( $_[0].'*\*\*\*\*\*.opt' );
   removeFile( $_[0].'*\*\*\*\*\*\*.opt' );

   removeFile( $_[0].'c\bin\*.dat' );
}

sub removeAllBinFile
{
   my $keepLib = $_[1];

   # Remove all generated executable and libraries.
   if( $keepLib ne 1 )
   {
      removeFile( $_[0].'c\lib\*.*' );
      removeFile( $_[0].'swig\lib\perl\*.*' );
      removeFile( $_[0].'swig\lib\perl\Finance\*.*' );
      #removeFile( $_[0].'excel\ta-lib.xll' );
      #removeFile( $_[0].'dotnet\src\Core\Release\*.*' );
      #removeFile( $_[0].'dotnet\src\Core\Debug\*.*' );
   }

   removeFile( $_[0].'c\bin\*.*' );
}

sub removeBinFromPackage
{
   my $a = $_[0]."release\\";
   my $b = "zip -d -o -q ".$_[1]; 
   execProg($a, $b." \\ta-lib\\excel\\ta-lib.xll" );
   execProg($a, $b." \\ta-lib\\dotnet\\src\\Core\\Debug\\TA-Lib-Core.dll"  );
   execProg($a, $b." \\ta-lib\\dotnet\\src\\Core\\Release\\TA-Lib-Core.dll"  );
   execProg($a, $b." \\ta-lib\\swig\\lib\\perl\\ta.dll"  );
   execProg($a, $b." \\ta-lib\\swig\\lib\\perl\\Finance\\TA.pm"  );
}

sub execProg
{
   my $dir = &cwd();

   chdir( $_[0] );
   system( $_[1] );
   # print $_[1];

   my $exit_value  = $? >> 8;
   my $signal_num  = $? & 127;
   my $dumped_core = $? & 128;

   if( ($exit_value) or
       ($signal_num) or
       ($dumped_core) )
   {
      print "\n========================================";
      print "\nProg      = ".$_[0]."  ".$_[1];
      print "\nExitValue = ".$exit_value;
      print "\nSignalNum = ".$signal_num;
      print "\nDumpCore  = ".$dumped_core."\n";
      print "\n========================================";
      if( $^O ne "MSWin32" )
      {
         chdir( '/mnt/hgfs/Release/log' );
         system( 'grep arning *.txt' );
      }
      else
      {
         chdir( '..\release\log' );
         print( "\n" );
         system( 'find /C "arning" *.txt' );
      }
      print "\n========================================\n";
   }

   not $exit_value or die "Script Abort";
   not $signal_num or die "Script Abort";
   not $dumped_core or die "Script Abort";

   chdir( $dir );
}

sub execProgForce
{
   my $dir = &cwd();

   # Same as execProg but ignore return value.
   chdir( $_[0] );
   system( $_[1] );

   chdir( $dir );
}

sub libversion
{
   if( $^O eq "MSWin32" )
   {   
      unlink( "version.exe" );
      unlink( "tmpVer" );
      execProg( '..\script', 'cl -nologo version.c' );
      execProg( '..\script', 'version.exe >tmpVer' );
      unlink( "version.obj" );
      unlink( "version.exe" );
   }
   else
   {
      unlink( "a.out" );
      unlink( "tmpVer" );
      execProg( '/mnt/hgfs/Shared/script', 'gcc version.c >/dev/null' );
      execProg( '/mnt/hgfs/Shared/script', './a.out >tmpVer' );
      unlink( "a.out" );
   }

   open(TMPVERFILE, "tmpVer" );
   my $versionString = <TMPVERFILE>;
   my @versionFields = split(/ /, $versionString);
   #print "[".@versionFields[0]."]";
   
   return @versionFields[0];
}

sub testBin
{
   my $binDir = $_[0].'c/bin';
   my $fastOption = $_[1];
   my $cmdPrefix = "";

   if( $^O ne "MSWin32" )
   {   
      $cmdPrefix = "./";
      execProg( $binDir, $cmdPrefix."gen_code" );
      execProg( $binDir, $cmdPrefix."ta_regtest" );
      execProg( $binDir, $cmdPrefix."ta_yahoo -dd us.nasdaq.stock MSFT >nul:" );
      execProg( $binDir, $cmdPrefix."gen_rdata -v us y_us.dat" );
   }
   else
   {
      # Execute all the binaries.
      # When fastOption execute only
      # the regtest.
      execProg( $binDir, $cmdPrefix."ta_regtest" );

      if( $fastOption eq 0 )
      {
         execProg( $binDir, $cmdPrefix."gen_code" );
         execProg( $binDir, $cmdPrefix."gen_data" );
         execProg( $binDir, $cmdPrefix."ta_yahoo -c" );
         execProg( $binDir, $cmdPrefix."ta_yahoo -s us.nasdaq.stock >nul:" );
         # execProg( $binDir, $cmdPrefix."ta_yahoo -dd us.nasdaq.stock MSFT >nul:" );
         execProg( $binDir, $cmdPrefix."gen_rdata -v us y_us.dat" );
         execProg( $binDir, $cmdPrefix."gen_rdata -v ca y_ca.dat" );
         # execProg( $binDir, $cmdPrefix."webfetch http://ta-lib.org >nul:" );
         # execProg( $binDir, $cmdPrefix."webfetch ta-lib.org >nul:" );
      }
   }
}

sub buildMSVC
{
   my $base       = $_[0];
   my $libVariant = $_[1];
   my $keepLib    = $_[2];
   my $log_path   = $_[3];
   my $lib_name   = $_[4];

   removeAllBinFile( $base, $keepLib );
   removeAllTempFile( $base );
   my $a = $base."c\\make\\".$libVariant."\\win32\\msvc";
   my $b = "nmake /NOLOGO ".">".$log_path.$lib_name."_msvc_".$libVariant.".txt";
   execProg( $a, $b );
}

sub testPerl
{
   my $base       = $_[0];
   my $log_path   = $_[1];
	
   my $a = $base."swig\\ide\\msvc\\perl";
   my $b = "nmake /NOLOGO perl.mak >".$log_path."perl_msvc.txt";
   execProg( $a, $b );
   $a = $base."swig\\src\\tools\\test_perl";
   $b = "perl runtests.pl >".$log_path."perl_msvc.txt";
   execProg( $a, $b );
}

sub buildBorland
{
   my $base       = $_[0];
   my $libVariant = $_[1];
   my $keepLib    = $_[2];
   my $log_path   = $_[3];
   my $lib_name   = $_[4];

   removeAllBinFile( $base, $keepLib );
   removeAllTempFile( $base );
   my $a = $base."c\\make\\".$libVariant."\\win32\\borland";
   my $b = "make ".">".$log_path.$lib_name."_borl_".$libVariant.".txt";
   execProg( $a, $b );
}

sub buildGCC
{
   my $base       = $_[0];
   my $libVariant = $_[1];
   my $keepLib    = $_[2];
   my $log_path   = $_[3];
   my $lib_name   = $_[4];

   removeAllBinFile( $base, $keepLib );
   removeAllTempFile( $base );
   my $a = $base."c/make/".$libVariant."/linux/g++";
   my $b = "make >".$log_path.$lib_name."_gcc_".$libVariant.".txt";
   execProg( $a, $b );
}

sub testBorland
{   
   buildBorland($_[0],$_[1],$_[3],$_[4],"win_ta_lib");
   if( $_[5] eq 0 )
   {
      testBin($_[0],$_[2]);
   }
}

sub testMSVC
{
   buildMSVC($_[0],$_[1],$_[3],$_[4],"win_ta_lib");
   if( $_[5] eq 0 )
   {
      testBin($_[0],$_[2]);
      # If "cdr" test the Perl interface   
      if( $_[1] eq "cdr" )    
      {
         testPerl($_[0],$_[4]);
      }
   }
}

sub testGCC
{
   buildGCC($_[0],$_[1],$_[3],$_[4],"unix_ta_lib");
   if( $_[5] eq 0 )
   {
      testBin($_[0],$_[2]);
   }
}

1;
