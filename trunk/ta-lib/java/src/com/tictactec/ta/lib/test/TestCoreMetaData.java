package com.tictactec.ta.lib.test;

import java.util.Set;

import com.tictactec.ta.lib.meta.CoreMetaData;
import com.tictactec.ta.lib.meta.TaFuncService;
import com.tictactec.ta.lib.meta.TaGrpService;
import com.tictactec.ta.lib.meta.annotation.InputParameterInfo;
import com.tictactec.ta.lib.meta.annotation.IntegerList;
import com.tictactec.ta.lib.meta.annotation.IntegerRange;
import com.tictactec.ta.lib.meta.annotation.OptInputParameterInfo;
import com.tictactec.ta.lib.meta.annotation.OutputParameterInfo;
import com.tictactec.ta.lib.meta.annotation.RealList;
import com.tictactec.ta.lib.meta.annotation.RealRange;

public class TestCoreMetaData {

    public static void main(String[] args) {
        
        final class DumpGrp implements TaGrpService {
            public void execute(String group, Set<CoreMetaData> set) {
                System.out.println("GROUP "+group);
                for (CoreMetaData mi : set) {
                    System.out.println("        "+mi.getFuncInfo().name());
                }
                
            }
        }
        
        final class DumpFunc implements TaFuncService {
            public void execute(CoreMetaData mi) {
                System.out.println(mi.getFuncInfo().name());
                for (int i = 0; i < mi.getFuncInfo().nbInput(); i++) {
                    InputParameterInfo pinfo = mi.getInputParameterInfo(i);
                    System.out.println("    " + pinfo.paramName());
                    System.out.println("        " + pinfo.type());
                }
                for (int i = 0; i < mi.getFuncInfo().nbOptInput(); i++) {
                    OptInputParameterInfo pinfo = mi.getOptInputParameterInfo(i);
                    System.out.println("    " + pinfo.paramName());
                    System.out.println("        " + pinfo.type());
                    switch (pinfo.type()) {
                    case TA_OptInput_RealRange:
                        RealRange rrange = mi.getOptInputRealRange(i);
                        System.out.println("            min="+rrange.min());
                        System.out.println("            max="+rrange.max());
                        System.out.println("            precision="+rrange.precision());
                        System.out.println("            default="+rrange.defaultValue());
                        break;
                    case TA_OptInput_RealList:
                        RealList rlist = mi.getOptInputRealList(i);
                        System.out.print("            value=");
                        for (double value : rlist.value()) {
                            System.out.print(value); System.out.print(" ");
                        }
                        System.out.println();
                        System.out.print("            string="+rlist.string());
                        for (String string : rlist.string()) {
                            System.out.print(string); System.out.print(" ");
                        }
                        System.out.println();
                        break;
                    case TA_OptInput_IntegerRange:
                        IntegerRange irange = mi.getOptInputIntegerRange(i);
                        System.out.println("            min="+irange.min());
                        System.out.println("            max="+irange.max());
                        System.out.println("            default="+irange.defaultValue());
                        break;
                    case TA_OptInput_IntegerList:
                        IntegerList ilist = mi.getOptInputIntegerList(i);
                        System.out.print("            value=");
                        for (int value : ilist.value()) {
                            System.out.print(value); System.out.print(" ");
                        }
                        System.out.println();
                        System.out.print("            string=");
                        for (String string : ilist.string()) {
                            System.out.print(string); System.out.print(" ");
                        }
                        System.out.println();
                        break;
                    }
                }
                for (int i = 0; i < mi.getFuncInfo().nbOutput(); i++) {
                    OutputParameterInfo pinfo = mi.getOutputParameterInfo(i);
                    System.out.println("    " + pinfo.paramName());
                    System.out.println("        " + pinfo.type());
                }
            }
        }

        TaGrpService grpServ = new DumpGrp();
        try {
            CoreMetaData.forEachGrp(grpServ);
        } catch (Exception e) {
            e.printStackTrace();
        }

        System.out.println("=  =  =  =  =  =  =  =  =  =  =  =  =");
        
        TaFuncService funcServ = new DumpFunc();
        try {
            CoreMetaData.forEachFunc(funcServ);
        } catch (Exception e) {
            e.printStackTrace();
        }
        System.out.println("=====================================");
    }

}
