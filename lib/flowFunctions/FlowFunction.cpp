#include "flowFunctions/FlowFunction.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include <functional>
#include <iostream>

std::vector<LatticePoint *> FlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint*> info_in){
  CPLatticePoint lp;
  errs() << "I told you so, Marco \n";
  std::vector<LatticePoint*> info_out;
  info_out.push_back(&lp);
  return info_out;
}
