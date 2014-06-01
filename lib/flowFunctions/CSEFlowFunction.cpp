#include "flowFunctions/CSEFlowFunction.h"

std::vector<LatticePoint *> CSEFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){
  // first, ensure that info_in_casted is empty
  info_in_casted = std::vector<CSELatticePoint *>();
  
  for(std::vector<LatticePoint *>::iterator it = info_in.begin(); it != info_in.end(); ++it) {
    if (CSELatticePoint *in_lattice_point = dyn_cast<CSELatticePoint>(*it)) {
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

void CSEFlowFunction::visitAllocaInst(AllocaInst &AI) {
  errs() << "CSEflow visiting an alloca";
  // ++Count; 
  // just stick bottom in the ret_value every time we hit an alloca (testing)
   ret_value = new CSELatticePoint(false, true, std::map<Value*, Instruction*>());
}

void CSEFlowFunction::visitBinaryOperator(BinaryOperator &BO) { 
  errs() << "CSEflow visiting a binary operator";
}
