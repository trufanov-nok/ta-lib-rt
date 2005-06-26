using System;
using TA.Lib;
/*
File 1:
namespace Example
{
    public class MyGeneric<T>
    {
        public T NoOp(T param)
        {
            return param;
        }
    }
}

File 2:
using MyAlias = Example.MyGeneric<int>;
...
   MyAlias obj = new MyAlias();
   int i = obj.NoOp(0);
*/

//using MyGeneric = TA.Lib.MyGeneric<int>;

namespace Tests
{       
	/// <summary>
	/// Perform tests to validate that the coverage of
    /// all the publish requirements.
    /// 
    /// Check also that the publish use cases are working.
    //    
	/// </summary>	
	class TimeseriesRequirementTests
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>		
		public TimeseriesRequirementTests()
		{
/*
            // Generic used as usual.
            MyGeneric<double> obj1 = MyGeneric<double>.Factory();
            double d = obj1.NoOp(1.0);

            // Alias to the generic with default type int.
            MyGeneric obj2 = MyGeneric.Factory();
            int i = obj2.NoOp(0);
*/
			R1();

			// Test Use Cases
			//UC1();
			UC2();
			UC3();
		}

		public static void R1()
		{
			// Create some timeseries to work with.
			Timeseries ts1 = Timeseries.RandomTimeseries(10);
			Timeseries ts2 = Timeseries.RandomTimeseriesOHLC(20);
			
			// (R-25) Rename a variable
			ts1.Rename("Random","Var1");

			// Apply operator. Modify the default variable directly.
			ts1.Apply.Sma(15);
			
			// ApplyTo operator. Modify a named variable directly.
			ts1.ApplyTo("Var1").Sma(10);

			// Add a "SMA_13" variable.
			ts1.Add.Sma(13);

			// Example of chaining (modify the default).
			ts1.Apply.Sma(12).Apply.Sma(4);

			// Example of chaining (creating a new variable this time, not touching ts1).
			Variable z = ts1["SMA_13"];

			// (R-1)
			foreach( Index idx in new Iter(ts1) )
			{
				double e = ts1["SMA_13"][idx];
			}
            
			Timeseries ts3 = Timeseries.RandomTimeseriesOHLC(20);
			Timeseries ts4 = ts1.Macd(12,26,4).VarSignal + ts1.Default;
			ts1["test"] = ts3.Aroon(12).VarDown + ts3.TypPrice();

			ts4 = ts3.Aroon(24);
			
			foreach( Variable var in ts4.Variables() )
			{
				Console.WriteLine( "[{0}]", var.Name );
			}
			
			// User can always call the Core TA-Lib directly.			
			double []input = new double[100];
			double []output = new double[100];
		    /*System.ValueType*/ int outBegIdx=0;
            /*System.ValueType*/ int outNbElement=0;
			Core.SMA( 0, 99, input, 12, out outBegIdx, out outNbElement, output );
		}
/*
		#region UC-1
		class MyIndicator : FunctionBase<double,double>
		{
			Input  open, close;
			Output result;

			public override void Pre()
			{
				open   = MapTo( "Open" );
				close  = MapTo( "Close" );
				result = MapTo( "Result" );
			}

			public override void Iter()
			{
				if( open > close.Prev )
					result.Data = (open + close.Prev)/2.0;
                else 
					result.Data = result.Prev;
			}
		}
       
		public static void UC1()
		{
			// Get Microsoft market data.
			Timeseries ts1 = Timeseries.RandomTimeseriesOHLC(20);

			// Use ts1 as input and ts2 will refer to the output.
			MyIndicator indicator = new MyIndicator();
			Timeseries ts2 = indicator.Exec(ts1);

			// Display the output.
			for( int i=0; i < ts2.Length; i++ )
			{
				Console.WriteLine( ts2["TheOutputName"][i] );
			}
		}
		#endregion
*/
		public static void UC2()
		{
			Timeseries ibm  = Timeseries.RandomTimeseriesOHLC(20); // Market data for IBM.
			Timeseries msft = Timeseries.RandomTimeseriesOHLC(20); // Market data for Microsoft.

			// Static method to synchronize the time series 
			// with each other.
			Timeseries.Sync( ibm, msft );

			// Calculate the typical price.
			Timeseries ts1 = new Timeseries();
			ts1["Price1"] = ibm.TypPrice();
			ts1["Price2"] = msft.TypPrice();

			// Calculate correlations between the two typical prices.
			double correl = ts1.CorrelValue();

			// Display : Approach 1
            foreach( Index idx in new Iter(ts1,ibm,msft) )
            {
				Console.WriteLine( "{0} {1} {2} {3} {4}",
					ibm.Timestamps[idx],
                    ibm.Close[idx],
                    msft.Close[idx],
                    ts1["Price1"][idx],
                    ts1["Price1"][idx]);
			}

			// Display : Approach 2
			// A better speed execution time by creating
			// a reference to the often access variables 
			// once prior to the loop. Still need to
			// put all the variable in the same time series
			// for synchronzation purpose.
			Variable var1 = ibm.Close;
			Variable var2 = msft.Close;
			Variable var3 = ts1["Price1"];
			Variable var4 = ts1["Price2"];
            foreach (Index idx in new Iter(var1,var2,var3,var4))
            {
                Console.WriteLine("{0} {1} {2} {3} {4}",
					var1.Timestamps[idx],
					var1[idx], var2[idx], var3[idx], var4[idx] );
			}

			// Display : Approach 3
			// A different way of creating new time series
			// by adding at once ALL the variables of a
			// time series. The prefix allows to create
			// namespaces to avoid variable name collision 
			// e.g. "Close" exist both in the ibm and msft
			// time series.
			Timeseries ts4 = new Timeseries();
			ts4.SetAllVar( "IBM.", ibm );
			ts4.SetAllVar( "MSFT.", msft );
			ts4.SetAllVar( "_", ts1 );
			foreach( Index idx in new Iter(ts4) )
			{
				Console.WriteLine( "{0} {1} {2} {3} {4}",
					ts4.Timestamps[idx],
					ts4["IBM.Close"][idx],
					ts4["MSFT.Close"][idx],
					ts4["_Price1"][idx],
					ts4["_Price2"][idx] );
			}
		}

