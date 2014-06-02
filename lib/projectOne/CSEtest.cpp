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

    errs() << " \n Constant value is " << someConstant->getValue() << "\n";

    CSEFlowFunction CSEFlow_native = CSEFlowFunction();

    FlowFunction* CSEFlow_casted = dyn_cast<FlowFunction>(&CSEFlow_native);

    Instruction* firstI = F.front().getFirstNonPHI();
    
    

    errs() << "First Instruction: " << Instruction::getOpcodeName(firstI->getOpcode()) << ", " << firstI->getNumOperands() << " arg(s)\n";
    
    std::vector<LatticePoint* > firstEval = (*CSEFlow_casted)(firstI, sampleArgs);
    // std::vector<LatticePoint* > secondEval = (*CSEFlow_native)(firstI, sampleArgs);


    // this is how we have to call the relevent flow functions when we
    // only have a FlowFunction*, not an object of the base type
    if (CSEFlowFunction *CSEFF = dyn_cast<CSEFlowFunction>(CSEFlow_casted)) {
      std::vector<LatticePoint* > secondEval = (*CSEFF)(firstI, sampleArgs);
    }


    // std::vector<LatticePoint* > secondEval = CSEf(firstI, firstEval);
		     
    
    // std::vector<std::vector< LatticePoint* > > lps;
    // for (inst_iterator I = inst_begin(F); I != inst_end(F) ; ++I){
    //   lps.push_back(CSEf(&(*I), sampleArgs));
    // }

    Instruction* prev_instruction;

    // let's test the instruction identity calls to LLVM
    // for (inst_iterator IP = inst_begin(F), inst_iterator I = ++inst_begin(F); I != inst_end(F) ; ++I, ++IP){
    //   errs() << "is this pair the same" << *IP->isIdenticalToWhenDefined(*I) << "\n";
    // }


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
