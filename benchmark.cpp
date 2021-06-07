#include "benchmark.hpp"

#include <chrono>
#include <iostream>

#include "fast_factorial.hpp"

int getFastestCoreCount(const unsigned int num)
{
    double testTimes[coreArraySize];

    // Start measuring time
    auto start = std::chrono::_V2::high_resolution_clock::now();

    for (int i = 0; i < coreArraySize; i++)
    {
        const auto coreCount = coreArray[i];
        printf("\tRun test for %d cores..\n", coreCount);

        double timer;
        fastFactorial(num, coreCount, &timer);
        testTimes[i] = timer;

        printf("\tFinished test: %.2f ms (%.2fs)\n\n", timer, timer / 1000.0);
    }

    // End time measurement
    auto end = std::chrono::_V2::high_resolution_clock::now();
    auto elapsed = (
        end.time_since_epoch().count() - 
        start.time_since_epoch().count()) / 1000000.0;

    printf("\nThe benchmark took %.2fms (%.2fs)\n", elapsed, elapsed / 1000.0);

    // TODO: return the fastest core count
    return 0;
}

/**
 * Compares the efficiency of two core counts for a factorial
 * 
 * @param num the number
 * @param core1 first core count
 * @param core2 second core count
 * 
 * @return -1, 0, 1 when:
 *              core1 < core2, 
 *              core1 == core2;
 *              core1 > core2
 */
short compareCoreCount(const unsigned int num,
    const unsigned int core1, const unsigned int core2)
{
    return 0;
}

void testDifferentCoreCounts(const unsigned int num)
{ }
