// Header for the worklist algorithm/analysis class.


// Standard Library
#include <map>
#include <list>
#include <utility>
#include <stack>
#include <stdlib.h>
#include <iostream>

// LLVM
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Function.h"

// Our Stuff
#include "LatticePoint.h"
#include "Lattice.h"
#include "FlowFunc.h"


class Analysis {
public:
  std::map<Instruction *, LatticePoint> analyze(Function &F, Lattice L, LatticePoint start, FlowFunction flowF);
private:
  std::pair<std::map<BasicBlock *, std::list<BasicBlock *> >,std::map<BasicBlock *, std::list<BasicBlock *> > > predecessorSuccessorMapConstructor(Function &F);
  bool applyBasicBlockFlowFunctions(std::map<std::pair<BasicBlock *, BasicBlock *>, LatticePoint> &edge_map, Lattice L, FlowFunction flowF, LatticePoint start, std::list<BasicBlock *> predecessors)
};

