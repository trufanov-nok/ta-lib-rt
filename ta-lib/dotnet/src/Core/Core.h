/* TA-LIB Copyright (c) 1999-2004, Mario Fortier
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither name of author nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* List of contributors:
 *
 *  Initial  Name/description
 *  -------------------------------------------------------------------
 *  MF       Mario Fortier
 *  PSG      Przemyslaw Grodzki (pgrodzki@ki.net.pl)
 *
 * Change history:
 *
 *  MMDDYY BY   Description
 *  -------------------------------------------------------------------
 *  050703 MF   First version with all the TA functions.
 *  112304 PSG  Fix #1072276 for TA_CandleDefaultSettings size.
 */

#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

#include <limits.h>

namespace TA
{
   namespace Lib
   {
      public __gc __sealed class Core
	  {
	  public:
         #include "ta_defs.h"

      private:
		  __value struct TA_CandleSetting {
              TA_CandleSettingType    settingType;
              TA_RangeType            rangeType;
              int                     avgPeriod;
              double                  factor;
         };

         __gc __sealed class TA_GlobalsType
         {
         public:
            TA_GlobalsType()
            {
               unstablePeriod = new unsigned int __gc [TA_FUNC_UNST_ALL];
               compatibility = 0;
               for( int i=0; i < TA_FUNC_UNST_ALL; i++ )
                  unstablePeriod[i] = 0;
			   candleSettings = new TA_CandleSetting __gc [TA_AllCandleSettings];
            }

            /* For handling the compatibility with other software */
            int compatibility;

            /* For handling the unstable period of some TA function. */
            unsigned int unstablePeriod __gc [];

            /* For handling the candlestick global settings */
            TA_CandleSetting candleSettings  __gc [];
         };

         static TA_GlobalsType *TA_Globals;

         static enum TA_RetCode TA_INT_EMA( int           startIdx,
                                int           endIdx,
                                double        inReal_0 __gc [],
                                int           optInTimePeriod_0, /* From 1 to 200 */
                                double        optInK_1,
                                [OutAttribute]Int32 *outBegIdx,
                                [OutAttribute]Int32 *outNbElement,
                                double        outReal_0 __gc []);

         static enum TA_RetCode TA_INT_EMA( int           startIdx,
                                int           endIdx,
                                float         inReal_0 __gc [],
                                int           optInTimePeriod_0, /* From 1 to 200 */
                                double        optInK_1,
                                [OutAttribute]Int32 *outBegIdx,
                                [OutAttribute]Int32 *outNbElement,
                                double        outReal_0 __gc []);

         static enum TA_RetCode TA_INT_SMA( int     startIdx,
                                int     endIdx,
                                double  inReal_0 __gc [],
                                int     optInTimePeriod_0, /* From 1 to 200 */
                                [OutAttribute]Int32 *outBegIdx,
                                [OutAttribute]Int32 *outNbElement,
                                double  outReal_0 __gc [] );

         static enum TA_RetCode TA_INT_SMA( int     startIdx,
                                int     endIdx,
                                float   inReal_0 __gc [],
                                int     optInTimePeriod_0, /* From 1 to 200 */
                                [OutAttribute]Int32 *outBegIdx,
                                [OutAttribute]Int32 *outNbElement,
                                double  outReal_0 __gc [] );

         static enum TA_RetCode TA_INT_MACD( int    startIdx,
                                 int    endIdx,
                                 double inReal_0 __gc [],
                                 int    optInFastPeriod_0, /* From 1 to 200, 0 is fix 12 */
                                 int    optInSlowPeriod_1, /* From 1 to 200, 0 is fix 26 */
                                 int    optInSignalPeriod_2, /* From 1 to 200 */
                                 [OutAttribute]Int32 *outBegIdx,
                                 [OutAttribute]Int32 *outNbElement,
                                 double outMACD_0 __gc [],
                                 double outMACDSignal_1 __gc [],
                                 double outMACDHist_2 __gc [] );

         static enum TA_RetCode TA_INT_MACD( int    startIdx,
                                 int    endIdx,
                                 float  inReal_0 __gc [],
                                 int    optInFastPeriod_0, /* From 1 to 200, 0 is fix 12 */
                                 int    optInSlowPeriod_1, /* From 1 to 200, 0 is fix 26 */
                                 int    optInSignalPeriod_2, /* From 1 to 200 */
                                 [OutAttribute]Int32 *outBegIdx,
                                 [OutAttribute]Int32 *outNbElement,
                                 double outMACD_0 __gc [],
                                 double outMACDSignal_1 __gc [],
                                 double outMACDHist_2 __gc [] );

         static enum TA_RetCode TA_INT_PO( int    startIdx,
                               int    endIdx,
                               double inReal_0 __gc [],
                               int    optInFastPeriod_0, /* From 1 to 200 */
                               int    optInSlowPeriod_1, /* From 1 to 200 */
                               TA_MAType optInMethod_2,
                               [OutAttribute]Int32 *outBegIdx,
                               [OutAttribute]Int32 *outNbElement,
                               double  outReal_0 __gc [],
                               double  tempBuffer __gc [],
                               unsigned int  doPercentageOutput );

         static enum TA_RetCode TA_INT_PO( int    startIdx,
                               int    endIdx,
                               float inReal_0 __gc [],
                               int    optInFastPeriod_0, /* From 1 to 200 */
                               int    optInSlowPeriod_1, /* From 1 to 200 */
                               TA_MAType optInMethod_2,
                               [OutAttribute]Int32 *outBegIdx,
                               [OutAttribute]Int32 *outNbElement,
                               double  outReal_0 __gc [],
                               double  tempBuffer __gc [],
                               unsigned int  doPercentageOutput );

         static enum TA_RetCode TA_INT_VAR( int    startIdx,
                                int    endIdx,
                                double inReal_0 __gc [],
                                int    optInTimePeriod_0,                       
                                [OutAttribute]Int32 *outBegIdx,
                                [OutAttribute]Int32 *outNbElement,
                                double outReal_0 __gc []);

         static enum TA_RetCode TA_INT_VAR( int    startIdx,
                                int    endIdx,
                                float inReal_0 __gc [],
                                int    optInTimePeriod_0,                       
                                [OutAttribute]Int32 *outBegIdx,
                                [OutAttribute]Int32 *outNbElement,
                                double outReal_0 __gc []);

         static void TA_INT_stddev_using_precalc_ma( double inReal __gc [],
                                              double inMovAvg __gc [],
                                              int inMovAvgBegIdx,
                                              int inMovAvgNbElement,
                                              int timePeriod,
                                              double output __gc []);

         static void TA_INT_stddev_using_precalc_ma( float inReal __gc [],
                                              double inMovAvg __gc [],
                                              int inMovAvgBegIdx,
                                              int inMovAvgNbElement,
                                              int timePeriod,
                                              double output __gc []);


      public:
         static Core()
         {
            // Initialize global settings
            TA_Globals = new TA_GlobalsType;
            /* Set the default value to global variables */
            TA_RestoreCandleDefaultSettings( TA_AllCandleSettings );
         }

         static enum TA_RetCode SetUnstablePeriod( enum TA_FuncUnstId id,
                                                   unsigned int  unstablePeriod );

         static unsigned int GetUnstablePeriod( TA_FuncUnstId id );

         static enum TA_RetCode       SetCompatibility( enum TA_Compatibility value );
         static enum TA_Compatibility GetCompatibility( void );

		 static TA_RetCode TA_SetCandleSettings( TA_CandleSettingType settingType, 
                                                 TA_RangeType rangeType, 
                                                 int avgPeriod, 
                                                 double factor )
         {    
            if( settingType >= TA_AllCandleSettings )
               return TA_BAD_PARAM;
            TA_Globals->candleSettings[settingType].settingType = settingType;
            TA_Globals->candleSettings[settingType].rangeType = rangeType;
            TA_Globals->candleSettings[settingType].avgPeriod = avgPeriod;
            TA_Globals->candleSettings[settingType].factor = factor;
            TA_Globals->candleSettings[settingType].avgPeriod,TA_Globals->candleSettings[settingType].factor;
            return TA_SUCCESS;
         }

         static TA_RetCode TA_RestoreCandleDefaultSettings( TA_CandleSettingType settingType )
         {
            const TA_CandleSetting TA_CandleDefaultSettings[] = {
                /* real body is long when it's longer than the average of the 10 previous candles' real body */
                { TA_BodyLong, TA_RangeType_RealBody, 10, 1.0 },
                /* real body is very long when it's longer than 3 times the average of the 10 previous candles' real body */
                { TA_BodyVeryLong, TA_RangeType_RealBody, 10, 3.0 },
                /* real body is short when it's shorter than the average of the 10 previous candles' real bodies */
                { TA_BodyShort, TA_RangeType_RealBody, 10, 1.0 },
                /* real body is like doji's body when it's shorter than 10% the average of the 10 previous candles' high-low range */
                { TA_BodyDoji, TA_RangeType_HighLow, 10, 0.1 },
                /* shadow is long when it's longer than the real body */
                { TA_ShadowLong, TA_RangeType_RealBody, 0, 1.0 },
                /* shadow is very long when it's longer than 2 times the real body */
                { TA_ShadowVeryLong, TA_RangeType_RealBody, 0, 2.0 },
                /* shadow is short when it's shorter than half the average of the 10 previous candles' sum of shadows */
                { TA_ShadowShort, TA_RangeType_Shadows, 10, 1.0 },
                /* shadow is very short when it's shorter than 10% the average of the 10 previous candles' high-low range */
                { TA_ShadowVeryShort, TA_RangeType_HighLow, 10, 0.1 },
                /* when measuring distance between parts of candles or width of gaps */
                /* "near" means "<= 20% of the average of the 5 previous candles' high-low range" */
                { TA_Near, TA_RangeType_HighLow, 5, 0.2 },
                /* when measuring distance between parts of candles or width of gaps */
                /* "far" means ">= 60% of the average of the 5 previous candles' high-low range" */
                { TA_Far, TA_RangeType_HighLow, 5, 0.6 }
            };

            int i;
            if( settingType > TA_AllCandleSettings )
               return TA_BAD_PARAM;
            if( settingType == TA_AllCandleSettings )
               for( i = 0; i < TA_AllCandleSettings; ++i )
                  TA_Globals->candleSettings[i] = TA_CandleDefaultSettings[i];
            else
               TA_Globals->candleSettings[settingType] = TA_CandleDefaultSettings[settingType];

            return TA_SUCCESS;
         }

/**** START GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
         static int MAX_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode MAX( int    startIdx,
                                     int    endIdx,
                                     double       inReal __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );
         static enum TA_RetCode MAX( int    startIdx,
                                     int    endIdx,
                                     float        inReal __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );

         #define TA_MAX Core::MAX
         #define TA_MAX_Lookback Core::MAX_Lookback

         static int MIN_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode MIN( int    startIdx,
                                     int    endIdx,
                                     double       inReal __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );
         static enum TA_RetCode MIN( int    startIdx,
                                     int    endIdx,
                                     float        inReal __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );

         #define TA_MIN Core::MIN
         #define TA_MIN_Lookback Core::MIN_Lookback

         static int BBANDS_Lookback( int           optInTimePeriod, /* From 2 to 100000 */
                                   double        optInNbDevUp, /* From TA_REAL_MIN to TA_REAL_MAX */
                                   double        optInNbDevDn, /* From TA_REAL_MIN to TA_REAL_MAX */
                                   TA_MAType     optInMAType ); 
         static enum TA_RetCode BBANDS( int    startIdx,
                                        int    endIdx,
                                        double       inReal __gc [],
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        double        optInNbDevUp, /* From TA_REAL_MIN to TA_REAL_MAX */
                                        double        optInNbDevDn, /* From TA_REAL_MIN to TA_REAL_MAX */
                                        TA_MAType     optInMAType,
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outRealUpperBand __gc [],
                                        double        outRealMiddleBand __gc [],
                                        double        outRealLowerBand __gc [] );
         static enum TA_RetCode BBANDS( int    startIdx,
                                        int    endIdx,
                                        float        inReal __gc [],
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        double        optInNbDevUp, /* From TA_REAL_MIN to TA_REAL_MAX */
                                        double        optInNbDevDn, /* From TA_REAL_MIN to TA_REAL_MAX */
                                        TA_MAType     optInMAType,
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outRealUpperBand __gc [],
                                        double        outRealMiddleBand __gc [],
                                        double        outRealLowerBand __gc [] );

