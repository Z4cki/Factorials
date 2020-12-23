#include <chrono>
#include <future>
#include <iostream>
#include <thread>

#include <gmpxx.h>
#include "measure_time.h"

mpz_class Calculate(int start, int number, uint cores);

template<typename T>
bool IsFutureFinished(std::future<T> const& f);

const uint core_count = std::thread::hardware_concurrency();
const char* debug_msg = "Thread finished";

int main()
{
    int number;
    std::cout << "Enter number: ";

    std::cin >> number;
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');

    // measure time
    debug::db_timer timer;

    std::future<mpz_class> futures[core_count];

    for (int i = 0; i < core_count; i++)
    {
        futures[i] = std::async(std::launch::async, Calculate, i + 2, number, core_count);
    }

    // collect all futures
    // not "blocking" the main thread by checking which future 
    // finished and doing work with them
    mpz_class result = 1;
    {
        int i = 0;
        while (i < core_count)
        {   
            for (int j = 0; j < core_count; j++)
            {
                if(IsFutureFinished(futures[j]))
                    result *= futures[j].get();
                    futures[j] = {};
                    i++;
            }
        }
    }

    //stop measuring time
    timer.end();

    //gmp_printf("%Zd\n", result);

    return 0;
}

/**
 *  Function to multiply numbers starting with start, in steps of "cores".
 *  We split up the calculation onto different processing cores and 
 *  count upwards the same steps, but with different starting points to not 
 *  multiply any numbers twice.
 * 
 *  for example: (with 2 cores)
 * 
 *  Core 1: 1 * 3 * 5 * 7 ... <= number 
 *  Core 2:   2 * 4 * 6 * ... <= number
 *  .
 *  .
 *  .
 * 
 *  @param start    To split the calculation in different parts we start with
 *                  numbers on different cores.
 *  @param number   Number entered by user to calculate the factorial for.
 *  @param cores    The count of cores used to caclulate a result. Here to count up 
 *                  in the for()-loop to even out the load on the cores.
 */
mpz_class Calculate(int start, int number, uint cores)
{
    debug::db_timer timer;
    mpz_class n = 1;
    for (int i = start; i <= number; i+=cores) n *= i;
    timer.end(debug_msg);
    return n;
}

template<typename T>
bool IsFutureFinished(std::future<T> const& f)
{
    if (!f.valid()) return false;
    return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}