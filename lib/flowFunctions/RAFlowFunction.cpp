#include "flowFunctions/RAFlowFunction.h"
#include <list>



LatticePoint RAFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){
  // dyncast on that vector;
  this->visit(instr);
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

bool compare_ConstantInts(ConstantInt* left, ConstantInt* right){
  return (left->getValue()).sle(right->getValue());
}

void RAFlowFunction::visitBinaryOperator(BinaryOperator &BO) {
  BinaryOperator* current = &BO;
  std::pair<Use*, Use *> operands = helper::getOperands(BO);
  Use* S1 = operands.first;
  Use* S2 = operands.second;
  std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > val;
  
  bool isLeftInfinite = false;
  bool isRightInfinite = false;
  ConstantInt* lb = NULL;
  ConstantInt* ub = NULL;
  
  if (isa<ConstantInt>(S1) && isa<ConstantInt>(S2)){
    ConstantInt* C1 = cast<ConstantInt>(S1);
    ConstantInt* C2 = cast<ConstantInt>(S2);
    lb = helper::foldBinaryOperator(BO.getOpcode(), C1, C2);;
    ub = lb;
  }
  else if (isa<ConstantInt>(S1) && ret_value.representation.count(S2->get()) > 0){
    // Here S2 is in our map and S1 is a constant.
    ConstantInt* C1 = cast<ConstantInt>(S1);
    std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > S2_val = ret_value.representation[S2->get()];
    if (S2_val.first.first) {
      isLeftInfinite = true;
    }
    else{
      lb = helper::foldBinaryOperator(BO.getOpcode(), C1, S2_val.second.first);
    }
    if (S2_val.first.second){
      isRightInfinite = true;
    }
    else{
      ub = helper::foldBinaryOperator(BO.getOpcode(), C1, S2_val.second.second);
    }
  }
  else if (isa<ConstantInt>(S2) && ret_value.representation.count(S1->get()) > 0){
    // Here S1 is in our map and S2 is a constant.
    ConstantInt* C2 = cast<ConstantInt>(S2);
    std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > S1_val = ret_value.representation[S1->get()];
    if (S1_val.first.first) {
      isLeftInfinite = true;
    }
    else{
      lb = helper::foldBinaryOperator(BO.getOpcode(), S1_val.second.first, C2);
    }
    if (S1_val.first.second){
      isRightInfinite = true;
    }
    else{
      ub = helper::foldBinaryOperator(BO.getOpcode(), S1_val.second.second, C2);
    }
  }
  else if (ret_value.representation.count(S1->get()) > 0 &&ret_value.representation.count(S2->get()) > 0){
    // Both S1 and S2 are in our map and non-constant.
    std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > S1_val = ret_value.representation[S1->get()];
    std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > S2_val = ret_value.representation[S2->get()];
    
    if (S1_val.first.first || S2_val.first.first || S1_val.first.second || S2_val.first.second) {
      isLeftInfinite = true;
      isRightInfinite = true;
    }
    else{
      std::list<ConstantInt *> possible_vals;
      possible_vals.push_back(helper::foldBinaryOperator(BO.getOpcode(), S1_val.second.first, S2_val.second.first));
      possible_vals.push_back(helper::foldBinaryOperator(BO.getOpcode(), S1_val.second.first, S2_val.second.second));
      possible_vals.push_back(helper::foldBinaryOperator(BO.getOpcode(), S1_val.second.second, S2_val.second.first));
      possible_vals.push_back(helper::foldBinaryOperator(BO.getOpcode(), S1_val.second.second, S2_val.second.second));
      possible_vals.sort(compare_ConstantInts);
      lb = possible_vals.front();
      ub = possible_vals.back();
    }
  }
  else{
    isLeftInfinite = true;
    isRightInfinite = true;
  }
  Count++;
  ret_value.representation[current] = std::make_pair(std::make_pair(isLeftInfinite, isRightInfinite), std::make_pair(lb, ub));
}

void RAFlowFunction::visitStoreInst(StoreInst   &I){
  Count++;
}





