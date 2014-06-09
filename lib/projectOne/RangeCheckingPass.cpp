#include "llvm/Pass.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/DataLayout.h"
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


struct RangeCheckingPass : public FunctionPass {
  static char ID;
  
  
  RangeCheckingPass() : FunctionPass(ID) {}
  
  // This is the main body of our code.
  virtual bool runOnFunction(Function &F){
    errs() << " -----Starting Range Function Checking Pass------ \n";
    
    Module* M = F.getParent();
    
    DataLayout* dl = M->getDataLayout();
    
    RAFlowFunction raf = RAFlowFunction();
    
    std::map<Value*, ConstantRange*> representation;
    
    /*
    errs() << "We are dealing with the following function \n";
    F.print(errs());
    errs() << "Our analysis returned the following \n";
    */
    
    RALatticePoint* bottom = new RALatticePoint(true, false, representation);
    std::map<Instruction *, LatticePoint *> result = Analysis::analyze(F, bottom, &raf);
    
    int i = 1;
    bool has_range_warnings = false;
    for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I){
      Instruction* current_instruction = &*I;
      LatticePoint* lp = result[current_instruction];
      RALatticePoint *rlp = dyn_cast<RALatticePoint>(lp);
      
      if (isa<GetElementPtrInst>(current_instruction)) {
        GetElementPtrInst* gep = cast<GetElementPtrInst>(current_instruction);
        errs() << "GEP instruction: ";
        gep->print(errs());
        errs() << " has pointer ";
        gep->getPointerOperand()->print(errs());
        AllocaInst* al = dyn_cast<AllocaInst>(gep->getPointerOperand());
        errs() << " with ";
        al->getArraySize()->print(errs());
        errs() << " elements, alignment: ";
        errs() << al->getAlignment();
        errs() << "\n";

      }
      
      /*
      I->print(errs());
      errs() << " --> ";
      rlp->printToErrs();
       */
      i++;
    }
    
    if (has_range_warnings) {
      errs() << "Done with range checking. Exited with errors!\n\n";
    }
    else{
      errs() << "Done with range checking. Exited with no errors.\n\n";

    }
    
    errs() << " -----Ending Range Function Checking Pass------ \n";
    
    return false;
  }
  
};
//}

char RangeCheckingPass::ID = 0;
static RegisterPass<RangeCheckingPass> X("RangeCheckingPass", "RangeCheckingPass Pass", false, false);
