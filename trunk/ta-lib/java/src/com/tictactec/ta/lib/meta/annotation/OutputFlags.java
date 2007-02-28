package com.tictactec.ta.lib.meta.annotation;


public final class OutputFlags {
    static public final int TA_OUT_LINE              = 0x00000001; /* Suggest to display as a connected line. */
    static public final int TA_OUT_DOT_LINE          = 0x00000002; /* Suggest to display as a 'dotted' line. */
    static public final int TA_OUT_DASH_LINE         = 0x00000004; /* Suggest to display as a 'dashed' line. */
    static public final int TA_OUT_DOT               = 0x00000008; /* Suggest to display with dots only. */
    static public final int TA_OUT_HISTO             = 0x00000010; /* Suggest to display as an histogram. */
    static public final int TA_OUT_PATTERN_BOOL      = 0x00000020; /* Indicates if pattern exists (!=0) or not (0) */
    static public final int TA_OUT_PATTERN_BULL_BEAR = 0x00000040; /* =0 no pattern, > 0 bullish, < 0 bearish */
    static public final int TA_OUT_PATTERN_STRENGTH  = 0x00000080; /* =0 neutral, ]0..100] getting bullish, ]100..200] bullish, [-100..0[ getting bearish, [-200..100[ bearish */
    static public final int TA_OUT_POSITIVE          = 0x00000100; /* Output can be positive */
    static public final int TA_OUT_NEGATIVE          = 0x00000200; /* Output can be negative */
    static public final int TA_OUT_ZERO              = 0x00000400; /* Output can be zero */
}
