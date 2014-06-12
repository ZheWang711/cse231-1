#ifndef CPFLOWFUNCTION_H_
#define CPFLOWFUNCTION_H_

// it WOULD APPEAR that we can inherit from both the INTERFACE
// flowfunction, and the IMPLEMENTATION AID InstVisitor with a
// template. at least, this builds with no errors, and C++ does in
// fact allow multiple inheritance...

#include "flowFunctions/FlowFunction.h"
#include "lattices/CPLatticePoint.h"
#include "llvm/IR/InstrTypes.h"
#include "helper/helper.h"
#include <map>

using namespace llvm;

class CPFlowFunction : public FlowFunction, public InstVisitor<CPFlowFunction>{
public:
  // local variables for passing arguments
  std::vector<CPLatticePoint *> info_in_casted;
  CPLatticePoint* ret_value = NULL;
  std::map<Value *, LatticePoint *> out_map;
  LLVMContext& context;

  // Constructor
  CPFlowFunction(LLVMContext& c) : FlowFunction(FFK_CPFlowFunction), context(c) {}

  // Visited Instructions
  void visitAllocaInst(AllocaInst &AI);
  void visitBinaryOperator(BinaryOperator &BO);
  void visitBranchInst(BranchInst &BI);
  void visitPHINode(PHINode &PI);
  void visitCmpInst(CmpInst &I);
  void visitTerminatorInst(TerminatorInst &I);
  void visitInstruction(Instruction &I);

  // Flow Function Interface
  std::vector<LatticePoint *> operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in);
  std::map<Value *, LatticePoint *> operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in, std::map<Value *, LatticePoint *> successor_map);

  static bool classof(const FlowFunction *F) {
    return F->getKind() == FFK_CPFlowFunction;
  }

};

#endif /* CPFLOWFUNCTION_H_ */
