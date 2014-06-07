#include "lattices/CSELatticePoint.h"

// Define join method.
LatticePoint* CSELatticePoint::join(LatticePoint* in){
  
  if (in->isBottom){
    return this;
  }
  if (this->isBottom) {
    return in;
  }
  
  CSELatticePoint* in_casted =  dyn_cast<CSELatticePoint>(in);
  
  std::map<Value*, Instruction*> representation1 = this->representation;
  std::map<Value*, Instruction*> representation2 = in_casted->representation;
  
  std::map<Value*, Instruction*> result_map;
  
  for (std::map<Value *, Instruction *>::iterator it=representation1.begin(); it!=representation1.end(); ++it){
    Value* elm = it->first;
    Instruction* c1 = it->second;
    if (representation2.count(elm) > 0){
      Instruction* c2 = representation2[elm];
      if (c1 == c2){
        result_map[elm] = c1;
      }
    }
  }
  CSELatticePoint* result = new CSELatticePoint(false, false, result_map);
  return result;
}



bool CSELatticePoint::equals(LatticePoint* in){
  // I don't know if this works. What if the maps have equal elements
  // but in a different order? Will C++ stl traverse maps that are
  // identical in the same order? This code relies on that assumption
  // which I cannot currently verify.
  if (in->isBottom || this->isBottom){
    return in->isBottom == this->isBottom;
  }
  CSELatticePoint* in_casted =  dyn_cast<CSELatticePoint>(in);
  std::map<Value*, Instruction*> representation1 = this->representation;
  std::map<Value*, Instruction*> representation2 = in_casted->representation;
  
  for (std::map<Value*, Instruction*>::iterator it=representation1.begin(); it!=representation1.end(); ++it){
    Value* elm = it->first;
    Instruction* i1 = it->second;
    if (representation2.count(elm) <= 0){
      return false;
    }
    else{
      Instruction* i2 = representation2[elm];
      // here, we want to be using actual pointer equality... not
      // instruction equality.
      if (i1 != i2){
        return false;
      }
    }
  }
  return true;
}


void CSELatticePoint::printToErrs() {
  errs() << "CSELatticePoint: isBottom: " << this->isBottom << ", isTop: " << this->isTop << " | ";
  if (this->isBottom || this->isTop){
    errs() << "\n";
    return;
  }
  errs() << "{ ";
  for(std::map<Value*, Instruction*>::iterator it = this->representation.begin(); it != representation.end(); ++it) {
    Value* val = it->first;
    val->print(errs());
    errs() << "@" << val;
    errs() << " --> ";
    Instruction* instr = it->second;
    instr->print(errs());
    errs() << "@" << instr;
    errs() << ", \n";
  }
  errs() << " } \n";
  return;
}
