#include <iostream>
#include <future>

#include <gmpxx.h>
#include "measure_time.h"

mpz_class calculate(int start, int number, uint cores);

const auto core_count = std::thread::hardware_concurrency();

int main()
{
    int number;
    std::cout << "Enter number : " << std::endl;

    std::cin >> number;
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');

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
mpz_class calculate(int start, int number, uint cores)
{
    mpz_class n = 1;
    for (int i = start; i <= number; i+=cores)
    {
        n *= i;
    }
    return n;
}