* TA-Lib Quick Reference *

Where is the documentation?
===========================
http://ta-lib.org in the documentation section.

What's this version? What's new?
================================
See CHANGELOG.TXT and HISTORY.TXT

How to use TA-Lib with Excel?
=============================
See "ta-lib\excel\README.TXT"

How to build the TA-Lib C Library?
==================================
Makefiles can be found in ta-lib/c/make. Find
your platform-compiler directory and run your
maker (make, nmake etc...).

Some MSVC projects can be found in ta-lib/c/ide.

All libraries are created in ta-lib/c/lib
All executable are created in ta-lib/c/bin

How to link to the TA-Lib?
==========================
Generally, you just need to link to the static
library created in ta-lib/c/lib

Your application code just need to
include ta-lib/c/include/ta_libc.h

How to uninstall the library?
=============================
Just delete the ta-lib directory. TA-Lib does
not touch your system settings or registry.

Comments/Help
=============
Try the forum at http://tadoc.org

