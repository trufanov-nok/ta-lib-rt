# Microsoft Developer Studio Project File - Name="mysqlpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=mysqlpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mysqlpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mysqlpp.mak" CFG="mysqlpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mysqlpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mysqlpp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "mysqlpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /GX /O2 /I "mysql/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x413 /d "NDEBUG"
# ADD RSC /l 0x413 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/mysql++.lib"

!ELSEIF  "$(CFG)" == "mysqlpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Gm /GX /ZI /Od /I "mysql/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x413 /d "_DEBUG"
# ADD RSC /l 0x413 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/mysql++.lib"

!ENDIF 

# Begin Target

# Name "mysqlpp - Win32 Release"
# Name "mysqlpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\sqlplus\coldata.cpp
# End Source File
# Begin Source File

SOURCE=.\sqlplus\connection.cpp
# End Source File
# Begin Source File

SOURCE=.\sqlplus\datetime.cpp
# End Source File
# Begin Source File

SOURCE=.\sqlplus\field_names.cpp
# End Source File
# Begin Source File

SOURCE=.\sqlplus\field_types.cpp
# End Source File
# Begin Source File

SOURCE=.\sqlplus\manip.cpp
# End Source File
# Begin Source File

SOURCE=.\sqlplus\query.cpp
# End Source File
# Begin Source File

SOURCE=.\sqlplus\result.cpp
# End Source File
# Begin Source File

SOURCE=.\sqlplus\set.cpp
# End Source File
# Begin Source File

SOURCE=.\sqlplus\sql_query.cpp
# End Source File
# Begin Source File

SOURCE=.\sqlplus\string_util.cpp
# End Source File
# Begin Source File

SOURCE=.\sqlplus\type_info.cpp
# End Source File
# Begin Source File

SOURCE=.\sqlplus\vallist.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\sqlplus\bad_query.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\coldata1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\coldata2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\coldata3.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\coldata4.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\compare1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\compare2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\compare3.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\connection0.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\connection1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\connection2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\connection3.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\const_string1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\const_string2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\const_string3.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\convert1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\convert2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\convert3.hh
# End Source File
# Begin Source File

SOURCE=".\sqlplus\custom-macros.hh"
# End Source File
# Begin Source File

SOURCE=.\sqlplus\custom.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\datetime1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\datetime2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\define_short.h
# End Source File
# Begin Source File

SOURCE=.\sqlplus\defs.h
# End Source File
# Begin Source File

SOURCE=.\sqlplus\field_names1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\field_names2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\field_names3.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\field_types1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\field_types2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\field_types3.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\fields1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\fields2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\manip1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\manip2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\manip3.hh
# End Source File
# Begin Source File

SOURCE=".\sqlplus\mysql++"
# End Source File
# Begin Source File

SOURCE=".\sqlplus\mysql++.h"
# End Source File
# Begin Source File

SOURCE=.\sqlplus\null1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\null2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\null3.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\query1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\query2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\query3.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\resiter1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\result1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\result2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\result3.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\row1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\row2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\row3.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\set1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\set2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\set3.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\sql_query0.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\sql_query1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\sql_query2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\sql_query3.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\sql_string1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\sql_string2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\sql_string3.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\sqlplus.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\stream2string1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\stream2string2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\stream2string3.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\string_util.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\tiny_int1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\tiny_int2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\tiny_int3.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\type_info1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\type_info2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\type_info3.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\undef_short.h
# End Source File
# Begin Source File

SOURCE=.\sqlplus\vallist1.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\vallist2.hh
# End Source File
# Begin Source File

SOURCE=.\sqlplus\vallist3.hh
# End Source File
# End Group
# Begin Group "Library Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mysql\lib\libmySQL.lib
# End Source File
# End Group
# End Target
# End Project
