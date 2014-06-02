#include "flowFunctions/RAFlowFunction.h"
#include <list>



std::vector<LatticePoint *> RAFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){
  // dyncast on that vector;
  errs() << "In operator \n";
  info_in_casted = std::vector<RALatticePoint *>();
  for (std::vector<LatticePoint *>::iterator it = info_in.begin(); it != info_in.end(); ++it){
    RALatticePoint* temp = dyn_cast<RALatticePoint>(*it);
    info_in_casted.push_back(temp);
  }
  errs() << "About to call visit \n";
  this->visit(instr);
  errs() << "Done with visit \n";
  return info_out;
}


// Allocate a memory location for a variable. Here we take the convention that this memory spot could have any value.
void RAFlowFunction::visitAllocaInst(AllocaInst &AI) {
  /*
  AllocaInst* current = &AI;
  std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > val;
  ConstantInt* filler = NULL;
  val = std::make_pair(std::make_pair(true, true), std::make_pair(filler, filler));
  ret_value.representation[current] = val;
   */
  errs() << "RA flow visiting an alloca instruction \n";
}

bool compare_ConstantInts(ConstantInt* left, ConstantInt* right){
  return (left->getValue()).sle(right->getValue());
}

void RAFlowFunction::visitBinaryOperator(BinaryOperator &BO) {
  // Get in Lattice Point.
  RALatticePoint ret_value = *(info_in_casted.back());
  info_in_casted.pop_back();
  
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
    errs() << "In both constants case \n";
    ConstantInt* C1 = cast<ConstantInt>(S1);
    ConstantInt* C2 = cast<ConstantInt>(S2);
    lb = helper::foldBinaryOperator(BO.getOpcode(), C1, C2);;
    ub = lb;
    ret_value.isBottom = false;
    ret_value.isTop = false;
  }
  else if (isa<ConstantInt>(S1) && ret_value.representation.count(S2->get()) > 0){
    // Here S2 is in our map and S1 is a constant.
    errs() << "In one constant case, one in our map case. \n";
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
    ret_value.isBottom = false;
    ret_value.isTop = false;
  }
  else if (isa<ConstantInt>(S2) && ret_value.representation.count(S1->get()) > 0){
    // Here S1 is in our map and S2 is a constant.
    errs() << "In one constant case, one in our map case. \n";
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
    ret_value.isBottom = false;
    ret_value.isTop = false;
  }
  else if (ret_value.representation.count(S1->get()) > 0 && ret_value.representation.count(S2->get()) > 0){
    errs() << "In both in our map case. \n";
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
    ret_value.isBottom = false;
    ret_value.isTop = false;
  }
  else{
    errs() << "In neither in our map case. \n";
    isLeftInfinite = true;
    isRightInfinite = true;
  }
  // Count++;
  ret_value.representation[current] = std::make_pair(std::make_pair(isLeftInfinite, isRightInfinite), std::make_pair(lb, ub));
  errs() << "Lattice point to be returned is [" << ret_value.LPprint() << "]\n";
  info_out.clear();
  info_out.push_back(&ret_value);
}

void RAFlowFunction::visitStoreInst(StoreInst   &I){
  // Count++;
  errs() << "RA flow visiting a store instruction \n";
}





