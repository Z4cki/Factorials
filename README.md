# Factorials
Calculate factorials of large numbers.  
Runs stable up to 100,000,000 for now.

## Currently updating this section

### TODO
1. Added Windows support in the makefile, update on how to build the program will follow soon
2. Improve computing algorithm
    - add multithreaded merging of intermediate results

### Build
Currently working on a detailed descreption for compilation for Windows. 
Compiling **ON** Windows is not possible at the moment.

Requires GMP [GNU Multiple Precision Library](https://gmplib.org/ "GMP Homepage").  
Make sure to configure GMP for C++ using 
- ```"./configure --enable-cxx"```
.

#### Build command:

You can either run:

- ~~```./build.sh```~~

- ```make``` (and optional ```make clean``` to remove any object files)

- ```mkdir -p bin && g++ src/factorial.cpp -o bin/factorial -pthread -lgmp -lgmpxx -std=c++17```

The executable ends up in bin/factorial
