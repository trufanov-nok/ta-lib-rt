#############################################################################
# Makefile for building ta_sql demo program (debug version)
#     Project: ta-lib
#     Module:  ta-unixodbc
#############################################################################

####### Compiler, tools and options

CC	=	gcc
CXX	=	g++
CFLAGS	=	-pipe -Wall -W -g -D_REENTRANT -DTA_DEBUG -D_DEBUG -DQT_THREAD_SUPPORT
CXXFLAGS=	-pipe -Wall -W -g -D_REENTRANT -DTA_DEBUG -D_DEBUG -DQT_THREAD_SUPPORT
INCPATH	=	-I../../../include -I../../../../../ta-lib/c/include

####### Files

HEADERS =	
SOURCES =	ta_sql.c
OBJECTS =	ta_sql.o 
LIBRARY =	../../../lib/libta_unixodbc_cmd.a ../../../../../ta-lib/c/lib/libta_libc_cmd.a
STDLIB  =	-l odbc -l pthread -l curl
TARGET	=	ta_sql

####### Implicit rules

.SUFFIXES: .cpp .cxx .cc .C .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules


all: $(TARGET)


$(TARGET): $(OBJECTS)  
	-rm -f $(TARGET)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBRARY) $(STDLIB)

clean:
	-rm -f $(OBJECTS) $(TARGET)
	-rm -f *~ core

