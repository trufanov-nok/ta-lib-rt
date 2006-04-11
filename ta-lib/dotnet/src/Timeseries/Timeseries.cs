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
using System.Collections.Generic;
using System.Diagnostics;
using TA.Lib;

// Constructor Logic.
// Call the base.Init()
// Call Local InitMembers();

namespace TA.Lib
{
    // Alias to generic for user convenience.
    public class Timeseries :
        Timeseries<Timeseries, Variable, double>
    {
        #region Constructors
        /// <summary>
        /// Default constructor.
        /// </summary>
        public Timeseries() 
        {
            base.Init();
            InitMembers();
        }

        /// <summary>
        /// Build a time series using an array of DateTime. Typically used to set
        /// the timestamps before adding data using plain arrays.
        /// </summary>
        /// <param name="dateTime">An array of timestamps using the .NET DateTime.</param>
        public Timeseries(DateTime[] dateTime)
        {
            base.Init(dateTime);
            InitMembers();
        }

        /// <summary>
        /// Build a time series using the timestamps of an existing Timeseries.
        /// </summary>
        /// <param name="dateTime">The reference Timestamps.</param>
        public Timeseries(Timestamps timestamps)
        {
            base.Init(timestamps);
            InitMembers();
        }

        /// <summary>
        /// Build a time series of a specific size using unspecified timestamps.
        /// </summary>
        public Timeseries(int size)
        {
            base.Init(size);
            InitMembers();
        }


        /// <summary>
        /// Special constructor when creating a "place holder" timeseries
        /// for an existing variable.
        /// 
        /// This occur when the use does soemthing like:
        ///    Variable v = new Varaible();
        /// 
        /// Since Varaible must always belong to a Timeseries, in that
        /// case the variable belongs to this invisble "place holder" 
        /// timeseries.
        /// </summary>
        internal Timeseries(Variable v)
        {
            base.Init();
            InitMembers();
            InternalSetVar("Default",v);
        }
        
        private void InitMembers()
        {
            Add = new AddOp(this);
            Apply = new ApplyOp(this);
        }
        #endregion

        #region Internal Factories
        internal override Variable createVariable()
        {
            return new Variable(this);
        }

        internal override Variable createVariable(double[] val)
        {
            return new Variable(this, val);
        }

        internal override Variable createVariable(double[] val, int offset)
        {
            return new Variable(this, val, offset);
        }

        internal override Timeseries createTimeseries()
        {
            return new Timeseries();
        }
        internal override Timeseries createTimeseries(DateTime[] dateTime)
        {
            return new Timeseries(dateTime);
        }
        internal override Timeseries createTimeseries(Timestamps timestamps)
        {
            return new Timeseries(timestamps);
        }
        #endregion

        #region Public Factories
        /// <summary>
        /// Create a Timeseries with a variable containing
        /// random values. 
        /// 
        /// The timestamps are daily starting on January 1st, 1970.
        /// 
        /// The variable is named "Random".
        /// </summary>
        /// <param name="size">The number of values</param>
        /// <returns></returns>
        public static Timeseries RandomTimeseries(int size)
        {
            // Create a time series with default DateTime
            DateTime[] tempDateTime;
            tempDateTime = new DateTime[size];
            for (int i = 1; i < tempDateTime.Length; i++)
            {
                tempDateTime[i] = tempDateTime[i - 1].AddDays(1.0);
            }
            Timeseries ts = new Timeseries(tempDateTime);

            // Add a variable with random values.
            double[] tempValue;
            tempValue = new double[size];
            for (int i = 1; i < tempValue.Length; i++)
            {
                // TODO Replace with true random (eventually).
                tempValue[i] = tempValue[i - 1] + 1;
            }
            ts.AddVariable("Random", tempValue);
            return ts;
        }

        /// <summary>
        /// Create a Timeseries with variables containing
        /// random values. 
        /// 
        /// The timestamps are daily starting on January 1st, 1970.
        /// 
        /// The variable are named "Open", "High", "Low", "Close"
        /// with values having the following relationships:
        ///     (1) High >= Close >= Low
        ///     (2) High >= Open >= Low
        /// </summary>
        /// <param name="size">The number of values</param>
        /// <returns></returns>
        public static Timeseries RandomTimeseriesOHLC(int size)
        {
            // Create a time series with default DateTime
            DateTime[] tempDateTime;
            tempDateTime = new DateTime[size];
            for (int i = 1; i < tempDateTime.Length; i++)
            {
                tempDateTime[i] = tempDateTime[i - 1].AddDays(1.0);
            }
            Timeseries ts = new Timeseries(tempDateTime);

            double[] tempValue;
            double[] data = new double[size];
            for (int i = 1; i < data.Length; i++)
            {
                // TODO Replace with true random (eventually).
                data[i] = data[i - 1] + 1;
            }

            // Add a low variable with random values.
            tempValue = (double[])data.Clone();
            ts.AddVariable("Low", tempValue);

            // Add a high variable with random values >= low
            tempValue = (double[])data.Clone();
            ts.AddVariable("High", tempValue);

            // Add an open variable at a random point between high and low.
            tempValue = (double[])data.Clone();
            ts.AddVariable("Open", tempValue);

            // Add an open variable at a random point between high and low.
            tempValue = (double[])data.Clone();
            ts.AddVariable("Close", tempValue);

            return ts;
        }
        #endregion

        #region AddOp
        /// <summary>
        /// Allows to conveniently add a variable to a time series by 
        /// calling a built-in function. The input of the function are
        /// part of the timeseries.
        /// </summary>
        public class AddOp
        {
            private Timeseries mParent;

            /// <summary>
            /// Constructor
            /// </summary>
            internal AddOp(Timeseries parent) { mParent = parent; }

            /// <summary>
            /// Create a variable using a deleguate functions
            /// that returns a value for each position 'n'.
            /// 
            /// 'n' goes from 0 to the (number of timestamps)-1
            /// 
            /// The added variable is named "Sequence".
            /// </summary>            
            public Variable Sequence(Variable.SequenceFunction f)
            {
                // Do Variable.Sequence on the default.
                Variable parentVar = mParent.Default;
                if( parentVar != null )
                {
                     Timeseries ts = parentVar.Sequence(f);
                     return mParent[ts.Default.Name] = ts.Default;
                }

                // If here, it means that there is NO variable
                // in the parent Timeseries. Create a variable that 
                // covers the whole range of the Timestamps.
                int size = mParent.Timestamps.Length;
                Variable newVar;
                if (size <= 0)
                    newVar = new Variable(mParent, new double[0]);
                else
                {
                    double[] output;
                    output = new double[size];

                    for (int n = 0; n < size; n++)
                    {
                        output[n] = f(n);
                    }
                    newVar = new Variable(mParent, output);
                }

                // Add the new variable.
                mParent["Sequence"] = newVar;
                return newVar;
            }

            /// <summary>
            /// Simple Moving average
            /// </summary>
            /// <param name="period"></param>
            /// <returns>Add variable named "Sma".</returns>
            public Variable Sma(int period)
            {
                Timeseries ts = mParent.Default.Sma(period);
                return mParent[ts.Default.Name] = ts.Default;
            }

            /// <summary>
            /// Summation over the specificed period.
            /// </summary>
            /// <param name="period"></param>
            /// <returns>Add variable named "Sum".</returns>
            public Variable Sum(int period)
            {
                Timeseries ts = mParent.Default.Sum(period);
                return mParent[ts.Default.Name] = ts.Default;
            }
        }
        /// <summary>
        /// Convenient access object allowing to use the time series as both the
        /// input and output for a built-in function.
        /// </summary>
        public AddOp Add;
        #endregion

        #region ApplyOp
        /// <summary>
        /// Allows to conveniently transform the Default variable.
        /// </summary>
        public class ApplyOp
        {
            private Timeseries mParent;

            /// <summary>
            /// Constructor
            /// </summary>
            internal ApplyOp(Timeseries parent) { mParent = parent; }

            /// <summary>
            /// Simple Moving average
            /// Perform the function on the default variable.
            /// </summary>
            /// <param name="period"></param>
            /// <returns>A reference on the transformed variable.</returns>
            public Variable Sma(int period)
            {
                return mParent.Default.Apply.Sma(period);
            }

            /// <summary>
            /// Summation over the specified period.
            /// Perform the function on the default variable.
            /// </summary>
            /// <param name="period"></param>
            /// <returns>A reference on the transformed variable.</returns>
            public Variable Sum(int period)
            {
                return mParent.Default.Apply.Sum(period);
            }
        }

        /// <summary>
        /// Convenient access object allowing to transform an existing 
        /// variable.
        /// </summary>
        public ApplyOp Apply;

        /// <summary>
        /// Select a variable to which transformation will be applied.
        /// </summary>
        /// <param name="variableName"></param>
        /// <returns>An access object allowing to call the transformation function.</returns>
        public Variable.ApplyOp ApplyTo(string variableName)
        {
            return this[variableName].Apply;
        }
        #endregion

        #region Built-in functions
        /// <summary>
        /// Simple moving average.
        /// </summary>
        /// <param name="period"></param>
        /// <returns>A new time series with a variable named "Sma".</returns>
        public Timeseries Sma(int period)
        {
            // TODO Speed optimize. In the meantime, this is
            // a good test.
            Timeseries ts = new Timeseries(Timestamps);
            ts["_"] = Default;
            ts.Add.Sma(period);
            ts.Delete("_");
            return ts;
        }

        /// <summary>
        /// Summation over the specified period.
        /// </summary>
        /// <param name="period"></param>
        /// <returns>A new time series with a variable named "Sum".</returns>
        public Timeseries Sum(int period)
        {
            // TODO Speed optimize. In the meantime, this is
            // a good test.
            Timeseries ts = new Timeseries(Timestamps);
            ts["_"] = Default;
            ts.Add.Sum(period);
            ts.Delete("_");
            return ts;
        }

        /// <summary>
        /// Typical price. High+Low+Close/3.0;
        /// </summary>
        /// <returns>A new timeseries with a variable named "TypPrice".</returns>
        public Timeseries TypPrice()
        {
            // TODO Implement properly
            Timeseries ts = new Timeseries(Timestamps);
            ts["TypPrice"] = this["High"] + this["Low"] + this["Close"] / 3.0;
            return ts;
        }

        /// <summary>
        /// Moving Average Convergence/Divergence
        /// </summary>
        /// <returns>A new timeseries with the variable "Macd" and "Signal".</returns>
        public TimeseriesMacd Macd(int fastPeriod, int slowPeriod, int signalPeriod)
        {
            // TODO Implement properly
            TimeseriesMacd ts = new TimeseriesMacd(Timestamps);
            ts.mLine = ts["Line"] = Default;
            ts.mSignal = ts["Signal"] = Default;
            return ts;
        }

        /// <summary>
        /// Technical analysis function Aroon.
        /// </summary>
        /// <returns>A new timeseries with the variable "AroonUp" and "AroonDn".</returns>
        public TimeseriesAroon Aroon(int period)
        {
            // TODO Implement properly
            TimeseriesAroon ts = new TimeseriesAroon(Timestamps);
            ts.mUp = ts["AroonUp"] = this["High"];
            ts.mDown = ts["AroonDown"] = this["Low"];
            return ts;
        }
        #endregion

        #region Static utility function
        /// <summary>
        /// Calculate Pearson's R correlation between two time series.
        /// </summary>
        /// <param name="seriesA"> is a timeseries.</param>
        /// <param name="seriesB"> is a timeseries.</param>
        /// <returns></returns>
        public static double Correl(Timeseries seriesA, Timeseries seriesB)
        {
            return 1.0;
        }

        /// <summary>
        /// Create a new timeseries with Open, High, Low, Close variables 
        /// at the specified period.
        /// 
        /// The input is the default vaiable.
        /// 
        /// Data compression and expansion will take place when needed e.g.
        /// a variable that is of period of 1 second can be compress into 
        /// hourly bar.
        /// 
        /// </summary>
        /// <param name="newPeriod">is the periodicity of the new timeseries created.</param>
        /// <returns>The new timeseries.</returns>
        public Timeseries CreateBar(Periodicity newPeriod)
        {
            // TODO Implement CreateBar
            return createTimeseries();
        }

        /// <summary>
        /// Compress or expand the default variable to a different periodicity.
        /// The new variable is returned in a new Timeseries.
        /// </summary>
        /// <param name="newPeriod">is the periodicity of the new variable.</param>
        /// <param name="flags">are flags to control the algorithm.</param>
        /// <returns>The new timeseries.</returns>
        public Timeseries ConvertPeriod(Periodicity newPeriod, PeriodConvertionFlags flags)
        {
            // TODO Implement ConvertPeriod
            return createTimeseries();
        }

        /// <summary>
        /// Compress or expand the default variable to a different periodicity.
        /// The new variable is returned in a new Timeseries.
        /// </summary>
        /// <param name="newPeriod">is the periodicity of the new variable.</param>
        /// <returns>The new timeseries.</returns>
        public Timeseries ConvertPeriod(Periodicity newPeriod)
        {
            // TODO Implement ConvertPeriod
            return createTimeseries();
        }

        /// <summary>
        /// Compress or expand the "Open","High","Low","Close","Volume" and "OpenInterest"
        /// to a different periodicity.
        /// The new variables are returned in a new Timeseries.
        /// </summary>
        /// <param name="newPeriod">is the periodicity of the new variables.</param>
        /// <param name="flags">are flags to control the algorithm.</param>
        /// <returns>The new timeseries.</returns>
        public Timeseries ConvertBarPeriod(Periodicity newPeriod, PeriodConvertionFlags flags)
        {
            // TODO Implement ConvertPeriod
            return createTimeseries();
        }

        /// <summary>
        /// Compress or expand the "Open","High","Low","Close","Volume" and "OpenInterest"
        /// to a different periodicity.
        /// The new variables are returned in a new Timeseries.
        /// </summary>
        /// <param name="newPeriod">is the periodicity of the new variables.</param>
        /// <returns>The new timeseries.</returns>
        public Timeseries ConvertBarPeriod(Periodicity newPeriod)
        {
            // TODO Implement ConvertPeriod
            return createTimeseries();
        }

        /// <summary>
        /// Return the Pearson correlation between the first two default
        /// variables.
        /// </summary>
        /// <returns> is the pearson-r correlation.</returns>
        public double CorrelValue()
        {
            return 1.0;
        }

        #endregion

        #region Arithmetic operator
        /// <summary>
        /// Add the default variable of two time series.
        /// </summary>
        /// <returns>A new timeseries with the added variables. The new variable is named "Result".</returns>
        public static Timeseries operator +(Timeseries a, Timeseries b)
        {
            return a.Default + b.Default;
        }

        public static Timeseries operator /(Timeseries a, double b)
        {
            return a.Default / b;
        }
        #endregion

        #region Reference on reserved variable name
        // TODO Need to speed optimized direct access functions

        /// <summary>
        /// Allows direct access to the variable named "Open".
        /// If such variable does not exist, an exception is thrown.
        /// </summary>		
        public Variable Open
        {
            get { return this["Open"]; }
        }

        /// <summary>
        /// Allows direct access to the variable named "High".
        /// If such variable does not exist, an exception is thrown.
        /// </summary>
        public Variable High
        {
            get { return this["High"]; }
        }

        /// <summary>
        /// Allows direct access to the variable named "Low".
        /// If such variable does not exist, an exception is thrown.
        /// </summary>
        public Variable Low
        {
            get { return this["Low"]; }
        }

        /// <summary>
        /// Allows direct access to the variable named "Close".
        /// If such variable does not exist, an exception is thrown.
        /// </summary>
        public Variable Close
        {
            get { return this["Close"]; }
        }

        /// <summary>
        /// Allows direct access to the variable named "Volume".
        /// If such variable does not exist, an exception is thrown.
        /// </summary>
        public Variable Volume
        {
            get { return this["Volume"]; }
        }
        #endregion      

}

