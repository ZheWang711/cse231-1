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
    errs() << " ----- Starting Range Checking Pass on Function " <<  F.getName() << " ------ \n";
    
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
        
        if (isa<ArrayType>(elm_type)) {
          ArrayType* arr_type = cast<ArrayType>(elm_type);
          //errs() << " number of elements is " << arr_type->getNumElements();
          int size = arr_type->getNumElements();

          
          Value* index = helper::getGEPIndex(*gep);

          if (rlp->representation.count(index) > 0) {
            APInt* max_size = new APInt(32, size);
            APInt* zero = new APInt(32, 0);
            
            ConstantRange* arr_range = new ConstantRange(*zero, *max_size);
            
            ConstantRange* index_range = rlp->representation[index];
            
            if (!arr_range->contains(*index_range)) {
              has_range_warnings = true;
              errs() << "Warning: possible out of bounds array access at line " << i;
              errs() << "\n-Instruction: ";
              gep->print(errs());
              errs() << "\n--- Valid array possitions: ";
              arr_range->print(errs());
              errs() << "\n--- Index has possible range: ";
              index_range->print(errs());
              errs() << "\n";
            }
            
          }
          else if (isa<ConstantInt>(index)){
            ConstantInt* index_value = cast<ConstantInt>(index);
            ConstantRange* index_range = new ConstantRange(index_value->getValue());
            
            APInt* max_size = new APInt(index_value->getBitWidth(), size - 1);
            APInt* zero = new APInt(index_value->getBitWidth(), 0);
            
            ConstantRange* arr_range = new ConstantRange(*zero, *max_size);
            
            if (!arr_range->contains(*index_range)) {
              has_range_warnings = true;
              errs() << "Warning: possible out of bounds array access at line " << i;
              errs() << "\n-Instruction: ";
              gep->print(errs());
              errs() << "\n--- Valid array possitions: ";
              arr_range->print(errs());
              errs() << "\n--- Index has possible range: ";
              index_range->print(errs());
              errs() << "\n";
            }
          }
        }
      }
      i++;
    }
    
    if (has_range_warnings) {
      errs() << "Done with range checking. Exited with warnings!\n\n";
    }
    else{
      errs() << "Done with range checking. Exited with no warnings.\n\n";

    }
    
    errs() << " ----- Ending Range Checking Pass on Function " <<  F.getName() << " ------ \n";
    
    return false;
  }
  
};
//}

char RangeCheckingPass::ID = 0;
static RegisterPass<RangeCheckingPass> X("RangeCheckingPass", "RangeCheckingPass Pass", false, false);
