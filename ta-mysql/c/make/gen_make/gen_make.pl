#!/usr/local/bin/perl

# This perl script is the "mother of all" making
# all the operations for re-generating all the
# makefiles variant for ta-mysql (only).

# You must have ta-lib and ta-mysql at the same level
# to make this perl script work.
#
# Example:
#   $ ls 
#   ta-lib ta-mysql
#   $
#

# Un-comment the following lines if
# you wish to provide your own TMAKEPATH.
# use Env qw( TMAKEPATH );
$ENV{'TMAKEPATH'} = 'template\\win32-msvc';

system( "perl ..\\..\\..\\..\\ta-lib\\c\\make\\gen_make\\make_make.pl cdr ..\\..\\..\\..\\ta-lib\\c\\make\\gen_make\\template\\win32-msvc ..\\..\\..\\..\\ta-lib\\c\\make\\gen_make\\template\\* msvc_only" );
