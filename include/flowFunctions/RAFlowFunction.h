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
  std::vector<RALatticePoint *> info_in_casted;
  unsigned Count;
  RALatticePoint ret_value;
  RAFlowFunction() : Count(0), ret_value(RALatticePoint()) {}
  void visitAllocaInst(AllocaInst &AI);
  void visitBinaryOperator(BinaryOperator &BO);
  void visitStoreInst(StoreInst   &I);
  LatticePoint operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in);
  std::string getRepresentation();
  ConstantInt* foldBinaryOperator(unsigned Opcode,ConstantInt *C1, ConstantInt *C2);
};
