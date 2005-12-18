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
            callMFI();
            callHT();
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

        void callMFI()
        {
            // Fill up some input with dummy data.
            double[] input = new double[10];
            int[] inputInt = new int[10];
            double[] output = new double[10];
            for (int i = 0; i < 10; i++)
            {
                input[i] = (double)i;
            }

            // Perform the call.
            int outBegIdx;
            int outNbElement;
            Core.MFI(0, 9, input, input, input, inputInt, 4, out outBegIdx, out outNbElement, output);
        }

        void callHT()
        {
            // Fill up some input with dummy data.
            double[] input = new double[200];
            double[] output = new double[200];
            for (int i = 0; i < 200; i++)
            {
                input[i] = (double)i;
            }

            // Perform the call.
            int outBegIdx;
            int outNbElement;
            Core.HT_DCPERIOD(0, 199, input, out outBegIdx, out outNbElement, output);
        }

    }
}
