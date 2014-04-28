#include "llvm/Support/InstIterator.h"

using namespace llvm;


for (Module::iterator MI = M.begin(), ME = M.end(); MI != ME; ++MI){
  
  
  // Get me a pointerType to char*
  PointerType* ConstCharPtrTy = PointerType::get(IntegerType::get(M.getContext(), 8), 0);

  // Function definition for void function (const char*)
  // Mangled Name of function: _Z17countInstExecutedPKc
  std::vector<Type*> ConstCharPtrTy2_args;
  ConstCharPtrTy2_args.push_back(ConstCharPtrTy);
  FunctionType* FuncTy2 = FunctionType::get(
					    /*Result=*/Type::getVoidTy(M.getContext()),
					    /*Params=*/ConstCharPtrTy2_args,
					    /*isVarArg=*/false);
  Constant* c2 = M.getOrInsertFunction("_Z17countInstExecutedPKc", FuncTy2);
  Function* initFunc = dyn_cast<Function>(c2);
  
  // Create the IRBuilder
  IRBuilder<> builder(M.getContext());
  bool printed = false;


  // MI is an iterator over functions in the program.
  for (inst_iterator I = inst_begin(MI), E = inst_end(MI); I != E; ++I){
    for (inst_iterator I = inst_begin(MI), E = inst_end(MI); I != E; ++I){
      // get the instruction opcode name
      int inst = I->getOpcodeName();
      
      // Now use this name in inserted call to 
      
    }
  } 
 }
