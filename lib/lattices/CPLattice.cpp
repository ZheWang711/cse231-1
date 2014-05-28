#include "lattices/CPLattice.h"

CPLattice::CPLattice(){
  this->top = CPLatticePoint(false, std::map<Value *, Constant *>());
  this->bottom = CPLatticePoint(true, std::map<Value *, Constant *>());
}

LatticePoint CPLattice::join(LatticePoint& in1, LatticePoint& in2){

  
  if (in1.isBottom){
    return in2;
  }
  if (in2.isBottom) {
    return in1;
  }
  
  CPLatticePoint& in1_casted =  dyn_cast<CPLatticePoint>(in1);
  CPLatticePoint* in2_casted =  dyn_cast<CPLatticePoint>(in2);

  std::map<Value *, Constant *> representation1 = in1_casted->representation;
  std::map<Value *, Constant *> representation2 = in2_casted->representation;

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
  return new CPLatticePoint(false, result);
}

CPLattice::LatticePoint& top(){
  return(CPLatticePoint());
}

CPLattice::LatticePoint& bottom(){
  return(CPLatticePoint());
}

bool CPLattice::equals(LatticePoint& in1, LatticePoint& in2){
  if (in1.isBottom || in2.isBottom){
    return in1.isBottom == in2.isBottom;
  }
  std::map<Value *, Constant *> representation1 = in1.representation;
  std::map<Value *, Constant *> representation2 = in2.representation;
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
