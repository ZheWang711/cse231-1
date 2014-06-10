#include "flowFunctions/CPFlowFunction.h"

std::vector<LatticePoint *> CPFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){
  // first, ensure that info_in_casted is empty
  errs() << "afsslfj\n";
  info_in_casted = std::vector<CPLatticePoint *>();
  
  for(std::vector<LatticePoint *>::iterator it = info_in.begin(); it != info_in.end(); ++it) {
    errs() << info_in.size() << " inside loop\n";
    CPLatticePoint *in_lattice_point = dyn_cast<CPLatticePoint>(*it);
    errs() << "in if\n";
    info_in_casted.push_back(in_lattice_point);
  }
  errs() << "before visit\n";
  visit(instr);
  errs() << "returned from visiting\n";
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

void CPFlowFunction::visitAllocaInst(AllocaInst &AI) {
  errs() << "Calling alloca visitor";
  CPLatticePoint* result = new CPLatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();

  // ++Count; 
  // just stick bottom in the ret_value every time we hit an alloca (testing)
   ret_value = new CPLatticePoint(result->isBottom, result->isTop, std::map<Value*, ConstantInt*>(result->representation));
}

void CPFlowFunction::visitBinaryOperator(BinaryOperator &BO) { 
  errs() << "\nCPflow visiting a binary operator\n";
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
    errs() << "S1 isa ConstantInt\n";
  } else if (result->representation.count(S1->get()) > 0) {
    C1 = result->representation[S1->get()];
  }
  if (isa<ConstantInt>(S2)) {
    C2 = dyn_cast<ConstantInt>(S2->get());
    errs() << "S2 isa ConstantInt\n";
  } else if (result->representation.count(S2->get()) > 0) {
    C2 = result->representation[S2->get()];
  }
  // representation never initialized
  ret_value = new CPLatticePoint(false, false, std::map<Value*, ConstantInt*>(result->representation));
  ret_value->representation[current] = helper::foldBinaryOperator(BO.getOpcode(), C1, C2);
}

void CPFlowFunction::visitLoadInst(LoadInst &LI) {
  errs() << "\nCPflow visiting a load\n";

}

void CPFlowFunction::visitStoreInst(StoreInst &SI) {
  errs() << "\nCPflow visiting a store\n";

}

void CPFlowFunction::visitBranchInst(BranchInst &BI) {
  errs() << "\nCPflow visiting a branch\n";
  CPLatticePoint* result = new CPLatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  BranchInst* current = &BI;

  if (BI.isConditional()) {
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
        errs() << "rhs isa ConstantInt\n";
      } else if (result->representation.count(rhs->get()) > 0) {
        rhs_const = result->representation[rhs->get()];
      }
      if (isa<ConstantInt>(lhs)) {
        lhs_const = dyn_cast<ConstantInt>(lhs->get());
        errs() << "lhs isa ConstantInt\n";
      } else if (result->representation.count(lhs->get()) > 0) {
        lhs_const = result->representation[lhs->get()];
      }

      // get predicate
      errs() << "ops: " << rhs->get() << " " << lhs->get();

    }
  } else {
    errs() << "unconditional\n";
  }
}

void CPFlowFunction::visitPHINode(PHINode &PI) {
  errs() << "\nCPflow visiting a phi\n";

}

void CPFlowFunction::visitCmpInst(CmpInst &I) {
  errs() << "\nCPflow visiting a cmp\n";
  CPLatticePoint* result = new CPLatticePoint(*(info_in_casted.back()));
  info_in_casted.pop_back();
  ret_value = new CPLatticePoint(false, false, std::map<Value*, ConstantInt*>(result->representation));

}
