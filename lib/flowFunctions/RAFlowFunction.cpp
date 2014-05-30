#include "flowFunctions/RAFlowFunction.h"

LatticePoint RAFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){
  // dyncast on that vector;
  // this.visit(instr);
  return ret_value;
}


// Allocate a memory location for a variable. Here we take the convention that this memory spot could have any value.
void RAFlowFunction::visitAllocaInst(AllocaInst &AI) {
  AllocaInst* current = &AI;
  std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > val;
  ConstantInt* filler = NULL;
  val = std::make_pair(std::make_pair(true, true), std::make_pair(filler, filler));
  ret_value.representation[current] = val;
}


void RAFlowFunction::visitBinaryOperator(BinaryOperator &BO) { ++Count; }


void RAFlowFunction::visitStoreInst(StoreInst   &I){
  value = I.getValueOperand();
  pointer = I.getPointerOperand();
}
