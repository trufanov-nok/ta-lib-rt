#!perl
#
# Test of ta_common
# 

use strict;
use lib "../../../lib/perl";
use Test;
BEGIN { plan tests => 121 }

use Finance::TA;

print "TA-Lib ", TA_GetVersionString(), "\n";
print "Testing ta_common...\n";

ok( defined TA_GetVersionString() );
ok( TA_GetVersionMajor(), qr/^\d+$/ );
ok( TA_GetVersionMinor(), qr/^\d+$/ );
ok( TA_GetVersionBuild(), qr/^\d+$/ );
ok( TA_GetVersionDate(), qr/^\w+\s+\d+\s+\d+$/ );
ok( TA_GetVersionTime(), qr/^\d\d:\d\d:\d\d$/ );

print "Testing TA_Period...\n";
ok( $TA_1SEC   , 1 );
ok( $TA_2SECS  , 2*$TA_1SEC );
ok( $TA_3SECS  , 3*$TA_1SEC );
ok( $TA_4SECS  , 4*$TA_1SEC );
ok( $TA_5SECS  , 5*$TA_1SEC );
ok( $TA_6SECS  , 6*$TA_1SEC );
ok( $TA_10SECS , 10*$TA_1SEC );
ok( $TA_12SECS , 12*$TA_1SEC );
ok( $TA_15SECS , 15*$TA_1SEC );
ok( $TA_20SECS , 20*$TA_1SEC );
ok( $TA_30SECS , 30*$TA_1SEC );

ok( $TA_1MIN   , 60*$TA_1SEC );
ok( $TA_2MINS  , 2*$TA_1MIN );
ok( $TA_3MINS  , 3*$TA_1MIN );
ok( $TA_4MINS  , 4*$TA_1MIN );
ok( $TA_5MINS  , 5*$TA_1MIN );
ok( $TA_6MINS  , 6*$TA_1MIN );
ok( $TA_10MINS , 10*$TA_1MIN );
ok( $TA_12MINS , 12*$TA_1MIN );
ok( $TA_15MINS , 15*$TA_1MIN );
ok( $TA_20MINS , 20*$TA_1MIN );
ok( $TA_30MINS , 30*$TA_1MIN );

ok( $TA_1HOUR   , 60*$TA_1MIN );
ok( $TA_2HOURS  , 2*$TA_1HOUR );
ok( $TA_3HOURS  , 3*$TA_1HOUR );
ok( $TA_4HOURS  , 4*$TA_1HOUR );
ok( $TA_6HOURS  , 6*$TA_1HOUR );
ok( $TA_8HOURS  , 8*$TA_1HOUR );
ok( $TA_12HOURS , 12*$TA_1HOUR );

ok( $TA_DAILY      , 32700 );
ok( $TA_WEEKLY     , 32710 );
ok( $TA_MONTHLY    , 32720 );
ok( $TA_QUARTERLY  , 32730 );
ok( $TA_YEARLY     , 32740 );

print "Testing TA_SetRetCodeInfo()...\n";
{
    my $rci = new TA_RetCodeInfo;
    TA_SetRetCodeInfo(0, $rci);
    ok($rci->{enumStr}, 'TA_SUCCESS' );
    ok($rci->{infoStr}, 'No error' );
    TA_SetRetCodeInfo(1, $rci );
    ok($rci->{enumStr}, 'TA_LIB_NOT_INITIALIZE' );
    ok($rci->{infoStr}, 'TA_Initialize was not sucessfully called' );
}

print "Testing TA_DayOfWeek...\n";
ok( $TA_SUNDAY,    0 );
ok( $TA_MONDAY,    1 );
ok( $TA_TUESDAY,   2 );
ok( $TA_WEDNESDAY, 3 );
ok( $TA_THURSDAY,  4 );
ok( $TA_FRIDAY,    5 );
ok( $TA_SATURDAY,  6 );

