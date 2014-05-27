#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
// Include the Instruction Iterator for Functions.
#include "llvm/Support/InstIterator.h"
#include <map>
#include "llvm/IR/Value.h"
using namespace llvm;

namespace {
  
  struct CountStaticInstructions : public ModulePass {
    static char ID;

    std::map<int, int> instructionCount; // maps instructions to the number of times they occur.
    
    CountStaticInstructions() : ModulePass(ID) {}
    
    // This is the main body of our code.
    virtual bool runOnModule(Module &M){
      for (Module::iterator MI = M.begin(), ME = M.end(); MI != ME; ++MI){
        // MI is an iterator over functions in the program.
        for (inst_iterator I = inst_begin(MI), E = inst_end(MI); I != E; ++I){
          // I is an iterator over instructions in the function.

	  errs() << "Instruction: " << Instruction::getOpcodeName(I->getOpcode()) << ", " << I->getNumOperands() << " args: ";
	  
	  for (User::op_iterator OP = I->op_begin(), OPE = I->op_end(); OP != OPE; ++OP){
	    // this garbage printed out is the memory address of the
	    // Value object that is this operand to the current
	    // instruction.
	    OP->get()->getType()->print(errs());
	    errs() << " " << OP->get() << ", ";
	  }
	  errs() << "\n";
	  
          // We map each instruction's opcode to the number of times it occurs.
          int inst = I->getOpcode();
          if (instructionCount.count(inst) > 0){
            instructionCount[inst] = instructionCount[inst] + 1;
          }
          else{
            instructionCount[inst] = 1;
          }
        }
      }
      
      

      return false;
    }
    
    // Override print method to output.
    virtual void print(llvm::raw_ostream &O, const Module *M) const {
      // We loop over elements of the map and print out the number of times they occured.
      // Because of various inheritance issues, it is a const_iterator.
      int total = 0;
      for (std::map<int, int>::const_iterator it=instructionCount.begin(); it!=instructionCount.end(); ++it){
        O << Instruction::getOpcodeName(it->first) << " " << it->second << "\n";
        total += it->second;
     } 
      O << "TOTAL " << total << "\n";
    }

  };
}
char CountStaticInstructions::ID = 0;
static RegisterPass<CountStaticInstructions> X("CountStaticInstructions", "CountStaticInstructions Pass", false, false);
