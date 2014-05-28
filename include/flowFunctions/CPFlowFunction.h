// it WOULD APPEAR that we can inherit from both the INTERFACE
// flowfunction, and the IMPLEMENTATION AID InstVisitor with a
// template. at least, this builds with no errors, and C++ does in
// fact allow multiple inheritance...

#include "flowFunctions/FlowFunction.h"


class CPFlowFunction : public FlowFunction, public InstVisitor<CPFlowFunction>{
public:
  unsigned Count;
  CPFlowFunction() : Count(0) {}
  
  void visitAllocaInst(AllocaInst &AI) { ++Count; }
  LatticePoint operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in);
};