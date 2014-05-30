#include "flowFunctions/RAFlowFunction.h"

LatticePoint RAFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){
  // dyncast on that vector;
  // this.visit(instr);
  return ret_value;
}


// Allocate a memory location for a variable. Here we take the convention that this memory spot could have any value.
void RAFlowFunction::visitAllocaInst(AllocaInst &AI) {
  AllocaInst* current = AI;
  std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > val;
  val = std::make_pair(std::make_pair(isLeftInfinite, isRightInfinite), std::make_pair(NULL, NULL));
  ret_value.representation[current] = val;
}


void RAFlowFunction::visitBinaryOperator(BinaryOperator &BO) { ++Count; }


void visitStoreInst(StoreInst   &I){
  Value* value = I.getValueOperand();
  Value* pointer = I.getPointerOperand();
}