    public class Timeseries<TVal> :
        Timeseries<Timeseries<TVal>, Variable<TVal>, TVal>
    {
        #region Constructors
        /// <summary>
        /// Default constructor.
        /// </summary>
        public Timeseries() 
        {
            base.Init();
        }

        /// <summary>
        /// Build a time series using an array of DateTime.
        /// </summary>
        /// <param name="dateTime"></param>
        public Timeseries(DateTime[] dateTime)
        {
            base.Init(dateTime);
        }

        public Timeseries(Timestamps timestamps)
        {
            base.Init(timestamps);
        }

        internal Timeseries(Variable<TVal> v)
        {
            base.Init();
            InternalSetVar("Default", v);
        }
        #endregion

        #region Internal Factories
        internal override Variable<TVal> createVariable()
        {
            return new Variable<TVal>(this);
        }

        internal override Variable<TVal> createVariable(TVal[] val)
        {
            return new Variable<TVal>(this, val);
        }

        internal override Variable<TVal> createVariable(TVal[] val, int offset)
        {
            return new Variable<TVal>(this, val, offset);
        }

        internal override Timeseries<TVal> createTimeseries()
        {
            return new Timeseries<TVal>();
        }
        internal override Timeseries<TVal> createTimeseries(DateTime[] dateTime)
        {
            return new Timeseries<TVal>(dateTime);
        }
        internal override Timeseries<TVal> createTimeseries(Timestamps timestamps)
        {
            return new Timeseries<TVal>(timestamps);
        }
        #endregion    
    }


