#ifndef LATTICEPOINT_H_
#define LATTICEPOINT_H_

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/InstIterator.h"
#include <map>

class LatticePoint {
public:
  LatticePoint();
  LatticePoint(llvm::Instruction& instr, LatticePoint& point);
  virtual ~LatticePoint();

private:
  std::map<int, const LatticePoint *> instrMap;
  virtual bool equality (LatticePoint& in1, LatticePoint& in2) = 0;
};

#endif /* LATTICEPOINT_H_ */

