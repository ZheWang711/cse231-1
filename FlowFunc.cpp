#include "FlowFunc.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"

#include <functional>

FlowFunc::operator()(llvm::Instruction instr, std::vector<LatticePoint> info_in){
  auto kitten =  instr->getOpcodeName();
}