    #region Global Enumerations
    /// <summary>
    /// Specify how synchronization is handled.
    /// 
    /// Synchronization can either be performed by the Timeseries::Sync() function 
    /// or when an out-of-sync variable is added to a time series.
    /// 
    /// On Timeseries::Sync(), Series A and Series B are the two first parameters.
    /// 
    /// On variable addition to a timeseries, Series A designate all the existing 
    /// variables in the timeseries while Series B is the new variable.
    /// </summary>
    public enum SyncMode
    {
        /// <summary>
        /// Action On Missing In Series A: Exception
        /// Action On Missing In Series B: Exception
        /// </summary>
        Mode1,
        /// <summary>
        /// Action On Missing In Series A: Exception
        /// Action On Missing In Series B: Interpolation In Series B
        /// </summary>
        Mode2,
        /// <summary>
        /// Action On Missing In Series A: Exception
        /// Action On Missing In Series B: Delete In Series A
        /// </summary>
        Mode3,
        /// <summary>
        /// Action On Missing In Series A: Delete In Series B
        /// Action On Missing In Series B: Exception
        /// </summary>
        Mode4,
        /// <summary>
        /// Action On Missing In Series A: Delete In Series B
        /// Action On Missing In Series B: Interpolation In Series B
        /// </summary>
        Mode5,
        /// <summary>
        /// Action On Missing In Series A: Delete In Series B
        /// Action On Missing In Series B: Delete In Series A
        /// </summary>
        Mode6,
        /// <summary>
        /// Action On Missing In Series A: Interpolation In Series A
        /// Action On Missing In Series B: Exception
        /// </summary>
        Mode7,
        /// <summary>
        /// Action On Missing In Series A: Interpolation In Series A
        /// Action On Missing In Series B: Interpolation In Series B
        /// </summary>
        Mode8,
        /// <summary>
        /// Action On Missing In Series A: Interpolation In Series A
        /// Action On Missing In Series B: Delete In Series A
        /// </summary>
        Mode9,
    }

    /// <summary>
    /// Depending of the synchronization configuration, missing
    /// values might be calculated base on one of the "Interpolation"
    /// algorithm.	
    /// Interpolation take place only between two existing values
    /// called neighbor.
    /// </summary>
    public enum Interpolation
    {
        /// <summary>
        /// Missing values are same as their oldest neighbor value.
        /// </summary>
        OldestNeighbor,

        /// <summary>
        /// Missing values are same as their more recent neighbor value.
        /// </summary>
        NewestNeighbor,

        /// <summary>
        /// Missing values are replaced by the value specificed by
        /// the property 'FixValue'.
        /// </summary>
        FixValue,

        /// <summary>
        /// The missing values are the average of the oldest and
        /// more recent neighbor.
        /// Important: For TimeSeries of user defined type, this 
        /// will act like OldestNeighbor.
        /// </summary>
        AvgNeighbors,

