// Our stuff
#include "flowFunctions/CPFlowFunction.h"
#include "lattices/CPLatticePoint.h"
#include <map>

// llvm
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"

// standard library
#include <iostream>
#include <functional>

// here we're going to fake up some uses of the flow function
// interface etc until the behaviors we want sortof exist

using namespace llvm;

int main(){

  std::cout << "Hello World!\n";

  CPLatticePoint meow = CPLatticePoint(true, false, std::map<Value*, Constant*>());

  LLVMContext& testContext = llvm::getGlobalContext();

  ConstantInt* testConstant = llvm::ConstantInt::get(testContext, llvm::APInt(/*nbits*/32, 5, /*bool*/true));

   std::cout << testConstant;

  // std::vector<LatticePoint> samplePoints;
  
  // // samplePoints.push_back(LatticePoint());
  // // samplePoints.push_back(LatticePoint());
  // // samplePoints.push_back(LatticePoint());


  // std::function<LatticePoint(llvm::Instruction&, std::vector<LatticePoint>)> ananfunctest = [](llvm::Instruction&, std::vector<LatticePoint>) -> LatticePoint {
  //   // return( LatticePoint());
  // };
}

// this does exactly nothing with our stuff right now -- I just want
// to make sure that something linking in to our headers compiles
