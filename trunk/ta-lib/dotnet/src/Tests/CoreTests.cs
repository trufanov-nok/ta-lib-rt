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
        }

        void simpleMACall()
        {
            // Just check that the following still compile/link.
            double []input = new double[10];
            double []output = new double[10];
            int outBegIdx;
            int outNbElement;

            // Fill up the input with dummy data.
            for( int i=0; i < 10; i++ )
            {        
               input[i] = (double)i; 
            }

            // Perform the call.
            Core.ATR(0, 9, input, input, input, 4, out outBegIdx, out outNbElement, output);
        }
    }
}
