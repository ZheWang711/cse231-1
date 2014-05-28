#include "flowFunctions/CPFlowFunction.h"

LatticePoint CPFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){
  // dyncast on that vector;
  // this.visit(instr);
  return ret_value;
}

void CPFlowFunction::visitAllocaInst(AllocaInst &AI) { ++Count; }

void CPFlowFunction::visitBinaryOperator(BinaryOperator &BO) { ++Count; }
