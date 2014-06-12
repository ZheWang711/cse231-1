#include "flowFunctions/CPFlowFunction.h"

std::vector<LatticePoint *> CPFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){
  // first, ensure that info_in_casted is empty
  info_in_casted = std::vector<CPLatticePoint *>();
  
  for(std::vector<LatticePoint *>::iterator it = info_in.begin(); it != info_in.end(); ++it) {
    CPLatticePoint *in_lattice_point = dyn_cast<CPLatticePoint>(*it);
    info_in_casted.push_back(in_lattice_point);
  }
  visit(instr);
  if (!ret_value) {
    errs() << "NEED TO IMPL VISIT FOR THIS INSTR: ";
    instr->print(errs());
    return std::vector<LatticePoint*>();
  }
  LatticePoint* lp = dyn_cast<LatticePoint>(ret_value);
  std::vector<LatticePoint*> info_out;
  info_out.push_back(lp);
  return info_out;
}

std::map<Value *, LatticePoint *> CPFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in, std::map<Value *, LatticePoint *> successor_map){
  out_map = successor_map;
  info_in_casted = std::vector<CPLatticePoint *>();
  for (std::vector<LatticePoint *>::iterator it = info_in.begin(); it != info_in.end(); ++it){
    CPLatticePoint* temp = dyn_cast<CPLatticePoint>(*it);
    info_in_casted.push_back(temp);
  }

  this->visit(instr);
  return out_map;
}

void CPFlowFunction::visitAllocaInst(AllocaInst &AI) {
  CPLatticePoint* result = new CPLatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();

  // ++Count; 
  // just stick bottom in the ret_value every time we hit an alloca (testing)
   ret_value = new CPLatticePoint(result->isBottom, result->isTop, std::map<Value*, ConstantInt*>(result->representation));
}

void CPFlowFunction::visitBinaryOperator(BinaryOperator &BO) { 
  // join ?
  CPLatticePoint* result = new CPLatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  BinaryOperator* current = &BO;
  std::pair<Use*, Use *> operands = helper::getOperands(BO);
  Use* S1 = operands.first;
  Use* S2 = operands.second;
  ConstantInt* C1 = NULL;
  ConstantInt* C2 = NULL;

  if (isa<ConstantInt>(S1)) {
    C1 = dyn_cast<ConstantInt>(S1);
  } else if (result->representation.count(S1->get()) > 0) {
    C1 = result->representation[S1->get()];
  } else {
    C1 = ConstantInt::get(context, llvm::APInt(32, 0, true));
  }
  if (isa<ConstantInt>(S2)) {
    C2 = dyn_cast<ConstantInt>(S2->get());
  } else if (result->representation.count(S2->get()) > 0) {
    C2 = result->representation[S2->get()];
  } else {
    C2 = ConstantInt::get(context, llvm::APInt(32, 0, true));
  }
  // representation never initialized
  ret_value = new CPLatticePoint(false, false, std::map<Value*, ConstantInt*>(result->representation));
  ret_value->representation[current] = helper::foldBinaryOperator(BO.getOpcode(), C1, C2);
}

void CPFlowFunction::visitBranchInst(BranchInst &BI) {
  
  BranchInst* current = &BI;

  if (BI.isConditional()) {
    CPLatticePoint* result = new CPLatticePoint(*(info_in_casted.back()));
    info_in_casted.pop_back();
    Value* cond = BI.getCondition();
    if (isa<ICmpInst>(cond)) {
      std::pair<Use*, Use *> branches = helper::getOps(BI);
      Use* true_branch = branches.first;
      Use* false_branch = branches.second;

      ICmpInst* cmp = dyn_cast<ICmpInst>(cond);
      std::pair<Use*, Use *> operands = helper::getOps(*cmp);
      Use* rhs = operands.second;
      Use* lhs = operands.first;

      ConstantInt* rhs_const = NULL;
      ConstantInt* lhs_const = NULL;
      // get the rhs/lhs as a constant int
      if (isa<ConstantInt>(rhs)) {
        rhs_const = dyn_cast<ConstantInt>(rhs);
      } else if (result->representation.count(rhs->get()) > 0) {
        rhs_const = result->representation[rhs->get()];
      } else {
        rhs_const = ConstantInt::get(context, llvm::APInt(32, 0, true));
      } 
      if (isa<ConstantInt>(lhs)) {
        lhs_const = dyn_cast<ConstantInt>(lhs->get());
      } else if (result->representation.count(lhs->get()) > 0) {
        lhs_const = result->representation[lhs->get()];
      } else {
        lhs_const = ConstantInt::get(context, llvm::APInt(32, 0, true));
      }

      // Create successors
      CPLatticePoint* true_branchCLP = new CPLatticePoint(false, false, std::map<Value*,ConstantInt*>(result->representation));
      CPLatticePoint* false_branchCLP = new CPLatticePoint(false, false, std::map<Value*,ConstantInt*>(result->representation));

      // get the predicate
      int predicate = 0;
      predicate = cmp->isSigned() ? cmp->getSignedPredicate() : cmp->getUnsignedPredicate();
      if (predicate == CmpInst::ICMP_EQ) {
        if (result->representation.count(rhs->get()) > 0) {
           true_branchCLP->representation[rhs->get()] = lhs_const;
        } else if (result->representation.count(lhs->get()) > 0) {
           true_branchCLP->representation[lhs->get()] = rhs_const;
        }
        out_map[true_branch->get()] = true_branchCLP;
        out_map[false_branch->get()] = false_branchCLP;
      } else if (predicate == CmpInst::ICMP_NE) {
        if (result->representation.count(rhs->get()) > 0) {
           false_branchCLP->representation[rhs->get()] = lhs_const;
        } else if (result->representation.count(lhs->get()) > 0) {
           false_branchCLP->representation[lhs->get()] = rhs_const;
        }
        out_map[true_branch->get()] = true_branchCLP;
        out_map[false_branch->get()] = false_branchCLP;
      } else {
        for (std::map<Value *, LatticePoint *>::iterator it=out_map.begin(); it != out_map.end(); ++it){
          CPLatticePoint* inCLP = new CPLatticePoint(*(info_in_casted.back()));
          info_in_casted.pop_back();
          Value* elm = it->first;
          out_map[elm] = new CPLatticePoint(*inCLP);
        }
      }
    } else {
      for (std::map<Value *, LatticePoint *>::iterator it=out_map.begin(); it != out_map.end(); ++it){
        CPLatticePoint* inCLP = new CPLatticePoint(*(info_in_casted.back()));
        info_in_casted.pop_back();
        Value* elm = it->first;
        out_map[elm] = new CPLatticePoint(*inCLP);
      }
    }
  } else {
    for (std::map<Value *, LatticePoint *>::iterator it=out_map.begin(); it != out_map.end(); ++it){
        CPLatticePoint* inCLP = new CPLatticePoint(*(info_in_casted.back()));
        info_in_casted.pop_back();
        Value* elm = it->first;
        out_map[elm] = new CPLatticePoint(*inCLP);
    }
  }
}

