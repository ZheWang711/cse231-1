// it WOULD APPEAR that we can inherit from both the INTERFACE
// flowfunction, and the IMPLEMENTATION AID InstVisitor with a
// template. at least, this builds with no errors, and C++ does in
// fact allow multiple inheritance...

#include "flowFunctions/FlowFunction.h"
#include "lattices/RALatticePoint.h"
#include "llvm/IR/Value.h"
#include "helper/helper.h"
#include <string>

using namespace llvm;

class RAFlowFunction : public FlowFunction, public InstVisitor<RAFlowFunction>{
public:
  // local variables for passing arguments
  std::vector<RALatticePoint *> info_in_casted;
  RALatticePoint ret_value;

  // Constructor
  RAFlowFunction() : ret_value(RALatticePoint()) {}

  // Visited Instructions
  void visitAllocaInst(AllocaInst &AI);
  void visitBinaryOperator(BinaryOperator &BO);
  void visitStoreInst(StoreInst   &I);

  // Flow Function Interface
  std::vector<LatticePoint *> operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in);
};
