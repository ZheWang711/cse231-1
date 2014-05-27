# Requirements #
	
Implement four analyses and optimizations that use these analyses,
using the LLVM compiler framework. There is some ambiguity here, as it
was implied in class at one point that we are only *required* to
implement the analyses. Either way, the analyses are a pre-requisite
for the transformations, so here is the list:

	1. Constant Propagation	
	2. Available Expressions
	3. Range Analysis
	4. Intra-Procedural Pointer Analysis
	
Our task is complicated by the additional requirement that each
analysis must be improved by the pointer analysis. That is, we must
make the results of pointer analysis available to each subsequent
analysis. This complicates the definition of the FlowFunction class
and necessitates the use of [LLVM features for sharing information
between analyses](http://llvm.org/docs/WritingAnLLVMPass.html#specifying-interactions-between-passes)

# Analysis Object Hierarchy #

Each analysis is specified by four objects, which inherit from:

	1. Lattice
	2. LatticePoint
	3. llvm::FunctionPass
	4. FlowFunction
	
These objects are organized by superclass in the lib subdirectory. The
role of the Lattice, LatticePoint, and FlowFunction classes is obvious
from an understanding of Data Flow Analysis. The role of the
llvm::FunctionPass object is to instantiate these "algorithmic"
objects, and then pass them to a generalized Worklist algorithm (a
seperate library, also stored in the lib/ directory). The
llvm::FunctionPass object also co-ordinates the activities of multiple
passes, using the LLVM features linked above.

Each library contains the titular superclass and any inheriting
classes. Thus each analysis is spread out over four libraries and
source files, but is well-modularized.

Comment: it may be correct but insufficient to register each analysis
as a function pass, given that I assume we want to run on all the
functions in the program. This snippet of LLVM documentation: "All
FunctionPass execute on each function in the program independent of
all of the other functions in the program" seems to imply that running
a function pass with "opt" will automatically run on each function of
the input, but I have not tested this yet.
	   
## Lattices ##

### Constant Prop ###

This lattice seems simple enough, and so it will be my first target
for concrete implementation. Obvious first issues:

	1. In class we had this magical "Vars" set. What do we use for
	this in LLVM based implementation?
	
	2. Types. We will specify that we only handle constant integers
	for now and leave it at that?
	
	
I hope that calls to std::set is enough to implement this lattice,
once I figure out what "Vars" should be in terms of LLVM.

I suspect that the correct analog to "Vars" in terms of LLVM is
ValuePointers. The potential problem with this is, I don't know if
ValuePointers remain fixed across multiple analysis passes. If our
pass stores a map of ValuePointers to may-points-to information, but
the second pass that would use this information maps the operands of
instructions to different Value memory locations, then this won't
work. 

It would probably be insane if these values changed between passes --
from reading Analyses implemented in LLVM it looks like they use
members of the IR directly from previous passes. 

I will register the Hello pass and CountStaticInstruction pass
together to test this. 


# TODO #
 
	 1. Implement a concrete Lattice and LatticePoint
		
	 2. Use concrete Lattice class to test FlowFunction design 
		
	 3. alter FlowFunction design to take into account may-point-to
		analysis. I am unsure how to do this. Preliminary idea: a map
		from LLVM variable types to sets of LLVM variable types passed
		to each flow function?
