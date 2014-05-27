#ifndef CPLATTICE_H_
#define CPLATTICE_H_

#include "Lattice.h"
#include "CPLatticePoint.h"

class CPLattice: public Lattice {
public:
  CPLattice();
  LatticePoint join(LatticePoint& in1, LatticePoint& in2);
  bool equals(LatticePoint& in1, LatticePoint& in2);
  LatticePoint& top = new CPLatticePoint(false, new std::map<Value *, Constant *>);
  LatticePoint& bottom = new CPLatticePoint(true, new std::map<Value *, Constant *>);
};

#endif /* CPLATTICE_H_ */