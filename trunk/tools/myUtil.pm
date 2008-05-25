# Misceleanous utility function shared by others script.

package myUtil;

use strict;
use base 'Exporter';
use Cwd;
use userSetup; # For user specific path/URL

our @EXPORT  = qw(removeFile execProg execProgForce libversion removeAllTempFile createWorkdir removeAllBinFile testExcel testBorland testMSVC testGCC testPerl buildMSVC buildBorland removeBinFromPackage getReleasedir getLogdir getTempdir getWorkdir getSVNRoot replaceLine);

my $workdir = "";
my $userdir = "";
my $releasedir = "";
my $logdir = "";
my $tempdir = "";

# The workdir is where all the processing take place.
#   - All output logs while running the scripts.
#   - Destination for the files produced by the scripts.
#   - All intermediate files.
sub getWorkdir
{  
   if( $workdir ne "" ) 
   {
      return $workdir;
   }

   if( $^O ne "MSWin32" )
   {   	
      $workdir = &getUserdir()."ta-lib-work/";
   }
   else
   {
      $workdir = &getUserdir()."ta-lib-work\\";
   }
   
   return $workdir;
}

# The release dir is the sub-directory of workdir intended to contains 
# all the file being released.
sub getReleasedir
{
   if( $releasedir ne "" ) 
   {
      return $releasedir;
   }

   if( $^O ne "MSWin32" )
   {   	
      $releasedir = &getWorkdir()."dist/";
   }
   else
   {
      $releasedir = &getWorkdir()."dist\\";
   }
   
   return $releasedir;
}

sub getLogdir
{
   if( $logdir ne "" ) 
   {
      return $logdir;
   }

   if( $^O ne "MSWin32" )
   {   	
      $logdir = &getWorkdir()."log/";
   }
   else
   {
      $logdir = &getWorkdir()."log\\";
   }
   
   return $logdir;
}

sub getTempdir
{
   if( $tempdir ne "" ) 
   {
      return $tempdir;
   }

   if( $^O ne "MSWin32" )
   {   	
      $tempdir = &getWorkdir()."temp/unix/";
   }
   else
   {
      $tempdir = &getWorkdir()."temp\\win32\\";
   }
   
   return $tempdir;
}

# copyFile( pattern, destinationPath )
# 
# This function supports only one wildcard '*' in the pattern.
#
# Examples:
#    copyFile( 'c:\*.c', 'c:\dest' );
#    copyFile( '/mnt/hgfs/include/*.h', '/user/root/include/' );
sub copyFile
{
   # 
   my $temp = $_[0];
   my $dest = $_[1];
  
   if( $^O eq "MSWin32" )
   {   	   
     #Handle special case for win32
     #Glob requires double backslash for '\' and a '\ ' for space.
     $temp =~ s/\\/\\\\/g; 
     $temp =~ s/\ /\\ /g;
   }
 
   my @files = glob($temp);
      
   foreach my $z (@files)
   {
      if( (not $z =~ /HOLDER/) 
           and (not $z =~ /Entries/) 
           and (not $z =~ /Repository/)
           and (not $z =~ /Root/)
           and (not $z =~ /TALib_Prefix.pch/) 
           and (not $z =~ /TA.pm/)
           and (not $z =~ /java/)
           and (not $z =~ /\.svn/) )
      {
         copy( $z );	      
      }
   }	
}

sub removeFile
{
   my $temp = $_[0];
  
   if( $^O eq "MSWin32" )
   {   	   
     #Handle special case for win32
     #Glob requires double backslash for '\' and a '\ ' for space.
     $temp =~ s/\\/\\\\/g; 
     $temp =~ s/\ /\\ /g;
   }
 
   #print "[".$temp."]\n";

   my @files = glob($temp);
      
   foreach my $z (@files)
   {
      if( (not $z =~ /HOLDER/) 
           and (not $z =~ /Entries/) 
           and (not $z =~ /Repository/)
           and (not $z =~ /Root/)
           and (not $z =~ /TALib_Prefix.pch/) 
           and (not $z =~ /TA.pm/)
           and (not $z =~ /java/)
           and (not $z =~ /\.svn/) )
      {
         unlink( $z );	      
      }
   }
}

sub removeFileAndDirectory
{
   my $temp = $_[0];

   if( $^O eq "MSWin32" )
   {   	   
     #Handle special case for win32
     #Glob requires double backslash for '\' and a '\ ' for space.
     $temp =~ s/\\/\\\\/g; 
     $temp =~ s/\ /\\ /g;
   }
   
   my @files = glob($temp);
   
   foreach my $z (@files)
   {
      unlink( $z );
      rmdir( $z );
   }
}

