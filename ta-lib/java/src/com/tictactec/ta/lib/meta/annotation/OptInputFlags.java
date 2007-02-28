package com.tictactec.ta.lib.meta.annotation;

/* The following are flags for optional inputs.
*
* TA_OPTIN_IS_PERCENT:  Input is a percentage.
*
* TA_OPTIN_IS_DEGREE:   Input is a degree (0-360).
*
* TA_OPTIN_IS_CURRENCY: Input is a currency.
*
* TA_OPTIN_ADVANCED:
*    Used for parameters who are rarely changed.
*    Most application can hide these advanced optional inputs to their
*    end-user (or make it harder to change).
*/
public final class OptInputFlags {
    static public final int TA_OPTIN_IS_PERCENT   = 0x00100000;
    static public final int TA_OPTIN_IS_DEGREE    = 0x00200000;
    static public final int TA_OPTIN_IS_CURRENCY  = 0x00400000;
    static public final int TA_OPTIN_ADVANCED     = 0x01000000;
}
