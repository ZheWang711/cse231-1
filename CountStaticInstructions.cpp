#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
// Include the Instruction Iterator for Functions.
#include "llvm/Support/InstIterator.h"
#include <map>

using namespace llvm;

namespace {
  
  struct CountStaticInstructions : public ModulePass {
    static char ID;
    CountStaticInstructions() : ModulePass(ID) {}
    
    
    // This is the main body of our code.
    virtual bool runOnModule(Module &M){
      std::map<int, int> instructionCount;
      
      for (Module::iterator MI = M.begin(), ME = M.end(); MI != ME; ++MI){
        // MI is an iterator over functions in the program.
        for (inst_iterator I = inst_begin(MI), E = inst_end(MI); I != E; ++I){
          // I is an iterator over instructions in the function.
          
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
      
      
      // Now we loop over elements of the map and print out the number of times they occured.
      for (std::map<int, int>::iterator it=instructionCount.begin(); it!=instructionCount.end(); ++it){
        errs() << Instruction::getOpcodeName(it->first) << " " << it->second << "\n";
      }
      return false;
    }

  };
}
char CountStaticInstructions::ID = 0;
static RegisterPass<CountStaticInstructions> X("CountStaticInstructions", "CountStaticInstructions Pass", false, false);
