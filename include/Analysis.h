// Header for the worklist algorithm/analysis class.


// Standard Library
#include <map>
#include <list>
#include <utility>
#include <vector>
#include <stack>
#include <stdlib.h>
#include <iostream>

// LLVM
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Function.h"

// Our Stuff
#include "lattices/LatticePoint.h"
#include "flowFunctions/FlowFunction.h"
#include "flowFunctions/CPFlowFunction.h"
#include "flowFunctions/RAFlowFunction.h"
#include "flowFunctions/CSEFlowFunction.h"
#include <memory>

class Analysis {
public:
  static std::map<Instruction *, LatticePoint *> analyze(Function &F, LatticePoint *start, FlowFunction* flowF){
    
    // First we analyze at the BasicBlock level. Then we will push our results down to the instruction level.
    std::pair<std::map<BasicBlock *, std::list<BasicBlock *> >,std::map<BasicBlock *, std::list<BasicBlock *> > > pair_map = Analysis::predecessorSuccessorMapConstructor(F);
    std::map<BasicBlock *, std::list<BasicBlock *> > predecessor_map = pair_map.first;
    std::map<BasicBlock *, std::list<BasicBlock *> > successor_map = pair_map.second;
    
    std::map<std::pair<BasicBlock *, BasicBlock *>, LatticePoint *> edge_map;
    std::list<BasicBlock *> worklist;
    
    errs() << "\n Building worklist now \n";
    
    // We first initialize all edges to be bottom and add all basic block nodes to our worklist.
    for (Function::iterator BB = F.begin(), e = F.end(); BB != e; ++BB){
      worklist.push_back(BB);
      std::list<BasicBlock *> successors = successor_map[BB];
      for (std::list<BasicBlock *>::iterator Succ=successors.begin(); Succ!=successors.end(); ++Succ){
        std::pair<BasicBlock *, BasicBlock *> edge;
        edge = std::make_pair(BB, *Succ);
        LatticePoint bottom = LatticePoint(start->getKind(), true, false);
        edge_map[edge] = &bottom;
      }
    }
    
    errs() << "\n Done building worklist. Worklist has " << worklist.size() << " elements\n";
    
    errs() << "\n Iterating until convergence now. \n";

    
    // Now we apply flow functions until we hit a fixed point.
    while (!worklist.empty()){
      errs() << "\n In worklist iteration... \n";
      BasicBlock *BB = worklist.front();
      worklist.remove(BB); // Remove all instances of BB in the worklist (handles multiples)
      std::list<BasicBlock *> predecessors = predecessor_map[BB];
      std::list<BasicBlock *> successors = successor_map[BB];
      errs() << "\n About to apply BBFF \n";
      bool flag = applyBasicBlockFlowFunctions(BB, edge_map, flowF, start, predecessors, successors);
      errs() << "\n Done with BBFF \n";
      if (flag) {
        // We modified the outgoing edges, add all the successors to the worklist.
        std::list<BasicBlock *> successors = successor_map[BB];
        for (std::list<BasicBlock *>::iterator Succ=successors.begin(); Succ!=successors.end(); ++Succ){
          worklist.push_back(*Succ);
        }
      }
    }
    
    errs() << "\n Converged. Executing final push now. \n";

    
    // We are at a fixed point. Time to push through all the corresponding lattice points.
    std::map<Instruction *, LatticePoint *> result;
    for (Function::iterator BB = F.begin(), e = F.end(); BB != e; ++BB){
      std::list<BasicBlock *> predecessors = predecessor_map[BB];
      std::vector<LatticePoint *> inputs;
      if (predecessors.empty()){
        // We are dealing with the first basic block
        inputs.push_back(start);
      }
      else{
        // We are not dealing with the first basic block
        for (std::list<BasicBlock *>::iterator Pred=predecessors.begin(); Pred!=predecessors.end(); ++Pred) {
          std::pair<BasicBlock *, BasicBlock *> edge;
          edge = std::make_pair(*Pred, BB);
          inputs.push_back(edge_map[edge]);
        }
      }
      
      for (BasicBlock::iterator I = BB->begin(), e = BB->end(); I != e; ++I){
        if (inputs.size() > 1){
          inputs = Analysis::extendedJoin(inputs);
        }
        result[I] = inputs.front();
        inputs = applyFlowFunction(flowF, I, inputs);
      }
    }
    errs() << "\n Done. result has " << result.size() << " elements.\n";

    
    return result;
  }
  
  
  
