#!/usr/bin/env bash
# linking example

#cp ~/workspace/cse231-proj1/llvm/src/lib/CSE231/branchinstr.cpp ~/Documents/CSE231/cse231-proj1/extra/instrumentation/branchbias/

# CPPFLAGS=
# LDFLAGS=
# if your instrumentation code calls into LLVM libraries, then comment out the above and use these instead:
CPPFLAGS=`llvm-config --cppflags`
LDFLAGS=`llvm-config --ldflags --libs`

## compile the instrumentation module to bitcode
clang $CPPFLAGS -O0 -emit-llvm -c dynamicinstr.cpp -o dynamicinstr.bc

## link instrumentation module
llvm-link $INSTRUMENTATION/dynamic/gcd.instrumented.bc dynamicinstr.bc -o gcd.linked.bc

## compile to native object file
llc -filetype=obj gcd.linked.bc -o=gcd.o

## generate native executable
g++ gcd.o $LDFLAGS -o gcd.exe

./gcd.exe

