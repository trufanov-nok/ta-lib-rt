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
    // Alias to generic for user convenience.
    public sealed partial class Variable :
        Variable<Timeseries, Variable, double>
    {}

    public sealed class Variable<TVal> :
        Variable<Timeseries<TVal>, Variable<TVal>, TVal>
    {
        #region Constructors
        internal Variable() : base() {}

        internal Variable(Timeseries<TVal> parent)
            : base(parent)
        {            
        }

        internal Variable(Timeseries<TVal> parent, TVal[] newData)
            : base(parent, newData)
        {        
        }

        internal Variable(Timeseries<TVal> parent, TVal[] newData, int offset)
            : base(parent, newData, offset)
        {
        }
        #endregion
    }

    #region Variable Generated section
    /// <summary>
    /// Variable holds floating point representation for distinct moment in time.
    /// A Variable ALWAYS belongs to one and only one Timeseries object.
    /// </summary>
    [Serializable()]
    public sealed partial class Variable
    {
        #region Constructors
        internal Variable() : base() { InitMembers(); }

        internal Variable(Timeseries parent)
            : base(parent)
        {
            InitMembers();
        }

        internal Variable(Timeseries parent, double[] newData)
            : base( parent, newData )
        {
            InitMembers();
        }

        internal Variable(Timeseries parent, double[] newData, int offset)
            : base(parent,newData,offset)
        {
            InitMembers();
        }

        // Utility function for constructors
        private void InitMembers()
        {
            Apply = new ApplyOp(this);
        }
        #endregion

        #region ApplyOp
        /// <summary>
        /// Allows to conveniently transform a variable.
        /// </summary>
        public class ApplyOp
        {
            private Variable mVarParent;

            /// <summary>
            /// Constructor
            /// </summary>
            internal ApplyOp(Variable parent) { mVarParent = parent; }

            /// <summary>
            /// Simple Moving average
            /// </summary>
            /// <param name="period"></param>
            /// <returns>This variable after transformation.</returns>
            public Variable Sma(int period)
            {
                // TODO Direct buffer speed optimization (in-place change).
                Timeseries ts = mVarParent.Sma(period);
                return mVarParent.mParent[mVarParent.Name] = ts.Default;
            }

            // Macd, TypPrice and Aroon have multiple inputs and/or outputs
            // so they are not implemented here.
        }

        /// <summary>
        /// Convenient access object allowing to transform this variable.
        /// </summary>
        public ApplyOp Apply;
        #endregion

        #region Arithmetic Operator
        // TODO Implement operator properly.
        /// <summary>
        /// Add two variables.
        /// </summary>
        /// <returns>A new timeseries with the added variables. The new variable is named "Result".</returns>
        public static Timeseries operator +(Variable a, Variable b)
        {
            Timeseries ts = new Timeseries(b.Parent.Timestamps);
            ts["Result"] = a.Parent.Default;
            return ts;
        }

        /// <summary>
        /// Divide each value of the variable by a double.
        /// </summary>
        /// <returns>A new timeseries with a new variable named "Result".</returns>
        public static Timeseries operator /(Variable a, double b)
        {
            Timeseries ts = new Timeseries(a.Parent.Timestamps);
            Variable vd = ts["Result"];

            vd.StartFillup(0.0);
            foreach (Index idx in new Iter(a,vd))
            {
                vd[idx] = a[idx] / b;
            }
            vd.EndFillup();
            return ts;
        }
        #endregion

        #region Built-in Functions
        /// <summary>
        /// Simple Moving average
        /// </summary>
        /// <param name="period"></param>
        /// <returns>Variable named "SMA_X" where X is the period.</returns>
        public Timeseries Sma(int period)
        {
            // TODO Find the common range of the inputs.

            // Allocate the output and call the function (as needed).
            Variable newVar;
            Timeseries retObject = new Timeseries(mParent.Timestamps);
            int lookback = Core.SMA_Lookback(period);
            int size = mData.Length - lookback;
            if (size <= 0)
                newVar = new Variable(retObject, new double[0]);
            else
            {
                double[] output;
                output = new double[size];
                int outBegIdx, outNbElement;
                Core.SMA( 0, size-1, mData, period, out outBegIdx, out outNbElement, output );                
                output = mData;
                // TODO Throw exception on retCode != TA_SUCCESS
                newVar = new Variable(retObject, output);
            }

            // Add the new variable to the new time series.
            retObject["SMA_" + period] = newVar;
            return retObject;
        }
        #endregion

        #region Misc Utility
        /// <summary>
        /// Create a new timeseries with Open, High, Low, Close variables 
        /// at the specified period.
        /// 
        /// Data compression and expansion will take place when needed e.g.
        /// a variable that is of period of 1 second can be 
        /// compress into hourly bar.
        /// </summary>
        /// <param name="newPeriod">is the periodicity of the new timeseries created.</param>
        /// <returns>The new timeseries.</returns>
        public Timeseries CreateBar(Periodicity newPeriod)
        {
            // TODO Implement CreateBar
            return new Timeseries();
        }

        /// <summary>
        /// Compress or expand one variable to a different periodicity.
        /// The new variable is returned in a new Timeseries.
        /// </summary>
        /// <param name="newPeriod">is the periodicity of the new variable.</param>
        /// <param name="flags">are flags to control the algorithm.</param>
        /// <returns>The new timeseries.</returns>
        public Timeseries ConvertPeriod(Periodicity newPeriod, PeriodConvertionFlags flags)
        {
            // TODO Implement ConvertPeriod
            return new Timeseries();
        }
        /// <summary>
        /// Compress or expand one variable to a different periodicity.
        /// The new variable is returned in a new Timeseries.
        /// </summary>
        /// <param name="newPeriod">is the periodicity of the new variable.</param>
        /// <returns>The new timeseries.</returns>
        public Timeseries ConvertPeriod(Periodicity newPeriod)
        {
            // TODO Implement ConvertPeriod
            return new Timeseries();
        }

        #endregion

        #region Private Members
        #endregion
    }

    #endregion

    #region Variable Generic
    /// <summary>
    /// Variable generic holds distinct value for distinct moment in time.
    /// A variable ALWAYS belongs to one and only one Timeseries generic object.
    /// </summary>
    [Serializable()]
    public class Variable<TSer,TVar,TVal> : IValueIter
        where TSer:Timeseries<TSer,TVar,TVal>
        where TVar:Variable<TSer,TVar,TVal>
    {    
        #region Constructors
        internal Variable(){}

        internal Variable(TSer parent)            
        {
            mParent = parent;
        }

        internal Variable(TSer parent, TVal[] newData)            
        {
            mParent = parent;
            mData = newData;
            //Values = new Values<TVal>(parent, mData);            
        }

        internal Variable(TSer parent, TVal[] newData, int offset)        
        {
            mParent = parent;
            mData = newData;
            mTimestampsOffset = offset;
        }
        #endregion

        #region IValueIter Members
        Timestamps IValueIter.GetTimestamps()
        {
            return mParent.Timestamps;
        }

        int IValueIter.GetStartTimestampOffset()
        {
            if( mData.Length > 0 )
               return mTimestampsOffset;
            else
               return -1;
        }

        int IValueIter.GetEndTimestampOffset()
        {
            if (mData.Length > 0)
                return mTimestampsOffset + mData.Length - 1;
            else
                return -1;
        }

        void IValueIter.SetIndexCache(Index index, int value)
        {
            mIndexRef = index;
            mIndexCache = value;
        }

        int IValueIter.GetIndexCache(Index index)
        {
            if (index.Equals(mIndexRef))
                return mIndexCache;
            else
                return -1;
        }

        private Index mIndexRef = null;
        private int mIndexCache = -1;
        #endregion

        /// <summary>
        /// Array of Timestamps.
        /// Accessible with index that range from 0 to Length-1
        /// when Length >= 1
        /// 
        /// The index range is base on the common range of the
        /// parent timeseries.
        /// </summary>
        public Timestamps Timestamps;

        #region Value Manipulation and Access
        /// <summary>
        /// Array of Values.
        /// 
        /// Accessible with index that range from 0 to Length-1
        /// when Length >= 1
        /// 
        /// The index range is base on the common range of the
        /// parent timeseries.
        /// </summary>
        
        //private ArraySegment<TVal> Values;

        /// <summary>
        /// Change or add a value at the specified moment in time.
        /// </summary>
        /// <param name="dateTime">is where the data is changed or added.</param>
        /// <param name="val">is the new value.</param>
        public void setValue(DateTime dateTime, TVal val)
        {
        }

        /// <summary>
        /// Change or add a value at the specified index of the parent timeseries.
        /// </summary>
        /// <param name="index">is where the data is changed or added.</param>
        /// <param name="val">is the new value.</param>
        public void setValue(int index, TVal val)
        {
        }

        /// <summary>
        /// Access to a value at the specified Index.
        /// </summary>
        public TVal this[Index idx]
        {
            get { return mData[idx.Offset(this)]; }
            set { }
        }
        #endregion

        /// <summary>
        /// Return a string identifier for this variable.
        /// The name is unique among all the variables belonging
        /// to the same Timeseries.
        /// </summary>
        public string Name
        {
            get
            {
                // Search the name among variables of the parent timeseries.
                return  mParent.VariableName(this);                
            }
            set
            {
                // Rename in the parent timeseries.
                string name = mParent.VariableName(this);
                mParent.Rename(name, value);
            }
        }

        #region Properties
        /// <summary>
        /// The Timeseries to which this variable belong.
        /// </summary>
        public TSer Parent
        {
            get
            {
                return mParent;
            }
        }
        #endregion

        #region Internal members
        internal TVal[] mData;
        internal TSer mParent;
        #endregion

        #region Private members
        // Offset in Timestamps of the parent Timeseries.
        private int mTimestampsOffset;
        #endregion        
    
        internal void StartFillup(TVal p)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        internal void EndFillup()
        {
            throw new Exception("The method or operation is not implemented.");
        }

        /*#region Arithmetic Operator
        // TODO Implement operator properly.
        /// <summary>
        /// Add two variables.
        /// </summary>
        /// <returns>A new timeseries with the added variables. The new variable is named "Result".</returns>
        public static Timeseries<double> operator +(Variable<T> a, Variable<T> b)
        {
            // Get access to double data of the variables.
            Variable<double> va = a.Default.ToDouble();
            Variable<double> vb = b.Default.ToDouble();
            
            Timeseries<double> ts = new Timeseries<double>(b.Parent.Timestamps);
            Variable<double> vd = ts["Result"];
            
            vd.StartFillup(0);
            foreach (Index idx in new Iter(va,vb,vd))
            {
                vd[idx] = va[idx] + vb[idx];
            }
            vd.EndFillup();
            return ts;
        }

        /// <summary>
        /// Divide each value of one variable by the corresponding value of another
        /// variable.
        /// </summary>
        /// <returns>A new timeseries with a new variable named "Result".</returns>
        public static Timeseries<double> operator /(Variable<T> a, Variable<T> b)
        {
            // Get access to double data of the variables.
            Variable<double> va = a.Default.ToDouble();
            Variable<double> vb = b.Default.ToDouble();

            Timeseries<double> ts = new Timeseries<double>(b.Parent.Timestamps);
            Variable<double> vd = ts["Result"];

            vd.StartFillup(0);
            foreach (Index idx in new Iter(va, vb, vd))
            {
                vd[idx] = va[idx] / vb[idx];
            }
            vd.EndFillup();
            return ts;
        }   
        #endregion*/
    }
    #endregion
}
