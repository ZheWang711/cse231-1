#!/usr/bin/env bash
# linking example

# CPPFLAGS=
# LDFLAGS=
# if your instrumentation code calls into LLVM libraries, then comment out the above and use these instead:
CPPFLAGS=`llvm-config --cppflags`
LDFLAGS=`llvm-config --ldflags --libs`

OUR_INSTRUMENTS="$CSE231ROOT/llvm/build/lib/CSE231/instrumentation/"

BENCH_NAME=`basename $1`

echo $BENCH_NAME

BENCH_BC="$BENCH_NAME.bc"

echo $BENCH_BC

opt -load $LLVMLIB/CSE231.so -CountDynamicInstructions < "$1/$BENCH_BC" > $INSTRUMENTATION/dynamic/$BENCH_NAME.instrumented.bc

## compile the instrumentation module to bitcode
clang $CPPFLAGS -O0 -emit-llvm -c $OUR_INSTRUMENTS/dynamic/dynamicinstr.cpp -o $OUR_INSTRUMENTS/dynamic/dynamicinstr.bc

# ## link instrumentation module
llvm-link $INSTRUMENTATION/dynamic/$BENCH_NAME.instrumented.bc $OUR_INSTRUMENTS/dynamic/dynamicinstr.bc -o $BENCH_NAME.linked.bc

# ## compile to native object file
# llc -filetype=obj gcd.linked.bc -o=gcd.o

# ## generate native executable
# g++ gcd.o $LDFLAGS -o gcd.exe

# ./gcd.exe

