#include "llvm/Pass.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
#include "llvm/Support/InstIterator.h"
#include "lattices/CPLatticePoint.h"
#include "lattices/RALatticePoint.h"
#include "flowFunctions/CPFlowFunction.h"
#include <map>
#include <list>
#include <utility>
#include <stack>
#include <stdlib.h>


using namespace llvm;

namespace {
  
  struct test : public FunctionPass {
    static char ID;
    
    
    test() : FunctionPass(ID) {}
    
    // This is the main body of our code.
    virtual bool runOnFunction(Function &F){
      errs() << " -----Starting Function Pass------ \n";
      
      errs() << " About to create CPLatticePoint \n";
      
      CPLatticePoint clp = CPLatticePoint(false, false, std::map<Value*, Constant*>());
      
      errs() << " Created CPLatticePoint with address " << &clp << "\n";
      
      errs() << " -----Ending Function Pass------ \n";
      
      return false;
    }
    
  };
}

char test::ID = 0;
static RegisterPass<test> X("test", "test Pass", false, false);
