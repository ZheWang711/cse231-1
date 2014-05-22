Please examine in FlowFunc.h line 27. Thus "operator" definition
contained in the class FlowFunction means that a worklist algorithm
could have the declaration "..., FlowFunction F, ..." in its argument
list and then literally *call* the object F like so:

 F(instruction, lattice_point_whatever)

TODO

1. Implement the flow function "operator()" in the FlowFunction base
class but do not implement a constructor in the base class. 

2. For each analysis, implement a constructor that populates the
LocalFunctions map with opcode -> function mappings

3. Create the functions populating LocalFunctions with lambda
statements that specify a CONCRETE SUBCLASS of lattice point in their
arguments, not LatticePoint.

I suspect that this is the least insane way to accomplish what we
want.