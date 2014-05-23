#ifndef LATTICE_H_
#define LATTICE_H_

#include "LatticePoint.h"

class Lattice {
public:
  Lattice();
  virtual ~Lattice();
  virtual LatticePoint join(LatticePoint& in1, LatticePoint& in2);

private:
  LatticePoint& top;
  LatticePoint& bottom;
};

#endif /* LATTICE_H_ */

