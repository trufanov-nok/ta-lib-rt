#!perl
#
# Test of ta_data
# 

use strict;
use lib "../../../lib/perl";
use Test;
BEGIN { plan tests => 66 }

use Finance::TA;

print "TA-Lib ", TA_GetVersionString(), "\n";
print "Testing ta_data...\n";

# First, we test all the constants, then the functions

ok( $TA_SOURCELOCATION_MAX_LENGTH > 0 );
ok( $TA_SOURCEINFO_MAX_LENGTH > 0 );
ok( $TA_CATEGORY_MAX_LENGTH > 0 );
ok( $TA_SYMBOL_MAX_LENGTH > 0 );

ok( $TA_CAT_COUNTRY_MAX_LENGTH > 0 );
ok( $TA_CAT_EXCHANGE_MAX_LENGTH > 0 );
ok( $TA_CAT_TYPE_MAX_LENGTH > 0 );

ok( $TA_DEFAULT_CATEGORY, "ZZ.OTHER.OTHER" );
ok( $TA_DEFAULT_CATEGORY_COUNTRY, "ZZ" );
ok( $TA_DEFAULT_CATEGORY_EXCHANGE, "OTHER" );
ok( $TA_DEFAULT_CATEGORY_TYPE, "OTHER" );

print "Testing TA_SourceId...\n";
ok( $TA_ASCII_FILE, 0 );
ok( $TA_SIMULATOR, 1 );
ok( $TA_YAHOO_WEB, 2 );
ok( $TA_SQL, 3 );
ok( $TA_NUM_OF_SOURCE_ID > 0 );

print "Testing TA_SourceFlag...\n";
ok( $TA_NO_FLAGS, 0 );
ok( $TA_REPLACE_ZERO_PRICE_BAR, 1 << 0 );
ok( $TA_DO_NOT_SPLIT_ADJUST, 1 << 1 );
ok( $TA_DO_NOT_VALUE_ADJUST, 1 << 2 );

ok( $TA_DOHLCV, "[Y][M][D][O][H][L][C][V]" );
ok( $TA_DOCHLV, "[Y][M][D][O][C][H][L][V]" );
ok( $TA_DOCV, "[Y][M][D][O][C][V]" );
ok( $TA_DCV, "[Y][M][D][C][V]" );

print "Testing TA_Field...\n";
ok( $TA_ALL, 0 );
ok( $TA_OPEN, 1 << 0 );
ok( $TA_HIGH, 1 << 1 );
ok( $TA_LOW, 1 << 2 );
ok( $TA_CLOSE, 1 << 3 );
ok( $TA_VOLUME, 1 << 4 );
ok( $TA_OPENINTEREST, 1 << 5 );
ok( $TA_TIMESTAMP, 1 << 6 );

print "Testing TA_ReportFlag...\n";
ok( $TA_REPORT_SYMBOL, 1 << 0 );
ok( $TA_REPORT_CATEGORY, 1 << 1 );
ok( $TA_REPORT_SOURCE, 1 << 2 );
ok( $TA_REPORT_TOTAL, 1 << 3 );

print "Testing functions...\n";
ok( TA_Initialize(undef), $TA_SUCCESS );
my $udb; # Universal DataBase
ok( TA_UDBaseAlloc(\$udb), $TA_SUCCESS );

print "Testing TA_SIMULATOR data source...\n";
my $sparam = new TA_AddDataSourceParam;
$sparam->{id} = $TA_SIMULATOR;
ok( TA_AddDataSource($udb, $sparam), $TA_SUCCESS );

{
    my $history1 = new TA_History($udb, "TA_SIM_REF", "DAILY_REF_0", $TA_DAILY, undef, undef, $TA_ALL);
    ok( defined $history1 );
    ok( $history1->{retCode}, $TA_SUCCESS );
    ok( $history1->{nbBars}, 252 );
    ok( $history1->{period}, $TA_DAILY );

    my $series;
    # testing TA_Real* array    
    $series = $history1->{close};
    ok( @$series, $history1->{nbBars} );
    ok( $$series[0], 91.500 );
    ok( $$series[1], 94.815 );
    ok( $$series[2], 94.375 );
    
    # testing TA_Integer* array
    $series = $history1->{volume};
    ok( @$series, $history1->{nbBars} );
    ok( $$series[0], 4077500 );
    ok( $$series[1], 4955900 );
    ok( $$series[2], 4775300 );

    # testing TA_Timestamp* array
    $series = $history1->{timestamp};
    ok( @$series, $history1->{nbBars} );
    my @timestamp;
    @timestamp = TA_GetDate( $$series[0] );
    ok( shift(@timestamp), $TA_SUCCESS );
    ok( "@timestamp", "1999 1 4" );
    @timestamp = TA_GetDate( $$series[1] );
    ok( shift(@timestamp), $TA_SUCCESS );
    ok( "@timestamp", "1999 1 5" );
    @timestamp = TA_GetDate( $$series[2] );
    ok( shift(@timestamp), $TA_SUCCESS );
    ok( "@timestamp", "1999 1 6" );

    # In TA_History::new, other parameters than the first four are optional    
    my $history2 = new TA_History($udb, "TA_SIM_REF", "INTRA_REF_0", $TA_10MINS);
    ok( defined $history2 );
    ok( $history2->{retCode}, $TA_SUCCESS );
    ok( $history2->{nbBars}, 33 );
    ok( $history2->{period}, $TA_10MINS );
    $series = $history2->{close};
    #print "@$series\n";

    ok(  TA_HistoryEqual($history1, $history1) );
    ok( !TA_HistoryEqual($history1, $history2) );

    # history will be freed automatically when 'my' variables go out of scope
    # Pay attention that it happens before TA_Shutdown!
}


ok( TA_UDBaseFree($udb), $TA_SUCCESS );
ok( TA_Shutdown(), $TA_SUCCESS );


