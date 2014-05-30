// it WOULD APPEAR that we can inherit from both the INTERFACE
// flowfunction, and the IMPLEMENTATION AID InstVisitor with a
// template. at least, this builds with no errors, and C++ does in
// fact allow multiple inheritance...

#include "flowFunctions/FlowFunction.h"
#include "lattices/RALatticePoint.h"

using namespace llvm;

class RAFlowFunction : public FlowFunction, public InstVisitor<RAFlowFunction>{
public:
  std::vector<RALatticePoint *> info_in_casted;
  RALatticePoint ret_value;
  unsigned Count;
  RAFlowFunction() : Count(0) {}
  void visitAllocaInst(AllocaInst &AI);
  void visitBinaryOperator(BinaryOperator &BO);
  /* void visitAllocaInst(AllocaInst &AI) { ++Count; } */
  LatticePoint operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in);
};
