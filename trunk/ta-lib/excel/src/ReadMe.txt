How to rebuild ta-lib.xll?
==========================

You need MSVC 6.0 to re-build (might work with Visual
Studio .NET, but htis has not been tested).

Step # 1 : Build ta_libc_cdr.lib
-----------------------------------
(1) Open workspace: ta-lib\c\ide\msvc\lib_proj\lib_proj.dsw
(2) Select "ta_libc" as the active project (will appear in bold)
(3) Select the configuration "Win32 CDR Multithread DLL Release".
(4) Build "ta_libc". The file "ta_libc_cdr.lib" shall be
    created in ta-lib\c\lib
(5) Close this workspace.

Step #2 : Build ta-lib.xll
--------------------------
(1) Open workspace: ta-lib\excel\src\ta-lib.dsw
(2) Select "xlw_for_talib" as the active project.
(3) Select the configuration "Win32 Release"
(4) Build "xlw_for_talib". The file "ta-lib.xll" shall be
    created in the directory ta-lib\excel
