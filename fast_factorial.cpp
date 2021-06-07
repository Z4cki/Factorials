#include "fast_factorial.h"

#include <chrono>
#include <iostream>
#include <thread>

/**
 * @brief Compute factorial
 * 
 * @param n number => !number
 * @param threadCount how many threads to be used
 * 
 * @return Status flag
 */
int fastFactorial(const unsigned int n, const unsigned int threadCount)
{
    // No factorial to compute
    if (n == 0) 
    {
        printf("Nothing to do.");
        return -1;
    }
    
    // Start time measurement
    auto startTime = std::chrono::_V2::high_resolution_clock::now();

    const unsigned int poolSize = threadCount * 2 - 1;

    // Collection of promises and futures
    mpz_promise     promisePool[poolSize];
    mpz_future      futurePool[poolSize];
    std::thread     threadPool[poolSize];

    // Spread calculation on different threads
    for (unsigned int i = 0; i < threadCount; i++)
    {
        // Map futures <-> promises in the pools
        futurePool[i] = promisePool[i].get_future();

        // Launch thread
        threadPool[i] = std::thread(computeSection, 
            std::move(promisePool[i]), i + 1, n, threadCount);
        
        // Release thread (get result via future)
        threadPool[i].detach();
    }

    // Merge results
    for (unsigned int i = threadCount, j = 0; i < poolSize; i++, j+=2)
    {
        // Map futures : promises in the pools
        futurePool[i] = promisePool[i].get_future();

        // Launch thread
        threadPool[i] = std::thread(mergeResult,
            std::move(promisePool[i]), &futurePool[j], &futurePool[j + 1]);

        // Release thread (get result via future)
        threadPool[i].detach();
    }

    // Copy result
    auto result = futurePool[poolSize - 1].get();

    // Stop timer
    auto endTime = std::chrono::_V2::high_resolution_clock::now();
    auto elapsed = (
            endTime.time_since_epoch().count() - 
            startTime.time_since_epoch().count()
        ) / 1000000.0;
    printf("Calculation took %f ms.\n", elapsed);

    #ifdef PRINT_FACTORIAL
    // Print result
    gmp_printf("%Zd\n", result);
    #endif

    return 0;
}

/**
 * @brief Calculate a range
 * 
 * Compute a part of the factorial with a given range and step size.
 * We don't want to multiply a number twice, so for every invocation
 * start grows by one up to the step count.
 * 
 * @param promise The result of the computation
 * @param start Start of the range
 * @param end End of the range
 * @param step The step size
 */
void computeSection(mpz_promise&& promise, int start,
    const int end, const int step)
{
    mpz_class n = 1;
    for (; start <= end; start += step) n *= start;
    promise.set_value(n);
}

/**
 * @brief Merge two numbers
 * 
 * Await for two futures and merges the stored numbers.
 * 
 * @param promise The result of the computation
 * @param fa The first future
 * @param fb The second future
 */
void mergeResult(mpz_promise&& promise, mpz_future* fa,
    mpz_future* fb)
{
    promise.set_value(fa->get() * fb->get());
}