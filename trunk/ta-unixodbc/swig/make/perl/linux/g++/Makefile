# makefile for building a perl TA.pm module with UnixODBC
# CMR (commandline multitheraded release only)
# Handmade (experimental)
#
# Tested with SWIG v1.3.21

PERL5_VERSION=5.8
PERL5_INCLUDE=/usr/lib/perl/$(PERL5_VERSION)/CORE

TALIBDIR=../../../../../../ta-lib
TOPDIR=../../../..
WRAPDIR=$(TOPDIR)/temp/perl/wrap
TEMPDIR=$(TOPDIR)/temp/perl/wrap

CPPFLAGS   = -Dbool=char -D_REENTRANT -D_GNU_SOURCE \
	     -DTHREADS_HAVE_PIDS -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 \
	     -I$(PERL5_INCLUDE) \
	     -I$(TALIBDIR)/c/include
CFLAGS     = -pipe -Wall -Wno-unused -O2 -fpic -fno-strict-aliasing

CC         = gcc
LDFLAGS    = -shared
LDLIBS     = -lpthread -lcurl -lodbc

all: $(TOPDIR)/lib/perl/TA.so $(TOPDIR)/lib/perl/Finance/TA.pm

clean:
	rm -f $(WRAPDIR)/*.c
	rm -f $(WRAPDIR)/*.pm
	rm -f $(TEMPDIR)/*.o

$(TOPDIR)/lib/perl/TA.so: $(TEMPDIR)/ta_libc_wrap.o
	$(CC) $(LDFLAGS) -o $@ $< \
		$(TALIBDIR)/c/lib/libta_libc_cmr.a $(TOPDIR)/../c/lib/libta_unixodbc_cmr.a $(LDLIBS)

$(TOPDIR)/lib/perl/Finance/TA.pm: \
		$(WRAPDIR)/TA.pm \
		$(TALIBDIR)/swig/src/interface/perl.pm \
		$(TOPDIR)/src/interface/perl.pm
	sed -e '$d' $(TALIBDIR)/swig/src/interface/perl.pm | cat $(WRAPDIR)/TA.pm - $(TOPDIR)/src/interface/perl.pm >$@ 

$(WRAPDIR)/TA.pm $(WRAPDIR)/ta_libc_wrap.c: \
		$(TOPDIR)/src/interface/ta_unixodbc.swg \
		$(TALIBDIR)/swig/src/interface/ta_libc.swg \
		$(TALIBDIR)/swig/src/interface/ta_func.swg
	swig -perl5 -proxy -Fstandard -o $(WRAPDIR)/ta_libc_wrap.c \
		-I$(TALIBDIR)/swig/src/interface -I$(TALIBDIR)/c/include \
		-I$(TOPDIR)/../c/include $<


.PHONY: all clean