        /// <summary>
        /// The slope is calculated between the oldest and more 
        /// recent neighbors. The missing values are then replace
        /// according to the linear equation 'y=mx+b'.
        /// Important: For TimeSeries of user defined type, this 
        /// will act like OldestNeighbor.        
        /// </summary>
        Linear
    }

    /// <summary>
    /// The timeseries timestamps can have different representation that are
    /// more convenient to the domain of the application.
    /// </summary>
    public enum Timebase
    {
        /// <summary>
        /// Each Timestamps are represented by the field
        ///  Year, month, day, hour, minute, seconds and milliseconds.
        /// </summary>
        Infinite,

        /// <summary>
        /// The range of the timestamps covers a year.
        /// </summary>
        OneYear,

        /// <summary>
        /// The range of the timestamps covers a month.
        /// </summary>
        OneMonth,

        /// <summary>
        /// The range of the timestamps covers a day.
        /// </summary>
        OneDay,

        /// <summary>
        /// The range of the timestamps covers an hour.
        /// </summary>
        OneHour,

        /// <summary>
        /// The range of the timestamps covers a minute.
        /// </summary>
        OneMinute,

        /// <summary>
        /// The range of the timestamps covers a second.
        /// </summary>
        OneSecond,

        /// <summary>
        /// The first moment is "0", the second "1" and so on...
        /// The year,month,day,hour,minute,second and millisecond field
        /// are unused.
        /// </summary>
        None
    }

    /// <summary>
    /// Specify the amount of time that are covered by each value.
    /// </summary>
    public enum Periodicity
    {
        /// <summary>
        /// Unspecified periodicity.
        /// </summary>
        PerUnknown,
        /// <summary>
        /// Each values represent a period of 1 second.
        /// </summary>
        Per1Sec,
        /// <summary>
        /// Each values represent a period of 2 seconds.
        /// </summary>
        Per2Sec,
        /// <summary>
        /// Each values represent a period of 3 seconds.
        /// </summary>
        Per3Sec,
        /// <summary>
        /// Each values represent a period of 4 seconds.
        /// </summary>
        Per4Sec,
        /// <summary>
        /// Each values represent a period of 5 seconds.
        /// </summary>
        Per5Sec,
        /// <summary>
        /// Each values represent a period of 6 seconds.
        /// </summary>
        Per6Sec,
        /// <summary>
        /// Each values represent a period of 10 seconds.
        /// </summary>
        Per10Sec,
        /// <summary>
        /// Each values represent a period of 12 seconds.
        /// </summary>
        Per12Sec,
        /// <summary>
        /// Each values represent a period of 5 seconds.
        /// </summary>
        Per15Sec,
        /// <summary>
        /// Each values represent a period of 20 seconds.
        /// </summary>
        Per20Sec,
        /// <summary>
        /// Each values represent a period of 30 seconds.
        /// </summary>
        Per30Sec,
        /// <summary>
        /// Each values represent a period of 1 minute.
        /// </summary>
        Per1Min,
        /// <summary>
        /// Each values represent a period of 2 minutes.
        /// </summary>
        Per2Min,
        /// <summary>
        /// Each values represent a period of 3 minutes.
        /// </summary>
        Per3Min,
        /// <summary>
        /// Each values represent a period of 4 minutes.
        /// </summary>
        Per4Min,
        /// <summary>
        /// Each values represent a period of 5 minutes.
        /// </summary>
        Per5Min,
        /// <summary>
        /// Each values represent a period of 6 minutes.
        /// </summary>
        Per6Min,
        /// <summary>
        /// Each values represent a period of 10 minutes.
        /// </summary>
        Per10Min,
        /// <summary>
        /// Each values represent a period of 12 minutes.
        /// </summary>
        Per12Min,
        /// <summary>
        /// Each values represent a period of 15 minutes.
        /// </summary>
        Per15Min,
        /// <summary>
        /// Each values represent a period of 20 minutes.
        /// </summary>
        Per20Min,
        /// <summary>
        /// Each values represent a period of 30 minutes.
        /// </summary>
        Per30Min,
        /// <summary>
        /// Each values represent a period of 1 hour.
        /// </summary>
        Per1Hour,
        /// <summary>
        /// Each values represent a period of 2 hours.
        /// </summary>
        Per2Hour,
        /// <summary>
        /// Each values represent a period of 3 hours.
        /// </summary>
        Per3Hour,
        /// <summary>
        /// Each values represent a period of 4 hours.
        /// </summary>
        Per4Hour,
        /// <summary>
        /// Each values represent a period of 6 hours.
        /// </summary>
        Per6Hour,
        /// <summary>
        /// Each values represent a period of 8 hours.
        /// </summary>
        Per8Hour,
        /// <summary>
        /// Each values represent a period of 12 hours.
        /// </summary>
        Per12Hour,
        /// <summary>
        /// Each values represent a period of a day.
        /// </summary>
        PerDaily,
        /// <summary>
        /// Each values represent a period of a week.
        /// </summary>
        PerWeekly,
        /// <summary>
        /// Each values represent a period of a quarter.
        /// </summary>
        PerQuarterly,
        /// <summary>
        /// Each values represent a period of a year.
        /// </summary>
        PerYearly
    }

    /// <summary>
    /// Allows to control the algorithm used on time compression and expansion.
    /// </summary>
    [FlagsAttribute]
    public enum PeriodConvertionFlags
    {
        /// <summary>
        /// Each variables, except for Volume and OpenInterest, are
        /// compress by calculating the average of all the values
        /// of the corresponding existing variable.
        /// </summary>
        UseAverage,

        /// <summary>
        /// The volume is compress by calculating the average of
        /// all the values of the existing Volume variable.
        /// </summary>
        UseAverageVolume,

        /// <summary>
        /// Same as UseAverageVolume, except that the resulting
        /// compression is always the "Daily Average Volume".
        /// This flag overrids the UseAverageVolume flag.
        /// This flag will not work for compression to
        /// an intraday period.
        /// </summary>
        UseDailyAverageVolume,

        /// <summary>
        /// The OpenInterest is compress by calculating the average 
        /// of all the values of the existing Volume variable.
        /// </summary>
        UseAverageOpenInterest,

        /// <summary>
        /// Same as UseAverageOPenInterest, except that the resulting
        /// compression is always the "Daily Average Open Interest".
        /// This flag overide the UseAverageOpenInterest flag.
        /// This flag will not work for compression to
        /// an intraday period.
        /// </summary>
        UseDailyAverageOpenInterest
    }

    #endregion
        

