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
#include <map>

using namespace llvm;

class RAFlowFunction : public FlowFunction, public InstVisitor<RAFlowFunction>{
public:
  // local variables for passing arguments
  std::vector<RALatticePoint *> info_in_casted;
  std::vector<LatticePoint *> info_out;
  std::map<Value *, LatticePoint *> out_map;
  
  // Keeps track of how many times we have changed the range of a value
  std::map<Value *, int> counter_map;
  int MAX_COUNT;
  
  // Constructor
  RAFlowFunction() : FlowFunction(FFK_RAFlowFunction), MAX_COUNT(1000) {}

  // Visited Instructions
  void visitBinaryOperator(BinaryOperator &BO);
  void visitBranchInst(BranchInst&I);
  void visitInstruction(Instruction &I);
  void visitCastInst(CastInst &I);
  void visitCmpInst(CmpInst &I);
  void visitTerminatorInst(TerminatorInst &I);
  void visitUnaryInstruction(UnaryInstruction &I);
  void visitPHINode(PHINode &PHI);
  
  
  void visitAllocaInst(AllocaInst &AI);
  void visitLoadInst(LoadInst     &LI);
  void visitStoreInst(StoreInst   &SI);
  
  
  
  // Flow Function Interface(s)
  std::vector<LatticePoint *> operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in);
  
  /*  
   Specifically for terminator instructions.
   Input: current instruction, the current set of lattice points, a map from successors --> NULL pointers
   Output: a map of successors -> LatticePoints.
  */
  std::map<Value *, LatticePoint *> operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in, std::map<Value *, LatticePoint *> successor_map);

  static bool classof(const FlowFunction *F) {
    return F->getKind() == FFK_RAFlowFunction;
  }
};

#endif /* RAFLOWFUNCTION_H_ */
