#!/usr/bin/env bash
# linking example

CPPFLAGS=
LDFLAGS=
# if your instrumentation code calls into LLVM libraries, then comment out the above and use these instead:
# CPPFLAGS=`llvm-config --cppflags`
# LDFLAGS=`llvm-config --ldflags --libs`

OUR_INSTRUMENTS="$INSTRUMENTATION"

BENCH_NAME=`basename $1`

cd $1

echo $BENCH_NAME

BENCH_BC="$BENCH_NAME.bc"

echo $BENCH_BC

opt -load $LLVMLIB/CSE231.so -BranchBias < "$1/$BENCH_BC" > $BENCH_NAME.branchbiasinstrumented.bc

## compile the instrumentation module to bitcode
clang $CPPFLAGS -O0 -emit-llvm -c $OUR_INSTRUMENTS/branchbias/branchinstr.cpp -o $BENCH_NAME.branchbiasinstr.bc

# ## link instrumentation module
llvm-link $BENCH_NAME.branchbiasinstrumented.bc $BENCH_NAME.branchbiasinstr.bc -o $BENCH_NAME.branchbiaslinked.bc

# ## compile to native object file
llc -filetype=obj $BENCH_NAME.branchbiaslinked.bc -o=$BENCH_NAME.o

# ## generate native executable
g++ $BENCH_NAME.o $LDFLAGS -o $BENCH_NAME.branchbiasinstrumented.exe

./$BENCH_NAME.branchbiasinstrumented.exe > $OUTPUTLOGS/$BENCH_NAME.branchbias.log

