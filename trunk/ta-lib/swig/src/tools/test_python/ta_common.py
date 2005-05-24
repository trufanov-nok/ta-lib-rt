#!/usr/bin/python
"""
Simple test of Python wrapper to ta_common
""" 

import sys
import re
import unittest
sys.path.insert(0,'../../../lib/python')

from TaLib import *



class ta_common_test(unittest.TestCase):

    def test_TA_GetVersion(self):
        self.assertNotEqual( TA_GetVersionString(), '' )
        r1 = re.compile(r'^\d+$')
        self.assert_( r1.match( TA_GetVersionMajor() ) )
        self.assert_( r1.match( TA_GetVersionMinor() ) )
        self.assert_( r1.match( TA_GetVersionBuild() ) )
        r2 = re.compile(r'^\w+\s+\d+\s+\d+$' )
        self.assert_( r2.match( TA_GetVersionDate() ) )
        r3 = re.compile( r'^\d\d:\d\d:\d\d$' )
        self.assert_( r3.match( TA_GetVersionTime() ) )

    def test_TA_Period(self):
        self.assertEqual( TA_1SEC   , 1 )
        self.assertEqual( TA_2SECS  , 2*TA_1SEC )
        self.assertEqual( TA_3SECS  , 3*TA_1SEC )
        self.assertEqual( TA_4SECS  , 4*TA_1SEC )
        self.assertEqual( TA_5SECS  , 5*TA_1SEC )
        self.assertEqual( TA_6SECS  , 6*TA_1SEC )
        self.assertEqual( TA_10SECS , 10*TA_1SEC )
        self.assertEqual( TA_12SECS , 12*TA_1SEC )
        self.assertEqual( TA_15SECS , 15*TA_1SEC )
        self.assertEqual( TA_20SECS , 20*TA_1SEC )
        self.assertEqual( TA_30SECS , 30*TA_1SEC )

        self.assertEqual( TA_1MIN   , 60*TA_1SEC )
        self.assertEqual( TA_2MINS  , 2*TA_1MIN )
        self.assertEqual( TA_3MINS  , 3*TA_1MIN )
        self.assertEqual( TA_4MINS  , 4*TA_1MIN )
        self.assertEqual( TA_5MINS  , 5*TA_1MIN )
        self.assertEqual( TA_6MINS  , 6*TA_1MIN )
        self.assertEqual( TA_10MINS , 10*TA_1MIN )
        self.assertEqual( TA_12MINS , 12*TA_1MIN )
        self.assertEqual( TA_15MINS , 15*TA_1MIN )
        self.assertEqual( TA_20MINS , 20*TA_1MIN )
        self.assertEqual( TA_30MINS , 30*TA_1MIN )

        self.assertEqual( TA_1HOUR   , 60*TA_1MIN )
        self.assertEqual( TA_2HOURS  , 2*TA_1HOUR )
        self.assertEqual( TA_3HOURS  , 3*TA_1HOUR )
        self.assertEqual( TA_4HOURS  , 4*TA_1HOUR )
        self.assertEqual( TA_6HOURS  , 6*TA_1HOUR )
        self.assertEqual( TA_8HOURS  , 8*TA_1HOUR )
        self.assertEqual( TA_12HOURS , 12*TA_1HOUR )

        self.assertEqual( TA_DAILY      , 32700 )
        self.assertEqual( TA_WEEKLY     , 32710 )
        self.assertEqual( TA_MONTHLY    , 32720 )
        self.assertEqual( TA_QUARTERLY  , 32730 )
        self.assertEqual( TA_YEARLY     , 32740 )

    def test_TA_SetRetCodeInfo(self):
        rci = TA_RetCodeInfo()
        TA_SetRetCodeInfo(0, rci)
        self.assertEqual( rci.enumStr, 'TA_SUCCESS' )
        self.assertEqual( rci.infoStr, 'No error' )
        TA_SetRetCodeInfo(1, rci )
        self.assertEqual( rci.enumStr, 'TA_LIB_NOT_INITIALIZE' )
        self.assertEqual( rci.infoStr, 'TA_Initialize was not sucessfully called' )

        # Using constructor parameter
        self.assertEqual( TA_RetCodeInfo(2).enumStr, 'TA_BAD_PARAM' )
        self.assertEqual( TA_RetCodeInfo(2).infoStr, 'A parameter is out of range' )

    def test_TA_DayOfWeek(self):
        self.assertEqual( TA_SUNDAY,    0 )
        self.assertEqual( TA_MONDAY,    1 )
        self.assertEqual( TA_TUESDAY,   2 )
        self.assertEqual( TA_WEDNESDAY, 3 )
        self.assertEqual( TA_THURSDAY,  4 )
        self.assertEqual( TA_FRIDAY,    5 )
        self.assertEqual( TA_SATURDAY,  6 )

    def test_TA_Timestamp(self):
        ts = TA_Timestamp()
        self.assertEqual( TA_SetDefault(ts), TA_SUCCESS )  # Default is: Jan 1st 1900, 00:00:00
        self.assertEqual( TA_GetYear(ts), 1900 )
        self.assertEqual( TA_GetMonth(ts), 1 )
        self.assertEqual( TA_GetDay(ts), 1 )
        self.assertEqual( TA_GetHour(ts), 0 )
        self.assertEqual( TA_GetMin(ts), 0 )
        self.assertEqual( TA_GetSec(ts), 0 )
        self.assertEqual( TA_GetDayOfTheWeek(ts),TA_MONDAY )
        self.assertEqual( TA_GetDayOfTheYear(ts), 0 )
        self.assertEqual( TA_GetWeekOfTheYear(ts), 0 )
        self.assertEqual( TA_GetQuarterOfTheYear(ts), 0 )

        self.assertEqual( TA_SetDate(2004,2,28,ts), TA_SUCCESS )
        self.assertEqual( TA_SetTime(9,11,55,ts), TA_SUCCESS )
        timedate = TA_GetDate(ts)
        self.assertEqual( timedate[0], TA_SUCCESS, "@timedate" )
        self.assertEqual( timedate[1], 2004 )
        self.assertEqual( timedate[2],    2 )
        self.assertEqual( timedate[3],   28 )
        timedate = TA_GetTime(ts)
        self.assertEqual( timedate[0], TA_SUCCESS, "@timedate" )
        self.assertEqual( timedate[1],  9 )
        self.assertEqual( timedate[2], 11 )
        self.assertEqual( timedate[3], 55 )

        # Testing param handling of TA_Timestamp constructor
        self.assert_( TA_TimestampEqual(ts, TA_Timestamp(2004, 2, 28, 9, 11, 55)) )
        self.assert_( TA_TimestampDateEqual(ts, TA_Timestamp(2004, 2, 28)) )
        self.assert_( TA_TimestampEqual(ts, TA_Timestamp("2004-02-28 09:11:55")) )
        self.assert_( TA_TimestampDateEqual(ts, TA_Timestamp("2004-02-28")) )

        self.assertEqual( TA_SetDateNow(ts), TA_SUCCESS )
        self.assertEqual( TA_SetTimeNow(ts), TA_SUCCESS )
        self.assertEqual( TA_TimestampValidate(ts), TA_SUCCESS )
        self.assertEqual( TA_TimestampValidateYMD(ts), TA_SUCCESS )
        self.assertEqual( TA_TimestampValidateHMS(ts), TA_SUCCESS )

        ts2 = TA_Timestamp()
        self.assertEqual( TA_TimestampCopy(ts2,ts), TA_SUCCESS )
        self.assertEqual( TA_NextDay(ts2), TA_SUCCESS )
        self.assertEqual( TA_TimestampEqual(ts,ts2), 0 )
        self.assertEqual( TA_TimestampLess(ts,ts2), 1 )
        self.assertEqual( TA_TimestampGreater(ts,ts2), 0 )
        self.assert_( TA_TimestampCompare(ts,ts2) < 0 )
        self.assertEqual( TA_TimestampDateEqual(ts,ts2), 0 )
        self.assertEqual( TA_TimestampDateLess(ts,ts2), 1 )
        self.assertEqual( TA_TimestampDateGreater(ts,ts2), 0 )
        self.assert_( TA_TimestampDateCompare(ts,ts2) < 0 )
        self.assertEqual( TA_NextYear(ts2), TA_SUCCESS )
        self.assertEqual( TA_PrevYear(ts2), TA_SUCCESS )
        self.assertEqual( TA_PrevDay(ts2), TA_SUCCESS )
        self.assertEqual( TA_NextWeekday(ts2), TA_SUCCESS )
        self.assertEqual( TA_PrevWeekday(ts2), TA_SUCCESS )
        self.assertEqual( TA_JumpToEndOfMonth(ts2), TA_SUCCESS )
        self.assertEqual( TA_BackToBeginOfMonth(ts2), TA_SUCCESS )
        self.assertEqual( TA_JumpToEndOfQuarter(ts2), TA_SUCCESS )
        self.assertEqual( TA_BackToBeginOfQuarter(ts2), TA_SUCCESS )
        self.assertEqual( TA_JumpToEndOfYear(ts2), TA_SUCCESS )
        self.assertEqual( TA_BackToBeginOfYear(ts2), TA_SUCCESS )
        self.assertEqual( TA_JumpToDayOfWeek(ts2,TA_FRIDAY), TA_SUCCESS )
        self.assertEqual( TA_BackToDayOfWeek(ts2,TA_WEDNESDAY), TA_SUCCESS )

        self.assertEqual( TA_SetDate(1967,4,22,ts), TA_SUCCESS )
        self.assertEqual( TA_SetDate(1979,3,17,ts2), TA_SUCCESS )
        # enough testing on TA_SUCCESS
        # here we will check the computed delta only
        self.assertEqual( (TA_TimestampDeltaWeek(ts,ts2))[1], 621 )
        self.assertEqual( (TA_TimestampDeltaMonth(ts,ts2))[1], 143 )
        self.assertEqual( (TA_TimestampDeltaYear(ts,ts2))[1], 11 )
        self.assertEqual( (TA_TimestampDeltaDay(ts,ts2))[1], 4348 )
        self.assertEqual( (TA_TimestampDeltaWeekday(ts,ts2))[1], 3105 )
        self.assertEqual( (TA_TimestampDeltaQuarter(ts,ts2))[1], 35 )

        self.assertEqual( TA_SetDate(2004,2,29,ts), TA_SUCCESS )
        self.assertEqual( TA_SetDate(2004,3,1,ts2), TA_SUCCESS )
        self.assertEqual( (TA_TimestampDeltaDay(ts,ts2))[1], 2 )
        self.assertEqual( TA_TimestampCopy(ts2,ts), TA_SUCCESS )
        self.assertEqual( TA_NextDay(ts2), TA_SUCCESS )
        self.assertEqual( (TA_TimestampDeltaDay(ts,ts2))[1], 2 )

    def test_TA_Initialize(self):
        self.assertEqual( TA_Initialize(), TA_SUCCESS )
        self.assertEqual( TA_Initialize(None), TA_SUCCESS )      # implicit call to TA_Shutdown
        self.assertEqual( TA_Shutdown(), TA_SUCCESS )
        self.assertEqual( TA_Shutdown(), TA_SUCCESS )            # accepted, no-op
        param = TA_InitializeParam()
        param.userLocalDrive = '.'
        self.assertEqual( TA_Initialize(param), TA_SUCCESS )
        self.assertEqual( TA_Shutdown(), TA_SUCCESS )


if __name__ == '__main__':
    print "TA-Lib ", TA_GetVersionString()
    print "Testing ta_common...";
    unittest.main()
