
CFLAGS += -Wall -O2 -g -std=gnu99
LDFLAGS += -shared -g

PREFIX := /usr/local
VERSION := 1.0

TARGET := libvector

# Detecting OS.
OS := $(shell uname -s)

ifeq ($(OS),Darwin) # OS X
CC := clang
LD := clang
CFLAGS += -arch i386 -arch x86_64
SOEXT = dylib
DBGEXT = dSYM
SONAME = $(TARGET).$(VERSION).$(SOEXT)
LDFLAGS += -install_name $(TARGET).$(SOEXT) -arch i386 -arch x86_64
else
ifeq ($(OS),Linux) # Linux
CC := gcc
LD := gcc
SOEXT := so
DBGEXT = d
SONAME = $(TARGET).$(SOEXT).$(VERSION)
LDFLAGS += -soname $(SONAME)
else
$(error This Makefile is for OS X and Linux only.)
endif
endif

LIBDIR = $(PREFIX)/lib
INCDIR = $(PREFIX)/include

all: $(SONAME) $(TARGET).$(SOEXT)

.PHONY: all clean install uninstall check

$(SONAME): vector.o
	@echo "LD        $@"
	@$(LD) $(LDFLAGS) vector.o -o $(SONAME)

$(TARGET).$(SOEXT): $(SONAME)
	@echo "LN        $@"
	@ln -s $(SONAME) $(TARGET).$(SOEXT)

%.o: %.c %.h
	@echo "CC        $@"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo CLEAN
	@-rm vector.o &> /dev/null
	@-rm -r *.$(DBGEXT) &> /dev/null
	@-rm $(SONAME) &> /dev/null
	@-rm $(TARGET).$(SOEXT) &> /dev/null
	@-make -C tests clean

install: $(SONAME) $(TARGET).$(SOEXT) vector.h
	@echo "INSTALL   $(SONAME)"
	@cp $(SONAME) $(LIBDIR) &> /dev/null
	@echo "INSTALL   $(TARGET).$(SOEXT)"
	@cp $(TARGET).$(SOEXT) $(LIBDIR) &> /dev/null
	@echo "INSTALL   vector.h"
	@cp vector.h $(INCDIR) &> /dev/null

uninstall:
	@echo "UNINSTALL $(SONAME)"
	@-rm $(LIBDIR)/$(SONAME) &> /dev/null
	@echo "UNINSTALL $(TARGET).$(SOEXT)"
	@-rm $(LIBDIR)/$(TARGET).$(SOEXT) &> /dev/null
	@echo "UNINSTALL vector.h"
	@-rm $(INCDIR)/vector.h &> /dev/null

check: all
	make -C tests
