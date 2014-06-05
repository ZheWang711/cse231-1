#include "flowFunctions/CSEFlowFunction.h"

std::vector<LatticePoint *> CSEFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){
  // dyncast on that vector;
  errs() << "In operator \n";
  info_in_casted = std::vector<CSELatticePoint *>();
  for (std::vector<LatticePoint *>::iterator it = info_in.begin(); it != info_in.end(); ++it){
    CSELatticePoint* temp = dyn_cast<CSELatticePoint>(*it);
    temp->printToErrs();
    info_in_casted.push_back(temp);
  }
  info_out.clear();
  errs() << "About to call visit with " << info_in_casted.size() << " arguments \n";
  this->visit(instr);
  errs() << "Done with visit \n";
  if(info_out.size() >= 1){
    return info_out;
  }else{
    // no visit defined, return top
    info_out.push_back(new CSELatticePoint(false, true, std::map<Value*, Instruction*>()));
    return info_out;
  }
}

void CSEFlowFunction::visitAllocaInst(AllocaInst &AI) {
  errs() << "CSEflow visiting an alloca \n";
  // ++Count; 
  // just stick bottom in the ret_value every time we hit an alloca (testing)
  info_out.push_back(new CSELatticePoint(false, true, std::map<Value*, Instruction*>()));
}

void CSEFlowFunction::visitBinaryOperator(BinaryOperator &BO) { 
  errs() << "CSEflow visiting a binary operator \n";
  errs() << "Info_in_casted.size() = " << info_in_casted.size() << "\n";
  // Haul representation out of lattice point we're supplied with
  std::map<Value*, Instruction*> input_rep = info_in_casted.front()->representation;
  // iterate over the pairs in the map. print them out for lack of
  // anything better to do.

  for (std::map<Value*, Instruction*>::iterator it=input_rep.begin(); it!=input_rep.end(); ++it){
    // errs() << print(it->first) << " => " << print(it->second) << '\n';

    Value* left_hand_side = it->first;
    Value* right_hand_side = it->second;
    left_hand_side->print(errs());
    right_hand_side->print(errs());

  }
}
