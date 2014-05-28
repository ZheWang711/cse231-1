#ifndef CPLATTICEPOINT_H_
#define CPLATTICEPOINT_H_

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/InstIterator.h"
#include <map>


using namespace llvm;

class CPLatticePoint: public LatticePoint {
public:
 CPLatticePoint() : LatticePoint(LPK_CPLatticePoint) {}  
  CPLatticePoint(bool isBottom, std::map<Value *, Constant *> representation);
  std::map<Value *, Constant *> representation;
  
  static bool classof(const LatticePoint *L) {
    return L->getKind() == LPK_CPLatticePoint;
  }
};

#endif /* CPLATTICEPOINT_H_ */
