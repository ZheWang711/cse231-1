#include <map>
#include <string>
#include <stdio.h>
#include <iostream>

#include "llvm/IR/Instruction.h"

// maps instruction opcodes to number of times they are executed
std::map<int, int> instExCount;

void printEverything() {
  printf("Instruction\tExecutions\t\n");
  int total = 0;
  for (std::map<int, int>::const_iterator it=instExCount.begin(); it!=instExCount.end(); ++it){
    
    printf("%s\t%d\n", llvm::Instruction::getOpcodeName(it->first), it->second);
    
    total += it->second;
  }
  // just sit on the total for now
  // O << "TOTAL " << total << "\n";
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

