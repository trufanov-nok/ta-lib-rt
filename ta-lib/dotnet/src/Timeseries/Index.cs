/* TA-Lib Copyright (c) 1999-2006, Mario Fortier
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
 * Change history:
 *
 *  MMDDYY BY     Description
 *  -------------------------------------------------------------------
 *  010105 MF     Initial Coding.
 */

/****************************** BIG WARNING ********************
 *   Only the code in TA-Lib-Core for .NET is mature.
 * 
 *   All code in TA-Lib-Timeseries is in development and is 
 *   not yet ready for use in applications.
 ****************************** BIG WARNING ********************/

using System;
using System.Collections;
using TA.Lib;
using System.Collections.Generic;

namespace TA.Lib
{
    // Index hides all the complexity related to offset within data during 
    // iteration of the values within the timeseries and variable.
    public class Index
    {
        // Offset within the timestamp array.
        private int mTimestampOffset;

        // Offset from the perspective of the foreach() user.
        private int mPosition;

        // One of the variable timestamps is selected
        // to be the reference.
        private Timestamps mRefTimestamps;

        // Info for each ValueIter provided by the user for this iteration.
        private ValueIterInfo[] mValueIter;

        // Info for each new ValueIter (new variable) being initialized
        // during this iteration.
        private List<ValueIterInfo> mNewValueIter;

        // Total number of iteration from the perspective of the foreach() user.
        private int mSize;

        // Temporary back offset. User set this offset by using the
        // substraction operator:
        //
        // foreach( Index i in ts )
        // {
        //    ...
        //    double d = ts[i-1];
        // }
        private int mBackOffset;
    
        // Public property so that the foreach() loop can identify
        // where it stands among all the iterations.
        public int PositionToEnd
        {
            get
            {
                return mSize - mPosition - 1;               
            }
        }

        public int Position
        {
            get
            {
                return mPosition;
            }
        }

        public int Size
        {
            get
            {
                return mSize;
            }
        }

        internal Timestamps RefTimestamps
        {
            get
            {
                return mRefTimestamps;
            }
        }

        // Find the common range among an array of IValueIter
        // Return false if a common range cannot be find.
        static public bool FindCommonRange(ValueIter[] list, out int beginCommonRange, out int endCommonRange)
        {
            ValueIter valueIter = list[0];
            if (valueIter.GetCommonRange(out beginCommonRange, out endCommonRange) == false)
            {
                // Common range does not have elements.
                return false;
            }

            if (list.Length > 1)
            {
                Timestamps refTimestamps = valueIter.GetTimestamps();
                for (int i = 1; i < list.Length; i++)
                {
                    valueIter = list[i];
                    int tempBegin, tempEnd;
                    if (valueIter.GetCommonRange(out tempBegin, out tempEnd) == false)
                    {
                        // Common range does not have elements.
                        return false;
                    }
                    if (tempBegin > beginCommonRange) beginCommonRange = tempBegin;
                    if (tempEnd < endCommonRange) endCommonRange = tempEnd;
                }
            }

            return true;
        }


        internal Index(params ValueIter[] list)
        {
            // Handle case of empty list.
            if (list.Length == 0)
                return;

            // Get the first IValueIter with defined timestamps.
            ValueIter valueIter = list[0];
            mRefTimestamps = valueIter.GetTimestamps();
            for (int i = 1; (mRefTimestamps == null) && (i < list.Length); i++)
            {
                valueIter = list[i];
                mRefTimestamps = valueIter.GetTimestamps();
            }

            // All IValueIter have no timestamps/content yet.
            if (mRefTimestamps == null)
                return;

            // Find the total number of ValueIter and verify all synchronized.
            // At the same time, identify the common range.
            int beginCommonRange = int.MinValue;
            int endCommonRange = int.MaxValue;
            valueIter = list[0];
            int nbValueIter = valueIter.NbValueIter();
            if (nbValueIter != 0)
            {
                if (valueIter.GetCommonRange(out beginCommonRange, out endCommonRange) == false)
                {
                    // Common range does not have elements.
                    return;
                }
            }
            
            for (int i = 1; i < list.Length; i++)                
            {
                valueIter = list[i];

                // Could be speed optimized...
                Timestamps t = valueIter.GetTimestamps();
                if (t != null)
                {
                    if (!t.IsSyncWith(mRefTimestamps))
                    {
                        throw new Exception("Iteration possible only among synchronized Timeseries and Variables");
                    }

                    int temp = valueIter.NbValueIter();
                    if (temp != 0)
                    {
                        nbValueIter += temp;

                        int tempBegin, tempEnd;
                        if (valueIter.GetCommonRange(out tempBegin, out tempEnd) == false)
                        {
                            // Common range does not have elements.
                            return;
                        }
                        if (tempBegin > beginCommonRange) beginCommonRange = tempBegin;
                        if (tempEnd < endCommonRange) endCommonRange = tempEnd;
                    }
                }
            }

            // Handle case with no IValueIter.
            // (Keep in mind the case of Timeseries with no variable).
            if (nbValueIter == 0)
            {
                return;
            }

            // TODO: Remove once FindCommonRange is confirm bug free.
            int begCommonRange2 = int.MinValue;
            int endCommonRange2 = int.MaxValue;
            if (FindCommonRange(list, out begCommonRange2, out endCommonRange2) == false)
            {
                throw new Exception("FindCommonRange: Iteration possible only for synchronized Timeseries and Variable");
            }

            if ((begCommonRange2 != beginCommonRange) || (endCommonRange2 != endCommonRange))
            {
                throw new Exception("Internal Bug!");
            }

            // The number of elements left to be iterated.            
            int positionToEnd = endCommonRange - beginCommonRange + 1;

            // Handle case of all empty variables or no common range.
            if ( positionToEnd <= 0 )
            {
                return;
            }

            // Each ValueIter will have a corresponding ValueIterInfo structure.
            mValueIter = new ValueIterInfo[nbValueIter];

            // Keep reference on new ValueIter initialize during the 
            // iteration.
            mNewValueIter = new List<ValueIterInfo>(10);

            // Get the starting offsets and reference on every ValueIter.
            int arrayPos = 0;
            for (int i = 0; i < list.Length; i++)
            {             
                list[i].SetValueIterInfo( ref mValueIter, ref arrayPos, beginCommonRange);
            }

            // Calculate the starting offset for the timestamp array.
            mTimestampOffset = beginCommonRange;

            // Now ready for first iteration.
            // Iterator will work only when mSize != 0.
            mSize = positionToEnd;
        }

