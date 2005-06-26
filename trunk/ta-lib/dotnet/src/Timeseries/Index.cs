using System;
using System.Collections;
using TA.Lib;

namespace TA.Lib
{
    public class Index
    {
        private int[] mOffset;        
        private IValueIter[] mValueIter;
        private int mLeftToIterate;
        private int mTimestampOffset;

        public int LeftToIterate
        {
            get
            {
                return mLeftToIterate;
            }
        }

        internal Index(params IValueIter[] list)
        {
            // Handle special case of empty list.
            if (list.Length == 0)
            {
                mLeftToIterate = 0;
                return;
            }

            // Each ValueIter have a corresponding "offset" maintained
            // locally in the Index object.
            mOffset = new int[list.Length];            

            // Validate all synchronized.
            // At the same time, identify the common range.            
            int begCommonRange;
            int endCommonRange;
            IValueIter valueIter = list[0];
            endCommonRange = valueIter.GetEndTimestampOffset();
            begCommonRange = valueIter.GetStartTimestampOffset();
            mOffset[0] = begCommonRange;
            if (list.Length > 1)
            {
                Timestamps refTimestamps = valueIter.GetTimestamps();
                for (int i = 1; i < list.Length; i++)
                {
                    valueIter = list[i];
                    if (!valueIter.GetTimestamps().Equals(refTimestamps))
                        throw new Exception("Iteration possible only for synchronized Timeseries and Variable");
                    int temp = valueIter.GetStartTimestampOffset();
                    if (temp > begCommonRange) begCommonRange = temp;
                    mOffset[i] = temp;
                    temp = valueIter.GetEndTimestampOffset();
                    if (temp < endCommonRange) endCommonRange = temp;
                }
            }

            // The number of elements left to be iterated.
            mLeftToIterate = endCommonRange - begCommonRange + 1;

            // Handle case of an empty ValueIter or no common range.
            if (mLeftToIterate <= 0)
            {
                mLeftToIterate = 0;
                return;
            }

            // Now that the common range is known, adjust the starting 
            // offset for each ValueIter.
            for (int i = 0; i < list.Length; i++)
            {
                mOffset[i] = begCommonRange - mOffset[i];
            }

            // Calculate the starting offset for the timestamp array.
            mTimestampOffset = begCommonRange;

            // Keep a reference on the list of ValueIter
            mValueIter = list;
        }

        internal bool Next()
        {
            if (mLeftToIterate == 0)
                return false;
            else
            {
                mLeftToIterate--;
            }

            // Adjust position for all the valueIter.
            for (int i = 0; i < mValueIter.Length; i++)
            {
                mOffset[i]++;
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
                return mOffset[iterIdx];

            // Not in the cache, so do a sequential
            // search for the right mOffset.
            for (int i = 0; i < mValueIter.Length; i++)
            {
                if (vi.Equals(mValueIter[i]))
                {
                    vi.SetIndexCache(this, i);
                    return mOffset[i];
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
    }
}
