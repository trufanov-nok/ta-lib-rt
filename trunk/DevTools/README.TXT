IMPORTANT: These scripts are not intended for the TA-Lib end user.

These scripts are used EXCLUSIVELY for testing/packaging a new TA-Lib release. For now, they are used solely by the official packager of TA-Lib (myself).

These scripts are setup to run on my computer and depends on some hard coded path. I usually specify these settings near the top of the Perl script... but I might not be consistent on this.

You also have the following dependency to solve (or work around):
  - Borland Compiler
  - MSVC Compiler
  - TMAKE
  - Make your unix machine access the same Win32 source directory (I use VMWare).
  - Internet Access (using libCurl on Unix).
  - CVS access to the repository.
  - Some other I can't think off right now...

There is so much dependency that I am force to say that if you are trying to use these scripts, you are on your own.

\Mario Fortier (mfortier@ta-lib.org)