         #define TA_BBANDS Core::BBANDS
         #define TA_BBANDS_Lookback Core::BBANDS_Lookback

         static int DEMA_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode DEMA( int    startIdx,
                                      int    endIdx,
                                      double       inReal __gc [],
                                      int           optInTimePeriod, /* From 2 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal __gc [] );
         static enum TA_RetCode DEMA( int    startIdx,
                                      int    endIdx,
                                      float        inReal __gc [],
                                      int           optInTimePeriod, /* From 2 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal __gc [] );

         #define TA_DEMA Core::DEMA
         #define TA_DEMA_Lookback Core::DEMA_Lookback

         static int EMA_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode EMA( int    startIdx,
                                     int    endIdx,
                                     double       inReal __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );
         static enum TA_RetCode EMA( int    startIdx,
                                     int    endIdx,
                                     float        inReal __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );

         #define TA_EMA Core::EMA
         #define TA_EMA_Lookback Core::EMA_Lookback

         static int HT_TRENDLINE_Lookback( void );

         static enum TA_RetCode HT_TRENDLINE( int    startIdx,
                                              int    endIdx,
                                              double       inReal __gc [],
                                              [OutAttribute]Int32 *outBegIdx,
                                              [OutAttribute]Int32 *outNbElement,
                                              double        outReal __gc [] );
         static enum TA_RetCode HT_TRENDLINE( int    startIdx,
                                              int    endIdx,
                                              float        inReal __gc [],
                                              [OutAttribute]Int32 *outBegIdx,
                                              [OutAttribute]Int32 *outNbElement,
                                              double        outReal __gc [] );

         #define TA_HT_TRENDLINE Core::HT_TRENDLINE
         #define TA_HT_TRENDLINE_Lookback Core::HT_TRENDLINE_Lookback

         static int KAMA_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode KAMA( int    startIdx,
                                      int    endIdx,
                                      double       inReal __gc [],
                                      int           optInTimePeriod, /* From 2 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal __gc [] );
         static enum TA_RetCode KAMA( int    startIdx,
                                      int    endIdx,
                                      float        inReal __gc [],
                                      int           optInTimePeriod, /* From 2 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal __gc [] );

         #define TA_KAMA Core::KAMA
         #define TA_KAMA_Lookback Core::KAMA_Lookback

         static int MA_Lookback( int           optInTimePeriod, /* From 1 to 100000 */
                               TA_MAType     optInMAType ); 
         static enum TA_RetCode MA( int    startIdx,
                                    int    endIdx,
                                    double       inReal __gc [],
                                    int           optInTimePeriod, /* From 1 to 100000 */
                                    TA_MAType     optInMAType,
                                    [OutAttribute]Int32 *outBegIdx,
                                    [OutAttribute]Int32 *outNbElement,
                                    double        outReal __gc [] );
         static enum TA_RetCode MA( int    startIdx,
                                    int    endIdx,
                                    float        inReal __gc [],
                                    int           optInTimePeriod, /* From 1 to 100000 */
                                    TA_MAType     optInMAType,
                                    [OutAttribute]Int32 *outBegIdx,
                                    [OutAttribute]Int32 *outNbElement,
                                    double        outReal __gc [] );

         #define TA_MA Core::MA
         #define TA_MA_Lookback Core::MA_Lookback

         static int MAMA_Lookback( double        optInFastLimit, /* From 0.01 to 0.99 */
                                 double        optInSlowLimit );  /* From 0.01 to 0.99 */

         static enum TA_RetCode MAMA( int    startIdx,
                                      int    endIdx,
                                      double       inReal __gc [],
                                      double        optInFastLimit, /* From 0.01 to 0.99 */
                                      double        optInSlowLimit, /* From 0.01 to 0.99 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outMAMA __gc [],
                                      double        outFAMA __gc [] );
         static enum TA_RetCode MAMA( int    startIdx,
                                      int    endIdx,
                                      float        inReal __gc [],
                                      double        optInFastLimit, /* From 0.01 to 0.99 */
                                      double        optInSlowLimit, /* From 0.01 to 0.99 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outMAMA __gc [],
                                      double        outFAMA __gc [] );

         #define TA_MAMA Core::MAMA
         #define TA_MAMA_Lookback Core::MAMA_Lookback

         static int MIDPRICE_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode MIDPRICE( int    startIdx,
                                          int    endIdx,
                                          double       inHigh __gc [],
                                          double       inLow __gc [],
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );
         static enum TA_RetCode MIDPRICE( int    startIdx,
                                          int    endIdx,
                                          float        inHigh __gc [],
                                          float        inLow __gc [],
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );

         #define TA_MIDPRICE Core::MIDPRICE
         #define TA_MIDPRICE_Lookback Core::MIDPRICE_Lookback

         static int MIDPOINT_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode MIDPOINT( int    startIdx,
                                          int    endIdx,
                                          double       inReal __gc [],
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );
         static enum TA_RetCode MIDPOINT( int    startIdx,
                                          int    endIdx,
                                          float        inReal __gc [],
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );

         #define TA_MIDPOINT Core::MIDPOINT
         #define TA_MIDPOINT_Lookback Core::MIDPOINT_Lookback

         static int SAR_Lookback( double        optInAcceleration, /* From 0 to TA_REAL_MAX */
                                double        optInMaximum );  /* From 0 to TA_REAL_MAX */

         static enum TA_RetCode SAR( int    startIdx,
                                     int    endIdx,
                                     double       inHigh __gc [],
                                     double       inLow __gc [],
                                     double        optInAcceleration, /* From 0 to TA_REAL_MAX */
                                     double        optInMaximum, /* From 0 to TA_REAL_MAX */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );
         static enum TA_RetCode SAR( int    startIdx,
                                     int    endIdx,
                                     float        inHigh __gc [],
                                     float        inLow __gc [],
                                     double        optInAcceleration, /* From 0 to TA_REAL_MAX */
                                     double        optInMaximum, /* From 0 to TA_REAL_MAX */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );

         #define TA_SAR Core::SAR
         #define TA_SAR_Lookback Core::SAR_Lookback

         static int SAREXT_Lookback( double        optInStartValue, /* From TA_REAL_MIN to TA_REAL_MAX */
                                   double        optInOffsetOnReverse, /* From 0 to TA_REAL_MAX */
                                   double        optInAccelerationInitLong, /* From 0 to TA_REAL_MAX */
                                   double        optInAccelerationLong, /* From 0 to TA_REAL_MAX */
                                   double        optInAccelerationMaxLong, /* From 0 to TA_REAL_MAX */
                                   double        optInAccelerationInitShort, /* From 0 to TA_REAL_MAX */
                                   double        optInAccelerationShort, /* From 0 to TA_REAL_MAX */
                                   double        optInAccelerationMaxShort );  /* From 0 to TA_REAL_MAX */

         static enum TA_RetCode SAREXT( int    startIdx,
                                        int    endIdx,
                                        double       inHigh __gc [],
                                        double       inLow __gc [],
                                        double        optInStartValue, /* From TA_REAL_MIN to TA_REAL_MAX */
                                        double        optInOffsetOnReverse, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationInitLong, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationLong, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationMaxLong, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationInitShort, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationShort, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationMaxShort, /* From 0 to TA_REAL_MAX */
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outReal __gc [] );
         static enum TA_RetCode SAREXT( int    startIdx,
                                        int    endIdx,
                                        float        inHigh __gc [],
                                        float        inLow __gc [],
                                        double        optInStartValue, /* From TA_REAL_MIN to TA_REAL_MAX */
                                        double        optInOffsetOnReverse, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationInitLong, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationLong, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationMaxLong, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationInitShort, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationShort, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationMaxShort, /* From 0 to TA_REAL_MAX */
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outReal __gc [] );

         #define TA_SAREXT Core::SAREXT
         #define TA_SAREXT_Lookback Core::SAREXT_Lookback

         static int SMA_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode SMA( int    startIdx,
                                     int    endIdx,
                                     double       inReal __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );
         static enum TA_RetCode SMA( int    startIdx,
                                     int    endIdx,
                                     float        inReal __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );

         #define TA_SMA Core::SMA
         #define TA_SMA_Lookback Core::SMA_Lookback

         static int T3_Lookback( int           optInTimePeriod, /* From 2 to 100000 */
                               double        optInVFactor );  /* From 0 to 1 */

         static enum TA_RetCode T3( int    startIdx,
                                    int    endIdx,
                                    double       inReal __gc [],
                                    int           optInTimePeriod, /* From 2 to 100000 */
                                    double        optInVFactor, /* From 0 to 1 */
                                    [OutAttribute]Int32 *outBegIdx,
                                    [OutAttribute]Int32 *outNbElement,
                                    double        outReal __gc [] );
         static enum TA_RetCode T3( int    startIdx,
                                    int    endIdx,
                                    float        inReal __gc [],
                                    int           optInTimePeriod, /* From 2 to 100000 */
                                    double        optInVFactor, /* From 0 to 1 */
                                    [OutAttribute]Int32 *outBegIdx,
                                    [OutAttribute]Int32 *outNbElement,
                                    double        outReal __gc [] );

         #define TA_T3 Core::T3
         #define TA_T3_Lookback Core::T3_Lookback

         static int TEMA_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode TEMA( int    startIdx,
                                      int    endIdx,
                                      double       inReal __gc [],
                                      int           optInTimePeriod, /* From 2 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal __gc [] );
         static enum TA_RetCode TEMA( int    startIdx,
                                      int    endIdx,
                                      float        inReal __gc [],
                                      int           optInTimePeriod, /* From 2 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal __gc [] );

         #define TA_TEMA Core::TEMA
         #define TA_TEMA_Lookback Core::TEMA_Lookback

         static int TRIMA_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode TRIMA( int    startIdx,
                                       int    endIdx,
                                       double       inReal __gc [],
                                       int           optInTimePeriod, /* From 2 to 100000 */
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outReal __gc [] );
         static enum TA_RetCode TRIMA( int    startIdx,
                                       int    endIdx,
                                       float        inReal __gc [],
                                       int           optInTimePeriod, /* From 2 to 100000 */
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outReal __gc [] );

         #define TA_TRIMA Core::TRIMA
         #define TA_TRIMA_Lookback Core::TRIMA_Lookback

         static int WMA_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode WMA( int    startIdx,
                                     int    endIdx,
                                     double       inReal __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );
         static enum TA_RetCode WMA( int    startIdx,
                                     int    endIdx,
                                     float        inReal __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );

         #define TA_WMA Core::WMA
         #define TA_WMA_Lookback Core::WMA_Lookback

