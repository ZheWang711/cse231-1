#include <map>
#include <string>
#include <stdio.h>
#include <iostream>

std::map<const char*, int> branchCount;
std::map<const char*, int> branchTaken;

void printEverything() {
  printf("Function\tBias\tTaken\tTotal\n");
  for (std::map<const char*, int>::const_iterator it = branchCount.begin();
      it != branchCount.end(); ++it) {
    double bias =
        branchCount[it->first] > 0 ?
            (double) branchTaken[it->first] / (double) branchCount[it->first] : 0;
    printf("%s\t%f\t%d\t%d\n", it->first, bias, branchTaken[it->first],
        branchCount[it->first]);
  }
}

// initialize map with func name -- handles case where there are no branches
void initFunc(const char* funcName) {
  if (branchTaken.count(funcName) < 1) {
    branchCount[funcName] = 0;
    branchTaken[funcName] = 0;
  }
}

// _Z20countFuncBranchTakenPKcb
void countFuncBranchTaken(const char* funcName, bool isTrue) {
  branchCount[funcName] = branchCount[funcName] + 1;
  if (isTrue) {
    branchTaken[funcName] = branchTaken[funcName] + 1;
  }
}

