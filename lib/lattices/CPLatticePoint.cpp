#include "lattices/CPLatticePoint.h"
// #include "lattices/LatticePoint.h"

// Define join method.
LatticePoint CPLatticePoint::join(LatticePoint& in){
  
  if (in.isBottom){
    return *this;
  }
  if (this->isBottom) {
    return in;
  }
  
  CPLatticePoint* in_casted =  dyn_cast<CPLatticePoint *>(in);
  
  std::map<Value *, Constant *> representation1 = this->representation;
  std::map<Value *, Constant *> representation2 = in_casted->representation;
  
  std::map<Value *, Constant *> result;
  
  for (std::map<Value *, Constant *>::iterator it=representation1.begin(); it!=representation1.end(); ++it){
    Value* elm = it->first;
    Constant* c1 = it->second;
    if (representation2.count(elm) > 0){
      Constant* c2 = representation2[elm];
      if (c1 == c2){
        result[elm] = c1;
      }
    }
  }
  return new CPLatticePoint(false, false, result);
}


bool CPLatticePoint::equals(LatticePoint& in){
  if (in.isBottom || this->isBottom){
    return in.isBottom == this->isBottom;
  }
  CPLatticePoint* in_casted =  dyn_cast<CPLatticePoint *>(in);
  std::map<Value *, Constant *> representation1 = this->representation;
  std::map<Value *, Constant *> representation2 = in_casted->representation;
  
  for (std::map<Value *, Constant *>::iterator it=representation1.begin(); it!=representation1.end(); ++it){
    Value* elm = it->first;
    Constant* c1 = it->second;
    if (representation2.count(elm) <= 0){
      return false;
    }
    else{
      Constant* c2 = representation2[elm];
      if (c1 != c2){
        return false
      }
    }
  }
  return true;
}