sub createWorkdir
{
   # Create the directories (ignore errors if they do already exist).
   my $workdir = &getWorkdir();
   my $logdir = &getLogdir();

   mkdir( $workdir );
   mkdir( $workdir."log" );
   mkdir( $workdir."dist" );
   mkdir( $workdir."temp" );
   
   if( $^O ne "MSWin32" )
   {         
	   #execProgForce( $userdir, "mkdir ta-lib-work >/dev/null" );
	   #execProgForce( $userdir, "mkdir ta-lib-work/log   >/dev/null" );
	   #execProgForce( $userdir, "mkdir ta-lib-work/dist  >/dev/null" );
	   #execProgForce( $userdir, "mkdir ta-lib-work/temp  >/dev/null" );
	   #execProgForce( $userdir, "mkdir ta-lib-work/temp/unix  >/dev/null" );
      mkdir( $workdir."temp/unix" );
   }
   else
   {
      mkdir( $workdir."temp\\win32" );
   }

   # Do some clean-up from (potential) previous execution.
   if( $^O ne "MSWin32" )
   {         
      removeFile( $logdir."execlog_unix.txt" );
      removeFile( $logdir."stderr_unix.txt" );
      removeFile( $logdir."stdout_unix.txt" );	   
      removeFile( $logdir."*_gcc_*.txt" );
      removeFile( $workdir."temp/unix/*" );
	  removeFile( $workdir."temp/unix/*" );
   }
   else
   {
      removeFile( $workdir."log\\stderr_win32.txt" );
      removeFile( $workdir."log\\stdout_win32.txt" );
      removeFile( $workdir,"log\\perl_msvc.txt" );
      removeFile( $workdir."log\\win_excel.txt" );      
      removeFile( $workdir."log\\win_ta*.txt" );
      removeFile( $workdir."temp\\win32\\*" );
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

   removeFile( $_[0].'*\*.TXT~' );
   removeFile( $_[0].'*\*\*.TXT~' );
   removeFile( $_[0].'*\*\*\*.TXT~' );
   removeFile( $_[0].'*\*\*\*\*.TXT~' );
   removeFile( $_[0].'*\*\*\*\*\*.TXT~' );
   removeFile( $_[0].'*\*\*\*\*\*\*.TXT~' );
   
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
      #removeFile( $_[0].'excel\ta-lib-reverse.xll' );
      removeFile( $_[0].'dotnet\src\Core\Release\*.*' );
      removeFile( $_[0].'dotnet\src\Core\Debug\*.*' );
   }

   removeFile( $_[0].'c\bin\*.*' );
}

sub removeBinFromPackage
{
   my $a = $_[0]."release\\";
   my $b = "zip -d -o -q ".$_[1]; 
   execProg($a, $b." \\ta-lib\\excel\\ta-lib.xll" );
   execProg($a, $b." \\ta-lib\\excel\\ta-lib-reverse.xll" );
   execProg($a, $b." \\ta-lib\\dotnet\\src\\Core\\Debug\\TA-Lib-Core.dll"  );
   execProg($a, $b." \\ta-lib\\dotnet\\src\\Core\\Release\\TA-Lib-Core.dll"  );
   execProg($a, $b." \\ta-lib\\swig\\lib\\perl\\Finance\\TA.pm"  );
}

