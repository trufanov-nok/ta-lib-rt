* TA-LIB for .NET *

Where is the documentation?
===========================
See http://ta-lib.org in the documentation section.

How to use TA-Lib with .NET?
============================
Copy and distribute TA-Lib-Core.dll in
the same directory as your application.

Two versions are available.

(1) Assembly for Release:
  ta-lib\dotnet\src\Core\Release\TA-Lib-Core.dll

(2) Assembly for Debug:
  ta-lib\dotnet\src\Core\Debug\TA-Lib-Core.dll

The assembly are not shared (or strongly named) and
consequently does not require to be added to the GAC.

The assembly does not contain language specific feature and
can be used with any .NET language (C#,VB.NET,C++,J#...).

These assemblies can be used with Mono as well.

Only the TA functions are currently implemented for
the .NET platform.

How to rebuild the TA-LIB assembly?
===================================
Using Visual Studio, open the following
solution file and rebuild TA-Lib-Core:
  ta-lib\dotnet\src\TA-Lib.sln

There is no makefile provided for Mono.

Can I re-distribute the TA-Lib assembly?
========================================
TA-Lib can be distributed with commercial software
for no fee. You must respect the LICENSE.TXT included
in this package.

How to uninstall the library?
=============================
Just delete the ta-lib directory or all the 
assembly. TA-LIB does not touch your system
settings, the GAC or the registry.

Comments/Help
=============
Visit http://ta-lib.org and subscribe to the mailing list.

