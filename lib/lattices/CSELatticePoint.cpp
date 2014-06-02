#include "lattices/CSELatticePoint.h"

// Define join method.
LatticePoint* CSELatticePoint::join(LatticePoint* in){
  
  if (in->isBottom){
    return this;
  }
  if (this->isBottom) {
    return in;
  }
  
  // CSELatticePoint* in_casted =  dyn_cast<CSELatticePoint>(in);
  
  // std::map<Value *, Constant *> representation1 = this->representation;
  // std::map<Value *, Constant *> representation2 = in_casted->representation;
  
  // std::map<Value *, Constant *> result_map;
  
  // for (std::map<Value *, Constant *>::iterator it=representation1.begin(); it!=representation1.end(); ++it){
  //   Value* elm = it->first;
  //   Constant* c1 = it->second;
  //   if (representation2.count(elm) > 0){
  //     Constant* c2 = representation2[elm];
  //     if (c1 == c2){
  //       result_map[elm] = c1;
  //     }
  //   }
  // }
  // CSELatticePoint* result = new CSELatticePoint(false, false, result_map);
  // return result;
  
  return in;
}



bool CSELatticePoint::equals(LatticePoint* in){
  // if (in->isBottom || this->isBottom){
  //   return in->isBottom == this->isBottom;
  // }
  // CSELatticePoint* in_casted =  dyn_cast<CSELatticePoint>(in);
  // std::map<Value *, Constant *> representation1 = this->representation;
  // std::map<Value *, Constant *> representation2 = in_casted->representation;
  
  // for (std::map<Value *, Constant *>::iterator it=representation1.begin(); it!=representation1.end(); ++it){
  //   Value* elm = it->first;
  //   Constant* c1 = it->second;
  //   if (representation2.count(elm) <= 0){
  //     return false;
  //   }
  //   else{
  //     Constant* c2 = representation2[elm];
  //     if (c1 != c2){
  //       return false;
  //     }
  //   }
  // }
  // return true;
  return false;
}

std::string CSELatticePoint::LPprint() {
  std::stringstream ss;
  ss << "\nCSE: isBottom: " << this->isBottom << ", isTop: " << this->isTop << "\n";
  // ss << "{ ";
  // for(std::map<Value*, Constant*>::iterator it = this->representation.begin(); it != representation.end(); ++it) {
  //   Value* val = it->first;
  //   Constant* con = it->second;
  //   ss << val << ": " << *(con->getUniqueInteger().getRawData()) << ", ";
  // }
  // ss << " }\n";
  return ss.str();
}
