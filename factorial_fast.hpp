#ifndef FACTORIAL_FAST_H_
#define FACTORIAL_FAST_H_

#include <future>

#include <gmpxx.h>

typedef std::future<mpz_class> mpz_future;
typedef std::promise<mpz_class> mpz_promise;

int fastFactorial(const unsigned int num,
    const unsigned int thread_count, double* timer);

void computeSection(mpz_promise&& promise, const int start,
    const int end, const int size);

void mergeResult(mpz_promise&& promise, mpz_future* first, 
    mpz_future* second);

#endif /* factorial_fast.hpp */