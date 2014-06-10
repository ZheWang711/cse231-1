#include "flowFunctions/CSEFlowFunction.h"



std::vector<LatticePoint *> CSEFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){

  // the memory management here is totally screwed up. new try:
  // copypasta of Chris' version of this thing.

  // dyncast on that vector;
  info_in_casted = std::vector<CSELatticePoint *>();
  
  errs() << "In instruction ";
  instr->print(errs());
  errs() << "Handed lattice point(s): \n";

  
  for (std::vector<LatticePoint *>::iterator it = info_in.begin(); it != info_in.end(); ++it){
    CSELatticePoint* temp = dyn_cast<CSELatticePoint>(*it);
    temp->printToErrs();
    info_in_casted.push_back(temp);
  }

  // Does this assume that we're handed only one input argument?
  // CSELatticePoint* old_state = new CSELatticePoint(*(info_in_casted.back()));
  info_out.clear();
  this->visit(instr);
  // LatticePoint* temp = info_out.back();
  // CSELatticePoint* temp1 = dyn_cast<CSELatticePoint>(temp);
  // CSELatticePoint* new_state = new CSELatticePoint(*temp1);
  // std::vector<Value*> differing_vals = new_state->differInRange(old_state);
  
  
  // for (int i = 0; i < differing_vals.size(); i++) {
  //   Value* val = differing_vals[i];
  //   if (counter_map.count(val) <= 0){
  //     counter_map[val] = 1;
  //   }
  //   else if (counter_map[val] == MAX_COUNT){
  //     new_state->representation[val] = new ConstantRange(32, true);
  //   }
  //   else{
  //     counter_map[val] = counter_map[val] + 1;
  //   }
  // }
  // info_out.clear();
  // info_out.push_back(new_state);
  return info_out;

  // // Print tells us what we're doing.
  // errs() << "In operator for CSEFlowFunction: setting up state for the current call. \n";

  // // errs() << info_in;

  // // for (std::vector<LatticePoint *>::iterator it = info_in.begin(); it != info_in.end(); ++it){
  // //   if (CSELatticePoint* CSELP = dyn_cast<CSELatticePoint>(*it)) {
  // //     CSELatticePoint* tmp = new CSELatticePoint(CSELP);
  // //     // if this causes problems maybe cast tmp to a LatticePoint*
  // //     tmp->printToErrs();
  // //   }else{
  // //     errs() << "BAD BAD THERE IS TERRIBLE PROBLEM PASSED IN A WRONG TYPE LATTICE POINT TO CSEFLOW \n";
  // //   }
  // // }

  // // First, make ABSOLUTELY SURE that info_in_cached has a safe copy
  // // of the input, in case we want to return the input latticePoint
  // // with no changes. This way, nothing can change info_in_cached if
  // // it changes info_in.
  // info_in_cached = std::vector<LatticePoint *>();
  // for (std::vector<LatticePoint *>::iterator it = info_in.begin(); it != info_in.end(); ++it){
  //   if (CSELatticePoint* CSELP = dyn_cast<CSELatticePoint>(*it)) {
  //     CSELatticePoint* tmp = new CSELatticePoint(CSELP);
  //     // if this causes problems maybe cast tmp to a LatticePoint*
  //     info_in_cached.push_back(tmp);
  //   }else{
  //     errs() << "BAD BAD THERE IS TERRIBLE PROBLEM PASSED IN A WRONG TYPE LATTICE POINT TO CSEFLOW \n";
  //   }
  // }

  // errs() << "Managed to create info_in_cached. \n";

  // // Next, dyn_cast everything in info_in from a LatticePoint to a
  // // CSELatticePoint. Also copy here, giving us freedom to mess with
  // // info_in_casted and not touch info_in.
  // info_in_casted = std::vector<CSELatticePoint *>();
  // for (std::vector<LatticePoint *>::iterator it = info_in.begin(); it != info_in.end(); ++it){
  //   if (CSELatticePoint* CSELP = dyn_cast<CSELatticePoint>(*it)) {
  //     CSELatticePoint* tmp = new CSELatticePoint(CSELP);
  //     info_in_casted.push_back(tmp);
  //   }else{
  //     errs() << "BAD BAD THERE IS TERRIBLE PROBLEM PASSED IN A WRONG TYPE LATTICE POINT TO CSEFLOW \n";
  //   }
  // }

  // // precondition of any Visit: info_out is EMPTY
  // info_out = std::vector<LatticePoint *>();
  // errs() << "About to call visit with " << info_in_casted.size() << " arguments \n";
  // this->visit(instr);
  // errs() << "Done with visit \n";
  // if(info_out.size() >= 1){
  //   return info_out;
  // }else{
  //   // no visit defined, return top
  //   info_out.push_back(new CSELatticePoint(false, true, std::map<Value*, Instruction*>()));
  //   return info_out;
  // }
}

