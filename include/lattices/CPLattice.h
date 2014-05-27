#ifndef CPLATTICE_H_
#define CPLATTICE_H_

#include "Lattice.h"
#include "CPLatticePoint.h"

class CPLattice:Lattice {
public:
  CPLattice();
  CPLatticePoint join(CPLatticePoint& in1, CPLatticePoint& in2);
  CPLatticePoint equals(CPLatticePoint& in1, CPLatticePoint& in2);
  CPLatticePoint& top;
  CPLatticePoint& bottom;
};

#endif /* CPLATTICE_H_ */