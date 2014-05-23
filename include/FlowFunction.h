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

// Our Stuff
#include "lattices/LatticePoint.h"
#include "lattices/Lattice.h"

class FlowFunction {
  // map from opcodes to local flow functions
  std::map<int, std::function<LatticePoint(llvm::Instruction&, std::vector<LatticePoint>)> > LocalFunctions;
public:
  // operation defined for all flow functions
  LatticePoint operator()(llvm::Instruction& instr, std::vector<LatticePoint> info_in);
};

class BlahFlowFunction : FlowFunction{
public:
  BlahFlowFunction();
};
  