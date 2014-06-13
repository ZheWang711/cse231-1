How to configure and run this code:

0. Place this folder (CSE231) and its contents into the path llvm/src/projects/CSE231

1. Run ./configure in the CSE231 folder.

2. Run make clean; make

3. To run the various analyses:

—For constant propagation run:

opt -load Debug+Asserts/lib/projectOne.so -CPtest (your bit code file) > /dev/null

—For range analysis run:

opt -load Debug+Asserts/lib/projectOne.so -RATest (your bit code file) > /dev/null

—For available expressions run:

opt -load Debug+Asserts/lib/projectOne.so -CSEtest (your bit code file) > /dev/null

—For pointer analysis run:

opt -load Debug+Asserts/lib/projectOne.so -PATest < (your bit code file) > /dev/null

4. To run our range checking analysis run:

opt -load Debug+Asserts/lib/projectOne.so -RangeCheckingPass (your bit code file) > /dev/null


******
The benchmarks we tested on are in the folder examples/
******
