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
        private IValueIter[] mValueIter;

        public Iter(params IValueIter[] list)
        {
            mValueIter = list.Clone() as IValueIter[];
        }

        public IEnumerator<Index> GetEnumerator()
        {
            Index mIndex = new Index(mValueIter);
            return mIndex.GetEnumerator();
        }
    }
}