sub execProg
{
   my $dir = &cwd();

   # print "cd [".$_[0]."]";
   chdir( $_[0] );
   system( $_[1] );

   my $exit_value  = $? >> 8;
   my $signal_num  = $? & 127;
   my $dumped_core = $? & 128;
   my $out = " ";

   if( ($exit_value) or
       ($signal_num) or
       ($dumped_core) )
   {
      $out .= "\n========================================";
      $out .= "\nProg      = ".$_[0]."  ".$_[1];
      $out .= "\nExitValue = ".$exit_value;
      $out .= "\nSignalNum = ".$signal_num;
      $out .= "\nDumpCore  = ".$dumped_core."\n";
      $out .= "\n========================================";
      if( $^O ne "MSWin32" )     
      {
         chdir( &getWorkdir().'log' );
         system( 'grep arning *.txt' );
      }
      else
      {
         chdir( &getWorkdir().'log' );
         $out .= ( "\n" );
         system( 'find /C "arning" *.txt' );
      }
      $out .= "\n========================================\n";

	  print $out;
	  if( $^O eq "MSWin32" ) 
	  {
	    open( OUTFILE, ">execlog_win32.txt");
	  }
      else
	  {
        open( OUTFILE, ">execlog_unix.txt");
	  }

	  print OUTFILE $out;
	  close( OUTFILE );
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
   my $workdir = &getWorkdir()."temp";	
   my $dir = &cwd();
   my $filesuffix;

   if( $^O eq "MSWin32" )
   {
     $filesuffix = "_win32";
   }
   else
   {
     $filesuffix = "_unix";
   }
   
   chdir( $workdir );
   
   # Clean-up some files from (potentially) previous run.  
   unlink( "tmpVer".$filesuffix );
   unlink( "version".$filesuffix.".c" );
   
   # Create a C program to get the info from the TA-Lib source code itself.
   open VERSION_C, ">version".$filesuffix.".c" or die "Can't create version_x.c file";
   printf VERSION_C "/* This program simply output the string hard coded in the library */\n";
   printf VERSION_C "#include <stdio.h>\n";
   if( $^O eq "MSWin32" )
   {
   printf VERSION_C "#include \"$dir\\..\\ta-lib\\c\\src\\ta_common\\ta_version.c\"\n";
   }
   else
   {
   printf VERSION_C "#include \"$dir/../ta-lib/c/src/ta_common/ta_version.c\"\n";
   }   
   printf VERSION_C "\n";
   printf VERSION_C "int main( int argc, char *argv[] )\n";
   printf VERSION_C "{\n";
   printf VERSION_C "   (void)argc;\n";
   printf VERSION_C "   (void)argv;\n";
   printf VERSION_C "   printf( TA_GetVersionString() );\n";
   printf VERSION_C "\n";
   printf VERSION_C "   return 0;\n";
   printf VERSION_C "}\n";
   close VERSION_C;
   
   if( $^O eq "MSWin32" )
   {   
      unlink( "version_win32.exe" );
      execProg( $workdir, "cl -nologo version".$filesuffix.".c" );
      execProg( $workdir, "version_win32.exe >tmpVer".$filesuffix );
      unlink( "version_win32.obj" );
      unlink( "version_win32.exe" );

   }
   else
   {
      unlink( "a.out" );
      unlink( "tmpVer".$filesuffix );
      execProg( $workdir, "gcc version".$filesuffix.".c >/dev/null" );
      execProg( $workdir, "./a.out >tmpVer".$filesuffix );
      unlink( "a.out" );
   }

   open TMPVERFILE, "tmpVer".$filesuffix;
   my $versionString = <TMPVERFILE>;
   my @versionFields = split(/ /, $versionString);
   #print "[".@versionFields[0]."]";
   close TMPVERFILE;
   unlink( "tmpVer".$filesuffix );
   unlink( "version".$filesuffix.".c" );
   chdir( $dir );
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
   my $b = "nmake /NOLOGO ".">\"".$log_path.$lib_name."_msvc_".$libVariant.".txt\"";
   execProg( $a, $b );
}

sub testPerl
{
   my $base       = $_[0];
   my $log_path   = $_[1];
	
   my $a = $base."swig\\ide\\vs2008\\perl";
   my $b = "msbuild perl.sln /t:clean >\"".&getWorkdir()."\\log\\win_ta_lib_perl.txt\"";
   execProg( $a, $b );
   $b = "msbuild perl.sln >\"".&getWorkdir()."\\log\\win_ta_lib_perl.txt\"";
   execProg( $a, $b );
   $a = $base."swig\\src\\tools\\test_perl";
   $b = "perl runtests.pl >\"".&getWorkdir()."\\log\\perl_msvc.txt\"";
   execProg( $a, $b );
}

sub testExcel
{
   my $base       = $_[0];
   my $log_path   = $_[1];

   removeFile( $base."excel\\ta-lib.xll" );
   removeFile( $base."excel\\ta-lib-reverse.xll" );
   
   execProg(  $base."excel\\src", "msbuild ta-lib.sln /p:Configuration=\"Release\" /t:Clean" );
   execProg(  $base."excel\\src", "msbuild ta-lib.sln /p:Configuration=\"Release\"  >\"".&getLogdir()."win_excel.txt\"" );

   execProg(  $base."excel\\src", "msbuild ta-lib.sln /p:Configuration=\"Release Reverse\" /t:Clean" );
   execProg(  $base."excel\\src", "msbuild ta-lib.sln /p:Configuration=\"Release Reverse\" >>\"".&getLogdir()."win_excel.txt\"" );
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
   my $b = "make ".">\"".$log_path.$lib_name."_borl_".$libVariant.".txt\"";
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
   my $b = "make >\"".$log_path.$lib_name."_gcc_".$libVariant.".txt\"";
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
      # If "cdr" test the Excel and Perl interface
      if( $_[1] eq "cdr" )    
      {
         testPerl($_[0]);
	     testExcel($_[0]);
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

# Usage replaceLine(f,x,y)
# Open file f, search for the first line containing x and replace 
# the whole line it with y
# 
# Leave the file untouched if nto found.
sub replaceLine
{
  my $f = $_[0];
  my $x = $_[1];
  my $y = $_[2];
  my $line;

  open(FILE, $f) or die("Could not open [".$f."].");
  my @lines = <FILE>;
  close(FILE);

  # Check if pattern exists and line different.
  my $found = 0;
  my $same = 0;

  foreach $line (@lines) 
  {
    chomp($line);
    if( $line =~ $x )
    {
       if( $found eq 0 )
       {       
          $found = 1;
	  if( $line eq $y )
	  {
	    $same = 1;
	  }
       }
    }
  }

  if( ($found eq 1) and ($same eq 0) )
  {
    open(FILE, ">".$f) or die ("Could not open for writing [".$f."]");
    foreach $line (@lines) 
    {
      chomp($line);
      if( $line =~ $x )
      {
         print FILE $y."\n";
      }
      else
      {
         print FILE $line."\n";
      }
    }
    close(FILE);
  }
  else
  {
     if( $found eq 0 )
     {
        die "Could not find [".$x."] in [".$f."]";
     }
  }
}


1;
