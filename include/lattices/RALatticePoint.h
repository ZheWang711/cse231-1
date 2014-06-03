#ifndef RALATTICEPOINT_H_
#define RALATTICEPOINT_H_

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/IR/Constants.h"
#include <utility>
#include <map>
#include <set>
#include "LatticePoint.h"
#include "llvm/Support/ConstantRange.h"
#include "llvm/Support/raw_ostream.h"


/*

 This is the range analysis lattice/latticepoint class. Range analysis is a MAY analysis. Thus, top is defined to be the full set and bottom is defined to be empty.
 
 Join must be union over ranges.
 
 Meet is intersection over ranges.
 
*/

using namespace llvm;

class RALatticePoint : public LatticePoint {
  
public:
  
  // ~RALatticePoint() {}
  
  /*
   Our representation maps values to integer ranges. We make use of LLVM's constant range class.
   */
  
  std::map<Value*, ConstantRange*> representation;
  
  RALatticePoint() : LatticePoint(LPK_RALatticePoint), representation(std::map<Value*, ConstantRange*>()) {}
  
  RALatticePoint(bool bottomIN, bool topIN, std::map<Value*, ConstantRange*> representationIN) : LatticePoint(LPK_RALatticePoint, bottomIN, topIN), representation(representationIN) {}
  
  RALatticePoint(RALatticePoint &copy) : LatticePoint(LPK_RALatticePoint, copy.isBottom, copy.isTop), representation(copy.representation) {}
  
  
  
  
  static bool classof(const LatticePoint *L) {
    return L->getKind() == LPK_RALatticePoint;
  }
  
  LatticePoint* join(LatticePoint* in);
  RALatticePoint* meet(LatticePoint* in);
  bool equals(LatticePoint* in);
  void printToErrs();
  
};

#endif /* RALATTICEPOINT_H_ */
