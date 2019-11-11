TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = gen_code

#link static libs
win32:LIBS = ./../../../../../lib/libta_common.lib
unix:LIBS =  ./../../../../../lib/libta_common.a

unix:LIBS += -ldl

DEFINES *= TA_GEN_CODE

# debug/release dependent options.
debug:DEFINES  *= TA_DEBUG
debug:DEFINES  *= _DEBUG
DEFINES        += TA_SINGLE_THREAD
thread:DEFINES -= TA_SINGLE_THREAD

# Platform dependent options.
win32:DEFINES              *= WIN32
win32-msvc:DEFINES         *= _MBCS _LIB
cygwin-g++:LIBS            -= -ldl
freebsd-g++:LIBS      -= -ldl
freebsd-g++:INCLUDEPATH += /usr/local/include


INCLUDEPATH += ./../../../../../include \
               ./../../../../../src/ta_common \
               ./../../../../../src/ta_abstract \
               ./../../../../../src/ta_abstract/tables \
               ./../../../../../src/ta_abstract/frames

SOURCES += \
    ../../../../../src/tools/gen_code/gen_code.c \
    ../../../../../src/tools/gen_code/print_funcs.c \
    ../../../../../src/ta_abstract/ta_abstract.c \
    ../../../../../src/ta_abstract/ta_def_ui.c \
    ../../../../../src/ta_abstract/tables/table_a.c \
    ../../../../../src/ta_abstract/tables/table_b.c \
    ../../../../../src/ta_abstract/tables/table_c.c \
    ../../../../../src/ta_abstract/tables/table_d.c \
    ../../../../../src/ta_abstract/tables/table_e.c \
    ../../../../../src/ta_abstract/tables/table_f.c \
    ../../../../../src/ta_abstract/tables/table_g.c \
    ../../../../../src/ta_abstract/tables/table_h.c \
    ../../../../../src/ta_abstract/tables/table_i.c \
    ../../../../../src/ta_abstract/tables/table_j.c \
    ../../../../../src/ta_abstract/tables/table_k.c \
    ../../../../../src/ta_abstract/tables/table_l.c \
    ../../../../../src/ta_abstract/tables/table_m.c \
    ../../../../../src/ta_abstract/tables/table_n.c \
    ../../../../../src/ta_abstract/tables/table_o.c \
    ../../../../../src/ta_abstract/tables/table_p.c \
    ../../../../../src/ta_abstract/tables/table_q.c \
    ../../../../../src/ta_abstract/tables/table_r.c \
    ../../../../../src/ta_abstract/tables/table_s.c \
    ../../../../../src/ta_abstract/tables/table_t.c \
    ../../../../../src/ta_abstract/tables/table_u.c \
    ../../../../../src/ta_abstract/tables/table_v.c \
    ../../../../../src/ta_abstract/tables/table_w.c \
    ../../../../../src/ta_abstract/tables/table_x.c \
    ../../../../../src/ta_abstract/tables/table_y.c \
    ../../../../../src/ta_abstract/tables/table_z.c


include(../Copy2Bin.pri)

HEADERS += \
    ../../../../../src/tools/gen_code/gen_code.h \
    ../../../../../src/tools/gen_code/print_funcs.h
