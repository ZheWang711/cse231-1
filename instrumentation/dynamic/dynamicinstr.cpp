#include <map>
#include <string>
#include <stdio.h>
#include <iostream>

// mangled version of branchbias helper module, using to get dynamic instruction counts

// maps instruction opcodes to number of times they are executed
std::map<int, int> instExCount;

void printEverything() {
  printf("Instruction\tExecutions\t\n");
  // for (std::map<const char*, int>::const_iterator it=branchCount.begin();
  //      it!=branchCount.end(); ++it){
  //   double bias = branchCount[it->first] > 0 ? branchTaken[it->first] / branchCount[it->first] : 0;
  //   printf("%s\t%f\t%d\t%d\n", it->first, bias, branchTaken[it->first], branchCount[it->first]);
  //  }
}

void countInstExecuted(int instOpcode) {
  printf("%s\n", "Calling countinstexecuted");
  if (instExCount.count(instOpcode) > 0){
    instExCount[instOpcode] = instExCount[instOpcode] + 1;
  }
  else{
    instExCount[instOpcode] = 1;
  }
}

