# Microsoft Developer Studio Project File - Name="xlw_for_talib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=xlw_for_talib - Win32 OnTheEdgeDebug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "xlw_for_talib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "xlw_for_talib.mak" CFG="xlw_for_talib - Win32 OnTheEdgeDebug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xlw_for_talib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xlw_for_talib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xlw_for_talib - Win32 OnTheEdgeDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xlw_for_talib - Win32 OnTheEdgeRelease" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/afl/xlw/xlw_for_talib", IXAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "xlw_for_talib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\temp"
# PROP Intermediate_Dir "..\..\temp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TEST_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(XLW_DIR)" /I "..\..\..\c\include" /I "..\..\..\c\src\ta_abstract" /I "..\..\..\c\src\ta_common" /I ".." /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"..\..\ta-lib.xll" /libpath:"$(XLW_DIR)\lib\Win32\VisualStudio"

!ELSEIF  "$(CFG)" == "xlw_for_talib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "build\Debug"
# PROP Intermediate_Dir "build\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TEST_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(XLW_DIR)" /I "g:\ta-lib\c\include" /I "g:\ta-lib\c\src\ta_abstract" /I "g:\ta-lib\c\src\ta_common" /D "XLW_DEBUG" /D "_DEBUG" /D "TEST_EXPORTS" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"xll\Win32\VisualStudio\xlw_for_talibd.xll" /pdbtype:sept /libpath:"$(XLW_DIR)\lib\Win32\VisualStudio"

!ELSEIF  "$(CFG)" == "xlw_for_talib - Win32 OnTheEdgeDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "test___Win32_OnTheEdgeDebug"
# PROP BASE Intermediate_Dir "test___Win32_OnTheEdgeDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "build\OnTheEdgeDebug"
# PROP Intermediate_Dir "build\OnTheEdgeDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "$(XLW_DIR)" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TEST_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "g:\ta-lib\c\include" /I "..\\" /I "g:\ta-lib\c\src\ta_abstract" /I "g:\ta-lib\c\src\ta_common" /D "XLW_DEBUG" /D "_DEBUG" /D "TEST_EXPORTS" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"Debug/xlw_for_talib.xll" /pdbtype:sept /libpath:"$(XLW_DIR)\Debug"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"xll\Win32\VisualStudio\xlw_for_talibd.xll" /pdbtype:sept /libpath:"..\lib\Win32\VisualStudio"
# Begin Custom Build
IntDir=.\build\OnTheEdgeDebug
TargetPath=.\xll\Win32\VisualStudio\xlw_for_talibd.xll
TargetName=xlw_for_talibd
InputPath=.\xll\Win32\VisualStudio\xlw_for_talibd.xll
SOURCE="$(InputPath)"

"$(BIN)\$(TargetName).xll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on 
	copy $(TargetPath) $(BIN)\. 
	copy $(IntDir)\$(TargetName).pdb $(BIN)\. 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "xlw_for_talib - Win32 OnTheEdgeRelease"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "test___Win32_OnTheEdgeRelease"
# PROP BASE Intermediate_Dir "test___Win32_OnTheEdgeRelease"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "build\OnTheEdgeRelease"
# PROP Intermediate_Dir "build\OnTheEdgeRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "$(XLW_DIR)" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\\" /I "g:\ta-lib\c\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/xlw_for_talib.xll" /libpath:"$(XLW_DIR)\Release"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:".\xll\Win32\VisualStudio\xlw_for_talib.xll" /libpath:"..\lib\Win32\VisualStudio"

!ENDIF 

# Begin Target

# Name "xlw_for_talib - Win32 Release"
# Name "xlw_for_talib - Win32 Debug"
# Name "xlw_for_talib - Win32 OnTheEdgeDebug"
# Name "xlw_for_talib - Win32 OnTheEdgeRelease"
# Begin Source File

SOURCE=.\Win32StreamBuf.cpp
# End Source File
# Begin Source File

SOURCE=.\Win32StreamBuf.h
# End Source File
# Begin Source File

SOURCE=.\Win32StreamBuf.inl
# End Source File
# Begin Source File

SOURCE=.\xlw_for_talib.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\c\lib\ta_libc_cdr.lib
# End Source File
# End Target
# End Project
