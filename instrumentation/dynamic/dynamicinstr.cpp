#include <map>
#include <string>
#include <stdio.h>
#include <iostream>

#include "llvm/IR/Instruction.h"

// maps instruction opcodes to number of times they are executed
std::map<int, int> instExCount;

void printEverything() {
  int total = 0;
  for (std::map<int, int>::const_iterator it=instExCount.begin(); it!=instExCount.end(); ++it){
    
    printf("%s\t%d\n", llvm::Instruction::getOpcodeName(it->first), it->second);
    
    total += it->second;
  }
  printf("TOTAL\t%d\n", total);
}

void countInstExecuted(int instOpcode) {
  // printf("%s\n", "Calling countinstexecuted");
  if (instExCount.count(instOpcode) > 0){
    instExCount[instOpcode] = instExCount[instOpcode] + 1;
  }
  else{
    instExCount[instOpcode] = 1;
  }
}

