#include "lattices/RALatticePoint.h"

/*
  Join == Union!
*/

LatticePoint* RALatticePoint::join(LatticePoint* in){
  
  RALatticePoint* in_casted =  dyn_cast<RALatticePoint>(in);
  if (in->isTop || this->isBottom){
    RALatticePoint* result = new RALatticePoint(*in_casted);
    return result;
  }
  if (this->isTop || in->isBottom) {
    RALatticePoint* result = new RALatticePoint(*this);
    return result;
  }
  std::map<Value*, ConstantRange*> representation1 = this->representation;
  std::map<Value*, ConstantRange*> representation2 = in_casted->representation;
  
  std::map<Value*, ConstantRange*> result_map;
  
  std::set<Value *> key_set;
  for (std::map<Value*, ConstantRange*>::iterator it=representation1.begin(); it!=representation1.end(); ++it){
    Value* elm = it->first;
    key_set.insert(elm);
  }
  for (std::map<Value*, ConstantRange*>::iterator it=representation2.begin(); it!=representation2.end(); ++it){
    Value* elm = it->first;
    key_set.insert(elm);
  }
  
  for (std::set<Value *>::iterator it = key_set.begin(); it != key_set.end(); ++it){
    if (representation1.count(*it) > 0 && representation2.count(*it) > 0){
      ConstantRange* c1 = representation1[*it];
      ConstantRange* c2 = representation2[*it];
      ConstantRange r = c1->unionWith(*c2);
      result_map[*it] = &r;
    }
    else if (representation1.count(*it) > 0 && representation2.count(*it) == 0){
      result_map[*it] = representation1[*it];
    }
    else if (representation1.count(*it) == 0 && representation2.count(*it) > 0){
      result_map[*it] = representation2[*it];
    }
  }
  
  RALatticePoint* result = new RALatticePoint(false, false, result_map);
  return result;
}

/*
  Meet == Intersection!
 */

RALatticePoint* RALatticePoint::meet(LatticePoint* in){
  
  RALatticePoint* in_casted =  dyn_cast<RALatticePoint>(in);
  if (in->isTop || this->isBottom){
    RALatticePoint* result = new RALatticePoint(*this);
    return result;
  }
  if (this->isTop || in->isBottom) {
    RALatticePoint* result = new RALatticePoint(*in_casted);
    return result;
  }
  
  std::map<Value*, ConstantRange*> representation1 = this->representation;
  std::map<Value*, ConstantRange*> representation2 = in_casted->representation;
  
  std::map<Value*, ConstantRange*> result_map;
  
  std::set<Value *> key_set;
  for (std::map<Value*, ConstantRange*>::iterator it=representation1.begin(); it!=representation1.end(); ++it){
    Value* elm = it->first;
    key_set.insert(elm);
  }
  for (std::map<Value*, ConstantRange*>::iterator it=representation2.begin(); it!=representation2.end(); ++it){
    Value* elm = it->first;
    key_set.insert(elm);
  }
  
  for (std::set<Value *>::iterator it = key_set.begin(); it != key_set.end(); ++it){
    if (representation1.count(*it) > 0 && representation2.count(*it) > 0){
      ConstantRange* c1 = representation1[*it];
      ConstantRange* c2 = representation2[*it];
      ConstantRange r = c1->intersectWith(*c2);
      result_map[*it] = &r;
    }
  }
  
  RALatticePoint* result = new RALatticePoint(false, false, result_map);
  return result;
}



bool RALatticePoint::equals(LatticePoint* in){
  if (in->isBottom || this->isBottom){
    return in->isBottom == this->isBottom;
  }
  if (in->isTop || this->isTop){
    return in->isTop == this->isTop;
  }
  
  RALatticePoint* in_casted =  dyn_cast<RALatticePoint>(in);
  std::map<Value*, ConstantRange*> representation1 = this->representation;
  std::map<Value*, ConstantRange*> representation2 = in_casted->representation;
  
  for (std::map<Value*, ConstantRange*>::iterator it=representation1.begin(); it!=representation1.end(); ++it){
    Value* elm = it->first;
    ConstantRange* c1 = it->second;
    if (representation2.count(elm) <= 0){
      return false;
    }
    else{
      ConstantRange* c2 = representation2[elm];
      if (*c1 != *c2) {
        return false;
      }
    }
  }
  return true;
}

void RALatticePoint::printToErrs() {
  errs() << "RALatticePoint: isBottom: " << this->isBottom << ", isTop: " << this->isTop << " | ";
  if (this->isBottom || this->isTop){
    errs() << "\n";
    return;
  }
	errs() << "{ ";
	for(std::map<Value*, ConstantRange*>::iterator it = this->representation.begin(); it != representation.end(); ++it) {
		Value* val = it->first;
    errs() << val << " --> ";
		ConstantRange* range = it->second;
    range->print(errs());
		errs() << ", ";
  }
  errs() << " } \n";
  return;
}
