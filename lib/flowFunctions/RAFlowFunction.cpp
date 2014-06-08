#include "flowFunctions/RAFlowFunction.h"
#include <list>

/*
 Non-terminator operator
 */

std::vector<LatticePoint *> RAFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){
  // dyncast on that vector;
  info_in_casted = std::vector<RALatticePoint *>();
  for (std::vector<LatticePoint *>::iterator it = info_in.begin(); it != info_in.end(); ++it){
    RALatticePoint* temp = dyn_cast<RALatticePoint>(*it);
    info_in_casted.push_back(temp);
  }
  
  RALatticePoint* old_state = new RALatticePoint(*(info_in_casted.back()));
  info_out.clear();
  this->visit(instr);
  LatticePoint* temp = info_out.back();
  RALatticePoint* temp1 = dyn_cast<RALatticePoint>(temp);
  RALatticePoint* new_state = new RALatticePoint(*temp1);
  std::vector<Value*> differing_vals = new_state->differInRange(old_state);
  
  
  for (int i = 0; i < differing_vals.size(); i++) {
    Value* val = differing_vals[i];
    if (counter_map.count(val) <= 0){
      counter_map[val] = 1;
    }
    else if (counter_map[val] == MAX_COUNT){
      new_state->representation[val] = new ConstantRange(32, true);
    }
    else{
      counter_map[val] = counter_map[val] + 1;
    }
  }
  info_out.clear();
  info_out.push_back(new_state);
  return info_out;
}

/*
 Terminator operator
 */

std::map<Value *, LatticePoint *> RAFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in, std::map<Value *, LatticePoint *> successor_map){
  out_map = successor_map;
  //errs() << "In terminator operator \n";
  info_in_casted = std::vector<RALatticePoint *>();
  for (std::vector<LatticePoint *>::iterator it = info_in.begin(); it != info_in.end(); ++it){
    RALatticePoint* temp = dyn_cast<RALatticePoint>(*it);
    //errs() << "Handed lattice point ";
    //temp->printToErrs();
    info_in_casted.push_back(temp);
  }

  this->visit(instr);
  return out_map;
}

/*
 Binary operator is NOT terminator.
 */

void RAFlowFunction::visitBinaryOperator(BinaryOperator &BO) {
  RALatticePoint* result = new RALatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  
  BinaryOperator* current = &BO;
  
  std::pair<Use*, Use *> operands = helper::getOperands(BO);
  Use* S1 = operands.first;
  Use* S2 = operands.second;
  /*
  errs() << "Dealing with instruction " << *current << "\n";
  errs() << "First operand is " << *(S1->get()) << "\n";
  errs() << "Second operand is " << *(S2->get()) << "\n";
  */
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
    R1 = new ConstantRange(32, false);
  }
  if (isa<ConstantInt>(S2)) {
    ConstantInt* C2 = cast<ConstantInt>(S2);
    R2 = new ConstantRange(C2->getValue());
  }
  else if (result->representation.count(S2->get()) > 0){
    R2 = result->representation[S2->get()];
  }
  else{
    R2 = new ConstantRange(32, false);
  }
  ConstantRange* range = new ConstantRange(32, true);
  *range = *(helper::foldBinaryOperator(current->getOpcode(), R1, R2));
  
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
  info_out.clear();
  info_out.push_back(result);
}



/*
 BranchInst IS terminator.
 */

