#ifndef CPLATTICEPOINT_H_
#define CPLATTICEPOINT_H_

#include "llvm/IR/Constants.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/Support/raw_ostream.h"

#include <map>
#include <string>
#include <sstream>

#include "LatticePoint.h"

using namespace llvm;

class CPLatticePoint : public LatticePoint {

public:
  
  // ~CPLatticePoint() {}

  std::map<Value*, ConstantInt*> representation;

  CPLatticePoint(bool bottomIN, bool topIN, std::map<Value*, ConstantInt*> representationIN) : LatticePoint(LPK_CPLatticePoint, bottomIN, topIN), representation(representationIN) {}

  // CPLatticePoint(bool bottomIN, bool topIN);
  
  CPLatticePoint() : LatticePoint(LPK_CPLatticePoint), representation(std::map<Value*, ConstantInt*>()) {}

    static bool classof(const LatticePoint *L) {
      errs() << L->getKind() << " classof?\n";
      return L->getKind() == LPK_CPLatticePoint;
    }
  LatticePoint* join(LatticePoint* in);
  bool equals(LatticePoint* in);
  std::string LPprint();
};

#endif /* CPLATTICEPOINT_H_ */
