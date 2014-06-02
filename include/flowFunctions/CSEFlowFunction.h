// it WOULD APPEAR that we can inherit from both the INTERFACE
// flowfunction, and the IMPLEMENTATION AID InstVisitor with a
// template. at least, this builds with no errors, and C++ does in
// fact allow multiple inheritance...

#include "flowFunctions/FlowFunction.h"
#include "lattices/CSELatticePoint.h"

using namespace llvm;

class CSEFlowFunction : public FlowFunction, public InstVisitor<CSEFlowFunction>{
public:
  // local variables for passing arguments
  std::vector<CSELatticePoint *> info_in_casted;
  CSELatticePoint* ret_value;

  // Constructor
  CSEFlowFunction() : FlowFunction(FFK_CSEFlowFunction) {}
  // Visited Instructions
  void visitAllocaInst(AllocaInst &AI);
  void visitBinaryOperator(BinaryOperator &BO);

  // Flow Function Interface
  std::vector<LatticePoint *> operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in);

  static bool classof(const FlowFunction *F) {
    return F->getKind() == FFK_CSEFlowFunction;
  }
};

