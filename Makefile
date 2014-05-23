##===- lib/Transforms/Hello/Makefile -----------------------*- Makefile -*-===##
#
#                     The LLVM Compiler Infrastructure
#
# This file is distributed under the University of Illinois Open Source
# License. See LICENSE.TXT for details.
#
##===----------------------------------------------------------------------===##

LEVEL = ../..
LIBRARYNAME = CSE231
LOADABLE_MODULE = 1
CFLAGS=-std=c++11

DIRS = tools

include $(LEVEL)/Makefile.common

