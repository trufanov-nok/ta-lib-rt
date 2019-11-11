TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = ta_regtest


#link static libs
win32:LIBS = ./../../../../../lib/libta_libc.lib
unix:LIBS =  ./../../../../../lib/libta_libc.a


unix:LIBS += -ldl


# debug/release dependent options.
debug:DEFINES   *= TA_DEBUG
debug:DEFINES   *= _DEBUG
DEFINES        += TA_SINGLE_THREAD
thread:DEFINES -= TA_SINGLE_THREAD


# Platform dependent options.
win32:DEFINES         *= WIN32
win32-msvc:DEFINES    *= _MBCS _LIB
cygwin-g++:LIBS       -= -ldl
freebsd-g++:LIBS      -= -ldl
freebsd-g++:INCLUDEPATH += /usr/local/include


INCLUDEPATH += ./../../../../../include \
               ./../../../../../src/ta_common \
               ./../../../../../src/tools/ta_regtest \
               ./../../../../../src/ta_func \
               ./../../../../../src/ta_common/trio \
               ./../../../../../src/ta_common/mt \

SOURCES += \
    ../../../../../src/tools/ta_regtest/ta_regtest.c \
    ../../../../../src/tools/ta_regtest/test_abstract.c \
    ../../../../../src/tools/ta_regtest/test_data.c \
    ../../../../../src/tools/ta_regtest/test_internals.c \
    ../../../../../src/tools/ta_regtest/test_util.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_1in_1out.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_1in_2out.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_adx.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_bbands.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_candlestick.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_ma.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_macd.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_minmax.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_mom.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_per_ema.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_per_hl.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_per_hlc.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_per_hlcv.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_per_ohlc.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_po.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_rsi.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_sar.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_stddev.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_stoch.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_trange.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_avgdev.c \
    ../../../../../src/tools/ta_regtest/ta_test_func/test_imi.c

HEADERS += \
    ../../../../../src/tools/ta_regtest/ta_error_number.h \
    ../../../../../src/tools/ta_regtest/ta_test_func.h \
    ../../../../../src/tools/ta_regtest/ta_test_priv.h


include(../Copy2Bin.pri)

