using System;
using System.Collections.Generic;
using System.Text;
using NUnit.Framework;
using TA.Lib;

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
        public void IndexObject()
        {
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
        }
    }

}
