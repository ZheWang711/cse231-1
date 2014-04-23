#include "llvm/Pass.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
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

  BranchBias() :
      ModulePass(ID) {
  }

  // This is the main body of our code.
  virtual bool runOnModule(Module &M) {
    // Function definition for void function (const char*, bool)
    PointerType* ConstCharPtrTy = PointerType::get(
        IntegerType::get(M.getContext(), 8), 0);
    std::vector<Type*> ConstCharPtrTy_args;
    ConstCharPtrTy_args.push_back(ConstCharPtrTy);
    ConstCharPtrTy_args.push_back(IntegerType::get(M.getContext(), 1));
    FunctionType* FuncTy = FunctionType::get(
    /*Result=*/Type::getVoidTy(M.getContext()),
    /*Params=*/ConstCharPtrTy_args,
    /*isVarArg=*/false);
    Constant* c = M.getOrInsertFunction("_Z20countFuncBranchTakenPKcb", FuncTy);
    Function* countFuncBranch = dyn_cast<Function>(c);

    for (Module::iterator MI = M.begin(), ME = M.end(); MI != ME; ++MI) {
      // MI is an iterator over functions in the program.

      // Create a const char[] for the function name
      Constant *const_array_7 = ConstantDataArray::getString(M.getContext(), MI->getName(), true);
      GlobalVariable* global_arr = new GlobalVariable(/*Module=*/M,
       /*Type=*/const_array_7->getType(),
       /*isConstant=*/true,
       /*Linkage=*/GlobalValue::InternalLinkage,
       /*Initializer=*/const_array_7, // has initializer, specified below
       /*Name=*/MI->getName());
      global_arr->setAlignment(16);

      for (Function::iterator BI = MI->begin(), BE = MI->end(); BI != BE;
          ++BI) {
        // BI is an iterator over basic blocks in the function.

        // Create an IRBuilder for this basic block
        IRBuilder<> builder(BI);

        // Each basic block ends with a terminator; a terminator can be a branch
        BranchInst* terminator = dyn_cast<BranchInst>(BI->getTerminator());
        // Make sure it's a conditional branch
        if (terminator != NULL && terminator->isConditional()) {
          // set the builder to insert right before the branch instr
          builder.SetInsertPoint(terminator);

          if (countFuncBranch) {
            errs() << "inserting countFuncBranchBool\n";

            // get the branch condition
            Value *cond = terminator->getCondition();

            // create a pointer to the global array
            ConstantInt* arr_int = ConstantInt::get(M.getContext(),
                APInt(32, StringRef("0"), 10));
            std::vector<Constant*> arr_indices;
            arr_indices.push_back(arr_int);
            arr_indices.push_back(arr_int);
            Constant *arr_ptr = ConstantExpr::getGetElementPtr(global_arr,
                arr_indices);

            // insert the call to count the branches
            builder.CreateCall2(countFuncBranch, arr_ptr, cond);
          }
        }
        // Print everything at the end (WHY IS THIS NOT WORKING?)
        if (ME->getPrevNode() == MI && BE->getPrevNode() == BI) {

          errs() << "test1 \n";
          builder.SetInsertPoint(BI->getTerminator());
          // Function definition for printEverything
          std::vector<Type*> VoidTy_args;
          FunctionType* VoidTy = FunctionType::get(
          /*Result=*/Type::getVoidTy(M.getContext()),
          /*Params=*/VoidTy_args,
          /*isVarArg=*/false);
          Constant* c2 = M.getOrInsertFunction("_Z15printEverythingv", VoidTy);
          Function* printFunc = dyn_cast<Function>(c2);

          errs() << "test3\n";
          builder.CreateCall(printFunc);
          errs() << "test4\n";
        }
      }
    }

    return false;
  }

};
}
char BranchBias::ID = 0;
static RegisterPass<BranchBias> X("BranchBias", "BranchBias Pass", false,
    false);