         static int ATR_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum TA_RetCode ATR( int    startIdx,
                                     int    endIdx,
                                     double       inHigh __gc [],
                                     double       inLow __gc [],
                                     double       inClose __gc [],
                                     int           optInTimePeriod, /* From 1 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );
         static enum TA_RetCode ATR( int    startIdx,
                                     int    endIdx,
                                     float        inHigh __gc [],
                                     float        inLow __gc [],
                                     float        inClose __gc [],
                                     int           optInTimePeriod, /* From 1 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );

         #define TA_ATR Core::ATR
         #define TA_ATR_Lookback Core::ATR_Lookback

         static int TRANGE_Lookback( void );

         static enum TA_RetCode TRANGE( int    startIdx,
                                        int    endIdx,
                                        double       inHigh __gc [],
                                        double       inLow __gc [],
                                        double       inClose __gc [],
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outReal __gc [] );
         static enum TA_RetCode TRANGE( int    startIdx,
                                        int    endIdx,
                                        float        inHigh __gc [],
                                        float        inLow __gc [],
                                        float        inClose __gc [],
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outReal __gc [] );

         #define TA_TRANGE Core::TRANGE
         #define TA_TRANGE_Lookback Core::TRANGE_Lookback

         static int ADX_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode ADX( int    startIdx,
                                     int    endIdx,
                                     double       inHigh __gc [],
                                     double       inLow __gc [],
                                     double       inClose __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );
         static enum TA_RetCode ADX( int    startIdx,
                                     int    endIdx,
                                     float        inHigh __gc [],
                                     float        inLow __gc [],
                                     float        inClose __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );

         #define TA_ADX Core::ADX
         #define TA_ADX_Lookback Core::ADX_Lookback

         static int ADXR_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode ADXR( int    startIdx,
                                      int    endIdx,
                                      double       inHigh __gc [],
                                      double       inLow __gc [],
                                      double       inClose __gc [],
                                      int           optInTimePeriod, /* From 2 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal __gc [] );
         static enum TA_RetCode ADXR( int    startIdx,
                                      int    endIdx,
                                      float        inHigh __gc [],
                                      float        inLow __gc [],
                                      float        inClose __gc [],
                                      int           optInTimePeriod, /* From 2 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal __gc [] );

         #define TA_ADXR Core::ADXR
         #define TA_ADXR_Lookback Core::ADXR_Lookback

         static int APO_Lookback( int           optInFastPeriod, /* From 2 to 100000 */
                                int           optInSlowPeriod, /* From 2 to 100000 */
                                TA_MAType     optInMAType ); 
         static enum TA_RetCode APO( int    startIdx,
                                     int    endIdx,
                                     double       inReal __gc [],
                                     int           optInFastPeriod, /* From 2 to 100000 */
                                     int           optInSlowPeriod, /* From 2 to 100000 */
                                     TA_MAType     optInMAType,
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );
         static enum TA_RetCode APO( int    startIdx,
                                     int    endIdx,
                                     float        inReal __gc [],
                                     int           optInFastPeriod, /* From 2 to 100000 */
                                     int           optInSlowPeriod, /* From 2 to 100000 */
                                     TA_MAType     optInMAType,
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );

         #define TA_APO Core::APO
         #define TA_APO_Lookback Core::APO_Lookback

         static int AROON_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode AROON( int    startIdx,
                                       int    endIdx,
                                       double       inHigh __gc [],
                                       double       inLow __gc [],
                                       int           optInTimePeriod, /* From 2 to 100000 */
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outAroonDown __gc [],
                                       double        outAroonUp __gc [] );
         static enum TA_RetCode AROON( int    startIdx,
                                       int    endIdx,
                                       float        inHigh __gc [],
                                       float        inLow __gc [],
                                       int           optInTimePeriod, /* From 2 to 100000 */
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outAroonDown __gc [],
                                       double        outAroonUp __gc [] );

         #define TA_AROON Core::AROON
         #define TA_AROON_Lookback Core::AROON_Lookback

         static int AROONOSC_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode AROONOSC( int    startIdx,
                                          int    endIdx,
                                          double       inHigh __gc [],
                                          double       inLow __gc [],
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );
         static enum TA_RetCode AROONOSC( int    startIdx,
                                          int    endIdx,
                                          float        inHigh __gc [],
                                          float        inLow __gc [],
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );

         #define TA_AROONOSC Core::AROONOSC
         #define TA_AROONOSC_Lookback Core::AROONOSC_Lookback

         static int CCI_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode CCI( int    startIdx,
                                     int    endIdx,
                                     double       inHigh __gc [],
                                     double       inLow __gc [],
                                     double       inClose __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );
         static enum TA_RetCode CCI( int    startIdx,
                                     int    endIdx,
                                     float        inHigh __gc [],
                                     float        inLow __gc [],
                                     float        inClose __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );

         #define TA_CCI Core::CCI
         #define TA_CCI_Lookback Core::CCI_Lookback

         static int DX_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode DX( int    startIdx,
                                    int    endIdx,
                                    double       inHigh __gc [],
                                    double       inLow __gc [],
                                    double       inClose __gc [],
                                    int           optInTimePeriod, /* From 2 to 100000 */
                                    [OutAttribute]Int32 *outBegIdx,
                                    [OutAttribute]Int32 *outNbElement,
                                    double        outReal __gc [] );
         static enum TA_RetCode DX( int    startIdx,
                                    int    endIdx,
                                    float        inHigh __gc [],
                                    float        inLow __gc [],
                                    float        inClose __gc [],
                                    int           optInTimePeriod, /* From 2 to 100000 */
                                    [OutAttribute]Int32 *outBegIdx,
                                    [OutAttribute]Int32 *outNbElement,
                                    double        outReal __gc [] );

         #define TA_DX Core::DX
         #define TA_DX_Lookback Core::DX_Lookback

         static int MACD_Lookback( int           optInFastPeriod, /* From 2 to 100000 */
                                 int           optInSlowPeriod, /* From 2 to 100000 */
                                 int           optInSignalPeriod );  /* From 1 to 100000 */

         static enum TA_RetCode MACD( int    startIdx,
                                      int    endIdx,
                                      double       inReal __gc [],
                                      int           optInFastPeriod, /* From 2 to 100000 */
                                      int           optInSlowPeriod, /* From 2 to 100000 */
                                      int           optInSignalPeriod, /* From 1 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outMACD __gc [],
                                      double        outMACDSignal __gc [],
                                      double        outMACDHist __gc [] );
         static enum TA_RetCode MACD( int    startIdx,
                                      int    endIdx,
                                      float        inReal __gc [],
                                      int           optInFastPeriod, /* From 2 to 100000 */
                                      int           optInSlowPeriod, /* From 2 to 100000 */
                                      int           optInSignalPeriod, /* From 1 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outMACD __gc [],
                                      double        outMACDSignal __gc [],
                                      double        outMACDHist __gc [] );

         #define TA_MACD Core::MACD
         #define TA_MACD_Lookback Core::MACD_Lookback

         static int MACDEXT_Lookback( int           optInFastPeriod, /* From 2 to 100000 */
                                    TA_MAType     optInFastMAType,
                                    int           optInSlowPeriod, /* From 2 to 100000 */
                                    TA_MAType     optInSlowMAType,
                                    int           optInSignalPeriod, /* From 1 to 100000 */
                                    TA_MAType     optInSignalMAType ); 
         static enum TA_RetCode MACDEXT( int    startIdx,
                                         int    endIdx,
                                         double       inReal __gc [],
                                         int           optInFastPeriod, /* From 2 to 100000 */
                                         TA_MAType     optInFastMAType,
                                         int           optInSlowPeriod, /* From 2 to 100000 */
                                         TA_MAType     optInSlowMAType,
                                         int           optInSignalPeriod, /* From 1 to 100000 */
                                         TA_MAType     optInSignalMAType,
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outMACD __gc [],
                                         double        outMACDSignal __gc [],
                                         double        outMACDHist __gc [] );
         static enum TA_RetCode MACDEXT( int    startIdx,
                                         int    endIdx,
                                         float        inReal __gc [],
                                         int           optInFastPeriod, /* From 2 to 100000 */
                                         TA_MAType     optInFastMAType,
                                         int           optInSlowPeriod, /* From 2 to 100000 */
                                         TA_MAType     optInSlowMAType,
                                         int           optInSignalPeriod, /* From 1 to 100000 */
                                         TA_MAType     optInSignalMAType,
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outMACD __gc [],
                                         double        outMACDSignal __gc [],
                                         double        outMACDHist __gc [] );

         #define TA_MACDEXT Core::MACDEXT
         #define TA_MACDEXT_Lookback Core::MACDEXT_Lookback

         static int MACDFIX_Lookback( int           optInSignalPeriod );  /* From 1 to 100000 */

         static enum TA_RetCode MACDFIX( int    startIdx,
                                         int    endIdx,
                                         double       inReal __gc [],
                                         int           optInSignalPeriod, /* From 1 to 100000 */
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outMACD __gc [],
                                         double        outMACDSignal __gc [],
                                         double        outMACDHist __gc [] );
         static enum TA_RetCode MACDFIX( int    startIdx,
                                         int    endIdx,
                                         float        inReal __gc [],
                                         int           optInSignalPeriod, /* From 1 to 100000 */
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outMACD __gc [],
                                         double        outMACDSignal __gc [],
                                         double        outMACDHist __gc [] );

         #define TA_MACDFIX Core::MACDFIX
         #define TA_MACDFIX_Lookback Core::MACDFIX_Lookback

         static int MFI_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode MFI( int    startIdx,
                                     int    endIdx,
                                     double       inHigh __gc [],
                                     double       inLow __gc [],
                                     double       inClose __gc [],
                                     int          inVolume __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );
         static enum TA_RetCode MFI( int    startIdx,
                                     int    endIdx,
                                     float        inHigh __gc [],
                                     float        inLow __gc [],
                                     float        inClose __gc [],
                                     int          inVolume __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );

         #define TA_MFI Core::MFI
         #define TA_MFI_Lookback Core::MFI_Lookback

         static int MINUS_DI_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum TA_RetCode MINUS_DI( int    startIdx,
                                          int    endIdx,
                                          double       inHigh __gc [],
                                          double       inLow __gc [],
                                          double       inClose __gc [],
                                          int           optInTimePeriod, /* From 1 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );
         static enum TA_RetCode MINUS_DI( int    startIdx,
                                          int    endIdx,
                                          float        inHigh __gc [],
                                          float        inLow __gc [],
                                          float        inClose __gc [],
                                          int           optInTimePeriod, /* From 1 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );

         #define TA_MINUS_DI Core::MINUS_DI
         #define TA_MINUS_DI_Lookback Core::MINUS_DI_Lookback

         static int MINUS_DM_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum TA_RetCode MINUS_DM( int    startIdx,
                                          int    endIdx,
                                          double       inHigh __gc [],
                                          double       inLow __gc [],
                                          int           optInTimePeriod, /* From 1 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );
         static enum TA_RetCode MINUS_DM( int    startIdx,
                                          int    endIdx,
                                          float        inHigh __gc [],
                                          float        inLow __gc [],
                                          int           optInTimePeriod, /* From 1 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );

         #define TA_MINUS_DM Core::MINUS_DM
         #define TA_MINUS_DM_Lookback Core::MINUS_DM_Lookback

         static int MOM_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum TA_RetCode MOM( int    startIdx,
                                     int    endIdx,
                                     double       inReal __gc [],
                                     int           optInTimePeriod, /* From 1 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );
         static enum TA_RetCode MOM( int    startIdx,
                                     int    endIdx,
                                     float        inReal __gc [],
                                     int           optInTimePeriod, /* From 1 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );

         #define TA_MOM Core::MOM
         #define TA_MOM_Lookback Core::MOM_Lookback

         static int PPO_Lookback( int           optInFastPeriod, /* From 2 to 100000 */
                                int           optInSlowPeriod, /* From 2 to 100000 */
                                TA_MAType     optInMAType ); 
         static enum TA_RetCode PPO( int    startIdx,
                                     int    endIdx,
                                     double       inReal __gc [],
                                     int           optInFastPeriod, /* From 2 to 100000 */
                                     int           optInSlowPeriod, /* From 2 to 100000 */
                                     TA_MAType     optInMAType,
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );
         static enum TA_RetCode PPO( int    startIdx,
                                     int    endIdx,
                                     float        inReal __gc [],
                                     int           optInFastPeriod, /* From 2 to 100000 */
                                     int           optInSlowPeriod, /* From 2 to 100000 */
                                     TA_MAType     optInMAType,
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );

