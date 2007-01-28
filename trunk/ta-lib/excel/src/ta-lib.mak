# Microsoft Developer Studio Generated NMAKE File, Based on ta-lib.dsp
!IF "$(CFG)" == ""
CFG=xlw - Win32 Release
!MESSAGE No configuration specified. Defaulting to xlw - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "xlw - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ta-lib.mak" CFG="xlw - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xlw - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

OUTDIR=.\..\temp
INTDIR=.\..\temp
# Begin Custom Macros
OutDir=.\..\temp
# End Custom Macros

ALL : "$(OUTDIR)\xlw.lib" "$(OUTDIR)\ta-lib.bsc"


CLEAN :
	-@erase "$(INTDIR)\excel32.obj"
	-@erase "$(INTDIR)\excel32.sbr"
	-@erase "$(INTDIR)\trionan.obj"
	-@erase "$(INTDIR)\trionan.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\XlfAbstractCmdDesc.obj"
	-@erase "$(INTDIR)\XlfAbstractCmdDesc.sbr"
	-@erase "$(INTDIR)\XlfArgDesc.obj"
	-@erase "$(INTDIR)\XlfArgDesc.sbr"
	-@erase "$(INTDIR)\XlfArgDescList.obj"
	-@erase "$(INTDIR)\XlfArgDescList.sbr"
	-@erase "$(INTDIR)\XlfCmdDesc.obj"
	-@erase "$(INTDIR)\XlfCmdDesc.sbr"
	-@erase "$(INTDIR)\XlfExcel.obj"
	-@erase "$(INTDIR)\XlfExcel.sbr"
	-@erase "$(INTDIR)\XlfException.obj"
	-@erase "$(INTDIR)\XlfException.sbr"
	-@erase "$(INTDIR)\XlfFuncDesc.obj"
	-@erase "$(INTDIR)\XlfFuncDesc.sbr"
	-@erase "$(INTDIR)\XlfOper.obj"
	-@erase "$(INTDIR)\XlfOper.sbr"
	-@erase "$(INTDIR)\XlfRef.obj"
	-@erase "$(INTDIR)\XlfRef.sbr"
	-@erase "$(OUTDIR)\ta-lib.bsc"
	-@erase "$(OUTDIR)\xlw.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I ".\\" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ta-lib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ta-lib.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\excel32.sbr" \
	"$(INTDIR)\trionan.sbr" \
	"$(INTDIR)\XlfAbstractCmdDesc.sbr" \
	"$(INTDIR)\XlfArgDesc.sbr" \
	"$(INTDIR)\XlfArgDescList.sbr" \
	"$(INTDIR)\XlfCmdDesc.sbr" \
	"$(INTDIR)\XlfExcel.sbr" \
	"$(INTDIR)\XlfException.sbr" \
	"$(INTDIR)\XlfFuncDesc.sbr" \
	"$(INTDIR)\XlfOper.sbr" \
	"$(INTDIR)\XlfRef.sbr"

"$(OUTDIR)\ta-lib.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\xlw.lib" 
LIB32_OBJS= \
	"$(INTDIR)\excel32.obj" \
	"$(INTDIR)\trionan.obj" \
	"$(INTDIR)\XlfAbstractCmdDesc.obj" \
	"$(INTDIR)\XlfArgDesc.obj" \
	"$(INTDIR)\XlfArgDescList.obj" \
	"$(INTDIR)\XlfCmdDesc.obj" \
	"$(INTDIR)\XlfExcel.obj" \
	"$(INTDIR)\XlfException.obj" \
	"$(INTDIR)\XlfFuncDesc.obj" \
	"$(INTDIR)\XlfOper.obj" \
	"$(INTDIR)\XlfRef.obj"

"$(OUTDIR)\xlw.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ta-lib.dep")
!INCLUDE "ta-lib.dep"
!ELSE 
!MESSAGE Warning: cannot find "ta-lib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "xlw - Win32 Release"
SOURCE=.\xlw\excel32.cpp

"$(INTDIR)\excel32.obj"	"$(INTDIR)\excel32.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\trio\trionan.c

"$(INTDIR)\trionan.obj"	"$(INTDIR)\trionan.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfAbstractCmdDesc.cpp

"$(INTDIR)\XlfAbstractCmdDesc.obj"	"$(INTDIR)\XlfAbstractCmdDesc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfArgDesc.cpp

"$(INTDIR)\XlfArgDesc.obj"	"$(INTDIR)\XlfArgDesc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfArgDescList.cpp

"$(INTDIR)\XlfArgDescList.obj"	"$(INTDIR)\XlfArgDescList.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfCmdDesc.cpp

"$(INTDIR)\XlfCmdDesc.obj"	"$(INTDIR)\XlfCmdDesc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfExcel.cpp

"$(INTDIR)\XlfExcel.obj"	"$(INTDIR)\XlfExcel.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfException.cpp

"$(INTDIR)\XlfException.obj"	"$(INTDIR)\XlfException.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfFuncDesc.cpp

"$(INTDIR)\XlfFuncDesc.obj"	"$(INTDIR)\XlfFuncDesc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfOper.cpp

"$(INTDIR)\XlfOper.obj"	"$(INTDIR)\XlfOper.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\xlw\XlfRef.cpp

"$(INTDIR)\XlfRef.obj"	"$(INTDIR)\XlfRef.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

