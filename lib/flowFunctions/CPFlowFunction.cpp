#include "flowFunctions/CPFlowFunction.h"

LatticePoint CPFlowFunction::operator()(llvm::Instruction* instr, std::vector<LatticePoint *> info_in);