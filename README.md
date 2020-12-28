# Factorials
Calculate factorials of large numbers.  
Runs stable up to 100,000,000 for now.

## Currently updating this section

### TODO
1. I added Windows support in the makefile, update on how to build the program will follow soon
2. Improve computing algorithm
-.. spread computing on more threads as returned by ```std::thread::hardware_concurrency()```
-.. add multithreaded merging of intermediate results

### Build
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