         #define TA_PPO Core::PPO
         #define TA_PPO_Lookback Core::PPO_Lookback

         static int PLUS_DI_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum TA_RetCode PLUS_DI( int    startIdx,
                                         int    endIdx,
                                         double       inHigh __gc [],
                                         double       inLow __gc [],
                                         double       inClose __gc [],
                                         int           optInTimePeriod, /* From 1 to 100000 */
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outReal __gc [] );
         static enum TA_RetCode PLUS_DI( int    startIdx,
                                         int    endIdx,
                                         float        inHigh __gc [],
                                         float        inLow __gc [],
                                         float        inClose __gc [],
                                         int           optInTimePeriod, /* From 1 to 100000 */
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outReal __gc [] );

         #define TA_PLUS_DI Core::PLUS_DI
         #define TA_PLUS_DI_Lookback Core::PLUS_DI_Lookback

         static int PLUS_DM_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum TA_RetCode PLUS_DM( int    startIdx,
                                         int    endIdx,
                                         double       inHigh __gc [],
                                         double       inLow __gc [],
                                         int           optInTimePeriod, /* From 1 to 100000 */
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outReal __gc [] );
         static enum TA_RetCode PLUS_DM( int    startIdx,
                                         int    endIdx,
                                         float        inHigh __gc [],
                                         float        inLow __gc [],
                                         int           optInTimePeriod, /* From 1 to 100000 */
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outReal __gc [] );

         #define TA_PLUS_DM Core::PLUS_DM
         #define TA_PLUS_DM_Lookback Core::PLUS_DM_Lookback

         static int ROC_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum TA_RetCode ROC( int    startIdx,
                                     int    endIdx,
                                     double       inReal __gc [],
                                     int           optInTimePeriod, /* From 1 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );
         static enum TA_RetCode ROC( int    startIdx,
                                     int    endIdx,
                                     float        inReal __gc [],
                                     int           optInTimePeriod, /* From 1 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );

         #define TA_ROC Core::ROC
         #define TA_ROC_Lookback Core::ROC_Lookback

         static int ROCP_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum TA_RetCode ROCP( int    startIdx,
                                      int    endIdx,
                                      double       inReal __gc [],
                                      int           optInTimePeriod, /* From 1 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal __gc [] );
         static enum TA_RetCode ROCP( int    startIdx,
                                      int    endIdx,
                                      float        inReal __gc [],
                                      int           optInTimePeriod, /* From 1 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal __gc [] );

         #define TA_ROCP Core::ROCP
         #define TA_ROCP_Lookback Core::ROCP_Lookback

         static int ROCR_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum TA_RetCode ROCR( int    startIdx,
                                      int    endIdx,
                                      double       inReal __gc [],
                                      int           optInTimePeriod, /* From 1 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal __gc [] );
         static enum TA_RetCode ROCR( int    startIdx,
                                      int    endIdx,
                                      float        inReal __gc [],
                                      int           optInTimePeriod, /* From 1 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal __gc [] );

         #define TA_ROCR Core::ROCR
         #define TA_ROCR_Lookback Core::ROCR_Lookback

         static int ROCR100_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum TA_RetCode ROCR100( int    startIdx,
                                         int    endIdx,
                                         double       inReal __gc [],
                                         int           optInTimePeriod, /* From 1 to 100000 */
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outReal __gc [] );
         static enum TA_RetCode ROCR100( int    startIdx,
                                         int    endIdx,
                                         float        inReal __gc [],
                                         int           optInTimePeriod, /* From 1 to 100000 */
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outReal __gc [] );

         #define TA_ROCR100 Core::ROCR100
         #define TA_ROCR100_Lookback Core::ROCR100_Lookback

         static int RSI_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode RSI( int    startIdx,
                                     int    endIdx,
                                     double       inReal __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );
         static enum TA_RetCode RSI( int    startIdx,
                                     int    endIdx,
                                     float        inReal __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );

         #define TA_RSI Core::RSI
         #define TA_RSI_Lookback Core::RSI_Lookback

         static int STOCH_Lookback( int           optInFastK_Period, /* From 1 to 100000 */
                                  int           optInSlowK_Period, /* From 1 to 100000 */
                                  TA_MAType     optInSlowK_MAType,
                                  int           optInSlowD_Period, /* From 1 to 100000 */
                                  TA_MAType     optInSlowD_MAType ); 
         static enum TA_RetCode STOCH( int    startIdx,
                                       int    endIdx,
                                       double       inHigh __gc [],
                                       double       inLow __gc [],
                                       double       inClose __gc [],
                                       int           optInFastK_Period, /* From 1 to 100000 */
                                       int           optInSlowK_Period, /* From 1 to 100000 */
                                       TA_MAType     optInSlowK_MAType,
                                       int           optInSlowD_Period, /* From 1 to 100000 */
                                       TA_MAType     optInSlowD_MAType,
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outSlowK __gc [],
                                       double        outSlowD __gc [] );
         static enum TA_RetCode STOCH( int    startIdx,
                                       int    endIdx,
                                       float        inHigh __gc [],
                                       float        inLow __gc [],
                                       float        inClose __gc [],
                                       int           optInFastK_Period, /* From 1 to 100000 */
                                       int           optInSlowK_Period, /* From 1 to 100000 */
                                       TA_MAType     optInSlowK_MAType,
                                       int           optInSlowD_Period, /* From 1 to 100000 */
                                       TA_MAType     optInSlowD_MAType,
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outSlowK __gc [],
                                       double        outSlowD __gc [] );

         #define TA_STOCH Core::STOCH
         #define TA_STOCH_Lookback Core::STOCH_Lookback

         static int STOCHF_Lookback( int           optInFastK_Period, /* From 1 to 100000 */
                                   int           optInFastD_Period, /* From 1 to 100000 */
                                   TA_MAType     optInFastD_MAType ); 
         static enum TA_RetCode STOCHF( int    startIdx,
                                        int    endIdx,
                                        double       inHigh __gc [],
                                        double       inLow __gc [],
                                        double       inClose __gc [],
                                        int           optInFastK_Period, /* From 1 to 100000 */
                                        int           optInFastD_Period, /* From 1 to 100000 */
                                        TA_MAType     optInFastD_MAType,
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outFastK __gc [],
                                        double        outFastD __gc [] );
         static enum TA_RetCode STOCHF( int    startIdx,
                                        int    endIdx,
                                        float        inHigh __gc [],
                                        float        inLow __gc [],
                                        float        inClose __gc [],
                                        int           optInFastK_Period, /* From 1 to 100000 */
                                        int           optInFastD_Period, /* From 1 to 100000 */
                                        TA_MAType     optInFastD_MAType,
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outFastK __gc [],
                                        double        outFastD __gc [] );

         #define TA_STOCHF Core::STOCHF
         #define TA_STOCHF_Lookback Core::STOCHF_Lookback

         static int STOCHRSI_Lookback( int           optInTimePeriod, /* From 2 to 100000 */
                                     int           optInFastK_Period, /* From 1 to 100000 */
                                     int           optInFastD_Period, /* From 1 to 100000 */
                                     TA_MAType     optInFastD_MAType ); 
         static enum TA_RetCode STOCHRSI( int    startIdx,
                                          int    endIdx,
                                          double       inReal __gc [],
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          int           optInFastK_Period, /* From 1 to 100000 */
                                          int           optInFastD_Period, /* From 1 to 100000 */
                                          TA_MAType     optInFastD_MAType,
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outFastK __gc [],
                                          double        outFastD __gc [] );
         static enum TA_RetCode STOCHRSI( int    startIdx,
                                          int    endIdx,
                                          float        inReal __gc [],
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          int           optInFastK_Period, /* From 1 to 100000 */
                                          int           optInFastD_Period, /* From 1 to 100000 */
                                          TA_MAType     optInFastD_MAType,
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outFastK __gc [],
                                          double        outFastD __gc [] );

         #define TA_STOCHRSI Core::STOCHRSI
         #define TA_STOCHRSI_Lookback Core::STOCHRSI_Lookback

         static int TRIX_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum TA_RetCode TRIX( int    startIdx,
                                      int    endIdx,
                                      double       inReal __gc [],
                                      int           optInTimePeriod, /* From 1 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal __gc [] );
         static enum TA_RetCode TRIX( int    startIdx,
                                      int    endIdx,
                                      float        inReal __gc [],
                                      int           optInTimePeriod, /* From 1 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal __gc [] );

         #define TA_TRIX Core::TRIX
         #define TA_TRIX_Lookback Core::TRIX_Lookback

         static int WILLR_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode WILLR( int    startIdx,
                                       int    endIdx,
                                       double       inHigh __gc [],
                                       double       inLow __gc [],
                                       double       inClose __gc [],
                                       int           optInTimePeriod, /* From 2 to 100000 */
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outReal __gc [] );
         static enum TA_RetCode WILLR( int    startIdx,
                                       int    endIdx,
                                       float        inHigh __gc [],
                                       float        inLow __gc [],
                                       float        inClose __gc [],
                                       int           optInTimePeriod, /* From 2 to 100000 */
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outReal __gc [] );

         #define TA_WILLR Core::WILLR
         #define TA_WILLR_Lookback Core::WILLR_Lookback

         static int HT_DCPERIOD_Lookback( void );

         static enum TA_RetCode HT_DCPERIOD( int    startIdx,
                                             int    endIdx,
                                             double       inReal __gc [],
                                             [OutAttribute]Int32 *outBegIdx,
                                             [OutAttribute]Int32 *outNbElement,
                                             double        outReal __gc [] );
         static enum TA_RetCode HT_DCPERIOD( int    startIdx,
                                             int    endIdx,
                                             float        inReal __gc [],
                                             [OutAttribute]Int32 *outBegIdx,
                                             [OutAttribute]Int32 *outNbElement,
                                             double        outReal __gc [] );

         #define TA_HT_DCPERIOD Core::HT_DCPERIOD
         #define TA_HT_DCPERIOD_Lookback Core::HT_DCPERIOD_Lookback

         static int HT_DCPHASE_Lookback( void );

         static enum TA_RetCode HT_DCPHASE( int    startIdx,
                                            int    endIdx,
                                            double       inReal __gc [],
                                            [OutAttribute]Int32 *outBegIdx,
                                            [OutAttribute]Int32 *outNbElement,
                                            double        outReal __gc [] );
         static enum TA_RetCode HT_DCPHASE( int    startIdx,
                                            int    endIdx,
                                            float        inReal __gc [],
                                            [OutAttribute]Int32 *outBegIdx,
                                            [OutAttribute]Int32 *outNbElement,
                                            double        outReal __gc [] );

         #define TA_HT_DCPHASE Core::HT_DCPHASE
         #define TA_HT_DCPHASE_Lookback Core::HT_DCPHASE_Lookback

         static int HT_PHASOR_Lookback( void );

