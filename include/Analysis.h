// Header for the worklist algorithm/analysis class.


// Standard Library
#include <map>
#include <list>
#include <utility>
#include <vector>
#include <stack>
#include <stdlib.h>
#include <iostream>
#include <memory>


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
#include "flowFunctions/PAFlowFunction.h"

class Analysis {
public:
  static std::map<Instruction *, LatticePoint *> analyze(Function &F, LatticePoint *start, FlowFunction* flowF){
    
    // First we analyze at the BasicBlock level. Then we will push our results down to the instruction level.
    std::pair<std::map<BasicBlock *, std::list<BasicBlock *> >,std::map<BasicBlock *, std::list<BasicBlock *> > > pair_map = Analysis::predecessorSuccessorMapConstructor(F);
    std::map<BasicBlock *, std::list<BasicBlock *> > predecessor_map = pair_map.first;
    std::map<BasicBlock *, std::list<BasicBlock *> > successor_map = pair_map.second;
    
    std::map<std::pair<BasicBlock *, BasicBlock *>, LatticePoint *> edge_map;
    std::list<BasicBlock *> worklist;
    
    //errs() << "\n Building worklist now \n";
    
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
    
    //errs() << "\n Done building worklist. Worklist has " << worklist.size() << " elements\n";
    
    //errs() << "\n Iterating until convergence now. \n";

    
    // Now we apply flow functions until we hit a fixed point.
    while (!worklist.empty()){
      BasicBlock *BB = worklist.front();
      worklist.remove(BB); // Remove all instances of BB in the worklist (handles multiples)
      std::list<BasicBlock *> predecessors = predecessor_map[BB];
      std::list<BasicBlock *> successors = successor_map[BB];
      bool flag = applyBasicBlockFlowFunctions(BB, edge_map, flowF, start, predecessors, successors);
      if (flag) {          // We modified the outgoing edges, add all the successors to the worklist.
        std::list<BasicBlock *> successors = successor_map[BB];
        for (std::list<BasicBlock *>::iterator Succ=successors.begin(); Succ!=successors.end(); ++Succ){
          worklist.push_back(*Succ);
        }
      }
    }
    
    //errs() << "\n Converged. Executing final push now. \n";

    
    // We are at a fixed point. Time to push through all the corresponding lattice points.
    std::map<Instruction *, LatticePoint *> result;
    for (Function::iterator BB = F.begin(), e = F.end(); BB != e; ++BB){
      std::list<BasicBlock *> predecessors = predecessor_map[BB];
      std::vector<LatticePoint *> inputs;
      if (predecessors.empty()){          // We are dealing with the first basic block
        inputs.push_back(start);
      }
      else{                               // We are not dealing with the first basic block
        for (std::list<BasicBlock *>::iterator Pred=predecessors.begin(); Pred!=predecessors.end(); ++Pred) {
          std::pair<BasicBlock *, BasicBlock *> edge = std::make_pair(*Pred, BB);
          inputs.push_back(edge_map[edge]);
        }
      }
    
      
      TerminatorInst* TI = BB->getTerminator();
      for (BasicBlock::iterator I = BB->begin(); !I->isTerminator(); ++I){ // Iteratively apply the flow function until we get to the terminator of BB.
        if (inputs.size() > 1){
          inputs = Analysis::extendedJoin(inputs);
        }
        result[I] = inputs.front();
        inputs = applyFlowFunction(flowF, I, inputs);
      }
      
      // One more time for the terminator.
      result[TI] = inputs.front();
    }
    
    return result;
  }
  
  
  /*
   Input: A function F.
   Output: A pair of maps. The first map is from basic blocks to the predecessors of that basic block. 
           The second map is from basic blocks to the successors of that basic block.
   */
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
  
  
  /*
   Input: a basic block, a reference to a map from edges between basic blocks to lattice points, a flow function, 
    a starting lattice point, a list of predecessors of the basic block, a list of successors of the basic block.
   
   Behavior: Modifies the outgoing edges from the current basic block to its successors. It takes as input the edges
    coming in from the predecessors. It applies the flow function to each of the instructions of the basic block in turn.
   
   Output: Returns true if any of the edges leaving the basic block are modified.
   */
  
