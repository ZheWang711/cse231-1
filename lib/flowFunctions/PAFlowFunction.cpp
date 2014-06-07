#include "flowFunctions/PAFlowFunction.h"
#include <list>

/*
 Non-terminator operator
 */

std::vector<LatticePoint *> PAFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){
  // dyncast on that vector;
  //errs() << "In operator \n";
  info_in_casted = std::vector<PALatticePoint *>();
  for (std::vector<LatticePoint *>::iterator it = info_in.begin(); it != info_in.end(); ++it){
    PALatticePoint* temp = dyn_cast<PALatticePoint>(*it);
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


/*
 By SSA, we will never overwrite a pointer with a binary operation. Thus, we punt on this lattice point.
 */

void PAFlowFunction::visitBinaryOperator(BinaryOperator &BO) {
  info_out.clear();
  PALatticePoint* inRLP = new PALatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  info_out.push_back(inRLP);
}


/*
 We punt on this lattice point.
 */

void PAFlowFunction::visitCastInst(CastInst &I){
  info_out.clear();
  PALatticePoint* inRLP = new PALatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  info_out.push_back(inRLP);
}

/*
 We punt on this lattice point.
 */
void PAFlowFunction::visitCmpInst(CmpInst &I){
  info_out.clear();
  PALatticePoint* inRLP = new PALatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  info_out.push_back(inRLP);
}


/*
 We punt on this lattice point.
 */

void PAFlowFunction::visitTerminatorInst(TerminatorInst &I){
  info_out.clear();
  PALatticePoint* inRLP = new PALatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  info_out.push_back(inRLP);
}

/*
  We need to union on incoming points_to sets.
 */
void PAFlowFunction::visitPHINode(PHINode &PHI){
  while (info_in_casted.size() > 1) {
    LatticePoint *l1 = info_in_casted.back();
    info_in_casted.pop_back();
    LatticePoint *l2 = info_in_casted.back();
    info_in_casted.pop_back();
    PALatticePoint* result = dyn_cast<PALatticePoint>(l1->join(l2));
    info_in_casted.push_back(result);
  }
  PALatticePoint* inRLP = new PALatticePoint(*(info_in_casted.back()));
  
  PHINode* current = &PHI;
  
  std::set<Value*> current_points_to_set;
  int num_incoming_vals = PHI.getNumIncomingValues();
  for (int i = 0; i != num_incoming_vals; i++){
    Value* val = PHI.getIncomingValue(i);
    if (inRLP->pointers_to_anything.count(val) > 0) {
      inRLP->pointers_to_anything.insert(current);
      break;
    }
    else if (inRLP->representation.count(val) > 0) {
      std::set<Value*> val_points_to_set = inRLP->representation[val];
      for (std::set<Value*>::iterator it = val_points_to_set.begin(); it!=val_points_to_set.end(); ++it) {
        current_points_to_set.insert(*it);
      }
    }
  }
  if (inRLP->pointers_to_anything.count(current) <= 0) {
    if (current_points_to_set.size() == 0 && inRLP->isBottom) { // We are still at bottom.
      inRLP->isTop = false;
      inRLP->isBottom = true;
    }
    else{ // We are neither top nor bottom
      inRLP->isTop = false;
      inRLP->isBottom = false;
      inRLP->representation[current] = current_points_to_set;
    }
  }
  else if(inRLP->isTop){ // We are still at top then
    inRLP->isTop = true;
    inRLP->isBottom = false;
  }
  
  info_out.clear();
  info_out.push_back(inRLP);
}


// Punt...
void PAFlowFunction::visitAllocaInst(AllocaInst &AI){
  info_out.clear();
  PALatticePoint* inRLP = new PALatticePoint(*(info_in_casted.back()));
  info_out.push_back(inRLP);
}

/*
  Corresponds to calls of the form 
            y = *x;
  This means for an instruction like %y = load %x, we add elements of the form y --> a to our lattice point, 
  where there exists a b s.t. x --> b and b -->a are both in our lattice point.
 
  LI.getPointerOperand() corresponds to %x in the above.
  LI corresponds to %y.
 */

void PAFlowFunction::visitLoadInst(LoadInst     &LI){
  info_out.clear();
  PALatticePoint* inRLP = new PALatticePoint(*(info_in_casted.back()));
  
  Value* y = &LI;
  Value* tmp = LI.getPointerOperand();
  errs() << "In load instruction: ";
  LI.print(errs());
  errs() << " Pointer is ";
  tmp->print(errs());
  errs() << "\n";
  
  AllocaInst* x = dyn_cast<AllocaInst>(tmp);
  
  Type* x_alloca = x->getAllocatedType();
  if (isa<PointerType>(x_alloca)) {
    std::set<Value*> y_points_to_set;
    if (inRLP->pointers_to_anything.count(x) > 0){
      inRLP->pointers_to_anything.insert(y);
    }
    else if (inRLP->representation.count(x) > 0){
      std::set<Value*> x_points_to_set = inRLP->representation[x];
      for (std::set<Value*>::iterator it = x_points_to_set.begin(); it!=x_points_to_set.end(); ++it){
        Value* b = *it;
        if (inRLP->pointers_to_anything.count(b) > 0) {
          inRLP->pointers_to_anything.insert(y);
          break;
        }
        else if(inRLP->pointers_to_anything.count(b) > 0){
          std::set<Value*> b_points_to_set = inRLP->representation[b];
          for (std::set<Value*>::iterator it1 = x_points_to_set.begin(); it1!=x_points_to_set.end(); ++it){
            Value* a = *it1;
            y_points_to_set.insert(a);
          }
        }
      }
    }
    if (inRLP->pointers_to_anything.count(y) <= 0) {  // Is y pointing to anything?
      if (y_points_to_set.size() == 0 && inRLP->isBottom) { // We are still at bottom.
        inRLP->isTop = false;
        inRLP->isBottom = true;
      }
      else{ // We are neither top nor bottom
        inRLP->isTop = false;
        inRLP->isBottom = false;
        inRLP->representation[y] = y_points_to_set;
      }
    }
    else if(inRLP->isTop){ // We are still at top then
      inRLP->isTop = true;
      inRLP->isBottom = false;
    }
  }
  info_out.push_back(inRLP);
  
}


/*
  Corresponds to calls of the form
    x = &y    and    *x = y
  
  This means for instructions like store %y %x, we add x --> y to our lattice point and all elements of the form
  a --> b where x--> a and y --> b.
 
  In our code, x corresponds to SI.getPointerOperand() and y corresponds to SI.getValueOperand()
 */

void PAFlowFunction::visitStoreInst(StoreInst   &SI){
  info_out.clear();
  PALatticePoint* inRLP = new PALatticePoint(*(info_in_casted.back()));
  
  Value* x = SI.getPointerOperand();
  Value* y = SI.getValueOperand();
  
  
  
  info_out.push_back(inRLP);
  /*
  errs() << "In store instruction: ";
  SI.print(errs());
  errs() << " Pointer is ";
  pointer->print(errs());
  errs() << " Value is ";
  value->print(errs());
  errs() << "\n";
   */
}

/*
 UnaryInstruction is not terminator.
 */
void PAFlowFunction::visitUnaryInstruction(UnaryInstruction &I){
  info_out.clear();
  PALatticePoint* result = new PALatticePoint(false, true, std::map<Value*, std::set<Value*> >());
  info_out.push_back(result);
}

// Be safe with memory!
void PAFlowFunction::visitInstruction(Instruction &I){
  info_out.clear();
  PALatticePoint* result = new PALatticePoint(false, true, std::map<Value*, std::set<Value*> >());
  info_out.push_back(result);
}