// A comment on return idioms: I believe that it is ok to use info_out
// = info_in_cached if this is the VERY LAST LINE of a visit
// implementation, because given that the return point will always be
// the same no mutation of either of these things occurs.

// Of course, the worklist algorithm now has a pointer to,
// essentially, info_out and info_in_cached in this instance. Does
// this mean that using clear() locally could screw up the worklist
// algorithm? Should I switch this to making fresh info_* objects
// every time operator() is invoked?


void CSEFlowFunction::visitAllocaInst(AllocaInst &AI) {
  errs() << "CSEflow visiting an alloca \n";
  // ++Count; 
  // just stick bottom in the ret_value every time we hit an alloca (testing)
  info_out.push_back(new CSELatticePoint(false, true, std::map<Value*, Instruction*>()));
}

void CSEFlowFunction::visitBranchInst(BranchInst &BI){
  // In this case, we just copy back whatever was passed in, because
  // branch instruction do nothing for us.
  errs() << "In branch instruction \n";
  CSELatticePoint* result = new CSELatticePoint(*(info_in_casted.back()));
  info_out.push_back(result);
  return;
}

void CSEFlowFunction::visitCmpInst(CmpInst &I){
  errs() << "In cmp instruction \n";
  CSELatticePoint* result = new CSELatticePoint(*(info_in_casted.back()));
  info_out.push_back(result);
  return;
}

 
void CSEFlowFunction::visitPHINode(PHINode &PHI){
  errs() << "In PHI instruction \n";
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

  for (std::vector<CSELatticePoint *>::iterator it = info_in_casted.begin(); it != info_in_casted.end(); ++it){
    errs() << "Post join, visitPHINode has this lattice point:";
    (*it)->printToErrs();
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
	  CSELatticePoint* result = new CSELatticePoint(*(info_in_casted.back()));
	  info_out.push_back(result);

  	  return;
  	}
      }else{
	errs() << "operand to PHI not an instruction, can't do CSE \n";
	CSELatticePoint* result = new CSELatticePoint(*(info_in_casted.back()));
	info_out.push_back(result);

	return;
      }
    }else {
      errs() << "operand to PHI not an instruction, can't do CSE \n";
      CSELatticePoint* result = new CSELatticePoint(*(info_in_casted.back()));
      info_out.push_back(result);

      return;
    }
  }

  // this is actually wrong. We need to make the PHI node point at one
  // of these things, not one of the instructions point to each other.

  inCSELP->representation[current] = dyn_cast<Instruction>(PHI.getIncomingValue(0));
  info_out.push_back(inCSELP);
  
  errs() <<  "sending back" << info_out.size() << "elements \n";
  inCSELP->printToErrs();
  return;
}

void CSEFlowFunction::visitBinaryOperator(BinaryOperator &BO) { 
  errs() << "CSEflow visiting a binary operator \n";
  errs() << "Info_in_casted.size() = " << info_in_casted.size() << "\n";
  

  // Haul representation out of lattice point we're supplied with. Of
  // course, this looks like it is just aliasing? Maybe it actually
  // copies because we're going from one std::map to another?
  std::map<Value*, Instruction*> input_rep = info_in_casted.front()->representation;

  errs() << "Input instruction is: ";
  BO.print(errs());
  errs() << "  @  " << &BO << " \n ";

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
  CSELatticePoint* tmp_created = new CSELatticePoint(false, false, input_rep);
  errs() << "Giving back: \n";
  tmp_created->printToErrs();
  info_out.push_back(tmp_created);
}
