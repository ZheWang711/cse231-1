#ifndef HELPER_H_
#define HELPER_H_

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/Support/Casting.h"
#include "llvm/IR/Constants.h"
using namespace llvm;

class helper {
public:
    
  /* 
   folds the binary operator for the special case of both arguments being ConstantInts.
   */
  static ConstantInt* foldBinaryOperator(unsigned Opcode ,ConstantInt *C1, ConstantInt *C2);
};

#endif /* HELPER_H_ */

