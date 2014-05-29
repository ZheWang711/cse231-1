#include "lattices/RALatticePoint.h"

/*
  Join == Union!
*/

LatticePoint* RALatticePoint::join(LatticePoint* in){
  if (in->isTop || this->isBottom){
    return in;
  }
  if (this->isTop || in->isBottom) {
    return this;
  }
  
  RALatticePoint* in_casted =  dyn_cast<RALatticePoint>(in);
  
  
  std::map<Value*, std::tuple<bool, bool, ConstantInt *, ConstantInt *> > representation1 = this->representation;
  std::map<Value*, std::tuple<bool, bool, ConstantInt *, ConstantInt *> > representation2 = in_casted->representation;
  
  std::map<Value*, std::tuple<bool, bool, ConstantInt *, ConstantInt *> > result_map;
  
  std::set<Value *> key_set;
  for (std::map<Value*, std::tuple<bool, bool, ConstantInt *, ConstantInt *> >::iterator it=representation1.begin(); it!=representation1.end(); ++it){
    Value* elm = it->first;
    key_set.insert(elm);
  }
  for (std::map<Value*, std::tuple<bool, bool, ConstantInt *, ConstantInt *> >::iterator it=representation2.begin(); it!=representation2.end(); ++it){
    Value* elm = it->first;
    key_set.insert(elm);
  }
  
  for (std::set<Value *>::iterator it = key_set.begin(); it != key_set.end(); ++it){
    if (representation1.count(*it) > 0 && representation2.count(*it) > 0){
      std::tuple<bool, bool, ConstantInt *, ConstantInt *> c1 = representation1[*it];
      std::tuple<bool, bool, ConstantInt *, ConstantInt *> c2 = representation2[*it];
      bool isLeftInfinite = std::get<0>(c1) || std::get<0>(c2);
      bool isRightInfinite = std::get<1>(c1) || std::get<1>(c2);
      ConstantInt* lowerBound = NULL;
      ConstantInt* upperBound = NULL;
      if (!isLeftInfinite){
        if (std::get<2>(c1)->getValue() < std::get<2>(c2)->getValue()){
          lowerBound = std::get<2>(c1)->getValue();
        }
        else{
          lowerBound = std::get<2>(c2)->getValue();
        }
      }
      if (!isRightInfinite){
        if (std::get<3>(c1)->getValue() > std::get<3>(c2)->getValue()){
          upperBound = std::get<3>(c1)->getValue();
        }
        else{
          upperBound = std::get<3>(c2)->getValue();
        }
      }
      result_map[*it] = std::make_tuple(isLeftInfinite, isRightInfinite, lowerBound, upperBound);
      
    }
    
    if (representation1.count(*it) > 0 && representation2.count(*it) == 0){
      result_map[*it] = representation1[*it];
    }
    
    if (representation1.count(*it) == 0 && representation2.count(*it) > 0){
      result_map[*it] = representation2[*it]
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
  std::map<Value*, std::tuple<bool, bool, ConstantInt *, ConstantInt *> > representation1 = this->representation;
  std::map<Value*, std::tuple<bool, bool, ConstantInt *, ConstantInt *> > representation2 = in_casted->representation;
  
  for (std::map<Value *, Constant *>::iterator it=representation1.begin(); it!=representation1.end(); ++it){
    Value* elm = it->first;
    std::tuple<bool, bool, ConstantInt *, ConstantInt *> c1 = it->second;
    if (representation2.count(elm) <= 0){
      return false;
    }
    else{
      std::tuple<bool, bool, ConstantInt *, ConstantInt *> c2 = representation2[elm];
      bool isLeftInfinite = std::get<0>(c1) || std::get<0>(c2);
      bool isRightInfinite = std::get<1>(c1) || std::get<1>(c2);
      
      if (isLeftInfinite && std::get<0>(c1) != std::get<0>(c2)){
        return false;
      }
      if (isRightInfinite && std::get<1>(c1) != std::get<1>(c2)){
        return false;
      }
      if (!isLeftInfinite && std::get<2>(c1)->getValue() != std::get<2>(c2)->getValue()){
        return false;
      }
      if (!isRightInfinite && std::get<3>(c1)->getValue() != std::get<3>(c2)->getValue()){
        return false;
      }
    }
  }
  return true;
}