         static enum TA_RetCode HT_PHASOR( int    startIdx,
                                           int    endIdx,
                                           double       inReal __gc [],
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           double        outInPhase __gc [],
                                           double        outQuadrature __gc [] );
         static enum TA_RetCode HT_PHASOR( int    startIdx,
                                           int    endIdx,
                                           float        inReal __gc [],
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           double        outInPhase __gc [],
                                           double        outQuadrature __gc [] );

         #define TA_HT_PHASOR Core::HT_PHASOR
         #define TA_HT_PHASOR_Lookback Core::HT_PHASOR_Lookback

         static int HT_SINE_Lookback( void );

         static enum TA_RetCode HT_SINE( int    startIdx,
                                         int    endIdx,
                                         double       inReal __gc [],
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outSine __gc [],
                                         double        outLeadSine __gc [] );
         static enum TA_RetCode HT_SINE( int    startIdx,
                                         int    endIdx,
                                         float        inReal __gc [],
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outSine __gc [],
                                         double        outLeadSine __gc [] );

         #define TA_HT_SINE Core::HT_SINE
         #define TA_HT_SINE_Lookback Core::HT_SINE_Lookback

         static int HT_TRENDMODE_Lookback( void );

         static enum TA_RetCode HT_TRENDMODE( int    startIdx,
                                              int    endIdx,
                                              double       inReal __gc [],
                                              [OutAttribute]Int32 *outBegIdx,
                                              [OutAttribute]Int32 *outNbElement,
                                              int           outInteger __gc [] );
         static enum TA_RetCode HT_TRENDMODE( int    startIdx,
                                              int    endIdx,
                                              float        inReal __gc [],
                                              [OutAttribute]Int32 *outBegIdx,
                                              [OutAttribute]Int32 *outNbElement,
                                              int           outInteger __gc [] );

         #define TA_HT_TRENDMODE Core::HT_TRENDMODE
         #define TA_HT_TRENDMODE_Lookback Core::HT_TRENDMODE_Lookback

         static int AD_Lookback( void );

         static enum TA_RetCode AD( int    startIdx,
                                    int    endIdx,
                                    double       inHigh __gc [],
                                    double       inLow __gc [],
                                    double       inClose __gc [],
                                    int          inVolume __gc [],
                                    [OutAttribute]Int32 *outBegIdx,
                                    [OutAttribute]Int32 *outNbElement,
                                    double        outReal __gc [] );
         static enum TA_RetCode AD( int    startIdx,
                                    int    endIdx,
                                    float        inHigh __gc [],
                                    float        inLow __gc [],
                                    float        inClose __gc [],
                                    int          inVolume __gc [],
                                    [OutAttribute]Int32 *outBegIdx,
                                    [OutAttribute]Int32 *outNbElement,
                                    double        outReal __gc [] );

         #define TA_AD Core::AD
         #define TA_AD_Lookback Core::AD_Lookback

         static int ADOSC_Lookback( int           optInFastPeriod, /* From 2 to 100000 */
                                  int           optInSlowPeriod );  /* From 2 to 100000 */

         static enum TA_RetCode ADOSC( int    startIdx,
                                       int    endIdx,
                                       double       inHigh __gc [],
                                       double       inLow __gc [],
                                       double       inClose __gc [],
                                       int          inVolume __gc [],
                                       int           optInFastPeriod, /* From 2 to 100000 */
                                       int           optInSlowPeriod, /* From 2 to 100000 */
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outReal __gc [] );
         static enum TA_RetCode ADOSC( int    startIdx,
                                       int    endIdx,
                                       float        inHigh __gc [],
                                       float        inLow __gc [],
                                       float        inClose __gc [],
                                       int          inVolume __gc [],
                                       int           optInFastPeriod, /* From 2 to 100000 */
                                       int           optInSlowPeriod, /* From 2 to 100000 */
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outReal __gc [] );

         #define TA_ADOSC Core::ADOSC
         #define TA_ADOSC_Lookback Core::ADOSC_Lookback

         static int OBV_Lookback( void );

         static enum TA_RetCode OBV( int    startIdx,
                                     int    endIdx,
                                     double       inReal __gc [],
                                     int          inVolume __gc [],
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     int           outInteger __gc [] );
         static enum TA_RetCode OBV( int    startIdx,
                                     int    endIdx,
                                     float        inReal __gc [],
                                     int          inVolume __gc [],
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     int           outInteger __gc [] );

         #define TA_OBV Core::OBV
         #define TA_OBV_Lookback Core::OBV_Lookback

         static int CDL2CROWS_Lookback( void );

         static enum TA_RetCode CDL2CROWS( int    startIdx,
                                           int    endIdx,
                                           double       inOpen __gc [],
                                           double       inHigh __gc [],
                                           double       inLow __gc [],
                                           double       inClose __gc [],
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           int           outInteger __gc [] );
         static enum TA_RetCode CDL2CROWS( int    startIdx,
                                           int    endIdx,
                                           float        inOpen __gc [],
                                           float        inHigh __gc [],
                                           float        inLow __gc [],
                                           float        inClose __gc [],
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           int           outInteger __gc [] );

         #define TA_CDL2CROWS Core::CDL2CROWS
         #define TA_CDL2CROWS_Lookback Core::CDL2CROWS_Lookback

         static int CDL3BLACKCROWS_Lookback( void );

         static enum TA_RetCode CDL3BLACKCROWS( int    startIdx,
                                                int    endIdx,
                                                double       inOpen __gc [],
                                                double       inHigh __gc [],
                                                double       inLow __gc [],
                                                double       inClose __gc [],
                                                [OutAttribute]Int32 *outBegIdx,
                                                [OutAttribute]Int32 *outNbElement,
                                                int           outInteger __gc [] );
         static enum TA_RetCode CDL3BLACKCROWS( int    startIdx,
                                                int    endIdx,
                                                float        inOpen __gc [],
                                                float        inHigh __gc [],
                                                float        inLow __gc [],
                                                float        inClose __gc [],
                                                [OutAttribute]Int32 *outBegIdx,
                                                [OutAttribute]Int32 *outNbElement,
                                                int           outInteger __gc [] );

         #define TA_CDL3BLACKCROWS Core::CDL3BLACKCROWS
         #define TA_CDL3BLACKCROWS_Lookback Core::CDL3BLACKCROWS_Lookback

         static int CDL3INSIDE_Lookback( void );

         static enum TA_RetCode CDL3INSIDE( int    startIdx,
                                            int    endIdx,
                                            double       inOpen __gc [],
                                            double       inHigh __gc [],
                                            double       inLow __gc [],
                                            double       inClose __gc [],
                                            [OutAttribute]Int32 *outBegIdx,
                                            [OutAttribute]Int32 *outNbElement,
                                            int           outInteger __gc [] );
         static enum TA_RetCode CDL3INSIDE( int    startIdx,
                                            int    endIdx,
                                            float        inOpen __gc [],
                                            float        inHigh __gc [],
                                            float        inLow __gc [],
                                            float        inClose __gc [],
                                            [OutAttribute]Int32 *outBegIdx,
                                            [OutAttribute]Int32 *outNbElement,
                                            int           outInteger __gc [] );

         #define TA_CDL3INSIDE Core::CDL3INSIDE
         #define TA_CDL3INSIDE_Lookback Core::CDL3INSIDE_Lookback

         static int CDL3LINESTRIKE_Lookback( void );

         static enum TA_RetCode CDL3LINESTRIKE( int    startIdx,
                                                int    endIdx,
                                                double       inOpen __gc [],
                                                double       inHigh __gc [],
                                                double       inLow __gc [],
                                                double       inClose __gc [],
                                                [OutAttribute]Int32 *outBegIdx,
                                                [OutAttribute]Int32 *outNbElement,
                                                int           outInteger __gc [] );
         static enum TA_RetCode CDL3LINESTRIKE( int    startIdx,
                                                int    endIdx,
                                                float        inOpen __gc [],
                                                float        inHigh __gc [],
                                                float        inLow __gc [],
                                                float        inClose __gc [],
                                                [OutAttribute]Int32 *outBegIdx,
                                                [OutAttribute]Int32 *outNbElement,
                                                int           outInteger __gc [] );

         #define TA_CDL3LINESTRIKE Core::CDL3LINESTRIKE
         #define TA_CDL3LINESTRIKE_Lookback Core::CDL3LINESTRIKE_Lookback

         static int CDL3OUTSIDE_Lookback( void );

         static enum TA_RetCode CDL3OUTSIDE( int    startIdx,
                                             int    endIdx,
                                             double       inOpen __gc [],
                                             double       inHigh __gc [],
                                             double       inLow __gc [],
                                             double       inClose __gc [],
                                             [OutAttribute]Int32 *outBegIdx,
                                             [OutAttribute]Int32 *outNbElement,
                                             int           outInteger __gc [] );
         static enum TA_RetCode CDL3OUTSIDE( int    startIdx,
                                             int    endIdx,
                                             float        inOpen __gc [],
                                             float        inHigh __gc [],
                                             float        inLow __gc [],
                                             float        inClose __gc [],
                                             [OutAttribute]Int32 *outBegIdx,
                                             [OutAttribute]Int32 *outNbElement,
                                             int           outInteger __gc [] );

         #define TA_CDL3OUTSIDE Core::CDL3OUTSIDE
         #define TA_CDL3OUTSIDE_Lookback Core::CDL3OUTSIDE_Lookback

         static int CDL3WHITESOLDIERS_Lookback( void );

         static enum TA_RetCode CDL3WHITESOLDIERS( int    startIdx,
                                                   int    endIdx,
                                                   double       inOpen __gc [],
                                                   double       inHigh __gc [],
                                                   double       inLow __gc [],
                                                   double       inClose __gc [],
                                                   [OutAttribute]Int32 *outBegIdx,
                                                   [OutAttribute]Int32 *outNbElement,
                                                   int           outInteger __gc [] );
         static enum TA_RetCode CDL3WHITESOLDIERS( int    startIdx,
                                                   int    endIdx,
                                                   float        inOpen __gc [],
                                                   float        inHigh __gc [],
                                                   float        inLow __gc [],
                                                   float        inClose __gc [],
                                                   [OutAttribute]Int32 *outBegIdx,
                                                   [OutAttribute]Int32 *outNbElement,
                                                   int           outInteger __gc [] );

         #define TA_CDL3WHITESOLDIERS Core::CDL3WHITESOLDIERS
         #define TA_CDL3WHITESOLDIERS_Lookback Core::CDL3WHITESOLDIERS_Lookback

         static int CDLABANDONEDBABY_Lookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum TA_RetCode CDLABANDONEDBABY( int    startIdx,
                                                  int    endIdx,
                                                  double       inOpen __gc [],
                                                  double       inHigh __gc [],
                                                  double       inLow __gc [],
                                                  double       inClose __gc [],
                                                  double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                  [OutAttribute]Int32 *outBegIdx,
                                                  [OutAttribute]Int32 *outNbElement,
                                                  int           outInteger __gc [] );
         static enum TA_RetCode CDLABANDONEDBABY( int    startIdx,
                                                  int    endIdx,
                                                  float        inOpen __gc [],
                                                  float        inHigh __gc [],
                                                  float        inLow __gc [],
                                                  float        inClose __gc [],
                                                  double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                  [OutAttribute]Int32 *outBegIdx,
                                                  [OutAttribute]Int32 *outNbElement,
                                                  int           outInteger __gc [] );

         #define TA_CDLABANDONEDBABY Core::CDLABANDONEDBABY
         #define TA_CDLABANDONEDBABY_Lookback Core::CDLABANDONEDBABY_Lookback

         static int CDLADVANCEBLOCK_Lookback( void );

