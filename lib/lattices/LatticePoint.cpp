#include "lattices/LatticePoint.h"

// LatticePoint::~LatticePoint() {}

LatticePoint* LatticePoint::join(LatticePoint* in) { return in; }

bool LatticePoint::equals(LatticePoint* in) { return true; }
