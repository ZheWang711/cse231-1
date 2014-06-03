#ifndef RAFLOWFUNCTION_H_
#define RAFLOWFUNCTION_H_

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
  std::vector<LatticePoint *> info_out;

  // Constructor
  RAFlowFunction() : FlowFunction(FFK_RAFlowFunction) {}

  // Visited Instructions
  void visitBinaryOperator(BinaryOperator &BO);

  // Flow Function Interface
  std::vector<LatticePoint *> operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in);

  static bool classof(const FlowFunction *F) {
    return F->getKind() == FFK_RAFlowFunction;
  }
};

#endif /* RAFLOWFUNCTION_H_ */
