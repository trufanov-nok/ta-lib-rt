/* TA-LIB Copyright (c) 1999-2006, Mario Fortier
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
 *  RM       Robert Meier (talib@meierlim.com http://www.meierlim.com)
 *
 *  MMDDYY BY     Description
 *  -------------------------------------------------------------------
 *  050703 MF     First version with all the TA functions.
 *  112304 PSG    Fix #1072276 for TA_CandleDefaultSettings size.
 *  123004 RM,MF  Adapt code to work with Visual Studio 2005
 *  112605 MF     New TA_BOP (Balance Of Power) function.
 */

#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

namespace TicTacTec
{
	namespace TA
	{
	   namespace Lib
	   {
		  public ref class Core abstract sealed
		  {
		  public:
			 #include "ta_defs.h"

		  private:
			  ref class TA_CandleSetting sealed 
			  {
			  public:
				  enum class TA_CandleSettingType settingType;
				  enum class TA_RangeType rangeType;
				  int     avgPeriod;
				  double  factor;
			 };

			 ref class TA_GlobalsType sealed
			 {
			 public:
				TA_GlobalsType()
				{
					unstablePeriod = gcnew cli::array<unsigned int>((int)TA_FuncUnstId::TA_FUNC_UNST_ALL);
					compatibility = NAMESPACE(TA_Compatibility)TA_COMPATIBILITY_DEFAULT;
					for( int i=0; i < (int)TA_FuncUnstId::TA_FUNC_UNST_ALL; i++ )
						unstablePeriod[i] = 0;
					candleSettings = gcnew cli::array<TA_CandleSetting^>((int)TA_CandleSettingType::TA_AllCandleSettings);
					for( int j=0; j < candleSettings->Length; j++ )
					{
						candleSettings[j] = gcnew TA_CandleSetting();					
					}
				}

				/* For handling the compatibility with other software */
				TA_Compatibility compatibility;

				/* For handling the unstable period of some TA function. */
				cli::array<unsigned int>^ unstablePeriod;

				/* For handling the candlestick global settings */
				cli::array<TA_CandleSetting^>^ candleSettings;
			 };

			 static TA_GlobalsType^ TA_Globals;

			 static  enum class TA_RetCode INT_EMA( int           startIdx,
									int           endIdx,
									cli::array<double>^ inReal_0,
									int           optInTimePeriod_0, /* From 1 to 200 */
									double        optInK_1,
									[Out]int% outBegIdx,
									[Out]int% outNbElement,
									cli::array<double>^ outReal_0);

			 static  enum class TA_RetCode INT_EMA( int           startIdx,
									int           endIdx,
									cli::array<float>^ inReal_0,
									int           optInTimePeriod_0, /* From 1 to 200 */
									double        optInK_1,
									[Out]int% outBegIdx,
									[Out]int% outNbElement,
									cli::array<double>^ outReal_0);

			 static  enum class TA_RetCode INT_SMA( int     startIdx,
									int     endIdx,
									cli::array<double>^ inReal_0,
									int     optInTimePeriod_0, /* From 1 to 200 */
									[Out]int% outBegIdx,
									[Out]int% outNbElement,
									cli::array<double>^ outReal_0);

			 static  enum class TA_RetCode INT_SMA( int     startIdx,
									int     endIdx,
									cli::array<float>^ inReal_0,
									int     optInTimePeriod_0, /* From 1 to 200 */
									[Out]int% outBegIdx,
									[Out]int% outNbElement,
									cli::array<double>^ outReal_0 );

			 static  enum class TA_RetCode INT_MACD( int    startIdx,
									 int    endIdx,
									 cli::array<double>^ inReal_0,
									 int    optInFastPeriod_0, /* From 1 to 200, 0 is fix 12 */
									 int    optInSlowPeriod_1, /* From 1 to 200, 0 is fix 26 */
									 int    optInSignalPeriod_2, /* From 1 to 200 */
									 [Out]int% outBegIdx,
									 [Out]int% outNbElement,
									 cli::array<double>^ outMACD_0,
									 cli::array<double>^ outMACDSignal_1,
									 cli::array<double>^ outMACDHist_2 );

			 static  enum class TA_RetCode INT_MACD( int    startIdx,
									 int    endIdx,
									 cli::array<float>^ inReal_0,
									 int    optInFastPeriod_0, /* From 1 to 200, 0 is fix 12 */
									 int    optInSlowPeriod_1, /* From 1 to 200, 0 is fix 26 */
									 int    optInSignalPeriod_2, /* From 1 to 200 */
									 [Out]int% outBegIdx,
									 [Out]int% outNbElement,
									 cli::array<double>^ outMACD_0,
									 cli::array<double>^ outMACDSignal_1,
									 cli::array<double>^ outMACDHist_2 );

			 static  enum class TA_RetCode INT_PO( int    startIdx,
								   int    endIdx,
								   cli::array<double>^ inReal_0,
								   int    optInFastPeriod_0, /* From 1 to 200 */
								   int    optInSlowPeriod_1, /* From 1 to 200 */
								   TA_MAType optInMethod_2,
								   [Out]int% outBegIdx,
								   [Out]int% outNbElement,
								   cli::array<double>^ outReal_0,
								   cli::array<double>^ tempBuffer,
								   int  doPercentageOutput );

			 static  enum class TA_RetCode INT_PO( int    startIdx,
								   int    endIdx,
								   cli::array<float>^ inReal_0,
								   int    optInFastPeriod_0, /* From 1 to 200 */
								   int    optInSlowPeriod_1, /* From 1 to 200 */
								   TA_MAType optInMethod_2,
								   [Out]int% outBegIdx,
								   [Out]int% outNbElement,
								   cli::array<double>^ outReal_0,
								   cli::array<double>^ tempBuffer,
								   int  doPercentageOutput );

			 static  enum class TA_RetCode INT_VAR( int    startIdx,
									int    endIdx,
									cli::array<double>^ inReal_0,
									int    optInTimePeriod_0,                       
									[Out]int% outBegIdx,
									[Out]int% outNbElement,
									cli::array<double>^ outReal_0);

			 static  enum class TA_RetCode INT_VAR( int    startIdx,
									int    endIdx,
									cli::array<float>^ inReal_0,
									int    optInTimePeriod_0,                       
									[Out]int% outBegIdx,
									[Out]int% outNbElement,
									cli::array<double>^ outReal_0);

			 static void INT_stddev_using_precalc_ma( cli::array<double>^  inReal,
												  cli::array<double>^ inMovAvg,
												  int inMovAvgBegIdx,
												  int inMovAvgNbElement,
												  int timePeriod,
												  cli::array<double>^ output );

			 static void INT_stddev_using_precalc_ma( cli::array<float>^ inReal,
												  cli::array<double>^ inMovAvg,
												  int inMovAvgBegIdx,
												  int inMovAvgNbElement,
												  int timePeriod,
												  cli::array<double>^ output);

		  public:
			 static Core()
			 {
				// Initialize global settings
				TA_Globals = gcnew TA_GlobalsType;
				/* Set the default value to global variables */
				TA_RestoreCandleDefaultSettings( TA_CandleSettingType::TA_AllCandleSettings );
			 }

			 static  enum class TA_RetCode SetUnstablePeriod(  enum class TA_FuncUnstId id,
															   unsigned int  unstablePeriod );

			 static unsigned int GetUnstablePeriod( TA_FuncUnstId id );

			 static  enum class TA_RetCode SetCompatibility( enum class TA_Compatibility value );
			 static  enum class TA_Compatibility GetCompatibility( void );

			 static  enum class TA_RetCode TA_SetCandleSettings(  enum class TA_CandleSettingType settingType, 
																  enum class TA_RangeType rangeType,
																  int avgPeriod, 
																  double factor )
			 {    
				 if( settingType >= TA_CandleSettingType::TA_AllCandleSettings )
				 {
					 return TA_RetCode::TA_BAD_PARAM;
				 }
				 TA_Globals->candleSettings[(int)settingType]->settingType = settingType;
				 TA_Globals->candleSettings[(int)settingType]->rangeType = rangeType;
				 TA_Globals->candleSettings[(int)settingType]->avgPeriod = avgPeriod;
				 TA_Globals->candleSettings[(int)settingType]->factor = factor;
				 return TA_RetCode::TA_SUCCESS;
			 }

			 
			 static enum class TA_RetCode TA_RestoreCandleDefaultSettings( TA_CandleSettingType settingType )
			 {			
				switch( settingType )
				{
				case TA_CandleSettingType::TA_BodyLong:
					TA_SetCandleSettings( TA_CandleSettingType::TA_BodyLong, TA_RangeType::TA_RangeType_RealBody, 10, 1.0 );
				   break;
				case TA_CandleSettingType::TA_BodyVeryLong:
				   TA_SetCandleSettings( TA_CandleSettingType::TA_BodyVeryLong, TA_RangeType::TA_RangeType_RealBody, 10, 3.0 );
				   break;
				case TA_CandleSettingType::TA_BodyShort:
				   TA_SetCandleSettings( TA_CandleSettingType::TA_BodyShort, TA_RangeType::TA_RangeType_RealBody, 10, 1.0 );
				   break;
				case TA_CandleSettingType::TA_BodyDoji:
				   TA_SetCandleSettings( TA_CandleSettingType::TA_BodyDoji, TA_RangeType::TA_RangeType_HighLow, 10, 0.1 );
				   break;
				case TA_CandleSettingType::TA_ShadowLong:
				   TA_SetCandleSettings( TA_CandleSettingType::TA_ShadowLong, TA_RangeType::TA_RangeType_RealBody, 0, 1.0 );
				   break;
				case TA_CandleSettingType::TA_ShadowVeryLong:
				   TA_SetCandleSettings( TA_CandleSettingType::TA_ShadowVeryLong, TA_RangeType::TA_RangeType_RealBody, 0, 2.0 );
				   break;
				case TA_CandleSettingType::TA_ShadowShort:
				   TA_SetCandleSettings( TA_CandleSettingType::TA_ShadowShort, TA_RangeType::TA_RangeType_Shadows, 10, 1.0 );
				   break;
				case TA_CandleSettingType::TA_ShadowVeryShort:
				   TA_SetCandleSettings( TA_CandleSettingType::TA_ShadowVeryShort, TA_RangeType::TA_RangeType_HighLow, 10, 0.1 );
				   break;
				case TA_CandleSettingType::TA_Near:
				   TA_SetCandleSettings( TA_CandleSettingType::TA_Near, TA_RangeType::TA_RangeType_HighLow, 5, 0.2 );
				   break;
				case TA_CandleSettingType::TA_Far:
				   TA_SetCandleSettings( TA_CandleSettingType::TA_Far, TA_RangeType::TA_RangeType_HighLow, 5, 0.6 );
				   break;
				case TA_CandleSettingType::TA_Equal:
				   TA_SetCandleSettings( TA_CandleSettingType::TA_Equal, TA_RangeType::TA_RangeType_HighLow, 5, 0.05);
				   break;
				case TA_CandleSettingType::TA_AllCandleSettings:
				   TA_SetCandleSettings( TA_CandleSettingType::TA_BodyLong, TA_RangeType::TA_RangeType_RealBody, 10, 1.0 );
				   TA_SetCandleSettings( TA_CandleSettingType::TA_BodyVeryLong, TA_RangeType::TA_RangeType_RealBody, 10, 3.0 );
				   TA_SetCandleSettings( TA_CandleSettingType::TA_BodyShort, TA_RangeType::TA_RangeType_RealBody, 10, 1.0 );
				   TA_SetCandleSettings( TA_CandleSettingType::TA_BodyDoji, TA_RangeType::TA_RangeType_HighLow, 10, 0.1 );
				   TA_SetCandleSettings( TA_CandleSettingType::TA_ShadowLong, TA_RangeType::TA_RangeType_RealBody, 0, 1.0 );
				   TA_SetCandleSettings( TA_CandleSettingType::TA_ShadowVeryLong, TA_RangeType::TA_RangeType_RealBody, 0, 2.0 );
				   TA_SetCandleSettings( TA_CandleSettingType::TA_ShadowShort, TA_RangeType::TA_RangeType_Shadows, 10, 1.0 );
				   TA_SetCandleSettings( TA_CandleSettingType::TA_ShadowVeryShort, TA_RangeType::TA_RangeType_HighLow, 10, 0.1 );
				   TA_SetCandleSettings( TA_CandleSettingType::TA_Near, TA_RangeType::TA_RangeType_HighLow, 5, 0.2 );
				   TA_SetCandleSettings( TA_CandleSettingType::TA_Far, TA_RangeType::TA_RangeType_HighLow, 5, 0.6 );
				   TA_SetCandleSettings( TA_CandleSettingType::TA_Equal, TA_RangeType::TA_RangeType_HighLow, 5, 0.05);
				   break;
				}

				return TA_RetCode::TA_SUCCESS;
			 }

/**** START GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
         static int MAX_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode MAX( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode MAX( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_MAX Core::MAX
         #define TA_MAX_Lookback Core::MAX_Lookback

         static int MIN_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode MIN( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode MIN( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_MIN Core::MIN
         #define TA_MIN_Lookback Core::MIN_Lookback

         static int SUM_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode SUM( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode SUM( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_SUM Core::SUM
         #define TA_SUM_Lookback Core::SUM_Lookback

         static int BBANDS_Lookback( int           optInTimePeriod, /* From 2 to 100000 */
                                   double        optInNbDevUp, /* From TA_REAL_MIN to TA_REAL_MAX */
                                   double        optInNbDevDn, /* From TA_REAL_MIN to TA_REAL_MAX */
                                   TA_MAType     optInMAType ); 
         static enum class TA_RetCode BBANDS( int    startIdx,
                                              int    endIdx,
                                              cli::array<double>^ inReal,
                                              int           optInTimePeriod, /* From 2 to 100000 */
                                              double        optInNbDevUp, /* From TA_REAL_MIN to TA_REAL_MAX */
                                              double        optInNbDevDn, /* From TA_REAL_MIN to TA_REAL_MAX */
                                              TA_MAType     optInMAType,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outRealUpperBand,
                                              cli::array<double>^  outRealMiddleBand,
                                              cli::array<double>^  outRealLowerBand );
         static enum class TA_RetCode BBANDS( int    startIdx,
                                              int    endIdx,
                                              cli::array<float>^ inReal,
                                              int           optInTimePeriod, /* From 2 to 100000 */
                                              double        optInNbDevUp, /* From TA_REAL_MIN to TA_REAL_MAX */
                                              double        optInNbDevDn, /* From TA_REAL_MIN to TA_REAL_MAX */
                                              TA_MAType     optInMAType,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outRealUpperBand,
                                              cli::array<double>^  outRealMiddleBand,
                                              cli::array<double>^  outRealLowerBand );

