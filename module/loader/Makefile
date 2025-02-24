#!/usr/bin/make -f
#
# Makefile for KCEJ IOP LOADER
#

ifeq ($(wildcard PathDefs),)
PathDefs:
	iop-path-setup > PathDefs || (rm -f PathDefs ; exit 1)
endif
include PathDefs

SCE_ROOT ?= /usr/local/sce
IOP_ROOT := $(SCE_ROOT)/iop

IOP_INSTALL ?= $(IOP_ROOT)
#IOP_INSTALL ?= $(IOP_ROOT)/install
#IOP_INSTALL ?= $(IOP_ROOT)/gcc/mipsel-scei-elfl

IOP_INCDIR := $(IOP_INSTALL)/include
IOP_LIBDIR := $(IOP_INSTALL)/lib
IOP_MODDIR := $(IOP_ROOT)/modules

#---------------------------------------------------------------

CFLAGS      = -G0 -O2 -Wall
ASFLAGS     =
CPPFLAGS    = -I$(IOP_INCDIR) -I$(SCE_ROOT)/common/include

PROGNAME    = pld

SRCS        = pld.c
OBJS        = pld.o $(PROGNAME)_entry.o
ILIBS       =

#---------------------------------------------------------------
.PHONY: all clean

all: $(PROGNAME).irx

$(PROGNAME).ilb: $(PROGNAME).tbl
	$(ILBGEN) -d $@ $<

$(PROGNAME)_entry.o: $(PROGNAME)_entry.s
$(PROGNAME)_entry.s: $(PROGNAME).tbl
	$(ILBGEN) -e $@ $<

$(PROGNAME).irx: $(OBJS)
	$(LINK.o) -o $@ $(OBJS) $(ILIBS)
	$(IFIXUP) -o $(PROGNAME).irx $(PROGNAME).irx

clean:
	-$(RM) $(OBJS) $(PROGNAME)_entry.s
	-$(RM) $(PROGNAME).irx $(PROGNAME).ilb
