# Microsoft Developer Studio Project File - Name="perl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=perl - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "perl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "perl.mak" CFG="perl - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "perl - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "perl - Win32 TA_Data Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
F90=df.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "perl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\temp\perl\cdr"
# PROP Intermediate_Dir "..\..\..\temp\perl\cdr"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EXAMPLE_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /O1 /I "$(PERL5_INCLUDE)" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MSWIN32" /D "_CONSOLE" /D "NO_STRICT" /D "PERL_MSVCRT_READFIX" /D "PERL_CAPI" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 ..\..\..\..\c\lib\ta_libc_cdr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib $(PERL5_INCLUDE)/perl56.lib /nologo /dll /pdb:none /machine:I386 /out:"..\..\..\lib\perl\ta.dll"

!ELSEIF  "$(CFG)" == "perl - Win32 TA_Data Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "perl___Win32_TA_Data_Release"
# PROP BASE Intermediate_Dir "perl___Win32_TA_Data_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\temp\perl\cdr\ta_data"
# PROP Intermediate_Dir "..\..\..\temp\perl\cdr\ta_data"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /O2 /I "$(PERL5_INCLUDE)" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MSWIN32" /D "PERL_CAPI" /YX /FD /c
# ADD CPP /nologo /MD /W3 /O2 /I "$(PERL5_INCLUDE)" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MSWIN32" /D "PERL_CAPI" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\..\c\lib\ta_libc_cdr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib $(PERL5_INCLUDE)/perl56.lib /nologo /dll /pdb:none /machine:I386 /out:"..\..\..\lib\perl\ta.dll"
# ADD LINK32 ..\..\..\..\c\lib\ta_libc_cdr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib $(PERL5_INCLUDE)/perl56.lib /nologo /dll /pdb:none /machine:I386 /out:"..\..\..\lib\perl\ta.dll"

!ENDIF 

# Begin Target

# Name "perl - Win32 Release"
# Name "perl - Win32 TA_Data Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\temp\perl\wrap\ta_libc_wrap.c

!IF  "$(CFG)" == "perl - Win32 Release"

# ADD CPP /W3

!ELSEIF  "$(CFG)" == "perl - Win32 TA_Data Release"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\..\c\include\ta_abstract.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\c\include\ta_common.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\c\include\ta_data.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\c\include\ta_defs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\c\include\ta_func.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\c\include\ta_libc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\c\include\ta_pm.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=..\..\..\src\interface\perl.pm
# End Source File
# Begin Source File

SOURCE=..\..\..\src\interface\ta_libc.i

!IF  "$(CFG)" == "perl - Win32 Release"

USERDEP__TA_LI="..\..\..\src\interface\perl.pm"	
# Begin Custom Build
InputPath=..\..\..\src\interface\ta_libc.i
InputName=ta_libc

BuildCmds= \
	echo In order to function correctly, please ensure the following environment variables are correctly set: \
	echo PERL5_INCLUDE: %PERL5_INCLUDE% \
	echo Make also sure that swig and perl are on search path: \
	echo %PATH% \
	echo on \
	swig -perl5 -proxy -Fmicrosoft -o ..\..\..\temp\perl\wrap\$(InputName)_wrap.c $(InputPath) \
	copy /Y /A ..\..\..\temp\perl\wrap\TA.pm+..\..\..\src\interface\perl.pm ..\..\..\lib\perl\Finance\TA.pm \
	

"..\..\..\temp\perl\wrap\$(InputName)_wrap.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\..\..\temp\perl\wrap\TA.pm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "perl - Win32 TA_Data Release"

!ENDIF 

# End Source File
# End Target
# End Project