void CPFlowFunction::visitPHINode(PHINode &PI) {
  while (info_in_casted.size() > 1) {
    LatticePoint *l1 = info_in_casted.back();
    info_in_casted.pop_back();
    LatticePoint *l2 = info_in_casted.back();
    info_in_casted.pop_back();
    CPLatticePoint* result = dyn_cast<CPLatticePoint>(l1->join(l2));
    info_in_casted.push_back(result);
  }
  CPLatticePoint* result = new CPLatticePoint(*(info_in_casted.back()));
  PHINode* current = &PI;
  int num_incoming_vals = PI.getNumIncomingValues();
  ConstantInt* resvalue = NULL;
  for (int i = 0; i != num_incoming_vals; ){
    Value* val1 = PI.getIncomingValue(i);
    i++;
    Value* val2 = PI.getIncomingValue(i);
    i++;
    ConstantInt* C1 = NULL;
    ConstantInt* C2 = NULL;
    ret_value = new CPLatticePoint(result->isBottom, result->isTop, std::map<Value*, ConstantInt*>(result->representation));

    if (result->representation.count(val1) > 0) {
      C1 = ret_value->representation[val1];
    }
    else if(isa<ConstantInt>(val1)){
      C1 = dyn_cast<ConstantInt>(val1);
    } else {
      C1 = ConstantInt::get(context, llvm::APInt(32, 0, true));
    }
    if (result->representation.count(val2) > 0) {
      C2 = ret_value->representation[val2];
    }
    else if(isa<ConstantInt>(val2)){
      C2 = dyn_cast<ConstantInt>(val2);
    } else {
      C2 = ConstantInt::get(context, llvm::APInt(32, 0, true));
    }
    // Prop the constant if equals, otherwise remove from map
    if (C1 == C2) {
      resvalue = C1;
    } else if (val1 == val2) {
      ret_value->representation.erase(val1);
    } else if (result->representation.count(val1) > 0 && result->representation.count(val2) > 0) {
      errs() << "test";
      ret_value->representation.erase(val1);
      ret_value->representation.erase(val2);
    } else if (result->representation.count(val1) > 0) {
      ret_value->representation.erase(val1);
    } else if (result->representation.count(val2) > 0) {
      ret_value->representation.erase(val2);
    } else {
      ret_value->representation.erase(val1);
      ret_value->representation.erase(val2);
    }
  }
  if (resvalue != NULL) {
    ret_value->isBottom = false;
    ret_value->isTop = false;
    ret_value->representation[current] = resvalue;
  } else {}
}

void CPFlowFunction::visitCmpInst(CmpInst &I) {
  CPLatticePoint* result = new CPLatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  ret_value = new CPLatticePoint(result->isBottom, result->isTop, std::map<Value*, ConstantInt*>(result->representation));
}

void CPFlowFunction::visitTerminatorInst(TerminatorInst &I){
  for (std::map<Value *, LatticePoint *>::iterator it=out_map.begin(); it != out_map.end(); ++it){
    CPLatticePoint* result = new CPLatticePoint(*(info_in_casted.back()));
    Value* elm = it->first;
    out_map[elm] = result;
  }
}

void CPFlowFunction::visitInstruction(Instruction &I) {
  CPLatticePoint* result = new CPLatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  ret_value = new CPLatticePoint(result->isBottom, result->isTop, std::map<Value*, ConstantInt*>(result->representation));
}
