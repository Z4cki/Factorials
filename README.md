# Factorials
Calculate factorials of large numbers
Runs stable up to 100,000,000 for now


## Build 
Requires GMP GNU Multiple Precision Library https://gmplib.org/
Make sure to configure GMP for C++ using 
- "./configure --enable-cxx"

### Build command:

g++ factorial.cpp -o factorial -pthread -lgmp -lgmpxx -std=c++17

or run the build.sh script from the terminal (note: output is in bin/)