         static enum TA_RetCode CDLADVANCEBLOCK( int    startIdx,
                                                 int    endIdx,
                                                 double       inOpen __gc [],
                                                 double       inHigh __gc [],
                                                 double       inLow __gc [],
                                                 double       inClose __gc [],
                                                 [OutAttribute]Int32 *outBegIdx,
                                                 [OutAttribute]Int32 *outNbElement,
                                                 int           outInteger __gc [] );
         static enum TA_RetCode CDLADVANCEBLOCK( int    startIdx,
                                                 int    endIdx,
                                                 float        inOpen __gc [],
                                                 float        inHigh __gc [],
                                                 float        inLow __gc [],
                                                 float        inClose __gc [],
                                                 [OutAttribute]Int32 *outBegIdx,
                                                 [OutAttribute]Int32 *outNbElement,
                                                 int           outInteger __gc [] );

         #define TA_CDLADVANCEBLOCK Core::CDLADVANCEBLOCK
         #define TA_CDLADVANCEBLOCK_Lookback Core::CDLADVANCEBLOCK_Lookback

         static int CDLDARKCLOUDCOVER_Lookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum TA_RetCode CDLDARKCLOUDCOVER( int    startIdx,
                                                   int    endIdx,
                                                   double       inOpen __gc [],
                                                   double       inHigh __gc [],
                                                   double       inLow __gc [],
                                                   double       inClose __gc [],
                                                   double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                   [OutAttribute]Int32 *outBegIdx,
                                                   [OutAttribute]Int32 *outNbElement,
                                                   int           outInteger __gc [] );
         static enum TA_RetCode CDLDARKCLOUDCOVER( int    startIdx,
                                                   int    endIdx,
                                                   float        inOpen __gc [],
                                                   float        inHigh __gc [],
                                                   float        inLow __gc [],
                                                   float        inClose __gc [],
                                                   double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                   [OutAttribute]Int32 *outBegIdx,
                                                   [OutAttribute]Int32 *outNbElement,
                                                   int           outInteger __gc [] );

         #define TA_CDLDARKCLOUDCOVER Core::CDLDARKCLOUDCOVER
         #define TA_CDLDARKCLOUDCOVER_Lookback Core::CDLDARKCLOUDCOVER_Lookback

         static int CDLDOJISTAR_Lookback( void );

         static enum TA_RetCode CDLDOJISTAR( int    startIdx,
                                             int    endIdx,
                                             double       inOpen __gc [],
                                             double       inHigh __gc [],
                                             double       inLow __gc [],
                                             double       inClose __gc [],
                                             [OutAttribute]Int32 *outBegIdx,
                                             [OutAttribute]Int32 *outNbElement,
                                             int           outInteger __gc [] );
         static enum TA_RetCode CDLDOJISTAR( int    startIdx,
                                             int    endIdx,
                                             float        inOpen __gc [],
                                             float        inHigh __gc [],
                                             float        inLow __gc [],
                                             float        inClose __gc [],
                                             [OutAttribute]Int32 *outBegIdx,
                                             [OutAttribute]Int32 *outNbElement,
                                             int           outInteger __gc [] );

         #define TA_CDLDOJISTAR Core::CDLDOJISTAR
         #define TA_CDLDOJISTAR_Lookback Core::CDLDOJISTAR_Lookback

         static int CDLENGULFING_Lookback( void );

         static enum TA_RetCode CDLENGULFING( int    startIdx,
                                              int    endIdx,
                                              double       inOpen __gc [],
                                              double       inHigh __gc [],
                                              double       inLow __gc [],
                                              double       inClose __gc [],
                                              [OutAttribute]Int32 *outBegIdx,
                                              [OutAttribute]Int32 *outNbElement,
                                              int           outInteger __gc [] );
         static enum TA_RetCode CDLENGULFING( int    startIdx,
                                              int    endIdx,
                                              float        inOpen __gc [],
                                              float        inHigh __gc [],
                                              float        inLow __gc [],
                                              float        inClose __gc [],
                                              [OutAttribute]Int32 *outBegIdx,
                                              [OutAttribute]Int32 *outNbElement,
                                              int           outInteger __gc [] );

         #define TA_CDLENGULFING Core::CDLENGULFING
         #define TA_CDLENGULFING_Lookback Core::CDLENGULFING_Lookback

         static int CDLEVENINGDOJISTAR_Lookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum TA_RetCode CDLEVENINGDOJISTAR( int    startIdx,
                                                    int    endIdx,
                                                    double       inOpen __gc [],
                                                    double       inHigh __gc [],
                                                    double       inLow __gc [],
                                                    double       inClose __gc [],
                                                    double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                    [OutAttribute]Int32 *outBegIdx,
                                                    [OutAttribute]Int32 *outNbElement,
                                                    int           outInteger __gc [] );
         static enum TA_RetCode CDLEVENINGDOJISTAR( int    startIdx,
                                                    int    endIdx,
                                                    float        inOpen __gc [],
                                                    float        inHigh __gc [],
                                                    float        inLow __gc [],
                                                    float        inClose __gc [],
                                                    double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                    [OutAttribute]Int32 *outBegIdx,
                                                    [OutAttribute]Int32 *outNbElement,
                                                    int           outInteger __gc [] );

         #define TA_CDLEVENINGDOJISTAR Core::CDLEVENINGDOJISTAR
         #define TA_CDLEVENINGDOJISTAR_Lookback Core::CDLEVENINGDOJISTAR_Lookback

         static int CDLEVENINGSTAR_Lookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum TA_RetCode CDLEVENINGSTAR( int    startIdx,
                                                int    endIdx,
                                                double       inOpen __gc [],
                                                double       inHigh __gc [],
                                                double       inLow __gc [],
                                                double       inClose __gc [],
                                                double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                [OutAttribute]Int32 *outBegIdx,
                                                [OutAttribute]Int32 *outNbElement,
                                                int           outInteger __gc [] );
         static enum TA_RetCode CDLEVENINGSTAR( int    startIdx,
                                                int    endIdx,
                                                float        inOpen __gc [],
                                                float        inHigh __gc [],
                                                float        inLow __gc [],
                                                float        inClose __gc [],
                                                double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                [OutAttribute]Int32 *outBegIdx,
                                                [OutAttribute]Int32 *outNbElement,
                                                int           outInteger __gc [] );

         #define TA_CDLEVENINGSTAR Core::CDLEVENINGSTAR
         #define TA_CDLEVENINGSTAR_Lookback Core::CDLEVENINGSTAR_Lookback

         static int CDLHAMMER_Lookback( void );

         static enum TA_RetCode CDLHAMMER( int    startIdx,
                                           int    endIdx,
                                           double       inOpen __gc [],
                                           double       inHigh __gc [],
                                           double       inLow __gc [],
                                           double       inClose __gc [],
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           int           outInteger __gc [] );
         static enum TA_RetCode CDLHAMMER( int    startIdx,
                                           int    endIdx,
                                           float        inOpen __gc [],
                                           float        inHigh __gc [],
                                           float        inLow __gc [],
                                           float        inClose __gc [],
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           int           outInteger __gc [] );

         #define TA_CDLHAMMER Core::CDLHAMMER
         #define TA_CDLHAMMER_Lookback Core::CDLHAMMER_Lookback

         static int CDLHANGINGMAN_Lookback( void );

         static enum TA_RetCode CDLHANGINGMAN( int    startIdx,
                                               int    endIdx,
                                               double       inOpen __gc [],
                                               double       inHigh __gc [],
                                               double       inLow __gc [],
                                               double       inClose __gc [],
                                               [OutAttribute]Int32 *outBegIdx,
                                               [OutAttribute]Int32 *outNbElement,
                                               int           outInteger __gc [] );
         static enum TA_RetCode CDLHANGINGMAN( int    startIdx,
                                               int    endIdx,
                                               float        inOpen __gc [],
                                               float        inHigh __gc [],
                                               float        inLow __gc [],
                                               float        inClose __gc [],
                                               [OutAttribute]Int32 *outBegIdx,
                                               [OutAttribute]Int32 *outNbElement,
                                               int           outInteger __gc [] );

         #define TA_CDLHANGINGMAN Core::CDLHANGINGMAN
         #define TA_CDLHANGINGMAN_Lookback Core::CDLHANGINGMAN_Lookback

         static int CDLHARAMI_Lookback( void );

         static enum TA_RetCode CDLHARAMI( int    startIdx,
                                           int    endIdx,
                                           double       inOpen __gc [],
                                           double       inHigh __gc [],
                                           double       inLow __gc [],
                                           double       inClose __gc [],
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           int           outInteger __gc [] );
         static enum TA_RetCode CDLHARAMI( int    startIdx,
                                           int    endIdx,
                                           float        inOpen __gc [],
                                           float        inHigh __gc [],
                                           float        inLow __gc [],
                                           float        inClose __gc [],
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           int           outInteger __gc [] );

         #define TA_CDLHARAMI Core::CDLHARAMI
         #define TA_CDLHARAMI_Lookback Core::CDLHARAMI_Lookback

         static int CDLHARAMICROSS_Lookback( void );

         static enum TA_RetCode CDLHARAMICROSS( int    startIdx,
                                                int    endIdx,
                                                double       inOpen __gc [],
                                                double       inHigh __gc [],
                                                double       inLow __gc [],
                                                double       inClose __gc [],
                                                [OutAttribute]Int32 *outBegIdx,
                                                [OutAttribute]Int32 *outNbElement,
                                                int           outInteger __gc [] );
         static enum TA_RetCode CDLHARAMICROSS( int    startIdx,
                                                int    endIdx,
                                                float        inOpen __gc [],
                                                float        inHigh __gc [],
                                                float        inLow __gc [],
                                                float        inClose __gc [],
                                                [OutAttribute]Int32 *outBegIdx,
                                                [OutAttribute]Int32 *outNbElement,
                                                int           outInteger __gc [] );

         #define TA_CDLHARAMICROSS Core::CDLHARAMICROSS
         #define TA_CDLHARAMICROSS_Lookback Core::CDLHARAMICROSS_Lookback

         static int CDLHIGHWAVE_Lookback( void );

         static enum TA_RetCode CDLHIGHWAVE( int    startIdx,
                                             int    endIdx,
                                             double       inOpen __gc [],
                                             double       inHigh __gc [],
                                             double       inLow __gc [],
                                             double       inClose __gc [],
                                             [OutAttribute]Int32 *outBegIdx,
                                             [OutAttribute]Int32 *outNbElement,
                                             int           outInteger __gc [] );
         static enum TA_RetCode CDLHIGHWAVE( int    startIdx,
                                             int    endIdx,
                                             float        inOpen __gc [],
                                             float        inHigh __gc [],
                                             float        inLow __gc [],
                                             float        inClose __gc [],
                                             [OutAttribute]Int32 *outBegIdx,
                                             [OutAttribute]Int32 *outNbElement,
                                             int           outInteger __gc [] );

         #define TA_CDLHIGHWAVE Core::CDLHIGHWAVE
         #define TA_CDLHIGHWAVE_Lookback Core::CDLHIGHWAVE_Lookback

         static int CDLIDENTICAL3CROWS_Lookback( void );

         static enum TA_RetCode CDLIDENTICAL3CROWS( int    startIdx,
                                                    int    endIdx,
                                                    double       inOpen __gc [],
                                                    double       inHigh __gc [],
                                                    double       inLow __gc [],
                                                    double       inClose __gc [],
                                                    [OutAttribute]Int32 *outBegIdx,
                                                    [OutAttribute]Int32 *outNbElement,
                                                    int           outInteger __gc [] );
         static enum TA_RetCode CDLIDENTICAL3CROWS( int    startIdx,
                                                    int    endIdx,
                                                    float        inOpen __gc [],
                                                    float        inHigh __gc [],
                                                    float        inLow __gc [],
                                                    float        inClose __gc [],
                                                    [OutAttribute]Int32 *outBegIdx,
                                                    [OutAttribute]Int32 *outNbElement,
                                                    int           outInteger __gc [] );

