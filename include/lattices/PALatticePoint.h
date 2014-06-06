#ifndef PALATTICEPOINT_H_
#define PALATTICEPOINT_H_

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

class PALatticePoint : public LatticePoint {
  
public:
  
  // ~RALatticePoint() {}
  
  /*
   Our representation maps values to integer ranges. We make use of LLVM's constant range class.
   */
  
  std::set<Value *> pointers_to_anything;
  
  std::map<Value*, std::set<Value*> > representation;
  
  PALatticePoint() : LatticePoint(LPK_PALatticePoint), representation(std::map<Value*, std::set<Value*> >()) {}
  
  PALatticePoint(bool bottomIN, bool topIN, std::map<Value*, std::set<Value*> > representationIN) : LatticePoint(LPK_PALatticePoint, bottomIN, topIN), representation(representationIN) {}
  
  PALatticePoint(PALatticePoint &copy) : LatticePoint(LPK_PALatticePoint, copy.isBottom, copy.isTop), representation(copy.representation) {}
  
  
  
  
  static bool classof(const LatticePoint *L) {
    return L->getKind() == LPK_PALatticePoint;
  }
  
  LatticePoint* join(LatticePoint* in);
  //PALatticePoint* meet(LatticePoint* in);
  bool equals(LatticePoint* in);
  void printToErrs();
  
};

#endif /* PALATTICEPOINT_H_ */
