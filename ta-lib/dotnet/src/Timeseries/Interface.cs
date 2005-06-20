using System;
using System.Collections.Generic;
using System.Text;

namespace TA.Lib
{
    public interface IValueIter
    {
        // Access to the timestamps. Used to verify if 
        // synchronization is done.
        Timestamps GetTimestamps();

        // Position of first value in common range (relative to the begining of the timestamps).
        int GetStartTimestampOffset();

        // Position of last value in common range (relative to the begining of the timestamps).
        int GetEndTimestampOffset();

        // Cache a value for an index.
        // Speed optimization for most common case.
        void SetIndexCache(Index index, int value);

        // Return -1 if the cache information is not known.
        int GetIndexCache(Index index);
    }
}
