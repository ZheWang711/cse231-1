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
    
    //Module* M = F.getParent();
    
    //DataLayout* dl = M->getDataLayout();
    
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
      RALatticePoint* rlp = dyn_cast<RALatticePoint>(lp);
      
      if (isa<GetElementPtrInst>(current_instruction)) {
        GetElementPtrInst* gep = cast<GetElementPtrInst>(current_instruction);
        Type* pt = gep->getPointerOperandType();
        PointerType* pointer_type = dyn_cast<PointerType>(pt);
        
        Type* elm_type = pointer_type->getElementType();
        
        errs() << "GEP instruction: ";
        gep->print(errs());
        errs() << "\n";
        
        
        
        if (isa<ArrayType>(elm_type)) {
          ArrayType* arr_type = cast<ArrayType>(elm_type);
          //errs() << " number of elements is " << arr_type->getNumElements();
          int size = arr_type->getNumElements();
          APInt* max_size = new APInt(32, size - 1);
          APInt* zero = new APInt(32, 0);
          
          ConstantRange* arr_range = new ConstantRange(*zero, *max_size);
          
          Value* index = helper::getGEPIndex(*gep);

          if (rlp->representation.count(index) > 0) {
            ConstantRange* index_range = rlp->representation[index];
            errs() << "Array range: ";
            arr_range->print(errs());
            errs() << " index range: ";
            index_range->print(errs());
            errs() << "\n";
            errs() << "Array range contains index range? " <<arr_range->contains(*index_range) << "\n";
            
          }
          else if (isa<ConstantInt>(index)){
            ConstantInt* index_value = cast<ConstantInt>(index);
            ConstantRange* index_range = new ConstantRange(index_value->getValue());
            errs() << "Array range: ";
            arr_range->print(errs());
            errs() << " index range: ";
            index_range->print(errs());
            errs() << "\n";
            errs() << "Array range contains index range? " <<arr_range->contains(*index_range) << "\n";
          }

          
        }
        //errs() << "\n";

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
