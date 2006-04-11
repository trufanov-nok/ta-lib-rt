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

using System;
using System.Collections.Generic;
using System.Text;
using NUnit.Framework;
using TA.Lib;
using TestData;

namespace SanityTests
{
    [TestFixture]
    public class ByRequirements
    {
        [Test]
        public void R1()
        {            
            Timeseries ts_r1 = new Timeseries(10);

            // Add a sequence 0,1,2,3,4,5,6,7,8,9
            ts_r1.Add.Sequence(delegate(int n) { return n; });
            
            // Apply Sma to the sequence.
            ts_r1.Add.Sma(4);
            
            string output1 = "";
            string output2 = "";
            bool firstTime = true;
            foreach (Index idx in ts_r1)
            {
                if (firstTime == true)
                {
                    Assert.AreEqual(6, idx.PositionToEnd );
                    firstTime = false;
                }
                output1 += ts_r1["Sequence"][idx].ToString() + " ";
                output2 += ts_r1["Sma"][idx].ToString() + " ";
            }
            Assert.AreEqual("3 4 5 6 7 8 9 ", output1);
            Assert.AreEqual("1.5 2.5 3.5 4.5 5.5 6.5 7.5 ", output2);            
        }
    }

    [TestFixture]
    public class ByObjects
    {
        [Test]
        public void IterObject()        
        {            
            Random rand = new Random();
            Timeseries ts1 = new Timeseries(13);
            ts1.Add.Sequence(delegate(int n) { return rand.NextDouble(); });

            Timeseries ts2 = new Timeseries(12);
            ts2.Add.Sequence(delegate(int n) { return n; });

            Timeseries ts3 = new Timeseries(11);
            ts3.Add.Sequence(delegate(int n) { return n; });

            ts3.Rename("Sequence", "Test");
            ts3.Apply.Sma(2);
            Iter iterList = new Iter(ts2,ts1,ts3["Test"]);
            foreach( Index idx in iterList )
            {
                Assert.AreEqual(0, idx.Position);
                Assert.AreEqual(9, idx.PositionToEnd);
                Assert.AreEqual(10, idx.Size);
                break;
            }
        }

        [Test]
        public void IndexObject()
        {
            // Test iterations of 3 values.
            Timeseries tsprev = new Timeseries(3);
            tsprev.Add.Sequence(delegate(int n) { return n; });
            foreach (Index i in tsprev)
            {
                switch (i.Position)
                {
                    case 0:
                        Assert.AreEqual(0, i.Position);
                        Assert.AreEqual(2, i.PositionToEnd);
                        Assert.AreEqual(3, i.Size);
                        Assert.AreEqual(0, tsprev[i]);
                        break;
                    case 1:
                        Assert.AreEqual(1, i.Position);
                        Assert.AreEqual(1, i.PositionToEnd);
                        Assert.AreEqual(3, i.Size);
                        Assert.AreEqual(1, tsprev[i]);
                        Assert.AreEqual(0, tsprev[i - 1]);
                        break;
                    case 2:
                        Assert.AreEqual(2, i.Position);
                        Assert.AreEqual(0, i.PositionToEnd);
                        Assert.AreEqual(3, i.Size);
                        Assert.AreEqual(2, tsprev[i]);
                        Assert.AreEqual(0, tsprev[i - 2]);
                        Assert.AreEqual(2, tsprev[i]);
                        Assert.AreEqual(1, tsprev[i - 1]);
                        Assert.AreEqual(0, tsprev[i - 2]);
                        break;
                    default:
                        Assert.Fail("Unexpected Position");
                        break;
                }
            }

            // Test public 'position' logic for the Index users.
            Timeseries ts = new Timeseries(10);
            ts.Add.Sequence(delegate(int n) { return n; });
            foreach (Index idx in ts)
            {
                Assert.AreEqual(0, idx.Position);
                Assert.AreEqual(9, idx.PositionToEnd);
                Assert.AreEqual(10, idx.Size);
                break;
            }
            ts.Add.Sma(2);

            // Test single variable iterations.
            foreach (Index idx in ts["Sequence"])
            {
                Assert.AreEqual(0, idx.Position);
                Assert.AreEqual(9, idx.PositionToEnd);
                Assert.AreEqual(10, idx.Size);
                break;
            }

            // Test single variable iterations.
            foreach (Index idx in ts["Sma"])
            {
                Assert.AreEqual(0, idx.Position);
                Assert.AreEqual(8, idx.PositionToEnd);
                Assert.AreEqual(9, idx.Size);
                break;
            }

        }
    }

