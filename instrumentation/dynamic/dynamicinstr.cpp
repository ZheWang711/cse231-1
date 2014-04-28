#include <map>
#include <string>
#include <stdio.h>
#include <iostream>

// mangled version of branchbias helper module, using to get dynamic instruction counts

std::map<const char*, int> instExCount;

void printEverything() {
  printf("Instruction\tExecutions\t\n");
  // for (std::map<const char*, int>::const_iterator it=branchCount.begin();
  //      it!=branchCount.end(); ++it){
  //   double bias = branchCount[it->first] > 0 ? branchTaken[it->first] / branchCount[it->first] : 0;
  //   printf("%s\t%f\t%d\t%d\n", it->first, bias, branchTaken[it->first], branchCount[it->first]);
  //  }
}

// Possibly don't need something like this
// void initFunc(const char* funcName) {
//   if (branchTaken.count(funcName) < 1) {
//     branchCount[funcName] = 0;
//     branchTaken[funcName] = 0;
//   }
// }

// _Z20countFuncBranchTakenPKcb
void countInstExecuted(const char* instName) {
  instExCount[instName] = instExCount[instName] + 1;
}

