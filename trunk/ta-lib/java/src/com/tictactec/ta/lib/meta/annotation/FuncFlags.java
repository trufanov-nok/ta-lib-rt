package com.tictactec.ta.lib.meta.annotation;

public class FuncFlags {
    static public final int TA_FUNC_FLG_OVERLAP     = 0x01000000;   /* Output scale same as input data. */
    static public final int TA_FUNC_FLG_VOLUME      = 0x04000000;   /* Output shall be over the volume data. */
    static public final int TA_FUNC_FLG_UNST_PER    = 0x08000000;   /* Indicate if this function have an unstable 
                                                                     * initial period. Some additional code exist
                                                                     * for these functions for allowing to set that
                                                                     * unstable period. See Documentation.
                                                                     */
    static public final int TA_FUNC_FLG_CANDLESTICK = 0x10000000;   /* Output shall be a candlestick */
}
