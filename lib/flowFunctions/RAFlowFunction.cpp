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


void RAFlowFunction::visitBinaryOperator(BinaryOperator &BO) {
  User S1;
  USer S2;
  int = 0;
  for (User::op_iterator OP = BO->op_begin(), OPE = I->op_end(); OP != OPE; ++OP){
    if(i = 0){
      S1 = *OP;
    }
    else{
      S2 = *OP;
    }
    i++;
  }
  if (ConstantInt* C1 = dyn_cast<ConstantInt>(&S1)) {
    if (ConstantInt* C2 = dyn_cast<ConstantInt>(&S2)) {
      curr = helper::foldBinaryOperator(BO.getOpcode(),C1, C2);
    }
  }
}

void RAFlowFunction::visitStoreInst(StoreInst   &I){
  value = I.getValueOperand();
  pointer = I.getPointerOperand();
  if (isa<ConstantInt>(value)){
    ret_value.representation[pointer] = std::make_pair(std::make_pair(false, false), std::make_pair(cast<ConstantInt>(value), cast<ConstantInt>(value)));
  }
  else{
    ConstantInt* filler = NULL;
    std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > val = std::make_pair(std::make_pair(true, true), std::make_pair(filler, filler));
    ret_value.representation[pointer] = val;
  }
}

std::string RAFlowFunction::getRepresentation(){
  std::string rep;
  std::map<Value*, std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > > representation = ret_value.representation;
  for (std::map<Value*, std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > >::iterator it=representation.begin(); it!=representation.end(); ++it){
    Value* elm = it->first;
    std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > range = it->second;
    bool isLeftInfinite = (range.first).first;
    bool isRightInfinite = (range.first).second;
    std::string rep = (elm->getName()).str();
    if (isLeftInfinite && isRightInfinite){
      rep += " --> (-infinite, infinite)";
    }
    if (isLeftInfinite && !isRightInfinite){
      rep += " --> (-infinite, ";
      rep += (range.second.first->getValue()).toString(10, true);
      rep += " )";
    }
    if (!isLeftInfinite && isRightInfinite){
      rep += " --> ( ";
      rep += (range.second.second->getValue()).toString(10, true);
      rep += ", infinite)";
    }
    if (isLeftInfinite && !isRightInfinite){
      rep += " --> (-infinite, ";
      rep += (range.second.first->getValue()).toString(10, true);
      rep += " )";
    }
    else{
      rep += " --> ( ";
      rep += (range.second.first->getValue()).toString(10, true);
      rep += " , ";
      rep += (range.second.second->getValue()).toString(10, true);
      rep += " )";
    }
  }
  return rep;
}





