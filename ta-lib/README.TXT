* TA-LIB Quick Reference *

Where is the documentation?
===========================
See http://ta-lib.org in the documentation section.

What's this version? What's new?
================================
See CHANGELOG.TXT and HISTORY.TXT

How to use TA-Lib with Excel?
=============================
See "ta-lib\excel\README.TXT"

How to build the TA-LIB C Library?
==================================
Makefiles can be found in ta-lib/c/make. Find
your platform-compiler directory and run your
maker (make, nmake etc...).

Some MSVC projects can be found in ta-lib/c/ide.

All libraries are created in ta-lib/c/lib
All executable are created in ta-lib/c/bin

How to link to the TA-LIB?
==========================
Generally, you just need to link to the static
library created in ta-lib/c/lib

Your application code just need to
include ta-lib/c/include/ta-libc.h

The same library and include can be directly
used in a C++ project.

How to uninstall the library?
=============================
Just delete the ta-lib directory. TA-LIB does
not touch your system settings or registry.

Comments/Help
=============
Visit http://ta-lib.org and subscribe to the mailing list.
