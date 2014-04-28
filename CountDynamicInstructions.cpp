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
  
	// Get me a pointerType to char*
	// PointerType* ConstCharPtrTy = PointerType::get(IntegerType::get(M.getContext(), 8), 0);
	// ConstCharPtrTy2_args.push_back(ConstCharPtrTy);

  
	// Function definition for void function (const char*)
	// Mangled Name of instrumentation function: _Z17countInstExecutedi
	std::vector<Type*> ConstCharPtrTy2_args;

	ConstCharPtrTy2_args.push_back(IntegerType::get(M.getContext(), 32));


	FunctionType* FuncTy2 = FunctionType::get(
						  /*Result=*/Type::getVoidTy(M.getContext()),
						  /*Params=*/ConstCharPtrTy2_args,
						  /*isVarArg=*/false);
	Constant* c2 = M.getOrInsertFunction("_Z17countInstExecutedi", FuncTy2);
	Function* countInstFunc = dyn_cast<Function>(c2);
  
	// Create the IRBuilder
	IRBuilder<> builder(M.getContext());
	// bool printed = false;


	for (Module::iterator MI = M.begin(), ME = M.end(); MI != ME; ++MI){
	  // MI is an iterator over functions in the program.
	  for (inst_iterator I = inst_begin(MI), E = inst_end(MI); I != E; ++I){

	    // I is an iterator over instructions in the function.

	    // // Create a const char[] for the instruction name
	    // Constant *data_arr = ConstantDataArray::getString(M.getContext(), MI->getName(), true);
	    // GlobalVariable* global_arr = new GlobalVariable(/*Module=*/M,
	    // 						    /*Type=*/data_arr->getType(),
	    // 						    /*isConstant=*/true,
	    // 						    /*Linkage=*/GlobalValue::InternalLinkage,
	    // 						    /*Initializer=*/data_arr, // has initializer, specified below
	    // 						    /*Name=*/I->getName());
	    // global_arr->setAlignment(16);
	    
	    // // create a pointer to the global array
	    // ConstantInt* arr_int = ConstantInt::get(M.getContext(),
	    // 					    APInt(32, StringRef("0"), 10));
	    // std::vector<Constant*> arr_indices;
	    // arr_indices.push_back(arr_int);
	    // arr_indices.push_back(arr_int);
	    // Constant *arr_ptr = ConstantExpr::getGetElementPtr(global_arr,
	    // 						       arr_indices);

	    // ConstantInt::get(context, llvm::APInt(/*nbits*/32, value, /*bool*/is_signed));

	    // get the instruction opcode 
	    int instOpcode = I->getOpcode();
	    Value *OpcodeValue = ConstantInt::get(Type::getInt32Ty(M.getContext()), instOpcode);       

	    // std::vector<Value*> args1;
	    // args1.push_back(OpcodeValue);

	    builder.SetInsertPoint(&*I);
	    builder.CreateCall(countInstFunc, OpcodeValue);
	  }
	
      }
    

      return false;
    }
  };
}
char CountDynamicInstructions::ID = 0;
static RegisterPass<CountDynamicInstructions> X("CountDynamicInstructions", "CountDynamicInstructions Pass", false, false);
