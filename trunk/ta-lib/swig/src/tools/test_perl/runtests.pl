#!perl
#
# Run all tests for Swig Perl wrapper module Finance::TA

use Test::Harness;

# Windows workaround - space problem
$^X =~ s/Program Files/PROGRA~1/;

@tests = <*.t>;
runtests(@tests);

