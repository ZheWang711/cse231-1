#include "flowFunctions/RAFlowFunction.h"
#include <list>



std::vector<LatticePoint *> RAFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){
  // dyncast on that vector;
  errs() << "In operator \n";
  info_in_casted = std::vector<RALatticePoint *>();
  for (std::vector<LatticePoint *>::iterator it = info_in.begin(); it != info_in.end(); ++it){
    RALatticePoint* temp = dyn_cast<RALatticePoint>(*it);
    errs() << "Handed lattice point ";
    temp->printToErrs();
    info_in_casted.push_back(temp);
  }
  info_out.clear();
  errs() << "About to call visit with " << info_in_casted.size() << " arguments \n";
  this->visit(instr);
  errs() << "Done with visit \n";
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
      std::pair<Use*, Use *> branches = helper::getBranches(BI);
      Use* true_branch = branches.first;
      Use* false_branch = branches.second;
      /*
      errs() << "Examining instruction " << BI.getName() << " looks kinda like " << BI << "\n";
      errs() << "True branch " << true_branch->get()->getName() << " looks kinda like " << * (true_branch->get()) << "\n";
      errs() << "False branch " << false_branch->get()->getName() << " looks kinda like " << * (false_branch->get()) << "\n";
       */
      ICmpInst* cmp = cast<ICmpInst>(cond);
      std::pair<Use*, Use *> operands = helper::getOperands(*cmp);
      Use* left_hand_side = operands.first;
      Use* right_hand_side = operands.second;
      
      /*
      errs() << "Left hand side " << left_hand_side->get()->getName() << " looks kinda like " << * (left_hand_side->get()) << "\n";
      errs() << "Right hand side " << right_hand_side->get()->getName() << " looks kinda like " << * (right_hand_side->get()) << "\n";
      */
      ConstantRange* lhs_range;
      ConstantRange* rhs_range;
      

      
      if (inRLP->representation.count(left_hand_side->get()) > 0) {
        lhs_range = inRLP->representation[left_hand_side->get()];
      }
      else if (isa<ConstantInt>(left_hand_side->get())) {
        ConstantInt* C2 = cast<ConstantInt>(left_hand_side->get());
        lhs_range = new ConstantRange(C2->getValue());
      }
      else{
        lhs_range = new ConstantRange(32, true);
      }
      
      if (inRLP->representation.count(right_hand_side->get()) > 0) {
        rhs_range = inRLP->representation[right_hand_side->get()];
      }
      else if (isa<ConstantInt>(right_hand_side->get())) {
        ConstantInt* C2 = cast<ConstantInt>(right_hand_side->get());
        rhs_range = new ConstantRange(C2->getValue());
      }
      else{
        rhs_range = new ConstantRange(32, true);
      }
      
      // First we compute the restrictions that cmp makes upon the regions.
      ConstantRange true_branch_lhs_restriction = ConstantRange::makeICmpRegion(cmp->getUnsignedPredicate(), *rhs_range);
      ConstantRange false_branch_lhs_restriction = (ConstantRange(32, true)).difference(true_branch_lhs_restriction);
      cmp->swapOperands();
      ConstantRange true_branch_rhs_restriction = ConstantRange::makeICmpRegion(cmp->getUnsignedPredicate(),*lhs_range);;
      ConstantRange false_branch_rhs_restriction = (ConstantRange(32, true)).difference(true_branch_rhs_restriction);
      
      // Next we intersect the ranges with the resulting restrictions.
      ConstantRange* true_branch_lhs_range = new ConstantRange(lhs_range->getBitWidth(), true);
      ConstantRange* false_branch_lhs_range = new ConstantRange(lhs_range->getBitWidth(), true);
      ConstantRange* true_branch_rhs_range = new ConstantRange(rhs_range->getBitWidth(), true);
      ConstantRange* false_branch_rhs_range = new ConstantRange(rhs_range->getBitWidth(), true);
      
      *true_branch_lhs_range = lhs_range->intersectWith(true_branch_lhs_restriction);
      *false_branch_lhs_range = lhs_range->intersectWith(false_branch_lhs_restriction);
      
      *true_branch_rhs_range = rhs_range->intersectWith(true_branch_rhs_restriction);
      *false_branch_rhs_range = rhs_range->intersectWith(false_branch_rhs_restriction);
      
      RALatticePoint* true_branchRLP = new RALatticePoint(*inRLP);
      RALatticePoint* false_branchRLP = new RALatticePoint(*inRLP);
      
      true_branchRLP->isBottom = false;
      true_branchRLP->isTop = false;

      false_branchRLP->isBottom = false;
      false_branchRLP->isTop = false;

      true_branchRLP->representation[left_hand_side->get()] = true_branch_lhs_range;
      true_branchRLP->representation[right_hand_side->get()] = true_branch_rhs_range;

      false_branchRLP->representation[left_hand_side->get()] = false_branch_lhs_range;
      false_branchRLP->representation[right_hand_side->get()] = false_branch_rhs_range;
      
      info_out.push_back(true_branchRLP);
      info_out.push_back(false_branchRLP);
    }
    else{
      // does not affect our lattice.
      info_out.push_back(inRLP);
    }
  }
}


void RAFlowFunction::visitCastInst(CastInst &I){
  info_out.clear();
  RALatticePoint* inRLP = new RALatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  info_out.push_back(inRLP);
}


void RAFlowFunction::visitCmpInst(CmpInst &I){
  info_out.clear();
  RALatticePoint* inRLP = new RALatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  info_out.push_back(inRLP);
}


void RAFlowFunction::visitTerminatorInst(TerminatorInst &I){
  info_out.clear();
  RALatticePoint* inRLP = new RALatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  info_out.push_back(inRLP);
}


// Be safe with memory!
void RAFlowFunction::visitUnaryInstruction(UnaryInstruction &I){
  info_out.clear();
  RALatticePoint* result = new RALatticePoint(false, true, std::map<Value*, ConstantRange*>());
  info_out.push_back(result);
}

// Be safe with memory!
void RAFlowFunction::visitInstruction(Instruction &I){
  info_out.clear();
  RALatticePoint* result = new RALatticePoint(false, true, std::map<Value*, ConstantRange*>());
  info_out.push_back(result);
}




