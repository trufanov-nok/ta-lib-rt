#!/usr/bin/perl -w
#
# Test of ta_pm
# 

use strict;
use lib "../../../lib/perl";
use Test;
BEGIN { plan tests => 77 }

use Finance::TA v0.1.2;

print "TA-Lib ", TA_GetVersionString(), "\n";
print "Testing ta_pm...\n";

# Constants first, as usual
ok( defined $TA_LONG_ENTRY );
ok( defined $TA_LONG_EXIT );
ok( defined $TA_SHORT_ENTRY );
ok( defined $TA_SHORT_EXIT );
ok( $TA_NB_TRADE_TYPE > 0 );

ok( defined $TA_PM_LONG_TRADES );
ok( defined $TA_PM_SHORT_TRADES );
ok( defined $TA_PM_ALL_TRADES );
ok( $TA_PM_NB_GROUP > 0 );

ok( defined $TA_PM_TOTAL_NB_OF_TRADE );
ok( defined $TA_PM_STARTING_CAPITAL );
ok( defined $TA_PM_ENDING_CAPITAL );
ok( defined $TA_PM_TOTAL_NET_PROFIT );
ok( defined $TA_PM_PROFIT_FACTOR );
ok( defined $TA_PM_PERCENT_PROFITABLE );
ok( defined $TA_PM_RATE_OF_RETURN );
ok( defined $TA_PM_ANNUALIZED_RETURN );
ok( defined $TA_PM_ANNUALIZED_COMPOUNDED_RETURN );
ok( defined $TA_PM_NB_WINNING_TRADE );
ok( defined $TA_PM_GROSS_PROFIT );
ok( defined $TA_PM_AVG_PROFIT );
ok( defined $TA_PM_AVG_PROFIT_PERCENT );
ok( defined $TA_PM_LARGEST_PROFIT );
ok( defined $TA_PM_LARGEST_PROFIT_PERCENT );
ok( defined $TA_PM_NB_LOSING_TRADE );
ok( defined $TA_PM_GROSS_LOSS );
ok( defined $TA_PM_AVG_LOSS );
ok( defined $TA_PM_AVG_LOSS_PERCENT );
ok( defined $TA_PM_LARGEST_LOSS );
ok( defined $TA_PM_LARGEST_LOSS_PERCENT );
ok( $TA_PM_NB_VALUEID > 0 );

ok( $TA_PMSTRING_ERROR, "#VALUE!" );
ok( $TA_PM_VALUE_ID_IS_CURRENCY,     0x0001 );
ok( $TA_PM_VALUE_ID_IS_PERCENT,      0x0002 );
ok( $TA_PM_VALUE_ID_IS_INTEGER,      0x0004 );
ok( $TA_PM_VALUE_ID_GENERAL,         0x0100 );
ok( $TA_PM_VALUE_ID_LOSING_RELATED,  0x0200 );
ok( $TA_PM_VALUE_ID_WINNING_RELATED, 0x0400 );
ok( $TA_PM_VALUE_ID_NOT_RECOMMENDED, 0x0800 );

ok( defined $TA_PM_ARRAY_EQUITY );
ok( $TA_PM_NB_ARRAYID > 0 );

my $instr = new TA_Instrument;
ok( defined $instr );
$instr->{catString} = "CAT";
$instr->{symString} = "SYM";
$instr->{userKey} = 10;
ok( $instr->{catString}, "CAT" );
ok( $instr->{symString}, "SYM" );
ok( $instr->{userKey}, 10 );

{
    my $tlog = new TA_TradeLog;
    my $trans = new TA_Transaction;
    $trans->{id} = $instr;
    # I will take care of MAE later
    ok( $trans->{nbPriceBar}, 0 );
    ok( $trans->{highPrice}, undef );
    ok( $trans->{lowPrice}, undef );

    $trans->{type} = $TA_LONG_ENTRY;
    $trans->{execTimestamp} = new TA_Timestamp("2003-01-02");
    $trans->{quantity} = 500;
    $trans->{price} = 16.95;
    ok( TA_TradeLogAdd($tlog, $trans), $TA_SUCCESS );

    $trans->{type} = $TA_LONG_EXIT;
    $trans->{execTimestamp} = new TA_Timestamp("2003-01-10");
    $trans->{quantity} = 500;
    $trans->{price} = 17.22;
    ok( $tlog->TradeLogAdd($trans), $TA_SUCCESS );

    my $ts1 = new TA_Timestamp("2003-01-01");
    my $ts2 = new TA_Timestamp("2003-12-31");
    my $pm = new TA_PM($ts1, $ts2, 100_000);
    ok( $pm->PMAddTradeLog($tlog), $TA_SUCCESS );

    ok( $pm->PMValue($TA_PM_TOTAL_NB_OF_TRADE, $TA_PM_ALL_TRADES), 1 );
    ok( $pm->PMValue(-1, $TA_PM_ALL_TRADES), undef );
    ok( TA_PMValueIdString($TA_PM_TOTAL_NB_OF_TRADE), "Number Of Trades");
    ok( TA_PMValueIdHint($TA_PM_TOTAL_NB_OF_TRADE), qr/Number of/);
    ok( TA_PMValueIdFlags($TA_PM_TOTAL_NB_OF_TRADE), $TA_PM_VALUE_ID_IS_INTEGER | $TA_PM_VALUE_ID_GENERAL );

    my $pmary = new TA_PMArray($pm, $TA_PM_ARRAY_EQUITY, $TA_PM_LONG_TRADES, $TA_DAILY);
    ok( $pmary->{retCode}, $TA_SUCCESS );
    # Another way:
    $pmary = $pm->PMArray($TA_PM_ARRAY_EQUITY, $TA_PM_LONG_TRADES, $TA_DAILY);
    ok( $pmary->{retCode}, $TA_SUCCESS );

    my $ts = $pmary->{timestamp};
    my $data = $pmary->{data};
    ok( scalar(@$ts), $pmary->{nbData} );
    ok( scalar(@$data), $pmary->{nbData} );
    ok( TA_TimestampEqual( $$ts[0], new TA_Timestamp("2003-01-01") ), 1 );
    ok( $$data[0], 100_000 );
    ok( $pmary->{arrayId}, $TA_PM_ARRAY_EQUITY );
    ok( $pmary->{grp}, $TA_PM_LONG_TRADES );
    ok( $pmary->{period}, $TA_DAILY );

    my @report = TA_PMReport($pm);
    ok( shift(@report), $TA_SUCCESS );

    # Quick way of printing a report:
    #{ local $" = "|\n"; print "@report|\n"; }

    my $tr = new TA_TradeReport($pm);
    ok( $tr->{retCode}, $TA_SUCCESS );
    # Another way:
    $tr = $pm->TradeReport();
    ok( $tr->{retCode}, $TA_SUCCESS );
    ok( $tr->{nbTrades}, 1 );

    my $trades = $tr->{trades};
    ok( $$trades[0]->{quantity}, $trans->{quantity} );
    ok( $$trades[0]->{entryPrice}, $trans->{quantity} * 16.95 );
    ok( $$trades[0]->{entryTimestamp}->GetStringDate(), "2003-01-02" );
    ok( $$trades[0]->{exitTimestamp}->GetStringDate(),  "2003-01-10" );
    ok( $$trades[0]->{profit}, 135 );
    ok( $$trades[0]->{id}{catString}, $instr->{catString} );
    ok( $$trades[0]->{id}{symString}, $instr->{symString} );
    ok( $$trades[0]->{id}{userKey}, $instr->{userKey} );

    # MAE not implemented
}