         #define TA_BBANDS Core::BBANDS
         #define TA_BBANDS_Lookback Core::BBANDS_Lookback

         static int DEMA_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode DEMA( int    startIdx,
                                            int    endIdx,
                                            cli::array<double>^ inReal,
                                            int           optInTimePeriod, /* From 2 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );
         static enum class TA_RetCode DEMA( int    startIdx,
                                            int    endIdx,
                                            cli::array<float>^ inReal,
                                            int           optInTimePeriod, /* From 2 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );

         #define TA_DEMA Core::DEMA
         #define TA_DEMA_Lookback Core::DEMA_Lookback

         static int EMA_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode EMA( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode EMA( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_EMA Core::EMA
         #define TA_EMA_Lookback Core::EMA_Lookback

         static int HT_TRENDLINE_Lookback( void );

         static enum class TA_RetCode HT_TRENDLINE( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<double>^ inReal,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<double>^  outReal );
         static enum class TA_RetCode HT_TRENDLINE( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<float>^ inReal,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<double>^  outReal );

         #define TA_HT_TRENDLINE Core::HT_TRENDLINE
         #define TA_HT_TRENDLINE_Lookback Core::HT_TRENDLINE_Lookback

         static int KAMA_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode KAMA( int    startIdx,
                                            int    endIdx,
                                            cli::array<double>^ inReal,
                                            int           optInTimePeriod, /* From 2 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );
         static enum class TA_RetCode KAMA( int    startIdx,
                                            int    endIdx,
                                            cli::array<float>^ inReal,
                                            int           optInTimePeriod, /* From 2 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );

         #define TA_KAMA Core::KAMA
         #define TA_KAMA_Lookback Core::KAMA_Lookback

         static int MA_Lookback( int           optInTimePeriod, /* From 1 to 100000 */
                               TA_MAType     optInMAType ); 
         static enum class TA_RetCode MA( int    startIdx,
                                          int    endIdx,
                                          cli::array<double>^ inReal,
                                          int           optInTimePeriod, /* From 1 to 100000 */
                                          TA_MAType     optInMAType,
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outReal );
         static enum class TA_RetCode MA( int    startIdx,
                                          int    endIdx,
                                          cli::array<float>^ inReal,
                                          int           optInTimePeriod, /* From 1 to 100000 */
                                          TA_MAType     optInMAType,
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outReal );

         #define TA_MA Core::MA
         #define TA_MA_Lookback Core::MA_Lookback

         static int MAMA_Lookback( double        optInFastLimit, /* From 0.01 to 0.99 */
                                 double        optInSlowLimit );  /* From 0.01 to 0.99 */

         static enum class TA_RetCode MAMA( int    startIdx,
                                            int    endIdx,
                                            cli::array<double>^ inReal,
                                            double        optInFastLimit, /* From 0.01 to 0.99 */
                                            double        optInSlowLimit, /* From 0.01 to 0.99 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outMAMA,
                                            cli::array<double>^  outFAMA );
         static enum class TA_RetCode MAMA( int    startIdx,
                                            int    endIdx,
                                            cli::array<float>^ inReal,
                                            double        optInFastLimit, /* From 0.01 to 0.99 */
                                            double        optInSlowLimit, /* From 0.01 to 0.99 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outMAMA,
                                            cli::array<double>^  outFAMA );

         #define TA_MAMA Core::MAMA
         #define TA_MAMA_Lookback Core::MAMA_Lookback

         static int MIDPRICE_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode MIDPRICE( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inHigh,
                                                cli::array<double>^ inLow,
                                                int           optInTimePeriod, /* From 2 to 100000 */
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );
         static enum class TA_RetCode MIDPRICE( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inHigh,
                                                cli::array<float>^ inLow,
                                                int           optInTimePeriod, /* From 2 to 100000 */
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );

         #define TA_MIDPRICE Core::MIDPRICE
         #define TA_MIDPRICE_Lookback Core::MIDPRICE_Lookback

         static int MIDPOINT_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode MIDPOINT( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inReal,
                                                int           optInTimePeriod, /* From 2 to 100000 */
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );
         static enum class TA_RetCode MIDPOINT( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inReal,
                                                int           optInTimePeriod, /* From 2 to 100000 */
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );

         #define TA_MIDPOINT Core::MIDPOINT
         #define TA_MIDPOINT_Lookback Core::MIDPOINT_Lookback

         static int SAR_Lookback( double        optInAcceleration, /* From 0 to TA_REAL_MAX */
                                double        optInMaximum );  /* From 0 to TA_REAL_MAX */

