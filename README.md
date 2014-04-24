cse231
======

CSE 231 project 1

Running Part 3:
1) Run the pass on the ORIGINAL benchmark's bitcode. This will output the resulting instrumented bitcode into 
the $INSTRUMENTATION/branchbias folder. This will insert the proper function calls into the benchmark's bc file. Make
sure you are not using the -analyze flag.
opt -load $LLVMLIB/CSE231.so -BranchBias < $BENCHMARKS/welcome/welcome.bc > $INSTRUMENTATION/branchbias/welcome.instrumented.bc
2) Modify run.sh to link the instrumentation module with the instrumented bitcode from the previous step.
3) Run ./run.sh, and the executable should properly count the branches taken/not taken, and print it out at the end.
