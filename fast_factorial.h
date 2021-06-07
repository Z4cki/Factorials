#ifndef FAST_FACTORIAL_H_
#define FAST_FACTORIAL_H_

#include <future>

#include <gmpxx.h>

typedef std::future<mpz_class> mpz_future;
typedef std::promise<mpz_class> mpz_promise;

int fastFactorial(const unsigned int n, const unsigned int threadCount);

void computeSection(mpz_promise&& promise, const int start,
    const int end, const int size);

void mergeResult(mpz_promise&& promise, mpz_future* first, 
    mpz_future* second);

#endif /* fast_factorial.h */