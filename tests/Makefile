
CFLAGS += -Wall -O2 -g -std=gnu99

PREFIX := /usr/local
VERSION := 1.0

TARGET := libvector

# Detecting OS.
OS := $(shell uname -s)

ifeq ($(OS),Darwin) # OS X
CC := clang
CFLAGS += -arch i386 -arch x86_64
DBGEXT = dSYM
LDFLAGS += -arch i386 -arch x86_64
LDSO_ENV = DYLD_LIBRARY_PATH
else
ifeq ($(OS),Linux) # Linux
CC := gcc
DBGEXT = d
LDSO_ENV = LD_LIBRARY_PATH
else
$(error This Makefile is for OS X and Linux only.)
endif
endif

TESTS := collector-test vector-add vector-sort vector-shrink vector-index

tests: collector $(TESTS) run

.PHONY: tests run clean

collector: collector.c
	@echo "CC        collector"
	@$(CC) $(CFLAGS) collector.c -o collector

%: %.c
	@echo "CC [T]    $@"
	@$(CC) $(CFLAGS) -I.. -L.. -lvector $< -o $@

run: collector $(TESTS)
	@echo "EXEC      ./collector $(TESTS)"
	@-$(LDSO_ENV)=$$$(LDSO_ENV):.. ./collector $(TESTS)

clean:
	@echo "CLEAN     TESTS"
	@-rm collector &> /dev/null
	@-rm $(TESTS) &> /dev/null
	@-rm -r *.$(DBGEXT) &> /dev/null