	#region Timeseries Generic Base
	/// <summary>
	/// Time series allows to aglomerate variables and keep 
	/// these synchronize with a common set of timestamps.
	/// </summary>
    [Serializable()]
    public abstract class Timeseries<TSer, TVar, TVal> : ValueIter, IEnumerable<Index>
        where TSer : Timeseries<TSer, TVar, TVal>
        where TVar : Variable<TSer, TVar, TVal>
    {
		#region Initializer
		protected void Init()
		{
            InitMembers();
		}

		protected void Init(DateTime []dateTime)
		{
            InitMembers();
            initTimestamps( new Timestamps(this,dateTime) );
        }

		protected void Init(Timestamps timestamps)
		{
            InitMembers();            
			initTimestamps( new Timestamps(this, timestamps) );
		}

        protected void Init(int size)
        {
            InitMembers();
            mTimebase = Timebase.None;
            initTimestamps( new Timestamps(this, size) );
        }

        // Special initializer when an empty Timeseries gets its 
        // first variable inserted during an Index iteration.
        internal void InitFromFirstVariable(Index idx)
        {
            if (this.mInitialized == true)
            {
                throw new Exception("Internal Error: Should never re-initialize timeseries");
            }

            initTimestamps( idx.RefTimestamps );
        }

        // This should remain the only function to 
        // initialize mTimestamps.
        private void initTimestamps(Timestamps value)
        {
            if (mTimestamps != null) throw new InternalError();
            if (mInitialized == true) throw new InternalError();
            mTimestamps = value;
            mInitialized = true;
        }

		#endregion

        #region Internal Factories
        internal abstract TVar createVariable();
        internal abstract TVar createVariable(TVal[] val);
        internal abstract TVar createVariable(TVal[] val, int offset );

        internal abstract TSer createTimeseries();
        internal abstract TSer createTimeseries(DateTime[] dateTime);
        internal abstract TSer createTimeseries(Timestamps timestamps);
        #endregion

		#region Public Factories
		/// <summary>
		/// Make a deep copy of the Timeseries.
		/// The new timeseries is independent with a copy
		/// of all the variable(s) and their value(s).
		/// </summary>
		/// <returns>The new timeseries.</returns>
		public TSer Clone()
		{
			// TODO Implement cloning
			return createTimeseries();
		}

		/// <summary>
		/// Allows to express concisely the creation of a new timeseries by 
		/// enumerating a subset of variables of this timeseries. 
		/// Example:
		///    Timeseries ts2 = ts1.Select( "Open", "Close" );
		///    will create a new timeseries ts2 with a copy
		///    of the variable "Open" and "Close" of the
		///    timeseries ts1.
		/// </summary>
		/// <param name="varNameList">is the list of variable's name.</param>
		/// <returns>The new timeseries.</returns>
		public TSer Select( params string[] varNameList )
		{
			// TODO Implement Select
			return createTimeseries();
		}

		/// <summary>
		/// Allows to express concisely the creation of a new time series
		/// built with variables in a specific order. The variables name
		/// in the new time series are unspecified. The user can only 
		/// assume that the variables names are in the proper sorted order. 
		/// </summary>
		/// <param name="varNameList">is the list of variable's name.</param>
		/// <returns>The new timeseries.</returns>
		public TSer SelectInOrder( params string[] varNameList )
		{
			// TODO Implement SelectInOrder
			return createTimeseries();
		}
		#endregion

        /// <summary>
        /// Array of Timestamps.
        /// Accessible with index that range from 0 to Length-1
        /// when Length >= 1
        /// </summary>
        private Timestamps mTimestamps;        

        public Timestamps Timestamps
        {            
            get
            {
                return mTimestamps;
            }
            set { /* Do Nothing */ }
        }
		
		#region AddVariable
		/// <summary>
		/// Build a new named variable from an existing array.
		/// The first entry in the array is assumed aligned with the first timestamps 
		/// that was used to build this timeseries.
		/// </summary>
		/// <param name="variableName">Name of the new variable. If the variable already exist in 
		/// the Timeseries, it will be replaced.</param>
		/// <param name="data">Floating-point values used to build the variable.</param>
		/// <returns>The newly added variable.</returns>
		public TVar AddVariable( string variableName, TVal []data )
		{
            // If not initialized, create Timestamps with a Timebase of None.
            if (mInitialized == false)
            {
                mTimebase = Timebase.None;
                initTimestamps( new Timestamps(this, data.Length) );
            }
			TVar x  = createVariable(data);
			this[variableName] = x;
			return x;
		}

        // Add an un-initialized variable.
        public TVar AddVariable(string variableName)
        {
            if (mInitialized == false)
            {
                mTimebase = Timebase.None;
                initTimestamps( new Timestamps(this,0) );
            }
            TVar x = createVariable();
            this[variableName] = x;
            return x;
        }
		#endregion

		#region Reference on reserved variable name
		/// <summary>
		/// Allows direct access the the default variable
		/// of this timeseries.
		/// </summary>
		public TVar Default
		{
			get 
			{ 
				// TODO Throw an exception when Default is null.
				return mDefault;
			}
		}
		#endregion

		#region Variable Manipulation and Access

		/// <summary>
		/// Rename the default variable.
		/// Take note that upon rename, the variable might not be the 
		/// default anymore.
		/// </summary>
		/// <param name="newName">New name for the variable.</param>
		/// <returns>A reference on the variable being renamed.</returns>
		public TVar Rename( string newName )
		{
            // TODO Throw exception if mVariable is empty.
			if( newName == mVariable.Keys[0] )
				return this[newName];
			else
			{
				TVar x = mVariable.Values[0];
				mVariable.RemoveAt(0);
				return this[newName] = x;
			}
		}
		/// <summary>
		/// Allows to rename a variable.
		/// If the new name is already used by another variable, the renamed variable
		/// will replace the existing variable.
		/// </summary>
		/// <param name="oldName">Name of the variable to be renamed.</param>
		/// <param name="newName">New name for the variable.</param>
		/// <returns>A reference on the variable being renamed.</returns>
		public TVar Rename( string oldName, string newName )
		{
			if( oldName == newName )
				return this[newName];
			else
			{				
				int idx = mVariable.IndexOfKey(oldName);
				// TODO Throw exception on unknown variable.
				TVar x = mVariable.Values[idx];
				mVariable.RemoveAt(idx);
				return this[newName] = x;
			}
		}

		/// <summary>
		/// Delete the specified variable.
		/// </summary>
		/// <param name="varName">The name of the variable to delete.</param>
		public void Delete( string varName )
		{
			int idx = mVariable.IndexOfKey(varName);
			// TODO Throw exception on unknown variable.
			TVar x = mVariable.Values[idx];
			mVariable.RemoveAt(idx);
		}

        /// <summary>
        /// Access to values of the default variable.
        /// </summary>
        public TVal this[Index idx]
        {
            get
            {
                return this.Default[idx];
            }
            set
            {
                this.Default[idx] = value;
            }
        }

		/// <summary>
		/// Access by name to variable belonging to this Timeseries.
		/// </summary>        
        [DebuggerBrowsable(DebuggerBrowsableState.Never)]
        public TVar this[string variableName]
		{
            get
            { 
				int idx = mVariable.IndexOfKey(variableName);
                if (idx == -1)
                {
                    // When not found, create an unitialized variable.
                    // It is up to the context of the variable operation
                    // to determine if this should be an error or not.
                    TVar newVar = createVariable();
                    mVariable.Add( variableName, newVar );
                    return newVar;
                }

                // Return the existing variable.
				return mVariable.Values[idx];
			}

			set { 
                TVar newVar;

                // When assignment from an uninitialized variable, just create
                // a new uninitialized variable with the same name for this object.
                if (value.mInitialized == false)
                    newVar = createVariable();
                else
                {
                    // If no timestamps, take the one from this new variable.
                    if (mTimestamps == null)
                    {
                        initTimestamps( value.Parent.Timestamps );
                    }

                    // Verify if same DateTime array, if not, check for synchronization
                    else if (value.Parent.Timestamps.IsSyncWith(Timestamps) == false)
                    {
                        // TODO All the sync logic					
                    }

                    // Create a new variable pointing on the same timestamps/data.
                    newVar = createVariable(value.mData, value.mTimestampsOffset);

                    // TODO Adjust the new common range.				
                    InternalSetVar(variableName, newVar);
                }

			}
		}

        protected void InternalSetVar(string variableName, TVar newVar)
        {
            // Put the new variable in mVariable.
            if (mVariable.ContainsKey(variableName))
            {
                mVariable.Remove(variableName);
            }
            mVariable.Add(variableName, newVar);

            // Update default variable according to sort logic.
            mDefault = mVariable.Values[0];
        }

		/// <summary>
		/// Add a variable to this time series with the specified name.
		/// If a variable of the same name already exist, it will be replaced.
		/// </summary>
		/// <param name="variableName">Name of the existing or new variable.</param>
		/// <param name="var">The variable that will correspond to that name.</param>
		public void SetVar( string variableName, TVar var )
		{
			this[variableName] = var;
		}

		/// <summary>
		/// Add a variable to this time series with the specified name.
		/// The new variable is built from an array of double.
		/// </summary>
		/// <param name="variableName"> is the name of the existing or new variable.</param>
		/// <param name="data"> is the data.</param>
		public void SetVar( string variableName, TVal[] data )
		{
			this[variableName] = createVariable(data);
		}

		/// <summary>
		/// Access a variable by name.
		/// </summary>
		/// <param name="variableName">The name of the variable.</param>
		/// <returns>The variable corresponding to the specified name.</returns>
		public TVar GetVar( string variableName )
		{
			return this[variableName];
		}

		/// <summary>
		/// Add all variables from a timeseries at once. The variable name
		/// will be appended with the specified prefix.
		/// </summary>
		/// <param name="variablePrefix"> is the prefix added to all variable names.</param>
		/// <param name="timeseries"> is the timeseries providing the variable to be added.</param>
		public void SetAllVar( string variablePrefix, TSer timeseries )
		{
			foreach( TVar var in timeseries.Variables() )
			{				
				this[variablePrefix+var.Name] = var;
			}
		}


		/// <summary>
		/// Verify if a variable exist in this timeseries.
		/// </summary>
		/// <param name="variableName"> is the name of the varaible to look for.</param>
		/// <returns>True if the variable exist in this timeseries, else false.</returns>
		public bool Exist( string variableName )
		{
			int idx = mVariable.IndexOfKey(variableName); 
            return( idx >= 0 );
		}

		/// <summary>
		/// Verify if a variable exist in this timeseries.
		/// </summary>
		/// <param name="variableRef"> is the varaible to look for.</param>
		/// <returns>True if the variable exist in this timeseries, else false.</returns>
		public bool Exist( TVar variableRef )
		{
			int idx = mVariable.IndexOfValue(variableRef);
			return( idx >= 0 );
		}

		#endregion

		#region Value Manipulation and Access
		/// <summary>
		/// Delete all values at the specified dateTime.
		/// </summary>
		/// <param name="dateTime">is the moment for which the values will be deleted.</param>
		public void delValue( DateTime dateTime )
		{
			// TODO 
		}

		/// <summary>
		/// Delete all values at the specified index.
		/// </summary>
		/// <param name="index">is the moment for which the values will be deleted.</param>
		public void delValue( int index )
		{
			// TODO 
		}
		#endregion

		#region Private members

        // A Timeseries is considered initialized when 
        // the timestamps are known.
        private bool mInitialized;

		private TVar mDefault;
        private SyncMode mSyncMode;

        private Timebase mTimebase;

        // Variable identifying the common region.
        private int mOffsetMinStart;
        private int mOffsetMaxStart;
        private int mOffsetMinEnd;
        private int mOffsetMaxEnd;

        private Periodicity mPeriodicity;

        private bool mAllowEmptyVariables;
        private bool mPadding;

        private Interpolation mInterpolation;

        private void InitMembers()
        {
            mInitialized = false;
            mVariable = new SortedList<string,TVar>();            
            mSyncMode = SyncMode.Mode8;
            mAllowEmptyVariables = true;
            mPadding = false;
            mPeriodicity = Periodicity.PerUnknown;
            mInterpolation = Interpolation.Linear;
            mTimebase = Timebase.Infinite;
        }

        private void UpdateOffsets()
        {
            // Iterate among all variables.
            bool firstTime = true;
            foreach (TVar v in this.Variables())
            {
                int start = v.Timestamps.Offset;
                int end = start + v.Timestamps.Length;

                if (firstTime == true)
                {
                    mOffsetMinStart = start;
                    mOffsetMaxStart = start;
                    mOffsetMinEnd = end;
                    mOffsetMaxEnd = end;
                    firstTime = false;
                }
                if (firstTime == true)
                    throw new InternalError();
            }
        }
        #endregion

        internal SortedList<string, TVar> mVariable;

		#region Cast Operator
		/// <summary>
		/// Implicit cast operator from Timeseries to Variable.
		/// </summary>
		/// <param name="ts">The targeted Timeseries.</param>
		/// <returns>The default variable of the timeseries.</returns>
		public static implicit operator TVar(Timeseries<TSer,TVar,TVal> ts)
		{
			return ts.Default;
		}
		#endregion

        #region Properties

        public bool Initialized
        {
            /// <summary>
            /// True when this timeseries have its timestamps initialized.
            /// 
            /// In the case that the timestamps were not specified on creation,
            /// the initialization will occur on the first occurence of:
            /// 
            ///  - Adding a non-empty variable. In which case this timeseries
            ///    will inherit the same Timestamps and Timebase that were used 
            ///    to produce that variable.
            /// 
            ///  OR
            /// 
            ///  - Adding data to an empty variable already belonging to this
            ///    timeseries. In which case this timeseries will have a 
            ///    Timebase "None".
            /// </summary>
            get
            {
                return mInitialized;
            }
        }

        public Timebase Timebase
        {
            /// <summary>
            /// Get the Timebase.
            /// </summary>
            get
            {
                return mTimebase;
            }

            /// <summary>
            /// Set the Timebase.
            /// Valide transitions are:
            ///   Infinite  -- to --> OneYear,OneMonth,OneDay,OneMinute,OneSecond,None
            ///   OneYear   -- to --> OneMonth,OneDay,OneMinute,OneSecond,None
            ///   OneMonth  -- to --> OneDay,OneMinute,OneSecond,None
            ///   OneDay    -- to --> OneMinute,OneSecond,None
            ///   OneMinute -- to --> OneSecond,None
            ///   OneSecond -- to --> None
            /// 
            /// Once Timebase is none, it is not possible to change further this
            /// property.
            /// </summary>
            set
            {
                // TODO Check for all valid transition.

                // Do nothing if no Timebase change.
                if( value == mTimebase ) return;

                if (mTimebase == Timebase.None)
                {
                    throw new Exception("Invalid Timebase property transition");
                }
                
                mTimebase = value;
            }
        }
        
        /// <summary>
        /// When Length is different than zero, Length represents the
        /// range of the index [0..Length-1]
        /// </summary>
        public int Length
        {
            get
            {
                // TODO LEngth veray depending if padding or not.
                return this.Timestamps.Length;
            }
        }

        /// <summary>
        /// Specify the action taken when synchronization is
        /// required when a variable is being added.
        /// </summary>
        public SyncMode SyncMode
        {
            get
            {
                return mSyncMode;
            }
            set
            {
                mSyncMode = value;
            }
        }

        /// <summary>
        /// The user can choose to be notified or not by an exception 
        /// when an operation did generate and empty variable because
        /// of lack of sufficient data from the inputs variables.
        /// </summary>
        public bool AllowEmptyVariables
        {
            get
            {
                return mAllowEmptyVariables;
            }
            set
            {
                mAllowEmptyVariables = value;
            }
        }

        /// <summary>
        /// User can enable padding of a time series for the purpose 
        /// to iterate on the whole range of values among all variables.
        /// </summary>
        public bool Padding
        {
            get
            {
                return mPadding;
            }
            set
            {
                mPadding = value;
            }
        }

        /// <summary>
        /// Specify the amount of time that are covered by each value.
        /// </summary>
        public Periodicity Periodicity
        {
            get
            {
                return mPeriodicity;
            }
            set
            {
                // TODO compression/expansion on period change.
                mPeriodicity = value;
            }
        }

        /// <summary>
        /// Specify how missing values are calculated on interpolation.
        /// Variable can overide this value with their own Interpolation
        /// property.
        /// </summary>
        public Interpolation Interpolation
        {
            get
            {
                return mInterpolation;
            }
            set
            {
                mInterpolation = value;
            }
        }

        /// <summary>
        /// Indicates if the timeseries is uniform or not.
        /// </summary>
        public bool Uniform
        {
            get
            {
                // TODO To be implemented.
                return true;
            }
        }
        #endregion

		#region Static Utility Function
		/// <summary>
		/// Synchronized two time series against each other.
		/// Interpolation will take place in both time series.
		/// (See Mode8 of SyncMode).
		/// </summary>
		/// <param name="seriesA"> is the 1st of the 2 series being synchronized.</param>
		/// <param name="seriesB"> is the 2nd of the 2 series being synchronized.</param>
		public static void Sync( ValueIter seriesA, ValueIter seriesB )
		{
			Sync( seriesA, seriesB, SyncMode.Mode8 );
		}									  
		/// <summary>
		/// Synchronized two time series using a specific SyncMode.
		/// </summary>
		/// <param name="seriesA"> is the 1st of the 2 series being synchronized.</param>
		/// <param name="seriesB"> is the 2nd of the 2 series being synchronized.</param>
		/// <param name="mode"> is the SyncMode to be used.</param>
		public static void Sync( ValueIter seriesA, ValueIter seriesB, SyncMode mode )
		{
		}
		#endregion

        #region ValueIter Members

        internal sealed override Timestamps GetTimestamps()
        {            
            return this.Timestamps;
        }

        internal sealed override bool GetCommonRange(out int begin, out int end)
        {
            if (Padding == true)
            {
                if (this.Timestamps.Length > 0)
                {
                    begin = 0;
                    end = this.Timestamps.Length;
                    return true;
                }
                else
                {
                    begin = end = -1;
                    return false;
                }
            }

            // TODO: Speed optimize once FindCommonRange is proven well debug.
            ValueIter[] list = new ValueIter[mVariable.Count];
            for( int i =0; i < list.Length; i++ )
            {
                list[i] = mVariable.Values[i] as ValueIter; 
            }
            return Index.FindCommonRange(list, out begin, out end);            
        }

        internal sealed override bool IsSame(ValueIter objectToBeTested)
        {
            // Check if 'this'
            if (this.Equals(objectToBeTested))
                return true;

            // Check if the tested object can be found among
            // all variables.             
            foreach(KeyValuePair<string,TVar> p in mVariable)
            {
                if( p.Value.Equals(objectToBeTested) == true )
                    return true;
            }

            // This object is not related to this TimeSeries.
            return false;
        }

        internal sealed override int NbValueIter()
        {
            // A Timeseries has as much ValueIter as variable.
            return mVariable.Count;
        }


        internal sealed override void SetValueIterInfo( ref ValueIterInfo[] iterRef,                                                        
                                                        ref int arrayIdx,
                                                        int commonBegIndex)
        {
            foreach (TVar v in mVariable.Values)
            {
                (v as ValueIter).SetValueIterInfo(ref iterRef, ref arrayIdx, commonBegIndex);
            }
        }

        internal sealed override bool Lock
        {
            // TODO: Really lock the object
            set { mLock = value; }
            get { return mLock; }
        }
        private bool mLock = false;
        #endregion

        // Implementing the enumerable pattern
        public IEnumerable<TVar> Variables()
        {
            for (int i = 0; i < mVariable.Count; i++)
                yield return mVariable.Values[i];
        }

        #region Internal functions for childrens
        internal string VariableName(Variable<TSer,TVar,TVal> var)
        {
            int idx = mVariable.IndexOfValue(var as TVar);
            if (idx == -1)
                return null;
            else
                return mVariable.Keys[idx];
        }
        internal bool IndexValid(int index)
        {
            return (index < this.Timestamps.Offset);
        }
        #endregion

        #region Virtual Functions
        public virtual double ToDouble(TVal p)
        {
            throw new Exception("The method or operation is not implemented.");
        }
        #endregion

        #region IEnumerable<Index> Members
        public override IEnumerator<Index> GetEnumerator()
        {
            Index mIndex = new Index(this);
            return mIndex.GetEnumerator();          
        }
        #endregion
        
        #region IEnumerable Members
        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
        #endregion

        #region operator
        public static Iter operator &(Timeseries<TSer, TVar, TVal> a, ValueIter b)
        {
            return new Iter(a, b);
        }
        #endregion
}

