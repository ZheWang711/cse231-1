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

    LLVMContext &someContext = F.getContext();
    
    ConstantInt *someConstant = llvm::ConstantInt::get(someContext, llvm::APInt(/*nbits*/32, 5, /*bool*/true));
    errs() << " \n Constant value is " << someConstant->getValue() << "\n";

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
    
    
    // --------------------------------------------------
    // Test that CSEFlowFunction executes the "operator() dance"
    // correctly.
    // --------------------------------------------------
    
    // 1. Create a CSELatticePoint and stick a pointer to it into a
    // vector of type LatticePoint*. This is what the worklist
    // algorithm will actually call CSEFlowFunction with.        
    
    errs() << " About to create CSELatticePoint \n";  
    CSELatticePoint cselp = CSELatticePoint();
    std::vector<LatticePoint* > sampleArgs;
    sampleArgs.push_back(dyn_cast<LatticePoint>(&cselp));

    errs() << " Created CSELatticePoint with address " << &cselp << "\n";
    errs() << " isBottom " << cselp.isBottom;
    errs() << " isTop " << cselp.isTop;

    // 2. Create an instance of CSEFlowFunction to call, casting it
    // "up" to a FlowFunction* which is what the worklist algorithm
    // will actually deal with.

    CSEFlowFunction CSEFlow_native = CSEFlowFunction();
    FlowFunction* CSEFlow_casted = dyn_cast<FlowFunction>(&CSEFlow_native);

    // 3. Now call the flow function created above. Since the lattice
    // point handed in as part of sampleArgs is empty, this should do
    // nothing but not crash.

    std::vector<LatticePoint* > firstEval = (*CSEFlow_casted)(firstI, sampleArgs);
    std::vector<LatticePoint* > secondEval = (*CSEFlow_casted)(secondI, sampleArgs);

    // NOTE: the behavior here is curious. CSEFlow_casted is a
    // FlowFunction*, but this call is correctly calling the
    // CSEFlowFunction member. This makes no sense based on previous
    // experience, but whatever.

    // 4. Now, we want to call the flow function with nontrivial
    // sample arguments that are non-empty, to verify proper behavior

    // Create a CSELatticePoint representation of, eg, the very first
    // instance of a value to instruction map.
    std::map<Value*, Instruction*> lpmap;
    lpmap.insert(std::pair<Value*, Instruction*>(firstI, firstI));
    CSELatticePoint nontrivialExampleLP = CSELatticePoint(false, false, lpmap);
    std::vector<LatticePoint* > nontrivialSampleArgs;
    nontrivialSampleArgs.push_back(dyn_cast<LatticePoint>(&cselp));
    // sample map for CSElattice point with actual content in it
    


    errs() << " -----Ending Function Pass------ \n";
    return false;
  }
    
};


char CSEtest::ID = 0;
static RegisterPass<CSEtest> X("CSEtest", "CSE test Pass", false, false);
