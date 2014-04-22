#include <map>
#include <string>
#include <stdio.h>
#include <iostream>

int count;
std::map<int, int> branchCount;

void testFunc() {
  int x = 10;
  if (x > 5)
    //printf("Greater than 5!");
    std::cout << "Greater than 5!\n";
  else
    //printf("Less than or equal to 5!");
    std::cout << "Less than or equal to 5!\n";
}

void countBranch(int funcName) {
  if (branchCount.count(funcName) > 0) {
    branchCount[funcName] = branchCount[funcName] + 1;
  } else {
    branchCount[funcName] = 1;
  }
  std::cout << funcName << " " << branchCount[funcName] << "\n";
}