	#region Built-in Return Values
	/// <summary>
	/// Facilitate access to variables returned by the built-in function Macd().
	/// </summary>
	public class TimeseriesMacd : Timeseries
	{
		internal TimeseriesMacd(DateTime []dateTime) : base(dateTime)
		{}

		internal TimeseriesMacd(Timestamps timestamps) : base(timestamps)
		{}

		/// <summary>
		/// The "Line" variable.
		/// </summary>
		public Variable VarLine
		{
			get
			{
				return mLine;
			}
		}

		/// <summary>
		/// The "Signal" variable.
		/// </summary>
		public Variable VarSignal
		{
			get
			{
				return mSignal;
			}
		}

		internal Variable mLine;
		internal Variable mSignal;
	}

	/// <summary>
	/// Facilitate access to variables returned by the built-in function Aroon().
	/// </summary>
	public class TimeseriesAroon : Timeseries
	{
		internal TimeseriesAroon(DateTime []dateTime) : base(dateTime)
		{}

		internal TimeseriesAroon(Timestamps timestamps) : base(timestamps)
		{}

		/// <summary>
		/// The "AroonUp" variable.
		/// </summary>
		public Variable VarUp
		{
			get
			{
				return mUp;
			}
		}

		/// <summary>
		/// The "AroonDown" variable.
		/// </summary>
		public Variable VarDown
		{
			get
			{
				return mDown;
			}
		}

