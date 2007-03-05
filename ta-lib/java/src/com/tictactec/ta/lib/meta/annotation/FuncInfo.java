package com.tictactec.ta.lib.meta.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
public @interface FuncInfo {
    String      name();
    String      group();

    String hint() default "";       // FIXME: fix gen_code
    String helpFile() default "";
    int flags();

    int nbInput();
    int nbOptInput();
    int nbOutput();
}
