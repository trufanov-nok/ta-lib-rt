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
    public interface IValueIter
    {
        // Access to the timestamps. Used to verify if 
        // synchronization is done.
        Timestamps GetTimestamps();

        // Position of first and last value in common range of this IValueIter.
        // Position is relative to the begining of the array represented
        // by GetTimesstamps().
        bool GetCommonRange(out int begin, out int end);

        // Verify if the tested IValueIter is the same as this object.
        bool IsSame(IValueIter toBeTestedObject);

        // Get the number of ValueIter.
        // (Some ValueIter are collections of ValueIter...)
        int NbValueIter();

        // SetValueIterInfo provides:
        //  - A reference on its ValueIter(s).
        //  - The offset from the beginning of the Timestamps
        //    for every ValueIter.
        //
        // These values should be set in the provided arrays
        // and increment the corresponding index for each 
        // added.
        //
        // The call to NbValueIter() and the number of
        // entries set here MUST be the same.
        void SetValueIterInfo(ref IValueIter[] iterRef,
                              ref int[] begOffset,
                              ref int arrayIdx,
                              int commonBegIndex );
        
        // Cache a value for a given index.
        // Speed optimization for most common case.
        void SetIndexCache(Index index, int value);

        // Return -1 if the cache information is not known.
        int GetIndexCache(Index index);

        // An IValueITer object should blocks all operations
        // that would affect its timestamp common range 
        // while being lock.
        bool Lock {get; set;}

        // All ValueIter must offer a mean to iterate using
        // an index object.
        IEnumerator<Index> GetEnumerator();
    }
}
