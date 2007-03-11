/* TA-LIB Copyright (c) 1999-2007, Mario Fortier
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
 *  RG       Richard Gomes
 *
 * Change history:
 *
 *  YYYYMMDD BY     Description
 *  -------------------------------------------------------------------
 *  20070311 RG     First Version
 */

package com.tictactec.ta.lib.meta;

import java.util.ArrayList;
import java.util.List;

import com.tictactec.ta.lib.meta.annotation.InputFlags;

/**
 * PriceHolder is reponsible for holding arrays relative to OHLCVI (open, high, low, close, volume, open interest) data points.
 * 
 * @author Richard Gomes
 */
public class PriceHolder {
    private int flags;
    List<double[]> list;
    
    /**
     * Constructs a PriceHolder by passing the an int value defined by <b>InputFlags</b> and all <b>double[]</b> assignment
     * compatible data point arrays which are referenced by the flags informed.
     * 
     * @param flags is an int built by ORing the values defined by InputFlags enum
     * @param open represent the open data points and is expected to be <b>double[]</b> assignment compatible.
     * @param high represent the high data points and is expected to be <b>double[]</b> assignment compatible.
     * @param low represent the low data points and is expected to be <b>double[]</b> assignment compatible.
     * @param close represent the close data points and is expected to be <b>double[]</b> assignment compatible.
     * @param volume represent the volume data points and is expected to be <b>double[]</b> assignment compatible.
     * @param openInterest represent the open interest data points and is expected to be <b>double[]</b> assignment compatible.
     * @throws NullPointerException
     */
    public PriceHolder(int flags, double[] open, double[] high, double[] low, double[] close, double[] volume, double[] openInterest) 
            throws NullPointerException {

        this.flags = flags;
        list = new ArrayList<double[]>();
        
        if ((flags&InputFlags.TA_IN_PRICE_OPEN)!=0) {
            if (open==null) throw new NullPointerException("open array is null");
            list.add(open);
        }
        if ((flags&InputFlags.TA_IN_PRICE_HIGH)!=0) {
            if (high==null) throw new NullPointerException("high array is null");
            list.add(high);
        }
        if ((flags&InputFlags.TA_IN_PRICE_LOW)!=0) {
            if (low==null) throw new NullPointerException("low array is null");
            list.add(low);
        }
        if ((flags&InputFlags.TA_IN_PRICE_CLOSE)!=0) {
            if (close==null) throw new NullPointerException("close array is null");
            list.add(close);
        }
        if ((flags&InputFlags.TA_IN_PRICE_VOLUME)!=0) {
            if (volume==null) throw new NullPointerException("volume array is null");
            list.add(volume);
        }
        if ((flags&InputFlags.TA_IN_PRICE_OPENINTEREST)!=0) {
            if (openInterest==null) throw new NullPointerException("open interest array is null");
            list.add(openInterest);
        }
    }
    
    /**
     * @return the flags informed when this object was constructed
     */
    public int getFlags() {
        return flags;
    }
    
    /**
     * @return the arrays of data points informed when this object was constructed
     */
    public Object[] toArray() {
        return list.toArray();
    }
    
    /**
     * @return the maximun number of arrays of data points possibly hold by this class and is equilavent of:
     * <pre>
     * this.toArray().size();
     * </pre> 
     */
    public int size() {
        return list.size();
    }
    
}


