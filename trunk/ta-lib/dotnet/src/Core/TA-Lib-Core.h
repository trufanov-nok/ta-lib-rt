/* TA-LIB Copyright (c) 1999-2007, Mario Fortier
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
			  ref class CandleSetting sealed 
			  {
			  public:
				  enum class CandleSettingType settingType;
				  enum class RangeType rangeType;
				  int     avgPeriod;
				  double  factor;
			 };

			 ref class GlobalsType sealed
			 {
			 public:
				GlobalsType()
				{
					unstablePeriod = gcnew cli::array<unsigned int>((int)FuncUnstId::FuncUnstAll);
					compatibility = Compatibility::Default;
					for( int i=0; i < (int)FuncUnstId::FuncUnstAll; i++ )
						unstablePeriod[i] = 0;
					candleSettings = gcnew cli::array<CandleSetting^>((int)CandleSettingType::AllCandleSettings);
					for( int j=0; j < candleSettings->Length; j++ )
					{
						candleSettings[j] = gcnew CandleSetting();					
					}
				}

				/* For handling the compatibility with other software */
				Compatibility compatibility;

				/* For handling the unstable period of some TA function. */
				cli::array<unsigned int>^ unstablePeriod;

				/* For handling the candlestick global settings */
				cli::array<CandleSetting^>^ candleSettings;
			 };

			 static GlobalsType^ Globals;

			 static  enum class RetCode TA_INT_EMA( int           startIdx,
									int           endIdx,
									cli::array<double>^ inReal_0,
									int           optInTimePeriod_0, /* From 1 to 200 */
									double        optInK_1,
									[Out]int% outBegIdx,
									[Out]int% outNbElement,
									cli::array<double>^ outReal_0);

			 static  enum class RetCode TA_INT_EMA( int           startIdx,
									int           endIdx,
									cli::array<float>^ inReal_0,
									int           optInTimePeriod_0, /* From 1 to 200 */
									double        optInK_1,
									[Out]int% outBegIdx,
									[Out]int% outNbElement,
									cli::array<double>^ outReal_0);

			 static  enum class RetCode TA_INT_SMA( int     startIdx,
									int     endIdx,
									cli::array<double>^ inReal_0,
									int     optInTimePeriod_0, /* From 1 to 200 */
									[Out]int% outBegIdx,
									[Out]int% outNbElement,
									cli::array<double>^ outReal_0);

			 static  enum class RetCode TA_INT_SMA( int     startIdx,
									int     endIdx,
									cli::array<float>^ inReal_0,
									int     optInTimePeriod_0, /* From 1 to 200 */
									[Out]int% outBegIdx,
									[Out]int% outNbElement,
									cli::array<double>^ outReal_0 );

			 static  enum class RetCode TA_INT_MACD( int    startIdx,
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

			 static  enum class RetCode TA_INT_MACD( int    startIdx,
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

			 static  enum class RetCode TA_INT_PO( int    startIdx,
								   int    endIdx,
								   cli::array<double>^ inReal_0,
								   int    optInFastPeriod_0, /* From 1 to 200 */
								   int    optInSlowPeriod_1, /* From 1 to 200 */
								   MAType optInMethod_2,
								   [Out]int% outBegIdx,
								   [Out]int% outNbElement,
								   cli::array<double>^ outReal_0,
								   cli::array<double>^ tempBuffer,
								   int  doPercentageOutput );

			 static  enum class RetCode TA_INT_PO( int    startIdx,
								   int    endIdx,
								   cli::array<float>^ inReal_0,
								   int    optInFastPeriod_0, /* From 1 to 200 */
								   int    optInSlowPeriod_1, /* From 1 to 200 */
								   MAType optInMethod_2,
								   [Out]int% outBegIdx,
								   [Out]int% outNbElement,
								   cli::array<double>^ outReal_0,
								   cli::array<double>^ tempBuffer,
								   int  doPercentageOutput );

			 static  enum class RetCode TA_INT_VAR( int    startIdx,
									int    endIdx,
									cli::array<double>^ inReal_0,
									int    optInTimePeriod_0,                       
									[Out]int% outBegIdx,
									[Out]int% outNbElement,
									cli::array<double>^ outReal_0);

			 static  enum class RetCode TA_INT_VAR( int    startIdx,
									int    endIdx,
									cli::array<float>^ inReal_0,
									int    optInTimePeriod_0,                       
									[Out]int% outBegIdx,
									[Out]int% outNbElement,
									cli::array<double>^ outReal_0);

			 static void TA_INT_stddev_using_precalc_ma( cli::array<double>^  inReal,
												  cli::array<double>^ inMovAvg,
												  int inMovAvgBegIdx,
												  int inMovAvgNbElement,
												  int timePeriod,
												  cli::array<double>^ output );

			 static void TA_INT_stddev_using_precalc_ma( cli::array<float>^ inReal,
												  cli::array<double>^ inMovAvg,
												  int inMovAvgBegIdx,
												  int inMovAvgNbElement,
												  int timePeriod,
												  cli::array<double>^ output);

		  public:
			 static Core()
			 {
				// Initialize global settings
				Globals = gcnew GlobalsType;
				/* Set the default value to global variables */
				RestoreCandleDefaultSettings( CandleSettingType::AllCandleSettings );
			 }

			 static  enum class RetCode SetUnstablePeriod(  enum class FuncUnstId id,
															   unsigned int  unstablePeriod );

			 static unsigned int GetUnstablePeriod( FuncUnstId id );

			 static  enum class RetCode SetCompatibility( enum class Compatibility value );
			 static  enum class Compatibility GetCompatibility( void );

			 static  enum class RetCode SetCandleSettings(  enum class CandleSettingType settingType, 
															enum class RangeType rangeType,
															int avgPeriod, 
															double factor )
			 {    
				 if( settingType >= CandleSettingType::AllCandleSettings )
				 {
					 return RetCode::BadParam;
				 }
				 Globals->candleSettings[(int)settingType]->settingType = settingType;
				 Globals->candleSettings[(int)settingType]->rangeType = rangeType;
				 Globals->candleSettings[(int)settingType]->avgPeriod = avgPeriod;
				 Globals->candleSettings[(int)settingType]->factor = factor;
				 return RetCode::Success;
			 }

			 
			 static enum class RetCode RestoreCandleDefaultSettings( CandleSettingType settingType )
			 {			
				switch( settingType )
				{
				case CandleSettingType::BodyLong:
				   SetCandleSettings( CandleSettingType::BodyLong, RangeType::RealBody, 10, 1.0 );
				   break;
				case CandleSettingType::BodyVeryLong:
				   SetCandleSettings( CandleSettingType::BodyVeryLong, RangeType::RealBody, 10, 3.0 );
				   break;
				case CandleSettingType::BodyShort:
				   SetCandleSettings( CandleSettingType::BodyShort, RangeType::RealBody, 10, 1.0 );
				   break;
				case CandleSettingType::BodyDoji:
				   SetCandleSettings( CandleSettingType::BodyDoji, RangeType::HighLow, 10, 0.1 );
				   break;
				case CandleSettingType::ShadowLong:
				   SetCandleSettings( CandleSettingType::ShadowLong, RangeType::RealBody, 0, 1.0 );
				   break;
				case CandleSettingType::ShadowVeryLong:
				   SetCandleSettings( CandleSettingType::ShadowVeryLong, RangeType::RealBody, 0, 2.0 );
				   break;
				case CandleSettingType::ShadowShort:
				   SetCandleSettings( CandleSettingType::ShadowShort, RangeType::Shadows, 10, 1.0 );
				   break;
				case CandleSettingType::ShadowVeryShort:
				   SetCandleSettings( CandleSettingType::ShadowVeryShort, RangeType::HighLow, 10, 0.1 );
				   break;
				case CandleSettingType::Near:
				   SetCandleSettings( CandleSettingType::Near, RangeType::HighLow, 5, 0.2 );
				   break;
				case CandleSettingType::Far:
				   SetCandleSettings( CandleSettingType::Far, RangeType::HighLow, 5, 0.6 );
				   break;
				case CandleSettingType::Equal:
				   SetCandleSettings( CandleSettingType::Equal, RangeType::HighLow, 5, 0.05);
				   break;
				case CandleSettingType::AllCandleSettings:
				   SetCandleSettings( CandleSettingType::BodyLong, RangeType::RealBody, 10, 1.0 );
				   SetCandleSettings( CandleSettingType::BodyVeryLong, RangeType::RealBody, 10, 3.0 );
				   SetCandleSettings( CandleSettingType::BodyShort, RangeType::RealBody, 10, 1.0 );
				   SetCandleSettings( CandleSettingType::BodyDoji, RangeType::HighLow, 10, 0.1 );
				   SetCandleSettings( CandleSettingType::ShadowLong, RangeType::RealBody, 0, 1.0 );
				   SetCandleSettings( CandleSettingType::ShadowVeryLong, RangeType::RealBody, 0, 2.0 );
				   SetCandleSettings( CandleSettingType::ShadowShort, RangeType::Shadows, 10, 1.0 );
				   SetCandleSettings( CandleSettingType::ShadowVeryShort, RangeType::HighLow, 10, 0.1 );
				   SetCandleSettings( CandleSettingType::Near, RangeType::HighLow, 5, 0.2 );
				   SetCandleSettings( CandleSettingType::Far, RangeType::HighLow, 5, 0.6 );
				   SetCandleSettings( CandleSettingType::Equal, RangeType::HighLow, 5, 0.05);
				   break;
				}

				return RetCode::Success;
			 }

/**** START GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
         static int AdLookback( void );

         static enum class RetCode Ad( int    startIdx,
                                       int    endIdx,
                                       cli::array<double>^ inHigh,
                                       cli::array<double>^ inLow,
                                       cli::array<double>^ inClose,
                                       cli::array<double>^ inVolume,
                                       [Out]int%    outBegIdx,
                                       [Out]int%    outNbElement,
                                       cli::array<double>^  outReal );
         static enum class RetCode Ad( int    startIdx,
                                       int    endIdx,
                                       cli::array<float>^ inHigh,
                                       cli::array<float>^ inLow,
                                       cli::array<float>^ inClose,
                                       cli::array<float>^ inVolume,
                                       [Out]int%    outBegIdx,
                                       [Out]int%    outNbElement,
                                       cli::array<double>^  outReal );

         #define TA_AD Core::Ad
         #define TA_AD_Lookback Core::AdLookback

         static int AdOscLookback( int           optInFastPeriod, /* From 2 to 100000 */
                                 int           optInSlowPeriod );  /* From 2 to 100000 */

         static enum class RetCode AdOsc( int    startIdx,
                                          int    endIdx,
                                          cli::array<double>^ inHigh,
                                          cli::array<double>^ inLow,
                                          cli::array<double>^ inClose,
                                          cli::array<double>^ inVolume,
                                          int           optInFastPeriod, /* From 2 to 100000 */
                                          int           optInSlowPeriod, /* From 2 to 100000 */
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outReal );
         static enum class RetCode AdOsc( int    startIdx,
                                          int    endIdx,
                                          cli::array<float>^ inHigh,
                                          cli::array<float>^ inLow,
                                          cli::array<float>^ inClose,
                                          cli::array<float>^ inVolume,
                                          int           optInFastPeriod, /* From 2 to 100000 */
                                          int           optInSlowPeriod, /* From 2 to 100000 */
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outReal );

         #define TA_ADOSC Core::AdOsc
         #define TA_ADOSC_Lookback Core::AdOscLookback

         static int AdxLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Adx( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inHigh,
                                        cli::array<double>^ inLow,
                                        cli::array<double>^ inClose,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Adx( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inHigh,
                                        cli::array<float>^ inLow,
                                        cli::array<float>^ inClose,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_ADX Core::Adx
         #define TA_ADX_Lookback Core::AdxLookback

         static int AdxrLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Adxr( int    startIdx,
                                         int    endIdx,
                                         cli::array<double>^ inHigh,
                                         cli::array<double>^ inLow,
                                         cli::array<double>^ inClose,
                                         int           optInTimePeriod, /* From 2 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );
         static enum class RetCode Adxr( int    startIdx,
                                         int    endIdx,
                                         cli::array<float>^ inHigh,
                                         cli::array<float>^ inLow,
                                         cli::array<float>^ inClose,
                                         int           optInTimePeriod, /* From 2 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );

         #define TA_ADXR Core::Adxr
         #define TA_ADXR_Lookback Core::AdxrLookback

         static int ApoLookback( int           optInFastPeriod, /* From 2 to 100000 */
                               int           optInSlowPeriod, /* From 2 to 100000 */
                               MAType        optInMAType ); 
         static enum class RetCode Apo( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inReal,
                                        int           optInFastPeriod, /* From 2 to 100000 */
                                        int           optInSlowPeriod, /* From 2 to 100000 */
                                        MAType        optInMAType,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Apo( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inReal,
                                        int           optInFastPeriod, /* From 2 to 100000 */
                                        int           optInSlowPeriod, /* From 2 to 100000 */
                                        MAType        optInMAType,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_APO Core::Apo
         #define TA_APO_Lookback Core::ApoLookback

         static int AroonLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Aroon( int    startIdx,
                                          int    endIdx,
                                          cli::array<double>^ inHigh,
                                          cli::array<double>^ inLow,
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outAroonDown,
                                          cli::array<double>^  outAroonUp );
         static enum class RetCode Aroon( int    startIdx,
                                          int    endIdx,
                                          cli::array<float>^ inHigh,
                                          cli::array<float>^ inLow,
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outAroonDown,
                                          cli::array<double>^  outAroonUp );

         #define TA_AROON Core::Aroon
         #define TA_AROON_Lookback Core::AroonLookback

         static int AroonOscLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode AroonOsc( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inHigh,
                                             cli::array<double>^ inLow,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );
         static enum class RetCode AroonOsc( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inHigh,
                                             cli::array<float>^ inLow,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );

         #define TA_AROONOSC Core::AroonOsc
         #define TA_AROONOSC_Lookback Core::AroonOscLookback

         static int AtrLookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class RetCode Atr( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inHigh,
                                        cli::array<double>^ inLow,
                                        cli::array<double>^ inClose,
                                        int           optInTimePeriod, /* From 1 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Atr( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inHigh,
                                        cli::array<float>^ inLow,
                                        cli::array<float>^ inClose,
                                        int           optInTimePeriod, /* From 1 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_ATR Core::Atr
         #define TA_ATR_Lookback Core::AtrLookback

         static int AvgPriceLookback( void );

         static enum class RetCode AvgPrice( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inOpen,
                                             cli::array<double>^ inHigh,
                                             cli::array<double>^ inLow,
                                             cli::array<double>^ inClose,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );
         static enum class RetCode AvgPrice( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inOpen,
                                             cli::array<float>^ inHigh,
                                             cli::array<float>^ inLow,
                                             cli::array<float>^ inClose,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );

         #define TA_AVGPRICE Core::AvgPrice
         #define TA_AVGPRICE_Lookback Core::AvgPriceLookback

         static int BbandsLookback( int           optInTimePeriod, /* From 2 to 100000 */
                                  double        optInNbDevUp, /* From TA_REAL_MIN to TA_REAL_MAX */
                                  double        optInNbDevDn, /* From TA_REAL_MIN to TA_REAL_MAX */
                                  MAType        optInMAType ); 
         static enum class RetCode Bbands( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           double        optInNbDevUp, /* From TA_REAL_MIN to TA_REAL_MAX */
                                           double        optInNbDevDn, /* From TA_REAL_MIN to TA_REAL_MAX */
                                           MAType        optInMAType,
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outRealUpperBand,
                                           cli::array<double>^  outRealMiddleBand,
                                           cli::array<double>^  outRealLowerBand );
         static enum class RetCode Bbands( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           double        optInNbDevUp, /* From TA_REAL_MIN to TA_REAL_MAX */
                                           double        optInNbDevDn, /* From TA_REAL_MIN to TA_REAL_MAX */
                                           MAType        optInMAType,
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outRealUpperBand,
                                           cli::array<double>^  outRealMiddleBand,
                                           cli::array<double>^  outRealLowerBand );

         #define TA_BBANDS Core::Bbands
         #define TA_BBANDS_Lookback Core::BbandsLookback

         static int BetaLookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class RetCode Beta( int    startIdx,
                                         int    endIdx,
                                         cli::array<double>^ inReal0,
                                         cli::array<double>^ inReal1,
                                         int           optInTimePeriod, /* From 1 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );
         static enum class RetCode Beta( int    startIdx,
                                         int    endIdx,
                                         cli::array<float>^ inReal0,
                                         cli::array<float>^ inReal1,
                                         int           optInTimePeriod, /* From 1 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );

         #define TA_BETA Core::Beta
         #define TA_BETA_Lookback Core::BetaLookback

         static int BopLookback( void );

         static enum class RetCode Bop( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inOpen,
                                        cli::array<double>^ inHigh,
                                        cli::array<double>^ inLow,
                                        cli::array<double>^ inClose,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Bop( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inOpen,
                                        cli::array<float>^ inHigh,
                                        cli::array<float>^ inLow,
                                        cli::array<float>^ inClose,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_BOP Core::Bop
         #define TA_BOP_Lookback Core::BopLookback

         static int CciLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Cci( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inHigh,
                                        cli::array<double>^ inLow,
                                        cli::array<double>^ inClose,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Cci( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inHigh,
                                        cli::array<float>^ inLow,
                                        cli::array<float>^ inClose,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_CCI Core::Cci
         #define TA_CCI_Lookback Core::CciLookback

         static int Cdl2CrowsLookback( void );

         static enum class RetCode Cdl2Crows( int    startIdx,
                                              int    endIdx,
                                              cli::array<double>^ inOpen,
                                              cli::array<double>^ inHigh,
                                              cli::array<double>^ inLow,
                                              cli::array<double>^ inClose,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<int>^  outInteger );
         static enum class RetCode Cdl2Crows( int    startIdx,
                                              int    endIdx,
                                              cli::array<float>^ inOpen,
                                              cli::array<float>^ inHigh,
                                              cli::array<float>^ inLow,
                                              cli::array<float>^ inClose,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<int>^  outInteger );

         #define TA_CDL2CROWS Core::Cdl2Crows
         #define TA_CDL2CROWS_Lookback Core::Cdl2CrowsLookback

         static int Cdl3BlackCrowsLookback( void );

         static enum class RetCode Cdl3BlackCrows( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inOpen,
                                                   cli::array<double>^ inHigh,
                                                   cli::array<double>^ inLow,
                                                   cli::array<double>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );
         static enum class RetCode Cdl3BlackCrows( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inOpen,
                                                   cli::array<float>^ inHigh,
                                                   cli::array<float>^ inLow,
                                                   cli::array<float>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );

         #define TA_CDL3BLACKCROWS Core::Cdl3BlackCrows
         #define TA_CDL3BLACKCROWS_Lookback Core::Cdl3BlackCrowsLookback

         static int Cdl3InsideLookback( void );

         static enum class RetCode Cdl3Inside( int    startIdx,
                                               int    endIdx,
                                               cli::array<double>^ inOpen,
                                               cli::array<double>^ inHigh,
                                               cli::array<double>^ inLow,
                                               cli::array<double>^ inClose,
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<int>^  outInteger );
         static enum class RetCode Cdl3Inside( int    startIdx,
                                               int    endIdx,
                                               cli::array<float>^ inOpen,
                                               cli::array<float>^ inHigh,
                                               cli::array<float>^ inLow,
                                               cli::array<float>^ inClose,
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<int>^  outInteger );

         #define TA_CDL3INSIDE Core::Cdl3Inside
         #define TA_CDL3INSIDE_Lookback Core::Cdl3InsideLookback

         static int Cdl3LineStrikeLookback( void );

         static enum class RetCode Cdl3LineStrike( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inOpen,
                                                   cli::array<double>^ inHigh,
                                                   cli::array<double>^ inLow,
                                                   cli::array<double>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );
         static enum class RetCode Cdl3LineStrike( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inOpen,
                                                   cli::array<float>^ inHigh,
                                                   cli::array<float>^ inLow,
                                                   cli::array<float>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );

         #define TA_CDL3LINESTRIKE Core::Cdl3LineStrike
         #define TA_CDL3LINESTRIKE_Lookback Core::Cdl3LineStrikeLookback

         static int Cdl3OutsideLookback( void );

         static enum class RetCode Cdl3Outside( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inOpen,
                                                cli::array<double>^ inHigh,
                                                cli::array<double>^ inLow,
                                                cli::array<double>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outInteger );
         static enum class RetCode Cdl3Outside( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inOpen,
                                                cli::array<float>^ inHigh,
                                                cli::array<float>^ inLow,
                                                cli::array<float>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outInteger );

         #define TA_CDL3OUTSIDE Core::Cdl3Outside
         #define TA_CDL3OUTSIDE_Lookback Core::Cdl3OutsideLookback

         static int Cdl3StarsInSouthLookback( void );

         static enum class RetCode Cdl3StarsInSouth( int    startIdx,
                                                     int    endIdx,
                                                     cli::array<double>^ inOpen,
                                                     cli::array<double>^ inHigh,
                                                     cli::array<double>^ inLow,
                                                     cli::array<double>^ inClose,
                                                     [Out]int%    outBegIdx,
                                                     [Out]int%    outNbElement,
                                                     cli::array<int>^  outInteger );
         static enum class RetCode Cdl3StarsInSouth( int    startIdx,
                                                     int    endIdx,
                                                     cli::array<float>^ inOpen,
                                                     cli::array<float>^ inHigh,
                                                     cli::array<float>^ inLow,
                                                     cli::array<float>^ inClose,
                                                     [Out]int%    outBegIdx,
                                                     [Out]int%    outNbElement,
                                                     cli::array<int>^  outInteger );

         #define TA_CDL3STARSINSOUTH Core::Cdl3StarsInSouth
         #define TA_CDL3STARSINSOUTH_Lookback Core::Cdl3StarsInSouthLookback

         static int Cdl3WhiteSoldiersLookback( void );

         static enum class RetCode Cdl3WhiteSoldiers( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<double>^ inOpen,
                                                      cli::array<double>^ inHigh,
                                                      cli::array<double>^ inLow,
                                                      cli::array<double>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );
         static enum class RetCode Cdl3WhiteSoldiers( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<float>^ inOpen,
                                                      cli::array<float>^ inHigh,
                                                      cli::array<float>^ inLow,
                                                      cli::array<float>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );

         #define TA_CDL3WHITESOLDIERS Core::Cdl3WhiteSoldiers
         #define TA_CDL3WHITESOLDIERS_Lookback Core::Cdl3WhiteSoldiersLookback

         static int CdlAbandonedBabyLookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum class RetCode CdlAbandonedBaby( int    startIdx,
                                                     int    endIdx,
                                                     cli::array<double>^ inOpen,
                                                     cli::array<double>^ inHigh,
                                                     cli::array<double>^ inLow,
                                                     cli::array<double>^ inClose,
                                                     double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                     [Out]int%    outBegIdx,
                                                     [Out]int%    outNbElement,
                                                     cli::array<int>^  outInteger );
         static enum class RetCode CdlAbandonedBaby( int    startIdx,
                                                     int    endIdx,
                                                     cli::array<float>^ inOpen,
                                                     cli::array<float>^ inHigh,
                                                     cli::array<float>^ inLow,
                                                     cli::array<float>^ inClose,
                                                     double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                     [Out]int%    outBegIdx,
                                                     [Out]int%    outNbElement,
                                                     cli::array<int>^  outInteger );

         #define TA_CDLABANDONEDBABY Core::CdlAbandonedBaby
         #define TA_CDLABANDONEDBABY_Lookback Core::CdlAbandonedBabyLookback

         static int CdlAdvanceBlockLookback( void );

         static enum class RetCode CdlAdvanceBlock( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<double>^ inOpen,
                                                    cli::array<double>^ inHigh,
                                                    cli::array<double>^ inLow,
                                                    cli::array<double>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );
         static enum class RetCode CdlAdvanceBlock( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<float>^ inOpen,
                                                    cli::array<float>^ inHigh,
                                                    cli::array<float>^ inLow,
                                                    cli::array<float>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );

         #define TA_CDLADVANCEBLOCK Core::CdlAdvanceBlock
         #define TA_CDLADVANCEBLOCK_Lookback Core::CdlAdvanceBlockLookback

         static int CdlBeltHoldLookback( void );

         static enum class RetCode CdlBeltHold( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inOpen,
                                                cli::array<double>^ inHigh,
                                                cli::array<double>^ inLow,
                                                cli::array<double>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outInteger );
         static enum class RetCode CdlBeltHold( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inOpen,
                                                cli::array<float>^ inHigh,
                                                cli::array<float>^ inLow,
                                                cli::array<float>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outInteger );

         #define TA_CDLBELTHOLD Core::CdlBeltHold
         #define TA_CDLBELTHOLD_Lookback Core::CdlBeltHoldLookback

         static int CdlBreakawayLookback( void );

         static enum class RetCode CdlBreakaway( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<double>^ inOpen,
                                                 cli::array<double>^ inHigh,
                                                 cli::array<double>^ inLow,
                                                 cli::array<double>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );
         static enum class RetCode CdlBreakaway( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<float>^ inOpen,
                                                 cli::array<float>^ inHigh,
                                                 cli::array<float>^ inLow,
                                                 cli::array<float>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );

         #define TA_CDLBREAKAWAY Core::CdlBreakaway
         #define TA_CDLBREAKAWAY_Lookback Core::CdlBreakawayLookback

         static int CdlClosingMarubozuLookback( void );

         static enum class RetCode CdlClosingMarubozu( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<double>^ inOpen,
                                                       cli::array<double>^ inHigh,
                                                       cli::array<double>^ inLow,
                                                       cli::array<double>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );
         static enum class RetCode CdlClosingMarubozu( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<float>^ inOpen,
                                                       cli::array<float>^ inHigh,
                                                       cli::array<float>^ inLow,
                                                       cli::array<float>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );

         #define TA_CDLCLOSINGMARUBOZU Core::CdlClosingMarubozu
         #define TA_CDLCLOSINGMARUBOZU_Lookback Core::CdlClosingMarubozuLookback

         static int CdlConcealBabysWallLookback( void );

         static enum class RetCode CdlConcealBabysWall( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<double>^ inOpen,
                                                        cli::array<double>^ inHigh,
                                                        cli::array<double>^ inLow,
                                                        cli::array<double>^ inClose,
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );
         static enum class RetCode CdlConcealBabysWall( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<float>^ inOpen,
                                                        cli::array<float>^ inHigh,
                                                        cli::array<float>^ inLow,
                                                        cli::array<float>^ inClose,
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );

         #define TA_CDLCONCEALBABYSWALL Core::CdlConcealBabysWall
         #define TA_CDLCONCEALBABYSWALL_Lookback Core::CdlConcealBabysWallLookback

         static int CdlCounterAttackLookback( void );

         static enum class RetCode CdlCounterAttack( int    startIdx,
                                                     int    endIdx,
                                                     cli::array<double>^ inOpen,
                                                     cli::array<double>^ inHigh,
                                                     cli::array<double>^ inLow,
                                                     cli::array<double>^ inClose,
                                                     [Out]int%    outBegIdx,
                                                     [Out]int%    outNbElement,
                                                     cli::array<int>^  outInteger );
         static enum class RetCode CdlCounterAttack( int    startIdx,
                                                     int    endIdx,
                                                     cli::array<float>^ inOpen,
                                                     cli::array<float>^ inHigh,
                                                     cli::array<float>^ inLow,
                                                     cli::array<float>^ inClose,
                                                     [Out]int%    outBegIdx,
                                                     [Out]int%    outNbElement,
                                                     cli::array<int>^  outInteger );

         #define TA_CDLCOUNTERATTACK Core::CdlCounterAttack
         #define TA_CDLCOUNTERATTACK_Lookback Core::CdlCounterAttackLookback

         static int CdlDarkCloudCoverLookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum class RetCode CdlDarkCloudCover( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<double>^ inOpen,
                                                      cli::array<double>^ inHigh,
                                                      cli::array<double>^ inLow,
                                                      cli::array<double>^ inClose,
                                                      double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );
         static enum class RetCode CdlDarkCloudCover( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<float>^ inOpen,
                                                      cli::array<float>^ inHigh,
                                                      cli::array<float>^ inLow,
                                                      cli::array<float>^ inClose,
                                                      double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );

         #define TA_CDLDARKCLOUDCOVER Core::CdlDarkCloudCover
         #define TA_CDLDARKCLOUDCOVER_Lookback Core::CdlDarkCloudCoverLookback

         static int CdlDojiLookback( void );

         static enum class RetCode CdlDoji( int    startIdx,
                                            int    endIdx,
                                            cli::array<double>^ inOpen,
                                            cli::array<double>^ inHigh,
                                            cli::array<double>^ inLow,
                                            cli::array<double>^ inClose,
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<int>^  outInteger );
         static enum class RetCode CdlDoji( int    startIdx,
                                            int    endIdx,
                                            cli::array<float>^ inOpen,
                                            cli::array<float>^ inHigh,
                                            cli::array<float>^ inLow,
                                            cli::array<float>^ inClose,
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<int>^  outInteger );

         #define TA_CDLDOJI Core::CdlDoji
         #define TA_CDLDOJI_Lookback Core::CdlDojiLookback

         static int CdlDojiStarLookback( void );

         static enum class RetCode CdlDojiStar( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inOpen,
                                                cli::array<double>^ inHigh,
                                                cli::array<double>^ inLow,
                                                cli::array<double>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outInteger );
         static enum class RetCode CdlDojiStar( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inOpen,
                                                cli::array<float>^ inHigh,
                                                cli::array<float>^ inLow,
                                                cli::array<float>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outInteger );

         #define TA_CDLDOJISTAR Core::CdlDojiStar
         #define TA_CDLDOJISTAR_Lookback Core::CdlDojiStarLookback

         static int CdlDragonflyDojiLookback( void );

         static enum class RetCode CdlDragonflyDoji( int    startIdx,
                                                     int    endIdx,
                                                     cli::array<double>^ inOpen,
                                                     cli::array<double>^ inHigh,
                                                     cli::array<double>^ inLow,
                                                     cli::array<double>^ inClose,
                                                     [Out]int%    outBegIdx,
                                                     [Out]int%    outNbElement,
                                                     cli::array<int>^  outInteger );
         static enum class RetCode CdlDragonflyDoji( int    startIdx,
                                                     int    endIdx,
                                                     cli::array<float>^ inOpen,
                                                     cli::array<float>^ inHigh,
                                                     cli::array<float>^ inLow,
                                                     cli::array<float>^ inClose,
                                                     [Out]int%    outBegIdx,
                                                     [Out]int%    outNbElement,
                                                     cli::array<int>^  outInteger );

         #define TA_CDLDRAGONFLYDOJI Core::CdlDragonflyDoji
         #define TA_CDLDRAGONFLYDOJI_Lookback Core::CdlDragonflyDojiLookback

         static int CdlEngulfingLookback( void );

         static enum class RetCode CdlEngulfing( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<double>^ inOpen,
                                                 cli::array<double>^ inHigh,
                                                 cli::array<double>^ inLow,
                                                 cli::array<double>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );
         static enum class RetCode CdlEngulfing( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<float>^ inOpen,
                                                 cli::array<float>^ inHigh,
                                                 cli::array<float>^ inLow,
                                                 cli::array<float>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );

         #define TA_CDLENGULFING Core::CdlEngulfing
         #define TA_CDLENGULFING_Lookback Core::CdlEngulfingLookback

         static int CdlEveningDojiStarLookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum class RetCode CdlEveningDojiStar( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<double>^ inOpen,
                                                       cli::array<double>^ inHigh,
                                                       cli::array<double>^ inLow,
                                                       cli::array<double>^ inClose,
                                                       double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );
         static enum class RetCode CdlEveningDojiStar( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<float>^ inOpen,
                                                       cli::array<float>^ inHigh,
                                                       cli::array<float>^ inLow,
                                                       cli::array<float>^ inClose,
                                                       double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );

         #define TA_CDLEVENINGDOJISTAR Core::CdlEveningDojiStar
         #define TA_CDLEVENINGDOJISTAR_Lookback Core::CdlEveningDojiStarLookback

         static int CdlEveningStarLookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum class RetCode CdlEveningStar( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inOpen,
                                                   cli::array<double>^ inHigh,
                                                   cli::array<double>^ inLow,
                                                   cli::array<double>^ inClose,
                                                   double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );
         static enum class RetCode CdlEveningStar( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inOpen,
                                                   cli::array<float>^ inHigh,
                                                   cli::array<float>^ inLow,
                                                   cli::array<float>^ inClose,
                                                   double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );

         #define TA_CDLEVENINGSTAR Core::CdlEveningStar
         #define TA_CDLEVENINGSTAR_Lookback Core::CdlEveningStarLookback

         static int CdlGapSideSideWhiteLookback( void );

         static enum class RetCode CdlGapSideSideWhite( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<double>^ inOpen,
                                                        cli::array<double>^ inHigh,
                                                        cli::array<double>^ inLow,
                                                        cli::array<double>^ inClose,
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );
         static enum class RetCode CdlGapSideSideWhite( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<float>^ inOpen,
                                                        cli::array<float>^ inHigh,
                                                        cli::array<float>^ inLow,
                                                        cli::array<float>^ inClose,
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );

         #define TA_CDLGAPSIDESIDEWHITE Core::CdlGapSideSideWhite
         #define TA_CDLGAPSIDESIDEWHITE_Lookback Core::CdlGapSideSideWhiteLookback

         static int CdlGravestoneDojiLookback( void );

         static enum class RetCode CdlGravestoneDoji( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<double>^ inOpen,
                                                      cli::array<double>^ inHigh,
                                                      cli::array<double>^ inLow,
                                                      cli::array<double>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );
         static enum class RetCode CdlGravestoneDoji( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<float>^ inOpen,
                                                      cli::array<float>^ inHigh,
                                                      cli::array<float>^ inLow,
                                                      cli::array<float>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );

         #define TA_CDLGRAVESTONEDOJI Core::CdlGravestoneDoji
         #define TA_CDLGRAVESTONEDOJI_Lookback Core::CdlGravestoneDojiLookback

         static int CdlHammerLookback( void );

         static enum class RetCode CdlHammer( int    startIdx,
                                              int    endIdx,
                                              cli::array<double>^ inOpen,
                                              cli::array<double>^ inHigh,
                                              cli::array<double>^ inLow,
                                              cli::array<double>^ inClose,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<int>^  outInteger );
         static enum class RetCode CdlHammer( int    startIdx,
                                              int    endIdx,
                                              cli::array<float>^ inOpen,
                                              cli::array<float>^ inHigh,
                                              cli::array<float>^ inLow,
                                              cli::array<float>^ inClose,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<int>^  outInteger );

         #define TA_CDLHAMMER Core::CdlHammer
         #define TA_CDLHAMMER_Lookback Core::CdlHammerLookback

         static int CdlHangingManLookback( void );

         static enum class RetCode CdlHangingMan( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<double>^ inOpen,
                                                  cli::array<double>^ inHigh,
                                                  cli::array<double>^ inLow,
                                                  cli::array<double>^ inClose,
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<int>^  outInteger );
         static enum class RetCode CdlHangingMan( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<float>^ inOpen,
                                                  cli::array<float>^ inHigh,
                                                  cli::array<float>^ inLow,
                                                  cli::array<float>^ inClose,
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<int>^  outInteger );

         #define TA_CDLHANGINGMAN Core::CdlHangingMan
         #define TA_CDLHANGINGMAN_Lookback Core::CdlHangingManLookback

         static int CdlHaramiLookback( void );

         static enum class RetCode CdlHarami( int    startIdx,
                                              int    endIdx,
                                              cli::array<double>^ inOpen,
                                              cli::array<double>^ inHigh,
                                              cli::array<double>^ inLow,
                                              cli::array<double>^ inClose,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<int>^  outInteger );
         static enum class RetCode CdlHarami( int    startIdx,
                                              int    endIdx,
                                              cli::array<float>^ inOpen,
                                              cli::array<float>^ inHigh,
                                              cli::array<float>^ inLow,
                                              cli::array<float>^ inClose,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<int>^  outInteger );

         #define TA_CDLHARAMI Core::CdlHarami
         #define TA_CDLHARAMI_Lookback Core::CdlHaramiLookback

         static int CdlHaramiCrossLookback( void );

         static enum class RetCode CdlHaramiCross( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inOpen,
                                                   cli::array<double>^ inHigh,
                                                   cli::array<double>^ inLow,
                                                   cli::array<double>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );
         static enum class RetCode CdlHaramiCross( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inOpen,
                                                   cli::array<float>^ inHigh,
                                                   cli::array<float>^ inLow,
                                                   cli::array<float>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );

         #define TA_CDLHARAMICROSS Core::CdlHaramiCross
         #define TA_CDLHARAMICROSS_Lookback Core::CdlHaramiCrossLookback

         static int CdlHignWaveLookback( void );

         static enum class RetCode CdlHignWave( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inOpen,
                                                cli::array<double>^ inHigh,
                                                cli::array<double>^ inLow,
                                                cli::array<double>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outInteger );
         static enum class RetCode CdlHignWave( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inOpen,
                                                cli::array<float>^ inHigh,
                                                cli::array<float>^ inLow,
                                                cli::array<float>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outInteger );

         #define TA_CDLHIGHWAVE Core::CdlHignWave
         #define TA_CDLHIGHWAVE_Lookback Core::CdlHignWaveLookback

         static int CdlHikkakeLookback( void );

         static enum class RetCode CdlHikkake( int    startIdx,
                                               int    endIdx,
                                               cli::array<double>^ inOpen,
                                               cli::array<double>^ inHigh,
                                               cli::array<double>^ inLow,
                                               cli::array<double>^ inClose,
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<int>^  outInteger );
         static enum class RetCode CdlHikkake( int    startIdx,
                                               int    endIdx,
                                               cli::array<float>^ inOpen,
                                               cli::array<float>^ inHigh,
                                               cli::array<float>^ inLow,
                                               cli::array<float>^ inClose,
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<int>^  outInteger );

         #define TA_CDLHIKKAKE Core::CdlHikkake
         #define TA_CDLHIKKAKE_Lookback Core::CdlHikkakeLookback

         static int CdlHikkakeModLookback( void );

         static enum class RetCode CdlHikkakeMod( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<double>^ inOpen,
                                                  cli::array<double>^ inHigh,
                                                  cli::array<double>^ inLow,
                                                  cli::array<double>^ inClose,
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<int>^  outInteger );
         static enum class RetCode CdlHikkakeMod( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<float>^ inOpen,
                                                  cli::array<float>^ inHigh,
                                                  cli::array<float>^ inLow,
                                                  cli::array<float>^ inClose,
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<int>^  outInteger );

         #define TA_CDLHIKKAKEMOD Core::CdlHikkakeMod
         #define TA_CDLHIKKAKEMOD_Lookback Core::CdlHikkakeModLookback

         static int CdlHomingPigeonLookback( void );

         static enum class RetCode CdlHomingPigeon( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<double>^ inOpen,
                                                    cli::array<double>^ inHigh,
                                                    cli::array<double>^ inLow,
                                                    cli::array<double>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );
         static enum class RetCode CdlHomingPigeon( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<float>^ inOpen,
                                                    cli::array<float>^ inHigh,
                                                    cli::array<float>^ inLow,
                                                    cli::array<float>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );

         #define TA_CDLHOMINGPIGEON Core::CdlHomingPigeon
         #define TA_CDLHOMINGPIGEON_Lookback Core::CdlHomingPigeonLookback

         static int CdlIdentical3CrowsLookback( void );

         static enum class RetCode CdlIdentical3Crows( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<double>^ inOpen,
                                                       cli::array<double>^ inHigh,
                                                       cli::array<double>^ inLow,
                                                       cli::array<double>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );
         static enum class RetCode CdlIdentical3Crows( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<float>^ inOpen,
                                                       cli::array<float>^ inHigh,
                                                       cli::array<float>^ inLow,
                                                       cli::array<float>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );

         #define TA_CDLIDENTICAL3CROWS Core::CdlIdentical3Crows
         #define TA_CDLIDENTICAL3CROWS_Lookback Core::CdlIdentical3CrowsLookback

         static int CdlInNeckLookback( void );

         static enum class RetCode CdlInNeck( int    startIdx,
                                              int    endIdx,
                                              cli::array<double>^ inOpen,
                                              cli::array<double>^ inHigh,
                                              cli::array<double>^ inLow,
                                              cli::array<double>^ inClose,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<int>^  outInteger );
         static enum class RetCode CdlInNeck( int    startIdx,
                                              int    endIdx,
                                              cli::array<float>^ inOpen,
                                              cli::array<float>^ inHigh,
                                              cli::array<float>^ inLow,
                                              cli::array<float>^ inClose,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<int>^  outInteger );

         #define TA_CDLINNECK Core::CdlInNeck
         #define TA_CDLINNECK_Lookback Core::CdlInNeckLookback

         static int CdlInvertedHammerLookback( void );

         static enum class RetCode CdlInvertedHammer( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<double>^ inOpen,
                                                      cli::array<double>^ inHigh,
                                                      cli::array<double>^ inLow,
                                                      cli::array<double>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );
         static enum class RetCode CdlInvertedHammer( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<float>^ inOpen,
                                                      cli::array<float>^ inHigh,
                                                      cli::array<float>^ inLow,
                                                      cli::array<float>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );

         #define TA_CDLINVERTEDHAMMER Core::CdlInvertedHammer
         #define TA_CDLINVERTEDHAMMER_Lookback Core::CdlInvertedHammerLookback

         static int CdlKickingLookback( void );

         static enum class RetCode CdlKicking( int    startIdx,
                                               int    endIdx,
                                               cli::array<double>^ inOpen,
                                               cli::array<double>^ inHigh,
                                               cli::array<double>^ inLow,
                                               cli::array<double>^ inClose,
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<int>^  outInteger );
         static enum class RetCode CdlKicking( int    startIdx,
                                               int    endIdx,
                                               cli::array<float>^ inOpen,
                                               cli::array<float>^ inHigh,
                                               cli::array<float>^ inLow,
                                               cli::array<float>^ inClose,
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<int>^  outInteger );

         #define TA_CDLKICKING Core::CdlKicking
         #define TA_CDLKICKING_Lookback Core::CdlKickingLookback

         static int CdlKickingByLengthLookback( void );

         static enum class RetCode CdlKickingByLength( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<double>^ inOpen,
                                                       cli::array<double>^ inHigh,
                                                       cli::array<double>^ inLow,
                                                       cli::array<double>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );
         static enum class RetCode CdlKickingByLength( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<float>^ inOpen,
                                                       cli::array<float>^ inHigh,
                                                       cli::array<float>^ inLow,
                                                       cli::array<float>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );

         #define TA_CDLKICKINGBYLENGTH Core::CdlKickingByLength
         #define TA_CDLKICKINGBYLENGTH_Lookback Core::CdlKickingByLengthLookback

         static int CdlLadderBottomLookback( void );

         static enum class RetCode CdlLadderBottom( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<double>^ inOpen,
                                                    cli::array<double>^ inHigh,
                                                    cli::array<double>^ inLow,
                                                    cli::array<double>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );
         static enum class RetCode CdlLadderBottom( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<float>^ inOpen,
                                                    cli::array<float>^ inHigh,
                                                    cli::array<float>^ inLow,
                                                    cli::array<float>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );

         #define TA_CDLLADDERBOTTOM Core::CdlLadderBottom
         #define TA_CDLLADDERBOTTOM_Lookback Core::CdlLadderBottomLookback

         static int CdlLongLeggedDojiLookback( void );

         static enum class RetCode CdlLongLeggedDoji( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<double>^ inOpen,
                                                      cli::array<double>^ inHigh,
                                                      cli::array<double>^ inLow,
                                                      cli::array<double>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );
         static enum class RetCode CdlLongLeggedDoji( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<float>^ inOpen,
                                                      cli::array<float>^ inHigh,
                                                      cli::array<float>^ inLow,
                                                      cli::array<float>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );

         #define TA_CDLLONGLEGGEDDOJI Core::CdlLongLeggedDoji
         #define TA_CDLLONGLEGGEDDOJI_Lookback Core::CdlLongLeggedDojiLookback

         static int CdlLongLineLookback( void );

         static enum class RetCode CdlLongLine( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inOpen,
                                                cli::array<double>^ inHigh,
                                                cli::array<double>^ inLow,
                                                cli::array<double>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outInteger );
         static enum class RetCode CdlLongLine( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inOpen,
                                                cli::array<float>^ inHigh,
                                                cli::array<float>^ inLow,
                                                cli::array<float>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outInteger );

         #define TA_CDLLONGLINE Core::CdlLongLine
         #define TA_CDLLONGLINE_Lookback Core::CdlLongLineLookback

         static int CdlMarubozuLookback( void );

         static enum class RetCode CdlMarubozu( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inOpen,
                                                cli::array<double>^ inHigh,
                                                cli::array<double>^ inLow,
                                                cli::array<double>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outInteger );
         static enum class RetCode CdlMarubozu( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inOpen,
                                                cli::array<float>^ inHigh,
                                                cli::array<float>^ inLow,
                                                cli::array<float>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outInteger );

         #define TA_CDLMARUBOZU Core::CdlMarubozu
         #define TA_CDLMARUBOZU_Lookback Core::CdlMarubozuLookback

         static int CdlMatchingLowLookback( void );

         static enum class RetCode CdlMatchingLow( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inOpen,
                                                   cli::array<double>^ inHigh,
                                                   cli::array<double>^ inLow,
                                                   cli::array<double>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );
         static enum class RetCode CdlMatchingLow( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inOpen,
                                                   cli::array<float>^ inHigh,
                                                   cli::array<float>^ inLow,
                                                   cli::array<float>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );

         #define TA_CDLMATCHINGLOW Core::CdlMatchingLow
         #define TA_CDLMATCHINGLOW_Lookback Core::CdlMatchingLowLookback

         static int CdlMatHoldLookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum class RetCode CdlMatHold( int    startIdx,
                                               int    endIdx,
                                               cli::array<double>^ inOpen,
                                               cli::array<double>^ inHigh,
                                               cli::array<double>^ inLow,
                                               cli::array<double>^ inClose,
                                               double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<int>^  outInteger );
         static enum class RetCode CdlMatHold( int    startIdx,
                                               int    endIdx,
                                               cli::array<float>^ inOpen,
                                               cli::array<float>^ inHigh,
                                               cli::array<float>^ inLow,
                                               cli::array<float>^ inClose,
                                               double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<int>^  outInteger );

         #define TA_CDLMATHOLD Core::CdlMatHold
         #define TA_CDLMATHOLD_Lookback Core::CdlMatHoldLookback

         static int CdlMorningDojiStarLookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum class RetCode CdlMorningDojiStar( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<double>^ inOpen,
                                                       cli::array<double>^ inHigh,
                                                       cli::array<double>^ inLow,
                                                       cli::array<double>^ inClose,
                                                       double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );
         static enum class RetCode CdlMorningDojiStar( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<float>^ inOpen,
                                                       cli::array<float>^ inHigh,
                                                       cli::array<float>^ inLow,
                                                       cli::array<float>^ inClose,
                                                       double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );

         #define TA_CDLMORNINGDOJISTAR Core::CdlMorningDojiStar
         #define TA_CDLMORNINGDOJISTAR_Lookback Core::CdlMorningDojiStarLookback

         static int CdlMorningStarLookback( double        optInPenetration );  /* From 0 to TA_REAL_MAX */

         static enum class RetCode CdlMorningStar( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inOpen,
                                                   cli::array<double>^ inHigh,
                                                   cli::array<double>^ inLow,
                                                   cli::array<double>^ inClose,
                                                   double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );
         static enum class RetCode CdlMorningStar( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inOpen,
                                                   cli::array<float>^ inHigh,
                                                   cli::array<float>^ inLow,
                                                   cli::array<float>^ inClose,
                                                   double        optInPenetration, /* From 0 to TA_REAL_MAX */
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );

         #define TA_CDLMORNINGSTAR Core::CdlMorningStar
         #define TA_CDLMORNINGSTAR_Lookback Core::CdlMorningStarLookback

         static int CdlOnNeckLookback( void );

         static enum class RetCode CdlOnNeck( int    startIdx,
                                              int    endIdx,
                                              cli::array<double>^ inOpen,
                                              cli::array<double>^ inHigh,
                                              cli::array<double>^ inLow,
                                              cli::array<double>^ inClose,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<int>^  outInteger );
         static enum class RetCode CdlOnNeck( int    startIdx,
                                              int    endIdx,
                                              cli::array<float>^ inOpen,
                                              cli::array<float>^ inHigh,
                                              cli::array<float>^ inLow,
                                              cli::array<float>^ inClose,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<int>^  outInteger );

         #define TA_CDLONNECK Core::CdlOnNeck
         #define TA_CDLONNECK_Lookback Core::CdlOnNeckLookback

         static int CdlPiercingLookback( void );

         static enum class RetCode CdlPiercing( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inOpen,
                                                cli::array<double>^ inHigh,
                                                cli::array<double>^ inLow,
                                                cli::array<double>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outInteger );
         static enum class RetCode CdlPiercing( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inOpen,
                                                cli::array<float>^ inHigh,
                                                cli::array<float>^ inLow,
                                                cli::array<float>^ inClose,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outInteger );

         #define TA_CDLPIERCING Core::CdlPiercing
         #define TA_CDLPIERCING_Lookback Core::CdlPiercingLookback

         static int CdlRickshawManLookback( void );

         static enum class RetCode CdlRickshawMan( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inOpen,
                                                   cli::array<double>^ inHigh,
                                                   cli::array<double>^ inLow,
                                                   cli::array<double>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );
         static enum class RetCode CdlRickshawMan( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inOpen,
                                                   cli::array<float>^ inHigh,
                                                   cli::array<float>^ inLow,
                                                   cli::array<float>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );

         #define TA_CDLRICKSHAWMAN Core::CdlRickshawMan
         #define TA_CDLRICKSHAWMAN_Lookback Core::CdlRickshawManLookback

         static int CdlRiseFall3MethodsLookback( void );

         static enum class RetCode CdlRiseFall3Methods( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<double>^ inOpen,
                                                        cli::array<double>^ inHigh,
                                                        cli::array<double>^ inLow,
                                                        cli::array<double>^ inClose,
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );
         static enum class RetCode CdlRiseFall3Methods( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<float>^ inOpen,
                                                        cli::array<float>^ inHigh,
                                                        cli::array<float>^ inLow,
                                                        cli::array<float>^ inClose,
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );

         #define TA_CDLRISEFALL3METHODS Core::CdlRiseFall3Methods
         #define TA_CDLRISEFALL3METHODS_Lookback Core::CdlRiseFall3MethodsLookback

         static int CdlSeperatingLinesLookback( void );

         static enum class RetCode CdlSeperatingLines( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<double>^ inOpen,
                                                       cli::array<double>^ inHigh,
                                                       cli::array<double>^ inLow,
                                                       cli::array<double>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );
         static enum class RetCode CdlSeperatingLines( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<float>^ inOpen,
                                                       cli::array<float>^ inHigh,
                                                       cli::array<float>^ inLow,
                                                       cli::array<float>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );

         #define TA_CDLSEPARATINGLINES Core::CdlSeperatingLines
         #define TA_CDLSEPARATINGLINES_Lookback Core::CdlSeperatingLinesLookback

         static int CdlShootingStarLookback( void );

         static enum class RetCode CdlShootingStar( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<double>^ inOpen,
                                                    cli::array<double>^ inHigh,
                                                    cli::array<double>^ inLow,
                                                    cli::array<double>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );
         static enum class RetCode CdlShootingStar( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<float>^ inOpen,
                                                    cli::array<float>^ inHigh,
                                                    cli::array<float>^ inLow,
                                                    cli::array<float>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );

         #define TA_CDLSHOOTINGSTAR Core::CdlShootingStar
         #define TA_CDLSHOOTINGSTAR_Lookback Core::CdlShootingStarLookback

         static int CdlShortLineLookback( void );

         static enum class RetCode CdlShortLine( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<double>^ inOpen,
                                                 cli::array<double>^ inHigh,
                                                 cli::array<double>^ inLow,
                                                 cli::array<double>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );
         static enum class RetCode CdlShortLine( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<float>^ inOpen,
                                                 cli::array<float>^ inHigh,
                                                 cli::array<float>^ inLow,
                                                 cli::array<float>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );

         #define TA_CDLSHORTLINE Core::CdlShortLine
         #define TA_CDLSHORTLINE_Lookback Core::CdlShortLineLookback

         static int CdlSpinningTopLookback( void );

         static enum class RetCode CdlSpinningTop( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inOpen,
                                                   cli::array<double>^ inHigh,
                                                   cli::array<double>^ inLow,
                                                   cli::array<double>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );
         static enum class RetCode CdlSpinningTop( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inOpen,
                                                   cli::array<float>^ inHigh,
                                                   cli::array<float>^ inLow,
                                                   cli::array<float>^ inClose,
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<int>^  outInteger );

         #define TA_CDLSPINNINGTOP Core::CdlSpinningTop
         #define TA_CDLSPINNINGTOP_Lookback Core::CdlSpinningTopLookback

         static int CdlStalledPatternLookback( void );

         static enum class RetCode CdlStalledPattern( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<double>^ inOpen,
                                                      cli::array<double>^ inHigh,
                                                      cli::array<double>^ inLow,
                                                      cli::array<double>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );
         static enum class RetCode CdlStalledPattern( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<float>^ inOpen,
                                                      cli::array<float>^ inHigh,
                                                      cli::array<float>^ inLow,
                                                      cli::array<float>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );

         #define TA_CDLSTALLEDPATTERN Core::CdlStalledPattern
         #define TA_CDLSTALLEDPATTERN_Lookback Core::CdlStalledPatternLookback

         static int CdlStickSandwhichLookback( void );

         static enum class RetCode CdlStickSandwhich( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<double>^ inOpen,
                                                      cli::array<double>^ inHigh,
                                                      cli::array<double>^ inLow,
                                                      cli::array<double>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );
         static enum class RetCode CdlStickSandwhich( int    startIdx,
                                                      int    endIdx,
                                                      cli::array<float>^ inOpen,
                                                      cli::array<float>^ inHigh,
                                                      cli::array<float>^ inLow,
                                                      cli::array<float>^ inClose,
                                                      [Out]int%    outBegIdx,
                                                      [Out]int%    outNbElement,
                                                      cli::array<int>^  outInteger );

         #define TA_CDLSTICKSANDWICH Core::CdlStickSandwhich
         #define TA_CDLSTICKSANDWICH_Lookback Core::CdlStickSandwhichLookback

         static int CdlTakuriLookback( void );

         static enum class RetCode CdlTakuri( int    startIdx,
                                              int    endIdx,
                                              cli::array<double>^ inOpen,
                                              cli::array<double>^ inHigh,
                                              cli::array<double>^ inLow,
                                              cli::array<double>^ inClose,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<int>^  outInteger );
         static enum class RetCode CdlTakuri( int    startIdx,
                                              int    endIdx,
                                              cli::array<float>^ inOpen,
                                              cli::array<float>^ inHigh,
                                              cli::array<float>^ inLow,
                                              cli::array<float>^ inClose,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<int>^  outInteger );

         #define TA_CDLTAKURI Core::CdlTakuri
         #define TA_CDLTAKURI_Lookback Core::CdlTakuriLookback

         static int CdlTasukiGapLookback( void );

         static enum class RetCode CdlTasukiGap( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<double>^ inOpen,
                                                 cli::array<double>^ inHigh,
                                                 cli::array<double>^ inLow,
                                                 cli::array<double>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );
         static enum class RetCode CdlTasukiGap( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<float>^ inOpen,
                                                 cli::array<float>^ inHigh,
                                                 cli::array<float>^ inLow,
                                                 cli::array<float>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );

         #define TA_CDLTASUKIGAP Core::CdlTasukiGap
         #define TA_CDLTASUKIGAP_Lookback Core::CdlTasukiGapLookback

         static int CdlThrustingLookback( void );

         static enum class RetCode CdlThrusting( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<double>^ inOpen,
                                                 cli::array<double>^ inHigh,
                                                 cli::array<double>^ inLow,
                                                 cli::array<double>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );
         static enum class RetCode CdlThrusting( int    startIdx,
                                                 int    endIdx,
                                                 cli::array<float>^ inOpen,
                                                 cli::array<float>^ inHigh,
                                                 cli::array<float>^ inLow,
                                                 cli::array<float>^ inClose,
                                                 [Out]int%    outBegIdx,
                                                 [Out]int%    outNbElement,
                                                 cli::array<int>^  outInteger );

         #define TA_CDLTHRUSTING Core::CdlThrusting
         #define TA_CDLTHRUSTING_Lookback Core::CdlThrustingLookback

         static int CdlTristarLookback( void );

         static enum class RetCode CdlTristar( int    startIdx,
                                               int    endIdx,
                                               cli::array<double>^ inOpen,
                                               cli::array<double>^ inHigh,
                                               cli::array<double>^ inLow,
                                               cli::array<double>^ inClose,
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<int>^  outInteger );
         static enum class RetCode CdlTristar( int    startIdx,
                                               int    endIdx,
                                               cli::array<float>^ inOpen,
                                               cli::array<float>^ inHigh,
                                               cli::array<float>^ inLow,
                                               cli::array<float>^ inClose,
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<int>^  outInteger );

         #define TA_CDLTRISTAR Core::CdlTristar
         #define TA_CDLTRISTAR_Lookback Core::CdlTristarLookback

         static int CdlUnique3RiverLookback( void );

         static enum class RetCode CdlUnique3River( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<double>^ inOpen,
                                                    cli::array<double>^ inHigh,
                                                    cli::array<double>^ inLow,
                                                    cli::array<double>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );
         static enum class RetCode CdlUnique3River( int    startIdx,
                                                    int    endIdx,
                                                    cli::array<float>^ inOpen,
                                                    cli::array<float>^ inHigh,
                                                    cli::array<float>^ inLow,
                                                    cli::array<float>^ inClose,
                                                    [Out]int%    outBegIdx,
                                                    [Out]int%    outNbElement,
                                                    cli::array<int>^  outInteger );

         #define TA_CDLUNIQUE3RIVER Core::CdlUnique3River
         #define TA_CDLUNIQUE3RIVER_Lookback Core::CdlUnique3RiverLookback

         static int CdlUpsideGap2CrowsLookback( void );

         static enum class RetCode CdlUpsideGap2Crows( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<double>^ inOpen,
                                                       cli::array<double>^ inHigh,
                                                       cli::array<double>^ inLow,
                                                       cli::array<double>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );
         static enum class RetCode CdlUpsideGap2Crows( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<float>^ inOpen,
                                                       cli::array<float>^ inHigh,
                                                       cli::array<float>^ inLow,
                                                       cli::array<float>^ inClose,
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<int>^  outInteger );

         #define TA_CDLUPSIDEGAP2CROWS Core::CdlUpsideGap2Crows
         #define TA_CDLUPSIDEGAP2CROWS_Lookback Core::CdlUpsideGap2CrowsLookback

         static int CdlXSideGap3MethodsLookback( void );

         static enum class RetCode CdlXSideGap3Methods( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<double>^ inOpen,
                                                        cli::array<double>^ inHigh,
                                                        cli::array<double>^ inLow,
                                                        cli::array<double>^ inClose,
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );
         static enum class RetCode CdlXSideGap3Methods( int    startIdx,
                                                        int    endIdx,
                                                        cli::array<float>^ inOpen,
                                                        cli::array<float>^ inHigh,
                                                        cli::array<float>^ inLow,
                                                        cli::array<float>^ inClose,
                                                        [Out]int%    outBegIdx,
                                                        [Out]int%    outNbElement,
                                                        cli::array<int>^  outInteger );

         #define TA_CDLXSIDEGAP3METHODS Core::CdlXSideGap3Methods
         #define TA_CDLXSIDEGAP3METHODS_Lookback Core::CdlXSideGap3MethodsLookback

         static int CmoLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Cmo( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Cmo( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_CMO Core::Cmo
         #define TA_CMO_Lookback Core::CmoLookback

         static int CorrelLookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class RetCode Correl( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal0,
                                           cli::array<double>^ inReal1,
                                           int           optInTimePeriod, /* From 1 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class RetCode Correl( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal0,
                                           cli::array<float>^ inReal1,
                                           int           optInTimePeriod, /* From 1 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_CORREL Core::Correl
         #define TA_CORREL_Lookback Core::CorrelLookback

         static int DemaLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Dema( int    startIdx,
                                         int    endIdx,
                                         cli::array<double>^ inReal,
                                         int           optInTimePeriod, /* From 2 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );
         static enum class RetCode Dema( int    startIdx,
                                         int    endIdx,
                                         cli::array<float>^ inReal,
                                         int           optInTimePeriod, /* From 2 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );

         #define TA_DEMA Core::Dema
         #define TA_DEMA_Lookback Core::DemaLookback

         static int DxLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Dx( int    startIdx,
                                       int    endIdx,
                                       cli::array<double>^ inHigh,
                                       cli::array<double>^ inLow,
                                       cli::array<double>^ inClose,
                                       int           optInTimePeriod, /* From 2 to 100000 */
                                       [Out]int%    outBegIdx,
                                       [Out]int%    outNbElement,
                                       cli::array<double>^  outReal );
         static enum class RetCode Dx( int    startIdx,
                                       int    endIdx,
                                       cli::array<float>^ inHigh,
                                       cli::array<float>^ inLow,
                                       cli::array<float>^ inClose,
                                       int           optInTimePeriod, /* From 2 to 100000 */
                                       [Out]int%    outBegIdx,
                                       [Out]int%    outNbElement,
                                       cli::array<double>^  outReal );

         #define TA_DX Core::Dx
         #define TA_DX_Lookback Core::DxLookback

         static int EmaLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Ema( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Ema( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_EMA Core::Ema
         #define TA_EMA_Lookback Core::EmaLookback

         static int HtDcPeriodLookback( void );

         static enum class RetCode HtDcPeriod( int    startIdx,
                                               int    endIdx,
                                               cli::array<double>^ inReal,
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<double>^  outReal );
         static enum class RetCode HtDcPeriod( int    startIdx,
                                               int    endIdx,
                                               cli::array<float>^ inReal,
                                               [Out]int%    outBegIdx,
                                               [Out]int%    outNbElement,
                                               cli::array<double>^  outReal );

         #define TA_HT_DCPERIOD Core::HtDcPeriod
         #define TA_HT_DCPERIOD_Lookback Core::HtDcPeriodLookback

         static int HtDcPhaseLookback( void );

         static enum class RetCode HtDcPhase( int    startIdx,
                                              int    endIdx,
                                              cli::array<double>^ inReal,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outReal );
         static enum class RetCode HtDcPhase( int    startIdx,
                                              int    endIdx,
                                              cli::array<float>^ inReal,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outReal );

         #define TA_HT_DCPHASE Core::HtDcPhase
         #define TA_HT_DCPHASE_Lookback Core::HtDcPhaseLookback

         static int HtPhasorLookback( void );

         static enum class RetCode HtPhasor( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inReal,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outInPhase,
                                             cli::array<double>^  outQuadrature );
         static enum class RetCode HtPhasor( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inReal,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outInPhase,
                                             cli::array<double>^  outQuadrature );

         #define TA_HT_PHASOR Core::HtPhasor
         #define TA_HT_PHASOR_Lookback Core::HtPhasorLookback

         static int HtSineLookback( void );

         static enum class RetCode HtSine( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outSine,
                                           cli::array<double>^  outLeadSine );
         static enum class RetCode HtSine( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outSine,
                                           cli::array<double>^  outLeadSine );

         #define TA_HT_SINE Core::HtSine
         #define TA_HT_SINE_Lookback Core::HtSineLookback

         static int HtTrendlineLookback( void );

         static enum class RetCode HtTrendline( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inReal,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );
         static enum class RetCode HtTrendline( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inReal,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<double>^  outReal );

         #define TA_HT_TRENDLINE Core::HtTrendline
         #define TA_HT_TRENDLINE_Lookback Core::HtTrendlineLookback

         static int HtTrendModeLookback( void );

         static enum class RetCode HtTrendMode( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inReal,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outInteger );
         static enum class RetCode HtTrendMode( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inReal,
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outInteger );

         #define TA_HT_TRENDMODE Core::HtTrendMode
         #define TA_HT_TRENDMODE_Lookback Core::HtTrendModeLookback

         static int KamaLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Kama( int    startIdx,
                                         int    endIdx,
                                         cli::array<double>^ inReal,
                                         int           optInTimePeriod, /* From 2 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );
         static enum class RetCode Kama( int    startIdx,
                                         int    endIdx,
                                         cli::array<float>^ inReal,
                                         int           optInTimePeriod, /* From 2 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );

         #define TA_KAMA Core::Kama
         #define TA_KAMA_Lookback Core::KamaLookback

         static int LinearRegLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode LinearReg( int    startIdx,
                                              int    endIdx,
                                              cli::array<double>^ inReal,
                                              int           optInTimePeriod, /* From 2 to 100000 */
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outReal );
         static enum class RetCode LinearReg( int    startIdx,
                                              int    endIdx,
                                              cli::array<float>^ inReal,
                                              int           optInTimePeriod, /* From 2 to 100000 */
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outReal );

         #define TA_LINEARREG Core::LinearReg
         #define TA_LINEARREG_Lookback Core::LinearRegLookback

         static int LinearRegAngleLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode LinearRegAngle( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inReal,
                                                   int           optInTimePeriod, /* From 2 to 100000 */
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<double>^  outReal );
         static enum class RetCode LinearRegAngle( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inReal,
                                                   int           optInTimePeriod, /* From 2 to 100000 */
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<double>^  outReal );

         #define TA_LINEARREG_ANGLE Core::LinearRegAngle
         #define TA_LINEARREG_ANGLE_Lookback Core::LinearRegAngleLookback

         static int LinearRegInterceptLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode LinearRegIntercept( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<double>^ inReal,
                                                       int           optInTimePeriod, /* From 2 to 100000 */
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<double>^  outReal );
         static enum class RetCode LinearRegIntercept( int    startIdx,
                                                       int    endIdx,
                                                       cli::array<float>^ inReal,
                                                       int           optInTimePeriod, /* From 2 to 100000 */
                                                       [Out]int%    outBegIdx,
                                                       [Out]int%    outNbElement,
                                                       cli::array<double>^  outReal );

         #define TA_LINEARREG_INTERCEPT Core::LinearRegIntercept
         #define TA_LINEARREG_INTERCEPT_Lookback Core::LinearRegInterceptLookback

         static int LinearRegSlopeLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode LinearRegSlope( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<double>^ inReal,
                                                   int           optInTimePeriod, /* From 2 to 100000 */
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<double>^  outReal );
         static enum class RetCode LinearRegSlope( int    startIdx,
                                                   int    endIdx,
                                                   cli::array<float>^ inReal,
                                                   int           optInTimePeriod, /* From 2 to 100000 */
                                                   [Out]int%    outBegIdx,
                                                   [Out]int%    outNbElement,
                                                   cli::array<double>^  outReal );

         #define TA_LINEARREG_SLOPE Core::LinearRegSlope
         #define TA_LINEARREG_SLOPE_Lookback Core::LinearRegSlopeLookback

         static int MovingAverageLookback( int           optInTimePeriod, /* From 1 to 100000 */
                                         MAType        optInMAType ); 
         static enum class RetCode MovingAverage( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<double>^ inReal,
                                                  int           optInTimePeriod, /* From 1 to 100000 */
                                                  MAType        optInMAType,
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<double>^  outReal );
         static enum class RetCode MovingAverage( int    startIdx,
                                                  int    endIdx,
                                                  cli::array<float>^ inReal,
                                                  int           optInTimePeriod, /* From 1 to 100000 */
                                                  MAType        optInMAType,
                                                  [Out]int%    outBegIdx,
                                                  [Out]int%    outNbElement,
                                                  cli::array<double>^  outReal );

         #define TA_MA Core::MovingAverage
         #define TA_MA_Lookback Core::MovingAverageLookback

         static int MacdLookback( int           optInFastPeriod, /* From 2 to 100000 */
                                int           optInSlowPeriod, /* From 2 to 100000 */
                                int           optInSignalPeriod );  /* From 1 to 100000 */

         static enum class RetCode Macd( int    startIdx,
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
         static enum class RetCode Macd( int    startIdx,
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

         #define TA_MACD Core::Macd
         #define TA_MACD_Lookback Core::MacdLookback

         static int MacdExtLookback( int           optInFastPeriod, /* From 2 to 100000 */
                                   MAType        optInFastMAType,
                                   int           optInSlowPeriod, /* From 2 to 100000 */
                                   MAType        optInSlowMAType,
                                   int           optInSignalPeriod, /* From 1 to 100000 */
                                   MAType        optInSignalMAType ); 
         static enum class RetCode MacdExt( int    startIdx,
                                            int    endIdx,
                                            cli::array<double>^ inReal,
                                            int           optInFastPeriod, /* From 2 to 100000 */
                                            MAType        optInFastMAType,
                                            int           optInSlowPeriod, /* From 2 to 100000 */
                                            MAType        optInSlowMAType,
                                            int           optInSignalPeriod, /* From 1 to 100000 */
                                            MAType        optInSignalMAType,
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outMACD,
                                            cli::array<double>^  outMACDSignal,
                                            cli::array<double>^  outMACDHist );
         static enum class RetCode MacdExt( int    startIdx,
                                            int    endIdx,
                                            cli::array<float>^ inReal,
                                            int           optInFastPeriod, /* From 2 to 100000 */
                                            MAType        optInFastMAType,
                                            int           optInSlowPeriod, /* From 2 to 100000 */
                                            MAType        optInSlowMAType,
                                            int           optInSignalPeriod, /* From 1 to 100000 */
                                            MAType        optInSignalMAType,
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outMACD,
                                            cli::array<double>^  outMACDSignal,
                                            cli::array<double>^  outMACDHist );

         #define TA_MACDEXT Core::MacdExt
         #define TA_MACDEXT_Lookback Core::MacdExtLookback

         static int MacdFixLookback( int           optInSignalPeriod );  /* From 1 to 100000 */

         static enum class RetCode MacdFix( int    startIdx,
                                            int    endIdx,
                                            cli::array<double>^ inReal,
                                            int           optInSignalPeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outMACD,
                                            cli::array<double>^  outMACDSignal,
                                            cli::array<double>^  outMACDHist );
         static enum class RetCode MacdFix( int    startIdx,
                                            int    endIdx,
                                            cli::array<float>^ inReal,
                                            int           optInSignalPeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outMACD,
                                            cli::array<double>^  outMACDSignal,
                                            cli::array<double>^  outMACDHist );

         #define TA_MACDFIX Core::MacdFix
         #define TA_MACDFIX_Lookback Core::MacdFixLookback

         static int MamaLookback( double        optInFastLimit, /* From 0.01 to 0.99 */
                                double        optInSlowLimit );  /* From 0.01 to 0.99 */

         static enum class RetCode Mama( int    startIdx,
                                         int    endIdx,
                                         cli::array<double>^ inReal,
                                         double        optInFastLimit, /* From 0.01 to 0.99 */
                                         double        optInSlowLimit, /* From 0.01 to 0.99 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outMAMA,
                                         cli::array<double>^  outFAMA );
         static enum class RetCode Mama( int    startIdx,
                                         int    endIdx,
                                         cli::array<float>^ inReal,
                                         double        optInFastLimit, /* From 0.01 to 0.99 */
                                         double        optInSlowLimit, /* From 0.01 to 0.99 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outMAMA,
                                         cli::array<double>^  outFAMA );

         #define TA_MAMA Core::Mama
         #define TA_MAMA_Lookback Core::MamaLookback

         static int MaxLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Max( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Max( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_MAX Core::Max
         #define TA_MAX_Lookback Core::MaxLookback

         static int MaxIndexLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode MaxIndex( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inReal,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<int>^  outInteger );
         static enum class RetCode MaxIndex( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inReal,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<int>^  outInteger );

         #define TA_MAXINDEX Core::MaxIndex
         #define TA_MAXINDEX_Lookback Core::MaxIndexLookback

         static int MedPriceLookback( void );

         static enum class RetCode MedPrice( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inHigh,
                                             cli::array<double>^ inLow,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );
         static enum class RetCode MedPrice( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inHigh,
                                             cli::array<float>^ inLow,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );

         #define TA_MEDPRICE Core::MedPrice
         #define TA_MEDPRICE_Lookback Core::MedPriceLookback

         static int MfiLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Mfi( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inHigh,
                                        cli::array<double>^ inLow,
                                        cli::array<double>^ inClose,
                                        cli::array<double>^ inVolume,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Mfi( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inHigh,
                                        cli::array<float>^ inLow,
                                        cli::array<float>^ inClose,
                                        cli::array<float>^ inVolume,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_MFI Core::Mfi
         #define TA_MFI_Lookback Core::MfiLookback

         static int MidPointLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode MidPoint( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inReal,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );
         static enum class RetCode MidPoint( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inReal,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );

         #define TA_MIDPOINT Core::MidPoint
         #define TA_MIDPOINT_Lookback Core::MidPointLookback

         static int MidPriceLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode MidPrice( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inHigh,
                                             cli::array<double>^ inLow,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );
         static enum class RetCode MidPrice( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inHigh,
                                             cli::array<float>^ inLow,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );

         #define TA_MIDPRICE Core::MidPrice
         #define TA_MIDPRICE_Lookback Core::MidPriceLookback

         static int MinLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Min( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Min( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_MIN Core::Min
         #define TA_MIN_Lookback Core::MinLookback

         static int MinIndexLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode MinIndex( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inReal,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<int>^  outInteger );
         static enum class RetCode MinIndex( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inReal,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<int>^  outInteger );

         #define TA_MININDEX Core::MinIndex
         #define TA_MININDEX_Lookback Core::MinIndexLookback

         static int MinMaxLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode MinMax( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outMin,
                                           cli::array<double>^  outMax );
         static enum class RetCode MinMax( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outMin,
                                           cli::array<double>^  outMax );

         #define TA_MINMAX Core::MinMax
         #define TA_MINMAX_Lookback Core::MinMaxLookback

         static int MinMaxIndexLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode MinMaxIndex( int    startIdx,
                                                int    endIdx,
                                                cli::array<double>^ inReal,
                                                int           optInTimePeriod, /* From 2 to 100000 */
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outMinIdx,
                                                cli::array<int>^  outMaxIdx );
         static enum class RetCode MinMaxIndex( int    startIdx,
                                                int    endIdx,
                                                cli::array<float>^ inReal,
                                                int           optInTimePeriod, /* From 2 to 100000 */
                                                [Out]int%    outBegIdx,
                                                [Out]int%    outNbElement,
                                                cli::array<int>^  outMinIdx,
                                                cli::array<int>^  outMaxIdx );

         #define TA_MINMAXINDEX Core::MinMaxIndex
         #define TA_MINMAXINDEX_Lookback Core::MinMaxIndexLookback

         static int MinusDILookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class RetCode MinusDI( int    startIdx,
                                            int    endIdx,
                                            cli::array<double>^ inHigh,
                                            cli::array<double>^ inLow,
                                            cli::array<double>^ inClose,
                                            int           optInTimePeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );
         static enum class RetCode MinusDI( int    startIdx,
                                            int    endIdx,
                                            cli::array<float>^ inHigh,
                                            cli::array<float>^ inLow,
                                            cli::array<float>^ inClose,
                                            int           optInTimePeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );

         #define TA_MINUS_DI Core::MinusDI
         #define TA_MINUS_DI_Lookback Core::MinusDILookback

         static int MinusDMLookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class RetCode MinusDM( int    startIdx,
                                            int    endIdx,
                                            cli::array<double>^ inHigh,
                                            cli::array<double>^ inLow,
                                            int           optInTimePeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );
         static enum class RetCode MinusDM( int    startIdx,
                                            int    endIdx,
                                            cli::array<float>^ inHigh,
                                            cli::array<float>^ inLow,
                                            int           optInTimePeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );

         #define TA_MINUS_DM Core::MinusDM
         #define TA_MINUS_DM_Lookback Core::MinusDMLookback

         static int MomLookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class RetCode Mom( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inReal,
                                        int           optInTimePeriod, /* From 1 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Mom( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inReal,
                                        int           optInTimePeriod, /* From 1 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_MOM Core::Mom
         #define TA_MOM_Lookback Core::MomLookback

         static int NatrLookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class RetCode Natr( int    startIdx,
                                         int    endIdx,
                                         cli::array<double>^ inHigh,
                                         cli::array<double>^ inLow,
                                         cli::array<double>^ inClose,
                                         int           optInTimePeriod, /* From 1 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );
         static enum class RetCode Natr( int    startIdx,
                                         int    endIdx,
                                         cli::array<float>^ inHigh,
                                         cli::array<float>^ inLow,
                                         cli::array<float>^ inClose,
                                         int           optInTimePeriod, /* From 1 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );

         #define TA_NATR Core::Natr
         #define TA_NATR_Lookback Core::NatrLookback

         static int ObvLookback( void );

         static enum class RetCode Obv( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inReal,
                                        cli::array<double>^ inVolume,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Obv( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inReal,
                                        cli::array<float>^ inVolume,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_OBV Core::Obv
         #define TA_OBV_Lookback Core::ObvLookback

         static int PlusDILookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class RetCode PlusDI( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inHigh,
                                           cli::array<double>^ inLow,
                                           cli::array<double>^ inClose,
                                           int           optInTimePeriod, /* From 1 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class RetCode PlusDI( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inHigh,
                                           cli::array<float>^ inLow,
                                           cli::array<float>^ inClose,
                                           int           optInTimePeriod, /* From 1 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_PLUS_DI Core::PlusDI
         #define TA_PLUS_DI_Lookback Core::PlusDILookback

         static int PlusDMLookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class RetCode PlusDM( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inHigh,
                                           cli::array<double>^ inLow,
                                           int           optInTimePeriod, /* From 1 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class RetCode PlusDM( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inHigh,
                                           cli::array<float>^ inLow,
                                           int           optInTimePeriod, /* From 1 to 100000 */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_PLUS_DM Core::PlusDM
         #define TA_PLUS_DM_Lookback Core::PlusDMLookback

         static int PpoLookback( int           optInFastPeriod, /* From 2 to 100000 */
                               int           optInSlowPeriod, /* From 2 to 100000 */
                               MAType        optInMAType ); 
         static enum class RetCode Ppo( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inReal,
                                        int           optInFastPeriod, /* From 2 to 100000 */
                                        int           optInSlowPeriod, /* From 2 to 100000 */
                                        MAType        optInMAType,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Ppo( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inReal,
                                        int           optInFastPeriod, /* From 2 to 100000 */
                                        int           optInSlowPeriod, /* From 2 to 100000 */
                                        MAType        optInMAType,
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_PPO Core::Ppo
         #define TA_PPO_Lookback Core::PpoLookback

         static int RocLookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class RetCode Roc( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inReal,
                                        int           optInTimePeriod, /* From 1 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Roc( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inReal,
                                        int           optInTimePeriod, /* From 1 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_ROC Core::Roc
         #define TA_ROC_Lookback Core::RocLookback

         static int RocPLookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class RetCode RocP( int    startIdx,
                                         int    endIdx,
                                         cli::array<double>^ inReal,
                                         int           optInTimePeriod, /* From 1 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );
         static enum class RetCode RocP( int    startIdx,
                                         int    endIdx,
                                         cli::array<float>^ inReal,
                                         int           optInTimePeriod, /* From 1 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );

         #define TA_ROCP Core::RocP
         #define TA_ROCP_Lookback Core::RocPLookback

         static int RocRLookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class RetCode RocR( int    startIdx,
                                         int    endIdx,
                                         cli::array<double>^ inReal,
                                         int           optInTimePeriod, /* From 1 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );
         static enum class RetCode RocR( int    startIdx,
                                         int    endIdx,
                                         cli::array<float>^ inReal,
                                         int           optInTimePeriod, /* From 1 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );

         #define TA_ROCR Core::RocR
         #define TA_ROCR_Lookback Core::RocRLookback

         static int RocR100Lookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class RetCode RocR100( int    startIdx,
                                            int    endIdx,
                                            cli::array<double>^ inReal,
                                            int           optInTimePeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );
         static enum class RetCode RocR100( int    startIdx,
                                            int    endIdx,
                                            cli::array<float>^ inReal,
                                            int           optInTimePeriod, /* From 1 to 100000 */
                                            [Out]int%    outBegIdx,
                                            [Out]int%    outNbElement,
                                            cli::array<double>^  outReal );

         #define TA_ROCR100 Core::RocR100
         #define TA_ROCR100_Lookback Core::RocR100Lookback

         static int RsiLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Rsi( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Rsi( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_RSI Core::Rsi
         #define TA_RSI_Lookback Core::RsiLookback

         static int SarLookback( double        optInAcceleration, /* From 0 to TA_REAL_MAX */
                               double        optInMaximum );  /* From 0 to TA_REAL_MAX */

         static enum class RetCode Sar( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inHigh,
                                        cli::array<double>^ inLow,
                                        double        optInAcceleration, /* From 0 to TA_REAL_MAX */
                                        double        optInMaximum, /* From 0 to TA_REAL_MAX */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Sar( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inHigh,
                                        cli::array<float>^ inLow,
                                        double        optInAcceleration, /* From 0 to TA_REAL_MAX */
                                        double        optInMaximum, /* From 0 to TA_REAL_MAX */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_SAR Core::Sar
         #define TA_SAR_Lookback Core::SarLookback

         static int SarExtLookback( double        optInStartValue, /* From TA_REAL_MIN to TA_REAL_MAX */
                                  double        optInOffsetOnReverse, /* From 0 to TA_REAL_MAX */
                                  double        optInAccelerationInitLong, /* From 0 to TA_REAL_MAX */
                                  double        optInAccelerationLong, /* From 0 to TA_REAL_MAX */
                                  double        optInAccelerationMaxLong, /* From 0 to TA_REAL_MAX */
                                  double        optInAccelerationInitShort, /* From 0 to TA_REAL_MAX */
                                  double        optInAccelerationShort, /* From 0 to TA_REAL_MAX */
                                  double        optInAccelerationMaxShort );  /* From 0 to TA_REAL_MAX */

         static enum class RetCode SarExt( int    startIdx,
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
         static enum class RetCode SarExt( int    startIdx,
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

         #define TA_SAREXT Core::SarExt
         #define TA_SAREXT_Lookback Core::SarExtLookback

         static int SmaLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Sma( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Sma( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_SMA Core::Sma
         #define TA_SMA_Lookback Core::SmaLookback

         static int StdDevLookback( int           optInTimePeriod, /* From 2 to 100000 */
                                  double        optInNbDev );  /* From TA_REAL_MIN to TA_REAL_MAX */

         static enum class RetCode StdDev( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           double        optInNbDev, /* From TA_REAL_MIN to TA_REAL_MAX */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );
         static enum class RetCode StdDev( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inReal,
                                           int           optInTimePeriod, /* From 2 to 100000 */
                                           double        optInNbDev, /* From TA_REAL_MIN to TA_REAL_MAX */
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outReal );

         #define TA_STDDEV Core::StdDev
         #define TA_STDDEV_Lookback Core::StdDevLookback

         static int StochLookback( int           optInFastK_Period, /* From 1 to 100000 */
                                 int           optInSlowK_Period, /* From 1 to 100000 */
                                 MAType        optInSlowK_MAType,
                                 int           optInSlowD_Period, /* From 1 to 100000 */
                                 MAType        optInSlowD_MAType ); 
         static enum class RetCode Stoch( int    startIdx,
                                          int    endIdx,
                                          cli::array<double>^ inHigh,
                                          cli::array<double>^ inLow,
                                          cli::array<double>^ inClose,
                                          int           optInFastK_Period, /* From 1 to 100000 */
                                          int           optInSlowK_Period, /* From 1 to 100000 */
                                          MAType        optInSlowK_MAType,
                                          int           optInSlowD_Period, /* From 1 to 100000 */
                                          MAType        optInSlowD_MAType,
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outSlowK,
                                          cli::array<double>^  outSlowD );
         static enum class RetCode Stoch( int    startIdx,
                                          int    endIdx,
                                          cli::array<float>^ inHigh,
                                          cli::array<float>^ inLow,
                                          cli::array<float>^ inClose,
                                          int           optInFastK_Period, /* From 1 to 100000 */
                                          int           optInSlowK_Period, /* From 1 to 100000 */
                                          MAType        optInSlowK_MAType,
                                          int           optInSlowD_Period, /* From 1 to 100000 */
                                          MAType        optInSlowD_MAType,
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outSlowK,
                                          cli::array<double>^  outSlowD );

         #define TA_STOCH Core::Stoch
         #define TA_STOCH_Lookback Core::StochLookback

         static int StochFLookback( int           optInFastK_Period, /* From 1 to 100000 */
                                  int           optInFastD_Period, /* From 1 to 100000 */
                                  MAType        optInFastD_MAType ); 
         static enum class RetCode StochF( int    startIdx,
                                           int    endIdx,
                                           cli::array<double>^ inHigh,
                                           cli::array<double>^ inLow,
                                           cli::array<double>^ inClose,
                                           int           optInFastK_Period, /* From 1 to 100000 */
                                           int           optInFastD_Period, /* From 1 to 100000 */
                                           MAType        optInFastD_MAType,
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outFastK,
                                           cli::array<double>^  outFastD );
         static enum class RetCode StochF( int    startIdx,
                                           int    endIdx,
                                           cli::array<float>^ inHigh,
                                           cli::array<float>^ inLow,
                                           cli::array<float>^ inClose,
                                           int           optInFastK_Period, /* From 1 to 100000 */
                                           int           optInFastD_Period, /* From 1 to 100000 */
                                           MAType        optInFastD_MAType,
                                           [Out]int%    outBegIdx,
                                           [Out]int%    outNbElement,
                                           cli::array<double>^  outFastK,
                                           cli::array<double>^  outFastD );

         #define TA_STOCHF Core::StochF
         #define TA_STOCHF_Lookback Core::StochFLookback

         static int StochRsiLookback( int           optInTimePeriod, /* From 2 to 100000 */
                                    int           optInFastK_Period, /* From 1 to 100000 */
                                    int           optInFastD_Period, /* From 1 to 100000 */
                                    MAType        optInFastD_MAType ); 
         static enum class RetCode StochRsi( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inReal,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             int           optInFastK_Period, /* From 1 to 100000 */
                                             int           optInFastD_Period, /* From 1 to 100000 */
                                             MAType        optInFastD_MAType,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outFastK,
                                             cli::array<double>^  outFastD );
         static enum class RetCode StochRsi( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inReal,
                                             int           optInTimePeriod, /* From 2 to 100000 */
                                             int           optInFastK_Period, /* From 1 to 100000 */
                                             int           optInFastD_Period, /* From 1 to 100000 */
                                             MAType        optInFastD_MAType,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outFastK,
                                             cli::array<double>^  outFastD );

         #define TA_STOCHRSI Core::StochRsi
         #define TA_STOCHRSI_Lookback Core::StochRsiLookback

         static int SumLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Sum( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Sum( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_SUM Core::Sum
         #define TA_SUM_Lookback Core::SumLookback

         static int T3Lookback( int           optInTimePeriod, /* From 2 to 100000 */
                              double        optInVFactor );  /* From 0 to 1 */

         static enum class RetCode T3( int    startIdx,
                                       int    endIdx,
                                       cli::array<double>^ inReal,
                                       int           optInTimePeriod, /* From 2 to 100000 */
                                       double        optInVFactor, /* From 0 to 1 */
                                       [Out]int%    outBegIdx,
                                       [Out]int%    outNbElement,
                                       cli::array<double>^  outReal );
         static enum class RetCode T3( int    startIdx,
                                       int    endIdx,
                                       cli::array<float>^ inReal,
                                       int           optInTimePeriod, /* From 2 to 100000 */
                                       double        optInVFactor, /* From 0 to 1 */
                                       [Out]int%    outBegIdx,
                                       [Out]int%    outNbElement,
                                       cli::array<double>^  outReal );

         #define TA_T3 Core::T3
         #define TA_T3_Lookback Core::T3Lookback

         static int TemaLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Tema( int    startIdx,
                                         int    endIdx,
                                         cli::array<double>^ inReal,
                                         int           optInTimePeriod, /* From 2 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );
         static enum class RetCode Tema( int    startIdx,
                                         int    endIdx,
                                         cli::array<float>^ inReal,
                                         int           optInTimePeriod, /* From 2 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );

         #define TA_TEMA Core::Tema
         #define TA_TEMA_Lookback Core::TemaLookback

         static int TrueRangeLookback( void );

         static enum class RetCode TrueRange( int    startIdx,
                                              int    endIdx,
                                              cli::array<double>^ inHigh,
                                              cli::array<double>^ inLow,
                                              cli::array<double>^ inClose,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outReal );
         static enum class RetCode TrueRange( int    startIdx,
                                              int    endIdx,
                                              cli::array<float>^ inHigh,
                                              cli::array<float>^ inLow,
                                              cli::array<float>^ inClose,
                                              [Out]int%    outBegIdx,
                                              [Out]int%    outNbElement,
                                              cli::array<double>^  outReal );

         #define TA_TRANGE Core::TrueRange
         #define TA_TRANGE_Lookback Core::TrueRangeLookback

         static int TrimaLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Trima( int    startIdx,
                                          int    endIdx,
                                          cli::array<double>^ inReal,
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outReal );
         static enum class RetCode Trima( int    startIdx,
                                          int    endIdx,
                                          cli::array<float>^ inReal,
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outReal );

         #define TA_TRIMA Core::Trima
         #define TA_TRIMA_Lookback Core::TrimaLookback

         static int TrixLookback( int           optInTimePeriod );  /* From 1 to 100000 */

         static enum class RetCode Trix( int    startIdx,
                                         int    endIdx,
                                         cli::array<double>^ inReal,
                                         int           optInTimePeriod, /* From 1 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );
         static enum class RetCode Trix( int    startIdx,
                                         int    endIdx,
                                         cli::array<float>^ inReal,
                                         int           optInTimePeriod, /* From 1 to 100000 */
                                         [Out]int%    outBegIdx,
                                         [Out]int%    outNbElement,
                                         cli::array<double>^  outReal );

         #define TA_TRIX Core::Trix
         #define TA_TRIX_Lookback Core::TrixLookback

         static int TsfLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Tsf( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Tsf( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_TSF Core::Tsf
         #define TA_TSF_Lookback Core::TsfLookback

         static int TypPriceLookback( void );

         static enum class RetCode TypPrice( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inHigh,
                                             cli::array<double>^ inLow,
                                             cli::array<double>^ inClose,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );
         static enum class RetCode TypPrice( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inHigh,
                                             cli::array<float>^ inLow,
                                             cli::array<float>^ inClose,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );

         #define TA_TYPPRICE Core::TypPrice
         #define TA_TYPPRICE_Lookback Core::TypPriceLookback

         static int UltOscLookback( int           optInTimePeriod1, /* From 1 to 100000 */
                                  int           optInTimePeriod2, /* From 1 to 100000 */
                                  int           optInTimePeriod3 );  /* From 1 to 100000 */

         static enum class RetCode UltOsc( int    startIdx,
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
         static enum class RetCode UltOsc( int    startIdx,
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

         #define TA_ULTOSC Core::UltOsc
         #define TA_ULTOSC_Lookback Core::UltOscLookback

         static int VarianceLookback( int           optInTimePeriod, /* From 1 to 100000 */
                                    double        optInNbDev );  /* From TA_REAL_MIN to TA_REAL_MAX */

         static enum class RetCode Variance( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inReal,
                                             int           optInTimePeriod, /* From 1 to 100000 */
                                             double        optInNbDev, /* From TA_REAL_MIN to TA_REAL_MAX */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );
         static enum class RetCode Variance( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inReal,
                                             int           optInTimePeriod, /* From 1 to 100000 */
                                             double        optInNbDev, /* From TA_REAL_MIN to TA_REAL_MAX */
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );

         #define TA_VAR Core::Variance
         #define TA_VAR_Lookback Core::VarianceLookback

         static int WclPriceLookback( void );

         static enum class RetCode WclPrice( int    startIdx,
                                             int    endIdx,
                                             cli::array<double>^ inHigh,
                                             cli::array<double>^ inLow,
                                             cli::array<double>^ inClose,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );
         static enum class RetCode WclPrice( int    startIdx,
                                             int    endIdx,
                                             cli::array<float>^ inHigh,
                                             cli::array<float>^ inLow,
                                             cli::array<float>^ inClose,
                                             [Out]int%    outBegIdx,
                                             [Out]int%    outNbElement,
                                             cli::array<double>^  outReal );

         #define TA_WCLPRICE Core::WclPrice
         #define TA_WCLPRICE_Lookback Core::WclPriceLookback

         static int WillRLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode WillR( int    startIdx,
                                          int    endIdx,
                                          cli::array<double>^ inHigh,
                                          cli::array<double>^ inLow,
                                          cli::array<double>^ inClose,
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outReal );
         static enum class RetCode WillR( int    startIdx,
                                          int    endIdx,
                                          cli::array<float>^ inHigh,
                                          cli::array<float>^ inLow,
                                          cli::array<float>^ inClose,
                                          int           optInTimePeriod, /* From 2 to 100000 */
                                          [Out]int%    outBegIdx,
                                          [Out]int%    outNbElement,
                                          cli::array<double>^  outReal );

         #define TA_WILLR Core::WillR
         #define TA_WILLR_Lookback Core::WillRLookback

         static int WmaLookback( int           optInTimePeriod );  /* From 2 to 100000 */

         static enum class RetCode Wma( int    startIdx,
                                        int    endIdx,
                                        cli::array<double>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );
         static enum class RetCode Wma( int    startIdx,
                                        int    endIdx,
                                        cli::array<float>^ inReal,
                                        int           optInTimePeriod, /* From 2 to 100000 */
                                        [Out]int%    outBegIdx,
                                        [Out]int%    outNbElement,
                                        cli::array<double>^  outReal );

         #define TA_WMA Core::Wma
         #define TA_WMA_Lookback Core::WmaLookback

/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/

  		   };
	   }
	}
}
