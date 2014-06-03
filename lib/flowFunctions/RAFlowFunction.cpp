#include "flowFunctions/RAFlowFunction.h"
#include <list>



std::vector<LatticePoint *> RAFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){
  // dyncast on that vector;
  //errs() << "In operator \n";
  info_in_casted = std::vector<RALatticePoint *>();
  for (std::vector<LatticePoint *>::iterator it = info_in.begin(); it != info_in.end(); ++it){
    RALatticePoint* temp = dyn_cast<RALatticePoint>(*it);
    //errs() << "Handed lattice point ";
    //temp->printToErrs();
    info_in_casted.push_back(temp);
  }
  info_out.clear();
  //errs() << "About to call visit with " << info_in_casted.size() << " arguments \n";
  this->visit(instr);
  //errs() << "Done with visit \n";
  return info_out;
}


void RAFlowFunction::visitBinaryOperator(BinaryOperator &BO) {
  RALatticePoint* result = new RALatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  
  BinaryOperator* current = &BO;
  std::pair<Use*, Use *> operands = helper::getOperands(BO);
  Use* S1 = operands.first;
  Use* S2 = operands.second;
  ConstantRange* R1;
  ConstantRange* R2;
  
  if (isa<ConstantInt>(S1)) {
    ConstantInt* C1 = cast<ConstantInt>(S1);
    R1 = new ConstantRange(C1->getValue());
  }
  else if (result->representation.count(S1->get()) > 0){
    R1 = result->representation[S1->get()];
  }
  else{
    R1 = new ConstantRange(32, true);
  }
  if (isa<ConstantInt>(S2)) {
    ConstantInt* C2 = cast<ConstantInt>(S2);
    R2 = new ConstantRange(C2->getValue());
  }
  else if (result->representation.count(S2->get()) > 0){
    R2 = result->representation[S2->get()];
  }
  else{
    R2 = new ConstantRange(32, true);
  }
  ConstantRange* range = new ConstantRange(32, true);
  *range = *(helper::foldBinaryOperator(current->getOpcode(), R1, R2));
  
  /*
  errs() << "Bit width of R1 is " << R1->getBitWidth() << "\n";
  errs() << "Bit width of R2 is " << R2->getBitWidth() << "\n";
  errs() << "Bit width of range is " << range->getBitWidth() << "\n";
  */
  result->representation[current] = range;
  
  if (result->isTop && (result->representation[current])->isFullSet()) {
    result->isTop = true;
  }
  else{
    result->isTop = false;
  }
  
  if (result->isBottom && (result->representation[current])->isEmptySet()) {
    result->isBottom = true;
  }
  else{
    result->isBottom = false;
  }

  //errs() << "Lattice point to be returned is ";
  //result->printToErrs();
  info_out.clear();
  info_out.push_back(result);
}

void RAFlowFunction::visitBranchInst(BranchInst &BI){
  RALatticePoint* inRLP = new RALatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  
  if (BI.isUnconditional()) {
    info_out.push_back(inRLP);
  }
  else{
    Value* cond = BI.getCondition();
    if (isa<ICmpInst>(cond)) {
      // may affect elements of our lattice.
      ICmpInst* cmp = cast<ICmpInst>(cond);
      for (User::op_iterator OP = cmp->op_begin(), OPE = cmp->op_end(); OP != OPE; ++OP){
        errs() << "Arg " << *OP << " has user " << OP->getUser() << " and value " << Op->get()  << "\n";
      }
    }
    else{
      // does not affect our lattice.
      info_out.push_back(inRLP);
    }
  }
}

void RAFlowFunction::visitInstruction(Instruction &I){
  info_out.clear();
  RALatticePoint* result = new RALatticePoint(false, true, std::map<Value*, ConstantRange*>());
  info_out.push_back(result);
}




