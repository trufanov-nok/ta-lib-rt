# !!! These are all the user specific URL/path that might need to be changed for 
# !!! your setup.

package userSetup;

use strict;
use base 'Exporter';
use Cwd;

our @EXPORT  = qw(getUserdir getSVNRoot);

my $userdir = "";

# User directory. All generated and temporary files will be in this folder.
sub getUserdir
{
   if( $userdir ne "" ) 
   {
      return $userdir;
   }

   if( $^O ne "MSWin32" )
   {   	
      # On my setup, both my unix and win32 machines share the
      # same user directory intended for my projects.
      # If that shared directory is found, use it instead.
      # If not, use a local directory in the OS user account.
      # \Mario
      my $temp = "/mnt/hgfs/ta-lib-user/";
      if( -e $temp && -d $temp )
      {
         $userdir = $temp;
      }
      else
      {
         $userdir = $ENV{'HOME'};
      }
   }
   else
   {
      # Running on win32 machine. 
      $userdir = $ENV{'USERPROFILE'}."\\Temp\\";
      #$userdir = "c:\\Users\\Mario\\ta-lib-user\\";
   }
   
   return $userdir;
}

# Return the SVN URL of TA-Lib
# In my case, I sometime change this to a local mirror repository. 
# Most people won't need to change this.
sub getSVNRoot
{
   return "http://ta-lib.svn.sourceforge.net/svnroot/ta-lib/trunk/ta-lib";
}

1;
