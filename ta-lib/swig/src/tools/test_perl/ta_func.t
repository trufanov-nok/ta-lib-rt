#!/usr/bin/perl -w
#
# Test of ta_func
# 

use strict;
use lib "../../../lib/perl";
use Test;
BEGIN { plan tests => 43 }

use Finance::TA v0.1.2;

print "TA-Lib ", TA_GetVersionString(), "\n";
print "Testing ta_func...\n";

my $udb = new TA_UDBase;
ok( defined $udb );

my $sparam = new TA_AddDataSourceParam;
$sparam->{id} = $TA_SIMULATOR;
ok( TA_AddDataSource($udb, $sparam), $TA_SUCCESS );

my $hparam = new TA_HistoryAllocParam;
$hparam->{category} = "TA_SIM_REF";
$hparam->{symbol} = "DAILY_REF_0";
$hparam->{period} = $TA_DAILY;
my $history = new TA_History($udb, $hparam);
ok( defined $history );
ok( $history->{retCode}, $TA_SUCCESS );
my $series = $history->{close};
ok( @$series, $history->{nbBars} );

my ($retCode, $begIdx, $result1, $result2, $result3);

print "Testing TA_MAX...\n";
($retCode, $begIdx, $result1) = TA_MAX(0, $#$series, $series, 4);
ok( $retCode, $TA_SUCCESS );
ok( $begIdx, TA_MAX_Lookback(4) );
ok( defined $result1 );
ok( $#$series - $#$result1, $begIdx );
ok( $$result1[2], 95.095 );
ok( $$result1[3], 95.095 );
ok( $$result1[4], 94.625 );
ok( $$result1[5], 94.625 );

print "Testing TA_MIN...\n";
($retCode, $begIdx, $result1) = TA_MIN(0, $#$series, $series, 4);
ok( $retCode, $TA_SUCCESS );
ok( $begIdx, TA_MIN_Lookback(4) );
ok( defined $result1 );
ok( $#$series - $#$result1, $begIdx );
ok( $$result1[1], 93.780 );
ok( $$result1[2], 93.780 );
ok( $$result1[3], 92.530 );
ok( $$result1[4], 92.530 );

print "Testing TA_BBANDS...\n";
($retCode, $begIdx, $result1, $result2, $result3) = TA_BBANDS(0, $#$series, $series, 20, 2.0, 2.0, $TA_MAType_EMA);
ok( $retCode, $TA_SUCCESS );
ok( $begIdx, TA_BBANDS_Lookback(20, 2.0, 2.0, $TA_MAType_EMA) );
ok( defined $result1 );
ok( defined $result2 );
ok( defined $result3 );
ok( $#$series - $#$result1, $begIdx );
ok( $#$series - $#$result2, $begIdx );
ok( $#$series - $#$result3, $begIdx );
ok( abs($$result1[0] - 98.0734) < 1e-3 );
ok( abs($$result2[0] - 92.8910) < 1e-3 );
ok( abs($$result3[0] - 87.7086) < 1e-3 );
ok( abs($$result1[13] - 93.674) < 1e-3 );
ok( abs($$result2[13] - 87.679) < 1e-3 );
ok( abs($$result3[13] - 81.685) < 1e-3 );

print "Testing TA_DEMA...\n";
($retCode, $begIdx, $result1) = TA_DEMA(0, $#$series, $series); # default optInTimePeriod
ok( $retCode, $TA_SUCCESS );
ok( $begIdx, TA_DEMA_Lookback(30) );
ok( defined $result1 );
ok( $#$series - $#$result1, $begIdx );
ok( abs($$result1[1] - 86.765) < 1e-3 );
ok( abs($$result1[2] - 86.942) < 1e-3 );
ok( abs($$result1[3] - 87.089) < 1e-3 );
ok( abs($$result1[4] - 87.656) < 1e-3 );

#print "@$series\n\n";
#print "@$result1\n\n";
