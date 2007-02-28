package com.tictactec.ta.lib.meta.annotation;

/* When the input is a TA_Input_Price, the following 
 * TA_InputFlags indicates the required components.
 * These can be combined for functions requiring more
 * than one component.
 *
 * Example:
 *   (TA_IN_PRICE_OPEN|TA_IN_PRICE_HIGH)
 *   Indicates that the functions requires two inputs
 *   that must be specifically the open and the high.
 */
public final class InputFlags {
    static public final int TA_IN_PRICE_OPEN         = 0x00000001;
    static public final int TA_IN_PRICE_HIGH         = 0x00000002;
    static public final int TA_IN_PRICE_LOW          = 0x00000004;
    static public final int TA_IN_PRICE_CLOSE        = 0x00000008;
    static public final int TA_IN_PRICE_VOLUME       = 0x00000010;
    static public final int TA_IN_PRICE_OPENINTEREST = 0x00000020;
    static public final int TA_IN_PRICE_TIMESTAMP    = 0x00000040;
}
