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
    public class Iter
    {
        private Index mIndex;

        public Iter(params IValueIter[] list)
        {
            // Create an Index object.
            mIndex = new Index(list);
        }

        public IEnumerator<Index> GetEnumerator()
        {
            if (mIndex.Size != 0)
            {
                mIndex.Lock = true;
                yield return mIndex;
                while (mIndex.PositionToEnd != 0)
                {
                    mIndex.Next();
                    yield return mIndex;
                }
                mIndex.Lock = false;
            }    
        }
    }
}
