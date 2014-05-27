#include "Analysis.h"

using namespace llvm;

namespace {
  std::map<Instruction *, LatticePoint> analyze(Function &F, Lattice L, LatticePoint start, FlowFunction flowF){
    
    // First we analyze at the BasicBlock level. Then we will push our results down to the instruction level.
    std::pair<std::map<BasicBlock *, std::list<BasicBlock *> >,std::map<BasicBlock *, std::list<BasicBlock *> > > pair_map = predecessorSuccessorMapConstructor(F);
    std::map<BasicBlock *, std::list<BasicBlock *> > predecessor_map = pair_map.first;
    std::map<BasicBlock *, std::list<BasicBlock *> > successor_map = pair_map.second;
    
    std::map<std::pair<BasicBlock *, BasicBlock *>, LatticePoint> edge_map;
    std::list<BasicBlock *> worklist;
    
    // We first initialize all edges to be bottom and add all basic block nodes to our worklist.
    for (Function::iterator BB = F->begin(), e = F->end(); BB != e; ++BB){
      worklist.push_back(BB);
      std::list<BasicBlock *> successors = successor_map[BB];
      for (std::list<BasicBlock *>::iterator Succ=successors.begin(); Succ!=successors.end(); ++Succ){
        std::pair<BasicBlock *, BasicBlock *> edge;
        edge = std::make_pair(BB, *Succ);
        edge_map[edge] = L.bottom;
      }
    }
    
    while (!worklist.empty()){
      BasicBlock *BB = worklist.front();
      worklist.remove(BB); // Remove all instances of BB in the worklist (handles multiples)
      std::list<BasicBlock *> predecessors = predecessor_map[BB];
      bool flag = applyBasicBlockFlowFunctions(edge_map, L, flowF, start, predecessors);
      if (flag) {
        // We modified the outgoing edges, add all the successors to the worklist.
      }
    }
  }
  
  
  
  // Tested (works). Returns a pair of maps that gives the structure of the basic blocks.
  std::pair<std::map<BasicBlock *, std::list<BasicBlock *> >,std::map<BasicBlock *, std::list<BasicBlock *> > > predecessorSuccessorMapConstructor(Function &F){
    std::map<BasicBlock *, std::list<BasicBlock *> > predecessors;
    std::map<BasicBlock *, std::list<BasicBlock *> > successors;
    for (Function::iterator BB = F.begin(), e = F.end(); BB != e; ++BB){
      const TerminatorInst *TInst = BB->getTerminator();
      for (unsigned I = 0, NSucc = TInst->getNumSuccessors(); I < NSucc; ++I) {
        BasicBlock *Succ = TInst->getSuccessor(I);
        successors[BB].push_front(Succ);
        predecessors[Succ].push_front(BB);
      }
    }
    std::pair<std::map<BasicBlock *, std::list<BasicBlock *> >,std::map<BasicBlock *, std::list<BasicBlock *> > > result;
    result = std::make_pair(predecessors,successors);
    return result;
  }
  
  // Returns TRUE if the exiting edges are modified.
  bool applyBasicBlockFlowFunctions(std::map<std::pair<BasicBlock *, BasicBlock *>, LatticePoint> &edge_map, Lattice L, FlowFunction flowF, LatticePoint start, std::list<BasicBlock *> predecessors){
    std::list<LatticePoint> inputs;
    if (predecessors.empty()){
      // We are dealing with the first basic block
      inputs.push_back(start);
    }
    else{
      // We are not dealing with the first basic block
      for (std::list<BasicBlock *>::iterator Pred=predecessors.begin(); Pred!=predecessors.end(); ++Pred) {
        std::pair<BasicBlock *, BasicBlock *> edge;
        edge = std::make_pair(*Pred, BB);
        inputs.push_back((*edge_map)[edge]);
      }
    }
    int i = 0;
    int s = BB->size();
    for (BasicBlock::iterator I = BB->begin(), e = BB->end(); I != e; ++I){
      inputs = flowF(I, inputs); // Apply our FlowFunction to each instruction in order. The outputs become the new inputs for the next instruction.
    }
    
    bool result = false;
    LatticePoint exit_lp = inputs.front();
    for (std::list<BasicBlock *>::iterator Succ=successors.begin(); Succ!=successors.end(); ++Succ){
      std::pair<BasicBlock *, BasicBlock *> edge;
      edge = std::make_pair(BB, Succ);
      result = result || (L.equality(exit_lp, (*edge_map)[edge]));
      (*edge_map)[edge] = exit_lp;
    }
    
    return result;
  }
  
    
}