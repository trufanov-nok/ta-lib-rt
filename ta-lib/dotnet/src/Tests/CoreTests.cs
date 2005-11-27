/****************************** BIG WARNING ********************
 *   Only the code in TA-Lib-Core for .NET is mature.
 * 
 *   All code in TA-Lib-Timeseries is in development and is 
 *   not yet ready for use in applications.
 ****************************** BIG WARNING ********************/

using System;
using System.Collections.Generic;
using System.Text;
using TA.Lib;

namespace Tests
{
    class CoreTests
    {
        public CoreTests()
        {
            simpleMACall();
            averageTrueRangeTest();
        }

        void simpleMACall()
        {
            // Fill up some input with dummy data.
            double[] input = new double[10];
            double []output = new double[10];
            for( int i=0; i < 10; i++ )
            {        
               input[i] = (double)i; 
            }

            // Perform the call.
            int outBegIdx;
            int outNbElement;
            Core.SMA(0, 9, input, 2, out outBegIdx, out outNbElement, output);
        }

        void averageTrueRangeTest()
        {
            // Fill up some input with dummy data.
            double[] input = new double[10];
            double[] output = new double[10];
            for (int i = 0; i < 10; i++)
            {
                input[i] = (double)i;
            }

            // Perform the call.
            int outBegIdx;
            int outNbElement;
            Core.ATR(0, 9, input, input, input, 4, out outBegIdx, out outNbElement, output);
        }

    }
}
