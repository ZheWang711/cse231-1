// LLVM
#include "llvm/Pass.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/InstIterator.h"

// STL
#include <iostream>
#include <map>
#include <list>
#include <utility>
#include <stack>
#include <stdlib.h>

// our stuff
#include "lattices/CSELatticePoint.h"
#include "flowFunctions/CSEFlowFunction.h"


using namespace llvm;
  
struct CSEtest : public FunctionPass {
  static char ID;
   
  CSEtest() : FunctionPass(ID) {}
    
  // This is the main body of our code.
  virtual bool runOnFunction(Function &F){
    errs() << " -----Starting Function Pass------ \n";
    errs() << " Testing CSE \n";

    errs() << " About to create CSELatticePoint \n";
      
    LLVMContext &someContext = F.getContext();

    std::map<Value*, Instruction*> lpmap;
    ConstantInt* ci = llvm::ConstantInt::get(someContext, llvm::APInt(/*nbits*/32, 10, /*bool*/true));

    // lpmap.insert(std::pair<Value*, Instruction*>(F.front().getInstList().front().getNextNode()->getPrevNode(), ci));

    // CSELatticePoint cselp = CSELatticePoint(false, true, lpmap);
    CSELatticePoint cselp = CSELatticePoint();
    std::vector<LatticePoint* > sampleArgs;
    sampleArgs.push_back(dyn_cast<LatticePoint>(&cselp));

    errs() << " Created CSELatticePoint with address " << &cselp << "\n";
    errs() << " isBottom " << cselp.isBottom;
    errs() << " isTop " << cselp.isTop;


    ConstantInt *someConstant = llvm::ConstantInt::get(someContext, llvm::APInt(/*nbits*/32, 5, /*bool*/true));

    errs() << " \n Constant value is " << someConstant->getValue();

    CSEFlowFunction CSEf = CSEFlowFunction();
    std::vector<std::vector< LatticePoint* > > lps;

    for (inst_iterator I = inst_begin(F); I != inst_end(F) ; ++I){
      // CSEf.visit(*I);
      lps.push_back(CSEf(&(*I), sampleArgs));
    }

    // for(std::vector<LatticePoint*>::iterator it = lps.begin(); it != lps.end(); ++it) {
    // 		errs() << (*it)->LPprint() << "\n";
    // 	}

    // errs() << " \n count = " << CSEf.Count;
    errs() << " \n wheeeeee " ;
    errs() << " -----Ending Function Pass------ \n";
      
    return false;
  }
    
};


char CSEtest::ID = 0;
static RegisterPass<CSEtest> X("CSEtest", "CSE test Pass", false, false);
