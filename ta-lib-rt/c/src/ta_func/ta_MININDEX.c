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
 *  AC       Angelo Ciceri
 *
 * Change history:
 *
 *  MMDDYY BY   Description
 *  -------------------------------------------------------------------
 *  120806 AC   Creation (equal to MIN but outputs index)
 *
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
/* Generated */ int Core::MinIndexLookback( int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #elif defined( _JAVA )
/* Generated */ public int minIndexLookback( int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #else
/* Generated */ TA_LIB_API int TA_MININDEX_Lookback( int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert local variable here */

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */    /* min/max are checked for optInTimePeriod. */
/* Generated */    if( (int)optInTimePeriod == TA_INTEGER_DEFAULT )
/* Generated */       optInTimePeriod = 30;
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
 * TA_MININDEX - Index of lowest value over a specified period
 * 
 * Input  = double
 * Output = int
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
/* Generated */ enum class Core::RetCode Core::MinIndex( int    startIdx,
/* Generated */                                          int    endIdx,
/* Generated */                                          SubArray<double>^ inReal,
/* Generated */                                          int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                          [Out]int%    outBegIdx,
/* Generated */                                          [Out]int%    outNBElement,
/* Generated */                                          SubArray<int>^  outInteger )
/* Generated */ #elif defined( _MANAGED )
/* Generated */ enum class Core::RetCode Core::MinIndex( int    startIdx,
/* Generated */                                          int    endIdx,
/* Generated */                                          cli::array<double>^ inReal,
/* Generated */                                          int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                          [Out]int%    outBegIdx,
/* Generated */                                          [Out]int%    outNBElement,
/* Generated */                                          cli::array<int>^  outInteger )
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode minIndex( int    startIdx,
/* Generated */                          int    endIdx,
/* Generated */                          double       inReal[],
/* Generated */                          int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                          MInteger     outBegIdx,
/* Generated */                          MInteger     outNBElement,
/* Generated */                          int           outInteger[] )
/* Generated */ #else
/* Generated */ TA_LIB_API TA_RetCode TA_MININDEX( int    startIdx,
/* Generated */                                    int    endIdx,
/* Generated */                                               const double inReal[],
/* Generated */                                               int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                               int          *outBegIdx,
/* Generated */                                               int          *outNBElement,
/* Generated */                                               int           outInteger[] )
/* Generated */ #endif
/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/
{
   /* Insert local variables here. */
   double lowest, tmp;
   int outIdx, nbInitialElementNeeded;
   int trailingIdx, lowestIdx, today, i;

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
/* Generated */    if( !inReal ) return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */    #endif /* !defined(_JAVA)*/
/* Generated */    /* min/max are checked for optInTimePeriod. */
/* Generated */    if( (int)optInTimePeriod == TA_INTEGER_DEFAULT )
/* Generated */       optInTimePeriod = 30;
/* Generated */    else if( ((int)optInTimePeriod < 2) || ((int)optInTimePeriod > 100000) )
/* Generated */       return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */ 
/* Generated */    #if !defined(_JAVA)
/* Generated */    if( !outInteger )
/* Generated */       return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */ 
/* Generated */    #endif /* !defined(_JAVA) */
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/

   /* Insert TA function code here. */

   /* Identify the minimum number of price bar needed
    * to identify at least one output over the specified
    * period.
    */
   nbInitialElementNeeded = (optInTimePeriod-1);

   /* Move up the start index if there is not
    * enough initial data.
    */
   if( startIdx < nbInitialElementNeeded )
      startIdx = nbInitialElementNeeded;

   /* Make sure there is still something to evaluate. */
   if( startIdx > endIdx )
   {
      VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
      VALUE_HANDLE_DEREF_TO_ZERO(outNBElement);
      return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
   }

   /* Proceed with the calculation for the requested range.
    * Note that this algorithm allows the input and
    * output to be the same buffer.
    */
   outIdx = 0;
   today       = startIdx;
   trailingIdx = startIdx-nbInitialElementNeeded;
   lowestIdx   = -1;
   lowest      = 0.0;
   
   while( today <= endIdx )
   {
      tmp = inReal[today];

      if( lowestIdx < trailingIdx )
      {
        lowestIdx = trailingIdx;
        lowest = inReal[lowestIdx];
        i = lowestIdx;
        while( ++i<=today )
        {
           tmp = inReal[i];
           if( tmp < lowest )
           {
              lowestIdx = i;
              lowest = tmp;
           }
        }
      }
      else if( tmp <= lowest )
      {
        lowestIdx = today;
        lowest = tmp;
      }

      outInteger[outIdx++] = lowestIdx;
      trailingIdx++;
      today++;  
   }

   /* Keep the outBegIdx relative to the
    * caller input before returning.
    */
   VALUE_HANDLE_DEREF(outBegIdx)    = startIdx;
   VALUE_HANDLE_DEREF(outNBElement) = outIdx;

   return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
}

/**** START GENCODE SECTION 5 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ Core::RetCode Core::MinIndexStateInit( struct TA_MinIndex_State** _state,
/* Generated */                                      int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode minIndexStateInit( struct TA_minIndex_State** _state,
/* Generated */                                 int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #else
/* Generated */ TA_LIB_API TA_RetCode TA_MININDEX_StateInit( struct TA_MININDEX_State** _state,
/* Generated */                                                       int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 5 - DO NOT DELETE THIS LINE ****/

{
   /* insert local variable here */
   #define TA_MININDEX_SUPPRESS_MEMORY_ALLOCATION
/**** START GENCODE SECTION 6 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */    if (_state == NULL)
/* Generated */          return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */    /* min/max are checked for optInTimePeriod. */
/* Generated */    if( (int)optInTimePeriod == TA_INTEGER_DEFAULT )
/* Generated */       optInTimePeriod = 30;
/* Generated */    else if( ((int)optInTimePeriod < 2) || ((int)optInTimePeriod > 100000) )
/* Generated */       return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */ 
/* Generated */    STATE = TA_Calloc(1, sizeof(struct TA_MININDEX_State));
/* Generated */    STATE_P.mem_index = 0;
/* Generated */    STATE_P.optInTimePeriod = optInTimePeriod;
/* Generated */    MEM_SIZE_P = TA_MININDEX_Lookback(optInTimePeriod );
/* Generated */    #ifndef TA_MININDEX_SUPPRESS_MEMORY_ALLOCATION
/* Generated */    if (MEM_SIZE_P > 0)
/* Generated */          MEM_P = TA_Calloc(MEM_SIZE_P, sizeof(struct TA_MININDEX_Data));
/* Generated */    else
/* Generated */    #endif
/* Generated */          MEM_P = NULL;/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 6 - DO NOT DELETE THIS LINE ****/

   /* insert state init code here. */


   return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
}

/**** START GENCODE SECTION 7 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ Core::RetCode Core::MinIndexState( struct TA_MinIndex_State* _state,
/* Generated */                                  cli::array<double>^ inReal,
/* Generated */                                  cli::array<int>^  *outInteger )
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode minIndexState( struct TA_minIndex_State* _state,
/* Generated */                             double       inReal,
/* Generated */                             int           *outInteger )
/* Generated */ #else
/* Generated */ TA_LIB_API TA_RetCode TA_MININDEX_State( struct TA_MININDEX_State* _state,
/* Generated */                                                   const double inReal,
/* Generated */                                                   int           *outInteger )
/* Generated */ #endif
/**** END GENCODE SECTION 7 - DO NOT DELETE THIS LINE ****/
{
   /* insert local variable here */
   #define TA_MININDEX_SUPPRESS_EXIT_ON_NOT_ENOUGH_DATA
/**** START GENCODE SECTION 8 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */    if (_state == NULL)
/* Generated */          return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */    #if !defined(_JAVA)
/* Generated */    /* Generated */    #endif /* !defined(_JAVA)*/
/* Generated */    size_t _cur_idx = STATE.mem_index++;
/* Generated */    if (MEM_SIZE > 0) _cur_idx %= MEM_SIZE;
/* Generated */    UNUSED_VARIABLE(_cur_idx); // in case PUSH\POP methods won't be used
/* Generated */    #ifndef TA_MININDEX_SUPPRESS_EXIT_ON_NOT_ENOUGH_DATA
/* Generated */    if (NEED_MORE_DATA) {
/* Generated */          PUSH_TO_MEM(inReal,inReal);
/* Generated */    return ENUM_VALUE(RetCode,TA_NEED_MORE_DATA,NeedMoreData); }
/* Generated */    #endif
/* Generated */    #if !defined(_JAVA)
/* Generated */    if( !outInteger )
/* Generated */       return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */ 
/* Generated */    #endif /* !defined(_JAVA) */
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 8 - DO NOT DELETE THIS LINE ****/

   /* insert state based TA func code here. */
 if (FIRST_LAUNCH)
  {
      STATE.min = inReal;
      STATE.minIdx = 0;
      STATE.currentIdx = 0;
  } else
        ++    STATE.currentIdx;

 if(    STATE.min > inReal )
 {
        STATE.min = inReal;
        STATE.minIdx =    STATE.currentIdx;
 } else
     if(    STATE.min == inReal )
            STATE.minIdx =    STATE.currentIdx;

 if (NEED_MORE_DATA) return ENUM_VALUE(RetCode,TA_NEED_MORE_DATA,NeedMoreData);

 VALUE_HANDLE_DEREF(outInteger) =    STATE.minIdx;

 return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
}

/**** START GENCODE SECTION 9 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ Core::RetCode Core::MinIndexBatchState( struct TA_MinIndex_State* _state,
/* Generated */                                       int startIdx,
/* Generated */                                       int endIdx,
/* Generated */                                       cli::array<double>^ inReal,
/* Generated */                                       [Out]int%    outBegIdx,
/* Generated */                                       [Out]int%    outNBElement,
/* Generated */                                       cli::array<int>^  outInteger )
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode minIndexBatchState( struct TA_minIndex_State* _state,
/* Generated */                                  int startIdx,
/* Generated */                                  int endIdx,
/* Generated */                                  double       inReal[],
/* Generated */                                  MInteger     outBegIdx,
/* Generated */                                  MInteger     outNBElement,
/* Generated */                                  int           outInteger[] )
/* Generated */ #else
/* Generated */ TA_LIB_API TA_RetCode TA_MININDEX_BatchState( struct TA_MININDEX_State* _state,
/* Generated */                                                        int startIdx,
/* Generated */                                                        int endIdx,
/* Generated */                                                        const double inReal[],
/* Generated */                                                        int          *outBegIdx,
/* Generated */                                                        int          *outNBElement,
/* Generated */                                                        int           outInteger[] )
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
/* Generated */    if( !inReal ) return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */    #endif /* !defined(_JAVA)*/
/* Generated */    #if !defined(_JAVA)
/* Generated */    if( !outInteger )
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
/* Generated */    int outIntegerVal;
/* Generated */    int retValue;
/* Generated */    
/* Generated */    int outIdx = 0;
/* Generated */    VALUE_HANDLE_DEREF(outBegIdx)  = startIdx;
/* Generated */    
/* Generated */    for (int i = startIdx; i <= endIdx; ++i, outIdx++) {
/* Generated */       retValue = TA_MININDEX_State( _state, inReal[i], &outIntegerVal );
/* Generated */       if ( retValue == ENUM_VALUE(RetCode,TA_SUCCESS,Success) ) {
/* Generated */          outInteger[outIdx] = outIntegerVal;
/* Generated */       } else if ( retValue == ENUM_VALUE(RetCode,TA_NEED_MORE_DATA,NeedMoreData) ) {
/* Generated */          outInteger[outIdx] = INT_MAX;
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
/* Generated */ Core::RetCode Core::MinIndexStateFree( struct TA_MinIndex_State** _state )
/* Generated */ 
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode minIndexStateFree( struct TA_minIndex_State** _state )
/* Generated */ 
/* Generated */ #else
/* Generated */ TA_LIB_API TA_RetCode TA_MININDEX_StateFree( struct TA_MININDEX_State** _state )
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 9 - DO NOT DELETE THIS LINE ****/
{
   /* insert local variable here */

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
/* Generated */ Core::RetCode Core::MinIndexStateSave( struct TA_MinIndex_State* _state,
/* Generated */                                      FILE* _file )
/* Generated */ 
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode minIndexStateSave( struct TA_minIndex_State* _state,
/* Generated */                                 FILE* _file )
/* Generated */ 
/* Generated */ #else
/* Generated */ TA_LIB_API TA_RetCode TA_MININDEX_StateSave( struct TA_MININDEX_State* _state,
/* Generated */                                                       FILE* _file )
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
/* Generated */    if (memory_allocated && STATE.mem_size > 0) { io_res = fwrite(STATE.memory,sizeof(struct TA_MININDEX_Data),STATE.mem_size,_file);
/* Generated */    if (io_res < (int) STATE.mem_size) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed); }
/* Generated */    io_res = fwrite(&STATE.optInTimePeriod,sizeof(STATE.optInTimePeriod),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    io_res = fwrite(&STATE.min,sizeof(STATE.min),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    io_res = fwrite(&STATE.minIdx,sizeof(STATE.minIdx),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    io_res = fwrite(&STATE.currentIdx,sizeof(STATE.currentIdx),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 12 - DO NOT DELETE THIS LINE ****/

   /* insert state save code here. */   
   return 0;
}

/**** START GENCODE SECTION 13 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ Core::RetCode Core::MinIndexStateLoad( struct TA_MinIndex_State** _state,
/* Generated */                                      FILE* _file )
/* Generated */ 
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode minIndexStateLoad( struct TA_minIndex_State** _state,
/* Generated */                                 FILE* _file )
/* Generated */ 
/* Generated */ #else
/* Generated */ TA_LIB_API TA_RetCode TA_MININDEX_StateLoad( struct TA_MININDEX_State** _state,
/* Generated */                                                       FILE* _file )
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
/* Generated */    STATE = TA_Calloc(1, sizeof(struct TA_MININDEX_State));
/* Generated */    io_res = fread(&STATE_P.mem_index,sizeof(STATE_P.mem_index),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    io_res = fread(&STATE_P.mem_size,sizeof(STATE_P.mem_size),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    int memory_allocated;
/* Generated */    io_res = fread(&memory_allocated,sizeof(memory_allocated),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    if (STATE_P.mem_size > 0 && memory_allocated) { STATE_P.memory = TA_Calloc(STATE_P.mem_size, sizeof(struct TA_MININDEX_Data));
/* Generated */    io_res = fread(STATE_P.memory,sizeof(struct TA_MININDEX_Data),STATE_P.mem_size,_file);
/* Generated */    if (io_res < (int) STATE_P.mem_size) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed); } 
/* Generated */    io_res = fread(&STATE_P.optInTimePeriod,sizeof(STATE_P.optInTimePeriod),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    io_res = fread(&STATE_P.min,sizeof(STATE_P.min),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    io_res = fread(&STATE_P.minIdx,sizeof(STATE_P.minIdx),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */    io_res = fread(&STATE_P.currentIdx,sizeof(STATE_P.currentIdx),1,_file);
/* Generated */    if (io_res < 1) return ENUM_VALUE(RetCode,TA_IO_FAILED,IOFailed);
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 14 - DO NOT DELETE THIS LINE ****/

   /* insert state load code here. */   
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
/* Generated */ enum class Core::RetCode Core::MinIndex( int    startIdx,
/* Generated */                                          int    endIdx,
/* Generated */                                          SubArray<float>^ inReal,
/* Generated */                                          int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                          [Out]int%    outBegIdx,
/* Generated */                                          [Out]int%    outNBElement,
/* Generated */                                          SubArray<int>^  outInteger )
/* Generated */ #elif defined( _MANAGED )
/* Generated */ enum class Core::RetCode Core::MinIndex( int    startIdx,
/* Generated */                                          int    endIdx,
/* Generated */                                          cli::array<float>^ inReal,
/* Generated */                                          int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                          [Out]int%    outBegIdx,
/* Generated */                                          [Out]int%    outNBElement,
/* Generated */                                          cli::array<int>^  outInteger )
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode minIndex( int    startIdx,
/* Generated */                          int    endIdx,
/* Generated */                          float        inReal[],
/* Generated */                          int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                          MInteger     outBegIdx,
/* Generated */                          MInteger     outNBElement,
/* Generated */                          int           outInteger[] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_S_MININDEX( int    startIdx,
/* Generated */                           int    endIdx,
/* Generated */                           const float  inReal[],
/* Generated */                           int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                           int          *outBegIdx,
/* Generated */                           int          *outNBElement,
/* Generated */                           int           outInteger[] )
/* Generated */ #endif
/* Generated */ {
/* Generated */    double lowest, tmp;
/* Generated */    int outIdx, nbInitialElementNeeded;
/* Generated */    int trailingIdx, lowestIdx, today, i;
/* Generated */  #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */     if( startIdx < 0 )
/* Generated */        return ENUM_VALUE(RetCode,TA_OUT_OF_RANGE_START_INDEX,OutOfRangeStartIndex);
/* Generated */     if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */        return ENUM_VALUE(RetCode,TA_OUT_OF_RANGE_END_INDEX,OutOfRangeEndIndex);
/* Generated */     #if !defined(_JAVA)
/* Generated */     if( !inReal ) return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */     #endif 
/* Generated */     if( (int)optInTimePeriod == TA_INTEGER_DEFAULT )
/* Generated */        optInTimePeriod = 30;
/* Generated */     else if( ((int)optInTimePeriod < 2) || ((int)optInTimePeriod > 100000) )
/* Generated */        return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */     #if !defined(_JAVA)
/* Generated */     if( !outInteger )
/* Generated */        return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */     #endif 
/* Generated */  #endif 
/* Generated */    nbInitialElementNeeded = (optInTimePeriod-1);
/* Generated */    if( startIdx < nbInitialElementNeeded )
/* Generated */       startIdx = nbInitialElementNeeded;
/* Generated */    if( startIdx > endIdx )
/* Generated */    {
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
/* Generated */       VALUE_HANDLE_DEREF_TO_ZERO(outNBElement);
/* Generated */       return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
/* Generated */    }
/* Generated */    outIdx = 0;
/* Generated */    today       = startIdx;
/* Generated */    trailingIdx = startIdx-nbInitialElementNeeded;
/* Generated */    lowestIdx   = -1;
/* Generated */    lowest      = 0.0;
/* Generated */    while( today <= endIdx )
/* Generated */    {
/* Generated */       tmp = inReal[today];
/* Generated */       if( lowestIdx < trailingIdx )
/* Generated */       {
/* Generated */         lowestIdx = trailingIdx;
/* Generated */         lowest = inReal[lowestIdx];
/* Generated */         i = lowestIdx;
/* Generated */         while( ++i<=today )
/* Generated */         {
/* Generated */            tmp = inReal[i];
/* Generated */            if( tmp < lowest )
/* Generated */            {
/* Generated */               lowestIdx = i;
/* Generated */               lowest = tmp;
/* Generated */            }
/* Generated */         }
/* Generated */       }
/* Generated */       else if( tmp <= lowest )
/* Generated */       {
/* Generated */         lowestIdx = today;
/* Generated */         lowest = tmp;
/* Generated */       }
/* Generated */       outInteger[outIdx++] = lowestIdx;
/* Generated */       trailingIdx++;
/* Generated */       today++;  
/* Generated */    }
/* Generated */    VALUE_HANDLE_DEREF(outBegIdx)    = startIdx;
/* Generated */    VALUE_HANDLE_DEREF(outNBElement) = outIdx;
/* Generated */    return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
/* Generated */ }
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ }}} // Close namespace TicTacTec.TA.Lib
/* Generated */ #endif
/**** END GENCODE SECTION 15 - DO NOT DELETE THIS LINE ****/

