#!perl -w
#
# Test of ta_func
# 

use strict;
use lib "../../../lib/perl";
use Test;
BEGIN { plan tests => 12 }

use Finance::TA v0.1.2;

print "TA-Lib ", TA_GetVersionString(), "\n";
print "Testing ta_func...\n";

my $udb = new TA_UDBase;
ok( defined $udb );

my $sparam = new TA_AddDataSourceParam;
$sparam->{id} = $TA_SIMULATOR;
ok( TA_AddDataSource($udb, $sparam), $TA_SUCCESS );

my $history = new TA_History($udb, "TA_SIM_REF", "DAILY_REF_0", $TA_DAILY);
ok( defined $history );
ok( $history->{retCode}, $TA_SUCCESS );
my $series = $history->{close};
ok( @$series, $history->{nbBars} );

my ($retCode, $begIdx, $result1, $result2, $result3);

print "Testing TA_MAX...\n";
($retCode, $begIdx, $result1) = TA_MAX(0, $#$series, $series, 4);
ok( $retCode, $TA_SUCCESS );
ok( $begIdx, 3 );
ok( defined $result1 );
ok( $$result1[2], 95.095 );
ok( $$result1[3], 95.095 );
ok( $$result1[4], 94.625 );
ok( $$result1[5], 94.625 );

#print "@$series\n\n";
#print "@$result1\n\n";
