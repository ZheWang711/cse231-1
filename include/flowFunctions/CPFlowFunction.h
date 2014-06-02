#ifndef CPFLOWFUNCTION_H_
#define CPFLOWFUNCTION_H_

// it WOULD APPEAR that we can inherit from both the INTERFACE
// flowfunction, and the IMPLEMENTATION AID InstVisitor with a
// template. at least, this builds with no errors, and C++ does in
// fact allow multiple inheritance...

#include "flowFunctions/FlowFunction.h"
#include "lattices/CPLatticePoint.h"

using namespace llvm;

class CPFlowFunction : public FlowFunction, public InstVisitor<CPFlowFunction>{
public:
  // local variables for passing arguments
  std::vector<CPLatticePoint *> info_in_casted;
  CPLatticePoint* ret_value;

  // Constructor
  CPFlowFunction() : FlowFunction(FFK_CPFlowFunction) {}


  // Visited Instructions
  void visitAllocaInst(AllocaInst &AI);
  void visitBinaryOperator(BinaryOperator &BO);

  // Flow Function Interface
  std::vector<LatticePoint *> operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in);

  static bool classof(const FlowFunction *F) {
    return F->getKind() == FFK_CPFlowFunction;
  }

};

