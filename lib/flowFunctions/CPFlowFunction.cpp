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
   ret_value = new CPLatticePoint(false, true, std::map<Value*, Constant*>());
}

void CPFlowFunction::visitBinaryOperator(BinaryOperator &BO) { 
  errs() << "CPflow visiting a binary operator";
}
