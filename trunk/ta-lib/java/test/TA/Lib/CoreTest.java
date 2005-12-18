/* TA-LIB Copyright (c) 1999-2006, Mario Fortier
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
 *  121005 MF     First Version
 */

package TA.Lib;

import junit.framework.*;

public class CoreTest extends TestCase {	
    private double input[];
    private int inputInt[];
    private double output[];
    private int outputInt[];
    private MInteger outBegIdx; 
    private MInteger outNbElement;
    private TA_RetCode retCode;
    private TA.Lib.Core lib;
    private int lookback;
    
    public CoreTest(String testName) {
        super(testName);
        // Create the library (typically done only once).
        lib = new TA.Lib.Core();
        input = new double[200];
        inputInt = new int[200];        
        output = new double[200];
        outputInt = new int[200];
        outBegIdx = new MInteger();
        outNbElement = new MInteger();
    }

    protected void setUp() {
    	for( int i=0; i < input.length; i++ )
    	{
    		input[i] = (double)i;
    		inputInt[i] = i;
    	}
    	for( int i=0; i < output.length; i++ )
    	{
    		output[i] = (double)-999999.0;
    		outputInt[i] = -999999;
    	}
    	outBegIdx.value = -1;
    	outNbElement.value = -1;
    	retCode = TA_RetCode.TA_INTERNAL_ERROR;
    	lookback = -1;
    }

    protected void tearDown() 
    {
    	assertEquals(retCode.toString(),TA_RetCode.TA_SUCCESS.toString());
    	assertEquals(lookback,outBegIdx.value);
    }

    public static Test suite() {
        TestSuite suite = new TestSuite(CoreTest.class);
        
        return suite;
    }

    public void testMFI()
    {
    	 lookback = lib.MFI_Lookback(2);
         retCode = lib.MFI(0,input.length-1,input,input,input,inputInt,2,outBegIdx,outNbElement,output);    
    }
    
    public void testHT()
    {
    	lookback = lib.HT_TRENDMODE_Lookback();
    	retCode = lib.HT_TRENDMODE(0,input.length-1,input,outBegIdx,outNbElement,outputInt);
    }
   
    public void testMA_MAMA()
    {
        lookback = lib.MA_Lookback(10,TA_MAType.TA_MAType_MAMA);
        retCode = lib.MA(0,input.length-1,input,10,TA_MAType.TA_MAType_MAMA,outBegIdx,outNbElement,output);        
    }
    
    public void testMA_SMA()
    {
        lookback = lib.MA_Lookback(10,TA_MAType.TA_MAType_SMA);
        retCode = lib.MA(0,input.length-1,input,10,TA_MAType.TA_MAType_SMA,outBegIdx,outNbElement,output);
        assertEquals(outBegIdx.value,9);
    }
    public void testSimpleCall() {        
                
        // Create Input/Output arrays.
        input[0] = 2.0;
        input[1] = 1.2;
        input[2] = 1.5;
                
        // Do the TA function call
        retCode = lib.MAX( 0, 2, input, 2,
                           outBegIdx, outNbElement,
                           output );
        
        // Test the results.
        assertEquals( retCode, TA_RetCode.TA_SUCCESS);
        assertEquals( outBegIdx.value, 1 );
        assertEquals( outNbElement.value, 2 );
        assertEquals( output[0], 2.0 );
        assertEquals( output[1], 1.5 );
        
        lookback = lib.MAX_Lookback(2);
    }    
}
