package com.tictactec.ta.lib.meta.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.PARAMETER)
@Retention(RetentionPolicy.RUNTIME)
public @interface RealRange {
    String  paramName();
    double  defaultValue();
    double  min();
    double  max();
    int     precision(); /* nb of digit after the '.' */

    /* The following suggested value are used by Tech. Analysis software
     * doing parameter "optimization". Can be ignored by most user.
     */
    double     suggested_start();
    double     suggested_end();
    double     suggested_increment();
}
