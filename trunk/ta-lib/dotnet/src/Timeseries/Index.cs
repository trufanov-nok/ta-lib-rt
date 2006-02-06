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
        // Offsets within the data arrays of each variable.
        private int[] mStartOffset;        

        // Offset within the timestamp array.
        private int mTimestampOffset;

        // Offset from the perspective of the foreach() user.
        private int mPosition;

        // One of the variable timestamps is selected
        // to be the reference.
        private Timestamps mRefTimestamps;

        // Keep a reference on all ValueIter during iteration.        
        private IValueIter[] mValueIter;

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
        static public bool FindCommonRange(IValueIter[] list, out int beginCommonRange, out int endCommonRange)
        {
            IValueIter valueIter = list[0];
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


        internal Index(params IValueIter[] list)
        {
            // Handle case of empty list.
            if (list.Length == 0)
                return;

            // Find the total number of ValueIter and verify all synchronized.
            // At the same time, identify the common range.
            int beginCommonRange = int.MinValue;
            int endCommonRange = int.MaxValue;
            IValueIter valueIter = list[0];
            if (valueIter.GetCommonRange(out beginCommonRange, out endCommonRange) == false)
            {
                // Common range does not have elements.
                return;
            }
            Timestamps mRefTimestamps = valueIter.GetTimestamps();
            int nbValueIter = valueIter.NbValueIter();

            // Handle case of Timeseries with no variables.
            if (nbValueIter == 0)
            {
                return;
            }

            for (int i = 1; i < list.Length; i++)                
            {
                valueIter = list[i];

                // Could be speed optimized...
                if (!valueIter.GetTimestamps().IsSyncWith(mRefTimestamps))
                {
                    throw new Exception("Iteration possible only among synchronized Timeseries and Variables");
                }

                int temp = valueIter.NbValueIter();
                // Handle case of Timeseries with no variables.
                if (temp == 0)
                {
                    return;
                }
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

            // TODO: Remove once FindCommonRange is confirm bug free.
            int begCommonRange2;
            int endCommonRange2;
            if (FindCommonRange(list, out begCommonRange2, out endCommonRange2) == false)
            {
                throw new Exception("Iteration possible only for synchronized Timeseries and Variable");
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

            // Each ValueIter will have a corresponding "offset" owned
            // by the Index object.
            mStartOffset = new int[nbValueIter];

            // Keep references on ALL ValueIter.
            mValueIter = new IValueIter[nbValueIter];

            // Get the starting offsets and reference on every ValueIter.
            int arrayPos = 0;
            for (int i = 0; i < list.Length; i++)
            {             
                list[i].SetValueIterInfo( ref mValueIter, ref mStartOffset, ref arrayPos, beginCommonRange);
            }

            // Calculate the starting offset for the timestamp array.
            mTimestampOffset = beginCommonRange;

            // Now ready for first iteration.
            // Iterator will work only when mSize != 0.
            mSize = positionToEnd;
        }

        internal int Offset(IValueIter vi)
        {
            // Reset the back offset.
            // It is assumed that the ValueIter will
            // call the Offset() function only once
            // for the current data access.
            int backOffset = mBackOffset;
            mBackOffset = 0;

            // Find which of the mOffset correspond
            // to this ValueIter. Use cache info when available.
            int iterIdx = vi.GetIndexCache(this);
            if (iterIdx != -1)
                return mStartOffset[iterIdx]-backOffset;
            
            // Not in the cache, so do a sequential
            // search for the right mOffset.
            for (int i = 0; i < mValueIter.Length; i++)
            {                
                if (mValueIter[i].IsSame(vi))
                {
                    vi.SetIndexCache(this, i);
                    return mStartOffset[i]-backOffset;
                }
            }

            // Attempt to use this Index on a Variable or Timeseries
            // that is not part of the Iter object.
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
                      mValueIter[i].Lock = value;
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
                        mStartOffset[i]++;
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
