TEMPLATE  = lib
CONFIG   += staticlib

# Identify the temp dir
cmd:OBJECTS_DIR = ../../../../../temp/cmd
cmr:OBJECTS_DIR = ../../../../../temp/cmr
csd:OBJECTS_DIR = ../../../../../temp/csd
csr:OBJECTS_DIR = ../../../../../temp/csr
cdr:OBJECTS_DIR = ../../../../../temp/cdr
cdd:OBJECTS_DIR = ../../../../../temp/cdd

# Identify the target name
LIBTARGET = ta_mysql
cmd:TARGET = ta_mysql_cmd
cmr:TARGET = ta_mysql_cmr
csd:TARGET = ta_mysql_csd
csr:TARGET = ta_mysql_csr
cdr:TARGET = ta_mysql_cdr
cdd:TARGET = ta_mysql_cdd

# Output info
DESTDIR     = ../../../../../lib

# File to process
SOURCES = ../../../../../src/ta_mysql.cpp

# Compiler Options
INCLUDEPATH *= ../../../../../include
INCLUDEPATH *= ../../../../../src/msvc-mysql++/include
INCLUDEPATH *= ../../../../../src/msvc-mysql++/include
INCLUDEPATH *= ../../../../../src/msvc-mysql++/mysql/include
INCLUDEPATH *= ../../../../../../../ta-lib/c/include
INCLUDEPATH *= ../../../../../../../ta-lib/c/src/ta_common
INCLUDEPATH *= ../../../../../../../ta-lib/c/src/ta_data/ta_source/ta_sql

TMAKE_CXXFLAGS += -GX

TMAKE_LIB += ../../../../../src/msvc-mysql++/lib/mysql++.lib
# TMAKE_LIB += ../../../../../src/msvc-mysql++/mysql/lib/libmySQL.lib

# debug/release dependent options.
debug:DEFINES   *= TA_DEBUG
debug:DEFINES   *= _DEBUG
DEFINES        += TA_SINGLE_THREAD
thread:DEFINES -= TA_SINGLE_THREAD
# Platform dependent options.
win32:DEFINES         *= WIN32
win32-msvc:DEFINES    *= _MBCS _LIB
win32:CLEAN_FILES = ../../../../../bin/*.map ../../../../../bin/*._xe ../../../../../bin/*.tds ../../../../../bin/*.pdb ../../../../../bin/*.pbo ../../../../../bin/*.pbi ../../../../../bin/*.pbt
