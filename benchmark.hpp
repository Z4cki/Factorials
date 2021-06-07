#ifndef BENCHMARK_H_
#define BENCHMARK_H_

const int coreArray[] = { 
    16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192
};

const int coreArraySize = sizeof(coreArray) / sizeof(coreArray[0]);

int getFastestCoreCount(const unsigned int num);

short compareCoreCount(const unsigned int num, 
    const unsigned int core1, const unsigned int core2);

void testDifferentCoreCounts(const unsigned int num);

#endif /* benchmark.hpp */