TEMPLATE  = lib
CONFIG   += staticlib

# Identify the temp dir
cmd:OBJECTS_DIR = ../../../../../temp/cmd
cmr:OBJECTS_DIR = ../../../../../temp/cmr
csd:OBJECTS_DIR = ../../../../../temp/csd
csr:OBJECTS_DIR = ../../../../../temp/csr

# Identify the target name
LIBTARGET = ta_unixodbc
cmd:TARGET = ta_unixodbc_cmd
cmr:TARGET = ta_unixodbc_cmr
csd:TARGET = ta_unixodbc_csd
csr:TARGET = ta_unixodbc_csr

# Output info
DESTDIR     = ../../../../../lib

# File to process
SOURCES = ../../../../../src/ta_unixodbc.c

# Compiler Options
INCLUDEPATH *= ../../../../../include
INCLUDEPATH *= ../../../../../../../ta-lib/c/include
INCLUDEPATH *= ../../../../../../../ta-lib/c/src/ta_common
INCLUDEPATH *= ../../../../../../../ta-lib/c/src/ta_data
INCLUDEPATH *= ../../../../../../../ta-lib/c/src/ta_data/ta_source
INCLUDEPATH *= ../../../../../../../ta-lib/c/src/ta_data/ta_source/ta_sql

# debug/release dependent options.
debug:DEFINES   *= TA_DEBUG
debug:DEFINES   *= _DEBUG
DEFINES        += TA_SINGLE_THREAD
thread:DEFINES -= TA_SINGLE_THREAD
# Platform dependent options.
win32:DEFINES         *= WIN32
win32-msvc:DEFINES    *= _MBCS _LIB
win32:CLEAN_FILES = ../../../../../bin/*.map ../../../../../bin/*._xe ../../../../../bin/*.tds ../../../../../bin/*.pdb ../../../../../bin/*.pbo ../../../../../bin/*.pbi ../../../../../bin/*.pbt
