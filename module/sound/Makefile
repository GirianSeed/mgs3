#!/usr/bin/make -f
#
# Makefile for KCEJ SDDRV/SDLIB
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

CFLAGS          = -G0 -O3 -Wall
ASFLAGS         =
CPPFLAGS        = -I$(IOP_INCDIR) -I$(SCE_ROOT)/common/include

LIBRARY         := sdlib
DRIVER          := sddrv

sdlib_SRCS      := sdlib.c
sdlib_OBJS      := $(sdlib_SRCS:.c=.o) $(LIBRARY)ent.o
sdlib_ILIBS     := -ilb=libsd.ilb

sddrv_SRCS      := sddrv.c sdfile.c mtast.c efx.c seq.c memst.c vagst.c plii.c
sddrv_OBJS      := $(sddrv_SRCS:.c=.o)
sddrv_ILIBS     := -ilb=libsd.ilb -ilb=./$(LIBRARY).ilb

#---------------------------------------------------------------

.PHONY: all
all: $(LIBRARY).irx $(LIBRARY).ilb
#all: $(DRIVER).irx

%.ilb: %.tbl
	$(ILBGEN) -d $@ $<

# sound library export table
$(LIBRARY)ent.o: $(LIBRARY)ent.s
$(LIBRARY)ent.s: $(LIBRARY).tbl
	$(ILBGEN) -e $@ $<

# sound library target
$(LIBRARY).irx: $(sdlib_OBJS)
	$(LINK.o) -o $@ $^ $(sdlib_ILIBS)
	$(IFIXUP) -o $(LIBRARY).irx $(LIBRARY).irx

# sound driver target
$(DRIVER).irx: $(sddrv_OBJS)
	$(LINK.o) -o $@ $^ $(sddrv_ILIBS)
	$(IFIXUP) -o $(DRIVER).irx $(DRIVER).irx

.PHONY: clean
clean:
	-$(RM) $(sdlib_OBJS) $(LIBRARY)ent.s $(LIBRARY).irx $(LIBRARY).ilb
#	-$(RM) $(sddrv_OBJS) $(DRIVER).irx
