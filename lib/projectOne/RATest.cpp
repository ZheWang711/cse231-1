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
#include "helper/helper.h"

using namespace llvm;


struct RATest : public FunctionPass {
  static char ID;
  
  
  RATest() : FunctionPass(ID) {}
  
  // This is the main body of our code.
  virtual bool runOnFunction(Function &F){
    errs() << " -----Starting Function Pass------ \n";
    
    /*
     ConstantRange c1 = ConstantRange(APInt(32, 0), APInt(32, 2) );
     ConstantRange c2 = ConstantRange(APInt(32, 0), APInt(32, 2) );
     errs() << "Adding constant ranges ";
     c1.print(errs());
     errs() << " + a few times ";
     c2.print(errs());
     errs() << " = ";
     for (int i = 0; i < 100; i++) {
     c2 = c1.add(c2);
     }
     c2.print(errs());
     errs() << "\n";
     ConstantRange c3 = ConstantRange(APInt(32, 1000), APInt(32, 1002) );
     errs() << "Unioning constant ranges ";
     c1.print(errs());
     errs() << " and ";
     c3.print(errs());
     errs() << " = ";
     ConstantRange c4 = c3.unionWith(c1);
     c4.print(errs());
     errs() << "\n";
     */
    
    
    RAFlowFunction raf = RAFlowFunction();
    
    std::map<Value*, ConstantRange*> representation;

    errs() << "We are dealing with the following function \n";
    F.print(errs());
    errs() << "Our analysis returned the following \n";
    
    RALatticePoint* bottom = new RALatticePoint(true, false, representation);
    std::map<Instruction *, LatticePoint *> result = Analysis::analyze(F, bottom, &raf);
    
    
    // F is a pointer to a Function instance
    for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I){
      LatticePoint* lp = result[&*I];
      RALatticePoint *rlp = dyn_cast<RALatticePoint>(lp);
      I->print(errs());
      errs() << " --> ";
      rlp->printToErrs();
    }
    
    errs() << " -----Ending Function Pass------ \n";
    
    return false;
  }
  
};
//}

char RATest::ID = 0;
static RegisterPass<RATest> X("RATest", "RATest Pass", false, false);
