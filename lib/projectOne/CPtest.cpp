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
#include "Analysis.h"
#include "lattices/CPLatticePoint.h"
#include "flowFunctions/CPFlowFunction.h"


using namespace llvm;
  
  struct CPtest : public FunctionPass {
    static char ID;
   
    CPtest() : FunctionPass(ID) {}
    
    // This is the main body of our code.
    virtual bool runOnFunction(Function &F){
      errs() << " -----Starting Function Pass------ \n";
      errs() << " Testing Constant Prop \n";

      errs() << " About to create CPLatticePoint \n";
      
	  LLVMContext &someContext = F.getContext();

	  std::map<Value*, ConstantInt*> lpmap;
      ConstantInt* ci = llvm::ConstantInt::get(someContext, llvm::APInt(/*nbits*/32, 10, /*bool*/true));

	  lpmap.insert(std::pair<Value*,ConstantInt*>(F.front().getInstList().front().getNextNode()->getPrevNode(), ci));

      CPLatticePoint* bottom = new CPLatticePoint(true, false, std::map<Value*, ConstantInt*>());
      /*std::vector<LatticePoint* > sampleArgs;
      sampleArgs.push_back(dyn_cast<LatticePoint>(&clp));
      errs() << " Created CPLatticePoint with address " << &clp << "\n";

	errs() << " isBottom " << clp.isBottom;

	errs() << " isTop " << clp.isTop;

*/
	ConstantInt *someConstant = llvm::ConstantInt::get(someContext, llvm::APInt(/*nbits*/32, 5, /*bool*/true));

//      	errs() << " \n Constant value is " << someConstant->getValue();

       	CPFlowFunction cpf = CPFlowFunction(F.getContext());
//	std::vector<std::vector< LatticePoint* > > lps;

        std::map<Instruction*, LatticePoint*> result = Analysis::analyze(F, bottom, &cpf);

     	for (inst_iterator I = inst_begin(F); I != inst_end(F) ; ++I){
	  // cpf.visit(*I);
	  //lps.push_back(cpf(&(*I), sampleArgs));
          LatticePoint* lp = result[&*I];
          CPLatticePoint* clp = dyn_cast<CPLatticePoint>(lp);
          errs() << clp->LPprint();
          I->print(errs());
          errs() << " --> ";
      	}

        // for(std::vector<LatticePoint*>::iterator it = lps.begin(); it != lps.end(); ++it) {
	// 		errs() << (*it)->LPprint() << "\n";
	// 	}

      	// errs() << " \n count = " << cpf.Count;
	errs() << " \n wheeeeee " ;
	errs() << " -----Ending Function Pass------ \n";
      
      return false;
    }
    
  };
//}

char CPtest::ID = 0;
static RegisterPass<CPtest> X("CPtest", "Constant Prop test Pass", false, false);
