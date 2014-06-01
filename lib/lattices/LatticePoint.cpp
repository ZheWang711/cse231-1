#include "lattices/LatticePoint.h"

// LatticePoint::~LatticePoint() {}

LatticePoint* LatticePoint::join(LatticePoint* in) { return in; }

bool LatticePoint::equals(LatticePoint* in) { return true; }

std::string LatticePoint::LPprint() {
    std::stringstream ss;
    ss << "isBottom: " << this->isBottom << ", isTop: " << this->isTop << "\n";
    return ss.str();
}

