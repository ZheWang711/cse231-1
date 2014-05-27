#ifndef LATTICEPOINT_H_
#define LATTICEPOINT_H_

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/InstIterator.h"
#include <map>

class LatticePoint {
public:
  LatticePoint();
  virtual ~LatticePoint();
};

#endif /* LATTICEPOINT_H_ */

