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
 We need to union on incoming ranges.
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
  /*
  PHINode* current = &PHI;
  ConstantRange* current_range = new ConstantRange(32, false);
  int num_incoming_vals = PHI.getNumIncomingValues();
  for (int i = 0; i != num_incoming_vals; i++){
    Value* val = PHI.getIncomingValue(i);
    if (inRLP->representation.count(val) > 0) {
      *current_range = current_range->unionWith(*(inRLP->representation[val]));
    }
  }
  
  inRLP->representation[current] = current_range;
  */
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
 */

void PAFlowFunction::visitLoadInst(LoadInst     &LI){
  info_out.clear();
  PALatticePoint* inRLP = new PALatticePoint(*(info_in_casted.back()));
  
  Value* pointer = LI.getPointerOperand();
  info_in_casted.pop_back();
  info_out.push_back(inRLP);
  /*
  errs() << "In load instruction: ";
  LI.print(errs());
  errs() << " Pointer is ";
  pointer->print(errs());
  errs() << "\n";
  */
}


/*
  Corresponds to calls of the form
            y = &x;
  We put in SI.getPointerOperand() --> SI.getValueOperand()
 */
void PAFlowFunction::visitStoreInst(StoreInst   &SI){
  info_out.clear();
  PALatticePoint* inRLP = new PALatticePoint(*(info_in_casted.back()));
  
  Value* pointer = SI.getPointerOperand();
  Value* value = SI.getValueOperand();
  
  std::set<Value *> pointer_range;
  pointer_range.insert(value);
  inRLP->representation[pointer] = pointer_range;
  inRLP->isTop = false;
  inRLP->isBottom = false;
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




