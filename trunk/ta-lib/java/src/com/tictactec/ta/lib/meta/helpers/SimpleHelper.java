package com.tictactec.ta.lib.meta.helpers;

import java.lang.reflect.InvocationTargetException;
import java.util.List;

import com.tictactec.ta.lib.MInteger;
import com.tictactec.ta.lib.meta.CoreMetaData;
import com.tictactec.ta.lib.meta.annotation.FuncInfo;
import com.tictactec.ta.lib.meta.annotation.InputParameterInfo;
import com.tictactec.ta.lib.meta.annotation.InputParameterType;
import com.tictactec.ta.lib.meta.annotation.IntegerList;
import com.tictactec.ta.lib.meta.annotation.IntegerRange;
import com.tictactec.ta.lib.meta.annotation.OptInputParameterInfo;
import com.tictactec.ta.lib.meta.annotation.OutputParameterInfo;
import com.tictactec.ta.lib.meta.annotation.OutputParameterType;
import com.tictactec.ta.lib.meta.annotation.RealList;
import com.tictactec.ta.lib.meta.annotation.RealRange;

public class SimpleHelper {
    
    private String   func = null;
    private String[] args = null;
    private CoreMetaData calc = null;
    
    public SimpleHelper(final String func, final List<String> args) {
        if (func==null || func.length()==0) throw new NullPointerException(); //TODO: message
        this.func = func;
        if (args!=null && args.size()>0) {
            this.args = (String[]) args.toArray(new String[0]);
            for (int i=0; i<this.args.length; i++) { this.args[i] = this.args[i].toUpperCase(); }
        }
    }

    public CoreMetaData getMetaData() throws NoSuchMethodException, IllegalArgumentException {
        if (this.calc!=null) return this.calc;
        this.calc = CoreMetaData.getInstance(func);
        FuncInfo finfo = calc.getFuncInfo();
        if (args.length>finfo.nbOptInput()) throw new IllegalArgumentException(); //TODO:message
        for (int i=0; i<args.length; i++) {
            OptInputParameterInfo ppinfo = calc.getOptInputParameterInfo(i);
            if (ppinfo.dataSet().isAssignableFrom(IntegerList.class) || ppinfo.dataSet().isAssignableFrom(IntegerRange.class)) {
                calc.setOptInputParamInteger(i, args[i]);
            } else if (ppinfo.dataSet().isAssignableFrom(RealList.class) || ppinfo.dataSet().isAssignableFrom(RealRange.class)) {
                calc.setOptInputParamReal(i, args[i]);
            } else {
                throw new ClassCastException(); //TODO: message
            }
        }
        return this.calc;
    }

    public int getLookback() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
        return getMetaData().getLookback();
    }
    
    public void calculate(final int startIndex, final int endIndex,
            final Object[] inputs, Object[] outputs,
            MInteger outBegIdx, MInteger outNbElement)
                throws IllegalArgumentException, NoSuchMethodException, IllegalAccessException, InvocationTargetException {

        //for (int i=startIndex; i<startIndex+endIndex; i++) {
        //    System.err.println("input["+i+"]="+((double[])(inputs[0]))[i]);
        //}
        
        // parse function name and optional arguments
        FuncInfo finfo = getMetaData().getFuncInfo();
        // set input parameters
        if (inputs==null  || inputs.length!=finfo.nbInput()) throw new IllegalArgumentException(); //TODO:message
        for (int i=0; i<inputs.length; i++) {
            InputParameterInfo ipinfo = calc.getInputParameterInfo(i);
            if (ipinfo.type()==InputParameterType.TA_Input_Price) {
                calc.setInputParamPrice(i, inputs[i]);
            } else if (ipinfo.type()==InputParameterType.TA_Input_Real) {
                calc.setInputParamReal(i, inputs[i]);
            } else if (ipinfo.type()==InputParameterType.TA_Input_Integer) {
                calc.setInputParamInteger(i, inputs[i]);
            } else {
                throw new IllegalArgumentException(); //TODO: message
            }
        }
        // set output parameters
        if (outputs==null || outputs.length!=finfo.nbOutput()) throw new IllegalArgumentException(); //TODO:message
        for (int i=0; i<outputs.length; i++) {
            OutputParameterInfo opinfo = calc.getOutputParameterInfo(i);
            if (opinfo.type()==OutputParameterType.TA_Output_Real) {
                calc.setOutputParamReal(i, outputs[i]);
            } else if (opinfo.type()==OutputParameterType.TA_Output_Integer) {
                calc.setOutputParamInteger(i, outputs[i]);
            } else {
                throw new IllegalArgumentException(); //TODO: message
            }
        }
        // call function
        calc.callFunc(startIndex, endIndex, outBegIdx, outNbElement); 
    }
    
}
