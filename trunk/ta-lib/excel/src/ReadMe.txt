How to rebuild ta-lib.xll?
==========================

You need MSVC 6.0 to re-build (might work with Visual
Studio .NET, but this has not been tested).

Step # 1 : Build ta_libc_cdr.lib
-----------------------------------
(1) Open workspace: ta-lib\c\ide\msvc\lib_proj\lib_proj.dsw
(2) Select "ta_libc" as the active project (will appear in bold)
(3) Select the configuration "Win32 CDR Multithread DLL Release".
(4) Build "ta_libc". The file "ta_libc_cdr.lib" shall be
    created in ta-lib\c\lib
(5) Close this workspace.

Step #2a : Build ta-lib.xll
--------------------------
You need to perform these steps only if the TA function
inputs are top to down or left to right.

(1) Open workspace: ta-lib\excel\src\ta-lib.dsw
(2) Select "xlw_for_talib" as the active project.
(3) Select the configuration "Win32 Release"
(4) Build "xlw_for_talib". The file "ta-lib.xll" shall be
    created in the directory ta-lib\excel

Step #2b : Build ta-lib-reverse.xll
----------------------------------=
You need to perform these steps only if the TA function
inputs are down to top or right to left.

(1) Open workspace: ta-lib\excel\src\ta-lib.dsw
(2) Select "xlw_for_talib" as the active project.
(3) Select the configuration "Win32 Release"
(4) Make sure DOWN_UP_CELL_ORDER is defined at the top of xlw_for_talib.cpp
(5) Build "xlw_for_talib". The file "ta-lib.xll" shall be
    created in the directory ta-lib\excel


Further information about XLW can be found here:
   http://xlw.sourceforge.net