  static bool applyBasicBlockFlowFunctions(BasicBlock *BB, std::map<std::pair<BasicBlock *, BasicBlock *>, LatticePoint *> &edge_map, FlowFunction* flowF, LatticePoint *start, std::list<BasicBlock *> predecessors, std::list<BasicBlock *> successors){
    
    // Setup our input vector and out successor_map.
    std::vector<LatticePoint *> inputs;
    std::map<Value *, LatticePoint *> successor_map;
    for (std::list<BasicBlock *>::iterator Succ=successors.begin(); Succ!=successors.end(); ++Succ){
      successor_map[*Succ] = NULL;
    }
    
    if (predecessors.empty()){ // We are in the first basic block. Thus we only have one input edge.
      inputs.push_back(start);
    }
    else{   // We are not dealing with the first basic block. So we need to add all the input edges.
      for (std::list<BasicBlock *>::iterator Pred=predecessors.begin(); Pred!=predecessors.end(); ++Pred) {
        std::pair<BasicBlock *, BasicBlock *> edge;
        edge = std::make_pair(*Pred, BB);
        inputs.push_back(edge_map[edge]);
      }
    }

    TerminatorInst* TI = BB->getTerminator();
    for (BasicBlock::iterator I = BB->begin(); !I->isTerminator(); ++I){ // Iteratively apply the flow function until we get to the terminator of BB.
      inputs = applyFlowFunction(flowF, I, inputs);
    }
    
    // Now apply the flow function to the terminator instruction.
    successor_map = applyFlowFunction(flowF, TI, inputs, successor_map);
    
    bool result = false;
    for (std::list<BasicBlock *>::iterator Succ=successors.begin(); Succ!=successors.end(); ++Succ){
      std::pair<BasicBlock *, BasicBlock *> edge;
      edge = std::make_pair(BB, *Succ);
      LatticePoint* current_lp = successor_map[*Succ];
      result = result || (!current_lp->equals(edge_map[edge]));
      edge_map[edge] = current_lp;
    }
    return result;
  }
  
  /*
   This case handles non-terminator instructions.
   
   */
  
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
    else if(isa<PAFlowFunction>(flowF)){
      PAFlowFunction* f = cast<PAFlowFunction>(flowF);
      outputs = (*f)(I, inputs);
    }
    else{
      errs() << "IN REALLY BAD CASE! \n";
    }
    return outputs;
  }
  
  /*
    This case handles terminator instructions. We only do this for Range analysis. Everything else does the normal stuff.
   */
  
  static std::map<Value *, LatticePoint *> applyFlowFunction(FlowFunction* flowF, Instruction* I, std::vector<LatticePoint*> inputs,std::map<Value *, LatticePoint *> successor_map){
    std::map<Value *, LatticePoint *> outputs;
    if (isa<RAFlowFunction>(flowF)) { // Implemented for RAFlowFunctions!
      RAFlowFunction* f = cast<RAFlowFunction>(flowF);
      outputs = (*f)(I, inputs, successor_map);
    }
    else if(isa<CPFlowFunction>(flowF)){ // Not implemented here. We do a hack to make it work.
      std::vector<LatticePoint*> temp;
      CPFlowFunction* f = cast<CPFlowFunction>(flowF);
      temp = (*f)(I, inputs);
      for (std::map<Value*, LatticePoint*>::iterator it=successor_map.begin(); it!=successor_map.end(); ++it){
        Value* elm = it->first;
        outputs[elm] = temp.front();
      }
    }
    else if(isa<CSEFlowFunction>(flowF)){ // Not implemented here. We do a hack to make it work.
      std::vector<LatticePoint*> temp;
      CSEFlowFunction* f = cast<CSEFlowFunction>(flowF);
      temp = (*f)(I, inputs);
      for (std::map<Value*, LatticePoint*>::iterator it=successor_map.begin(); it!=successor_map.end(); ++it){
        Value* elm = it->first;
        outputs[elm] = temp.front();
      }
    }
    else if(isa<PAFlowFunction>(flowF)){ // Not implemented here. We do a hack to make it work.
      std::vector<LatticePoint*> temp;
      PAFlowFunction* f = cast<PAFlowFunction>(flowF);
      temp = (*f)(I, inputs);
      for (std::map<Value*, LatticePoint*>::iterator it=successor_map.begin(); it!=successor_map.end(); ++it){
        Value* elm = it->first;
        outputs[elm] = temp.front();
      }
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
      LatticePoint* result = l1->join(l2);
      lps.push_back(result);
    }
    return lps;
  }
  
};

