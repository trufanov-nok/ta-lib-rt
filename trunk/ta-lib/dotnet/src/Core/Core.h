/* TA-LIB Copyright (c) 1999-2003, Mario Fortier
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
 *
 *
 * Change history:
 *
 *  MMDDYY BY   Description
 *  -------------------------------------------------------------------
 *  050703 MF   First version with all the TA functions.
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
         __gc __sealed class TA_GlobalsType
         {
         public:
            TA_GlobalsType()
            {
               unstablePeriod = new unsigned int __gc [TA_FUNC_UNST_ALL];
               compatibility = 0;
               for( int i=0; i < TA_FUNC_UNST_ALL; i++ )
                  unstablePeriod[i] = 0;
            }

            /* For handling the compatibility with other software */
            int compatibility;

            /* For handling the unstable period of some TA function. */
            unsigned int unstablePeriod __gc [];
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
         }

         static enum TA_RetCode SetUnstablePeriod( enum TA_FuncUnstId id,
                                                   unsigned int  unstablePeriod );

         static unsigned int GetUnstablePeriod( TA_FuncUnstId id );

         static enum TA_RetCode       SetCompatibility( enum TA_Compatibility value );
         static enum TA_Compatibility GetCompatibility( void );

/**** START GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
         static int MAX_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode MAX( int    startIdx,
                                     int    endIdx,
                                     double       inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );
         static enum TA_RetCode MAX( int    startIdx,
                                     int    endIdx,
                                     float        inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );

         #define TA_MAX Core::MAX
         #define TA_MAX_Lookback Core::MAX_Lookback

         static int MIN_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode MIN( int    startIdx,
                                     int    endIdx,
                                     double       inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );
         static enum TA_RetCode MIN( int    startIdx,
                                     int    endIdx,
                                     float        inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );

         #define TA_MIN Core::MIN
         #define TA_MIN_Lookback Core::MIN_Lookback

         static int BBANDS_Lookback( int           optInTimePeriod_0, /* From 2 to 100000 */
                                   double        optInNbDevUp_1, /* From TA_REAL_MIN to TA_REAL_MAX */
                                   double        optInNbDevDn_2, /* From TA_REAL_MIN to TA_REAL_MAX */
                                   TA_MAType     optInMAType_3 ); 
         static enum TA_RetCode BBANDS( int    startIdx,
                                        int    endIdx,
                                        double       inReal_0 __gc [],
                                        int           optInTimePeriod_0, /* From 2 to 100000 */
                                        double        optInNbDevUp_1, /* From TA_REAL_MIN to TA_REAL_MAX */
                                        double        optInNbDevDn_2, /* From TA_REAL_MIN to TA_REAL_MAX */
                                        TA_MAType     optInMAType_3,
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outRealUpperBand_0 __gc [],
                                        double        outRealMiddleBand_1 __gc [],
                                        double        outRealLowerBand_2 __gc [] );
         static enum TA_RetCode BBANDS( int    startIdx,
                                        int    endIdx,
                                        float        inReal_0 __gc [],
                                        int           optInTimePeriod_0, /* From 2 to 100000 */
                                        double        optInNbDevUp_1, /* From TA_REAL_MIN to TA_REAL_MAX */
                                        double        optInNbDevDn_2, /* From TA_REAL_MIN to TA_REAL_MAX */
                                        TA_MAType     optInMAType_3,
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outRealUpperBand_0 __gc [],
                                        double        outRealMiddleBand_1 __gc [],
                                        double        outRealLowerBand_2 __gc [] );

         #define TA_BBANDS Core::BBANDS
         #define TA_BBANDS_Lookback Core::BBANDS_Lookback

         static int DEMA_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode DEMA( int    startIdx,
                                      int    endIdx,
                                      double       inReal_0 __gc [],
                                      int           optInTimePeriod_0, /* From 2 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal_0 __gc [] );
         static enum TA_RetCode DEMA( int    startIdx,
                                      int    endIdx,
                                      float        inReal_0 __gc [],
                                      int           optInTimePeriod_0, /* From 2 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal_0 __gc [] );

         #define TA_DEMA Core::DEMA
         #define TA_DEMA_Lookback Core::DEMA_Lookback

         static int EMA_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode EMA( int    startIdx,
                                     int    endIdx,
                                     double       inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );
         static enum TA_RetCode EMA( int    startIdx,
                                     int    endIdx,
                                     float        inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );

         #define TA_EMA Core::EMA
         #define TA_EMA_Lookback Core::EMA_Lookback

         static int HT_TRENDLINE_Lookback( void );

         static enum TA_RetCode HT_TRENDLINE( int    startIdx,
                                              int    endIdx,
                                              double       inReal_0 __gc [],
                                              [OutAttribute]Int32 *outBegIdx,
                                              [OutAttribute]Int32 *outNbElement,
                                              double        outReal_0 __gc [] );
         static enum TA_RetCode HT_TRENDLINE( int    startIdx,
                                              int    endIdx,
                                              float        inReal_0 __gc [],
                                              [OutAttribute]Int32 *outBegIdx,
                                              [OutAttribute]Int32 *outNbElement,
                                              double        outReal_0 __gc [] );

         #define TA_HT_TRENDLINE Core::HT_TRENDLINE
         #define TA_HT_TRENDLINE_Lookback Core::HT_TRENDLINE_Lookback

         static int KAMA_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode KAMA( int    startIdx,
                                      int    endIdx,
                                      double       inReal_0 __gc [],
                                      int           optInTimePeriod_0, /* From 2 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal_0 __gc [] );
         static enum TA_RetCode KAMA( int    startIdx,
                                      int    endIdx,
                                      float        inReal_0 __gc [],
                                      int           optInTimePeriod_0, /* From 2 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal_0 __gc [] );

         #define TA_KAMA Core::KAMA
         #define TA_KAMA_Lookback Core::KAMA_Lookback

         static int MA_Lookback( int           optInTimePeriod_0, /* From 2 to 100000 */
                               TA_MAType     optInMAType_1 ); 
         static enum TA_RetCode MA( int    startIdx,
                                    int    endIdx,
                                    double       inReal_0 __gc [],
                                    int           optInTimePeriod_0, /* From 2 to 100000 */
                                    TA_MAType     optInMAType_1,
                                    [OutAttribute]Int32 *outBegIdx,
                                    [OutAttribute]Int32 *outNbElement,
                                    double        outReal_0 __gc [] );
         static enum TA_RetCode MA( int    startIdx,
                                    int    endIdx,
                                    float        inReal_0 __gc [],
                                    int           optInTimePeriod_0, /* From 2 to 100000 */
                                    TA_MAType     optInMAType_1,
                                    [OutAttribute]Int32 *outBegIdx,
                                    [OutAttribute]Int32 *outNbElement,
                                    double        outReal_0 __gc [] );

         #define TA_MA Core::MA
         #define TA_MA_Lookback Core::MA_Lookback

         static int MAMA_Lookback( double        optInFastLimit_0, /* From 0.01 to 0.99 */
                                 double        optInSlowLimit_1 );  /* From 0.01 to 0.99 */

         static enum TA_RetCode MAMA( int    startIdx,
                                      int    endIdx,
                                      double       inReal_0 __gc [],
                                      double        optInFastLimit_0, /* From 0.01 to 0.99 */
                                      double        optInSlowLimit_1, /* From 0.01 to 0.99 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outMAMA_0 __gc [],
                                      double        outFAMA_1 __gc [] );
         static enum TA_RetCode MAMA( int    startIdx,
                                      int    endIdx,
                                      float        inReal_0 __gc [],
                                      double        optInFastLimit_0, /* From 0.01 to 0.99 */
                                      double        optInSlowLimit_1, /* From 0.01 to 0.99 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outMAMA_0 __gc [],
                                      double        outFAMA_1 __gc [] );

         #define TA_MAMA Core::MAMA
         #define TA_MAMA_Lookback Core::MAMA_Lookback

         static int MIDPRICE_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode MIDPRICE( int    startIdx,
                                          int    endIdx,
                                          double       inHigh_0 __gc [],
                                          double       inLow_0 __gc [],
                                          int           optInTimePeriod_0, /* From 2 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );
         static enum TA_RetCode MIDPRICE( int    startIdx,
                                          int    endIdx,
                                          float        inHigh_0 __gc [],
                                          float        inLow_0 __gc [],
                                          int           optInTimePeriod_0, /* From 2 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );

         #define TA_MIDPRICE Core::MIDPRICE
         #define TA_MIDPRICE_Lookback Core::MIDPRICE_Lookback

         static int MIDPOINT_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode MIDPOINT( int    startIdx,
                                          int    endIdx,
                                          double       inReal_0 __gc [],
                                          int           optInTimePeriod_0, /* From 2 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );
         static enum TA_RetCode MIDPOINT( int    startIdx,
                                          int    endIdx,
                                          float        inReal_0 __gc [],
                                          int           optInTimePeriod_0, /* From 2 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );

         #define TA_MIDPOINT Core::MIDPOINT
         #define TA_MIDPOINT_Lookback Core::MIDPOINT_Lookback

         static int SAR_Lookback( double        optInAcceleration_0, /* From 0 to TA_REAL_MAX */
                                double        optInMaximum_1 );  /* From 0 to TA_REAL_MAX */

         static enum TA_RetCode SAR( int    startIdx,
                                     int    endIdx,
                                     double       inHigh_0 __gc [],
                                     double       inLow_0 __gc [],
                                     double        optInAcceleration_0, /* From 0 to TA_REAL_MAX */
                                     double        optInMaximum_1, /* From 0 to TA_REAL_MAX */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );
         static enum TA_RetCode SAR( int    startIdx,
                                     int    endIdx,
                                     float        inHigh_0 __gc [],
                                     float        inLow_0 __gc [],
                                     double        optInAcceleration_0, /* From 0 to TA_REAL_MAX */
                                     double        optInMaximum_1, /* From 0 to TA_REAL_MAX */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );

         #define TA_SAR Core::SAR
         #define TA_SAR_Lookback Core::SAR_Lookback

         static int SAREXT_Lookback( double        optInStartValue_0, /* From 0 to TA_REAL_MAX */
                                   double        optInOffsetOnReverse_1, /* From 0 to TA_REAL_MAX */
                                   double        optInAccelerationInitLong_2, /* From 0 to TA_REAL_MAX */
                                   double        optInAccelerationLong_3, /* From 0 to TA_REAL_MAX */
                                   double        optInAccelerationMaxLong_4, /* From 0 to TA_REAL_MAX */
                                   double        optInAccelerationInitShort_5, /* From 0 to TA_REAL_MAX */
                                   double        optInAccelerationShort_6, /* From 0 to TA_REAL_MAX */
                                   double        optInAccelerationMaxShort_7 );  /* From 0 to TA_REAL_MAX */

         static enum TA_RetCode SAREXT( int    startIdx,
                                        int    endIdx,
                                        double       inHigh_0 __gc [],
                                        double       inLow_0 __gc [],
                                        double        optInStartValue_0, /* From 0 to TA_REAL_MAX */
                                        double        optInOffsetOnReverse_1, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationInitLong_2, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationLong_3, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationMaxLong_4, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationInitShort_5, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationShort_6, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationMaxShort_7, /* From 0 to TA_REAL_MAX */
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outReal_0 __gc [] );
         static enum TA_RetCode SAREXT( int    startIdx,
                                        int    endIdx,
                                        float        inHigh_0 __gc [],
                                        float        inLow_0 __gc [],
                                        double        optInStartValue_0, /* From 0 to TA_REAL_MAX */
                                        double        optInOffsetOnReverse_1, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationInitLong_2, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationLong_3, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationMaxLong_4, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationInitShort_5, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationShort_6, /* From 0 to TA_REAL_MAX */
                                        double        optInAccelerationMaxShort_7, /* From 0 to TA_REAL_MAX */
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outReal_0 __gc [] );

         #define TA_SAREXT Core::SAREXT
         #define TA_SAREXT_Lookback Core::SAREXT_Lookback

         static int SMA_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode SMA( int    startIdx,
                                     int    endIdx,
                                     double       inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );
         static enum TA_RetCode SMA( int    startIdx,
                                     int    endIdx,
                                     float        inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );

         #define TA_SMA Core::SMA
         #define TA_SMA_Lookback Core::SMA_Lookback

         static int T3_Lookback( int           optInTimePeriod_0, /* From 2 to 100000 */
                               double        optInVFactor_1 );  /* From 0 to 1 */

         static enum TA_RetCode T3( int    startIdx,
                                    int    endIdx,
                                    double       inReal_0 __gc [],
                                    int           optInTimePeriod_0, /* From 2 to 100000 */
                                    double        optInVFactor_1, /* From 0 to 1 */
                                    [OutAttribute]Int32 *outBegIdx,
                                    [OutAttribute]Int32 *outNbElement,
                                    double        outReal_0 __gc [] );
         static enum TA_RetCode T3( int    startIdx,
                                    int    endIdx,
                                    float        inReal_0 __gc [],
                                    int           optInTimePeriod_0, /* From 2 to 100000 */
                                    double        optInVFactor_1, /* From 0 to 1 */
                                    [OutAttribute]Int32 *outBegIdx,
                                    [OutAttribute]Int32 *outNbElement,
                                    double        outReal_0 __gc [] );

         #define TA_T3 Core::T3
         #define TA_T3_Lookback Core::T3_Lookback

         static int TEMA_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode TEMA( int    startIdx,
                                      int    endIdx,
                                      double       inReal_0 __gc [],
                                      int           optInTimePeriod_0, /* From 2 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal_0 __gc [] );
         static enum TA_RetCode TEMA( int    startIdx,
                                      int    endIdx,
                                      float        inReal_0 __gc [],
                                      int           optInTimePeriod_0, /* From 2 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal_0 __gc [] );

         #define TA_TEMA Core::TEMA
         #define TA_TEMA_Lookback Core::TEMA_Lookback

         static int TRIMA_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode TRIMA( int    startIdx,
                                       int    endIdx,
                                       double       inReal_0 __gc [],
                                       int           optInTimePeriod_0, /* From 2 to 100000 */
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outReal_0 __gc [] );
         static enum TA_RetCode TRIMA( int    startIdx,
                                       int    endIdx,
                                       float        inReal_0 __gc [],
                                       int           optInTimePeriod_0, /* From 2 to 100000 */
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outReal_0 __gc [] );

         #define TA_TRIMA Core::TRIMA
         #define TA_TRIMA_Lookback Core::TRIMA_Lookback

         static int WMA_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode WMA( int    startIdx,
                                     int    endIdx,
                                     double       inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );
         static enum TA_RetCode WMA( int    startIdx,
                                     int    endIdx,
                                     float        inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );

         #define TA_WMA Core::WMA
         #define TA_WMA_Lookback Core::WMA_Lookback

         static int ATR_Lookback( int           optInTimePeriod_0 );  /* From 1 to 100000 */

         static enum TA_RetCode ATR( int    startIdx,
                                     int    endIdx,
                                     double       inHigh_0 __gc [],
                                     double       inLow_0 __gc [],
                                     double       inClose_0 __gc [],
                                     int           optInTimePeriod_0, /* From 1 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );
         static enum TA_RetCode ATR( int    startIdx,
                                     int    endIdx,
                                     float        inHigh_0 __gc [],
                                     float        inLow_0 __gc [],
                                     float        inClose_0 __gc [],
                                     int           optInTimePeriod_0, /* From 1 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );

         #define TA_ATR Core::ATR
         #define TA_ATR_Lookback Core::ATR_Lookback

         static int TRANGE_Lookback( void );

         static enum TA_RetCode TRANGE( int    startIdx,
                                        int    endIdx,
                                        double       inHigh_0 __gc [],
                                        double       inLow_0 __gc [],
                                        double       inClose_0 __gc [],
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outReal_0 __gc [] );
         static enum TA_RetCode TRANGE( int    startIdx,
                                        int    endIdx,
                                        float        inHigh_0 __gc [],
                                        float        inLow_0 __gc [],
                                        float        inClose_0 __gc [],
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outReal_0 __gc [] );

         #define TA_TRANGE Core::TRANGE
         #define TA_TRANGE_Lookback Core::TRANGE_Lookback

         static int ADX_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode ADX( int    startIdx,
                                     int    endIdx,
                                     double       inHigh_0 __gc [],
                                     double       inLow_0 __gc [],
                                     double       inClose_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );
         static enum TA_RetCode ADX( int    startIdx,
                                     int    endIdx,
                                     float        inHigh_0 __gc [],
                                     float        inLow_0 __gc [],
                                     float        inClose_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );

         #define TA_ADX Core::ADX
         #define TA_ADX_Lookback Core::ADX_Lookback

         static int ADXR_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode ADXR( int    startIdx,
                                      int    endIdx,
                                      double       inHigh_0 __gc [],
                                      double       inLow_0 __gc [],
                                      double       inClose_0 __gc [],
                                      int           optInTimePeriod_0, /* From 2 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal_0 __gc [] );
         static enum TA_RetCode ADXR( int    startIdx,
                                      int    endIdx,
                                      float        inHigh_0 __gc [],
                                      float        inLow_0 __gc [],
                                      float        inClose_0 __gc [],
                                      int           optInTimePeriod_0, /* From 2 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal_0 __gc [] );

         #define TA_ADXR Core::ADXR
         #define TA_ADXR_Lookback Core::ADXR_Lookback

         static int APO_Lookback( int           optInFastPeriod_0, /* From 2 to 100000 */
                                int           optInSlowPeriod_1, /* From 2 to 100000 */
                                TA_MAType     optInMAType_2 ); 
         static enum TA_RetCode APO( int    startIdx,
                                     int    endIdx,
                                     double       inReal_0 __gc [],
                                     int           optInFastPeriod_0, /* From 2 to 100000 */
                                     int           optInSlowPeriod_1, /* From 2 to 100000 */
                                     TA_MAType     optInMAType_2,
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );
         static enum TA_RetCode APO( int    startIdx,
                                     int    endIdx,
                                     float        inReal_0 __gc [],
                                     int           optInFastPeriod_0, /* From 2 to 100000 */
                                     int           optInSlowPeriod_1, /* From 2 to 100000 */
                                     TA_MAType     optInMAType_2,
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );

         #define TA_APO Core::APO
         #define TA_APO_Lookback Core::APO_Lookback

         static int AROON_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode AROON( int    startIdx,
                                       int    endIdx,
                                       double       inHigh_0 __gc [],
                                       double       inLow_0 __gc [],
                                       int           optInTimePeriod_0, /* From 2 to 100000 */
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outAroonDown_0 __gc [],
                                       double        outAroonUp_1 __gc [] );
         static enum TA_RetCode AROON( int    startIdx,
                                       int    endIdx,
                                       float        inHigh_0 __gc [],
                                       float        inLow_0 __gc [],
                                       int           optInTimePeriod_0, /* From 2 to 100000 */
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outAroonDown_0 __gc [],
                                       double        outAroonUp_1 __gc [] );

         #define TA_AROON Core::AROON
         #define TA_AROON_Lookback Core::AROON_Lookback

         static int AROONOSC_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode AROONOSC( int    startIdx,
                                          int    endIdx,
                                          double       inHigh_0 __gc [],
                                          double       inLow_0 __gc [],
                                          int           optInTimePeriod_0, /* From 2 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );
         static enum TA_RetCode AROONOSC( int    startIdx,
                                          int    endIdx,
                                          float        inHigh_0 __gc [],
                                          float        inLow_0 __gc [],
                                          int           optInTimePeriod_0, /* From 2 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );

         #define TA_AROONOSC Core::AROONOSC
         #define TA_AROONOSC_Lookback Core::AROONOSC_Lookback

         static int CCI_Lookback( int           optInTimePeriod_0 );  /* From 5 to 100000 */

         static enum TA_RetCode CCI( int    startIdx,
                                     int    endIdx,
                                     double       inHigh_0 __gc [],
                                     double       inLow_0 __gc [],
                                     double       inClose_0 __gc [],
                                     int           optInTimePeriod_0, /* From 5 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );
         static enum TA_RetCode CCI( int    startIdx,
                                     int    endIdx,
                                     float        inHigh_0 __gc [],
                                     float        inLow_0 __gc [],
                                     float        inClose_0 __gc [],
                                     int           optInTimePeriod_0, /* From 5 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );

         #define TA_CCI Core::CCI
         #define TA_CCI_Lookback Core::CCI_Lookback

         static int DX_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode DX( int    startIdx,
                                    int    endIdx,
                                    double       inHigh_0 __gc [],
                                    double       inLow_0 __gc [],
                                    double       inClose_0 __gc [],
                                    int           optInTimePeriod_0, /* From 2 to 100000 */
                                    [OutAttribute]Int32 *outBegIdx,
                                    [OutAttribute]Int32 *outNbElement,
                                    double        outReal_0 __gc [] );
         static enum TA_RetCode DX( int    startIdx,
                                    int    endIdx,
                                    float        inHigh_0 __gc [],
                                    float        inLow_0 __gc [],
                                    float        inClose_0 __gc [],
                                    int           optInTimePeriod_0, /* From 2 to 100000 */
                                    [OutAttribute]Int32 *outBegIdx,
                                    [OutAttribute]Int32 *outNbElement,
                                    double        outReal_0 __gc [] );

         #define TA_DX Core::DX
         #define TA_DX_Lookback Core::DX_Lookback

         static int MACD_Lookback( int           optInFastPeriod_0, /* From 2 to 100000 */
                                 int           optInSlowPeriod_1, /* From 2 to 100000 */
                                 int           optInSignalPeriod_2 );  /* From 1 to 100000 */

         static enum TA_RetCode MACD( int    startIdx,
                                      int    endIdx,
                                      double       inReal_0 __gc [],
                                      int           optInFastPeriod_0, /* From 2 to 100000 */
                                      int           optInSlowPeriod_1, /* From 2 to 100000 */
                                      int           optInSignalPeriod_2, /* From 1 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outMACD_0 __gc [],
                                      double        outMACDSignal_1 __gc [],
                                      double        outMACDHist_2 __gc [] );
         static enum TA_RetCode MACD( int    startIdx,
                                      int    endIdx,
                                      float        inReal_0 __gc [],
                                      int           optInFastPeriod_0, /* From 2 to 100000 */
                                      int           optInSlowPeriod_1, /* From 2 to 100000 */
                                      int           optInSignalPeriod_2, /* From 1 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outMACD_0 __gc [],
                                      double        outMACDSignal_1 __gc [],
                                      double        outMACDHist_2 __gc [] );

         #define TA_MACD Core::MACD
         #define TA_MACD_Lookback Core::MACD_Lookback

         static int MACDEXT_Lookback( int           optInFastPeriod_0, /* From 2 to 100000 */
                                    TA_MAType     optInFastMAType_1,
                                    int           optInSlowPeriod_2, /* From 2 to 100000 */
                                    TA_MAType     optInSlowMAType_3,
                                    int           optInSignalPeriod_4, /* From 1 to 100000 */
                                    TA_MAType     optInSignalMAType_5 ); 
         static enum TA_RetCode MACDEXT( int    startIdx,
                                         int    endIdx,
                                         double       inReal_0 __gc [],
                                         int           optInFastPeriod_0, /* From 2 to 100000 */
                                         TA_MAType     optInFastMAType_1,
                                         int           optInSlowPeriod_2, /* From 2 to 100000 */
                                         TA_MAType     optInSlowMAType_3,
                                         int           optInSignalPeriod_4, /* From 1 to 100000 */
                                         TA_MAType     optInSignalMAType_5,
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outMACD_0 __gc [],
                                         double        outMACDSignal_1 __gc [],
                                         double        outMACDHist_2 __gc [] );
         static enum TA_RetCode MACDEXT( int    startIdx,
                                         int    endIdx,
                                         float        inReal_0 __gc [],
                                         int           optInFastPeriod_0, /* From 2 to 100000 */
                                         TA_MAType     optInFastMAType_1,
                                         int           optInSlowPeriod_2, /* From 2 to 100000 */
                                         TA_MAType     optInSlowMAType_3,
                                         int           optInSignalPeriod_4, /* From 1 to 100000 */
                                         TA_MAType     optInSignalMAType_5,
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outMACD_0 __gc [],
                                         double        outMACDSignal_1 __gc [],
                                         double        outMACDHist_2 __gc [] );

         #define TA_MACDEXT Core::MACDEXT
         #define TA_MACDEXT_Lookback Core::MACDEXT_Lookback

         static int MACDFIX_Lookback( int           optInSignalPeriod_0 );  /* From 1 to 100000 */

         static enum TA_RetCode MACDFIX( int    startIdx,
                                         int    endIdx,
                                         double       inReal_0 __gc [],
                                         int           optInSignalPeriod_0, /* From 1 to 100000 */
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outMACD_0 __gc [],
                                         double        outMACDSignal_1 __gc [],
                                         double        outMACDHist_2 __gc [] );
         static enum TA_RetCode MACDFIX( int    startIdx,
                                         int    endIdx,
                                         float        inReal_0 __gc [],
                                         int           optInSignalPeriod_0, /* From 1 to 100000 */
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outMACD_0 __gc [],
                                         double        outMACDSignal_1 __gc [],
                                         double        outMACDHist_2 __gc [] );

         #define TA_MACDFIX Core::MACDFIX
         #define TA_MACDFIX_Lookback Core::MACDFIX_Lookback

         static int MFI_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode MFI( int    startIdx,
                                     int    endIdx,
                                     double       inHigh_0 __gc [],
                                     double       inLow_0 __gc [],
                                     double       inClose_0 __gc [],
                                     int          inVolume_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );
         static enum TA_RetCode MFI( int    startIdx,
                                     int    endIdx,
                                     float        inHigh_0 __gc [],
                                     float        inLow_0 __gc [],
                                     float        inClose_0 __gc [],
                                     int          inVolume_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );

         #define TA_MFI Core::MFI
         #define TA_MFI_Lookback Core::MFI_Lookback

         static int MINUS_DI_Lookback( int           optInTimePeriod_0 );  /* From 1 to 100000 */

         static enum TA_RetCode MINUS_DI( int    startIdx,
                                          int    endIdx,
                                          double       inHigh_0 __gc [],
                                          double       inLow_0 __gc [],
                                          double       inClose_0 __gc [],
                                          int           optInTimePeriod_0, /* From 1 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );
         static enum TA_RetCode MINUS_DI( int    startIdx,
                                          int    endIdx,
                                          float        inHigh_0 __gc [],
                                          float        inLow_0 __gc [],
                                          float        inClose_0 __gc [],
                                          int           optInTimePeriod_0, /* From 1 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );

         #define TA_MINUS_DI Core::MINUS_DI
         #define TA_MINUS_DI_Lookback Core::MINUS_DI_Lookback

         static int MINUS_DM_Lookback( int           optInTimePeriod_0 );  /* From 1 to 100000 */

         static enum TA_RetCode MINUS_DM( int    startIdx,
                                          int    endIdx,
                                          double       inHigh_0 __gc [],
                                          double       inLow_0 __gc [],
                                          int           optInTimePeriod_0, /* From 1 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );
         static enum TA_RetCode MINUS_DM( int    startIdx,
                                          int    endIdx,
                                          float        inHigh_0 __gc [],
                                          float        inLow_0 __gc [],
                                          int           optInTimePeriod_0, /* From 1 to 100000 */
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );

         #define TA_MINUS_DM Core::MINUS_DM
         #define TA_MINUS_DM_Lookback Core::MINUS_DM_Lookback

         static int MOM_Lookback( int           optInTimePeriod_0 );  /* From 1 to 100000 */

         static enum TA_RetCode MOM( int    startIdx,
                                     int    endIdx,
                                     double       inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 1 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );
         static enum TA_RetCode MOM( int    startIdx,
                                     int    endIdx,
                                     float        inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 1 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );

         #define TA_MOM Core::MOM
         #define TA_MOM_Lookback Core::MOM_Lookback

         static int PPO_Lookback( int           optInFastPeriod_0, /* From 2 to 100000 */
                                int           optInSlowPeriod_1, /* From 2 to 100000 */
                                TA_MAType     optInMAType_2 ); 
         static enum TA_RetCode PPO( int    startIdx,
                                     int    endIdx,
                                     double       inReal_0 __gc [],
                                     int           optInFastPeriod_0, /* From 2 to 100000 */
                                     int           optInSlowPeriod_1, /* From 2 to 100000 */
                                     TA_MAType     optInMAType_2,
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );
         static enum TA_RetCode PPO( int    startIdx,
                                     int    endIdx,
                                     float        inReal_0 __gc [],
                                     int           optInFastPeriod_0, /* From 2 to 100000 */
                                     int           optInSlowPeriod_1, /* From 2 to 100000 */
                                     TA_MAType     optInMAType_2,
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );

         #define TA_PPO Core::PPO
         #define TA_PPO_Lookback Core::PPO_Lookback

         static int PLUS_DI_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode PLUS_DI( int    startIdx,
                                         int    endIdx,
                                         double       inHigh_0 __gc [],
                                         double       inLow_0 __gc [],
                                         double       inClose_0 __gc [],
                                         int           optInTimePeriod_0, /* From 2 to 100000 */
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outReal_0 __gc [] );
         static enum TA_RetCode PLUS_DI( int    startIdx,
                                         int    endIdx,
                                         float        inHigh_0 __gc [],
                                         float        inLow_0 __gc [],
                                         float        inClose_0 __gc [],
                                         int           optInTimePeriod_0, /* From 2 to 100000 */
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outReal_0 __gc [] );

         #define TA_PLUS_DI Core::PLUS_DI
         #define TA_PLUS_DI_Lookback Core::PLUS_DI_Lookback

         static int PLUS_DM_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode PLUS_DM( int    startIdx,
                                         int    endIdx,
                                         double       inHigh_0 __gc [],
                                         double       inLow_0 __gc [],
                                         int           optInTimePeriod_0, /* From 2 to 100000 */
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outReal_0 __gc [] );
         static enum TA_RetCode PLUS_DM( int    startIdx,
                                         int    endIdx,
                                         float        inHigh_0 __gc [],
                                         float        inLow_0 __gc [],
                                         int           optInTimePeriod_0, /* From 2 to 100000 */
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outReal_0 __gc [] );

         #define TA_PLUS_DM Core::PLUS_DM
         #define TA_PLUS_DM_Lookback Core::PLUS_DM_Lookback

         static int ROC_Lookback( int           optInTimePeriod_0 );  /* From 1 to 100000 */

         static enum TA_RetCode ROC( int    startIdx,
                                     int    endIdx,
                                     double       inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 1 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );
         static enum TA_RetCode ROC( int    startIdx,
                                     int    endIdx,
                                     float        inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 1 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );

         #define TA_ROC Core::ROC
         #define TA_ROC_Lookback Core::ROC_Lookback

         static int ROCP_Lookback( int           optInTimePeriod_0 );  /* From 1 to 100000 */

         static enum TA_RetCode ROCP( int    startIdx,
                                      int    endIdx,
                                      double       inReal_0 __gc [],
                                      int           optInTimePeriod_0, /* From 1 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal_0 __gc [] );
         static enum TA_RetCode ROCP( int    startIdx,
                                      int    endIdx,
                                      float        inReal_0 __gc [],
                                      int           optInTimePeriod_0, /* From 1 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal_0 __gc [] );

         #define TA_ROCP Core::ROCP
         #define TA_ROCP_Lookback Core::ROCP_Lookback

         static int ROCR_Lookback( int           optInTimePeriod_0 );  /* From 1 to 100000 */

         static enum TA_RetCode ROCR( int    startIdx,
                                      int    endIdx,
                                      double       inReal_0 __gc [],
                                      int           optInTimePeriod_0, /* From 1 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal_0 __gc [] );
         static enum TA_RetCode ROCR( int    startIdx,
                                      int    endIdx,
                                      float        inReal_0 __gc [],
                                      int           optInTimePeriod_0, /* From 1 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal_0 __gc [] );

         #define TA_ROCR Core::ROCR
         #define TA_ROCR_Lookback Core::ROCR_Lookback

         static int ROCR100_Lookback( int           optInTimePeriod_0 );  /* From 1 to 100000 */

         static enum TA_RetCode ROCR100( int    startIdx,
                                         int    endIdx,
                                         double       inReal_0 __gc [],
                                         int           optInTimePeriod_0, /* From 1 to 100000 */
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outReal_0 __gc [] );
         static enum TA_RetCode ROCR100( int    startIdx,
                                         int    endIdx,
                                         float        inReal_0 __gc [],
                                         int           optInTimePeriod_0, /* From 1 to 100000 */
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outReal_0 __gc [] );

         #define TA_ROCR100 Core::ROCR100
         #define TA_ROCR100_Lookback Core::ROCR100_Lookback

         static int RSI_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode RSI( int    startIdx,
                                     int    endIdx,
                                     double       inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );
         static enum TA_RetCode RSI( int    startIdx,
                                     int    endIdx,
                                     float        inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );

         #define TA_RSI Core::RSI
         #define TA_RSI_Lookback Core::RSI_Lookback

         static int STOCH_Lookback( int           optInFastK_Period_0, /* From 1 to 100000 */
                                  int           optInSlowK_Period_1, /* From 1 to 100000 */
                                  TA_MAType     optInSlowK_MAType_2,
                                  int           optInSlowD_Period_3, /* From 1 to 100000 */
                                  TA_MAType     optInSlowD_MAType_4 ); 
         static enum TA_RetCode STOCH( int    startIdx,
                                       int    endIdx,
                                       double       inHigh_0 __gc [],
                                       double       inLow_0 __gc [],
                                       double       inClose_0 __gc [],
                                       int           optInFastK_Period_0, /* From 1 to 100000 */
                                       int           optInSlowK_Period_1, /* From 1 to 100000 */
                                       TA_MAType     optInSlowK_MAType_2,
                                       int           optInSlowD_Period_3, /* From 1 to 100000 */
                                       TA_MAType     optInSlowD_MAType_4,
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outSlowK_0 __gc [],
                                       double        outSlowD_1 __gc [] );
         static enum TA_RetCode STOCH( int    startIdx,
                                       int    endIdx,
                                       float        inHigh_0 __gc [],
                                       float        inLow_0 __gc [],
                                       float        inClose_0 __gc [],
                                       int           optInFastK_Period_0, /* From 1 to 100000 */
                                       int           optInSlowK_Period_1, /* From 1 to 100000 */
                                       TA_MAType     optInSlowK_MAType_2,
                                       int           optInSlowD_Period_3, /* From 1 to 100000 */
                                       TA_MAType     optInSlowD_MAType_4,
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outSlowK_0 __gc [],
                                       double        outSlowD_1 __gc [] );

         #define TA_STOCH Core::STOCH
         #define TA_STOCH_Lookback Core::STOCH_Lookback

         static int STOCHF_Lookback( int           optInFastK_Period_0, /* From 1 to 100000 */
                                   int           optInFastD_Period_1, /* From 1 to 100000 */
                                   TA_MAType     optInFastD_MAType_2 ); 
         static enum TA_RetCode STOCHF( int    startIdx,
                                        int    endIdx,
                                        double       inHigh_0 __gc [],
                                        double       inLow_0 __gc [],
                                        double       inClose_0 __gc [],
                                        int           optInFastK_Period_0, /* From 1 to 100000 */
                                        int           optInFastD_Period_1, /* From 1 to 100000 */
                                        TA_MAType     optInFastD_MAType_2,
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outFastK_0 __gc [],
                                        double        outFastD_1 __gc [] );
         static enum TA_RetCode STOCHF( int    startIdx,
                                        int    endIdx,
                                        float        inHigh_0 __gc [],
                                        float        inLow_0 __gc [],
                                        float        inClose_0 __gc [],
                                        int           optInFastK_Period_0, /* From 1 to 100000 */
                                        int           optInFastD_Period_1, /* From 1 to 100000 */
                                        TA_MAType     optInFastD_MAType_2,
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outFastK_0 __gc [],
                                        double        outFastD_1 __gc [] );

         #define TA_STOCHF Core::STOCHF
         #define TA_STOCHF_Lookback Core::STOCHF_Lookback

         static int TRIX_Lookback( int           optInTimePeriod_0 );  /* From 1 to 100000 */

         static enum TA_RetCode TRIX( int    startIdx,
                                      int    endIdx,
                                      double       inReal_0 __gc [],
                                      int           optInTimePeriod_0, /* From 1 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal_0 __gc [] );
         static enum TA_RetCode TRIX( int    startIdx,
                                      int    endIdx,
                                      float        inReal_0 __gc [],
                                      int           optInTimePeriod_0, /* From 1 to 100000 */
                                      [OutAttribute]Int32 *outBegIdx,
                                      [OutAttribute]Int32 *outNbElement,
                                      double        outReal_0 __gc [] );

         #define TA_TRIX Core::TRIX
         #define TA_TRIX_Lookback Core::TRIX_Lookback

         static int WILLR_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode WILLR( int    startIdx,
                                       int    endIdx,
                                       double       inHigh_0 __gc [],
                                       double       inLow_0 __gc [],
                                       double       inClose_0 __gc [],
                                       int           optInTimePeriod_0, /* From 2 to 100000 */
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outReal_0 __gc [] );
         static enum TA_RetCode WILLR( int    startIdx,
                                       int    endIdx,
                                       float        inHigh_0 __gc [],
                                       float        inLow_0 __gc [],
                                       float        inClose_0 __gc [],
                                       int           optInTimePeriod_0, /* From 2 to 100000 */
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outReal_0 __gc [] );

         #define TA_WILLR Core::WILLR
         #define TA_WILLR_Lookback Core::WILLR_Lookback

         static int HT_DCPERIOD_Lookback( void );

         static enum TA_RetCode HT_DCPERIOD( int    startIdx,
                                             int    endIdx,
                                             double       inReal_0 __gc [],
                                             [OutAttribute]Int32 *outBegIdx,
                                             [OutAttribute]Int32 *outNbElement,
                                             double        outReal_0 __gc [] );
         static enum TA_RetCode HT_DCPERIOD( int    startIdx,
                                             int    endIdx,
                                             float        inReal_0 __gc [],
                                             [OutAttribute]Int32 *outBegIdx,
                                             [OutAttribute]Int32 *outNbElement,
                                             double        outReal_0 __gc [] );

         #define TA_HT_DCPERIOD Core::HT_DCPERIOD
         #define TA_HT_DCPERIOD_Lookback Core::HT_DCPERIOD_Lookback

         static int HT_DCPHASE_Lookback( void );

         static enum TA_RetCode HT_DCPHASE( int    startIdx,
                                            int    endIdx,
                                            double       inReal_0 __gc [],
                                            [OutAttribute]Int32 *outBegIdx,
                                            [OutAttribute]Int32 *outNbElement,
                                            double        outReal_0 __gc [] );
         static enum TA_RetCode HT_DCPHASE( int    startIdx,
                                            int    endIdx,
                                            float        inReal_0 __gc [],
                                            [OutAttribute]Int32 *outBegIdx,
                                            [OutAttribute]Int32 *outNbElement,
                                            double        outReal_0 __gc [] );

         #define TA_HT_DCPHASE Core::HT_DCPHASE
         #define TA_HT_DCPHASE_Lookback Core::HT_DCPHASE_Lookback

         static int HT_PHASOR_Lookback( void );

         static enum TA_RetCode HT_PHASOR( int    startIdx,
                                           int    endIdx,
                                           double       inReal_0 __gc [],
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           double        outInPhase_0 __gc [],
                                           double        outQuadrature_1 __gc [] );
         static enum TA_RetCode HT_PHASOR( int    startIdx,
                                           int    endIdx,
                                           float        inReal_0 __gc [],
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           double        outInPhase_0 __gc [],
                                           double        outQuadrature_1 __gc [] );

         #define TA_HT_PHASOR Core::HT_PHASOR
         #define TA_HT_PHASOR_Lookback Core::HT_PHASOR_Lookback

         static int HT_SINE_Lookback( void );

         static enum TA_RetCode HT_SINE( int    startIdx,
                                         int    endIdx,
                                         double       inReal_0 __gc [],
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outSine_0 __gc [],
                                         double        outLeadSine_1 __gc [] );
         static enum TA_RetCode HT_SINE( int    startIdx,
                                         int    endIdx,
                                         float        inReal_0 __gc [],
                                         [OutAttribute]Int32 *outBegIdx,
                                         [OutAttribute]Int32 *outNbElement,
                                         double        outSine_0 __gc [],
                                         double        outLeadSine_1 __gc [] );

         #define TA_HT_SINE Core::HT_SINE
         #define TA_HT_SINE_Lookback Core::HT_SINE_Lookback

         static int HT_TRENDMODE_Lookback( void );

         static enum TA_RetCode HT_TRENDMODE( int    startIdx,
                                              int    endIdx,
                                              double       inReal_0 __gc [],
                                              [OutAttribute]Int32 *outBegIdx,
                                              [OutAttribute]Int32 *outNbElement,
                                              int           outInteger_0 __gc [] );
         static enum TA_RetCode HT_TRENDMODE( int    startIdx,
                                              int    endIdx,
                                              float        inReal_0 __gc [],
                                              [OutAttribute]Int32 *outBegIdx,
                                              [OutAttribute]Int32 *outNbElement,
                                              int           outInteger_0 __gc [] );

         #define TA_HT_TRENDMODE Core::HT_TRENDMODE
         #define TA_HT_TRENDMODE_Lookback Core::HT_TRENDMODE_Lookback

         static int AD_Lookback( void );

         static enum TA_RetCode AD( int    startIdx,
                                    int    endIdx,
                                    double       inHigh_0 __gc [],
                                    double       inLow_0 __gc [],
                                    double       inClose_0 __gc [],
                                    int          inVolume_0 __gc [],
                                    [OutAttribute]Int32 *outBegIdx,
                                    [OutAttribute]Int32 *outNbElement,
                                    double        outReal_0 __gc [] );
         static enum TA_RetCode AD( int    startIdx,
                                    int    endIdx,
                                    float        inHigh_0 __gc [],
                                    float        inLow_0 __gc [],
                                    float        inClose_0 __gc [],
                                    int          inVolume_0 __gc [],
                                    [OutAttribute]Int32 *outBegIdx,
                                    [OutAttribute]Int32 *outNbElement,
                                    double        outReal_0 __gc [] );

         #define TA_AD Core::AD
         #define TA_AD_Lookback Core::AD_Lookback

         static int ADOSC_Lookback( int           optInFastPeriod_0, /* From 2 to 100000 */
                                  int           optInSlowPeriod_1 );  /* From 2 to 100000 */

         static enum TA_RetCode ADOSC( int    startIdx,
                                       int    endIdx,
                                       double       inHigh_0 __gc [],
                                       double       inLow_0 __gc [],
                                       double       inClose_0 __gc [],
                                       int          inVolume_0 __gc [],
                                       int           optInFastPeriod_0, /* From 2 to 100000 */
                                       int           optInSlowPeriod_1, /* From 2 to 100000 */
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outReal_0 __gc [] );
         static enum TA_RetCode ADOSC( int    startIdx,
                                       int    endIdx,
                                       float        inHigh_0 __gc [],
                                       float        inLow_0 __gc [],
                                       float        inClose_0 __gc [],
                                       int          inVolume_0 __gc [],
                                       int           optInFastPeriod_0, /* From 2 to 100000 */
                                       int           optInSlowPeriod_1, /* From 2 to 100000 */
                                       [OutAttribute]Int32 *outBegIdx,
                                       [OutAttribute]Int32 *outNbElement,
                                       double        outReal_0 __gc [] );

         #define TA_ADOSC Core::ADOSC
         #define TA_ADOSC_Lookback Core::ADOSC_Lookback

         static int OBV_Lookback( void );

         static enum TA_RetCode OBV( int    startIdx,
                                     int    endIdx,
                                     double       inReal_0 __gc [],
                                     int          inVolume_1 __gc [],
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     int           outInteger_0 __gc [] );
         static enum TA_RetCode OBV( int    startIdx,
                                     int    endIdx,
                                     float        inReal_0 __gc [],
                                     int          inVolume_1 __gc [],
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     int           outInteger_0 __gc [] );

         #define TA_OBV Core::OBV
         #define TA_OBV_Lookback Core::OBV_Lookback

         static int LINEARREG_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode LINEARREG( int    startIdx,
                                           int    endIdx,
                                           double       inReal_0 __gc [],
                                           int           optInTimePeriod_0, /* From 2 to 100000 */
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           double        outReal_0 __gc [] );
         static enum TA_RetCode LINEARREG( int    startIdx,
                                           int    endIdx,
                                           float        inReal_0 __gc [],
                                           int           optInTimePeriod_0, /* From 2 to 100000 */
                                           [OutAttribute]Int32 *outBegIdx,
                                           [OutAttribute]Int32 *outNbElement,
                                           double        outReal_0 __gc [] );

         #define TA_LINEARREG Core::LINEARREG
         #define TA_LINEARREG_Lookback Core::LINEARREG_Lookback

         static int LINEARREG_SLOPE_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode LINEARREG_SLOPE( int    startIdx,
                                                 int    endIdx,
                                                 double       inReal_0 __gc [],
                                                 int           optInTimePeriod_0, /* From 2 to 100000 */
                                                 [OutAttribute]Int32 *outBegIdx,
                                                 [OutAttribute]Int32 *outNbElement,
                                                 double        outReal_0 __gc [] );
         static enum TA_RetCode LINEARREG_SLOPE( int    startIdx,
                                                 int    endIdx,
                                                 float        inReal_0 __gc [],
                                                 int           optInTimePeriod_0, /* From 2 to 100000 */
                                                 [OutAttribute]Int32 *outBegIdx,
                                                 [OutAttribute]Int32 *outNbElement,
                                                 double        outReal_0 __gc [] );

         #define TA_LINEARREG_SLOPE Core::LINEARREG_SLOPE
         #define TA_LINEARREG_SLOPE_Lookback Core::LINEARREG_SLOPE_Lookback

         static int LINEARREG_ANGLE_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode LINEARREG_ANGLE( int    startIdx,
                                                 int    endIdx,
                                                 double       inReal_0 __gc [],
                                                 int           optInTimePeriod_0, /* From 2 to 100000 */
                                                 [OutAttribute]Int32 *outBegIdx,
                                                 [OutAttribute]Int32 *outNbElement,
                                                 double        outReal_0 __gc [] );
         static enum TA_RetCode LINEARREG_ANGLE( int    startIdx,
                                                 int    endIdx,
                                                 float        inReal_0 __gc [],
                                                 int           optInTimePeriod_0, /* From 2 to 100000 */
                                                 [OutAttribute]Int32 *outBegIdx,
                                                 [OutAttribute]Int32 *outNbElement,
                                                 double        outReal_0 __gc [] );

         #define TA_LINEARREG_ANGLE Core::LINEARREG_ANGLE
         #define TA_LINEARREG_ANGLE_Lookback Core::LINEARREG_ANGLE_Lookback

         static int LINEARREG_INTERCEPT_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode LINEARREG_INTERCEPT( int    startIdx,
                                                     int    endIdx,
                                                     double       inReal_0 __gc [],
                                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                                     [OutAttribute]Int32 *outBegIdx,
                                                     [OutAttribute]Int32 *outNbElement,
                                                     double        outReal_0 __gc [] );
         static enum TA_RetCode LINEARREG_INTERCEPT( int    startIdx,
                                                     int    endIdx,
                                                     float        inReal_0 __gc [],
                                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                                     [OutAttribute]Int32 *outBegIdx,
                                                     [OutAttribute]Int32 *outNbElement,
                                                     double        outReal_0 __gc [] );

         #define TA_LINEARREG_INTERCEPT Core::LINEARREG_INTERCEPT
         #define TA_LINEARREG_INTERCEPT_Lookback Core::LINEARREG_INTERCEPT_Lookback

         static int STDDEV_Lookback( int           optInTimePeriod_0, /* From 2 to 100000 */
                                   double        optInNbDev_1 );  /* From TA_REAL_MIN to TA_REAL_MAX */

         static enum TA_RetCode STDDEV( int    startIdx,
                                        int    endIdx,
                                        double       inReal_0 __gc [],
                                        int           optInTimePeriod_0, /* From 2 to 100000 */
                                        double        optInNbDev_1, /* From TA_REAL_MIN to TA_REAL_MAX */
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outReal_0 __gc [] );
         static enum TA_RetCode STDDEV( int    startIdx,
                                        int    endIdx,
                                        float        inReal_0 __gc [],
                                        int           optInTimePeriod_0, /* From 2 to 100000 */
                                        double        optInNbDev_1, /* From TA_REAL_MIN to TA_REAL_MAX */
                                        [OutAttribute]Int32 *outBegIdx,
                                        [OutAttribute]Int32 *outNbElement,
                                        double        outReal_0 __gc [] );

         #define TA_STDDEV Core::STDDEV
         #define TA_STDDEV_Lookback Core::STDDEV_Lookback

         static int TSF_Lookback( int           optInTimePeriod_0 );  /* From 2 to 100000 */

         static enum TA_RetCode TSF( int    startIdx,
                                     int    endIdx,
                                     double       inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );
         static enum TA_RetCode TSF( int    startIdx,
                                     int    endIdx,
                                     float        inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 2 to 100000 */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );

         #define TA_TSF Core::TSF
         #define TA_TSF_Lookback Core::TSF_Lookback

         static int VAR_Lookback( int           optInTimePeriod_0, /* From 1 to 100000 */
                                double        optInNbDev_1 );  /* From TA_REAL_MIN to TA_REAL_MAX */

         static enum TA_RetCode VAR( int    startIdx,
                                     int    endIdx,
                                     double       inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 1 to 100000 */
                                     double        optInNbDev_1, /* From TA_REAL_MIN to TA_REAL_MAX */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );
         static enum TA_RetCode VAR( int    startIdx,
                                     int    endIdx,
                                     float        inReal_0 __gc [],
                                     int           optInTimePeriod_0, /* From 1 to 100000 */
                                     double        optInNbDev_1, /* From TA_REAL_MIN to TA_REAL_MAX */
                                     [OutAttribute]Int32 *outBegIdx,
                                     [OutAttribute]Int32 *outNbElement,
                                     double        outReal_0 __gc [] );

         #define TA_VAR Core::VAR
         #define TA_VAR_Lookback Core::VAR_Lookback

         static int AVGPRICE_Lookback( void );

         static enum TA_RetCode AVGPRICE( int    startIdx,
                                          int    endIdx,
                                          double       inOpen_0 __gc [],
                                          double       inHigh_0 __gc [],
                                          double       inLow_0 __gc [],
                                          double       inClose_0 __gc [],
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );
         static enum TA_RetCode AVGPRICE( int    startIdx,
                                          int    endIdx,
                                          float        inOpen_0 __gc [],
                                          float        inHigh_0 __gc [],
                                          float        inLow_0 __gc [],
                                          float        inClose_0 __gc [],
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );

         #define TA_AVGPRICE Core::AVGPRICE
         #define TA_AVGPRICE_Lookback Core::AVGPRICE_Lookback

         static int MEDPRICE_Lookback( void );

         static enum TA_RetCode MEDPRICE( int    startIdx,
                                          int    endIdx,
                                          double       inHigh_0 __gc [],
                                          double       inLow_0 __gc [],
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );
         static enum TA_RetCode MEDPRICE( int    startIdx,
                                          int    endIdx,
                                          float        inHigh_0 __gc [],
                                          float        inLow_0 __gc [],
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );

         #define TA_MEDPRICE Core::MEDPRICE
         #define TA_MEDPRICE_Lookback Core::MEDPRICE_Lookback

         static int TYPPRICE_Lookback( void );

         static enum TA_RetCode TYPPRICE( int    startIdx,
                                          int    endIdx,
                                          double       inHigh_0 __gc [],
                                          double       inLow_0 __gc [],
                                          double       inClose_0 __gc [],
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );
         static enum TA_RetCode TYPPRICE( int    startIdx,
                                          int    endIdx,
                                          float        inHigh_0 __gc [],
                                          float        inLow_0 __gc [],
                                          float        inClose_0 __gc [],
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );

         #define TA_TYPPRICE Core::TYPPRICE
         #define TA_TYPPRICE_Lookback Core::TYPPRICE_Lookback

         static int WCLPRICE_Lookback( void );

         static enum TA_RetCode WCLPRICE( int    startIdx,
                                          int    endIdx,
                                          double       inHigh_0 __gc [],
                                          double       inLow_0 __gc [],
                                          double       inClose_0 __gc [],
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );
         static enum TA_RetCode WCLPRICE( int    startIdx,
                                          int    endIdx,
                                          float        inHigh_0 __gc [],
                                          float        inLow_0 __gc [],
                                          float        inClose_0 __gc [],
                                          [OutAttribute]Int32 *outBegIdx,
                                          [OutAttribute]Int32 *outNbElement,
                                          double        outReal_0 __gc [] );

         #define TA_WCLPRICE Core::WCLPRICE
         #define TA_WCLPRICE_Lookback Core::WCLPRICE_Lookback

/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/

  	   };
   }
}

