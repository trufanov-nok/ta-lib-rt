package com.tictactec.ta.lib.meta.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.PARAMETER)
@Retention(RetentionPolicy.RUNTIME)
public @interface InputParameterInfo {
    InputParameterType  type();
    String              paramName();
    int                 flags(); // bitwise OR of InputFlags
}
