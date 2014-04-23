#include <map>
#include <string>
#include <stdio.h>
#include <iostream>

std::map<const char*, int> branchCount;
std::map<const char*, int> branchTaken;

void printEverything() {
  printf("Function\tBias\tTaken\tTotal\n");
  for (std::map<const char*, int>::const_iterator it=branchCount.begin();
       it!=branchCount.end(); ++it){
    double bias = branchTaken[it->first] / branchCount[it->first];
    printf("%s\t%f\t%d\t%d\n", it->first, bias, branchTaken[it->first], branchCount[it->first]);
  }
}

// _Z20countFuncBranchTakenPKcb
void countFuncBranchTaken(const char* funcName, bool isTrue) {
  if (branchCount.count(funcName) > 0) {
    branchCount[funcName] = branchCount[funcName] + 1;
  } else {
    branchCount[funcName] = 1;
  }
  if (isTrue && branchTaken.count(funcName) > 0) {
    branchTaken[funcName] = branchTaken[funcName] + 1;
  } else if (isTrue) {
    branchTaken[funcName] = 1;
  }
}

