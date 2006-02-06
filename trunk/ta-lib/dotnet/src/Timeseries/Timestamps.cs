/****************************** BIG WARNING ********************
 *   Only the code in TA-Lib-Core for .NET is mature.
 * 
 *   All code in TA-Lib-Timeseries is in development and is 
 *   not yet ready for use in applications.
 ****************************** BIG WARNING ********************/

using System;
using System.Collections.Generic;
using System.Text;

namespace TA.Lib
{
    #region Timestamps
    /// <summary>
	/// Object to provide access to timestamps.
	/// </summary>
	[Serializable()]
	public class Timestamps
	{
		#region Constructors
		internal Timestamps( IValueIter parent, DateTime []array )
		{
			// Make a copy of the provided DateTime array.
			mParent = parent;
			mTimestamps = (DateTime[])array.Clone();
            mLength = array.Length;
            mTotalLength = mLength;
		}

		internal Timestamps( IValueIter parent, Timestamps timestamps )
		{
			// Reference on same data of an existing Timestamps.
			mParent = parent;
			mTimestamps = timestamps.mTimestamps;
            mStartDateTime = timestamps.mStartDateTime;
            mLength = timestamps.Length;
            mTotalLength = mLength;
        }

		internal Timestamps(IValueIter parent, int size )
		{
			mParent = parent;
            mStartDateTime = new DateTime(0);
            mLength = size;
            mTotalLength = mLength;
		}
		#endregion

		/// <summary>
		/// Access to the DateTime for the parent timeseries.
		/// </summary>
		public DateTime this [Index index]
		{
			get 
			{
                int idx = index.TimestampOffset;
				if( mTimestamps == null )
					return mStartDateTime.AddMilliseconds(idx);
				else
					return mTimestamps[idx];
			}
		}

        /// <summary>
        /// Allows to get the total size.
        /// </summary>
        /// <returns>Return the number of timestamps.</returns>
        public int Length
        { 
            get 
            {
                return mLength;
            }
        }

        /// <summary>
        /// Allows to set/get the offset this Timestamps
        /// is using within the timestamps that were
        /// specified at creation.
        /// </summary>
        internal int Offset
        {
            get
            {
                return mOffset;
            }
            set
            {
                if ((value > mLength) || (value < 0))
                {
                    throw new InternalError();
                }
                mOffset = value;
                mLength = mTotalLength - mOffset;
            }
        }


		#region Internal Members
        internal bool IsSyncWith(Timestamps timeStamps)
        {
            // If exact same object, it is synchronized...
            if (this.Equals(timeStamps)) 
                return true;

            // If both are positional, synchronization is assumed
            // because the timestamps are alway {0,1,2,3...}
            if (this.mTimestamps == null)
            {
                if (timeStamps.mTimestamps == null)
                    return true;

                // Positional can be synchronized only with another
                // positional timestamps.
                return false;
            }
            
            // TODO Implement identification of Timeseries with
            // same DateTime among their common range.
            return false;
        }
		#endregion

		#region Private Members

        // Either the timestamps are stored in mTimestamps,
        // or are generated from a starting mStartDateTime.
		private DateTime mStartDateTime;
        private DateTime[] mTimestamps;

        // A Timestamps always belong to one and only one parent object.
        private IValueIter mParent;		

        // An offset into the mTimestamps
        private int mOffset;

        // How many values available within the timestamps (starting at mOffset).
        private int mLength;

        // Length that was provided on construction.
        private int mTotalLength;
		#endregion
	}
	#endregion
}
