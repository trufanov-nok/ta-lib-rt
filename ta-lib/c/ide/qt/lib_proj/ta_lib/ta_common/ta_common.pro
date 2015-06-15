TEMPLATE = lib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = ta_common

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