		internal Variable mUp;
		internal Variable mDown;
	}
#endregion
}
#region deprecated
/* About Timeseries<double>
     * ========================
     * A Timeseries is equivalent to a Timeseries<double>
     * plus the functions that can perform calculation e.g.
     * all the technical analysis functions.
     * 
     * From a design perspective, it would have make sense
     * to derive Timeseries from Timeseries<double> and extend it.
     * 
     * In practice, it was preferred to encapsulate the Timeseries<double>
     * and "mimic" its public interface in the Timeseries.
     * 
     * The reason is that inheritance of Timeseries<double> would
     * require a LOT of overiding of public method. These
     * are not speed efficient. Furthermore, casting between
     * Timeseries<double> and Timeseries were often necessary 
     * (and costly).
     * 
     * With the approach of the Timeseries encapsulating the 
     * Timeseries<double>,the call are forward down to the 
     * private Timeseries<double> object. Such call to a
     * non-virtual/non-overidden function is twice faster. 
     * It is assumed that most Timeseries method doing a
     * simple call forward will be inlined.
     */
/*
public class Timeseries : TimeseriesBase 
{
     

    private Timeseries<double> mTimeseriesD;

    #region Constructors
    public Timeseries() : base()
    {
        Init();
    }

    public Timeseries(DateTime[] dateTime)
        : base(dateTime)
    {
        Init();
    }

    internal Timeseries(Timestamps timestamps)
        : base(timestamps)
    {
        Init();
    }
    #endregion



    #region ApplyOp
    /// <summary>
    /// Allows to conveniently transform the Default variable.
    /// </summary>
    public class ApplyOp
    {
        private Timeseries mParent;

        /// <summary>
        /// Constructor
        /// </summary>
        internal ApplyOp(Timeseries parent) { mParent = parent; }

        /// <summary>
        /// Simple Moving average
        /// Perform the function on the default variable.
        /// </summary>
        /// <param name="period"></param>
        /// <returns>A reference on the transformed variable.</returns>
        public Variable<double> Sma(int period)
        {
            return mParent.Default.Apply.Sma(period);
        }
    }

    /// <summary>
    /// Convenient access object allowing to transform an existing 
    /// variable.
    /// </summary>
    public ApplyOp Apply;

    /// <summary>
    /// Select a variable to which transformation will be applied.
    /// </summary>
    /// <param name="variableName"></param>
    /// <returns>An access object allowing to call the transformation function.</returns>
    public Variable.ApplyOp ApplyTo(string variableName)
    {
        return this[variableName].Apply;
    }
    #endregion

    #region Reference on reserved variable name
    // TODO Need to speed optimized direct access functions

    /// <summary>
    /// Allows direct access to the variable named "Open".
    /// If such variable does not exist, an exception is thrown.
    /// </summary>		
    public Variable Open
    {
        get { return mVariable["Open"] as Variable; }
    }

    /// <summary>
    /// Allows direct access to the variable named "High".
    /// If such variable does not exist, an exception is thrown.
    /// </summary>
    public Variable High
    {
        get { return mVariable["High"] as Variable; }
    }

    /// <summary>
    /// Allows direct access to the variable named "Low".
    /// If such variable does not exist, an exception is thrown.
    /// </summary>
    public Variable Low
    {
        get { return mVariable["Low"] as Variable; }
    }

    /// <summary>
    /// Allows direct access to the variable named "Close".
    /// If such variable does not exist, an exception is thrown.
    /// </summary>
    public Variable Close
    {
        get { return mVariable["Close"] as Variable; }
    }

    /// <summary>
    /// Allows direct access to the variable named "Volume".
    /// If such variable does not exist, an exception is thrown.
    /// </summary>
    public Variable Volume
    {
        get { return mVariable["Volume"] as Variable; }
    }

    /// <summary>
    /// Allows direct access the the default variable
    /// of this timeseries.
    /// </summary>
    public Variable Default
    {
        get
        {
            // TODO Throw an exception when Default is null.
            return mDefault as Variable;
        }
    }
    #endregion

    #region Arithmetic Operators
    // TODO Implement all operators properly.

    /// <summary>
    /// Add the default variable of two time series.
    /// </summary>
    /// <returns>A new timeseries with the added variables. The new variable is named "Result".</returns>
    public static Timeseries operator +(Timeseries a, Timeseries b)
    {
        Timeseries ts = new Timeseries(b.Timestamps);
        ts["Result"] = a.mDefault;
        return ts;
    }

    /// <summary>
    /// Add the default variable of this time series to a variable.
    /// </summary>
    /// <returns>A new timeseries with the added variables. The new variable is named "Result".</returns>
    public static Timeseries operator +(Timeseries a, Variable b)
    {
        Timeseries ts = new Timeseries(b.Parent.Timestamps);
        ts["Result"] = b;
        return ts;
    }
    #endregion

    #region private member
    private void Init()
    {
       Add = new AddOp(this);
       Apply = new ApplyOp(this);
    }
    #endregion
}*/  
#endregion
#endregion
