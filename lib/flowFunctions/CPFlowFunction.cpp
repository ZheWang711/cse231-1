#include "flowFunctions/CPFlowFunction.h"

std::vector<LatticePoint *> CPFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){
  // first, ensure that info_in_casted is empty
  info_in_casted = std::vector<CPLatticePoint *>();
  
  for(std::vector<LatticePoint *>::iterator it = info_in.begin(); it != info_in.end(); ++it) {
    if (CPLatticePoint *in_lattice_point = dyn_cast<CPLatticePoint>(*it)) {
      info_in_casted.push_back(in_lattice_point);
    }
    else{ 
      errs() << "SERIOUS RUNTIME TYPE ERROR, PASSED WRONG THING TO OPERATOR \n";
    }
  }
  visit(instr);
  errs() << "returned from visiting\n";
  LatticePoint* lp = dyn_cast<LatticePoint>(ret_value);
  
  std::vector<LatticePoint*> info_out;
  info_out.push_back(lp);
  return info_out;
}

void CPFlowFunction::visitAllocaInst(AllocaInst &AI) {
  errs() << "Calling alloca visitor";
  // ++Count; 
  // just stick bottom in the ret_value every time we hit an alloca (testing)
   ret_value = new CPLatticePoint(false, true, std::map<Value*, ConstantInt*>());
}

void CPFlowFunction::visitBinaryOperator(BinaryOperator &BO) { 
  errs() << "CPflow visiting a binary operator";
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
  }

  if (isa<ConstantInt>(S2)) {
    C2 = dyn_cast<ConstantInt>(S2->get());
  } else if (result->representation.count(S2->get()) > 0) {
    C2 = result->representation[S2->get()];
  }
  ret_value->representation[current] = helper::foldBinaryOperator(BO.getOpcode(), C1, C2);
}
