#!perl -w
#
# Test of ta_data
# 

use strict;
use lib "../../../lib/perl";
use Test;
BEGIN { plan tests => 96 }

use Finance::TA v0.1.2;

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
my $udb; # Universal DataBase
ok( TA_UDBaseAlloc(\$udb), $TA_SUCCESS );
ok( TA_UDBaseFree($udb), $TA_SUCCESS );
undef $udb;     # IMPORTANT: don't forget to undef the database 
                # after call to &TA_UDBaseFree or segfault may happen!

ok( TA_UDBaseAlloc(\$udb), $TA_SUCCESS );
ok( TA_UDBaseFree($udb), $TA_SUCCESS );

$udb = new TA_UDBase;   # Preferred way of allocating the database
ok( defined $udb );
undef $udb;
$udb = new TA_UDBase;
ok( defined $udb );


print "Testing TA_SIMULATOR data source...\n";
my $sparam = new TA_AddDataSourceParam;
ok( $sparam->{id}, 0 );
ok( $sparam->{flags}, $TA_NO_FLAGS );
ok( $sparam->{period}, 0 );
ok( $sparam->{location}, undef );
ok( $sparam->{info}, undef );
ok( $sparam->{username}, undef );
ok( $sparam->{password}, undef );
ok( $sparam->{category}, undef );
ok( $sparam->{country}, undef );
ok( $sparam->{exchange}, undef );
ok( $sparam->{type}, undef );
ok( $sparam->{symbol}, undef );
ok( $sparam->{name}, undef );
$sparam->{id} = $TA_SIMULATOR;
ok( TA_AddDataSource($udb, $sparam), $TA_SUCCESS );

{
    # Testing string tables
    my @categories = TA_CategoryTable($udb);
    #print "Categories: @categories\n";
    ok( shift(@categories), $TA_SUCCESS );
    #ok( $categories[0], "TA_SIM_MRG" );
    ok( $categories[0], "TA_SIM_REF" );
    ok( $categories[1], "ZZ.OTHER.OTHER" );

    # Another way - using shadow class
    @categories = $udb->CategoryTable();
    #ok( $categories[0], "TA_SIM_MRG" );
    ok( $categories[0], "TA_SIM_REF" );
    ok( $categories[1], "ZZ.OTHER.OTHER" );
    
    my @symbols = TA_SymbolTable($udb, "TA_SIM_REF");
    #print "Symbols @symbols\n";
    ok( shift(@symbols), $TA_SUCCESS );
    ok( $symbols[0], "DAILY_REF_0" );
    ok( $symbols[1], "INTRA_REF_0" );

    # Another way - using shadow class
    @symbols = $udb->SymbolTable("TA_SIM_REF");
    ok( $symbols[0], "DAILY_REF_0" );
    ok( $symbols[1], "INTRA_REF_0" );

    # Negative testing
    @symbols = TA_SymbolTable($udb, "BOGUS");
    ok( shift(@symbols), $TA_CATEGORY_NOT_FOUND );
    ok( $udb->SymbolTable("BOGUS"), undef );

    my $udbx;  # undef
    @categories = TA_CategoryTable($udbx);
    ok( shift(@categories), $TA_BAD_PARAM );
    @symbols = TA_SymbolTable($udbx, "BOGUS");
    ok( shift(@symbols), $TA_BAD_PARAM );
}

{
    # Testing history
    my $histparam = new TA_HistoryAllocParam;
    $histparam->{source} = "Simulator";
    $histparam->{category} = "TA_SIM_REF";
    $histparam->{symbol} = "DAILY_REF_0";
    $histparam->{period} = $TA_DAILY;
    $histparam->{field} = $TA_ALL;
 
    #my $history1 = new TA_History($udb, "TA_SIM_REF", "DAILY_REF_0", $TA_DAILY, undef, undef, $TA_ALL);
    my $history1 = new TA_History($udb, $histparam);
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

    my @sources = $history1->{listOfSource};
    ok( $sources[0], "SIMULATOR" );

    $histparam->{symbol} = "INTRA_REF_0";
    $histparam->{period} = $TA_10MINS;
    $histparam->{start} = new TA_Timestamp("1999-01-01");
    $histparam->{end} = new TA_Timestamp("2000-01-01");
    my $history2 = new TA_History($udb, $histparam);
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