print "Testing TA_Timestamp...\n";
my $ts = new TA_Timestamp;
ok( TA_SetDefault($ts), $TA_SUCCESS );  # Default is: Jan 1st 1900, 00:00:00
ok( TA_GetYear($ts), 1900 );
ok( TA_GetMonth($ts), 1 );
ok( TA_GetDay($ts), 1 );
ok( TA_GetHour($ts), 0 );
ok( TA_GetMin($ts), 0 );
ok( TA_GetSec($ts), 0 );
ok( TA_GetDayOfTheWeek($ts),$TA_MONDAY );
ok( TA_GetDayOfTheYear($ts), 0 );
ok( TA_GetWeekOfTheYear($ts), 0 );
ok( TA_GetQuarterOfTheYear($ts), 0 );
{
    ok( TA_SetDate(2004,2,28,$ts), $TA_SUCCESS );
    ok( TA_SetTime(23,11,55,$ts), $TA_SUCCESS );
    my @timedate;
    @timedate = TA_GetDate($ts);
    ok( $timedate[0], $TA_SUCCESS, "@timedate" );
    ok( $timedate[1], 2004 );
    ok( $timedate[2], 2 );
    ok( $timedate[3], 28 );
    @timedate = TA_GetTime($ts);
    ok( $timedate[0], $TA_SUCCESS, "@timedate" );
    ok( $timedate[1], 23 );
    ok( $timedate[2], 11 );
    ok( $timedate[3], 55 );
}
ok( TA_SetDateNow($ts), $TA_SUCCESS );
ok( TA_SetTimeNow($ts), $TA_SUCCESS );
ok( TA_TimestampValidate($ts), $TA_SUCCESS );
ok( TA_TimestampValidateYMD($ts), $TA_SUCCESS );
ok( TA_TimestampValidateHMS($ts), $TA_SUCCESS );

my $ts2 = new TA_Timestamp;
ok( TA_TimestampCopy($ts2,$ts), $TA_SUCCESS );
ok( TA_NextDay($ts2), $TA_SUCCESS );
ok( TA_TimestampEqual($ts,$ts2), 0 );
ok( TA_TimestampLess($ts,$ts2), 1 );
ok( TA_TimestampGreater($ts,$ts2), 0 );
ok( TA_TimestampCompare($ts,$ts2) < 0 );
ok( TA_TimestampDateEqual($ts,$ts2), 0 );
ok( TA_TimestampDateLess($ts,$ts2), 1 );
ok( TA_TimestampDateGreater($ts,$ts2), 0 );
ok( TA_TimestampDateCompare($ts,$ts2) < 0 );
ok( TA_NextYear($ts2), $TA_SUCCESS );
ok( TA_PrevYear($ts2), $TA_SUCCESS );
ok( TA_PrevDay($ts2), $TA_SUCCESS );
ok( TA_NextWeekday($ts2), $TA_SUCCESS );
ok( TA_PrevWeekday($ts2), $TA_SUCCESS );
ok( TA_JumpToEndOfMonth($ts2), $TA_SUCCESS );
ok( TA_BackToBeginOfMonth($ts2), $TA_SUCCESS );
ok( TA_JumpToEndOfQuarter($ts2), $TA_SUCCESS );
ok( TA_BackToBeginOfQuarter($ts2), $TA_SUCCESS );
ok( TA_JumpToEndOfYear($ts2), $TA_SUCCESS );
ok( TA_BackToBeginOfYear($ts2), $TA_SUCCESS );
ok( TA_JumpToDayOfWeek($ts2,$TA_FRIDAY), $TA_SUCCESS );
ok( TA_BackToDayOfWeek($ts2,$TA_WEDNESDAY), $TA_SUCCESS );

ok( TA_SetDate(1967,4,22,$ts), $TA_SUCCESS );
ok( TA_SetDate(1979,3,17,$ts2), $TA_SUCCESS );
# enough testing on $TA_SUCCESS;
# here we will check the computed delta only
ok( (TA_TimestampDeltaWeek($ts,$ts2))[1], 621 );
ok( (TA_TimestampDeltaMonth($ts,$ts2))[1], 143 );
ok( (TA_TimestampDeltaYear($ts,$ts2))[1], 11 );
ok( (TA_TimestampDeltaDay($ts,$ts2))[1], 4348 );
ok( (TA_TimestampDeltaWeekday($ts,$ts2))[1], 3105 );
ok( (TA_TimestampDeltaQuarter($ts,$ts2))[1], 35 );

ok( TA_SetDate(2004,2,29,$ts), $TA_SUCCESS );
ok( TA_SetDate(2004,3,1,$ts2), $TA_SUCCESS );
ok( (TA_TimestampDeltaDay($ts,$ts2))[1], 2 );
ok( TA_TimestampCopy($ts2,$ts), $TA_SUCCESS );
ok( TA_NextDay($ts2), $TA_SUCCESS );
ok( (TA_TimestampDeltaDay($ts,$ts2))[1], 2 );

print "Testing TA_Initialize and TA_Shutdown...\n";
ok( TA_Initialize(), $TA_SUCCESS );
ok( TA_Initialize(), $TA_SUCCESS );       # implicit call to &TA_Shutdown
ok( TA_Initialize(undef), $TA_SUCCESS );
ok( TA_Shutdown(), $TA_SUCCESS );
ok( TA_Shutdown(), $TA_SUCCESS );          # accepted, no-op
my $param = new TA_InitializeParam;
$param->{userLocalDrive} = '.';
ok( TA_Initialize($param), $TA_SUCCESS );
ok( TA_Shutdown(), $TA_SUCCESS );

