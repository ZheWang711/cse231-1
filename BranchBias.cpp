#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
// Include the Instruction Iterator for Functions.
#include "llvm/Support/InstIterator.h"
#include <map>

using namespace llvm;

namespace {

struct BranchBias: public ModulePass {
  static char ID;

  std::map<int, int> instructionCount; // maps instructions to the number of times they occur.

  BranchBias() :
      ModulePass(ID) {
  }

  // This is the main body of our code.
  virtual bool runOnModule(Module &M) {
    errs() << "BEGIN!\n";
    for (Module::iterator MI = M.begin(), ME = M.end(); MI != ME; ++MI) {
      // MI is an iterator over functions in the program.
      errs() << "MI getname: " << MI->getName().str() << "\n";
      for (Function::iterator BI = MI->begin(), BE = MI->end(); BI != BE; ++BI) {
        // BI is an iterator over basic blocks in the function.

        // Each basic block ends with a terminator; a terminator can be a branch
        BranchInst* BR = dyn_cast<BranchInst>(BI->getTerminator());
        errs() << "terminator: " << BR << "\n";
        // Make sure it's a conditional branch
        if (BR == NULL || !BR->isConditional()) {
          errs() << "Not conditional br: " << "\n";
          continue;
        }

        errs() << BR->getName().str() << "\n";
        // insert the module call

        // for insert, first need to set insert point
      }
    }

    return false;
  }

  // Override print method to output.
  virtual void print(llvm::raw_ostream &O, const Module *M) const {
    // We loop over elements of the map and print out the number of times they occured.
    // Because of various inheritance issues, it is a const_iterator.
    for (std::map<int, int>::const_iterator it = instructionCount.begin();
        it != instructionCount.end(); ++it) {
      O << Instruction::getOpcodeName(it->first) << " " << it->second << "\n";
    }
  }

};
}
char BranchBias::ID = 0;
static RegisterPass<BranchBias> X("BranchBias", "BranchBias Pass", false,
    false);
