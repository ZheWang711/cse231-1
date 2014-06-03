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
    // sample map for CSElattice point with actual content in it
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

    // std::vector<LatticePoint* > firstEval = (*CSEFlow_casted)(firstI, sampleArgs);
    // std::vector<LatticePoint* > secondEval = (*CSEFlow_native)(firstI, sampleArgs);


    // this is how we have to call the relevent flow functions when we
    // only have a FlowFunction*, not an object of the base type
    // if (CSEFlowFunction *CSEFF = dyn_cast<CSEFlowFunction>(CSEFlow_casted)) {
    //   std::vector<LatticePoint* > secondEval = (*CSEFF)(firstI, sampleArgs);
    // }


    // std::vector<LatticePoint* > secondEval = CSEf(firstI, firstEval);
		     
    // note: this snippet works to get the first non phi instruction if we need it from F
    // Instruction* firstI = F.front().getFirstNonPHI();


    // --------------------------------------------------
    // Test for instruction equivalence in LLVM, using first two
    // instructions of function.
    // --------------------------------------------------

    // 1. get first two instructions of first basicblock
    inst_iterator I = inst_begin(F);
    Instruction* firstI = &(*I);
    I++;    
    Instruction* secondI = &(*I);
    
    errs() << "First Instruction: " << firstI << " " << Instruction::getOpcodeName(firstI->getOpcode()) << ", " << firstI->getNumOperands() << " arg(s)\n";

    errs() << "Second Instruction: " << secondI << " " << Instruction::getOpcodeName(secondI->getOpcode()) << ", " << secondI->getNumOperands() << " arg(s)\n";
    

    // 2. attempt to see if they are equal

    errs() << "Instructions are " << firstI->isIdenticalToWhenDefined(secondI)  << " equal\n";
    
    errs() << " -----Ending Function Pass------ \n";
      
    return false;
  }
    
};


char CSEtest::ID = 0;
static RegisterPass<CSEtest> X("CSEtest", "CSE test Pass", false, false);
