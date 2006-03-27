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
    #region Value Generic
    /// <summary>
    /// Storage of information related to the value of
    /// a variable at a given point in time.
    /// 
    /// Take note that this is a value type, not a
    /// reference type.
    /// </summary>
    [Serializable()]
    public struct Value<T> 
    {
        internal Value( bool isDefined, T theValue, double doubleValue )
        {
            mIsDefined = isDefined;
            mDoubleValue = doubleValue;
            mData = theValue;
        }

        /// <summary>
        /// True when the value is known.
        /// False when this is a "pad value" or unknown value.
        /// </summary>
        public bool IsDefined
        {
            get
            {
                return mIsDefined;
            }
            internal set
            {
                mIsDefined = value;
            }
        }

        /// <summary>
        /// Floating-point representation of the value.
        /// </summary>
        public double AsDouble
        {
            get
            {
                return mDoubleValue;
            }
            internal set
            {
                mDoubleValue = value;
            }
        }

        /// <summary>
        /// User defined representation of the value.
        /// </summary>
        public T Data
        {
            get
            {
                return mData;
            }
            internal set
            {
                mData = value;
            }
        }

        private bool mIsDefined;
        private double mDoubleValue;
        private T mData;
    }
    #endregion

    
/*
    #region Values Generic
    /// <summary>
    /// Object to provide access to values.
    /// </summary>
    [Serializable()]
    public class Values<T>
    {        
        #region Constructors
        internal Values(TimeseriesBase tsb, T[] array)
        {
            // Make a copy of the provided new data.
            mParent = tsb;
            if( array is double )
                mDoubleValues = (double[])array.Clone();
            else
                mValues = (T[])array.Clone();
        }

        internal Values(TimeseriesBase tsb, Values<T> values)
        {
            // Reference on same data of existing Values.
            mParent = tsb;
            mValues = values.mValues;
            mDoubleValues = values.mDoubleValues;
        }
        #endregion

        /// <summary>Initialize a Value object for a given index.</summary>
        public void GetValue(int index, Value<T> val)
        {
            if (mParent.IndexValid(index) == false)
            {
                throw new Exception("Out-of-bound subscript");
            }

            // TODO Offset calculation
            int localIndex = index;

            // TODO Pad Value detection.

            // As needed, convert the requested value to double.                
            if( mValues != null )
            {
                val.Data = mValues[localIndex];
                if( mDoubleValues == null )
                {
                    // The Timeseries must provides a mean to translate T to double.
                    val.AsDouble = (mParent as Timeseries<T>).ToDouble(mValues[index]);
                }
                else
                    val.AsDouble = mDoubleValues[localIndex];
            }
            else if (mDoubleValues != null)
            {
                val.AsDouble = mDoubleValues[localIndex];
            }
            else
            {
                throw new Exception("Internal Error");
            }
        }
        
        /// <summary>
        /// Access to the Value object for a given index.
        /// The index range from 0 to the Timeseries Length-1
        /// </summary>
        public Value<T> this[int index]
        {
            get
            {
                Value<T> retVal = new Value<T>();
                GetValue(index, retVal);
                return retVal;
            }
        }

        // TODO: Provide a mechanism to convert mValues to mDoubleValues at once.

        #region Internal Members
        internal T[]      mValues;       // Storage for user defined values.
        internal double[] mDoubleValues; // Storage for double precision values.
        #endregion

        #region Private Members
        private TimeseriesBase mParent;
        #endregion
    }
    #endregion
 */
}