		public static void UC3()
		{
			double[] open  = {1.1, 2.1, 3.1, 4.0, 5.0, 6.0};
			double[] high  = {1.3, 2.3, 3.3, 4.3, 5.3, 6.3};
			double[] low   = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
			double[] close = {1.2, 2.2, 3.2, 4.2, 5.2, 6.2};
			int[] volume   = {100, 200, 300, 400, 500, 600};

			// With no timestamp specified, the time series will
			// default the first element to "1970-01-01 00:00:00"
			// (Unix Epoch). The next element is for the next day.
			Timeseries ts1 = new Timeseries();
			ts1.SetVar( "Open", open );
			ts1.SetVar( "High", high );
			ts1.SetVar( "Low", low );
			ts1.SetVar( "Close", close );
			//ts1.SetVar( "Volume", volume );

			// User can perform technical analysis as usual.
			// Here, doing a simple moving average of the typical price.
			ts1["Sma"] = ts1.TypPrice().Sma(3);

			// User can still get a timestamp. The user
			// can calculate the difference in seconds since 
			// the Unix epoch and find that way find the offset of 
			// the output relative to the original plain old arrays.
			DateTime unixEpoch = new DateTime(1970,1,1);
			foreach( Index idx in new Iter( ts1 ) )
			{
				Console.WriteLine( "{0} {1}\n",
					ts1.Timestamps[idx] - unixEpoch,
					ts1["Sma"][idx] );
			}
		}
	}
}