#ifndef CSELATTICEPOINT_H_
#define CSELATTICEPOINT_H_

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/InstIterator.h"

#include <map>
#include <string>
#include <sstream>

#include "LatticePoint.h"

using namespace llvm;

class CSELatticePoint : public LatticePoint {

public:
  
  std::map<Value*, Instruction*> representation;

  // Constructors
  CSELatticePoint(bool bottomIN, bool topIN, std::map<Value*, Instruction*> representationIN) : LatticePoint(LPK_CSELatticePoint, bottomIN, topIN), representation(representationIN) {}

  CSELatticePoint() : LatticePoint(LPK_CSELatticePoint), representation(std::map<Value*, Instruction*>()) {}

  static bool classof(const LatticePoint *L) {
    return L->getKind() == LPK_CSELatticePoint;
  }
  
  LatticePoint* join(LatticePoint* in);
  bool equals(LatticePoint* in);
  std::string LPprint();
};

#endif /* CSELATTICEPOINT_H_ */
