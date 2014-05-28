// Header for the flow function classes.

// Very preliminary for now -- I have tried to define only the bare
// minimum functionality to make specifying the abstract worklist
// algorithm possible from a flow function perspective. See the
// README-flowfunc.md file for more on:
// 1. current design (such as it is)
// 2. planned design evolutions
// 3. implementation TODO structure


// Standard Library
#include <iostream>
#include <map>
#include <functional>

// LLVM
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/InstVisitor.h"

// Our Stuff
#include "lattices/LatticePoint.h"
#include "lattices/CPLatticePoint.h"


class FlowFunction {
public:
  // operation defined for all flow functions
  virtual LatticePoint operator()(llvm::Instruction& instr, std::vector<LatticePoint> info_in) = 0;
};

// it WOULD APPEAR that we can inherit from both the INTERFACE
// flowfunction, and the IMPLEMENTATION AID InstVisitor with a
// template. at least, this builds with no errors, and C++ does in
// fact allow multiple inheritance...

class BlahFlowFunction : public FlowFunction, public InstVisitor<BlahFlowFunction>{
public:
  unsigned Count;
  BlahFlowFunction() : Count(0) {}

  void visitAllocaInst(AllocaInst &AI) { ++Count; }
  LatticePoint operator()(llvm::Instruction& instr, std::vector<LatticePoint> info_in);
};
  
