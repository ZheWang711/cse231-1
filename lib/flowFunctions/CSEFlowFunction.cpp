#include "flowFunctions/CSEFlowFunction.h"

std::vector<LatticePoint *> CSEFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){
  info_in_cached = info_in;
  // dyncast on that vector;
  errs() << "In operator \n";
  info_in_casted = std::vector<CSELatticePoint *>();
  for (std::vector<LatticePoint *>::iterator it = info_in.begin(); it != info_in.end(); ++it){
    CSELatticePoint* temp = dyn_cast<CSELatticePoint>(*it);
    temp->printToErrs();
    info_in_casted.push_back(temp);
  }
  // precondition of any Visit: info_out is EMPTY
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

void CSEFlowFunction::visitBranchInst(BranchInst &BI){
  // In this case, we just copy back whatever was passed in, because
  // branch instruction do nothing for us.
  info_out = info_in_cached;
  return;
}

void CSEFlowFunction::visitCmpInst(CmpInst &I){
  errs() << "In cmp instruction \n";
  info_out = info_in_cached;
}

 
void CSEFlowFunction::visitPHINode(PHINode &PHI){
  // this will pairwise-join all incoming CSELatticePoints on the
  // edges
  while (info_in_casted.size() > 1) {
    LatticePoint *l1 = info_in_casted.back();
    info_in_casted.pop_back();
    LatticePoint *l2 = info_in_casted.back();
    info_in_casted.pop_back();
    CSELatticePoint* result = dyn_cast<CSELatticePoint>(l1->join(l2));
    info_in_casted.push_back(result);
  }

  // get a pointer to the phi node (by executing "address of" on a
  // reference, as if that isn't an insane and broken language
  // construct)
  PHINode* current = &PHI;

  CSELatticePoint* inCSELP = new CSELatticePoint(*(info_in_casted.back()));

  // Now: compare each incoming expression to each incoming
  // instruction pairwise

  int num_incoming_vals = PHI.getNumIncomingValues();
  errs() << "phi node has " << num_incoming_vals << " incoming values \n";

  for (int i = 0; i+1 <= (num_incoming_vals-1); i++){
    Value* val_left = PHI.getIncomingValue(i);
    Value* val_right = PHI.getIncomingValue(i+1);
    if (Instruction* instL = dyn_cast<Instruction>(val_left)){
      if(Instruction* instR = dyn_cast<Instruction>(val_right)) {
  	// both operands are instructions
  	if(instL->isIdenticalToWhenDefined(instR)){
	  // 
	  errs() << "a pair of phi operands compared equal \n";
  	  continue;
  	}else{
	  errs() << "a pair of phi operands compared NOT equal \n";
  	  info_out = info_in_cached;
  	  return;
  	}
      }else{
	errs() << "operand to PHI not an instruction, can't do CSE \n";
	info_out = info_in_cached;
	return;
      }
    }else {
      errs() << "operand to PHI not an instruction, can't do CSE \n";
      info_out = info_in_cached;
      return;
    }
  }
  
  inCSELP->representation[current] = dyn_cast<Instruction>(PHI.getIncomingValue(0));
  info_out.push_back(inCSELP);
  
  errs() <<  "sending back" << info_out.size() << "elements \n";
  inCSELP->printToErrs();
  return;
  // info_out.push_back(inCSELP);
  // return;
}

void CSEFlowFunction::visitBinaryOperator(BinaryOperator &BO) { 
  errs() << "CSEflow visiting a binary operator \n";
  errs() << "Info_in_casted.size() = " << info_in_casted.size() << "\n";
  // Haul representation out of lattice point we're supplied with
  std::map<Value*, Instruction*> input_rep = info_in_casted.front()->representation;
  // iterate over the pairs in the map. print them out for lack of
  // anything better to do.
  
  errs() << "Input instruction is: ";
  BO.print(errs());
  errs() << "  @ " << &BO << " \n ";

  errs() << "Input LP representation is: ";
  info_in_casted.front()->printToErrs();

  if (input_rep.count(&BO) > 0){
    errs() << "This value is already mapped to something \n";
    info_out = info_in_cached;
    return;
  }else{ 
    errs() << "This value is not mapped to anything, therefore we continue analysis \n";
  }
  
  Value* visited_value = &BO;
  Instruction* equal_to_visited_value;
  bool found_equal;
  
  for (std::map<Value*, Instruction*>::iterator it=input_rep.begin(); it!=input_rep.end(); ++it){

    Value* left_hand_side_val = it->first;
    Instruction* right_hand_side_instr = it->second;
    Value* right_hand_side_val = it->second;

    // left_hand_side->print(errs());
    // right_hand_side->print(errs());

    if(right_hand_side_instr->isIdenticalToWhenDefined(&BO)){
      errs() << "Instructions are identical when defined \n";
      equal_to_visited_value = right_hand_side_instr;
      found_equal = true;
    }    
  }
  if(found_equal){
    input_rep[visited_value] = equal_to_visited_value;
  }else{
    input_rep[visited_value] = dyn_cast<Instruction>(visited_value);
  }
  info_out.push_back(new CSELatticePoint(false, false, input_rep));

}
