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
            while (mIndex.LeftToIterate != 0)
            {
                yield return mIndex;
                mIndex.Next();
            }
            yield break;
        }
    }
}
