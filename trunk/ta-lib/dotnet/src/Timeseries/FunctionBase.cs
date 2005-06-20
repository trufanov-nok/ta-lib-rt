using System;

namespace TA.Lib
{
	/// <summary>
	/// Allows to build a function to create and transform variables.
	/// </summary>
	public class FunctionBase<TInput,TOutput>
	{		
		/// <summary>
		/// Oject allowing to create Input and Output object being
		/// map to variable names of timeseries.
		/// </summary>
		public class MapToOp
		{
			private string mTimeseriesVarName;
			/// <summary>
			/// Name of the variable in the timeseries.
			/// </summary>
			public string TimeseriesVarName
			{
				get
				{
					return mTimeseriesVarName;
				}
			}
			internal MapToOp( string varName )
			{
				mTimeseriesVarName = varName;
			}

			/// <summary>
			/// Return an Input being map to the corresponding named variable
			/// of the input timeseries.
			/// </summary>
			/// <param name="d"> is the name of the variable.</param>
			/// <returns> a reference on the Input object.</returns>
			public static implicit operator Input(MapToOp d)
			{
				return new Input( d.mTimeseriesVarName );
			}

			/// <summary>
			/// Return an Output map to the corresponding named variable
			/// of the output timeseries.
			/// </summary>
			/// <param name="d"> is the name of the variable.</param>
			/// <returns> a reference on the Output object.</returns>
			public static implicit operator Output(MapToOp d)
			{
				return new Output( d.mTimeseriesVarName );
			}
		}

		/// <summary>
		/// Allows to have variable for temporary storage
		/// while doing iteration.
		/// </summary>
		public class Var
		{
			internal Var()
			{
			}

			/// <summary>
			/// Implicit conversion of a variable to a double.
			/// The value is the one at the latest index.
			/// </summary>
			/// <param name="d"> is the target variable.</param>
			/// <returns> the value of the variable at the latest index.</returns>
			public static implicit operator double(Var d)
			{
				return 1.0;
			}

			/// <summary>
			/// Access to the value at the latest index.
			/// </summary>
			public double Data
			{
				get
				{
					return 1.0;
				}
				set
				{}
			}

			/// <summary>
			/// Access to the previous value.
			/// </summary>
			/// <returns> the previous value.</returns>
			public double Prev
			{
				get
				{
					return 1.0;
				}
				
			}

			/// <summary>
			/// Access to older values 'nbBars' ago.
			/// If 'n' == 0, it returns the current value.
			/// If 'n' == 1, it returns the previous value.
			/// If 'n' == 2, it returns the value before the previous.
			/// ...
			/// </summary>
			/// <returns> the value 'nBars' ago.</returns>
			public double Previous( int nbBars )
			{
				return 1.0;
			}
		}

		/// <summary>
		/// Define an input variable for the function.
		/// </summary>
		public class Input : Var
		{
			private string mTimeseriesVarName;
			/// <summary>
			/// Each 'Input' are map to a variable of the input timeseries.
			/// </summary>
			public string TimeseriesVarName
			{
				get
				{
					return mTimeseriesVarName;
				}
			}			
			internal Input( string mapToName )
			{
				mTimeseriesVarName = mapToName;
			}
		}
		/// <summary>
		/// Define an output variable for the function.
		/// </summary>
		public class Output : Var
		{		
			private string mTimeseriesVarName;
			/// <summary>
			/// Each 'Input' are map to a variable of the input timeseries.
			/// </summary>
			public string TimeseriesVarName
			{
				get
				{
					return mTimeseriesVarName;
				}
			}

			internal Output( string mapToName )
			{
				mTimeseriesVarName = mapToName;
			}
		}

		/// <summary>
		/// Allows to map a Input or a Output to a variable of 
		/// the corresponding input and output timeseries.
		/// </summary>
		/// <param name="name"> name of the variable.</param>
		/// <returns> an Input or an Output object.</returns>
		public MapToOp MapTo( string name )
		{
			return new MapToOp(name);
		}

		/// <summary>
		/// Connect a variable to a named variable in the input timeseries.
		/// </summary>
		/// <param name="inVar"> is the 'Input' reference to initialize.</param>
		/// <param name="name"> is the name of the corresponding variable in the input timeseries.</param>
		public void Map( out Input inVar, string name )
		{
			inVar = new Input("test");
		}

		/// <summary>
		/// Connect a variable to a named variable in the output timeseries.
		/// </summary>
		/// <param name="outVar"> is the 'Input' reference to initialize.</param>
		/// <param name="name"> is the name of the corresponding variable in the input timeseries.</param>
		public void Map( out Output outVar, string name )
		{
			outVar = new Output("test");
		}

		/// <summary>
		/// Function called for each value of the timeseries.
		/// </summary>
		public virtual void Iter()
		{
		}

		/// <summary>
		/// Function called prior to the iteration.
		/// </summary>
		public virtual void Pre()
		{
		}
		/// <summary>
		/// Function called after the iteration is completed.
		/// </summary>
		public virtual void Post()
		{
		}

		/// <summary>
		/// Execute the function on a timeseries.
		/// </summary>
		public Timeseries<double> Exec( Timeseries<double> input )
		{
			Pre();
			for( int i=0; i < input.Length; i++ )
			{
				Iter();
			}
			Post();
			return (Timeseries<double>)input.Clone();
		}
	}
}
