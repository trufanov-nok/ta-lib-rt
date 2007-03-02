package com.tictactec.ta.lib.meta;

import java.util.ArrayList;
import java.util.List;

import com.tictactec.ta.lib.meta.annotation.InputFlags;

public class PriceHolder {
    private int flags;
    List<double[]> list;
    
    public PriceHolder(int flags, double[] open, double[] high, double[] low, double[] close, double[] volume, double[] openInterest) {
        this.flags = flags;
        list = new ArrayList<double[]>();
        
        if ((flags&InputFlags.TA_IN_PRICE_OPEN)!=0) {
            if (open==null) throw new NullArrayException("open");
            list.add(open);
        }
        if ((flags&InputFlags.TA_IN_PRICE_HIGH)!=0) {
            if (high==null) throw new NullArrayException("high");
            list.add(high);
        }
        if ((flags&InputFlags.TA_IN_PRICE_LOW)!=0) {
            if (low==null) throw new NullArrayException("low");
            list.add(low);
        }
        if ((flags&InputFlags.TA_IN_PRICE_CLOSE)!=0) {
            if (close==null) throw new NullArrayException("close");
            list.add(close);
        }
        if ((flags&InputFlags.TA_IN_PRICE_VOLUME)!=0) {
            if (volume==null) throw new NullArrayException("volume");
            list.add(volume);
        }
        if ((flags&InputFlags.TA_IN_PRICE_OPENINTEREST)!=0) {
            if (openInterest==null) throw new NullArrayException("open interest");
            list.add(openInterest);
        }
    }
    
    public int getFlags() {
        return flags;
    }
    
    public Object[] toArray() {
        return list.toArray();
    }
    
    public int size() {
        return list.size();
    }
    
    private class NullArrayException extends NullPointerException {
        
        public NullArrayException(String name) {
            super(name + "array is null");
        }
    }
}


