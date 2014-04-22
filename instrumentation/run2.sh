#!/usr/bin/env bash
# linking example

CPPFLAGS=
LDFLAGS=
# if your instrumentation code calls into LLVM libraries, then comment out the above and use these instead:
#CPPFLAGS=`llvm-config --cppflags`
#LDFLAGS=`llvm-config --ldflags --libs`

## compile the instrumentation module to bitcode
clang $CPPFLAGS -O0 -emit-llvm -c branchinstr.cpp -o branchinstr.bc

## link instrumentation module
## test.instrumented.bc is the output of the pass:
## opt -load $LLVMLIB/CSE231.so -BranchBias < $INSTRUMENTATION/branchbias/test.bc > $INSTRUMENTATION/branchbias/test.instrumented.bc
llvm-link test.instrumented.bc branchinstr.bc -o test.linked.bc

## instrumented bitcode now has access to module functions
## note: I had to use mangled names for M.getOrInsertFunction()
## compile to native object file
llc -filetype=obj test.linked.bc -o=test.o

## generate native executable
g++ test.o $LDFLAGS -o test.exe

./test.exe