    [TestFixture]
    public class ByUserCase
    {
        class T
        {
            public int i;
            public T Prev(int p)
            {
                  i-=p;
                  return this;
            }
        }

        [Test]
        public void UC5()
       { 
            // Initialize using arrays.
            Timeseries ts = new Timeseries();
            ts.AddVariable("Open", TestData.DailySample.Open);
            ts.AddVariable("High", TestData.DailySample.High);
            ts.AddVariable("Low", TestData.DailySample.Low);
            ts.AddVariable("Close", TestData.DailySample.Close);
            ts.AddVariable("Volume", TestData.DailySample.Volume);
            
            ts["Vydia"] = Vidya(ts["Close"], 14, 7);

            //87.625
            //87.5036
            //...
            //108.3335
            foreach (Index i in ts["Vydia"])
            {
                Console.WriteLine("{0} {1}", ts.Timestamps[i], ts["Vydia"][i]);
            }

            T[] fibarray = new T[4];
            for(int i=0; i < fibarray.Length; i++ )
            {
                fibarray[i] = new T();
                fibarray[i].i = i;
            }

            foreach (T i in fibarray)
            {                
                System.Console.WriteLine(i.Prev(1).i);
            }

            Timeseries ts1 = Timeseries.RandomTimeseriesOHLC(10);


            /*
            User Function
             
            Inputs:Length(NumericSimple), Smooth(NumericSimple);
            Vars: Up(0), Dn(0), UpSum(0), DnSum(0), AbsCMO(0), SC(0);
            Up=IFF(Close>Close[1], Close-Close[1],0);
            Dn=IFF(Close<Close[1],AbsValue(Close-Close[1]),0);
            UpSum=Summation(Up,Length);
            DnSum=Summation(Dn,Length);
            If UpSum+DnSum >0 then
            AbsCMO=AbsValue((UpSum-DnSum)/(UpSum+DnSum));
            SC= 2/(Smooth+1);
            If Currentbar=Length then VIDYA=close;
            If Currentbar>Length then
            VIDYA=(SC*AbsCMO*Close)+((1-(SC*AbsCMO))*VIDYA[1]);
            */

        }

        public Variable Vidya( Variable close, int length, int smooth )
        {
            double sc = 2 / (smooth + 1);

            Variable up    = new Variable();
            Variable dn    = new Variable();
            Variable vidya = new Variable();
            
            foreach (Index i in close )
            {
                if (i.Position >= 1)
                {
                    double delta = close[i]-close[i-1];
                    up[i] = delta > 0 ? delta : 0;
                    dn[i] = delta < 0 ? -delta : 0;
                }
            }
            
            up.Apply.Sum(length);
            dn.Apply.Sum(length);
            
            double absCMO = 0.0;
            foreach (Index i in (close & up & dn) )
            {
                if (i.Position == 0)
                    vidya[i] = close[i];
                else
                {
                    double upSum = up[i];
                    double dnSum = dn[i];
                    if (upSum + dnSum > 0.0)
                        absCMO = Math.Abs((upSum - dnSum) / (upSum + dnSum));

                    vidya[i] = (sc * absCMO * close[i]) + ((1 - (sc * absCMO)) * vidya[i - 1]);
                }
            }

            return vidya;
        }
    }
}
