# Microsoft Developer Studio Project File - Name="xlw" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=xlw - Win32 OnTheEdgeRelease
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ta-lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ta-lib.mak" CFG="xlw - Win32 OnTheEdgeRelease"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xlw - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/xlw", BXAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\temp"
# PROP Intermediate_Dir "..\temp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\\" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\temp\xlw.lib"
# Begin Target

# Name "xlw - Win32 Release"
# Begin Group "Include"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\xlw\config.bcc.h
# End Source File
# Begin Source File

SOURCE=.\xlw\config.msvc.h
# End Source File
# Begin Source File

SOURCE=.\xlw\EXCEL32_API.h
# End Source File
# Begin Source File

SOURCE=.\xlw\macros.h
# End Source File
# Begin Source File

SOURCE=.\xlw\port.h
# End Source File
# Begin Source File

SOURCE=.\xlw\pragmas.h
# End Source File
# Begin Source File

SOURCE=.\xlw\xlcall32.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfAbstractCmdDesc.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfArgDesc.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfArgDescList.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfCmdDesc.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfExcel.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfException.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfFuncDesc.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfOper.h
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfRef.h
# End Source File
# Begin Source File

SOURCE=.\xlw\xlw.h
# End Source File
# End Group
# Begin Group "Source"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\xlw\excel32.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfAbstractCmdDesc.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfArgDesc.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfArgDescList.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfCmdDesc.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfExcel.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfException.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfFuncDesc.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfOper.cpp
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfRef.cpp
# End Source File
# End Group
# Begin Group "Inline"

# PROP Default_Filter ".inl"
# Begin Source File

SOURCE=.\xlw\XlfAbstractCmdDesc.inl
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfExcel.inl
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfException.inl
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfOper.inl
# End Source File
# Begin Source File

SOURCE=.\xlw\XlfRef.inl
# End Source File
# End Group
# End Target
# End Project
