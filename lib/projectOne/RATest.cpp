#include "llvm/Pass.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
#include "llvm/Support/InstIterator.h"
#include "lattices/RALatticePoint.h"
#include "flowFunctions/RAFlowFunction.h"
#include "Analysis.h"
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
    
    RAFlowFunction raf = RAFlowFunction();
    
    std::map<Value*, ConstantRange*> representation;
    RALatticePoint* bottom = new RALatticePoint(true, false, representation);
    std::map<Instruction *, LatticePoint *> result = Analysis::analyze(F, bottom, &raf);
    
    for (std::map<Instruction *, LatticePoint *>::iterator it = result.begin(); it != result.end(); ++it){
      Instruction* I = it->first;
      if (isa<RALatticePoint>(it->second)) {
        RALatticePoint *rlp = dyn_cast<RALatticePoint>(it->second);
        errs() << "Instruction " << I << " --> ";
        rlp->printToErrs();
      }
      else{
        errs() << "Instruction " << I << " missing RAlattice point. Is it a LatticePoint? " << isa<LatticePoint>(it->second) << "\n";
      }
      
      
    }
    
    errs() << " -----Ending Function Pass------ \n";
    
    return false;
  }
  
};
//}

char RATest::ID = 0;
static RegisterPass<RATest> X("RATest", "RATest Pass", false, false);
