#include "FlowFunction.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"

#include <functional>
#include <iostream>

 LatticePoint FlowFunction::operator()(llvm::Instruction& instr, std::vector<LatticePoint> info_in){
   return CPLatticePoint();
}