         static enum class TA_RetCode SAR( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inHigh,
                                           cli::array<double>^ inLow,
                                           double        optInAcceleration, /* From 0 to TA_REAL_MAX */
                                           double        optInMaximum, /* From 0 to TA_REAL_MAX */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode SAR( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inHigh,
                                           cli::array<float>^ inLow,
                                           double        optInAcceleration, /* From 0 to TA_REAL_MAX */
                                           double        optInMaximum, /* From 0 to TA_REAL_MAX */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

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

         static enum class TA_RetCode SAREXT( int    startIdx,
                                              int    endIdx,
                                              cli::array<double>^ inHigh,
                                              cli::array<double>^ inLow,
                                              double        optInStartValue, /* From TA_REAL_MIN to TA_REAL_MAX */
                                              double        optInOffsetOnReverse, /* From 0 to TA_REAL_MAX */
                                              double        optInAccelerationInitLong, /* From 0 to TA_REAL_MAX */
                                              double        optInAccelerationLong, /* From 0 to TA_REAL_MAX */
                                              double        optInAccelerationMaxLong, /* From 0 to TA_REAL_MAX */
                                              double        optInAccelerationInitShort, /* From 0 to TA_REAL_MAX */
                                              double        optInAccelerationShort, /* From 0 to TA_REAL_MAX */
                                              double        optInAccelerationMaxShort, /* From 0 to TA_REAL_MAX */
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outReal );
         static enum class TA_RetCode SAREXT( int    startIdx,
                                              int    endIdx,
                                              cli::array<float>^ inHigh,
                                              cli::array<float>^ inLow,
                                              double        optInStartValue, /* From TA_REAL_MIN to TA_REAL_MAX */
                                              double        optInOffsetOnReverse, /* From 0 to TA_REAL_MAX */
                                              double        optInAccelerationInitLong, /* From 0 to TA_REAL_MAX */
                                              double        optInAccelerationLong, /* From 0 to TA_REAL_MAX */
                                              double        optInAccelerationMaxLong, /* From 0 to TA_REAL_MAX */
                                              double        optInAccelerationInitShort, /* From 0 to TA_REAL_MAX */
                                              double        optInAccelerationShort, /* From 0 to TA_REAL_MAX */
                                              double        optInAccelerationMaxShort, /* From 0 to TA_REAL_MAX */
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outReal );

         #define TA_SAREXT Core::SAREXT
         #define TA_SAREXT_Lookback Core::SAREXT_Lookback

         static int SMA_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode SMA( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode SMA( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_SMA Core::SMA
         #define TA_SMA_Lookback Core::SMA_Lookback

         static int T3_Lookback( int           optInTimePeriod, /* From 2 to 100000 */
                               double        optInVFactor );  /* From 0 to 1 */

         static enum class TA_RetCode T3( int    startIdx,
                                          int    endIdx,
                                          cli::array<double>^ inReal,
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          double        optInVFactor, /* From 0 to 1 */
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outReal );
         static enum class TA_RetCode T3( int    startIdx,
                                          int    endIdx,
                                          cli::array<float>^ inReal,
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          double        optInVFactor, /* From 0 to 1 */
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outReal );

         #define TA_T3 Core::T3
         #define TA_T3_Lookback Core::T3_Lookback

         static int TEMA_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode TEMA( int    startIdx,
                                            int    endIdx,
                                            cli::array<double>^ inReal,
                                            int           optInTimePeriod, /* From 2 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );
         static enum class TA_RetCode TEMA( int    startIdx,
                                            int    endIdx,
                                            cli::array<float>^ inReal,
                                            int           optInTimePeriod, /* From 2 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );

         #define TA_TEMA Core::TEMA
         #define TA_TEMA_Lookback Core::TEMA_Lookback

         static int TRIMA_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode TRIMA( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inReal,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );
         static enum class TA_RetCode TRIMA( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inReal,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );

         #define TA_TRIMA Core::TRIMA
         #define TA_TRIMA_Lookback Core::TRIMA_Lookback

         static int WMA_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode WMA( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode WMA( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_WMA Core::WMA
         #define TA_WMA_Lookback Core::WMA_Lookback

         static int ATR_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class TA_RetCode ATR( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inHigh,
                                           cli::array<double>^ inLow,
                                           cli::array<double>^ inClose,
                                           int           optInTimePeriod, /* From 1 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode ATR( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inHigh,
                                           cli::array<float>^ inLow,
                                           cli::array<float>^ inClose,
                                           int           optInTimePeriod, /* From 1 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_ATR Core::ATR
         #define TA_ATR_Lookback Core::ATR_Lookback

         static int NATR_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class TA_RetCode NATR( int    startIdx,
                                            int    endIdx,
                                            cli::array<double>^ inHigh,
                                            cli::array<double>^ inLow,
                                            cli::array<double>^ inClose,
                                            int           optInTimePeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );
         static enum class TA_RetCode NATR( int    startIdx,
                                            int    endIdx,
                                            cli::array<float>^ inHigh,
                                            cli::array<float>^ inLow,
                                            cli::array<float>^ inClose,
                                            int           optInTimePeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );

         #define TA_NATR Core::NATR
         #define TA_NATR_Lookback Core::NATR_Lookback

         static int TRANGE_Lookback( void );

         static enum class TA_RetCode TRANGE( int    startIdx,
                                              int    endIdx,
                                              cli::array<double>^ inHigh,
                                              cli::array<double>^ inLow,
                                              cli::array<double>^ inClose,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outReal );
         static enum class TA_RetCode TRANGE( int    startIdx,
                                              int    endIdx,
                                              cli::array<float>^ inHigh,
                                              cli::array<float>^ inLow,
                                              cli::array<float>^ inClose,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outReal );

         #define TA_TRANGE Core::TRANGE
         #define TA_TRANGE_Lookback Core::TRANGE_Lookback

         static int ADX_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode ADX( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inHigh,
                                           cli::array<double>^ inLow,
                                           cli::array<double>^ inClose,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode ADX( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inHigh,
                                           cli::array<float>^ inLow,
                                           cli::array<float>^ inClose,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_ADX Core::ADX
         #define TA_ADX_Lookback Core::ADX_Lookback

         static int ADXR_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode ADXR( int    startIdx,
                                            int    endIdx,
                                            cli::array<double>^ inHigh,
                                            cli::array<double>^ inLow,
                                            cli::array<double>^ inClose,
                                            int           optInTimePeriod, /* From 2 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );
         static enum class TA_RetCode ADXR( int    startIdx,
                                            int    endIdx,
                                            cli::array<float>^ inHigh,
                                            cli::array<float>^ inLow,
                                            cli::array<float>^ inClose,
                                            int           optInTimePeriod, /* From 2 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );

         #define TA_ADXR Core::ADXR
         #define TA_ADXR_Lookback Core::ADXR_Lookback

         static int APO_Lookback( int           optInFastPeriod, /* From 2 to 100000 */
                                int           optInSlowPeriod, /* From 2 to 100000 */
                                TA_MAType     optInMAType ); 
         static enum class TA_RetCode APO( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           int           optInFastPeriod, /* From 2 to 100000 */
                                           int           optInSlowPeriod, /* From 2 to 100000 */
                                           TA_MAType     optInMAType,
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode APO( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           int           optInFastPeriod, /* From 2 to 100000 */
                                           int           optInSlowPeriod, /* From 2 to 100000 */
                                           TA_MAType     optInMAType,
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_APO Core::APO
         #define TA_APO_Lookback Core::APO_Lookback

         static int AROON_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode AROON( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inHigh,
                                             cli::array<double>^ inLow,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outAroonDown,
                                             cli::array<double>^  outAroonUp );
         static enum class TA_RetCode AROON( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inHigh,
                                             cli::array<float>^ inLow,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outAroonDown,
                                             cli::array<double>^  outAroonUp );

         #define TA_AROON Core::AROON
         #define TA_AROON_Lookback Core::AROON_Lookback

         static int AROONOSC_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode AROONOSC( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inHigh,
                                                cli::array<double>^ inLow,
                                                int           optInTimePeriod, /* From 2 to 100000 */
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );
         static enum class TA_RetCode AROONOSC( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inHigh,
                                                cli::array<float>^ inLow,
                                                int           optInTimePeriod, /* From 2 to 100000 */
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );

         #define TA_AROONOSC Core::AROONOSC
         #define TA_AROONOSC_Lookback Core::AROONOSC_Lookback

         static int BOP_Lookback( void );

         static enum class TA_RetCode BOP( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inOpen,
                                           cli::array<double>^ inHigh,
                                           cli::array<double>^ inLow,
                                           cli::array<double>^ inClose,
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode BOP( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inOpen,
                                           cli::array<float>^ inHigh,
                                           cli::array<float>^ inLow,
                                           cli::array<float>^ inClose,
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_BOP Core::BOP
         #define TA_BOP_Lookback Core::BOP_Lookback

         static int CCI_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode CCI( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inHigh,
                                           cli::array<double>^ inLow,
                                           cli::array<double>^ inClose,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode CCI( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inHigh,
                                           cli::array<float>^ inLow,
                                           cli::array<float>^ inClose,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_CCI Core::CCI
         #define TA_CCI_Lookback Core::CCI_Lookback

         static int CMO_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode CMO( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode CMO( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_CMO Core::CMO
         #define TA_CMO_Lookback Core::CMO_Lookback

         static int DX_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode DX( int    startIdx,
                                          int    endIdx,
                                          cli::array<double>^ inHigh,
                                          cli::array<double>^ inLow,
                                          cli::array<double>^ inClose,
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outReal );
         static enum class TA_RetCode DX( int    startIdx,
                                          int    endIdx,
                                          cli::array<float>^ inHigh,
                                          cli::array<float>^ inLow,
                                          cli::array<float>^ inClose,
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outReal );

         #define TA_DX Core::DX
         #define TA_DX_Lookback Core::DX_Lookback

         static int MACD_Lookback( int           optInFastPeriod, /* From 2 to 100000 */
                                 int           optInSlowPeriod, /* From 2 to 100000 */
                                 int           optInSignalPeriod );  /* From 1 to 100000 */

         static enum class TA_RetCode MACD( int    startIdx,
                                            int    endIdx,
                                            cli::array<double>^ inReal,
                                            int           optInFastPeriod, /* From 2 to 100000 */
                                            int           optInSlowPeriod, /* From 2 to 100000 */
                                            int           optInSignalPeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outMACD,
                                            cli::array<double>^  outMACDSignal,
                                            cli::array<double>^  outMACDHist );
         static enum class TA_RetCode MACD( int    startIdx,
                                            int    endIdx,
                                            cli::array<float>^ inReal,
                                            int           optInFastPeriod, /* From 2 to 100000 */
                                            int           optInSlowPeriod, /* From 2 to 100000 */
                                            int           optInSignalPeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outMACD,
                                            cli::array<double>^  outMACDSignal,
                                            cli::array<double>^  outMACDHist );

         #define TA_MACD Core::MACD
         #define TA_MACD_Lookback Core::MACD_Lookback

         static int MACDEXT_Lookback( int           optInFastPeriod, /* From 2 to 100000 */
                                    TA_MAType     optInFastMAType,
                                    int           optInSlowPeriod, /* From 2 to 100000 */
                                    TA_MAType     optInSlowMAType,
                                    int           optInSignalPeriod, /* From 1 to 100000 */
                                    TA_MAType     optInSignalMAType ); 
         static enum class TA_RetCode MACDEXT( int    startIdx,
                                               int    endIdx,
                                               cli::array<double>^ inReal,
                                               int           optInFastPeriod, /* From 2 to 100000 */
                                               TA_MAType     optInFastMAType,
                                               int           optInSlowPeriod, /* From 2 to 100000 */
                                               TA_MAType     optInSlowMAType,
                                               int           optInSignalPeriod, /* From 1 to 100000 */
                                               TA_MAType     optInSignalMAType,
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<double>^  outMACD,
                                               cli::array<double>^  outMACDSignal,
                                               cli::array<double>^  outMACDHist );
         static enum class TA_RetCode MACDEXT( int    startIdx,
                                               int    endIdx,
                                               cli::array<float>^ inReal,
                                               int           optInFastPeriod, /* From 2 to 100000 */
                                               TA_MAType     optInFastMAType,
                                               int           optInSlowPeriod, /* From 2 to 100000 */
                                               TA_MAType     optInSlowMAType,
                                               int           optInSignalPeriod, /* From 1 to 100000 */
                                               TA_MAType     optInSignalMAType,
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<double>^  outMACD,
                                               cli::array<double>^  outMACDSignal,
                                               cli::array<double>^  outMACDHist );

         #define TA_MACDEXT Core::MACDEXT
         #define TA_MACDEXT_Lookback Core::MACDEXT_Lookback

         static int MACDFIX_Lookback( int           optInSignalPeriod );  /* From 1 to 100000 */

         static enum class TA_RetCode MACDFIX( int    startIdx,
                                               int    endIdx,
                                               cli::array<double>^ inReal,
                                               int           optInSignalPeriod, /* From 1 to 100000 */
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<double>^  outMACD,
                                               cli::array<double>^  outMACDSignal,
                                               cli::array<double>^  outMACDHist );
         static enum class TA_RetCode MACDFIX( int    startIdx,
                                               int    endIdx,
                                               cli::array<float>^ inReal,
                                               int           optInSignalPeriod, /* From 1 to 100000 */
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<double>^  outMACD,
                                               cli::array<double>^  outMACDSignal,
                                               cli::array<double>^  outMACDHist );

         #define TA_MACDFIX Core::MACDFIX
         #define TA_MACDFIX_Lookback Core::MACDFIX_Lookback

         static int MFI_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode MFI( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inHigh,
                                           cli::array<double>^ inLow,
                                           cli::array<double>^ inClose,
                                           cli::array<int>^ inVolume,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode MFI( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inHigh,
                                           cli::array<float>^ inLow,
                                           cli::array<float>^ inClose,
                                           cli::array<int>^ inVolume,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_MFI Core::MFI
         #define TA_MFI_Lookback Core::MFI_Lookback

         static int MINUS_DI_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class TA_RetCode MINUS_DI( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inHigh,
                                                cli::array<double>^ inLow,
                                                cli::array<double>^ inClose,
                                                int           optInTimePeriod, /* From 1 to 100000 */
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );
         static enum class TA_RetCode MINUS_DI( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inHigh,
                                                cli::array<float>^ inLow,
                                                cli::array<float>^ inClose,
                                                int           optInTimePeriod, /* From 1 to 100000 */
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );

         #define TA_MINUS_DI Core::MINUS_DI
         #define TA_MINUS_DI_Lookback Core::MINUS_DI_Lookback

         static int MINUS_DM_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class TA_RetCode MINUS_DM( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inHigh,
                                                cli::array<double>^ inLow,
                                                int           optInTimePeriod, /* From 1 to 100000 */
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );
         static enum class TA_RetCode MINUS_DM( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inHigh,
                                                cli::array<float>^ inLow,
                                                int           optInTimePeriod, /* From 1 to 100000 */
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );

         #define TA_MINUS_DM Core::MINUS_DM
         #define TA_MINUS_DM_Lookback Core::MINUS_DM_Lookback

         static int MOM_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class TA_RetCode MOM( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           int           optInTimePeriod, /* From 1 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode MOM( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           int           optInTimePeriod, /* From 1 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_MOM Core::MOM
         #define TA_MOM_Lookback Core::MOM_Lookback

         static int PPO_Lookback( int           optInFastPeriod, /* From 2 to 100000 */
                                int           optInSlowPeriod, /* From 2 to 100000 */
                                TA_MAType     optInMAType ); 
         static enum class TA_RetCode PPO( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           int           optInFastPeriod, /* From 2 to 100000 */
                                           int           optInSlowPeriod, /* From 2 to 100000 */
                                           TA_MAType     optInMAType,
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode PPO( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           int           optInFastPeriod, /* From 2 to 100000 */
                                           int           optInSlowPeriod, /* From 2 to 100000 */
                                           TA_MAType     optInMAType,
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_PPO Core::PPO
         #define TA_PPO_Lookback Core::PPO_Lookback

         static int PLUS_DI_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class TA_RetCode PLUS_DI( int    startIdx,
                                               int    endIdx,
                                               cli::array<double>^ inHigh,
                                               cli::array<double>^ inLow,
                                               cli::array<double>^ inClose,
                                               int           optInTimePeriod, /* From 1 to 100000 */
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<double>^  outReal );
         static enum class TA_RetCode PLUS_DI( int    startIdx,
                                               int    endIdx,
                                               cli::array<float>^ inHigh,
                                               cli::array<float>^ inLow,
                                               cli::array<float>^ inClose,
                                               int           optInTimePeriod, /* From 1 to 100000 */
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<double>^  outReal );

         #define TA_PLUS_DI Core::PLUS_DI
         #define TA_PLUS_DI_Lookback Core::PLUS_DI_Lookback

         static int PLUS_DM_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class TA_RetCode PLUS_DM( int    startIdx,
                                               int    endIdx,
                                               cli::array<double>^ inHigh,
                                               cli::array<double>^ inLow,
                                               int           optInTimePeriod, /* From 1 to 100000 */
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<double>^  outReal );
         static enum class TA_RetCode PLUS_DM( int    startIdx,
                                               int    endIdx,
                                               cli::array<float>^ inHigh,
                                               cli::array<float>^ inLow,
                                               int           optInTimePeriod, /* From 1 to 100000 */
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<double>^  outReal );

         #define TA_PLUS_DM Core::PLUS_DM
         #define TA_PLUS_DM_Lookback Core::PLUS_DM_Lookback

         static int ROC_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class TA_RetCode ROC( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           int           optInTimePeriod, /* From 1 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode ROC( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           int           optInTimePeriod, /* From 1 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_ROC Core::ROC
         #define TA_ROC_Lookback Core::ROC_Lookback

         static int ROCP_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class TA_RetCode ROCP( int    startIdx,
                                            int    endIdx,
                                            cli::array<double>^ inReal,
                                            int           optInTimePeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );
         static enum class TA_RetCode ROCP( int    startIdx,
                                            int    endIdx,
                                            cli::array<float>^ inReal,
                                            int           optInTimePeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );

         #define TA_ROCP Core::ROCP
         #define TA_ROCP_Lookback Core::ROCP_Lookback

         static int ROCR_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class TA_RetCode ROCR( int    startIdx,
                                            int    endIdx,
                                            cli::array<double>^ inReal,
                                            int           optInTimePeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );
         static enum class TA_RetCode ROCR( int    startIdx,
                                            int    endIdx,
                                            cli::array<float>^ inReal,
                                            int           optInTimePeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );

         #define TA_ROCR Core::ROCR
         #define TA_ROCR_Lookback Core::ROCR_Lookback

         static int ROCR100_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class TA_RetCode ROCR100( int    startIdx,
                                               int    endIdx,
                                               cli::array<double>^ inReal,
                                               int           optInTimePeriod, /* From 1 to 100000 */
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<double>^  outReal );
         static enum class TA_RetCode ROCR100( int    startIdx,
                                               int    endIdx,
                                               cli::array<float>^ inReal,
                                               int           optInTimePeriod, /* From 1 to 100000 */
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<double>^  outReal );

         #define TA_ROCR100 Core::ROCR100
         #define TA_ROCR100_Lookback Core::ROCR100_Lookback

         static int RSI_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode RSI( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode RSI( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_RSI Core::RSI
         #define TA_RSI_Lookback Core::RSI_Lookback

         static int STOCH_Lookback( int           optInFastK_Period, /* From 1 to 100000 */
                                  int           optInSlowK_Period, /* From 1 to 100000 */
                                  TA_MAType     optInSlowK_MAType,
                                  int           optInSlowD_Period, /* From 1 to 100000 */
                                  TA_MAType     optInSlowD_MAType ); 
         static enum class TA_RetCode STOCH( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inHigh,
                                             cli::array<double>^ inLow,
                                             cli::array<double>^ inClose,
                                             int           optInFastK_Period, /* From 1 to 100000 */
                                             int           optInSlowK_Period, /* From 1 to 100000 */
                                             TA_MAType     optInSlowK_MAType,
                                             int           optInSlowD_Period, /* From 1 to 100000 */
                                             TA_MAType     optInSlowD_MAType,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outSlowK,
                                             cli::array<double>^  outSlowD );
         static enum class TA_RetCode STOCH( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inHigh,
                                             cli::array<float>^ inLow,
                                             cli::array<float>^ inClose,
                                             int           optInFastK_Period, /* From 1 to 100000 */
                                             int           optInSlowK_Period, /* From 1 to 100000 */
                                             TA_MAType     optInSlowK_MAType,
                                             int           optInSlowD_Period, /* From 1 to 100000 */
                                             TA_MAType     optInSlowD_MAType,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outSlowK,
                                             cli::array<double>^  outSlowD );

         #define TA_STOCH Core::STOCH
         #define TA_STOCH_Lookback Core::STOCH_Lookback

         static int STOCHF_Lookback( int           optInFastK_Period, /* From 1 to 100000 */
                                   int           optInFastD_Period, /* From 1 to 100000 */
                                   TA_MAType     optInFastD_MAType ); 
         static enum class TA_RetCode STOCHF( int    startIdx,
                                              int    endIdx,
                                              cli::array<double>^ inHigh,
                                              cli::array<double>^ inLow,
                                              cli::array<double>^ inClose,
                                              int           optInFastK_Period, /* From 1 to 100000 */
                                              int           optInFastD_Period, /* From 1 to 100000 */
                                              TA_MAType     optInFastD_MAType,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outFastK,
                                              cli::array<double>^  outFastD );
         static enum class TA_RetCode STOCHF( int    startIdx,
                                              int    endIdx,
                                              cli::array<float>^ inHigh,
                                              cli::array<float>^ inLow,
                                              cli::array<float>^ inClose,
                                              int           optInFastK_Period, /* From 1 to 100000 */
                                              int           optInFastD_Period, /* From 1 to 100000 */
                                              TA_MAType     optInFastD_MAType,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outFastK,
                                              cli::array<double>^  outFastD );

         #define TA_STOCHF Core::STOCHF
         #define TA_STOCHF_Lookback Core::STOCHF_Lookback

         static int STOCHRSI_Lookback( int           optInTimePeriod, /* From 2 to 100000 */
                                     int           optInFastK_Period, /* From 1 to 100000 */
                                     int           optInFastD_Period, /* From 1 to 100000 */
                                     TA_MAType     optInFastD_MAType ); 
         static enum class TA_RetCode STOCHRSI( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inReal,
                                                int           optInTimePeriod, /* From 2 to 100000 */
                                                int           optInFastK_Period, /* From 1 to 100000 */
                                                int           optInFastD_Period, /* From 1 to 100000 */
                                                TA_MAType     optInFastD_MAType,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outFastK,
                                                cli::array<double>^  outFastD );
         static enum class TA_RetCode STOCHRSI( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inReal,
                                                int           optInTimePeriod, /* From 2 to 100000 */
                                                int           optInFastK_Period, /* From 1 to 100000 */
                                                int           optInFastD_Period, /* From 1 to 100000 */
                                                TA_MAType     optInFastD_MAType,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outFastK,
                                                cli::array<double>^  outFastD );

         #define TA_STOCHRSI Core::STOCHRSI
         #define TA_STOCHRSI_Lookback Core::STOCHRSI_Lookback

         static int TRIX_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class TA_RetCode TRIX( int    startIdx,
                                            int    endIdx,
                                            cli::array<double>^ inReal,
                                            int           optInTimePeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );
         static enum class TA_RetCode TRIX( int    startIdx,
                                            int    endIdx,
                                            cli::array<float>^ inReal,
                                            int           optInTimePeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );

         #define TA_TRIX Core::TRIX
         #define TA_TRIX_Lookback Core::TRIX_Lookback

         static int ULTOSC_Lookback( int           optInTimePeriod1, /* From 1 to 100000 */
                                   int           optInTimePeriod2, /* From 1 to 100000 */
                                   int           optInTimePeriod3 );  /* From 1 to 100000 */

         static enum class TA_RetCode ULTOSC( int    startIdx,
                                              int    endIdx,
                                              cli::array<double>^ inHigh,
                                              cli::array<double>^ inLow,
                                              cli::array<double>^ inClose,
                                              int           optInTimePeriod1, /* From 1 to 100000 */
                                              int           optInTimePeriod2, /* From 1 to 100000 */
                                              int           optInTimePeriod3, /* From 1 to 100000 */
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outReal );
         static enum class TA_RetCode ULTOSC( int    startIdx,
                                              int    endIdx,
                                              cli::array<float>^ inHigh,
                                              cli::array<float>^ inLow,
                                              cli::array<float>^ inClose,
                                              int           optInTimePeriod1, /* From 1 to 100000 */
                                              int           optInTimePeriod2, /* From 1 to 100000 */
                                              int           optInTimePeriod3, /* From 1 to 100000 */
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outReal );

         #define TA_ULTOSC Core::ULTOSC
         #define TA_ULTOSC_Lookback Core::ULTOSC_Lookback

         static int WILLR_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode WILLR( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inHigh,
                                             cli::array<double>^ inLow,
                                             cli::array<double>^ inClose,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );
         static enum class TA_RetCode WILLR( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inHigh,
                                             cli::array<float>^ inLow,
                                             cli::array<float>^ inClose,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );

         #define TA_WILLR Core::WILLR
         #define TA_WILLR_Lookback Core::WILLR_Lookback

         static int HT_DCPERIOD_Lookback( void );

         static enum class TA_RetCode HT_DCPERIOD( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inReal,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<double>^  outReal );
         static enum class TA_RetCode HT_DCPERIOD( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inReal,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<double>^  outReal );

         #define TA_HT_DCPERIOD Core::HT_DCPERIOD
         #define TA_HT_DCPERIOD_Lookback Core::HT_DCPERIOD_Lookback

         static int HT_DCPHASE_Lookback( void );

         static enum class TA_RetCode HT_DCPHASE( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<double>^ inReal,
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<double>^  outReal );
         static enum class TA_RetCode HT_DCPHASE( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<float>^ inReal,
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<double>^  outReal );

         #define TA_HT_DCPHASE Core::HT_DCPHASE
         #define TA_HT_DCPHASE_Lookback Core::HT_DCPHASE_Lookback

         static int HT_PHASOR_Lookback( void );

         static enum class TA_RetCode HT_PHASOR( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<double>^ inReal,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<double>^  outInPhase,
                                                 cli::array<double>^  outQuadrature );
         static enum class TA_RetCode HT_PHASOR( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<float>^ inReal,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<double>^  outInPhase,
                                                 cli::array<double>^  outQuadrature );

         #define TA_HT_PHASOR Core::HT_PHASOR
         #define TA_HT_PHASOR_Lookback Core::HT_PHASOR_Lookback

         static int HT_SINE_Lookback( void );

         static enum class TA_RetCode HT_SINE( int    startIdx,
                                               int    endIdx,
                                               cli::array<double>^ inReal,
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<double>^  outSine,
                                               cli::array<double>^  outLeadSine );
         static enum class TA_RetCode HT_SINE( int    startIdx,
                                               int    endIdx,
                                               cli::array<float>^ inReal,
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<double>^  outSine,
                                               cli::array<double>^  outLeadSine );

         #define TA_HT_SINE Core::HT_SINE
         #define TA_HT_SINE_Lookback Core::HT_SINE_Lookback

         static int HT_TRENDMODE_Lookback( void );

         static enum class TA_RetCode HT_TRENDMODE( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<double>^ inReal,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );
         static enum class TA_RetCode HT_TRENDMODE( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<float>^ inReal,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );

         #define TA_HT_TRENDMODE Core::HT_TRENDMODE
         #define TA_HT_TRENDMODE_Lookback Core::HT_TRENDMODE_Lookback

         static int AD_Lookback( void );

         static enum class TA_RetCode AD( int    startIdx,
                                          int    endIdx,
                                          cli::array<double>^ inHigh,
                                          cli::array<double>^ inLow,
                                          cli::array<double>^ inClose,
                                          cli::array<int>^ inVolume,
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outReal );
         static enum class TA_RetCode AD( int    startIdx,
                                          int    endIdx,
                                          cli::array<float>^ inHigh,
                                          cli::array<float>^ inLow,
                                          cli::array<float>^ inClose,
                                          cli::array<int>^ inVolume,
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outReal );

         #define TA_AD Core::AD
         #define TA_AD_Lookback Core::AD_Lookback

         static int ADOSC_Lookback( int           optInFastPeriod, /* From 2 to 100000 */
                                  int           optInSlowPeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode ADOSC( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inHigh,
                                             cli::array<double>^ inLow,
                                             cli::array<double>^ inClose,
                                             cli::array<int>^ inVolume,
                                             int           optInFastPeriod, /* From 2 to 100000 */
                                             int           optInSlowPeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );
         static enum class TA_RetCode ADOSC( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inHigh,
                                             cli::array<float>^ inLow,
                                             cli::array<float>^ inClose,
                                             cli::array<int>^ inVolume,
                                             int           optInFastPeriod, /* From 2 to 100000 */
                                             int           optInSlowPeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );

         #define TA_ADOSC Core::ADOSC
         #define TA_ADOSC_Lookback Core::ADOSC_Lookback

         static int OBV_Lookback( void );

         static enum class TA_RetCode OBV( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           cli::array<int>^ inVolume,
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<int>^  outInteger );
         static enum class TA_RetCode OBV( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           cli::array<int>^ inVolume,
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<int>^  outInteger );

         #define TA_OBV Core::OBV
         #define TA_OBV_Lookback Core::OBV_Lookback

         static int CDL2CROWS_Lookback( void );

         static enum class TA_RetCode CDL2CROWS( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<double>^ inOpen,
                                                 cli::array<double>^ inHigh,
                                                 cli::array<double>^ inLow,
                                                 cli::array<double>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );
         static enum class TA_RetCode CDL2CROWS( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<float>^ inOpen,
                                                 cli::array<float>^ inHigh,
                                                 cli::array<float>^ inLow,
                                                 cli::array<float>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );

         #define TA_CDL2CROWS Core::CDL2CROWS
         #define TA_CDL2CROWS_Lookback Core::CDL2CROWS_Lookback

         static int CDL3BLACKCROWS_Lookback( void );

         static enum class TA_RetCode CDL3BLACKCROWS( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<double>^ inOpen,
                                                      cli::array<double>^ inHigh,
                                                      cli::array<double>^ inLow,
                                                      cli::array<double>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );
         static enum class TA_RetCode CDL3BLACKCROWS( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<float>^ inOpen,
                                                      cli::array<float>^ inHigh,
                                                      cli::array<float>^ inLow,
                                                      cli::array<float>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );

         #define TA_CDL3BLACKCROWS Core::CDL3BLACKCROWS
         #define TA_CDL3BLACKCROWS_Lookback Core::CDL3BLACKCROWS_Lookback

         static int CDL3INSIDE_Lookback( void );

         static enum class TA_RetCode CDL3INSIDE( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<double>^ inOpen,
                                                  cli::array<double>^ inHigh,
                                                  cli::array<double>^ inLow,
                                                  cli::array<double>^ inClose,
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<int>^  outInteger );
         static enum class TA_RetCode CDL3INSIDE( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<float>^ inOpen,
                                                  cli::array<float>^ inHigh,
                                                  cli::array<float>^ inLow,
                                                  cli::array<float>^ inClose,
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<int>^  outInteger );

         #define TA_CDL3INSIDE Core::CDL3INSIDE
         #define TA_CDL3INSIDE_Lookback Core::CDL3INSIDE_Lookback

         static int CDL3LINESTRIKE_Lookback( void );

         static enum class TA_RetCode CDL3LINESTRIKE( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<double>^ inOpen,
                                                      cli::array<double>^ inHigh,
                                                      cli::array<double>^ inLow,
                                                      cli::array<double>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );
         static enum class TA_RetCode CDL3LINESTRIKE( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<float>^ inOpen,
                                                      cli::array<float>^ inHigh,
                                                      cli::array<float>^ inLow,
                                                      cli::array<float>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );

         #define TA_CDL3LINESTRIKE Core::CDL3LINESTRIKE
         #define TA_CDL3LINESTRIKE_Lookback Core::CDL3LINESTRIKE_Lookback

         static int CDL3OUTSIDE_Lookback( void );

         static enum class TA_RetCode CDL3OUTSIDE( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inOpen,
                                                   cli::array<double>^ inHigh,
                                                   cli::array<double>^ inLow,
                                                   cli::array<double>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );
         static enum class TA_RetCode CDL3OUTSIDE( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inOpen,
                                                   cli::array<float>^ inHigh,
                                                   cli::array<float>^ inLow,
                                                   cli::array<float>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );

         #define TA_CDL3OUTSIDE Core::CDL3OUTSIDE
         #define TA_CDL3OUTSIDE_Lookback Core::CDL3OUTSIDE_Lookback

         static int CDL3STARSINSOUTH_Lookback( void );

         static enum class TA_RetCode CDL3STARSINSOUTH( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<double>^ inOpen,
                                                        cli::array<double>^ inHigh,
                                                        cli::array<double>^ inLow,
                                                        cli::array<double>^ inClose,
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );
         static enum class TA_RetCode CDL3STARSINSOUTH( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<float>^ inOpen,
                                                        cli::array<float>^ inHigh,
                                                        cli::array<float>^ inLow,
                                                        cli::array<float>^ inClose,
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );

         #define TA_CDL3STARSINSOUTH Core::CDL3STARSINSOUTH
         #define TA_CDL3STARSINSOUTH_Lookback Core::CDL3STARSINSOUTH_Lookback

         static int CDL3WHITESOLDIERS_Lookback( void );

         static enum class TA_RetCode CDL3WHITESOLDIERS( int    startIdx,
                                                         int    endIdx,
                                                         cli::array<double>^ inOpen,
                                                         cli::array<double>^ inHigh,
                                                         cli::array<double>^ inLow,
                                                         cli::array<double>^ inClose,
                                                         [Out]int%    outBegIdx,
                                                         [Out]int%    outNbElement,
                                                         cli::array<int>^  outInteger );
         static enum class TA_RetCode CDL3WHITESOLDIERS( int    startIdx,
                                                         int    endIdx,
                                                         cli::array<float>^ inOpen,
                                                         cli::array<float>^ inHigh,
                                                         cli::array<float>^ inLow,
                                                         cli::array<float>^ inClose,
                                                         [Out]int%    outBegIdx,
                                                         [Out]int%    outNbElement,
                                                         cli::array<int>^  outInteger );

         #define TA_CDL3WHITESOLDIERS Core::CDL3WHITESOLDIERS
         #define TA_CDL3WHITESOLDIERS_Lookback Core::CDL3WHITESOLDIERS_Lookback

         static int CDLABANDONEDBABY_Lookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum class TA_RetCode CDLABANDONEDBABY( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<double>^ inOpen,
                                                        cli::array<double>^ inHigh,
                                                        cli::array<double>^ inLow,
                                                        cli::array<double>^ inClose,
                                                        double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLABANDONEDBABY( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<float>^ inOpen,
                                                        cli::array<float>^ inHigh,
                                                        cli::array<float>^ inLow,
                                                        cli::array<float>^ inClose,
                                                        double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );

         #define TA_CDLABANDONEDBABY Core::CDLABANDONEDBABY
         #define TA_CDLABANDONEDBABY_Lookback Core::CDLABANDONEDBABY_Lookback

         static int CDLADVANCEBLOCK_Lookback( void );

         static enum class TA_RetCode CDLADVANCEBLOCK( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<double>^ inOpen,
                                                       cli::array<double>^ inHigh,
                                                       cli::array<double>^ inLow,
                                                       cli::array<double>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLADVANCEBLOCK( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<float>^ inOpen,
                                                       cli::array<float>^ inHigh,
                                                       cli::array<float>^ inLow,
                                                       cli::array<float>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );

         #define TA_CDLADVANCEBLOCK Core::CDLADVANCEBLOCK
         #define TA_CDLADVANCEBLOCK_Lookback Core::CDLADVANCEBLOCK_Lookback

         static int CDLBELTHOLD_Lookback( void );

         static enum class TA_RetCode CDLBELTHOLD( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inOpen,
                                                   cli::array<double>^ inHigh,
                                                   cli::array<double>^ inLow,
                                                   cli::array<double>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLBELTHOLD( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inOpen,
                                                   cli::array<float>^ inHigh,
                                                   cli::array<float>^ inLow,
                                                   cli::array<float>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );

         #define TA_CDLBELTHOLD Core::CDLBELTHOLD
         #define TA_CDLBELTHOLD_Lookback Core::CDLBELTHOLD_Lookback

         static int CDLBREAKAWAY_Lookback( void );

         static enum class TA_RetCode CDLBREAKAWAY( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<double>^ inOpen,
                                                    cli::array<double>^ inHigh,
                                                    cli::array<double>^ inLow,
                                                    cli::array<double>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLBREAKAWAY( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<float>^ inOpen,
                                                    cli::array<float>^ inHigh,
                                                    cli::array<float>^ inLow,
                                                    cli::array<float>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );

         #define TA_CDLBREAKAWAY Core::CDLBREAKAWAY
         #define TA_CDLBREAKAWAY_Lookback Core::CDLBREAKAWAY_Lookback

         static int CDLCLOSINGMARUBOZU_Lookback( void );

         static enum class TA_RetCode CDLCLOSINGMARUBOZU( int    startIdx,
                                                          int    endIdx,
                                                          cli::array<double>^ inOpen,
                                                          cli::array<double>^ inHigh,
                                                          cli::array<double>^ inLow,
                                                          cli::array<double>^ inClose,
                                                          [Out]int%    outBegIdx,
                                                          [Out]int%    outNbElement,
                                                          cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLCLOSINGMARUBOZU( int    startIdx,
                                                          int    endIdx,
                                                          cli::array<float>^ inOpen,
                                                          cli::array<float>^ inHigh,
                                                          cli::array<float>^ inLow,
                                                          cli::array<float>^ inClose,
                                                          [Out]int%    outBegIdx,
                                                          [Out]int%    outNbElement,
                                                          cli::array<int>^  outInteger );

         #define TA_CDLCLOSINGMARUBOZU Core::CDLCLOSINGMARUBOZU
         #define TA_CDLCLOSINGMARUBOZU_Lookback Core::CDLCLOSINGMARUBOZU_Lookback

         static int CDLCONCEALBABYSWALL_Lookback( void );

         static enum class TA_RetCode CDLCONCEALBABYSWALL( int    startIdx,
                                                           int    endIdx,
                                                           cli::array<double>^ inOpen,
                                                           cli::array<double>^ inHigh,
                                                           cli::array<double>^ inLow,
                                                           cli::array<double>^ inClose,
                                                           [Out]int%    outBegIdx,
                                                           [Out]int%    outNbElement,
                                                           cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLCONCEALBABYSWALL( int    startIdx,
                                                           int    endIdx,
                                                           cli::array<float>^ inOpen,
                                                           cli::array<float>^ inHigh,
                                                           cli::array<float>^ inLow,
                                                           cli::array<float>^ inClose,
                                                           [Out]int%    outBegIdx,
                                                           [Out]int%    outNbElement,
                                                           cli::array<int>^  outInteger );

         #define TA_CDLCONCEALBABYSWALL Core::CDLCONCEALBABYSWALL
         #define TA_CDLCONCEALBABYSWALL_Lookback Core::CDLCONCEALBABYSWALL_Lookback

         static int CDLCOUNTERATTACK_Lookback( void );

         static enum class TA_RetCode CDLCOUNTERATTACK( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<double>^ inOpen,
                                                        cli::array<double>^ inHigh,
                                                        cli::array<double>^ inLow,
                                                        cli::array<double>^ inClose,
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLCOUNTERATTACK( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<float>^ inOpen,
                                                        cli::array<float>^ inHigh,
                                                        cli::array<float>^ inLow,
                                                        cli::array<float>^ inClose,
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );

         #define TA_CDLCOUNTERATTACK Core::CDLCOUNTERATTACK
         #define TA_CDLCOUNTERATTACK_Lookback Core::CDLCOUNTERATTACK_Lookback

         static int CDLDARKCLOUDCOVER_Lookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum class TA_RetCode CDLDARKCLOUDCOVER( int    startIdx,
                                                         int    endIdx,
                                                         cli::array<double>^ inOpen,
                                                         cli::array<double>^ inHigh,
                                                         cli::array<double>^ inLow,
                                                         cli::array<double>^ inClose,
                                                         double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                         [Out]int%    outBegIdx,
                                                         [Out]int%    outNbElement,
                                                         cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLDARKCLOUDCOVER( int    startIdx,
                                                         int    endIdx,
                                                         cli::array<float>^ inOpen,
                                                         cli::array<float>^ inHigh,
                                                         cli::array<float>^ inLow,
                                                         cli::array<float>^ inClose,
                                                         double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                         [Out]int%    outBegIdx,
                                                         [Out]int%    outNbElement,
                                                         cli::array<int>^  outInteger );

         #define TA_CDLDARKCLOUDCOVER Core::CDLDARKCLOUDCOVER
         #define TA_CDLDARKCLOUDCOVER_Lookback Core::CDLDARKCLOUDCOVER_Lookback

         static int CDLDOJI_Lookback( void );

         static enum class TA_RetCode CDLDOJI( int    startIdx,
                                               int    endIdx,
                                               cli::array<double>^ inOpen,
                                               cli::array<double>^ inHigh,
                                               cli::array<double>^ inLow,
                                               cli::array<double>^ inClose,
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLDOJI( int    startIdx,
                                               int    endIdx,
                                               cli::array<float>^ inOpen,
                                               cli::array<float>^ inHigh,
                                               cli::array<float>^ inLow,
                                               cli::array<float>^ inClose,
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<int>^  outInteger );

         #define TA_CDLDOJI Core::CDLDOJI
         #define TA_CDLDOJI_Lookback Core::CDLDOJI_Lookback

         static int CDLDOJISTAR_Lookback( void );

         static enum class TA_RetCode CDLDOJISTAR( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inOpen,
                                                   cli::array<double>^ inHigh,
                                                   cli::array<double>^ inLow,
                                                   cli::array<double>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLDOJISTAR( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inOpen,
                                                   cli::array<float>^ inHigh,
                                                   cli::array<float>^ inLow,
                                                   cli::array<float>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );

         #define TA_CDLDOJISTAR Core::CDLDOJISTAR
         #define TA_CDLDOJISTAR_Lookback Core::CDLDOJISTAR_Lookback

         static int CDLDRAGONFLYDOJI_Lookback( void );

         static enum class TA_RetCode CDLDRAGONFLYDOJI( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<double>^ inOpen,
                                                        cli::array<double>^ inHigh,
                                                        cli::array<double>^ inLow,
                                                        cli::array<double>^ inClose,
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLDRAGONFLYDOJI( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<float>^ inOpen,
                                                        cli::array<float>^ inHigh,
                                                        cli::array<float>^ inLow,
                                                        cli::array<float>^ inClose,
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );

         #define TA_CDLDRAGONFLYDOJI Core::CDLDRAGONFLYDOJI
         #define TA_CDLDRAGONFLYDOJI_Lookback Core::CDLDRAGONFLYDOJI_Lookback

         static int CDLENGULFING_Lookback( void );

         static enum class TA_RetCode CDLENGULFING( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<double>^ inOpen,
                                                    cli::array<double>^ inHigh,
                                                    cli::array<double>^ inLow,
                                                    cli::array<double>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLENGULFING( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<float>^ inOpen,
                                                    cli::array<float>^ inHigh,
                                                    cli::array<float>^ inLow,
                                                    cli::array<float>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );

         #define TA_CDLENGULFING Core::CDLENGULFING
         #define TA_CDLENGULFING_Lookback Core::CDLENGULFING_Lookback

         static int CDLEVENINGDOJISTAR_Lookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum class TA_RetCode CDLEVENINGDOJISTAR( int    startIdx,
                                                          int    endIdx,
                                                          cli::array<double>^ inOpen,
                                                          cli::array<double>^ inHigh,
                                                          cli::array<double>^ inLow,
                                                          cli::array<double>^ inClose,
                                                          double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                          [Out]int%    outBegIdx,
                                                          [Out]int%    outNbElement,
                                                          cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLEVENINGDOJISTAR( int    startIdx,
                                                          int    endIdx,
                                                          cli::array<float>^ inOpen,
                                                          cli::array<float>^ inHigh,
                                                          cli::array<float>^ inLow,
                                                          cli::array<float>^ inClose,
                                                          double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                          [Out]int%    outBegIdx,
                                                          [Out]int%    outNbElement,
                                                          cli::array<int>^  outInteger );

         #define TA_CDLEVENINGDOJISTAR Core::CDLEVENINGDOJISTAR
         #define TA_CDLEVENINGDOJISTAR_Lookback Core::CDLEVENINGDOJISTAR_Lookback

         static int CDLEVENINGSTAR_Lookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum class TA_RetCode CDLEVENINGSTAR( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<double>^ inOpen,
                                                      cli::array<double>^ inHigh,
                                                      cli::array<double>^ inLow,
                                                      cli::array<double>^ inClose,
                                                      double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLEVENINGSTAR( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<float>^ inOpen,
                                                      cli::array<float>^ inHigh,
                                                      cli::array<float>^ inLow,
                                                      cli::array<float>^ inClose,
                                                      double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );

         #define TA_CDLEVENINGSTAR Core::CDLEVENINGSTAR
         #define TA_CDLEVENINGSTAR_Lookback Core::CDLEVENINGSTAR_Lookback

         static int CDLGAPSIDESIDEWHITE_Lookback( void );

         static enum class TA_RetCode CDLGAPSIDESIDEWHITE( int    startIdx,
                                                           int    endIdx,
                                                           cli::array<double>^ inOpen,
                                                           cli::array<double>^ inHigh,
                                                           cli::array<double>^ inLow,
                                                           cli::array<double>^ inClose,
                                                           [Out]int%    outBegIdx,
                                                           [Out]int%    outNbElement,
                                                           cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLGAPSIDESIDEWHITE( int    startIdx,
                                                           int    endIdx,
                                                           cli::array<float>^ inOpen,
                                                           cli::array<float>^ inHigh,
                                                           cli::array<float>^ inLow,
                                                           cli::array<float>^ inClose,
                                                           [Out]int%    outBegIdx,
                                                           [Out]int%    outNbElement,
                                                           cli::array<int>^  outInteger );

         #define TA_CDLGAPSIDESIDEWHITE Core::CDLGAPSIDESIDEWHITE
         #define TA_CDLGAPSIDESIDEWHITE_Lookback Core::CDLGAPSIDESIDEWHITE_Lookback

         static int CDLGRAVESTONEDOJI_Lookback( void );

         static enum class TA_RetCode CDLGRAVESTONEDOJI( int    startIdx,
                                                         int    endIdx,
                                                         cli::array<double>^ inOpen,
                                                         cli::array<double>^ inHigh,
                                                         cli::array<double>^ inLow,
                                                         cli::array<double>^ inClose,
                                                         [Out]int%    outBegIdx,
                                                         [Out]int%    outNbElement,
                                                         cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLGRAVESTONEDOJI( int    startIdx,
                                                         int    endIdx,
                                                         cli::array<float>^ inOpen,
                                                         cli::array<float>^ inHigh,
                                                         cli::array<float>^ inLow,
                                                         cli::array<float>^ inClose,
                                                         [Out]int%    outBegIdx,
                                                         [Out]int%    outNbElement,
                                                         cli::array<int>^  outInteger );

         #define TA_CDLGRAVESTONEDOJI Core::CDLGRAVESTONEDOJI
         #define TA_CDLGRAVESTONEDOJI_Lookback Core::CDLGRAVESTONEDOJI_Lookback

         static int CDLHAMMER_Lookback( void );

         static enum class TA_RetCode CDLHAMMER( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<double>^ inOpen,
                                                 cli::array<double>^ inHigh,
                                                 cli::array<double>^ inLow,
                                                 cli::array<double>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLHAMMER( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<float>^ inOpen,
                                                 cli::array<float>^ inHigh,
                                                 cli::array<float>^ inLow,
                                                 cli::array<float>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );

         #define TA_CDLHAMMER Core::CDLHAMMER
         #define TA_CDLHAMMER_Lookback Core::CDLHAMMER_Lookback

         static int CDLHANGINGMAN_Lookback( void );

         static enum class TA_RetCode CDLHANGINGMAN( int    startIdx,
                                                     int    endIdx,
                                                     cli::array<double>^ inOpen,
                                                     cli::array<double>^ inHigh,
                                                     cli::array<double>^ inLow,
                                                     cli::array<double>^ inClose,
                                                     [Out]int%    outBegIdx,
                                                     [Out]int%    outNbElement,
                                                     cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLHANGINGMAN( int    startIdx,
                                                     int    endIdx,
                                                     cli::array<float>^ inOpen,
                                                     cli::array<float>^ inHigh,
                                                     cli::array<float>^ inLow,
                                                     cli::array<float>^ inClose,
                                                     [Out]int%    outBegIdx,
                                                     [Out]int%    outNbElement,
                                                     cli::array<int>^  outInteger );

         #define TA_CDLHANGINGMAN Core::CDLHANGINGMAN
         #define TA_CDLHANGINGMAN_Lookback Core::CDLHANGINGMAN_Lookback

         static int CDLHARAMI_Lookback( void );

         static enum class TA_RetCode CDLHARAMI( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<double>^ inOpen,
                                                 cli::array<double>^ inHigh,
                                                 cli::array<double>^ inLow,
                                                 cli::array<double>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLHARAMI( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<float>^ inOpen,
                                                 cli::array<float>^ inHigh,
                                                 cli::array<float>^ inLow,
                                                 cli::array<float>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );

         #define TA_CDLHARAMI Core::CDLHARAMI
         #define TA_CDLHARAMI_Lookback Core::CDLHARAMI_Lookback

         static int CDLHARAMICROSS_Lookback( void );

         static enum class TA_RetCode CDLHARAMICROSS( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<double>^ inOpen,
                                                      cli::array<double>^ inHigh,
                                                      cli::array<double>^ inLow,
                                                      cli::array<double>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLHARAMICROSS( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<float>^ inOpen,
                                                      cli::array<float>^ inHigh,
                                                      cli::array<float>^ inLow,
                                                      cli::array<float>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );

         #define TA_CDLHARAMICROSS Core::CDLHARAMICROSS
         #define TA_CDLHARAMICROSS_Lookback Core::CDLHARAMICROSS_Lookback

         static int CDLHIGHWAVE_Lookback( void );

         static enum class TA_RetCode CDLHIGHWAVE( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inOpen,
                                                   cli::array<double>^ inHigh,
                                                   cli::array<double>^ inLow,
                                                   cli::array<double>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLHIGHWAVE( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inOpen,
                                                   cli::array<float>^ inHigh,
                                                   cli::array<float>^ inLow,
                                                   cli::array<float>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );

         #define TA_CDLHIGHWAVE Core::CDLHIGHWAVE
         #define TA_CDLHIGHWAVE_Lookback Core::CDLHIGHWAVE_Lookback

         static int CDLHIKKAKE_Lookback( void );

         static enum class TA_RetCode CDLHIKKAKE( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<double>^ inOpen,
                                                  cli::array<double>^ inHigh,
                                                  cli::array<double>^ inLow,
                                                  cli::array<double>^ inClose,
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLHIKKAKE( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<float>^ inOpen,
                                                  cli::array<float>^ inHigh,
                                                  cli::array<float>^ inLow,
                                                  cli::array<float>^ inClose,
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<int>^  outInteger );

         #define TA_CDLHIKKAKE Core::CDLHIKKAKE
         #define TA_CDLHIKKAKE_Lookback Core::CDLHIKKAKE_Lookback

         static int CDLHIKKAKEMOD_Lookback( void );

         static enum class TA_RetCode CDLHIKKAKEMOD( int    startIdx,
                                                     int    endIdx,
                                                     cli::array<double>^ inOpen,
                                                     cli::array<double>^ inHigh,
                                                     cli::array<double>^ inLow,
                                                     cli::array<double>^ inClose,
                                                     [Out]int%    outBegIdx,
                                                     [Out]int%    outNbElement,
                                                     cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLHIKKAKEMOD( int    startIdx,
                                                     int    endIdx,
                                                     cli::array<float>^ inOpen,
                                                     cli::array<float>^ inHigh,
                                                     cli::array<float>^ inLow,
                                                     cli::array<float>^ inClose,
                                                     [Out]int%    outBegIdx,
                                                     [Out]int%    outNbElement,
                                                     cli::array<int>^  outInteger );

         #define TA_CDLHIKKAKEMOD Core::CDLHIKKAKEMOD
         #define TA_CDLHIKKAKEMOD_Lookback Core::CDLHIKKAKEMOD_Lookback

         static int CDLHOMINGPIGEON_Lookback( void );

         static enum class TA_RetCode CDLHOMINGPIGEON( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<double>^ inOpen,
                                                       cli::array<double>^ inHigh,
                                                       cli::array<double>^ inLow,
                                                       cli::array<double>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLHOMINGPIGEON( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<float>^ inOpen,
                                                       cli::array<float>^ inHigh,
                                                       cli::array<float>^ inLow,
                                                       cli::array<float>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );

         #define TA_CDLHOMINGPIGEON Core::CDLHOMINGPIGEON
         #define TA_CDLHOMINGPIGEON_Lookback Core::CDLHOMINGPIGEON_Lookback

         static int CDLIDENTICAL3CROWS_Lookback( void );

         static enum class TA_RetCode CDLIDENTICAL3CROWS( int    startIdx,
                                                          int    endIdx,
                                                          cli::array<double>^ inOpen,
                                                          cli::array<double>^ inHigh,
                                                          cli::array<double>^ inLow,
                                                          cli::array<double>^ inClose,
                                                          [Out]int%    outBegIdx,
                                                          [Out]int%    outNbElement,
                                                          cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLIDENTICAL3CROWS( int    startIdx,
                                                          int    endIdx,
                                                          cli::array<float>^ inOpen,
                                                          cli::array<float>^ inHigh,
                                                          cli::array<float>^ inLow,
                                                          cli::array<float>^ inClose,
                                                          [Out]int%    outBegIdx,
                                                          [Out]int%    outNbElement,
                                                          cli::array<int>^  outInteger );

         #define TA_CDLIDENTICAL3CROWS Core::CDLIDENTICAL3CROWS
         #define TA_CDLIDENTICAL3CROWS_Lookback Core::CDLIDENTICAL3CROWS_Lookback

         static int CDLINNECK_Lookback( void );

         static enum class TA_RetCode CDLINNECK( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<double>^ inOpen,
                                                 cli::array<double>^ inHigh,
                                                 cli::array<double>^ inLow,
                                                 cli::array<double>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLINNECK( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<float>^ inOpen,
                                                 cli::array<float>^ inHigh,
                                                 cli::array<float>^ inLow,
                                                 cli::array<float>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );

         #define TA_CDLINNECK Core::CDLINNECK
         #define TA_CDLINNECK_Lookback Core::CDLINNECK_Lookback

         static int CDLINVERTEDHAMMER_Lookback( void );

         static enum class TA_RetCode CDLINVERTEDHAMMER( int    startIdx,
                                                         int    endIdx,
                                                         cli::array<double>^ inOpen,
                                                         cli::array<double>^ inHigh,
                                                         cli::array<double>^ inLow,
                                                         cli::array<double>^ inClose,
                                                         [Out]int%    outBegIdx,
                                                         [Out]int%    outNbElement,
                                                         cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLINVERTEDHAMMER( int    startIdx,
                                                         int    endIdx,
                                                         cli::array<float>^ inOpen,
                                                         cli::array<float>^ inHigh,
                                                         cli::array<float>^ inLow,
                                                         cli::array<float>^ inClose,
                                                         [Out]int%    outBegIdx,
                                                         [Out]int%    outNbElement,
                                                         cli::array<int>^  outInteger );

         #define TA_CDLINVERTEDHAMMER Core::CDLINVERTEDHAMMER
         #define TA_CDLINVERTEDHAMMER_Lookback Core::CDLINVERTEDHAMMER_Lookback

         static int CDLKICKING_Lookback( void );

         static enum class TA_RetCode CDLKICKING( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<double>^ inOpen,
                                                  cli::array<double>^ inHigh,
                                                  cli::array<double>^ inLow,
                                                  cli::array<double>^ inClose,
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLKICKING( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<float>^ inOpen,
                                                  cli::array<float>^ inHigh,
                                                  cli::array<float>^ inLow,
                                                  cli::array<float>^ inClose,
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<int>^  outInteger );

         #define TA_CDLKICKING Core::CDLKICKING
         #define TA_CDLKICKING_Lookback Core::CDLKICKING_Lookback

         static int CDLKICKINGBYLENGTH_Lookback( void );

         static enum class TA_RetCode CDLKICKINGBYLENGTH( int    startIdx,
                                                          int    endIdx,
                                                          cli::array<double>^ inOpen,
                                                          cli::array<double>^ inHigh,
                                                          cli::array<double>^ inLow,
                                                          cli::array<double>^ inClose,
                                                          [Out]int%    outBegIdx,
                                                          [Out]int%    outNbElement,
                                                          cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLKICKINGBYLENGTH( int    startIdx,
                                                          int    endIdx,
                                                          cli::array<float>^ inOpen,
                                                          cli::array<float>^ inHigh,
                                                          cli::array<float>^ inLow,
                                                          cli::array<float>^ inClose,
                                                          [Out]int%    outBegIdx,
                                                          [Out]int%    outNbElement,
                                                          cli::array<int>^  outInteger );

         #define TA_CDLKICKINGBYLENGTH Core::CDLKICKINGBYLENGTH
         #define TA_CDLKICKINGBYLENGTH_Lookback Core::CDLKICKINGBYLENGTH_Lookback

         static int CDLLADDERBOTTOM_Lookback( void );

         static enum class TA_RetCode CDLLADDERBOTTOM( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<double>^ inOpen,
                                                       cli::array<double>^ inHigh,
                                                       cli::array<double>^ inLow,
                                                       cli::array<double>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLLADDERBOTTOM( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<float>^ inOpen,
                                                       cli::array<float>^ inHigh,
                                                       cli::array<float>^ inLow,
                                                       cli::array<float>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );

         #define TA_CDLLADDERBOTTOM Core::CDLLADDERBOTTOM
         #define TA_CDLLADDERBOTTOM_Lookback Core::CDLLADDERBOTTOM_Lookback

         static int CDLLONGLEGGEDDOJI_Lookback( void );

         static enum class TA_RetCode CDLLONGLEGGEDDOJI( int    startIdx,
                                                         int    endIdx,
                                                         cli::array<double>^ inOpen,
                                                         cli::array<double>^ inHigh,
                                                         cli::array<double>^ inLow,
                                                         cli::array<double>^ inClose,
                                                         [Out]int%    outBegIdx,
                                                         [Out]int%    outNbElement,
                                                         cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLLONGLEGGEDDOJI( int    startIdx,
                                                         int    endIdx,
                                                         cli::array<float>^ inOpen,
                                                         cli::array<float>^ inHigh,
                                                         cli::array<float>^ inLow,
                                                         cli::array<float>^ inClose,
                                                         [Out]int%    outBegIdx,
                                                         [Out]int%    outNbElement,
                                                         cli::array<int>^  outInteger );

         #define TA_CDLLONGLEGGEDDOJI Core::CDLLONGLEGGEDDOJI
         #define TA_CDLLONGLEGGEDDOJI_Lookback Core::CDLLONGLEGGEDDOJI_Lookback

         static int CDLLONGLINE_Lookback( void );

         static enum class TA_RetCode CDLLONGLINE( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inOpen,
                                                   cli::array<double>^ inHigh,
                                                   cli::array<double>^ inLow,
                                                   cli::array<double>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLLONGLINE( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inOpen,
                                                   cli::array<float>^ inHigh,
                                                   cli::array<float>^ inLow,
                                                   cli::array<float>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );

         #define TA_CDLLONGLINE Core::CDLLONGLINE
         #define TA_CDLLONGLINE_Lookback Core::CDLLONGLINE_Lookback

         static int CDLMARUBOZU_Lookback( void );

         static enum class TA_RetCode CDLMARUBOZU( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inOpen,
                                                   cli::array<double>^ inHigh,
                                                   cli::array<double>^ inLow,
                                                   cli::array<double>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLMARUBOZU( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inOpen,
                                                   cli::array<float>^ inHigh,
                                                   cli::array<float>^ inLow,
                                                   cli::array<float>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );

         #define TA_CDLMARUBOZU Core::CDLMARUBOZU
         #define TA_CDLMARUBOZU_Lookback Core::CDLMARUBOZU_Lookback

         static int CDLMATHOLD_Lookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum class TA_RetCode CDLMATHOLD( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<double>^ inOpen,
                                                  cli::array<double>^ inHigh,
                                                  cli::array<double>^ inLow,
                                                  cli::array<double>^ inClose,
                                                  double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLMATHOLD( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<float>^ inOpen,
                                                  cli::array<float>^ inHigh,
                                                  cli::array<float>^ inLow,
                                                  cli::array<float>^ inClose,
                                                  double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<int>^  outInteger );

         #define TA_CDLMATHOLD Core::CDLMATHOLD
         #define TA_CDLMATHOLD_Lookback Core::CDLMATHOLD_Lookback

         static int CDLMATCHINGLOW_Lookback( void );

         static enum class TA_RetCode CDLMATCHINGLOW( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<double>^ inOpen,
                                                      cli::array<double>^ inHigh,
                                                      cli::array<double>^ inLow,
                                                      cli::array<double>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLMATCHINGLOW( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<float>^ inOpen,
                                                      cli::array<float>^ inHigh,
                                                      cli::array<float>^ inLow,
                                                      cli::array<float>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );

         #define TA_CDLMATCHINGLOW Core::CDLMATCHINGLOW
         #define TA_CDLMATCHINGLOW_Lookback Core::CDLMATCHINGLOW_Lookback

         static int CDLMORNINGDOJISTAR_Lookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum class TA_RetCode CDLMORNINGDOJISTAR( int    startIdx,
                                                          int    endIdx,
                                                          cli::array<double>^ inOpen,
                                                          cli::array<double>^ inHigh,
                                                          cli::array<double>^ inLow,
                                                          cli::array<double>^ inClose,
                                                          double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                          [Out]int%    outBegIdx,
                                                          [Out]int%    outNbElement,
                                                          cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLMORNINGDOJISTAR( int    startIdx,
                                                          int    endIdx,
                                                          cli::array<float>^ inOpen,
                                                          cli::array<float>^ inHigh,
                                                          cli::array<float>^ inLow,
                                                          cli::array<float>^ inClose,
                                                          double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                          [Out]int%    outBegIdx,
                                                          [Out]int%    outNbElement,
                                                          cli::array<int>^  outInteger );

         #define TA_CDLMORNINGDOJISTAR Core::CDLMORNINGDOJISTAR
         #define TA_CDLMORNINGDOJISTAR_Lookback Core::CDLMORNINGDOJISTAR_Lookback

         static int CDLMORNINGSTAR_Lookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum class TA_RetCode CDLMORNINGSTAR( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<double>^ inOpen,
                                                      cli::array<double>^ inHigh,
                                                      cli::array<double>^ inLow,
                                                      cli::array<double>^ inClose,
                                                      double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLMORNINGSTAR( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<float>^ inOpen,
                                                      cli::array<float>^ inHigh,
                                                      cli::array<float>^ inLow,
                                                      cli::array<float>^ inClose,
                                                      double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );

         #define TA_CDLMORNINGSTAR Core::CDLMORNINGSTAR
         #define TA_CDLMORNINGSTAR_Lookback Core::CDLMORNINGSTAR_Lookback

         static int CDLONNECK_Lookback( void );

         static enum class TA_RetCode CDLONNECK( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<double>^ inOpen,
                                                 cli::array<double>^ inHigh,
                                                 cli::array<double>^ inLow,
                                                 cli::array<double>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLONNECK( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<float>^ inOpen,
                                                 cli::array<float>^ inHigh,
                                                 cli::array<float>^ inLow,
                                                 cli::array<float>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );

         #define TA_CDLONNECK Core::CDLONNECK
         #define TA_CDLONNECK_Lookback Core::CDLONNECK_Lookback

         static int CDLPIERCING_Lookback( void );

         static enum class TA_RetCode CDLPIERCING( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inOpen,
                                                   cli::array<double>^ inHigh,
                                                   cli::array<double>^ inLow,
                                                   cli::array<double>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLPIERCING( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inOpen,
                                                   cli::array<float>^ inHigh,
                                                   cli::array<float>^ inLow,
                                                   cli::array<float>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );

         #define TA_CDLPIERCING Core::CDLPIERCING
         #define TA_CDLPIERCING_Lookback Core::CDLPIERCING_Lookback

         static int CDLRICKSHAWMAN_Lookback( void );

         static enum class TA_RetCode CDLRICKSHAWMAN( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<double>^ inOpen,
                                                      cli::array<double>^ inHigh,
                                                      cli::array<double>^ inLow,
                                                      cli::array<double>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLRICKSHAWMAN( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<float>^ inOpen,
                                                      cli::array<float>^ inHigh,
                                                      cli::array<float>^ inLow,
                                                      cli::array<float>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );

         #define TA_CDLRICKSHAWMAN Core::CDLRICKSHAWMAN
         #define TA_CDLRICKSHAWMAN_Lookback Core::CDLRICKSHAWMAN_Lookback

         static int CDLRISEFALL3METHODS_Lookback( void );

         static enum class TA_RetCode CDLRISEFALL3METHODS( int    startIdx,
                                                           int    endIdx,
                                                           cli::array<double>^ inOpen,
                                                           cli::array<double>^ inHigh,
                                                           cli::array<double>^ inLow,
                                                           cli::array<double>^ inClose,
                                                           [Out]int%    outBegIdx,
                                                           [Out]int%    outNbElement,
                                                           cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLRISEFALL3METHODS( int    startIdx,
                                                           int    endIdx,
                                                           cli::array<float>^ inOpen,
                                                           cli::array<float>^ inHigh,
                                                           cli::array<float>^ inLow,
                                                           cli::array<float>^ inClose,
                                                           [Out]int%    outBegIdx,
                                                           [Out]int%    outNbElement,
                                                           cli::array<int>^  outInteger );

         #define TA_CDLRISEFALL3METHODS Core::CDLRISEFALL3METHODS
         #define TA_CDLRISEFALL3METHODS_Lookback Core::CDLRISEFALL3METHODS_Lookback

         static int CDLSEPARATINGLINES_Lookback( void );

         static enum class TA_RetCode CDLSEPARATINGLINES( int    startIdx,
                                                          int    endIdx,
                                                          cli::array<double>^ inOpen,
                                                          cli::array<double>^ inHigh,
                                                          cli::array<double>^ inLow,
                                                          cli::array<double>^ inClose,
                                                          [Out]int%    outBegIdx,
                                                          [Out]int%    outNbElement,
                                                          cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLSEPARATINGLINES( int    startIdx,
                                                          int    endIdx,
                                                          cli::array<float>^ inOpen,
                                                          cli::array<float>^ inHigh,
                                                          cli::array<float>^ inLow,
                                                          cli::array<float>^ inClose,
                                                          [Out]int%    outBegIdx,
                                                          [Out]int%    outNbElement,
                                                          cli::array<int>^  outInteger );

         #define TA_CDLSEPARATINGLINES Core::CDLSEPARATINGLINES
         #define TA_CDLSEPARATINGLINES_Lookback Core::CDLSEPARATINGLINES_Lookback

         static int CDLSHOOTINGSTAR_Lookback( void );

         static enum class TA_RetCode CDLSHOOTINGSTAR( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<double>^ inOpen,
                                                       cli::array<double>^ inHigh,
                                                       cli::array<double>^ inLow,
                                                       cli::array<double>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLSHOOTINGSTAR( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<float>^ inOpen,
                                                       cli::array<float>^ inHigh,
                                                       cli::array<float>^ inLow,
                                                       cli::array<float>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );

         #define TA_CDLSHOOTINGSTAR Core::CDLSHOOTINGSTAR
         #define TA_CDLSHOOTINGSTAR_Lookback Core::CDLSHOOTINGSTAR_Lookback

         static int CDLSHORTLINE_Lookback( void );

         static enum class TA_RetCode CDLSHORTLINE( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<double>^ inOpen,
                                                    cli::array<double>^ inHigh,
                                                    cli::array<double>^ inLow,
                                                    cli::array<double>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLSHORTLINE( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<float>^ inOpen,
                                                    cli::array<float>^ inHigh,
                                                    cli::array<float>^ inLow,
                                                    cli::array<float>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );

         #define TA_CDLSHORTLINE Core::CDLSHORTLINE
         #define TA_CDLSHORTLINE_Lookback Core::CDLSHORTLINE_Lookback

         static int CDLSPINNINGTOP_Lookback( void );

         static enum class TA_RetCode CDLSPINNINGTOP( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<double>^ inOpen,
                                                      cli::array<double>^ inHigh,
                                                      cli::array<double>^ inLow,
                                                      cli::array<double>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLSPINNINGTOP( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<float>^ inOpen,
                                                      cli::array<float>^ inHigh,
                                                      cli::array<float>^ inLow,
                                                      cli::array<float>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );

         #define TA_CDLSPINNINGTOP Core::CDLSPINNINGTOP
         #define TA_CDLSPINNINGTOP_Lookback Core::CDLSPINNINGTOP_Lookback

         static int CDLSTALLEDPATTERN_Lookback( void );

         static enum class TA_RetCode CDLSTALLEDPATTERN( int    startIdx,
                                                         int    endIdx,
                                                         cli::array<double>^ inOpen,
                                                         cli::array<double>^ inHigh,
                                                         cli::array<double>^ inLow,
                                                         cli::array<double>^ inClose,
                                                         [Out]int%    outBegIdx,
                                                         [Out]int%    outNbElement,
                                                         cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLSTALLEDPATTERN( int    startIdx,
                                                         int    endIdx,
                                                         cli::array<float>^ inOpen,
                                                         cli::array<float>^ inHigh,
                                                         cli::array<float>^ inLow,
                                                         cli::array<float>^ inClose,
                                                         [Out]int%    outBegIdx,
                                                         [Out]int%    outNbElement,
                                                         cli::array<int>^  outInteger );

         #define TA_CDLSTALLEDPATTERN Core::CDLSTALLEDPATTERN
         #define TA_CDLSTALLEDPATTERN_Lookback Core::CDLSTALLEDPATTERN_Lookback

         static int CDLSTICKSANDWICH_Lookback( void );

         static enum class TA_RetCode CDLSTICKSANDWICH( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<double>^ inOpen,
                                                        cli::array<double>^ inHigh,
                                                        cli::array<double>^ inLow,
                                                        cli::array<double>^ inClose,
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLSTICKSANDWICH( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<float>^ inOpen,
                                                        cli::array<float>^ inHigh,
                                                        cli::array<float>^ inLow,
                                                        cli::array<float>^ inClose,
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );

         #define TA_CDLSTICKSANDWICH Core::CDLSTICKSANDWICH
         #define TA_CDLSTICKSANDWICH_Lookback Core::CDLSTICKSANDWICH_Lookback

         static int CDLTAKURI_Lookback( void );

         static enum class TA_RetCode CDLTAKURI( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<double>^ inOpen,
                                                 cli::array<double>^ inHigh,
                                                 cli::array<double>^ inLow,
                                                 cli::array<double>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLTAKURI( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<float>^ inOpen,
                                                 cli::array<float>^ inHigh,
                                                 cli::array<float>^ inLow,
                                                 cli::array<float>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );

         #define TA_CDLTAKURI Core::CDLTAKURI
         #define TA_CDLTAKURI_Lookback Core::CDLTAKURI_Lookback

         static int CDLTASUKIGAP_Lookback( void );

         static enum class TA_RetCode CDLTASUKIGAP( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<double>^ inOpen,
                                                    cli::array<double>^ inHigh,
                                                    cli::array<double>^ inLow,
                                                    cli::array<double>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLTASUKIGAP( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<float>^ inOpen,
                                                    cli::array<float>^ inHigh,
                                                    cli::array<float>^ inLow,
                                                    cli::array<float>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );

         #define TA_CDLTASUKIGAP Core::CDLTASUKIGAP
         #define TA_CDLTASUKIGAP_Lookback Core::CDLTASUKIGAP_Lookback

         static int CDLTHRUSTING_Lookback( void );

         static enum class TA_RetCode CDLTHRUSTING( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<double>^ inOpen,
                                                    cli::array<double>^ inHigh,
                                                    cli::array<double>^ inLow,
                                                    cli::array<double>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLTHRUSTING( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<float>^ inOpen,
                                                    cli::array<float>^ inHigh,
                                                    cli::array<float>^ inLow,
                                                    cli::array<float>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );

         #define TA_CDLTHRUSTING Core::CDLTHRUSTING
         #define TA_CDLTHRUSTING_Lookback Core::CDLTHRUSTING_Lookback

         static int CDLTRISTAR_Lookback( void );

         static enum class TA_RetCode CDLTRISTAR( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<double>^ inOpen,
                                                  cli::array<double>^ inHigh,
                                                  cli::array<double>^ inLow,
                                                  cli::array<double>^ inClose,
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLTRISTAR( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<float>^ inOpen,
                                                  cli::array<float>^ inHigh,
                                                  cli::array<float>^ inLow,
                                                  cli::array<float>^ inClose,
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<int>^  outInteger );

         #define TA_CDLTRISTAR Core::CDLTRISTAR
         #define TA_CDLTRISTAR_Lookback Core::CDLTRISTAR_Lookback

         static int CDLUNIQUE3RIVER_Lookback( void );

         static enum class TA_RetCode CDLUNIQUE3RIVER( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<double>^ inOpen,
                                                       cli::array<double>^ inHigh,
                                                       cli::array<double>^ inLow,
                                                       cli::array<double>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLUNIQUE3RIVER( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<float>^ inOpen,
                                                       cli::array<float>^ inHigh,
                                                       cli::array<float>^ inLow,
                                                       cli::array<float>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );

         #define TA_CDLUNIQUE3RIVER Core::CDLUNIQUE3RIVER
         #define TA_CDLUNIQUE3RIVER_Lookback Core::CDLUNIQUE3RIVER_Lookback

         static int CDLUPSIDEGAP2CROWS_Lookback( void );

         static enum class TA_RetCode CDLUPSIDEGAP2CROWS( int    startIdx,
                                                          int    endIdx,
                                                          cli::array<double>^ inOpen,
                                                          cli::array<double>^ inHigh,
                                                          cli::array<double>^ inLow,
                                                          cli::array<double>^ inClose,
                                                          [Out]int%    outBegIdx,
                                                          [Out]int%    outNbElement,
                                                          cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLUPSIDEGAP2CROWS( int    startIdx,
                                                          int    endIdx,
                                                          cli::array<float>^ inOpen,
                                                          cli::array<float>^ inHigh,
                                                          cli::array<float>^ inLow,
                                                          cli::array<float>^ inClose,
                                                          [Out]int%    outBegIdx,
                                                          [Out]int%    outNbElement,
                                                          cli::array<int>^  outInteger );

         #define TA_CDLUPSIDEGAP2CROWS Core::CDLUPSIDEGAP2CROWS
         #define TA_CDLUPSIDEGAP2CROWS_Lookback Core::CDLUPSIDEGAP2CROWS_Lookback

         static int CDLXSIDEGAP3METHODS_Lookback( void );

         static enum class TA_RetCode CDLXSIDEGAP3METHODS( int    startIdx,
                                                           int    endIdx,
                                                           cli::array<double>^ inOpen,
                                                           cli::array<double>^ inHigh,
                                                           cli::array<double>^ inLow,
                                                           cli::array<double>^ inClose,
                                                           [Out]int%    outBegIdx,
                                                           [Out]int%    outNbElement,
                                                           cli::array<int>^  outInteger );
         static enum class TA_RetCode CDLXSIDEGAP3METHODS( int    startIdx,
                                                           int    endIdx,
                                                           cli::array<float>^ inOpen,
                                                           cli::array<float>^ inHigh,
                                                           cli::array<float>^ inLow,
                                                           cli::array<float>^ inClose,
                                                           [Out]int%    outBegIdx,
                                                           [Out]int%    outNbElement,
                                                           cli::array<int>^  outInteger );

         #define TA_CDLXSIDEGAP3METHODS Core::CDLXSIDEGAP3METHODS
         #define TA_CDLXSIDEGAP3METHODS_Lookback Core::CDLXSIDEGAP3METHODS_Lookback

         static int CORREL_Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class TA_RetCode CORREL( int    startIdx,
                                              int    endIdx,
                                              cli::array<double>^ inReal0,
                                              cli::array<double>^ inReal1,
                                              int           optInTimePeriod, /* From 1 to 100000 */
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outReal );
         static enum class TA_RetCode CORREL( int    startIdx,
                                              int    endIdx,
                                              cli::array<float>^ inReal0,
                                              cli::array<float>^ inReal1,
                                              int           optInTimePeriod, /* From 1 to 100000 */
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outReal );

         #define TA_CORREL Core::CORREL
         #define TA_CORREL_Lookback Core::CORREL_Lookback

         static int LINEARREG_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode LINEARREG( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<double>^ inReal,
                                                 int           optInTimePeriod, /* From 2 to 100000 */
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<double>^  outReal );
         static enum class TA_RetCode LINEARREG( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<float>^ inReal,
                                                 int           optInTimePeriod, /* From 2 to 100000 */
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<double>^  outReal );

         #define TA_LINEARREG Core::LINEARREG
         #define TA_LINEARREG_Lookback Core::LINEARREG_Lookback

         static int LINEARREG_SLOPE_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode LINEARREG_SLOPE( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<double>^ inReal,
                                                       int           optInTimePeriod, /* From 2 to 100000 */
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<double>^  outReal );
         static enum class TA_RetCode LINEARREG_SLOPE( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<float>^ inReal,
                                                       int           optInTimePeriod, /* From 2 to 100000 */
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<double>^  outReal );

         #define TA_LINEARREG_SLOPE Core::LINEARREG_SLOPE
         #define TA_LINEARREG_SLOPE_Lookback Core::LINEARREG_SLOPE_Lookback

         static int LINEARREG_ANGLE_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode LINEARREG_ANGLE( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<double>^ inReal,
                                                       int           optInTimePeriod, /* From 2 to 100000 */
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<double>^  outReal );
         static enum class TA_RetCode LINEARREG_ANGLE( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<float>^ inReal,
                                                       int           optInTimePeriod, /* From 2 to 100000 */
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<double>^  outReal );

         #define TA_LINEARREG_ANGLE Core::LINEARREG_ANGLE
         #define TA_LINEARREG_ANGLE_Lookback Core::LINEARREG_ANGLE_Lookback

         static int LINEARREG_INTERCEPT_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode LINEARREG_INTERCEPT( int    startIdx,
                                                           int    endIdx,
                                                           cli::array<double>^ inReal,
                                                           int           optInTimePeriod, /* From 2 to 100000 */
                                                           [Out]int%    outBegIdx,
                                                           [Out]int%    outNbElement,
                                                           cli::array<double>^  outReal );
         static enum class TA_RetCode LINEARREG_INTERCEPT( int    startIdx,
                                                           int    endIdx,
                                                           cli::array<float>^ inReal,
                                                           int           optInTimePeriod, /* From 2 to 100000 */
                                                           [Out]int%    outBegIdx,
                                                           [Out]int%    outNbElement,
                                                           cli::array<double>^  outReal );

         #define TA_LINEARREG_INTERCEPT Core::LINEARREG_INTERCEPT
         #define TA_LINEARREG_INTERCEPT_Lookback Core::LINEARREG_INTERCEPT_Lookback

         static int STDDEV_Lookback( int           optInTimePeriod, /* From 2 to 100000 */
                                   double        optInNbDev );  /* From TA_REAL_MIN to TA_REAL_MAX */

         static enum class TA_RetCode STDDEV( int    startIdx,
                                              int    endIdx,
                                              cli::array<double>^ inReal,
                                              int           optInTimePeriod, /* From 2 to 100000 */
                                              double        optInNbDev, /* From TA_REAL_MIN to TA_REAL_MAX */
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outReal );
         static enum class TA_RetCode STDDEV( int    startIdx,
                                              int    endIdx,
                                              cli::array<float>^ inReal,
                                              int           optInTimePeriod, /* From 2 to 100000 */
                                              double        optInNbDev, /* From TA_REAL_MIN to TA_REAL_MAX */
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outReal );

         #define TA_STDDEV Core::STDDEV
         #define TA_STDDEV_Lookback Core::STDDEV_Lookback

         static int TSF_Lookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class TA_RetCode TSF( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode TSF( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_TSF Core::TSF
         #define TA_TSF_Lookback Core::TSF_Lookback

         static int VAR_Lookback( int           optInTimePeriod, /* From 1 to 100000 */
                                double        optInNbDev );  /* From TA_REAL_MIN to TA_REAL_MAX */

         static enum class TA_RetCode VAR( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           int           optInTimePeriod, /* From 1 to 100000 */
                                           double        optInNbDev, /* From TA_REAL_MIN to TA_REAL_MAX */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class TA_RetCode VAR( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           int           optInTimePeriod, /* From 1 to 100000 */
                                           double        optInNbDev, /* From TA_REAL_MIN to TA_REAL_MAX */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_VAR Core::VAR
         #define TA_VAR_Lookback Core::VAR_Lookback

         static int AVGPRICE_Lookback( void );

         static enum class TA_RetCode AVGPRICE( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inOpen,
                                                cli::array<double>^ inHigh,
                                                cli::array<double>^ inLow,
                                                cli::array<double>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );
         static enum class TA_RetCode AVGPRICE( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inOpen,
                                                cli::array<float>^ inHigh,
                                                cli::array<float>^ inLow,
                                                cli::array<float>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );

         #define TA_AVGPRICE Core::AVGPRICE
         #define TA_AVGPRICE_Lookback Core::AVGPRICE_Lookback

         static int MEDPRICE_Lookback( void );

         static enum class TA_RetCode MEDPRICE( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inHigh,
                                                cli::array<double>^ inLow,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );
         static enum class TA_RetCode MEDPRICE( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inHigh,
                                                cli::array<float>^ inLow,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );

         #define TA_MEDPRICE Core::MEDPRICE
         #define TA_MEDPRICE_Lookback Core::MEDPRICE_Lookback

         static int TYPPRICE_Lookback( void );

         static enum class TA_RetCode TYPPRICE( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inHigh,
                                                cli::array<double>^ inLow,
                                                cli::array<double>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );
         static enum class TA_RetCode TYPPRICE( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inHigh,
                                                cli::array<float>^ inLow,
                                                cli::array<float>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );

         #define TA_TYPPRICE Core::TYPPRICE
         #define TA_TYPPRICE_Lookback Core::TYPPRICE_Lookback

         static int WCLPRICE_Lookback( void );

         static enum class TA_RetCode WCLPRICE( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inHigh,
                                                cli::array<double>^ inLow,
                                                cli::array<double>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );
         static enum class TA_RetCode WCLPRICE( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inHigh,
                                                cli::array<float>^ inLow,
                                                cli::array<float>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );

         #define TA_WCLPRICE Core::WCLPRICE
         #define TA_WCLPRICE_Lookback Core::WCLPRICE_Lookback

/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/

  		   };
	   }
	}
}
