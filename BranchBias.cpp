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

  std::map<int, int> instructionCount; // maps instructions to the number of times they occur.

  BranchBias() :
      ModulePass(ID) {
  }

  // This is the main body of our code.
  virtual bool runOnModule(Module &M) {
    // find countBranch
    std::vector<Type*>FuncTy_25_args;
    FuncTy_25_args.push_back(IntegerType::get(M.getContext(), 32));
    FunctionType* FuncTy_25 = FunctionType::get(
      /*Result=*/Type::getVoidTy(M.getContext()),
      /*Params=*/FuncTy_25_args,
      /*isVarArg=*/false);
    Constant* c = M.getOrInsertFunction("_Z11countBranchi", FuncTy_25);
    Function* countBranch = dyn_cast<Function>(c);

    std::vector<Type*>FuncTy_40_args;
    FunctionType* FuncTy_40 = FunctionType::get(
     /*Result=*/Type::getVoidTy(M.getContext()),
     /*Params=*/FuncTy_40_args,
     /*isVarArg=*/false);
    Constant* c2 = M.getOrInsertFunction("_Z8testFuncv", FuncTy_40);
    Function* testFunc = dyn_cast<Function>(c2);

    for (Module::iterator MI = M.begin(), ME = M.end(); MI != ME; ++MI) {
      // MI is an iterator over functions in the program.

//      errs() << "function: " << MI->getName() << "\n";
//      // create a global var for this function
//      ArrayType* ArrayTy = ArrayType::get(IntegerType::get(M.getContext(), 8), MI->getName().size());
//      GlobalVariable* global_array = new GlobalVariable(M,
//       ArrayTy,
//       /*isConstant=*/true,
//       /*Linkage=*/GlobalValue::InternalLinkage,
//       /*Initializer=*/0, // has initializer, specified below
//       /*Name=*/MI->getName());
//      global_array->setAlignment(1);
//      Constant *const_array = ConstantDataArray::getString(M.getContext(), MI->getName(), true);
//      global_array->setInitializer(const_array);

      for (Function::iterator BI = MI->begin(), BE = MI->end(); BI != BE; ++BI) {
        // BI is an iterator over basic blocks in the function.

        // Create an IRBuilder for this basic block
        IRBuilder<> builder(BI);

        // Each basic block ends with a terminator; a terminator can be a branch
        BranchInst* BR = dyn_cast<BranchInst>(BI->getTerminator());
        // Make sure it's a conditional branch
        if (BR == NULL || !BR->isConditional()) {
          continue;
        }

        // set the builder to insert right before the branch instr
        builder.SetInsertPoint(BR);
        errs() << BI->getName() << "\n";
        if (testFunc) {
          errs() << "inserting testFunc!\n";
          builder.CreateCall(testFunc);
        }
        if (countBranch) {
          errs() << "inserting countBranch\n";
          Value* integer = ConstantInt::get(M.getContext(), APInt(32, BR->getOpcode(), 10));
          builder.CreateCall(countBranch, integer);
        }

        /*
        // evaluate the condition?
        Value *cond = BR->getCondition();
        ICmpInst *CI = dyn_cast<ICmpInst>(cond);
        if (!CI || !CI->isEquality())
          continue;

        Value *LHS = CI->getOperand(0);
        errs() << "MI getname: " << MI->getName().str() << "\n";
        errs() << "Cond " << cond->getName() << "\n";
        errs() << "ICmpInst operand0 " << LHS->getName() << "\n";
        */
      }
    }

    return false;
  }

};
}
char BranchBias::ID = 0;
static RegisterPass<BranchBias> X("BranchBias", "BranchBias Pass", false,
    false);