  // Tested (works). Returns a pair of maps that gives the structure of the basic blocks.
  static std::pair<std::map<BasicBlock *, std::list<BasicBlock *> >,std::map<BasicBlock *, std::list<BasicBlock *> > > predecessorSuccessorMapConstructor(Function &F){
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
  static bool applyBasicBlockFlowFunctions(BasicBlock *BB, std::map<std::pair<BasicBlock *, BasicBlock *>, LatticePoint *> &edge_map, FlowFunction* flowF, LatticePoint *start, std::list<BasicBlock *> predecessors, std::list<BasicBlock *> successors){
    
    // We use vectors for passing lists of lattice points into flow functions.
    std::vector<LatticePoint *> inputs;
    if (predecessors.empty()){
      // We are dealing with the first basic block
      inputs.push_back(start);
    }
    else{
      // We are not dealing with the first basic block
      for (std::list<BasicBlock *>::iterator Pred=predecessors.begin(); Pred!=predecessors.end(); ++Pred) {
        std::pair<BasicBlock *, BasicBlock *> edge;
        edge = std::make_pair(*Pred, BB);
        inputs.push_back(edge_map[edge]);
      }
    }
    errs() << "\n In BBFF \n";
    for (BasicBlock::iterator I = BB->begin(), e = BB->end(); I != e; ++I){
      /*
       Hopefully we figure out how to coordinate the output of flow functions with the structure of the CFG.
       */
      errs() << "Working on instruction " << *I << "\n";
      inputs = applyFlowFunction(flowF, I, inputs);
      errs() << "Done with instruction " << *I << "\n";

      /*
       LatticePoint* output = flowF(*I, inputs); // Apply our FlowFunction to each instruction in order. The output becomes the new inputs for the next instruction.
       
       inputs = std::vector<LatticePoint *>();
       inputs.push_back(output);
       */
    }
    
    if (successors.size() != inputs.size()) {
      // Here the outgoing edges have identical LatticePoints.
      inputs = std::vector<LatticePoint *>(successors.size(), inputs.front());
    }
    int i = 0;
    bool result = false;
    for (std::list<BasicBlock *>::iterator Succ=successors.begin(); Succ!=successors.end(); ++Succ){
      std::pair<BasicBlock *, BasicBlock *> edge;
      edge = std::make_pair(BB, *Succ);
      LatticePoint* current_lp = inputs[i];
      result = result || current_lp->equals(edge_map[edge]);
      edge_map[edge] = current_lp;
      i++;
    }
    return result;
  }
  
  static std::vector<LatticePoint*> applyFlowFunction(FlowFunction* flowF, Instruction* I, std::vector<LatticePoint*> inputs){
    std::vector<LatticePoint*> outputs;
    if (isa<RAFlowFunction>(flowF)) {
      RAFlowFunction* f = cast<RAFlowFunction>(flowF);
      outputs = (*f)(I, inputs);
    }
    else if(isa<CPFlowFunction>(flowF)){
      CPFlowFunction* f = cast<CPFlowFunction>(flowF);
      outputs = (*f)(I, inputs);
    }
    else if(isa<CSEFlowFunction>(flowF)){
      CSEFlowFunction* f = cast<CSEFlowFunction>(flowF);
      outputs = (*f)(I, inputs);
    }
    else{
      errs() << "IN REALLY BAD CASE! \n";
    }
    return outputs;
  }
  
  
  /*
    Performs a join of all the lattice points in lps and returns a singleton vector.
   */
  static std::vector<LatticePoint*> extendedJoin(std::vector<LatticePoint *> lps){
    while (lps.size() > 1) {
      LatticePoint *l1 = lps.back();
      lps.pop_back();
      LatticePoint *l2 = lps.back();
      lps.pop_back();
      lps.push_back(l1->join(l2));
    }
    return lps;
  }
  
};

