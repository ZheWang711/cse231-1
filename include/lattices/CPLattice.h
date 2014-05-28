#ifndef CPLATTICE_H_
#define CPLATTICE_H_

#include "Lattice.h"
#include "CPLatticePoint.h"


using namespace llvm;


  class CPLattice: public Lattice {
 
  public:
    
  CPLattice() : Lattice(LK_CPLattice) { }
    
    LatticePoint join(LatticePoint& in1, LatticePoint& in2);
    bool equals(LatticePoint& in1, LatticePoint& in2);

    static bool classof(const Lattice *L) {
      return L->getKind() == LK_CPLattice;
    }
    LatticePoint& top();
    LatticePoint& bottom();

  };  


#endif /* CPLATTICE_H_ */
