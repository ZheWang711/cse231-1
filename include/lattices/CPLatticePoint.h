#ifndef CPLATTICEPOINT_H_
#define CPLATTICEPOINT_H_

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/InstIterator.h"
#include <map>

class CPLatticePoint:LatticePoint {
public:
  CPLatticePoint();
  CPLatticePoint(bool isBottom, std::map<Value *, Constant *> representation);
  bool isBottom;
  std::map<Value *, Constant *> representation;
};

#endif /* CPLATTICEPOINT_H_ */
