#include "lattices/PALatticePoint.h"
#include "helper/helper.h"

/*
 Join == Union!
 */

LatticePoint* PALatticePoint::join(LatticePoint* in){
  
  PALatticePoint* in_casted =  dyn_cast<PALatticePoint>(in);
  
  if (in->isTop || this->isBottom){
    PALatticePoint* result = new PALatticePoint(*in_casted);
    return result;
  }
  if (this->isTop || in->isBottom) {
    PALatticePoint* result = new PALatticePoint(*this);
    return result;
  }
  
  std::map<Value*, std::set<Value*> > representation1 = this->representation;
  std::map<Value*, std::set<Value*> >representation2 = in_casted->representation;
  
  std::set<Value*> pointers_to_anything_1 = this->pointers_to_anything;
  std::set<Value*> pointers_to_anything_2 = in_casted->pointers_to_anything;
  
  std::map<Value*, std::set<Value*> > result_map;
  std::set<Value*> pointers_to_anything_results;
  
  std::set<Value *> key_set;
  for (std::map<Value*, std::set<Value*> >::iterator it=representation1.begin(); it!=representation1.end(); ++it){
    Value* elm = it->first;
    key_set.insert(elm);
  }
  for (std::map<Value*, std::set<Value*> >::iterator it=representation2.begin(); it!=representation2.end(); ++it){
    Value* elm = it->first;
    key_set.insert(elm);
  }
  for (std::set<Value*>::iterator it = pointers_to_anything_1.begin(); it!=pointers_to_anything_1.end(); ++it) {
    key_set.insert(*it)
  }
  for (std::set<Value*>::iterator it = pointers_to_anything_2.begin(); it!=pointers_to_anything_2.end(); ++it) {
    key_set.insert(*it)
  }
  
  for (std::set<Value *>::iterator it = key_set.begin(); it != key_set.end(); ++it){
    if (pointers_to_anything_1.count(*it) > 0 || pointers_to_anything_2.count(*it) > 0) {
      pointers_to_anything_results.insert(*it);
    }
    else if (representation1.count(*it) > 0 && representation2.count(*it) > 0){
      std::set<Value*> union_points;
      std::set<Value*> c1 = representation1[*it];
      std::set<Value*> c2 = representation2[*it];
      for (std::set<Value*>::iterator it1 = c1.begin(); it1!=c1.end(); ++it1){
        union_points.insert(*it1);
      }
      for (std::set<Value*>::iterator it2 = c2.begin(); it2!=c2.end(); ++it2){
        union_points.insert(*it2);
      }
      result_map[*it] = union_points;
    }
    else if (representation1.count(*it) > 0 && representation2.count(*it) == 0){
      result_map[*it] = representation1[*it];
    }
    else if (representation1.count(*it) == 0 && representation2.count(*it) > 0){
      result_map[*it] = representation2[*it];
    }
  }

  
  PALatticePoint* result = new PALatticePoint(false, false, result_map);

  return result;
}

// DONE
bool PALatticePoint::equals(LatticePoint* in){
  if (in->isBottom || this->isBottom){
    return in->isBottom == this->isBottom;
  }
  if (in->isTop || this->isTop){
    return in->isTop == this->isTop;
  }
  
  PALatticePoint* in_casted =  dyn_cast<PALatticePoint>(in);
  std::map<Value*, std::set<Value*> > representation1 = this->representation;
  std::map<Value*, std::set<Value*> >representation2 = in_casted->representation;
  
  std::set<Value*> pointers_to_anything_1 = this->pointers_to_anything;
  std::set<Value*> pointers_to_anything_2 = in_casted->pointers_to_anything;
  
  if (pointers_to_anything_1.size() != pointers_to_anything_2.size()) {
    return false;
  }
  
  for (std::set<Value*>::iterator it = pointers_to_anything_1.begin(); it!=pointers_to_anything_1.end(); ++it) {
    if (pointers_to_anything_2.count(*it) <= 0) {
      return false;
    }
  }
  
  
  for (std::map<Value*, std::set<Value*> >::iterator it=representation1.begin(); it!=representation1.end(); ++it){
    Value* elm = it->first;
    std::set<Value*> c1 = it->second;
    if (representation2.count(elm) <= 0){
      return false;
    }
    else{
      std::set<Value*> c2 = representation2[elm];
      if (c1.size() != c2.size()) {
        return false;
      }
      for (std::set<Value*>::iterator it = c1.begin(); it!=c1.end(); ++it){
        if (c2.count(*it) <= 0) {
          return false;
        }
      }
    }
  }
  
  return true;
}

// Done.
void PALatticePoint::printToErrs() {
  errs() << "PALatticePoint: isBottom: " << this->isBottom << ", isTop: " << this->isTop << " | ";
  if (this->isBottom || this->isTop){
    errs() << "\n";
    return;
  }
	errs() << "{ ";
  
  std::set<Value*> pointers_to_anything_1 = this->pointers_to_anything;
  for (std::set<Value*>::iterator it = pointers_to_anything_1.begin(); it!=pointers_to_anything_1.end(); ++it) {
    (*it)->print(errs());
    errs() << " --> (anything) ,";
  }
  
  
	for(std::map<Value*, std::set<Value*> >::iterator it = this->representation.begin(); it != representation.end(); ++it) {
		Value* val = it->first;
    val->print(errs());
    errs() << " --> [ ";
		std::set<Value*> point_set = it->second;
    for (std::set<Value*>::iterator it = point_set.begin(); it!=point_set.end(); ++it){
      (*it)->print(errs());
      errs() << " ,";
    }
		errs() << "] ; ";
  }
  errs() << " } \n";
  return;
}

//inline bool operator!=()
