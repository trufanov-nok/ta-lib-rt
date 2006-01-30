/****************************** BIG WARNING ********************
 *   Only the code in TA-Lib-Core for .NET is mature.
 * 
 *   All code in TA-Lib-Timeseries is in development and is 
 *   not yet ready for use in applications.
 ****************************** BIG WARNING ********************/
using System;
using System.Collections;
using TA.Lib;

namespace TA.Lib
{
    
    public class Index
    {
        private int[] mStartOffset;        
        private IValueIter[] mValueIter;        
        private int mPosition;
        private int mSize;
        private int mTimestampOffset;

        public int PositionToEnd
        {
            get
            {
                if( mSize == 0 )
                    return -1;
                else
                    return mSize-mPosition-1;
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
            // Default.
            mPosition = -1;            

            // Handle case of empty list.
            if (list.Length == 0)
                return;

            // Find the total number of ValueIter and
            // verify all synchronized.
            // At the same time, identify the common range.
            int beginCommonRange = int.MinValue;
            int endCommonRange = int.MaxValue;
            IValueIter valueIter = list[0];
            if (valueIter.GetCommonRange(out beginCommonRange, out endCommonRange) == false)
            {
                // Common range does not have elements.
                return;
            }
            Timestamps refTimestamps = valueIter.GetTimestamps();
            int nbValueIter = valueIter.NbValueIter();

            // Handle case of Timeseries with no variables.
            if (nbValueIter == 0)
            {
                return;
            }

            for (int i = 1; i < list.Length; i++)                
            {
                valueIter = list[i];
                if (!valueIter.GetTimestamps().Equals(refTimestamps))
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
            // Set variable allowing the user to identify the position
            // within the iterations.
            mPosition = 0;
            mSize = positionToEnd;
        }

        internal bool Next()
        {
            if (mPosition == mSize)
                return false;
            else
                mPosition++;

            // Adjust position for all the valueIter.
            for (int i = 0; i < mValueIter.Length; i++)
            {
                mStartOffset[i]++;
            }
            mTimestampOffset++;
            return true;
        }

        internal int Offset(IValueIter vi)
        {
            // Find which of the mOffset correspond
            // to this ValueIter. Use cache info when available.
            int iterIdx = vi.GetIndexCache(this);
            if (iterIdx != -1)
                return mStartOffset[iterIdx];
            
            // Not in the cache, so do a sequential
            // search for the right mOffset.
            for (int i = 0; i < mValueIter.Length; i++)
            {                
                if (mValueIter[i].IsSame(vi))
                {
                    vi.SetIndexCache(this, i);
                    return mStartOffset[i];
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
        public bool Lock
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
    }
}
