#include "llvm/Pass.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
#include "llvm/Support/InstIterator.h"
#include "lattices/PALatticePoint.h"
#include "flowFunctions/PAFlowFunction.h"
#include "Analysis.h"
#include <map>
#include <list>
#include <utility>
#include <stack>
#include <stdlib.h>
#include "helper/helper.h"

using namespace llvm;


struct PATest : public FunctionPass {
  static char ID;
  
  
  PATest() : FunctionPass(ID) {}
  
  // This is the main body of our code.
  virtual bool runOnFunction(Function &F){
    errs() << " -----Starting Function Pass------ \n";
    
    PAFlowFunction raf = PAFlowFunction();
    
    std::map<Value*, std::set<Value *> > representation;
    PALatticePoint* bottom = new PALatticePoint(true, false, representation);
    std::map<Instruction *, LatticePoint *> result = Analysis::analyze(F, bottom, &raf);
    
    errs() << "We are dealing with the following function \n";
    F.print(errs());
    errs() << "Our analysis returned the following \n";
    
    // F is a pointer to a Function instance
    for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I){
      LatticePoint* lp = result[&*I];
      PALatticePoint *rlp = dyn_cast<PALatticePoint>(lp);
      I->print(errs());
      errs() << " --> ";
      rlp->printToErrs();
    }
    
    errs() << " -----Ending Function Pass------ \n";
    
    return false;
  }
  
};
//}

char PATest::ID = 0;
static RegisterPass<PATest> X("PATest", "PATest Pass", false, false);
