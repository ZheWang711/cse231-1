#ifndef CSELATTICEPOINT_H_
#define CSELATTICEPOINT_H_

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/Support/raw_ostream.h"

#include <map>
#include <string>
#include <sstream>

#include "LatticePoint.h"
#include <utility>
#include <algorithm>

using namespace llvm;

class CSELatticePoint : public LatticePoint {

public:
  
  std::map<Value*, Instruction*> representation;

  // Constructors
  CSELatticePoint() : LatticePoint(LPK_CSELatticePoint), representation(std::map<Value*, Instruction*>()) {}

  CSELatticePoint(bool bottomIN, bool topIN, std::map<Value*, Instruction*> representationIN) : LatticePoint(LPK_CSELatticePoint, bottomIN, topIN), representation(representationIN) {}

  CSELatticePoint(CSELatticePoint &copy) : LatticePoint(LPK_CSELatticePoint, copy.isBottom, copy.isTop), representation(copy.representation) {}

  CSELatticePoint(CSELatticePoint *copy) : LatticePoint(LPK_CSELatticePoint, copy->isBottom, copy->isTop), representation(copy->representation) {}
  
  // CSELatticePoint(const CSELatticePoint&);
  // CSELatticePoint& operator=(const CSELatticePoint&);


  static bool classof(const LatticePoint *L) {
    return L->getKind() == LPK_CSELatticePoint;
  }
  
  LatticePoint* join(LatticePoint* in);
  bool equals(LatticePoint* in);
  // std::string LPprint();
  void printToErrs();
};

#endif /* CSELATTICEPOINT_H_ */
