package com.tictactec.ta.lib.meta;

import java.lang.annotation.IncompleteAnnotationException;

import com.tictactec.ta.lib.RetCode;
import com.tictactec.ta.lib.meta.annotation.FuncInfo;
import com.tictactec.ta.lib.meta.annotation.InputParameterInfo;
import com.tictactec.ta.lib.meta.annotation.OptInputParameterInfo;
import com.tictactec.ta.lib.meta.annotation.OutputParameterInfo;

public class CoreMetaDataCompatibility extends CoreMetaData {

    static RetCode taGetFuncHandle(final String name, CoreMetaData retHandle) {
        try {
            retHandle = getFuncHandle(name);
            return RetCode.Success;
        } catch (NoSuchMethodException e) {
            return RetCode.BadParam;
        }
    }
    

    RetCode taGetFuncInfo(FuncInfo retFuncInfo) {
        try {
            retFuncInfo = super.getFuncInfo();
            return RetCode.Success;
        } catch (IncompleteAnnotationException e) {
            return RetCode.InternalError;
        }
    }
    

    RetCode taGetInputParameterInfo(final int paramIndex, InputParameterInfo retInputParameterInfo) {
        try {
            retInputParameterInfo = super.getInputParameterInfo(paramIndex);
            return RetCode.Success;
        } catch (IllegalArgumentException e) {
            return RetCode.BadParam;
        }
    }


    RetCode taGetInputParameterInfo(final int paramIndex, OptInputParameterInfo retOptInputParameterInfo) {
        try {
            retOptInputParameterInfo = super.getOptInputParameterInfo(paramIndex);
            return RetCode.Success;
        } catch (IllegalArgumentException e) {
            return RetCode.BadParam;
        }
    }


    RetCode taGetOutputParameterInfo(final int paramIndex, OutputParameterInfo retOutputParameterInfo) {
        try {
            retOutputParameterInfo = super.getOutputParameterInfo(paramIndex);
            return RetCode.Success;
        } catch (IllegalArgumentException e) {
            return RetCode.BadParam;
        }
    }


    RetCode taSetInputParamIntegerPtr(final int paramIndex, final int[] value ) {
        try {
            super.setInputParamInteger(paramIndex, value);
            return RetCode.Success;
        } catch (NullPointerException e) {
            return RetCode.BadParam;
        }
    }

    
    RetCode taSetInputParamRealPtr(final int paramIndex, final double[] value ) {
        try {
            super.setInputParamReal(paramIndex, value);
            return RetCode.Success;
        } catch (NullPointerException e) {
            return RetCode.BadParam;
        }
    }

    
    RetCode taSetInputParamPricePtr(final int paramIndex,
            final double[] open,
            final double[] high,
            final double[] low,
            final double[] close,
            final double[] volume,
            final double[] openInterest) {
        try {
            super.setInputParamPrice(paramIndex, open, high, low, close, volume, openInterest);
            return RetCode.Success;
        } catch (NullPointerException e) {
            return RetCode.BadParam;
        }
    }
    
    
    RetCode taSetOptInputParamInteger(final int paramIndex, final int optInValue) {
        try {
            setOptInputParamInteger(paramIndex, optInValue);
            return RetCode.Success;
        } catch (IllegalArgumentException e) {
            return RetCode.BadParam;
        }
    }
        
    
    RetCode taSetOptInputParamReal(final int paramIndex, final double optInValue) {
        try {
            setOptInputParamReal(paramIndex, optInValue);
            return RetCode.Success;
        } catch (IllegalArgumentException e) {
            return RetCode.BadParam;
        }
    }
    
   
    RetCode taSetOutputParamIntegerPtr(final int paramIndex, int[] outArray) {
        if (outArray == null) return RetCode.BadParam;
        try {
            setOutputParamInteger(paramIndex, outArray);
            return RetCode.Success;
        } catch (IllegalArgumentException e) {
            return RetCode.BadParam;
        }
    }

    
    RetCode taSetOutputParamRealPtr(final int paramIndex, double[] outArray) {
        if (outArray == null) return RetCode.BadParam;
        try {
            setOutputParamReal(paramIndex, outArray);
            return RetCode.Success;
        } catch (IllegalArgumentException e) {
            return RetCode.BadParam;
        }
    }


}
