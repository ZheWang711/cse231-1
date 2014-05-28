#ifndef LATTICEPOINT_H_
#define LATTICEPOINT_H_

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/InstIterator.h"
#include <map>
#include "llvm/Support/Casting.h"

class LatticePoint {
public:



  virtual ~LatticePoint();
  bool isBottom;
  bool isTop;

  enum LatticePointKind {
    LPK_CPLatticePoint
  };

  LatticePointKind getKind() const { return Kind; }
 LatticePoint(LatticePointKind K, bool isTopIn, bool isBottomIn) : Kind(K), isTop(isTopIn), isBottom(isBottomIn){}
 private:
  const LatticePointKind Kind;


};

#endif /* LATTICEPOINT_H_ */

