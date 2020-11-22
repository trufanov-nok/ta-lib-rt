/* TA-LIB Copyright (c) 1999-2008, Mario Fortier
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
 *  031202 MF   Template creation.
 *  052603 MF   Port to managed C++. Change to use CIRCBUF macros.
 *  061704 MF   Lower limit for period to 2, and correct algorithm
 *              to avoid cummulative error when value are close to
 *              the floating point epsilon.
 */

/**** START GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
/* All code within this section is automatically
 * generated by gen_code. Any modification will be lost
 * next time gen_code is run.
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */    #include "TA-Lib-Core.h"
/* Generated */    #define TA_INTERNAL_ERROR(Id) (RetCode::InternalError)
/* Generated */    namespace TicTacTec { namespace TA { namespace Library {
/* Generated */ #elif defined( _JAVA )
/* Generated */    #include "ta_defs.h"
/* Generated */    #include "ta_java_defs.h"
/* Generated */    #define TA_INTERNAL_ERROR(Id) (RetCode.InternalError)
/* Generated */ #else
/* Generated */    #include <string.h>
/* Generated */    #include <math.h>
/* Generated */    #include "ta_func.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_UTILITY_H
/* Generated */    #include "ta_utility.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_MEMORY_H
/* Generated */    #include "ta_memory.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #define TA_PREFIX(x) TA_##x
/* Generated */ #define INPUT_TYPE   double
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ int Core::CciLookback( int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #elif defined( _JAVA )
/* Generated */ public int cciLookback( int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #else
/* Generated */ TA_LIB_API int TA_CCI_Lookback( int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert local variable here */

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */    /* min/max are checked for optInTimePeriod. */
/* Generated */    if( (int)optInTimePeriod == TA_INTEGER_DEFAULT )
/* Generated */       optInTimePeriod = 14;
/* Generated */    else if( ((int)optInTimePeriod < 2) || ((int)optInTimePeriod > 100000) )
/* Generated */       return -1;
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/**** END GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/

   /* insert lookback code here. */
   return (optInTimePeriod-1);
}

/**** START GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/
/*
 * TA_CCI - Commodity Channel Index
 * 
 * Input  = High, Low, Close
 * Output = double
 * 
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 *    Number of period
 * 
 * 
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED ) && defined( USE_SUBARRAY )
/* Generated */ enum class Core::RetCode Core::Cci( int    startIdx,
/* Generated */                                     int    endIdx,
/* Generated */                                     SubArray<double>^ inHigh,
/* Generated */                                     SubArray<double>^ inLow,
/* Generated */                                     SubArray<double>^ inClose,
/* Generated */                                     int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                     [Out]int%    outBegIdx,
/* Generated */                                     [Out]int%    outNBElement,
/* Generated */                                     SubArray<double>^  outReal )
/* Generated */ #elif defined( _MANAGED )
/* Generated */ enum class Core::RetCode Core::Cci( int    startIdx,
/* Generated */                                     int    endIdx,
/* Generated */                                     cli::array<double>^ inHigh,
/* Generated */                                     cli::array<double>^ inLow,
/* Generated */                                     cli::array<double>^ inClose,
/* Generated */                                     int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                     [Out]int%    outBegIdx,
/* Generated */                                     [Out]int%    outNBElement,
/* Generated */                                     cli::array<double>^  outReal )
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode cci( int    startIdx,
/* Generated */                     int    endIdx,
/* Generated */                     double       inHigh[],
/* Generated */                     double       inLow[],
/* Generated */                     double       inClose[],
/* Generated */                     int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                     MInteger     outBegIdx,
/* Generated */                     MInteger     outNBElement,
/* Generated */                     double        outReal[] )
/* Generated */ #else
/* Generated */ TA_LIB_API TA_RetCode TA_CCI( int    startIdx,
/* Generated */                               int    endIdx,
/* Generated */                                          const double inHigh[],
/* Generated */                                          const double inLow[],
/* Generated */                                          const double inClose[],
/* Generated */                                          int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                          int          *outBegIdx,
/* Generated */                                          int          *outNBElement,
/* Generated */                                          double        outReal[] )
/* Generated */ #endif
/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/
{

	/* insert local variable here */
   double tempReal, tempReal2, theAverage, lastValue;
   int i, j, outIdx, lookbackTotal;

   /* This ptr will points on a circular buffer of
    * at least "optInTimePeriod" element.
    */
   CIRCBUF_PROLOG(circBuffer,double,30);

/**** START GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */    /* Validate the requested output range. */
/* Generated */    if( startIdx < 0 )
/* Generated */       return ENUM_VALUE(RetCode,TA_OUT_OF_RANGE_START_INDEX,OutOfRangeStartIndex);
/* Generated */    if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */       return ENUM_VALUE(RetCode,TA_OUT_OF_RANGE_END_INDEX,OutOfRangeEndIndex);
/* Generated */ 
/* Generated */    #if !defined(_JAVA)
/* Generated */    /* Verify required price component. */
/* Generated */    if(!inHigh||!inLow||!inClose)
/* Generated */       return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */ 
/* Generated */    #endif /* !defined(_JAVA)*/
/* Generated */    /* min/max are checked for optInTimePeriod. */
/* Generated */    if( (int)optInTimePeriod == TA_INTEGER_DEFAULT )
/* Generated */       optInTimePeriod = 14;
/* Generated */    else if( ((int)optInTimePeriod < 2) || ((int)optInTimePeriod > 100000) )
/* Generated */       return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */ 
/* Generated */    #if !defined(_JAVA)
/* Generated */    if( !outReal )
/* Generated */       return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */ 
/* Generated */    #endif /* !defined(_JAVA) */
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/

   /* Insert TA function code here. */
   
   /* Identify the minimum number of price bar needed
    * to calculate at least one output.
    */
   lookbackTotal = (optInTimePeriod-1);

   /* Move up the start index if there is not
    * enough initial data.
    */
   if( startIdx < lookbackTotal )
      startIdx = lookbackTotal;

   /* Make sure there is still something to evaluate. */
   if( startIdx > endIdx )
   {
      VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
      VALUE_HANDLE_DEREF_TO_ZERO(outNBElement);
      return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
   }

   /* Allocate a circular buffer equal to the requested
    * period.
    */
   CIRCBUF_INIT( circBuffer, double, optInTimePeriod );
  
   /* Do the MA calculation using tight loops. */

   /* Add-up the initial period, except for the last value. 
    * Fill up the circular buffer at the same time.
    */
   i=startIdx-lookbackTotal;
   if( optInTimePeriod > 1 )
   {
      while( i < startIdx )
      {
         circBuffer[circBuffer_Idx] = (inHigh[i]+inLow[i]+inClose[i])/3;
         i++;
         CIRCBUF_NEXT(circBuffer);
      }
   }

   /* Proceed with the calculation for the requested range.
    * Note that this algorithm allows the inReal and
    * outReal to be the same buffer.
    */
   outIdx = 0;
   do
   {
      lastValue = (inHigh[i]+inLow[i]+inClose[i])/3;
      circBuffer[circBuffer_Idx] = lastValue;

      /* Calculate the average for the whole period. */
      theAverage = 0;
      for( j=0; j < optInTimePeriod; j++ )
         theAverage += circBuffer[j];
      theAverage /= optInTimePeriod;

      /* Do the summation of the ABS(TypePrice-average)
       * for the whole period.
       */
      tempReal2 = 0;
      for( j=0; j < optInTimePeriod; j++ )
         tempReal2 += std_fabs(circBuffer[j]-theAverage);

      /* And finally, the CCI... */
      tempReal = lastValue-theAverage;

      if( (tempReal != 0.0) && (tempReal2 != 0.0) )
      {
         outReal[outIdx++] = tempReal/(0.015*(tempReal2/optInTimePeriod));
      }
      else
         outReal[outIdx++] = 0.0;
      
      /* Move forward the circular buffer indexes. */
      CIRCBUF_NEXT(circBuffer);

      i++;
   } while( i <= endIdx );

   /* All done. Indicate the output limits and return. */
   VALUE_HANDLE_DEREF(outNBElement) = outIdx;
   VALUE_HANDLE_DEREF(outBegIdx)    = startIdx;

   /* Free the circular buffer if it was dynamically allocated. */
   CIRCBUF_DESTROY(circBuffer);

   return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
}

#ifndef TA_CCI_STATE_CIRCBUF_DEFINED
#define TA_CCI_STATE_CIRCBUF_DEFINED
DEFINE_CIRCBUF_STRUCT(CCI, double)
#endif

/**** START GENCODE SECTION 5 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ Core::RetCode Core::CciStateInit( struct TA_Cci_State** _state,
/* Generated */                                 int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode cciStateInit( struct TA_cci_State** _state,
/* Generated */                            int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #else
/* Generated */ TA_LIB_API TA_RetCode TA_CCI_StateInit( struct TA_CCI_State** _state,
/* Generated */                                                  int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 5 - DO NOT DELETE THIS LINE ****/

{
   /* insert local variable here */
#define TA_CCI_SUPPRESS_MEMORY_ALLOCATION
/**** START GENCODE SECTION 6 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */    if (_state == NULL)
/* Generated */          return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */    /* min/max are checked for optInTimePeriod. */
/* Generated */    if( (int)optInTimePeriod == TA_INTEGER_DEFAULT )
/* Generated */       optInTimePeriod = 14;
/* Generated */    else if( ((int)optInTimePeriod < 2) || ((int)optInTimePeriod > 100000) )
/* Generated */       return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */ 
/* Generated */    STATE = TA_Calloc(1, sizeof(struct TA_CCI_State));
/* Generated */    STATE_P.mem_index = 0;
/* Generated */    STATE_P.optInTimePeriod = optInTimePeriod;
/* Generated */    MEM_SIZE_P = TA_CCI_Lookback(optInTimePeriod );
/* Generated */    #ifndef TA_CCI_SUPPRESS_MEMORY_ALLOCATION
/* Generated */    if (MEM_SIZE_P > 0)
/* Generated */          MEM_P = TA_Calloc(MEM_SIZE_P, sizeof(struct TA_CCI_Data));
/* Generated */    else
/* Generated */    #endif
/* Generated */          MEM_P = NULL;/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 6 - DO NOT DELETE THIS LINE ****/

   /* insert state init code here. */

   CREATE_CIRCBUF_STRUCT(CCI, circBuf, double, optInTimePeriod-1);
   STATE_P.theAverage = 0.;
   return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
}

/**** START GENCODE SECTION 7 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ Core::RetCode Core::CciState( struct TA_Cci_State* _state,
/* Generated */                             cli::array<double>^ inHigh,
/* Generated */                             cli::array<double>^ inLow,
/* Generated */                             cli::array<double>^ inClose,
/* Generated */                             cli::array<double>^  *outReal )
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode cciState( struct TA_cci_State* _state,
/* Generated */                        double       inHigh,
/* Generated */                        double       inLow,
/* Generated */                        double       inClose,
/* Generated */                        double        *outReal )
/* Generated */ #else
/* Generated */ TA_LIB_API TA_RetCode TA_CCI_State( struct TA_CCI_State* _state,
/* Generated */                                              const double inHigh,
/* Generated */                                              const double inLow,
/* Generated */                                              const double inClose,
/* Generated */                                              double        *outReal )
/* Generated */ #endif
/**** END GENCODE SECTION 7 - DO NOT DELETE THIS LINE ****/
{
   /* insert local variable here */
#define TA_CCI_SUPPRESS_EXIT_ON_NOT_ENOUGH_DATA
int i;
double lastValue, sum, avg;
/**** START GENCODE SECTION 8 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */    if (_state == NULL)
/* Generated */          return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */    #if !defined(_JAVA)
/* Generated */    #endif /* !defined(_JAVA)*/
/* Generated */    size_t _cur_idx = STATE.mem_index++;
/* Generated */    if (MEM_SIZE > 0) _cur_idx %= MEM_SIZE;
/* Generated */    UNUSED_VARIABLE(_cur_idx); // in case PUSH\POP methods won't be used
/* Generated */    #ifndef TA_CCI_SUPPRESS_EXIT_ON_NOT_ENOUGH_DATA
/* Generated */    if (NEED_MORE_DATA) {
/* Generated */          PUSH_TO_MEM(inHigh,inHigh);
/* Generated */          PUSH_TO_MEM(inLow,inLow);
/* Generated */          PUSH_TO_MEM(inClose,inClose);
/* Generated */    return ENUM_VALUE(RetCode,TA_NEED_MORE_DATA,NeedMoreData); }
/* Generated */    #endif
/* Generated */    #if !defined(_JAVA)
/* Generated */    if( !outReal )
/* Generated */       return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */ 
/* Generated */    #endif /* !defined(_JAVA) */
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 8 - DO NOT DELETE THIS LINE ****/

   /* insert state based TA func code here. */
   lastValue = (inHigh+inLow+inClose) / 3.0;

   STATE.theAverage += lastValue;

   if (NEED_MORE_DATA)
   {
        CIRCBUF_STRUCT_CURRENT_EL(CCI, circBuf) = lastValue;
        CIRCBUF_STRUCT_NEXT( CCI, circBuf);
        return ENUM_VALUE(RetCode,TA_NEED_MORE_DATA,NeedMoreData);
   }

   sum = 0;
   avg = STATE.theAverage / STATE.optInTimePeriod;

   STATE.theAverage -= CIRCBUF_STRUCT_CURRENT_EL(CCI, circBuf);

   for( i=0; i < CIRCBUF_STRUCT_SIZE(CCI, circBuf); i++ )
      sum += std_fabs(CIRCBUF_STRUCT_EL(CCI, circBuf, i) - avg);
   sum += std_fabs(lastValue - avg);

   CIRCBUF_STRUCT_CURRENT_EL(CCI, circBuf) = lastValue;

   lastValue -= avg;

   if( (std_fabs(lastValue) > 1e-13) && (std_fabs(sum) > 1e-13) )
   {
      VALUE_HANDLE_DEREF(outReal) = lastValue/(0.015*(sum/STATE.optInTimePeriod));
   }
   else
       VALUE_HANDLE_DEREF(outReal) = 0.0;

   CIRCBUF_STRUCT_NEXT( CCI, circBuf);
   return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
}

/**** START GENCODE SECTION 9 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ Core::RetCode Core::CciBatchState( struct TA_Cci_State* _state,
/* Generated */                                  int startIdx,
/* Generated */                                  int endIdx,
/* Generated */                                  cli::array<double>^ inHigh,
/* Generated */                                  cli::array<double>^ inLow,
/* Generated */                                  cli::array<double>^ inClose,
/* Generated */                                  [Out]int%    outBegIdx,
/* Generated */                                  [Out]int%    outNBElement,
/* Generated */                                  cli::array<double>^  outReal )
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode cciBatchState( struct TA_cci_State* _state,
/* Generated */                             int startIdx,
/* Generated */                             int endIdx,
/* Generated */                             double       inHigh[],
/* Generated */                             double       inLow[],
/* Generated */                             double       inClose[],
/* Generated */                             MInteger     outBegIdx,
/* Generated */                             MInteger     outNBElement,
/* Generated */                             double        outReal[] )
/* Generated */ #else
/* Generated */ TA_LIB_API TA_RetCode TA_CCI_BatchState( struct TA_CCI_State* _state,
/* Generated */                                                   int startIdx,
/* Generated */                                                   int endIdx,
/* Generated */                                                   const double inHigh[],
/* Generated */                                                   const double inLow[],
/* Generated */                                                   const double inClose[],
/* Generated */                                                   int          *outBegIdx,
/* Generated */                                                   int          *outNBElement,
/* Generated */                                                   double        outReal[] )
/* Generated */ #endif
/**** END GENCODE SECTION 9 - DO NOT DELETE THIS LINE ****/

{
  /* insert local variable here */

/**** START GENCODE SECTION 10 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_OVERWRITE_BATCH_STATE_CODE
/* Generated */ 
/* Generated */    if (_state == NULL)
/* Generated */          return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */    #if !defined(_JAVA)
/* Generated */    /* Verify required price component. */
/* Generated */    if(!inHigh||!inLow||!inClose)
/* Generated */       return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */ 
/* Generated */    #endif /* !defined(_JAVA)*/
/* Generated */    #if !defined(_JAVA)
/* Generated */    if( !outReal )
/* Generated */       return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */ 
/* Generated */    #endif /* !defined(_JAVA) */
/* Generated */    /* Make sure there is still something to evaluate. */
/* Generated */    if( startIdx > endIdx )
/* Generated */    {
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outNBElement);
/* Generated */       return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
/* Generated */    }
/* Generated */    
/* Generated */    
/* Generated */    double outRealVal;
/* Generated */    int retValue;
/* Generated */    
/* Generated */    int outIdx = 0;
/* Generated */    VALUE_HANDLE_DEREF(outBegIdx)  = startIdx;
/* Generated */    
/* Generated */    for (int i = startIdx; i <= endIdx; ++i, outIdx++) {
/* Generated */       retValue = TA_CCI_State( _state, inHigh[i], inLow[i], inClose[i], &outRealVal );
/* Generated */       if ( retValue == ENUM_VALUE(RetCode,TA_SUCCESS,Success) ) {
/* Generated */          outReal[outIdx] = outRealVal;
/* Generated */       } else if ( retValue == ENUM_VALUE(RetCode,TA_NEED_MORE_DATA,NeedMoreData) ) {
/* Generated */          outReal[outIdx] = NAN;
/* Generated */       } else {
/* Generated */          break;
/* Generated */        }
/* Generated */    }
/* Generated */    
/* Generated */    VALUE_HANDLE_DEREF(outNBElement) = outIdx;
/* Generated */ #endif /* TA_OVERWRITE_BATCH_STATE_CODE */
/* Generated */ 
/**** END GENCODE SECTION 10 - DO NOT DELETE THIS LINE ****/

  /* insert batch state code here. */
  return retValue;
}

/**** START GENCODE SECTION 11 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ Core::RetCode Core::CciStateFree( struct TA_Cci_State** _state )
/* Generated */ 
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode cciStateFree( struct TA_cci_State** _state )
/* Generated */ 
/* Generated */ #else
/* Generated */ TA_LIB_API TA_RetCode TA_CCI_StateFree( struct TA_CCI_State** _state )
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 9 - DO NOT DELETE THIS LINE ****/
{
   /* insert local variable here */
  FREE_CIRCBUF_STRUCT(CCI, circBuf);
/**** START GENCODE SECTION 10 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */    if (_state == NULL)
/* Generated */          return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */    if (STATE != NULL) {
/* Generated */          if (MEM_P != NULL) TA_Free(MEM_P);
/* Generated */          TA_Free(STATE); STATE = NULL;}
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 10 - DO NOT DELETE THIS LINE ****/

   /* insert state free code here. */   
   return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
}

/**** START GENCODE SECTION 11 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ Core::RetCode Core::CciStateSave( struct TA_Cci_State* _state,
/* Generated */                                 FILE* _file )
/* Generated */ 
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode cciStateSave( struct TA_cci_State* _state,
/* Generated */                            FILE* _file )
/* Generated */ 
/* Generated */ #else
/* Generated */ TA_LIB_API TA_RetCode TA_CCI_StateSave( struct TA_CCI_State* _state,
/* Generated */                                                  FILE* _file )
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 11 - DO NOT DELETE THIS LINE ****/

{
   /* insert local variable here */

/**** START GENCODE SECTION 12 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */     int io_res; int state_is_null; state_is_null = (_state == NULL);
/* Generated */    io_res = fwrite(&state_is_null,sizeof(state_is_null),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    if (state_is_null) return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
/* Generated */    io_res = fwrite(&STATE.mem_index,sizeof(STATE.mem_index),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    io_res = fwrite(&STATE.mem_size,sizeof(STATE.mem_size),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    int memory_allocated;
/* Generated */    memory_allocated = STATE.memory != NULL;
/* Generated */    io_res = fwrite(&memory_allocated,sizeof(memory_allocated),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    if (memory_allocated && STATE.mem_size > 0) { io_res = fwrite(STATE.memory,sizeof(struct TA_CCI_Data),STATE.mem_size,_file);
/* Generated */    if (io_res < (int) STATE.mem_size) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed); }
/* Generated */    io_res = fwrite(&STATE.optInTimePeriod,sizeof(STATE.optInTimePeriod),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    // Warning: STATE.circBuf must be saved manually!
/* Generated */    io_res = fwrite(&STATE.theAverage,sizeof(STATE.theAverage),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 12 - DO NOT DELETE THIS LINE ****/

   /* insert state save code here. */   
      CIRCBUF_STRUCT_SAVE(CCI, circBuf, double)

   return 0;
}

/**** START GENCODE SECTION 13 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ Core::RetCode Core::CciStateLoad( struct TA_Cci_State** _state,
/* Generated */                                 FILE* _file )
/* Generated */ 
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode cciStateLoad( struct TA_cci_State** _state,
/* Generated */                            FILE* _file )
/* Generated */ 
/* Generated */ #else
/* Generated */ TA_LIB_API TA_RetCode TA_CCI_StateLoad( struct TA_CCI_State** _state,
/* Generated */                                                  FILE* _file )
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 13 - DO NOT DELETE THIS LINE ****/
{
   /* insert local variable here */

/**** START GENCODE SECTION 14 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */    int io_res; int state_is_null;
/* Generated */    io_res = fread(&state_is_null,sizeof(state_is_null),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    if (state_is_null) return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
/* Generated */    if (STATE != NULL) return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */    STATE = TA_Calloc(1, sizeof(struct TA_CCI_State));
/* Generated */    io_res = fread(&STATE_P.mem_index,sizeof(STATE_P.mem_index),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    io_res = fread(&STATE_P.mem_size,sizeof(STATE_P.mem_size),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    int memory_allocated;
/* Generated */    io_res = fread(&memory_allocated,sizeof(memory_allocated),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    if (STATE_P.mem_size > 0 && memory_allocated) { STATE_P.memory = TA_Calloc(STATE_P.mem_size, sizeof(struct TA_CCI_Data));
/* Generated */    io_res = fread(STATE_P.memory,sizeof(struct TA_CCI_Data),STATE_P.mem_size,_file);
/* Generated */    if (io_res < (int) STATE_P.mem_size) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed); } 
/* Generated */    io_res = fread(&STATE_P.optInTimePeriod,sizeof(STATE_P.optInTimePeriod),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    // Warning: STATE_P.circBuf must be loaded manually!
/* Generated */    io_res = fread(&STATE_P.theAverage,sizeof(STATE_P.theAverage),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 14 - DO NOT DELETE THIS LINE ****/

   /* insert state load code here. */
        CIRCBUF_STRUCT_LOAD(CCI, circBuf, double)
   return 0;
}

/**** START GENCODE SECTION 15 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #define  USE_SINGLE_PRECISION_INPUT
/* Generated */ #undef  TA_LIB_PRO
/* Generated */ #if !defined( _MANAGED ) && !defined( _JAVA )
/* Generated */    #undef   TA_PREFIX
/* Generated */    #define  TA_PREFIX(x) TA_S_##x
/* Generated */ #endif
/* Generated */ #undef   INPUT_TYPE
/* Generated */ #define  INPUT_TYPE float
/* Generated */ #if defined( _MANAGED ) && defined( USE_SUBARRAY )
/* Generated */ enum class Core::RetCode Core::Cci( int    startIdx,
/* Generated */                                     int    endIdx,
/* Generated */                                     SubArray<float>^ inHigh,
/* Generated */                                     SubArray<float>^ inLow,
/* Generated */                                     SubArray<float>^ inClose,
/* Generated */                                     int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                     [Out]int%    outBegIdx,
/* Generated */                                     [Out]int%    outNBElement,
/* Generated */                                     SubArray<double>^  outReal )
/* Generated */ #elif defined( _MANAGED )
/* Generated */ enum class Core::RetCode Core::Cci( int    startIdx,
/* Generated */                                     int    endIdx,
/* Generated */                                     cli::array<float>^ inHigh,
/* Generated */                                     cli::array<float>^ inLow,
/* Generated */                                     cli::array<float>^ inClose,
/* Generated */                                     int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                     [Out]int%    outBegIdx,
/* Generated */                                     [Out]int%    outNBElement,
/* Generated */                                     cli::array<double>^  outReal )
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode cci( int    startIdx,
/* Generated */                     int    endIdx,
/* Generated */                     float        inHigh[],
/* Generated */                     float        inLow[],
/* Generated */                     float        inClose[],
/* Generated */                     int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                     MInteger     outBegIdx,
/* Generated */                     MInteger     outNBElement,
/* Generated */                     double        outReal[] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_S_CCI( int    startIdx,
/* Generated */                      int    endIdx,
/* Generated */                      const float  inHigh[],
/* Generated */                      const float  inLow[],
/* Generated */                      const float  inClose[],
/* Generated */                      int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                      int          *outBegIdx,
/* Generated */                      int          *outNBElement,
/* Generated */                      double        outReal[] )
/* Generated */ #endif
/* Generated */ {
/* Generated */    double tempReal, tempReal2, theAverage, lastValue;
/* Generated */    int i, j, outIdx, lookbackTotal;
/* Generated */    CIRCBUF_PROLOG(circBuffer,double,30);
/* Generated */  #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */     if( startIdx < 0 )
/* Generated */        return ENUM_VALUE(RetCode,TA_OUT_OF_RANGE_START_INDEX,OutOfRangeStartIndex);
/* Generated */     if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */        return ENUM_VALUE(RetCode,TA_OUT_OF_RANGE_END_INDEX,OutOfRangeEndIndex);
/* Generated */     #if !defined(_JAVA)
/* Generated */     if(!inHigh||!inLow||!inClose)
/* Generated */        return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */     #endif 
/* Generated */     if( (int)optInTimePeriod == TA_INTEGER_DEFAULT )
/* Generated */        optInTimePeriod = 14;
/* Generated */     else if( ((int)optInTimePeriod < 2) || ((int)optInTimePeriod > 100000) )
/* Generated */        return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */     #if !defined(_JAVA)
/* Generated */     if( !outReal )
/* Generated */        return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */     #endif 
/* Generated */  #endif 
/* Generated */    lookbackTotal = (optInTimePeriod-1);
/* Generated */    if( startIdx < lookbackTotal )
/* Generated */       startIdx = lookbackTotal;
/* Generated */    if( startIdx > endIdx )
/* Generated */    {
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outNBElement);
/* Generated */       return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
/* Generated */    }
/* Generated */    CIRCBUF_INIT( circBuffer, double, optInTimePeriod );
/* Generated */    i=startIdx-lookbackTotal;
/* Generated */    if( optInTimePeriod > 1 )
/* Generated */    {
/* Generated */       while( i < startIdx )
/* Generated */       {
/* Generated */          circBuffer[circBuffer_Idx] = (inHigh[i]+inLow[i]+inClose[i])/3;
/* Generated */          i++;
/* Generated */          CIRCBUF_NEXT(circBuffer);
/* Generated */       }
/* Generated */    }
/* Generated */    outIdx = 0;
/* Generated */    do
/* Generated */    {
/* Generated */       lastValue = (inHigh[i]+inLow[i]+inClose[i])/3;
/* Generated */       circBuffer[circBuffer_Idx] = lastValue;
/* Generated */       theAverage = 0;
/* Generated */       for( j=0; j < optInTimePeriod; j++ )
/* Generated */          theAverage += circBuffer[j];
/* Generated */       theAverage /= optInTimePeriod;
/* Generated */       tempReal2 = 0;
/* Generated */       for( j=0; j < optInTimePeriod; j++ )
/* Generated */          tempReal2 += std_fabs(circBuffer[j]-theAverage);
/* Generated */       tempReal = lastValue-theAverage;
/* Generated */       if( (tempReal != 0.0) && (tempReal2 != 0.0) )
/* Generated */       {
/* Generated */          outReal[outIdx++] = tempReal/(0.015*(tempReal2/optInTimePeriod));
/* Generated */       }
/* Generated */       else
/* Generated */          outReal[outIdx++] = 0.0;
/* Generated */       CIRCBUF_NEXT(circBuffer);
/* Generated */       i++;
/* Generated */    } while( i <= endIdx );
/* Generated */    VALUE_HANDLE_DEREF(outNBElement) = outIdx;
/* Generated */    VALUE_HANDLE_DEREF(outBegIdx)    = startIdx;
/* Generated */    CIRCBUF_DESTROY(circBuffer);
/* Generated */    return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
/* Generated */ }
/* Generated */ #ifndef TA_CCI_STATE_CIRCBUF_DEFINED
/* Generated */ #define TA_CCI_STATE_CIRCBUF_DEFINED
/* Generated */ DEFINE_CIRCBUF_STRUCT(CCI, double)
/* Generated */ #endif
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ }}} // Close namespace TicTacTec.TA.Lib
/* Generated */ #endif
/**** END GENCODE SECTION 15 - DO NOT DELETE THIS LINE ****/

