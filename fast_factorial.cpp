#include "fast_factorial.hpp"

#include <chrono>
#include <iostream>
#include <thread>

/**
 * @brief Compute factorial
 * 
 * @param num number => !number
 * @param thread_count how many threads to be used
 * 
 * @return Status flag
 */
int fastFactorial(const unsigned int num,
    const unsigned int thread_count, double* timer)
{
    // No factorial to compute
    if (num == 0) 
    {
        printf("Nothing to do.");
        return -1;
    }
    
    // Start time measurement
    auto start_time = std::chrono::_V2::high_resolution_clock::now();

    const unsigned int pool_size = thread_count * 2 - 1;

    // Collection of promises and futures
    mpz_promise     promise_pool[pool_size];
    mpz_future      future_pool[pool_size];
    std::thread     thread_pool[pool_size];

    // Spread calculation on different threads
    for (unsigned int i = 0; i < thread_count; i++)
    {
        // Map futures <-> promises in the pools
        future_pool[i] = promise_pool[i].get_future();

        // Launch thread
        thread_pool[i] = std::thread(computeSection, 
            std::move(promise_pool[i]), i + 1, num, thread_count);
        
        // Release thread (get result via future)
        thread_pool[i].detach();
    }

    // Merge results
    for (unsigned int i = thread_count, j = 0; i < pool_size; i++, j+=2)
    {
        // Map futures : promises in the pools
        future_pool[i] = promise_pool[i].get_future();

        // Launch thread
        thread_pool[i] = std::thread(mergeResult,
            std::move(promise_pool[i]), &future_pool[j], &future_pool[j + 1]);

        // Release thread (get result via future)
        thread_pool[i].detach();
    }

    // Copy result
    auto result = future_pool[pool_size - 1].get();

    // Stop timer
    auto end_time = std::chrono::_V2::high_resolution_clock::now();
    auto elapsed_ms = (
            end_time.time_since_epoch().count() - 
            start_time.time_since_epoch().count()
        ) / 1000000.0;
    
    *timer = elapsed_ms;

    // Print result
    #ifdef PRINT_FACTORIAL
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