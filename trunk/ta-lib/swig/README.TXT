SWIG Wrapper for TA-Lib
=======================
 vi:set tw=77:

This directory tree contains files needed to build a SWIG wrapper to 
TA-Lib. SWIG is a software development tool for building scripting language
interfaces to C and C++ programs. It supports a number of target languages:
including Guile, Java, Mzscheme, Ocaml, Perl, Pike, PHP, Python, Ruby, and
Tcl.  More information can be found at http://www.swig.org

Although SWIG is capable of generating wrappers to many languages, makefiles
in this directory tree support perl only.  Tahking perl as example, one can
extend it to other laungages, if needed.

Installation
============
You need to have SWIG installed at your system. Get it from
http://www.swig.org.  The swig executable must be present on your search
path. Verify it at command prompt:
> swig -version

This project is tested with SWIG version 1.3.21. It should work also with
higher versions within the 1.3.x familly.  If you have a lower SWIG version, 
better upgrade.

Obviously, you need also perl installed at your system (Perl5).  The project
is tested with perl 5.6.1.  It should work with newer perl releases as well.

Further, you need a C/C++ compiler, the same as used to compile the perl
executable you use.  At the end, we will be building perl modules.  If you
use ActivePerl on Windows (from ActiveState), you most probably need Visual
C++ version 6.0.  If you use Linux, you probably need gcc, etc.  To find out, try:
> perl -V

Building the Perl module
========================
Build process can be done using make/nmake utility or using IDE

IDE - Microsoft Developer Studio
--------------------------------
First, make sure that the proper ta-lib library is already build in
ta-lib/c/lib.  The wrapper links only with Release Multithreaded DLL variant
(because of necessary compatibility with Perl build), so you need
ta_libc_cdr.lib and the family.

Open workspace ta-lib\swig\ide\msvc\perl\perl.dsw and hit Build All.

make/nmake
----------
[under construction]

Using ta-lib in Perl
====================
The generated perl modules are placed in ta-lib/swig/lib/perl, so make sure
that this directory is placed in your Perl lib search path.  Alternatively,
copy the modules to the appropriate places in your system, where local/site
modules belong.  Another alternative is to use "use lib" pragma in your perl
scripts.

The module name is Finance::TA.  The C identifier names are retained literally, 
so you can use the C API spec.  In case of doubt, look at examples in
ta-lib/swig/src/demo/perl and - even better - at the test scripts in 
ta-lib/swig/src/tools/test_perl.  The test scripts tend to be complete so there is
an example for every function, constant, or type.

The module covers ta_defs, ta_common, ta_data, ta_func, and ta_pm.  It does not 
cover ta_abstract - on purpose.  The information about ta_func can be obtained
in Perl much easier in may other perlish ways.

Good luck!
Pawel Konieczny, konieczp-at-users.sourceforge.net 


Open issues/To do
=================

* How to export automatically (i.e. from SWIG) all public libary symbols
  - low priority as I have solved it with Perl
* How to generate submodules, e.g. Finance::TA::func
  - answer: use %import, see SWIG examples
* How to write log files to stdout
* How to define a custom TA fatal handler in Perl
* Automatically call TA_Shutdown on program exit if needed
* Automatically call TA_Initialize on module load; get parameters on 'use"-line
* Allow to pass hash table to TA_AddDataSourceParam::new with initial values
* Add nice constructors to TA_Timestamp

