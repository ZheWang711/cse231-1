#include "lattices/CPLatticePoint.h"
// #include "lattices/LatticePoint.h"

// CPLatticePoint::CPLatticePoint(){
//   LatticePoint( LPK_CPLatticePoint);
//   this.isBottom = false;
//   this.isTop = false;
//   this.representation = std::map<Value*, Constant*>()
// }

// Define join method.
LatticePoint* CPLatticePoint::join(LatticePoint* in){
  
  if (in->isBottom){
    return this;
  }
  if (this->isBottom) {
    return in;
  }
  
  CPLatticePoint* in_casted =  dyn_cast<CPLatticePoint>(in);
  
  std::map<Value *, Constant *> representation1 = this->representation;
  std::map<Value *, Constant *> representation2 = in_casted->representation;
  
  std::map<Value *, Constant *> result_map;
  
  for (std::map<Value *, Constant *>::iterator it=representation1.begin(); it!=representation1.end(); ++it){
    Value* elm = it->first;
    Constant* c1 = it->second;
    if (representation2.count(elm) > 0){
      Constant* c2 = representation2[elm];
      if (c1 == c2){
        result_map[elm] = c1;
      }
    }
  }
  CPLatticePoint* result = new CPLatticePoint(false, false, result_map);
  return result;
}




bool CPLatticePoint::equals(LatticePoint* in){
  if (in->isBottom || this->isBottom){
    return in->isBottom == this->isBottom;
  }
  CPLatticePoint* in_casted =  dyn_cast<CPLatticePoint>(in);
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
        return false;
      }
    }
  }
  return true;
}