         #define TA_CDLIDENTICAL3CROWS Core::CDLIDENTICAL3CROWS
         #define TA_CDLIDENTICAL3CROWS_Lookback Core::CDLIDENTICAL3CROWS_Lookback

         static int CDLINNECK_Lookback( void );

         static enum TA_RetCode CDLINNECK( int    startIdx,
                                           int    endIdx,
                                           double       inOpen __gc [],
                                           double       inHigh __gc [],
                                           double       inLow __gc [],
                                           double       inClose __gc [],
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           int           outInteger __gc [] );
         static enum TA_RetCode CDLINNECK( int    startIdx,
                                           int    endIdx,
                                           float        inOpen __gc [],
                                           float        inHigh __gc [],
                                           float        inLow __gc [],
                                           float        inClose __gc [],
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           int           outInteger __gc [] );

         #define TA_CDLINNECK Core::CDLINNECK
         #define TA_CDLINNECK_Lookback Core::CDLINNECK_Lookback

         static int CDLINVERTEDHAMMER_Lookback( void );

         static enum TA_RetCode CDLINVERTEDHAMMER( int    startIdx,
                                                   int    endIdx,
                                                   double       inOpen __gc [],
                                                   double       inHigh __gc [],
                                                   double       inLow __gc [],
                                                   double       inClose __gc [],
                                                   [OutAttribute]Int32 *outBegIdx,
                                                   [OutAttribute]Int32 *outNbElement,
                                                   int           outInteger __gc [] );
         static enum TA_RetCode CDLINVERTEDHAMMER( int    startIdx,
                                                   int    endIdx,
                                                   float        inOpen __gc [],
                                                   float        inHigh __gc [],
                                                   float        inLow __gc [],
                                                   float        inClose __gc [],
                                                   [OutAttribute]Int32 *outBegIdx,
                                                   [OutAttribute]Int32 *outNbElement,
                                                   int           outInteger __gc [] );

         #define TA_CDLINVERTEDHAMMER Core::CDLINVERTEDHAMMER
         #define TA_CDLINVERTEDHAMMER_Lookback Core::CDLINVERTEDHAMMER_Lookback

         static int CDLLONGLINE_Lookback( void );

         static enum TA_RetCode CDLLONGLINE( int    startIdx,
                                             int    endIdx,
                                             double       inOpen __gc [],
                                             double       inHigh __gc [],
                                             double       inLow __gc [],
                                             double       inClose __gc [],
                                             [OutAttribute]Int32 *outBegIdx,
                                             [OutAttribute]Int32 *outNbElement,
                                             int           outInteger __gc [] );
         static enum TA_RetCode CDLLONGLINE( int    startIdx,
                                             int    endIdx,
                                             float        inOpen __gc [],
                                             float        inHigh __gc [],
                                             float        inLow __gc [],
                                             float        inClose __gc [],
                                             [OutAttribute]Int32 *outBegIdx,
                                             [OutAttribute]Int32 *outNbElement,
                                             int           outInteger __gc [] );

         #define TA_CDLLONGLINE Core::CDLLONGLINE
         #define TA_CDLLONGLINE_Lookback Core::CDLLONGLINE_Lookback

         static int CDLMORNINGDOJISTAR_Lookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum TA_RetCode CDLMORNINGDOJISTAR( int    startIdx,
                                                    int    endIdx,
                                                    double       inOpen __gc [],
                                                    double       inHigh __gc [],
                                                    double       inLow __gc [],
                                                    double       inClose __gc [],
                                                    double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                    [OutAttribute]Int32 *outBegIdx,
                                                    [OutAttribute]Int32 *outNbElement,
                                                    int           outInteger __gc [] );
         static enum TA_RetCode CDLMORNINGDOJISTAR( int    startIdx,
                                                    int    endIdx,
                                                    float        inOpen __gc [],
                                                    float        inHigh __gc [],
                                                    float        inLow __gc [],
                                                    float        inClose __gc [],
                                                    double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                    [OutAttribute]Int32 *outBegIdx,
                                                    [OutAttribute]Int32 *outNbElement,
                                                    int           outInteger __gc [] );

         #define TA_CDLMORNINGDOJISTAR Core::CDLMORNINGDOJISTAR
         #define TA_CDLMORNINGDOJISTAR_Lookback Core::CDLMORNINGDOJISTAR_Lookback

         static int CDLMORNINGSTAR_Lookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum TA_RetCode CDLMORNINGSTAR( int    startIdx,
                                                int    endIdx,
                                                double       inOpen __gc [],
                                                double       inHigh __gc [],
                                                double       inLow __gc [],
                                                double       inClose __gc [],
                                                double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                [OutAttribute]Int32 *outBegIdx,
                                                [OutAttribute]Int32 *outNbElement,
                                                int           outInteger __gc [] );
         static enum TA_RetCode CDLMORNINGSTAR( int    startIdx,
                                                int    endIdx,
                                                float        inOpen __gc [],
                                                float        inHigh __gc [],
                                                float        inLow __gc [],
                                                float        inClose __gc [],
                                                double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                [OutAttribute]Int32 *outBegIdx,
                                                [OutAttribute]Int32 *outNbElement,
                                                int           outInteger __gc [] );

         #define TA_CDLMORNINGSTAR Core::CDLMORNINGSTAR
         #define TA_CDLMORNINGSTAR_Lookback Core::CDLMORNINGSTAR_Lookback

         static int CDLONNECK_Lookback( void );

         static enum TA_RetCode CDLONNECK( int    startIdx,
                                           int    endIdx,
                                           double       inOpen __gc [],
                                           double       inHigh __gc [],
                                           double       inLow __gc [],
                                           double       inClose __gc [],
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           int           outInteger __gc [] );
         static enum TA_RetCode CDLONNECK( int    startIdx,
                                           int    endIdx,
                                           float        inOpen __gc [],
                                           float        inHigh __gc [],
                                           float        inLow __gc [],
                                           float        inClose __gc [],
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           int           outInteger __gc [] );

         #define TA_CDLONNECK Core::CDLONNECK
         #define TA_CDLONNECK_Lookback Core::CDLONNECK_Lookback

         static int CDLPIERCING_Lookback( void );

         static enum TA_RetCode CDLPIERCING( int    startIdx,
                                             int    endIdx,
                                             double       inOpen __gc [],
                                             double       inHigh __gc [],
                                             double       inLow __gc [],
                                             double       inClose __gc [],
                                             [OutAttribute]Int32 *outBegIdx,
                                             [OutAttribute]Int32 *outNbElement,
                                             int           outInteger __gc [] );
         static enum TA_RetCode CDLPIERCING( int    startIdx,
                                             int    endIdx,
                                             float        inOpen __gc [],
                                             float        inHigh __gc [],
                                             float        inLow __gc [],
                                             float        inClose __gc [],
                                             [OutAttribute]Int32 *outBegIdx,
                                             [OutAttribute]Int32 *outNbElement,
                                             int           outInteger __gc [] );

         #define TA_CDLPIERCING Core::CDLPIERCING
         #define TA_CDLPIERCING_Lookback Core::CDLPIERCING_Lookback

         static int CDLSHOOTINGSTAR_Lookback( void );

         static enum TA_RetCode CDLSHOOTINGSTAR( int    startIdx,
                                                 int    endIdx,
                                                 double       inOpen __gc [],
                                                 double       inHigh __gc [],
                                                 double       inLow __gc [],
                                                 double       inClose __gc [],
                                                 [OutAttribute]Int32 *outBegIdx,
                                                 [OutAttribute]Int32 *outNbElement,
                                                 int           outInteger __gc [] );
         static enum TA_RetCode CDLSHOOTINGSTAR( int    startIdx,
                                                 int    endIdx,
                                                 float        inOpen __gc [],
                                                 float        inHigh __gc [],
                                                 float        inLow __gc [],
                                                 float        inClose __gc [],
                                                 [OutAttribute]Int32 *outBegIdx,
                                                 [OutAttribute]Int32 *outNbElement,
                                                 int           outInteger __gc [] );

         #define TA_CDLSHOOTINGSTAR Core::CDLSHOOTINGSTAR
         #define TA_CDLSHOOTINGSTAR_Lookback Core::CDLSHOOTINGSTAR_Lookback

         static int CDLSHORTLINE_Lookback( void );

         static enum TA_RetCode CDLSHORTLINE( int    startIdx,
                                              int    endIdx,
                                              double       inOpen __gc [],
                                              double       inHigh __gc [],
                                              double       inLow __gc [],
                                              double       inClose __gc [],
                                              [OutAttribute]Int32 *outBegIdx,
                                              [OutAttribute]Int32 *outNbElement,
                                              int           outInteger __gc [] );
         static enum TA_RetCode CDLSHORTLINE( int    startIdx,
                                              int    endIdx,
                                              float        inOpen __gc [],
                                              float        inHigh __gc [],
                                              float        inLow __gc [],
                                              float        inClose __gc [],
                                              [OutAttribute]Int32 *outBegIdx,
                                              [OutAttribute]Int32 *outNbElement,
                                              int           outInteger __gc [] );

         #define TA_CDLSHORTLINE Core::CDLSHORTLINE
         #define TA_CDLSHORTLINE_Lookback Core::CDLSHORTLINE_Lookback

         static int CDLSPINNINGTOP_Lookback( void );

         static enum TA_RetCode CDLSPINNINGTOP( int    startIdx,
                                                int    endIdx,
                                                double       inOpen __gc [],
                                                double       inHigh __gc [],
                                                double       inLow __gc [],
                                                double       inClose __gc [],
                                                [OutAttribute]Int32 *outBegIdx,
                                                [OutAttribute]Int32 *outNbElement,
                                                int           outInteger __gc [] );
         static enum TA_RetCode CDLSPINNINGTOP( int    startIdx,
                                                int    endIdx,
                                                float        inOpen __gc [],
                                                float        inHigh __gc [],
                                                float        inLow __gc [],
                                                float        inClose __gc [],
                                                [OutAttribute]Int32 *outBegIdx,
                                                [OutAttribute]Int32 *outNbElement,
                                                int           outInteger __gc [] );

         #define TA_CDLSPINNINGTOP Core::CDLSPINNINGTOP
         #define TA_CDLSPINNINGTOP_Lookback Core::CDLSPINNINGTOP_Lookback

         static int CDLSTALLEDPATTERN_Lookback( void );

         static enum TA_RetCode CDLSTALLEDPATTERN( int    startIdx,
                                                   int    endIdx,
                                                   double       inOpen __gc [],
                                                   double       inHigh __gc [],
                                                   double       inLow __gc [],
                                                   double       inClose __gc [],
                                                   [OutAttribute]Int32 *outBegIdx,
                                                   [OutAttribute]Int32 *outNbElement,
                                                   int           outInteger __gc [] );
         static enum TA_RetCode CDLSTALLEDPATTERN( int    startIdx,
                                                   int    endIdx,
                                                   float        inOpen __gc [],
                                                   float        inHigh __gc [],
                                                   float        inLow __gc [],
                                                   float        inClose __gc [],
                                                   [OutAttribute]Int32 *outBegIdx,
                                                   [OutAttribute]Int32 *outNbElement,
                                                   int           outInteger __gc [] );

         #define TA_CDLSTALLEDPATTERN Core::CDLSTALLEDPATTERN
         #define TA_CDLSTALLEDPATTERN_Lookback Core::CDLSTALLEDPATTERN_Lookback

         static int CDLTHRUSTING_Lookback( void );

