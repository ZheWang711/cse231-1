#ifndef CPLATTICEPOINT_H_
#define CPLATTICEPOINT_H_

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/InstIterator.h"

#include <map>

#include "LatticePoint.h"

using namespace llvm;

class CPLatticePoint : public LatticePoint {

public:
  
  // ~CPLatticePoint() {}

  std::map<Value*, Constant*> representation;

  CPLatticePoint(bool bottomIN, bool topIN, std::map<Value*, Constant*> representationIN) : LatticePoint(LPK_CPLatticePoint, bottomIN, topIN), representation(representationIN) {}

  // CPLatticePoint(bool bottomIN, bool topIN);
  
  CPLatticePoint() : LatticePoint(LPK_CPLatticePoint), representation(std::map<Value*, Constant*>()) {}



    static bool classof(const LatticePoint *L) {
      return L->getKind() == LPK_CPLatticePoint;
    }
  LatticePoint* join(LatticePoint* in);
  bool equals(LatticePoint* in);
};

#endif /* CPLATTICEPOINT_H_ */
