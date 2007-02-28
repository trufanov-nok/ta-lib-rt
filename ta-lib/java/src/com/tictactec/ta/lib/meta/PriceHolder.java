package com.tictactec.ta.lib.meta;

import java.util.ArrayList;
import java.util.List;

import com.tictactec.ta.lib.meta.annotation.InputFlags;

public class PriceHolder {
    private int flags;
    List<double[]> list;
    
    PriceHolder(int flags, double[] open, double[] high, double[] low, double[] close, double[] volume, double[] openInterest) {
        this.flags = flags;
        list = new ArrayList<double[]>();
        
        if ((flags&InputFlags.TA_IN_PRICE_OPEN)!=0) {
            if (open==null) throw new NullPointerException(); //TODO: message
            list.add(open);
        }
        if ((flags&InputFlags.TA_IN_PRICE_HIGH)!=0) {
            if (high==null) throw new NullPointerException(); //TODO: message
            list.add(high);
        }
        if ((flags&InputFlags.TA_IN_PRICE_LOW)!=0) {
            if (low==null) throw new NullPointerException(); //TODO: message
            list.add(low);
        }
        if ((flags&InputFlags.TA_IN_PRICE_CLOSE)!=0) {
            if (close==null) throw new NullPointerException(); //TODO: message
            list.add(close);
        }
        if ((flags&InputFlags.TA_IN_PRICE_VOLUME)!=0) {
            if (volume==null) throw new NullPointerException(); //TODO: message
            list.add(volume);
        }
        if ((flags&InputFlags.TA_IN_PRICE_OPENINTEREST)!=0) {
            if (openInterest==null) throw new NullPointerException(); //TODO: message
            list.add(openInterest);
        }
    }
    
    public int getFlags() {
        return flags;
    }
    
    public Object[] toArray() {
        return list.toArray();
    }
}


