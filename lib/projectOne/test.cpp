#include "llvm/Pass.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
#include "llvm/Support/InstIterator.h"
#include "lattices/CPLatticePoint.h"
#include "lattices/RALatticePoint.h"
//#include "flowFunctions/FlowFunction.h"
#include "flowFunctions/CPFlowFunction.h"
#include <map>
#include <list>
#include <utility>
#include <stack>
#include <stdlib.h>


using namespace llvm;

//namespace {
/*
class CPFlowFunction : public FlowFunction, public InstVisitor<CPFlowFunction>{
public:
  std::vector<CPLatticePoint *> info_in_casted;
  CPLatticePoint ret_value;
  unsigned Count;
  CPFlowFunction() : Count(0) {}
//  void visitAllocaInst(AllocaInst &AI);
//  void visitBinaryOperator(BinaryOperator &BO);
//  void visitAllocaInst(AllocaInst &AI) { ++Count; }
//  LatticePoint operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in);

LatticePoint operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in){
  // dyncast on that vector;
  // this.visit(instr);
  return ret_value;
}

void visitAllocaInst(AllocaInst &AI) { ++Count; }

void visitBinaryOperator(BinaryOperator &BO) { ++Count; }
};
*/

  
  struct test : public FunctionPass {
    static char ID;
    
    
    test() : FunctionPass(ID) {}
    
    // This is the main body of our code.
    virtual bool runOnFunction(Function &F){
      errs() << " -----Starting Function Pass------ \n";
      
      errs() << " About to create CPLatticePoint \n";
      
      CPLatticePoint clp = CPLatticePoint(false, true, std::map<Value*, ConstantInt*>());
      
      errs() << " Created CPLatticePoint with address " << &clp << "\n";

	errs() << " isBottom " << clp.isBottom;

	errs() << " isTop " << clp.isTop;

	LLVMContext &someContext = F.getContext();

	ConstantInt *someConstant = llvm::ConstantInt::get(someContext, llvm::APInt(/*nbits*/32, 5, /*bool*/true));

      	errs() << " \n Constant value is " << someConstant->getValue();

       	CPFlowFunction cpf = CPFlowFunction();

//	    CountAllocaVisitor CAV;
    

     	for (inst_iterator I = inst_begin(F); I != inst_end(F) ; ++I){
     		cpf.visit(*I);
      	}

      	// errs() << " \n count = " << cpf.Count;
	errs() << " \n wheeeeee " ;
      errs() << " -----Ending Function Pass------ \n";
      
      return false;
    }
    
  };
//}

char test::ID = 0;
static RegisterPass<test> X("test", "test Pass", false, false);