void RAFlowFunction::visitBranchInst(BranchInst &BI){
  RALatticePoint* inRLP = new RALatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  
  if (BI.isUnconditional()) {
    for (std::map<Value *, LatticePoint *>::iterator it=out_map.begin(); it != out_map.end(); ++it){
      Value* elm = it->first;
      out_map[elm] = inRLP;
    }
  }
  else{
    Value* cond = BI.getCondition();
    if (isa<ICmpInst>(cond)) {
      // may affect elements of our lattice.
      std::pair<Use*, Use *> branches = helper::getBranches(BI);
      Use* true_branch = branches.first;
      Use* false_branch = branches.second;
      /*
      errs() << "Examining instruction" << BI << "\n";
      errs() << "True branch is " << * (true_branch->get()) << "\n";
      errs() << "False branch is " << * (false_branch->get()) << "\n";
      */
      
      ICmpInst* cmp = cast<ICmpInst>(cond);
      std::pair<Use*, Use *> operands = helper::getOperands(*cmp);
      Use* right_hand_side = operands.second;
      Use*  left_hand_side = operands.first;
      
      /*
      errs() << "Comparison " << *cmp << "\n";
      errs() << "Left hand side is " << * (left_hand_side->get()) << "\n";
      errs() << "Right hand side is " << * (right_hand_side->get()) << "\n";
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
        lhs_range = new ConstantRange(32, false);
      }
      
      if (inRLP->representation.count(right_hand_side->get()) > 0) {
        rhs_range = inRLP->representation[right_hand_side->get()];
      }
      else if (isa<ConstantInt>(right_hand_side->get())) {
        ConstantInt* C2 = cast<ConstantInt>(right_hand_side->get());
        rhs_range = new ConstantRange(C2->getValue());
      }
      else{
        rhs_range = new ConstantRange(32, false);
      }
      /*
      errs() << "Left hand side has range ";
      lhs_range->print(errs());
      errs() << "\nRight hand side has range ";
      rhs_range->print(errs());
      errs() << " \n ";
      */
      // First we compute the restrictions that cmp makes upon the regions.
      
      //errs() << " Compare looks like " << *cmp << "\n";

      int predicate = 0;
      
      if (cmp->isSigned()) {
        predicate = cmp->getSignedPredicate();
      }
      else{
        predicate = cmp->getUnsignedPredicate();
      }
      
      ConstantRange true_branch_lhs_restriction = ConstantRange::makeICmpRegion(predicate, *rhs_range);
      
      /*
      errs() << "True branch lhs_restriction: ";
      true_branch_lhs_restriction.print(errs());
      errs() << "\n";
      */
      
      ConstantRange false_branch_lhs_restriction = (ConstantRange(32, true)).difference(true_branch_lhs_restriction);
      
      /*
      errs() << "False branch lhs_restriction: ";
      false_branch_lhs_restriction.print(errs());
      errs() << "\n";
      */
      
      cmp->swapOperands();
      
      //errs() << " After swapping, compare looks like " << *cmp << "\n";

      
      ConstantRange true_branch_rhs_restriction = ConstantRange::makeICmpRegion(predicate,*lhs_range);
      
      /*
      errs() << "\nTrue branch rhs_restriction: ";
      true_branch_rhs_restriction.print(errs());
      errs() << " is it wrapped range? " << true_branch_rhs_restriction.isSignWrappedSet() << " is it empty? " << true_branch_rhs_restriction.isEmptySet() << " what is its size? " << true_branch_rhs_restriction.getSetSize() << "\n";
      */
      
      ConstantRange false_branch_rhs_restriction = (ConstantRange(32, true)).difference(true_branch_rhs_restriction);
      
      /*
      errs() << "False branch rhs_restriction: ";
      false_branch_rhs_restriction.print(errs());
      errs() << "\n";
      
      
      */
      
      cmp->swapOperands();
      
      // Next we intersect the ranges with the resulting restrictions.
      ConstantRange* true_branch_lhs_range = new ConstantRange(lhs_range->getBitWidth(), true);
      ConstantRange* false_branch_lhs_range = new ConstantRange(lhs_range->getBitWidth(), true);
      ConstantRange* true_branch_rhs_range = new ConstantRange(rhs_range->getBitWidth(), true);
      ConstantRange* false_branch_rhs_range = new ConstantRange(rhs_range->getBitWidth(), true);
      
      *true_branch_lhs_range = lhs_range->intersectWith(true_branch_lhs_restriction);
      *false_branch_lhs_range = lhs_range->intersectWith(false_branch_lhs_restriction);
      
      *true_branch_rhs_range = rhs_range->intersectWith(true_branch_rhs_restriction);
      *false_branch_rhs_range = rhs_range->intersectWith(false_branch_rhs_restriction);
      
      /*
      errs() << "True branch lhs range ";
      true_branch_lhs_range->print(errs());
      errs() << "\n";
      
      
      errs() << "False branch lhs range ";
      false_branch_lhs_range->print(errs());
      errs() << "\n";
      
      
      errs() << "True branch rhs range ";
      true_branch_rhs_range->print(errs());
      errs() << "\n";
      
      
      errs() << "False branch rhs range ";
      false_branch_rhs_range->print(errs());
      errs() << "\n";
      */
      
      RALatticePoint* true_branchRLP = new RALatticePoint(*inRLP);
      RALatticePoint* false_branchRLP = new RALatticePoint(*inRLP);
      
      
      true_branchRLP->isBottom = false;
      true_branchRLP->isTop = false;

      false_branchRLP->isBottom = false;
      false_branchRLP->isTop = false;

      if (inRLP->representation.count(left_hand_side->get()) > 0){
        //errs() << "\nIn if statement for lhs \n";

        
        true_branchRLP->representation[left_hand_side->get()] = true_branch_lhs_range;
        false_branchRLP->representation[left_hand_side->get()] = false_branch_lhs_range;
        /*
        errs() << "True branch lhs range ";
        true_branch_lhs_range->print(errs());
        errs() << "\n";
        
        
        errs() << "False branch lhs range ";
        false_branch_lhs_range->print(errs());
        errs() << "\n";
         */
      }
      if (inRLP->representation.count(right_hand_side->get()) > 0){
        //errs() << "\nIn if statement for rhs \n";
        
        true_branchRLP->representation[right_hand_side->get()] = true_branch_rhs_range;
        false_branchRLP->representation[right_hand_side->get()] = false_branch_rhs_range;
        /*
        errs() << "True branch rhs range ";
        true_branch_rhs_range->print(errs());
        errs() << "\n";
        
        
        errs() << "False branch rhs range ";
        false_branch_rhs_range->print(errs());
        errs() << "\n";
        */
      }
      /*
       info_out.push_back(true_branchRLP);
       info_out.push_back(false_branchRLP);
      */
      
      out_map[true_branch->get()] = true_branchRLP;
      /*
      errs() << "\nTrue branch lattice point is ";
      true_branchRLP->printToErrs();
      */
      out_map[false_branch->get()] = false_branchRLP;
      /*
      errs() << "\nFalse branch lattice point is ";
      false_branchRLP->printToErrs();
      */
    }
    else{
      // does not affect our lattice.
      for (std::map<Value *, LatticePoint *>::iterator it=out_map.begin(); it != out_map.end(); ++it){
        Value* elm = it->first;
        out_map[elm] = inRLP;
      }
    }
  }
}

