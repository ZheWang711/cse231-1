#ifndef FLOWFUNCTION_H_
#define FLOWFUNCTION_H_

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
  enum FlowFunctionKind {
    FFK_CPFlowFunction,
    FFK_RAFlowFunction,
    FFK_CSEFlowFunction
  };

  FlowFunctionKind getKind() const { return Kind; }

  FlowFunction(FlowFunctionKind K) : Kind(K) {}

  // operation defined for all flow functions
  virtual std::vector<LatticePoint *> operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in);

private:
  FlowFunctionKind Kind;
};


#endif /* FLOWFUNCTION_H_ */

