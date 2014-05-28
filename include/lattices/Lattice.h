#ifndef LATTICE_H_
#define LATTICE_H_


#include "LatticePoint.h"
#include "CPLatticePoint.h"
#include "llvm/Support/Casting.h"

class Lattice {
 public:
    
  /// Discriminator for LLVM-style RTTI (dyn_cast<> et al.)
  enum LatticeKind {
    LK_CPLattice
  };
  
  Lattice(LatticeKind K) : Kind(K) {}
  
  virtual ~Lattice();
  virtual LatticePoint join(LatticePoint& in1, LatticePoint& in2);
  virtual bool equals(LatticePoint& in1, LatticePoint& in2);

  virtual LatticePoint& top() = 0;
  virtual LatticePoint& bottom() = 0;

  // LatticePoint& top;
  // LatticePoint& bottom;
  
  LatticeKind getKind() const { return Kind; }

 private:
  const LatticeKind Kind;
};

#endif /* LATTICE_H_ */

