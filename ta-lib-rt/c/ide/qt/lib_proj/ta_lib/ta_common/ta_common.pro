TEMPLATE = lib
CONFIG -= qt
CONFIG += staticlib

TARGET = ta_common

# debug/release dependent options.
debug:DEFINES   *= TA_DEBUG
debug:DEFINES   *= _DEBUG
DEFINES        += TA_SINGLE_THREAD
thread:DEFINES -= TA_SINGLE_THREAD

# Platform dependent options.
win32:DEFINES         *= WIN32
win32-msvc:DEFINES    *= _MBCS _LIB
freebsd-g++:LIBS      -= -ldl
freebsd-g++:INCLUDEPATH += /usr/local/include

#LIBS += -L./../../../../../lib
INCLUDEPATH += ./../../../../../include \
               ./../../../../../src/ta_common/imatix/sfl \
               ./../../../../../src/ta_common \
               ./../../../../../src/ta_common/mt

SOURCES += \
   ../../../../../src/ta_common/ta_global.c \
   ../../../../../src/ta_common/ta_retcode.c \
   ../../../../../src/ta_common/ta_version.c

HEADERS += \
    ../../../../../src/ta_common/ta_global.h \
    ../../../../../src/ta_common/ta_magic_nb.h \
    ../../../../../src/ta_common/ta_pragma.h \
    ../../../../../include/ta_common.h \
    ../../../../../include/ta_defs.h \
    ../../../../../include/ta_func.h

include(../Copy2Lib.pri)
