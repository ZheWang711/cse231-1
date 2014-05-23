#include "llvm/Pass.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
// Include the Instruction Iterator for Functions.
#include "llvm/Support/InstIterator.h"

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

    // Function definition for void function (const char*)
    std::vector<Type*> ConstCharPtrTy2_args;
    ConstCharPtrTy2_args.push_back(ConstCharPtrTy);
    FunctionType* FuncTy2 = FunctionType::get(
    /*Result=*/Type::getVoidTy(M.getContext()),
    /*Params=*/ConstCharPtrTy2_args,
    /*isVarArg=*/false);
    Constant* c2 = M.getOrInsertFunction("_Z8initFuncPKc", FuncTy2);
    Function* initFunc = dyn_cast<Function>(c2);

    // Function definition for printEverything
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

    for (Module::iterator MI = M.begin(), ME = M.end(); MI != ME; ++MI) {
      // MI is an iterator over functions in the program.

      // Create a const char[] for the function name
      Constant *data_arr = ConstantDataArray::getString(M.getContext(), MI->getName(), true);
      GlobalVariable* global_arr = new GlobalVariable(/*Module=*/M,
       /*Type=*/data_arr->getType(),
       /*isConstant=*/true,
       /*Linkage=*/GlobalValue::InternalLinkage,
       /*Initializer=*/data_arr, // has initializer, specified below
       /*Name=*/MI->getName());
      global_arr->setAlignment(16);

      // create a pointer to the global array
      ConstantInt* arr_int = ConstantInt::get(M.getContext(),
          APInt(32, StringRef("0"), 10));
      std::vector<Constant*> arr_indices;
      arr_indices.push_back(arr_int);
      arr_indices.push_back(arr_int);
      Constant *arr_ptr = ConstantExpr::getGetElementPtr(global_arr,
          arr_indices);

      for (Function::iterator BI = MI->begin(), BE = MI->end(); BI != BE;
          ++BI) {
        // BI is an iterator over basic blocks in the function.

        // handles the case where there are no branches
        builder.SetInsertPoint(BI->getFirstInsertionPt());
        builder.CreateCall(initFunc, arr_ptr);

        // Each basic block ends with a terminator; a terminator can be a branch
        BranchInst* terminator = dyn_cast<BranchInst>(BI->getTerminator());

        if (terminator != NULL && terminator->isConditional()) {

          // set the builder to insert right before the branch instr
          builder.SetInsertPoint(terminator);

          // get the branch condition
          Value *cond = terminator->getCondition();

          // insert the call to count the branches
          builder.CreateCall2(countFuncBranch, arr_ptr, cond);
        }
        // make the call to print everything at the end of main
        if (MI->getName() == "main" && !printed) {
          // This is a little hacky -- only the getPrevNode() and getNextNode() methods
          // return the correct type. Fix this if you can.
          builder.SetInsertPoint(MI->back().getInstList().back().getPrevNode()->getNextNode());
          builder.CreateCall(printFunc);
          printed = true; // only call once
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
