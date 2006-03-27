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
            
            // If reference on same data, it is considered
            // synchronized.
            if (this.mTimestamps == timeStamps.mTimestamps)
                return true;
            
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
