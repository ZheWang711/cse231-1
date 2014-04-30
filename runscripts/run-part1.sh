#!/usr/bin/env bash

BENCH_NAME=`basename $1`

cd $1

echo $BENCH_NAME

BENCH_BC="$BENCH_NAME.bc"

echo $BENCH_BC

opt -analyze -load $LLVMLIB/CSE231.so -CountStaticInstructions < $BENCH_BC > $OUTPUTLOGS/$BENCH_NAME.static.log
