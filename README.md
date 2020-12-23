# Factorials
Calculate factorials of large numbers.  
Runs stable up to 100,000,000 for now.


### Build 
Requires GMP [GNU Multiple Precision Library](https://gmplib.org/ "GMP Homepage").  
Make sure to configure GMP for C++ using 
- ```"./configure --enable-cxx"```
.

#### Build command:

You can either run:

- ```./build.sh```

- ```make``` (and optional ```make clean``` to remove any object files)

- ```mkdir -p bin && g++ src/factorial.cpp -o bin/factorial -pthread -lgmp -lgmpxx -std=c++17```

The executable ends up in bin/factorial
