#include "flowFunctions/RAFlowFunction.h"

LatticePoint RAFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){
  // dyncast on that vector;
  // this.visit(instr);
  return ret_value;
}

void RAFlowFunction::visitAllocaInst(AllocaInst &AI) { ++Count; }

void RAFlowFunction::visitBinaryOperator(BinaryOperator &BO) { ++Count; }
