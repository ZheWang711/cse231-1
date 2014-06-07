#ifndef PAFLOWFUNCTION_H_
#define PAFLOWFUNCTION_H_

#include "flowFunctions/FlowFunction.h"
#include "lattices/PALatticePoint.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Value.h"
#include "helper/helper.h"
#include <string>
#include <map>

using namespace llvm;

class PAFlowFunction : public FlowFunction, public InstVisitor<PAFlowFunction>{
public:
  // local variables for passing arguments
  std::vector<PALatticePoint *> info_in_casted;
  std::vector<LatticePoint *> info_out;
  std::map<Value *, LatticePoint *> out_map;
  
  // Constructor
  PAFlowFunction() : FlowFunction(FFK_PAFlowFunction) {}
  
  // Visited Instructions
  void visitBinaryOperator(BinaryOperator &BO);
  void visitBranchInst(BranchInst&I);
  void visitInstruction(Instruction &I);
  void visitCastInst(CastInst &I);
  void visitCmpInst(CmpInst &I);
  void visitTerminatorInst(TerminatorInst &I);
  void visitUnaryInstruction(UnaryInstruction &I);
  void visitPHINode(PHINode &PHI);
  
  // These are especially important for pointer analysis
  void visitAllocaInst(AllocaInst &AI);
  void visitLoadInst(LoadInst     &LI);
  void visitStoreInst(StoreInst   &SI);
  
  // Flow Function Interface(s)
  std::vector<LatticePoint *> operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in);
  
  static bool classof(const FlowFunction *F) {
    return F->getKind() == FFK_PAFlowFunction;
  }
};

#endif /* PAFLOWFUNCTION_H_ */
