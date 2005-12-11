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
    
    public CoreTest(String testName) {
        super(testName);
    }

    protected void setUp() throws Exception {
    }

    protected void tearDown() throws Exception {
    }

    public static Test suite() {
        TestSuite suite = new TestSuite(CoreTest.class);
        
        return suite;
    }

    public void testSimpleCall() {        
        // Create the library (typically done only once).
        TA.Lib.Core lib = new TA.Lib.Core();
                
        // Create Input/Output arrays.
        double input[] = new double[3];
        double output[] = new double[2];
        input[0] = 2.0;
        input[1] = 1.2;
        input[2] = 1.5;
        
        // Create two mutable Integer objects to facilitate multiple 
        // return values from a single function call.
        MInteger outBegIdx = new MInteger();
        MInteger outNbElement = new MInteger();
        
        // Do the TA function call
        TA_RetCode retCode = lib.MAX( 0, 2, input, 2,
                                      outBegIdx, outNbElement,
                                      output );
        
        // Use the results.
        if( retCode == TA_RetCode.TA_SUCCESS )
        {
           // Will display "1   2   2.0   1.5"
	   System.out.println( outBegIdx.value + "    " + 
                               outNbElement.value + "    " + 
                               output[0] + "    " + 
                               output[1] );
        }
    }    
}
