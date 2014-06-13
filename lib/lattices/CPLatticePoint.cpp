#include "lattices/CPLatticePoint.h"
// #include "lattices/LatticePoint.h"

// CPLatticePoint::CPLatticePoint(){
//   LatticePoint( LPK_CPLatticePoint);
//   this.isBottom = false;
//   this.isTop = false;
//   this.representation = std::map<Value*, ConstantInt*>()
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
  
  std::map<Value *, ConstantInt *> representation1 = this->representation;
  std::map<Value *, ConstantInt *> representation2 = in_casted->representation;
  
  std::map<Value *, ConstantInt *> result_map;
  
  for (std::map<Value *, ConstantInt *>::iterator it=representation1.begin(); it!=representation1.end(); ++it){
    Value* elm = it->first;
    ConstantInt* c1 = it->second;
    if (representation2.count(elm) > 0){
      ConstantInt* c2 = representation2[elm];
      if (c1 == c2){
        result_map[elm] = c1;
      }
    }
  }
  CPLatticePoint* result = new CPLatticePoint(false, false, std::map<Value*, ConstantInt*>(result_map));
  return result;
}




bool CPLatticePoint::equals(LatticePoint* in){
  if (in->isBottom || this->isBottom){
    return in->isBottom == this->isBottom;
  }
  CPLatticePoint* in_casted =  dyn_cast<CPLatticePoint>(in);
  std::map<Value *, ConstantInt *> representation1 = this->representation;
  std::map<Value *, ConstantInt *> representation2 = in_casted->representation;
  
  for (std::map<Value *, ConstantInt *>::iterator it=representation1.begin(); it!=representation1.end(); ++it){
    Value* elm = it->first;
    ConstantInt* c1 = it->second;
    if (representation2.count(elm) <= 0){
      return false;
    }
    else{
      ConstantInt* c2 = representation2[elm];
      if (c1 != c2){
        return false;
      }
    }
  }
  return true;
}

std::string CPLatticePoint::LPprint() {
	std::stringstream ss;
    ss << "\nCP: isBottom: " << this->isBottom << ", isTop: " << this->isTop << "\n";
	ss << "{ ";
	for(std::map<Value*, ConstantInt*>::iterator it = this->representation.begin(); it != representation.end(); ++it) {
		Value* val = it->first;
		ConstantInt* con = it->second;
                if (val->getName().size() < 10)
                  ss << val->getName().str();
                else 
                  ss << val->getValueName();
		ss << ": " << con->getValue().toString(10,true) << ", ";
    }
    ss << " }\n";
    return ss.str();
}
