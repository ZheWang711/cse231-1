// Our stuff
#include "../FlowFunc.h"

// llvm
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"

// standard library
#include <iostream>
#include <functional>

// here we're going to fake up some uses of the flow function
// interface etc until the behaviors we want sortof exist

int main(){

  std::cout << "Hello World!\n";

}

// this does exactly nothing with our stuff right now -- I just want
// to make sure that something linking in to our headers compiles
