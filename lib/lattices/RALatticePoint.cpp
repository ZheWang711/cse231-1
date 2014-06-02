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
  
  
  std::map<Value*, std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > > representation1 = this->representation;
  std::map<Value*, std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > > representation2 = in_casted->representation;
  
  std::map<Value*, std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > >result_map;
  
  std::set<Value *> key_set;
  for (std::map<Value*, std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > >::iterator it=representation1.begin(); it!=representation1.end(); ++it){
    Value* elm = it->first;
    key_set.insert(elm);
  }
  for (std::map<Value*, std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > >::iterator it=representation2.begin(); it!=representation2.end(); ++it){
    Value* elm = it->first;
    key_set.insert(elm);
  }
  
  for (std::set<Value *>::iterator it = key_set.begin(); it != key_set.end(); ++it){
    
    if (representation1.count(*it) > 0 && representation2.count(*it) > 0){
      std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > c1 = representation1[*it];
      std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > c2 = representation2[*it];
      
      
      bool isLeftInfinite = (c1.first).first || (c2.first).first;
      bool isRightInfinite = (c1.first).second || (c2.first).second;
      ConstantInt* lowerBound = NULL;
      ConstantInt* upperBound = NULL;
      if (!isLeftInfinite){
        if ((((c1.second).first)->getValue()).slt(((c2.second).first)->getValue())){
          lowerBound = ((c1.second).first);
        }
        else{
          lowerBound = ((c2.second).first);
        }
      }
      if (!isRightInfinite){
        if ((((c1.second).second)->getValue()).sgt(((c2.second).second)->getValue())){
          upperBound = ((c1.second).second);
        }
        else{
          upperBound = ((c2.second).second);
        }
      }
      result_map[*it] = std::make_pair(std::make_pair(isLeftInfinite, isRightInfinite), std::make_pair(lowerBound, upperBound));
      
    }
    
    if (representation1.count(*it) > 0 && representation2.count(*it) == 0){
      result_map[*it] = representation1[*it];
    }
    
    if (representation1.count(*it) == 0 && representation2.count(*it) > 0){
      result_map[*it] = representation2[*it];
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
  std::map<Value*, std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > > representation1 = this->representation;
  std::map<Value*, std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > > representation2 = in_casted->representation;
  
  for (std::map<Value*, std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > >::iterator it=representation1.begin(); it!=representation1.end(); ++it){
    Value* elm = it->first;
    std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > c1 = it->second;
    if (representation2.count(elm) <= 0){
      return false;
    }
    else{
      std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > c2 = representation2[elm];
      bool isLeftInfinite = (c1.first).first || (c2.first).first;
      bool isRightInfinite = (c1.first).second || (c2.first).second;
      
      if (isLeftInfinite && (c1.first).first != (c2.first).first){
        return false;
      }
      if (isRightInfinite && (c1.first).second != (c2.first).second){
        return false;
      }
      if (!isLeftInfinite && (c1.second).first->getValue() != (c2.second).first->getValue()){
        return false;
      }
      if (!isRightInfinite && (c1.second).second->getValue() != (c2.second).second->getValue()){
        return false;
      }
    }
  }
  return true;
}

std::string RALatticePoint::LPprint() {
	std::stringstream ss;
  ss << "--> RP: isBottom: " << this->isBottom << ", isTop: " << this->isTop << "\n";
  if (this->isBottom || this->isTop){
    return ss.str();
  }
  
	ss << "{ ";
	for(std::map<Value*, std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > >::iterator it = this->representation.begin(); it != representation.end(); ++it) {
		Value* val = it->first;
		std::pair<std::pair<bool, bool>, std::pair<ConstantInt *, ConstantInt *> > range = it->second;
    bool isLeftInfinite = (range.first).first;
    bool isRightInfinite = (range.first).second;
    ss << val << ": ";
    if (isLeftInfinite && isRightInfinite){
      ss << "(-infinite, infinite)";
    }
    else if (isLeftInfinite && !isRightInfinite){
      ss << "(-infinite, ";
      ss << (range.second.first->getValue()).toString(10, true);
      ss << " )";
    }
    else if (!isLeftInfinite && isRightInfinite){
      ss << "( ";
      ss << (range.second.second->getValue()).toString(10, true);
      ss << ", infinite)";
    }
    else if (isLeftInfinite && !isRightInfinite){
      ss << " --> (-infinite, ";
      ss << (range.second.first->getValue()).toString(10, true);
      ss << " )";
    }
    else{
      ss << "( ";
      ss << (range.second.first->getValue()).toString(10, true);
      ss << " , ";
      ss << (range.second.second->getValue()).toString(10, true);
      ss << " )";
    }
		ss << ", ";
  }
  ss << " } \n";
  return ss.str();
}
