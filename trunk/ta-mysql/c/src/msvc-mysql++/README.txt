mysql++ 1.7.1 readme (Win32/Visual C++) version
-----------------------------------------------

NOTES:
------
1) The main workspace and project for the mysql++ API are located in the root
   directory
2) This project, when built, will yield the static library mysql++.lib in the
   /lib directory
3) This library needs the header files in the /include and /mysql/include
   directory, and libmysql.lib in the mysql/lib directory
4) All programs using MySQL++ need libmysql.dll (located in the /mysql/lib
   directory) to be able to run. You have to put it into the same directory
   as the executable, or for example copy it into the windows/system directory
5) In the /example directory a workspace and project have been made for
   building the (non-MFC) examples
6) In the /example/MFC_example an example for using MySQL++ in an MFC project
   has been made

PROBLEMS:
---------
1) Visual C++ doesn't provide full functionality for longlongs, such as
   strtoll and ostream operator <<, so all longlongs have been replaced with
   ints in the examples
2) The example custom4.cpp could not be compiled
3) There are still some problems with the functions for static result sets.
   They seem to work alright with vectors, but might not work for the other
   STL containers
4) In every project you make with MySQL++ support, you need to use the
   multithreaded DLL run-time library. This can be set in Project Settings,
   C/C++ tab, category Code Generation, "Use run-time library" listbox.
   If you don't want to change your run-time library, change the run-time
   library in the MySQL++ project and rebuild mysql++.lib (warning: this is
   not recommended and may yield linker errors in your project!)

HOW TO RUN THE EXAMPLES
-----------------------
1) You should have mysql server installed on your localhost with user root and
   no password.
2) Run resetdb.exe example in order to create test database.
3) Run other examples

HOW TO ADD MYSQL++ TO AN EXISTING VISUAL C++ PROJECT
----------------------------------------------------
1) Add mysql++.lib to the project
2) Go to Project Settings, C/C++ tab, category Preprocessor, and add the
   directories include and mysql/include to the "Additional include
   directories" edit box
3) In the source files, in which you want to use MySQL++, add the line
   #include <mysql++>
   after all other included header files (especially those of MFC)
4) If errors occur, see the "Problems" section


Good Luck !

The Lazy Fox
mailto:lazyfox@foxden.dhs.org
