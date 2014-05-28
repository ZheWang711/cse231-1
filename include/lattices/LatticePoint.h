#ifndef LATTICEPOINT_H_
#define LATTICEPOINT_H_

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/InstIterator.h"
#include <map>
#include "llvm/Support/Casting.h"

using namespace llvm;

class LatticePoint {
  
public:
  
  enum LatticePointKind {
    LPK_CPLatticePoint
  };
  

  virtual ~LatticePoint();
  bool isBottom;
  bool isTop;
  

  LatticePointKind getKind() const { return Kind; }
  
  LatticePoint(LatticePointKind K) : Kind(K) {}
  
  virtual LatticePoint join(LatticePoint& in);
  virtual bool equals(LatticePoint& in);

 private:
  const LatticePointKind Kind;

};

#endif /* LATTICEPOINT_H_ */

