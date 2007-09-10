# -*-Perl-*-
eval 'exec perl -S $0 ${1+"$@"}'
   if 0;

use strict;
use Getopt::Long;

my $usage = "Usage: release_unix.pl -version VERSION [-rpm] [-deb] [-source srcdir]\n";

my($version, $rpm, $deb, $srcdir);

GetOptions( 'version=s' => \$version,
	    'rpm' => \$rpm,
	    'deb' => \$deb,
	    'source=s' => \$srcdir
) or die $usage;

die $usage if not defined $version;

my $workdir = $ENV{'HOME'} . "/ta-lib-$version-work";

# Remove existing directory if it exists
system( "rm -Rf $workdir" ) if( -d $workdir );
system( "mkdir -p $workdir" ) == 0 or die "Cannot create directory $workdir";
system( "mkdir -p $workdir/dist" ) == 0 or die "Cannot create directory $workdir/dist";

if( not defined $srcdir )
{
    # Get the latest code from SVN
    system( "svn co https://ta-lib.svn.sourceforge.net/svnroot/ta-lib/trunk/ta-lib/c/ $workdir/ta-lib" ) == 0 or die "Failed to checkout latest SVN code.";

    # Enable exec permission here, until we figure out how to do it in SVN instead.
    system( "chmod guo+x $workdir/ta-lib/autogen.sh" ) == 0 or die "Failed to set exec permission for autogen.sh";
}else
{
    # Copy srcdir into build tree
    print "Acquiring sources...\n";
    system( "cp $srcdir $workdir/ta-lib -R" ) == 0 or die "Failed to copy source directory.";
}

# Additional (non-mandatory) copy of doc from my VMWare shared distribution directory.
if( -e '/mnt/hgfs/ta-lib-user/ta-lib-work/dist' )
{
   if( not -e '/mnt/hgfs/ta-lib-user/ta-lib-work/dist/CHANGELOG.TXT' )
   {
      die "Missing CHANGELOG.TXT in dist"; 
   }

   if( not -e '/mnt/hgfs/ta-lib-user/ta-lib-work/dist/HISTORY.TXT' )
   {
      die "Missing HISTORY.TXT in dist"; 
   }

   system( "cp /mnt/hgfs/ta-lib-user/ta-lib-work/dist/*.TXT $workdir/ta-lib" ) == 0 or die "Failed to get documentation from dist.";
}

print "Setting up autoconf...\n";

# Create the autoconf files by running autogen.sh
chdir "$workdir/ta-lib" or die "Cannot chdir to $workdir/ta-lib";

# Change the version number in configure.in
my $tmp = `mktemp`; chomp($tmp);
system( "cp configure.in $tmp" ) == 0 or die "Failed to copy configure.in";
system( "sed -e 's/\\[SVN\\]/\[$version\]/g' < $tmp > configure.in" ) == 0 or die "Failed to modify configure version number.";
unlink $tmp or die "Failed to remove $tmp";
system( "./autogen.sh" ) == 0 or die "Failed to autoconf files.";

# Create the "source" package
chdir( "$workdir" ) or die "Failed to chdir to $workdir";
system( "tar -cf ta-lib-$version-src.tar --exclude=.svn --exclude=make --exclude=ide --exclude=temp --exclude=lib --exclude=bin  ta-lib" ) == 0 or die "Failed to create tarball.";
system( "gzip --best ta-lib-$version-src.tar" ) == 0 or die "Failed to gzip tarball.";
system( "mv ta-lib-$version-src.tar.gz $workdir/dist/" ) == 0 or die "Failed to move tarball into dist dir";

if( defined $rpm )
{
    print "Setting up RPM...\n";
    # Setup RPM directories
    system( "mkdir -p $workdir/rpm" ) == 0 or die "Failed to create RPM directory.";
    system( "mkdir -p $workdir/rpm/SOURCES" ) == 0 or die "Failed to create RPM directory.";
    system( "mkdir -p $workdir/rpm/SPECS" ) == 0 or die "Failed to create RPM directory.";
    system( "mkdir -p $workdir/rpm/BUILD" ) == 0 or die "Failed to create RPM directory.";
    system( "mkdir -p $workdir/rpm/RPMS" ) == 0 or die "Failed to create RPM directory.";
    system( "mkdir -p $workdir/rpm/RPMS/i386"  == 0) or die "Failed to create RPM directory.";
    system( "mkdir -p $workdir/rpm/SRPMS" ) == 0 or die "Failed to create RPM directory.";
    system( "mkdir -p $workdir/rpm/ROOT" ) == 0 or die "Failed to create RPM directory.";

    # Setup this directory with RPM
    system( "echo \'%_topdir $workdir/rpm\' > ~/.rpmmacros" ) == 0 or die "Failed to configure RPM";

    # Copy the sources into the RPM build directory.
    chdir "$workdir/ta-lib";
    system( "cp -R * $workdir/rpm/BUILD/" );
}
chdir "$workdir/ta-lib";

print "Compiling sources...\n";

# Build and test these sources.
system( "./configure" );
#system( "CFLAGS=\"-O2 -g0 -pipe -march=i686\" ./configure --prefix=/usr" );
system( "make" );
system( "sudo make install" );

print "Running tests...\n";

# Do the tests
system( "$workdir/ta-lib/src/tools/ta_regtest/ta_regtest" ) == 0 or die "Regression test failed.";

if( defined $rpm )
{
    print "Building RPMs...\n";
    # Build the RPM
    system( "rpmbuild -ba ta-lib.spec --buildroot $workdir/rpm/ROOT/" ) == 0 or die "Failed to build RPM";

    # Copy RPMs into the dist directory.
    system( "cp $workdir/rpm/RPMS/i386/*.rpm $workdir/dist/" ) == 0 or die "Failed to copy RPMs";
}

#Build the .deb package (requires DPKG)
if( defined $deb )
{
    print "Building deb packages...\n";
    # Create a directory to install into
    system( "mkdir -p $workdir/inst" ) == 0 or die "Failed to create instdir";
    system( "mkdir -p $workdir/inst/DEBIAN" ) == 0 or die "Failed to create instdir";
    
    # Install into this directory
    system( "make DESTDIR=$workdir/inst install" ) == 0 or die "Failed to install ta-lib.";

    # Copy dpkg file to control flie
    system( "cp ta-lib.dpkg $workdir/inst/DEBIAN/control" ) == 0 or die "Failed to copy dpkg file.";

    # Build a package of the installation.
    system( "dpkg --build $workdir/inst/ $workdir/dist/ta-lib-$version.deb" ) == 0 or die "Failed to build debian package.";
}

# Additional (non-mandatory) copy to my VMWare shared distribution directory.
if( -e '/mnt/hgfs/ta-lib-user/ta-lib-work/dist' )
{
   system( "cp $workdir/dist/* /mnt/hgfs/ta-lib-user/ta-lib-work/dist" ) == 0 or warn "Failed to copy final version in dist.";
}

print "\n*** Building of unix packages completed ***\n";