         static enum TA_RetCode CDLTHRUSTING( int    startIdx,
                                              int    endIdx,
                                              double       inOpen __gc [],
                                              double       inHigh __gc [],
                                              double       inLow __gc [],
                                              double       inClose __gc [],
                                              [OutAttribute]Int32 *outBegIdx,
                                              [OutAttribute]Int32 *outNbElement,
                                              int           outInteger __gc [] );
         static enum TA_RetCode CDLTHRUSTING( int    startIdx,
                                              int    endIdx,
                                              float        inOpen __gc [],
                                              float        inHigh __gc [],
                                              float        inLow __gc [],
                                              float        inClose __gc [],
                                              [OutAttribute]Int32 *outBegIdx,
                                              [OutAttribute]Int32 *outNbElement,
                                              int           outInteger __gc [] );

         #define TA_CDLTHRUSTING Core::CDLTHRUSTING
         #define TA_CDLTHRUSTING_Lookback Core::CDLTHRUSTING_Lookback

         static int CDLTRISTAR_Lookback( void );

         static enum TA_RetCode CDLTRISTAR( int    startIdx,
                                            int    endIdx,
                                            double       inOpen __gc [],
                                            double       inHigh __gc [],
                                            double       inLow __gc [],
                                            double       inClose __gc [],
                                            [OutAttribute]Int32 *outBegIdx,
                                            [OutAttribute]Int32 *outNbElement,
                                            int           outInteger __gc [] );
         static enum TA_RetCode CDLTRISTAR( int    startIdx,
                                            int    endIdx,
                                            float        inOpen __gc [],
                                            float        inHigh __gc [],
                                            float        inLow __gc [],
                                            float        inClose __gc [],
                                            [OutAttribute]Int32 *outBegIdx,
                                            [OutAttribute]Int32 *outNbElement,
                                            int           outInteger __gc [] );

         #define TA_CDLTRISTAR Core::CDLTRISTAR
         #define TA_CDLTRISTAR_Lookback Core::CDLTRISTAR_Lookback

         static int CDLUPSIDEGAP2CROWS_Lookback( void );

         static enum TA_RetCode CDLUPSIDEGAP2CROWS( int    startIdx,
                                                    int    endIdx,
                                                    double       inOpen __gc [],
                                                    double       inHigh __gc [],
                                                    double       inLow __gc [],
                                                    double       inClose __gc [],
                                                    [OutAttribute]Int32 *outBegIdx,
                                                    [OutAttribute]Int32 *outNbElement,
                                                    int           outInteger __gc [] );
         static enum TA_RetCode CDLUPSIDEGAP2CROWS( int    startIdx,
                                                    int    endIdx,
                                                    float        inOpen __gc [],
                                                    float        inHigh __gc [],
                                                    float        inLow __gc [],
                                                    float        inClose __gc [],
                                                    [OutAttribute]Int32 *outBegIdx,
                                                    [OutAttribute]Int32 *outNbElement,
                                                    int           outInteger __gc [] );

         #define TA_CDLUPSIDEGAP2CROWS Core::CDLUPSIDEGAP2CROWS
         #define TA_CDLUPSIDEGAP2CROWS_Lookback Core::CDLUPSIDEGAP2CROWS_Lookback

         static int CORREL_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum TA_RetCode CORREL( int    startIdx,
                                        int    endIdx,
                                        double       inReal0 __gc [],
                                        double       inReal1 __gc [],
                                        int           optInTimePeriod, /* From 1 to 100000 */
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outReal __gc [] );
         static enum TA_RetCode CORREL( int    startIdx,
                                        int    endIdx,
                                        float        inReal0 __gc [],
                                        float        inReal1 __gc [],
                                        int           optInTimePeriod, /* From 1 to 100000 */
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outReal __gc [] );

         #define TA_CORREL Core::CORREL
         #define TA_CORREL_Lookback Core::CORREL_Lookback

         static int LINEARREG_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode LINEARREG( int    startIdx,
                                           int    endIdx,
                                           double       inReal __gc [],
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           double        outReal __gc [] );
         static enum TA_RetCode LINEARREG( int    startIdx,
                                           int    endIdx,
                                           float        inReal __gc [],
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           double        outReal __gc [] );

         #define TA_LINEARREG Core::LINEARREG
         #define TA_LINEARREG_Lookback Core::LINEARREG_Lookback

         static int LINEARREG_SLOPE_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode LINEARREG_SLOPE( int    startIdx,
                                                 int    endIdx,
                                                 double       inReal __gc [],
                                                 int           optInTimePeriod, /* From 2 to 100000 */
                                                 [OutAttribute]Int32 *outBegIdx,
                                                 [OutAttribute]Int32 *outNbElement,
                                                 double        outReal __gc [] );
         static enum TA_RetCode LINEARREG_SLOPE( int    startIdx,
                                                 int    endIdx,
                                                 float        inReal __gc [],
                                                 int           optInTimePeriod, /* From 2 to 100000 */
                                                 [OutAttribute]Int32 *outBegIdx,
                                                 [OutAttribute]Int32 *outNbElement,
                                                 double        outReal __gc [] );

         #define TA_LINEARREG_SLOPE Core::LINEARREG_SLOPE
         #define TA_LINEARREG_SLOPE_Lookback Core::LINEARREG_SLOPE_Lookback

         static int LINEARREG_ANGLE_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode LINEARREG_ANGLE( int    startIdx,
                                                 int    endIdx,
                                                 double       inReal __gc [],
                                                 int           optInTimePeriod, /* From 2 to 100000 */
                                                 [OutAttribute]Int32 *outBegIdx,
                                                 [OutAttribute]Int32 *outNbElement,
                                                 double        outReal __gc [] );
         static enum TA_RetCode LINEARREG_ANGLE( int    startIdx,
                                                 int    endIdx,
                                                 float        inReal __gc [],
                                                 int           optInTimePeriod, /* From 2 to 100000 */
                                                 [OutAttribute]Int32 *outBegIdx,
                                                 [OutAttribute]Int32 *outNbElement,
                                                 double        outReal __gc [] );

         #define TA_LINEARREG_ANGLE Core::LINEARREG_ANGLE
         #define TA_LINEARREG_ANGLE_Lookback Core::LINEARREG_ANGLE_Lookback

         static int LINEARREG_INTERCEPT_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode LINEARREG_INTERCEPT( int    startIdx,
                                                     int    endIdx,
                                                     double       inReal __gc [],
                                                     int           optInTimePeriod, /* From 2 to 100000 */
                                                     [OutAttribute]Int32 *outBegIdx,
                                                     [OutAttribute]Int32 *outNbElement,
                                                     double        outReal __gc [] );
         static enum TA_RetCode LINEARREG_INTERCEPT( int    startIdx,
                                                     int    endIdx,
                                                     float        inReal __gc [],
                                                     int           optInTimePeriod, /* From 2 to 100000 */
                                                     [OutAttribute]Int32 *outBegIdx,
                                                     [OutAttribute]Int32 *outNbElement,
                                                     double        outReal __gc [] );

         #define TA_LINEARREG_INTERCEPT Core::LINEARREG_INTERCEPT
         #define TA_LINEARREG_INTERCEPT_Lookback Core::LINEARREG_INTERCEPT_Lookback

         static int STDDEV_Lookback( int           optInTimePeriod, /* From 2 to 100000 */
                                   double        optInNbDev );  /* From TA_REAL_MIN to TA_REAL_MAX */

         static enum TA_RetCode STDDEV( int    startIdx,
                                        int    endIdx,
                                        double       inReal __gc [],
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        double        optInNbDev, /* From TA_REAL_MIN to TA_REAL_MAX */
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outReal __gc [] );
         static enum TA_RetCode STDDEV( int    startIdx,
                                        int    endIdx,
                                        float        inReal __gc [],
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        double        optInNbDev, /* From TA_REAL_MIN to TA_REAL_MAX */
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outReal __gc [] );

         #define TA_STDDEV Core::STDDEV
         #define TA_STDDEV_Lookback Core::STDDEV_Lookback

         static int TSF_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum TA_RetCode TSF( int    startIdx,
                                     int    endIdx,
                                     double       inReal __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );
         static enum TA_RetCode TSF( int    startIdx,
                                     int    endIdx,
                                     float        inReal __gc [],
                                     int           optInTimePeriod, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );

         #define TA_TSF Core::TSF
         #define TA_TSF_Lookback Core::TSF_Lookback

         static int VAR_Lookback( int           optInTimePeriod, /* From 1 to 100000 */
                                double        optInNbDev );  /* From TA_REAL_MIN to TA_REAL_MAX */

         static enum TA_RetCode VAR( int    startIdx,
                                     int    endIdx,
                                     double       inReal __gc [],
                                     int           optInTimePeriod, /* From 1 to 100000 */
                                     double        optInNbDev, /* From TA_REAL_MIN to TA_REAL_MAX */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );
         static enum TA_RetCode VAR( int    startIdx,
                                     int    endIdx,
                                     float        inReal __gc [],
                                     int           optInTimePeriod, /* From 1 to 100000 */
                                     double        optInNbDev, /* From TA_REAL_MIN to TA_REAL_MAX */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal __gc [] );

         #define TA_VAR Core::VAR
         #define TA_VAR_Lookback Core::VAR_Lookback

         static int AVGPRICE_Lookback( void );

         static enum TA_RetCode AVGPRICE( int    startIdx,
                                          int    endIdx,
                                          double       inOpen __gc [],
                                          double       inHigh __gc [],
                                          double       inLow __gc [],
                                          double       inClose __gc [],
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );
         static enum TA_RetCode AVGPRICE( int    startIdx,
                                          int    endIdx,
                                          float        inOpen __gc [],
                                          float        inHigh __gc [],
                                          float        inLow __gc [],
                                          float        inClose __gc [],
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );

         #define TA_AVGPRICE Core::AVGPRICE
         #define TA_AVGPRICE_Lookback Core::AVGPRICE_Lookback

         static int MEDPRICE_Lookback( void );

         static enum TA_RetCode MEDPRICE( int    startIdx,
                                          int    endIdx,
                                          double       inHigh __gc [],
                                          double       inLow __gc [],
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );
         static enum TA_RetCode MEDPRICE( int    startIdx,
                                          int    endIdx,
                                          float        inHigh __gc [],
                                          float        inLow __gc [],
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );

         #define TA_MEDPRICE Core::MEDPRICE
         #define TA_MEDPRICE_Lookback Core::MEDPRICE_Lookback

         static int TYPPRICE_Lookback( void );

         static enum TA_RetCode TYPPRICE( int    startIdx,
                                          int    endIdx,
                                          double       inHigh __gc [],
                                          double       inLow __gc [],
                                          double       inClose __gc [],
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );
         static enum TA_RetCode TYPPRICE( int    startIdx,
                                          int    endIdx,
                                          float        inHigh __gc [],
                                          float        inLow __gc [],
                                          float        inClose __gc [],
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );

         #define TA_TYPPRICE Core::TYPPRICE
         #define TA_TYPPRICE_Lookback Core::TYPPRICE_Lookback

         static int WCLPRICE_Lookback( void );

         static enum TA_RetCode WCLPRICE( int    startIdx,
                                          int    endIdx,
                                          double       inHigh __gc [],
                                          double       inLow __gc [],
                                          double       inClose __gc [],
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );
         static enum TA_RetCode WCLPRICE( int    startIdx,
                                          int    endIdx,
                                          float        inHigh __gc [],
                                          float        inLow __gc [],
                                          float        inClose __gc [],
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal __gc [] );

         #define TA_WCLPRICE Core::WCLPRICE
         #define TA_WCLPRICE_Lookback Core::WCLPRICE_Lookback

/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/

  	   };
   }
}


