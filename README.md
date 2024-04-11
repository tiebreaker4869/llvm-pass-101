# LLVM Pass 101
This repository contains simple code demonstrations of writing an LLVM pass, based on the blog post [LLVM for Grad Students](https://www.cs.cornell.edu/~asampson/blog/llvm.html).

This project is licensed under the [MIT License](LICENSE).

## Overview
LLVM is a powerful compiler infrastructure that can be leveraged for various program analysis and transformation tasks, beyond just implementing new compiler optimizations. This repository provides a starting point for graduate students and researchers to explore using LLVM in their own work.

## Usage
The main implementation code is located in skeleton/Skeleton.cpp. Configuring the build system can be a common pain point, but this repository aims to streamline that process so you can focus on the core LLVM pass development.

### Building the Pass
Use the following commands to build the project:

```shell
$ mkdir build
$ cd build
$ cmake ..
$ make
```
The commands above will produce a shared library (.so file) in the build directory, which contains the compiled LLVM pass. In this example, the output file will be named SkeletonPass.so.

### Running the Pass
To use the compiled pass when compiling a target C/C++ file, use the following command:

```shell
$ clang -fpass-plugin=`echo build/skeleton/SkeletonPass.*` target.c
```
Replace target.c with the path to your target source file.

### Linking with a Runtime Library
If your pass needs to interact with a runtime library, you can compile the runtime code to an object file (.o) and link it with the instrumented target code:

```shell
$ cc -c rtlib.c # The runtime functions are in rtlib.c
$ clang -fpass-plugin=`echo build/skeleton/SkeletonPass.*` -c target.c
$ cc target.o rtlib.o # Link the object files to produce the executable
$ ./a.out
```
This approach allows you to implement more complex runtime behaviors in C and integrate them with your LLVM pass.

## Additional Resources
The blog post provides valuable information on understanding LLVM IR, writing passes, and exploring advanced topics like annotations. We recommend referring to the original post for a more comprehensive introduction to working with LLVM.

Happy hacking!