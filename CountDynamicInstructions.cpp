#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
// Include the Instruction Iterator for Functions.
#include "llvm/Support/InstIterator.h"
#include <map>

using namespace llvm;

namespace {

  struct CountDynamicInstructions: public ModulePass {
    static char ID;
    
    CountDynamicInstructions() : ModulePass(ID) {}
    
    // This is the main body of our code.
    virtual bool runOnModule(Module &M) {
    
	// Function definition for void countInstExecuted(int)
	// Mangled Name of instrumentation function: _Z17countInstExecutedi
	std::vector<Type*> ConstCharPtrTy2_args;

	ConstCharPtrTy2_args.push_back(IntegerType::get(M.getContext(), 32));

	FunctionType* FuncTy2 = FunctionType::get(
						  /*Result=*/Type::getVoidTy(M.getContext()),
						  /*Params=*/ConstCharPtrTy2_args,
						  /*isVarArg=*/false);
	Constant* c2 = M.getOrInsertFunction("_Z17countInstExecutedi", FuncTy2);
	Function* countInstFunc = dyn_cast<Function>(c2);
  
	// Function definition for void printEverything()
	// Mangled Name of instrumentation function: _Z15printEverythingv
	std::vector<Type*> VoidTy_args;
	FunctionType* VoidTy = FunctionType::get(
						 /*Result=*/Type::getVoidTy(M.getContext()),
						 /*Params=*/VoidTy_args,
						 /*isVarArg=*/false);
	Constant* c3 = M.getOrInsertFunction("_Z15printEverythingv", VoidTy);
	Function* printFunc = dyn_cast<Function>(c3);
	

	// Create the IRBuilder
	IRBuilder<> builder(M.getContext());
	bool printed = false;
    
	for (Module::iterator MI = M.begin(), ME = M.end(); MI != ME; ++MI){
	  // MI is an iterator over functions in the program.
	  for (inst_iterator I = inst_begin(MI), E = inst_end(MI); I != E; ++I){

	    // I is an iterator over instructions in the function.

	    // get the instruction opcode 
	    int instOpcode = I->getOpcode();
	    // get a ConstantInt with the opcode value
	    Value *OpcodeValue = ConstantInt::get(Type::getInt32Ty(M.getContext()), instOpcode);       

	    builder.SetInsertPoint(&*I);
	    builder.CreateCall(countInstFunc, OpcodeValue);
	  }
	  if (MI->getName() == "main") {
	    // This is a little hacky -- only the getPrevNode() and getNextNode() methods
	    // return the correct type. Fix this if you can.
	    builder.SetInsertPoint(MI->back().getInstList().back().getPrevNode()->getNextNode());
	    builder.CreateCall(printFunc);
	    // printed = true; // only call once	  	  
	  }
	}
	return false;
    }
  };
}
char CountDynamicInstructions::ID = 0;
static RegisterPass<CountDynamicInstructions> X("CountDynamicInstructions", "CountDynamicInstructions Pass", false, false);