/*
 CastInst is NOT terminator.
 */

void RAFlowFunction::visitCastInst(CastInst &I){
  info_out.clear();
  RALatticePoint* inRLP = new RALatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  info_out.push_back(inRLP);
}

/*
 CmpInst is NOT terminator.
 */


void RAFlowFunction::visitCmpInst(CmpInst &I){
  //errs() << "In cmp instruction \n";
  info_out.clear();
  RALatticePoint* inRLP = new RALatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  info_out.push_back(inRLP);
}


/*
 TerminatorInst IS terminator.
 */

void RAFlowFunction::visitTerminatorInst(TerminatorInst &I){
  RALatticePoint* inRLP = new RALatticePoint(*(info_in_casted.back()));
  for (std::map<Value *, LatticePoint *>::iterator it=out_map.begin(); it != out_map.end(); ++it){
    Value* elm = it->first;
    out_map[elm] = inRLP;
  }
}

/*
 PHINode is NOT a terminator.
 */
void RAFlowFunction::visitPHINode(PHINode &PHI){
  while (info_in_casted.size() > 1) {
    LatticePoint *l1 = info_in_casted.back();
    info_in_casted.pop_back();
    LatticePoint *l2 = info_in_casted.back();
    info_in_casted.pop_back();
    RALatticePoint* result = dyn_cast<RALatticePoint>(l1->join(l2));
    info_in_casted.push_back(result);
  }
  RALatticePoint* inRLP = new RALatticePoint(*(info_in_casted.back()));
  PHINode* current = &PHI;
  ConstantRange* current_range = new ConstantRange(32, false);
  int num_incoming_vals = PHI.getNumIncomingValues();
  for (int i = 0; i != num_incoming_vals; i++){
    Value* val = PHI.getIncomingValue(i);
    if (inRLP->representation.count(val) > 0) {
      *current_range = current_range->unionWith(*(inRLP->representation[val])); // Optimistic analysis
    }
  }
  
  inRLP->representation[current] = current_range;
  //inRLP->printToErrs();
  
  info_out.clear();
  info_out.push_back(inRLP);
}


/*
 
 
 */
void visitAllocaInst(AllocaInst &AI)
{
  info_out.clear();
  RALatticePoint* inRLP = new RALatticePoint(*(info_in_casted.back()));
  info_out.push_back(inRLP);
}

/*
 Since we don't know much about pointers, at the end of this, the only thing that will change is that LI --> full-range
 */
void visitLoadInst(LoadInst     &LI){
  info_out.clear();
  RALatticePoint* inRLP = new RALatticePoint(*(info_in_casted.back()));
  Value* current = &LI;
  if(inRLP->isTop){
    info_out.push_back(inRLP);
  }
  else{
    ConstantRange current_range = new ConstantRange(32, true);
    inRLP->representation[current] = current_range;
    info_out.push_back(inRLP);
  }
}

/*
 We don't know much about pointers, stores can affect any variable.
 However, because LLVM has type-safety, the only stores that can affect
 variables we care about are stores of ConstantInts. Thus, we must expand all the ranges
 of all variables in our lattice point to include the stored value.
 */

void visitStoreInst(StoreInst   &SI){
  info_out.clear();
  RALatticePoint* inRLP = new RALatticePoint(*(info_in_casted.back()));
  
  Value* y = SI.getValueOperand();
  if (isa<ConstantInt>(y)) {
    ConstantInt* c = cast<ConstantInt>(y);
    ConstantRange* c_range = new ConstantRange(c->getValue());
    
    std::map<Value*, ConstantRange*> representation = inRLP->representation;
    for (std::map<Value*, ConstantRange*>::iterator it=representation.begin(); it!=representation.end(); ++it){
      Value* elm = it->first;
      ConstantRange* curr_range = it->second;
      ConstantRange* new_range = new ConstantRange(32, true);
      *new_range = current_range->unionWith(c_range);
      inRLP->representation[elm] = new_range;
    }
  }
  info_out.push_back(inRLP);
}

/*
 UnaryInstruction is not terminator.
 */
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