        // Allow addition of new empty variables during iteration.
        internal void AddNewValueIter( ValueIter vi, int startOffset )
        {
            // TODO Remove this sanity test eventually.
            if (vi.NbValueIter() != 1)
            {
                // Shall never happen since only variable can be added,
                // not a timeseries.
                throw new InternalError();
            }
                
            ValueIterInfo newInfo = new ValueIterInfo();
            newInfo.mValueIter = vi;
            newInfo.mStartOffset = startOffset;
            mNewValueIter.Add(newInfo);
        }

        internal int Offset(ValueIter vi)
        {
            // Reset the back offset.
            // It is assumed that the ValueIter will
            // call the Offset() function only once
            // for the current data access.
            int backOffset = mBackOffset;
            mBackOffset = 0;

            // Find which of the mOffset correspond
            // to this ValueIter. Use cache info when available.
            ValueIterInfo cachedInfo = vi.GetIndexCache(this);
            if (cachedInfo != null )
                return cachedInfo.mStartOffset-backOffset;
            
            // Not in the cache, so do a sequential
            // search for the right mOffset.
            for (int i = 0; i < mValueIter.Length; i++)
            {                
                if (mValueIter[i].mValueIter.IsSame(vi))
                {
                    vi.SetIndexCache(this, mValueIter[i]);
                    return mValueIter[i].mStartOffset-backOffset;
                }
            }

            // Not in the list of ValueIter specified by 
            // the user prior to iteration, so search in the 
            // list of newValueIter added during iteration.            
            foreach (ValueIterInfo i in mNewValueIter)
            {
                if( i.mValueIter.IsSame(vi) )
                {
                    vi.SetIndexCache(this, i);
                    return i.mStartOffset - backOffset;
                }
            }

            
            // Attempt to use this Index on an invalid Variable.
            // All non-empty variable must be specified in the 
            // foreach statement.
            //
            // Example:
            //    foreach( Index i in (close&open) ) { ... }
            //
            //    Access to variable other than close and open 
            //    will cause this exception to occur.
            throw new Exception("Variable not accessible with this index");
        }

        internal int TimestampOffset
        {
            get
            {
                return mTimestampOffset;
            }
        }

        // Locking allows to properly prevent and/or handle safely changes to 
        // the objects being iterated.
        private bool mLock = false;
        private bool Lock
        {
            get { return mLock; }
            set 
            {
                if (value != mLock)
                {
                   for (int i = 0; i < mValueIter.Length; i++)
                   {
                      mValueIter[i].mValueIter.Lock = value;
                   }
                   if (mNewValueIter.Count != 0)
                   {
                       foreach (ValueIterInfo i in mNewValueIter)
                       {
                           i.mValueIter.Lock = value;
                       }
                   }
                }
                mLock = value; 
            }
        }	

        // Return an enumerator for this index.
        public IEnumerator<Index> GetEnumerator()
        {
            if (mSize != 0)
            {
                Lock = true;
                mPosition = 0;
                yield return this;
                while (++mPosition != mSize)
                {
                    // Adjust position for all the valueIter.
                    for (int i = 0; i < mValueIter.Length; i++)
                    {
                        mValueIter[i].mStartOffset++;
                    }
                    if (mNewValueIter.Count != 0)
                    {
                        foreach (ValueIterInfo i in mNewValueIter)
                        {
                            i.mStartOffset++;
                        }
                    }
                    mTimestampOffset++;
                    //mBackOffset = 0; 
                    yield return this;                    
                }
                Lock = false;
            }
        }

        public static Index operator -(Index a, int b)
        {
            a.mBackOffset = b;
            return a;
        }

        public Index Prev(int backOffset)
        {
            this.mBackOffset = backOffset;
            return this;
        }
    }
}
