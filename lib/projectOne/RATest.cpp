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
#include "flowFunctions/RAFlowFunction.h"
#include <map>
#include <list>
#include <utility>
#include <stack>
#include <stdlib.h>


using namespace llvm;


struct RATest : public FunctionPass {
  static char ID;
  
  
  RATest() : FunctionPass(ID) {}
  
  // This is the main body of our code.
  virtual bool runOnFunction(Function &F){
    errs() << " -----Starting Function Pass------ \n";
    
    errs() << " About to create RALatticePoint \n";
    
    RALatticePoint rlp = RALatticePoint();
    
    errs() << " Created CPLatticePoint with address " << &rlp << "\n";
    
    errs() << " isBottom " << rlp.isBottom << "\n";
    
    errs() << " isTop " << rlp.isTop << "\n";
    
    LLVMContext &someContext = F.getContext();
    
    ConstantInt *someConstant = llvm::ConstantInt::get(someContext, llvm::APInt(/*nbits*/32, 5, /*bool*/true));
    
    errs() << " \n Constant value is " << someConstant->getValue();
    
    RAFlowFunction raf = RAFlowFunction();
    
    
    for (inst_iterator I = inst_begin(F); I != inst_end(F) ; ++I){
      raf.visit(*I);
      errs() << " Value is : " << *(raf.value) << " \n";
      errs() << " Pointer is : " << *(raf.pointer) << " \n ";
    }
    
    errs() << " \n count = " << raf.Count;
    errs() << " -----Ending Function Pass------ \n";
    
    return false;
  }
  
};
//}

char RATest::ID = 0;
static RegisterPass<RATest> X("RATest", "RATest Pass", false, false);
