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

/*

 This is the range analysis lattice/latticepoint class. Range analysis is a MAY analysis. Thus, top is defined to be the full set and bottom is defined to be empty.
 
 Join must be union over ranges.
 
 Meet is intersection over ranges.
 
 We define our
*/

using namespace llvm;

class RALatticePoint : public LatticePoint {
  
public:
  
  // ~RALatticePoint() {}
  
  /*
   Our representation maps values to integer ranges. The two booleans stand for left-infinite and right infinite. That is, if x->(-infinite, 8), the tuple would look like
            (true, false, some value, 8).
   
   */
  std::map<Value*, std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > > representation;
  

  
  RALatticePoint(bool bottomIN, bool topIN, std::map<Value*, std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > > representationIN) : LatticePoint(LPK_RALatticePoint, bottomIN, topIN), representation(representationIN) {}
  
  // CPLatticePoint(bool bottomIN, bool topIN);
  
  RALatticePoint() : LatticePoint(LPK_RALatticePoint), representation(std::map<Value*, std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > >()) {}
  
  
  
  static bool classof(const LatticePoint *L) {
    return L->getKind() == LPK_RALatticePoint;
  }
  LatticePoint* join(LatticePoint* in);
  bool equals(LatticePoint* in);
  std::string LPprint();
  
};

#endif /* RALATTICEPOINT_H_ */
