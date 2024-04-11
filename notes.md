# LLVM Pass Tutorial
> This note is mainly a summary of the blog post [LLVM For Grad Students](https://www.cs.cornell.edu/~asampson/blog/llvm.html).

## What is LLVM?
LLVM is a compiler infrastructure, which is super useful when you need to do stuffs with program (for analysis, transformation, etc.).

## The Pieces
LLVM can be divided to three components:
- the front end: deals with the parsing issues, which translates the source code to the LLVM IR (Intermediate Representation).

- the middle end: performs analysis and transformation on LLVM IR.

- the back end: emits target specific machine code from LLVM IR.

The most brilliant innovation of LLVM is the LLVM IR, which is well designed to be easily manipulated and visualized.

## Useful Docs
- [The doxygen pages](http://llvm.org/doxygen/): API Docs

- [Language Reference Manual](http://llvm.org/docs/LangRef.html): LLVM IR Syntax

- [The Programmer's Manual](http://llvm.org/docs/ProgrammersManual.html): Some information on LLVM toolchest, such as some utilities.

- [LLVM Writing a LLVM Pass Tutorial](http://llvm.org/docs/WritingAnLLVMPass.html): Official Tutorial on writing a LLVM Pass

- [LLVM Github Repo](https://github.com/llvm/llvm-project): for browsing the source code online.

## Understanding LLVM IR
LLVM IR Unit has a hierarchical structure:

- Module: a LLVM IR Module represents a translation unit, which contains several globals and function definitions.

- Function: a LLVM Function represents a function definition, which contains several basic blocks.

- Basic Block: a LLVM Basic Block represents a basic block, which contains several instructions.

- Instruction: a LLVM Instruction represents an instruction, which is a typed assembly instruction.

> Most things in LLVM—including Function, BasicBlock, and Instruction—are C++ classes that inherit from an omnivorous base class called Value. A Value is any data that can be used in a computation—a number, for example, or the address of some code. Global variables and constants (a.k.a. literals or immediates, like 5) are also Values.

## Writing a LLVM Pass
See [code](skeleton/Skeleton.cpp), which I think is pretty self-explanatory.

## Continuing
Some resources which look interesting:

- [llvm-tutor](https://github.com/banach-space/llvm-tutor)